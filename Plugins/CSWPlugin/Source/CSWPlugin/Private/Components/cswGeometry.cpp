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

	// Check supported primitives right now

	switch (geom->getGeoPrimType())
	{

		case GZ_PRIM_NOPRIM:
		case GZ_PRIM_POINTS:
		case GZ_PRIM_LINES:
		case GZ_PRIM_LINESTRIPS:
		case GZ_PRIM_FLAT_LINESTRIPS:
		case GZ_PRIM_LINELOOPS:
			return true;				// Lets just swallow these prims ok right now

		case GZ_PRIM_TRIS:
			break;

		case GZ_PRIM_QUADS:				// All these types are basically error
		case GZ_PRIM_TRISTRIPS:
		case GZ_PRIM_FLAT_TRISTRIPS:
		case GZ_PRIM_TRIFANS:
		case GZ_PRIM_FLAT_TRIFANS:
		case GZ_PRIM_POLYS:
		case GZ_PRIM_QUADSTRIPS:
		case GZ_PRIM_HIDDEN_POLYS:
			return false;
	}

	// New object
	m_meshComponent = NewObject<UStaticMeshComponent>(this, geom->getName().getWideString());

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
					meshDescBuilder.SetInstanceNormal(index, cswVector3d::UEVector3(gzVec3(0,1, 0)));
					break;

				case GZ_BIND_OVERALL:
					meshDescBuilder.SetInstanceNormal(index, cswVector3d::UEVector3(geom->getNormalArray(FALSE)[0]));
					break;

				case GZ_BIND_PER_PRIM:
					meshDescBuilder.SetInstanceNormal(index, cswVector3d::UEVector3(geom->getNormalArray(FALSE)[i/3]));
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

					case GZ_BIND_OVERALL:
						meshDescBuilder.SetInstanceUV(index, cswVector2d::UEVector2(geom->getTexCoordinateArray(layer, FALSE)[0]), layer);
						break;

					case GZ_BIND_PER_PRIM:
						meshDescBuilder.SetInstanceUV(index, cswVector2d::UEVector2(geom->getTexCoordinateArray(layer, FALSE)[i/3]), layer);
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

				case GZ_BIND_OVERALL:
					meshDescBuilder.SetInstanceColor(index, cswVector4::UEVector4(geom->getColorArray(FALSE)[0]));
					break;

				case GZ_BIND_PER_PRIM:
					meshDescBuilder.SetInstanceColor(index, cswVector4::UEVector4(geom->getColorArray(FALSE)[i/3]));
					break;

				case GZ_BIND_ON:
					meshDescBuilder.SetInstanceColor(index, cswVector4::UEVector4(geom->getColorArray(FALSE)[indices[index]]));
					break;

			}
		}

		meshDescBuilder.AppendTriangle(id[2], id[1], id[0], polygonGroup);
	}


	// At least one material must be added
	TObjectPtr<UStaticMesh> staticMesh;

	staticMesh = NewObject<UStaticMesh>(this);

	staticMesh->GetStaticMaterials().Add(FStaticMaterial());

	UStaticMesh::FBuildMeshDescriptionsParams mdParams;
	mdParams.bBuildSimpleCollision = false;
	mdParams.bFastBuild = true;


	// Build static mesh
	TArray<const FMeshDescription*> meshDescPtrs;
	meshDescPtrs.Emplace(&meshDesc);
	staticMesh->BuildFromMeshDescriptions(meshDescPtrs, mdParams);


	// Assign new static mesh to the static mesh component
	m_meshComponent->SetStaticMesh(staticMesh);


	m_meshComponent->SetMobility(EComponentMobility::Stationary);

	m_meshComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	m_meshComponent->RegisterComponent();

	return true;
}

bool  UCSWGeometry::destroy(gzNode* destroyItem)
{
	// Do cleanup

	m_meshComponent->DestroyComponent();

	return Super::destroy(destroyItem);
}
