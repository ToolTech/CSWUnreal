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
// File			: cswBuildInterface.h
// Module		: CSW StreamingMap Unreal
// Description	: Interface to build functions 
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
// AMO	241107	Created file 							(1.1.1)
//
//******************************************************************************
#pragma once

#include "gzNode.h"
#include "Engine/EngineTypes.h"

class UCSWSceneComponent;

struct BuildProperties
{
	// Use fastbuild for meshes as default
	bool fastBuild = true;

	// dont build any collisions. lets integrate ours
	bool buildSimpleCollision = false;

	// right now dont knwo what this affects
	bool simulatePhysics = false;

	// turn of collsion
	ECollisionEnabled::Type collision = ECollisionEnabled::NoCollision;
};

class cswResourceManager;

class IBuildInterface
{
public:

	virtual bool build(UCSWSceneComponent *parent,gzNode* buildItem, gzState *state, BuildProperties &buildProperties, cswResourceManager *resources)=0;
	virtual bool destroy(gzNode* destroyItem,cswResourceManager* resources) = 0;
};