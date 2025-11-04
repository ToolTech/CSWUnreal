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
// File			: gzTexEnv.h
// Module		: 
// Description	: Class definition of the gzTexEnv class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.283
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
// AMO	990520	Created file 	
//
//******************************************************************************
#ifndef __GZ_TEXENV_H__
#define __GZ_TEXENV_H__

/*!	\file 
	\brief Base definitions texture environment (TexEnv)

*/


#include "gzObject.h"
#include "gzMatrix.h"
#include "gzImage.h"

class gzContext;

enum gzTexEnvMode
{
	GZ_TEXENV_MODE_DECAL	=	GZ_DECAL,
	GZ_TEXENV_MODE_REPLACE	=	GZ_REPLACE,
	GZ_TEXENV_MODE_MODULATE	=	GZ_MODULATE,
	GZ_TEXENV_MODE_BLEND	=	GZ_BLEND,
	GZ_TEXENV_MODE_ADD		=	GZ_ADD,
	GZ_TEXENV_MODE_COMBINE	=	GZ_COMBINE,
};


//******************************************************************************
// Class	: gzTexEnv
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990520	Created 
//									
//******************************************************************************
class gzTexEnv : public gzObject 
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzTexEnv();
	GZ_GRAPH_EXPORT virtual ~gzTexEnv(){};

	GZ_GRAPH_EXPORT gzVoid	virtual activate(gzContext *context);

	GZ_GRAPH_EXPORT static gzVoid deactivate(gzContext *context); 

	GZ_GRAPH_EXPORT gzVoid			setMode(gzTexEnvMode mode);
	GZ_GRAPH_EXPORT gzTexEnvMode	getMode() const;

	GZ_GRAPH_EXPORT gzVoid			setBlendColor(gzFloat red , gzFloat green , gzFloat blue , gzFloat alpha);
	GZ_GRAPH_EXPORT gzVoid			setBlendColor(const gzVec4 &color);
	GZ_GRAPH_EXPORT gzVec4			getBlendColor()	const;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
	GZ_GRAPH_EXPORT virtual gzBool useDeepCopy() override;

	// ---------- Misc --------------------------------------------------

	GZ_GRAPH_EXPORT gzBool operator==(const gzTexEnv &right) const;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

private:

	gzTexEnvMode	m_mode;
	gzFloat			m_red,m_green,m_blue,m_alpha;


};

GZ_DECLARE_REFPTR(gzTexEnv);


#endif
