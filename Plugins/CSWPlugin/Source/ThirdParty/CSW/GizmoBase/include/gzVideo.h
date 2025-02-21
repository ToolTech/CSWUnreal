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
// File			: gzVide.h
// Module		: gzBase
// Description	: Class definition of the gzVideo class
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.223
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
// AMO	060630	Created file 	
// TCL	121219	Added gzVideoServiceInterface							(2.6.18)
//
//******************************************************************************
#ifndef __GZ_VIDEO_H__
#define __GZ_VIDEO_H__

/*!	\file 
	\brief Video utilites (bitmaps)

*/

#include "gzImage.h"

const gzUInt32 GZ_INVALID_FRAME=0xffffffffUL;	//!< Invalid frame set by reset

class gzVideoControlInterface
{
public:

	virtual gzVoid updateFrame(gzUInt32 frame)=0;

	virtual gzBool skipFrame(gzUInt32 frame)=0;

	virtual gzBool forceFrame(gzUInt32 frame)=0;

	virtual gzBool discardFrame(gzUInt32 frame)=0;

	virtual gzDouble getCurrentTime()=0;

	virtual gzUInt64 getCurrentTimeStamp()=0;

	virtual gzDouble getStartReceiveTime()=0;

	virtual gzBool close(gzUInt32 msWait=0)=0;
};

typedef gzVideoControlInterface * gzVideoControlInterfacePtr;

const gzString GZ_VIDEO_CONTROL_INTERFACE="gzVideoControlInterface";

class gzVideoProgressInterface
{
public:

	virtual gzVoid saveProgress(gzUByte percentage)=0;
	virtual gzBool abort()=0;
};

typedef gzVideoProgressInterface * gzVideoProgressInterfacePtr;

const gzString GZ_VIDEO_PROGRESS_INTERFACE="gzVideoProgressInterface";

class gzVideoServiceInterface
{
public:

    virtual gzVoid onEnd()=0;
};

typedef gzVideoServiceInterface * gzVideoServiceInterfacePtr;

const gzString GZ_VIDEO_SERVICE_INTERFACE="gzVideoServiceInterface";

class gzVideo : public gzImage
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// typed interface

	GZ_BASE_EXPORT gzVideo(const gzString & name=GZ_EMPTY_STRING);
	GZ_BASE_EXPORT virtual ~gzVideo(){};
	
	GZ_BASE_EXPORT gzVoid	setTime(const gzDouble &seconds);
	GZ_BASE_EXPORT gzBool	setFrame(gzUInt32 frameNumber,gzBool updateStartTime=FALSE);

	GZ_BASE_EXPORT gzVoid	start(const gzDouble &startTime=0);
	GZ_BASE_EXPORT gzVoid	stop();

	//! Return current frame index
	GZ_BASE_EXPORT gzUInt32	getCurrentFrame();

	GZ_BASE_EXPORT gzUInt32	updateFrameCount();

	//! Callback activated upon new frame request
	GZ_BASE_EXPORT virtual	gzBool onFrame(gzUInt32 /*frame*/){ return FALSE; }
	GZ_BASE_EXPORT virtual	gzVoid onStart(const gzDouble & /*startTime*/){};
	GZ_BASE_EXPORT virtual	gzVoid onReset(const gzDouble & /*startTime*/){};
	GZ_BASE_EXPORT virtual	gzVoid onStop(){};
	GZ_BASE_EXPORT virtual	gzVoid onEnd(){};
			
	
	GZ_BASE_EXPORT virtual	gzUByte getVideoComponents();

	GZ_BASE_EXPORT gzVoid reset();		// Issue a reset of stream
	GZ_BASE_EXPORT gzVoid end();		// Issue a end of stream
	

	GZ_BASE_EXPORT virtual gzBool enableVideoThread(gzBool /*videoThread*/=TRUE){ return FALSE; }
	GZ_BASE_EXPORT virtual gzBool enableAudioThread(gzBool /*audioThread*/=TRUE){ return FALSE; }
	GZ_BASE_EXPORT virtual gzBool hasVideoThread() { return FALSE; }
	GZ_BASE_EXPORT virtual gzBool hasAudioThread() { return FALSE; }
	
	GZ_PROPERTY_EXPORT(		gzUInt32,					FrameCount			,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzUInt32,					MaxLagFrames		,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzDouble,					FrameDuration		,GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzDouble,					RealTimeStartDiff	,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzVideoControlInterfacePtr, ControlInterface	,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzVideoProgressInterfacePtr,ProgressInterface	,GZ_BASE_EXPORT);
    GZ_PROPERTY_EXPORT(		gzVideoServiceInterfacePtr, ServiceInterface	,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzDouble,					FramesPerSecond		,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzString,					VideoInfo			,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzString,					AudioInfo			,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzBool,						RestartOnEnd		,GZ_BASE_EXPORT);

	// ---- Serializing --------------------------------
	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

	// ---- Clone --------------------------------------
	GZ_BASE_EXPORT virtual gzReference *clone() const override;

private:

	gzDouble	m_startTime;
	gzBool		m_running;
	gzBool		m_pendingEnd;

	gzUInt32		m_currentFrame;
};

#endif //__GZ_VIDEO_H__


