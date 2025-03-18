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
// File			: gzLight.h
// Module		: 
// Description	: Class definition of the gzLight classes
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.231
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
#ifndef __GZ_LIGHT_H__
#define __GZ_LIGHT_H__

/*!	\file 
	\brief Base definitions for lights etc.

*/

class gzContext;	// Forward declaration

//******************************************************************************
// Class	: gzLightPosition
//									
// Purpose  : Position of a light source
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991025	Created 
//									
//******************************************************************************
class gzLightPosition
{
public:
	GZ_GRAPH_EXPORT gzLightPosition(gzFloat xp=10.0f , gzFloat yp=10.0f, gzFloat zp=0.0f , gzFloat w_local=1.0f ):x(xp),y(yp),z(zp),w(w_local){};

	GZ_GRAPH_EXPORT virtual ~gzLightPosition(){};

	GZ_GRAPH_EXPORT gzFloat *getPositionVector(){ return &x; }

	GZ_GRAPH_EXPORT gzVec4 getPosition();

	GZ_GRAPH_EXPORT gzBool operator==(const gzLightPosition& right);

	GZ_GRAPH_EXPORT gzBool operator!=(const gzLightPosition& right);

	gzFloat	x,y,z,w;
};

//******************************************************************************
// Class	: gzLightDirection
//									
// Purpose  : Beam direction of a light source
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991025	Created 
//									
//******************************************************************************
//!The class holds information about the light direction.
class gzLightDirection

{
public:
	GZ_GRAPH_EXPORT gzLightDirection(gzFloat dx=10.0f , gzFloat dy=10.0f, gzFloat dz=0.0f ):x(dx),y(dy),z(dz){};

	GZ_GRAPH_EXPORT virtual ~gzLightDirection(){};

	GZ_GRAPH_EXPORT gzFloat *getDirectionVector(){ return &x; }

	GZ_GRAPH_EXPORT gzVec3 getDirection();

	gzFloat	x,y,z;
};

//******************************************************************************
// Class	: gzLight
//									
// Purpose  : The actual definition of a light source
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
//!The class defines a light source.
class gzLight : public gzObject , public gzNameInterface , public gzUpdateIDInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzLight(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzLight(){};

	GZ_GRAPH_EXPORT gzVoid virtual activate(gzContext *context , gzUInt32 lightIndex , gzUInt32 transformIndex);

	GZ_GRAPH_EXPORT static gzVoid deactivate(gzContext *context , gzUInt32 lightIndex);


	//!Sets the ambient color for light.
	/*!
	Default ambient color is black.
	*/
	GZ_GRAPH_EXPORT gzVoid setAmbientColor(gzFloat red=0.0f , gzFloat green=0.0f, gzFloat blue=0.0f , gzFloat alpha=1.0f );

	//!Sets the diffuse color for light.
	/*!
	Default diffuse color is white.
	*/
	GZ_GRAPH_EXPORT gzVoid setDiffuseColor(gzFloat red=1.0f , gzFloat green=1.0f, gzFloat blue=1.0f , gzFloat alpha=1.0f );

	//!Sets the specular color for light.
	/*!
	Default specular color is white. 
	*/
	GZ_GRAPH_EXPORT gzVoid setSpecularColor(gzFloat red=1.0f , gzFloat green=1.0f, gzFloat blue=1.0f , gzFloat alpha=1.0f );


	//!Sets position for the light.
	GZ_GRAPH_EXPORT gzVoid setPosition(gzFloat x=0.0f , gzFloat y=0.0f, gzFloat z=1.0f , gzFloat w=1.0f );
	GZ_GRAPH_EXPORT gzVoid setSpot(gzFloat dx=0.0f , gzFloat dy=0.0f, gzFloat dz=-1.0f , gzFloat exponent=0.0f , gzFloat cutoff=45.0f);
	GZ_GRAPH_EXPORT gzVoid setAttenuation( gzFloat constant=1.0f , gzFloat linear=0.0f , gzFloat quadratic=0.0f );
	GZ_GRAPH_EXPORT gzVoid setDirectionalLight(gzFloat dx=0.0f , gzFloat dy=0.0f, gzFloat dz=-1.0f);

	// Vector variants..

	//!Sets position for the light.
	/*!
	\param position is a gzVec3 which contains a x, y and z position for the light given in world coordinates.
	*/
	GZ_GRAPH_EXPORT gzVoid setPosition(const gzVec3 & position);
	GZ_GRAPH_EXPORT gzVoid setDirectionalLight(const gzVec3 & direction);


	// Get utilities

	//!Returns the light position.
	GZ_GRAPH_EXPORT gzLightPosition &getPosition();

	//!Returns the color for the ambient part of the light.
	GZ_GRAPH_EXPORT gzRGBA	&getAmbientColor();

	//!Returns the color for the specular part of the light.
	GZ_GRAPH_EXPORT gzRGBA	&getSpecularColor();

	//!Returns the color for the diffuse part of the light.
	GZ_GRAPH_EXPORT gzRGBA	&getDiffuseColor();

	//!Turns the light on or off.
	/*!
	\param on is TRUE if the light shall be enabled, otherwise false. 

	By default the light is activated.
	*/
	GZ_GRAPH_EXPORT gzVoid	enableLight(gzBool on=TRUE);
	
	//!Returns TRUE if the light is on, otherwise false.
	GZ_GRAPH_EXPORT gzBool	isEnabled();

	GZ_GRAPH_EXPORT gzVoid invertShadowLight(gzBool on);

	GZ_GRAPH_EXPORT gzVoid excludeDiffuseInShadow(gzBool on);

	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

private:

	gzLightPosition m_lightpos;

	gzRGBA	m_ambient;
	gzRGBA	m_diffuse;
	gzRGBA	m_specular;

	gzLightDirection	m_spot_direction;
	gzFloat				m_spot_exponent;
	gzFloat				m_spot_cutoff;
	gzFloat				m_constant_attenuation;
	gzFloat				m_linear_attenuation;
	gzFloat				m_quadratic_attenuation;

	gzBool				m_enabled:1;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzLight);

const gzUInt32 GZ_NUMBER_OF_ACTIVE_LIGHTS=8;

//******************************************************************************
// Class	: gzLightState
//									
// Purpose  : The actual state of the current lights
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
class gzLightState
{
public:

	GZ_GRAPH_EXPORT gzLightState():m_count(0){};
	GZ_GRAPH_EXPORT virtual ~gzLightState(){};

	GZ_GRAPH_EXPORT gzVoid	add(gzLightState &lightState);

	GZ_GRAPH_EXPORT gzVoid addLight( gzLight *light);
	GZ_GRAPH_EXPORT gzVoid removeLight( gzLight *light);
	GZ_GRAPH_EXPORT gzUInt32	getNumberOfLights();
	GZ_GRAPH_EXPORT gzLight *getLight(gzUInt32 lightIndex);
	GZ_GRAPH_EXPORT gzUInt32 getTransformIndex(gzLight *light);

	GZ_GRAPH_EXPORT gzVoid setAllTransformIndex(gzUInt32 index);

	GZ_GRAPH_EXPORT gzVoid activate(gzContext *context);

	GZ_GRAPH_EXPORT static gzVoid transferActiveLightStates(gzContext *from , gzContext *to);

private:

	gzRefPointer<gzLight>	m_lights[GZ_NUMBER_OF_ACTIVE_LIGHTS];
	gzUInt32					m_transformIndex[GZ_NUMBER_OF_ACTIVE_LIGHTS];
	gzMutex					m_locker;
	gzUByte					m_count;

};


#endif

