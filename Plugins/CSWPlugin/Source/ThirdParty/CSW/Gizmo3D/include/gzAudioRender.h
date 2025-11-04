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
// File			: gzAudioRender.h
// Module		: 
// Description	: Class definition of the gzAudioRender class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.283
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
// ZMX	101124	Created file 	
//
//******************************************************************************
#ifndef __GZ_AUDIO_RENDER_H__
#define __GZ_AUDIO_RENDER_H__

/*!	\file 
 \brief Base definitions of a Gizmo3D Audio Renderer
 
 */

#include "gzBase.h"
#include "gzRenderBase.h"

#include "gzAudioAbstractionLayer.h"
#include "gzWindow.h"

//******************************************************************************
// Class	: gzAudioRender
//									
// Purpose  : System dependant implementation of a AudioRenderInterface
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000903	Created 
//									
//******************************************************************************


class gzAudioRender : public gzAudioRenderInterface
{
public:
	
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_SYSTEM_EXPORT);	// typed interface
	
	GZ_SYSTEM_EXPORT gzAudioRender( gzString devicename, gzUInt32 samplerate, gzUInt32 channels );
	
	GZ_SYSTEM_EXPORT gzAudioRender( const gzAudioRender &copy);
	
	GZ_SYSTEM_EXPORT virtual ~gzAudioRender();
	
	GZ_SYSTEM_EXPORT gzUInt32 getAudioDataSize();
	GZ_SYSTEM_EXPORT gzUByte * getAudioData();
	GZ_SYSTEM_EXPORT gzUInt32 getAudioData(gzUInt32 wantedSize, gzUByte *& ptr); // Returns the number of bytes actually retrieved

	GZ_SYSTEM_EXPORT virtual	gzBool	refresh() override; // Route to render audio
    GZ_SYSTEM_EXPORT virtual	gzBool	renderAudio();
	
	//--------- some virtual convenience callbacks -------------
	
	GZ_SYSTEM_EXPORT virtual gzReference* clone() const override;
	
protected:

	gzString		m_device_name;
	gzAudioDevice * m_device;

	gzUInt32		m_samplerate;
	gzUInt32		m_channels;

	gzUByte *		m_buffer;
	gzUInt32		m_buffersize;
	gzUInt32		m_bufferpos;
	
    gzUByte *		m_tempbuffer;
	gzUInt32		m_tempsize;
};

GZ_DECLARE_REFPTR(gzAudioRender);

#endif // __GZ_AUDIO_RENDER_H__
