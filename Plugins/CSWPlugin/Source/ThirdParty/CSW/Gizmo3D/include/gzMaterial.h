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
// File			: gzMaterial.h
// Module		: 
// Description	: Class definition of the gzMaterial class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.222
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
// AMO	990415	Created file 	
//
//******************************************************************************
#ifndef __GZ_MATERIAL_H__
#define __GZ_MATERIAL_H__

/*!	\file 
	\brief Base definitions for object materials

*/


#include "gzObject.h"
#include "gzMatrix.h"
#include "gzImage.h"

class gzContext;

enum gzColorMaterialMode
{
	GZ_COLOR_MODE_EMISSION				=	GZ_EMISSION,
	GZ_COLOR_MODE_AMBIENT				=	GZ_AMBIENT,
	GZ_COLOR_MODE_DIFFUSE				=	GZ_DIFFUSE,
	GZ_COLOR_MODE_SPECULAR				=	GZ_SPECULAR,
	GZ_COLOR_MODE_AMBIENT_AND_DIFFUSE	=	GZ_AMBIENT_AND_DIFFUSE,
};

//******************************************************************************
// Class	: gzMaterial
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990415	Created 
//									
//******************************************************************************
class gzMaterial : public gzObject , public gzNameInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	//!Constructor
	/*!
	It is possible to set a name for the material.
	*/
	GZ_GRAPH_EXPORT gzMaterial(const gzString & name=GZ_EMPTY_STRING);

	//!Destructor
	GZ_GRAPH_EXPORT virtual ~gzMaterial(){};

	GZ_GRAPH_EXPORT gzVoid	virtual activate(gzContext *context , gzEnum face);
	GZ_GRAPH_EXPORT static gzVoid deactivate(gzContext *context);

	GZ_GRAPH_EXPORT gzVoid useColorAsMaterial(gzBool on , gzColorMaterialMode mode=GZ_COLOR_MODE_AMBIENT_AND_DIFFUSE);

	//!Sets the ambient property for the material.
	/*!
	The ambient material defines how the ambient light is reflected. \n
	The red ambient material color tells how the red ambient light for the color is reflected.
	The green ambient material color tells how the green ambient light for the color is reflected, etc.
	This combination gives the resulting color for the reflected ambient light.
	*/
	GZ_GRAPH_EXPORT gzVoid setAmbient(const gzRGBA &matcol );

	//!Sets the diffuse property for the material.
	/*!
	The diffuse material defines how the diffuse light is reflected. \n
	The red diffuse material color tells how the red diffuse light for the color is reflected.
	The green diffuse material color tells how the green diffuse light for the color is reflected, etc.
	This combination gives the resulting color for the reflected diffuse light.
	*/
	GZ_GRAPH_EXPORT gzVoid setDiffuse(const gzRGBA &matcol );

	//!Sets the specular property for the material.
	/*!
	The specular material defines how the specular light is reflected. \n
	The red specular material color tells how the red specular light for the color is reflected.
	The green specular material color tells how the green specular light for the color is reflected, etc.
	This combination gives the resulting color for the reflected specular light.
	*/
	GZ_GRAPH_EXPORT gzVoid setSpecular(const gzRGBA &matcol);

	//!Sets the emissive light for the material.
	GZ_GRAPH_EXPORT gzVoid setEmission(const gzRGBA &matcol);


	//!Sets the ambient property for the material.
	/*!
	The ambient material defines how the ambient light is reflected. \n
	The red ambient material color tells how the red ambient light for the color is reflected.
	The green ambient material color tells how the green ambient light for the color is reflected, etc.
	This combination gives the resulting color for the reflected ambient light.
	*/
	GZ_GRAPH_EXPORT gzVoid setAmbient(gzFloat red=1 , gzFloat green=1 , gzFloat blue=1 , gzFloat alpha=1 );
		
	//!Sets the diffuse property for the material.
	/*!
	The diffuse material defines how the diffuse light is reflected. \n
	The red diffuse material color tells how the red diffuse light for the color is reflected.
	The green diffuse material color tells how the green diffuse light for the color is reflected, etc.
	This combination gives the resulting color for the reflected diffuse light.
	*/GZ_GRAPH_EXPORT gzVoid setDiffuse(gzFloat red=1 , gzFloat green=1 , gzFloat blue=1 , gzFloat alpha=1 );
	
	//!Sets the specular property for the material.
	/*!
	The specular material defines how the specular light is reflected. \n
	The red specular material color tells how the red specular light for the color is reflected.
	The green specular material color tells how the green specular light for the color is reflected, etc.
	This combination gives the resulting color for the reflected specular light.
	*/
	GZ_GRAPH_EXPORT gzVoid setSpecular(gzFloat red=1 , gzFloat green=1 , gzFloat blue=1 , gzFloat alpha=1);
	
	//!Sets the emissive light for the material.
	GZ_GRAPH_EXPORT gzVoid setEmission(gzFloat red=1 , gzFloat green=1 , gzFloat blue=1 , gzFloat alpha=1);


	//!Sets the size of the highlight.
	GZ_GRAPH_EXPORT gzVoid setShininess(gzFloat shininess);

	//!Specifies the alpha value for the material.
	/*!
	The ambient, diffuse, specular and emission gets this alpha value.
	*/
	GZ_GRAPH_EXPORT gzVoid setMaterialAlpha(gzFloat value );

	
	//!Returns the ambient color.
	GZ_GRAPH_EXPORT const gzRGBA &		getAmbient() const;

	//!Returns the diffuse color.
	GZ_GRAPH_EXPORT const gzRGBA &		getDiffuse() const;

	//!Returns the specular color.
	GZ_GRAPH_EXPORT const gzRGBA &		getSpecular() const;

	//!Returns the emmision color.
	GZ_GRAPH_EXPORT const gzRGBA &		getEmission() const ;

	//!Returns the shininess factor.
	GZ_GRAPH_EXPORT gzFloat				getShininess() const;

	//!Returns the shininess factor.
	GZ_GRAPH_EXPORT gzBool				useColorAsMaterial() const;

	GZ_GRAPH_EXPORT gzColorMaterialMode	getColorMaterialMode() const;

	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	//!Overrides the gzReference useDeepCopyMode() to use gzNodeCopyMode.
	/*!
	Depending on what copy mode you have set a clone of a gzNode will either 
	return a new instance of a gzMaterial or a shared instance.
	*/
	GZ_GRAPH_EXPORT virtual gzBool useDeepCopy() override;

	// ---------- Misc --------------------------------------------------

	//!Equal operator
	/*!Returns true if the two materials are equal.
	*/
	GZ_GRAPH_EXPORT gzBool operator==(const gzMaterial &right) const;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const override;


private:

	gzRGBA	m_ambient;
	gzRGBA	m_diffuse;
	gzRGBA	m_specular;
	gzRGBA	m_emission;
	gzFloat	m_shininess;
	gzBool	m_colorAsMaterial;
	gzEnum	m_colorMode;
};

GZ_DECLARE_REFPTR(gzMaterial);

#endif
