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
// File			: gzCrossVolume.h
// Module		: 
// Description	: Class definition of the Crossboard class
// Author		: Anders Mod�n		
// Product		: Gizmo3D 2.12.220
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
// AMO	110927	Created file 	
//
//******************************************************************************
#ifndef __GZ_CROSS_VOLUME_H__
#define __GZ_CROSS_VOLUME_H__

/*!	\file 
	\brief Definitions of gzCrossVolume

*/


#include "gzGeometry.h"

struct gzCrossVolumeObjectData
{
	gzCrossVolumeObjectData()
	{
		size=1;
		heading=0;
		pitch=0;
		roll=0;
	}

	float	size;
	float	heading;
	float	pitch;
	float	roll;

	gzVoid		write(gzSerializeAdapter *adapter);
	gzVoid		read(gzSerializeAdapter *adapter);
	gzVoid		pushBack(gzSerializeAdapter *adapter);
	gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;

};


struct gzCrossVolumeTextureData
{
	gzFloat	texture_offset_lowleft_s;		// 0-1 in texture coordinates
	gzFloat	texture_offset_lowleft_t;

	gzFloat	texture_offset_topright_s;		// 0-1 in texture coordinates
	gzFloat	texture_offset_topright_t;

	gzFloat	base_scale_lowleft_s;			// -1 to -1 in -x to + x
	gzFloat	base_scale_lowleft_t;			// default to 1

	gzFloat	base_scale_topright_s;			// -1 to -1 in -x to + x
	gzFloat	base_scale_topright_t;			// default to 1
};

//******************************************************************************
// Class	: gzCrossVolume
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
class gzCrossVolume : public gzBaseGeometry
{
public:
	GZ_GRAPH_EXPORT gzCrossVolume(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzCrossVolume();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	
	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- No cloning of base - pure virtual ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- The control API ---------------------------------------

	GZ_GRAPH_EXPORT gzVoid	setNumberOfObjects(gzUInt32 count);
	GZ_GRAPH_EXPORT gzUInt32 getNumberOfObjects();

	GZ_GRAPH_EXPORT gzVoid	setObjectPosition(gzUInt32 object,const gzVec3 &position);
	GZ_GRAPH_EXPORT gzVec3	getObjectPosition(gzUInt32 object);

	GZ_GRAPH_EXPORT gzVoid	setObjectHeading(gzUInt32 object,const gzFloat &heading);
	GZ_GRAPH_EXPORT gzFloat getObjectHeading(gzUInt32 object);

	GZ_GRAPH_EXPORT gzVoid	setObjectPitch(gzUInt32 object,const gzFloat &pitch);
	GZ_GRAPH_EXPORT gzFloat getObjectPitch(gzUInt32 object);

	GZ_GRAPH_EXPORT gzVoid	setObjectRoll(gzUInt32 object,const gzFloat &roll);
	GZ_GRAPH_EXPORT gzFloat getObjectRoll(gzUInt32 object);

	GZ_GRAPH_EXPORT gzVoid	setObjectSize(gzUInt32 object,const gzFloat &size);
	GZ_GRAPH_EXPORT gzFloat	getObjectSize(gzUInt32 object);

	GZ_GRAPH_EXPORT gzVoid	setObjectColor(gzUInt32 object, const gzVec4 &color);
	GZ_GRAPH_EXPORT gzVec4	getObjectColor(gzUInt32 object);


	GZ_GRAPH_EXPORT gzVoid	setTextureParams(gzClampType<gzUInt32,0,47> textureID,const gzCrossVolumeTextureData &data);
	GZ_GRAPH_EXPORT gzCrossVolumeTextureData getTextureParams(gzClampType<gzUInt32,0,47> textureID);

	GZ_GRAPH_EXPORT	gzVoid setupDefaultTextureData(gzBool toZero=FALSE);

	GZ_GRAPH_EXPORT gzVoid	hatch(gzFloat x, gzFloat y, gzFloat z, const gzVec4 &color = GZ_ONE_VEC4, gzFloat scale = GZ_FLOAT_ONE, gzInt32 index = -1);
	GZ_GRAPH_EXPORT gzVoid	clear();
	GZ_GRAPH_EXPORT gzVoid	removeLast();
	GZ_GRAPH_EXPORT gzVoid	removeObject(gzUInt32 object);

	GZ_PROPERTY_EXPORT(gzVec3,	HatchOffsets,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,	HatchDirection,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,	HatchSize,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,	HatchSizeVariance,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_(gzBool,	UseColors,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec4,	BaseColor,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat,	Near,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,	NearFade,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat,	Far,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,	FarFade,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat,	MaxHalfDist,		GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt32,	Level,				GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool,	UseWind,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,	WindSpeed,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,	WindStrength,		GZ_GRAPH_EXPORT);

	// ---------- Serializing -------------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	//! Return TRUE if object needs a custom state
	GZ_GRAPH_EXPORT virtual gzBool retainState() override { return TRUE; }

	GZ_GRAPH_EXPORT virtual gzVoid setState( gzState *state ) override;

private:

	gzVoid dropVBO(gzBool setDirtyNode);
	gzVoid checkMinMaxSize();
	
	gzArray<gzVec3>						m_positions;
	gzArray<gzCrossVolumeObjectData>	m_objectData;
	gzArray<gzVec4>						m_colorData;
	gzArray<gzFloat>					m_textureData;


	gzArray<gzVec3>						m_coordinates;
	gzArray<gzVec3>						m_normals;
	gzArray<gzVec2>						m_texcoords;
	gzArray<gzVec4>						m_colors;

	gzFloat								m_minSize;
	gzFloat								m_maxSize;

	gzLateBindData<gzVertexBufferInfo>	m_vboBindInfo;

	gzGFXProgramPtr						m_vertexProgram;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzCrossVolume);

#endif // __GZ_CROSS_VOLUME_H__

