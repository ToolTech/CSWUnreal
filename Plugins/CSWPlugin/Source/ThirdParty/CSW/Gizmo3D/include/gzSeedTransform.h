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
// File			: gzSeedTransform.h
// Module		: 
// Description	: Class definition of the gzSeedTransform class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.283
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
#ifndef __GZ_SEED_TRANSFORM_H__
#define __GZ_SEED_TRANSFORM_H__

/*!	\file 
	\brief Base definitions for seed driven transforms

*/

#include "gzTransform.h"

template <class T> class gzSeedData 
{
public:

	T	min;

	T	max;

	gzDouble	 weightFactor;
};

class gzSeedRefData : public gzReference
{
public:
	gzMatrix4	transform;
	gzFloat		maxScale;
};
	
//******************************************************************************
// Class	: gzSeedTransform
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030314	Created 
//									
//******************************************************************************
class gzSeedTransform : public gzTransform
{
public:

	GZ_GRAPH_EXPORT gzSeedTransform(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzSeedTransform();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Seed transform interface ------------------------------

	GZ_GRAPH_EXPORT	gzVoid setHPRSeedValue(gzBool on , gzVec3 min=gzVec3(0,0,0),gzVec3 max=gzVec3(0,0,0),gzDouble weight=1.0);

	GZ_GRAPH_EXPORT	gzVoid setRecursiveDepthScaleFactor(const gzFloat &factor);

	// ---------- Striving values ---------------------------------------

	GZ_GRAPH_EXPORT gzVoid setStriveDirection(const gzVec3 &direction);

	GZ_GRAPH_EXPORT gzVoid setStriveFactors(gzFloat constantFactor=0.2f , gzFloat recursiveDepthFactor=0.0f , gzFloat maxWeightFactor=1.0f);

	GZ_GRAPH_EXPORT gzVoid static setGlobalStriveStrength(const gzFloat &striveStrength);


	// ---------- traversing --------------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	
private:

	gzLateBindData<gzSeedData<gzVec3> >	m_hprSeedValue;

	gzVec3								m_striveDirection;

	gzFloat								m_constantFactor;

	gzFloat								m_recursiveDepthFactor;

	gzFloat								m_maxWeightFactor;

	gzFloat								m_recursiveDepthScaleFactor;

	static gzFloat						s_globalStriveStrength;								
};

#endif
