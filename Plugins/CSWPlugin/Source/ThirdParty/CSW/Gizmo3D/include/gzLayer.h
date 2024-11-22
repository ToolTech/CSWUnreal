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
// File			: gzLayer.h
// Module		: 
// Description	: Class definition of the gzLayer class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.200
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
// AMO	000305	Created file 	
//
//******************************************************************************
#ifndef __GZ_LAYER_H__
#define __GZ_LAYER_H__

/*!	\file 
	\brief Base definitions for Layer nodes

*/

#include "gzGroup.h"

//******************************************************************************
// Class	: gzLayer
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000305	Created 
//									
//******************************************************************************
class gzLayer : public gzGroup
{
public:
	GZ_GRAPH_EXPORT gzLayer(const gzString & name=GZ_EMPTY_STRING);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT virtual ~gzLayer(){};


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ----------- gzGroup interface ------------------------------------

	GZ_GRAPH_EXPORT virtual gzBool	isChildOrderDependant() const override;

	GZ_GRAPH_EXPORT virtual gzBool	checkTraversePerChild() const override;


	// ---------- gzLayer commands --------------------------------------

	// ---------- Action Interface --------------------------------------
	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index, gzContext *context) override;
};

#endif
