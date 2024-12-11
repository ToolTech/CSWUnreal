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
// File			: cswFactory.h
// Module		: CSW StreamingMap Unreal
// Description	: Interface to Factory builders
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
class UCSWSceneComponent;

class cswFactory : public gzObject
{
public:

	// Type info
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSWPLUGIN_API);			// Each factory has a specific type and hierarchy

	CSWPLUGIN_API cswFactory();									// make sure its initialized

	CSWPLUGIN_API static UCSWSceneComponent* newObject(USceneComponent* parent,gzNode* node, EObjectFlags Flags = RF_NoFlags, UObject* Template = nullptr, bool bCopyTransientsFromClassDefaults = false, FObjectInstancingGraph* InInstanceGraph = nullptr);

	CSWPLUGIN_API static gzBool registerFactory(const gzString &className, cswFactory *factory);

	CSWPLUGIN_API static gzBool unregisterFactory(const gzString& className);

	CSWPLUGIN_API static cswFactory* getFactory(const gzString& className);
	
	// factory uses clone to create instance and must bve derived 
	CSWPLUGIN_API virtual gzReference* clone() const = 0;

protected:

	CSWPLUGIN_API virtual UCSWSceneComponent* newObjectInstance(USceneComponent* parent,gzNode *node, EObjectFlags Flags, UObject* Template, bool bCopyTransientsFromClassDefaults , FObjectInstancingGraph* InInstanceGraph ) = 0;

private:

	

	static gzMutex s_factoryLock;

	static gzRefDict< gzString, cswFactory>	s_factoryLookup;
};

GZ_DECLARE_REFPTR(cswFactory);