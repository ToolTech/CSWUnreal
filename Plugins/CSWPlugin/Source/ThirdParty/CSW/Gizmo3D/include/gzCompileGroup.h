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
// File			: gzCompileGroup.h
// Module		: 
// Description	: Class definition of the gzCompileGroup class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.223
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
// AMO	030312	Created file 
//
//******************************************************************************
#ifndef __GZ_COMPILE_GROUP_H__
#define __GZ_COMPILE_GROUP_H__

/*!	\file 
	\brief Base definitions for compiled node contents

*/


#include "gzGroup.h"

//******************************************************************************
// Class	: gzCompileGroup
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
class gzCompileGroup : public gzGroup
{
public:
	GZ_GRAPH_EXPORT gzCompileGroup(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzCompileGroup();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- gzCompileGroup commands ----------------------------------------

	GZ_GRAPH_EXPORT	gzVoid reCompile();

	GZ_GRAPH_EXPORT gzVoid expandGeometry(gzBool on=TRUE);

	GZ_GRAPH_EXPORT gzVoid dropSource(gzBool on);

	// ---------- Action Interface --------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index, gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction *actionclass , gzContext *context) override;


private:

	gzVoid clearCompiledContexts();

	gzDynamicArray<gzRefPointer<gzContext> >	m_compiledContexts;

	gzBool										m_expandGeometry:1;

	gzBool										m_dropSource:1;

};

#endif
