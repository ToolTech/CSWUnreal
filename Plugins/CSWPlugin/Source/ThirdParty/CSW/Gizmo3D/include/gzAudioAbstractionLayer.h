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
// File			: gzAudioAbstractionLayer.h
// Module		: gzGraph
// Description	: Class implementation of the AAL class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.275
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
// AMO	990103	Created file 	
//
//******************************************************************************

#ifndef __GZ_AUDIO_ABSTRACTION_LAYER_H__
#define __GZ_AUDIO_ABSTRACTION_LAYER_H__

/*!	\file 
	\brief Low level API bridge between Gizmo3D low level API and the system API

  The user can select the type of system interface he wishes to use. E.g OpenGL or DirectX

*/

#include "gzBase.h"

// forward declaration
typedef struct gzAudioDevice_struct		gzAudioDevice;
typedef struct gzAudioContext_struct	gzAudioContext;


//--------------------- gzAudioAbstractionLayer -------------------------------------------

class GZ_GRAPH_EXPORT gzAudioAbstractionLayer
{
public:

	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioEnable)( gzEnum capability );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioDisable)( gzEnum capability ); 
	static	gzBool			(GZ_CALLBACK_C *	imp_gzAudioIsEnabled)( gzEnum capability ); 
	static	const gzChar *	(GZ_CALLBACK_C *	imp_gzAudioGetString)( gzEnum param );
	static	const gzChar *	(GZ_CALLBACK_C *	imp_gzAudioContextGetString)( void * device, gzEnum param );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetBooleanv)( gzEnum param, gzBool* data );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetIntegerv)( gzEnum param, gzInt32* data );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetFloatv)( gzEnum param, gzFloat* data );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetDoublev)( gzEnum param, gzDouble* data );
	static	gzBool			(GZ_CALLBACK_C *	imp_gzAudioGetBoolean)( gzEnum param );
	static	gzInt32			(GZ_CALLBACK_C *	imp_gzAudioGetInteger)( gzEnum param );
	static	gzFloat			(GZ_CALLBACK_C *	imp_gzAudioGetFloat)( gzEnum param );
	static	gzDouble		(GZ_CALLBACK_C *	imp_gzAudioGetDouble)( gzEnum param );
	static	gzEnum			(GZ_CALLBACK_C *	imp_gzAudioGetError)();
	static	gzEnum			(GZ_CALLBACK_C *	imp_gzAudioGetEnumValue)( const gzChar* ename );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioListenerf)( gzEnum param, gzFloat value );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioListener3f)( gzEnum param, gzFloat value1, gzFloat value2, gzFloat value3 );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioListenerfv)( gzEnum param, const gzFloat* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioListeneri)( gzEnum param, gzInt32 value );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioListener3i)( gzEnum param, gzInt32 value1, gzInt32 value2, gzInt32 value3 );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioListeneriv)( gzEnum param, const gzInt32* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetListenerf)( gzEnum param, gzFloat* value );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetListener3f)( gzEnum param, gzFloat *value1, gzFloat *value2, gzFloat *value3 );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetListenerfv)( gzEnum param, gzFloat* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetListeneri)( gzEnum param, gzInt32* value );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetListener3i)( gzEnum param, gzInt32 *value1, gzInt32 *value2, gzInt32 *value3 );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetListeneriv)( gzEnum param, gzInt32* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGenSources)( gzUInt32 n, gzUInt32* sources ); 
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioDeleteSources)( gzUInt32 n, const gzUInt32* sources );
	static	gzBool			(GZ_CALLBACK_C *	imp_gzAudioIsSource)( gzUInt32 sid ); 
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourcef)( gzUInt32 sid, gzEnum param, gzFloat value); 
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSource3f)( gzUInt32 sid, gzEnum param, gzFloat value1, gzFloat value2, gzFloat value3 );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourcefv)( gzUInt32 sid, gzEnum param, const gzFloat* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourcei)( gzUInt32 sid, gzEnum param, gzInt32 value); 
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSource3i)( gzUInt32 sid, gzEnum param, gzInt32 value1, gzInt32 value2, gzInt32 value3 );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourceiv)( gzUInt32 sid, gzEnum param, const gzInt32* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetSourcef)( gzUInt32 sid, gzEnum param, gzFloat* value );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetSource3f)( gzUInt32 sid, gzEnum param, gzFloat* value1, gzFloat* value2, gzFloat* value3);
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetSourcefv)( gzUInt32 sid, gzEnum param, gzFloat* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetSourcei)( gzUInt32 sid, gzEnum param, gzInt32* value );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetSource3i)( gzUInt32 sid, gzEnum param, gzInt32* value1, gzInt32* value2, gzInt32* value3);
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetSourceiv)( gzUInt32 sid, gzEnum param, gzInt32* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourcePlayv)( gzUInt32 ns, const gzUInt32 *sids );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourceStopv)( gzUInt32 ns, const gzUInt32 *sids );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourceRewindv)( gzUInt32 ns, const gzUInt32 *sids );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourcePausev)( gzUInt32 ns, const gzUInt32 *sids );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourcePlay)( gzUInt32 sid );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourceStop)( gzUInt32 sid );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourceRewind)( gzUInt32 sid );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourcePause)( gzUInt32 sid );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourceQueueBuffers)(gzUInt32 sid, gzUInt32 numEntries, const gzUInt32 *bids );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSourceUnqueueBuffers)(gzUInt32 sid, gzUInt32 numEntries, gzUInt32 *bids );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGenBuffers)( gzUInt32 n, gzUInt32* buffers );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioDeleteBuffers)( gzUInt32 n, const gzUInt32* buffers );
	static	gzBool			(GZ_CALLBACK_C *	imp_gzAudioIsBuffer)( gzUInt32 bid );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioBufferData)( gzUInt32 bid, gzEnum format, const gzVoid* data, gzUInt32 size, gzUInt32 freq );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioBufferf)( gzUInt32 bid, gzEnum param, gzFloat value);
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioBuffer3f)( gzUInt32 bid, gzEnum param, gzFloat value1, gzFloat value2, gzFloat value3 );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioBufferfv)( gzUInt32 bid, gzEnum param, const gzFloat* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioBufferi)( gzUInt32 bid, gzEnum param, gzInt32 value);
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioBuffer3i)( gzUInt32 bid, gzEnum param, gzInt32 value1, gzInt32 value2, gzInt32 value3 );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioBufferiv)( gzUInt32 bid, gzEnum param, const gzInt32* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetBufferf)( gzUInt32 bid, gzEnum param, gzFloat* value );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetBuffer3f)( gzUInt32 bid, gzEnum param, gzFloat* value1, gzFloat* value2, gzFloat* value3);
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetBufferfv)( gzUInt32 bid, gzEnum param, gzFloat* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetBufferi)( gzUInt32 bid, gzEnum param, gzInt32* value );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetBuffer3i)( gzUInt32 bid, gzEnum param, gzInt32* value1, gzInt32* value2, gzInt32* value3);
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioGetBufferiv)( gzUInt32 bid, gzEnum param, gzInt32* values );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioDopplerFactor)( gzFloat value );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioDopplerVelocity)( gzFloat value );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSpeedOfSound)( gzFloat value );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioDistanceModel)( gzEnum distanceModel );

	// context management

	static	gzAudioContext *(GZ_CALLBACK_C *	imp_gzAudioCreateContext)( gzAudioDevice *device, const gzInt32* attrlist );
	static	gzBool			(GZ_CALLBACK_C *	imp_gzAudioMakeContextCurrent)( gzAudioContext *context );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioProcessContext)( gzAudioContext *context );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioSuspendContext)( gzAudioContext *context );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioDestroyContext)( gzAudioContext *context );
	static	gzAudioContext *(GZ_CALLBACK_C *	imp_gzAudioGetCurrentContext)();
	static	gzAudioDevice *	(GZ_CALLBACK_C *	imp_gzAudioGetContextsDevice)( gzAudioContext *context );

	static	gzAudioDevice *	(GZ_CALLBACK_C *	imp_gzAudioOpenDevice)( const gzChar *devicename );
	static	gzBool			(GZ_CALLBACK_C *	imp_gzAudioCloseDevice)( gzAudioDevice *device );

	static	gzEnum			(GZ_CALLBACK_C *	imp_gzAudioDeviceGetError)( gzAudioDevice *device );
	static	gzEnum			(GZ_CALLBACK_C *	imp_gzAudioDeviceGetEnumValue)( gzAudioDevice *device, const gzChar *enumname );
	static	const gzChar *	(GZ_CALLBACK_C *	imp_gzAudioDeviceGetString)( gzAudioDevice *device, gzEnum param );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioDeviceGetIntegerv)( gzAudioDevice *device, gzEnum param, gzUInt32 size, gzInt32 *data );

	static	gzAudioDevice *	(GZ_CALLBACK_C *	imp_gzAudioCaptureOpenDevice)( const gzChar *devicename, gzUInt32 frequency, gzEnum format, gzUInt32 buffersize );
	static	gzBool			(GZ_CALLBACK_C *	imp_gzAudioCaptureCloseDevice)( gzAudioDevice *device );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioCaptureStart)( gzAudioDevice *device );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioCaptureStop)( gzAudioDevice *device );
	static	gzVoid			(GZ_CALLBACK_C *	imp_gzAudioCaptureSamples)( gzAudioDevice *device, gzVoid *buffer, gzUInt32 samples );
	static  gzVoid			(GZ_CALLBACK_C *	imp_gzAudioCaptureGetIntegerv)( gzAudioDevice *device, gzEnum param, gzInt32 size, gzInt32 * data);

	static gzString			(GZ_CALLBACK *		imp_gzAudioErrorDescription)(gzEnum error);
};

//#define GZ_DEBUG_AUDIO_API // To force API debugging
#define GZ_DEBUG_AUDIO_API_STOP		TRUE

// Definition of the API error macros
#ifdef GZ_DEBUG_AUDIO_API 
#define __gz_dbg_audio_api_start__	{ while(gzEnum error=gzAudioGetError()){GZTRACE("External Audio error:'%s' at line %ld in file %s",(const char *)gzAudioErrorDescription(error),__LINE__,__FILE__);while(GZ_DEBUG_AUDIO_API_STOP);}

#define __gz_dbg_audio_api_end__	; while(gzEnum error=gzAudioGetError()){GZTRACE("API Audio error:'%s' at line %ld in file %s",(const char *)gzAudioErrorDescription(error),__LINE__,__FILE__); while(GZ_DEBUG_AUDIO_API_STOP); } }
#else
#define __gz_dbg_audio_api_start__		
#define __gz_dbg_audio_api_end__		
#endif

// Function macro definitions


#define gzAudioErrorDescription(p1)				(gzAudioAbstractionLayer::imp_gzAudioErrorDescription)(p1)
#define gzAudioGetError()						(gzAudioAbstractionLayer::imp_gzAudioGetError)()

#define gzAudioEnable(p1)						__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioEnable)(p1)				__gz_dbg_audio_api_end__
#define gzAudioDisable(p1)						__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioDisable)(p1)				__gz_dbg_audio_api_end__
#define gzAudioisEnabled(p1)												(gzAudioAbstractionLayer::imp_gzAudioIsEnabled)(p1)				
#define gzAudioGetString(p1)												(gzAudioAbstractionLayer::imp_gzAudioGetString)(p1)				
#define gzAudioContextGetString(p1,p2)										(gzAudioAbstractionLayer::imp_gzAudioContextGetString)(p1,p2)				
#define gzAudioGetBooleanv(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetBooleanv)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioGetIntegerv(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetIntegerv)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioGetFloatv(p1,p2)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetFloatv)(p1,p2)			__gz_dbg_audio_api_end__
#define gzAudioGetDoublev(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetDoublev)(p1,p2)			__gz_dbg_audio_api_end__
#define gzAudioGetBoolean(p1)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetBoolean)(p1)			__gz_dbg_audio_api_end__
#define gzAudioGetInteger(p1)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetInteger)(p1)			__gz_dbg_audio_api_end__
#define gzAudioGetFloat(p1)						__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetFloat)(p1)				__gz_dbg_audio_api_end__
#define gzAudioGetDouble(p1)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetDouble)(p1)				__gz_dbg_audio_api_end__
#define gzAudioGetEnumValue(p1)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetEnumValue)(p1)			__gz_dbg_audio_api_end__
#define gzAudioListenerf(p1,p2)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioListenerf)(p1,p2)			__gz_dbg_audio_api_end__
#define gzAudioListener3f(p1,p2,p3,p4)			__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioListener3f)(p1,p2,p3,p4)	__gz_dbg_audio_api_end__
#define gzAudioListenerfv(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioListenerfv)(p1,p2)			__gz_dbg_audio_api_end__
#define gzAudioListeneri(p1,p2)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioListeneri)(p1,p2)			__gz_dbg_audio_api_end__
#define gzAudioListener3i(p1,p2,p3,p4)			__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioListener3i)(p1,p2,p3,p4)	__gz_dbg_audio_api_end__
#define gzAudioListeneriv(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioListeneriv)(p1,p2)			__gz_dbg_audio_api_end__
#define gzAudioGetListenerf(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetListenerf)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioGetListener3f(p1,p2,p3,p4)		__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetListener3f)(p1,p2,p3,p4)__gz_dbg_audio_api_end__
#define gzAudioGetListenerfv(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetListenerfv)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioGetListeneri(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetListeneri)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioGetListener3i(p1,p2,p3,p4)		__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetListener3i)(p1,p2,p3,p4)__gz_dbg_audio_api_end__
#define gzAudioGetListeneriv(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetListeneriv)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioGenSources(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGenSources)(p1,p2)			__gz_dbg_audio_api_end__
#define gzAudioDeleteSources(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioDeleteSources)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioIsSource(p1)						__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioIsSource)(p1)				__gz_dbg_audio_api_end__
#define gzAudioSourcef(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourcef)(p1,p2,p3)			__gz_dbg_audio_api_end__
#define gzAudioSource3f(p1,p2,p3,p4,p5)			__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSource3f)(p1,p2,p3,p4,p5)	__gz_dbg_audio_api_end__
#define gzAudioSourcefv(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourcefv)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioSourcei(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourcei)(p1,p2,p3)			__gz_dbg_audio_api_end__
#define gzAudioSource3i(p1,p2,p3,p4,p5)			__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSource3i)(p1,p2,p3,p4,p5)	__gz_dbg_audio_api_end__
#define gzAudioSourceiv(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourceiv)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioGetSourcef(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetSourcef)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioGetSource3f(p1,p2,p3,p4,p5)		__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetSource3f)(p1,p2,p3,p4,p5)__gz_dbg_audio_api_end__
#define gzAudioGetSourcefv(p1,p2,p3)			__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetSourcefv)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioGetSourcei(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetSourcei)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioGetSource3i(p1,p2,p3,p4,p5)		__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetSource3i)(p1,p2,p3,p4,p5)__gz_dbg_audio_api_end__
#define gzAudioGetSourceiv(p1,p2,p3)			__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetSourceiv)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioSourcePlayv(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourcePlayv)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioSourceStopv(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourceStopv)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioSourceRewindv(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourceRewindv)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioSourcePausev(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourcePausev)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioSourcePlay(p1)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourcePlay)(p1)			__gz_dbg_audio_api_end__
#define gzAudioSourceStop(p1)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourceStop)(p1)			__gz_dbg_audio_api_end__
#define gzAudioSourceRewind(p1)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourceRewind)(p1)			__gz_dbg_audio_api_end__
#define gzAudioSourcePause(p1)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourcePause)(p1)			__gz_dbg_audio_api_end__
#define gzAudioSourceQueueBuffers(p1,p2,p3)		__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourceQueueBuffers)(p1,p2,p3)__gz_dbg_audio_api_end__
#define gzAudioSourceUnqueueBuffers(p1,p2,p3)	__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSourceUnqueueBuffers)(p1,p2,p3)__gz_dbg_audio_api_end__
#define gzAudioGenBuffers(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGenBuffers)(p1,p2)			__gz_dbg_audio_api_end__
#define gzAudioDeleteBuffers(p1,p2)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioDeleteBuffers)(p1,p2)		__gz_dbg_audio_api_end__
#define gzAudioIsBuffer(p1)						__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioIsBuffer)(p1)				__gz_dbg_audio_api_end__
#define gzAudioBufferData(p1,p2,p3,p4,p5)		__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioBufferData)(p1,p2,p3,p4,p5)__gz_dbg_audio_api_end__
#define gzAudioBufferf(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioBufferf)(p1,p2,p3)			__gz_dbg_audio_api_end__
#define gzAudioBuffer3f(p1,p2,p3,p4,p5)			__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioBuffer3f)(p1,p2,p3,p4,p5)	__gz_dbg_audio_api_end__
#define gzAudioBufferfv(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioBufferfv)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioBufferi(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioBufferi)(p1,p2,p3)			__gz_dbg_audio_api_end__
#define gzAudioBuffer3i(p1,p2,p3,p4,p5)			__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioBuffer3i)(p1,p2,p3,p4,p5)	__gz_dbg_audio_api_end__
#define gzAudioBufferiv(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioBufferiv)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioGetBufferf(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetBufferf)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioGetBuffer3f(p1,p2,p3,p4,p5)		__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetBuffer3f)(p1,p2,p3,p4,p5)__gz_dbg_audio_api_end__
#define gzAudioGetBufferfv(p1,p2,p3)			__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetBufferfv)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioGetBufferi(p1,p2,p3)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetBufferi)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioGetBuffer3i(p1,p2,p3,p4,p5)		__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetBuffer3i)(p1,p2,p3,p4,p5)__gz_dbg_audio_api_end__
#define gzAudioGetBufferiv(p1,p2,p3)			__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioGetBufferiv)(p1,p2,p3)		__gz_dbg_audio_api_end__
#define gzAudioDopplerFactor(p1)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioDopplerFactor)(p1)			__gz_dbg_audio_api_end__
#define gzAudioDopplerVelocity(p1)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioDopplerVelocity)(p1)		__gz_dbg_audio_api_end__
#define gzAudioSpeedOfSound(p1)					__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioSpeedOfSound)(p1)			__gz_dbg_audio_api_end__
#define gzAudioDistanceModel(p1)				__gz_dbg_audio_api_start__	(gzAudioAbstractionLayer::imp_gzAudioDistanceModel)(p1)			__gz_dbg_audio_api_end__

// Context management

#define gzAudioCreateContext(p1,p2)				(gzAudioAbstractionLayer::imp_gzAudioCreateContext)(p1,p2)
#define gzAudioMakeContextCurrent(p1)			(gzAudioAbstractionLayer::imp_gzAudioMakeContextCurrent)(p1)
#define gzAudioProcessContext(p1)				(gzAudioAbstractionLayer::imp_gzAudioProcessContext)(p1)
#define gzAudioSuspendContext(p1)				(gzAudioAbstractionLayer::imp_gzAudioSuspendContext)(p1)
#define gzAudioDestroyContext(p1)				(gzAudioAbstractionLayer::imp_gzAudioDestroyContext)(p1)
#define gzAudioGetCurrentContext()				(gzAudioAbstractionLayer::imp_gzAudioGetCurrentContext)()
#define gzAudioGetContextsDevice(p1)			(gzAudioAbstractionLayer::imp_gzAudioGetContextsDevice)(p1)

#define gzAudioOpenDevice(p1)					(gzAudioAbstractionLayer::imp_gzAudioOpenDevice)(p1)
#define gzAudioCloseDevice(p1)					(gzAudioAbstractionLayer::imp_gzAudioCloseDevice)(p1)

#define gzAudioDeviceGetError(p1)				(gzAudioAbstractionLayer::imp_gzAudioDeviceGetError)(p1)
#define gzAudioDeviceGetEnumValue(p1,p2)		(gzAudioAbstractionLayer::imp_gzAudioDeviceGetEnumValue)(p1,p2)
#define gzAudioDeviceGetString(p1,p2)			(gzAudioAbstractionLayer::imp_gzAudioDeviceGetString)(p1,p2)
#define gzAudioDeviceGetIntegerv(p1,p2,p3,p4)	(gzAudioAbstractionLayer::imp_gzAudioDeviceGetIntegerv)(p1,p2,p3,p4)

#define gzAudioCaptureOpenDevice(p1,p2,p3,p4)	(gzAudioAbstractionLayer::imp_gzAudioCaptureOpenDevice)(p1,p2,p3,p4)
#define gzAudioCaptureCloseDevice(p1)			(gzAudioAbstractionLayer::imp_gzAudioCaptureCloseDevice)(p1)
#define gzAudioCaptureStart(p1)					(gzAudioAbstractionLayer::imp_gzAudioCaptureStart)(p1)
#define gzAudioCaptureStop(p1)					(gzAudioAbstractionLayer::imp_gzAudioCaptureStop)(p1)
#define gzAudioCaptureSamples(p1,p2,p3)			(gzAudioAbstractionLayer::imp_gzAudioCaptureSamples)(p1,p2,p3)
#define gzAudioCaptureGetIntegerv(p1,p2,p3,p4)  (gzAudioAbstractionLayer::imp_gzAudioCaptureGetIntegerv)(p1,p2,p3,p4)

#define GZ_CHECK_AUDIO_ENGINE_ERROR(x) {while (gzEnum audioerror=gzAudioEngine::hasValidEngine()?gzAudioGetError():(gzEnum)FALSE){gzString errStr = gzString::formatString("%s Audio Engine Error:%s at line %ld in file %s", x,gzAudioErrorDescription(audioerror), __LINE__, __FILE__);gzAudioEngine::pushEngineError(errStr);GZMESSAGE(GZ_MESSAGE_DEBUG, errStr);}}

#endif // __GZ_AUDIO_ABSTRACTION_LAYER_H__
