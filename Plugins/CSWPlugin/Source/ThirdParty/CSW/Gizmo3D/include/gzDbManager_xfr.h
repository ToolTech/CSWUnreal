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
// File			: gzDbManager_xfr.h
// Module		: 
// Description	: Class definition of the XFrog xfr format loader
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.306
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
// AMO	091109	Created file 	
//
//******************************************************************************
#ifndef __GZ_DB_XFR_H__
#define __GZ_DB_XFR_H__

/*!	\file 
	\brief Base definitions of a XFR database 

*/

#include "gzGroup.h"

class gzDbManager_xfr : public gzDbManager	
{
public:

	GZ_DB_EXPORT gzDbManager_xfr();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	//GZ_DB_EXPORT virtual gzBool		saveDB(gzNode *node ,gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;

};




#endif
