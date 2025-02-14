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
// File			: cswGeoUTMComponent.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Base class for CSW UTM projection
// Author		: Anders Mod�n		
// Product		: CSW 1.1.2
//		
//
//			
// NOTE:	CSW (Common Synthetic World) is a simulation and presentation
//			framework for large scale digital twins on multiple platforms
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	241107	Created file 					(1.1.1)
//
//******************************************************************************

#include "Geo/cswGeoUTMComponent.h"

#include "gzCoordinate.h"

// Sets default values for this component's properties
UCSWGeoUTMComponent::UCSWGeoUTMComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

gzVoid UCSWGeoUTMComponent::setCoordinateSystem(const gzString& cs, const gzVec3D& origo)
{
	Super::setCoordinateSystem(cs, origo);

	gzCoordSystem system;

	gzCoordSystemMetaData meta;

	if (!gzCoordinate::getCoordinateSystem(cs, system, meta))
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to get CS from '%s' in UCSWGeoUTMComponent", cs);
		return;
	}

	gzLatPos latpos;

	if(!gzCoordinate::getGlobalCoordinate(origo, system, meta, latpos))
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to get Global Coordinate from '%s:%s' in UCSWGeoUTMComponent", cs,origo.asString());
		return;
	}

	gzCoordinate converter;

	converter.setLatPos(latpos);

	gzUTMPos utmpos;

	if(!converter.getUTMPos(utmpos))
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to get UTMPos from '%s:%s' in UCSWGeoUTMComponent", cs, origo.asString());
		return;
	}

	Zone = utmpos.zone;
	Hemisphere = utmpos.north ? "Northern" : "Southern";
	Easting = gzPrecision(utmpos.easting,2);
	Northing = gzPrecision(utmpos.northing,2);
	Height = utmpos.h;
}

