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
// File			: gzDbFlags.h
// Module		: 
// Description	: Enum definitions of loader flags for DB and IMAGE loaders
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
// AMO	981014	Created file 	
//
//******************************************************************************
#ifndef __GZ_DB_FLAGS_H__
#define __GZ_DB_FLAGS_H__

/*!	\file 
	\brief Enum definitions of loader flags for DB and IMAGE loaders

*/

#include "gzImage.h"

#define GZ_DB_FLAG_NUM(x)	(gzSerializeAdapterFlags)(LLU(1)<<( x+GZ_IMAGE_FLAG_MAX_SIZE))

/*!
This will flip .dds images referenced by the dataset as the .dds format is ambigious from some vendors.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_FLIP_FLIPPED_IMAGES			=	GZ_IMAGE_FLAGS_FLIP_FLIPPED_IMAGES;			

/*!
The image will not be cached for later on usage. Normally when an image is read by a loader the image 
is cached so consecutive loaders will use the same instance. Sometimes you want to change path with 
the GIZMO_PATH environment variable to change time of year etc. Then you want to use the same name of 
the image but a different file.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_NO_CACHED_IMAGE				=	GZ_IMAGE_FLAGS_NO_CACHED_IMAGE;	

/*!
Gizmo3D normally tries to load alternate images when an image is not understood by the loader. E.g. a 
database might reference a file “test.tiff” and there is no “tiff” reader registered. In that case 
Gizmo3D normally want to find a “test.dds” or a “test.bmp” file. This flag disables that search.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_NO_ALTERNATE_IMAGE_EXT		=	GZ_IMAGE_FLAGS_NO_ALTERNATE_IMAGE_EXT;

const gzSerializeAdapterFlags	GZ_DB_FLAGS_IGNORE_IMAGE_MIPMAPS		=	GZ_IMAGE_FLAGS_IGNORE_IMAGE_MIPMAPS;

//! Use this flag to load dxt1 images (.dds) without alpha
const gzSerializeAdapterFlags	GZ_DB_FLAGS_NO_DXT1_ALPHA				=	GZ_IMAGE_FLAGS_NO_DXT1_ALPHA;

/*!
This flag will tell Gizmo3D to add keyframe transforms for animations instead of static transforms in the scene graph.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_ANIMATION				=	GZ_DB_FLAG_NUM(0);	

/*!
This flag will tell Gizmo3D to automatically enable mip maps for all loaded textures.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_MIPMAPS					=	GZ_DB_FLAG_NUM(1);						

/*!
This flag will tell Gizmo3D to use a dynamic loader in some cases. The loader will not wait for the loading 
to return, but a background process will load the database.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_DYNAMIC_LOADING			=	GZ_DB_FLAG_NUM(2);						

/*!
This flag will tell Gizmo3D to use a name encoding schema. The node names e.g. in a .3ds file will be used 
to create billboards, switches etc. even if the format doesn’t support them. See node name encodings.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_NAME_ENCODED_NODES		=	GZ_DB_FLAG_NUM(3);		

/*!
This flag will tell Gizmo3D to generate light material properties and to smooth shade the geometry 
(generate normals) to models that doesn’t have light material properties. This way pure geometry 
will look shaded under a light lamp.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_GENERATE_LIGHT_MATERIAL		=	GZ_DB_FLAG_NUM(4);						

/*!
This flag will tell Gizmo3D to smooth binary alpha. Images with nearly two distinct alpha levels 
will be smoothed and sorted in the normal alpha sorting pipeline. Gives better images, but lower 
performance.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_SMOOTH_BINARY_ALPHA			=	GZ_DB_FLAG_NUM(5);						

/*!
This flag will tell Gizmo3D to not use alpha blending for binary alpha images. Gives better 
performance but the actual “edge” of the image is non transparent.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_FAST_BINARY_ALPHA			=	GZ_DB_FLAG_NUM(6);	

/*!
This flag will tell Gizmo3D to create indexed geometry. Geometry with many same coordinates 
referenced by many triangles etc. will be faster as indexed geometry.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_INDEXED_GEOMETRY		=	GZ_DB_FLAG_NUM(7);			

/*!
This flag will tell Gizmo3D to create display lists of the geometries. The geometries are 
compiled into displaylists the first time. Very fast on HW that supports displaylists good 
e.g. SGI HW.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_DISPLAYLIST_GEOMETRY	=	GZ_DB_FLAG_NUM(8);	

/*!
This flag will tell Gizmo3D to use VBO (Vertex Buffer Objects) for the geometry. A very 
fast way to render. However the memory consumption is doubled as the geometry is stored 
both in CPU mem and GFX mem.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_BUFFERED_GEOMETRY		=	GZ_DB_FLAG_NUM(9);						

/*!
This flag will tell Gizmo3D to convert read images to grayscale. Allows view usage of 
imagages on low memory apps.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_CONVERT_IMAGES_TO_GRAYSCALE	=	GZ_DB_FLAG_NUM(10);					

/*!
This flag will tell Gizmo3D to compress images as they are read. Converts all images to 
compressed formats.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_COMPRESS_ON_GPU				=	GZ_DB_FLAG_NUM(11);						

/*!
This flag will tell Gizmo3D to drop the image from CPU mem. You can not read the image 
after this.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_DISPOSE_TEX_IMAGE			=	GZ_DB_FLAG_NUM(12);						

/*!
This flag will tell Gizmo3D to dispose memory on CPU. You will not be able to read the 
geometry again but you will get a very fast rendering of it. Must be combined with 
GZ_DB_FLAGS_USE_BUFFERED_GEOMETRY.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_DISPOSE_BUFFERED_GEOMETRY	=	GZ_DB_FLAG_NUM(13);						

/*!
Normally Gizmo3D treats DXT1 as opaque, DXT3 as binary alpha and DXT5 as continious alpha. 
However this is not always correct. The flag enables a calculation of the image during load.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_CHECK_DDS_ALPHA				=	GZ_DB_FLAG_NUM(14);						

/*!
This flag will tell Gizmo3D to treat all alpha images as binary alpha. No sorting is done 
for any alpha image. The fastest way to render alpha images, but you might get anomalies 
where some images might exclude others even if they are transparent.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_NO_SORT_CONT_ALPHA			=	GZ_DB_FLAG_NUM(15);						

/*!
This flag auto enables the gzNodeOptimizer to run the db before returning the node handle.
*/
const gzSerializeAdapterFlags	GZ_DB_FLAGS_OPTIMIZE_DB					=	GZ_DB_FLAG_NUM(16);						

const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_TWO_PASS_ALPHA			=	GZ_DB_FLAG_NUM(17);						

const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_FOUR_PASS_ALPHA			=	GZ_DB_FLAG_NUM(18);						

const gzSerializeAdapterFlags	GZ_DB_FLAGS_OPTIMIZE_IMAGE_DATA			=	GZ_DB_FLAG_NUM(19);		

const gzSerializeAdapterFlags	GZ_DB_FLAGS_READ_ONLY_HEADER			=	GZ_DB_FLAG_NUM(20);		// Fixed. Do not change

const gzSerializeAdapterFlags	GZ_DB_FLAGS_NO_FLAT_GEOMETRY			=	GZ_DB_FLAG_NUM(21);	

const gzSerializeAdapterFlags	GZ_DB_FLAGS_SKIP_NODE_NAMES				=	GZ_DB_FLAG_NUM(22);	

const gzSerializeAdapterFlags	GZ_DB_FLAGS_DONT_SAVE_HIERARCHY			=	GZ_DB_FLAG_NUM(23);	

const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_PBR_LIGHT				=	GZ_DB_FLAG_NUM(24L);	

const gzSerializeAdapterFlags	GZ_DB_FLAGS_CREATE_MIPMAPS				=	GZ_DB_FLAG_NUM(25L);	

const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_HALF_ALPHA				=	GZ_DB_FLAG_NUM(26L);						

const gzSerializeAdapterFlags	GZ_DB_FLAGS_SKIP_NORMALS				=	GZ_DB_FLAG_NUM(27L);

const gzSerializeAdapterFlags	GZ_DB_FLAGS_SKIP_OPTIMIZE_GEOMETRY		=	GZ_DB_FLAG_NUM(28L);

const gzSerializeAdapterFlags	GZ_DB_FLAGS_SKIP_DB_INFO_TYPE			=	GZ_DB_FLAG_NUM(29L);

const gzSerializeAdapterFlags	GZ_DB_FLAGS_IGNORE_TEXTURE_ALPHA		=	GZ_DB_FLAG_NUM(30L);

const gzSerializeAdapterFlags	GZ_DB_FLAGS_SKIP_TEXTURE				=	GZ_DB_FLAG_NUM(31L);

const gzSerializeAdapterFlags	GZ_DB_FLAGS_USE_CACHED_MODEL			=	GZ_DB_FLAG_NUM(32L);

const gzSerializeAdapterFlags	GZ_DB_FLAGS_CREATE_CACHED_MODEL			=	GZ_DB_FLAG_NUM(33L);

const gzSerializeAdapterFlags	GZ_DB_FLAGS_DYN_LOAD_RETRY_WAIT			=	GZ_DB_FLAG_NUM(34L);

//! Feature flags for DB loaders
const gzSerializeAdapterFlags	GZ_DB_FLAGS_DEFAULT						=	GZ_DB_FLAGS_SKIP_DB_INFO_TYPE | GZ_DB_FLAGS_DYN_LOAD_RETRY_WAIT;		// Dont add loaded file type as attribute

#endif // __GZ_DB_FLAGS_H__

