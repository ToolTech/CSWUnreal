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
// File			: gzShader.h
// Module		: 
// Description	: Class definition of the gzShader class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.224
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
// AMO	020618	Created file 
// AMO	110916	Added Faceboard shaders									(2.5.22)
// AMO	111121	Added Tesselation Shaders								(2.5.32)
//
//******************************************************************************
#ifndef __GZ_SHADER_H__
#define __GZ_SHADER_H__

/*!	\file 
	\brief Base definitions of vertex and pixel shaders

*/


#include "gzMatrix.h"
#include "gzTexture.h"

// Forwards...
class gzContext;
class gzGFXProgram;
class gzState;

//! Defines the current types of program
enum gzGFXProgramType	{ 
							GZ_GFX_VERTEX_PROGRAM		= 0,
							GZ_GFX_GEOMETRY_PROGRAM		= 1,
							GZ_GFX_FRAGMENT_PROGRAM		= 2,
							GZ_GFX_SOFTWARE_PROGRAM		= 3,
							GZ_GFX_TESS_CTRL_PROGRAM	= 4,
							GZ_GFX_TESS_EVAL_PROGRAM	= 5,
							GZ_GFX_COMPUTE_PROGRAM		= 6,	// This many programs

							GZ_GFX_GLOBAL				= 7,	// For uniform attribs, Not a program
						};

const gzUInt32 GZ_NUMBER_OF_GFX_PROGRAM_TYPES = 7; 

// --------------------------  Enumerable for internal shader parameter syntax version -------------------------------

const gzUInt32 GZ_GFX_SHADER_VERSION = 2;

// 0,1	: Old legacy shader version
// 2	: Current Version					(2.12.131)

// ----------------------- Defined global parameters ----------------------

const gzString	GZ_GFX_GLOBAL_ENABLED_LIGHTS			= "gz_EnabledLights";			// bool[8]	for each lamp
const gzString	GZ_GFX_GLOBAL_ENABLED_LIGHT				= "gz_EnabledLight";			// bool		for all lamps
const gzString	GZ_GFX_GLOBAL_DEPTH_RENDER				= "gz_DepthRender";				// bool		TRUE if depth only rendering
const gzString	GZ_GFX_GLOBAL_RENDER_TIME				= "gz_RenderTime";				// float	seconds in current day
const gzString	GZ_GFX_GLOBAL_RENDER_DAY				= "gz_RenderDay";				// float	days since 1 jan 1990 
const gzString	GZ_GFX_GLOBAL_WIN_WIDTH					= "gz_WinWidth";				// float	width of rendering window  
const gzString	GZ_GFX_GLOBAL_WIN_HEIGHT				= "gz_WinHeight";				// float	height of rendering window  
const gzString	GZ_GFX_GLOBAL_HALF_ALPHA_STAGE			= "gz_HalfAlphaStage";			// float	current alpha stage 0=disabled,1,2,3
const gzString	GZ_GFX_GLOBAL_MAIN_TRANSFORM			= "gz_MainTransform";			// mat4		current camera modelview
const gzString	GZ_GFX_GLOBAL_MAIN_INVERTED_TRANSFORM	= "gz_MainInvertedTransform";	// mat4		current inverted camera modelview
const gzString	GZ_GFX_GLOBAL_PERSP_CAMERA_WIDTH		= "gz_PerspCamWidth";			// mat4		camera width, =0 if not persp camera
const gzString	GZ_GFX_GLOBAL_PERSP_CAMERA_HEIGHT		= "gz_PerspCamHeight";			// mat4		camera height
const gzString	GZ_GFX_GLOBAL_PERSP_CAMERA_WIDTH_FACT	= "gz_PerspCamWidthFact";		// mat4		camera width factor
const gzString	GZ_GFX_GLOBAL_PERSP_CAMERA_HEIGHT_FACT	= "gz_PerspCamHeightFact";		// mat4		camera height factor
const gzString	GZ_GFX_GLOBAL_CAMERA_NEAR				= "gz_CameraNear";				// mat4		camera Near dist
const gzString	GZ_GFX_GLOBAL_CAMERA_FAR				= "gz_CameraFar";				// mat4		camera Far dist
const gzString	GZ_GFX_GLOBAL_BASE_TRANSFORMS			= "gz_BaseTransforms";			// mat4[]	base transforms
const gzString	GZ_GFX_GLOBAL_BASE_TRANSFORM_COUNT		= "gz_BaseTransformCount";		// uint		nr of base transforms
const gzString	GZ_GFX_GLOBAL_TRANSPARENCY				= "gz_Transparency";			// float	a global transparency value
const gzString	GZ_GFX_GLOBAL_SHADER_VERSION			= "gz_ShaderVersion";			// uint		Current Gizmo Shader Version

// ----------------------- Preferred Attribute Names ------------------------

const gzString GZ_GFX_ATTRIB_TANGENT			= "gz_Tangent";			// tangent space coordinates
const gzString GZ_GFX_ATTRIB_VERTEX_WEIGHTS		= "gz_VertexWeights";	// Vertex Weights 4 x float (vec4)
const gzString GZ_GFX_ATTRIB_VERTEX_BASE_ID		= "gz_VertexBaseID";	// Vertex Weight Base ID transform 4 x float int (vec4)


//******************************************************************************
// Class	: gzParameterUpdateInfo
//									
// Purpose  : Keep bind info about global updates per context
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030422	Created 
//									
//******************************************************************************
class gzParameterUpdateInfo
{
public:

	gzParameterUpdateInfo():updateID(0),contextEnumerator(0xFFFFUL),attribIndexID(0){};

	gzUInt32							updateID;
	gzUInt32							contextEnumerator;
	gzUInt32							attribIndexID;
};


//******************************************************************************
// Class	: gzGFXProgramManager
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030204	Created 
// AMO	250227	Added thread safe reference so we can delete safely outside node lock (2.12.224)
//									
//******************************************************************************
class gzGFXProgramManager : public gzThreadSafeReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT virtual				~gzGFXProgramManager();

	GZ_GRAPH_EXPORT gzUInt32			getVersion()	{ return m_version;		}

	GZ_GRAPH_EXPORT virtual gzBool		isManagerFor(gzGFXProgram *program)=0;

	GZ_GRAPH_EXPORT virtual gzBool		activate(gzContext *context,gzGFXProgram *program,gzGFXProgramType type)=0;

	GZ_GRAPH_EXPORT virtual gzBool		deactivate(gzContext *context,gzGFXProgram *program,gzGFXProgramType type)=0; 

	GZ_GRAPH_EXPORT virtual gzVoid		cleanUpContext(gzContext * /*context*/){};

	GZ_GRAPH_EXPORT virtual gzVoid		resetProgram(gzGFXProgram * /*program*/){};

	GZ_GRAPH_EXPORT virtual gzVoid		deleteProgram(gzGFXProgram * /*program*/){};

	// ------ statics -------------

	GZ_GRAPH_EXPORT static gzVoid		registerManager(gzGFXProgramManager *manager);

	GZ_GRAPH_EXPORT static gzVoid		unregisterManagers();

	GZ_GRAPH_EXPORT static gzGFXProgramManager * getManagerForProgram(gzGFXProgram *program);

	GZ_GRAPH_EXPORT static gzVoid		cleanUpGFXData(gzContext *context);			\

protected:

	GZ_GRAPH_EXPORT virtual gzVoid		registerManager()=0;

	static gzRefList<gzGFXProgramManager> s_registeredGFXProgramManagers;

	gzUInt32				m_version;

};

enum gzGFXProgramParameterType
{
	GZ_GFX_PARAM_INTEGER,
	GZ_GFX_PARAM_FLOAT,
	GZ_GFX_PARAM_VEC2,
	GZ_GFX_PARAM_IVEC2,
	GZ_GFX_PARAM_VEC3,
	GZ_GFX_PARAM_IVEC3,
	GZ_GFX_PARAM_VEC4,
	GZ_GFX_PARAM_IVEC4,
	GZ_GFX_PARAM_MAT2,
	GZ_GFX_PARAM_MAT3,
	GZ_GFX_PARAM_MAT4
};

union gzFloatInt
{
	gzFloat	fVal;
	gzInt32	iVal;

	gzVoid      write(gzSerializeAdapter *adapter);
	gzVoid      read(gzSerializeAdapter *adapter);
	gzVoid      pushBack(gzSerializeAdapter *adapter);
	gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;

};

class gzGFXProgramParameter : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);

	GZ_GRAPH_EXPORT gzGFXProgramParameter();

	GZ_GRAPH_EXPORT gzGFXProgramParameter& operator=(const gzFloat& value);
	GZ_GRAPH_EXPORT gzGFXProgramParameter& operator=(const gzInt32& value);

	GZ_GRAPH_EXPORT gzGFXProgramParameter & operator=(const gzMatrix4 &mat);



	// ------------- clone ----------------------------------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
		
	// ---------- Serializing -------------------------------------------
	GZ_GRAPH_EXPORT gzVoid write(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzVoid read(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;


	gzString					name;
	gzUInt32					position;
	gzBool						usePosition;
	gzGFXProgramParameterType	type;

	gzArray<gzFloatInt>			values;
};

GZ_DECLARE_REFPTR(gzGFXProgramParameter);

class gzGlobalGFXProgramParams
{
public:

	gzRefList<gzGFXProgramParameter>		params;
	gzDynamicArray<gzParameterUpdateInfo>	updateInfo;
};

class GZ_GRAPH_EXPORT gzVertexAttributeIndex : public gzReference
{
public:

	virtual ~gzVertexAttributeIndex(){};

	virtual gzReference* clone() const
	{
		return new gzVertexAttributeIndex(*this);
	}

	// ---------- Serializing -------------------------------------------
	gzVoid		write(gzSerializeAdapter *adapter);
	gzVoid		read(gzSerializeAdapter *adapter);
	gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;

	gzString		name;
	gzUInt32		index;
};

//----------------- Special Create Attributes --------------

const gzString GZ_GFX_PROGRAM_SETTINGS					=	"GZ_GFX_PROGRAM_SETTINGS";

//---------------- Special for geometry programs ----------

const gzString GZ_GFX_GEOMETRY_PROGRAM_INPUT_TYPE		=	"GZ_GFX_GEOMETRY_PROGRAM_INPUT_TYPE";
const gzString GZ_GFX_GEOMETRY_PROGRAM_OUTPUT_TYPE		=	"GZ_GFX_GEOMETRY_PROGRAM_OUTPUT_TYPE";
const gzString GZ_GFX_GEOMETRY_PROGRAM_VERTICES_OUT		=	"GZ_GFX_GEOMETRY_PROGRAM_VERTICES_OUT";

enum gzGFXProgramFeatureVariant
{
	GZ_GFX_PROGRAM_FEATURE_VARIANT_UNKNOW,
	GZ_GFX_PROGRAM_FEATURE_VARIANT_1,
	GZ_GFX_PROGRAM_FEATURE_VARIANT_2,
	GZ_GFX_PROGRAM_FEATURE_VARIANT_3,
	GZ_GFX_PROGRAM_FEATURE_VARIANT_4,
	GZ_GFX_PROGRAM_FEATURE_VARIANT_5,
	GZ_GFX_PROGRAM_FEATURE_VARIANT_6,
	GZ_GFX_PROGRAM_FEATURE_VARIANT_7,
	GZ_GFX_PROGRAM_FEATURE_VARIANT_8,
	GZ_GFX_PROGRAM_FEATURE_VARIANT_9,
	GZ_GFX_PROGRAM_FEATURE_VARIANT_10,	// ETC..
};

enum gzGFXProgramErrorLevel
{
	GZ_GFX_PROGRAM_ERROR_LEVEL_NONE=0,
	GZ_GFX_PROGRAM_ERROR_LEVEL_WARNING=1,
	GZ_GFX_PROGRAM_ERROR_LEVEL_ERROR=2,
};

//******************************************************************************
// Class	: gzGFXProgram
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	020618	Created 
//									
//******************************************************************************
class gzGFXProgram : public gzObject , public gzNameInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzGFXProgram(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzGFXProgram();

	GZ_GRAPH_EXPORT virtual gzBool	activate(gzContext *context,gzGFXProgramType type);

	GZ_GRAPH_EXPORT virtual gzBool	deactivate(gzContext *context,gzGFXProgramType type); 

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
	GZ_GRAPH_EXPORT virtual gzBool useDeepCopy() override;

	// ---------- gzGFXProgram interface --------------------------------------

	//! Set the program script in the script string
	GZ_GRAPH_EXPORT gzVoid				setProgramScript(const gzString &script);

	//! Loads the program script from the url adress
	GZ_GRAPH_EXPORT gzBool				loadProgramScript(const gzString &url);

	//! Return the program script
	GZ_GRAPH_EXPORT const gzString	&	getProgramScript();

	//! return the current manager for the program.
	GZ_GRAPH_EXPORT gzGFXProgramManager *getCurrentManager() { return m_manager.get(); }

	//! returns true if script is wrong
	GZ_GRAPH_EXPORT gzBool				hasError(gzGFXProgramErrorLevel level=GZ_GFX_PROGRAM_ERROR_LEVEL_ERROR);
	
	//! Get the error string. Typical error description + position
	GZ_GRAPH_EXPORT const gzString &	getError();
	
	//! Error position on line or text character from start
	GZ_GRAPH_EXPORT	gzUInt16			getErrorPos();

	GZ_GRAPH_EXPORT gzGFXProgramErrorLevel getErrorLevel();
	
	//! Force to set an error. Disables activation
	GZ_GRAPH_EXPORT gzVoid				setError(const gzString & error,gzGFXProgramErrorLevel level=GZ_GFX_PROGRAM_ERROR_LEVEL_ERROR,gzInt16 line=-1);


	GZ_GRAPH_EXPORT gzVoid				setManagerData(gzReference *data);
	GZ_GRAPH_EXPORT gzReference *		getManagerData();

	//! Set the fallback program if program fails
	GZ_GRAPH_EXPORT gzVoid				setFallbackProgram(gzGFXProgram *program);
	GZ_GRAPH_EXPORT gzGFXProgram *		getFallbackProgram();

	// ---------- Vertex Attributes --------------------------------------------

	GZ_GRAPH_EXPORT gzVoid		bindVertexAttribute(const gzString &name, gzUInt32 index); 
	GZ_GRAPH_EXPORT gzUInt32	getVertexAttributeIndex(const gzString &name);
	GZ_GRAPH_EXPORT const gzRefList<gzVertexAttributeIndex> & getVertexAttributeIndexList();


	// ---------- Index Local Attributes ---------------------------------------

	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzUInt32& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzInt32& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzFloat& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzVec2& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzVec3& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzVec4& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzMatrix2& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzMatrix3& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzMatrix4& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzArray<gzFloat>& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzArray<gzInt32>& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzArray<gzVec3>& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzArray<gzVec4>& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzArray<gzMatrix3>& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(gzUInt32 index, const gzArray<gzMatrix4>& val);

	GZ_GRAPH_EXPORT const gzGFXProgramParameter * getLocalParameter(gzUInt32 index,gzGFXProgramParameterType type, gzBool update=FALSE);

	GZ_GRAPH_EXPORT const gzRefList<gzGFXProgramParameter> & getLocalParameterList();

	// ---------- Named Local Attributes ---------------------------------------

	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzUInt32& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzInt32& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzFloat& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzVec2& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzVec3& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzVec4& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzMatrix2& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzMatrix3& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzMatrix4& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzArray<gzFloat>& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzArray<gzInt32>& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzArray<gzVec3>& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzArray<gzVec4>& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzArray<gzMatrix3>& val);
	GZ_GRAPH_EXPORT gzVoid	setLocalParameter(const gzString& name, const gzArray<gzMatrix4>& val);

	GZ_GRAPH_EXPORT const gzGFXProgramParameter * getLocalParameter(const gzString &name,gzGFXProgramParameterType type,gzBool update=FALSE);
	GZ_GRAPH_EXPORT gzVoid	addLocalParameter(gzGFXProgramParameter *param);


	GZ_GRAPH_EXPORT gzParameterUpdateInfo & getLocalUpdateInfo(gzUInt32 contextID);

	GZ_GRAPH_EXPORT gzVoid	useGlobalProgramScripts(gzBool on);
	GZ_GRAPH_EXPORT gzBool	useGlobalProgramScripts();

	// ---------- operators --------------------------------------------
	//!Equal operator
	GZ_GRAPH_EXPORT gzBool operator==(const gzGFXProgram& right) const;

	// ---------- Serializing -------------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	//! Release all external references
	GZ_GRAPH_EXPORT virtual gzBool releaseRefs() override;

	// ----------- Globals ----------------------------------------------------

	static GZ_GRAPH_EXPORT gzParameterUpdateInfo & getGlobalUpdateInfo(gzUInt32 contextID,gzGFXProgramType type=GZ_GFX_GLOBAL);

	// ---------- Index Global Attributes ---------------------------------------

	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(gzUInt32 index,const gzFloat &val,gzBool integer=FALSE,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(gzUInt32 index,const gzVec2 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(gzUInt32 index,const gzVec3 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(gzUInt32 index,const gzVec4 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(gzUInt32 index,const gzMatrix2 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(gzUInt32 index,const gzMatrix3 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(gzUInt32 index,const gzMatrix4 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);

	static GZ_GRAPH_EXPORT const gzGFXProgramParameter * getGlobalParameter(gzUInt32 index,gzGFXProgramParameterType type,gzGFXProgramType programType=GZ_GFX_GLOBAL,gzBool update=FALSE);

	static GZ_GRAPH_EXPORT const gzRefList<gzGFXProgramParameter> & getGlobalParameterList(gzGFXProgramType type=GZ_GFX_GLOBAL);

	// ---------- Named Global Attributes ---------------------------------------

	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(const gzString &name,const gzFloat &val,gzBool integer=FALSE,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(const gzString &name,const gzVec2 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(const gzString &name,const gzVec3 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(const gzString &name,const gzVec4 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(const gzString &name,const gzMatrix2 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(const gzString &name,const gzMatrix3 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(const gzString &name,const gzMatrix4 &val,gzGFXProgramType type=GZ_GFX_GLOBAL);
	static GZ_GRAPH_EXPORT gzVoid	setGlobalParameter(const gzString &name,const gzBool (&val)[8],gzGFXProgramType type=GZ_GFX_GLOBAL);

	static GZ_GRAPH_EXPORT const gzGFXProgramParameter * getGlobalParameter(const gzString &name,gzGFXProgramParameterType type,gzGFXProgramType programType=GZ_GFX_GLOBAL,gzBool update=FALSE);

	// ---------- Global program scripts ----------------------------------------

	static GZ_GRAPH_EXPORT gzVoid						setGlobalProgramScript(gzGFXProgramType type , gzUInt32 index,const gzString &script);
	static GZ_GRAPH_EXPORT gzDynamicArray<gzString> &	getGlobalProgramScripts(gzGFXProgramType type,gzBool update=FALSE);
	static GZ_GRAPH_EXPORT gzUInt32						getGlobalProgramScriptUpdateID(gzGFXProgramType type);

	// ---------- Generic program scripts ---------------------------------------

	static GZ_GRAPH_EXPORT gzGFXProgram *getProgram(const gzString &name,gzGFXProgramType type,gzBool shared=FALSE);
	static GZ_GRAPH_EXPORT gzVoid registerProgram(const gzString &name,gzGFXProgramType type,gzGFXProgram *program);
	static GZ_GRAPH_EXPORT gzVoid unregisterProgram(const gzString &name,gzGFXProgramType type,gzGFXProgram *program);
	static GZ_GRAPH_EXPORT gzVoid clearPrograms();

	// ----------------- Some Properties -----------------------------

	GZ_PROPERTY_EXPORT(gzInt16,						ErrorLine,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzGFXProgramFeatureVariant,	FeatureVariant,		GZ_GRAPH_EXPORT);

private:

	gzString									m_script;
												
	gzRefPointer<gzGFXProgramManager>			m_manager;
											
	gzBool										m_useGlobalProgramScripts;

	gzGFXProgramErrorLevel						m_errorLevel;
												
	gzString									m_error;

	gzRefList<gzGFXProgramParameter>			m_params;

	gzRefList<gzVertexAttributeIndex>			m_vertexAttributeIndex;

	gzDynamicArray<gzParameterUpdateInfo>		m_updateInfo;

	gzRefPointer<gzReference>					m_managerData;

	gzRefPointer<gzGFXProgram>					m_fallbackProgram;

	static gzGlobalGFXProgramParams				s_globalEnvParams[GZ_NUMBER_OF_GFX_PROGRAM_TYPES+1];

	static gzDynamicArray<gzString>				s_globalProgramScripts[GZ_NUMBER_OF_GFX_PROGRAM_TYPES];

	static gzUInt32								s_globalProgramScriptsUpdateID[GZ_NUMBER_OF_GFX_PROGRAM_TYPES];

	static gzRefDict<gzString,gzGFXProgram>		s_registeredPrograms[GZ_NUMBER_OF_GFX_PROGRAM_TYPES];

	static gzMutex								s_programLocker;
};

GZ_DECLARE_REFPTR(gzGFXProgram);

//******************************************************************************
// Class	: gzGFXProgramManager_VFP_1
//									
// Purpose  : Vertex and Fragment program manager low level (ARB VP & FP)
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030204	Created 
//									
//******************************************************************************
class gzGFXProgramManager_VFP_1 : public gzGFXProgramManager
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT					gzGFXProgramManager_VFP_1();

	GZ_GRAPH_EXPORT virtual			~gzGFXProgramManager_VFP_1();

	GZ_GRAPH_EXPORT virtual gzBool	isManagerFor(gzGFXProgram *program) override;

	GZ_GRAPH_EXPORT virtual gzBool	activate(gzContext *context,gzGFXProgram *program,gzGFXProgramType type) override;

	GZ_GRAPH_EXPORT virtual gzBool	deactivate(gzContext *context,gzGFXProgram *program,gzGFXProgramType type) override; 

	GZ_GRAPH_EXPORT virtual gzVoid	cleanUpContext(gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid	resetProgram(gzGFXProgram *program) override;

	GZ_GRAPH_EXPORT virtual gzVoid	deleteProgram(gzGFXProgram *program) override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

protected:

	GZ_GRAPH_EXPORT virtual gzVoid	registerManager() override;

private:

	static gzQueue<gzUInt32>							s_deleteBindID;

	static gzDynamicArray<gzParameterUpdateInfo>	s_updateInfo[GZ_NUMBER_OF_GFX_PROGRAM_TYPES];
};	

//******************************************************************************
// Class	: gzGFXProgramManager_GLSL_VS_1
//									
// Purpose  : Shader manager for GLSL
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040421	Created 
//									
//******************************************************************************
class gzGFXProgramManager_GLSL_1 : public gzGFXProgramManager
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT					gzGFXProgramManager_GLSL_1();

	GZ_GRAPH_EXPORT virtual			~gzGFXProgramManager_GLSL_1();

	GZ_GRAPH_EXPORT virtual gzBool	isManagerFor(gzGFXProgram *program) override;

	GZ_GRAPH_EXPORT virtual gzBool	activate(gzContext *context,gzGFXProgram *program,gzGFXProgramType type) override;

	GZ_GRAPH_EXPORT virtual gzBool	deactivate(gzContext *context,gzGFXProgram *program,gzGFXProgramType type) override; 

	GZ_GRAPH_EXPORT virtual gzVoid	cleanUpContext(gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid	resetProgram(gzGFXProgram *program) override;

	GZ_GRAPH_EXPORT virtual gzVoid	deleteProgram(gzGFXProgram *program) override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

protected:

	GZ_GRAPH_EXPORT virtual gzVoid	registerManager() override;

	GZ_GRAPH_EXPORT gzVoid setUniform(gzInt32 index,gzGFXProgramParameter *parameter);

private:

	static gzQueue<gzHandle>						s_deleteHandles;
};

// --------------------- gzGFXProgramPreCache --------------------

class gzGFXProgramPreCache
{
public:

	GZ_GRAPH_EXPORT	gzGFXProgramPreCache();

	GZ_GRAPH_EXPORT gzVoid upload(gzContext *context);

	GZ_GRAPH_EXPORT gzVoid addState(gzState *state);

	GZ_PROPERTY_EXPORT(gzUInt32,		MaxUploadsPerFrame,		GZ_GRAPH_EXPORT);

private:

	gzMutex					m_locker;

	gzRefList<gzState>		m_states;

};


GZ_GRAPH_EXPORT gzVoid gzInitializeGFXProgramManagers();
GZ_GRAPH_EXPORT gzVoid gzUninitializeGFXProgramManagers();

// ----------------------- BuiltIn Programs -------------------

//  Programs --

const gzString GZ_ALPHA_NORMAL_VP				=	"GZ_ALPHA_NORMAL_VP";		//! Renders alpha modulated by view vector and normals
const gzString GZ_ALPHA_NORMAL_DS_VP			=	"GZ_ALPHA_NORMAL_DS_VP";	//! Renders alpha modulated by view vector and normals, double sided
const gzString GZ_ALPHA_NORMAL_LOD_VP			=	"GZ_ALPHA_NORMAL_LOD_VP";
//  Programs --

const gzString GZ_PBR_VP			=	"GZ_PBR_VP";			//! Interpolates the normal over a surface
const gzString GZ_PBR_FP			=	"GZ_PBR_FP";			//! Interpolates the normal over a surface
const gzString GZ_SIMPLE_PBR_FP		=	"GZ_SIMPLE_PBR_FP";		//! Interpolates the normal over a surface, no specular and no bump
const gzString GZ_WATER_FP			=	"GZ_WATER_FP";			//! Interpolates the normal over a water
const gzString GZ_WATER_VP			=	"GZ_WATER_VP";			//! Interpolates the normal over a water
const gzString GZ_FALLBACK_FP		=	"GZ_FALLBACK_FP";		//! Fallback fragment shader

// Imposter Programs --

const gzString GZ_CROSSBOARD_VP		= "GZ_CROSSBOARD_VP";		// Generates split cross imposter from point
const gzString GZ_CROSSBOARD_GP		= "GZ_CROSSBOARD_GP";		// 
const gzString GZ_CROSSBOARD_FP		= "GZ_CROSSBOARD_FP";		// 

const gzString GZ_CROSSVOLUME_VP	= "GZ_CROSSVOLUME_VP";		// Generates split cross imposter from point
const gzString GZ_CROSSVOLUME_GP	= "GZ_CROSSVOLUME_GP";		// 
const gzString GZ_CROSSVOLUME_FP	= "GZ_CROSSVOLUME_FP";		// 

const gzString GZ_FACEBOARD_VP		= "GZ_FACEBOARD_VP";		// Generates face imposter from point
const gzString GZ_FACEBOARD_GP		= "GZ_FACEBOARD_GP";		// 
const gzString GZ_FACEBOARD_FP		= "GZ_FACEBOARD_FP";		// 

// ------------- Some generic program param names ------------

const gzString GZ_PARAM_INDEX				= gzUniqueString("index",40);
const gzString GZ_PARAM_USE_COLORS			= gzUniqueString("useColors",41);
const gzString GZ_PARAM_MAX_HALF_DIST		= gzUniqueString("maxHalfDist",42);
const gzString GZ_PARAM_INV_LOD_FACTOR_MAG	= gzUniqueString("invLodFactorMag",43);
const gzString GZ_PARAM_INV_SCALE_MAG		= gzUniqueString("invScaleMag",44);
const gzString GZ_PARAM_LOD_NEAR			= gzUniqueString("lodNear",45);
const gzString GZ_PARAM_LOD_NEAR_FADE		= gzUniqueString("lodNearFade",46);
const gzString GZ_PARAM_LOD_FAR				= gzUniqueString("lodFar",47);
const gzString GZ_PARAM_LOD_FAR_FADE		= gzUniqueString("lodFarFade",48);
const gzString GZ_PARAM_WIND_SPEED			= gzUniqueString("windSpeed",49);
const gzString GZ_PARAM_USE_WIND			= gzUniqueString("useWind",50);
const gzString GZ_PARAM_WIND_STRENGTH		= gzUniqueString("windStrength",51);
const gzString GZ_PARAM_SCALE				= gzUniqueString("scale",52);
const gzString GZ_PARAM_TEXTURE_DATA		= gzUniqueString("texData",53);
const gzString GZ_PARAM_SHADOW_MAP_TRANS	= gzUniqueString("shadowMapTransform",54);
const gzString GZ_PARAM_SHADOW_MAP_WIDTH	= gzUniqueString("shadowMapWidth",55);
const gzString GZ_PARAM_SHADOW_MAP_HEIGHT	= gzUniqueString("shadowMapHeight",56);
const gzString GZ_PARAM_USE_SOFT_SHADOW		= gzUniqueString("useSoftShadow",57);
const gzString GZ_PARAM_OFFSET				= gzUniqueString("offset", 58);
const gzString GZ_PARAM_USE_LOD				= gzUniqueString("useLod", 59);
const gzString GZ_PARAM_BASE_COLOR			= gzUniqueString("baseColor", 60);
const gzString GZ_PARAM_MAX_SCALE			= gzUniqueString("maxScale", 61);

// Some specific image names

const gzString GZ_IMAGE_MAP_METAL_ROUGNESS	= gzUniqueString("_METAL_ROUGH_",62);
const gzString GZ_IMAGE_MAP_SHADOW			= gzUniqueString("_SHADOW_",63);
const gzString GZ_IMAGE_MAP_NORMAL			= gzUniqueString("_NORMAL_",64);	
const gzString GZ_IMAGE_MAP_ALBEDO			= gzUniqueString("_ALBEDO_", 87);
const gzString GZ_IMAGE_MAP_OCCLUSION		= gzUniqueString("_OCCLUSION_", 84);
const gzString GZ_IMAGE_MAP_EMISSION		= gzUniqueString("_EMISSION_", 86);


// Default texture
const gzString GZ_PARAM_BASE_MAP			= gzUniqueString("baseMap", 65);
const gzString GZ_PARAM_USE_BASE_MAP		= gzUniqueString("useBaseMap", 77);
const gzString GZ_PARAM_BASE_MAP_TEX_INDEX	= gzUniqueString("baseMapTexIndex", 73);

// Normal texture (bump)
const gzString GZ_PARAM_NORMAL_MAP									= gzUniqueString("normalMap", 66);
const gzString GZ_PARAM_USE_NORMAL_MAP								= gzUniqueString("useNormalMap", 67);
const gzString GZ_PARAM_NORMAL_MAP_TEX_INDEX						= gzUniqueString("normalMapTexIndex", 72);

// Metallic/Roughness Map (shininess)
const gzString GZ_PARAM_METALLIC_ROUGHNESS_MAP						= gzUniqueString("metallicRoughnessMap", 68);
const gzString GZ_PARAM_USE_METALLIC_ROUGHNESS_MAP					= gzUniqueString("useMetallicRoughnessMap", 69);

// Shadow Map
const gzString GZ_PARAM_SHADOW_MAP									= gzUniqueString("shadowMap", 70);
const gzString GZ_PARAM_USE_SHADOW_MAP								= gzUniqueString("useShadowMap", 71);	

// Metallic Roughness
const gzString GZ_PARAM_METALLIC_FACTOR								= gzUniqueString("metallicFactor", 74);
const gzString GZ_PARAM_ROUGHNESS_FACTOR							= gzUniqueString("roughnessFactor", 85);	
const gzString GZ_PARAM_METALLIC_ROUGHNESS_MAP_TEX_INDEX			= gzUniqueString("metallicRoughnessMapTexIndex", 76);	

// Occlusion map
const gzString GZ_PARAM_OCCLUSION_MAP								= gzUniqueString("occlusionMap", 78);
const gzString GZ_PARAM_USE_OCCLUSION_MAP							= gzUniqueString("useOcclusionMap", 79);
const gzString GZ_PARAM_OCCLUSION_MAP_TEX_INDEX						= gzUniqueString("occlusionMapTexIndex", 80);	

// Omissive map
const gzString GZ_PARAM_EMISSIVE_MAP								= gzUniqueString("emissiveMap", 81);
const gzString GZ_PARAM_USE_EMISSIVE_MAP							= gzUniqueString("useEmissiveMap", 82);
const gzString GZ_PARAM_EMISSIVE_MAP_TEX_INDEX						= gzUniqueString("emissiveMapTexIndex", 83);	


// CURRENT LAST ID for Graph = 87

// ----------------------- BuiltIn Generic States ------------

GZ_GRAPH_EXPORT gzState * gzGetBuiltInState_PBR(gzTexture *albedo_texture=nullptr, gzTexture* normal_texture = NULL,gzTexture *metal_roughness_texture=nullptr,gzTexture *occlusion_texture=nullptr,gzTexture *emission_texture=nullptr,gzTexture *shadow_texture=nullptr);
GZ_GRAPH_EXPORT gzState * gzGetBuiltInState_Water(gzBool useWaterVP=FALSE);

#endif
