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
// File			: gzCoordinate.h
// Module		: gzCoordinate
// Description	: Class definition of coordinate transforms
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.306
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
// EHA	230608	Added flat earth coordinate type			(2.12.87)
//
//******************************************************************************
#ifndef __GZ_COORDINATE_H__
#define __GZ_COORDINATE_H__

/*!	\file 
	\brief Coordinate transformations in GizmoSDK

	This file provides utilities to translate between various simple coordinate systems

*/

#include "gzHeightModelTransform.h"

enum gzCoordType
{
	GZ_COORDTYPE_GEOCENTRIC,	// Cartesian
	GZ_COORDTYPE_GEODETIC,		// Geodetic lat/lon in radians
	GZ_COORDTYPE_PROJECTED,		// Gauss-Kreuger (Trans Mercator)
	GZ_COORDTYPE_UTM,			// UTM Gauss-Kreuger (Trans Mercator)
	GZ_COORDTYPE_MGRS,			// Military Grid Reference
	GZ_COORDTYPE_FLATEARTH,		// Local cartesian on a flat earth
	GZ_COORDTYPE_STATE_COUNT,	// Must be second last
	GZ_COORDTYPE_UNDEFINED,
};

struct gzCoordSystem
{
	gzGeodeticDatum		datum;				// Datum

	gzFlatProjection	projection;			// What kind of possible projection

	gzCoordType			type;				// What kind of coordinate type
};

// -------------------------------- Meta -----------------------

struct gzCoordSystemMetaData
{
	union									// Extra metadata for coordinate systems
	{
		struct 
		{
			gzInt32		zone;
			gzBool		north;

		} utm;

		struct 
		{
			gzDouble	originLat;
			gzDouble	originLon;
			gzDouble	originHeight;

		} flatEarth;

		struct 
		{
			gzUInt64	value1;
			gzUInt64	value2;

		} undefined;		// Used to zero out value in union. Must be large enough to cover all meta types
	};
};

struct gzCoordStateData
{
	gzCoordSystem			system;
	gzCoordSystemMetaData	meta;

	struct
	{
		gzCartPos	cartpos;
		gzLatPos	latpos;
		gzProjPos	projpos;
		gzUTMPos	utmpos;
		gzString	mgrs;
		gzVec3D		localpos;

	} position;
};

//! Mapping swizzle between (x,y,z) and varoius coordinates
enum gzCoordinateSwizzle
{
	GZ_COORD_SWIZZLE_MAP_LATITUDE_TO_X	= 1 << 0,
	GZ_COORD_SWIZZLE_MAP_LATITUDE_TO_Y	= 1 << 1,
	GZ_COORD_SWIZZLE_MAP_LATITUDE_TO_Z	= 1 << 2,

	GZ_COORD_SWIZZLE_MAP_LONGITUDE_TO_X = 1 << 3,
	GZ_COORD_SWIZZLE_MAP_LONGITUDE_TO_Y = 1 << 4,
	GZ_COORD_SWIZZLE_MAP_LONGITUDE_TO_Z = 1 << 5,

	GZ_COORD_SWIZZLE_MAP_NORTHING_TO_X	= 1 << 6,
	GZ_COORD_SWIZZLE_MAP_NORTHING_TO_Y	= 1 << 7,
	GZ_COORD_SWIZZLE_MAP_NORTHING_TO_Z	= 1 << 8,

	GZ_COORD_SWIZZLE_MAP_EASTING_TO_X	= 1 << 9,
	GZ_COORD_SWIZZLE_MAP_EASTING_TO_Y	= 1 << 10,
	GZ_COORD_SWIZZLE_MAP_EASTING_TO_Z	= 1 << 11,

	GZ_COORD_SWIZZLE_MAP_ALTITUDE_TO_X	= 1 << 12,
	GZ_COORD_SWIZZLE_MAP_ALTITUDE_TO_Y	= 1 << 13,
	GZ_COORD_SWIZZLE_MAP_ALTITUDE_TO_Z	= 1 << 14,

	GZ_COORD_SWIZZLE_MAP_LATITUDE_TO_NEG_X	= 1 << 15,
	GZ_COORD_SWIZZLE_MAP_LATITUDE_TO_NEG_Y	= 1 << 16,
	GZ_COORD_SWIZZLE_MAP_LATITUDE_TO_NEG_Z	= 1 << 17,

	GZ_COORD_SWIZZLE_MAP_LONGITUDE_TO_NEG_X	= 1 << 18,
	GZ_COORD_SWIZZLE_MAP_LONGITUDE_TO_NEG_Y = 1 << 19,
	GZ_COORD_SWIZZLE_MAP_LONGITUDE_TO_NEG_Z = 1 << 20,

	GZ_COORD_SWIZZLE_MAP_NORTHING_TO_NEG_X	= 1 << 21,
	GZ_COORD_SWIZZLE_MAP_NORTHING_TO_NEG_Y	= 1 << 22,
	GZ_COORD_SWIZZLE_MAP_NORTHING_TO_NEG_Z	= 1 << 23,

	GZ_COORD_SWIZZLE_MAP_EASTING_TO_NEG_X	= 1 << 24,
	GZ_COORD_SWIZZLE_MAP_EASTING_TO_NEG_Y	= 1 << 25,
	GZ_COORD_SWIZZLE_MAP_EASTING_TO_NEG_Z	= 1 << 26,

	GZ_COORD_SWIZZLE_MAP_ALTITUDE_TO_NEG_X	= 1 << 27,
	GZ_COORD_SWIZZLE_MAP_ALTITUDE_TO_NEG_Y	= 1 << 28,
	GZ_COORD_SWIZZLE_MAP_ALTITUDE_TO_NEG_Z	= 1 << 29,

	//! Map between 3D coordinates and position
	GZ_COORD_SWIZZLE_MAP_DEFAULT	= GZ_COORD_SWIZZLE_MAP_LATITUDE_TO_NEG_Z | GZ_COORD_SWIZZLE_MAP_LONGITUDE_TO_X | GZ_COORD_SWIZZLE_MAP_NORTHING_TO_NEG_Z | GZ_COORD_SWIZZLE_MAP_EASTING_TO_X | GZ_COORD_SWIZZLE_MAP_ALTITUDE_TO_Y,

	//! Map between (E (x),N (y),U (z)) and position 
	GZ_COORD_SWIZZLE_ENU			= GZ_COORD_SWIZZLE_MAP_LATITUDE_TO_Y | GZ_COORD_SWIZZLE_MAP_LONGITUDE_TO_X | GZ_COORD_SWIZZLE_MAP_NORTHING_TO_Y | GZ_COORD_SWIZZLE_MAP_EASTING_TO_X | GZ_COORD_SWIZZLE_MAP_ALTITUDE_TO_Z,

};


GZ_USE_BIT_LOGIC(gzCoordinateSwizzle);

GZ_DECLARE_DYNAMIC_ENUM(gzCoordinateSwizzle);

template <> inline gzUInt32 gzGetHash(const gzHeightModel& k) { return (gzUInt32)k; }

//******************************************************************************
// Class	: gzCoordinate
//									
// Purpose  : Service management
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	180220	Created 
//									
//******************************************************************************
class gzCoordinate
{

public:

	GZ_COORDINATE_EXPORT	gzCoordinate();

	GZ_COORDINATE_EXPORT	virtual ~gzCoordinate() {};

	GZ_COORDINATE_EXPORT	gzVoid setCartPos(const gzCartPos &pos, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID);
	GZ_COORDINATE_EXPORT	gzBool getCartPos(gzCartPos &pos, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID);

	GZ_COORDINATE_EXPORT	gzVoid setLatPos(const gzLatPos &pos, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID);
	GZ_COORDINATE_EXPORT	gzBool getLatPos(gzLatPos &pos, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID);

	GZ_COORDINATE_EXPORT	gzVoid setUTMPos(const gzUTMPos &pos, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID);
	GZ_COORDINATE_EXPORT	gzBool getUTMPos(gzUTMPos &pos, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID);

	GZ_COORDINATE_EXPORT	gzVoid setFlatEarthPos(const gzVec3D& pos, const gzCoordSystemMetaData& origin, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID);
	GZ_COORDINATE_EXPORT	gzBool getFlatEarthPos(gzVec3D& pos, const gzCoordSystemMetaData& origin, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID);

	GZ_COORDINATE_EXPORT	gzVoid setProjPos(const gzProjPos &pos, gzFlatProjection proj= GZ_PROJ_RT90);
	GZ_COORDINATE_EXPORT	gzBool getProjPos(gzProjPos &pos, gzFlatProjection proj = GZ_PROJ_RT90);

	GZ_COORDINATE_EXPORT	gzVoid setMGRS(const gzString &mgrs, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID);
	GZ_COORDINATE_EXPORT	gzBool getMGRS(gzString &mgrs, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID);

	// --- Transformations ---------------------------------------------------------

	GZ_COORDINATE_EXPORT	gzBool		WGS_To_Other(gzCartPos &dest,	const gzCartPos &cart_wgs,	gzGeodeticDatum other);
	GZ_COORDINATE_EXPORT	gzBool		Other_To_WGS(gzCartPos &dest,	const gzCartPos &cart_wgs,	gzGeodeticDatum other);
	GZ_COORDINATE_EXPORT	gzBool		Cart_To_Lat(gzLatPos &dest,		const gzCartPos &cartpos,	gzEllipsoid e);
	GZ_COORDINATE_EXPORT	gzBool		Lat_To_Cart(gzCartPos &dest,	const gzLatPos &latpos,		gzEllipsoid e);
	GZ_COORDINATE_EXPORT	gzBool		Proj_To_Lat(gzLatPos &dest,		const gzProjPos &projpos,	gzFlatProjection proj);
	GZ_COORDINATE_EXPORT	gzBool		Lat_To_Proj(gzProjPos &dest,	const gzLatPos &latpos,		gzFlatProjection proj);
	GZ_COORDINATE_EXPORT	gzBool		UTM_To_Lat(gzLatPos&dest,		const gzUTMPos &utmpos,		gzEllipsoid e);
	GZ_COORDINATE_EXPORT	gzBool		Lat_To_UTM(gzUTMPos &dest,		const gzLatPos &latpos,		gzEllipsoid e);
	GZ_COORDINATE_EXPORT	gzBool		Cart_To_Local(gzVec3D&dest,		const gzCartPos& cartPos,	const gzLatPos origin,	gzEllipsoid e);
	GZ_COORDINATE_EXPORT	gzBool		Local_To_Cart(gzCartPos&dest,	const gzVec3D& localPos,	const gzLatPos origin,	gzEllipsoid e);
	GZ_COORDINATE_EXPORT	gzBool		UTM_To_MGRS(gzString &dest,		const gzUTMPos &utmpos,		gzEllipsoid e);
	GZ_COORDINATE_EXPORT	gzBool		MGRS_To_UTM(gzUTMPos &dest,		const gzString &mgrs,		gzEllipsoid e);
	GZ_COORDINATE_EXPORT	gzBool		Height_To_Ellipsoid(gzLatPos &pos, gzHeightModel model, gzEllipsoid e);
	GZ_COORDINATE_EXPORT	gzBool		Ellipsoid_To_Height(gzLatPos &pos, gzHeightModel model, gzEllipsoid e);

	GZ_COORDINATE_EXPORT	gzGeodeticDatum getDatum(gzEllipsoid e, gzHeightModel model);

	// --- Property control ---------------------------------------------------------

	GZ_PROPERTY_EXPORT(gzBool,		MGRSAltitude,		GZ_COORDINATE_EXPORT);		// TRUE or FALSE to add UTM altitude in MGRS. Default is FALSE
	GZ_PROPERTY_EXPORT_(gzInt32,	PrefUTMZone,		GZ_COORDINATE_EXPORT);		// <0 for no preference, 0-59 for preferred zone
	GZ_PROPERTY_EXPORT_(gzInt32,	PrefUTMHemisphere,	GZ_COORDINATE_EXPORT);		// =0 for no preference, 1 for north and -1 for south

	// Utilities -------------------------------------------------------------------

	// --- Result in {E,N,U} coordinate system ------

	GZ_COORDINATE_EXPORT	static gzMatrix3 getOrientationMatrix(const gzLatPos& pos, gzEllipsoid e = gzEllipsoid::GZ_ELLIPSOID_WGS84);
	GZ_COORDINATE_EXPORT	static gzMatrix3 getOrientationMatrix(const gzCartPos& pos, gzEllipsoid e = gzEllipsoid::GZ_ELLIPSOID_WGS84);

	GZ_COORDINATE_EXPORT	static gzVec3 getSphericalDirection(const gzLatPos& from, const gzLatPos& to, gzEllipsoid e = gzEllipsoid::GZ_ELLIPSOID_WGS84);
	GZ_COORDINATE_EXPORT	static gzVec3 getSphericalDirection(const gzCartPos& from, const gzCartPos& to, gzEllipsoid e = gzEllipsoid::GZ_ELLIPSOID_WGS84);

	// --- Systems Lockup -----------------------------------------------------------

	GZ_COORDINATE_EXPORT	static gzBool	getCoordinateSystem(const gzString &name, gzCoordSystem &system, gzCoordSystemMetaData &meta);
	GZ_COORDINATE_EXPORT	static gzString	getCoordinateSystem(const gzCoordSystem &system, const gzCoordSystemMetaData &meta);

	GZ_COORDINATE_EXPORT	static gzVoid	registerHeightModelTransformer(gzHeightModel height_model, gzHeightModelTransformer* transformer);
	GZ_COORDINATE_EXPORT	static gzVoid	unregisterHeightModelTransformer(gzHeightModel height_model, gzHeightModelTransformer* transformer);

	GZ_COORDINATE_EXPORT	static gzHeightModel getHeightModel(gzGeodeticDatum datum);

	GZ_COORDINATE_EXPORT	static gzBool	get3DCoordinate(const gzLatPos& latpos, const gzCoordSystem& system, const gzCoordSystemMetaData& meta, gzVec3D &position, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzBool	getGlobalCoordinate(const gzVec3D& position, const gzCoordSystem& system, const gzCoordSystemMetaData& meta, gzLatPos& latpos, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzBool	get3DCoordinate(const gzCartPos& cartpos, const gzCoordSystem& system, const gzCoordSystemMetaData& meta, gzVec3D& position, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzBool	getGlobalCoordinate(const gzVec3D& position, const gzCoordSystem& system, const gzCoordSystemMetaData& meta, gzCartPos& cartpos, gzGeodeticDatum datum = GZ_GEODETIC_DATUM_WGS84_ELLIPSOID, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);

	GZ_COORDINATE_EXPORT	static gzBool	get3DCoordinate(const gzDynamicType& geopos, const gzCoordSystem& system, const gzCoordSystemMetaData& meta, gzVec3D& position, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzBool	getGlobalCoordinate(const gzVec3D& position, const gzCoordSystem& system, const gzCoordSystemMetaData& meta, gzDynamicType& geopos, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);

	GZ_COORDINATE_EXPORT	static gzBool	get3DOrientation(const gzLatPos& latpos, const gzCoordSystem& system, const gzCoordSystemMetaData& meta, gzMatrix3& enu_orientation, gzEllipsoid e = gzEllipsoid::GZ_ELLIPSOID_WGS84);
	GZ_COORDINATE_EXPORT	static gzBool	get3DOrientation(const gzCartPos& cartpos, const gzCoordSystem& system, const gzCoordSystemMetaData& meta, gzMatrix3& enu_orientation, gzEllipsoid e = gzEllipsoid::GZ_ELLIPSOID_WGS84);

	GZ_COORDINATE_EXPORT	static gzBool	Flat_To_Lat_Gauss_Kruger(gzLatPos& dest, const gzDouble &x,const gzDouble& y, const gzEllipsoidParameters* ellipsoid_params, const gzDouble& false_northing, const gzDouble& false_easting, const gzDouble& central_meridan, const gzDouble &latitude_origo, const gzDouble& scale_on_central_meridian, const gzDouble& convergence_accuracy=1e-5);
	GZ_COORDINATE_EXPORT	static gzBool	Lat_To_Flat_Gauss_Kruger(gzDouble& x, gzDouble& y, const gzLatPos& latpos, const gzEllipsoidParameters* ellipsoid_params, const gzDouble& false_northing, const gzDouble& false_easting, const gzDouble& central_meridan, const gzDouble &latitude_origo, const gzDouble& scale_on_central_meridian);

	GZ_COORDINATE_EXPORT	static gzBool	convert(gzDouble& x, gzDouble& y, gzDouble& z, const gzString& sourceCoordSystem, const gzString& destinationCoordSystem, const gzCoordinateSwizzle& swizzleSource=GZ_COORD_SWIZZLE_MAP_DEFAULT, const gzCoordinateSwizzle& swizzleDestination = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzBool	convert(gzDouble& x, gzDouble& y, gzDouble& z, const gzCoordSystem& sourceCoordSystem, const gzCoordSystemMetaData& sourceCoordSystemMetaData, const gzCoordSystem& destinationCoordSystem, const gzCoordSystemMetaData& destinationCoordSystemMetaData, const gzCoordinateSwizzle& swizzleSource = GZ_COORD_SWIZZLE_MAP_DEFAULT, const gzCoordinateSwizzle& swizzleDestination = GZ_COORD_SWIZZLE_MAP_DEFAULT);

	// ------ Utility ------------------------------------------------------------

	GZ_COORDINATE_EXPORT	static gzDouble	getLatitude(const gzDouble& x, const gzDouble& y, const gzDouble& z, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzDouble	getLongitude(const gzDouble& x, const gzDouble& y, const gzDouble& z, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzDouble	getEasting(const gzDouble& x, const gzDouble& y, const gzDouble& z, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzDouble	getNorthing(const gzDouble& x, const gzDouble& y, const gzDouble& z, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzDouble	getAltitude(const gzDouble& x, const gzDouble& y, const gzDouble& z, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);

	GZ_COORDINATE_EXPORT	static gzVoid	setLatitude(const gzDouble &latitude, gzDouble& x,  gzDouble& y,  gzDouble& z, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzVoid	setLongitude(const gzDouble& longitude, gzDouble& x,  gzDouble& y,  gzDouble& z, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzVoid	setEasting(const gzDouble& easting, gzDouble& x,  gzDouble& y,  gzDouble& z, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzVoid	setNorthing(const gzDouble& northing, gzDouble& x,  gzDouble& y,  gzDouble& z, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);
	GZ_COORDINATE_EXPORT	static gzVoid	setAltitude(const gzDouble& altitude, gzDouble& x,  gzDouble& y,  gzDouble& z, const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);

	GZ_COORDINATE_EXPORT	static gzBool getLatPos(const gzString& position, gzLatPos& latpos, gzBool in_degrees=TRUE, const gzString& source_system="WGS84:GEOD,ELLIPSOID", const gzString& result_system = "WGS84:GEOD,ELLIPSOID");
	GZ_COORDINATE_EXPORT	static gzBool get3DCoordinate(const gzString& position, gzVec3D& pos, gzBool in_degrees = TRUE, const gzString& system = "WGS84:GEOC,ELLIPSOID", const gzCoordinateSwizzle& swizzle = GZ_COORD_SWIZZLE_MAP_DEFAULT);

private:

	// ------ internal state machine ------

	gzBool					transferState();

	gzCoordStateData		m_currentStateData;
	gzCoordStateData		m_requestedStateData;

	gzGaussProjection		m_user_defined_projection;
	gzEllipsoidParameters	m_user_defined_ellipsoid_parameters;
	gzGeodeticTransform		m_user_defined_geoid_transform;

	static gzMutex			s_heightModelLock;
	static gzRefDict<gzHeightModel, gzHeightModelTransformer>	s_heightModelTransformers;
};

GZ_COORDINATE_EXPORT gzBool operator==(const gzCoordSystem &left, const gzCoordSystem &right);

GZ_COORDINATE_EXPORT gzBool operator==(const gzCoordSystemMetaData &left, const gzCoordSystemMetaData &right);

GZ_COORDINATE_EXPORT gzVoid gzCheckLibraryVersion_coordinate(gzInt32 major = GZ_VERSION_MAJ, gzInt32 minor = GZ_VERSION_MIN, gzInt32 dev = GZ_VERSION_DEV);

#endif // __GZ_COORDINATE_H__







