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
// Description	: Implementation if factory for cswTransform
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
#include "cswTransform.h"

//---------------------- cswTransformFactory -------------------------------------

class cswTransformFactory : public cswFactory
{
public:

	GZ_DECLARE_TYPE_INTERFACE;

	virtual gzReference* clone() const
	{
		return new cswTransformFactory(*this);
	}

	virtual USceneComponent* newObjectInstance(gzNode* node, USceneComponent* parent) override
	{
		UCSWTransform *trans = NewObject<UCSWTransform>(parent, node->getName().getWideString());

		trans->RegisterComponent();

		trans->AttachToComponent(parent, FAttachmentTransformRules::KeepRelativeTransform);

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
		// register factory 
		m_id=gzObject::registerFactoryObject(new cswTransformFactory);

		cswFactory::registerFactoryLookup(gzString("gzTransform").hash(), m_id);
	}

	gzBool	releaseRefs() 
	{ 
		if (m_id)
		{
			cswFactory::unregisterFactoryLookup(gzString("gzTransform").hash());

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
