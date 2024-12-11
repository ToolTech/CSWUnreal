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
// File			: cswUEGlue.h
// Module		: CSW StreamingMap Unreal
// Description	: Glue Between Unreal CSW and GizmoSDK
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

// UE Includes
#include "CoreMinimal.h"
#include "Misc/OutputDevice.h"

// CSW/Gizmo includes
#include "gzBaseLibrary.h"

DECLARE_LOG_CATEGORY_EXTERN(CSW, Log, All);

//------------------------ cswToUnrealMessageReceiver ------------------------------------------

CSWPLUGIN_API class cswToUnrealMessageReceiver : public gzMessageReceiverInterface, public gzReference
{
public:

	cswToUnrealMessageReceiver();

	~cswToUnrealMessageReceiver();

protected:

	virtual gzVoid onMessage(const gzString& sender, gzMessageLevel level, const char* message) override;
};

//----------------------- cswFromUnrealMessageReceiver ---------------------------------------

CSWPLUGIN_API class cswFromUnrealMessageReceiver : public FOutputDevice, public gzReference
{
public:
	cswFromUnrealMessageReceiver();

	~cswFromUnrealMessageReceiver();
	

protected:

	virtual void Serialize(const TCHAR* Message, ELogVerbosity::Type Verbosity, const class FName& Category) override;

	virtual bool CanBeUsedOnMultipleThreads() const override;

};

CSWPLUGIN_API gzVoid cswInitializeUnrealGlue();
CSWPLUGIN_API gzVoid cswUnInitializeUnrealGlue();