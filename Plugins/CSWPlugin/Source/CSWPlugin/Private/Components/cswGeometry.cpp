// Fill out your copyright notice in the Description page of Project Settings.


#include "components/cswGeometry.h"

#include "MeshDescription.h"
#include "MeshDescriptionBuilder.h"
#include "StaticMeshAttributes.h"

// Sets default values for this component's properties
UCSWGeometry::UCSWGeometry()
{
}


bool UCSWGeometry::build(UCSWSceneComponent* parent, gzNode* buildItem)
{
	if (!Super::build(parent,buildItem))
		return false;

	m_meshComponent = NewObject<UStaticMeshComponent>(this, NAME_None);

	m_meshComponent->RegisterComponent();

	m_meshComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);


	// Mesh description will hold all the geometry, uv, normals going into the static mesh
	FMeshDescription meshDesc;
	FStaticMeshAttributes Attributes(meshDesc);
	Attributes.Register();

	FMeshDescriptionBuilder meshDescBuilder;
	meshDescBuilder.SetMeshDescription(&meshDesc);
	meshDescBuilder.EnablePolyGroups();
	meshDescBuilder.SetNumUVLayers(1);

	// Create the 5 vertices needed for the shape
	TArray< FVertexID > vertexIDs; vertexIDs.SetNum(3);

	vertexIDs[0] = meshDescBuilder.AppendVertex(FVector(0.0, 0.0, 0.0)); // Apex
	vertexIDs[1] = meshDescBuilder.AppendVertex(FVector(100.0, 0.0, 0.0)); // Corner 1
	vertexIDs[2] = meshDescBuilder.AppendVertex(FVector(100.0, 0.0, -100.0)); // Corner 2


	// Array to store all the vertex instances (3 per face)
	TArray< FVertexInstanceID > vertexInsts;

	// Face 1 (Faces towards -X) vertex instances
	FVertexInstanceID instance = meshDescBuilder.AppendInstance(vertexIDs[0]);
	meshDescBuilder.SetInstanceNormal(instance, FVector(0, 1, 0));
	meshDescBuilder.SetInstanceUV(instance, FVector2D(0, 1), 0);
	meshDescBuilder.SetInstanceColor(instance, FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	vertexInsts.Add(instance);

	instance = meshDescBuilder.AppendInstance(vertexIDs[1]);
	meshDescBuilder.SetInstanceNormal(instance, FVector(0, 1, 0));
	meshDescBuilder.SetInstanceUV(instance, FVector2D(0, 0), 0);
	meshDescBuilder.SetInstanceColor(instance, FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	vertexInsts.Add(instance);

	instance = meshDescBuilder.AppendInstance(vertexIDs[2]);
	meshDescBuilder.SetInstanceNormal(instance, FVector(0, 1, 0));
	meshDescBuilder.SetInstanceUV(instance, FVector2D(1, 0), 0);
	meshDescBuilder.SetInstanceColor(instance, FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	vertexInsts.Add(instance);


	// Allocate a polygon group
	FPolygonGroupID polygonGroup = meshDescBuilder.AppendPolygonGroup();

	// Add triangles to mesh description
	meshDescBuilder.AppendTriangle(vertexInsts[2], vertexInsts[1], vertexInsts[0], polygonGroup);

	// At least one material must be added
	TObjectPtr<UStaticMesh> staticMesh;

	staticMesh = NewObject<UStaticMesh>(this);

	staticMesh->GetStaticMaterials().Add(FStaticMaterial());

	UStaticMesh::FBuildMeshDescriptionsParams mdParams;
	mdParams.bBuildSimpleCollision = true;
	mdParams.bFastBuild = true;

	// Build static mesh
	TArray<const FMeshDescription*> meshDescPtrs;
	meshDescPtrs.Emplace(&meshDesc);
	staticMesh->BuildFromMeshDescriptions(meshDescPtrs, mdParams);

	// Assign new static mesh to the static mesh component
	m_meshComponent->SetStaticMesh(staticMesh);

	return true;
}

bool  UCSWGeometry::destroy(gzNode* destroyItem)
{
	// Do cleanup

	m_meshComponent->DestroyComponent();

	return Super::destroy(destroyItem);
}
