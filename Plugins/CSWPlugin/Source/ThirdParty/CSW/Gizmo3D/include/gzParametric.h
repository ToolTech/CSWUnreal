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
// File			: gzParametric.h
// Module		: 
// Description	: Class definition of parametric geometry classes
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.224
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
//
//******************************************************************************
#ifndef __GZ_PARAMETRIC_H__
#define __GZ_PARAMETRIC_H__

/*!	\file 
	\brief Base definitions for parametric geometry classes

*/

// The gzParametricGeometry implements a general purpose LOD function named
// IRMA (Improved ROAM Algorithm (C) 1999 Anders Modén)

#include "gzGeometry.h"

class gzParametricGeometry;

// ------------ Special constants ----------------------------------------------

const gzFloat I_127 = GZ_FLOAT_ONE/127.0f;

const gzFloat I_127_2=I_127*I_127;

// Forward declarations
class gzLODContainerItem;
class gzLODContainer;
class gzParametricGeometry;

//******************************************************************************
// Class	: gzLODItem
//									
// Purpose  : Private structure for automatic LOD calcs
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991020	Created 
//									
//******************************************************************************
class gzLODItem 
{
private:
	friend class gzLODContainerItem;
	friend class gzLODContainer;
	friend class gzParametricGeometry;

	gzByte		n_x,n_y,n_z;
	gzBool		renderChildren;
	gzFloat		diff2;
	gzUInt16	counter;

	gzBool isLODVisible(gzParametricGeometry *geom,gzLODContainerItem *item);

};


class gzLODSize 
{
public:
	gzFloat		diff2;
	gzByte		n_x,n_y,n_z;
};

//******************************************************************************
// Class	: gzLODContainerItem
//									
// Purpose  : Private structure for automatic LOD calcs
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000223	Created 
//									
//******************************************************************************
class gzLODContainerItem
{
private:

	friend class gzLODContainer;
	friend class gzParametricGeometry;
	friend class gzLODItem;

	gzLODContainerItem *leftChild,*rightChild;
	gzLODContainerItem * split;
	gzLODContainerItem * parent;
	
	gzUInt32		v0_s;
	gzUInt32		v0_t;
	gzUInt32		index_0;

	gzUInt32		v1_s;
	gzUInt32		v1_t;
	gzUInt32		index_1;

	gzUInt32		va_s;
	gzUInt32		va_t;
	gzUInt32		index_a;

	gzUInt32		vc_s;
	gzUInt32		vc_t;
	gzUInt32		index_c;

	gzUInt32		index;

	gzBool checkSplit(gzParametricGeometry *geom);

	gzVec3		calculateCenterDiff(gzParametricGeometry *geom);
	gzLODSize	completeUnifyDynamicLOD(gzParametricGeometry *geom);

	gzBool	updateIndex(gzParametricGeometry *geom);
	gzVoid	forceSplit(gzParametricGeometry *geom);
	gzVoid	updateSplit(gzParametricGeometry *geom);
	gzVoid	renderIndex(gzParametricGeometry *geom , gzUByte toggle=0);

	gzVoid	isectorIndex(gzParametricGeometry *geom,gzIntersectorAction *isector,gzContext *context);
};


//******************************************************************************
// Class	: gzLODContainer
//									
// Purpose  : Private structure for automatic LOD calcs
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000223	Created 
//									
//******************************************************************************
class gzLODContainer : public gzReference
{
public:
	
	gzLODContainer(gzUInt32 s_index, gzUInt32 t_index,gzUInt32 max_t_index);
	virtual ~gzLODContainer();

private:

	friend class gzParametricGeometry;

	static gzLODContainer	*getLODContainer(gzUInt32 s_index, gzUInt32 t_index);

	gzLODContainerItem		*createLODItem(gzUInt32 v0_s,gzUInt32 v0_t,gzUInt32 v1_s,gzUInt32 v1_t,gzUInt32 va_s,gzUInt32 va_t,gzLODContainerItem	*parent,gzUInt32 max_t_index);

	gzVoid					deleteLODItem(gzLODContainerItem *item);
	
	gzVoid					createSplit(gzLODContainerItem *item);
	
	gzLODContainerItem		*findSplit(gzLODContainerItem *split,gzLODContainerItem *search);
	
	gzVoid					updateMergeBoundary(gzParametricGeometry *geom);

	gzLODContainerItem						*tree_a,*tree_b,*item;
	gzLODItem								*lod_item;
	gzList<gzLODContainerItem>				boundaryTree;

	gzListIterator<gzLODContainerItem>		iterator;

	gzUInt32						s_index_size;
	gzUInt32						t_index_size;

	gzUInt32						lod_index_size;
};


//******************************************************************************
// Class	: gzParametricGeometry
//									
// Purpose  : -
//									
// Notes	: Uses a improved ROAM algorithm for high performance LODs	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990106	Created 
//									
//******************************************************************************
/*! \brief Provides a base interface for parametric geometry (x,y,z)=f(s,t)

Derive your parametric geometry class from this inteface. You will then get a 
APARS (Adaptive Parametric Surface) that dynamically can adjust the presented number
of polygons to your underlying graphics hardware capabilities

*/
class gzParametricGeometry : public gzBaseGeometry
{
public:

	GZ_GRAPH_EXPORT gzParametricGeometry(const gzString & name=GZ_EMPTY_STRING);
	GZ_GRAPH_EXPORT virtual ~gzParametricGeometry(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override=0;
	GZ_GRAPH_EXPORT virtual gzBool useDeepCopy() override;
	
	// ---------- Geometry Interface ------------------------------------


	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	
	// ---------- gzParametricGeometry Interface ------------------------

	/*! Set the start value of the surface vars (x,y,z)=f(s,t) */
	GZ_GRAPH_EXPORT gzVoid setStartParams(	gzDouble start_s ,	gzDouble start_t );

	/*! Set the stop value of the surface vars */
	GZ_GRAPH_EXPORT gzVoid setStopParams(	gzDouble stop_s ,	gzDouble stop_t );

	/*! Set the step value of the surface vars */
	GZ_GRAPH_EXPORT gzVoid setStepParams(	gzDouble step_s ,	gzDouble step_t );

	/*! Set the number of steps between start and stop values of (s,t)
	Calculates the step parameters for you. Could be convenient for you when you want
	your step index be a power of 2 (x^2 , required for AutoLOD ) */
	GZ_GRAPH_EXPORT gzVoid setStepIndex( gzUInt16 count_s_index , gzUInt16 count_t_index );

	GZ_GRAPH_EXPORT gzVoid getStepIndex( gzUInt16 &count_s_index , gzUInt16 &count_t_index );

	/*! Sets the Level Of Detail factor. Use this to adjust the detail. Start with a value of 1-4 */
	GZ_GRAPH_EXPORT gzVoid setLODFactor( gzFloat factor );

	/*! Creates a LOD structure for you. You will notice that your gemetry starts to adapt as a function 
	of complexity and distance from viewer. */
	GZ_GRAPH_EXPORT gzVoid createDynamicLOD();

	/*! Deletes the LOD structure. Normal rendering activated. No Auto LOD of your geometry. */
	GZ_GRAPH_EXPORT gzVoid deleteDynamicLOD();

	/*! Creates a patch geometry as a function of your (x,y,z)=f(s,t) function. You must call this one to see any geometry.*/
	GZ_GRAPH_EXPORT gzVoid createPatch();

	/*! Enable the colorfield as a function of (s,t). */
	GZ_GRAPH_EXPORT gzVoid useColor(gzBool on)			{ m_useColor=on;}

	/*! Enable the texture as a function of (s,t). */
	GZ_GRAPH_EXPORT gzVoid useTexture(gzBool on,gzUInt32 unit=0)		{ m_useTexture[unit]=on;}

	/*! Enable the normal as a function of (s,t). */
	GZ_GRAPH_EXPORT gzVoid useNormal(gzBool on)			{ m_useNormal=on;}

	/*! Override this method and provide your coordinate gzVec3(x,y,z) as a function of (s,t) */
	GZ_GRAPH_EXPORT virtual gzVec3 getCoordinate(gzDouble s , gzDouble t);

	/*! Override this method and provide your normal gzVec3(x,y,z) as a function of (s,t) */
	GZ_GRAPH_EXPORT virtual gzVec3 getNormal(gzDouble s , gzDouble t);

	/*! Override this method and provide your color gzVec3(r,g,b,a) as a function of (s,t) */
	GZ_GRAPH_EXPORT virtual gzVec4 getColor(gzDouble s , gzDouble t);

	/*! Override this method and provide your texture coordinate gzVec2(u,v) as a function of (s,t) */
	GZ_GRAPH_EXPORT virtual gzVec2 getTexCoordinate(gzDouble s , gzDouble t , gzUInt32 unit);

	/*! Unify your LOD structure to neighbour patches. Removes visual cracks and effects that can be seen
	if two adjacent autoLOD geometries have different distance to the viewer. 
	Returns TRUE if it updated any of the geometries */
	GZ_GRAPH_EXPORT gzBool unifyDynamicLOD(gzParametricGeometry *geometry);

	GZ_GRAPH_EXPORT gzVoid	setTextureUnits( gzUInt32 size=1 );
	GZ_GRAPH_EXPORT gzUInt32	getTextureUnits();


	GZ_GRAPH_EXPORT gzArray<gzVec3> & getCoordinateArray();


	GZ_GRAPH_EXPORT gzFloat	getPointSize();
	GZ_GRAPH_EXPORT gzVoid	setPointSize(gzFloat size);

	GZ_GRAPH_EXPORT gzFloat	getLineWidth();
	GZ_GRAPH_EXPORT gzVoid	setLineWidth(gzFloat size);

	GZ_GRAPH_EXPORT gzVoid	setViewParams(gzFloat midTVal, gzFloat smallTVal );


protected:

	// common protected methods for IRMA (Improved ROAM Algorithm (C) 1999 Anders Modén)

	friend class gzLODContainerItem;
	friend class gzLODContainer;
	friend class gzLODItem;

	GZ_GRAPH_EXPORT gzVoid	outputIndex(gzUInt32 index);
	GZ_GRAPH_EXPORT gzVoid	outputIndexSplit(gzLODContainerItem *item);
	GZ_GRAPH_EXPORT gzVoid	outputIndex(gzLODContainerItem *item);

	GZ_GRAPH_EXPORT gzVoid	isectorIndexSplit(gzLODContainerItem *item,gzIntersectorAction *isector,gzContext *context);
	GZ_GRAPH_EXPORT gzVoid	isectorIndex(gzLODContainerItem *item,gzIntersectorAction *isector,gzContext *context);

	GZ_GRAPH_EXPORT gzVoid	calculateMaxIndex();

	GZ_GRAPH_EXPORT	gzVoid virtual calculateIntersections(gzIntersectorAction *isector , gzContext *context);

	// common data

	gzDouble	m_start_s		,	m_start_t;
	gzDouble	m_stop_s		,	m_stop_t;
	gzDouble	m_step_s		,	m_step_t;
	gzUInt16	m_max_index_s	,	m_max_index_t;

	gzVec3		m_eye,m_geneye;
	
	gzArray<gzBool>				m_useTexture;
	gzBool						m_useColor:1,m_useNormal:1;
	gzFloat						m_pointSize;
	gzFloat						m_lineWidth;

	// Geometry

	gzArray<gzVec3>				m_coordinates;
	gzArray<gzVec3>				m_normals;
	gzArray<gzVec4>				m_colors;
	gzArray< gzArray<gzVec2> >	m_tex_coordinates;

	// IRMA data

	gzFloat				m_LODfactor;
	gzArray<gzLODItem>	m_lodArray;
	gzLODItem			*m_lodAddress;
	gzVec3				*m_coordAddress;
	gzUInt16			m_counter,m_lastCounter;

	gzFloat				m_midTVal,m_smallTVal;

	gzArray<gzUInt32>	m_indexArray;
	gzUInt32				*m_indexAdress;
	gzUInt32				m_indexCounter;

	gzRefPointer<gzLODContainer>	m_lodContainer;

};

//******************************************************************************
// Function	: gzUnifyDynamicLOD
//									
// Purpose  : Unifies the LOD matrix contents so no cracks appears  
//									
// Params   : gzArray2D<gzParametricGeometry *> &matrix - matrix of pointers	
//										
// Result	: -
//										
// Notes	: -
//								
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	010329	Created release 
//									
//******************************************************************************
gzVoid GZ_GRAPH_EXPORT gzUnifyDynamicLOD(gzArray2D<gzParametricGeometry *> &matrix);


#endif

