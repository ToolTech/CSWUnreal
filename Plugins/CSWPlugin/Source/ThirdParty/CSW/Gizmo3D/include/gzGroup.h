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
// File			: gzGroup.h
// Module		: 
// Description	: Class definition of the gzGroup class
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
// AMO	981122	Created file 	
// AMO	120614	Added gzResourceGroup								(2.6.8)
//
//******************************************************************************
#ifndef __GZ_GROUP_H__
#define __GZ_GROUP_H__

/*!	\file 
	\brief Base definitions for node groupes

*/

#include "gzNode.h"

enum { 
		GZ_GROUP_SORT_Z,
		GZ_GROUP_SORT_STATE
	};	//!< Group sorting criterias

const gzUInt32  GZ_CHILD_NOT_IN_LIST = 0xfffffffful;

//******************************************************************************
// Class	: gzGroup
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981122	Created 
//									
//******************************************************************************
class gzGroup : public gzNode
{
public:

	GZ_GRAPH_EXPORT gzGroup(const gzString & name=GZ_EMPTY_STRING);
	GZ_GRAPH_EXPORT virtual ~gzGroup();

	// Declare implicits base ----------

	GZ_GRAPH_EXPORT gzGroup(const gzGroup &copy);
	GZ_GRAPH_EXPORT gzGroup & operator=(const gzGroup &copy);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
	GZ_GRAPH_EXPORT virtual gzVoid setCopyMode(const gzCopyMode & mode) override;


	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- group interface ---------------------------------------

	GZ_GRAPH_EXPORT gzUInt32 	getNumberOfNodes();

	GZ_GRAPH_EXPORT gzNode		*getNode( gzUInt32 childIndex );

	GZ_GRAPH_EXPORT gzNode		*getFirstNode();

	GZ_GRAPH_EXPORT gzUInt32	getNodeIndex( gzNode *child );

	GZ_GRAPH_EXPORT gzVoid 		addNode( gzNode *child , gzInt32 index = -1 );

	GZ_GRAPH_EXPORT gzVoid 		addNodeSorted( gzNode *child , const gzDouble & sortVal ,gzBool preInsert=FALSE);

	GZ_GRAPH_EXPORT gzBool  	removeNode(gzNode *child,gzListIterator<gzNode> *iterator=nullptr);

	GZ_GRAPH_EXPORT gzBool  	removeNode(const gzString& nodeName, gzBool multiple = FALSE, gzBool recursive=FALSE);

	GZ_GRAPH_EXPORT gzVoid		removeAllNodes(gzBool dirty=TRUE);

	GZ_GRAPH_EXPORT gzVoid		addGroupNodes( const gzGroup *parent );

	GZ_GRAPH_EXPORT virtual gzNode	*	find(const gzString &path,gzBool recursive=TRUE) override;
	GZ_GRAPH_EXPORT virtual gzBool		hasSiblingNode(gzNode *child);

	//! Recursive update of dirty node data
	GZ_GRAPH_EXPORT virtual gzVoid updateNodeData(gzBool force=FALSE) override;

	//! Check if group can be traversed
	GZ_GRAPH_EXPORT virtual gzBool	isTraversable( gzTraverseAction * /*action*/ , gzNode * /*node*/ , gzUInt32 /*index*/ , gzContext * /*context*/ ) { return TRUE; }

	//! Check if we will check traversal per child
	GZ_GRAPH_EXPORT virtual gzBool	checkTraversePerChild() const { return FALSE; }

	GZ_GRAPH_EXPORT virtual gzBool	isChildOrderDependant() const { return FALSE; }

	//! Speed up group
	GZ_GRAPH_EXPORT virtual gzBool	isGroupNode() const override { return TRUE; }	// Speed up RTTI

	GZ_GRAPH_EXPORT virtual gzVoid	sortNodes(gzUInt32 sortCriteria, gzBool recursive=FALSE);

	GZ_GRAPH_EXPORT gzRefList<gzNode> &	getNodeList();

	// ---------- Debug function ----------------------------------------
	GZ_GRAPH_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;
	GZ_GRAPH_EXPORT virtual	gzVoid	debugOutputTraverse(gzString base , gzString anchor , gzDebugFlags features) override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// -------------- Node visibility extent -----------------------------
	//! Returns false if visibility extent not defined or infinite
	GZ_GRAPH_EXPORT virtual gzBool getVisibilityExtent(gzVec3 &min,gzVec3 &max) const override;

	// ------------- Dirty save management ------------------------------
	GZ_GRAPH_EXPORT virtual gzBool hasDirtySaveData() const override;					// Looks downwards in tree
	GZ_GRAPH_EXPORT virtual gzBool saveDirtyData(const gzString &url = GZ_EMPTY_STRING) override;



protected:

	friend class gzTraverseAction;

	gzRefList<gzNode> m_childList;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzGroup);

//******************************************************************************
// Class	: gzDummyBoundary
//									
// Purpose  : To add a dummy boundary update to tree in e.g. a skinned model
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040803	Created 
//									
//******************************************************************************
class gzDummyBoundary : public gzGroup
{
public:

	GZ_GRAPH_EXPORT gzDummyBoundary(const gzString & name=GZ_EMPTY_STRING);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Actual action is not to continue rendering of dummy
	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction * /*action*/ , gzNode * /*node*/ , gzUInt32 /*index*/, gzContext * /*context*/) override { return FALSE; }

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
};

//******************************************************************************
// Class	: gzResourceGroup
//									
// Purpose  : Will not be optimized and will not drop any resources at dealloc
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	120614	Created 
//									
//******************************************************************************
class gzResourceGroup : public gzGroup
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzResourceGroup(const gzString & name=GZ_EMPTY_STRING);

	// ---------- release refs that will remain active ------------------
	GZ_GRAPH_EXPORT virtual gzBool	releaseRefs() override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
};

#endif
