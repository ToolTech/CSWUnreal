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
// File			: cswUEUtility.h
// Module		: CSW StreamingMap Unreal
// Description	: Utilities for UE from GizmoSDK
// Author		: Anders Modén		
// Product		: CSW 1.1.2
//		
//
//			
// NOTE:	CSW (Common Synthetic World) is a simulation and presentation
//			framework for large scale digital twins on multiple platforms
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	241107	Created file 					(1.1.1)
//
//******************************************************************************

#pragma once

// UE Includes

#include "Engine/Texture2D.h"


// CSW/Gizmo includes
#include "gzGraphLibrary.h"

//! Create a UTexture2D from a gzImage 
CSWPLUGIN_API UTexture2D* cswUETexture2DFromImage(gzImage* image);

CSWPLUGIN_API void cswScreenMessage(const gzString& message,const gzInt32 &line=-1,const FColor &color=FColor::Yellow);

// Utility classes

