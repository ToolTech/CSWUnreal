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
// File			: gzCoordinateTypes.h
// Module		: gzCoordinate
// Description	: Class definition of coordinate transforms types
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.200
//		
// Copyright © 2010- SAAB AB, Sweden
//			
// NOTE:	GizmoBase is a platform abstraction utility layer for C++. It contains 
//			design patterns and C++ solutions for the advanced programmer.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	180215	Created file								(2.9.1)
// AMO	241009	Added normalize() to LatPos					(2.12.191)
//
//******************************************************************************
#ifndef __GZ_COORDINATE_TYPES_H__
#define __GZ_COORDINATE_TYPES_H__

/*!	\file 
	\brief Coordinate transformations types

	This file provides utilities to translate between various simple coordinate systems

*/

#include "gzCoordinateBase.h"

// --------------------- Macros ---------------------------

#define GZ_DEG_MIN_SEC_2_RAD(deg,min,sec) (gzSign(deg)*(gzAbs(deg)+min/60.0+sec/3600.0)*GZ_DEG2RAD)
#define GZ_DEG_MIN_2_RAD(deg,min) (gzSign(deg)*(gzAbs(deg)+min/60.0)*GZ_DEG2RAD)

//********************** TYPES & STRUCTS ***************************************

enum gzCoordPresFlags
{
	GZ_COORD_PRES_NO_FLAG	= 0,
	GZ_COORD_PRES_DEGREES	= 1 << 0,
	GZ_COORD_PRES_MINUTES	= 1 << 1,
	GZ_COORD_PRES_SECONDS	= 1 << 2,

	GZ_COORD_PRES_N_E		= 1 << 3,
	GZ_COORD_PRES_ALTITUDE	= 1 << 4,
	GZ_COORD_PRES_SPACE_SEP	= 1 << 5,
	GZ_COORD_PRES_PREFIX	= 1 << 6,

	GZ_COORD_PRES_DEFAULT = GZ_COORD_PRES_DEGREES | GZ_COORD_PRES_MINUTES | GZ_COORD_PRES_SECONDS | GZ_COORD_PRES_N_E | GZ_COORD_PRES_PREFIX ,
};

GZ_USE_BIT_LOGIC(gzCoordPresFlags);

class GZ_COORDINATE_EXPORT gzLatPos
{
public:

	gzDouble	latitude;
	gzDouble	longitude;
	gzDouble	altitude;

	gzString	asString(gzCoordPresFlags flags = GZ_COORD_PRES_DEFAULT);

	gzVoid		RAD2DEG();
	gzVoid		DEG2RAD();
	gzVoid		normalize();

	static gzLatPos fromString(const gzString& str,gzBool *ok=NULL);
};

class GZ_COORDINATE_EXPORT gzCartPos
{
public:

	gzDouble	x;
	gzDouble	y;
	gzDouble	z;


	// Some simple utilities for cartesian coordinates

	operator gzVec3D() { return gzVec3D(x, y, z); }

	gzCartPos operator+(const gzVec3& offset) { return gzCartPos{ x + offset.x,y + offset.y,z + offset.z }; }
	gzCartPos operator-(const gzVec3& offset) { return gzCartPos{ x - offset.x,y - offset.y,z - offset.z }; }

	gzCartPos operator+(const gzVec3D& offset) { return gzCartPos{ x + offset.x,y + offset.y,z + offset.z }; }
	gzCartPos operator-(const gzVec3D& offset) { return gzCartPos{ x - offset.x,y - offset.y,z - offset.z }; }
	
	// Standard output

	gzString	asString(gzCoordPresFlags flags= GZ_COORD_PRES_DEFAULT);

	static gzCartPos fromString(const gzString& str, gzBool* ok = NULL);

};

class GZ_COORDINATE_EXPORT gzProjPos
{
public:

	gzDouble	x;		// North
	gzDouble	y;		// East
	gzDouble	h;		// Height

	gzString	asString(gzCoordPresFlags flags = GZ_COORD_PRES_DEFAULT);

	static gzProjPos fromString(const gzString& str, gzBool* ok = NULL);
};

class GZ_COORDINATE_EXPORT gzUTMPos
{
public:

	gzInt32		zone;
	gzBool		north;

	gzDouble	northing;	// North
	gzDouble	easting;	// East
	gzDouble	h;			// Height
	
	gzString	asString(gzCoordPresFlags flags = GZ_COORD_PRES_DEFAULT);

	static gzUTMPos fromString(const gzString& str, gzBool* ok = NULL);
};

// ------------------ Ellipsoids -------------------------------------

enum gzEllipsoid
{
	GZ_ELLIPSOID_WGS84,							// WGS84		EPSG:4326
	GZ_ELLIPSOID_GRS80,							// GRS80
	GZ_ELLIPSOID_BESSEL_1841,					// BESSEL 1841	EPSG:7004
	GZ_ELLIPSOID_CLARKE_1866,					// Clarke 1866	EPSG:7008
	GZ_ELLIPSOID_AIRY_1830,						// AIRY 1830	EPSG:7001
	GZ_ELLIPSOID_WGS72,							// WGS72		EPSG:4985

	GZ_ELLIPSOID_USER_DEFINED,

	GZ_ELLIPSOID_NOT_DEFINED,
};

enum gzGeodeticDatum							// Correpond to GZ_GEODETIC_TRANS
{
	GZ_GEODETIC_DATUM_WGS84_ELLIPSOID,			// Must be one datum for each ref ellipsoid
	GZ_GEODETIC_DATUM_GRS80_ELLIPSOID,
	GZ_GEODETIC_DATUM_BESSEL_1841_ELLIPSOID,
	GZ_GEODETIC_DATUM_CLARKE_1866_ELLIPSOID,
	GZ_GEODETIC_DATUM_AIRY_1830_ELLIPSOID,		// OSGB36
		

	GZ_GEODETIC_DATUM_WGS84_EGM2008,			// Additional datums for each alt model
	GZ_GEODETIC_DATUM_BESSEL_RH70,

	GZ_GEODETIC_DATUM_USER_DEFINED,

	GZ_GEODETIC_DATUM_NOT_DEFINED,
};

enum gzHeightModel
{
	GZ_HEIGHT_MODEL_ELLIPSOID,
	GZ_HEIGHT_MODEL_EGM2008,
	GZ_HEIGHT_MODEL_EGM96,
	GZ_HEIGHT_MODEL_RH2000,
	GZ_HEIGHT_MODEL_RH70,
	GZ_HEIGHT_MODEL_NOT_DEFINED,
};

// ------------- Transformation with Helmerts 7 parameter formula between ellipsoids (FROM WGS84 to XXX) --------------------

struct gzGeodeticTransform
{
	gzEllipsoid		ellipsoid;									// ref ellipsoid

	gzDouble		trans_x,	trans_y,	trans_z;			// m
	gzDouble		rot_x,		rot_y,		rot_z;				// bågsekunder
	gzDouble		scale_d_ppm;								// mm/km

	gzHeightModel	height_model;								// ref height model
};

// --------- Ellipsoid Parameters

struct gzEllipsoidParameters
{
	gzDouble	semi_axis;						// m
	gzDouble	inverse_flattening;				// 1/f
};

// --------- Transformation till Gauss konforma projektion ---------------------

enum gzFlatProjection		// Various types of projections
{
	GZ_PROJ_RT90,			// RT90 2.5 GON V	(Gauss Kreuger (TM))
	GZ_PROJ_SWEREF99,		// (Gauss Kreuger (TM))
	GZ_PROJ_UTM,			// (Gauss Kreuger (TM))
	GZ_PROJ_OSGB36,			// (Gauss Kreuger (TM))
	GZ_PROJ_RT90_0_GON,		// (Gauss Kreuger (TM))
	GZ_PROJ_RT90_5_GON_V,	// (Gauss Kreuger (TM))
	GZ_PROJ_RT90_7_5_GON_V,	// (Gauss Kreuger (TM))
	GZ_PROJ_RT90_2_5_GON_O,	// (Gauss Kreuger (TM))
	GZ_PROJ_RT90_5_GON_O,	// (Gauss Kreuger (TM))

	GZ_PROJ_USER_DEFINED,	// (Gauss Kreuger (TM)) with own parameters
	GZ_PROJ_NOT_DEFINED,
};

enum gzProjectionType				// Various types of flat projections
{
	GZ_PROJ_TYPE_GAUSS_KREUGER,
	GZ_PROJ_TYPE_LAMBERT,	
};

struct gzProjectionParameters
{
	gzProjectionType	type;
	gzUInt32			param_index;
};

struct gzGaussProjection
{
	gzGeodeticDatum		datum;							// gzGeodeticDatum
	gzDouble			central_meridian;				// rad (longitude origo)
	gzDouble			latitude_origo;					// rad	(latitude origo)
	gzDouble			scale_on_central_meridian;		
	gzDouble			false_northing;					// m
	gzDouble			false_easting;					// m
};

// ---------------- Ellipsoids ---------------




#endif // __GZ_COORDINATE_TYPES_H__







