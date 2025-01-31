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
// File			: gzApplication.h
// Module		: 
// Description	: Class definition of the gzApplication class
// Author		: Anders ModÈn		
// Product		: Gizmo3D 2.12.211
//		
//	
//			
// NOTE:	Gizmo3D is a high performance 3D Scene Graph and effect visualisation 
//			C++ toolkit for Linux, Mac OS X, Windows (Win32) and IRIXÆ for  
//			usage in Game or VisSim development.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981027	Created file 	
// AMO	130124	Added use of pre defined windows in .nib files etc		(2.6.23)
//
//******************************************************************************
#ifndef __GZ_APPLICATION_H__
#define __GZ_APPLICATION_H__

/*!	\file 
	\brief Base definitions of a Gizmo3D Application

*/

#include "gzBase.h"
#include "gzThread.h"
#include "gzNotify.h"
#include "gzGraphicsAbstractionLayer.h"

#ifdef GZ_WINDOWS 
// ------------------------  GZ_WINDOWS ---------------------------------

using	gzDeviceContext = HDC;
using	gzWindowHandle = HWND;
using	gzWindowContext = HWND;

class gzAppContext
{
public:
	HINSTANCE 		instance;
	gzDeviceContext display;
};

#elif defined GZ_GLX 

// ------------------------ UNIX ----------------------------------- 

#include <X11/Xlib.h>         // Missing:: Install libx11-dev
#include <X11/Intrinsic.h>    // Missing:: Install libxt-dev

typedef Display*					gzDeviceContext;
typedef Widget						gzWindowHandle;
typedef Window						gzWindowContext;

class gzAppContext
{
public:
	gzDeviceContext display;
	XtAppContext	context;
};

#elif defined GZ_IOS || defined GZ_MAC

// ------------------------ IPhone/Mac OS X ------------------------------	

typedef gzInt32*					gzDeviceContext;
typedef gzVoid*						gzWindowHandle;         // gzWindow_ ObjC
typedef gzInt32*					gzWindowContext;


class gzAppContext
	{
	public:
		gzDeviceContext     display;
		gzUInt32			context;
        gzVoid *            objCApplication;
	};

#elif defined GZ_ANDROID_SYST

struct android_app;
struct ANativeWindow;


typedef android_app*				gzDeviceContext;
typedef ANativeWindow*				gzWindowHandle;
typedef gzInt32*					gzWindowContext;

class gzAppContext
	{
	public:
		gzDeviceContext     application;
		gzVoid *			prev_onAppCmd;
		gzVoid *			prev_userData;
		
	};

#else	// --------------- No defined UI or Application System----------

typedef gzInt32 *						gzDeviceContext;
typedef gzInt32 *						gzWindowHandle;
typedef gzInt32 *						gzWindowContext;


class gzAppContext
{
public:
	gzDeviceContext     application;
};

#endif // ------------------------ COMMON ---------------------------------

//******************************************************************************
// Class	: gzApplication
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981027	Created 
//									
//******************************************************************************
class gzApplication : public gzNotifyManager , public gzReference , public gzProgramExecution
{
public:

	GZ_SYSTEM_EXPORT gzApplication(const gzString & name="GIZMO APPLICATION" , int argc=0 , char **argv=NULL , gzDeviceContext dc=NULL);

	GZ_SYSTEM_EXPORT virtual ~gzApplication();

	//! Start the application loop
    //! If loadSystemAppWindows=TRUE, windows will be loaded from application (nib files etc.) when run mode is entered
	GZ_SYSTEM_EXPORT gzVoid	run(gzBool loadSystemAppWindows=FALSE);

	//! Stop the application loop
	GZ_SYSTEM_EXPORT gzVoid	stop();

	//! Polled execution of app events.
	/*! Returns 0 if no more pending events. returns -1 if exit is pending. returns 1 else. */
	GZ_SYSTEM_EXPORT gzInt32	poll(gzBool forceExecNotifications=TRUE);

	GZ_SYSTEM_EXPORT virtual gzVoid onIdle();

	GZ_SYSTEM_EXPORT virtual gzVoid onTick();

	GZ_SYSTEM_EXPORT gzVoid	setTickInterval( gzDouble seconds );
	
	GZ_SYSTEM_EXPORT gzDouble getTickInterval();

	GZ_SYSTEM_EXPORT gzAppContext getAppContext();

	GZ_SYSTEM_EXPORT gzBool isRunning();

	GZ_SYSTEM_EXPORT gzBool isStopping();

	GZ_SYSTEM_EXPORT static gzVoid clearGizmoApplication();
	
	GZ_SYSTEM_EXPORT static gzRefPointer<gzApplication> getGizmoApplication();

	GZ_SYSTEM_EXPORT static gzVoid stopGizmoApplication();

	GZ_SYSTEM_EXPORT static gzBool refresh();

	GZ_SYSTEM_EXPORT gzBool	useDeepCopy() { return FALSE; }	// Default behaviour is to SHARE

#if defined GZ_GLX 

// -------------------------------  UNIX ---------------------------------

	gzInt32 	getWMProtocolLength()	{ return 1; }
	Atom *		getWMProtocol()			{ return &m_wm_delete_window; }
	
#endif // ------------------------ COMMON ---------------------------------


private:

	gzApplication(const gzApplication &right):gzNotifyManager(),gzReference(right),gzProgramExecution(){}		// Forbidden

	GZ_SYSTEM_EXPORT virtual gzVoid onProgramExecution();
		
	friend class gzWindow;

	gzString	m_appName;

	gzDouble	m_tickIntervalTime;

	gzDouble	m_nextTickTime;

	gzBool		m_isRunning;

	gzBool		m_isStopping;
	
	gzAppContext m_appContext;

	gzMutex		m_appLock;
	
#if defined GZ_GLX
// ------------------  UNIX ---------------------------------

	static Boolean workproc( XtPointer clientData);

	Atom m_wm_protocols;
	Atom m_wm_delete_window;
 	
#endif // ------------------------ COMMON ---------------------------------

	static gzRefPointer<gzApplication>  s_gizmoApplication;
	static gzMutex                      s_appLocker;
};

GZ_DECLARE_REFPTR(gzApplication);



#endif // __GZ_APPLICATION_H__
