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
// File			: cswUETypes.h
// Module		: CSW StreamingMap Unreal
// Description	: Utilities for UE from GizmoSDK
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

#pragma once

#include "gzBaseLibrary.h"


class CSWPathIdentyIndex
{
public:

	CSWPathIdentyIndex(gzNode* _item, const gzUInt64& _pathID) :item(_item), pathID(_pathID) {};

	gzUInt32	hash() const
	{
		return (gzUInt32)(gzPtr2Val(item) + pathID);
	}

	bool operator==(const CSWPathIdentyIndex& right)
	{
		return item == right.item && pathID == right.pathID;
	}

	gzNode* item;

	gzUInt64 pathID;
};

typedef gzNode* InstanceAddress;