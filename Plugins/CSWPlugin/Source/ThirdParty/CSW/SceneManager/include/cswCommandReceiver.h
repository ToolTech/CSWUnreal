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
// File			: cswSceneManager.h
// Module		: cswSceneManager
// Description	: Management of the SceneManager library
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

#include "cswCommandBuffer.h"

class cswSceneManager;

// Disable clear and destroy for gzList<cswSceneManager>
template <> inline gzVoid gzList<cswSceneManager>::clearAndDestroy(){}

//******************************************************************************
// Class	: cswCommandReceiverInterface
//
// Purpose  : Utility class for command receiver from SceneManager
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
class cswCommandReceiverInterface
{
public:

	CSW_SM_EXPORT	virtual ~cswCommandReceiverInterface();

	// ------------ the receiver --------------------
	CSW_SM_EXPORT	virtual gzVoid onCommand(cswSceneManager *manager,cswCommandBuffer* buffer) = 0;

private:

	friend class cswSceneManager;

	gzList<cswSceneManager>	m_sources;
};
