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
// File			: cswFactory.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Implementation basics of cswFactory
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
#include "cswUESceneManager.h"
#include "cswFactory.h"

// Called in EDIT LOCK
gzReference* cswUESceneManager::preBuildReference(gzNode* node, const gzUInt64& pathID, gzGroup* parent, const gzUInt64& parentPathID, gzState* state)
{
	// Route pre build into factories
	return cswFactory::preBuildReference(node, pathID, parent, parentPathID, state);
}

// Called in EDIT LOCK
gzReference* cswUESceneManager::updateReference(gzNode* node, const gzUInt64& pathID, gzGroup* parent, const gzUInt64& parentPathID, gzState* state, gzReference* userdata)
{
	// Route update into factories
	return cswFactory::updateReference(node, pathID, parent, parentPathID, state , userdata);
}

// Called in EDIT LOCK
gzVoid cswUESceneManager::preDestroyReference(gzNode* node, const gzUInt64& pathID, gzReference* userdata)
{
	// Route pre destroy into factories
	cswFactory::preDestroyReference(node, pathID, userdata);
}
