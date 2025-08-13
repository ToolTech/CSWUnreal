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
// File			: gzDbManager_dae.h
// Module		: 
// Description	: Class definition of the COLLADA format loader
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.262
//		
//
//			
// NOTE:	Gizmo3D is a high performance 3D Scene Graph and effect visualisation 
//			C++ toolkit for Linux, Mac OS X, Windows, Android, iOS and HoloLens for  
//			usage in Game or VisSim development.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	061116	Created file 	
//
//******************************************************************************
#ifndef __GZ_DB_DAE_H__
#define __GZ_DB_DAE_H__

/*!	\file 
	\brief Base definitions of a COLLADA database 

*/

#include "gzGroup.h"
#include "gzXML.h"

#include "gzSerialize.h"
#include "gzLicense.h"
#include "gzExceptions.h"
#include "gzXML.h"
#include "gzGroup.h"
#include "gzGeometry.h"

#include "gzNodeConstants.h"

// UserData Db INFO attributes
const gzString GZ_DB_INFO_TYPE_COLLADA = "dae";

class gzDbManager_dae : public gzDbManager	
{
public:

	GZ_DB_EXPORT gzDbManager_dae();

	GZ_DB_EXPORT virtual ~gzDbManager_dae();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	//GZ_DB_EXPORT virtual gzBool		saveDB(gzNode *node ,gzSerializeAdapter *adapter);

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;

	GZ_DB_EXPORT gzVoid registerInterface(const gzString &className, gzXmlCustomDataInterface *iface);

private:

	gzRefList<gzXmlCustomDataInterface>		m_interfaces;
};


// ---------------------------- gzDaeReader ----------------------------

enum DaeState
{
	DAE_STATE_UNKNOWN = 0,

	DAE_STATE_START_OF_DOCUMENT,
	DAE_STATE_COLLADA,
	DAE_STATE_EXTRA,
	DAE_STATE_ASSET,
	DAE_STATE_VERSION,

	DAE_STATE_PROFILE_COMMON,

	DAE_STATE_LIBRARY_IMAGES,
	DAE_STATE_LIBRARY_MATERIALS,
	DAE_STATE_LIBRARY_EFFECTS,
	DAE_STATE_LIBRARY_GEOMETRIES,
	DAE_STATE_LIBRARY_VISUAL_SCENES,

	DAE_STATE_SCENE,
	DAE_STATE_NODE,
	DAE_STATE_INSTANCE_VISUAL_SCENE,
	DAE_STATE_INSTANCE_GEOMETRY,

	DAE_STATE_GEOMETRY,
	DAE_STATE_MESH,
	DAE_STATE_SOURCE,
	DAE_STATE_FLOAT_ARRAY,
	DAE_STATE_ACCESSOR,
	DAE_STATE_VERTICES,

	DAE_STATE_INPUT,

	DAE_STATE_TRIANGLES,
	DAE_STATE_POLYLIST,
	DAE_STATE_VCOUNT,
	DAE_STATE_P,

	DAE_STATE_IMAGE,
	DAE_STATE_INIT_FROM,

	DAE_STATE_MATERIAL,
	DAE_STATE_INSTANCE_EFFECT,

	DAE_STATE_EFFECT,
	DAE_STATE_NEWPARAM,
	DAE_STATE_SURFACE,
	DAE_STATE_SAMPLER2D,

	DAE_STATE_TECHNIQUE,
	DAE_STATE_TEXTURE,
	DAE_STATE_DIFFUSE,

	DAE_STATE_TRANSLATE,
	DAE_STATE_SCALE,
	DAE_STATE_ROTATE,

	DAE_STATE_UNIT,
	DAE_STATE_UP_AXIS,

	DAE_STATE_CS,

	DAE_STATE_AUTHOR,
	DAE_STATE_COMMENTS,
};

enum DaeNewparamType
{
	DAE_NEWPARAM_TYPE_SURFACE = 0,
	DAE_NEWPARAM_TYPE_SAMPLER2D,
};

enum DaeUpAxis
{
	DAE_UP_AXIS_X,
	DAE_UP_AXIS_Y,
	DAE_UP_AXIS_Z,
};

// ------------------------------------------------------------------------------------------------

class gzDaeAsset : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzDaeAsset()
	{
		up_axis = DAE_UP_AXIS_Y;
		scale = 1;
	}

	DaeUpAxis	up_axis;
	gzFloat		scale;
};

GZ_DECLARE_REFPTR(gzDaeAsset);

// ------------------------------------------------------------------------------------------------

class gzDaeTexture : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString samplerId;
	gzString texCoord;
};

GZ_DECLARE_REFPTR(gzDaeTexture);

// ------------------------------------------------------------------------------------------------

class gzDaeNewparam : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString sid;
	DaeNewparamType type;

	// Type surface:
	gzString surfaceType;
	gzString initFrom;

	// Type sampler2d:
	gzString sampler2DSource;
};

GZ_DECLARE_REFPTR(gzDaeNewparam);

// ------------------------------------------------------------------------------------------------

class gzDaeTechnique : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString id;

	gzString profile;

	gzRefDict<gzString, gzDaeTexture> textures;
};

GZ_DECLARE_REFPTR(gzDaeTechnique);

// ------------------------------------------------------------------------------------------------

class gzDaeProfile : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString type;

	gzRefDict<gzString, gzDaeNewparam>	newparams;
	gzRefDict<gzString, gzDaeTechnique> techniques;
};

GZ_DECLARE_REFPTR(gzDaeProfile);

// ------------------------------------------------------------------------------------------------


class gzDaeEffect : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString id;
	
	gzRefDict<gzString, gzDaeProfile> profiles;
};

GZ_DECLARE_REFPTR(gzDaeEffect);

// ------------------------------------------------------------------------------------------------

class gzDaeMap : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzRefPointer<gzImage>	image;
	gzRefPointer<gzTexture> texture;
	gzRefPointer<gzTexEnv>	texenv;
	gzUInt16				options;
	gzFloat					filtering_blur;
	gzFloat					v_scale;
	gzFloat					u_scale;
	gzFloat					v_offset;
	gzFloat					u_offset;
};

GZ_DECLARE_REFPTR(gzDaeMap);

// ------------------------------------------------------------------------------------------------

class gzDaeInstanceEffect : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString	sid;
	gzString	name;
	gzString	url;
};

GZ_DECLARE_REFPTR(gzDaeInstanceEffect);

// ------------------------------------------------------------------------------------------------

class gzDaeInstanceGeometry : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString	sid;
	gzString	name;
	gzString	url;
};

GZ_DECLARE_REFPTR(gzDaeInstanceGeometry);

// ------------------------------------------------------------------------------------------------

class gzDaeMaterial : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;
	
	gzString id;
	gzString name;

	gzDaeInstanceEffectPtr		instance_effect;

	gzRefPointer<gzMaterial>	material;
	gzRefPointer<gzDaeMap>		diffuseMap;
	gzRefPointer<gzState>		state;
};

GZ_DECLARE_REFPTR(gzDaeMaterial);

// ------------------------------------------------------------------------------------------------

class gzDaeImage : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString id;
	gzString name;
	gzString url;
};

GZ_DECLARE_REFPTR(gzDaeImage);

// ------------------------------------------------------------------------------------------------

class gzDaeInput : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString sematic;							// Sematics of the input
	gzString source;							// Source of this particular input.
	gzUInt32 offset;							// Optional offset.
};

GZ_DECLARE_REFPTR(gzDaeInput);

// ------------------------------------------------------------------------------------------------

class gzDaePolygons : public gzReference
{
public:
	GZ_DECLARE_TYPE_INTERFACE;

	gzGeoPrimType					primType;

	gzString						material;
	gzUInt32						count;		// Total number of triangles/etc. in the polygon.
	gzRefDict<gzString, gzDaeInput> inputs;		// Dict of inputs: VERTEX, NORMAL, etc.
	gzDynamicArray<gzInt64>			vcount;		// Number of vertices per primitive.
	gzDynamicArray<gzInt64>			primitive;	// Array of vertex/normal/texcoord/(...) indices.


	virtual	gzBool	useDeepCopy() override	{ return FALSE; }
};

GZ_DECLARE_REFPTR(gzDaePolygons);

// ------------------------------------------------------------------------------------------------

class gzDaeSource : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString				id;					// Id of the source.
	gzDynamicArray<gzFloat> floatArray;			// Array of floats containing, for example, vertex x, y, z coordinates.
	gzUInt32				count;				// Number of vertices/normals/etc.
	gzUInt32				stride;				// Stride per vertex/normal/etc.
};

GZ_DECLARE_REFPTR(gzDaeSource);

// ------------------------------------------------------------------------------------------------

class gzDaeTriangles : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString							material;
	gzUInt32							count;
	gzString							name;

	gzRefDict<gzString, gzDaeInput>		inputs;
	gzDynamicArray<gzInt64>				p;
};

GZ_DECLARE_REFPTR(gzDaeTriangles);

// ------------------------------------------------------------------------------------------------

class gzDaeVertices : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString	id;
	gzRefDict<gzString, gzDaeInput>		inputs;

	
};

GZ_DECLARE_REFPTR(gzDaeVertices);

// ------------------------------------------------------------------------------------------------

class gzDaeTranslate : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzVec3	translate;
};

GZ_DECLARE_REFPTR(gzDaeTranslate);

// ------------------------------------------------------------------------------------------------

class gzDaeMesh : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzDaeVerticesPtr						vertices;
	gzRefDict<gzString, gzDaeSource>		sources;	// All the geometry sources.
	gzRefList<gzReference>					primitives;	// All primitives

	gzGroupPtr								group;
};

GZ_DECLARE_REFPTR(gzDaeMesh);

// ------------------------------------------------------------------------------------------------

class gzDaeGeometry : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString								id;			// Id of the geometry.
	gzString								name;		// Name of the geometry.

	gzReferencePtr							geometric_element;		// the geometric element

	gzDaeAssetPtr							asset;

	gzGroupPtr								geom;
};

GZ_DECLARE_REFPTR(gzDaeGeometry);

// ------------------------------------------------------------------------------------------------

class gzDaeNode : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	gzString								id;			// Id of the geometry.
	gzString								name;		// Name of the geometry.

	gzDaeAssetPtr							asset;

	gzRefList<gzReference>					elements;
};

GZ_DECLARE_REFPTR(gzDaeNode);

// ------------------------------------------------------------------------------------------------

class gzDaeScene : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	
	gzString								id;			// Id of the geometry.
	gzString								name;		// Name of the geometry.

	gzDaeAssetPtr							asset;

	gzRefList<gzDaeNode>					nodes;
};

GZ_DECLARE_REFPTR(gzDaeScene);

// ------------------------------------------------------------------------------------------------

// -------------------------------- gzDaeReader --------------------------------------------------------------

class gzDaeReader : public gzXmlSax
{
public:

	gzDaeReader(gzRefPointer<gzSerializeAdapter> adapter);
	virtual ~gzDaeReader();
	
	gzNode *getNode();

	//! When the instanced scene is not specified
	gzVoid buildAllScenes();

	GZ_PROPERTY_GET(gzBool, HasInstancedScene);

private:

	DaeState getStateFromString(const gzString & /*elementName*/);

	virtual	gzBool onElementStart(const gzString & /*elementName*/, gzUInt32 /*level*/);
	virtual	gzBool onElementEnd(const gzString & /*elementName*/, gzUInt32 /*level*/);
	virtual gzBool onAttribute(const gzString & /*attributeName*/, const gzString & /*attributeValue*/, gzUInt32 /*level*/);
	virtual	gzBool onElementAttributeEnd(const gzString & /*elementName*/, gzUInt32 /*level*/);
	virtual gzBool onCharData(const gzString & /*charData*/, gzUInt32 /*level*/);

	virtual gzBool processStateChange();
	virtual gzBool processStateLeave();

	gzParseResult parseFloatArray(gzDynamicArray<gzFloat> &dest);
	gzParseResult parseIntegerArray(gzDynamicArray<gzInt64> &dest);

	// -- Members ----------------------------------------------------------


	gzQueue<DaeState>		m_currentStateStack;
	gzQueue<gzDaeNodePtr>	m_currentNodeStack;

	gzDict<gzString, gzVoid> m_lookup;

	gzGroupPtr m_head;

	gzUInt32				m_skipLevels;

	gzDbInfoStatusBits		m_dbStatus;
	gzString				m_dbStatusMessage;

	//gzString				m_currentTechniqueProfile;

	gzRefDict<gzString, gzDaeGeometry>	m_geometries;		// All the geometries, inserted on id.
	gzRefDict<gzString, gzDaeImage>		m_images;
	gzRefDict<gzString, gzDaeMaterial>	m_materials;
	gzRefDict<gzString, gzDaeEffect>	m_effects;
	gzRefDict<gzString, gzDaeScene>		m_scenes;

	gzDaeAssetPtr						m_globalAsset;


	// Quick access pointers to a number of active elements.

	gzDaeScenePtr				m_currentScene;
	gzDaeNodePtr				m_referenceNode;
	gzDaeNodePtr				m_currentParent;
	gzDaeAssetPtr				m_currentAsset;
	gzDaeGeometryPtr			m_currentGeometry;
	gzDaeTrianglesPtr			m_currentTriangles;
	gzDaeMeshPtr				m_currentMesh;
	gzDaeVerticesPtr			m_currentVertices;
	gzDaeSourcePtr				m_currentSource;
	gzDaePolygonsPtr			m_currentPolylist;
	gzDaeInputPtr				m_currentInput;
	gzDaeImagePtr				m_currentImage;
	gzDaeMaterialPtr			m_currentMaterial;
	gzDaeEffectPtr				m_currentEffect;
	gzDaeNewparamPtr			m_currentNewparam;
	gzDaeTexturePtr				m_currentTexture;
	gzDaeProfilePtr				m_currentProfile;
	gzDaeTechniquePtr			m_currentTechnique;
	gzDaeInstanceEffectPtr		m_currentInstanceEffect;
	gzDaeInstanceGeometryPtr	m_currentInstanceGeometry;
	gzDaeTranslatePtr			m_currentTranslate;

	gzString				m_currentVerticesId;


	DaeState				m_currentState;
	DaeState				m_prevState;


	friend class gzDaeReaderParser;
	friend class float_array_dae;
	friend class p_array_dae;

	class gzDaeReaderParser				*m_parser;
	gzRefPointer<gzSerializeAdapter>	m_adapter;


	gzVoid buildMaterial(gzDaeMaterial *material);
	gzVoid buildGeometry(gzDaeGeometry *geometry, gzGroup *parent, gzMatrix4D currentTransform);
	gzVoid buildScene(gzDaeScene *scene);
	gzVoid buildNode(gzDaeNode *node,gzGroup *parent,gzMatrix4D currentTransform);

	gzVoid handleAttributeGeometry(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeSource(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeAccessor(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeVertices(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeInput(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributePolygons(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeImage(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeMaterial(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeInstanceEffect(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeEffect(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeNewparam(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeSurface(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeTexture(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeProfile(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeTechnique(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeTriangles(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeUnit(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeInstanceScene(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeScene(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);
	gzVoid handleAttributeInstanceGeometry(const gzString & attributeName, const gzString & attributeValue, gzUInt32 level);

};


#endif
