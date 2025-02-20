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
// File			: gzForceTraverse.h
// Module		: 
// Description	: Class definition of the gzForceTraverse class
// Author		: Anders Mod�n		
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
// AMO	200523	Created file		(2.10.5) 	
//
//******************************************************************************
#ifndef __GZ_FORCE_TRAVERSE_H__
#define __GZ_FORCE_TRAVERSE_H__

/*!	\file 
	\brief Base definitions for force travesr swith nodes

*/


#include "gzGroup.h"

//******************************************************************************
// Class	: gzForceTraverse
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	200523	Created 
//									
//******************************************************************************
class gzForceTraverse : public gzGroup
{
public:
	GZ_GRAPH_EXPORT gzForceTraverse(const gzString & name=GZ_EMPTY_STRING);
	GZ_GRAPH_EXPORT virtual ~gzForceTraverse(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ----------- Properties -------------------------------------------

	GZ_PROPERTY_EXPORT(gzBool,		DefaultEnable,		GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt32,	ForceEnableMask,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32,	ForceDisableMask,	GZ_GRAPH_EXPORT);

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzBool	checkTraversePerChild() const override { return TRUE; }

	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index, gzContext *context) override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

private:

};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzForceTraverse);

#endif
