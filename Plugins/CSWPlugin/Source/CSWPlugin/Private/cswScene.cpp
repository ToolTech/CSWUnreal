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
// Product		: CSW 1.1.2
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
#include "HAL/PlatformProcess.h"
#include "HAL/PlatformTime.h"
#include "Misc/ScopeLock.h"


#include "UEGlue/cswUEMatrix.h"
#include "UEGlue/cswUEUtility.h"

#include "Geo/cswGeoModelComponent.h"
#include "Geo/cswGeoUTMComponent.h"
#include "Geo/cswGeoProjectedComponent.h"
#include "Geo/cswGeoGeodeticComponent.h"
#include "Geo/cswGeoGeocentricComponent.h"
#include "Geo/cswGeoFlatEarthComponent.h"

// TODO: remove
#include "Builders/cswGeometry.h"

#include "gzCoordinate.h"


UCSWScene::UCSWScene(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer), m_indexLUT(IN_MEM_RESOURCE_COUNT),m_slots(GZ_QUEUE_LIFO, IN_MEM_RESOURCE_COUNT), m_components(IN_MEM_RESOURCE_COUNT)
{
	// Tick flags must be set on the CDO so instances inherit them
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	//PrimaryComponentTick.SetTickFunctionEnable(true);

	bTickInEditor = true;
	bAutoActivate = true;

	SetMobility(EComponentMobility::Movable);

	if (!IsTemplate())	// Avoid construction of threads and resources for CDO
	{
		// Register properties
		registerPropertyCallbacks();

		// Register root component
		registerComponent(this, nullptr, 0);

		// Perform init of scenemanager 
		initSceneManager();
	}
}

UCSWScene::~UCSWScene()
{
	unInitSceneManager();
}

void UCSWScene::registerPropertyCallbacks()
{
	// Register callbacks
	registerPropertyUpdate("MapUrls", &UCSWScene::onMapUrlsPropertyUpdate);
	registerPropertyUpdate("CoordType", &UCSWScene::onCoordTypePropertyUpdate);
	registerPropertyUpdate("CenterOrigin", &UCSWScene::onCenterOriginPropertyUpdate);
	registerPropertyUpdate("AllowCustomOrigin", &UCSWScene::onCenterOriginPropertyUpdate);
	registerPropertyUpdate("OmniView", &UCSWScene::onOmniViewPropertyUpdate);
	registerPropertyUpdate("LodFactor", &UCSWScene::onLodFactorPropertyUpdate);
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

	//// Test to drive a whole scene from begin play
	//for(gzUInt32 i = 0; i < 100; )
	//{
	//	i+=processFrames(m_firstRun);
	//	m_firstRun = false;
	//	gzSleep(1);
	//}

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

	// Drive the scene from tick

	/*gzUInt32 frames=processFrames(m_firstRun, m_firstRun ? false : true,10000);

	cswScreenMessage(gzString::formatString("processed frames:%d", frames));*/

	if (m_firstRun)
	{
		// Perform init of resource manager 
		initResourceManager();
	}

	processFrames(m_firstRun);
		
	m_firstRun = false;
}


void UCSWScene::initSceneManager()
{
	if (!m_manager)
	{
		m_manager = new cswUESceneManager();

		// Do conversion in manager thread
		m_manager->enableCapabilities(CSW_CAPABILITY_CONVERT_TO_TRIANGLE|CSW_CAPABILITY_INDEX_GEOMETRY/*|CSW_CAPABILITY_REBUILD_INDEX_GEOMETRY*/);

		// Register us as receiver of scene commands
		m_manager->addCommandReceiver(this);

		// Commands
		cswCommandBuffer* buffer = new cswCommandBuffer;

		// Initalize scenegraph
		buffer->addCommand(new cswSceneCommandInitialize(FALSE));

		// Set a property on culling
		buffer->addCommand(new cswSceneCommandSetOmniTraverse(OmniView));

		// Set camera setings
		buffer->addCommand(new cswSceneCommandCameraSettings(50,10000,TRUE));

		m_manager->addCommandBuffer(buffer);
	}
}

void UCSWScene::unInitSceneManager()
{
	// Empty graphics data

	m_pendingBuffers.clear();

	if (m_manager)
	{
		m_manager->shutdown();

		// Cleanup while we have virtual members
		m_manager = nullptr;
	}
}

void UCSWScene::initResourceManager()
{
	m_resource = new cswResourceManager;

	m_baseMaterial = m_resource->initializeBaseMaterial();
}

bool UCSWScene::processCameras(bool forceUpdate)
{
	FVector		CameraLocation;
	FRotator	CameraRotation;

	float		CameraVFOV = 90.0f;
	float		CameraHFOV = 90.0f;

	// Check manager

	if (!m_manager)
		return false;

	GZ_INSTRUMENT_NAME("UCSWScene::processCameras");

#if WITH_EDITOR

	if (!GEditor)
		return false;

	if (!GEditor->IsPlayingSessionInEditor())
	{
		FViewport *viewport=GEditor->GetActiveViewport();

		if (!viewport)
			return false;

		FEditorViewportClient* client = (FEditorViewportClient*)viewport->GetClient();

		if (!client)
			return false;

		CameraLocation = client->GetViewLocation();
		CameraRotation = client->GetViewRotation();

		float aspectRatio = 1.0f;

		FIntPoint size = viewport->GetSizeXY();

		aspectRatio = (float)size.X / (float)size.Y;

		CameraHFOV = client->ViewFOV;
		CameraVFOV = atan( tan(CameraHFOV*GZ_DEG2RAD_F/2) / aspectRatio) * GZ_RAD2DEG_F * 2;
	}
	else
#endif
	// In play Mode
	{
		UWorld* world = GetWorld();

		if (!world)
			return false;

		APlayerController* playerController = world->GetFirstPlayerController();

		if (!playerController)
			return false;

		APlayerCameraManager* cameraManager = playerController->PlayerCameraManager;

		if (!cameraManager)
			return false;

		CameraLocation = cameraManager->GetCameraLocation();
		CameraRotation = cameraManager->GetCameraRotation();

		float aspectRatio = 1.0f;

		UEngine* engine = GEngine;

		if (!engine)
			return false;

		UGameViewportClient *client=engine->GameViewport;

		if (!client)
			return false;

		FViewport* viewport = client->Viewport;

		if (!viewport)
			return false;

		FIntPoint size = viewport->GetSizeXY();

		aspectRatio = (float)size.X / (float)size.Y;

		CameraHFOV = cameraManager->GetFOVAngle();
		CameraVFOV = atan(tan(CameraHFOV * GZ_DEG2RAD_F / 2) / aspectRatio) * GZ_RAD2DEG_F * 2;
	}

	FVector position = GetRelativeLocation();

	// Add possible offset to Camera Location

	/*if (CenterOrigin)
		CameraLocation += FVector3d(ModelOriginX, ModelOriginY, ModelOriginZ);*/

	CameraLocation -= position;

	// Get Large World position of camera 

	gzVec3D pos = UE_2_GZ(CameraLocation, CoordType,getWorldScale());

	// Get rotation matrix from camera

	FMatrix rotation = FRotationMatrix::Make(CameraRotation).RemoveTranslation();

	// Build camera matrix in GZ world

	gzMatrix4D mat = UE_2_GZ(CoordType) * cswMatrix4d::GZMatrix4<double>(rotation) * cswMatrix4d::GZ_2_UE();

	// Get rotation indep of possiböle translation

	gzMatrix3D rot = mat.quaternion().rotationMatrix();

	// Decompose Camera HPR in GZ world

	double h, p, r;

	rot.decompose_euler_yxz(h, p, r);

	// Send camera update without trigger buffer processing

	m_manager->addSingleCommand(new cswSceneCommandPositionCamera(pos, gzVec3(h, p, r) * GZ_RAD2DEG, CameraHFOV, CameraVFOV), FALSE);

	/*cswScreenMessage(gzString::formatString("H:%.2f P:%.2f R:%.2f Pos:%s",h,p,r,pos.asString()),0);*/

	return true;
}

//! Processes all updates, waits for possible frame with timeout
gzUInt32 UCSWScene::processFrames(bool forceNewFrame, bool waitForFrame , gzUInt32 timeOut )
{
	bool isActive = m_manager && m_manager->isRunning();

	// Transfer incoming to gamethread and don not wait for a frame
	bool fetchOk=fetchBuffers(waitForFrame,timeOut);

	// Work on buffers, max 10 full frames, max primitives per frame
	gzUInt32 frames = processPendingBuffers(1, MaxPrimitivesPerFrame);

	
	// -- Trigger next frame --
	// If we are active AND
	// We got a frame in process OR if we fetched a frame and waited OR if we want a forced new frame
	// Trigger buffer processing

	if (isActive && ((frames > 0) || (fetchOk & waitForFrame) || forceNewFrame))
	{
		processCameras(forceNewFrame);

		m_manager->addSingleCommand(new cswSceneCommandRefreshScene(gzTime::systemSeconds()), TRUE);
	}
		
	return frames;
}

// lock and iterate over incoming commands and transfer them to game thread
bool UCSWScene::fetchBuffers(bool waitForFrame,gzUInt32 timeOut)
{
	GZ_INSTRUMENT_NAME("UCSWScene::fetchBuffers");

	GZ_BODYGUARD(m_bufferInLock);

	//UETRACE(gzString::formatString("Buffers:%d", m_bufferIn.entries()));

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

		cswSceneCommandGroundClampPositionResponse* groundClamp = gzDynamic_Cast<cswSceneCommandGroundClampPositionResponse>(command);

		if (groundClamp)
		{
			handleGroundClampResponse(groundClamp);
			continue;
		}
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

	if (!buffer->tryLockEdit(FrameSkipLatency))		// We failed to lock buffer
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
			// Do stuff from start
			continue;
		}

		cswSceneCommandEndFrame* endFrame = gzDynamic_Cast<cswSceneCommandEndFrame>(command);

		if (endFrame)
		{
			// Do stuff from end
			--maxFrames;
		}
	
	}

	buffer->unLock();				// finished

	return !buffer->entries();		// return false if we have items left
}

bool UCSWScene::processDeleteBuffer(cswCommandBuffer* buffer)
{
	GZ_INSTRUMENT_NAME("UCSWScene::processDeleteBuffer");

	if (!buffer->tryLockEdit(FrameSkipLatency))		// We failed to lock buffer  in edit mode
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

	if (!buffer->tryLockEdit(FrameSkipLatency))		// We failed to lock buffer
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
		GZMESSAGE(GZ_MESSAGE_DEBUG, "Failed to get registered parent. Probably destroyed");
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
		GZMESSAGE(GZ_MESSAGE_DEBUG, "Failed to get component for deletion. Probably removed");
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
		UEOrigin = GZ_2_UE(command->getOrigin(), CoordType::Geometry,scale);
	}
	else
	{

		gzCoordSystem system;

		gzCoordSystemMetaData meta;

		if (!gzCoordinate::getCoordinateSystem(command->getCoordinateSystem(), system, meta))
		{
			CoordType = CoordType::Geometry;
			GeoOrigin = NewObject<UCSWGeoModelComponent>(this);
			UEOrigin = GZ_2_UE(command->getOrigin(), CoordType::Geometry,scale);
			GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to set interpret coordinate system %s", command->getCoordinateSystem());
			
		}
		else
		{
			switch (system.type)
			{
				case gzCoordType::GZ_COORDTYPE_GEOCENTRIC:
					CoordType = CoordType::Geocentric;
					GeoOrigin = NewObject<UCSWGeoGeocentricComponent>(this);
					break;

				case gzCoordType::GZ_COORDTYPE_GEODETIC:
					CoordType = CoordType::Geodetic;
					GeoOrigin = NewObject<UCSWGeoGeodeticComponent>(this);
					break;

				case gzCoordType::GZ_COORDTYPE_PROJECTED:
					CoordType = CoordType::Projected;
					GeoOrigin = NewObject<UCSWGeoProjectedComponent>(this);
					break;

				case gzCoordType::GZ_COORDTYPE_UTM:
					CoordType = CoordType::UTM;
					GeoOrigin = NewObject<UCSWGeoUTMComponent>(this);
					break;

				case gzCoordType::GZ_COORDTYPE_FLATEARTH:
					CoordType = CoordType::FlatEarth;
					GeoOrigin = NewObject<UCSWGeoFlatEarthComponent>(this);
					break;

				default:
					CoordType = CoordType::Geometry;
					GeoOrigin = NewObject<UCSWGeoModelComponent>(this);
					break;
			}

			UEOrigin = GZ_2_UE(command->getOrigin(), CoordType, scale);
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

	// Return index id
	m_slots.push(id);

	// And set slot to nullptr
	m_components[id] = nullptr;

	// Remove LUT
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
gzVoid UCSWScene::onCommand(cswSceneManager* manager, cswCommandBuffer* buffer)
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
		m_firstRun = true;
	}
	else
	{
		m_manager->addSingleCommand(new cswSceneCommandClearMaps());
	}
		
	return true;
}

bool UCSWScene::onOmniViewPropertyUpdate()
{
	GZ_INSTRUMENT_NAME("UCSWScene::onOmniViewPropertyUpdate");

	if (m_manager)
		m_manager->addSingleCommand(new cswSceneCommandSetOmniTraverse(OmniView), FALSE);

	return true;
}

bool UCSWScene::onLodFactorPropertyUpdate()
{
	GZ_INSTRUMENT_NAME("UCSWScene::onLodFactorPropertyUpdate");

	if (m_manager)
		m_manager->addSingleCommand(new cswSceneCommandSetLodFactor(LodFactor), FALSE);

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
	if (!AllowCustomOrigin)
	{
		FTransform m;

		// map SCENE content in Gizmo World to UE world with or without origin

		gzVec3D origin = CenterOrigin ? UE_2_GZ(FVector3d(ModelOriginX, ModelOriginY, ModelOriginZ), CoordType, getWorldScale()) : GZ_ZERO_VEC3D;

		// Move children negative origin so our map origin ends up in 0,0,0

		m.SetFromMatrix(cswMatrix4_<double>::UEMatrix4(GZ_2_UE(CoordType, getWorldScale(), origin)));

		// Apply Transform to root

		SetRelativeTransform(m);
	}
}

gzMatrix4D UCSWScene::UE_2_GZ(enum CoordType type, const double& scale, const gzVec3D& offset) const
{
	gzMatrix4D mat;
	
	if(GZ_2_UE(type, scale, offset).inverse(mat))
		return mat;

	GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to invert local matrix to global");

	return gzMatrix4D::identityMatrix();
}

gzMatrix4D UCSWScene::GZ_2_UE(enum CoordType type, const double& scale, const gzVec3D& offset) const
{
	switch (type)
	{
		case CoordType::Geometry:
			return cswMatrix4d::GZ_2_UE(-offset, scale);

		case CoordType::Projected:
		case CoordType::UTM:
			return cswMatrix4d::GZ_UTM_2_UE(-offset, scale);

		default:
			GZ_XXX;
	}

	return gzMatrix4D::identityMatrix();
}


FVector3d UCSWScene::GZ_2_UE(const gzVec3D& local,enum CoordType type, const double& scale , const gzVec3D& offset) const
{
	return cswVector3d::UEVector3<double>(GZ_2_UE(type,scale,offset) * local);
}

gzVec3D UCSWScene::UE_2_GZ(const FVector3d& global, enum CoordType type, const double& scale , const gzVec3D& offset) const
{
	return  (gzVec3D) (UE_2_GZ(type,scale,offset) * cswVector3d::GZVector3<double>(global));
}

FVector3d UCSWScene::GZ_2_UE_Vector(const gzVec3D& vector, enum CoordType type, const double& scale) const
{
	// Vector conversion: no translation (offset = 0). Use scale for unit conversion if needed.
	const gzMatrix4D mat = GZ_2_UE(type, scale, GZ_ZERO_VEC3D);
	return cswVector3d::UEVector3<double>(mat * vector);
}

gzVec3D UCSWScene::UE_2_GZ_Vector(const FVector3d& vector, enum CoordType type, const double& scale) const
{
	// Vector conversion: no translation (offset = 0). Use scale for unit conversion if needed.
	const gzMatrix4D mat = UE_2_GZ(type, scale, GZ_ZERO_VEC3D);
	return  (gzVec3D) (mat * cswVector3d::GZVector3<double>(vector));
}


FVector3d UCSWScene::GZ_2_UE_Local(const gzVec3D& position) const
{
	// GZ position -> UE local, then add scene origin to get UE world
	const FVector3d local = GZ_2_UE(position, CoordType, getWorldScale());
	const FVector3d origin = FVector3d(GetRelativeLocation());
	return local + origin;
}

gzVec3D UCSWScene::UE_2_GZ_Local(const FVector3d& world) const
{
	// UE world -> UE local (remove origin), then map to GZ position
	const FVector3d origin = FVector3d(GetRelativeLocation());
	const FVector3d local = world - origin;
	return UE_2_GZ(local, CoordType, getWorldScale());
}

bool UCSWScene::GeodeticToWorld(double latitudeDeg, double longitudeDeg, double altitudeMeters, FVector3d& outWorld) const
{
	if (CoordSystem.IsEmpty())
		return false;

	gzCoordSystem system;
	gzCoordSystemMetaData meta;

	if (!gzCoordinate::getCoordinateSystem(toString(CoordSystem), system, meta))
		return false;

	// Steg 1: lat/lon/alt (grader) -> gzLatPos (radianer)
	// Steg 2: gzLatPos -> GZ position i kartans coord system (Gizmo)
	// Steg 3: GZ position -> UE local via GZ_2_UE (CoordType + skala)
	// Steg 4: lagg pa scenens origo (root transform). Offset hanteras dar.

	gzLatPos latpos{ latitudeDeg, longitudeDeg, altitudeMeters };
	latpos.DEG2RAD();

	gzVec3D position;

	if (!gzCoordinate::get3DCoordinate(latpos, system, meta, position))
		return false;

	outWorld = GZ_2_UE_Local(position);

	return true;
}

bool UCSWScene::WorldToGeodetic(const FVector3d& world, double& outLatitudeDeg, double& outLongitudeDeg, double& outAltitudeMeters) const
{
	if (CoordSystem.IsEmpty())
		return false;

	gzCoordSystem system;
	gzCoordSystemMetaData meta;

	if (!gzCoordinate::getCoordinateSystem(toString(CoordSystem), system, meta))
		return false;

	// Steg 1: UE world -> local (ta bort scenens origo)
	// Steg 2: UE local -> GZ via UE_2_GZ (CoordType + skala)
	// Steg 3: GZ position -> geodetic (lat/lon/alt)
	// Offset hanteras av root transform, inte i UE_2_GZ anropet

	const gzVec3D position = UE_2_GZ_Local(world);

	gzLatPos latpos;

	if (!gzCoordinate::getGlobalCoordinate(position, system, meta, latpos))
		return false;

	latpos.RAD2DEG();

	outLatitudeDeg = latpos.latitude;
	outLongitudeDeg = latpos.longitude;
	outAltitudeMeters = latpos.altitude;

	return true;
}


bool UCSWScene::GeodeticToWorldBP(double latitudeDeg, double longitudeDeg, double altitudeMeters, FVector& outWorld) const
{
	FVector3d world3d;
	if (!GeodeticToWorld(latitudeDeg, longitudeDeg, altitudeMeters, world3d))
		return false;
	outWorld = FVector(world3d);
	return true;
}

bool UCSWScene::WorldToGeodeticBP(const FVector& world, double& outLatitudeDeg, double& outLongitudeDeg, double& outAltitudeMeters) const
{
	const FVector3d world3d(world);
	return WorldToGeodetic(world3d, outLatitudeDeg, outLongitudeDeg, outAltitudeMeters);
}

int32 UCSWScene::RequestGroundClampPosition(double latitudeDeg, double longitudeDeg, double heightAboveGround, bool waitForData)
{
	if (!m_manager)
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "Ground clamp request ignored: scene manager not initialized");
		return 0;
	}

	gzUInt32 requestId = 0;
	{
		FScopeLock lock(&m_groundClampLock);
		requestId = ++m_groundClampNextRequestId;
	}
	m_manager->requestGroundClampPosition(latitudeDeg, longitudeDeg, heightAboveGround, waitForData ? TRUE : FALSE, requestId);
	return (int32)requestId;
}

bool UCSWScene::TryGetGroundClampResponse(int32 requestId, FCSWGroundClampResult& outResult)
{
	if (requestId <= 0)
		return false;

	{
		FScopeLock lock(&m_groundClampLock);
		if (FCSWGroundClampResult* found = m_groundClampResponses.Find((gzUInt32)requestId))
		{
			outResult = *found;
			m_groundClampResponses.Remove((gzUInt32)requestId);
			return true;
		}
	}

	return false;
}

bool UCSWScene::WaitForGroundClampResponse(int32 requestId, FCSWGroundClampResult& outResult, double timeoutSeconds, double pollIntervalSeconds)
{
	if (requestId <= 0)
		return false;

	if (IsInGameThread())
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "WaitForGroundClampResponse called on game thread; aborting");
		return false;
	}

	const double startTime = FPlatformTime::Seconds();

	while ((FPlatformTime::Seconds() - startTime) < timeoutSeconds)
	{
		if (TryGetGroundClampResponse(requestId, outResult))
			return true;

		FPlatformProcess::Sleep((float)pollIntervalSeconds);
	}

	return false;
}

void UCSWScene::handleGroundClampResponse(cswSceneCommandGroundClampPositionResponse* response)
{
	if (!response)
		return;

	FCSWGroundClampResult result;
	result.RequestId = (int32)response->getCommandRefID();
	result.bSuccess = (bool)response->getClampResult();
	result.Altitude = response->getAltitude();

	const gzVec3D positionGZ = response->getPosition();
	result.WorldPosition = FVector(GZ_2_UE_Local(positionGZ));

	const gzVec3D normalGZ = (gzVec3D)response->getNormal();
	const gzVec3D upGZ = (gzVec3D)response->getUp();

	const FVector3d worldNormal = GZ_2_UE_Vector(normalGZ, CoordType, getWorldScale());
	const FVector3d worldUp = GZ_2_UE_Vector(upGZ, CoordType, getWorldScale());

	result.WorldNormal = FVector(worldNormal).GetSafeNormal();
	result.WorldUp = FVector(worldUp).GetSafeNormal();

	{
		FScopeLock lock(&m_groundClampLock);
		m_groundClampResponses.Add((gzUInt32)result.RequestId, result);
	}
	OnGroundClampResponse.Broadcast(result);
}

double UCSWScene::getWorldScale() const
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
