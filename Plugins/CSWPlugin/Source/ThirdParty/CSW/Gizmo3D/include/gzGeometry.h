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
// File			: gzGeometry.h
// Module		: 
// Description	: Class definition of the gzGeometry class
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
// AMO	981122	Created file 	
// AMO	100420	Added spatial intersector optimization for gzGeometry		(2.5.4)
//
//******************************************************************************
#ifndef __GZ_GEOMETRY_H__
#define __GZ_GEOMETRY_H__

/*!	\file 
	\brief Base definitions for geometry classes

*/


#include "gzNode.h"
#include "gzState.h"
#include "gzMatrix.h"
#include "gzDisplayList.h"
#include "gzVertexAttributes.h"
#include "gzIntersector.h"


enum gzGeoPrimType
{	
	GZ_PRIM_NOPRIM , 
	GZ_PRIM_POINTS ,				//!<	Points, each point is defined by a vertice. Length array NOT  USED.
	GZ_PRIM_LINES ,					//!<	Lines, each line uses two vertices. Length array NOT USED (decided by coords/2 or indices/2).
	GZ_PRIM_LINESTRIPS ,			//!<	A consecutive line. A line is drawn between each vertex.
	GZ_PRIM_FLAT_LINESTRIPS ,		//!<	Non shaded version of GZ_PRIM_LINESTRIPS.
	GZ_PRIM_LINELOOPS ,				//!<	Close loop lines.	Length array required.
	GZ_PRIM_TRIS ,					//!<	Triangles, each triangle is defined by 3 vertices. Length array NOT USED (decided by coords/3 or indices/3).
	GZ_PRIM_QUADS ,					//!<	Quads, each quad is defined by 4 vertices.Length array NOT USED (decided by coords/4 or indices/4).
	GZ_PRIM_TRISTRIPS ,				//!<	A strip build by triangles.
	GZ_PRIM_FLAT_TRISTRIPS ,		//!<	Non shaded version of GZ_PRIM_TRISTRIPS.
	GZ_PRIM_TRIFANS ,				//!<	A fan build by triangles.
	GZ_PRIM_FLAT_TRIFANS ,			//!<	Non shaded version of GZ_PRIM_TRIFANS.
	GZ_PRIM_POLYS ,					//!<	A convex polygon.
	GZ_PRIM_QUADSTRIPS,				//!<	A strip build by quads.
	GZ_PRIM_HIDDEN_POLYS			//!<	A hidden geometry polygon - not rendered
};
	

// Optimizer levels

enum gzGeoOptimizeLevel
{	GZ_GEO_OPTIMIZE_NO_OPTS				=	(1<<0),		//!< Just convert
	GZ_GEO_OPTIMIZE_GENERATE_INDEXED	=	(1<<1),		//!< Generate indexed geometry
	GZ_GEO_OPTIMIZE_LEAVE_LINES			=	(1<<2),		//!< Do not remove points on parallell line
	GZ_GEO_OPTIMIZE_FAN_TO_TRISTRIP		=	(1<<3),		//!< Convert fans to tristrip
	GZ_GEO_OPTIMIZE_GENERATE_NORMALS	=	(1<<4),		//!< Generate Normals
	GZ_GEO_OPTIMIZE_USE_INDEXED			=	(1<<5),		//!< Optimize and change indexed geometry
	GZ_GEO_OPTIMIZE_TO_TRIANGLES		=	(1<<6),		//!< Just create triangle soup with all attributes per vertex
	GZ_GEO_OPTIMIZE_DONT_USE_PER_PRIM	=	(1<<7),		//!< Do not set per prim values. Either overall or per vertex
	GZ_GEO_OPTIMIZE_COMBINE_INTERNAL	=	(1<<8),		//!< Combine internal geometry
	GZ_GEO_OPTIMIZE_USE_OVERALL			=	(1<<9),		//!< Try to set overall binding
	GZ_GEO_OPTIMIZE_FORCE				=	(1<<10),	//!< Force optimization (may result in zero data)
};

//! Use as attribute for meta data to skip optims
#define GZ_SKIP_OPTIMIZE "optimize", "dont_optimize"

enum gzPolygonWinding
{
	GZ_POLYGON_WINDING_UNDEFINED			=	0,
	GZ_POLYGON_WINDING_CLOCKWISE			=	1,
	GZ_POLYGON_WINDING_COUNTER_CLOCKWISE	=	2,
	GZ_POLYGON_WINDING_MIXED				=	3,
};

GZ_USE_BIT_LOGIC(gzGeoOptimizeLevel);
GZ_USE_BIT_LOGIC(gzPolygonWinding);


enum gzStitchSettings
{
	GZ_STITCH_SETTING_OFF					=	0,
	GZ_STITCH_SETTING_EVEN_ODD				=	1,
	GZ_STITCH_SETTING_NON_ZERO				=	2,
	GZ_STITCH_SETTING_OR					=	2,
	GZ_STITCH_SETTING_POSITIVE				=	3,
	GZ_STITCH_SETTING_NEGATIVE				=	4,
	GZ_STITCH_SETTING_AND					=	5,
	GZ_STITCH_SETTING_DEFAULT				=	GZ_STITCH_SETTING_EVEN_ODD,
};

GZ_USE_BIT_LOGIC(gzStitchSettings);

//******************************************************************************
// Class	: gzVertexGroupInfo
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000202	Created 
//									
//******************************************************************************
class gzVertexGroupInfo
{
public:
	gzArray<gzUInt32>	groupID;
	gzArray<gzUInt32>	connections;
};

//******************************************************************************
// Class	: gzBaseGeometry
//									
// Purpose  : 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	020202	Created 
//									
//******************************************************************************
class gzBaseGeometry : public gzNode // Default base Interface for all geometry
{
public:
	//!Default constructor.
	/*!
	It is possible to specify a name for the gzBaseGeometry.
	*/
	GZ_GRAPH_EXPORT gzBaseGeometry(const gzString & name=GZ_EMPTY_STRING);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override =0;

	// ---------- Common graph functions --------------------------------

	//!Pure virtual function for node update. 
	/*!
	Needs to be implemented in classes which inherit from gzBaseGeometry. 
	Otherwise the class will not be able to instantiate.
	*/
	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override =0;

	// ---------- No cloning of base - pure virtual ---------------------

	//!Pure virtual function for cloning. 
	/*!
	Needs to be implemented in classes which inherit from gzBaseGeometry. 
	Otherwise the class will not be able to instantiate.
	*/
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override =0;
};

/*! The gzWeightMethod describes how the method generateWeights() creates the weighting coordinates */
enum gzWeightMethod
{
	GZ_WEIGHT_START_TRANS,		//!< Affects start coordinates (smaller values)
	GZ_WEIGHT_END_TRANS,		//!< Affects end coordinates
	GZ_WEIGHT_MID_TRANS,		//!< Affects mid coords
	GZ_WEIGHT_START_END_TRANS,	//!< Affects start and end coords
	GZ_WEIGHT_CONSTANT			//!< Affect all coordinates with constant value
};

class gzIntersectorAction; // Forward decl

//******************************************************************************
// Class	: gzWeightGeomInfo
//									
// Purpose  : 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021029	Created 
//									
//******************************************************************************
class gzWeightGeomInfo : public gzMutex
{
public:

	gzWeightGeomInfo():currentUpdateID(0) {}

	gzArray<gzVec3>		currentCoordinates;

	gzArray<gzVec3>		currentNormals;

	gzUInt32			currentUpdateID;

};

enum gzVertexBufferType
{
	GZ_VBO_DYNAMIC,
	GZ_VBO_STATIC,
	GZ_VBO_STATIC_DROP_LOCAL,
	GZ_VBO_SOMETIMES
};

class gzVertexBufferBindInfo
{
public:
	//!Default constructor.
	GZ_GRAPH_EXPORT gzVertexBufferBindInfo();

	//!Destructor
	GZ_GRAPH_EXPORT virtual ~gzVertexBufferBindInfo();

	gzUInt32							bindID;
	gzUInt32							indexBindID;
	gzUInt32							contextEnumerator;
	gzRefPointer<gzRefIdStorage>	bindPool;

};

class gzVertexBufferInfo
{
public:

	//!Default constructor.
	GZ_GRAPH_EXPORT gzVertexBufferInfo();

	//!Destructor
	GZ_GRAPH_EXPORT ~gzVertexBufferInfo();

	gzVertexBufferType						vboType;
	gzUInt32									entries;
	gzUInt32									index;
	gzBool									useEdges;
	gzDynamicArray<gzVertexBufferBindInfo>	bindInfo;
};

class gzVertexAttributeManager
{
public:

	//!Default constructor
	GZ_GRAPH_EXPORT gzVertexAttributeManager();

	//!Destructor
	GZ_GRAPH_EXPORT virtual ~gzVertexAttributeManager(){};

	GZ_GRAPH_EXPORT gzVertexAttributeManager(const gzVertexAttributeManager &right);

	GZ_GRAPH_EXPORT const gzVertexAttributeManager & operator =(const gzVertexAttributeManager &right);

	GZ_GRAPH_EXPORT gzVoid activateOverall();

	GZ_GRAPH_EXPORT gzVoid activatePerPrim(gzUInt32 index);

	GZ_GRAPH_EXPORT gzVoid deactivate();

	GZ_GRAPH_EXPORT gzVertexAttributeListPtr getVertexAttributeList(gzUInt32 listIndex);

	GZ_GRAPH_EXPORT gzArray<gzVertexAttributeListPtr> getVertexAttributeLists();

	//!Removes list from the list of vertex attributes.
	GZ_GRAPH_EXPORT gzVoid remove(gzVertexAttributeList *list);

	//!Removes all attributes.
	GZ_GRAPH_EXPORT gzVoid removeAll();

	//!Inserts list to the list of vertex attributes.
	GZ_GRAPH_EXPORT gzVoid insert(gzVertexAttributeList *list);

	//!Checks if the gzVertexAttributeManager is active.
	/*!
	Returns true if there are attributes available.
	*/
	GZ_GRAPH_EXPORT gzBool isActive() const;

	//!Returns true if GZ_BIND_OVERALL binding is used, otherwise false.
	GZ_GRAPH_EXPORT gzBool hasOverallBinding()	{ return m_hasOverallBinding; }

	//!Returns true if GZ_BIND_PER_PRIM binding is used, otherwise false.
	GZ_GRAPH_EXPORT gzBool hasPrimBinding()		{ return m_hasPrimBinding; }

	//!Returns true if GZ_BIND_PER_VERTEX binding is used, otherwise false.
	GZ_GRAPH_EXPORT gzBool hasVertexBinding()	{ return m_hasVertexBinding; }

	GZ_GRAPH_EXPORT gzVoid updateBindingInfo();

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT gzVoid write(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzVoid read(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;


private:

	gzRefList<gzVertexAttributeList> 		m_attributes;
	gzListIterator<gzVertexAttributeList>	m_iterator;
	gzVertexAttributeList	*				m_item;

	gzBool									m_hasOverallBinding;
	gzBool									m_hasPrimBinding;
	gzBool									m_hasVertexBinding;

};

class gzWeightValue
{
public:

	//!Default constructor.
	GZ_GRAPH_EXPORT gzWeightValue(gzFloat value=GZ_FLOAT_ZERO,gzUInt32 transformID=1,const gzMatrix4& preMult=gzGetUnitMatrix(),gzBool usePreMult=FALSE );

	//!Not equal operator.
	/*!
	Returns true if the two attributes not are equal. Otherwise true is returned.
	*/
	GZ_GRAPH_EXPORT gzBool operator!=(const gzWeightValue &right);

	gzUInt32	transformID;
	gzFloat		value;

	gzMatrix4	preMultMatrix;
	gzBool		usePremultMatrix;
	
	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT gzVoid write(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzVoid read(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzVoid pushBack(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;

};

class gzWeight
{
public:

	//!Constructor
	GZ_GRAPH_EXPORT gzWeight();

	//!Constructor with one defined weight.
	GZ_GRAPH_EXPORT gzWeight(gzFloat val);

	//!Constructor with two weights defined.
	GZ_GRAPH_EXPORT gzWeight(gzFloat val1,gzFloat val2);

	//!Equal operator.
	/*!
	Returns true if the two attributes are equal. Otherwise false is returned.
	*/
	GZ_GRAPH_EXPORT gzBool operator==(const gzWeight &right);

	GZ_GRAPH_EXPORT gzWeightValue & operator[](gzUInt32 index);

	gzArray<gzWeightValue>	weights;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT gzVoid write(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzVoid read(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzVoid pushBack(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;

};

//******************************************************************************
// Class	: gzGeometry
//									
// Purpose  : -
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
class gzGeometry : public gzBaseGeometry
{
public:

	//!Constructor
	/*!
	It is possible to specify a name for the gzGeometry.
	*/
	GZ_GRAPH_EXPORT gzGeometry(const gzString & name=GZ_EMPTY_STRING);

	//!Destructor
	GZ_GRAPH_EXPORT virtual ~gzGeometry();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
	GZ_GRAPH_EXPORT virtual gzBool useDeepCopy() override;
	
	// ---------- Geometry Interface ------------------------------------

	// ---------- General utilites --------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid	transform(gzMatrix4 &matrix);

	//!Optimizes the geometry.
	/*!
	If no optimize level is defined the GZ_GEO_OPTIMIZE_LEAVE_LINES is used.
	*/
	GZ_GRAPH_EXPORT virtual gzVoid	optimize(gzGeoOptimizeLevel level=GZ_GEO_OPTIMIZE_LEAVE_LINES);

	//!Combines two geometries.
	/*!
	Creates one compound geometry.
	*/
	GZ_GRAPH_EXPORT gzBool	combineGeometry(gzGeometry *toCombineWith,gzBool optimize=TRUE);
	GZ_GRAPH_EXPORT gzVoid	combineFinalGeometry(gzBool optimize=TRUE);
	GZ_GRAPH_EXPORT gzVoid	combineInternalGeometry();

	GZ_GRAPH_EXPORT gzVoid	averageNormals(gzVertexGroupInfo *info=nullptr,gzBool smoothAllIndex=FALSE);
	
	/*!
	Generates normals for the geometry. 
	
	Implemented for GZ_PRIM_TRIFANS, GZ_PRIM_TRIS, GZ_PRIM_TRISTRIPS
	*/
	GZ_GRAPH_EXPORT gzVoid	generateNormals();
	GZ_GRAPH_EXPORT gzBool	generateTangents(gzUInt32 textureUnit=0,gzUInt32 vertexList=10);
	GZ_GRAPH_EXPORT gzVoid	generateWeights(const gzFloat &factor=1.0f,gzUInt32 coordIndex=2,gzWeightMethod method=GZ_WEIGHT_START_TRANS,gzUInt32 baseID=1,gzFloat baseWeight=GZ_FLOAT_ONE);

	GZ_GRAPH_EXPORT gzVoid	convertToIndexed();
	GZ_GRAPH_EXPORT gzVoid	convertToNonIndexed();

	// ----- weight info ------------------------
	GZ_GRAPH_EXPORT gzBool	updateWeightInfo(gzContext *context);
	GZ_GRAPH_EXPORT gzBool	useVertexWeights();
	GZ_GRAPH_EXPORT gzWeightGeomInfo &getWeightInfo();
	GZ_GRAPH_EXPORT gzVoid	usePerfectWeightedNormals(gzBool on);
	GZ_GRAPH_EXPORT gzBool	usePerfectWeightedNormals() const;
	GZ_GRAPH_EXPORT gzVoid	smoothAllWeightedNormals(gzBool on);
	GZ_GRAPH_EXPORT gzBool	smoothAllWeightedNormals() const;

	// ----- Coordinate stuff -----------------------
	//!Returns the coordinate array for the gzGeometry.
	GZ_GRAPH_EXPORT gzArray<gzVec3> &	getCoordinateArray(gzBool changeData=TRUE);

	//!Returns an array of lengts of the primitives in the gzGeometry.
	GZ_GRAPH_EXPORT gzArray<gzUInt32>&	getPrimLengthArray(gzBool changeData=TRUE);

	//!Returns the color array for the gzGeometry.
	GZ_GRAPH_EXPORT gzArray<gzVec4> &	getColorArray(gzBool changeData=TRUE);

	//!Returns the array of normals for the gzGeometry.
	GZ_GRAPH_EXPORT gzArray<gzVec3> &	getNormalArray(gzBool changeData=TRUE);

	//!Returns the array of texture coordinates for the gzGeometry.
	GZ_GRAPH_EXPORT gzArray<gzVec2> &	getTexCoordinateArray(gzUInt32 unit=0,gzBool changeData=TRUE);

	//!Returns an array which contains TRUE for edges, otherwise false.
	/*!

	*/
	GZ_GRAPH_EXPORT gzArray<gzBool> &	getEdgeArray(gzBool changeData=TRUE);

	//!Returns the weight array for the gzGeometry.
	GZ_GRAPH_EXPORT gzArray<gzWeight>&	getWeightArray(gzBool changeData=TRUE);

	//!Returns the index array for the geometry.
	/*!
	The index array describes which index in the geometry coordinate array that are use to create each primitive.
	*/
	GZ_GRAPH_EXPORT gzArray<gzUInt32>&	getIndexArray(gzBool changeData=TRUE);
	
	GZ_GRAPH_EXPORT gzVoid		setTextureUnits( gzUInt32 size=1 );
	GZ_GRAPH_EXPORT gzUInt32	getTextureUnits();

	//!Returns an array of arrays with texture coordinates.
	GZ_GRAPH_EXPORT gzArray<gzArray<gzVec2> >&	getTexCoordinateArrays(gzBool changeData=TRUE);

	// Normal array version

	//!Sets the coordinate array for the geometry.
	/*!
	Sets an array of coordinates which is used by the geometry to create triangles.
	*/
	GZ_GRAPH_EXPORT gzVoid	setCoordinateArray		( const gzArray<gzVec3> & array);
	
	//!	Sets an array which specify the size of each primitive in the geometry. 
	/*!
	This array need to be specified when using the following primitives:\n
	GZ_PRIM_LINESTRIPS \n
    GZ_PRIM_FLAT_LINESTRIPS \n
	GZ_PRIM_LINELOOPS \n
	GZ_PRIM_TRISTRIPS \n
	GZ_PRIM_FLAT_TRISTRIPS \n
	GZ_PRIM_TRIFANS \n		
	GZ_PRIM_FLAT_TRIFANS \n
	GZ_PRIM_POLYS \n 		
	GZ_PRIM_QUADSTRIPS	
	*/
	GZ_GRAPH_EXPORT gzVoid	setPrimLengthArray		( const gzArray<gzUInt32>& array);
	//! convenient func for just one primitive
	GZ_GRAPH_EXPORT gzVoid	setPrimLength			(const gzUInt32 &length);
	
	//!Sets an array with colors that shall be applied to the geometry.
	GZ_GRAPH_EXPORT gzVoid	setColorArray			( const gzArray<gzVec4> & array);
	//!Set overall color
	GZ_GRAPH_EXPORT gzVoid	setColor(const gzVec4 &color);
	
	//!Sets an array with normals that shall be applied to the geometry.
	GZ_GRAPH_EXPORT gzVoid	setNormalArray			( const gzArray<gzVec3> & array);
	
	//!Sets an array with texture coordinates.
	GZ_GRAPH_EXPORT gzVoid	setTexCoordinateArray	( const gzArray<gzVec2> & array , gzUInt32 unit=0);
	GZ_GRAPH_EXPORT gzVoid	setEdgeArray			( const gzArray<gzBool> & array);
	GZ_GRAPH_EXPORT gzVoid	setWeightArray			( const gzArray<gzWeight> & array);

	//!Sets an index array.
	/*!
	Sets an array which specifies the order the coordinates and texture coordinates for the geometry shall be applied.
	If each point is used several times it is better to specify each coordinate once and 
	than use the index array to specify when a point shall be used.
	*/
	GZ_GRAPH_EXPORT gzVoid	setIndexArray			( const gzArray<gzUInt32> & array);

	//!Sets an array of texture coordinates arrays.
	GZ_GRAPH_EXPORT gzVoid	setTexCoordinateArrays	(const gzArray<gzArray<gzVec2> > &array);
	
	// Dynamic array version
	
	//!Sets a dynamic coordinate array for the geometry.
	/*!
	Sets a dynamic array of coordinates which is used by the geometry to create triangles.
	*/
	GZ_GRAPH_EXPORT gzVoid	setCoordinateArray		( const gzDynamicArray<gzVec3> & array);
	
	//!Sets an array which specifies the size of each primitive in the geometry. 
	/*!
	This array need to be specified when using the following primitives:\n
	GZ_PRIM_LINESTRIPS \n
    GZ_PRIM_FLAT_LINESTRIPS \n
	GZ_PRIM_LINELOOPS \n
	GZ_PRIM_TRISTRIPS \n
	GZ_PRIM_FLAT_TRISTRIPS \n
	GZ_PRIM_TRIFANS \n	
	GZ_PRIM_FLAT_TRIFANS \n
	GZ_PRIM_POLYS \n		
	GZ_PRIM_QUADSTRIPS	
	*/
	GZ_GRAPH_EXPORT gzVoid	setPrimLengthArray		( const gzDynamicArray<gzUInt32>& array);

	//!Sets a dynamic array with colors that shall be applied to the geometry.
	GZ_GRAPH_EXPORT gzVoid	setColorArray			( const gzDynamicArray<gzVec4> & array);

	//!Sets a dynamic array with normals that shall be applied to the geometry.
	GZ_GRAPH_EXPORT gzVoid	setNormalArray			( const gzDynamicArray<gzVec3> & array);
	
	//!Sets a dynamic array with texture coordinates.
	GZ_GRAPH_EXPORT gzVoid	setTexCoordinateArray	( const gzDynamicArray<gzVec2> & array , gzUInt32 unit=0);
	GZ_GRAPH_EXPORT gzVoid	setEdgeArray			( const gzDynamicArray<gzBool> & array);
	GZ_GRAPH_EXPORT gzVoid	setWeightArray			( const gzDynamicArray<gzWeight> & array);

	//!Sets a dynamic index array.
	/*!
	Sets a dynamic array which specifies the order the coordinates and texture coordinates for the geometry shall be applied.
	If each point is used several times it is better to specify each coordinate once and 
	than use the index array to specify when a point shall be used.
	*/
	GZ_GRAPH_EXPORT gzVoid	setIndexArray			( const gzDynamicArray<gzUInt32> & array);

	//!Sets a dynamic array of texture coordinates arrays.
	GZ_GRAPH_EXPORT gzVoid	setTexCoordinateArrays	( const	gzDynamicArray<gzArray<gzVec2> > &array);

	// Prim type

	//!Returns the primitive type of the geometry.
	GZ_GRAPH_EXPORT gzGeoPrimType getGeoPrimType();
	
	//!Specify the primitive type for the geometry.
	GZ_GRAPH_EXPORT gzVoid setGeoPrimType(gzGeoPrimType primtype);

	// Binding

	//!Returns the binding method for the normals.
	GZ_GRAPH_EXPORT gzGeoAttribBinding getNormalBind();
	
	//!Returns the binding method for the colors.
	GZ_GRAPH_EXPORT gzGeoAttribBinding getColorBind();
	
	//!Returns the binding method for the texture.
	GZ_GRAPH_EXPORT gzGeoAttribBinding getTexBind(gzUInt32 unit=0);

	//!Returns an array of binding methods for the texture.
	GZ_GRAPH_EXPORT gzArray<gzGeoAttribBinding> & getTexBindArray(gzBool changeData=TRUE);

	//!Specifies how the normal is binded to the geometry.
	GZ_GRAPH_EXPORT gzVoid	setNormalBind( gzGeoAttribBinding binding);
	
	//!Specifies how the color is binded to the geometry.
	GZ_GRAPH_EXPORT gzVoid	setColorBind( gzGeoAttribBinding binding);
	 
	//!Specifies how the texture is binded to the geometry.
	GZ_GRAPH_EXPORT gzVoid	setTexBind( gzGeoAttribBinding binding,gzUInt32 unit=0);

	//!Sets an array with specification of how the texture is binded to the geometry.
	GZ_GRAPH_EXPORT gzVoid	setTexBindArray( const gzArray<gzGeoAttribBinding> & binding);

	// Misc
	
	//!Returns the size of the points in the geometry.
	GZ_GRAPH_EXPORT gzFloat	getPointSize();
	
	//!Sets the size of the points in the geometry.
	GZ_GRAPH_EXPORT gzVoid	setPointSize(gzFloat size);

	//!Returns the width of the lines in the geometry.
	GZ_GRAPH_EXPORT gzFloat	getLineWidth();
	
	//!Sets the width for the lines in the geometry.
	GZ_GRAPH_EXPORT gzVoid	setLineWidth(gzFloat size);

	GZ_GRAPH_EXPORT gzVoid	useDisplayList(gzBool on);
	GZ_GRAPH_EXPORT gzBool	useDisplayList();
	GZ_GRAPH_EXPORT gzVoid	reCreateDisplayList();

	// ---------- Utilities ---------------------------------------------

	GZ_GRAPH_EXPORT gzVoid swapCoordinateOrder();

	// ---------- Common graph functions --------------------------------

	//!Updates the boundary for the gzGeometry.
	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Serializing -------------------------------------------

	//!Writes the gzGeometry data to the adapter.
	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;

	//!Reads the gzGeometry data from the adapter.
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;

	//!Returns the size of the gzGeometry data.
	GZ_GRAPH_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

	// ---------- Debug output ------------------------------------------
	//!Prints debug information about the class.
	/*!
	Prints to the console by default. Uses gzMessage mechanism.
	*/
	GZ_GRAPH_EXPORT virtual gzVoid debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ---------- Vertex Attributes -------------------------------------
	
	GZ_GRAPH_EXPORT gzVoid addVertexAttributeList(gzVertexAttributeList *list);
	GZ_GRAPH_EXPORT gzVoid removeVertexAttributeList(gzVertexAttributeList *list);
	GZ_GRAPH_EXPORT gzVoid removeAllVertexAttributeLists();
	GZ_GRAPH_EXPORT gzVertexAttributeListPtr getVertexAttributeList(gzUInt32 listIndex);
	GZ_GRAPH_EXPORT gzBool hasActiveVertexAttributeList() const;
	GZ_GRAPH_EXPORT gzArray<gzVertexAttributeListPtr> getVertexAttributeLists();

	// ---------- Vertex Buffer Object Control --------------------------

	GZ_GRAPH_EXPORT gzVoid setBind(gzBool bind,gzVertexBufferType type=GZ_VBO_STATIC);
	GZ_GRAPH_EXPORT gzVoid reBind();
	GZ_GRAPH_EXPORT gzBool isBind();

	// ---------- geometry utilities ------------------------------------

	//! Returns clockwise and/or counter clockwise windings of polys
	GZ_GRAPH_EXPORT gzPolygonWinding polygonWinding(const gzVec3 &upVec=GZ_Z_VEC3);

	//! Returns FALSE if geometry is not valid, index out of range etc.
	GZ_GRAPH_EXPORT gzBool	checkValidGeometry(gzBool notify=TRUE);

	//! Creates a new polygon/line set out of geometry data
	GZ_GRAPH_EXPORT gzVoid	stitchGeometry(const gzVec3 &upVec=GZ_Z_VEC3,gzStitchSettings setting=GZ_STITCH_SETTING_DEFAULT,gzFloat maxdist=GZ_FLOAT_ONE);


	// ---------- Common context based utilities ------------------------

	GZ_GRAPH_EXPORT static gzVoid setMaxVBOInitsPerFrame(gzContext *context ,gzUInt32 maxVal);
	GZ_GRAPH_EXPORT static gzVoid setMaxDisplayListsInitsPerFrame(gzContext *context ,gzUInt32 maxVal);

	// ---------- rebuild internal data --------------------------------
	GZ_GRAPH_EXPORT gzVoid virtual updateGeomInternals();

protected:

	friend class gzGeometryOptimizer;	// Friend declaration to geometry optimizer

	GZ_GRAPH_EXPORT gzVoid preTraverseBuffers(gzContext *context,gzBool useWeights);
	GZ_GRAPH_EXPORT gzVoid preTraverseStatistics(gzContext *context,gzBool useWeights,gzUInt32 factor=1,gzBool renderStats=TRUE);

	gzFloat									m_pointSize;
	gzFloat									m_lineWidth;

	// Type

	gzGeoPrimType  							m_primType:5;

	// Binding data

	gzGeoAttribBinding						m_normalBind:3;
	gzGeoAttribBinding						m_colorBind:3;

	gzBool									m_useDisplayList:1;
	gzBool									m_recreateDisplayList:1;
	gzBool									m_usePerfectWeightedNormals:1;
	gzBool									m_smoothAllWeigthedNormals:1;
	gzBool									m_checkValidGeometry:1;

	gzDynamicArray<gzDisplayListInfo>		m_dispInfo;
	
	gzArray< gzGeoAttribBinding >			m_texBind;
	
	// Prim lengths
	gzArray<gzUInt32>						m_length;
 
	gzArray<gzVec3>							m_coordinates;
	gzArray<gzVec4>							m_colors;
	gzArray<gzVec3>							m_normals;
	gzArray<gzUInt32>						m_index;

	gzArray< gzWeight >						m_weights;

	gzArray< gzArray<gzVec2>	>			m_tex_coordinates;

	gzArray<gzBool>							m_edges;

	gzLateBindData<gzWeightGeomInfo>		m_weightInfo;

	gzUInt32								m_instances;


	// Combined Info ----------------------------------

	class gzCombineInfo
	{
	public:

		gzCombineInfo():vertexCount(0){}

		gzRefList<gzGeometry>	combGeom;

		gzUInt32					vertexCount;
	};

	gzLateBindData<gzCombineInfo>				m_combinedGeometry;
	
	// Vertex Attributes
	
	gzVertexAttributeManager 					m_vertexAttributes;

	// Vertex buffer objects bindings

	gzLateBindData<gzVertexBufferInfo>			m_vboBindInfo;

	class gzSpatialIndex
	{
	public:

		gzUInt32	v0,v1,v2;
		gzUInt32	n0;
	};

	gzLateBindData<gzSpatialData<gzSpatialIndex> >	m_spatialIndex;

	GZ_GRAPH_EXPORT gzVoid checkIntersection(gzIntersectorAction *isector,gzContext *context,const gzSpatialIndex &spatial,gzIntersectorResult &result,gzBool addSpatial);

	GZ_GRAPH_EXPORT	gzVoid virtual calculateIntersections(gzIntersectorAction *isector , gzContext *context);

private:
		
	gzVoid draw_POINTS(gzContext *context,gzBool useWeights);
	gzVoid draw_LINES(gzContext *context, gzBool useWeights);
	gzVoid draw_LINESTRIPS(gzContext *context, gzBool useWeights);
	gzVoid draw_TRIS(gzContext *context, gzBool useWeights);
	gzVoid draw_QUADS(gzContext *context, gzBool useWeights);
	gzVoid draw_TRISTRIPS(gzContext *context, gzBool useWeights);
	gzVoid draw_TRIFANS(gzContext *context, gzBool useWeights);
	gzVoid draw_POLYS(gzContext *context, gzBool useWeights);
	gzVoid draw_QUADSTRIPS(gzContext *context, gzBool useWeights);
	gzVoid draw_LINELOOPS(gzContext *context, gzBool useWeights);
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzGeometry);

//******************************************************************************
// Class	: gzTriGeometry
//									
// Purpose  : Special Geometry that consists of triangles
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990409	Created 
//									
//******************************************************************************
/*! Creates a gzTriGeometry based on a gzGeometry with triangles. Default color is set to white
*/
class gzTriGeometry : public gzGeometry
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	//!Constructor 
	/*!
	It is possible to specify a name for the triGeometry.
	*/
	GZ_GRAPH_EXPORT gzTriGeometry(const gzString & name=GZ_EMPTY_STRING);

	//!Destructor
	GZ_GRAPH_EXPORT virtual ~gzTriGeometry(){};

	//Sets a triangle.
	/*!
	A triangle with index one is created with the corners in points a, b and c.
	*/
	GZ_GRAPH_EXPORT gzVoid setTri(gzUInt32 index , const gzVec3 &a , const gzVec3 &b , const gzVec3 &c);

	//!Sets the number of triangles in the triangle geometry.
	GZ_GRAPH_EXPORT gzVoid setSize(gzUInt32 size);

	//!Sets the color for triangle with specified index.
	GZ_GRAPH_EXPORT gzVoid setColor( gzUInt32 index , const gzVec4 &color);

	//!Sets the color for the whole geometry.
	GZ_GRAPH_EXPORT gzVoid setColor( const gzVec4 &color );

	//!Sets the edges for the triangle with specified index. 
	/*!
	If the edge of a triangle is an edge of the triGeometry this is assigned the value TRUE, else it is assigned FALSE.

	Default value for each edge in the triangle is FALSE.
	*/
	GZ_GRAPH_EXPORT gzVoid setEdge( gzUInt32 index , gzBool ab , gzBool bc , gzBool ca );
    
	//!Sets the texture coordinates for the triangle with specified index.
	GZ_GRAPH_EXPORT gzVoid setTexCord(gzUInt32 index , const gzVec2 &a , const gzVec2 &b , const gzVec2 &c , gzUInt32 unit=0);

	//!Sets the color for the triangle with specified index. 
	/*!
	Different colors can be set for the three corners.
	*/
	GZ_GRAPH_EXPORT gzVoid setColor( gzUInt32 index , const gzVec4 &col_a , const gzVec4 &col_b , const gzVec4 &col_c );

	//!Calculates normals for the geometry and store in a normal array.
	GZ_GRAPH_EXPORT gzVoid calculateNormals();

	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

private:
			
	gzUInt32 m_size;

};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzTriGeometry);

//******************************************************************************
// Class	: gzInstancedGeometry
//									
// Purpose  : Special Geometry that is repeated for multiple instances
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080211	Created 
//									
//******************************************************************************
class gzInstancedGeometry : public gzGeometry
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzInstancedGeometry(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzInstancedGeometry(){};

	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	//!Updates the boundary.
	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// --------- Properties ---------------------------------------------

	//! Number of instances
	GZ_PROPERTY_EXPORT(gzUInt32,		Instances,		GZ_GRAPH_EXPORT);

	//! Center of all instances
	GZ_PROPERTY_EXPORT_(gzVec3,		Center,			GZ_GRAPH_EXPORT);

	//! Radius of surrounding sphere
	GZ_PROPERTY_EXPORT_(gzFloat,		Radius,			GZ_GRAPH_EXPORT);

private:
		
	gzVoid draw_POINTS(gzContext *context);
	gzVoid draw_LINES(gzContext *context);
	gzVoid draw_LINESTRIPS(gzContext *context);
	gzVoid draw_TRIS(gzContext *context);
	gzVoid draw_QUADS(gzContext *context);
	gzVoid draw_TRISTRIPS(gzContext *context);
	gzVoid draw_TRIFANS(gzContext *context);
	gzVoid draw_POLYS(gzContext *context);
	gzVoid draw_QUADSTRIPS(gzContext *context);
	gzVoid draw_LINELOOPS(gzContext *context);
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzInstancedGeometry);


//--------------------------------- Template Specifics ------------------------------------------------------

// -------------------------------- copyInstances -----------------------------------------------------------

template <> inline gzVoid copyInstances(gzWeightValue* to, gzWeightValue* from, const gzUInt64& count, gzBool /*clearSource*/)
{
	memmove(to, from, count * sizeof(gzWeightValue));
}

// ---------------------------- End of template specifics ---------------------------------------------------

#endif

