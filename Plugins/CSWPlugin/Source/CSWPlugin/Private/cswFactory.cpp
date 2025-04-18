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
// Author		: Anders Mod�n		
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
// AMO	241107	Created file 							(1.1.1)
//
//******************************************************************************
#include "cswFactory.h"
#include <gzPerformance.h>

GZ_DECLARE_TYPE_CHILD(gzObject, cswFactory, "cswFactory");

//gzMutex cswFactory::s_factoryLock;
//
//gzRefDict< gzString, cswFactory > cswFactory::s_factoryLookup;

gzMutex s_factoryLock;

gzRefDict< gzString, cswFactory > s_factoryLookup;

cswFactory::cswFactory()									// make sure its initialized
{
	GZ_BODYGUARD(s_factoryLock);
}

UCSWSceneComponent* cswFactory::newObject(USceneComponent* parent,gzNode* node, EObjectFlags Flags , UObject* Template , bool bCopyTransientsFromClassDefaults , FObjectInstancingGraph* InInstanceGraph )
{
	GZ_INSTRUMENT_NAME("cswFactory::newObject");

	gzType* type = node->getType();

	cswFactory* factory;

	while (type)
	{
		factory = getFactory(type->getName());

		if (!factory)
		{
			type = type->getParent();
			continue;
		}

		return factory->newObjectInstance(parent, node, Flags, Template, bCopyTransientsFromClassDefaults, InInstanceGraph);
	}
	
	GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to get CSW factory for type (%s)", node->getTypeName());

	return nullptr;
}

gzReference* cswFactory::preBuildReference(gzNode* node, const gzUInt64& pathID, gzGroup* parent, const gzUInt64& parentPathID, gzState* state)
{
	GZ_INSTRUMENT_NAME("cswFactory::preBuildReference");

	gzType* type = node->getType();

	cswFactory* factory;

	while (type)
	{
		factory = getFactory(type->getName());

		if (!factory)
		{
			type = type->getParent();
			continue;
		}

		return factory->preBuildReferenceInstance(node,pathID,parent,parentPathID,state);
	}

	GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to get CSW factory for type (%s)", node->getTypeName());

	return nullptr;
}

gzVoid cswFactory::preDestroyReference(gzNode* node, const gzUInt64& pathID, gzReference* userdata)
{
	GZ_INSTRUMENT_NAME("cswFactory::preDestroyReference");

	gzType* type = node->getType();

	cswFactory* factory;

	while (type)
	{
		factory = getFactory(type->getName());

		if (!factory)
		{
			type = type->getParent();
			continue;
		}

		return factory->preDestroyReferenceInstance(node,pathID,userdata);
	}

	GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to get CSW factory for type (%s)", node->getTypeName());
}


gzBool cswFactory::registerFactory(const gzString& className, cswFactory* factory)
{
	GZ_BODYGUARD(s_factoryLock);

	if (s_factoryLookup.find(className))
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "Multiple factory registrations for class (%s)", className);
		return FALSE;
	}

	s_factoryLookup.enter(className, factory);

	return TRUE;
}

gzBool cswFactory::unregisterFactory(const gzString& className)
{
	GZ_BODYGUARD(s_factoryLock);

	if (!s_factoryLookup.find(className))
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "Factory not regisstered for class (%s)", className);
		return FALSE;
	}

	s_factoryLookup.remove(className);

	return TRUE;
}

cswFactory * cswFactory::getFactory(const gzString& className)
{
	GZ_BODYGUARD(s_factoryLock);

	return s_factoryLookup.find(className);
}

gzReference* cswFactory::preBuildReferenceInstance(gzNode* node, const gzUInt64& pathID, gzGroup* parent, const gzUInt64& parentPathID, gzState* state)
{
	// Default do nothing
	return nullptr;
}

gzVoid cswFactory::preDestroyReferenceInstance(gzNode* node, const gzUInt64& pathID, gzReference* userdata)
{
	// Default do nothing
}
