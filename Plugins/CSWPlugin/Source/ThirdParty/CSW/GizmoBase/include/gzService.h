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
// File			: gzService.h
// Module		: gzBase
// Description	: Class definition of service features
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.275
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
// AMO	041104	Created file 	
//
//******************************************************************************
#ifndef __GZ_SERVICE_H__
#define __GZ_SERVICE_H__

#include "gzBase.h"
#include "gzLex.h"
#include "gzModule.h"

enum gzServiceStatus
{
	GZ_SERVICE_STOPPED,
	GZ_SERVICE_PAUSED_RUNNING,
	GZ_SERVICE_RUNNING
};

const gzUInt32 GZ_SERVICE_EXIT_THROW_EXCEPTION = 99;	// Exit result 99 wil throw exception

//******************************************************************************
// Class	: gzService
//									
// Purpose  : Service management
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	041104	Created 
//									
//******************************************************************************
class gzService : public gzProgramExecution
{
public:

	GZ_BASE_EXPORT gzService(const gzString &name,const gzString &comment=GZ_EMPTY_STRING);
	GZ_BASE_EXPORT virtual ~gzService();

	GZ_BASE_EXPORT gzBool registerService(gzBool autostart=TRUE);
	GZ_BASE_EXPORT gzBool unregisterService();

	GZ_BASE_EXPORT gzBool exec(int argc, char *argv[]);
	GZ_BASE_EXPORT gzBool exec(const gzArgumentParser &args);

	GZ_BASE_EXPORT gzVoid setExecution(const gzArgumentParser& args,gzBool runAsService);

	GZ_BASE_EXPORT gzBool	startService();
	GZ_BASE_EXPORT gzBool	stopService();
	GZ_BASE_EXPORT gzBool	pauseService();
	GZ_BASE_EXPORT gzBool	continueService();

	GZ_BASE_EXPORT virtual gzVoid process(const gzArgumentParser &args,gzBool runAsService)=0;
	
	GZ_BASE_EXPORT gzBool	isRunning();
	GZ_BASE_EXPORT gzBool	isPaused();
	GZ_BASE_EXPORT gzBool	isRegistered();

	GZ_BASE_EXPORT gzVoid	setStatus(gzServiceStatus status);

	GZ_BASE_EXPORT const gzString &			getName();
	GZ_BASE_EXPORT const gzString &			getComment();
	GZ_BASE_EXPORT const gzArgumentParser &	getArguments();
	GZ_BASE_EXPORT gzString 				getPath();


	// virtual callbacks

	GZ_BASE_EXPORT virtual gzVoid	onStop(){};
	GZ_BASE_EXPORT virtual gzVoid	onPause(){};
	GZ_BASE_EXPORT virtual gzVoid	onContinue(){};

	GZ_BASE_EXPORT static gzService*	getInstance();
	GZ_BASE_EXPORT static gzBool		runAsService(gzBool on=TRUE);

	GZ_PROPERTY_EXPORT(gzUInt32, ExitValue, GZ_BASE_EXPORT);
	GZ_BASE_EXPORT virtual gzUInt32	getExitCode() const;


private:

	GZ_BASE_EXPORT virtual gzVoid onProgramExecution();


	gzArgumentParser		m_args;

	gzBool					m_runAsService;

	gzString				m_name;

	gzString				m_comment;

	gzServiceStatus			m_status;
};

#endif //__GZ_SERVICE_H__
