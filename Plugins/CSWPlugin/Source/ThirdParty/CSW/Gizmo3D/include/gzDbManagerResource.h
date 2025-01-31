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
// File			: gzDbManagerResource.h
// Module		: 
// Description	: Common resource manager
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.211
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
// AMO	120614	Created file 	(2.6.8)
//
//******************************************************************************
#ifndef __GZ_DB_MANAGER_RESOURCE_H__
#define __GZ_DB_MANAGER_RESOURCE_H__

/*!	\file 
	\brief Base definitions of a resource manager

*/

#include "gzSerialize.h"

const gzString	GZ_URLBASE_RES		= "res:";	// subfile name resource
const gzString	GZ_RES_EXTENSION	= "res";

class gzDbManagerResource : public gzSerializeURLManagerInterface
{
public:
	gzDbManagerResource();
	virtual ~gzDbManagerResource();

	virtual gzSerializeAdapter *getURLAdapter(const gzString &url,gzSerializeAction action,gzSerializeAdapterFlags flags, const gzString &password, gzString *errorString,gzSerializeAdapterError *errorType) override;

	virtual gzBool getURLBaseEncoding(const gzString& _url, gzBool& _isAbsolute, gzString& _urlBase, gzString& _defaultPath, gzString& _urlName, gzString& _urlAttributes, gzBool& _syntax_OK) override;

	static gzVoid registerResourceManager();
	static gzVoid unregisterResourceManager();

protected:

	static gzRefPointer<gzDbManagerResource> s_manager;
};

#endif //__GZ_DB_MANAGER_RESOURCE_H__

