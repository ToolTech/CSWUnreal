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
// File			: gzBillboard.h
// Module		: 
// Description	: Class definition of the gzBillboard class
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
// AMO	990511	Created file 	
//
//******************************************************************************
#ifndef __GZ_BILLBOARD_H__
#define __GZ_BILLBOARD_H__

/*!	\file 
	\brief Base definitions for billboard nodes

*/

#include "gzTransform.h"

typedef enum {	GZ_BILLBOARD_AXIS ,					//!>	Rotates the billboard around an axis.
				GZ_BILLBOARD_POINT_AXIS ,			//!>	Rotates the billboard around a point.
				GZ_BILLBOARD_POINT_CAMERA_UP ,		//!>	Rotates the billboard around a point with billboard facing camera up.
				GZ_BILLBOARD_POINT_CAMERA_ORTHO		//!>	Rotates the billboard aroung a point with orthogonal camera projection.
} gzBillboardType;

//******************************************************************************
// Class	: gzBillboard
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990511	Created 
//									
//******************************************************************************
class gzBillboard : public gzTransform
{
public:
	//!Constructor
	/*!
	A billboard is a group transform that calculates the transform as the scene graph
	is rendered. If you with to make a tree that always is facing the viewer, 
	the billbord class can rotate this tree for you. 

	It is possible to set a name for the billboard.
	*/
	GZ_GRAPH_EXPORT gzBillboard(const gzString &name=GZ_EMPTY_STRING);

	//!Destructor
	GZ_GRAPH_EXPORT virtual ~gzBillboard(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Common graph functions --------------------------------

	//!Updates the bounding sphere for the billboard.
	/*!
	The bounding sphere surrounds the billboard and all its children.
	*/
	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- billboard commands -------------------------------------

	//!Sets the axis the billboard rotates around.
	GZ_GRAPH_EXPORT gzVoid setAxis(gzVec3 axis);

	//!Sets the billboard type.
	/*!
	The billboard can rotate around an axis or around a point. 
	*/
	GZ_GRAPH_EXPORT gzVoid setType(gzBillboardType type);

	//Aligns billboard orthogonal to the viewer center z axis.
	/*!
	If on=TRUE the children to the billboard are aligned orthogonal to the z axis.
	Then they will not rotate around you when you get near them.

	If on=FALSE you can move very close to billboards and they will stay aligned 
	towards you. This is useful for trees in a forest when you move through the forest.
	*/
	GZ_GRAPH_EXPORT gzVoid usePlanarBillboard(gzBool on);

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

protected:

	GZ_GRAPH_EXPORT gzVoid calculateBillboardTransform(gzContext *context,gzBool force=FALSE);

private:

	gzBillboardType		m_type:3;
	gzBool				m_usePlanarBillboard:1;

	gzVec3				m_upAxis;
	gzVec3				m_lastCalc_e;

};

GZ_DECLARE_REFPTR(gzBillboard);

#endif
