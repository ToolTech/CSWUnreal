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
// File			: gzImageManager_rgb.h
// Module		: 
// Description	: Class definition of the rgb format reader
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
// AMO	000308	Created file 	
//
//******************************************************************************
#ifndef __GZ_IMAGE_RGB_H__
#define __GZ_IMAGE_RGB_H__

/*!	\file 
	\brief Base definitions of a RGB bitmap reader

*/
#include "gzImage.h"

class gzImageManager_rgb : public gzImageManager	
{
public:

	GZ_IMAGE_EXPORT gzImageManager_rgb();

	GZ_IMAGE_EXPORT virtual ~gzImageManager_rgb(){};

	GZ_IMAGE_EXPORT virtual gzImage	*loadImage(gzSerializeAdapter *adapter) override;

	//GZ_IMAGE_EXPORT virtual gzBool  saveImage(gzImage *image , gzSerializeAdapter *adapter) override;

	GZ_IMAGE_EXPORT virtual gzString	getExtensions() override;

	GZ_IMAGE_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_IMAGE_EXPORT virtual gzBool		canSave() override;
};

#endif
