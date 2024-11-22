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
// File			: gzHeightModelTransform.h
// Module		: gzCoordinate
// Description	: Class definition of height model transforms
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
// AMO	200331	Created file								(2.10.5)
//
//******************************************************************************
#ifndef __GZ_HEIGHT_MODEL_TRANSFORM_H__
#define __GZ_HEIGHT_MODEL_TRANSFORM_H__

/*!	\file 
	\brief Height model transformations in GizmoSDK

	This file provides utilities to translate between various simple height model systems

*/

#include "gzCoordinateTypes.h"
#include "gzAltitudeLookup.h"

//******************************************************************************
// Class	: gzHeightModelTransformer
//									
// Purpose  : Jump Between height models and associated ellipsoid
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	200331	Created 
//									
//******************************************************************************
class GZ_COORDINATE_EXPORT gzHeightModelTransformer : public gzThreadSafeReference
{

public:

	virtual gzBool Height_To_Ellipsoid(gzLatPos&/*pos*/, gzHeightModel /*model*/, gzEllipsoid /*e*/) = 0;

	virtual gzBool Ellipsoid_To_Height(gzLatPos&/*pos*/, gzHeightModel /*model*/, gzEllipsoid /*e*/) = 0;

};

GZ_DECLARE_REFPTR(gzHeightModelTransformer);

//******************************************************************************
// Class	: gzEGM2008
//									
// Purpose  : Jump Between egm 2008 and associated ellipsoid
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	200331	Created 
//									
//******************************************************************************
class gzEGM2008 : public gzHeightModelTransformer
{

public:

	GZ_COORDINATE_EXPORT	gzBool Height_To_Ellipsoid(gzLatPos&/*pos*/, gzHeightModel /*model*/, gzEllipsoid /*e*/) override;

	GZ_COORDINATE_EXPORT	gzBool Ellipsoid_To_Height(gzLatPos&/*pos*/, gzHeightModel /*model*/, gzEllipsoid /*e*/) override;

	GZ_COORDINATE_EXPORT	gzBool init(const gzString& filename);

	GZ_COORDINATE_EXPORT	gzDouble getOffset(gzDouble lat_in_deg, gzDouble lon_in_deg);

	GZ_COORDINATE_EXPORT	gzFloat getIndexOffset(gzInt32 x, gzInt32 y);

private:

	gzSerializeAdapterFilePtr	m_adapter;

	gzMutex						m_locker;
};

GZ_DECLARE_REFPTR(gzEGM2008);

//******************************************************************************
// Class	: gzEGM2008v2
//									
// Purpose  : Jump Between egm 2008 and associated ellipsoid
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	200331	Created 
//									
//******************************************************************************
class gzEGM2008v2 : public gzHeightModelTransformer
{

public:

	GZ_COORDINATE_EXPORT	gzBool Height_To_Ellipsoid(gzLatPos&/*pos*/, gzHeightModel /*model*/, gzEllipsoid /*e*/) override;

	GZ_COORDINATE_EXPORT	gzBool Ellipsoid_To_Height(gzLatPos&/*pos*/, gzHeightModel /*model*/, gzEllipsoid /*e*/) override;

	GZ_COORDINATE_EXPORT	gzBool init(const gzString& url);

	GZ_COORDINATE_EXPORT	gzDouble getOffset(gzDouble lat_in_deg, gzDouble lon_in_deg,gzBool *ok=NULL);

	GZ_COORDINATE_EXPORT	gzDouble getOffsetInRad(gzDouble lat_in_rad, gzDouble lon_in_rad,gzBool* ok = NULL);

private:

	gzAltitudeLookupPtr		m_lookup;

};

GZ_DECLARE_REFPTR(gzEGM2008v2);

#endif // __GZ_HEIGHT_MODEL_TRANSFORM_H__







