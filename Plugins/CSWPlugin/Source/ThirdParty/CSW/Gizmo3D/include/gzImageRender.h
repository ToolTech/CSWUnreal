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
// File			: gzImageRender.h
// Module		: 
// Description	: Class definition of the gzImageRender class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.201
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
// AMO	131015	Created file 										(2.7.2)
// AMO	140210	Updated ImageRender with size and format params		(2.7.4)
//
//******************************************************************************
#ifndef __GZ_IMAGE_RENDER_H__
#define __GZ_IMAGE_RENDER_H__

/*!	\file 
	\brief Base definitions of a Gizmo3D Image Renderer

*/

#include "gzTextureRender.h"

//******************************************************************************
// Class	: gzImageRender
//									
// Purpose  : Base class for rendering of a scene graph to an image
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
class gzImageRender : public gzRenderBase 
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzImageRender(gzUInt32 maxWidth=1024,gzUInt32 maxHeight=1024,gzGraphicsFormat *format=nullptr);

	GZ_GRAPH_EXPORT virtual ~gzImageRender();

	GZ_GRAPH_EXPORT virtual gzBool refresh() override; // route to texture

	GZ_GRAPH_EXPORT virtual gzBool refreshImage(); // route to texture

	//! Drops context binding of VBO
	GZ_GRAPH_EXPORT gzVoid reBind();

	//! Render active context directly into image
	GZ_GRAPH_EXPORT gzVoid renderImage(gzUInt32 bltSrc=0,gzUInt32 bltDest=0);

	GZ_PROPERTY_EXPORT(gzImagePtr,			Image,	GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT_(gzUInt32XY,			Size,	GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzGraphicsFormatPtr,	Format,	GZ_GRAPH_EXPORT);

private:

	gzDynamicArray<gzFrameBufferBindInfo>	m_bindInfo;
	gzDynamicArray<gzFrameBufferBindInfo>	m_bindInfoMultisample;
};

GZ_DECLARE_REFPTR(gzImageRender);

#endif // __GZ_IMAGE_RENDER_H__
