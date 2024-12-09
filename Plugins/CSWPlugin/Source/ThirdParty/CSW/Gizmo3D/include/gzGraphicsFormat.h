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
// File			: gzGraphicsFormat.h
// Module		: 
// Description	: Class definition of the gzGraphicsFormat class
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
// AMO	990614	Created file 	
// AMO	120216	Moved to gzGraph library for consistence			(2.6.2)
//
//******************************************************************************
#ifndef __GZ_GRAPHICSFORMAT_H__
#define __GZ_GRAPHICSFORMAT_H__

/*!	\file 
	\brief Base definitions for graphic formats

*/

#include "gzReference.h"
#include "gzGraphicsAbstractionLayer.h"
#include "gzContext.h"

enum gzGraphicsFormatScreenPart
{
	GZ_GRAPHICS_FORMAT_SCREEN_BOTTOM	=1<<0,
	GZ_GRAPHICS_FORMAT_SCREEN_TOP		=1<<1,
	GZ_GRAPHICS_FORMAT_SCREEN_LEFT		=1<<2,
	GZ_GRAPHICS_FORMAT_SCREEN_RIGHT		=1<<3,

	GZ_GRAPHICS_FORMAT_SCREEN_FULL=	15,
};

GZ_USE_BIT_LOGIC(gzGraphicsFormatScreenPart);

class gzGraphicsFormat : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);

	GZ_GRAPH_EXPORT gzGraphicsFormat( gzInt32 redbits=8 , gzInt32 greenbits=8 , gzInt32 bluebits=8 , gzInt32 alphabits=0 , gzInt32 stencilbits=0 ,
										gzInt32 depthbits=32 , gzInt32 accredbits=0 , gzInt32 accgreenbits=0 , gzInt32 accbluebits=0  , gzInt32 accalphabits=0 );

	GZ_GRAPH_EXPORT virtual	~gzGraphicsFormat();

	GZ_GRAPH_EXPORT gzVoid	setRGBBits( gzInt32 redbits , gzInt32 greenbits , gzInt32 bluebits  );
	
	GZ_GRAPH_EXPORT gzVoid	setRedBits(gzInt32 bits);
	GZ_GRAPH_EXPORT gzVoid	setGreenBits(gzInt32 bits);
	GZ_GRAPH_EXPORT gzVoid	setBlueBits(gzInt32 bits);
	
	GZ_GRAPH_EXPORT gzInt32	getRedBits();
	GZ_GRAPH_EXPORT gzInt32	getGreenBits();
	GZ_GRAPH_EXPORT gzInt32	getBlueBits();
	GZ_GRAPH_EXPORT gzInt32	getColorBits();
	

	GZ_GRAPH_EXPORT gzBool	useDoubleBuffer() const;
    GZ_GRAPH_EXPORT gzVoid	useDoubleBuffer( gzBool enable );

    GZ_GRAPH_EXPORT gzBool	useDepth() const;
    GZ_GRAPH_EXPORT gzVoid	useDepth( gzBool enable );
	GZ_GRAPH_EXPORT gzVoid	setDepthBits( gzInt32 bits );
	GZ_GRAPH_EXPORT gzInt32	getDepthBits();

    GZ_GRAPH_EXPORT gzBool	useAlpha() const;
    GZ_GRAPH_EXPORT gzVoid	useAlpha( gzBool enable );
	GZ_GRAPH_EXPORT gzVoid	setAlphaBits(gzInt32 bits );
	GZ_GRAPH_EXPORT gzInt32	getAlphaBits();

    GZ_GRAPH_EXPORT gzBool	useAccum() const;
    GZ_GRAPH_EXPORT gzVoid	useAccum( gzBool enable );

	GZ_GRAPH_EXPORT gzVoid	setAccumBits( gzInt32 redbits , gzInt32 greenbits , gzInt32 bluebits  , gzInt32 alphabits=0 );
	
	GZ_GRAPH_EXPORT gzVoid	setAccumRedBits(gzInt32 bits);
	GZ_GRAPH_EXPORT gzVoid	setAccumGreenBits(gzInt32 bits);
	GZ_GRAPH_EXPORT gzVoid	setAccumBlueBits(gzInt32 bits);
	GZ_GRAPH_EXPORT gzVoid	setAccumAlphaBits(gzInt32 bits);
	
	GZ_GRAPH_EXPORT gzInt32	getAccumRedBits();
	GZ_GRAPH_EXPORT gzInt32	getAccumGreenBits();
	GZ_GRAPH_EXPORT gzInt32	getAccumBlueBits();
	GZ_GRAPH_EXPORT gzInt32	getAccumAlphaBits();
	GZ_GRAPH_EXPORT gzInt32	getAccumBits();


    GZ_GRAPH_EXPORT gzBool	useStencil() const;
    GZ_GRAPH_EXPORT gzVoid	useStencil( gzBool enable );
	GZ_GRAPH_EXPORT gzVoid	setStencilBits(gzInt32 bits );
	GZ_GRAPH_EXPORT gzInt32	getStencilBits();

	GZ_GRAPH_EXPORT gzVoid	setTransparentColor(const gzRGBA &color);
	GZ_GRAPH_EXPORT gzRGBA	getTransparentColor();

	GZ_GRAPH_EXPORT gzVoid	useTransparentColor(gzBool on);
	GZ_GRAPH_EXPORT gzBool	useTransparentColor() const;

	GZ_GRAPH_EXPORT gzVoid	useFullScreen(gzBool on);
	GZ_GRAPH_EXPORT gzBool	useFullScreen() const;

	GZ_GRAPH_EXPORT gzVoid	useStereo(gzBool on);
	GZ_GRAPH_EXPORT gzBool	useStereo() const;

	GZ_GRAPH_EXPORT gzVoid	useMultisample(gzBool on);
	GZ_GRAPH_EXPORT gzBool	useMultisample() const;

	GZ_GRAPH_EXPORT gzVoid	setMultisamples(gzInt32 samples);
	GZ_GRAPH_EXPORT gzInt32	getMultisamples();

	GZ_GRAPH_EXPORT gzVoid	setFullScreenWidth(gzInt32 width=0);		// Best hit
	GZ_GRAPH_EXPORT gzInt32	getFullScreenWidth();

	GZ_GRAPH_EXPORT gzVoid	setFullScreenHeight(gzInt32 height=0);	// Best hit
	GZ_GRAPH_EXPORT gzInt32	getFullScreenHeight();

	GZ_GRAPH_EXPORT gzVoid	setFullScreenFrequency(gzInt32 hz=0);		// default rate = 0
	GZ_GRAPH_EXPORT gzInt32	getFullScreenFrequency() const ;

	GZ_GRAPH_EXPORT gzVoid	notifyFormat();

	GZ_GRAPH_EXPORT gzVoid	setDefault();
	
	GZ_GRAPH_EXPORT static gzVoid clearDefault();
	GZ_GRAPH_EXPORT static	gzGraphicsFormat * getDefault();

	GZ_PROPERTY_EXPORT(gzBool,							UseFullDesktop,		GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzInt32,							OffsetX,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzInt32,							OffsetY,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzGraphicsFormatScreenPart,		ScreenPart,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool,							OnTop,				GZ_GRAPH_EXPORT);

private:

	enum CAPS_BITS
	{	
		GZ_USE_DOUBLE_BUFFER		=	(1<<0),
		GZ_USE_ALPHA				=	(1<<1),
		GZ_USE_ACCUM				=	(1<<2),
		GZ_USE_STENCIL				=	(1<<3),
		GZ_USE_DEPTH				=	(1<<4),
		GZ_USE_STEREO				=	(1<<5),
		GZ_USE_MULTISAMPLE			=	(1<<6),
		GZ_USE_FULLSCREEN			=	(1<<7),
		GZ_USE_TRANSPARENT_COLOR	=	(1<<8),
	};

	
	gzUInt16	m_enable;

	gzInt32		m_red_bits;
	gzInt32		m_green_bits;
	gzInt32		m_blue_bits;
	gzInt32		m_alpha_bits;
	gzInt32		m_depth_bits;
	gzInt32		m_stencil_bits;
	gzInt32		m_accum_red_bits;	
	gzInt32		m_accum_green_bits;	
	gzInt32		m_accum_blue_bits;	
	gzInt32		m_accum_alpha_bits;	

	gzInt32		m_fullScreenWidth;
	gzInt32		m_fullScreenHeight;
	gzInt32		m_fullScreenFrequency;

	gzInt32		m_multisamples;

	gzRGBA		m_transparentColor;
	
	static gzRefPointer<gzGraphicsFormat> s_defaultFormat;
};

GZ_DECLARE_REFPTR(gzGraphicsFormat);

#endif // __GZ_GRAPHICSFORMAT_H__


