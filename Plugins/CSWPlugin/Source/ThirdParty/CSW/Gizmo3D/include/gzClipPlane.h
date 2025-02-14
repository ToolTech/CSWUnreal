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
// File			: gzClipPlane.h
// Module		: 
// Description	: Class definition of the gzClipPlane class
// Author		: Anders Modén		
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
// AMO	990831	Created file 	
//
//******************************************************************************
#ifndef __GZ_CLIPPLANE_H__
#define __GZ_CLIPPLANE_H__

/*!	\file 
	\brief Base definitions for clip planes

*/

#include "gzBasicTypes.h"

const gzUInt32 GZ_NUMBER_OF_ACTIVE_CLIP_PLANES=6;

#include "gzObject.h"
#include "gzMatrix.h"

class gzContext;	// Forward declaration

//******************************************************************************
// Class	: gzClipPlane
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990831	Created 
//									
//******************************************************************************
class gzClip : public gzObject , public gzNameInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzClip(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzClip(){};
	
	GZ_GRAPH_EXPORT gzVoid setClipPlane(gzVec3 norm , gzVec3 base);


	GZ_GRAPH_EXPORT gzVoid	virtual activate(gzContext *context , gzUInt32 clipIndex , gzUInt32 transformIndex);
	GZ_GRAPH_EXPORT static gzVoid deactivate(gzContext *context ,gzUInt32 clipIndex );

	GZ_GRAPH_EXPORT gzVoid	flipPlane();

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

private:

	gzDouble a,b,c,d;	// Plane Equation

};

GZ_DECLARE_REFPTR(gzClip);

//******************************************************************************
// Class	: gzClipState
//									
// Purpose  : The actual state of the current clip planes
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991027	Created 
//									
//******************************************************************************
class gzClipState 
{
public:

	GZ_GRAPH_EXPORT gzClipState();

	GZ_GRAPH_EXPORT virtual ~gzClipState();

	GZ_GRAPH_EXPORT gzVoid	add(gzClipState &clipState);

	GZ_GRAPH_EXPORT gzVoid addClipPlane( gzClip *plane);
	GZ_GRAPH_EXPORT gzVoid removeClipPlane( gzClip *plane);

	GZ_GRAPH_EXPORT gzUInt32	getNumberOfClipPlanes();
	GZ_GRAPH_EXPORT gzClip *getClipPlane(gzUInt32 clipIndex);


	GZ_GRAPH_EXPORT gzVoid setTransformIndex(gzUInt32 index);

	GZ_GRAPH_EXPORT gzVoid activate(gzContext *context);

	GZ_GRAPH_EXPORT gzVoid flipPlanes();

	GZ_GRAPH_EXPORT static gzVoid transferActiveClipStates(gzContext *from , gzContext *to);

private:

	gzRefPointer<gzClip>		m_clipPlanes[GZ_NUMBER_OF_ACTIVE_CLIP_PLANES];
	gzUInt32						m_transformIndex[GZ_NUMBER_OF_ACTIVE_CLIP_PLANES];
	gzUByte						m_count;

};

#endif
