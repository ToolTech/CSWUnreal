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
// File			: gzEnvironment.h
// Module		: 
// Description	: Class definition of the gzEnvironment classes
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.306
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
// AMO	990312	Created file 	
//
//******************************************************************************
#ifndef __GZ_ENVIRONMENT_H__
#define __GZ_ENVIRONMENT_H__

/*!	\file 
	\brief Base definitions for environments with lights etc.

	Definition of all environment effects shall be activated through the gzEnvironment. All
	other state mechanisms that affect geometry rendering shall be activated through the gzState.
*/


#include "gzGroup.h"
#include "gzLight.h"
#include "gzClipPlane.h"

enum gzFogMode
{
	GZ_FOG_MODE_EXP		=GZ_EXP,
	GZ_FOG_MODE_EXP2	=GZ_EXP2,
	GZ_FOG_MODE_LINEAR	=GZ_LINEAR
};

//******************************************************************************
// Class	: gzFogInfo
//									
// Purpose  : Hold information about the fog.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990312	Created 
//									
//******************************************************************************
class gzFogInfo
{
public:
	//!Constructor.
	GZ_GRAPH_EXPORT	gzFogInfo();

private:

	gzVoid activate(gzContext *context);

	static gzVoid deactivate(gzContext *context);

	friend class gzEnvironment;

	gzBool		enabled;
	gzFogMode	mode;
	gzRGBA		color;
	gzFloat		density;
	gzFloat		start;
	gzFloat		end;
};

//******************************************************************************
// Class	: gzEnvironment
//									
// Purpose  : An environment that hold lights, clipplanes etc.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990312	Created 
//									
//******************************************************************************
//!The gzEnvironment class is used when you want to add environmental effects to a scene.
/*! It is possible to add light or create fog to get a more realistic environment. 
*/
class gzEnvironment : public gzGroup	
{
public:
	//!Constructor.
	/*!
	\param name specifies a name for the gzEnvironment.
	*/
	GZ_GRAPH_EXPORT gzEnvironment(const gzString & name=GZ_EMPTY_STRING):gzGroup(name){};

	//!Destructor.
	GZ_GRAPH_EXPORT virtual ~gzEnvironment(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	//!Clone interface.
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Action Interface --------------------------------------
	//!Called in the traversal process.
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	//!Called in the traversal process.
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Light Management interface ----------------------------

	GZ_GRAPH_EXPORT static gzVoid resetLightStateIndex(gzContext *context );
	GZ_GRAPH_EXPORT static gzVoid invalidateActiveLightState(gzContext *context );
	GZ_GRAPH_EXPORT static gzVoid activateLightStateIndex(gzContext *context ,gzUInt32 index);
	GZ_GRAPH_EXPORT static gzVoid setMainLightState(gzContext *context);

	//!Adds a light to the environment.
	/*!
	It is possible to add several light sources to the same environment. 
	These light sources will light all nodes which are below the environment node in the scene graph. 
	\param light specifies the light that shall be added to the environment. \n
	*/
	GZ_GRAPH_EXPORT gzVoid	addLight( gzLight *light);
	
	//!Removes the light from the scene graph.
	/*!
	\param light is the light that shall be removed from the environment.
	*/
	GZ_GRAPH_EXPORT gzVoid	removeLight( gzLight *light);
	
	//!Returns the number of lights connected to the scene.
	GZ_GRAPH_EXPORT gzUInt32	getNumberOfLights();

	//!Returns a light.
	/*!
	\param lightIndex specifies the index of the light that shall be returned.
	*/
	GZ_GRAPH_EXPORT gzLight *getLight(gzUInt32 lightIndex);


	// ---------- Clip Management interface ----------------------------

	GZ_GRAPH_EXPORT static gzVoid resetClipStateIndex(gzContext *context );
	GZ_GRAPH_EXPORT static gzVoid activateClipStateIndex(gzContext *context , gzUInt32 index);

	//!Adds a clip plane to the environment. 
	/*!
	\param clip is the clip plane that shall be added to the environment.
	*/
	GZ_GRAPH_EXPORT gzVoid addClipPlane(gzClip *clip);

	//!Removes the clip plane from the environment.
	/*!
	\param clip is the clip plane that shall be removed from the environment.
	*/
	GZ_GRAPH_EXPORT gzVoid removeClipPlane(gzClip *clip);

	//!Returns the number of clip planes added to the environment.
	GZ_GRAPH_EXPORT gzUInt32	getNumberOfClipPlanes();

	//!Returns a clip plane.
	/*!
	\param clipIndex is the index for the clip plane that shall be returned.
	*/
	GZ_GRAPH_EXPORT gzClip *getClipPlane(gzUInt32 clipIndex);

	// ---------- Fog interface ----------------------------------------

	GZ_GRAPH_EXPORT static gzVoid resetFogStateIndex(gzContext *context);
	GZ_GRAPH_EXPORT static gzVoid activateFogStateIndex(gzContext *context , gzUInt32 index);

	//!Specifies if fog are used.
	/*! 
	\param enable is true if fog shall be used and false if no fog shall be used.

	Initially fog is disabled
	*/
	GZ_GRAPH_EXPORT gzVoid useFog( gzBool enable );

	//!Sets the fog mode.
	/*!
	\param mode specifies the fog mode that shall be used.

	\sa gzFogMode
	*/
	GZ_GRAPH_EXPORT gzVoid setFogMode( gzFogMode mode );

	//!Sets the color for the fog.
	GZ_GRAPH_EXPORT gzVoid setFogColor( const gzRGBA &color );

	//!Sets the density for the fog.
	GZ_GRAPH_EXPORT gzVoid setFogDensity( gzFloat density );

	//!Sets the start for the fog.
	GZ_GRAPH_EXPORT gzVoid setFogStart( gzFloat start );

	//!Sets the end for the fog.
	GZ_GRAPH_EXPORT gzVoid setFogEnd( gzFloat end );


	// ---------- generic environment, immediate activation ------------

	//!Applies the context lighting model on the environment.
	GZ_GRAPH_EXPORT static gzVoid setLightModel(gzContext *context);
	
	//!Activates/ deactivates two side lighting.
	GZ_GRAPH_EXPORT static gzVoid setTwoSideLighting(gzContext *context , gzBool on);
	GZ_GRAPH_EXPORT static gzVoid setLocalViewer(gzContext *context,gzBool on);

	//!Sets the ambient color for the global environment.
	GZ_GRAPH_EXPORT static gzVoid setGlobalAmbientColor(gzContext *context , gzFloat red=0.1f , gzFloat green=0.1f, gzFloat blue=0.1f , gzFloat alpha=1.0f );

private:

	gzLightState		m_lightState;

	gzClipState			m_clipState;

	gzFogInfo			m_fogInfo;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzEnvironment);

#endif

