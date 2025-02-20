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
// File			: gzAudioEngine.h
// Module		: 
// Description	: Class definition of stub calls for AAL
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.222
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

#ifndef __GZ_AUDIO_ENGINE_H__
#define __GZ_AUDIO_ENGINE_H__

/*!	\file 
	\brief Bridge between Gizmo3D low level Audio API and system Audio API

*/


#include "gzBasicTypes.h"
#include "gzAudioAbstractionLayer.h"
#include "gzBase.h"

//! Audio Engine Types
/*! Initialise with gzAudioEngine::useEngine(xxx) before using any Gizmo3D Audio code */
enum gzAudioEngineType
{ 
	GZ_AUDIO_ENGINE_NOT_INIT		= -2 ,
	GZ_AUDIO_ENGINE_NONE			= -1 , 
	GZ_AUDIO_ENGINE_DEBUG			=  0 , 
	GZ_AUDIO_ENGINE_SOFTWARE		=  1 , 
	GZ_AUDIO_ENGINE_OPENAL			=  2 , 
	GZ_AUDIO_ENGINE_DIRECT_SOUND	=  3
} ;

const gzUByte GZ_MAX_AUDIO_ENGINES=10;

//-------------------- engine dependant implementations ------------------------

//******************************************************************************
// Class	: gzAudioEngine
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
class gzAudioEngine
{
public:

	/*

	// ------------------- extensions. Not basically supported by Engine --------------------

	GZ_GRAPH_EXPORT static  inline	gzBool	has_vertex_array()				{ return s_vertex_array; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_polygon_offset()			{ return s_polygon_offset; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_multitexture()				{ return s_multitexture; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_compiled_vertex_array()		{ return s_compiled_vertex_array; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_texenvop()					{ return s_texenvop; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_pbuffer()					{ return s_pbuffer; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_compressed_textures()		{ return s_compressed_textures; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_compressed_s3tc()			{ return s_compressed_s3tc; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_depth_clamp()				{ return s_depth_clamp; }
	
	GZ_GRAPH_EXPORT static  inline	gzBool	has_vertex_program()			{ return s_vertex_program; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_fragment_program()			{ return s_fragment_program; }
	
	GZ_GRAPH_EXPORT static  inline	gzBool	has_vertex_buffer_object()		{ return s_vertex_buffer_object; }
	
	GZ_GRAPH_EXPORT static  inline  gzBool	has_two_sided_stencil()			{ return s_two_sided_stencil; }
	GZ_GRAPH_EXPORT static  inline  gzBool	has_separate_stencil()			{ return s_separate_stencil; }

	GZ_GRAPH_EXPORT static  inline  gzBool	has_shader_objects()			{ return s_shader_objects; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_vertex_shader()				{ return s_vertex_shader; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_fragment_shader()			{ return s_fragment_shader; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_multisample()				{ return s_multisample; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_auto_mipmap()				{ return s_auto_mipmap; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_npot_texture()				{ return s_npot_texture; }


	// --- limits ------

	GZ_GRAPH_EXPORT static	inline	gzInt32	getMaxTextureSize()				{ return s_maxtexturesize; }

	GZ_GRAPH_EXPORT static	inline	gzUInt32	getNumberOfTextureUnits()		{ return s_numberOfTextureUnits; }

	GZ_GRAPH_EXPORT static	inline	gzBool	isRemoteConnection()			{ return s_remoteConnection; }
	
*/

	// --- generic -----

	GZ_GRAPH_EXPORT static gzBool				hasValidEngine();
	GZ_GRAPH_EXPORT static gzVoid				useEngine(gzAudioEngineType type);
	GZ_GRAPH_EXPORT static gzAudioEngineType	getEngineType();
	GZ_GRAPH_EXPORT static gzAudioEngine *		getEngine();
	GZ_GRAPH_EXPORT static gzFloat				getVersion();
	GZ_GRAPH_EXPORT static gzString				getExtensions();

	// Engine functions
	
	GZ_GRAPH_EXPORT	virtual gzVoid setupEngine()=0;
	GZ_GRAPH_EXPORT	virtual gzVoid shutdownEngine()=0;

	
protected:


	/*

	GZ_GRAPH_EXPORT static gzBool	s_vertex_array;
	GZ_GRAPH_EXPORT static gzBool	s_compiled_vertex_array;
	GZ_GRAPH_EXPORT static gzBool	s_multitexture;
	GZ_GRAPH_EXPORT static gzBool	s_texenvop;
	GZ_GRAPH_EXPORT static gzBool	s_pbuffer;
	GZ_GRAPH_EXPORT static gzBool	s_polygon_offset;
	GZ_GRAPH_EXPORT static gzBool	s_compressed_textures;
	GZ_GRAPH_EXPORT static gzBool	s_compressed_s3tc;
	GZ_GRAPH_EXPORT static gzBool	s_depth_clamp;
	GZ_GRAPH_EXPORT static gzBool	s_vertex_program;
	GZ_GRAPH_EXPORT static gzBool	s_fragment_program;
	GZ_GRAPH_EXPORT static gzBool	s_vertex_buffer_object;
	GZ_GRAPH_EXPORT static gzBool	s_two_sided_stencil;
	GZ_GRAPH_EXPORT static gzBool	s_separate_stencil;
	GZ_GRAPH_EXPORT static gzBool	s_shader_objects;
	GZ_GRAPH_EXPORT static gzBool	s_vertex_shader;
	GZ_GRAPH_EXPORT static gzBool	s_fragment_shader;
	GZ_GRAPH_EXPORT static gzBool	s_multisample;
	GZ_GRAPH_EXPORT static gzBool	s_auto_mipmap;
	GZ_GRAPH_EXPORT static gzBool	s_npot_texture;

*/

	GZ_GRAPH_EXPORT static gzString				s_gz_extensions;
	GZ_GRAPH_EXPORT static gzFloat				s_gz_version;
	GZ_GRAPH_EXPORT static gzAudioEngineType	s_engineType;
	GZ_GRAPH_EXPORT	static gzAudioEngine *		s_currentEngine;


	GZ_GRAPH_EXPORT static gzAudioEngine *		s_engine[GZ_MAX_AUDIO_ENGINES];

};


#endif //__GZ_AUDIO_ENGINE_H__


