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
// File			: gzAttach.h
// Module		: 
// Description	: Class definition of the gzAttach class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.262
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
#ifndef __GZ_ATTACH_H__
#define __GZ_ATTACH_H__

/*!	\file 
	\brief Base definitions for group attached node

*/

#include "gzGroup.h"
#include "gzLod.h"

class gzAttach;	// Forward declaration

class gzAttachIdChangeAction : public gzNodeActionInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzAttachIdChangeAction(gzAttach *owner);

	GZ_GRAPH_EXPORT virtual ~gzAttachIdChangeAction(){};

	GZ_GRAPH_EXPORT	virtual gzVoid onAction(gzNodeActionEvent action , gzContext *context , gzNodeActionProvider *trigger ,gzTraverseAction *actionclass ,gzVoid *userdata) override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

private:

	gzAttach *	m_owner;
};


//******************************************************************************
// Class	: gzAttach
//									
// Purpose  : Attach our subtree under a given node id on a group
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
class gzAttach : public gzGroup
{
public:

	GZ_GRAPH_EXPORT gzAttach(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzAttach();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- shotdown some group traversals etc.. ------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT gzBool	isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index , gzContext *context ) override;

	GZ_GRAPH_EXPORT gzVoid	updateNodeData(gzBool force=FALSE) override;

	GZ_GRAPH_EXPORT gzVoid	updateNode() override;

	GZ_GRAPH_EXPORT gzVoid	debugOutputTraverse(gzString base , gzString anchor , gzDebugFlags features) override;

	GZ_GRAPH_EXPORT virtual gzVoid debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ---------- attach interface --------------------------------------

	GZ_GRAPH_EXPORT	gzVoid	setAttachID(gzUInt32 id);

	GZ_GRAPH_EXPORT	gzVoid	attachGroup();

	GZ_GRAPH_EXPORT gzVoid	detachGroup();

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	GZ_GRAPH_EXPORT virtual gzBool releaseRefs() override;
	
private:

	gzUInt32									m_currentAttachID;

	gzRefPointer<gzGroup>					m_currentGroup;

	gzRefPointer<gzLodForceAction>			m_lodForceAction;

	gzRefPointer<gzAttachIdChangeAction>	m_idChangeAction;

};

#endif
