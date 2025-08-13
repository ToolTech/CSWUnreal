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
// File			: gzAltitudeLookup.h
// Module		: gzCoordinate
// Description	: Class definition of altitude management
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.262
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
// AMO	200407	Created file								(2.10.5)
//
//******************************************************************************
#ifndef __GZ_ALTITUDE_LOOKUP_H__
#define __GZ_ALTITUDE_LOOKUP_H__

/*!	\file 
	\brief Altitude Lookup in GizmoSDK

	This file provides utilities to find altitudes at lat/long very fast

*/

#include "gzCoordinateBase.h"

// --------------------------- Alt file header ----------------------------------

#define GZ_ALT_MAGIC	LLU(0x37fb6aec7bd29721)
#define GZ_ALT_VERSION	1

struct gzLatLongInfo
{
	gzDouble		latitude;
	gzDouble		longitude;

	gzDouble		latitude_delta;
	gzDouble		longitude_delta;

	gzUInt32		latitude_rows;
	gzUInt32		longitude_columns;
};

class AltFileHeader : public gzSerializeData
{
public:
	gzUInt64		magic;
	gzUInt16		version;
	gzLatLongInfo	info;

	GZ_DECLARE_SERIALIZE_8_LE("ALT", magic, version, info.latitude, info.longitude, info.latitude_delta, info.longitude_delta, info.latitude_rows, info.longitude_columns);
};

// ------------------------- Altitude Dataset ---------------------------------------

typedef gzRefData<gzArray<gzFloat>> gzAltitudeRefData;

GZ_DECLARE_REFPTR(gzAltitudeRefData);

class gzAltitudeDataset :	public gzThreadSafeReference,
							public gzSerializeData
{
public:

	gzAltitudeDataset() :accessTime(0) {}

	gzString				url;

	gzAltitudeRefDataPtr	data;

	gzLatLongInfo			info;

	gzDouble				accessTime;

	gzMutex					dataLock;

	GZ_COORDINATE_EXPORT static gzAltitudeDataset*	readAltitudeDataset(const gzString& url, gzBool onlyHeader=FALSE, gzAltitudeDataset *input=NULL);
	GZ_COORDINATE_EXPORT static gzBool				writeAltitudeDataset(gzAltitudeDataset *dataset);

	GZ_COORDINATE_EXPORT gzBool getHeight(const gzDouble& latitude, const gzDouble &longitude, gzDouble &height, gzInt32& lat_index, gzDouble &lat_fraction, gzInt32& lon_index, gzDouble &lon_fraction);

	// ------------------------ SerializeData -----------------------------------

	GZ_COORDINATE_EXPORT virtual gzVoid write(gzSerializeAdapter* adapter);

	GZ_COORDINATE_EXPORT virtual gzVoid read(gzSerializeAdapter* adapter);

	GZ_COORDINATE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter* adapter);

	GZ_COORDINATE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter* adapter = nullptr) const;
};

GZ_DECLARE_REFPTR(gzAltitudeDataset);

// --------------------------- gzAltitudeLookup ----------------------

class gzAltitudeLookup :	public gzReference,
							public gzThread,
							public gzSerializeData
{
public:

	GZ_COORDINATE_EXPORT	gzAltitudeLookup();

	GZ_COORDINATE_EXPORT	virtual ~gzAltitudeLookup();

	GZ_COORDINATE_EXPORT	gzBool	addDirectory(const gzString& path = ".", gzBool recursive = TRUE);

	GZ_COORDINATE_EXPORT	gzVoid	clearDirectories();

	GZ_COORDINATE_EXPORT	gzBool	addAltitudeDataset(gzAltitudeDataset* dataset);

	GZ_COORDINATE_EXPORT	gzBool	loadURL(const gzString& url);
	GZ_COORDINATE_EXPORT	gzBool	saveURL(const gzString& url);

	
	//! Radians for latitude and longitude
	GZ_COORDINATE_EXPORT	gzDouble getAltitude(gzDouble latitude, gzDouble longitude,gzBool sample=TRUE,gzBool *ok=NULL);

	GZ_COORDINATE_EXPORT	gzVoid	clear();

	GZ_PROPERTY_RW_MUTEX_GET_EXPORT(gzDouble, LatitudeMin, m_spatialLocker, GZ_COORDINATE_EXPORT);
	GZ_PROPERTY_RW_MUTEX_GET_EXPORT(gzDouble, LatitudeMax, m_spatialLocker, GZ_COORDINATE_EXPORT);
	GZ_PROPERTY_RW_MUTEX_GET_EXPORT(gzDouble, LongitudeMin, m_spatialLocker, GZ_COORDINATE_EXPORT);
	GZ_PROPERTY_RW_MUTEX_GET_EXPORT(gzDouble, LongitudeMax, m_spatialLocker, GZ_COORDINATE_EXPORT);

	GZ_PROPERTY_MUTEX_EXPORT(gzDouble, PurgeTime, m_inUseLock, GZ_COORDINATE_EXPORT);

	GZ_COORDINATE_EXPORT	gzUInt32 getDatasetCount();

	// ------------------------ SerializeData -----------------------------------

	GZ_COORDINATE_EXPORT virtual gzVoid write(gzSerializeAdapter* adapter) override;

	GZ_COORDINATE_EXPORT virtual gzVoid read(gzSerializeAdapter* adapter) override;

	GZ_COORDINATE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter* adapter) override;

	GZ_COORDINATE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter* adapter = nullptr) const override;

private:

	gzDouble getSampledAltitude(const gzDouble&value_0_0 , const gzLatLongInfo &info, const gzInt32 & lat_index, const gzDouble & lat_fraction, const gzInt32& lon_index, const gzDouble & lon_fraction, gzBool* ok = NULL);

	//! Override this method to get the default execution
	virtual gzVoid process() override;

	gzReadWriteMutex					m_spatialLocker;
	gzSpatialData<gzAltitudeDatasetPtr> m_spatial;

	gzAltitudeDatasetPtr				m_last;

	gzEvent								m_inUseLock;
	gzRefList<gzAltitudeDataset>		m_inUse;

	gzMutex								m_addedDictsMutex;
	gzDict<gzString, gzVoid>			m_addedDicts;

};

GZ_DECLARE_REFPTR(gzAltitudeLookup);

#endif // __GZ_ALTITUDE_LOOKUP_H__







