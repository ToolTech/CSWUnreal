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
// File			: gzTextureRender.h
// Module		: 
// Description	: Class definition of the gzRenderBase class types
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
// AMO	111111	Created file 	
//
//******************************************************************************
#ifndef __GZ_TEXTURE_RENDER_H__
#define __GZ_TEXTURE_RENDER_H__

/*!	\file 
	\brief Basic implementation of rendering directly into texture object

*/

#include "gzRenderBase.h"

class gzFrameBufferBindInfo
{
public:
	//!Default constructor.
	GZ_GRAPH_EXPORT gzFrameBufferBindInfo();

	//!Destructor
	GZ_GRAPH_EXPORT virtual ~gzFrameBufferBindInfo();

	gzUInt32							bindID;
	gzUInt32							contextEnumerator;
	gzRefPointer<gzRefIdStorage>	bindPool;
};


enum gzTextureRenderType
{
	GZ_TEXTURE_RENDER_RGBA8,
	GZ_TEXTURE_RENDER_DEPTH
};

//******************************************************************************
// Class	: gzTextureRender
//									
// Purpose  : Base class for rendering of a scene graph to a texture
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	111111	Created 
//									
//******************************************************************************
class gzTextureRender : public gzRenderBase 
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzTextureRender();

	GZ_GRAPH_EXPORT virtual ~gzTextureRender();

	GZ_GRAPH_EXPORT virtual gzBool refresh() override; // route to texture

	GZ_GRAPH_EXPORT virtual gzBool refreshTexture(); // route to texture

	GZ_PROPERTY_EXPORT(gzTexturePtr,		Texture,		GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt32XY,			Size,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzTextureRenderType, RenderType,		GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool,				AutoMipMaps,	GZ_GRAPH_EXPORT);

private:

	gzDynamicArray<gzFrameBufferBindInfo>	m_bindInfo;

};

GZ_DECLARE_REFPTR(gzTextureRender);

//******************************************************************************
// Class	: gzTextureRenderNode
//									
// Purpose  : To be put in a scene graph to automatically render a texture upon scene refresh
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	111114	Created 
//									
//******************************************************************************
class gzTextureRenderNode : public gzNode 
{
public:

	GZ_GRAPH_EXPORT gzTextureRenderNode(const gzString & name=GZ_EMPTY_STRING);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	GZ_PROPERTY_EXPORT(gzTextureRenderPtr,	TextureRender,	GZ_GRAPH_EXPORT);

private:

	//TODO: fix in context instead

	gzGuard<gzBool> m_inRender;
};

GZ_DECLARE_REFPTR(gzTextureRenderNode);


#endif // __GZ_TEXTURE_RENDER_H__
