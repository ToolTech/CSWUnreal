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
// File			: gzIntersector.h
// Module		: 
// Description	: Class definition of the gzIntersector class
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
// AMO	000828	Created file 	
// AMO	111216	Made context available in gzIntersector				             (2.5.36)
// AMO	111216	Added currentIntersectorsPerFrame to allow count of intersectors (2.5.36
//
//******************************************************************************
#ifndef __GZ_INTERSECTOR_H__
#define __GZ_INTERSECTOR_H__

/*!	\file 
	\brief Base definitions for collision detection, line of sight etc.

*/

#include "gzScene.h"
#include "gzContext.h"

enum gzIntersectQuery
{
	GZ_INTERSECTOR_NULL						=	0,
	GZ_INTERSECTOR_NEAREST_POINT			= (1 << 0),		// Return only closest HIT
	GZ_INTERSECTOR_NORMAL					= (1 << 1),		// Add normal of HIT triangle
	GZ_INTERSECTOR_NODE						= (1 << 2),		// Add node that was hit
	GZ_INTERSECTOR_HISTORY					= (1 << 3),		// Add traversal history
	GZ_INTERSECTOR_ABC_TRI					= (1 << 4),		// Returns triangle points
	GZ_INTERSECTOR_ALL_HITS					= (1 << 5),		// Return all HITS
	GZ_INTERSECTOR_ONE_HIT					= (1 << 6),		// Return first HIT
	GZ_INTERSECTOR_ACCELLERATE				= (1 << 7),		// Build and use nonatree
	GZ_INTERSECTOR_WAIT_FOR_DYNAMIC_DATA	= (1 << 8),		// Wait for dynamic loaded data
	GZ_INTERSECTOR_UPDATE_DYNAMIC_DATA		= (1 << 9),		// Update dynamic loaded data
	GZ_INTERSECTOR_TRANSFORM				= (1 << 10),	// Add transform to result
	GZ_INTERSECTOR_UV						= (1 << 11),	// Add UV Coordinate
};

GZ_USE_BIT_LOGIC(gzIntersectQuery);


class gzIntersectorResult
{
public:

	gzVec3							coordinate;				// The coordinate that we hit

	gzVec3							a,b,c;					// Triangle hit coordinates : GZ_INTERSECTOR_ABC_TRI

	gzVec3							normal;					// Calculated normal at hit	: GZ_INTERSECTOR_NORMAL

	gzVec2							uv;						// calculated uv coordinate	: GZ_INTERSECTOR_UV

	gzNode *						node;					// node instance that was hit. Not ref!! : GZ_INTERSECTOR_NODE

	gzUInt64						pathID;					// Unique traversal path ID

	gzList<gzNode>					history;				// History stack of hit nodes : GZ_INTERSECTOR_HISTORY

	gzMatrix4						transform;				// Current transform at hit point : GZ_INTERSECTOR_TRANSFORM

	gzUInt32						resultmask;				// Caps of hit result
};

class gzIntersector;

class gzIntersectorAction : public gzTraverseAction
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzIntersectorAction(gzIntersector *intersector=nullptr);

	GZ_GRAPH_EXPORT virtual ~gzIntersectorAction(){};

	GZ_GRAPH_EXPORT virtual gzBool isTransformTraverser()	const	override { return TRUE; }
	GZ_GRAPH_EXPORT virtual gzBool isRenderTraverser()		const	override { return FALSE; }
	GZ_GRAPH_EXPORT virtual gzBool isIntersectorTraverser()	const	override { return TRUE; }

	GZ_GRAPH_EXPORT virtual gzBool isIntersecting(gzNode* node) const override;
	GZ_GRAPH_EXPORT virtual gzBool isIntersecting(const gzIntersectMaskValue& value) const override; 


	GZ_GRAPH_EXPORT gzVoid action(gzNode *node , gzContext *context);

	GZ_GRAPH_EXPORT gzVoid setIntersector(gzIntersector *intersector);

	GZ_GRAPH_EXPORT gzIntersector *getIntersector()					{ return m_intersector; }

	GZ_GRAPH_EXPORT const gzVec3 & getStartPos()			const	{ return m_transformedStartPos; } 
	GZ_GRAPH_EXPORT const gzVec3 & getDirection()			const	{ return m_transformedDirection; }

	GZ_GRAPH_EXPORT const gzList<gzNode> & getHistory()		const	{ return m_history; };

protected:

	GZ_GRAPH_EXPORT virtual gzBool checkBoundary(gzContext *context, gzNode *node) override;
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzNode *node , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzNode *node , gzContext *context) override;

private:

	gzIntersector *		m_intersector;
						
	gzUInt32			m_currentTransformIndex;
						
	gzVec3				m_transformedStartPos;
	gzVec3				m_transformedDirection;

	gzQueue<gzVec3>		m_transformedStartPosStorage;				
	gzQueue<gzVec3>		m_transformedDirectionStorage;


	gzList<gzNode>		m_history;
};

GZ_DECLARE_REFPTR(gzIntersectorAction);

//******************************************************************************
// Class	: gzIntersector
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000828	Created 
//									
//******************************************************************************
class gzIntersector : public gzObject , public gzNameInterface , public gzIntersectMask
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzIntersector(const gzString & name=GZ_EMPTY_STRING);
	GZ_GRAPH_EXPORT gzIntersector(const gzIntersector &copy);
	GZ_GRAPH_EXPORT virtual ~gzIntersector();

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- intersector interface ---------------------------------

	GZ_GRAPH_EXPORT gzVoid setBaseTransform(const gzMatrix4 &baseTransform);
	GZ_GRAPH_EXPORT gzVoid setProjectionTransform(const gzMatrix4 &projectionTransform);

	GZ_GRAPH_EXPORT gzVoid setStartPosition(const gzVec3 &position);									// Local based
	GZ_GRAPH_EXPORT gzVoid setStartPosition(const gzVec3D &position, const gzVec3D &roi_position);		// Roi based
	GZ_GRAPH_EXPORT gzVoid setDirection(const gzVec3 &direction);
	GZ_GRAPH_EXPORT gzVoid setCamera(const gzCamera * camera);
	
	GZ_GRAPH_EXPORT gzBool intersect(gzNode *node,gzIntersectQuery queryType=GZ_INTERSECTOR_NEAREST_POINT,gzFloat lodFactor=1.0,gzBool useRoiPosition=FALSE,const gzDoubleXYZ &roi_position=gzDoubleXYZ(0,0,0) );

	GZ_GRAPH_EXPORT gzVoid clearCurrentIntersectorCount();

	GZ_GRAPH_EXPORT	virtual gzBool terminate();


	// ---------- intersector data --------------------------------------

	GZ_PROPERTY_GET_EXPORT( gzBool			,	HasBaseTransform		, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_GET_EXPORT( gzBool			,	HasProjectionTransform	, GZ_GRAPH_EXPORT);

	GZ_PROPERTY_GET_EXPORT( gzMatrix4		,	ProjectionTransform		, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_GET_EXPORT( gzMatrix4		,	InvProjectionTransform	, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_GET_EXPORT( gzMatrix4		,	BaseTransform			, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_GET_EXPORT( gzMatrix4		,	InvBaseTransform		, GZ_GRAPH_EXPORT);

	GZ_PROPERTY_GET_EXPORT( gzCameraPtr		,	Camera					, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT	  ( gzBool			,	UseCameraFrustrum		, GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT	  ( gzBool			,	UpdateDynamicLoading	, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT	  ( gzBool			,	WaitForDynamicData		, GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT	  ( gzContextPtr	,	Context					, GZ_GRAPH_EXPORT);

	// ---------- query results -----------------------------------------

	GZ_GRAPH_EXPORT gzDynamicArray<gzIntersectorResult> getResult();

	GZ_GRAPH_EXPORT gzIntersectQuery getQueryType();

	GZ_GRAPH_EXPORT gzVoid addResult(const gzIntersectorResult &data);

	GZ_GRAPH_EXPORT static gzVoid clearCurrentIntersector();

private:

	friend class gzIntersectorAction;

	gzVec3								m_startPos;
	gzVec3								m_direction;

	gzVec3								m_unTransformedStartPos;
	gzVec3								m_unTransformedDirection;

	gzBool								m_hasStartPosition;
	gzBool								m_hasDirection;

	gzIntersectQuery					m_queryType;

	gzDynamicArray<gzIntersectorResult>	m_results;
};

GZ_DECLARE_REFPTR(gzIntersector);


#endif
