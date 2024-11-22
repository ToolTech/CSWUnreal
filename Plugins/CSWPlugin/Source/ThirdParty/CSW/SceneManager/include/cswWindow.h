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
// File			: cswWindow.h
// Module		: cswSceneManager
// Description	: Definition of debug viewer for csw native
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
// Class	: cswWindow
//
// Purpose  : The SceneManager
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
class cswWindow : public gzWindow
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswWindow(const gzString& name = "CSW", gzWindowHandle parent = NULL, gzGraphicsFormat* format = NULL, gzBool activateWindow = TRUE);

	CSW_SM_EXPORT virtual ~cswWindow();

	CSW_SM_EXPORT gzVoid setCamera(const gzCameraPtr& camera) override;

protected:

	CSW_SM_EXPORT gzBool onKey(gzKeyValue key, gzKeyState keystate, gzInt32 mouse_x, gzInt32 mouse_y) override;

private:

	gzInputInterface* m_input;
};

GZ_DECLARE_REFPTR(cswWindow);
