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
// File			: gzSplit.h
// Module		: 
// Description	: Class definition of the gzSplit class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.211
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
// AMO	040830	Created file 	
//
//******************************************************************************
#ifndef __GZ_SPLIT
#define __GZ_SPLIT

/*!	\file 
	\brief Base definitions for a group node that splits rendering on recursive or shared traversals

*/

#include "gzGroup.h"
#include "gzLod.h"

class gzSplitInfo 
{
public:

	gzSplitInfo():renderTime(0),index(0){};

	gzDouble	renderTime;

	gzUInt32		index;

};


//******************************************************************************
// Class	: gzSplit
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040830	Created 
//									
//******************************************************************************
class gzSplit : public gzGroup
{
public:

	GZ_GRAPH_EXPORT gzSplit(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzSplit();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- shutdown some group traversals etc.. ------------------

	GZ_GRAPH_EXPORT virtual gzBool checkTraversePerChild() const override { return TRUE; }

	GZ_GRAPH_EXPORT gzBool	isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index , gzContext *context ) override;

	GZ_GRAPH_EXPORT gzVoid	debugOutputTraverse(gzString base , gzString anchor , gzDebugFlags features) override;

	GZ_GRAPH_EXPORT virtual gzVoid debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	
private:

	gzDynamicArray<gzSplitInfo>	m_splitInfo;

};

#endif
