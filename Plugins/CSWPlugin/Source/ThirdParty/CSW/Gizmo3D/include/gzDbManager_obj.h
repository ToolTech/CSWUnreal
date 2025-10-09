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
// File			: gzDbManager_obj.h
// Module		: 
// Description	: Class definition of the OBJ format
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.275
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
// AMO	121010	Created file 									(2.6.16)
//
//******************************************************************************
#ifndef __GZ_DB_OBJ_H__
#define __GZ_DB_OBJ_H__

/*!	\file 
	\brief Base definitions of a OBJ database 

*/

#include "gzNode.h"

// Current OBJ format version
const gzUInt32	GZ_OBJ_VERSION=100;

//******************************************************************************
// Class	: gzDbManager_obj
//									
// Purpose  : Reader/Writer for OBJ file format
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	010508	Created 
//									
//******************************************************************************
class gzDbManager_obj : public gzDbManager	
{
public:

	GZ_DB_EXPORT gzDbManager_obj();
	GZ_DB_EXPORT virtual ~gzDbManager_obj();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	//GZ_DB_EXPORT virtual gzBool		saveDB(gzNode *node , gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;

protected:

	GZ_DB_EXPORT virtual gzVoid		registerManager(const gzString &extension) override;
};

#endif // __GZ_DB_OBJ_H__

