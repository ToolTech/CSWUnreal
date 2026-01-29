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
// File			: gzCrossboard.h
// Module		: 
// Description	: Class definition of the Crossboard class
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
// AMO	080122	Created file 	
//
//******************************************************************************
#ifndef __GZ_CROSSBOARD_H__
#define __GZ_CROSSBOARD_H__

/*!	\file 
	\brief Definitions of gzCrossboard

*/


#include "gzGeometry.h"

struct gzCrossboardObjectData
{
	gzCrossboardObjectData()
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

//******************************************************************************
// Class	: gzCrossboard
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
class gzCrossboard : public gzBaseGeometry
{
public:
	GZ_GRAPH_EXPORT gzCrossboard(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzCrossboard();

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

	// -- Array version ---
	GZ_GRAPH_EXPORT gzArray<gzVec3> &getObjectPositionArray();

	GZ_GRAPH_EXPORT gzVoid	setObjectHeading(gzUInt32 object,const gzFloat &heading);
	GZ_GRAPH_EXPORT gzFloat getObjectHeading(gzUInt32 object);

	GZ_GRAPH_EXPORT gzVoid	setObjectPitch(gzUInt32 object,const gzFloat &pitch);
	GZ_GRAPH_EXPORT gzFloat getObjectPitch(gzUInt32 object);

	GZ_GRAPH_EXPORT gzVoid	setObjectRoll(gzUInt32 object,const gzFloat &roll);
	GZ_GRAPH_EXPORT gzFloat getObjectRoll(gzUInt32 object);

	GZ_GRAPH_EXPORT gzVoid	setObjectSize(gzUInt32 object,const gzFloat &size);
	GZ_GRAPH_EXPORT gzFloat	getObjectSize(gzUInt32 object);

	// -- Array version ---
	GZ_GRAPH_EXPORT gzArray<gzCrossboardObjectData> &getObjectDataArray();

	GZ_GRAPH_EXPORT gzVoid	setObjectColor(gzUInt32 object, const gzVec4 &color);
	GZ_GRAPH_EXPORT gzVec4	getObjectColor(gzUInt32 object);

	// -- Array version ---
	GZ_GRAPH_EXPORT	gzArray<gzVec4> &getColorArray();
		

	GZ_GRAPH_EXPORT gzVoid	hatch(gzFloat x,gzFloat y,gzFloat z,const gzVec4& color=GZ_ONE_VEC4,gzFloat scale=GZ_FLOAT_ONE,gzInt32 index=-1);
	GZ_GRAPH_EXPORT gzVoid	clear();
	GZ_GRAPH_EXPORT gzVoid	removeLast();
	GZ_GRAPH_EXPORT gzVoid	removeObject(gzUInt32 object);

	GZ_PROPERTY_EXPORT(gzVec3,	PlaneOffsets,		GZ_GRAPH_EXPORT);
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

	// ---------- Serializing -------------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	//! Return TRUE if object needs a custom state
	GZ_GRAPH_EXPORT virtual gzBool retainState() override { return TRUE; }

	GZ_GRAPH_EXPORT virtual gzVoid setState( gzState *state ) override;

private:

	gzVoid dropVBO(gzBool setDirtyNode);
	gzVoid checkMinMaxSize();

	gzArray<gzVec3>						m_positions;	// 3D positions
	gzArray<gzCrossboardObjectData>		m_objectData;	// Object data
	gzArray<gzFloat>					m_textureData;	// Offset values in textures
	gzArray<gzVec4>						m_colorData;	// Color data

	// Work Buffers in case of missing geometry shaders

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
GZ_DECLARE_REFPTR(gzCrossboard);

#endif // __GZ_CROSSBOARD_H__

