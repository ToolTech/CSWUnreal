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
// File			: cswApplication.h
// Module		: cswSceneManager
// Description	: Definition of application for csw native
// Author		: Anders Modén		
// Product		: CSW 1.1.1
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
// AMO	240912	Created file 					(1.1.1)
//
//******************************************************************************
#pragma once

#include "cswSceneManagerBase.h"
#include "gzSystemLibrary.h"

//******************************************************************************
// Class	: cswApplication
//
// Purpose  : The SceneManager external application control
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	240912	Created		(1.1.1)
//									
//******************************************************************************
class cswApplication : public gzApplication
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswApplication();

	CSW_SM_EXPORT virtual ~cswApplication();

	
};

GZ_DECLARE_REFPTR(cswApplication);
