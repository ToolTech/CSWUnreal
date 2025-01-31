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
// File			: gzDbManager_sba.h
// Module		: 
// Description	: Class definition of the native RapidMapping format from SBD
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
// AMO	080512	Created file 	
//
//******************************************************************************
#ifndef __GZ_DB_SBA_H__
#define __GZ_DB_SBA_H__

/*!	\file 
	\brief Basic natie reader of the RapidMapping format from SAAB Dynamics (Vricon) 

*/

#include "gzNode.h"

// UserData Db INFO attributes
const gzString GZ_DB_INFO_TYPE_SBA	="sba";

// Forward decl..

class gzDbManager_sba_url;

//******************************************************************************
// Class	: gzDbManager_sba
//									
// Purpose  : Reader for native RapidMapping format (zip files)
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	121129	Created 
//									
//******************************************************************************
class gzDbManager_sba : public gzDbManager	
{
public:

	GZ_DB_EXPORT gzDbManager_sba();
	GZ_DB_EXPORT virtual ~gzDbManager_sba();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;

protected:

	GZ_DB_EXPORT virtual gzVoid		registerManager(const gzString &extension) override;

private:

	static gzDbManager_sba_url * s_urlManager;
};

#endif //__GZ_DB_SBA_H__
