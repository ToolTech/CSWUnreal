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
// File			: gzViewController.h
// Module		: 
// Description	: Class definition of view controller classes
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
// AMO	011026	Created file 	
//
//******************************************************************************
#ifndef __GZ_VIEW_CONTROLLER_H__
#define __GZ_VIEW_CONTROLLER_H__

#include "gzThread.h"
#include "gzInput.h"
#include "gzCamera.h"


/*!	\file 
	\brief Basic view controllers


*/

enum gzViewControlMovements
{
	GZ_VIEWCONTROL_MOVE_FORWARD,
	GZ_VIEWCONTROL_MOVE_BACKWARD,
	GZ_VIEWCONTROL_MOVE_LEFT,
	GZ_VIEWCONTROL_MOVE_RIGHT,
	GZ_VIEWCONTROL_MOVE_UP,
	GZ_VIEWCONTROL_MOVE_DOWN,
	GZ_VIEWCONTROL_ROTATE_RIGHT,
	GZ_VIEWCONTROL_ROTATE_LEFT,
	GZ_VIEWCONTROL_ROTATE_UP,
	GZ_VIEWCONTROL_ROTATE_DOWN,
	GZ_VIEWCONTROL_TILT_RIGHT,
	GZ_VIEWCONTROL_TILT_LEFT,
	GZ_VIEWCONTROL_ACCELLERATE,
	GZ_VIEWCONTROL_FOCUS,
	GZ_VIEWCONTROL_SIZE			// Don't touch
} ;

class gzSimpleMouseViewControl : public gzInputInterface , public gzThreadTicker
{
public:

	GZ_SYSTEM_EXPORT gzSimpleMouseViewControl(gzCamera *camera);

	GZ_SYSTEM_EXPORT virtual ~gzSimpleMouseViewControl();

	GZ_SYSTEM_EXPORT virtual gzBool onKey(gzKeyValue key , gzKeyState keystate , const gzInt32XY &mousePos , const gzInt32XY &centerMousePos , gzTypeInterface *sender) override;
	GZ_SYSTEM_EXPORT virtual gzVoid onMouseMove(const gzInt32XY &mousePos , const gzInt32XY &centerMousePos , gzTypeInterface *sender) override;
	GZ_SYSTEM_EXPORT virtual gzVoid onMouseWheel(const gzInt32 &delta , const gzInt32XY &mousePos , const gzInt32XY &centerMousePos , gzTypeInterface *sender) override;
	GZ_SYSTEM_EXPORT virtual gzVoid onKeyEvaluation() override;
	GZ_SYSTEM_EXPORT virtual gzVoid onKeyFocus(gzBool gotKeyFocus,gzTypeInterface *sender) override;


	GZ_SYSTEM_EXPORT virtual gzVoid onTick() override;

	GZ_SYSTEM_EXPORT gzKeyValue mapKey(gzViewControlMovements movement,gzKeyValue newKeyValue);

	GZ_SYSTEM_EXPORT gzVoid setSpeed(gzDouble speed);

	GZ_SYSTEM_EXPORT gzVoid setRotationSpeed(gzFloat rotspeed);

	//! Define if the system shall use Head up y axis
	GZ_PROPERTY_EXPORT(gzBool,		HeadUp,				GZ_SYSTEM_EXPORT);
	
	//! Proportional movement according to mouse offset
	GZ_PROPERTY_EXPORT(gzBool,		Proportional,		GZ_SYSTEM_EXPORT);

	//! Proportional movement according to mouse offset
	GZ_PROPERTY_EXPORT(gzBool,		InvertedMouse,		GZ_SYSTEM_EXPORT);

protected:

	gzRefPointer<gzCamera>	m_camera;

	gzDouble				m_speed;
	gzFloat					m_rotSpeed;
	gzFloat					m_mouseSpeed;

	gzBool					m_forward	:1;
	gzBool					m_backward	:1;
	gzBool					m_left		:1;
	gzBool					m_right		:1;
	gzBool					m_up		:1;
	gzBool					m_down		:1;

	gzBool					m_rot_right	:1;
	gzBool					m_rot_left	:1;
	gzBool					m_rot_up	:1;
	gzBool					m_rot_down	:1;
	gzBool					m_rot_tilt_r:1;
	gzBool					m_rot_tilt_l:1;

	gzBool					m_inMouseMove:1;

	gzBool					m_accellerate:1;

	gzInt32XY				m_mousePos;

	gzInt32XY				m_mouseCenterPos;

	gzDouble				m_lastSystemTick;

	gzDouble				m_lastStepTime;

	gzArray<gzKeyValue>		m_keyValueMapping;
};

#endif // __GZ_VIEW_CONTROLLER_H__






