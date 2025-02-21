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
// File			: gzImage.h
// Module		: gzBase
// Description	: Class definition of the gzImage class
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
// AMO	990223	Created file 	
// AMO	211202	Added feature and layer info to metadata			(2.11.55)
// AMO	221006	Added sample type of image data to metadata			(2.12.13)
// AMO	231010	Added multiple classes for features					(2.12.107)
// AMO	240920 Reverted change in homography						(2.12.188)
//
//******************************************************************************
#ifndef __GZ_IMAGE_H__
#define __GZ_IMAGE_H__

/*!	\file
	\brief Image utilites (bitmaps)

  Various formats of image data. All types of image data are derived from the base class
  gzImage. You can provide your own formats as long as you implement the virtual functions
  in gzImage.

*/

#include "gzBase.h"
#include "gzReference.h"
#include "gzSerialize.h"

#include "gzRGBA.h"
#include "gzObject.h"

enum gzImageChanges
{
	GZ_IMAGE_CHANGE_DATA = 1 << 0,
	GZ_IMAGE_CHANGE_FORMAT = 1 << 1,
	GZ_IMAGE_CHANGE_ALL = GZ_IMAGE_CHANGE_DATA + GZ_IMAGE_CHANGE_FORMAT
};

enum gzImageType
{
	/*!An image with RGB format. It has three components: Red, Green and Blue.
	*/
	GZ_IMAGE_TYPE_RGB_8,
	/*!An image with RGBA format. It has four components: Red, Green, Blue and Alpha.
	*/
	GZ_IMAGE_TYPE_RGBA_8,
	GZ_IMAGE_TYPE_BW_8,
	GZ_IMAGE_TYPE_BW_HALF,
	GZ_IMAGE_TYPE_BWA_8,
	GZ_IMAGE_TYPE_BWA_HALF,
	GZ_IMAGE_TYPE_DEPTHMAP,
	GZ_IMAGE_TYPE_BITMAP,
	GZ_IMAGE_TYPE_BGRA_5_5_5_1,
	GZ_IMAGE_TYPE_BGR_5_6_5,
	GZ_IMAGE_TYPE_RGBA_FLOAT,	// 32 bits
	GZ_IMAGE_TYPE_RGB_FLOAT,
	GZ_IMAGE_TYPE_RGBA_HALF,	// 16 bits
	GZ_IMAGE_TYPE_RGB_HALF,
	GZ_IMAGE_TYPE_RGBA_FPX,	// Special FPX Gizmo Extension packed bits r7g7b7 r6g6b6 etc..

	GZ_IMAGE_TYPE_RGB_8_DXT1,
	GZ_IMAGE_TYPE_RGBA_8_DXT1,
	GZ_IMAGE_TYPE_RGBA_8_DXT3,
	GZ_IMAGE_TYPE_RGBA_8_DXT5,

	GZ_IMAGE_TYPE_BW_16,
	GZ_IMAGE_TYPE_BW_FLOAT,
	GZ_IMAGE_TYPE_BWA_16,
	GZ_IMAGE_TYPE_BWA_FLOAT,
	GZ_IMAGE_TYPE_RGB_16,
	GZ_IMAGE_TYPE_RGBA_16,
	GZ_IMAGE_TYPE_ABGR_16,

	GZ_IMAGE_TYPE_BGR_8,
	GZ_IMAGE_TYPE_ABGR_8,

	GZ_IMAGE_TYPE_RGB_8_ETC2,
	GZ_IMAGE_TYPE_RGB_8_A_1_ETC2,
	GZ_IMAGE_TYPE_RGBA_8_ETC2,
	GZ_IMAGE_TYPE_R_11_ETC2,
	GZ_IMAGE_TYPE_RG_11_ETC2,

	GZ_IMAGE_TYPE_META_DATA,	// Empty image with possibly user meta data populated

	GZ_IMAGE_TYPE_CUSTOM,		// Custom type

	GZ_IMAGE_TYPE_BGRA_8,
};

enum gzImageFormat
{
	GZ_IMAGE_FORMAT_RGB = GZ_RGB,
	GZ_IMAGE_FORMAT_BGR = GZ_BGR,
	GZ_IMAGE_FORMAT_BGRA = GZ_BGRA,
	GZ_IMAGE_FORMAT_RGBA = GZ_RGBA,
	GZ_IMAGE_FORMAT_LUMINANCE = GZ_LUMINANCE,
	GZ_IMAGE_FORMAT_LUMINANCE_ALPHA = GZ_LUMINANCE_ALPHA,
	GZ_IMAGE_FORMAT_COLOR_INDEX = GZ_COLOR_INDEX,

	// Predefined S3TC Compressed variants
	GZ_IMAGE_FORMAT_COMPRESSED_RGB_S3TC_DXT1 = GZ_COMPRESSED_RGB_S3TC_DXT1,
	GZ_IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT1 = GZ_COMPRESSED_RGBA_S3TC_DXT1,
	GZ_IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT3 = GZ_COMPRESSED_RGBA_S3TC_DXT3,
	GZ_IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT5 = GZ_COMPRESSED_RGBA_S3TC_DXT5,

	// Special depth image format
	GZ_IMAGE_FORMAT_DEPTH_COMPONENT				= GZ_DEPTH_COMPONENT,

	// Predefined ETC2/EAC Compressed variants
	GZ_IMAGE_FORMAT_COMPRESSED_RGB8_ETC2		= GZ_COMPRESSED_RGB8_ETC2,
	GZ_IMAGE_FORMAT_COMPRESSED_RGB8_A1_ETC2		= GZ_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,
	GZ_IMAGE_FORMAT_COMPRESSED_RGBA8_ETC2		= GZ_COMPRESSED_RGBA8_ETC2_EAC,
	GZ_IMAGE_FORMAT_COMPRESSED_R11_EAC			= GZ_COMPRESSED_R11_EAC,
	GZ_IMAGE_FORMAT_COMPRESSED_RG11_EAC			= GZ_COMPRESSED_RG11_EAC,

	GZ_IMAGE_FORMAT_META						= 0,

};

enum gzComponentType
{
	GZ_COMPONENT_BYTE						= GZ_BYTE,
	GZ_COMPONENT_UNSIGNED_BYTE				= GZ_UNSIGNED_BYTE,
	GZ_COMPONENT_SHORT						= GZ_SHORT,
	GZ_COMPONENT_UNSIGNED_SHORT				= GZ_UNSIGNED_SHORT,
	GZ_COMPONENT_UNSIGNED_SHORT_1_5_5_5_REV = GZ_UNSIGNED_SHORT_1_5_5_5_REV,
	GZ_COMPONENT_UNSIGNED_SHORT_4_4_4_4_REV = GZ_UNSIGNED_SHORT_4_4_4_4_REV,
	GZ_COMPONENT_UNSIGNED_SHORT_5_6_5_REV	= GZ_UNSIGNED_SHORT_5_6_5_REV,
	GZ_COMPONENT_INT						= GZ_INT,
	GZ_COMPONENT_UNSIGNED_INT				= GZ_UNSIGNED_INT,
	GZ_COMPONENT_FLOAT						= GZ_FLOAT,
	GZ_COMPONENT_HALF_FLOAT					= GZ_HALF_FLOAT,
	GZ_COMPONENT_DOUBLE						= GZ_DOUBLE,
	GZ_COMPONENT_BITMAP						= GZ_BITMAP,
	GZ_COMPONENT_META						= 0,
};


class gzPixelInterface
{
public:

	virtual gzRGBA  getPixel(gzUInt32 width, gzUInt32 height, gzUInt32 depth = 0) = 0;
	virtual gzBool  setPixel(gzUInt32 width, gzUInt32 height, const gzRGBA& value, gzUInt32 depth = 0) = 0;
	virtual gzBool	hasOriginAtLowerLeft() = 0;
};

// ------------------------------ Image Metadata ----------------------------------

//! Image class type
enum gzImageInfoClass
{
	GZ_IMAGE_INFO_CLASS_NOT_DEF,
	GZ_IMAGE_INFO_CLASS_TEXTURE,
	GZ_IMAGE_INFO_CLASS_ALTITUDE,				// DEM (Elevation Model (m - float or int) )
	GZ_IMAGE_INFO_CLASS_ALTITUDE_SURFACE,		// DSM (Surface Model (m - float or int) )
	GZ_IMAGE_INFO_CLASS_SURFACE_HEIGHT,			// DSM (Surface Model) - DEM (Elevation) = Height of terrain features (m - float or int)
	GZ_IMAGE_INFO_CLASS_DEPTH,	
	GZ_IMAGE_INFO_CLASS_DENSITY,
	GZ_IMAGE_INFO_CLASS_FEATURE,	// See below for feature encoding
	GZ_IMAGE_INFO_CLASS_LAYER,		// See below for layer (discrete on off or probability percentage)
};

GZ_DECLARE_DYNAMIC_ENUM(gzImageInfoClass);

//! Mutiple features per layer
enum gzImageInfoFeatureType					// Feature define encoding of feature per pixel
{
	GZ_IMAGE_INFO_FEATURE_TYPE_NOT_DEF,		// Just plain image data, RGB encoding is custom
	GZ_IMAGE_INFO_FEATURE_TYPE_DEFAULT,		// Default feature encoding (Gizmo default)
	GZ_IMAGE_INFO_FEATURE_TYPE_FORRESTRY,
	GZ_IMAGE_INFO_FEATURE_TYPE_WINTER_FORRESTRY,
	GZ_IMAGE_INFO_FEATURE_TYPE_MAXAR,		// Same as default as we used Maxar first classes as original data
};

GZ_DECLARE_DYNAMIC_ENUM(gzImageInfoFeatureType);

enum gzImageFeatureClass							// Default labelled classes	(M=present in GZ_IMAGE_INFO_FEATURE_TYPE_MAXAR as well) 
{
	GZ_IMAGE_FEATURE_CLASS_0_NODATA						= 0,		// No data								(M)
	GZ_IMAGE_FEATURE_CLASS_1_UNDEFINED					= 1,		// Undefined							(M)
	GZ_IMAGE_FEATURE_CLASS_6_BUILDING					= 6,		// Generic Buildings					(M)
	GZ_IMAGE_FEATURE_CLASS_8_MAN_MADE_OBJECT			= 8,		// Man made object						(M)
	GZ_IMAGE_FEATURE_CLASS_21_GRASS						= 21,		// Ground Grass							(M)
	GZ_IMAGE_FEATURE_CLASS_22_BARREN					= 22,		// Ground Barren						(M)
	GZ_IMAGE_FEATURE_CLASS_23_SAND						= 23,		// Ground Sand	
	GZ_IMAGE_FEATURE_CLASS_24_ROCK						= 24,		// Ground Rock	
	GZ_IMAGE_FEATURE_CLASS_25_HYDRO_SOIL				= 25,		// Ground hydro soil	
	GZ_IMAGE_FEATURE_CLASS_26_GRAVEL					= 26,		// Ground Gravel
	GZ_IMAGE_FEATURE_CLASS_27_CROPS						= 27,		// Ground Crops
	GZ_IMAGE_FEATURE_CLASS_28_SWAMP						= 28,		// Ground swamp	
	GZ_IMAGE_FEATURE_CLASS_29_HEATH						= 29,		// Ground heath (hed)	
	GZ_IMAGE_FEATURE_CLASS_40_VEGETATION				= 40,		// Generic vegetation on ground			(M)
	GZ_IMAGE_FEATURE_CLASS_47_VEGETATION_OVER_ROAD		= 47,		// Generic vegetation over road			(M)
	GZ_IMAGE_FEATURE_CLASS_48_VEGETATION_OVER_BUILDING	= 48,		// Generic vegetation over building		(M)
	GZ_IMAGE_FEATURE_CLASS_49_VEGETATION_OVER_BRIDGE	= 49,		// Generic vegetation over bridge		(M)
	GZ_IMAGE_FEATURE_CLASS_60_WATER						= 60,		// Water								(M)
	GZ_IMAGE_FEATURE_CLASS_65_SWIMMINGPOOL				= 65,		// Water - Swimmingpool					(M)
	GZ_IMAGE_FEATURE_CLASS_80_MAN_MADE_SURFACE			= 80,		// Man made surface - generic			(M)
	GZ_IMAGE_FEATURE_CLASS_81_PAVED_ROAD				= 81,		// Man made surface - paved road		(M)
	GZ_IMAGE_FEATURE_CLASS_83_DIRT_ROAD					= 83,		// Man made surface - dirt road			(M)
	GZ_IMAGE_FEATURE_CLASS_86_BRIDGE					= 86,		// Man made surface - bridge			(M)
	GZ_IMAGE_FEATURE_CLASS_89_RAIL_BRIDGE				= 89,		// Man made surface - railbridge		(M)
	GZ_IMAGE_FEATURE_CLASS_90_RAIL						= 90,		// Man made surface - rail				(M)
	GZ_IMAGE_FEATURE_CLASS_92_RUNWAY					= 92,		// Man made surface - runway			(M)

};

//! Single type per layer
enum gzImageInfoLayerType					// Layers define probability 0%-100% 
{
	GZ_IMAGE_INFO_LAYER_TYPE_NOT_DEF,		// Just plain image data, RGB encoding is custom
	GZ_IMAGE_INFO_LAYER_TYPE_FEATURE_DATA,	// Layer defines probability percentage of feature type in separate images 
	GZ_IMAGE_INFO_LAYER_TYPE_GRASSLAND,		// Grass and low shrubbery layer
	GZ_IMAGE_INFO_LAYER_TYPE_BUILDINGS,
	GZ_IMAGE_INFO_LAYER_TYPE_VEGETATION,	// Trees and large shrubbery
	GZ_IMAGE_INFO_LAYER_TYPE_WATER,
	GZ_IMAGE_INFO_LAYER_TYPE_DIRT_ROAD,
	GZ_IMAGE_INFO_LAYER_TYPE_BARREN,
	GZ_IMAGE_INFO_LAYER_TYPE_MAN_MADE_GROUND,
	GZ_IMAGE_INFO_LAYER_TYPE_ASPHALT_ROAD,
	GZ_IMAGE_INFO_LAYER_TYPE_RAILWAY,
	GZ_IMAGE_INFO_LAYER_TYPE_RUNWAY,
	GZ_IMAGE_INFO_LAYER_TYPE_CROPS,
	GZ_IMAGE_INFO_LAYER_TYPE_UNTRUSTED,
};

GZ_DECLARE_DYNAMIC_ENUM(gzImageInfoLayerType);

//! Single type per layer
enum gzImageInfoSampleType
{
	GZ_IMAGE_SAMPLE_TYPE_CONTINIOUS,		// Sample using bicubic
	GZ_IMAGE_SAMPLE_TYPE_NEAREST,			// Nearest neighbour
	GZ_IMAGE_SAMPLE_TYPE_MAX,				// Maximum type value of neighbours
	GZ_IMAGE_SAMPLE_TYPE_MIN,				// Minimum type value of neighbours
	GZ_IMAGE_SAMPLE_TYPE_MEDIAN,			// Median histogram type value of neighbours
};

GZ_DECLARE_DYNAMIC_ENUM(gzImageInfoSampleType);

//! SubImage types
enum gzSubImageType
{
	GZ_SUB_IMAGE_TYPE_UNDEFINED,			// undefined type. plain subimages
	GZ_SUB_IMAGE_TYPE_MIPMAP,				// MipMap pyramid
	GZ_SUB_IMAGE_TYPE_VIRTUAL_LAYOUT,		// Virtual layout for super large images
	GZ_SUB_IMAGE_TYPE_FRAMES,				// Image frames (discrete movie)
};

//! Serialize class for GZ_IMAGE_INFO_IMAGE_TO_WORLD_HOMOGRAPHY
class gzImageHomography : public gzSerializeData
{
public:

	gzImageHomography(const gzMatrix3D& _matrix = gzMatrix3D::identityMatrix()) :matrix(_matrix) {}

	gzMatrix3D matrix;

	GZ_DECLARE_SERIALIZE_9("gzImageHomography", 
		matrix.v11,
		matrix.v12,
		matrix.v13,
		matrix.v21,
		matrix.v22,
		matrix.v23,
		matrix.v31,
		matrix.v32,
		matrix.v33);
};

GZ_DECLARE_DYNAMIC_CUSTOM_TYPE(gzImageHomography);

// ------------------------------------ META data for images ------------------------------------------------
// 
//! Constants for named UserData used by images
const gzString	GZ_USERDATA_IM_INFO = "UserDataImInfo";

//! Constants for Attributes provided by the GZ_USERDATA_IM_INFO
const gzString GZ_IMAGE_INFO_COORD_SYS = "ImI-CoordSystem";								// Coord Sys String

//! Coordinate Swizzle to x,y,z
const gzString GZ_IMAGE_INFO_SWIZZLE = "ImI-Swizzle";									// gzCoordinateSwizzle

//! Image to World homography 3x3 matrix (double)
const gzString GZ_IMAGE_INFO_IMAGE_TO_WORLD_HOMOGRAPHY = "ImI-Wrld-Hom";				// gzImageHomography

const gzString GZ_IMAGE_INFO_PIXEL_X_SIZE = "ImI-Pixel-X-size";							// Size of Image in meta data
const gzString GZ_IMAGE_INFO_PIXEL_Y_SIZE = "ImI-Pixel-Y-size";
const gzString GZ_IMAGE_INFO_PIXEL_Z_SIZE = "ImI-Pixel-Z-size";

const gzString GZ_IMAGE_INFO_PIXEL_X_STEP = "ImI-Pixel-X-step";							// Step in coordinate system for pixel
const gzString GZ_IMAGE_INFO_PIXEL_Y_STEP = "ImI-Pixel-Y-step";
const gzString GZ_IMAGE_INFO_PIXEL_Z_STEP = "ImI-Pixel-Z-step";

const gzString GZ_IMAGE_INFO_PIXEL_X_BORDER = "ImI-Pixel-X-border";						// Border values (outside wrap on both sides)
const gzString GZ_IMAGE_INFO_PIXEL_Y_BORDER = "ImI-Pixel-Y-border";
const gzString GZ_IMAGE_INFO_PIXEL_Z_BORDER = "ImI-Pixel-Z-border";

const gzString GZ_IMAGE_INFO_MIN_TEXEL_AREA = "ImI-Texel-minArea";						// Number
const gzString GZ_IMAGE_INFO_MAX_TEXEL_AREA = "ImI-Texel-maxArea";

const gzString GZ_IMAGE_INFO_CLASS = "ImI-Class";										// gzImageInfoClass

const gzString GZ_IMAGE_INFO_FEATURE_TYPE = "ImI-Class-Feature-Type";					// gzImageInfoFeatureType

const gzString GZ_IMAGE_INFO_LAYER_TYPE = "ImI-Class-Layer-Type";						// gzImageInfoLayerType

const gzString GZ_IMAGE_INFO_SAMPLE_TYPE = "ImI-Sample-Type";							// gzImageInfoSampleType

// ------------- data type of storage ---------------

typedef gzDynamicArray<gzQWA_UByte>	ImageData;

//******************************************************************************
// Class	: gzImage
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990223	Created 
//									
//******************************************************************************
class  gzImage : public gzObject, public gzNameInterface, public gzUpdateIDFeatureInterface, public gzPixelInterface
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// typed interface

	//!Destructor
	/*!
	It is possible to specify a name for the image.
	*/
	GZ_BASE_EXPORT gzImage(const gzString& name = GZ_EMPTY_STRING);

	//!Destructor
	GZ_BASE_EXPORT virtual ~gzImage();

	GZ_BASE_EXPORT gzBool operator==(const gzImage& right) const;

	//!Sets the width for the image.
	GZ_BASE_EXPORT gzVoid	setWidth(gzUInt32 width);
	//!Sets the height for the image.
	GZ_BASE_EXPORT gzVoid	setHeight(gzUInt32 height);
	//!Sets the depth for the image.
	GZ_BASE_EXPORT gzVoid	setDepth(gzUInt32 depth = 1);

	//!Sets the width and height and depth for the image.
	GZ_BASE_EXPORT gzVoid	setSize(gzUInt32 width, gzUInt32 height, gzUInt32 depth = 1);

	GZ_PROPERTY_EXPORT(gzImageType,			ImageType,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT_(gzImageFormat,		Format,				GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT_(gzComponentType,	ComponentType,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT_(gzUByte,			Alignment,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT_(gzBool,				SwapBytes,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT_(gzUInt32,			RowLength,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT_(gzUInt32,			SkipRows,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT_(gzUInt32,			SkipPixels,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT_(gzBool,				LSBFirst,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT_(gzFloat,			BytesPerComponent,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT_(gzUByte,			Components,			GZ_BASE_EXPORT);

	//!Compress the image
	GZ_BASE_EXPORT virtual	gzBool	isCompressed();
	GZ_BASE_EXPORT virtual	gzBool	compress(gzImageFormat compressFormat);
	GZ_BASE_EXPORT virtual	gzBool	uncompress();


	//!Returns the width of the image.
	GZ_BASE_EXPORT gzUInt32	getWidth() const { return m_width; }

	//!Returns the height of the image.
	GZ_BASE_EXPORT gzUInt32	getHeight() const { return m_height; }

	//!Returns the depth of the image.
	GZ_BASE_EXPORT gzUInt32	getDepth() const { return m_depth; }


	//!Resample an existing image.
	/*!
	The width and height for the new image is specified.

	A template image is provided that is used to create a new image of the template image type.
	If there is no ref on the template image it is deleted so you can enter an unreferenced image without
	you needing to delete it.
	*/
	GZ_BASE_EXPORT gzImage* reSample(gzUInt32 width, gzUInt32 height, gzImage* template_image = NULL, gzBool sample = TRUE, gzInt32 sampleWidth = 2, gzBool progress = FALSE);

	GZ_BASE_EXPORT gzImage* deinterlace(gzUInt32 factor_x = 1, gzUInt32 factor_y = 2);

	//!Create a new image using a template image.
	/*!A template image is provided that is used to create a new image
	of the template image type. If there is no ref on the template image it is deleted so you can enter a
	unreferenced image whithout you needing to delete it.
	*/
	GZ_BASE_EXPORT gzImage* create(gzImage* template_image = NULL, gzRGBASwizzle swizzle = GZ_MAP_RGBA_TO_RGBA, gzFloat R_factor = GZ_FLOAT_ONE, gzFloat G_factor = GZ_FLOAT_ONE, gzFloat B_factor = GZ_FLOAT_ONE, gzFloat A_factor = GZ_FLOAT_ONE, gzFloat C_value = GZ_FLOAT_ONE);

	GZ_BASE_EXPORT gzVoid createQuadImage(gzImage* bottomLeft, gzImage* bottomRight, gzImage* topLeft, gzImage* topRight);

	GZ_BASE_EXPORT gzVoid addImage(gzImage* imageA, gzImage* imageB, gzInt32 offsetAX = 0, gzInt32 offsetAY = 0, gzInt32 offsetBX = 0, gzInt32 offsetBY = 0);

	//!Copy an image.
	/*!
	A template image is provided that is used to create a new image
	of the template image type. If there is no ref on the template image it is deleted so you can enter a
	unreferenced image whithout you needing to delete it.
	*/
	GZ_BASE_EXPORT gzVoid copyFrom(gzImage* image, gzRGBASwizzle swizzle = GZ_MAP_RGBA_TO_RGBA, gzFloat R_factor = GZ_FLOAT_ONE, gzFloat G_factor = GZ_FLOAT_ONE, gzFloat B_factor = GZ_FLOAT_ONE, gzFloat A_factor = GZ_FLOAT_ONE, gzFloat C_value = GZ_FLOAT_ONE);
	GZ_BASE_EXPORT gzVoid copyFrom(gzImage* image_1, gzImage* image_2, gzRGBASwizzle swizzle_1 = GZ_MAP_RGBA_TO_RGBA, gzFloat R_factor_1 = GZ_FLOAT_ONE, gzFloat G_factor_1 = GZ_FLOAT_ONE, gzFloat B_factor_1 = GZ_FLOAT_ONE, gzFloat A_factor_1 = GZ_FLOAT_ONE, gzFloat C_value_1 = GZ_FLOAT_ONE, gzRGBASwizzle swizzle_2 = GZ_MAP_RGBA_TO_RGBA, gzFloat R_factor_2 = GZ_FLOAT_ONE, gzFloat G_factor_2 = GZ_FLOAT_ONE, gzFloat B_factor_2 = GZ_FLOAT_ONE, gzFloat A_factor_2 = GZ_FLOAT_ONE, gzFloat C_value_2 = GZ_FLOAT_ONE);

	// Utility methods to manage image contents

	//!Invert the image colors.
	GZ_BASE_EXPORT	gzVoid	invert();

	//! normalize data by min/max or by stddev
	GZ_BASE_EXPORT	gzVoid	normalize(gzBool useStats = FALSE);

	//! MAX value of RGBA
	GZ_BASE_EXPORT	gzRGBA maxRGBA(const gzRGBA& threshold = gzRGBA());
	//! MIN value of RGBA
	GZ_BASE_EXPORT	gzRGBA minRGBA(const gzRGBA& threshold = gzRGBA());


	GZ_BASE_EXPORT	gzVoid	toGray();
	GZ_BASE_EXPORT	gzVoid	alphaMask(gzDouble level);
	GZ_BASE_EXPORT	gzVoid	alphaMask(const gzRGBA& mask);	// Only mask for RGB values
	GZ_BASE_EXPORT	gzVoid	alphaDiv();

	GZ_BASE_EXPORT	gzVoid	setTransparencyColor(const gzRGBA& mask, const gzFloat& minAlpha = 0.0f);	// Change full alpha transparency to this color if alpha<=minAlpha

	//!Flips the image vertical.
	GZ_BASE_EXPORT	gzBool	flipVertical();

	//!Flips the image horizontal.
	GZ_BASE_EXPORT	gzBool	flipHorizontal();

	GZ_BASE_EXPORT gzImage* part(gzUInt32 x, gzUInt32 y, gzUInt32 width, gzUInt32 height, gzUInt32 z = 0, gzUInt32 depth = 1);


	// Alpha checking utilites
	//!Checks if not all alpha values are equal to 1.
	/*!
	If you set the evaluateDDS to TRUE, you will check the DDS image contents. Else the dxt3 will encode
	to binary alpha	and dxt5 will encode to continius ALPHA
	*/
	GZ_BASE_EXPORT gzBool	hasSignificantAlpha(gzBool evaluateDDS = FALSE);

	//!Checks if not all alpha values are equal to 0 or 1.
	/*!
	If you set the evaluateDDS to TRUE, you will check the DDS image contents. Else the dxt3 will encode
	to binary alpha	and dxt5 will encode to continius ALPHA
	*/
	GZ_BASE_EXPORT gzBool	hasContiniousAlpha(gzBool evaluateDDS = FALSE, gzFloat minMaxDiff = 0.05f);

	// Commonn access methods
	//!Returns true if the alpha component is valid.
	GZ_BASE_EXPORT virtual gzBool  hasAlphaComponent();

	//!Returns the size in bytes of one row.
	GZ_BASE_EXPORT gzUInt32 getRowSize();

	//!Returns the size of an image with given size.
	GZ_BASE_EXPORT virtual gzUInt32 getArraySize(gzUInt32 width = 0, gzUInt32 height = 0, gzUInt32 depth = 0);

	//!Returns the size in bytes of one row aligned for width pixels.
	GZ_BASE_EXPORT virtual gzUInt32 getAlignedRowSize(gzUInt32 width);

	//! Sample function in float positions
	GZ_BASE_EXPORT gzRGBA  sample(gzFloat width, gzFloat height, gzUInt32 depth = 0);

	// ---------------- Pixel Interface ----------------------------

	//!Returns the RGBA value for the pixel at position (width, height).
	GZ_BASE_EXPORT virtual gzRGBA  getPixel(gzUInt32 width, gzUInt32 height, gzUInt32 depth = 0) override;

	//!Sets the color value for the pixel at position (width, height and optional depth).
	GZ_BASE_EXPORT virtual gzBool  setPixel(gzUInt32 width, gzUInt32 height, const gzRGBA& value, gzUInt32 depth = 0) override;

	//! returns TRUE (default) if image has origo in lower left corner
	GZ_BASE_EXPORT virtual gzBool	hasOriginAtLowerLeft() override;

	// Array management ------------------------------------------


	GZ_BASE_EXPORT ImageData& getArray() { return m_data; }
	GZ_BASE_EXPORT ImageData& createArray(gzBool clearData = FALSE);	// Based on width and height etc.

	GZ_BASE_EXPORT gzVoid		setArray(const gzArray<gzUByte>& array);
	GZ_BASE_EXPORT gzVoid		setArray(const gzDynamicArray<gzUByte>& array);
	GZ_BASE_EXPORT gzVoid		setArray(const ImageData& array);

	GZ_BASE_EXPORT gzBool		hasCreatedArray() { return m_hasCreatedArray; }
	GZ_BASE_EXPORT gzVoid		setCreatedArray(gzBool on) { m_hasCreatedArray = on; }

	//! Cloning ---------------------------------------------------
	//! 
	GZ_BASE_EXPORT virtual gzImage* cloneImageType() const;
	GZ_BASE_EXPORT virtual gzReference* clone() const override;

	// Sub Images (mipmaps,animations etc.)

	GZ_PROPERTY_EXPORT(gzSubImageType, SubImageType, GZ_BASE_EXPORT);

	//!Returns true if the image has a sub image.
	GZ_BASE_EXPORT gzBool	hasSubImage();

	//!Returns the number of sub images connected to the image.
	GZ_BASE_EXPORT gzUInt32	getNumberOfSubImages();

	//!Returns the sub image with index index.
	GZ_BASE_EXPORT gzImage* getSubImage(gzUInt32 index);

	GZ_BASE_EXPORT gzRefList<gzImage>& getSubImageList();

	//!Add a sub image to the image.
	/*!
	An image is added as sub image with index index to the image.
	*/
	GZ_BASE_EXPORT gzVoid	addSubImage(gzImage* image, gzInt32 index = -1);

	//!Removes the subimage image.
	GZ_BASE_EXPORT gzVoid	removeSubImage(gzImage* image);

	//!All sub images are removed.
	GZ_BASE_EXPORT gzVoid	removeAllSubImages();

	//! Mipmap generation
	GZ_BASE_EXPORT gzBool	createMipMaps(gzBool forceCreate=FALSE);

	// ---- Serializing --------------------------------

	//!Writes the gzImage data to the adapter.
	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter* adapter) override;

	//!Reads the gzImage data from the adapter.
	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter* adapter) override;

	//!Returns the size of the gzImage data.
	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter* adapter = NULL) const override;

	// Image templates

	//!Creates an image of type type.
	/*!
	Crete a new image with the following code:
	\code

	gzImage *image=gzImage::createImage(GZ_IMAGE_TYPE_RGBA_8));
	\endcode

	It is possible to specify a name for the image.
	*/
	GZ_BASE_EXPORT static gzImage* createImage(gzImageType type, const gzString& name = GZ_EMPTY_STRING);

	GZ_BASE_EXPORT static gzImage* createChecker(gzRGBA color_a = gzRGBA(1.0f, 1.0f, 1.0f, 1.0f), gzRGBA color_b = gzRGBA(0.0f, 0.0f, 0.0f, 1.0f), gzImageType type = GZ_IMAGE_TYPE_BW_8, gzUInt32 size_x = 512, gzUInt32 size_y = 512, gzUInt32 x_divs = 64, gzUInt32 y_divs = 64);

	// ------------------- Image Data Registration ------------------

	GZ_BASE_EXPORT gzVoid registerImageData(gzUInt32 bytes = 0);
	GZ_BASE_EXPORT gzVoid unRegisterImageData();

	GZ_BASE_EXPORT static gzUInt64 getRegisteredImageData();

protected:

	GZ_BASE_EXPORT gzFloat	sampleFunction(gzFloat x);


	ImageData 							m_data;

	gzUInt32							m_width;
	gzUInt32							m_height;
	gzUInt32							m_depth;


	gzUInt32							m_calcAlignedRowSize;
	gzBool								m_hasCreatedArray;
	gzBool								m_hasCalcAlignedRowSize;

	gzLateBindData<gzRefList<gzImage> >	m_subImageList;

private:

	gzUInt32							m_registeredImageData;
	static gzMutex						s_registeredImageDataLocker;
	static gzUInt64						s_registeredImageDataTotal;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzImage);

const gzString GZ_EVALUATE_EXTENSION = "";
const gzString GZ_TRY_ALL_EXTENSION = "*";

// !Image loader flags
/*! These flags defines the behaviour of hhow the loader processes the images at load time */

#define GZ_IMAGE_FLAG_NUM(x)	(gzSerializeAdapterFlags)(LLU(1)<<( x+GZ_SERIALIZE_ADAPTER_FLAG_MAX_SIZE))

const gzSerializeAdapterFlags	GZ_IMAGE_FLAGS_DEFAULT = (gzSerializeAdapterFlags)0;

/*!
This will flip .dds images referenced by the dataset as the .dds format is ambigious from some vendors.
*/
const gzSerializeAdapterFlags	GZ_IMAGE_FLAGS_FLIP_FLIPPED_IMAGES = GZ_IMAGE_FLAG_NUM(0);

/*!
The image will not be cached for later on usage and you will not use any cahced image so a new read is done. Normally when an image is read by a loader the image
is cached so consecutive loaders will use the same instance. Sometimes you want to change path with
the GIZMO_PATH environment variable to change time of year etc. Then you want to use the same name of
the image but a different file.
*/
const gzSerializeAdapterFlags	GZ_IMAGE_FLAGS_NO_CACHED_IMAGE = GZ_IMAGE_FLAG_NUM(1);

/*!
Gizmo3D normally tries to load alternate images when an image is not understood by the loader. E.g. a
database might reference a file “test.tiff” and there is no “tiff” reader registered. In that case
Gizmo3D normally want to find a “test.dds” or a “test.bmp” file. This flag disables that search.
*/
const gzSerializeAdapterFlags	GZ_IMAGE_FLAGS_NO_ALTERNATE_IMAGE_EXT = GZ_IMAGE_FLAG_NUM(2);
const gzSerializeAdapterFlags	GZ_IMAGE_FLAGS_IGNORE_IMAGE_MIPMAPS = GZ_IMAGE_FLAG_NUM(3);

//! Use this flag to load dxt1 images (.dds) without alpha
const gzSerializeAdapterFlags	GZ_IMAGE_FLAGS_NO_DXT1_ALPHA = GZ_IMAGE_FLAG_NUM(4);

const gzSerializeAdapterFlags	GZ_IMAGE_FLAGS_NO_MISSING_REF_IMAGE_WARN = GZ_IMAGE_FLAG_NUM(5);


//! Definition of how many flags there are in gzImageFlags
const gzUInt64 GZ_IMAGE_FLAG_MAX_SIZE = GZ_SERIALIZE_ADAPTER_FLAG_MAX_SIZE + 6;	// Number of flags in image flag set


// Extensions (same flag as db or above db ) ---------------------------------------------

// Fixed. Do not change !
const gzSerializeAdapterFlags	GZ_IMAGE_FLAGS_READ_ONLY_HEADER = ((gzUInt64)1) << (20 + 6 + 6); //GZ_DB_FLAGS_READ_ONLY_HEADER


//******************************************************************************
// Class	: gzImageManager
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990223	Created 
//									
//******************************************************************************

class  gzImageManager : public gzThreadSafeReference
{
public:
	//!Destructor
	GZ_BASE_EXPORT virtual ~gzImageManager() {};

	//!Register the image manager manager.
	GZ_BASE_EXPORT static gzVoid	registerManager(gzImageManager* manager);

	//!Unregister the image manager manager.
	GZ_BASE_EXPORT static gzBool	unregisterManager(gzImageManager* manager);

	//!Unregister the image manager manager.
	GZ_BASE_EXPORT static gzBool	unregisterExtension(const gzString &extension);

	//!Unregister all registered image managers.
	GZ_BASE_EXPORT static gzVoid	unregisterManagers();

	//!Loads an image.
	GZ_BASE_EXPORT static gzImage* loadImage(const gzString& url, gzString extension = GZ_EVALUATE_EXTENSION, gzSerializeAdapterFlags flags = GZ_IMAGE_FLAGS_DEFAULT, gzUInt32 version = 0, const gzString& password = GZ_EMPTY_STRING, gzReference* associatedData = NULL, gzUInt32* adapterLength = NULL, gzString* errorString = NULL, gzSerializeAdapterError* errorType = NULL);

	//!Loads an image from an adapter. 
	GZ_BASE_EXPORT virtual gzImage* loadImage(gzSerializeAdapter* adapter);

	//!Saves the image.
	GZ_BASE_EXPORT static gzBool	saveImage(gzImage* image, const gzString& url, gzString extension = GZ_EVALUATE_EXTENSION, gzSerializeAdapterFlags flags = GZ_IMAGE_FLAGS_DEFAULT, gzUInt32 version = 0, const gzString& password = GZ_EMPTY_STRING);

	//!Saves the image to an adapter.
	GZ_BASE_EXPORT virtual gzBool	saveImage(gzImage* image, gzSerializeAdapter* adapter);

	GZ_BASE_EXPORT static gzVoid	clearCachedImages(gzBool leaveShared = TRUE);

	GZ_BASE_EXPORT static gzVoid	updateCachedImage(gzImage* oldImage, gzImage* newImage);

	GZ_BASE_EXPORT static gzVoid	registerImageFactoryObjects();

	GZ_BASE_EXPORT static gzString	getAllExtensions(gzBool onlySavers=FALSE);

	//!Returns the image extension. ("rgb:rgba:int") etc..
	GZ_BASE_EXPORT virtual gzString	getExtensions() = 0;

	//!Returns the image version for a certain extension
	GZ_BASE_EXPORT virtual gzUInt32	getVersion(const gzString& extension) = 0;

	GZ_BASE_EXPORT static gzRefPointer<gzImageManager> getImageManager(const gzString& extension, gzUInt32 version = 0);

	//! return true if class can save images
	GZ_BASE_EXPORT virtual gzBool	canSave() = 0;

	GZ_BASE_EXPORT virtual	gzBool	useDeepCopy() { return FALSE; }	// Default behaviour is shallow share

	GZ_STATIC_PROPERTY_EXPORT(gzBool, KeepRetryLoading, GZ_BASE_EXPORT);

protected:

	//! displays info about registration for a certain extension
	GZ_BASE_EXPORT virtual gzVoid	registerManager(const gzString& extension);

	static gzRefDict<gzString, gzImageManager>	s_registeredImageManagers;

	static gzMutex								s_managerLock;

	static gzRefDict<gzString, gzImage>	s_imageCache;

};

GZ_DECLARE_REFPTR(gzImageManager);

//******************************************************************************
// Class	: gzRefImage
//									
// Purpose  : A soft url reference in name that is not serialized as raw data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990223	Created 
//									
//******************************************************************************
class gzRefImage : public gzImage
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// typed interface

	GZ_BASE_EXPORT gzRefImage(const gzString& name = GZ_EMPTY_STRING);
	GZ_BASE_EXPORT virtual ~gzRefImage() {};

	// ---- Cloning ------------------------------------

	GZ_BASE_EXPORT virtual gzReference* clone() const override;

	// ---- Serializing --------------------------------

	//!Writes the gzImage data to the adapter.
	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter* adapter) override;

	//!Reads the gzImage data from the adapter.
	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter* adapter) override;

	//!Returns the size of the gzImage data.
	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter* adapter = NULL) const override;

};

#endif
