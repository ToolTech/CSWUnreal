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
// File			: gzStackInfo.h
// Module		: gzBase
// Description	: Class definitions and macros for stack debugging aid
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.262
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
// AMO	050211	Created file 	
// AMO	210521	Added dump of android crash to /sdcard/			(2.11.6)
// AMO	210521	Added dump of unix to execition dir				(2.11.6)
//
//******************************************************************************

#ifndef __GZ_STACK_INFO_H__
#define __GZ_STACK_INFO_H__

/*!	\file 
	\brief Basic utilites for stack debug management

	Generator of stacks for program execution info
*/

#include "gzReference.h"
#include "gzBase.h"
#include "gzExceptions.h"
#include "gzSerialize.h"

// Declaration of probe
typedef gzString (*ProbeFunc)();

GZ_BASE_EXPORT gzBool gzGetStackInfo(gzStackInfo *info);

class gzProgramExecution
{
public:

	GZ_BASE_EXPORT gzProgramExecution();
	GZ_BASE_EXPORT virtual ~gzProgramExecution();

	//! Will execute program provided in onProgramExecution
	GZ_BASE_EXPORT gzVoid run();

	GZ_BASE_EXPORT gzVoid checkBaseExceptions();

	GZ_BASE_EXPORT virtual gzVoid onProgramExecution()=0;
	GZ_BASE_EXPORT virtual gzVoid onCrash(gzStackInfo *info);
	GZ_BASE_EXPORT virtual gzVoid onBaseException(const gzBaseError &error);

	GZ_PROPERTY_EXPORT(gzBool,					ExceptionHandled,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,					SplashScreen,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,					RouteExceptions,	GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzString,			LastDumpName,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzStackInfoPtr,			StackInfo,			GZ_BASE_EXPORT);


	GZ_BASE_EXPORT	gzBool openDump();
	GZ_BASE_EXPORT	gzVoid closeDump();

	GZ_BASE_EXPORT static ProbeFunc setProbeFunction(ProbeFunc foo);

	GZ_BASE_EXPORT static gzString probeFunction();

private:

	gzSerializeAdapterFile *m_crashDump;

	static ProbeFunc	s_probeFunc;
	static gzMutex		s_probeLock;
};

GZ_BASE_EXPORT gzVoid gzExecuteProgram(gzProgramExecution *instance);

GZ_BASE_EXPORT gzVoid gzCheckStackDumpManager();

#endif
