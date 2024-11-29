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
#include "cswFactory.h"

GZ_DECLARE_TYPE_CHILD(gzObject, cswFactory, "cswFactory");

gzMutex cswFactory::s_factoryLock;

gzDict< gzUInt32CompareInterface, gzVoid> cswFactory::s_factoryLookup;


USceneComponent* cswFactory::newObject(gzNode* node, USceneComponent* parent)
{
	gzUInt32 factoryID = getFactoryLookup(gzString(node->getTypeName()).hash());

	if (!factoryID)
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to get CSW factory ID for type (%s)", node->getTypeName());
		return nullptr;
	}

	cswFactoryPtr factory = gzDynamic_Cast<cswFactory>(gzObject::createFactoryObject(factoryID));

	if (!factory)
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to get CSW factory for type (%s)", node->getTypeName());
		return nullptr;
	}

	return factory->newObjectInstance(node,parent);
}

gzBool cswFactory::registerFactoryLookup(const gzUInt32& in, const gzUInt32& out)
{
	GZ_BODYGUARD(s_factoryLock);

	if (s_factoryLookup.find(in))
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "Multiple factory registrations for id (%d)", in);
		return FALSE;
	}

	s_factoryLookup.enter(in, gzVal2Ptr(out));

	return TRUE;
}

gzBool cswFactory::unregisterFactoryLookup(const gzUInt32& in)
{
	GZ_BODYGUARD(s_factoryLock);

	if (!s_factoryLookup.find(in))
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "Factory not regisstered for id (%d)", in);
		return FALSE;
	}

	s_factoryLookup.remove(in);

	return TRUE;
}

gzUInt32 cswFactory::getFactoryLookup(const gzUInt32& in)
{
	GZ_BODYGUARD(s_factoryLock);

	return (gzUInt32)gzPtr2Val(s_factoryLookup.find(in));
}