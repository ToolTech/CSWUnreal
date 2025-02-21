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
// File			: gzRecursiveSwitch.h
// Module		: 
// Description	: Class definition of the gzRecursiveSwitch class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.223
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
#ifndef __GZ_RECURSIVE_SWITCH_H__
#define __GZ_RECURSIVE_SWITCH_H__

/*!	\file 
	\brief Base definitions for Recursive Switches and how to select childs per recursive level

*/


#include "gzGroup.h"


class gzRecursiveSwitchLevel
{
public:
	gzRecursiveSwitchLevel(gzBool enable=TRUE,gzUInt32 min=0,gzUInt32 max=0xfffffffful):m_min_depth(min),m_max_depth((gzFloat)max),m_enabled(enable){};

	virtual ~gzRecursiveSwitchLevel(){};

	gzUInt32	m_min_depth;
	gzFloat		m_max_depth;
	gzBool		m_enabled;
};

//******************************************************************************
// Class	: gzRecursiveSwitch
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
class gzRecursiveSwitch : public gzGroup
{
public:
	GZ_GRAPH_EXPORT gzRecursiveSwitch(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzRecursiveSwitch(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- gzRecursiveSwitch commands ----------------------------------------

	GZ_GRAPH_EXPORT gzVoid setRecursiveDepth(gzUInt32 index , gzBool enable , gzUInt32 min = 0 , gzUInt32 max = 0xfffffffful);

	GZ_GRAPH_EXPORT gzVoid useLevels(gzBool on);

	GZ_GRAPH_EXPORT gzBool useLevels();

	GZ_GRAPH_EXPORT gzDynamicArray<gzRecursiveSwitchLevel> & getLevels();

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
	
	gzDynamicArray<gzRecursiveSwitchLevel>	m_levels;
	gzBool									m_useLevels:1;
};

#endif
