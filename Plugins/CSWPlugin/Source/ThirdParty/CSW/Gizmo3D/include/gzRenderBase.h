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
// File			: gzRenderBase.h
// Module		: 
// Description	: Class definition of the gzRenderBase class types
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
// AMO	000903	Created file 	
// AMO	111111	Added generic virtual refresh to a renderbase to be routed to specific imp	(2.5.32)
// CAE	120201	Removed faulty signature setDepthFunc and setClearDepth in gzRenderBase		(2.6.2)
//
//******************************************************************************
#ifndef __GZ_RENDER_BASE_H__
#define __GZ_RENDER_BASE_H__

/*!	\file 
	\brief Basic Settings for all renderers

*/

#include "gzContext.h"
#include "gzCamera.h"
#include "gzGraphicsFormat.h"

//******************************************************************************
// Class	: gzActiveRenderContext
//									
// Purpose  : Virtual Base Interface class for activating and using a rendering context;
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	120216	Created 
//									
//******************************************************************************
class gzActiveRenderContext : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzActiveRenderContext();

	GZ_GRAPH_EXPORT virtual ~gzActiveRenderContext();

	GZ_GRAPH_EXPORT gzBool	pushCurrentContext(gzContext *newContext);

	GZ_GRAPH_EXPORT gzBool	popCurrentContext();

	GZ_GRAPH_EXPORT	virtual gzBool	activate()=0;

	GZ_GRAPH_EXPORT	virtual gzBool	deactivate()=0;

	GZ_GRAPH_EXPORT	virtual gzVoid	swapBuffers(){};

	GZ_GRAPH_EXPORT	virtual gzVoid	setSwapInterval(gzInt32 interval=1);

	GZ_GRAPH_EXPORT virtual gzVoid *getSymbol(const gzString &symbolName)=0;

	GZ_GRAPH_EXPORT virtual gzString getPlatformExtensions()=0;

	GZ_GRAPH_EXPORT virtual gzBool initializeEngine()=0;
    
    GZ_GRAPH_EXPORT virtual gzVoid destroy()=0;

	// ---------- Active Render Context factory -------------------------------

	GZ_GRAPH_EXPORT static gzVoid	installFactory(gzActiveRenderContext *instance);

	GZ_GRAPH_EXPORT static gzVoid	unInstallFactory();

	GZ_GRAPH_EXPORT static gzBool	hasFactory();

	GZ_GRAPH_EXPORT static gzActiveRenderContext *	createActiveRenderContext(gzContext *context,gzGraphicsFormat *format,gzVoid *param1=nullptr,gzVoid *param2=nullptr,gzVoid *param3=nullptr,gzVoid *param4=nullptr,gzVoid *param5=nullptr);

	GZ_GRAPH_EXPORT	virtual gzActiveRenderContext* create(gzContext *context,gzGraphicsFormat *format,gzVoid *param1,gzVoid *param2,gzVoid *param3,gzVoid *param4,gzVoid *param5) const=0;

	// Create parameters
	// Win32	: param1=HWND				, param2=HDC	
	// GLX		: param1=Display * 
	// Android	: param1=ANativeWindow *
	// iOS		: param1=__bridge gzWindow_

	GZ_GRAPH_EXPORT	virtual gzBool getParams(gzVoid *param1=nullptr,gzVoid *param2=nullptr,gzVoid *param3=nullptr,gzVoid *param4=nullptr,gzVoid *param5=nullptr) const=0;
	GZ_GRAPH_EXPORT	virtual gzBool setParams(gzVoid *param1=nullptr,gzVoid *param2=nullptr,gzVoid *param3=nullptr,gzVoid *param4=nullptr,gzVoid *param5=nullptr) = 0;

	// Get/Set paramters for non null params adress
	// Win32	: param1=HWND			, param2=HDC			, param3=HGLRC
	// GLX		: param1=Display *		, param2=XVisualInfo *	, param3=GLXContext		, param4=Window
	// Android	: param1=ANativeWindow *, param2=EGLDisplay *	, param3=EGLContext *	, param4=EGLSurface *

private:

	gzThreadData<gzQueue<gzContextPtr> >		m_contextStack;

	static	gzRefPointer<gzActiveRenderContext>	s_factoryInstance;
	static	gzMutex								s_factoryLocker;
};

GZ_DECLARE_REFPTR(gzActiveRenderContext);

//******************************************************************************
// Class	: gzRenderBase
//									
// Purpose  : Base class for rendering of a scene graph to a target
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990607	Created 
//									
//******************************************************************************
class gzRenderBase : public gzObject
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzRenderBase();

	GZ_GRAPH_EXPORT virtual ~gzRenderBase();

	GZ_GRAPH_EXPORT virtual gzBool refresh()=0;	//!< Route this refresh to specific refresh in subclass

	GZ_GRAPH_EXPORT virtual gzVoid onPreRender(gzContext *context, gzUInt32 size_x , gzUInt32 size_y);
	GZ_GRAPH_EXPORT virtual gzVoid onPostRender(gzContext *context, gzUInt32 size_x , gzUInt32 size_y);
	GZ_GRAPH_EXPORT virtual gzVoid onInitContext(gzContext *context);

	GZ_GRAPH_EXPORT gzVoid		setBackground( gzFloat red , gzFloat green , gzFloat blue , gzFloat alpha=1.0f );
	GZ_GRAPH_EXPORT gzVoid		setBackground( const gzVec4& color );
	GZ_GRAPH_EXPORT gzVec4		getBackground();

	GZ_GRAPH_EXPORT gzVoid		setContext( gzContext *context );
	GZ_GRAPH_EXPORT gzContext	*getContext() const;

	GZ_GRAPH_EXPORT virtual gzVoid render(gzContext *context, gzUInt32 size_x,gzUInt32 size_y,gzUInt32 max_width, gzTraverseAction *action);

	GZ_GRAPH_EXPORT gzDouble	getFrameRate();

	//! Override current rendertime
	GZ_GRAPH_EXPORT gzVoid		setForcedRenderTime(const gzDouble &renderTime=0.0);

	//! Relative offset of viewport -1 to +1. Larger numbers are treated as absolute pixel values
	GZ_GRAPH_EXPORT gzVoid		setViewportOffset(gzFloat x , gzFloat y);

	//! Relative scale of viewport 0 to +1. Larger numbers are treated as absolute pixel values
	GZ_GRAPH_EXPORT gzVoid		setViewportScale(gzFloat sx , gzFloat sy);

	GZ_GRAPH_EXPORT gzVoid		useFinish(gzBool active=FALSE);

	//! Updated camera interface to allow virtual callback
	GZ_GRAPH_EXPORT virtual gzVoid setCamera(const gzCameraPtr& camera);
	GZ_GRAPH_EXPORT virtual const gzCameraPtr &getCamera() const;

	GZ_PROPERTY_EXPORT(gzActiveRenderContextPtr,	RenderContext,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool,						ClearBufferColor,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,						ClearBufferDepth,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,						ClearBufferStencil,		GZ_GRAPH_EXPORT);


	GZ_PROPERTY_EXPORT(gzFloat,						ClearDepth,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzEnum,						DepthFunc,				GZ_GRAPH_EXPORT);

protected:

	gzDouble				m_lastFrameTime;
	gzUInt32				m_frameCount;
	gzDouble				m_frameRate;

	gzFloat					m_backColor_red;
	gzFloat					m_backColor_green;
	gzFloat					m_backColor_blue; 
	gzFloat					m_backColor_alpha;

	gzFloat					m_refreshRate;


	gzFloatXY				m_viewportOffset;

	gzFloatXY				m_viewportScale;

	gzRefPointer<gzContext>	m_context;

	//---------------- graph members ----------------------------

private:

	gzBool					m_hasInitContext;

	gzBool					m_useFinish;

	gzDouble				m_forceRenderTime;

	gzCameraPtr				m_camera;
};


class gzAudioRenderInterface : public gzRenderBase
{
public:
	GZ_GRAPH_EXPORT gzAudioRenderInterface(){};
	GZ_GRAPH_EXPORT ~gzAudioRenderInterface(){};
	
	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const=0;
	
	// ---------- Image rendering factory -------------------------------
	
	GZ_GRAPH_EXPORT static gzVoid	installFactory(gzAudioRenderInterface *instance);
	
	GZ_GRAPH_EXPORT static gzVoid	unInstallFactory();
	
	GZ_GRAPH_EXPORT static gzBool	hasFactory();
	
	GZ_GRAPH_EXPORT static gzAudioRenderInterface *	getAudioRender();

private:
	
	static	gzRefPointer<gzAudioRenderInterface>	s_factoryInstance;
	static	gzMutex									s_factoryLocker;
	
	
};

#endif // __GZ_RENDER_BASE_H__
