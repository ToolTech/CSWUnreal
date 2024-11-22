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
// File			: gzRefNode.h
// Module		: 
// Description	: Class definition of the gzRefNode class
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
// AMO	091125	Created file 	
//
//******************************************************************************
#ifndef __GZ_REF_NODE_H__
#define __GZ_REF_NODE_H__

/*!	\file 
	\brief Base definitions for a weak referenced node

*/

#include "gzGroup.h"
#include "gzLod.h"

class gzRefNode;	// Forward declaration

//******************************************************************************
// Class	: gzRefNode
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	020919	Created 
//									
//******************************************************************************
class gzRefNode : public gzGroup
{
public:

	GZ_GRAPH_EXPORT gzRefNode(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzRefNode();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- shotdown some group traversals etc.. ------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzBool isTraversable(gzTraverseAction* action, gzNode* node, gzUInt32 index, gzContext* context) override;

	GZ_GRAPH_EXPORT gzVoid	debugOutputTraverse(gzString base , gzString anchor , gzDebugFlags features) override;

	GZ_GRAPH_EXPORT virtual gzVoid debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ---------- attach interface --------------------------------------

	GZ_GRAPH_EXPORT	gzVoid	setReferencedNodeID(gzUInt32 id);

	GZ_GRAPH_EXPORT gzUInt32 getReferencedNodeID();

	GZ_GRAPH_EXPORT gzBool	hasReferencedNodeID();

	GZ_GRAPH_EXPORT	gzBool	attachNode();

	GZ_GRAPH_EXPORT gzVoid	detachNode();

	GZ_GRAPH_EXPORT gzBool	isAttached();

	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// release vital shared data before thread deallocates
	GZ_GRAPH_EXPORT virtual gzBool releaseRefs() override;

	GZ_STATIC_PROPERTY_EXPORT(gzCopyMode, CloneFlags, GZ_GRAPH_EXPORT);

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

private:

	gzUInt32								m_referenceNodeID;

	gzRefPointer<gzNode>					m_referenceNode;
};

#endif
