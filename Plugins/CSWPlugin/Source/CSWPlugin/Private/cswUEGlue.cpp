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
// File			: cswUEGlue.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Glue Between Unreal CSW and GizmoSDK callbacks
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
// AMO	241107	Created file 					(1.1.1)
//
//******************************************************************************


#include "cswUEGlue.h"
#include "gzImageLibrary.h"

//-------------------- cswToUnrealMessageReceiver --------------------------------------------

cswToUnrealMessageReceiver::cswToUnrealMessageReceiver()
{
	gzMessage::addMessageReceiver(this);
}

cswToUnrealMessageReceiver::~cswToUnrealMessageReceiver()
{
	gzMessage::removeMessageReceiver(this);
}

const gzString CSW_SENDER = "CSW";

DEFINE_LOG_CATEGORY(CSW);

gzVoid cswToUnrealMessageReceiver::onMessage(const gzString& sender, gzMessageLevel level, const char* message)
{
	if (sender == CSW_SENDER)
		return;

	switch (level & GZ_MESSAGE_LEVEL_MASK_STD)
	{
		case GZ_MESSAGE_FATAL:
			UE_LOG(CSW, Fatal, TEXT("%s"), gzString(message).getWideString());
			break;

		case GZ_MESSAGE_ASSERT:
			UE_LOG(CSW, Error, TEXT("%s"), gzString(message).getWideString());
			break;

		case GZ_MESSAGE_WARNING:
			UE_LOG(CSW, Warning, TEXT("%s"), gzString(message).getWideString());
			break;

		case GZ_MESSAGE_NOTICE:
			UE_LOG(CSW, Display, TEXT("%s"), gzString(message).getWideString());
			break;

		case GZ_MESSAGE_DEBUG:
			UE_LOG(CSW, Log, TEXT("%s"), gzString(message).getWideString());
			break;

		case GZ_MESSAGE_DETAIL_DEBUG:
		default:
			UE_LOG(CSW, Verbose, TEXT("%s"), gzString(message).getWideString());
			break;
	}
}

//------------------- cswFromUnrealMessageReceiver -------------------------------------------

cswFromUnrealMessageReceiver::cswFromUnrealMessageReceiver()
{
	check(GLog);
	GLog->AddOutputDevice(this);
}

cswFromUnrealMessageReceiver::~cswFromUnrealMessageReceiver()
{
	if (GLog != nullptr)
	{
		GLog->RemoveOutputDevice(this);
	}
}

void cswFromUnrealMessageReceiver::Serialize(const TCHAR* Message, ELogVerbosity::Type Verbosity, const class FName& Category)
{
	// Skip route of our own messages
	if (Category == CSW.GetCategoryName())
		return;

	switch (Verbosity)
	{
		case ELogVerbosity::Fatal:
			GZMESSAGE(CSW_SENDER,GZ_MESSAGE_FATAL, Message);
			break;

		case ELogVerbosity::Error:
			GZMESSAGE(CSW_SENDER,GZ_MESSAGE_ASSERT, Message);
			break;

		case ELogVerbosity::Warning:
			GZMESSAGE(CSW_SENDER,GZ_MESSAGE_WARNING, Message);
			break;

		case ELogVerbosity::Display:
			GZMESSAGE(CSW_SENDER,GZ_MESSAGE_NOTICE, Message);
			break;

		case ELogVerbosity::Log:
			GZMESSAGE(CSW_SENDER,GZ_MESSAGE_DEBUG, Message);
			break;

		case ELogVerbosity::Verbose:
		case ELogVerbosity::VeryVerbose:
		default:
			GZMESSAGE(CSW_SENDER,GZ_MESSAGE_DETAIL_DEBUG, Message);
			break;
	}
}

bool  cswFromUnrealMessageReceiver::CanBeUsedOnMultipleThreads() const
{
	return true;
}

//---------------------------------------------------------------------------------------------

gzCleanupReference _GZ_Receiver = new cswToUnrealMessageReceiver;
gzCleanupReference _UE_Receiver = new cswFromUnrealMessageReceiver;

gzUInt32 _counter = 0;
gzMutex _locker;

gzVoid cswInitializeUnrealGlue()
{
	GZ_BODYGUARD(_locker);

	if (!_counter)
	{
		_GZ_Receiver = new cswToUnrealMessageReceiver;
		_UE_Receiver = new cswFromUnrealMessageReceiver;

		gzInitializeImageManagers();
	}

	_counter++;
}

gzVoid cswUnInitializeUnrealGlue()
{
	GZ_BODYGUARD(_locker);

	if (_counter)
	{
		_counter--;

		if (!_counter)
		{
			gzUninitializeImageManagers();

			_GZ_Receiver = nullptr;
			_UE_Receiver = nullptr;
		}
	}
}

