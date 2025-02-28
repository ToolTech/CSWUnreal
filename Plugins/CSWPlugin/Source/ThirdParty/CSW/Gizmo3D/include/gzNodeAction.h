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
// File			: gzNodeAction.h
// Module		: 
// Description	: Class definition of the gzNodeAction class types
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
// AMO	000719	Created file 	
//
//******************************************************************************
#ifndef __GZ_NODE_ACTION_H__
#define __GZ_NODE_ACTION_H__

/*!	\file 
	\brief Actions for Pre / Post traversal actions like vertex interpolations etc.

*/

#include "gzNode.h"

//******************************************************************************
// Class	: gzNodeAction
//									
// Purpose  : Base class for all added actions to a node
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991116	Created 
//									
//******************************************************************************
class gzNodeAction : public gzNodeActionInterface , public gzNameInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzNodeAction(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzNodeAction(){};

	GZ_GRAPH_EXPORT	virtual gzVoid onAction(gzNodeActionEvent action , gzContext *context , gzNodeActionProvider *trigger ,gzTraverseAction *actionclass ,gzVoid *userdata) override =0;

	//---------------- Generic action interface ----------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid attach(gzNode *node);
	GZ_GRAPH_EXPORT virtual gzVoid deattach(gzNode *node);
};

//******************************************************************************
// Class	: gzPerformanceAction
//									
// Purpose  : Samples performance info for a specific node
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991116	Created 
//									
//******************************************************************************
class gzPerformanceAction : public gzNodeAction
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzPerformanceAction(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzPerformanceAction(){};

	GZ_GRAPH_EXPORT	virtual gzVoid onAction(gzNodeActionEvent action , gzContext *context , gzNodeActionProvider *trigger ,gzTraverseAction *actionclass ,gzVoid *userdata) override;

	GZ_GRAPH_EXPORT virtual gzVoid attach(gzNode *node) override;
	GZ_GRAPH_EXPORT virtual gzVoid deattach(gzNode *node) override;

private:

	gzString	m_updateSection;
	gzString	m_traverseSection;
	gzString	m_renderSection;
};

//******************************************************************************
// Class	: gzDebugAction
//									
// Purpose  : Breaks into debug mode for a certain node
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991116	Created 
//									
//******************************************************************************
class gzDebugAction : public gzNodeAction
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzDebugAction(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzDebugAction(){};

	GZ_GRAPH_EXPORT	virtual gzVoid onAction(gzNodeActionEvent action , gzContext *context , gzNodeActionProvider *trigger ,gzTraverseAction *actionclass ,gzVoid *userdata) override;

	GZ_GRAPH_EXPORT virtual gzVoid attach(gzNode *node) override;
	GZ_GRAPH_EXPORT virtual gzVoid deattach(gzNode *node) override;

	GZ_PROPERTY_EXPORT(gzBool,		BreakOnRender,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,		BreakOnTraverse,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,		BreakOnUpdate,		GZ_GRAPH_EXPORT);
};

#endif

