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
// File			: gzWindow.h
// Module		: 
// Description	: Class definition of the gzWindow class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.306
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
// AMO	981027	Created file 	
//
//******************************************************************************
#ifndef __GZ_WINDOW_H__
#define __GZ_WINDOW_H__

/*!	\file 
	\brief Base definitions of a Gizmo3D Window

*/

#include "gzBase.h"
#include "gzApplication.h"
#include "gzRenderBase.h"
#include "gzContext.h"
#include "gzInput.h"
#include "gzNetwork.h"

#include "gzGraphicsFormat.h"

// Performance section in gzWindow
const gzString GZ_SECTION_WIN_MAKE_CURRENT	="_win_make_curr";
const gzString GZ_SECTION_WIN_SWAP_BUFFERS	="_win_swap_buffers";

class gzWindow;	// Forward declaration

typedef gzWindow * ( GZ_CALLBACK * gzWindowCreator)(const gzString & name , gzWindowHandle parent , gzGraphicsFormat *format, gzBool activateWindow);

//******************************************************************************
// Class	: gzWindow
//									
// Purpose  : -
//									
// Notes	: A window is owned by a single thread ! The refresh method MUST be 
//			  called from the owner thread !!!!!
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981027	Created 
//									
//******************************************************************************
class gzWindow : public gzRenderBase , public gzInputProvider , public gzNotifyInterface , public gzNameInterface , public gzMutex
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_SYSTEM_EXPORT);	// typed interface

	//! Gizmo3D STD window
	GZ_SYSTEM_EXPORT gzWindow( const gzString & name = "Gizmo3D" , gzWindowHandle parent=NULL ,gzGraphicsFormat *format=NULL , gzBool activateWindow=TRUE);

	//! subwindow creation
	GZ_SYSTEM_EXPORT gzWindow( const gzString & name , gzWindowContext parent , gzDeviceContext dc , gzGraphicsFormat *format , gzBool activateWindow);

	GZ_SYSTEM_EXPORT virtual ~gzWindow();

	//! Get the HWND on Win32 systems or Widget on X11 systems
	GZ_SYSTEM_EXPORT gzWindowHandle		getHandle()		{ return m_handle; };

	//! Get the HWND on Win32 systems or Window on X11 systems
	GZ_SYSTEM_EXPORT gzWindowContext	getWinContext() { return m_winContext; };

	GZ_SYSTEM_EXPORT gzBool	hasActiveContext();

	GZ_SYSTEM_EXPORT static gzWindow *getWindow( gzWindowHandle handle=0 , gzWindowContext=0 );
	
	GZ_SYSTEM_EXPORT static gzWindow *getWindow( const gzString &name );
	
	GZ_SYSTEM_EXPORT static gzWindow *createDefaultWindow( const gzString & name = "Gizmo3D" , gzWindowHandle parent=NULL  , gzGraphicsFormat *format=NULL , gzBool activateWindow=TRUE);
	
	GZ_SYSTEM_EXPORT static gzWindowCreator setDefaultWindowCreator( gzWindowCreator creator);
	

	// ---------------- Control the window ---------------------

	GZ_SYSTEM_EXPORT gzUInt32XY getSize();
	GZ_SYSTEM_EXPORT gzInt32XY	getPosition();

	GZ_SYSTEM_EXPORT gzInt32XY	getMousePosition();
	GZ_SYSTEM_EXPORT gzInt32XY	getCenterMousePosition();

	GZ_SYSTEM_EXPORT const gzGraphicsFormat *getFormat();

	GZ_SYSTEM_EXPORT gzVoid	setSize(gzUInt32 width , gzUInt32 height);
	GZ_SYSTEM_EXPORT gzVoid	setPosition(gzInt32 x , gzInt32 y);
	GZ_SYSTEM_EXPORT gzVoid setTitle(const gzString &title);
    GZ_SYSTEM_EXPORT gzVoid setScreenWidth(gzUInt32 width);

	GZ_SYSTEM_EXPORT gzVoid show();			// call to close output.
	GZ_SYSTEM_EXPORT gzVoid hide();			// call to close output.

	GZ_SYSTEM_EXPORT gzVoid	doQuitOnClose(gzBool quit);
	GZ_SYSTEM_EXPORT gzVoid	useInputProvider(gzBool on);
	GZ_SYSTEM_EXPORT gzVoid	deleteContext();

	GZ_SYSTEM_EXPORT virtual gzBool refresh() override; // route to window
	GZ_SYSTEM_EXPORT virtual gzBool	refreshWindow();
	GZ_SYSTEM_EXPORT gzVoid	setRefreshRate(gzFloat rate);

	//! Window locking and activating
	GZ_SYSTEM_EXPORT gzVoid setForeground();
	GZ_SYSTEM_EXPORT gzVoid lockForeground(gzBool on);

	//! Mouse locking and activating
	GZ_SYSTEM_EXPORT gzVoid setCaptureMouse(gzBool on);
	GZ_SYSTEM_EXPORT gzVoid setHideMouse(gzBool on);
	GZ_SYSTEM_EXPORT gzVoid	setMousePosition(gzUInt32 x , gzUInt32 y);
	
	GZ_SYSTEM_EXPORT gzVoid	showDynamicLoadProgress(gzBool on);

	GZ_PROPERTY_EXPORT(gzBool,	IncludeSwapInDraw,		GZ_SYSTEM_EXPORT);	//!< True if swap time is included in draw time
	GZ_PROPERTY_EXPORT(gzInt32,	SwapInterval,			GZ_SYSTEM_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,	StopApplicationOnESC,	GZ_SYSTEM_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,	EnableSwap,				GZ_SYSTEM_EXPORT);

	//--------- some virtual convenience callbacks -------------
	
	GZ_SYSTEM_EXPORT virtual gzVoid onCommand(int /*wmId*/, int /*wmEvent*/){};
	GZ_SYSTEM_EXPORT virtual gzBool onKey(gzKeyValue key , gzKeyState keystate , gzInt32 mouse_x , gzInt32 mouse_y);
	GZ_SYSTEM_EXPORT virtual gzVoid onMouseMove(gzInt32 mouse_x , gzInt32 mouse_y);
	GZ_SYSTEM_EXPORT virtual gzVoid onMouseWheel(gzInt32 delta,gzInt32 mouse_x , gzInt32 mouse_y);

	GZ_SYSTEM_EXPORT virtual gzVoid onShow(){};
	GZ_SYSTEM_EXPORT virtual gzVoid onHide(){};
	GZ_SYSTEM_EXPORT virtual gzVoid onSize(gzUInt32 /*width*/ , gzUInt32 /*height*/){};
	GZ_SYSTEM_EXPORT virtual gzVoid onPosition(gzInt32 /*width*/ , gzInt32 /*height*/){};

	GZ_SYSTEM_EXPORT		 gzVoid setFocus();
	GZ_SYSTEM_EXPORT virtual gzVoid onFocus();
	GZ_SYSTEM_EXPORT virtual gzVoid onLostFocus();
	GZ_SYSTEM_EXPORT virtual gzVoid onClose(){};

	GZ_SYSTEM_EXPORT virtual gzBool onMouseCursor();

	GZ_SYSTEM_EXPORT virtual gzBool quitOnClose();	// return TRUE if quit app on close

	GZ_SYSTEM_EXPORT virtual gzVoid onNotify(gzNotifyManager * /*master*/,gzRefPointer<gzNotifyMessage> & /*data*/,gzUInt64 /*senderClass*/) override {};
	
	//--------- External Syncronized rendering ---------------------

	GZ_SYSTEM_EXPORT gzVoid	setExternalSwapEvent(gzEvent* swapEvent);	
	GZ_SYSTEM_EXPORT gzVoid	setExternalRenderEvent(gzEvent* renderEvent);	

	GZ_SYSTEM_EXPORT gzRefPointer<gzEvent>	getExternalSwapEvent();	
	GZ_SYSTEM_EXPORT gzRefPointer<gzEvent>	getExternalRenderEvent();	

	GZ_SYSTEM_EXPORT gzVoid	setMaxSwapWaitTime(gzDouble seconds);
	GZ_SYSTEM_EXPORT gzVoid	setMaxRenderWaitTime(gzDouble seconds);

	GZ_SYSTEM_EXPORT gzWindowContext getWindowContext();
	GZ_SYSTEM_EXPORT gzDeviceContext getDeviceContext();
    
    GZ_SYSTEM_EXPORT gzBool rebuildRenderContext();

	GZ_SYSTEM_EXPORT gzBool allowMultiThreadRender(gzBool on);
	
private:

	GZ_SYSTEM_EXPORT gzVoid setupDefaultSettings(gzBool hasParent , gzDeviceContext dc);

protected:

#ifdef GZ_WINDOWS // ------------------  GZ_WINDOWS ---------------------------------
		
	friend LRESULT CALLBACK GWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:

	GZ_SYSTEM_EXPORT gzVoid routeToParentWindowProc( gzBool=FALSE );

protected:

	GZ_SYSTEM_EXPORT virtual LRESULT defaultWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	WNDPROC			m_parentWindowProc;

	gzBool			m_routeToWindowProc;

	UINT_PTR		m_timer;

	DEVMODE			*m_saveMode;
	DEVMODE			*m_devMode;

#elif defined GZ_GLX
// ------------------------ UNIX -----------------------------------
	
	static gzVoid initgl( gzWindowHandle w,  XtPointer clientData, XtPointer callData);
	static gzVoid keyEvent( gzWindowHandle w,  XtPointer clientData, XtPointer callData);
	static gzVoid refresh( gzWindowHandle w,  XtPointer clientData, XtPointer callData);
	static gzVoid timer( XtPointer clientData , XtIntervalId *id );
	static gzVoid generalEventHandler( gzWindowHandle w , XtPointer clientData , XEvent *event , Boolean *continueDispatch );
    
	static Atom s_MotifHintsAtom;

	XtIntervalId			m_timer;

#endif // ------------------------ COMMON ---------------------------------

	// Mouse vars
	gzInt32XY				m_mouse;

	gzUInt32				m_hasCapture;
	gzUInt32				m_hideMouse;

	gzWindowHandle			m_handle;			// Handle to main window control

	gzWindowHandle			m_parent;			// Handle to parent window or parent housing

	// Vital context info

	gzWindowContext			m_winContext;
	gzDeviceContext			m_deviceContext;

	// Size etc...

	gzUInt32				m_screen_width;
	
	gzUInt32XY				m_size;
	gzInt32XY				m_position;

	gzRefPointer<gzGraphicsFormat>	m_format;

	gzBool					m_doOutput;
	gzBool					m_doQuitOnClose;

	gzBool					m_createdParentHandle;		// True if parent handle is create by us
	gzBool					m_createdHandle;			// True if our handle is create by us
	gzBool					m_createdWinContext;		// True if winContext != handle and winContext is create by us
	gzBool					m_isInputProvider;			// True if generate key input from window
	gzBool					m_showDynamicLoadProgress;	// True if show the dynamic load progress	

	gzBool					m_inRefresh:1;	// Are we in refresh
	
	// ExtSync

	gzRefPointer<gzEvent>	m_externalRenderEvent;		

	gzRefPointer<gzEvent>	m_externalSwapEvent;

	gzDouble				m_maxRenderWaitTime;

	gzDouble				m_maxSwapWaitTime;

	// statics
	
	GZ_SYSTEM_EXPORT static gzList<gzWindow>	s_globalWindowList;

	static gzMutex								s_globalLock;
	
	static  gzWindowCreator						s_defaultCreator;

};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzWindow);

//******************************************************************************
// Function	: gzWindow * gzCreatePerformanceWindow
//									
// Purpose  : Create a performance dump window that displays perf section info
//									
// Params   :	const gzArray<gzString> & sections	- array of section names
//				
//				gzUInt32 iterations					- number of iterations before reset
//										
// Result	: -
//										
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040414	Created release 
//									
//******************************************************************************

//! Utility to create a performance dump window
/*! Add names to the sections array. The utility will then create a performance dump window
 that will display info about average performance of the sections for default 100 iterations */

GZ_SYSTEM_EXPORT gzWindow * gzCreatePerformanceWindow(const gzArray<gzString> &sections=gzArray<gzString>(0),gzBool showAllocMem=FALSE , gzUInt16 iterations=100);

#endif // __GZ_WINDOW_H__






