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
// File			: gzCuller.h
// Module		: 
// Description	: Class definition of the gzCuller utility class
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
// AMO	991222	Created file 	
//
//******************************************************************************
#ifndef __GZ_CULLER_H__
#define __GZ_CULLER_H__

/*!	\file 
	\brief Base definitions for culler utility

*/

#include "gzMatrix.h"
#include "gzGroup.h"



//******************************************************************************
// Class	: gzCuller
//									
// Purpose  : Base Interface for culling and occlusion testing in scene graph
//									
// Notes	: Only used internally	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991222	Created 
//									
//******************************************************************************
class gzCuller : public gzReference
{
public:

	GZ_GRAPH_EXPORT gzCuller(){};

	GZ_GRAPH_EXPORT virtual ~gzCuller(){};

	GZ_GRAPH_EXPORT virtual gzBool isVisible( const gzVec3 &pos , const gzFloat &rad , gzNode *node)=0;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const=0;


};

//******************************************************************************
// Class	: gzConeCuller
//									
// Purpose  : Base Interface for culling and occlusion testing in scene graph
//									
// Notes	: Only used internally	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991222	Created 
//									
//******************************************************************************
class gzConeCuller : public gzCuller
{
public:

	GZ_GRAPH_EXPORT gzConeCuller(gzNode *node , gzMatrix4 & transform , gzFloat & maxscale);

	GZ_GRAPH_EXPORT virtual ~gzConeCuller(){};

	GZ_GRAPH_EXPORT virtual gzBool isVisible( const gzVec3 &pos , const gzFloat &rad , gzNode *node) override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

private:

	gzVec3	m_pos;
	gzFloat	m_rad;
	gzFloat	m_length;
	gzFloat	m_alpha;
};


//******************************************************************************
// Class	: gzViewPlaneCuller
//									
// Purpose  : Culls children when loceated on a certian side of a view plane
//									
// Notes	: 	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030718	Created 
//									
//******************************************************************************
class gzViewPlaneCuller : public gzGroup
{
public:

	GZ_GRAPH_EXPORT gzViewPlaneCuller(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzViewPlaneCuller(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzBool	checkTraversePerChild() const override { return TRUE; }

	GZ_GRAPH_EXPORT virtual gzBool	isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index , gzContext *context ) override;

	// ---------- gzConeCuller ----------------------------------

	GZ_GRAPH_EXPORT gzVoid setViewPlane(const gzVec3 &position, const gzVec3 & cullDirection);

private:

	gzVec3	m_cullPosition;

	gzVec3	m_cullDirection;

};



#endif
