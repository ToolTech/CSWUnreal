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
// File			: gzGeometryVolume.h
// Module		: 
// Description	: Class definition of the geometry volumetric  classes
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
// AMO	080122	Created file 	
//
//******************************************************************************
#ifndef __GZ_GEOMETRY_VOLUME_H__
#define __GZ_GEOMETRY_VOLUME_H__

/*!	\file 
	\brief Definitions of gzGeometryVolume

*/


#include "gzGeometry.h"


//******************************************************************************
// Class	: gzGeometryVolume
//									
// Purpose  : Renders a geometrical volume (cloud etc)
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080122	Created 
//									
//******************************************************************************
class gzGeometryVolume : public gzBaseGeometry
{
public:
	GZ_GRAPH_EXPORT gzGeometryVolume(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzGeometryVolume(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- No cloning of base - pure virtual ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- The control API ---------------------------------------

	GZ_GRAPH_EXPORT gzVoid setSize(gzFloat x_size,gzFloat y_size,gzFloat z_size);
	GZ_GRAPH_EXPORT gzVoid setSlices(gzUInt32 x_slices,gzUInt32 y_slices,gzUInt32 z_slices);

	GZ_GRAPH_EXPORT gzVoid setXOffset(gzUInt32 y,gzUInt32 z,gzFloat offset);
	GZ_GRAPH_EXPORT gzVoid setYOffset(gzUInt32 x,gzUInt32 z,gzFloat offset);
	GZ_GRAPH_EXPORT gzVoid setZOffset(gzUInt32 x,gzUInt32 y,gzFloat offset);

	GZ_GRAPH_EXPORT gzFloat getXOffset(gzUInt32 y,gzUInt32 z);
	GZ_GRAPH_EXPORT gzFloat getYOffset(gzUInt32 x,gzUInt32 z);
	GZ_GRAPH_EXPORT gzFloat getZOffset(gzUInt32 x,gzUInt32 y);

	GZ_GRAPH_EXPORT gzVoid setXTexMapping(gzUInt32 x,const gzVec2& loLeft,const gzVec2& upRight);
	GZ_GRAPH_EXPORT gzVoid setYTexMapping(gzUInt32 y,const gzVec2& loLeft,const gzVec2& upRight);
	GZ_GRAPH_EXPORT gzVoid setZTexMapping(gzUInt32 z,const gzVec2& loLeft,const gzVec2& upRight);

	GZ_GRAPH_EXPORT gzVec2 getXTexMapping(gzUInt32 x,gzUInt32 y,gzUInt32 z);
	GZ_GRAPH_EXPORT gzVec2 getYTexMapping(gzUInt32 x,gzUInt32 y,gzUInt32 z);
	GZ_GRAPH_EXPORT gzVec2 getZTexMapping(gzUInt32 x,gzUInt32 y,gzUInt32 z);

	GZ_PROPERTY_EXPORT( gzVec4			,	BaseColor			, GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT_( gzBool			,	UseXOffsets			, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_( gzBool			,	UseYOffsets			, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_( gzBool			,	UseZOffsets			, GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT_( gzBool			,	UseXTexMapping		, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_( gzBool			,	UseYTexMapping		, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_( gzBool			,	UseZTexMapping		, GZ_GRAPH_EXPORT);


private:

	gzVoid createArrays();

	gzFloat	m_x_size,m_y_size,m_z_size;

	gzUInt32	m_x_slices,m_y_slices,m_z_slices;

	gzArray<gzVec2>			m_textureOffsetX;
	gzArray<gzVec2>			m_textureOffsetY;
	gzArray<gzVec2>			m_textureOffsetZ;

	gzImagePtr				m_x_offsets;
	gzImagePtr				m_y_offsets;
	gzImagePtr				m_z_offsets;

	gzImagePtr				m_x_tex_mapping;
	gzImagePtr				m_y_tex_mapping;
	gzImagePtr				m_z_tex_mapping;

	gzBool					m_buildGeometry;

	gzDynamicArray<gzVec3>	m_x_slice_coords;
	gzDynamicArray<gzVec3>	m_y_slice_coords;
	gzDynamicArray<gzVec3>	m_z_slice_coords;

	gzDynamicArray<gzVec2>	m_x_slice_tex_coords;
	gzDynamicArray<gzVec2>	m_y_slice_tex_coords;
	gzDynamicArray<gzVec2>	m_z_slice_tex_coords;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzGeometryVolume);

#endif // __GZ_GEOMETRY_VOLUME_H__

