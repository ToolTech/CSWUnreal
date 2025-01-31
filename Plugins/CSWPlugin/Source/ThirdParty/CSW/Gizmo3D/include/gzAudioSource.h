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
// File			: gzAudioSource.h
// Module		: 
// Description	: Class definition of the gzAudioSource class
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
// AMO	060801	Created file 	
//
//******************************************************************************
#ifndef __GZ_AUDIO_SOURCE_H__
#define __GZ_AUDIO_SOURCE_H__

/*!	\file 
	\brief Base definitions for audio source nodes classes

*/

#include "gzNode.h"
#include "gzThread.h"


enum gzAudioSourceFormat
{
	GZ_AUDIO_SOURCE_FORMAT_MONO_8		=	GZ_AUDIO_FORMAT_MONO8,
	GZ_AUDIO_SOURCE_FORMAT_MONO_16		=	GZ_AUDIO_FORMAT_MONO16,
	GZ_AUDIO_SOURCE_FORMAT_STEREO_8		=	GZ_AUDIO_FORMAT_STEREO8,
	GZ_AUDIO_SOURCE_FORMAT_STEREO_16	=	GZ_AUDIO_FORMAT_STEREO16,
	GZ_AUDIO_SOURCE_FORMAT_INVALID,
};

enum gzAudioSourceState
{
	GZ_AUDIO_SOURCE_INITIAL=GZ_AUDIO_INITIAL,
	GZ_AUDIO_SOURCE_PLAYING=GZ_AUDIO_PLAYING,
	GZ_AUDIO_SOURCE_PAUSED=GZ_AUDIO_PAUSED,
	GZ_AUDIO_SOURCE_STOPPED=GZ_AUDIO_STOPPED,
	GZ_AUDIO_SOURCE_ERROR
};

//******************************************************************************
// Class	: gzAudioSource
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
class gzAudioSource : public gzNode
{
public:
	GZ_GRAPH_EXPORT gzAudioSource(const gzString &name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzAudioSource();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- gzAudioSource commands ------------------------------

	GZ_GRAPH_EXPORT gzBool addData(gzAudioSourceFormat format , gzVoid *data , gzUInt32 samples , gzUInt32 frequency , gzUByte stride=0);

	GZ_GRAPH_EXPORT gzBool play(const gzFloat &offset=0.0);
	GZ_GRAPH_EXPORT gzBool pause();
	GZ_GRAPH_EXPORT gzBool resume();
	GZ_GRAPH_EXPORT gzBool stop();

	GZ_GRAPH_EXPORT gzBool loop(gzBool on=FALSE);

	GZ_GRAPH_EXPORT gzAudioSourceState getAudioSourceState();

	// ---------- Synced control --------------------------------------

	GZ_GRAPH_EXPORT static	gzBool play(const gzRefList<gzAudioSource> &sources,const gzFloat &offset=0.0);
	GZ_GRAPH_EXPORT static	gzBool pause(const gzRefList<gzAudioSource> &sources);
	GZ_GRAPH_EXPORT static	gzBool resume(const gzRefList<gzAudioSource> &sources);
	GZ_GRAPH_EXPORT static	gzBool stop(const gzRefList<gzAudioSource> &sources);

	// ---------- Scene Graph or immediate commands -------------------

	GZ_GRAPH_EXPORT gzBool	setPosition(const gzVec3 &position , gzBool immediate=FALSE);
	GZ_GRAPH_EXPORT gzBool	setOrientation(gzFloat heading,gzFloat pitch,gzFloat roll,gzBool immediate=FALSE);
	GZ_GRAPH_EXPORT gzBool	setDirection(const gzVec3 &targetvector, gzFloat roll , const gzVec3 &up=gzVec3(0,1,0),gzBool immediate=FALSE);

	// ---------- Buffer management -----------------------------------

	GZ_GRAPH_EXPORT gzVoid cleanBuffers();

	//! Returns -1 for error, else number of buffers
	GZ_GRAPH_EXPORT gzInt32 getPendingBuffers();
	
	// ---------- Action Interface ------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

protected:

	GZ_GRAPH_EXPORT gzUInt32 init();

	gzUInt32	m_sourceID;
	gzVec3	m_position;
	gzVec3	m_orientation;
	
	gzDynamicArray<gzUByte>	m_buffer;

};

// ----------------------- gzAudioStreamPlayer -------------------------

class gzAudioStreamPlayer : public gzThreadTicker
{
public:

	GZ_GRAPH_EXPORT gzAudioStreamPlayer(gzAudioSource *leftSource,gzAudioSource *rightSource=nullptr);
	GZ_GRAPH_EXPORT virtual ~gzAudioStreamPlayer();

	GZ_PROPERTY_EXPORT(gzAudioSourceFormat,Format,GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzAudioSourceFormat,Frequency,GZ_GRAPH_EXPORT);

	GZ_GRAPH_EXPORT	gzVoid play();
	GZ_GRAPH_EXPORT gzVoid stop();

	GZ_GRAPH_EXPORT gzBool setStream(gzSerializeAdapter *adapter);

	GZ_GRAPH_EXPORT virtual gzVoid onTick();


private:

	gzRefPointer<gzAudioSource>			m_leftSource;
	gzRefPointer<gzAudioSource>			m_rightSource;
	gzRefPointer<gzReference>			m_extSoundManager;
	gzRefPointer<gzSerializeAdapter>	m_adapter;
	gzDynamicArray<gzUByte>				m_buffer;
};

#endif // __GZ_AUDIO_SOURCE_H__

