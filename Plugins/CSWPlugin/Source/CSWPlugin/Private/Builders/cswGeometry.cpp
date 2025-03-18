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
// File			: cswGeometry.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Builder class for gzGeometry
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
// AMO	241211	Created file 					(1.1.1)
//
//******************************************************************************
#include "Builders/cswGeometry.h"

// GizmoSDK
#include "gzGeometry.h"

// Glue
#include "UEGlue/cswUEMatrix.h"

#include "cswResourceManager.h"

#include "MeshDescription.h"
#include "StaticMeshAttributes.h"

// Sets default values for this component's properties
UCSWGeometry::UCSWGeometry(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


bool UCSWGeometry::build(UCSWSceneComponent* parent, gzNode* buildItem, gzState* state, BuildProperties& buildProperties, cswResourceManager* resources)
{
	if (!Super::build(parent,buildItem, state, buildProperties,resources))
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

	{
		GZ_INSTRUMENT_NAME("UCSWGeometry::build::component setup");

		// New object
		m_meshComponent = NewObject<UStaticMeshComponent>(this, geom->getName().getWideString());

		// Settings specific and optims for fast render
		m_meshComponent->SetSimulatePhysics(buildProperties.simulatePhysics);
		m_meshComponent->SetCollisionEnabled(buildProperties.collision);

		m_meshComponent->SetUsingAbsoluteLocation(false);
		m_meshComponent->SetUsingAbsoluteRotation(false);
		m_meshComponent->SetUsingAbsoluteScale(false);

		m_meshComponent->ForcedLodModel = 1;	// Tvinga lägsta LOD

		m_meshComponent->SetMobility(EComponentMobility::Stationary);

		m_meshComponent->SetRenderCustomDepth(false); // stänger av outline effekter

		//m_meshComponent->SetCastShadow(false); // Ingen skuggning

		m_meshComponent->bAffectDistanceFieldLighting = false; // avståndsbaserad 

		m_meshComponent->bAffectDynamicIndirectLighting = false;

		m_meshComponent->bAlwaysCreatePhysicsState = false;

		m_meshComponent->bReceivesDecals = false;

		//m_meshComponent->bUseAttachParentBound = true;

	}
	
	// Mesh description will hold all the geometry, uv, normals going into the static mesh
	FMeshDescription MeshDescription;

	// Registrera så många UV-lager du behöver (standard är 1) // Om du vill ha fler lager:
	const int32 NumUVChannels = geom->getTextureUnits();

	MeshDescription.SetNumUVChannels(NumUVChannels);
			
	FStaticMeshAttributes Attributes(MeshDescription); 
	
	Attributes.Register();

	// Skapa en PolygonGroup (en grupp för polygoner, oftast en grupp = ett material) 
	FPolygonGroupID PolygonGroupID = MeshDescription.CreatePolygonGroup();


	// --------------- coordinates (vertices) ----------------------

	gzArray<gzVec3>& coordinates = geom->getCoordinateArray(FALSE);

	{
		GZ_INSTRUMENT_NAME("UCSWGeometry::build::vertice setup");

		// Reserve vertices in mesh description
		MeshDescription.ReserveNewVertices(coordinates.getSize());

		TVertexAttributesRef<FVector3f> vertex = Attributes.GetVertexPositions();

		for (gzUInt32 i = 0; i < coordinates.getSize(); i++)
		{
			MeshDescription.CreateVertex();
			vertex[i] = cswVector3::UEVector3(coordinates[i]);
		}
	}

	// --------------- indices -------------------------------------

	gzArray<gzUInt32>& indices = geom->getIndexArray(FALSE);

	gzUInt32 icount = indices.getSize();

	// Reserve indices in mesh description
	MeshDescription.ReserveNewVertexInstances(icount);
	MeshDescription.ReserveNewTriangles(icount / 3);

	TVertexInstanceAttributesRef<FVector3f> normal = Attributes.GetVertexInstanceNormals();
	TVertexInstanceAttributesRef<FVector2f> texcoord = Attributes.GetVertexInstanceUVs();
	TVertexInstanceAttributesRef<FVector4f> colors = Attributes.GetVertexInstanceColors();

	gzArray<gzVec3>& normal_in(geom->getNormalArray(FALSE));
	gzArray<gzVec4>& colors_in(geom->getColorArray(FALSE));
	gzArray<gzArray<gzVec2>>& texcoord_in(geom->getTexCoordinateArrays(FALSE));
	

	TArray<FVertexInstanceID> id;
	id.SetNum(3);

	FVertexInstanceID ind;

	{
		GZ_INSTRUMENT_NAME("UCSWGeometry::build::attrib setup");

		if (icount)	// We have an indexed structure
		{
			for (gzUInt32 i = 0; i < icount; i += 3)
			{
				for (gzUInt32 j = 0; j < 3; j++)
				{
					gzUInt32 index = i + 2 - j;

					{
						GZ_INSTRUMENT_NAME("UCSWGeometry::build::create vertex instance");
						id[j] = ind = MeshDescription.CreateVertexInstance(indices[index]);
					}


					{
						GZ_INSTRUMENT_NAME("UCSWGeometry::build::normal");
						// Normal indexed -----------------------------------------------

						switch (geom->getNormalBind())
						{
							case GZ_BIND_OFF:
								normal[ind] = cswVector3::UEVector3(gzVec3(0, 1, 0));
								break;

							case GZ_BIND_OVERALL:
								normal[ind] = cswVector3::UEVector3(normal_in[0]);
								break;

							case GZ_BIND_PER_PRIM:
								normal[ind] = cswVector3::UEVector3(normal_in[i / 3]);
								break;

							case GZ_BIND_ON:
								normal[ind] = cswVector3::UEVector3(normal_in[indices[index]]);
								break;

						}
					}

					{
						GZ_INSTRUMENT_NAME("UCSWGeometry::build::tex");
						// Tex indexed -----------------------------------------------

						for (gzUInt32 layer = 0; layer < geom->getTextureUnits(); layer++)
						{
							switch (geom->getTexBind(layer))
							{
								case GZ_BIND_OFF:
									break;

								case GZ_BIND_OVERALL:
									texcoord.Set(ind, layer, cswVector2::UEVector2(texcoord_in[layer][0]));
									break;

								case GZ_BIND_PER_PRIM:
									texcoord.Set(ind, layer, cswVector2::UEVector2(texcoord_in[layer][i / 3]));
									break;


								case GZ_BIND_ON:
									texcoord.Set(ind, layer, cswVector2::UEVector2(texcoord_in[layer][indices[index]]));
									break;

							}
						}
					}

					{
						GZ_INSTRUMENT_NAME("UCSWGeometry::build::color");

						// Color indexed -----------------------------------------------

						switch (geom->getColorBind())
						{
							case GZ_BIND_OFF:
								break;

							case GZ_BIND_OVERALL:
								colors[ind] = cswVector4::UEVector4(colors_in[0]);
								break;

							case GZ_BIND_PER_PRIM:
								colors[ind] = cswVector4::UEVector4(colors_in[i / 3]);
								break;

							case GZ_BIND_ON:
								colors[ind] = cswVector4::UEVector4(colors_in[indices[index]]);
								break;

						}
					}
				}

				{
					GZ_INSTRUMENT_NAME("UCSWGeometry::build::poly");
					MeshDescription.CreatePolygon(PolygonGroupID, id);
				}
			}
		}
		else
		{
			// Non indexed. Not so optimal perhapsbut we dont take the penalty here to convert it

			for (gzUInt32 i = 0; i < coordinates.getSize(); i += 3)
			{
				for (gzUInt32 j = 0; j < 3; j++)
				{
					gzUInt32 index = i + 2 - j;

					id[j] = ind = MeshDescription.CreateVertexInstance(index);



					// Normal -----------------------------------------------

					switch (geom->getNormalBind())
					{
						case GZ_BIND_OFF:
							normal[ind] = cswVector3::UEVector3(gzVec3(0, 1, 0));
							break;

						case GZ_BIND_OVERALL:
							normal[ind] = cswVector3::UEVector3(normal_in[0]);
							break;

						case GZ_BIND_PER_PRIM:
							normal[ind] = cswVector3::UEVector3(normal_in[i / 3]);
							break;

						case GZ_BIND_ON:
							normal[ind] = cswVector3::UEVector3(normal_in[index]);
							break;

					}


					// Tex -----------------------------------------------

					for (gzUInt32 layer = 0; layer < geom->getTextureUnits(); layer++)
					{
						switch (geom->getTexBind(layer))
						{
							case GZ_BIND_OFF:
								break;

							case GZ_BIND_OVERALL:
								texcoord.Set(ind, layer, cswVector2::UEVector2(texcoord_in[layer][0]));
								break;

							case GZ_BIND_PER_PRIM:
								texcoord.Set(ind, layer, cswVector2::UEVector2(texcoord_in[layer][i / 3]));
								break;


							case GZ_BIND_ON:
								texcoord.Set(ind, layer, cswVector2::UEVector2(texcoord_in[layer][index]));
								break;

						}
					}

					// Color -----------------------------------------------

					switch (geom->getColorBind())
					{
						case GZ_BIND_OFF:
							break;

						case GZ_BIND_OVERALL:
							colors[ind] = cswVector4::UEVector4(colors_in[0]);
							break;

						case GZ_BIND_PER_PRIM:
							colors[ind] = cswVector4::UEVector4(colors_in[i / 3]);
							break;

						case GZ_BIND_ON:
							colors[ind] = cswVector4::UEVector4(colors_in[index]);
							break;

					}
				}

				MeshDescription.CreatePolygon(PolygonGroupID, id);
			}
		}

	}

	// At least one material must be added
	TObjectPtr<UStaticMesh> staticMesh;

	staticMesh = NewObject<UStaticMesh>(this);

	staticMesh->bDoFastBuild = true;
	staticMesh->bSupportRayTracing = false;

	// Get material array
	TArray<FStaticMaterial>& materials = staticMesh->GetStaticMaterials();

	// Setup a static material
	FStaticMaterial staticMaterial;

	// Enable UVChannel data
	staticMaterial.UVChannelData.bInitialized = true;

	// Add the static material for current mesh
	materials.Add(staticMaterial);

	// Some extra build parmeters
	UStaticMesh::FBuildMeshDescriptionsParams mdParams;

	mdParams.bBuildSimpleCollision = buildProperties.buildSimpleCollision;
	mdParams.bFastBuild = buildProperties.fastBuild;
	mdParams.bCommitMeshDescription = false;
	mdParams.bAllowCpuAccess = false;
	//mdParams.bMarkPackageDirty = false;



	// Build static mesh ----------------------------------------------------------------------

	{
		GZ_INSTRUMENT_NAME("UCSWGeometry::build::mesh build");

		TArray<const FMeshDescription*> meshDescPtrs;
		meshDescPtrs.Emplace(&MeshDescription);
		staticMesh->BuildFromMeshDescriptions(meshDescPtrs, mdParams);
	}

	// Assign new static mesh to the static mesh component and finalize build ------------------

	{
		GZ_INSTRUMENT_NAME("UCSWGeometry::build::set mesh");
		m_meshComponent->SetStaticMesh(staticMesh);
	}

	UMaterialInterface* material = resources->getMaterial(this, state, CSW_MATERIAL_TYPE_BASE_MATERIAL);

	if(material)
		m_meshComponent->SetMaterial(0,material);
		

	{
		GZ_INSTRUMENT_NAME("UCSWGeometry::build::Attach & Register");

		m_meshComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

		m_meshComponent->RegisterComponent();
	}

	return true;
}

bool  UCSWGeometry::destroy(gzNode* destroyItem, cswResourceManager* resources)
{
	// Do cleanup

	GZ_INSTRUMENT_NAME("UCSWGeometry::destroy");

	m_meshComponent->DestroyComponent();

	return Super::destroy(destroyItem, resources);
}
