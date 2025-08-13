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
// File			: gzImageManager_png.h
// Module		: 
// Description	: Class definition of the png format reader
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
// AMO	011204	Created file 	
// AMO	241007	Added basic save functionality						(2.12.189)
//
//******************************************************************************
#ifndef __GZ_IMAGE_PNG_H__
#define __GZ_IMAGE_PNG_H__

/*!	\file 
	\brief Base definitions of a PNG (Portable Network Graphics) bitmap reader

*/

#include "gzImage.h"
#include "gzSerialize.h"


class gzImageManager_png : public gzImageManager	
{
public:

	GZ_IMAGE_EXPORT gzImageManager_png();

	GZ_IMAGE_EXPORT virtual ~gzImageManager_png(){};

	GZ_IMAGE_EXPORT virtual gzImage	*loadImage(gzSerializeAdapter *adapter) override;

	GZ_IMAGE_EXPORT virtual gzBool  saveImage(gzImage *image , gzSerializeAdapter *adapter) override;

	GZ_IMAGE_EXPORT virtual gzString	getExtensions() override;

	GZ_IMAGE_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_IMAGE_EXPORT virtual gzBool		canSave() override;
};


#endif

