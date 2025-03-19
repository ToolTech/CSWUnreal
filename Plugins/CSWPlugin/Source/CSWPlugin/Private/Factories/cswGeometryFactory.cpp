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
// File			: cswGeometryFactory.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Implementation if factory for cswGeometry
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
#include "cswFactory.h"
#include "Builders/cswGeometry.h"
#include "gzGeometry.h"

// Glue
#include "UEGlue/cswUEMatrix.h"

#include "MeshDescription.h"
#include "StaticMeshAttributes.h"

#include "cswSceneManagerBase.h"

//---------------------- cswGeometryFactory -------------------------------------

class cswGeometryFactory : public cswFactory
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	virtual gzReference* clone() const
	{
		return new cswGeometryFactory(*this);
	}

	virtual UCSWSceneComponent* newObjectInstance(USceneComponent* parent,gzNode* node, EObjectFlags Flags, UObject* Template, bool bCopyTransientsFromClassDefaults, FObjectInstancingGraph* InInstanceGraph) override
	{
		UCSWGeometry *geom = NewObject<UCSWGeometry>(parent, node->getName().getWideString(),Flags,Template,bCopyTransientsFromClassDefaults,InInstanceGraph);

		return geom;
	}

	virtual gzReference* preBuildReferenceInstance(gzNode* node, const gzUInt64& pathID, gzGroup* parent, const gzUInt64& parentPathID, gzState* state) override;

	virtual gzVoid preDestroyReferenceInstance(gzNode* node, const gzUInt64& pathID, gzReference* userdata) override;
};

GZ_DECLARE_TYPE_CHILD(cswFactory, cswGeometryFactory, "cswGeometryFactory");

//---------------------- cswGeometryFactoryRegistrar -------------------------------------

class cswGeometryFactoryRegistrar : public gzReference
{
public:

	cswGeometryFactoryRegistrar()
	{
		cswFactoryPtr factory = new cswGeometryFactory;

		// register factory for object serialize
		m_id=gzObject::registerFactoryObject(factory);

		// register factory for component creation
		cswFactory::registerFactory("gzGeometry", factory);
	}

	gzBool	releaseRefs() 
	{ 
		if (m_id)
		{
			cswFactory::unregisterFactory("gzGeometry");

			// release factory early
			gzObject::unregisterFactory(m_id);
			m_id = 0;
		}

		return TRUE; 
	}

	~cswGeometryFactoryRegistrar()
	{
		// If not handled by releaseRefs earlier
		releaseRefs();
	}

private:

	gzUInt32 m_id;
};

gzCleanupReference cleanUpGeometryFactory(new cswGeometryFactoryRegistrar, GZ_CLEANUP_MODULES);


gzReference* cswGeometryFactory::preBuildReferenceInstance(gzNode* node, const gzUInt64& pathID, gzGroup* parent, const gzUInt64& parentPathID, gzState* state)
{
	// Assume we are called in dynamic load
	// We can then exit edit lock mode
	
	GZ_EDIT_GUARD_PAUSE;

	// Get Handle to geometry
	gzGeometry* geom = gzDynamic_Cast<gzGeometry>(node);

	if (!geom)
		return nullptr;

	switch (geom->getGeoPrimType())
	{

		case GZ_PRIM_NOPRIM:
		case GZ_PRIM_POINTS:
		case GZ_PRIM_LINES:
		case GZ_PRIM_LINESTRIPS:
		case GZ_PRIM_FLAT_LINESTRIPS:
		case GZ_PRIM_LINELOOPS:
			return nullptr;				// Lets just swallow these prims ok right now

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
			return nullptr;
	}

	cswGeometryBuild* build = new cswGeometryBuild;


	// Registrera så många UV-lager du behöver (standard är 1) // Om du vill ha fler lager:
	const int32 NumUVChannels = geom->getTextureUnits();

	// Mesh description will hold all the geometry, uv, normals going into the static mesh
	FMeshDescription MeshDescription;

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
		
	build->staticMesh = NewObject<UStaticMesh>();

	// Get material array
	TArray<FStaticMaterial>& materials = build->staticMesh->GetStaticMaterials();

	// Setup a static material
	FStaticMaterial staticMaterial;

	// Enable UVChannel data
	staticMaterial.UVChannelData.bInitialized = true;

	// Add the static material for current mesh
	materials.Add(staticMaterial);

	build->staticMesh->bDoFastBuild = true;
	build->staticMesh->bSupportRayTracing = false;

	// Some extra build parmeters
	UStaticMesh::FBuildMeshDescriptionsParams mdParams;

	mdParams.bBuildSimpleCollision = false;
	mdParams.bFastBuild = true;
	mdParams.bCommitMeshDescription = false;
	mdParams.bAllowCpuAccess = false;
	mdParams.bMarkPackageDirty = false;



	// Build static mesh ----------------------------------------------------------------------

	{
		GZ_INSTRUMENT_NAME("UCSWGeometry::build::mesh build");

		TArray<const FMeshDescription*> meshDescPtrs;
		meshDescPtrs.Emplace(&MeshDescription);
		build->staticMesh->BuildFromMeshDescriptions(meshDescPtrs, mdParams);
	}





	return build;
}

gzVoid cswGeometryFactory::preDestroyReferenceInstance(gzNode* node, const gzUInt64& pathID, gzReference* userdata)
{
	
}