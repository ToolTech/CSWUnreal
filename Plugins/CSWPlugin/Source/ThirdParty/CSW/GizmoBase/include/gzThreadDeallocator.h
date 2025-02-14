//******************************************************************************
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
// File			: gzThreadDeallocator.h
// Module		: gzBase
// Description	: Class definition of the gzThreadDeallocator class
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.220
//		
//
//			
// NOTE:	GizmoBase is a platform abstraction utility layer for C++. It contains 
//			design patterns and C++ solutions for the advanced programmer.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	091224	Created file 	
//
//******************************************************************************
#ifndef __GZ_THREAD_DEALLOCATOR_H__
#define __GZ_THREAD_DEALLOCATOR_H__

/*!	\file 
	\brief Paged loading/unloading manager

*/

#include "gzReference.h"
#include "gzThread.h"
#include "gzMutex.h"

//******************************************************************************
// Class	: gzThreadDeallocator
//
// Purpose  : The manager for dynamic delete.
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
class gzThreadDeallocator : public gzThread
{
public:

	gzThreadDeallocator();

	virtual ~gzThreadDeallocator();
	
	GZ_BASE_EXPORT static	gzVoid startDeallocator();

	GZ_BASE_EXPORT static	gzVoid stopDeallocator();

	GZ_BASE_EXPORT static	gzBool isDeallocatorRunning();

	GZ_BASE_EXPORT static	gzVoid deallocObject(gzReference *object,gzBool force=FALSE);

	GZ_BASE_EXPORT static	gzVoid trigger();

	GZ_BASE_EXPORT static	gzVoid waitLock();

	GZ_BASE_EXPORT static	gzVoid unLock();

	GZ_BASE_EXPORT static	gzBool hasPendingDealloc();

	GZ_STATIC_PROPERTY_MUTEX_EXPORT(gzUInt32, MaxPendingDeletes,	s_locker, GZ_BASE_EXPORT);

private:

	static gzMutex					s_locker;
	static gzRefList<gzReference>	s_objectList_in;
	static gzRefList<gzReference>	s_objectList_del;
	static gzEvent					s_trigger;
	
	virtual gzVoid process();
};

#endif //__GZ_THREAD_DEALLOCATOR_H__
