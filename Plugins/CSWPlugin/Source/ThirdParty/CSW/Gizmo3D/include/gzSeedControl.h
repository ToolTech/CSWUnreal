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
// File			: gzSeedControl.h
// Module		: 
// Description	: Class definition of the gzSeedControl class
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
// AMO	981122	Created file 	
//
//******************************************************************************
#ifndef __GZ_SEED_CONTROL_H__
#define __GZ_SEED_CONTROL_H__

/*!	\file 
	\brief Base definitions for seed controlling mechanisms

*/

#include "gzGroup.h"
#include "gzLod.h"

enum gzSeedControlType
{
	GZ_SEED_FROM_X		=	(1<<0),
	GZ_SEED_FROM_Y		=	(1<<1),
	GZ_SEED_FROM_Z		=	(1<<2),
	GZ_SEED_FROM_XY		=	GZ_SEED_FROM_X|GZ_SEED_FROM_Y,
	GZ_SEED_FROM_XZ		=	GZ_SEED_FROM_X|GZ_SEED_FROM_Z,
	GZ_SEED_FROM_YZ		=	GZ_SEED_FROM_Y|GZ_SEED_FROM_Z,
	GZ_SEED_FROM_XYZ	=	GZ_SEED_FROM_X|GZ_SEED_FROM_Y|GZ_SEED_FROM_Z,
	GZ_SEED_FROM_VALUE	=	(1<<3),
	GZ_SEED_FROM_TIME	=	(1<<4)
};

//******************************************************************************
// Class	: gzSeedControl
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030313	Created 
//									
//******************************************************************************
class gzSeedControl : public gzGroup
{
public:

	GZ_GRAPH_EXPORT gzSeedControl(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzSeedControl();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Seed control interface --------------------------------

	GZ_GRAPH_EXPORT gzVoid setSeedControlType(gzSeedControlType type);

	GZ_GRAPH_EXPORT gzVoid setSeedValue(gzUInt32 value);

	GZ_GRAPH_EXPORT gzVoid setSeedScaleFactor(const gzFloat &factor);


	// ---------- updates of seed values --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	
private:

	gzSeedControlType	m_controlType;

	gzUInt32				m_value;

	gzFloat				m_scaleFactor;
};

#endif
