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
// File			: cswCullTraverseAction.h
// Module		: cswSceneManager
// Description	: Definition of external cull control
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

//******************************************************************************
// Class	: cswCullTraverseAction
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
class cswCullTraverseAction : public gzTraverseAction
{
public:

	CSW_SM_EXPORT cswCullTraverseAction();

	CSW_SM_EXPORT virtual ~cswCullTraverseAction();

	CSW_SM_EXPORT gzBool isTransformTraverser()		const		override { return TRUE; }
	CSW_SM_EXPORT gzBool isRenderTraverser()		const		override { return FALSE; }
	CSW_SM_EXPORT gzBool isIntersectorTraverser()	const		override { return FALSE; }


	CSW_SM_EXPORT gzVoid initTraversal(gzContext* context) override;

	CSW_SM_EXPORT gzBool checkBoundary(gzContext* context, gzNode* node) override;

	GZ_PROPERTY_EXPORT(gzBool, OmniTraverser, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzDouble, RenderTime, CSW_SM_EXPORT);

};

GZ_DECLARE_REFPTR(cswCullTraverseAction);
