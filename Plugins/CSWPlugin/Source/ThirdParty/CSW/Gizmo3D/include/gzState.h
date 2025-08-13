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
// File			: gzState.h
// Module		: 
// Description	: Class definition of the gzState class
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
// AMO	981111	Created file
//
//******************************************************************************
#ifndef __GZ_STATE_H__
#define __GZ_STATE_H__

/*!	\file 
	\brief Base definitions for state management (textures, materials etc.)

*/

/*! Definitions of the various stages a render does. You can select the rendering state with a gzState */

typedef enum {	GZ_ACTION_STAGE_TRAVERSE					=-1,	//!< Special Traverse stage, no rendering
				GZ_ACTION_STAGE_DEFAULT						=3,		//!< Defines the default rendering stage

				GZ_ACTION_STAGE_UNDERLAY					=0,		//!< First stage, Scene Graph Order
				GZ_ACTION_STAGE_FRONT_TO_BACK				=1,		//!< Sorts in depth
				GZ_ACTION_STAGE_USER_1						=2,		//!< User available
				GZ_ACTION_STAGE_SORTED_TEXTURE				=3,		//!< sorts in textures
				GZ_ACTION_STAGE_SORTED_NOFLIP_TEXTURE		=4,		//!< sorts in textures but without flip texture order
				GZ_ACTION_STAGE_MULTIPASS_TEXTURE			=5,		//!< additive multitexture pass
				GZ_ACTION_STAGE_SCENE_GRAPH_ORDER			=6,		//!< renders according to scene graph order
				GZ_ACTION_STAGE_USER_2						=7,		//!< User avail
				GZ_ACTION_STAGE_BACK_TO_FRONT				=8,		//!< sorts in depth with Z buffer
				GZ_ACTION_STAGE_USER_3						=9,		//!< User avail
				GZ_ACTION_STAGE_ALPHA_SORTED_TRANSPARENCY	=10,	//!< sorted transparency using alpha as sort
				GZ_ACTION_STAGE_SEPARATE_ALPHA_HIGHQ		=11,	//!< four pass, non sorted sorted transparency using separate 4 pass alpha
				GZ_ACTION_STAGE_SEPARATE_ALPHA				=12,	//!< two pass, non sorted sorted transparency using separate 2 pass alpha
				GZ_ACTION_STAGE_HALF_ALPHA					=13,	//!< three pass, non sorted sorted transparency using 3 pass alpha
				GZ_ACTION_STAGE_USER_4						=14,	//!< User avail
				GZ_ACTION_STAGE_SHADOWED_TRANSPARENCY		=15,	//!< sorted transparency in depth back to front, shadowed
				GZ_ACTION_STAGE_NO_DEPTH_UPDATE				=16,	//!< non sorted transparency without depth update
				GZ_ACTION_STAGE_SHADOW						=17,	//!< late rendering, after all normal passes
				GZ_ACTION_STAGE_TRANSPARENCY				=18,	//!< sorted transparency in depth back to front
				GZ_ACTION_STAGE_USER_5						=19,	//!< User avail
				GZ_ACTION_STAGE_OVERLAY						=20,	//!< overlay, no depth cull, Scene graph order
				GZ_ACTION_STAGE_USER_6						=21,	//!< User avail
				GZ_ACTION_STAGE_COUNT						=22,	//!< How many stages... don't use..
				GZ_ACTION_STAGE_PRE_RENDER					=23,	//!< Stage in preRender
				GZ_ACTION_STAGE_POST_RENDER					=24,	//!< Stage in postRender
			 } gzActionStage;

//! Define how you want to change the state in a gzState object. The GZ_STATE_GLOBAL leaves it as the parent hierarchy has defined it
typedef enum { GZ_STATE_ON , GZ_STATE_OFF , GZ_STATE_GLOBAL } gzStateModeActivation;


#include "gzObject.h"
#include "gzMatrix.h"
#include "gzTexture.h"
#include "gzMaterial.h"
#include "gzTexEnv.h"
#include "gzTexGen.h"
#include "gzShader.h"

class gzContext;	// Forward decl of graphics context

//! Various features you can turn on/off in a gzState
typedef enum {	
				GZ_STATE_EMPTY				= 0 ,
				GZ_STATE_LINE_STIPPLE		= (1 << 0), //!<	Enable line stipple parameters
				GZ_STATE_POLYGON_MODE		= (1 <<	1),	//!<	Enable polygon mode parameters.
				GZ_STATE_BLENDING			= (1 <<	2), //!<	Enable blending parameters
				GZ_STATE_TEXTURE			= (1 << 3), //!<	Enable textures
				GZ_STATE_MATERIAL			= (1 << 4), //!<	Enable materials
				GZ_STATE_TEXENV				= (1 << 5), //!<	Enable texture environment
				GZ_STATE_TEXGEN				= (1 << 6), //!<	Enable texture coord generation
				GZ_STATE_POLYGON_OFFSET		= (1 << 7), //!<	Enable polygon offset
				GZ_STATE_ACTION_STAGE		= (1 << 8), //!<	Set active rendering stage
				GZ_STATE_GENERATE_DEBUG_INFO= (1 << 9), //!<	Generate debug info
				GZ_STATE_ALPHA_FUNC			= (1 << 10),//!<	Enable alpha func
				GZ_STATE_GFX_PROGRAM		= (1 << 11),//!<	Enable GFX Programs

			 } gzStateMode;

GZ_USE_BIT_LOGIC(gzStateMode);		// Allow | & operators for gzStateMode

//! Various modes for polygon modes
enum gzPolygonModeType 
{
	GZ_POLYGON_MODE_FILL,	//!<	Enable filled polygons (Default)
	GZ_POLYGON_MODE_LINE,	//!<	The polygons are drawn using lines between vertices.
	GZ_POLYGON_MODE_POINT,	//!<	The polygons are drawn using points for each vertex.
	GZ_POLYGON_MODE_CULL	//!<	The polygons are not drawn
};

//! A default set of blending factors.
enum gzStateBlendFactor
{	
	GZ_STATE_BLEND_ZERO					=GZ_ZERO ,					//!<	RGBA blend factor = (0, 0, 0, 0)
	GZ_STATE_BLEND_ONE					=GZ_ONE,					//!<	RGBA blend factor = (1, 1, 1, 1)
	GZ_STATE_BLEND_DST_COLOR			=GZ_DST_COLOR ,				//!<	RGBA blend factor = (R_destination, G_destination, B_destination, A_destination)
	GZ_STATE_BLEND_SRC_COLOR			=GZ_SRC_COLOR ,				//!<	RGBA blend factor = (R_source, G_source, B_source, A_source)
	GZ_STATE_BLEND_ONE_MINUS_DST_COLOR	=GZ_ONE_MINUS_DST_COLOR,	//!<	RGBA blend factor = (1-R_destination, 1-R_destination, 1-R_destination, 1-R_destination)
	GZ_STATE_BLEND_ONE_MINUS_SRC_COLOR	=GZ_ONE_MINUS_SRC_COLOR,	//!<	RGBA blend factor = (1-R_source, 1-G_source, 1-B_source, 1-A_source)
	GZ_STATE_BLEND_SRC_ALPHA			=GZ_SRC_ALPHA,				//!<	RGBA blend factor = (A_source, A_source, A_source, A_source)
	GZ_STATE_BLEND_ONE_MINUS_SRC_ALPHA	=GZ_ONE_MINUS_SRC_ALPHA,	//!<	RGBA blend factor = (1-A_source, 1-A_source, 1-A_source, 1-A_source)
	GZ_STATE_BLEND_DST_ALPHA			=GZ_DST_ALPHA,				//!<	RGBA blend factor = (A_destination, A_destination, A_destination, A_destination)
	GZ_STATE_BLEND_ONE_MINUS_DST_ALPHA	=GZ_ONE_MINUS_DST_ALPHA,	//!<	RGBA blend factor = (1-A_destination, 1-A_destination, 1-A_destination, 1-A_destination)
	GZ_STATE_BLEND_SRC_ALPHA_SATURATE	=GZ_SRC_ALPHA_SATURATE		//!<	RGBA blend factor = (min(A_source, 1-A_destination), min(A_source, 1-A_destination), min(A_source, 1-A_destination), 1)
};

//! A defualt set of alpha functions
enum gzAlphaFuncFactor
{
	GZ_ALPHA_FUNC_NEVER		=GZ_NEVER,		//!<	The fragment is never accepted
	GZ_ALPHA_FUNC_ALWAYS	=GZ_ALWAYS,		//!<	The fragment is always accepted
	GZ_ALPHA_FUNC_LESS		=GZ_LESS,		//!<	True if fragment alpha < reference alpha
	GZ_ALPHA_FUNC_LEQUAL	=GZ_LEQUAL,		//!<	True if fragment alpha = reference alpha
	GZ_ALPHA_FUNC_EQUAL		=GZ_EQUAL,		//!<	True if fragment alpha = reference alpha
	GZ_ALPHA_FUNC_GEQUAL	=GZ_GEQUAL,		//!<	True if fragment alpha = reference alpha
	GZ_ALPHA_FUNC_GREATER	=GZ_GREATER,	//!<	True if fragment alpha > reference alpha 
	GZ_ALPHA_FUNC_NOTEQUAL	=GZ_NOTEQUAL	//!<	True if fragment alpha ? reference alpha
};

enum gzPolyOffsetMode
{ 
	GZ_POLYGON_OFFSET_FILL_MODE	=GZ_POLYGON_OFFSET_FILL,	//!<	Enables polygon offset for filled surfaces.
	GZ_POLYGON_OFFSET_LINE_MODE	=GZ_POLYGON_OFFSET_LINE,	//!<	Enables polygon offset for lines.
	GZ_POLYGON_OFFSET_POINT_MODE=GZ_POLYGON_OFFSET_POINT	//!<	Enables polygon offset for points.
};

//! Bitwize flags to enable various debugging features
enum gzStateDebugMode
{
	GZ_STATE_DEBUG_OFF				=	0,			//!<	Disable debug information
	GZ_STATE_DEBUG_SHOW_NORMALS		=	(1<<0),		//!<	Normals is visible
	GZ_STATE_DEBUG_SHOW_BSPHERE		=	(1<<1),		//!<	Bounding spheres is visible
	GZ_STATE_DEBUG_COLLECT_STATS	=	(1<<2),		//!<	Collect number of drawn primitives during the rendering.
	GZ_STATE_DEBUG_SHOW_NODE_INFO	=	(1<<3),		//!<	Node info is displayed as text.
};

GZ_USE_BIT_LOGIC(gzStateDebugMode);		// Allow | & operators for gzStateDebugMode

//******************************************************************************
// Function	: gzGraphicsStats
//									
// Purpose  : Creates a string with statistics about the GFX pieline
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021208	Created 
//									
//******************************************************************************
//!Creates a debug output string of the collected statistics in the context.
GZ_GRAPH_EXPORT gzString gzGraphicsStats(gzContext *context);


//******************************************************************************
// Class	: gzStateAttribute
//									
// Purpose  : Holds the current state attributes
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981111	Created 
//									
//******************************************************************************
//!Stores internal information for gzState.
class gzStateAttribute
{
public:

	// State attribute management
	//!Activates the state for the context.	
	GZ_GRAPH_EXPORT gzVoid activate(gzContext *context,gzBool activatePrograms);

	GZ_GRAPH_EXPORT gzVoid activatePrograms(gzContext *context);
	GZ_GRAPH_EXPORT gzVoid deactivatePrograms(gzContext *context);
	
	//!Default constructor.
	GZ_GRAPH_EXPORT gzStateAttribute();

	//!Destructor
	GZ_GRAPH_EXPORT virtual ~gzStateAttribute(){};

	//!Used by the traversal process to store current state attribute.
	GZ_GRAPH_EXPORT gzVoid pushCurrentStateAttribute(gzContext *context);

	// --------------- Current States ----------------------
	
	//!Returns the texture used by the current state.
	GZ_GRAPH_EXPORT static gzTexture *		getCurrentStateTexture(gzContext *context);
	
	//!Returns the material used by the current state.
	GZ_GRAPH_EXPORT static gzMaterial*		getCurrentStateMaterial(gzContext *context);
	
	//!Returns the graphics program of program type type used by the current state.
	/*!
	\param type specifies the program type of the graphics program (shader)
	*/
	GZ_GRAPH_EXPORT static gzGFXProgram *	getCurrentGFXProgram(gzContext *context,gzGFXProgramType type);

	//!Returns the transparency value used by the current state.
	GZ_GRAPH_EXPORT static gzFloat getCurrentStateTransparency(gzContext *context);

	//!Returns true if objects are drawn with a separate front and back rendering.
	GZ_GRAPH_EXPORT static gzBool getActiveSeparation(gzContext *context);

	// -------------- Control ------------------------------

	//!Used by the traversal process to reset the state attribute index.
	GZ_GRAPH_EXPORT static gzVoid resetIndex(gzContext *context,gzBool activateRender=TRUE);

	//!Used by the traversal process to get the state attribute index.
	GZ_GRAPH_EXPORT static gzUInt32 getCurrentStateAttributeIndex(gzContext *context);

	//!Used by the traversal process to activate the state attribute index.
	GZ_GRAPH_EXPORT static gzBool activateIndex(gzContext *context , gzUInt32 index);

	//!Sets cloning mode for the state attribute.
	/*!
	\sa gzNodeCopyMode.
	*/
	GZ_GRAPH_EXPORT virtual gzVoid	setCopyMode(const gzCopyMode &mode);

	// State attribute data

	//!Returns true if the mode is enabled otherwise false.
	GZ_GRAPH_EXPORT gzBool isEnabled(gzStateMode mode) { return (m_enable_mode & mode)!=0; }

	//!Returns the debug mode for the state.
	GZ_GRAPH_EXPORT gzStateDebugMode getDebugMode();

	//!Assignment operator
	GZ_GRAPH_EXPORT gzVoid operator=(const gzStateAttribute & right);

	//!Not equal operator.
	/*!
	Returns true if the two attributes not are equal. Otherwise true is returned.
	*/
	GZ_GRAPH_EXPORT gzBool operator!=(const gzStateAttribute & right) const;

	//!Equal operator.
	/*!
	Returns true if the two attributes are equal. Otherwise false is returned.
	*/
	GZ_GRAPH_EXPORT gzBool operator==(const gzStateAttribute & right) const;

	GZ_GRAPH_EXPORT gzVoid clear();

	//! Release all external references
	GZ_GRAPH_EXPORT virtual gzBool releaseRefs();

private:

	friend class gzState;
	friend class gzContext;

	// Attributes

	gzStateMode			m_enable_mode;
	gzStateMode			m_disable_mode;

	gzUInt16			m_lineStipple;
	gzInt32				m_stippleFactor;

	gzStateBlendFactor	m_blend_src;
	gzStateBlendFactor	m_blend_dst;

	gzPolygonModeType	m_polygon_front_mode;
	gzPolygonModeType	m_polygon_back_mode;

	// Texture enabled is embedded in texture class
	gzArray< gzRefPointer<gzTexture>	>	m_texture;

	// Material enabled is embedded in material class
	gzRefPointer<gzMaterial>				m_material;

	gzRefPointer<gzMaterial>				m_backmaterial;

	// TexEnv
	gzArray< gzRefPointer<gzTexEnv> >		m_texenv;

	// TexGen
	gzArray< gzRefPointer<gzTexGen> >		m_texgen;

	gzArray< gzRefPointer<gzGFXProgram> >	m_gfxPrograms;


	// Polygon Offset
	gzPolyOffsetMode	m_polygonOffsetMode;
	gzFloat				m_polygonOffsetFactor;
	gzFloat				m_polygonOffsetUnit;

	// ActionStage

	gzActionStage		m_actionStage;

	// Debug info
	gzStateDebugMode	m_debugMode;

	// Transparency
	gzFloat				m_transparency;

	// Alpha func
	gzAlphaFuncFactor	m_alphaFunc;
	gzFloat				m_alphaRef;

	// Generic
	gzUInt32			m_currentStateUpdateID;
	gzBool				m_accumulateTransparency;
	gzBool				m_separateBackAndFrontRender;
	gzBool				m_useTransp;
};

//******************************************************************************
// Class	: gzState
//									
// Purpose  : Provides the user interface for state management
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981111	Created 
//									
//******************************************************************************
//!Contains the state attributes for a gzNode.
class gzState : public gzObject 
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface
	
	//!Default constructor.
	GZ_GRAPH_EXPORT gzState();

	GZ_GRAPH_EXPORT gzState(const gzState &copy);
	GZ_GRAPH_EXPORT gzState & operator=(const gzState &copy);

	
	//! Destructor
	GZ_GRAPH_EXPORT virtual ~gzState();

	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	//!Overrides the gzReference useDeepCopyMode() to use gzNodeCopyMode.
	/*!
	Depending on what copy mode you have set a clone of a gzNode will either 
	return a new instance of a gzState or a shared instance.
	*/
	GZ_GRAPH_EXPORT virtual gzBool useDeepCopy() override;
	
	//!Sets cloning mode for the state.
	/*!
	\sa gzNodeCopyMode.
	*/
	GZ_GRAPH_EXPORT virtual gzVoid	setCopyMode(const gzCopyMode &mode) override;

	//! Release all external references
	GZ_GRAPH_EXPORT virtual gzBool releaseRefs() override;

	// ---------- Activation of states ----------------------------------

	//!Activates the gzState instance during the rendering process.
	/*!
	If you derive your own gzNode class you can use this method
	to activate a gzState in a pre or post traversal.
	*/
	GZ_GRAPH_EXPORT gzVoid activate(gzContext *context);		// Immediate mode
	GZ_GRAPH_EXPORT gzVoid deactivate(gzContext *context);		// Immediate mode
	GZ_GRAPH_EXPORT gzVoid activatePrograms(gzContext *context);// Immediate mode
	GZ_GRAPH_EXPORT static gzVoid deactivatePrograms(gzContext *context);// Immediate mode

	GZ_GRAPH_EXPORT gzStateAttribute &getCurrentStateAttribute(gzContext *context);

	// ---------- Global state control ( scene graph mode ) -------------

	//!Sets a global state for the context.
	/*!
	The state is applied as global state to the context.

	This state is used as a default state for the rendering. 
	*/
	GZ_GRAPH_EXPORT static gzVoid setGlobalState(  gzContext *context, gzState *state );
	
	//The state is applied as current state to the context.
	//!Used internally by the rendering process. Don't use this method.
	GZ_GRAPH_EXPORT static gzVoid setCurrentState( gzContext *context, gzState *state );
	
	//Returns the current state for the context.
	/*!
	If you have derived your own gzNode you can use this method to get the current state
	in pre and post traversal.
	*/
	GZ_GRAPH_EXPORT static gzState *getCurrentState(gzContext *context);

	//!Call this method in post and pre traversal to activate the current state if you have activated your own state previously. 
	GZ_GRAPH_EXPORT static gzVoid activateCurrentState(gzContext *context);
	
	//!Call this method to tell the rendering process that you have changed the state.
	/*!
	If you have used activate() you need to call this method when you leave pre or post traversal.
	*/
	GZ_GRAPH_EXPORT static gzVoid invalidateActiveState(gzContext *context);

	//!Call this method to tell the rendering process that you have changed some of the GFXProgram parameters in a pre traverse.
	GZ_GRAPH_EXPORT static gzVoid refreshActiveGFXProgram(gzContext *context);


	//!Used by the rendering process to reset state index.
	GZ_GRAPH_EXPORT static gzVoid resetIndex(gzContext *context);

	//!Used by the rendering process to store current state.
	GZ_GRAPH_EXPORT static gzVoid push(gzContext *context);

	//!Used by the rendering process to restore current state.
	GZ_GRAPH_EXPORT static gzVoid pop(gzContext *context);

	//!Returns current action stage for the rendering process.
	GZ_GRAPH_EXPORT static gzActionStage useActionStage(gzContext *context);

	//!Sets a state mode.
	/*!
	Activates or deactivates modes for the state. It is possible to have several state modes 
	enabled at the same time. An active mode affects the way the gzNode is rendered as the 
	state attributes affects the rendering.
	*/
	GZ_GRAPH_EXPORT gzVoid setMode( gzStateMode mode , gzStateModeActivation activation );
	
	//!Sets properties for the state that override other properties.
	/*!
	With setOverride you turn off the possibility for sibling children to 
	change state parameters with setMode functions.

	This makes it easy to enable or disable wireframe, textures or materials even if 
	the sibling childrens have set their own states.

	E.g. if you have textures activated and want to disable the texture you use 
	setOverride(GZ_STATE_TEXTURE, GZ_STATE_OFF). To enable the textures again you 
	use setOverride(GZ_STATE_TEXTURE, GZ_STATE_ON)
	*/
	GZ_GRAPH_EXPORT gzVoid setOverride( gzStateMode mode , gzStateModeActivation activation );
	
	//!Returns the current activation for the mode.
	GZ_GRAPH_EXPORT gzStateModeActivation getMode(gzStateMode mode);

	//!Returns the current locked activation for the mode.
	GZ_GRAPH_EXPORT gzStateModeActivation getOverrideMode(gzStateMode mode);

	//!Use this to disable all non enabled modes in the state.
	GZ_GRAPH_EXPORT gzVoid disableAllNonEnabledModes();

	// Attributes

	//!Sets the stippling pattern for lines.
	/*!
	The stipple argument describes the pattern for the line on a pixel-by-pixel basis. 
	A 1 indicates that drawing occurs and a 0 that it does not. 

	E.g 0xF3CC results in the pattern 
	1111001111001100 with line pattern 
	"----  ----  --  "

	Note that line stippling must be activated in the state if this function should give a noticeable result.
	*/
	GZ_GRAPH_EXPORT gzVoid setLineStipple( gzUInt16 stipple );
	
	//!Sets the stretch factor for the stipple lines.
	/*!
	The line pattern is stretched using the factor.

	The factor is clamped to a value between 1 and 256.	Default value is 1.

	If a stretch factor is applied to the pattern "----  ----  --  " 
	the following result occurs.

	Factor = 1: "----  ----  --  "

	Factor = 2: "--------    --------    ----    "

	Factor = 3: "------------      ------------      ------      "  etc.

	Note that line stippling must be activated in the state if this function should give a noticeable result.
	*/
	GZ_GRAPH_EXPORT gzVoid setStippleFactor( gzInt32 factor );

	//!Sets the blending function for the state.
	/*!
	When blending is used, the color values of the incoming fragment (source) are combined with the 
	color values of the currently stored pixel value (destination). 

	You need to define how to compute the source and destination factors. These factors are multiplied
	with each component in the RGBA-color in the source and destination respectively. 

	Finally the two components are combined. The source blending factors are SR, SG, SB, SA and
	the destination blending factors are DR, DG, DB and DA. The RGBA values of the source are 
	R_source, G_source, B_source, and A_source.
	The RGBA values for the destination are R_destination, G_destination, B_destination and A_destination. 
	The blending formula is the following:

	(R_source*SR + R_destination*DR, G_source*SG + G_destination*DG, B_source*SB + B_destination*DB, A_source*SA + A_destination*DA)
	*/
	GZ_GRAPH_EXPORT gzVoid setBlendFunction( gzStateBlendFactor src  , gzStateBlendFactor dst );
	GZ_GRAPH_EXPORT gzVoid getBlendFunction( gzStateBlendFactor &src  , gzStateBlendFactor &dst );

	GZ_GRAPH_EXPORT gzVoid setSeparateFrontAndBackRender(gzBool on);
	GZ_GRAPH_EXPORT gzBool getSeparateFrontAndBackRender() const;

	//!Sets the polygon mode type for the front of each polygon. 
	/*
	The default mode is GZ_POLYGON_FILL.
	*/
	GZ_GRAPH_EXPORT gzVoid setFrontPolygonMode( gzPolygonModeType mode );
	GZ_GRAPH_EXPORT gzPolygonModeType getFrontPolygonMode();
	
	//!Sets the polygon mode type for the back of each polygon. 
	/*
	The default mode is GZ_POLYGON_MODE_FILL.
	*/
	GZ_GRAPH_EXPORT gzVoid setBackPolygonMode( gzPolygonModeType mode );
	GZ_GRAPH_EXPORT gzPolygonModeType getBackPolygonMode();

	//!Sets the texture for the state. 
	/*!
	If several textures are used, a unit need to be specified for each texture. 
	The number of textures used is specified with setNumberOfTextures(gzUInt32 units).

	The GZ_STATE_TEXTURE mode has to be enabled if the 
	texture shall be visible.
	*/
	GZ_GRAPH_EXPORT gzVoid		setTexture( gzTexture *texture , gzUInt32 unit=0);

	//! Adds a texture to the next free texture Unit or shared slot. Returns texture unit id;
	GZ_GRAPH_EXPORT gzUInt32	addTexture(gzTexture* texture);
	
	//!Returns the texture used by the state. 
	/*!
	It is possible to get a texture with a specified unit.
	*/
	GZ_GRAPH_EXPORT gzTexture *	getTexture(gzUInt32 unit=0);
	
	//!Sets the number of textures used by the state.
	GZ_GRAPH_EXPORT gzVoid		setNumberOfTextures(gzUInt32 units);
	
	//!Returns the number of textures used by the state.
	GZ_GRAPH_EXPORT gzUInt32	getNumberOfTextures();

	//!Sets the material used by the state. 
	/*!
	The GZ_STATE_MATERIAL mode has to be enabled if the 
	material shall be visible.
	*/
	GZ_GRAPH_EXPORT gzVoid		setMaterial( gzMaterial *material );
	
	//!Returns the material used by the state.
	GZ_GRAPH_EXPORT gzMaterial	*getMaterial();

	//!Sets the material used on back faces.
	/*!
	The GZ_STATE_MATERIAL mode has to be enabled if the material shall be visible.
	*/
	GZ_GRAPH_EXPORT gzVoid		setBackMaterial( gzMaterial *material );

	//!Returns the back face material.
	GZ_GRAPH_EXPORT gzMaterial	*getBackMaterial();

	//!Sets the texture environment used by the state. 
	/*!
	If several texture environments are used a unit number has to be specified for each gzTexEnv.
	Use setNumberOfTexEnv(gzUInt32 units) to specify the number of gzTexEnv.

	GZ_STATE_TEXENV need to be enabled.
	*/
	GZ_GRAPH_EXPORT gzVoid		setTexEnv( gzTexEnv *env , gzUInt32 unit=0);
	
	//!Returns the texture environment used by the state.
	GZ_GRAPH_EXPORT gzTexEnv *	getTexEnv(gzUInt32 unit=0);
	
	//!Sets the number of texture environments that are used.
	/*!
	If more than one texture environment is used this has to be specified with units.
	*/
	GZ_GRAPH_EXPORT gzVoid		setNumberOfTexEnv(gzUInt32 units);
	
	//!Returns the number of texture environments which are used by the state.
	GZ_GRAPH_EXPORT gzUInt32	getNumberOfTexEnv();


	//!Sets the texture coordinate generator used by the state. 
	/*!
	If several texture coordinate generators are used a unit number has to be specified for each gzTexGen.
	Use setNumberOfTexGen(gzUInt32 units) to specify the number of gzTexGen.

	GZ_STATE_TEXGEN need to be enabled.
	*/
	GZ_GRAPH_EXPORT gzVoid		setTexGen( gzTexGen *gen , gzUInt32 unit=0);

	//!Returns the texture coordinate generator used by the state.
	GZ_GRAPH_EXPORT gzTexGen *	getTexGen(gzUInt32 unit=0);

	//!Sets the number of texture coordinate generators that are used.
	/*!
	If more than one texture coordinate generator is used this has to be specified with units.
	*/
	GZ_GRAPH_EXPORT gzVoid		setNumberOfTexGen(gzUInt32 units);

	//!Returns the number of texture coordinate generators which are used by the state.
	GZ_GRAPH_EXPORT gzUInt32	getNumberOfTexGen();

	//!Sets the transparency value for the state.
	/*!
		\param transparency is a value from 0 to 1. 0 is invisible and 1 is opaque.
		\param accumTransparency is TRUE if transparency shall be accumulated. Otherwise it is replaced.
	*/
	GZ_GRAPH_EXPORT gzVoid		setTransparency( gzClampf transparency , gzBool accumTransparency=TRUE);
	
	//!Returns the transparency value for the state.
	GZ_GRAPH_EXPORT gzClampf	getTransparency( gzBool *accumTransparency=nullptr);

	/*!
	Sets the mode for the polygon offset. 

	Polygon offset is useful when you want to draw a filled model with one color using GZ_POLYGON_MODE_FILL
	and draw the edges with another color using GZ_POLYGON_MODE_LINE. Since lines and filled polygons not 
	are rasterized in the same way the lines may fade in and out of the filled polygon. This depends on the 
	variation in alpha values for the line and filled polygon. By using polygon offset this behaviour can 
	be eliminated. 

	The polygon offset adds an offset which force coincident z-values apart which separates a polygon edge 
	from its highlighting line. 

	An offset value, o, is calculated by using the factor and units which must be specified for the offset.
	This value is added to the depth value for each fragment. After this value has been added the depth 
	test is performed.

	The default mode is GZ_POLYGON_OFFSET_FILL_MODE.
	The default offset factor and unit is 0.
	*/
	GZ_GRAPH_EXPORT gzVoid setPolygonOffset(gzPolyOffsetMode mode , gzFloat factor , gzFloat unit);

	GZ_GRAPH_EXPORT gzPolyOffsetMode	getPolygonOffsetMode();
	GZ_GRAPH_EXPORT gzFloat				getPolygonOffsetFactor();
	GZ_GRAPH_EXPORT gzFloat				getPolygonOffsetUnit();

	//! Set the required gzActionStage. 
	/*
		Must be enabled with GZ_STATE_ACTION_STAGE
	*/
	GZ_GRAPH_EXPORT gzVoid setActionStage(gzActionStage stage );

	//! Get gzActionStage
	GZ_GRAPH_EXPORT gzActionStage getActionStage();

	//! Set the required debug mode.
	/*!
	Makes it possible to show debug information like normals or bounding spheres. It is also possible to tell 
	the scene graph to count what is draws like number of triangles, lines, points etc. 

	Default debug mode is GZ_STATE_DEBUG_OFF.
	*/
	GZ_GRAPH_EXPORT gzVoid setDebugMode(gzStateDebugMode mode );

	//!Sets an alpha function and reference value.
	/*!
	When using RGBA images it is possible to draw or cull a fragment depending on its alpha value. 
	The incoming alpha value is compared with the refValue. The refValue is claped to a value between 0 and 1.

	The comparison function is set with func. If the comparison of the function is true the fragment is drawn, 
	otherwise it is culled.
	*/
	GZ_GRAPH_EXPORT gzVoid setAlphaFunc(gzAlphaFuncFactor func , gzClampf refValue);
	GZ_GRAPH_EXPORT gzVoid getAlphaFunc(gzAlphaFuncFactor &func , gzClampf &refValue);


	// Utility functions

	//! Calulates the best alpha and stage settings for a given texture image.
	GZ_GRAPH_EXPORT gzVoid setBestAlphaTextureSettings(gzImage *image,gzSerializeAdapterFlags flags);

	// GFX Programs

	//!Sets a graphics program (shader) of a specific type. 
	/*
	The GZ_STATE_GFX_PROGRAM mode has to be enabled if you want to use shaders.
	*/
	GZ_GRAPH_EXPORT gzVoid setGFXProgram(gzGFXProgramType type,gzGFXProgram *program);
	GZ_GRAPH_EXPORT gzGFXProgram * getGFXProgram(gzGFXProgramType type);

	// ----------- Static utlities for the context ------------------

	//!Sets the generic depth function for a given context.
	/*!
	Default is GZ_LEQUAL.
	*/
	GZ_GRAPH_EXPORT static gzVoid setCurrentDepthFunc( gzContext *context , gzEnum func);

	//!Returns the generic depth function for a given context.
	GZ_GRAPH_EXPORT static gzEnum getCurrentDepthFunc(gzContext *context);


	//!Enables or disables depth function for a given context.
	GZ_GRAPH_EXPORT static gzVoid setUseDepthBuffer( gzContext *context , gzBool on);

	//!Returns the state for the depth function for a given context.
	GZ_GRAPH_EXPORT static gzBool getUseDepthBuffer(gzContext *context);

	// ---------- Debug function ----------------------------------------
	//!Prints debug information about the class.
	/*!
	Prints to the console by default. Uses gzMessage mechanism.
	*/
	GZ_GRAPH_EXPORT virtual gzVoid debugOutput(gzString base , gzString anchor , gzDebugFlags features);

	// ---------- State identities ---------------------------------------

	GZ_GRAPH_EXPORT	gzBool	registerStateID(gzUInt32 id,gzBool forceUpdate=FALSE);
	GZ_GRAPH_EXPORT gzBool	unregisterStateID();
	GZ_GRAPH_EXPORT gzBool	getStateID(gzUInt32 &id);
	GZ_GRAPH_EXPORT gzBool	hasStateID();

	static GZ_GRAPH_EXPORT	gzState *findState(gzUInt32 id);
	static GZ_GRAPH_EXPORT	gzBool isRegisteredState(gzState *state);
	static GZ_GRAPH_EXPORT	gzUInt32 getMaxUsedStateID();
	static GZ_GRAPH_EXPORT	gzVoid preAllocateStateID(gzUInt32 id);
	static GZ_GRAPH_EXPORT	gzVoid clearAllStateID(gzBool force=FALSE);

	// ---------- Serializing -------------------------------------------
	//!Writes the gzState data to the adapter.
	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;

	//!Reads the gzState data from the adapter.
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;

	//!Returns the size of the gzState data.
	/*!
	The size is given in bytes.
	*/
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	//!Equal operator.
	/*!
	Returns true if the two attributes are equal. Otherwise false is returned.
	*/
	GZ_GRAPH_EXPORT gzBool operator==(const gzState & right);
	
	//!Not equal operator.
	/*!
	Returns true if the two attributes not are equal. Otherwise false is returned.
	*/
	GZ_GRAPH_EXPORT gzBool operator!=(const gzState & right);


private:

	friend class gzContext;

	static gzVoid	activateCurrentNow(gzContext *context);
	static gzVoid	activateCurrentProgramsNow(gzContext *context);
	static gzVoid	deactivateCurrentProgramsNow(gzContext *context);

	gzVoid			updateFromState( gzContext *context,gzState *state);
	gzBool			getStateID_unsafe(gzUInt32 &id);

	gzStateAttribute					m_originalState;
	gzStateMode							m_original_lock_mode;

	gzDynamicArray<gzStateAttribute>	m_currentState;
	gzDynamicArray<gzStateMode>			m_current_lock_mode;
	
	gzUInt32							m_stateID;
	gzBool								m_active;

	// Static vars

	static gzMutex										stateIDLocker;
	static gzDict<gzUInt32CompareInterface,gzState>		stateIDStorage;
	static gzDict<gzInstanceCompareInterface,gzVoid>	IDStateStorage;
};

GZ_DECLARE_REFPTR(gzState);

// ------------------------------ gzVertexArrayState ------------------------------------

class gzGeometry; // Forward declaration

class gzVertexArrayState
{
public:
	
	static GZ_GRAPH_EXPORT gzVoid deactivateAll(gzContext *context);
	
	static GZ_GRAPH_EXPORT gzVoid enableEdgeFlag(gzContext *context);
	static GZ_GRAPH_EXPORT gzVoid disableEdgeFlag(gzContext *context);
	
	static GZ_GRAPH_EXPORT gzVoid enableTexCoord(gzContext *context,gzUInt32 index);
	static GZ_GRAPH_EXPORT gzVoid disableTexCoord(gzContext *context,gzUInt32 index);
	static GZ_GRAPH_EXPORT gzVoid disableRemainingTexCoord(gzContext *context,gzUInt32 index);

	static GZ_GRAPH_EXPORT gzVoid enableColor(gzContext *context);
	static GZ_GRAPH_EXPORT gzVoid disableColor(gzContext *context);
	
	static GZ_GRAPH_EXPORT gzVoid enableNormal(gzContext *context);
	static GZ_GRAPH_EXPORT gzVoid disableNormal(gzContext *context);

	static GZ_GRAPH_EXPORT gzVoid enableIndex(gzContext *context);
	static GZ_GRAPH_EXPORT gzVoid disableIndex(gzContext *context);
	
	static GZ_GRAPH_EXPORT gzVoid enableVertex(gzContext *context);
	static GZ_GRAPH_EXPORT gzVoid disableVertex(gzContext *context);

};

#endif
