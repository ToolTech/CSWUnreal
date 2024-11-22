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
// File			: gzSeedSwitch.h
// Module		: 
// Description	: Class definition of the gzSeedSwitch class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.200
//		
//
//			
// NOTE:	Gizmo3D is a high performance 3D Scene Graph and effect visualisation 
//			C++ toolkit for Linux, Mac OS X, Windows, Android, iOS and HoloLens for  
//			usage in Game or VisSim development.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030312	Created file 
//
//******************************************************************************
#ifndef __GZ_SEED_SWITCH_H__
#define __GZ_SEED_SWITCH_H__

/*!	\file 
	\brief Base definitions for Seed Switches and how to select childs per seed value

*/


#include "gzGroup.h"

class gzSeedSwitchProbability
{
public:

	gzSeedSwitchProbability():probability(GZ_DOUBLE_ONE){};

	gzDouble probability;
};


//******************************************************************************
// Class	: gzSeedSwitch
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990516	Created 
//									
//******************************************************************************
class gzSeedSwitch : public gzGroup
{
public:
	GZ_GRAPH_EXPORT gzSeedSwitch(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzSeedSwitch(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- gzSeedSwitch commands ----------------------------------------

	GZ_GRAPH_EXPORT gzVoid setSeedProbability(gzUInt32 index , gzDouble probability=1.0);

	GZ_GRAPH_EXPORT gzVoid useExclusive(gzBool on);

	// ----------- gzGroup interface ------------------------------------

	GZ_GRAPH_EXPORT virtual gzBool	isChildOrderDependant() const override;

	GZ_GRAPH_EXPORT virtual gzBool	checkTraversePerChild() const override;

	// ---------- Action Interface --------------------------------------
	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index, gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Debug Inteface ----------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

private:
	
	gzDynamicArray<gzSeedSwitchProbability>	m_probabilites;
	gzBool									m_useExclusive:1;
};

#endif
