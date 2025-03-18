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
// File			: cswUESceneManager.h
// Module		: CSW StreamingMap Unreal
// Description	: Interface to custom scenemanager
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
// AMO	250318	Created file 							(1.1.3)
//
//******************************************************************************
#pragma once

#include "cswSceneManager.h"

class cswUESceneManager : public cswSceneManager
{
public:

	virtual gzReference*	preBuildReference(gzNode* node, const gzUInt64& pathID, gzGroup* parent, const gzUInt64& parentPathID, gzState* state) override;
	virtual gzVoid			preDestroyReference(gzNode* node, const gzUInt64& pathID, gzReference* userdata) override;
};

GZ_DECLARE_REFPTR(cswUESceneManager);
