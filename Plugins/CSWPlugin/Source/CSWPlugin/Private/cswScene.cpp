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
// Author		: Anders Mod�n		
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
#include "cswUEUtility.h"
#include "cswUEMatrix.h"
#include "cswFactory.h"






UCSWScene::UCSWScene(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
	bAutoActivate = true;

	// Register callbacks
	registerPropertyUpdate("MapUrls", &UCSWScene::onMapUrlsPropertyUpdate);
		
	//SetMobility(EComponentMobility::Static);

	/*_smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"), true);

	_smComp->SetupAttachment(this);*/

	//_smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"), true);

	initSceneManager();

	counter = 0;
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

void UCSWScene::BeginPlay()
{
	Super::BeginPlay();

}

void UCSWScene::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

	bool isActive = m_manager && m_manager->isRunning();

	// Transfer incoming to gamethread and wait for a frame
	fetchBuffers(isActive);

	// Work on buffers
	processBuffersOut();

	// Trigger next frame
	if(isActive)
		m_manager->addSingleCommand(new cswSceneCommandRefreshScene(gzTime::systemSeconds()));

	counter++;

	if (counter == 10)
	{
		trans = cswFactory::newObject(this,new gzTransform);

		trans->RegisterComponent();

		trans->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

		trans->build(nullptr);
	}
}

void UCSWScene::initSceneManager()
{
	if (!m_manager)
	{
		m_manager = new cswSceneManager();

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

		// First initial refresh

		buffer->addCommand(new cswSceneCommandRefreshScene(gzTime::systemSeconds()));

		m_manager->addCommandBuffer(buffer);
	}
}

// lock and iterate over incoming commands and transfer them to game thread
void UCSWScene::fetchBuffers(bool waitForFrame,gzUInt32 timeOut)
{
	GZ_BODYGUARD(m_bufferInLock);

	while (true)
	{
		gzListIterator<cswCommandBuffer> iterator(m_bufferIn);
		cswCommandBuffer* buffer(nullptr);

		while ((buffer = iterator()))
		{
			m_bufferOut.insert(buffer);

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
}

void UCSWScene::processBuffersOut()
{
	gzListIterator<cswCommandBuffer> iterator(m_bufferOut);
	cswCommandBuffer* buffer(nullptr);

	while ((buffer = iterator()))
	{
		if (buffer->entries() > 2)
		{
			gzString message = gzString::formatString("%s:Processed buffer out of type (%d) with %d commands", gzTime::now().asString(), buffer->getBufferType(), buffer->entries());

			cswScreenMessage(message);
		}
	}

	// All data processed. Empty buffer
	m_bufferOut.clear();
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
		
	return true;
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



//void UCSWScene::test(bool inPlay)
//{
//	//_smComp = NewObject<UStaticMeshComponent>(this,NAME_None);
//
//	//_smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"), true);
//
//	_smComp->SetupAttachment(this);
//
//
//
//	// Build a simple pyramid after play has begun
//	// Mesh description will hold all the geometry, uv, normals going into the static mesh
//	FMeshDescription meshDesc;
//	FStaticMeshAttributes Attributes(meshDesc);
//	Attributes.Register();
//
//	FMeshDescriptionBuilder meshDescBuilder;
//	meshDescBuilder.SetMeshDescription(&meshDesc);
//	meshDescBuilder.EnablePolyGroups();
//	meshDescBuilder.SetNumUVLayers(1);
//
//	// Create the 5 vertices needed for the shape
//	TArray< FVertexID > vertexIDs; vertexIDs.SetNum(3);
//
//	vertexIDs[0] = meshDescBuilder.AppendVertex(FVector(0.0, 0.0, 0.0)); // Apex
//	vertexIDs[1] = meshDescBuilder.AppendVertex(FVector(100.0, 0.0, 0.0)); // Corner 1
//	vertexIDs[2] = meshDescBuilder.AppendVertex(FVector(100.0, 0.0, -100.0)); // Corner 2
//
//
//	// Array to store all the vertex instances (3 per face)
//	TArray< FVertexInstanceID > vertexInsts;
//
//	// Face 1 (Faces towards -X) vertex instances
//	FVertexInstanceID instance = meshDescBuilder.AppendInstance(vertexIDs[0]);
//	meshDescBuilder.SetInstanceNormal(instance, FVector(0, 1, 0));
//	meshDescBuilder.SetInstanceUV(instance, FVector2D(0, 1), 0);
//	meshDescBuilder.SetInstanceColor(instance, FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
//	vertexInsts.Add(instance);
//
//	instance = meshDescBuilder.AppendInstance(vertexIDs[1]);
//	meshDescBuilder.SetInstanceNormal(instance, FVector(0, 1, 0));
//	meshDescBuilder.SetInstanceUV(instance, FVector2D(0, 0), 0);
//	meshDescBuilder.SetInstanceColor(instance, FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
//	vertexInsts.Add(instance);
//
//	instance = meshDescBuilder.AppendInstance(vertexIDs[2]);
//	meshDescBuilder.SetInstanceNormal(instance, FVector(0, 1, 0));
//	meshDescBuilder.SetInstanceUV(instance, FVector2D(1, 0), 0);
//	meshDescBuilder.SetInstanceColor(instance, FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
//	vertexInsts.Add(instance);
//
//
//	// Allocate a polygon group
//	FPolygonGroupID polygonGroup = meshDescBuilder.AppendPolygonGroup();
//
//	// Add triangles to mesh description
//	meshDescBuilder.AppendTriangle(vertexInsts[2], vertexInsts[1], vertexInsts[0], polygonGroup);
//
//	// At least one material must be added
//	TObjectPtr<UStaticMesh> staticMesh;
//
//	if (inPlay)
//		staticMesh = NewObject<UStaticMesh>(this);
//	else
//		staticMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Oahh"), true);
//
//	staticMesh->GetStaticMaterials().Add(FStaticMaterial());
//
//	UStaticMesh::FBuildMeshDescriptionsParams mdParams;
//	mdParams.bBuildSimpleCollision = true;
//	mdParams.bFastBuild = true;
//
//	// Build static mesh
//	TArray<const FMeshDescription*> meshDescPtrs;
//	meshDescPtrs.Emplace(&meshDesc);
//	staticMesh->BuildFromMeshDescriptions(meshDescPtrs, mdParams);
//
//	// Assign new static mesh to the static mesh component
//	_smComp->SetStaticMesh(staticMesh);
//}