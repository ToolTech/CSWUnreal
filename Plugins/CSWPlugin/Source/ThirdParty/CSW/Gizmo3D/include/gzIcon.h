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
// File			: gzIcon.h
// Module		: 
// Description	: Class definition of the gzGroup class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.306
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
// SEP	250923	Created file 									(2.12.267)
//
//******************************************************************************
#ifndef __GZ_ICON_H__
#define __GZ_ICON_H__

#include "gzNode.h"
#include "gzFont.h"

// Common 2D text start positions
const gzVec3 GZ_ICON_UPPER_LEFT_POS=gzVec3((gzFloat)-1,(gzFloat)1,(gzFloat)0);
const gzVec3 GZ_ICON_LOWER_LEFT_POS=gzVec3((gzFloat)-1,(gzFloat)-1,(gzFloat)0);
const gzVec3 GZ_ICON_CENTER_POS=gzVec3((gzFloat)0,(gzFloat)0,(gzFloat)0);

// 20250901070123utc a56766 TODO: insert correct class documentation here
class gzIcon : public gzNode
{
public:
	GZ_GRAPH_EXPORT gzIcon(const gzString &name=GZ_EMPTY_STRING);

  GZ_GRAPH_EXPORT virtual ~gzIcon() {};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
	GZ_GRAPH_EXPORT virtual gzVoid	setCopyMode(const gzCopyMode &mode) override;

	// ---------- text commands -----------------------------------------

	GZ_GRAPH_EXPORT gzVoid useOverlay(gzBool on);

	GZ_GRAPH_EXPORT gzVoid use2DPosition(gzBool on);

	GZ_GRAPH_EXPORT gzVoid set2DPosition( gzInt16 x_off_pixels=0, gzInt16 y_off_pixels=0,const gzVec3 &startPosition=GZ_ICON_UPPER_LEFT_POS);

	GZ_GRAPH_EXPORT gzVoid setColor(const gzVec4 &color);

	GZ_GRAPH_EXPORT gzVoid useScreenFixedPositioning(gzBool on=TRUE);

	GZ_GRAPH_EXPORT gzVoid useTransparentBackground(gzBool on=TRUE);

	GZ_GRAPH_EXPORT gzVoid renderIcon(gzContext *context, gzVec3 rasterpos);

	// ---------- overall orientation etc.. ------------------------------

	GZ_GRAPH_EXPORT gzVoid	setScale(const gzVec3 &scale);
	GZ_GRAPH_EXPORT gzVoid	setScale(gzFloat scale);

	GZ_GRAPH_EXPORT gzVoid	setHPR(const gzVec3 &hpr);
	GZ_GRAPH_EXPORT gzVoid	setHPR(gzFloat heading,gzFloat pitch,gzFloat roll);

  GZ_GRAPH_EXPORT gzVoid setDimensions(gzInt32 width, gzInt32 height);

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzActionStage  useActionStage( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Properties -------------------------------------------

	GZ_PROPERTY_EXPORT(gzFloat,					DeltaX,			GZ_GRAPH_EXPORT);	//!< If non zero it defines the delta x step for each letter
	GZ_PROPERTY_EXPORT(gzFloat,					DeltaY,			GZ_GRAPH_EXPORT);	//!< If non zero it defines the delta y step for each letter

	GZ_PROPERTY_EXPORT(gzArray<gzFloat>,		TSpanX,			GZ_GRAPH_EXPORT);	//!< If array not empty it defines the x pos for each letter for each index
	GZ_PROPERTY_EXPORT(gzArray<gzFloat>,		TSpanY,			GZ_GRAPH_EXPORT);	//!< If array not empty it defines the y pos for each letter for each index

	GZ_PROPERTY_GET_EXPORT_(gzFloat,			MaxOffsetX,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_GET_EXPORT_(gzFloat,			MaxOffsetY,		GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzVec3,					Center,			GZ_GRAPH_EXPORT);	//! Added center to allow local transform in text render

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

protected:

	gzBool					m_useOverlay:1;

	gzBool					m_use2DPosition:1;

	gzBool					m_useScreenFixedPositioning:1;

	gzBool					m_useTranspBack:1;

	gzVec4					m_color;

	gzVec3					m_2DPosition;

	gzInt16					m_x_off_pixels;

	gzInt16					m_y_off_pixels;

	gzVec3					m_scale;

	gzVec3					m_hpr;

  gzInt32					m_width;

  gzInt32					m_height;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzIcon);

#endif
