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
// File			: gzBezier.h
// Module		: 
// Description	: Class definition of Bezier geometry classes
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
// AMO	000807	Created file 	
//
//******************************************************************************
#ifndef __GZ_BEZIER_H__
#define __GZ_BEZIER_H__

/*!	\file 
	\brief Base definitions for Bezier patches

*/

#include "gzParametric.h"

//******************************************************************************
// Class	: gzBezier
//									
// Purpose  : -
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000807	Created 
//									
//******************************************************************************
/*! \brief Provides a base interface for Bezier geometry 

  More info of bezier

*/

class gzBezier : public gzParametricGeometry
{
public:

	GZ_GRAPH_EXPORT gzBezier(const gzString & name=GZ_EMPTY_STRING);
	GZ_GRAPH_EXPORT virtual ~gzBezier(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Bezier interface ---------------------------------------
	
	GZ_GRAPH_EXPORT gzVoid	setControlPointSize( gzUInt16 sizeX , gzUInt16 sizeY );

	GZ_GRAPH_EXPORT gzVoid	setControlPoint( gzUInt16 pointX , gzUInt16 pointY , const gzVec3 &data );

	GZ_GRAPH_EXPORT gzVoid	setControlPointData( const gzArray<gzVec3> &data);

	GZ_GRAPH_EXPORT gzVoid	setControlPointData( const gzArray2D<gzVec3> &data);

	// ---------- Parametric ---------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVec3 getCoordinate(gzDouble s , gzDouble t) override;



private:

	gzArray< gzVec3 >	m_controlPoints;

	gzArray< gzVec3 >	m_bufferPoints;

	gzUInt16			m_sizeX,m_sizeY;
};


#endif

