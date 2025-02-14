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
// File			: gzDbManager_3ds.h
// Module		: 
// Description	: Class definition of the 3ds db format
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.220
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
// AMO	990401	Created file 	
//
//******************************************************************************
#ifndef __GZ_DB_3DS_H__
#define __GZ_DB_3DS_H__

/*!	\file 
	\brief Base definitions of a 3DS (3D Studio) database 

*/

#include "gzNode.h"

// UserData Db INFO attributes
const gzString GZ_DB_INFO_TYPE_3DS	="3ds";


//******************************************************************************
// Class	: -
//									
// Purpose  : - 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981104	Created 
//									
//******************************************************************************
class gzDbManager_3ds : public gzDbManager	
{
public:

	GZ_DB_EXPORT gzDbManager_3ds();

	GZ_DB_EXPORT virtual ~gzDbManager_3ds();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	//GZ_DB_EXPORT virtual gzBool		saveDB(gzNode *node ,gzSerializeAdapter *adapter);

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;
};

GZ_DB_EXPORT gzVoid gzSet3dsBaseTransform(const gzMatrix4 &transform);

#endif
