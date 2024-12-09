// Fill out your copyright notice in the Description page of Project Settings.


#include "components/cswGeometry.h"
#include "cswUEMatrix.h"

// GizmoSDK
#include "gzGeometry.h"

#include "MeshDescription.h"
#include "MeshDescriptionBuilder.h"
#include "StaticMeshAttributes.h"

// Sets default values for this component's properties
UCSWGeometry::UCSWGeometry(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


bool UCSWGeometry::build(UCSWSceneComponent* parent, gzNode* buildItem)
{
	if (!Super::build(parent,buildItem))
		return false;

	GZ_INSTRUMENT_NAME("UCSWGeometry::build");

	// Get Handle to geometry
	gzGeometry* geom = gzDynamic_Cast<gzGeometry>(buildItem);

	if (!geom)
		return false;

	// New object
	m_meshComponent = NewObject<UStaticMeshComponent>(this, NAME_None);

	// Settings specific
	m_meshComponent->SetSimulatePhysics(false);
	m_meshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
	// Mesh description will hold all the geometry, uv, normals going into the static mesh
	FMeshDescription meshDesc;
	FStaticMeshAttributes Attributes(meshDesc);
	Attributes.Register();

	// builder is used to work on description
	FMeshDescriptionBuilder meshDescBuilder;
	meshDescBuilder.SetMeshDescription(&meshDesc);
	//meshDescBuilder.EnablePolyGroups();

	// Create first polygon group
	FPolygonGroupID polygonGroup = meshDescBuilder.AppendPolygonGroup();


	// --------------- coordinates (vertices) ----------------------

	gzArray<gzVec3>& coordinates = geom->getCoordinateArray(FALSE);

	meshDescBuilder.ReserveNewVertices(coordinates.getSize());

	meshDescBuilder.SetNumUVLayers(geom->getTextureUnits());

	for (gzUInt32 i = 0; i < coordinates.getSize(); i++)
	{
		gzVec3& coord = coordinates[i];

		meshDescBuilder.AppendVertex(FVector(coord.x, coord.y, coord.z));
	}

	// --------------- indices -------------------------------------

	gzArray<gzUInt32>& indices = geom->getIndexArray(FALSE);

	for (gzUInt32 i = 0; i < indices.getSize(); i += 3)
	{
		gzArray<FVertexInstanceID> id(3);

		for (gzUInt32 j = 0; j < 3; j++)
		{
			gzUInt32 index = i + j;

			id[j] = meshDescBuilder.AppendInstance(indices[index]);

			switch (geom->getNormalBind())
			{
				case GZ_BIND_OFF:
					meshDescBuilder.SetInstanceNormal(index, cswVector3d::UEVector3(gzVec3(0,1,0)));
					break;

				case GZ_BIND_ON:
					meshDescBuilder.SetInstanceNormal(index, cswVector3d::UEVector3(geom->getNormalArray(FALSE)[indices[index]]));
					break;

			}

			for (gzUInt32 layer = 0; layer < geom->getTextureUnits(); layer++)
			{
				switch (geom->getTexBind(layer))
				{
					case GZ_BIND_OFF:
						break;

					case GZ_BIND_ON:
						meshDescBuilder.SetInstanceUV(index, cswVector2d::UEVector2(geom->getTexCoordinateArray(layer, FALSE)[indices[index]]), layer);
						break;

				}
			}

			switch (geom->getColorBind())
			{
				case GZ_BIND_OFF:
					break;

				case GZ_BIND_ON:
					meshDescBuilder.SetInstanceColor(index, cswVector4::UEVector4(geom->getColorArray(FALSE)[indices[index]]));
					break;

			}
		}

		meshDescBuilder.AppendTriangle(id[2], id[1], id[0], polygonGroup);
	}







	//GZ_ENTER_PERFORMANCE_SECTION("UE:AppendVertex");

	//// Create the 5 vertices needed for the shape
	//TArray< FVertexID > vertexIDs; vertexIDs.SetNum(3);

	//vertexIDs[0] = meshDescBuilder.AppendVertex(FVector(0.0, 0.0, 0.0)); // Apex
	//vertexIDs[1] = meshDescBuilder.AppendVertex(FVector(100.0, 0.0, 0.0)); // Corner 1
	//vertexIDs[2] = meshDescBuilder.AppendVertex(FVector(100.0, 0.0, -100.0)); // Corner 2


	// Array to store all the vertex instances (3 per face)
	//TArray< FVertexInstanceID > vertexInsts;

	// Face 1 (Faces towards -X) vertex instances
	/*FVertexInstanceID instance = meshDescBuilder.AppendInstance(vertexIDs[0]);
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

	GZ_LEAVE_PERFORMANCE_SECTION;*/

	

	



	GZ_ENTER_PERFORMANCE_SECTION("UE:StaticMesh:NewObject");

	// At least one material must be added
	TObjectPtr<UStaticMesh> staticMesh;

	staticMesh = NewObject<UStaticMesh>(this);

	staticMesh->GetStaticMaterials().Add(FStaticMaterial());

	UStaticMesh::FBuildMeshDescriptionsParams mdParams;
	mdParams.bBuildSimpleCollision = false;
	mdParams.bFastBuild = true;

	GZ_LEAVE_PERFORMANCE_SECTION;





	GZ_ENTER_PERFORMANCE_SECTION("UE:BuildFromMeshDescriptions");

	// Build static mesh
	TArray<const FMeshDescription*> meshDescPtrs;
	meshDescPtrs.Emplace(&meshDesc);
	staticMesh->BuildFromMeshDescriptions(meshDescPtrs, mdParams);

	GZ_LEAVE_PERFORMANCE_SECTION;
	
	
	
	
	GZ_ENTER_PERFORMANCE_SECTION("UE:SetStaticMesh");

	// Assign new static mesh to the static mesh component
	m_meshComponent->SetStaticMesh(staticMesh);

	GZ_LEAVE_PERFORMANCE_SECTION;




	GZ_ENTER_PERFORMANCE_SECTION("UE:AttachToComponent_x");

	m_meshComponent->SetMobility(EComponentMobility::Stationary);

	m_meshComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
		
	GZ_LEAVE_PERFORMANCE_SECTION;



	GZ_ENTER_PERFORMANCE_SECTION("UE:RegisterComponent_x");

	m_meshComponent->RegisterComponent();

	GZ_LEAVE_PERFORMANCE_SECTION;



	return true;
}

bool  UCSWGeometry::destroy(gzNode* destroyItem)
{
	// Do cleanup

	m_meshComponent->DestroyComponent();

	return Super::destroy(destroyItem);
}
