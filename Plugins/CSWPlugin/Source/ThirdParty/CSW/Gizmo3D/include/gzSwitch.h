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
// File			: gzSwitch.h
// Module		: 
// Description	: Class definition of the gzSwitch class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.201
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
// AMO	990511	Created file 	
//
//******************************************************************************
#ifndef __GZ_SWITCH_H__
#define __GZ_SWITCH_H__

/*!	\file 
	\brief Base definitions for switch nodes

*/


#include "gzGroup.h"

const gzUInt32 GZ_SWITCH_ALL=0xfffffffful;
const gzUInt32 GZ_SWITCH_NONE=0xfffffffeul;


class gzSwitchState : public gzReference
{
public:
	gzBool	on;

};

//******************************************************************************
// Class	: gzSwitch
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990511	Created 
//									
//******************************************************************************
class gzSwitch : public gzGroup
{
public:
	GZ_GRAPH_EXPORT gzSwitch(const gzString& name = GZ_EMPTY_STRING);
	GZ_GRAPH_EXPORT virtual ~gzSwitch() {};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- gzSwitch commands -------------------------------------

	GZ_GRAPH_EXPORT gzVoid	setActive(gzString name, gzBool on);
	GZ_GRAPH_EXPORT gzVoid	useNameActivation(gzBool on);
	GZ_GRAPH_EXPORT gzBool	useNameActivation();

	GZ_GRAPH_EXPORT gzVoid	useBitActivation(gzBool on);
	GZ_GRAPH_EXPORT gzBool	useBitActivation();

	GZ_GRAPH_EXPORT gzVoid	useMaskValues(gzBool on);
	GZ_GRAPH_EXPORT gzBool	useMaskValues();

	GZ_GRAPH_EXPORT gzUInt32 setSwitchVal(gzUInt32 value);
	GZ_GRAPH_EXPORT gzUInt32 getSwitchVal();

	GZ_GRAPH_EXPORT gzVoid		setMaskValue(gzUInt32 switchVal, gzUInt32 maskvalue, gzUInt32 wordCountOffset = 0);
	GZ_GRAPH_EXPORT gzUInt32	getMaskValue(gzUInt32 switchVal, gzUInt32 wordCountOffset = 0);

	GZ_GRAPH_EXPORT gzVoid		setMaskValueCount(gzUInt32 switchCount);
	GZ_GRAPH_EXPORT gzUInt32	getMaskValueCount();

	GZ_GRAPH_EXPORT gzVoid		setMaskWordCount(gzUInt32 wordCount);
	GZ_GRAPH_EXPORT gzUInt32	getMaskWordCount();

	// ----------- gzGroup interface ------------------------------------

	GZ_GRAPH_EXPORT virtual gzBool	isChildOrderDependant() const override { return TRUE; }

	GZ_GRAPH_EXPORT virtual gzBool	checkTraversePerChild() const override { return TRUE; }

	// ---------- Action Interface --------------------------------------
	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index, gzContext *context) override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

private:

	gzLateBindData< gzRefDict<gzString,gzSwitchState> >		m_activeNodes;

	gzUInt32												m_maskWordCount;

	gzUInt32												m_switchVal;
	gzLateBindData< gzDynamicArray<gzUInt32>	>			m_maskArray;

	gzBool													m_useNameActivation;
	gzBool													m_useBitActivation;
	gzBool													m_useMaskValues;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzSwitch);

#endif
