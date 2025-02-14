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
// File			: cswTransformFactory.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Implementation if factory for cswTransform
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
// AMO	241107	Created file 							(1.1.1)
//
//******************************************************************************
#include "cswFactory.h"
#include "Builders/cswTransform.h"

//---------------------- cswTransformFactory -------------------------------------

class cswTransformFactory : public cswFactory
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	virtual gzReference* clone() const
	{
		return new cswTransformFactory(*this);
	}

	virtual UCSWSceneComponent* newObjectInstance(USceneComponent* parent,gzNode* node, EObjectFlags Flags, UObject* Template, bool bCopyTransientsFromClassDefaults, FObjectInstancingGraph* InInstanceGraph) override
	{
		UCSWTransform *trans = NewObject<UCSWTransform>(parent, node->getName().getWideString(),Flags,Template,bCopyTransientsFromClassDefaults,InInstanceGraph);

		return trans;
	}
};

GZ_DECLARE_TYPE_CHILD(cswFactory, cswTransformFactory, "cswTransformFactory");

//---------------------- cswTransformFactoryRegistrar -------------------------------------

class cswTransformFactoryRegistrar : public gzReference
{
public:

	cswTransformFactoryRegistrar()
	{
		cswFactoryPtr factory = new cswTransformFactory;

		// register factory for object serialize
		m_id=gzObject::registerFactoryObject(factory);

		// register factory for component creation
		cswFactory::registerFactory("gzTransform", factory);
	}

	gzBool	releaseRefs() 
	{ 
		if (m_id)
		{
			cswFactory::unregisterFactory("gzTransform");

			// release factory early
			gzObject::unregisterFactory(m_id);
			m_id = 0;
		}

		return TRUE; 
	}

	~cswTransformFactoryRegistrar()
	{
		// If not handled by releaseRefs earlier
		releaseRefs();
	}

private:

	gzUInt32 m_id;
};

gzCleanupReference cleanUpTransformFactory(new cswTransformFactoryRegistrar, GZ_CLEANUP_MODULES);
