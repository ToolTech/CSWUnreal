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
// File			: gzLod.h
// Module		: 
// Description	: Class definition of the gzLod class
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
// AMO	990516	Created file 
// AMO	011004	Added access to LOD levels array	
//
//******************************************************************************
#ifndef __GZ_LOD_H__
#define __GZ_LOD_H__

/*!	\file 
	\brief Base definitions for Level Of Detail (LOD) nodes

*/


#include "gzGroup.h"
#include "gzNodeAction.h"

enum gzLodForceEnableType
{
	GZ_LOD_FORCE_ENABLE_NEAR,
	GZ_LOD_FORCE_ENABLE_FAR,
	GZ_LOD_FORCE_ENABLE_BOTH
};

class gzLodLevel
{
public:
	//!Constructor
	GZ_GRAPH_EXPORT gzLodLevel();

	GZ_PROPERTY_EXPORT_(	gzFloat,				NearDistance,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_(	gzFloat,				FarDistance,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_(	gzFloat,				NearFadeDistance,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_(	gzFloat,				FarFadeDistance,	GZ_GRAPH_EXPORT);

	GZ_PROPERTY_GET_EXPORT(	gzFloat,				NearDistanceFactor,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzFloat,				FarDistanceFactor,	GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(		gzUInt32,				EnableMask,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(		gzUInt32,				DisableMask,		GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(		gzLodForceEnableType,	ForceEnableType,	GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(		gzFloat,				NearOverlapFactor,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(		gzFloat,				FarOverlapFactor,	GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(		gzBool,					Enabled,			GZ_GRAPH_EXPORT);

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT gzVoid		write(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzVoid		read(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzVoid		pushBack(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;
};

//******************************************************************************
// Class	: gzLod
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
class gzLod : public gzGroup
{
public:
	//!Constructor
	/*!
	It is possible to specify a name for the lod node.
	*/
	GZ_GRAPH_EXPORT gzLod(const gzString & name=GZ_EMPTY_STRING);

	//!Destructor
	GZ_GRAPH_EXPORT virtual ~gzLod(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- gzLod commands ----------------------------------------

	//!Creates a lod level with specified index.
	/*!
	A lod level specifies when a child to the lod node is visible. 
	The first child added to the node is assigned the index 0, the second is assigned index 1 etc. 
	For each index the near and far distances need to be specified. The child will be visible 
	when the distance from the centre of the bounding sphere to the center is between 
	the near_dist and far_dist. 

	It is possible to fade between lod levels. E.g. If the near fade is set to 10 for an index, the
	node with this index will start to fade on at distance near_fade - 10.

	If the node shall be visible between the near_dist and far_dist enable need to be set to TRUE.

	The default near_dist is  and defalt far_dist is 1.
	Default near_fade is 0 and far_fade is 0 (disabled).
	*/
	GZ_GRAPH_EXPORT gzVoid setLOD(gzUInt32 index , gzBool enable , gzFloat near_dist = 0 , gzFloat far_dist = FLT_MAX, gzFloat near_fade=0 , gzFloat far_fade=0);
	GZ_GRAPH_EXPORT gzVoid getLOD(gzUInt32 index , gzBool *enable=nullptr , gzFloat *near_dist=nullptr , gzFloat *far_dist=nullptr , gzFloat *near_fade=nullptr , gzFloat *far_fade=nullptr) const;

	//! Set the generic lod level and disables the use of levels
	GZ_GRAPH_EXPORT gzVoid setGenericLOD(gzBool enable , gzFloat near_dist = 0, gzFloat far_dist = FLT_MAX, gzFloat near_fade=0 , gzFloat far_fade=0);

	//!Sets the fading distances for node with specified index.
	GZ_GRAPH_EXPORT gzVoid setFadeDistance(gzUInt32 index , gzFloat near_fade=0,gzFloat far_fade=0);

	GZ_GRAPH_EXPORT gzVoid setNearOverlapFactor(gzUInt32 index,gzFloat factor=0.0f);
	GZ_GRAPH_EXPORT gzVoid setFarOverlapFactor(gzUInt32 index,gzFloat factor=0.0f);

	//!Sets the lod index to a specific enumerated lod level. If zero any forced lod level applies
	GZ_GRAPH_EXPORT gzVoid		useForceEnableMask(gzUInt32 index , gzUInt32 lodMask);
	GZ_GRAPH_EXPORT gzUInt32	useForceEnableMask(gzUInt32 index) const;

	GZ_GRAPH_EXPORT gzVoid	setForceEnableType(gzUInt32 index , gzLodForceEnableType type=GZ_LOD_FORCE_ENABLE_BOTH);

	GZ_GRAPH_EXPORT gzVoid	useForceDisableMask(gzUInt32 index , gzUInt32 lodMask);
	GZ_GRAPH_EXPORT gzUInt32 useForceDisableMask(gzUInt32 index) const;

	//!Sets the center. 
	/*!
	The lod distance is computed from the center to the center of the bounding sphere for the node.

	Default center position is (0, 0, 0).
	*/

	GZ_PROPERTY_EXPORT(	gzVec3,			Center,					GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(	gzBool,			UseBoundaryCenter,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(	gzActionStage,	TranspLodStage,			GZ_GRAPH_EXPORT);


	//!Sets the center. 
	/*!
	The lod distance is computed from the center to the center of the bounding sphere for the node.

	Default center position is (0, 0, 0).
	*/
	GZ_GRAPH_EXPORT gzVoid setCenter(gzFloat x , gzFloat y , gzFloat z);

	//!Enable/ disable the use of lod levels per child.
	/*!
	Default is TRUE.
	*/
	GZ_GRAPH_EXPORT gzVoid useLevels(gzBool on);

	//!Returns TRUE if lod levels are used per child, otherwise false.
	GZ_GRAPH_EXPORT gzBool useLevels() const;

	//!Returns a dynamic array with lod levels.
	GZ_GRAPH_EXPORT gzDynamicArray<gzLodLevel> & getLevels();

	GZ_GRAPH_EXPORT static gzFloat setLodFactor( gzContext *context , gzFloat factor );

	//! A value fade>0 sets a generic fading distance. =0 disables the fade
	GZ_GRAPH_EXPORT static gzFloat setGenericFadeDistance( gzContext *context , gzFloat fade );

	//! Force the lod selection to a specific enumerated lod level
	GZ_GRAPH_EXPORT static gzUInt32 setForceLodMask( gzContext *context , gzUInt32 lodMask);

	GZ_GRAPH_EXPORT gzVoid checkTransparencyState();

	// ----------- gzGroup interface ------------------------------------

	GZ_GRAPH_EXPORT virtual gzBool	isChildOrderDependant() const override;

	GZ_GRAPH_EXPORT virtual gzBool	checkTraversePerChild() const override;

	// ---------- Action Interface --------------------------------------
	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index, gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Debug Inteface ----------------------------------------
	//!Prints debug information about the class.
	/*!
	Prints to the console by default. Uses gzMessage mechanism.
	*/
	GZ_GRAPH_EXPORT virtual gzVoid debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// -------------- Node visibility extent -----------------------------
	//! Returns false if visibility extent not defined or infinite
	GZ_GRAPH_EXPORT virtual gzBool getVisibilityExtent(gzVec3 &min,gzVec3 &max) const override;


private:

	mutable gzDynamicArray<gzLodLevel>	m_levels;

	gzRefPointer<gzState>		m_transparencyState;

	gzBool						m_useLevels:1;
	gzBool						m_useFading:1;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzLod);


class gzLodForceAction : public gzNodeAction 
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzLodForceAction(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzLodForceAction(){};

	GZ_GRAPH_EXPORT	virtual gzVoid onAction(gzNodeActionEvent action , gzContext *context , gzNodeActionProvider *trigger ,gzTraverseAction *actionclass ,gzVoid *userdata) override;

	GZ_GRAPH_EXPORT gzVoid	setForceLodMask(gzUInt32 mask);

	//---------------- Generic action interface ----------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid attach(gzNode *node) override;
	GZ_GRAPH_EXPORT virtual gzVoid deattach(gzNode *node) override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;


private:

	gzUInt32 m_forceLodMask;

};

#endif
