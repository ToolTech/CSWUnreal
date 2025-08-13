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
// File			: gzDbManager_flt.h
// Module		: 
// Description	: Class definition of the flt format
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.262
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
#ifndef __GZ_DB_FLT_H__
#define __GZ_DB_FLT_H__

#include "gzNode.h"

/*!	\file 
	\brief Base definitions of a Multigen OpenFlight database 

*/

// UserData Db INFO attributes
const gzString GZ_DB_INFO_TYPE_OPENFLIGHT	="flt";


//************************ OpenFlight Loader ***********************************

class gzDbManager_flt : public gzDbManager 
{
public:

	GZ_DB_EXPORT					gzDbManager_flt();

	GZ_DB_EXPORT virtual			~gzDbManager_flt();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	//GZ_DB_EXPORT virtual gzBool		saveDB(gzNode *node ,gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;
};

class gzDFADFlightEncoder : public gzReference
{
public:

	virtual gzIntersectMaskValue encodeIntersectMask(gzInt16 featureID , gzInt16 surfaceID)=0;

	static gzVoid setEncoder(gzDFADFlightEncoder *encoder);

	static gzRefPointer<gzDFADFlightEncoder> getEncoder();

private:

	static gzGuard< gzRefPointer<gzDFADFlightEncoder> > s_encoder;

};

#endif
