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
// File			: gzFrame.h
// Module		: 
// Description	: Class definition of the gzFrame class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.283
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
// AMO	990519	Created file 
// AMO	000516	Updated with CYCLE and SWING modes	
//
//******************************************************************************
#ifndef __GZ_FRAME_H__
#define __GZ_FRAME_H__

/*!	\file 
	\brief Base definitions for frame based animations

*/


#include "gzGroup.h"

typedef enum	{ 
					GZ_FRAME_CYCLE , 
					GZ_FRAME_SWING ,
					GZ_FRAME_POSITION ,
					GZ_FRAME_TRANSITION ,

				} gzFrameType;


class GZ_GRAPH_EXPORT gzFrameState : public gzReference
{
public:

	gzFrameState(){}
	virtual ~gzFrameState(){}

	GZ_PROPERTY(	gzUInt32,	NumberOfFrames		);
	GZ_PROPERTY(	gzUInt32,	StartFrameOffset	);

};

//******************************************************************************
// Class	: gzFrame
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990519	Created 
//									
//******************************************************************************
class gzFrame : public gzGroup
{
public:
	GZ_GRAPH_EXPORT gzFrame(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzFrame(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- gzFrame commands --------------------------------------

	GZ_GRAPH_EXPORT gzVoid	startFrameCounter(const gzDouble &startTime=0);
	GZ_GRAPH_EXPORT gzVoid	stopFrameCounter();

	// ---------- Equal Frame Duration ----------------------------------
	GZ_GRAPH_EXPORT gzVoid	setFrameDuration(const gzFloat& length);
	GZ_GRAPH_EXPORT gzFloat	getFrameDuration() const;

	// ---------- Non Equal frame Duration ------------------------------
	GZ_GRAPH_EXPORT gzVoid	setFrameDuration(gzUInt32 frame , const gzFloat& length);
	GZ_GRAPH_EXPORT gzFloat	getFrameDuration(gzUInt32 frame) const;

	// ---------- Common settings ---------------------------------------

	GZ_GRAPH_EXPORT	gzVoid		addFrameState(const gzString &name,gzFrameState *state);

	// ----------- Properties -------------------------------------------

	GZ_PROPERTY_EXPORT_(	gzUInt32,		NumberOfFrames,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_(	gzUInt32,		StartFrame,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(		gzFrameType,	FrameType,				GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(		gzUInt32,		FrameIndex,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(		gzUInt32,		NextFrameIndex,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(		gzFloat,		FrameFraction,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(		gzUInt32,		RepeatCount,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT_(	gzBool,			UniformFrames,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(		gzBool,			SelectChildPerFrame,	GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(		gzFloat,		SpeedFactor,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(		gzBool,			Running,				GZ_GRAPH_EXPORT);

	GZ_GRAPH_EXPORT gzUInt32	getNumberOfDefinedFrameDurations();
	GZ_GRAPH_EXPORT gzVoid		setNumberOfDefinedFrameDurations(gzUInt32 size);

	// ----------- gzGroup interface ------------------------------------

	GZ_GRAPH_EXPORT virtual gzBool	isChildOrderDependant() const override;

	GZ_GRAPH_EXPORT virtual gzBool	checkTraversePerChild() const override;

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index, gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

private:
		
	gzBool								m_calculatedSweepTime;

	gzDynamicArray<gzFloat>				m_frameDuration;
	gzFloat								m_uniformFrameDuration;

	gzFloat								m_sweepTime;
	gzDouble							m_startTime;

	gzVec3								m_lastPosition;

	gzRefDict<gzString,gzFrameState>	m_frameStates;
};

//******************************************************************************
// Class	: gzActiveFrame
//									
// Purpose  : Hold frame activation
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990607	Created 
//									
//******************************************************************************
class gzActiveFrame
{
public:
	gzActiveFrame():isActive(FALSE){};
	gzBool	isActive;
};

//******************************************************************************
// Class	: gzFrameKey
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990607	Created 
//									
//******************************************************************************
class gzFrameKey : public gzGroup
{
public:
	GZ_GRAPH_EXPORT gzFrameKey(const gzString & name=GZ_EMPTY_STRING);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- gzFrame commands -------------------------------------

	GZ_GRAPH_EXPORT gzVoid	activateFrame( gzUInt32 count);
	GZ_GRAPH_EXPORT gzVoid	deactivateFrame( gzUInt32 count);


	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index, gzContext *context) override;

private:
	gzDynamicArray<gzActiveFrame>	m_activeFrames;
};

#endif
