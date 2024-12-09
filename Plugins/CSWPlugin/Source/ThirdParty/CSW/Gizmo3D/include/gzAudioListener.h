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
// File			: gzAudioListener.h
// Module		: 
// Description	: Class definition of the gzAudioListener class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.201
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
// AMO	060801	Created file 	
//
//******************************************************************************
#ifndef __GZ_AUDIO_LISTENER_H__
#define __GZ_AUDIO_LISTENER_H__

/*!	\file 
	\brief Base definitions for audio listener nodes classes

*/

#include "gzNode.h"
#include "gzCamera.h"

//******************************************************************************
// Class	: gzAudioListener
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	060801	Created 
//									
//******************************************************************************
class gzAudioListener : public gzNode
{
public:
	GZ_GRAPH_EXPORT gzAudioListener(const gzString &name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzAudioListener(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- gzAudioListener commands ------------------------------

	GZ_GRAPH_EXPORT gzVoid	followCamera(gzCamera *camera,gzBool updateCameraScene=TRUE);

	GZ_GRAPH_EXPORT gzBool	setPosition(const gzVec3 &position , gzBool immediate=FALSE);
	GZ_GRAPH_EXPORT gzBool	setOrientation(gzFloat heading,gzFloat pitch,gzFloat roll,gzBool immediate=FALSE);
	GZ_GRAPH_EXPORT gzBool	setDirection(const gzVec3 &targetvector, gzFloat roll , const gzVec3 &up=gzVec3(0,1,0),gzBool immediate=FALSE);

	GZ_GRAPH_EXPORT gzBool	setGain(gzFloat gain=1.0f, gzBool immediate=FALSE);
	

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

protected:

	gzRefPointer<gzCamera>	m_followCam;

	gzVec3					m_position;
	gzVec3					m_orientation;
	gzFloat					m_gain;
};



#endif // __GZ_AUDIO_LISTENER_H__

