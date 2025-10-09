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
// File			: gzFont.h
// Module		: 
// Description	: Class definition of the gzFont class
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
// AMO	001016	Created file
// TSV  140128  Added gzSerializeFontInfo
//
//******************************************************************************
#ifndef __GZ_FONT_H__
#define __GZ_FONT_H__

/*!	\file 
	\brief Base definitions for fonts

*/


#include "gzObject.h"
#include "gzDisplayList.h"

const gzString	GZ_FONT_DEFAULT_NAME		=	"courier";
const gzInt32		GZ_FONT_DEFAULT_COUNT		=	256;
const gzInt32		GZ_FONT_DEFAULT_HEIGHT		=	11;
const gzInt32		GZ_FONT_DEFAULT_WIDTH		=	0;

// Built in fonts

#define GZ_FONT_ARIAL_24			"arial",256,24,0,FALSE,FALSE,FALSE,FALSE,TRUE
#define GZ_FONT_ARIAL_24_UNDERLINE	"arial",256,24,0,FALSE,FALSE,TRUE,FALSE,TRUE
#define GZ_FONT_ARIAL_24_BOLD		"arial",256,24,0,FALSE,TRUE,FALSE,FALSE,TRUE
#define GZ_FONT_ARIAL_24_ITALIC		"arial",256,24,0,TRUE,FALSE,FALSE,FALSE,TRUE

#define GZ_FONT_DOM_CASUAL_24		"dom casual",256,24,0,FALSE,FALSE,FALSE,FALSE,TRUE
#define GZ_FONT_SYMBOL_24			"symbol",256,24,0,FALSE,FALSE,FALSE,FALSE,TRUE
#define GZ_FONT_PALACE_SRIPT_24		"palace script mt",256,24,0,FALSE,FALSE,FALSE,FALSE,TRUE

class GZ_GRAPH_EXPORT gzFontInfo 
{
public:

	gzFontInfo(	const gzString &	fontName		= GZ_FONT_DEFAULT_NAME , 
				const gzUInt16		characterCount	= GZ_FONT_DEFAULT_COUNT,
				const gzInt32		genericHeight	= GZ_FONT_DEFAULT_HEIGHT,
				const gzInt32		genericWidth	= GZ_FONT_DEFAULT_WIDTH,
				gzBool				italic			= FALSE,
				gzBool				bold			= FALSE,
				gzBool				underline		= FALSE,
				gzBool				strikeout		= FALSE,
				gzBool				antialias		= FALSE ); 

	gzBool operator ==(const gzFontInfo &) const;

	gzUInt32 hash() const ;

	//--- public attributes -------------------

	gzString	fontName;
	gzUInt16	characterCount;
	gzInt32		genericHeight;
	gzInt32		genericWidth;
	gzInt32		completeHeight;

	gzBool		italic;
	gzBool		bold;
	gzBool		underline;
	gzBool		strikeout;
	gzBool		antialias;
};

class GZ_GRAPH_EXPORT gzGlyphInfo 
{
public:

	gzGlyphInfo(gzFloat sizeX=0,gzFloat sizeY=0,gzFloat offsetX=0,gzFloat offsetY=0,gzFloat stepX=0,gzFloat stepY=0,gzFloat originX=0,gzFloat originY=0);

	gzFloat size_x;
	gzFloat size_y;

	gzFloat offset_x;
	gzFloat offset_y;

	gzFloat	step_x;
	gzFloat	step_y;

	gzFloat origin_x;
	gzFloat	origin_y;
};


//******************************************************************************
// Class	: gzFont
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	001016	Created 
//									
//******************************************************************************
class gzFont : public gzObject , public gzNameInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzFont(	const gzFontInfo & fontInfo=gzFontInfo() , gzBool createFromSystem=TRUE);

	GZ_GRAPH_EXPORT virtual ~gzFont();

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
	GZ_GRAPH_EXPORT virtual gzBool useDeepCopy() override;

	// ---------- Font interface ----------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid renderChar( gzContext *context , gzUInt16 index,const gzFloat & x,const gzFloat & y,const gzFloat & z,const gzFloat &scale=GZ_FLOAT_ONE);

	GZ_GRAPH_EXPORT virtual gzVoid beginRenderText(gzContext *context);

	GZ_GRAPH_EXPORT virtual gzVoid endRenderText(gzContext *context);

	GZ_GRAPH_EXPORT gzVec2		getSize( gzUInt16 index );

	GZ_GRAPH_EXPORT gzVec2		getStep( gzUInt16 index );

	GZ_GRAPH_EXPORT gzUInt16	getCharacterCount();

	GZ_GRAPH_EXPORT gzFloat		getRowHeight();

	GZ_GRAPH_EXPORT gzFloat		getBaseOffset();

	GZ_GRAPH_EXPORT gzFontInfo	getFontInfo();

	GZ_GRAPH_EXPORT gzVoid		disposeImageData();

	// ---------- Global fonts ------------------------------------------

	GZ_GRAPH_EXPORT static gzFont *getFont(	const gzFontInfo & fontInfo=gzFontInfo() , gzBool useBuiltIn=TRUE);

	GZ_GRAPH_EXPORT static gzVoid setFont(	const gzFontInfo & fontInfo , gzFont *font);

	GZ_GRAPH_EXPORT static gzVoid clearFontDictionary();

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

	// ---------- properties --------------------------------------------

	GZ_PROPERTY_EXPORT(gzTexturePtr,	FontTexture,	GZ_GRAPH_EXPORT);

	// ---------- Thread safe -------------------------------------------

	GZ_THREADSAFE_REF(m_locker);

	// ------- Static utility ------------------------------------------

	GZ_GRAPH_EXPORT static gzVoid displayDefaultText(gzContext *context,const gzString &text,const gzVec3 &pos,const gzFloat &scale=GZ_FLOAT_ONE);

protected:

	gzArray<gzGlyphInfo>						m_fontItems;

	gzFontInfo									m_fontInfo;

	gzUInt32									m_texWidth;

	gzUInt32									m_texHeight;

	gzFloat										m_baseOffset;

	gzMutex										m_locker;
	
private:

	static gzRefDict<gzFontInfo,gzFont>			s_fontDictionary;

	static gzMutex								s_fontLocker;
	
};

GZ_DECLARE_REFPTR(gzFont);

//******************************************************************************
// Class	: gzSerializeFontInfo
//									
// Purpose  : Help class for gzFontInfo storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// TSV	140128	Created 
//									
//******************************************************************************
class  gzSerializeFontInfo : public gzSerializeData
{
public:

	GZ_GRAPH_EXPORT gzSerializeFontInfo(gzBool useBigEndian=TRUE):m_useBigEndian(useBigEndian){};

	GZ_GRAPH_EXPORT virtual ~gzSerializeFontInfo(){};

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;

	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;

	GZ_GRAPH_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) override;


	GZ_GRAPH_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

	GZ_GRAPH_EXPORT operator gzFontInfo () const { return m_fi; }

	GZ_GRAPH_EXPORT const gzFontInfo  & operator = (const gzFontInfo &data) { m_fi=data ; return m_fi; }

	GZ_GRAPH_EXPORT gzVoid setBigEndian(gzBool useBigEndian){ m_useBigEndian=useBigEndian; }

private:

	gzBool		m_useBigEndian;
	gzFontInfo	m_fi;
};

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzFontInfo &data,const gzBool useBigEndian)
{
	gzSerializeFontInfo writer(useBigEndian);

	writer=data;

	writer.write(adapter);
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzFontInfo &data,const gzBool useBigEndian)
{
	gzSerializeFontInfo reader(useBigEndian);

	if(adapter->length()<reader.getDataSize())
		return FALSE;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzFontInfo &data,const gzBool useBigEndian)
{
	gzSerializeFontInfo writer(useBigEndian);

	writer=data;

	writer.pushBack(adapter);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzFontInfo &data,const gzBool /*useBigEndian*/)
{
	gzSerializeFontInfo	writer;
	writer=data;
	return writer.getDataSize(adapter);
}

#endif
