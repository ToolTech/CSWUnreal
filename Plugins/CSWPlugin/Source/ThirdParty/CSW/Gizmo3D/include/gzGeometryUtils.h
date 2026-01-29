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
// File			: gzGeometryUtils.h
// Module		: 
// Description	: Class definition of the geometry utility classes
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
// AMO	021213	Created file 	
// AMO	091104	Changed gzViewPlane members to protected				(2.4.12)
// AMO	110511	Changed default color of viewplane to white				(2.5.20)
// AMO	110511	Added a matched texture coordinate setting to viewplane	(2.5.20)
//
//******************************************************************************
#ifndef __GZ_GEOMETRY_UTILS_H__
#define __GZ_GEOMETRY_UTILS_H__

/*!	\file 
	\brief Definitions geometry utilites

*/


#include "gzGeometry.h"
#include "gzText.h"
#include "gzIntersector.h"
#include "gzImageRender.h"

//******************************************************************************
// Class	: gzGeometryAxis
//									
// Purpose  : Coordinate Axis used in development to see local coordinates
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981122	Created 
//									
//******************************************************************************
class gzGeometryAxis : public gzGeometry
{
public:
	GZ_GRAPH_EXPORT gzGeometryAxis(gzFloat size=GZ_FLOAT_ONE , gzFloat step=GZ_FLOAT_ONE , const gzVec4 &color=gzVec4(0.0,0.0,0.0,1.0),const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzGeometryAxis(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---- util functions -------

	GZ_PROPERTY_EXPORT_(	gzFloat	,	Size	,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_(	gzFloat	,	Step	,	GZ_GRAPH_EXPORT);

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Serializing -------------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;


private:

	gzVoid createGeometryAxis();
};

//******************************************************************************
// Class	: gzGeometrySphere
//									
// Purpose  : A Simple Sphere
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011011	Created 
//									
//******************************************************************************
class gzGeometrySphere : public gzGeometry
{
public:
	GZ_GRAPH_EXPORT gzGeometrySphere(gzFloat radius=10 , gzInt32 sections=30 , const gzVec4 &color=gzVec4(1.0,1.0,1.0,1.0) , const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzGeometrySphere(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
};

typedef  gzFloat		(*gzEvalFunc_Tube_Radius)		(gzFloat zero_to_one, gzFloat angle);
typedef  gzFloatXY	(*gzEvalFunc_Tube_Displacement)	(gzFloat zero_to_one);

//********************** Some sample evaluation functions **********************

// --- Radius methods ----

//! Linear radius from 1 to 0
GZ_GRAPH_EXPORT gzFloat GZ_TUBE_CONE(gzFloat zero_to_one, gzFloat angle);

//******************************************************************************
// Class	: gzGeometryTube
//									
// Purpose  : A Rather Simple Tube
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030315	Created 
//									
//******************************************************************************
class gzGeometryTube : public gzGeometry
{
public:

	GZ_GRAPH_EXPORT gzGeometryTube(		gzFloat length=10,
										gzFloat width=1,
										gzUInt32 lengthSamples=10,
										gzUInt32 widthSamples=10,
										gzEvalFunc_Tube_Radius			evalRadiusFunc=nullptr,
										gzEvalFunc_Tube_Displacement	evalDisplacementFunc=nullptr,
										gzFloat texture_x_scale=1,
										gzFloat texture_y_scale=1,
										const gzVec4 &color=gzVec4(1.0,1.0,1.0,1.0) , 
										const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzGeometryTube(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
};


enum gzViewPlaneAlign
{
	GZ_VIEWPLANE_ALIGN_UPPER_LEFT,
	GZ_VIEWPLANE_ALIGN_UPPER_RIGHT,
	GZ_VIEWPLANE_ALIGN_BOTTOM_LEFT,
	GZ_VIEWPLANE_ALIGN_BOTTOM_RIGHT,
	GZ_VIEWPLANE_ALIGN_UPPER_CENTER,
	GZ_VIEWPLANE_ALIGN_BOTTOM_CENTER,
	GZ_VIEWPLANE_ALIGN_LEFT_CENTER,
	GZ_VIEWPLANE_ALIGN_RIGHT_CENTER
};

//******************************************************************************
// Class	: gzViewPlane
//									
// Purpose  : Projects a HUD plane covering full screen at user defined distance
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	020204	Created 
//									
//******************************************************************************
class gzViewPlane : public gzBaseGeometry
{
public:
	GZ_GRAPH_EXPORT gzViewPlane(const gzFloat &distance=-1,const gzVec4 &color=gzVec4(1.0,1.0,1.0,1.0),const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzViewPlane(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- No cloning of base - pure virtual ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- ViewPlane methods -------------------------------------

	GZ_GRAPH_EXPORT	gzVoid	setCoordinates(const gzVec2 & bottomLeftCoordinate, const gzVec2 & upperRightCoordinate,gzBool matchTextureCoordinates=FALSE);

	GZ_GRAPH_EXPORT	gzVoid	setTexCoordinates(const gzVec2 & bottomLeftTexCoordinate, const gzVec2 & upperRightTexCoordinate);

	/*! When you use pixel positions,the pixel coordinates are calculates as offsets to the current origo and counting "x" positive to the right and "y" positive up. 
		You set the origo by using the setAlignment method */
	GZ_GRAPH_EXPORT	gzVoid	usePixelPosition(gzBool on);	// Use pixels and alignment. pos dep on alignment

	/*! The default alignment is the lower left window corner. E.g. a square in the lower left coner is then specified 
		by setCoordinates(gzVec2(0,0),gzVec2(100,100)) */
	GZ_GRAPH_EXPORT gzVoid	setAlignment(gzViewPlaneAlign alignment);

	// ---------- Properties -------------------------------------------

	//! Set to TRUE if active in intersections
	GZ_PROPERTY_EXPORT( gzBool			,	UseIntersection			, GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT( gzVec4			,	Color					, GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT( gzFloat			,	Distance				, GZ_GRAPH_EXPORT);

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

protected:

	gzVec2	m_bottomLeftCoordinate;		// default (-1,-1)	x-> right y-> up from bottom left

	gzVec2	m_upperRightCoordinate;		// default (0,0)

	gzVec2	m_bottomLeftTexCoordinate;

	gzVec2	m_upperRightTexCoordinate;

	gzViewPlaneAlign		m_align;	// Default upper left corner. Only for pixel positions

	gzBool	m_usePixelPosition;				// Default FALSE
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzViewPlane);

//! Enumerates for the various angle units that can be used with gzLineOfSight
enum gzAngleUnits
{
	GZ_ANGLE_UNIT_DEGREES,
	GZ_ANGLE_UNIT_RADIANS,
	GZ_ANGLE_UNIT_MILS
};

//******************************************************************************
// Class	: gzLineOfSight
//									
// Purpose  : Calculates and draws a LOS vector from start to stop with 
//			  measured values.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021204	Created 
//									
//******************************************************************************
class gzLineOfSight : public gzBaseGeometry
{
public:
	GZ_GRAPH_EXPORT gzLineOfSight(const gzVec3 & start=gzVec3(0,0,0) , const gzVec3 & stop=gzVec3(0,0,0) , const gzVec4 &color=gzVec4(1.0,1.0,1.0,1.0),const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzLineOfSight(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- No cloning of base - pure virtual ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- The control API ---------------------------------------

	GZ_GRAPH_EXPORT gzVoid	setStartPosition(const gzVec3 & start);

	GZ_GRAPH_EXPORT gzVoid	setStopPosition(const gzVec3 & stop);

	GZ_GRAPH_EXPORT gzVoid	setNodeTree(gzNode *tree);

	// ---------- Properties -------------------------------------------

	GZ_PROPERTY_EXPORT( gzVec3			,	NorthVector				, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT( gzVec3			,	EastVector				, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT( gzBool			,	ShowBearing				, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT( gzAngleUnits	,	BearingUnits			, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT( gzBool			,	ShowTotalDistance		, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT( gzBool			,	ShowLineOfSightDistance	, GZ_GRAPH_EXPORT);



private:

	gzVec4					m_color;

	gzVec3					m_start;

	gzVec3					m_stop;

	gzDouble				m_animationTick;

	gzDouble				m_updateTick;

	gzUInt16				m_stipple;

	gzNodePtr				m_nodeTree;

	gzIntersectorPtr		m_intersector;

	gzBool					m_needUpdate;

	gzVec3					m_hitPoint;

	gzText					m_text;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzLineOfSight);


////******************************************************************************
//// Class	: gzVisualCoverage
////									
//// Purpose  : Calculates and renders the visual coverage as seen from a certain
////			  point. The actual inverse of a shaodw
////									
//// Notes	: -	
////									
//// Revision History...							
////									
//// Who	Date	Description						
////									
//// AMO	021204	Created 
////									
////******************************************************************************
//class gzVisualCoverage : public gzShadowRender
//{
//public:
//
//	GZ_GRAPH_EXPORT gzVisualCoverage(const gzString & name=GZ_EMPTY_STRING);
//
//	GZ_GRAPH_EXPORT virtual ~gzVisualCoverage();
//
//	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface
//
//
//	// -- gzVisualCoverage interface -------------------------------------
//
//	GZ_GRAPH_EXPORT gzVoid	setPosition(const gzVec3 &pos);
//
//	GZ_GRAPH_EXPORT gzVoid	setNodeTree(gzNode *tree);
//
//private:
//
//	gzRefPointer<gzNode>			m_nodeTree;
//
//	gzRefPointer<gzLight>			m_light;
//
//	gzRefList<gzShadowGenerator>	m_generators;
//
//};

//******************************************************************************
// Class	: gzVisualCovSample
//									
// Purpose  : Calculates and renders the visual coverage as sampled from a certain
//			  point. View position dependant.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021204	Created 
//									
//******************************************************************************
class gzVisualCovSample : public gzBaseGeometry
{
public:

	GZ_GRAPH_EXPORT gzVisualCovSample(gzImageRender *renderer , gzImage *image , const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzVisualCovSample();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- No cloning of base - pure virtual ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;


	// -- gzVisualCovSample interface -------------------------------------

	GZ_GRAPH_EXPORT gzVoid	setPosition(const gzVec3D &pos,const gzFloat &maxRadius=10000);

	GZ_GRAPH_EXPORT gzVoid	lookAt(const gzVec3D &pos);

	GZ_GRAPH_EXPORT gzVoid	setNodeTree(gzNode *tree);

	GZ_GRAPH_EXPORT gzImage *getCoverageImage();

private:

	gzVoid	generateGeometry();

	gzDynamicArray<gzVec3>					m_geometry;

	gzImageRenderPtr						m_imageRender;

	gzRefPointer<gzImage>					m_image;

	gzMatrix4								m_matrix;
};

enum gzSkyBoxLocation
{
	GZ_SKYBOX_EAST	=0,
	GZ_SKYBOX_WEST	=1,
	GZ_SKYBOX_SOUTH	=2,
	GZ_SKYBOX_NORTH	=3,
	GZ_SKYBOX_GROUND=4,
	GZ_SKYBOX_SKY	=5
};

class gzQuadTexMapping
{
public:

	GZ_GRAPH_EXPORT gzQuadTexMapping(gzVec2 _c1=gzVec2(0,0),gzVec2 _c2=gzVec2(1,0),gzVec2 _c3=gzVec2(1,1),gzVec2 _c4=gzVec2(0,1)):c1(_c1),c2(_c2),c3(_c3),c4(_c4){}

	GZ_GRAPH_EXPORT	gzVec2 center()
	{
		return (c1+c2+c3+c4)*0.25f;
	}

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT	gzVoid write(gzSerializeAdapter *adapter)
	{
		::writeAdapter(adapter,c1);
		::writeAdapter(adapter,c2);
		::writeAdapter(adapter,c3);
		::writeAdapter(adapter,c4);
	}

	GZ_GRAPH_EXPORT	gzVoid read(gzSerializeAdapter *adapter)
	{
		::readAdapter(adapter,c1);
		::readAdapter(adapter,c2);
		::readAdapter(adapter,c3);
		::readAdapter(adapter,c4);
	}

	GZ_GRAPH_EXPORT	gzVoid pushBack(gzSerializeAdapter *adapter)
	{
		::pushBackAdapter(adapter,c4);
		::pushBackAdapter(adapter,c3);
		::pushBackAdapter(adapter,c2);
		::pushBackAdapter(adapter,c1);
	}

	GZ_GRAPH_EXPORT	gzUInt32	getDataSize(gzSerializeAdapter *adapter) const
	{
		gzUInt32 size(0);

		size+=::getDataSize(adapter,c1);
		size+=::getDataSize(adapter,c2);
		size+=::getDataSize(adapter,c3);
		size+=::getDataSize(adapter,c4);

		return size;
	}

	
	gzVec2	c1;
	gzVec2	c2;
	gzVec2	c3;
	gzVec2	c4;
};

//******************************************************************************
// Class	: gzSkyBox
//									
// Purpose  : Calculates and renders a skybox around the viewer
//			  
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030328	Created 
//									
//******************************************************************************
class gzSkyBox : public gzBaseGeometry
{
public:

	GZ_GRAPH_EXPORT gzSkyBox(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzSkyBox();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- No cloning of base - pure virtual ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Skybox methods ----------------------------------------

	GZ_GRAPH_EXPORT gzVoid		setOrientation(gzFloat heading, gzFloat pitch , gzFloat roll);

	GZ_GRAPH_EXPORT gzVoid		setGroundPoint( gzFloat x , gzFloat y , gzFloat z);

	GZ_GRAPH_EXPORT gzVoid		setStandardHeight(gzFloat height);

	GZ_GRAPH_EXPORT gzVoid		setHorizonAngle(gzFloat angle);

	GZ_GRAPH_EXPORT gzVoid		useFixedHeight(gzBool on=FALSE);

	GZ_GRAPH_EXPORT gzVoid		setImageSide(gzSkyBoxLocation side, gzImage *image,gzQuadTexMapping mapping=gzQuadTexMapping());

	GZ_GRAPH_EXPORT gzVoid		setGroundColor(const gzVec4 &color);

	GZ_GRAPH_EXPORT gzVoid		setSkyColor(const gzVec4 &color);

	// --------- Special acess methods for expert users ----------------

	GZ_GRAPH_EXPORT gzState *	getState(gzSkyBoxLocation side);

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;


private:

	gzMatrix4							m_transform;

	gzVec3								m_groundPoint;

	gzFloat								m_height_y;

	gzFloat								m_horiz_angle;

	gzArray<gzRefPointer<gzState> >		m_texSides;
	gzArray<gzQuadTexMapping>			m_texMapping;
	
	gzVec4								m_topColor;
	gzVec4								m_midColor;
	gzVec4								m_groundColor;
	
	gzFloat								m_topDecay;
	gzFloat								m_midDecay;

	gzBool								m_useFixedHeight;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzSkyBox);

//******************************************************************************
// Class	: gzSkyLayer
//									
// Purpose  : renders layers of sky data
//			  
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030328	Created 
//									
//******************************************************************************
class gzSkyLayer : public gzBaseGeometry
{
public:

	GZ_GRAPH_EXPORT gzSkyLayer(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzSkyLayer();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- No cloning of base - pure virtual ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Skybox methods ----------------------------------------

	GZ_GRAPH_EXPORT gzVoid	setOrientation(gzFloat heading, gzFloat pitch , gzFloat roll);

	GZ_GRAPH_EXPORT gzVoid	setLayerImage(gzImage *image , gzFloat width , gzFloat length , gzFloat heightAboveGround , gzFloat northSpeed=0, gzFloat eastSpeed=0);

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ----------- Properties ---------------------------

	GZ_PROPERTY_EXPORT(gzFloat,		HorizonAngle,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat,		StandardHeight,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzVec3,		GroundPoint,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT_(gzBool,		VisibleFromAbove,		GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool,		FixedHeight,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat,		NorthSpeed,				GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat,		EastSpeed,				GZ_GRAPH_EXPORT);

private:

	gzMatrix4	m_transform;

	gzRefPointer<gzState>	m_skyLayer;

	gzFloat		m_heightAboveGround;

	gzFloat		m_width;

	gzFloat		m_length;

};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzSkyLayer);


//******************************************************************************
// Class	: gzIBRIndexSets
//									
// Purpose  : IBR index data
//			  
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030714	Created 
//									
//******************************************************************************
class gzIBRIndexSets : public gzReference
{
public:

	GZ_GRAPH_EXPORT static gzIBRIndexSets * getIndexSet(gzUInt32 width,gzUInt32 height);

	GZ_GRAPH_EXPORT virtual ~gzIBRIndexSets();

	gzVoid render(gzContext *context);

private:

	//friend class gzIBRGeometry;

	gzIBRIndexSets(gzUInt32 width , gzUInt32 height);

	gzVoid dropVBO();

	static gzRefList<gzIBRIndexSets>	s_indexStorage;

	gzUInt32				m_width;
	gzUInt32				m_height;

	gzArray<gzUInt32>	m_index;
	gzArray<gzInt16XY>	m_xy;

	gzLateBindData<gzVertexBufferInfo>	m_vboBindInfo;

};


//******************************************************************************
// Class	: gzIBRGeometry
//									
// Purpose  : IBR geometry
//			  
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030714	Created 
//									
//******************************************************************************
class gzIBRGeometry : public gzBaseGeometry
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);		// provide RTTI typed interface

	GZ_GRAPH_EXPORT gzIBRGeometry(const gzString & name="gzIBRGeometry");

	GZ_GRAPH_EXPORT virtual ~gzIBRGeometry(){};

	//! Return TRUE if object needs a custom state
	GZ_GRAPH_EXPORT virtual gzBool retainState() override { return TRUE; }

	GZ_GRAPH_EXPORT virtual gzVoid setState( gzState *state ) override;
	
	// ---------- Clone interface ---------------------------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;	// Provide a clone method for factories
	
	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	
	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction *actionclass , gzContext *context) override;
	
	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- IBR Interface ----------------------------------------
	
	GZ_GRAPH_EXPORT gzVoid setSize(gzUInt32 size_x, gzUInt32 size_y);
	
	GZ_GRAPH_EXPORT gzVoid setDepthMap(gzImage *image);
	
	GZ_GRAPH_EXPORT gzVoid setColorMap(gzImage *image);

	GZ_GRAPH_EXPORT gzVoid setNormalMap(gzImage *image);
	
	GZ_GRAPH_EXPORT gzVoid setTransform(const gzMatrix4 &matrix);
	
	GZ_GRAPH_EXPORT gzVoid filterSideGeometry(gzFloat filterStep=0.0001f);

	// ---------- Properties ------------------------------------------

	GZ_PROPERTY_EXPORT(	gzFloat,	CutOffValue,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(	gzBool,		UseFPX,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(	gzBool,		HideInifiniteDepth,	GZ_GRAPH_EXPORT);
	
private:

	gzBool isDiscreteJump(gzInt32 width,gzInt32 height,gzFloat max);
	
	gzFloat getDepth(gzInt32 width,gzInt32 height);

	gzUInt32											m_width;

	gzUInt32											m_height;

	gzRefPointer<gzIBRIndexSets>					m_indexSet;

	gzRefPointer<gzImage>							m_depthMap;

	gzRefPointer<gzImage>							m_colorMap;

	gzRefPointer<gzImage>							m_normalMap;

	gzRefPointer<gzGFXProgram>						m_program;

	gzMatrix4										m_transform;
};

GZ_DECLARE_REFPTR(gzIBRGeometry);

//******************************************************************************
// Geometry calculation utilities
//******************************************************************************

GZ_GRAPH_EXPORT gzBool gzIntersect(const gzVec3 &origin, const gzVec3 &direction, const gzVec3 &v0, const gzVec3 &v1 ,const gzVec3 &v2 , gzVec3 &p);

GZ_GRAPH_EXPORT gzVoid gzUVMap(const gzVec3 &v0, const gzVec3 &v1 ,const gzVec3 &v2 , const gzVec3 &p , gzFloat &u , gzFloat &v);

//******************************************************************************
// Render utilities
//******************************************************************************

gzVoid GZ_GRAPH_EXPORT gzDrawBoundingSphere(gzNode *node,gzContext *context);
gzVoid GZ_GRAPH_EXPORT gzDrawNodeInfo(gzNode *node,gzContext *context);

#endif

