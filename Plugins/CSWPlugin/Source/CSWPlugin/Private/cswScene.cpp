//*****************************************************************************
//
// Copyright (C) SAAB AB
//
// All rights, including the copyright, to the computer program(s)
// herein belong to SAAB AB. The program(s) may be used and/or
// copied only with the written permission of SAAB AB, or in
// accordance with the terms and conditions stipulated in the
// agreement/contract under which the program(s) have been
// supplied.
//
//
// Information Class:	COMPANY UNCLASSIFIED
// Defence Secrecy:		NOT CLASSIFIED
// Export Control:		NOT EXPORT CONTROLLED
//
//
// File			: cswScene.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Interface to StreamingMapPlugin
// Author		: Anders Modén		
// Product		: CSW 1.1.1
//		
//
//			
// NOTE:	CSW (Common Synthetic World) is a simulation and presentation
//			framework for large scale digital twins on multiple platforms
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	241107	Created file 							(1.1.1)
//
//******************************************************************************


#include "cswScene.h"
#include "cswFactory.h"


#include "UEGlue/cswUEMatrix.h"

#include "Geo/cswGeoModelComponent.h"
#include "Geo/cswGeoUTMComponent.h"
#include "Geo/cswGeoProjectedComponent.h"
#include "Geo/cswGeoGeodeticComponent.h"
#include "Geo/cswGeoGeocentricComponent.h"
#include "Geo/cswGeoFlatEarthComponent.h"

#include "gzCoordinate.h"


UCSWScene::UCSWScene(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer), m_indexLUT(1000),m_slots(GZ_QUEUE_LIFO,1000), m_components(1000)
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
	bAutoActivate = true;

	SetMobility(EComponentMobility::Movable);

	//GeoInfo = CreateDefaultSubobject<UCSWGeoModelComponent>(TEXT("GeoInfo"),true);

	// Register callbacks
	registerPropertyUpdate("MapUrls", &UCSWScene::onMapUrlsPropertyUpdate);
	registerPropertyUpdate("CoordType", &UCSWScene::onCoordTypePropertyUpdate);
	registerPropertyUpdate("CenterOrigin", &UCSWScene::onCenterOriginPropertyUpdate);

	registerComponent(this, nullptr, 0);	// Register root

	// Perform init of scenemanager 
	initSceneManager();

	// Perform init of resource manager 
	initResourceManager();
}

UCSWScene::~UCSWScene()
{
	if (m_manager)
	{
		m_manager->shutdown();

		// Cleanup while we have virtual members
		m_manager = nullptr;
	}
}

bool UCSWScene::isEditorComponent()
{
	AActor* owner = GetOwner();
	
	if (!owner)
		return false;

	return owner->HasAnyFlags(RF_Transactional);
}

void SubDestroy(USceneComponent* parent)
{
	TArray<USceneComponent*> SubComponents = parent->GetAttachChildren();

	for (USceneComponent* SubComp : SubComponents)
	{
		SubDestroy(SubComp);

		SubComp->DestroyComponent();
	}
}

void UCSWScene::BeginPlay()
{
	Super::BeginPlay();

	SubDestroy(this);

#if defined GZ_INSTRUMENT_CODE

	gzClearPerformanceSection("", 0);

	gzEnablePerformanceSections(true);

	gzStartPerformanceThread();

	gzSetPerformanceThreadName("main");

#endif // GZ_INSTRUMENT_CODE
}

void UCSWScene::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

#if defined GZ_INSTRUMENT_CODE

	gzStopPerformanceThread();

	gzDumpPerformanceInfo(/*GZ_PERF_DUMP_RUNNING |*/ GZ_PERF_DUMP_STOPPED | GZ_PERF_DUMP_ACCUMULATED_SECTIONS | GZ_PERF_DUMP_HIERARCHICAL_SECTIONS, GZ_MESSAGE_NOTICE);

	gzEnablePerformanceSections(false);

#endif // GZ_INSTRUMENT_CODE
}

void UCSWScene::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

	bool isActive = m_manager && m_manager->isRunning();

	// Transfer incoming to gamethread and don not wait for a frame
	fetchBuffers();

	// Work on buffers
	gzUInt32 frames(0);
	
	//Modify();
	{
		//FScopedMovementUpdate BatchUpdate(this);

		frames = processPendingBuffers(10, MaxPrimitivesPerFrame);
	}

	// Trigger next frame
	if(isActive && ((frames>0) || m_firstRun))
	{ 
		m_manager->addSingleCommand(new cswSceneCommandRefreshScene(gzTime::systemSeconds()));
		m_firstRun = false;
	}
}


void UCSWScene::initSceneManager()
{
	if (!m_manager)
	{
		m_manager = new cswSceneManager();

		// Do conversion in manager thread
		m_manager->enableCapabilities(CSW_CAPABILITY_CONVERT_TO_TRIANGLE|CSW_CAPABILITY_INDEX_GEOMETRY|CSW_CAPABILITY_REBUILD_INDEX_GEOMETRY);

		// Register us as receiver of scene commands
		m_manager->addCommandReceiver(this);

		// Commands
		cswCommandBufferPtr buffer = new cswCommandBuffer;

		// Initalize scenegraph
		buffer->addCommand(new cswSceneCommandInitialize(FALSE));

		// Set a property on culling
		buffer->addCommand(new cswSceneCommandSetOmniTraverse(FALSE));

		// Set number of loaders
		//buffer->addCommand(new cswSceneCommandSetLoaders(4));

		// Demo position for camera right now... Just to get data into frame
		buffer->addCommand(new cswSceneCommandPositionCamera(gzVec3D(336424, 131, -6580704), gzVec3(0, -10, 0)));

		m_manager->addCommandBuffer(buffer);
	}
}

void UCSWScene::initResourceManager()
{
	m_resource = new cswResourceManager;

	m_baseMaterial = m_resource->initializeBaseMaterial();
}

// lock and iterate over incoming commands and transfer them to game thread
bool UCSWScene::fetchBuffers(bool waitForFrame,gzUInt32 timeOut)
{
	gzPerformanceBody A("fetchBuffers");

	GZ_BODYGUARD(m_bufferInLock);

	while (true)
	{
		gzListIterator<cswCommandBuffer> iterator(m_bufferIn);
		cswCommandBuffer* buffer(nullptr);

		while ((buffer = iterator()))
		{
			m_pendingBuffers.insert(buffer);

			// We own the buffer soon. Lets set it to be deleted in node lock to protect ref data
			buffer->setBufferDeleteMode(CSW_BUFFER_DELETE_MODE_EDIT_LOCK);


			if (buffer->getBufferType() == CSW_BUFFER_TYPE_FRAME)
				waitForFrame = false;
		}

		// All data taken. Empty buffer
		m_bufferIn.clear();

		if (waitForFrame)
		{
			GZ_BODYGUARD_PAUSE(m_bufferInLock);

			// Wait for more

			// This section will wait timeout for more data that is fired()

			GZ_SIGNALGUARD(m_bufferInLock, timeOut);

			// Check if we didn't receive any more data async
			if (!m_bufferIn.entries())
				break;

			// We got more data. lets continue
			m_bufferInLock.reset();
		}
		else
			break;

		
	}

	return !waitForFrame;
}

// We will do all processing in GameThread so we will not start with threaded access to component lookup
gzUInt32 UCSWScene::processPendingBuffers(gzUInt32 maxFrames, gzUInt32 maxBuilds)
{
	GZ_INSTRUMENT_NAME("UCSWScene::processPendingBuffers");

	gzListIterator<cswCommandBuffer> iterator(m_pendingBuffers);
	cswCommandBuffer* buffer(nullptr);

	bool result(true);
	gzUInt32 frames(maxFrames);

	while ( (buffer = iterator()) && frames && maxBuilds)
	{
		/*if (buffer->entries() > 2)
		{
			gzString message = gzString::formatString("%s:Processed buffer out of type (%d) with %d commands", gzTime::now().asString(), buffer->getBufferType(), buffer->entries());

			cswScreenMessage(message);
		}*/

		switch (buffer->getBufferType())
		{
			case  CSW_BUFFER_TYPE_GENERIC:
				result = processGenericBuffer(buffer);
				break;

			case CSW_BUFFER_TYPE_ERROR:
				result = processErrorBuffer(buffer);
				break;

			case CSW_BUFFER_TYPE_FRAME:
				result = processFrameBuffer(buffer,frames);
				break;

			case CSW_BUFFER_TYPE_NEW:
				result = processNewBuffer(buffer,maxBuilds);
				break;

			case CSW_BUFFER_TYPE_DELETE:
				result = processDeleteBuffer(buffer);
				break;
		}

		if (result)					// If we handled the buffer ok we continue
			iterator.remove();
		else
			break;					// else we exit and let the system carry on smooth
	}

	return maxFrames - frames;
}

bool UCSWScene::processGenericBuffer(cswCommandBuffer* buffer)
{
	GZ_INSTRUMENT_NAME("UCSWScene::processGenericBuffer");

	if (!buffer->tryLockEdit())		// We failed to lock buffer
		return false;

	while (buffer->hasCommands())
	{
		cswSceneCommandPtr command = buffer->getCommand();
	}

	buffer->unLock();				// finished

	return true;
}

bool UCSWScene::processErrorBuffer(cswCommandBuffer* buffer)
{
	GZ_INSTRUMENT_NAME("UCSWScene::processErrorBuffer");

	// !!! No ref 3D data in errors so we dont lock and we delete in unlocked mode for performance

	while (buffer->hasCommands())
	{
		cswSceneCommandPtr command = buffer->getCommand();
	}

	buffer->setBufferDeleteMode(CSW_BUFFER_DELETE_MODE_UNLOCKED);

	return true;
}

bool UCSWScene::processFrameBuffer(cswCommandBuffer* buffer, gzUInt32& maxFrames)
{
	GZ_INSTRUMENT_NAME("UCSWScene::processFrameBuffer");

	if (!buffer->tryLockEdit())		// We failed to lock buffer
		return false;

	while (buffer->hasCommands() && maxFrames)
	{
		cswSceneCommandPtr command = buffer->getCommand();

		cswSceneCommandActivation* activation = gzDynamic_Cast<cswSceneCommandActivation>(command);

		if (activation)
		{
			if (!processActivation(activation))
				return false;
			
			continue;
		}

		cswSceneCommandStartFrame* startFrame = gzDynamic_Cast<cswSceneCommandStartFrame>(command);

		if (startFrame)
		{
			RenderTime = startFrame->getRenderTime();
			continue;
		}

		cswSceneCommandEndFrame* endFrame = gzDynamic_Cast<cswSceneCommandEndFrame>(command);

		
		--maxFrames;
		continue;

	}

	buffer->unLock();				// finished

	return !buffer->entries();		// return false if we have items left
}

bool UCSWScene::processDeleteBuffer(cswCommandBuffer* buffer)
{
	GZ_INSTRUMENT_NAME("UCSWScene::processDeleteBuffer");

	if (!buffer->tryLockEdit())		// We failed to lock buffer
		return false;

	bool result(true);

	while (buffer->hasCommands())
	{
		cswSceneCommandPtr command = buffer->getCommand();

		cswSceneCommandDeleteNode* deleteNode = gzDynamic_Cast<cswSceneCommandDeleteNode>(command);

		if (deleteNode)
		{
			if (!(result = processDeleteNode(deleteNode)))
				break;

			continue;
		}

		cswSceneCommandGeoInfo* geoInfo = gzDynamic_Cast<cswSceneCommandGeoInfo>(command);

		if (geoInfo)
		{
			if (!(result = processGeoInfo(geoInfo)))
				break;

			continue;
		}
	}

	buffer->unLock();				// finished

	return result;
}

bool UCSWScene::processNewBuffer(cswCommandBuffer* buffer, gzUInt32& maxBuilds)
{
	GZ_INSTRUMENT_NAME("UCSWScene::processNewBuffer");

	if (!buffer->tryLockEdit())		// We failed to lock buffer
		return false;

	bool result(true);

	while (buffer->hasCommands() && maxBuilds)
	{
		cswSceneCommandPtr command = buffer->getCommand();

		cswSceneCommandNewNode* newNode = gzDynamic_Cast<cswSceneCommandNewNode>(command);

		if (newNode)
		{
			if (!(result = processNewNode(newNode)))
				break;

			if(maxBuilds)
				--maxBuilds;

			if (!maxBuilds)
				result = false;

			continue;
		}

		cswSceneCommandGeoInfo* geoInfo = gzDynamic_Cast<cswSceneCommandGeoInfo>(command);

		if (geoInfo)
		{
			if(!(result = processGeoInfo(geoInfo)))
				break;

			continue;
		}
				
	}

	buffer->unLock();				// finished

	return result;
}

bool UCSWScene::processNewNode(cswSceneCommandNewNode* command)
{
	GZ_INSTRUMENT_NAME("UCSWScene::processNewNode");

	gzGroup* parentGroup = command->getParent();
	gzUInt64 parentPathID = command->getParentPathID();

	/*gzUInt64 debugParentPathID(0xffffffffff);

	if (parentGroup)
		gzDynamic_Cast(parentGroup->getAttribute("debug", "pathID"), debugParentPathID);*/


	UCSWSceneComponent* parent = getComponent(parentGroup, parentPathID);

	if (!parent)
	{
		GZMESSAGE(GZ_MESSAGE_FATAL, "Failed to get registered parent");
		return false;
	}
		
	gzNode* node = command->getNode();
	gzUInt64 pathID = command->getPathID();

	GZ_ENTER_PERFORMANCE_SECTION("UE:NewObject");

	UCSWSceneComponent* component = cswFactory::newObject(parent, node);

	GZ_LEAVE_PERFORMANCE_SECTION;

	if(!component)
	{
		GZMESSAGE(GZ_MESSAGE_FATAL, "Failed to get new component");
		return false;
	}

	{
		GZ_INSTRUMENT_NAME("UCSW*::build");
			

		if (!component->build(parent, node, command->getState(), m_buildProperties,m_resource))
		{
			GZMESSAGE(GZ_MESSAGE_FATAL, "Failed to build component");
			return false;
		}
	}

	GZ_ENTER_PERFORMANCE_SECTION("UE:RegisterComponent");
	component->RegisterComponent();
	GZ_LEAVE_PERFORMANCE_SECTION;

	if(!registerComponent(component, node, pathID))
	{
		GZMESSAGE(GZ_MESSAGE_FATAL, "Failed to register component");
		return false;
	}
	
	return true;
}

bool UCSWScene::processDeleteNode(cswSceneCommandDeleteNode* command)
{
	GZ_INSTRUMENT_NAME("UCSWScene::processDeleteNode");

	gzNode* node = command->getNode();
	gzUInt64 pathID = command->getPathID();


	UCSWSceneComponent* component = getComponent(node, pathID);

	if (!component)
	{
		GZMESSAGE(GZ_MESSAGE_FATAL, "Failed to get component for deletion");
		return false;
	}

	{
		GZ_INSTRUMENT_NAME("UCSW*::destroy");
		if (!component->destroy(node,m_resource))
		{
			GZMESSAGE(GZ_MESSAGE_FATAL, "Failed to destoy component");
			return false;
		}
	}

	GZ_ENTER_PERFORMANCE_SECTION("UE:DestroyComponent");
	component->DestroyComponent();
	GZ_LEAVE_PERFORMANCE_SECTION;

	if(!unregisterComponent(node,pathID))
	{
		GZMESSAGE(GZ_MESSAGE_FATAL, "Failed to unregister component");
		return false;
	}

	return true;
}

bool UCSWScene::processActivation(cswSceneCommandActivation* command)
{
	GZ_INSTRUMENT_NAME("UCSWScene::processActivation");

	gzNode* node = command->getNode();
	gzUInt64 pathID = command->getPathID();

	UCSWSceneComponent* component = getComponent(node, pathID);

	if (!component)
	{
		GZMESSAGE(GZ_MESSAGE_FATAL, "Failed to get component for activation");
		return false;
	}

	component->SetVisibility(command->getActivation() == ACTIVATION_ON,true);

	return true;
}

bool UCSWScene::processGeoInfo(cswSceneCommandGeoInfo* command)
{
	GZ_INSTRUMENT_NAME("UCSWScene::processGeoInfo");

	CoordSystem = command->getCoordinateSystem().getWideString();

	FVector3d UEOrigin;

	double scale = getWorldScale();

	if (!command->getCoordinateSystem())
	{
		// Empty. Plain Geometry
		CoordType = CoordType::Geometry;
		GeoOrigin = NewObject<UCSWGeoModelComponent>(this);
		UEOrigin = localToGlobal(command->getOrigin(), CoordType::Geometry);
	}
	else
	{

		gzCoordSystem system;

		gzCoordSystemMetaData meta;

		if (!gzCoordinate::getCoordinateSystem(command->getCoordinateSystem(), system, meta))
		{
			CoordType = CoordType::Geometry;
			GeoOrigin = NewObject<UCSWGeoModelComponent>(this);
			UEOrigin = localToGlobal(command->getOrigin(), CoordType::Geometry);
			GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to set interpret coordinate system %s", command->getCoordinateSystem());
			
		}
		else
		{

			switch (system.type)
			{
				case gzCoordType::GZ_COORDTYPE_GEOCENTRIC:
					CoordType = CoordType::Geocentric;
					GeoOrigin = NewObject<UCSWGeoGeocentricComponent>(this);
					UEOrigin = localToGlobal(command->getOrigin(), CoordType::Geocentric);
					break;

				case gzCoordType::GZ_COORDTYPE_GEODETIC:
					CoordType = CoordType::Geodetic;
					GeoOrigin = NewObject<UCSWGeoGeodeticComponent>(this);
					UEOrigin = localToGlobal(command->getOrigin(), CoordType::Geodetic);
					break;

				case gzCoordType::GZ_COORDTYPE_PROJECTED:
					CoordType = CoordType::Projected;
					GeoOrigin = NewObject<UCSWGeoProjectedComponent>(this);
					UEOrigin = localToGlobal(command->getOrigin(), CoordType::Projected);
					break;

				case gzCoordType::GZ_COORDTYPE_UTM:
					CoordType = CoordType::UTM;
					GeoOrigin = NewObject<UCSWGeoUTMComponent>(this);
					UEOrigin = localToGlobal(command->getOrigin(), CoordType::UTM);
					break;

				case gzCoordType::GZ_COORDTYPE_FLATEARTH:
					CoordType = CoordType::FlatEarth;
					GeoOrigin = NewObject<UCSWGeoFlatEarthComponent>(this);
					UEOrigin = localToGlobal(command->getOrigin(), CoordType::FlatEarth);
					break;

				default:
					CoordType = CoordType::Geometry;
					GeoOrigin = NewObject<UCSWGeoModelComponent>(this);
					UEOrigin = localToGlobal(command->getOrigin(), CoordType::Geometry);
					break;
			}
		}
	}

	GeoOrigin->setCoordinateSystem(command->getCoordinateSystem(), command->getOrigin());

	ModelOriginX = UEOrigin.X;
	ModelOriginY = UEOrigin.Y;
	ModelOriginZ = UEOrigin.Z;

	propertyUpdate("CoordType");

	return true;
}


// Register component
bool UCSWScene::registerComponent(UCSWSceneComponent* component, gzNode* node, gzUInt64 pathID)
{
	GZ_INSTRUMENT_NAME("UCSWScene::registerComponent");

	if (m_indexLUT.find(CSWPathIdentyIndex(node, pathID)))
		return false;

	gzUInt32 id;	// start from 0

	if (m_slots.entries())
	{
		id = m_slots.pop();
		m_components[id] = component;
	}
	else
	{
		id = m_components.getSize();
		m_components += component;
	}

	m_indexLUT.enter(CSWPathIdentyIndex(node, pathID), gzVal2Ptr(id + 1));

	return true;
}

// Unregister component
bool UCSWScene::unregisterComponent(gzNode* node, gzUInt64 pathID)
{
	GZ_INSTRUMENT_NAME("UCSWScene::unregisterComponent");

	gzVoid* res = m_indexLUT.find(CSWPathIdentyIndex(node, pathID));

	if (!res)
		return false;

	gzUInt32 id = gzPtr2Val(res) - 1;

	m_slots.push(id);
	m_components[id] = nullptr;

	m_indexLUT.remove(CSWPathIdentyIndex(node, pathID));

	return true;
}

UCSWSceneComponent* UCSWScene::getComponent(gzNode* node, gzUInt64 pathID)
{
	GZ_INSTRUMENT_NAME("UCSWScene::getComponent");

	gzVoid* res = m_indexLUT.find(CSWPathIdentyIndex(node, pathID));

	if (!res)
		return nullptr;

	return m_components[gzPtr2Val(res) - 1];
}

// Called by scene manager from custom threads
gzVoid UCSWScene::onCommand(cswCommandBuffer* buffer)
{
	GZ_BODYGUARD(m_bufferInLock);
	m_bufferIn.insert(buffer);			// add refs in locked mode by m_bufferInLock
	m_bufferInLock.fire();
}

bool UCSWScene::onMapUrlsPropertyUpdate()
{
	GZ_INSTRUMENT_NAME("UCSWScene::onMapUrlsPropertyUpdate");

	gzString mapURL = toString(MapUrls);

	if (mapURL.length())
	{
		if (!m_manager->isRunning())
		{
			// We got a map. lets start manager
			m_manager->run();
		}

		m_manager->addSingleCommand(new cswSceneCommandSetMapUrls(mapURL));
	}
	else
	{
		m_manager->addSingleCommand(new cswSceneCommandClearMaps());
	}
		
	return true;
}

bool UCSWScene::onCenterOriginPropertyUpdate()
{
	GZ_INSTRUMENT_NAME("UCSWScene::onCenterOriginPropertyUpdate");

	updateOriginTransform();

	return true;
}

bool UCSWScene::onCoordTypePropertyUpdate()
{
	GZ_INSTRUMENT_NAME("UCSWScene::onCoordTypePropertyUpdate");

	updateOriginTransform();

	return true;
}

void  UCSWScene::updateOriginTransform()
{
	FTransform m;

	// map SCENE content in Gizmo World to UE world

	gzVec3D origin;

	double scale = getWorldScale();

	switch (CoordType)
	{
		case CoordType::Geometry:
		case CoordType::Projected:
		case CoordType::UTM:
			origin = CenterOrigin ? globalToLocal(FVector3d(ModelOriginX, ModelOriginY, ModelOriginZ), CoordType::UTM) : GZ_ZERO_VEC3D;
			// Move children negative origin so our map origin ends up in 0,0,0
			m.SetFromMatrix(cswMatrix4_<double>::UEMatrix4(cswMatrix4_<double>::GZ_2_UE(-origin, scale)));
			break;

		case CoordType::Geodetic:
			break;

		case CoordType::Geocentric:
			m.SetFromMatrix(cswMatrix4_<double>::UEMatrix4(cswMatrix4_<double>::GZ_2_UE()));
			break;

		case CoordType::FlatEarth:
			m.SetFromMatrix(cswMatrix4_<double>::UEMatrix4(cswMatrix4_<double>::GZ_2_UE()));
			break;
	}

	SetRelativeTransform(m);
}

FVector3d UCSWScene::localToGlobal(const gzVec3D& local,enum CoordType type)
{
	double scale = getWorldScale();

	return cswVector3d::UEVector3(scale * (gzVec3D)(cswMatrix4_<double>::GZ_2_UE() * local));
}

gzVec3D UCSWScene::globalToLocal(const FVector3d& global, enum CoordType type)
{
	double scale = getWorldScale();

	return  (gzVec3D) (cswMatrix4_<double>::UE_2_GZ() * cswVector3d::GZVector3(global)) / scale ;
}

double UCSWScene::getWorldScale()
{
	if (GetWorld())
		return GetWorld()->GetWorldSettings()->WorldToMeters;	// Centimeters ?
	else
		return 100.0;
}


// Called after the C++ constructor and after the properties have been initialized, including those loaded from config.This is called before any serialization or other setup has happened.

void UCSWScene::PostInitProperties()
{
	Super::PostInitProperties();

	propertyUpdate();
}

//Do any object-specific cleanup required immediately after loading an object. This is not called for newly-created objects, and by default will always execute on the game thread.

void UCSWScene::PostLoad()
{
	Super::PostLoad();

	propertyUpdate();
}

#if WITH_EDITOR	// ------------------------------ EDITOR Only --------------------------------------

void UCSWScene::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (!PropertyChangedEvent.Property)
		return;

	FName PropName = PropertyChangedEvent.Property->GetFName();

	if (!propertyUpdate(PropName))
		GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to do a UCSWScene::PostEditChangeProperty on property (%s)", toString(PropName));
}

void UCSWScene::PostEditUndo()
{
	Super::PostEditUndo();

	propertyUpdate();
}

void UCSWScene::PostEditImport()
{
	Super::PostEditImport();

	propertyUpdate();
}

#endif // ------------------------------ EDITOR Only --------------------------------------

