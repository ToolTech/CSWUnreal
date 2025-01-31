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
// File			: gzTexture.h
// Module		: 
// Description	: Class definition of the gzTexture class
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
// AMO	990210	Created file 	
// LJH	041029	Added comments
//
//******************************************************************************
#ifndef __GZ_TEXTURE_H__
#define __GZ_TEXTURE_H__

/*!	\file 
	\brief Base definitions for object textures

*/

#include "gzObject.h"
#include "gzMatrix.h"
#include "gzImage.h"

//!The available magnification filters.
enum gzTextureMagFilter
{
	GZ_TEXTURE_MAG_NEAREST	=GZ_NEAREST,		//!<	The texel with coordinates nearest the center of the pixel is used for magnification.
	GZ_TEXTURE_MAG_LINEAR	=GZ_LINEAR,			//!<	A weighted average of the texels nearest to the center of the pixel is used for magnification.
};

//!The available minification filters
enum gzTextureMinFilter
{
	GZ_TEXTURE_MIN_NEAREST					=GZ_NEAREST,					//!<	The texel with coordinates nearest the center of the pixel is used for minification.
	GZ_TEXTURE_MIN_LINEAR					=GZ_LINEAR,						//!<	A weighted average of the texels nearest to the center of the pixel is used for minification.
	GZ_TEXTURE_MIN_NEAREST_MIPMAP_NEAREST	=GZ_NEAREST_MIPMAP_NEAREST,		//!<	The nearest pixel in an individual mipmap is used.
	GZ_TEXTURE_MIN_NEAREST_MIPMAP_LINEAR	=GZ_NEAREST_MIPMAP_LINEAR,		//!<	The values of nearest texel in each of the two mipmaps are selected and linear interpolated.
	GZ_TEXTURE_MIN_LINEAR_MIPMAP_NEAREST	=GZ_LINEAR_MIPMAP_NEAREST,		//!<	Linear interpolation is used within an individual mipmap.
	GZ_TEXTURE_MIN_LINEAR_MIPMAP_LINEAR		=GZ_LINEAR_MIPMAP_LINEAR,		//!<	Linear interpolates the value in each of two maps and then linear interpolates these two resulting values.
};

//!Specifies the available texture wrapping methods.
/*!
Note that if a texture has a border of a specified texture border color is used the visibel result is influenced by 
both the wrapping mode and the filtering method. 
*/
enum gzTextureWrapMode
{
	GZ_TEXTURE_WRAP_CLAMP			= GZ_CLAMP,				//!<	Texture coordinates larger than 1.0 is set to 1.0 and coordinate values less than 0.0 is set to 0.0.
	GZ_TEXTURE_WRAP_REPEAT			= GZ_REPEAT,			//!<	The texture is repeated when texture coordinates outside the range [0, 1] is used.
	GZ_TEXTURE_WRAP_CLAMP_TO_EDGE	= GZ_CLAMP_TO_EDGE,		//!<	The border is ignored. Texels near the edge is used for texturing.
	GZ_TEXTURE_WRAP_CLAMP_TO_BORDER	= GZ_CLAMP_TO_BORDER,	//!<	Texture coordinates outside the range [0, 1] uses only the border texels for texture application.
	GZ_TEXTURE_WRAP_MIRRORED_REPEAT	= GZ_MIRRORED_REPEAT,	//!<	Repeats the texture but flips the orientation of the texture at every integer texture coordinate.
};

enum gzTextureCompareMode
{
	GZ_TEXTURE_COMPARE_MODE_NONE			= GZ_NONE,
	GZ_TEXTURE_COMPARE_MODE_R_TO_TEXTURE	= GZ_COMPARE_R_TO_TEXTURE,
};

enum gzTextureCompareFunc
{
	GZ_TEXTURE_COMPARE_FUNC_NEVER		=GZ_NEVER,		//!<	The TEXTURE is never accepted
	GZ_TEXTURE_COMPARE_FUNC_ALWAYS		=GZ_ALWAYS,		//!<	The TEXTURE is always accepted
	GZ_TEXTURE_COMPARE_FUNC_LESS		=GZ_LESS,		//!<	True if reference  < TEXTURE 
	GZ_TEXTURE_COMPARE_FUNC_LEQUAL		=GZ_LEQUAL,		//!<	True if reference  = TEXTURE 
	GZ_TEXTURE_COMPARE_FUNC_EQUAL		=GZ_EQUAL,		//!<	True if reference  = TEXTURE 
	GZ_TEXTURE_COMPARE_FUNC_GEQUAL		=GZ_GEQUAL,		//!<	True if reference  = TEXTURE 
	GZ_TEXTURE_COMPARE_FUNC_GREATER		=GZ_GREATER,	//!<	True if reference  > TEXTURE  
	GZ_TEXTURE_COMPARE_FUNC_NOTEQUAL	=GZ_NOTEQUAL	//!<	True if reference  != TEXTURE 
};

enum gzTextureType
{
	GZ_TEXTURE_TYPE_1D				= GZ_TEXTURE_1D,
	GZ_TEXTURE_TYPE_2D				= GZ_TEXTURE_2D,
	GZ_TEXTURE_TYPE_3D				= GZ_TEXTURE_3D,
};

class gzContext;

//******************************************************************************
// Class	: gzBindTextureInfo
//									
// Purpose  : Keep bind info about texture per context
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030422	Created 
//									
//******************************************************************************
class gzBindTextureInfo
{
public:

	gzBindTextureInfo():bindID(0),contextEnumerator(0),isBind(FALSE){};

	gzRefPointer<gzRefIdStorage>	bindPool;
	gzUInt32						bindID;
	gzUInt32						contextEnumerator;
	gzBool							isBind;
};

//! Internal texture format. Used as a hint for GFX hw.
enum gzGfxInternalTextureFormat
{
	GZ_TEX_FORMAT_LUMINANCE						=	GZ_LUMINANCE,			//! equiv to setComponents(1)
	GZ_TEX_FORMAT_LUMINANCE_ALPHA				=	GZ_LUMINANCE_ALPHA,		//! equiv to setComponents(2)
	GZ_TEX_FORMAT_RGB							=	GZ_RGB,					//! equiv to setComponents(3)
	GZ_TEX_FORMAT_RGBA							=	GZ_RGBA,				//! equiv to setComponents(4)
	
	GZ_TEX_FORMAT_LUMINANCE_FLOAT				=	GZ_LUMINANCE32F,		
	GZ_TEX_FORMAT_LUMINANCE_ALPHA_FLOAT			=	GZ_LUMINANCE_ALPHA32F,	
	GZ_TEX_FORMAT_RGB_FLOAT						=	GZ_RGB32F,				
	GZ_TEX_FORMAT_RGBA_FLOAT					=	GZ_RGBA32F,				

	GZ_TEX_FORMAT_GZ_INTENSITY					=	GZ_INTENSITY,

	GZ_TEX_FORMAT_LUMINANCE_HALF				=	GZ_LUMINANCE16F,		
	GZ_TEX_FORMAT_LUMINANCE_ALPHA_HALF			=	GZ_LUMINANCE_ALPHA16F,	
	GZ_TEX_FORMAT_RGB_HALF						=	GZ_RGB16F,				
	GZ_TEX_FORMAT_RGBA_HALF						=	GZ_RGBA16F,				

	GZ_TEX_FORMAT_ALPHA							=	GZ_ALPHA,						
	GZ_TEX_FORMAT_ALPHA4						=	GZ_ALPHA4,						
	GZ_TEX_FORMAT_ALPHA8						=	GZ_ALPHA8,						
	GZ_TEX_FORMAT_ALPHA12						=	GZ_ALPHA12,						
	GZ_TEX_FORMAT_ALPHA16						=	GZ_ALPHA16,						
	GZ_TEX_FORMAT_COMPRESSED_ALPHA				=	GZ_COMPRESSED_ALPHA,			
	GZ_TEX_FORMAT_COMPRESSED_LUMINANCE			=	GZ_COMPRESSED_LUMINANCE,		
	GZ_TEX_FORMAT_COMPRESSED_LUMINANCE_ALPHA	=	GZ_COMPRESSED_LUMINANCE_ALPHA,	
	GZ_TEX_FORMAT_COMPRESSED_INTENSITY			=	GZ_COMPRESSED_INTENSITY,		
	GZ_TEX_FORMAT_COMPRESSED_RGB				=	GZ_COMPRESSED_RGB,				
	GZ_TEX_FORMAT_COMPRESSED_RGBA				=	GZ_COMPRESSED_RGBA,				
	GZ_TEX_FORMAT_DEPTH_COMPONENT				=	GZ_DEPTH_COMPONENT,				
};


//******************************************************************************
// Class	: gzTexture
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990210	Created 
//									
//******************************************************************************
class gzTexture : public gzObject,public gzNameInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	//!Constructor.
	GZ_GRAPH_EXPORT gzTexture(const gzString& name=GZ_EMPTY_STRING);

	//!Constructor which creates a copy of the input texture.
	GZ_GRAPH_EXPORT gzTexture( const gzTexture &copy);

	//!Destructor.
	GZ_GRAPH_EXPORT virtual ~gzTexture();

	GZ_GRAPH_EXPORT gzBool	virtual activate(gzContext *context);
	GZ_GRAPH_EXPORT static gzVoid deactivate(gzContext *context);

	GZ_GRAPH_EXPORT gzUInt32	getTextureID(gzContext *context);


	//!Specifies an image for the texture. 
	/*!
	\param image is the image that will be visible when the texture is applied to a geometry.
	*/
	GZ_GRAPH_EXPORT gzImage *			setImage(gzImage *image, gzBool ignoreAlpha=FALSE);

	//!Returns the texture image.
	GZ_GRAPH_EXPORT gzImage *			getImage();


	/*! set internal format components 1-4 on GFX HW */
	GZ_GRAPH_EXPORT gzVoid				setComponents(gzUByte count,gzComponentType type=GZ_COMPONENT_UNSIGNED_BYTE,gzBool ignoreAlpha=FALSE);


	/*! set internal format used e.g. GZ_TEX_FORMAT_RGBA on GFX HW */
	GZ_GRAPH_EXPORT gzVoid						setInternalFormat(gzGfxInternalTextureFormat format);
	GZ_GRAPH_EXPORT gzGfxInternalTextureFormat	getInternalFormat();
	

	//!Sets the wrapping mode for the texture in the S direction
	/*!
	\param wrap specifies the wrapping method that shall be used to apply the texture to a geometry.
	\sa gzTextureWrapMode 
	*/
	GZ_GRAPH_EXPORT gzVoid				setWrapS(gzTextureWrapMode wrap);

	//!Returns the wrapping mode used in the S direction.
	GZ_GRAPH_EXPORT gzTextureWrapMode	getWrapS();


	//!Sets the wrapping mode for the texture in the T direction
	/*!
	\param wrap specifies the wrapping method that shall be used to apply the texture to a geometry.
	\sa gzTextureWrapMode 
	*/
	GZ_GRAPH_EXPORT gzVoid				setWrapT(gzTextureWrapMode wrap);

	//!Returns the wrapping mode used in the T direction.
	GZ_GRAPH_EXPORT gzTextureWrapMode	getWrapT();
	
	//!Sets the wrapping mode for the texture in the R (3D( direction
	/*!
	\param wrap specifies the wrapping method that shall be used to apply the texture to a geometry.
	\sa gzTextureWrapMode 
	*/
	GZ_GRAPH_EXPORT gzVoid				setWrapR(gzTextureWrapMode wrap);

	//!Returns the wrapping mode used in the R (3D) direction.
	GZ_GRAPH_EXPORT gzTextureWrapMode	getWrapR();


	//!Sets type of magnification filter.
	/*!
	\param filter specifies the magnification filter used when the texture is enlarged on the screen.
	\sa gzTextureMagFilter
	*/
	GZ_GRAPH_EXPORT gzVoid				setMagFilter(gzTextureMagFilter filter);
	GZ_GRAPH_EXPORT gzTextureMagFilter	getMagFilter();

	//!Sets type of minification filter.
	/*!
	\param filter specifies the minification filter used when the size of texture on the screen is reduced.
	\sa gzTextureMinfilter
	*/
	GZ_GRAPH_EXPORT gzVoid				setMinFilter(gzTextureMinFilter filter);
	GZ_GRAPH_EXPORT gzTextureMinFilter	getMinFilter();


	//!Sets a color for the texture border.
	GZ_GRAPH_EXPORT gzVoid				setBorder(gzFloat red , gzFloat green , gzFloat blue , gzFloat alpha); 


	//!Sets the width for the texture border.
	GZ_GRAPH_EXPORT gzVoid				setBorderWidth(gzUInt16 width);

	//!Returns the width of the texture border.
	GZ_GRAPH_EXPORT gzUInt16			getBorderWidth();

	GZ_GRAPH_EXPORT gzVoid					setTextureCompareMode(gzTextureCompareMode mode);
	GZ_GRAPH_EXPORT gzTextureCompareMode	getTextureCompareMode();

	GZ_GRAPH_EXPORT gzVoid					setTextureCompareFunc(gzTextureCompareFunc func);
	GZ_GRAPH_EXPORT gzTextureCompareFunc	getTextureCompareFunc();

	//!Enables/ disables the use of mipmaps.
	/*!
	\param on is true if mipmaps are used, otherwise it is false.
	*/
	GZ_GRAPH_EXPORT gzVoid				useMipMaps(gzBool on);

	GZ_GRAPH_EXPORT gzBool				useMipMaps();

	//!Sets a list of images as mipmaps.
	GZ_GRAPH_EXPORT gzVoid				setMipMaps(const gzRefList<gzImage> &imageList);

	//!Returns a reflist of mipmap images.
	GZ_GRAPH_EXPORT gzRefList<gzImage> &getMipMaps();

	GZ_GRAPH_EXPORT gzBool				hasSubMipMaps();


	GZ_GRAPH_EXPORT gzVoid				setBind(gzBool bind);

	//! Drops context binding
	GZ_GRAPH_EXPORT gzVoid				reBind();

	GZ_GRAPH_EXPORT gzVoid				disposeImage(gzBool on=FALSE);
	GZ_GRAPH_EXPORT gzVoid				compressImageOnGPU(gzBool on=FALSE);

	//!Automatically generates mipmaps for the texture.
	GZ_GRAPH_EXPORT gzBool				createMipMaps(gzBool rebind=TRUE,gzBool forceCreate=FALSE);

	GZ_GRAPH_EXPORT gzVoid				setTextureType(gzTextureType type);
	GZ_GRAPH_EXPORT gzTextureType		getTextureType();

	GZ_GRAPH_EXPORT gzBool				checkUpdateContextTexture(gzUInt32 context_id);

	//! Excluded in rendering context
	GZ_PROPERTY_EXPORT(gzBool,	Excluded,	GZ_GRAPH_EXPORT);

	// ---------- Clone interface ---------------------------------------
	//!Clone interface.
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	//!Overrides the gzReference useDeepCopyMode() to use gzNodeCopyMode.
	GZ_GRAPH_EXPORT virtual gzBool useDeepCopy() override;

	// ---------- operators --------------------------------------------
	//!Equal operator
	/*!
	Returns true if two textures are equal.\n
	Otherwise false is returned.
	*/
	GZ_GRAPH_EXPORT gzBool operator==(const gzTexture &right) const;

	//!Not equal operator
	/*!
	Returns true if two textures not are equal. \n
	Otherwise false is returned.
	*/
	GZ_GRAPH_EXPORT gzBool operator!=(const gzTexture &right) const { return !operator==(right); }

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const override;


private:

	gzBool		transferImage(gzContext *context,gzBool forceImageUpload);
	gzBool		transferImage(gzImage *image,gzUInt32 level,gzBool fullUpload,gzContext *mainContext);
	gzVoid		checkImagePowerSize();
	

	gzDynamicArray<gzBindTextureInfo>	m_bindInfo;
	
	gzRefList<gzImage>					m_mipMaps;
	gzRefPointer<gzImage>				m_image;

	gzEnum								m_wrap_s;
	gzEnum								m_wrap_t;
	gzEnum								m_wrap_r;

	gzEnum								m_mag_filter;
	gzEnum								m_min_filter;

	gzEnum								m_compare_mode;
	gzEnum								m_compare_func;

	gzUInt32							m_texDataSize;
	
	gzLookupUpdateID					m_updateID;

	gzLateBindData<gzRGBA>				m_border_color;

	gzUInt16							m_borderWidth;

	gzGfxInternalTextureFormat			m_internalFormat;

	gzEnum								m_texType;

	gzBool								m_useMipMap:1;
	gzBool								m_bind:1;
	gzBool								m_disposeImage:1;
	gzBool								m_compressOnGPU:1;
	gzBool								m_subMipMaps:1;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzTexture);

// --------------------- gzTexturePreCache --------------------

class gzTexturePreCache
{
public:

	GZ_GRAPH_EXPORT	gzTexturePreCache();

	GZ_GRAPH_EXPORT gzVoid upload(gzContext *context);

	GZ_GRAPH_EXPORT gzVoid addTexture(gzTexture *texture);

	GZ_PROPERTY_EXPORT(gzUInt32,		MaxUploadsPerFrame,		GZ_GRAPH_EXPORT);

private:

	gzMutex					m_locker;

	gzRefList<gzTexture>	m_textures;

};

// ----------------------- gzSimpleImageStream -------------------

class gzSimpleImageStream : public gzImage , public gzObjectReceiver
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzSimpleImageStream(const gzString &channelName,gzSerializeAdapter *adapter=nullptr);

	// ---- Serializing --------------------------------

	//!Writes the gzImage data to the adapter.
	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;

	//!Reads the gzImage data from the adapter.
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;

	//!Returns the size of the gzImage data.
	GZ_GRAPH_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

	//! Clone
	GZ_GRAPH_EXPORT virtual gzReference *clone() const override;

protected:

	GZ_GRAPH_EXPORT gzVoid onObject(gzObject *object) override;
};

#endif
