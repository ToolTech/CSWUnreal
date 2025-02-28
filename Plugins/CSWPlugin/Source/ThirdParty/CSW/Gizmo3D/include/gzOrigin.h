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
// File			: gzOrigin.h
// Module		: 
// Description	: Class definition of the gzOrigin class
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
#ifndef __GZ_ORIGIN_H__
#define __GZ_ORIGIN_H__

/*!	\file 
	\brief Base definitions for local origin data

*/

#include "gzTransform.h"

//******************************************************************************
// Class	: gzOrigin
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030310	Created 
//									
//******************************************************************************
class gzOrigin : public gzTransform
{
public:

	//! Default constructor
	/*!
	A gzOrigin is a transform node. Every child of the origin is placed in a local coordinate system
	around the origin. There can be several origins in the same scene. 
	An originID needs to be specified for the origin. Each origin has an ID which makes it easy
	to search for a specific origin. It is possible to change the ID with setOriginID.

	Use this transform to crete a local coordinate system somewhere in the scene graph.
	You can then query the world coordinate for the local coordinate origin.

	If is possible but not necessary to set a name for the origin.
	*/
	GZ_GRAPH_EXPORT gzOrigin(gzUInt32 originID , const gzString & name=GZ_EMPTY_STRING);

	//!Destructor
	GZ_GRAPH_EXPORT virtual ~gzOrigin();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	GZ_GRAPH_EXPORT virtual gzVoid debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ---------- origin interface --------------------------------------

	//!Set an ID for the origin.
	GZ_GRAPH_EXPORT	gzVoid setOriginID(gzUInt32 originID);

	//!Returns the ID for the origin.
	GZ_GRAPH_EXPORT	gzUInt32 getOriginID();
	
	//!Return the position of the origin given i world coordinates.
	/*!
	Note that if the gzOrigin transform is equal unit matrix, then the Origin position will be the 
	same as the child position.
	*/
	GZ_GRAPH_EXPORT	gzVec3		getGlobalOriginPosition();
	
	//!Return the position of the origin given i screen coordinates.
	GZ_GRAPH_EXPORT	gzVec3		getGlobalOriginScreenPosition();

	/*!
	Returns the global origin position for the children. I.e. the sum of the global origin 
	position + the local transform in the gzOrigin class
	*/
	GZ_GRAPH_EXPORT	gzVec3		getGlobalChildPosition();
	
	//!Return the position of the origin child given i screen coordinates.
	GZ_GRAPH_EXPORT	gzVec3		getGlobalChildScreenPosition();

	//! Return the last rendertime from gzContext that the node was traversed and
	GZ_GRAPH_EXPORT	gzDouble	getLastActiveRenderTime();


	//!Returns the origin with id originID.
	GZ_GRAPH_EXPORT static gzOrigin *findOrigin( gzUInt32 originID );

	/*!
	Add origin axis to all gzOrigin instances in the scene graph. 
	The size of the geometry axis is 10 and the step is 1.
	*/
	GZ_GRAPH_EXPORT static gzVoid addOriginAxis(const gzVec4 &color = gzVec4(0.0, 0.0, 0.0, 1.0));

	//!	The local coordinate system is scaled with the factor scale.
	/*!
	The scale factor is different for each context.
	*/
	GZ_GRAPH_EXPORT static gzVoid setOriginScale(gzContext *context,gzFloat scale);

	//!Makes it possible to scale an origin. 
	/*!
	Used to override the local coordinate system scale. Even if parent tree has a 
	non unit scale, the origin will be scaled by unit. Default is FALSE.
	*/
	GZ_GRAPH_EXPORT gzVoid useOriginScale(gzBool useScale);

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	
private:

	gzUInt32						m_originID;

	gzVec3							m_globalOriginPosition;

	gzVec3							m_globalChildPosition;

	gzDouble						m_lastActiveRenderTime;

	gzVec3							m_globalOriginScreenPosition;

	gzVec3							m_globalChildScreenPosition;

	gzBool							m_useScale:1;

	static gzMemCheck<gzDict<gzUInt32CompareInterface,gzOrigin> > s_originDictionary;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzOrigin);

#endif
