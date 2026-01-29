//******************************************************************************
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
// File			: gzLicense.h
// Module		: gzBase
// Description	: Class definition of the gzLicense class
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.306
//		
//
//			
// NOTE:	GizmoBase is a platform abstraction utility layer for C++. It contains 
//			design patterns and C++ solutions for the advanced programmer.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990420	Created file 	
//
//******************************************************************************
#ifndef __GZ_LICENSE_H__
#define __GZ_LICENSE_H__

/*!	\file 
	\brief License management utilites 

	Certain parts of the Gizmo3D toolkit is license restricted. You can also use these
	tools to provide license management for your own features.
*/

#include "gzBase.h"
#include "gzService.h"
#include "gzThread.h"

//!License management class

enum gzLicenceFeature
{	
	GZ_LICENSE_FEATURE_NONE		=	0 , 
	GZ_LICENSE_FEATURE_GRAPHICS	=	(1<<0),
	GZ_LICENSE_FEATURE_SAVERS	=	(1<<1),
	GZ_LICENSE_FEATURE_DEVELOPER=	(1<<2),
};

GZ_USE_BIT_LOGIC(gzLicenceFeature);

enum gzLicenseCheckFeature
{	
	GZ_LICENSE_CHECK_FEATURE_VALID			=	 1,
	GZ_LICENSE_CHECK_FEATURE_INVALID		=	-1,
	GZ_LICENSE_CHECK_FEATURE_WRONG_VERSION	=	-2,
	GZ_LICENSE_CHECK_FEATURE_EXPIRED		=	-3,
	GZ_LICENSE_CHECK_FEATURE_NOT_STARTED	=	-4,
	GZ_LICENSE_CHECK_FEATURE_NOT_LICENSED	=	-5,
	GZ_LICENSE_CHECK_FEATURE_PERMANENT		=	32767,
};

//******************************************************************************
// Class	: gzLicense
//									
// Purpose  : Manage GizmoSDK Licenses 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981128	Created 
//									
//******************************************************************************
class gzLicense
{
public:
		
	GZ_BASE_EXPORT static gzUInt64		getMachineID();												//!< Retrieves the unique ID of the current machine platform

	GZ_BASE_EXPORT static gzUInt16		getFeatureKey(const gzString &licenseName=GZ_EMPTY_STRING);	//!< Retrieves the license feature for a specific license name

	GZ_BASE_EXPORT static gzUInt16		getFeatureKey(const gzUInt64 &licenseKey);					//!< Retrieves the license feature for a specific license key

	GZ_BASE_EXPORT static gzVoid		notifyDefaultLicense();										//!< Notifies the user of the current default license status

	GZ_BASE_EXPORT static gzUInt64		getLicenseKey(const gzString & licenseName=GZ_EMPTY_STRING);				//!< Retrieves the license key for a specific license name

	GZ_BASE_EXPORT static gzUInt64		createLicenseKey(const gzString & licenseName,gzUInt64 machid ,gzUInt16 start,gzUInt16 stop,gzUInt16 features,const gzString &password);

	GZ_BASE_EXPORT static gzLicenseCheckFeature getEncodedKey(gzUInt64 &key,gzString licenseName=GZ_EMPTY_STRING);

	GZ_BASE_EXPORT static gzUInt64		getLicenseIdentifier(gzUInt64 UID);

	GZ_BASE_EXPORT static gzUInt64		splashLicenseText(const gzString &header,const gzString &text,gzUInt64 checkid=0,gzUByte timeoutSec=5);

	GZ_BASE_EXPORT static gzString		getLicenseInfoText();

	GZ_BASE_EXPORT static gzInt32		getLicenseExpirationDays(const gzString &licenseName=GZ_EMPTY_STRING);

	GZ_BASE_EXPORT static gzBool		isPermanentLicense(const gzString &licenseName);

	GZ_BASE_EXPORT static gzBool		isPermanentLicenseSet(const gzString &licenseName);

	GZ_BASE_EXPORT static gzVoid		setPermanentLicense(const gzString &licenseName);

};

//******************************************************************************
// Class	: gzLicenseManager
//									
// Purpose  : Manage licese server
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981128	Created 
// AMO	191015	Added gzReference as base class (2.10.4)
//									
//******************************************************************************
class  gzLicenseManager :	public gzService, 
							public gzThread,
							public gzReference
{
public:

	GZ_BASE_EXPORT gzLicenseManager();

	GZ_BASE_EXPORT virtual ~gzLicenseManager();

	GZ_BASE_EXPORT gzVoid process();

	GZ_BASE_EXPORT gzVoid process(const gzArgumentParser &args,gzBool runAsService);

	GZ_BASE_EXPORT gzVoid debugMessage(const gzString &message);

	GZ_BASE_EXPORT gzBool run(gzBool waitForRunning = FALSE);
};

GZ_DECLARE_REFPTR(gzLicenseManager);

enum gzFeatureInfo
{
	GZ_FEATURE_OK,
	GZ_FEATURE_MISSING,
	GZ_FEATURE_NOT_ACTIVATED,
	GZ_FEATURE_APPLICATION_MASK_MISMATCH,
	GZ_FEATURE_USER_ROLE_MISMATCH,
	GZ_FEATURE_LICENSE_MISMATCH
};

//******************************************************************************
// Class	: gzFeature
//									
// Purpose  : Manage license features, applications and roles
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	070416	Created 
//									
//******************************************************************************
class  gzFeature : public gzThreadSafeReference
{
public:

	GZ_BASE_EXPORT virtual ~gzFeature();
	GZ_BASE_EXPORT	gzBool	useDeepCopy() { return FALSE; }	// Shallow share

	// Properties --------------------------

	GZ_PROPERTY_GET_EXPORT(	gzString,		Name,			GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzString,		Description,	GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzUInt32,		AppMask,		GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzUInt32,		RoleMask,		GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzString,		License,		GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzUInt16,		FeatureMask,	GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzBool,			Activated,		GZ_BASE_EXPORT);


	// Application Feature management ------------------

	GZ_BASE_EXPORT static gzVoid setFeature(	const gzString &	name,
												const gzString &	description,
												const gzUInt32		appMask,
												const gzUInt32		roleMask,
												const gzString &	license=GZ_EMPTY_STRING,
												const gzUInt16		featureMask=0);

	GZ_BASE_EXPORT static gzRefPointer<gzFeature> getFeature(const gzString &name );

	GZ_BASE_EXPORT static gzVoid removeFeature(	const gzString &name );

	GZ_BASE_EXPORT static gzVoid clearFeatures();

	GZ_BASE_EXPORT static gzVoid setActivated(const gzString &featureName , gzBool activated);

	GZ_BASE_EXPORT static gzArray<gzRefPointer<gzFeature> > getFeatures();

	// Application & Role --------------------------

	GZ_BASE_EXPORT static gzVoid setApplicationMask(gzUInt32 mask);
	GZ_BASE_EXPORT static gzUInt32 getApplicationMask();
	GZ_BASE_EXPORT static gzVoid setSystemRoleMask(gzUInt32 mask);
	GZ_BASE_EXPORT static gzUInt32 getSystemRoleMask();

	// User Utilities -----------------------------------

	GZ_BASE_EXPORT static gzBool hasAllowedFeature(const gzString &featureName,gzFeatureInfo *info=nullptr);
	GZ_BASE_EXPORT static gzInt32 getFeatureExpirationDays(const gzString &featureName);

	GZ_BASE_EXPORT static gzString getFeatureSetIdentification();
	GZ_BASE_EXPORT static gzVoid setFeatureSetIdentification(const gzString &string);

	GZ_BASE_EXPORT static gzBool readFeatures(const gzString &url,const gzString &elementName);
	GZ_BASE_EXPORT static gzBool writeFeatures(const gzString &url,const gzString &elementName,gzBool onlyActivated=TRUE,gzBool noDescriptions=FALSE);

	GZ_BASE_EXPORT static gzBool readFeatures(gzSerializeAdapter *adapter);
	GZ_BASE_EXPORT static gzBool writeFeatures(gzSerializeAdapter *adapter,gzBool onlyActivated=TRUE,gzBool noDescriptions=FALSE);

private:

	GZ_BASE_EXPORT gzFeature();

	friend class gzFeatureCleanup;

	static	gzRefDict<gzString,gzFeature>	s_featureDict;
	static	gzMutex							s_featureDictLocker;
	static	gzUInt32						s_applicationMask;
	static	gzUInt32						s_roleMask;
	static	gzString						s_identification;
};

// --- Utilities ----

#define GZ_DEBUG_WAIT gzLicense::splashLicenseText("Debug", "waiting")

#endif
