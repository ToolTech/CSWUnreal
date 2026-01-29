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
// File			: gzGeometryOptimizer.h
// Module		: 
// Description	: Class definition of the gzGeometryOptimizer class
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
// AMO	981122	Created file 	
// AMO	230621	Fixed problem in self intersecting geometry		(2.12.88)
// AMO	260126	Added triangle container API					(2.12.307)
// AMO	260126	Added triangle container aggregation			(2.12.307)
// AMO	260127	Switch entries to geometry handles				(2.12.307)
// AMO	260127	Added triangle optimize test flag		(2.12.308)
//
//******************************************************************************
#ifndef __GZ_GEOMETRY_OPTIMIZER_H__
#define __GZ_GEOMETRY_OPTIMIZER_H__

/*!	\file 
	\brief Base definitions for geometry optimization classes

*/

#include "gzGeometry.h"
#include "gzMutex.h"
#include "gzState.h"

GZ_DECLARE_MEMBASE_EXPORT(gzVertex,GZ_GRAPH_EXPORT);
GZ_DECLARE_MEMBASE_EXPORT(gzTriangle,GZ_GRAPH_EXPORT);
GZ_DECLARE_MEMBASE_EXPORT(gzPolygon,GZ_GRAPH_EXPORT);

GZ_DECLARE_RECYCLE_DATA_EXPORT(gzGeometryOptimizer, GZ_GRAPH_EXPORT);

//******************************************************************************
// Class	: gzVertex
//									
// Purpose  : Utility class to hold vertex data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990106	Created 
//									
//******************************************************************************
class gzVertex : public gzReference , public GZ_MEMBASE(gzVertex)
{
public:

	GZ_MEMBASE_IMP(gzVertex);

	GZ_GRAPH_EXPORT gzVertex();

	GZ_GRAPH_EXPORT virtual ~gzVertex();

	GZ_GRAPH_EXPORT virtual	gzBool	useDeepCopy() { return FALSE; }

	// -------------- data ---------------

	gzVec3			coordinate;
	gzVec2			projcoordinate;
	gzVec3			normal;
	gzVec4			color;
	gzArray<gzVec2>	texcoord;
	gzWeight		weight;
	gzBool			edge;
};

//******************************************************************************
// Class	: gzVertexList
//									
// Purpose  : Utility class to very fast recycle storage for vertex lists
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080124	Created 
//									
//******************************************************************************
class gzVertexList : public gzRecycleDataExport(gzGeometryOptimizer)<gzRefList<gzVertex> >
{
public:
	virtual gzVoid onNewItem(gzRefList<gzVertex> & data) const;
	virtual gzVoid onInitItem(gzRefList<gzVertex> & data) const;
};

//******************************************************************************
// Class	: gzTriStrip
//									
// Purpose  : Utility class to hold tristrip data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990106	Created 
//									
//******************************************************************************
class gzTriStrip : public gzReference
{
public:
	GZ_GRAPH_EXPORT gzTriStrip();

	GZ_GRAPH_EXPORT virtual ~gzTriStrip();

	GZ_GRAPH_EXPORT virtual	gzBool	useDeepCopy() { return FALSE; }

	// ----------- data --------------

	gzVertexList	vertexList;
};

//******************************************************************************
// Class	: gzPolygon
//									
// Purpose  : Utility class to hold polygon data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990106	Created 
//									
//******************************************************************************
class gzPolygon : public gzReference , public GZ_MEMBASE(gzPolygon)
{
public:

	GZ_MEMBASE_IMP(gzPolygon);

	GZ_GRAPH_EXPORT gzPolygon();

	GZ_GRAPH_EXPORT virtual ~gzPolygon();

	// ------------ utils --------------

	GZ_GRAPH_EXPORT gzBool	calcNormal(gzBool project);
	GZ_GRAPH_EXPORT gzVoid	clean(const gzGeoOptimizeLevel &level);
	GZ_GRAPH_EXPORT gzBool	intersect(const gzVec3 &p1 , const gzVec3 &p3);
	GZ_GRAPH_EXPORT gzBool	hasVertex(gzVertex * p);
	GZ_GRAPH_EXPORT gzBool	contains(const gzVec3 &p1 , gzFloat maxdist);
	GZ_GRAPH_EXPORT gzBool	contains(gzPolygon *poly , gzFloat maxdist);
	GZ_GRAPH_EXPORT gzBool	addSubPoly(gzPolygon *poly , gzFloat maxdist);
	GZ_GRAPH_EXPORT gzVoid	subtractPolyList(gzRefList<gzPolygon> &subs);
	GZ_GRAPH_EXPORT gzDouble minVertexDistanceMag(gzPolygon *poly,gzUInt32 *coordIndex=nullptr,gzUInt32 *closestCoordIndex=nullptr);
	GZ_GRAPH_EXPORT gzBool	insertPoly(gzPolygon *poly,gzUInt32 startIndex,gzUInt32 polyStartIndex,gzBool subtract);
	GZ_GRAPH_EXPORT gzVoid	reverse();

	GZ_GRAPH_EXPORT virtual	gzBool	useDeepCopy() { return FALSE; }
	
	// ----------- data ----------------

	gzVertexList			vertexList;
	gzVec3					normalVec;
	gzMatrix4				projector;
	gzPolygonWinding		winding;
	gzRefList<gzPolygon>	subPolys;
};

GZ_DECLARE_REFPTR(gzPolygon);

//******************************************************************************
// Class	: gzTriangle
//									
// Purpose  : Utility class to hold triangle data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990106	Created 
//									
//******************************************************************************
class gzTriangle : public gzReference , public GZ_MEMBASE(gzTriangle)
{
public:

	GZ_MEMBASE_IMP(gzTriangle);

	GZ_GRAPH_EXPORT gzTriangle();
	GZ_GRAPH_EXPORT virtual ~gzTriangle();

	GZ_GRAPH_EXPORT virtual	gzBool	useDeepCopy() { return FALSE; }


	// ------------ data --------------

	gzVertex	a,b,c;

	gzTriangle *a_b , *b_c , *c_a;

	gzUInt32	sourceIndex;

	gzUByte		connections;

	gzUByte		isValid;
};

GZ_DECLARE_REFPTR(gzTriangle);

// Triangle container optimization flags
enum gzTriangleOptimizeFlags
{
	GZ_TRIANGLE_OPTIMIZE_NONE		=	0,
	GZ_TRIANGLE_OPTIMIZE_TEST_1	=	(1<<0)
};

GZ_USE_BIT_LOGIC(gzTriangleOptimizeFlags);

//******************************************************************************
// Class	: gzTriangleContainerEntry
//										
// Purpose  : Context entry for triangles built from geometry
//										
// Notes	: -	
//										
// Revision History...									
//										
// Who	Date	Description							
//										
// AMO	260126	Created 						
//										
//******************************************************************************
class gzTriangleContainerEntry : public gzReference
{
public:
	GZ_GRAPH_EXPORT gzTriangleContainerEntry();
	GZ_GRAPH_EXPORT gzTriangleContainerEntry(const gzTriangleContainerEntry &copy);
	GZ_GRAPH_EXPORT gzTriangleContainerEntry &operator=(const gzTriangleContainerEntry &copy);

	GZ_GRAPH_EXPORT virtual gzBool useDeepCopy() { return FALSE; }

	gzGeometryPtr	geometry;
	gzStatePtr		state;
	gzMatrix4		worldTransform;
	gzMatrix4		worldNormalTransform;
	gzUInt32		texUnits;
	gzBool		useNormals;
	gzBool		useTexCoord;
	gzBool		useEdges;
	gzBool		useColors;
	gzBool		useWeights;
};

GZ_DECLARE_REFPTR(gzTriangleContainerEntry);

//******************************************************************************
// Class	: gzTriangleContainer
//										
// Purpose  : Container for triangle data built from geometry
//										
// Notes	: -	
//										
// Revision History...									
//										
// Who	Date	Description							
//										
// AMO	260126	Created 						
//										
//******************************************************************************
class gzTriangleContainer : public gzReference
{
public:

	GZ_GRAPH_EXPORT gzTriangleContainer();
	GZ_GRAPH_EXPORT virtual ~gzTriangleContainer();

	GZ_GRAPH_EXPORT gzBool buildFromGeometry(gzGeometry *geometry,gzGeoOptimizeLevel level=GZ_GEO_OPTIMIZE_TO_TRIANGLES|GZ_GEO_OPTIMIZE_USE_INDEXED|GZ_GEO_OPTIMIZE_USE_OVERALL);
	GZ_GRAPH_EXPORT gzBool buildFromGeometry(gzGeometry *geometry,const gzMatrix4 &transform,gzState *state,gzGeoOptimizeLevel level=GZ_GEO_OPTIMIZE_TO_TRIANGLES|GZ_GEO_OPTIMIZE_USE_INDEXED|GZ_GEO_OPTIMIZE_USE_OVERALL);
	GZ_GRAPH_EXPORT gzUInt32 addFromGeometry(gzGeometry *geometry,const gzMatrix4 &transform,gzState *state,gzGeoOptimizeLevel level=GZ_GEO_OPTIMIZE_TO_TRIANGLES|GZ_GEO_OPTIMIZE_USE_INDEXED|GZ_GEO_OPTIMIZE_USE_OVERALL);
	GZ_GRAPH_EXPORT gzVoid clear();

	GZ_GRAPH_EXPORT gzRefList<gzTriangle> &getTriangles();
	GZ_GRAPH_EXPORT const gzRefList<gzTriangle> &getTriangles() const;

	GZ_GRAPH_EXPORT gzUInt32 getTriangleCount() const;
	GZ_GRAPH_EXPORT gzUInt32 getEntryCount() const;
	GZ_GRAPH_EXPORT gzBool writeBack(gzString *errorString=nullptr);
	GZ_GRAPH_EXPORT gzBool optimize(gzTriangleOptimizeFlags flags,gzFloat param1,gzFloat param2,gzFloat param3,gzString *errorString=nullptr);
	GZ_GRAPH_EXPORT gzTriangleContainerEntry &getEntry(gzUInt32 index);
	GZ_GRAPH_EXPORT const gzTriangleContainerEntry &getEntry(gzUInt32 index) const;

private:

	gzVoid createTriangleList(gzGeometry *geometry,const gzMatrix4 &transform,const gzMatrix4 &normalTransform,gzUInt32 sourceIndex);
	gzTriangle *findTriangle(gzVertex &a , gzVertex &b , gzTriangle *exclude,gzUInt32 sourceIndex);
	gzBool updateGeometryForEntry(gzUInt32 entryIndex,gzString *errorString);

	gzRefList<gzTriangle>			 m_triList;
	gzRefDict<gzVec3,gzTriangle>	m_hashTriList;
	gzDynamicArray<gzTriangleContainerEntryPtr>	m_entries;

	gzBool		m_useNormals;
	gzBool		m_useTexCoord;
	gzBool		m_useEdges;
	gzBool		m_useColors;
	gzBool		m_useWeights;
};

GZ_DECLARE_REFPTR(gzTriangleContainer);

//******************************************************************************
// Class	: gzPolygonOptimizer
//									
// Purpose  : Utility class to optimize polygon geometry 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990106	Created 
//									
//******************************************************************************
class gzPolygonOptimizer
{
public:

	GZ_GRAPH_EXPORT gzPolygonOptimizer();
	GZ_GRAPH_EXPORT virtual ~gzPolygonOptimizer();

	GZ_GRAPH_EXPORT gzBool optimize(gzGeometry *geometry , gzGeoOptimizeLevel level);

	GZ_GRAPH_EXPORT gzPolygonWinding polygonWinding(gzGeometry *geometry,const gzVec3 &up);
	GZ_GRAPH_EXPORT gzBool stitchGeometry(gzGeometry *geometry,const gzVec3 &upVec=GZ_Z_VEC3,gzStitchSettings setting=GZ_STITCH_SETTING_DEFAULT,gzFloat maxdist=GZ_FLOAT_ONE);

private:

	gzVoid	createPolygonList(gzBool convertToConvex);
	gzVoid	optimizeForTriFan(gzPolygon *poly);
	gzBool	updateGeometry(gzBool force,gzBool isTrifan);
	gzVoid	calculatePolygonWinding(const gzVec3 &up);
	gzVoid	calculatePolygonContainment(const gzVec3 &up,gzFloat maxdist);
	gzVoid	splitIntersectedPolygons();

	gzVoid	createEvenOddPolygons();

	gzGeometry				*m_geometry;

	gzRefList<gzPolygon>	m_polygonList;
	gzRefList<gzPolygon>	m_polygonTopList;

	gzGeoOptimizeLevel		m_optimizeLevel;

	gzBool		m_useNormals;
	gzBool		m_useTexCoord;
	gzBool		m_useEdges;
	gzBool		m_useColors;
};

class gzTriOptimData
{
public:

	gzRefList<gzTriangle>			m_triList;
	gzRefList<gzTriStrip>			m_stripList;
	gzRefDict<gzVec3,gzTriangle>	m_hashTriList;
};

class gzRecycledTriOptimData : public gzRecycleDataExport(gzGeometryOptimizer)<gzTriOptimData>
{
public:

	virtual gzVoid onNewItem(gzTriOptimData & data) const 
	{
		data.m_hashTriList.setSize(100);
		data.m_hashTriList.useAutoResize(TRUE);
		data.m_hashTriList.reuseLinks(TRUE);
		data.m_stripList.reuseLinks(TRUE);
		data.m_triList.reuseLinks(TRUE);
	}									
		
	virtual gzVoid onInitItem(gzTriOptimData & data) const 
	{
		data.m_hashTriList.clear();
		data.m_stripList.clear();
		data.m_triList.clear();
	}

};


//******************************************************************************
// Class	: gzTriOptimizer
//									
// Purpose  : Utility class to optimize triangle geometry 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990106	Created 
//									
//******************************************************************************
class gzTriOptimizer
{
public:

	GZ_GRAPH_EXPORT gzTriOptimizer():m_leastTriangle(NULL){};

	GZ_GRAPH_EXPORT virtual ~gzTriOptimizer(){};

	GZ_GRAPH_EXPORT gzBool optimize(gzGeometry *geometry , gzGeoOptimizeLevel level);
	GZ_GRAPH_EXPORT gzPolygonWinding polygonWinding(gzGeometry *geometry,const gzVec3 &up);

private:

	gzVoid createTriangleList();
	gzVoid optimizeForTriList();
	gzBool updateGeometry();

	gzTriangle *findTriangle(gzVertex &a , gzVertex &b , gzTriangle *exclude);

	gzTriangle *findLeastTriangle();

	gzGeometry					*m_geometry;

	gzRecycledTriOptimData		m_optimData;

	gzGeoOptimizeLevel			m_optimizeLevel;

	gzTriangle					*m_leastTriangle;

	gzUByte						m_leastConnections;


	gzBool		m_useNormals;
	gzBool		m_useTexCoord;
	gzBool		m_useEdges;
	gzBool		m_useColors;
	gzBool		m_useWeights;
};

//******************************************************************************
// Class	: gzTrifanOptimizer
//									
// Purpose  : Utility class to optimize trifan geometry
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990106	Created 
//									
//******************************************************************************
class gzTrifanOptimizer
{
public:

	GZ_GRAPH_EXPORT gzTrifanOptimizer(){};

	GZ_GRAPH_EXPORT virtual ~gzTrifanOptimizer(){};

	GZ_GRAPH_EXPORT gzBool optimize(gzGeometry *geometry , gzGeoOptimizeLevel level);

private:

	gzGeometry	*m_geometry;

	gzBool		m_useNormals;
	gzBool		m_useTexCoord;
	gzBool		m_useEdges;
	gzBool		m_useColors;

	gzVoid createTriData();

};

class gzTristripOptimizer
{
public:

	GZ_GRAPH_EXPORT gzTristripOptimizer(){};

	GZ_GRAPH_EXPORT virtual ~gzTristripOptimizer(){};

	GZ_GRAPH_EXPORT gzBool optimize(gzGeometry *geometry , gzGeoOptimizeLevel level);

private:

	gzGeometry	*m_geometry;

	gzBool		m_useNormals;
	gzBool		m_useTexCoord;
	gzBool		m_useEdges;
	gzBool		m_useColors;

	gzVoid createTriData();

};

//******************************************************************************
// Class	: gzGeometryOptimizer
//									
// Purpose  : Utility class to convert geometry to optimized fans or polys
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990106	Created 
//									
//******************************************************************************
class gzGeometryOptimizer
{
public:
	GZ_GRAPH_EXPORT static gzBool optimize(gzGeometry *geometry , gzGeoOptimizeLevel level=GZ_GEO_OPTIMIZE_LEAVE_LINES|GZ_GEO_OPTIMIZE_COMBINE_INTERNAL);
	GZ_GRAPH_EXPORT static gzPolygonWinding polygonWinding(gzGeometry *geometry,const gzVec3 &upVec=GZ_Z_VEC3);
	GZ_GRAPH_EXPORT static gzVoid stitchGeometry(gzGeometry *geometry,const gzVec3 &upVec=GZ_Z_VEC3,gzStitchSettings setting=GZ_STITCH_SETTING_DEFAULT,gzFloat maxdist=GZ_FLOAT_ONE);
	GZ_GRAPH_EXPORT static gzTriangleContainer *createTriangleContainer(gzGeometry *geometry,gzGeoOptimizeLevel level=GZ_GEO_OPTIMIZE_TO_TRIANGLES|GZ_GEO_OPTIMIZE_USE_INDEXED|GZ_GEO_OPTIMIZE_USE_OVERALL);
	GZ_GRAPH_EXPORT static gzTriangleContainer *createTriangleContainer(gzGeometry *geometry,const gzMatrix4 &transform,gzState *state,gzGeoOptimizeLevel level=GZ_GEO_OPTIMIZE_TO_TRIANGLES|GZ_GEO_OPTIMIZE_USE_INDEXED|GZ_GEO_OPTIMIZE_USE_OVERALL);
};


#endif

