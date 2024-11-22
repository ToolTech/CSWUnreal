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
// File			: gzImageManager_bmp.h
// Module		: 
// Description	: Class definition of the bmp format reader
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.200
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
// AMO	990301	Created file 	
//
//******************************************************************************
#ifndef __GZ_IMAGE_BMP_H__
#define __GZ_IMAGE_BMP_H__

/*!	\file 
	\brief Base definitions of a BMP bitmap reader

*/
#include "gzImage.h"

class gzImageManager_bmp : public gzImageManager	
{
public:

	GZ_IMAGE_EXPORT gzImageManager_bmp();

	GZ_IMAGE_EXPORT virtual ~gzImageManager_bmp(){};

	GZ_IMAGE_EXPORT virtual gzImage	*	loadImage(gzSerializeAdapter *adapter) override;

	GZ_IMAGE_EXPORT virtual gzBool		saveImage(gzImage *image , gzSerializeAdapter *adapter) override;

	GZ_IMAGE_EXPORT virtual gzString	getExtensions() override;

	GZ_IMAGE_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_IMAGE_EXPORT virtual gzBool		canSave() override;

protected:

	gzImage *getImageVersion3(gzSerializeAdapter *adapter);
	gzImage *getImageVersion1(gzSerializeAdapter *adapter);
};




#endif
