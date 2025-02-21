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
// File			: gzThreadNodeDeallocator.h
// Module		: gzGraph
// Description	: Class definition of the gzThreadNodeDeallocator that deallocates with write lock
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
// AMO	180607	Created file 	
//
//******************************************************************************
#ifndef __GZ_THREAD_NODE_DEALLOCATOR_H__
#define __GZ_THREAD_NODE_DEALLOCATOR_H__

/*!	\file 
	\brief Paged loading/unloading manager for references used in gzNode write lock

*/

#include "gzNode.h"

//******************************************************************************
// Class	: gzThreadNodeLockedDeallocator
//
// Purpose  : The manager for dynamic delete of references during node lock
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	021119	Created
//
//******************************************************************************
class gzThreadEditLockedDeallocator : public gzThread
{
public:

	GZ_GRAPH_EXPORT gzThreadEditLockedDeallocator();

	GZ_GRAPH_EXPORT virtual ~gzThreadEditLockedDeallocator();

	GZ_GRAPH_EXPORT static	gzVoid startDeallocator();

	GZ_GRAPH_EXPORT static	gzVoid stopDeallocator();

	GZ_GRAPH_EXPORT static	gzBool isDeallocatorRunning();

	GZ_GRAPH_EXPORT static	gzVoid deallocObject(gzReference *object, gzBool force = FALSE);

	GZ_GRAPH_EXPORT static	gzVoid trigger();

	GZ_GRAPH_EXPORT static	gzVoid waitLock();

	GZ_GRAPH_EXPORT static	gzVoid unLock();

	GZ_GRAPH_EXPORT static	gzBool hasPendingDealloc();

	GZ_STATIC_PROPERTY_MUTEX_EXPORT(gzUInt32, MaxPendingDeletes, s_locker, GZ_GRAPH_EXPORT);

	GZ_NO_IMPLICITS(gzThreadEditLockedDeallocator);

private:

	static gzMutex					s_locker;
	static gzRefList<gzReference>	s_objectList_in;
	static gzRefList<gzReference>	s_objectList_del;
	static gzEvent					s_trigger;

	virtual gzVoid process();
};

//******************************************************************************
// Class	: gzThreadNodeDeallocator
//
// Purpose  : The manager for dynamic delete of nodes during node lock
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	180607	Created
//
//******************************************************************************
class gzThreadNodeDeallocator : public gzThread
{
public:

	GZ_GRAPH_EXPORT gzThreadNodeDeallocator();

	GZ_GRAPH_EXPORT virtual ~gzThreadNodeDeallocator();
	
	GZ_GRAPH_EXPORT static	gzVoid startDeallocator();

	GZ_GRAPH_EXPORT static	gzVoid stopDeallocator();

	GZ_GRAPH_EXPORT static	gzBool isDeallocatorRunning();

	GZ_GRAPH_EXPORT static	gzVoid deallocNode(gzNode *node,gzBool force=FALSE);

	GZ_GRAPH_EXPORT static	gzVoid trigger();

	GZ_GRAPH_EXPORT static	gzVoid waitLock();

	GZ_GRAPH_EXPORT static	gzVoid unLock();

	GZ_GRAPH_EXPORT static	gzMutex& getDeallocatorLock();

	GZ_GRAPH_EXPORT static	gzBool hasPendingDealloc();

	GZ_STATIC_PROPERTY_MUTEX_EXPORT(gzUInt32, MaxPendingDeletes,	s_locker, GZ_GRAPH_EXPORT);

	GZ_NO_IMPLICITS(gzThreadNodeDeallocator);

private:

	static gzMutex				s_locker;
	static gzRefList<gzNode>	s_nodeList_in;
	static gzRefList<gzNode>	s_nodeList_del;
	static gzEvent				s_trigger;
	
	virtual gzVoid process();
};

#endif //__GZ_THREAD_NODE_DEALLOCATOR_H__

