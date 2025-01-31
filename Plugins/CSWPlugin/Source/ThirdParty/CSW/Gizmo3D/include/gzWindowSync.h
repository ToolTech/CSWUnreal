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
// File			: gzWindowSync.h
// Module		: 
// Description	: Class definition of the gzWindowSync class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.211
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
#ifndef __GZ_WINDOW_SYNC_H__
#define __GZ_WINDOW_SYNC_H__

/*!	\file 
	\brief Base definitions of a Gizmo3D gzWindowSync

*/

#include "gzThread.h"
#include "gzNetwork.h"

class gzWindow;		// Forward declaration

//******************************************************************************
// Class	: gzWindowSync
//									
// Purpose  : Syncronizes multiple rendering windows
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
class gzWindowSync : public gzThread
{
public:

	GZ_SYSTEM_EXPORT gzWindowSync(gzUInt32 renderID=0,gzUInt32 appID=0,gzUInt16 portID=2537);

	GZ_SYSTEM_EXPORT virtual ~gzWindowSync();

	GZ_SYSTEM_EXPORT gzVoid addWindow(gzWindow *window);

	GZ_SYSTEM_EXPORT gzVoid removeWindow(gzWindow *window);

protected:

	GZ_SYSTEM_EXPORT virtual gzVoid process();

private:

	gzRefPointer<gzEvent>	m_renderEvent;

	gzRefPointer<gzEvent>	m_swapEvent;

	gzSocket				*m_socket;

	gzUInt32					m_renderID;

	gzUInt32					m_appID;

	gzUInt16				m_portID;

	gzRefList<gzWindow>		m_windowList;

	gzArray<gzUByte>		m_buffer;
};

//******************************************************************************
// Class	: gzWindowSyncControl
//									
// Purpose  : Controls Syncronization for multiple rendering windows
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
class gzWindowSyncControl : public gzThread
{
public:

	GZ_SYSTEM_EXPORT gzWindowSyncControl(gzUInt32 appID=0,gzUInt16 portID=2537);

	GZ_SYSTEM_EXPORT virtual ~gzWindowSyncControl();
		
	GZ_SYSTEM_EXPORT gzVoid swapBuffers();

	GZ_SYSTEM_EXPORT gzVoid startRender(const gzDouble &time=0);

protected:

	GZ_SYSTEM_EXPORT virtual gzVoid process();

private:

	gzSocket				*m_socket;

	gzUInt32					m_appID;

	gzUInt16				m_portID;

	gzArray<gzUByte>		m_buffer;

};

#endif // __GZ_WINDOW_SYNC_H__






