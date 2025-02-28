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
// File			: gzNodeConstants.h
// Module		: 
// Description	: Constant and structures for node attributes and definitions
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
// AMO	010505	Created file 	
// AMO	120116	Fixed bug in serializers DBSize etc..				(2.6.0)
// AMO	230309	Added some macros for dynamic types					(2.12.67)
// AMO	230413	Added MapTypes										(2.12.72)
// AMO	231019	Added Map Title as identifier for map in readable	(2.12.110)
// AMO	250117	Added STATUS_MESSAGE with list of messages			(2.12.207)
//
//******************************************************************************
#ifndef __GZ_NODE_CONSTANTS_H__
#define __GZ_NODE_CONSTANTS_H__

/*!	\file 
	\brief constant definitions for scene graph nodes

*/

#include "gzNode.h"

GZ_GRAPH_EXPORT gzVoid gzSetNodeDbInfo(gzNode *node,const gzString &attribute,const gzDynamicType &data);

GZ_GRAPH_EXPORT	gzDynamicType gzGetNodeDbInfo(const gzNode *node);

GZ_GRAPH_EXPORT	gzDynamicType gzGetNodeDbInfo(const gzNode *node,const gzString &attribute);

GZ_GRAPH_EXPORT	gzBool gzHasNodeDbInfo(const gzNode *node,const gzString &attribute);

GZ_GRAPH_EXPORT	gzBool gzHasNodeDbInfo(const gzNode *node);

GZ_GRAPH_EXPORT	gzVoid gzRemoveNodeDbInfo(gzNode *node,const gzString &attribute);



// Constants for named UserData used by nodes

const gzString	GZ_USERDATA_DB_INFO	="UserDataDbInfo";


// Constants for Attributes provided by the GZ_USERDATA_DB_INFO

const gzString	GZ_DB_INFO_CREATION_TIME	= "DbI-CreationTime";			// Time String
const gzString	GZ_DB_INFO_AUTHOR			= "DbI-Author";					// Author String
const gzString	GZ_DB_INFO_TITLE			= "DbI-Title";					// Title String that identifies map

const gzString	GZ_DB_INFO_TYPE				= "DbI-Type";					// 3D Type GZ_DB_INFO_TYPE_xxx  3ds,gzd, etc..
const gzString	GZ_DB_INFO_TYPE_VERSION		= "DbI-Type-Version";			// 3D Type GZ_DB_INFO_TYPE_xxx  version for each type 3ds,gzd, etc..

const gzString	GZ_DB_INFO_CONTENT			= "DbI-Content";				// GZ_DB_INFO_CONTENT_xx  bits

const gzString	GZ_DB_INFO_MAP_TYPE			= "DbI-MapType";				// GZ_DB_INFO_MAP_TYPE_xx bits

const gzString	GZ_DB_INFO_MAP_SEASON		= "DbI-MapSeason";				// GZ_DB_INFO_MAP_SEASON_xx

const gzString	GZ_DB_INFO_FLAGS			= "DbI-Flags";					// Serialize Attribute flags

const gzString	GZ_DB_INFO_VERSION			= "DbI-Version";				// String value. On file level its the version of indata. On db level its tha db version

const gzString	GZ_DB_INFO_GC				= "DbI-GroundClamp";			// Bool value. True (!=0) means one or more groundclamped attempt

const gzString	GZ_DB_INFO_METER_SCALE		= "DbI-MeterScale";				// Number to scale model to meters approx
const gzString	GZ_DB_INFO_PROJECTION		= "DbI-Projection";				// GZ_DB_INFO_PROJECTION_xx
const gzString	GZ_DB_INFO_ELLIPSOID		= "DbI-Ellipsoid";
const gzString	GZ_DB_INFO_COORD_SYS		= "DbI-CoordSystem";			// CoordSystem String

const gzString	GZ_DB_INFO_DB_ORIGIN_POS	= "DbI-Database Origin";		// Depends on GZ_DB_INFO_COORD_SYS
const gzString	GZ_DB_INFO_DB_SW_POS		= "DbI-Database SWpos";			// gzAttribute_LatPos in radians
const gzString	GZ_DB_INFO_DB_NE_POS		= "DbI-Database NEpos";			// gzAttribute_LatPos in radians


const gzString	GZ_DB_INFO_COMMENT			= "DbI-Comment";				// String generic comment

const gzString	GZ_DB_INFO_SHADOW_GENERATOR	= "GenShad";
const gzString	GZ_DB_INFO_STATUS			= "Dbi-Status";					// gzDbInfoStatusBits
const gzString	GZ_DB_INFO_STATUS_MESSAGE	= "Dbi-Status-Message";			// List of vital status messages


// DFAD data & ID

const gzString	GZ_DB_INFO_DFAD_SURFACE_MATERIAL	= "DbI-DFAD-SMC";
const gzString	GZ_DB_INFO_DFAD_FEATURE_ID			= "DbI-DFAD-FID";

const gzString	GZ_DB_INFO_ID						= "DbI-ID";				// Guid or number ID
const gzString	GZ_DB_INFO_INSTANCE_ID				= "DbI-InstanceID";		// Number ID of instance

// License Feature

const gzString	GZ_DB_INFO_LICENSE					="DbI-LIC";				// String

// Database size 

const gzString	GZ_DB_INFO_DB_SIZE					="DbI-SZ";				// gzAttribute_DBSize


// Max Lod distance from loaded db

const gzString	GZ_DB_INFO_DB_MAX_LOD_RANGE			="DbI-LR";				// Meters

// --------- Attribute constant values ---------------------------------------------------------------------------------------------

// BIT values for GZ_DB_INFO_MAP_TYPE ---------------------------------------------------------------------------------------------

enum gzDbInfoMapType
{
	GZ_DB_INFO_MAP_TYPE_UNKNOWN			= 0,
	GZ_DB_INFO_MAP_TYPE_FLAT			= 1 << 0,					// Only flat geometry
	GZ_DB_INFO_MAP_TYPE_DEM				= 1 << 1,					// DEM based elevation used for ground
	GZ_DB_INFO_MAP_TYPE_DSM				= 1 << 2,					// DSM based elevation used for ground
	GZ_DB_INFO_MAP_TYPE_HEIGHT			= 1 << 3,					// DSM-DEM based elevation used for surface height
	GZ_DB_INFO_MAP_TYPE_FEATURE			= 1 << 4,					// Feature classification used in textures
	GZ_DB_INFO_MAP_TYPE_KML				= 1 << 5,					// KML data used in scene
	GZ_DB_INFO_MAP_TYPE_BUILDINGS		= 1 << 6,					// Building objects data used in scene
	GZ_DB_INFO_MAP_TYPE_OBJECTS			= 1 << 7,					// Additional objects data used in scene
	GZ_DB_INFO_MAP_TYPE_SHADERS			= 1 << 8,					// Custom Shaders (non built in)  used in scene
};

GZ_USE_BIT_LOGIC(gzDbInfoMapType);
GZ_DECLARE_DYNAMIC_ENUM(gzDbInfoMapType);

// Constants for GZ_DB_INFO_MAP_SEASON ---------------------------------------------------------------------------------------------

const gzString	GZ_DB_INFO_MAP_SEASON_GENERIC		= "Generic";	// No specific season (alround)
const gzString	GZ_DB_INFO_MAP_SEASON_VINTER		= "Vinter";		// Vinter Theme
const gzString	GZ_DB_INFO_MAP_SEASON_SUMMER		= "Summer";		// Summer Theme
const gzString	GZ_DB_INFO_MAP_SEASON_SPRING		= "Spring";		// Spring Theme
const gzString	GZ_DB_INFO_MAP_SEASON_AUTUMN		= "Autumn";		// Autumn Theme				// Can use multiple themes separated by semicolon

// Constants for GZ_DB_INFO_PROJECTION ---------------------------------------------------------------------------------------------

const gzString	GZ_DB_INFO_PROJECTION_FLAT			= "Flat Earth";
const gzString	GZ_DB_INFO_PROJECTION_SPHERE		= "Sphere";
const gzString	GZ_DB_INFO_PROJECTION_GEODETIC		= "Geodetic";
const gzString	GZ_DB_INFO_PROJECTION_GEOCENTRIC	= "Geocentric";
const gzString	GZ_DB_INFO_PROJECTION_TRAPEZODIAL	= "Trapezoidal";
const gzString	GZ_DB_INFO_PROJECTION_LAMBERT		= "Lambert";
const gzString	GZ_DB_INFO_PROJECTION_UTM			= "UTM";
const gzString	GZ_DB_INFO_PROJECTION_RT90			= "RT90";
const gzString	GZ_DB_INFO_PROJECTION_SWEREF99		= "SWEREF99";
const gzString	GZ_DB_INFO_PROJECTION_PROJECTED		= "Projected";

// Constants for GZ_DB_INFO_ELLIPSOID ---------------------------------------------------------------------------------------------

const gzString	GZ_DB_INFO_ELLIPSOID_WGS84			= "WGS 1984";	// default
const gzString	GZ_DB_INFO_ELLIPSOID_WGS72			= "WGS 1972";
const gzString	GZ_DB_INFO_ELLIPSOID_GRS80			= "GRS80";

const gzString	GZ_DB_INFO_ELLIPSOID_BESSEL			= "Bessel 1841";		// RT90 Sweden

const gzString	GZ_DB_INFO_ELLIPSOID_CLARKE_1866	= "Clarke 1866";
const gzString	GZ_DB_INFO_ELLIPSOID_AIRY_1830		= "AIRY 1830";
const gzString	GZ_DB_INFO_ELLIPSOID_NAD_1927		= "NAD 1927";

// BIT values for GZ_DB_INFO_CONTENT ---------------------------------------------------------------------------------------------

enum gzDbInfoContent
{
	GZ_DB_INFO_CONTENT_UNKNOWN		= 0,
	GZ_DB_INFO_CONTENT_MAP_DATA		= 1 << 0,			// Contains map data that shall be rebuilt in different projections
	GZ_DB_INFO_CONTENT_MODEL_DATA	= 1 << 1,			// Contains model data that are fixed in shape between different projections
	GZ_DB_INFO_CONTENT_FOLIAGE		= 1 << 2,			// Contains map objects foliage that need to be rebuilt for different projections
	GZ_DB_INFO_CONTENT_OVERLAY		= 1 << 3,			// Contains map overlay data that needs to be rebuilt
};

GZ_USE_BIT_LOGIC(gzDbInfoContent);
GZ_DECLARE_DYNAMIC_ENUM(gzDbInfoContent);

// BIT values for GZ_DBI_INFO_STATUS ---------------------------------------------------------------------------------------------

enum gzDbInfoStatusBits
{
	GZ_DB_INFO_STATUS_OK				= 0,
	GZ_DB_INFO_STATUS_UNKNOW_DATA		= 1<<0,
	GZ_DB_INFO_STATUS_MISSING_TEXTURE	= 1<<1,
};

GZ_USE_BIT_LOGIC(gzDbInfoStatusBits);
GZ_DECLARE_DYNAMIC_ENUM(gzDbInfoStatusBits);

// Structures

// ---------------------------------- latpos --------------------------------
// Compatible with gzCoordinate LatPos

class gzAttribute_LatPos : public gzSerializeData
{
public:

	gzAttribute_LatPos(gzDoubleXYZ pos=gzDoubleXYZ(0,0,0))
	{
		latitude=pos.x;
		longitude=pos.y;
		altitude=pos.z;
	}

	// Attribute data

	gzDouble	latitude;	// In radians

	gzDouble	longitude;	// In radians
		
	gzDouble	altitude;	// In meters

	// Serializing methods

	GZ_DECLARE_SERIALIZE_3(GZ_DYNAMIC_TYPE_LATPOS,latitude,longitude,altitude);

};

// ------------------------------------- CartPos --------------------------------------
// Compatible with gzCoordinate CartPos

class gzAttribute_CartPos : public gzSerializeData
{
public:

	gzAttribute_CartPos(gzDoubleXYZ pos=gzDoubleXYZ(0,0,0))
	{
		x=pos.x;
		y=pos.y;
		z=pos.z;
	}

	// Attribute data

	gzDouble	x;			// In db units

	gzDouble	y;			// In db units
		
	gzDouble	z;			// In db units

	// Serializing methods

	GZ_DECLARE_SERIALIZE_3(GZ_DYNAMIC_TYPE_CARTPOS,x,y,z);
};

// ------------------------------------- UTMPos --------------------------------------
// Compatible with gzCoordinate UTMPos

class gzAttribute_UTMPos : public gzSerializeData
{
public:

	gzAttribute_UTMPos(gzInt32 _zone=0,gzBool _north=0, gzDouble _northing=0,gzDouble	_easting=0,gzDouble _h=0)
	{
		zone = _zone;
		north = _north;
		northing = _northing;
		easting = _easting;
		h = _h;
	}

	// Attribute data

	gzInt32		zone;
	gzBool		north;

	gzDouble	northing;
	gzDouble	easting;
	gzDouble	h;


	// Serializing methods

	GZ_DECLARE_SERIALIZE_5(GZ_DYNAMIC_TYPE_UTMPOS, zone, north, northing, easting, h);
};

//------------------- Database size ----------------------------------------

class gzAttribute_DBSize : public gzSerializeData
{
public:

	gzAttribute_DBSize(gzDoubleXYZ min=gzDoubleXYZ(0,0,0),gzDoubleXYZ max=gzDoubleXYZ(0,0,0))
	{
		minX=min.x;
		minY=min.y;
		minZ=min.z;

		maxX=max.x;
		maxY=max.y;
		maxZ=max.z;
	}

	// Attribute data

	gzDouble	minX;

	gzDouble	minY;

	gzDouble	minZ;

	gzDouble	maxX;

	gzDouble	maxY;

	gzDouble	maxZ;

	// Serializing methods

	GZ_DECLARE_SERIALIZE_6("DBSize",minX,minY,minZ,maxX,maxY,maxZ);

};

// --------------------------------------------------------------------------------------

#endif // __GZ_NODE_CONSTANTS_H__
