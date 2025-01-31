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
// File			: gzGraphicsEngine.h
// Module		: 
// Description	: Class definition of stub calls
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
// AMO	990217	Created file 	
//
//******************************************************************************

#ifndef __GZ_GRAPHICS_ENGINE_H__
#define __GZ_GRAPHICS_ENGINE_H__

/*!	\file 
	\brief Bridge between Gizmo3D low level API and system graphics API

*/


#include "gzBasicTypes.h"
#include "gzGraphicsAbstractionLayer.h"
#include "gzBase.h"

//! Graphics Engine Types
/*! Initialise with gzGraphicsEngine::useEngine(xxx) before using any Gizmo3D 3D code */
enum gzEngineType
{ 
	GZ_ENGINE_NOT_INIT	= -2 ,
	GZ_ENGINE_NONE		= -1 , 
	GZ_ENGINE_DEBUG		=  0 , 
	GZ_ENGINE_SOFTWARE	=  1 , 
	GZ_ENGINE_OPENGL	=  2 , 
	GZ_ENGINE_DIRECTX	=  3 ,
	GZ_ENGINE_OPENGL_3	=  4 ,
	GZ_ENGINE_OPENGLES	=  5 ,
} ;

const gzUByte GZ_MAX_3D_ENGINES=6; // Number of valid entries in above structure

enum gzEngineVendor
{
	GZ_ENGINE_VENDOR_UNKNOWN	=	0,
	GZ_ENGINE_VENDOR_NVIDIA		=	1,
	GZ_ENGINE_VENDOR_ATI		=	2,
	GZ_ENGINE_VENDOR_MATROX		=	3,
	GZ_ENGINE_VENDOR_INTEL		=	4,
	GZ_ENGINE_VENDOR_MESA		=	5,
	GZ_ENGINE_VENDOR_APPLE		=	6,
};


//-------------------- engine dependant implementations ------------------------

//******************************************************************************
// Class	: gzGraphicsEngine
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990217	Created 
//									
//******************************************************************************
class gzGraphicsEngine
{
public:

	// ------------------- extensions. Not basically supported by Engine --------------------

	GZ_GRAPH_EXPORT static  inline	gzBool	has_vertex_array()							{ return s_vertex_array; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_polygon_offset()						{ return s_polygon_offset; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_multitexture()							{ return s_multitexture; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_compiled_vertex_array()					{ return s_compiled_vertex_array; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_texenvop()								{ return s_texenvop; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_compressed_textures()					{ return s_compressed_textures; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_compressed_s3tc()						{ return s_compressed_s3tc; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_compressed_etc2()						{ return s_compressed_etc2; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_depth_clamp()							{ return s_depth_clamp; }
	
	GZ_GRAPH_EXPORT static  inline	gzBool	has_vertex_program()						{ return s_vertex_program; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_fragment_program()						{ return s_fragment_program; }
	
	GZ_GRAPH_EXPORT static  inline	gzBool	has_vertex_buffer_object()					{ return s_vertex_buffer_object; }
	
	GZ_GRAPH_EXPORT static  inline  gzBool	has_two_sided_stencil()						{ return s_two_sided_stencil; }
	GZ_GRAPH_EXPORT static  inline  gzBool	has_separate_stencil()						{ return s_separate_stencil; }

	GZ_GRAPH_EXPORT static  inline  gzBool	has_shader_objects()						{ return s_shader_objects; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_vertex_shader()							{ return s_vertex_shader; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_fragment_shader()						{ return s_fragment_shader; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_multisample()							{ return s_multisample; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_multisample_fbo()						{ return s_multisample_fbo; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_auto_mipmap()							{ return s_auto_mipmap; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_npot_texture()							{ return s_npot_texture; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_pixel_buffer_object()					{ return s_pixel_buffer_object; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_geometry_shader()						{ return s_geometry_shader; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_draw_instanced()						{ return s_draw_instanced; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_texture_3d()							{ return s_texture_3d; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_vertex_program_texture_lookup()			{ return s_vertex_program_texture_lookup; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_float_textures()						{ return s_float_textures; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_frame_buffer_object()					{ return s_frame_buffer_object; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_displaylist()							{ return s_displaylist; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_compare_func()							{ return s_compare_func; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_advanced_pixel_storage()				{ return s_advanced_pixel_storage; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_quad_and_poly()							{ return s_has_quad_and_poly; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_indexed_geometry()						{ return s_has_indexed_geometry; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_3d_texture()							{ return s_has_3d_texture; }
	GZ_GRAPH_EXPORT static  inline	gzBool	has_nonuniform_matrix_upload()				{ return s_matrix_nonuniform_upload; }

	// --- limits ------

	GZ_GRAPH_EXPORT static	inline	gzInt32		getMaxTextureSize()							{ return s_maxtexturesize; }

	GZ_GRAPH_EXPORT static	inline	gzUInt32	getNumberOfTextureUnits()					{ return s_numberOfTextureUnits; }

	GZ_GRAPH_EXPORT static	inline	gzBool		isRemoteConnection()						{ return s_remoteConnection; }
	
	// --- generic -----

	GZ_GRAPH_EXPORT static  inline	gzEngineVendor	getEngineVendor()					{ return s_engineVendor; }
	GZ_GRAPH_EXPORT static gzBool					hasValidEngine();
	GZ_GRAPH_EXPORT static gzBool					useEngine(gzEngineType type,gzBool throwExceptions=TRUE);
	GZ_GRAPH_EXPORT static gzEngineType				getEngineType();
	GZ_GRAPH_EXPORT static gzGraphicsEngine *		getEngine();
	GZ_GRAPH_EXPORT static gzFloat					getVersion();
	GZ_GRAPH_EXPORT static gzFloat					getShaderVersion();
	GZ_GRAPH_EXPORT static gzString					getExtensions();
	GZ_GRAPH_EXPORT static gzString					getRenderer();

	// Engine functions
	
	GZ_GRAPH_EXPORT	virtual gzVoid setupEngine()=0;
	GZ_GRAPH_EXPORT	virtual gzVoid shutdownEngine()=0;
	
protected:


	GZ_GRAPH_EXPORT static gzBool	s_vertex_array;
	GZ_GRAPH_EXPORT static gzBool	s_compiled_vertex_array;
	GZ_GRAPH_EXPORT static gzBool	s_multitexture;
	GZ_GRAPH_EXPORT static gzBool	s_texenvop;
	GZ_GRAPH_EXPORT static gzBool	s_polygon_offset;
	GZ_GRAPH_EXPORT static gzBool	s_compressed_textures;
	GZ_GRAPH_EXPORT static gzBool	s_compressed_s3tc;
	GZ_GRAPH_EXPORT static gzBool	s_compressed_etc2;
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
	GZ_GRAPH_EXPORT static gzBool	s_multisample_fbo;
	GZ_GRAPH_EXPORT static gzBool	s_auto_mipmap;
	GZ_GRAPH_EXPORT static gzBool	s_npot_texture;
	GZ_GRAPH_EXPORT static gzBool	s_pixel_buffer_object;
	GZ_GRAPH_EXPORT static gzBool	s_geometry_shader;
	GZ_GRAPH_EXPORT static gzBool	s_draw_instanced;
	GZ_GRAPH_EXPORT static gzBool	s_texture_3d;
	GZ_GRAPH_EXPORT static gzBool	s_vertex_program_texture_lookup;
	GZ_GRAPH_EXPORT static gzBool	s_float_textures;
	GZ_GRAPH_EXPORT static gzBool	s_frame_buffer_object;
	GZ_GRAPH_EXPORT static gzBool	s_displaylist;
	GZ_GRAPH_EXPORT static gzBool	s_compare_func;
	GZ_GRAPH_EXPORT static gzBool	s_advanced_pixel_storage;
	GZ_GRAPH_EXPORT static gzBool	s_has_quad_and_poly;
	GZ_GRAPH_EXPORT static gzBool	s_has_indexed_geometry;
	GZ_GRAPH_EXPORT static gzBool	s_has_3d_texture;
	GZ_GRAPH_EXPORT static gzBool	s_matrix_nonuniform_upload;


	GZ_GRAPH_EXPORT static gzInt32				s_maxtexturesize;

	GZ_GRAPH_EXPORT	static gzUInt32				s_numberOfTextureUnits;


	GZ_GRAPH_EXPORT static gzString				s_gz_extensions;
	GZ_GRAPH_EXPORT static gzFloat				s_gz_version;
	GZ_GRAPH_EXPORT static gzEngineType			s_engineType;
	GZ_GRAPH_EXPORT	static gzGraphicsEngine *	s_currentEngine;
	GZ_GRAPH_EXPORT static gzEngineVendor		s_engineVendor;
	GZ_GRAPH_EXPORT static gzString				s_renderer;

	GZ_GRAPH_EXPORT static gzBool				s_remoteConnection;
	GZ_GRAPH_EXPORT static gzFloat				s_shader_version;
	GZ_GRAPH_EXPORT static gzGraphicsEngine *	s_engine[GZ_MAX_3D_ENGINES];
};


#endif


