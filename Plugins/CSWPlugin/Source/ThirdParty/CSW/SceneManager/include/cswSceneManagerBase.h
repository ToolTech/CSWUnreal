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
// File			: cswSceneManagerBase.h
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

/*!	\file 
	\brief Base Settings

Blah
	
*/

#include "cswCommon.h"

//******************************************************************
// Version and DLL information for Windows DLLs
// We are using Gizmo3D as Win32 DLLs and need to activate CSW_XXX_DLL 
// for each package

// The static libraries are available upon request

#ifdef GZ_WINDOWS		// From Gizmo libs
#ifndef CSW_STATIC		// Default to use CSW as dlls or so
#define CSW_SM_DLL		// Define CSW_STATIC to use static libs
#endif
#endif // GZ_WINDOWS

#ifdef CSW_SM_DLL		// defined as dll
#ifdef CSW_SM_EXPORTS
#define CSW_SM_EXPORT	__declspec(dllexport)
#else
#define CSW_SM_EXPORT	__declspec(dllimport)
#endif
#else
#define CSW_SM_EXPORT
#endif

class  CSW_SM_EXPORT PathIDReference 
{
public:

	//! Default constructor, Creates unique instance hash value 
	PathIDReference(gzReference* ref, const gzUInt64 pathID) : m_address(ref), m_pathID(pathID) {}

	//! returns the hash value of your instance
	gzUInt32 hash() const { return (gzUInt32)gzPtr2Val(m_address)+(gzUInt32)m_pathID; }

	//! equality operator
	gzBool operator ==(const PathIDReference& right) const
	{
		return (m_address == right.m_address) && (m_pathID==right.m_pathID);
	}

private:

	const gzReference*	m_address;
	gzUInt64			m_pathID;

};

enum Activation
{
	ACTIVATION_INIT,
	ACTIVATION_OFF,
	ACTIVATION_ON
};

class  PathIDActivation : public gzReference
{
public:

	CSW_SM_EXPORT PathIDActivation() :m_propertyActivation(ACTIVATION_INIT) {}

	GZ_PROPERTY_EXPORT(Activation, Activation, CSW_SM_EXPORT);
};

// Constants --------------------------------------

const gzString CSW_META = "CSW";
const gzString BUILD_DATA = "build";
