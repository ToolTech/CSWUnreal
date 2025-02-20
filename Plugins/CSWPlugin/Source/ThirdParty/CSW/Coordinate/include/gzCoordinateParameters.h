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
// File			: gzCoordinateParameters.h
// Module		: gzCoordinate
// Description	: Parameters for conversions
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.222
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
// AMO	180215	Created file								(2.9.1)	
//
//******************************************************************************
#ifndef __GZ_COORDINATE_PARAMETERS_H__
#define __GZ_COORDINATE_PARAMETERS_H__

/*!	\file 
	\brief Parameters for conversion between different geoides etc.

*/

#include "gzCoordinateTypes.h"

#ifdef GZ_INCLUDE_GEODETIC_TRANS		// Set to include transform data

gzGeodeticTransform GZ_GEODETIC_TRANS[] = {	{ GZ_ELLIPSOID_WGS84,		0,0,0,0,0,0,0, GZ_HEIGHT_MODEL_ELLIPSOID },																						// WGS84
											{ GZ_ELLIPSOID_GRS80,		0,0,0,0,0,0,0, GZ_HEIGHT_MODEL_ELLIPSOID },																						// GRS80
											{ GZ_ELLIPSOID_BESSEL_1841,	-414.0978567149, -41.3381489658, -603.0627177516 ,-0.8550434314 ,+2.1413465185 ,-7.0227209516 ,0,GZ_HEIGHT_MODEL_ELLIPSOID },	// BESSEL
											{ GZ_ELLIPSOID_CLARKE_1866, 8, -160, -176, 0, 0, 0, 0,GZ_HEIGHT_MODEL_ELLIPSOID},																			// CLARKE_1866
											{ GZ_ELLIPSOID_AIRY_1830,	-446.448, 125.157, -542.06, -0.1502, -0.247, -0.8421 ,20.4894 ,GZ_HEIGHT_MODEL_ELLIPSOID},										// OSGB36
											{ GZ_ELLIPSOID_WGS84,		0,0,0,0,0,0,0, GZ_HEIGHT_MODEL_EGM2008 },																						// WGS84_EGM2008
											{ GZ_ELLIPSOID_BESSEL_1841,	-414.0978567149, -41.3381489658, -603.0627177516 ,-0.8550434314 ,+2.1413465185 ,-7.0227209516 ,0,GZ_HEIGHT_MODEL_RH70 },		// RR92
											{ GZ_ELLIPSOID_BESSEL_1841,	-414.0978567149, -41.3381489658, -603.0627177516 ,-0.8550434314 ,+2.1413465185 ,-7.0227209516 ,0,GZ_HEIGHT_MODEL_RH70 },		// RR92
											{ GZ_ELLIPSOID_USER_DEFINED,0,0,0,0,0,0,0, GZ_HEIGHT_MODEL_ELLIPSOID },																						// User defined

};

gzEllipsoidParameters GZ_ELLIPSOID_PARAMS[] = { { 6378137.0, 298.257223563 },					// WGS84
												{ 6378137.0, 298.257222101 },					// GRS80
												{ 6377397.155, 299.1528128 }, 					// BESSEL 1841
												{ 6378206.4, 294.978698213898 }, 				// CLARKE 1866
												{ 6377563.396,299.3249646  },					// AIRY 1830		
												{ 6378135,298.26},								// WGS72
};

// Kind of projection and what index parameters have in parameter list per type
gzProjectionParameters GZ_PROJECTIONS[] = {	{GZ_PROJ_TYPE_GAUSS_KREUGER ,0},	// GZ_PROJ_RT90	 RT90 2.5 GON V
											{GZ_PROJ_TYPE_GAUSS_KREUGER ,1},	// GZ_PROJ_SWEREF99
											{GZ_PROJ_TYPE_GAUSS_KREUGER ,2},	// GZ_PROJ_UTM
											{GZ_PROJ_TYPE_GAUSS_KREUGER ,3},	// GZ_PROJ_OSGB36
											{GZ_PROJ_TYPE_GAUSS_KREUGER ,4},	// GZ_PROJ_RT90_0_GON,
											{GZ_PROJ_TYPE_GAUSS_KREUGER ,5},	// GZ_PROJ_RT90_5_GON_V,
											{GZ_PROJ_TYPE_GAUSS_KREUGER ,6},	// GZ_PROJ_RT90_7_5_GON_V,
											{GZ_PROJ_TYPE_GAUSS_KREUGER ,7},	// GZ_PROJ_RT90_2_5_GON_O,
											{GZ_PROJ_TYPE_GAUSS_KREUGER ,8},	// GZ_PROJ_RT90_5_GON_O,
											};

gzGaussProjection GZ_GAUSS_FLAT_PROJ[] = {	{ GZ_GEODETIC_DATUM_BESSEL_1841_ELLIPSOID,GZ_DEG_MIN_SEC_2_RAD(15,48,29.8),0,1.0,0,1500000} ,										// RT90 2.5 GON V
											{ GZ_GEODETIC_DATUM_GRS80_ELLIPSOID,GZ_DEG_MIN_SEC_2_RAD(15,00,00),0,0.9996,0,500000 } ,											// SWEREF99
											{ GZ_GEODETIC_DATUM_WGS84_ELLIPSOID,0,0,0.9996,0,500000 },																			// UTM Template
											{ GZ_GEODETIC_DATUM_AIRY_1830_ELLIPSOID,GZ_DEG_MIN_SEC_2_RAD(-2,0,0),GZ_DEG_MIN_SEC_2_RAD(49,0,0),0.9996012717,-100000,400000} ,	// OSGB36 (BNG)
											{ GZ_GEODETIC_DATUM_BESSEL_1841_ELLIPSOID,GZ_DEG_MIN_SEC_2_RAD(18,03,29.8),0,1.0,0,1500000} ,										// RT90 0 GON
											{ GZ_GEODETIC_DATUM_BESSEL_1841_ELLIPSOID,GZ_DEG_MIN_SEC_2_RAD(13,33,29.8),0,1.0,0,1500000} ,										// RT90 5 GON V 
											{ GZ_GEODETIC_DATUM_BESSEL_1841_ELLIPSOID,GZ_DEG_MIN_SEC_2_RAD(11,18,29.8),0,1.0,0,1500000} ,										// RT90 7.5 GON V
											{ GZ_GEODETIC_DATUM_BESSEL_1841_ELLIPSOID,GZ_DEG_MIN_SEC_2_RAD(20,18,29.8),0,1.0,0,1500000} ,										// RT90 2.5 GON O
											{ GZ_GEODETIC_DATUM_BESSEL_1841_ELLIPSOID,GZ_DEG_MIN_SEC_2_RAD(22,33,29.8),0,1.0,0,1500000} ,										// RT90 5 GON O
											};

#endif





#endif // __GZ_COORDINATE_PARAMETERS_H__

