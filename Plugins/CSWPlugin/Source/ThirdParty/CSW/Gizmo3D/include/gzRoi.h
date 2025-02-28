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
// File			: gzRoi.h
// Module		: 
// Description	: Class definition of the gzRoi class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.224
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
// AMO	000503	Created file 	
//
//******************************************************************************
#ifndef __GZ_ROI_H__
#define __GZ_ROI_H__

/*!	\file 
	\brief Large Region Of interest support

*/

#include "gzTransform.h"
#include "gzDynamicLoader.h"
#include "gzSpatial.h"

// -------------------------- gzRoiDependancyInterface --------------------------------------------

class gzRoiDependancyInterface : public gzObject
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);

	GZ_GRAPH_EXPORT	gzRoiDependancyInterface();
	GZ_GRAPH_EXPORT	virtual ~gzRoiDependancyInterface();

	GZ_GRAPH_EXPORT	virtual gzUInt32 getDependancyMask()=0;

	//! Called by the first dependancy with TRUE and last with FALSE
	GZ_GRAPH_EXPORT	virtual gzVoid	setDependancy(gzBool /*on*/){};

	//! Called each dependancy add/remove
	GZ_GRAPH_EXPORT	virtual gzVoid	addDependancy(gzDynamicLoader * /*loader*/){};
	GZ_GRAPH_EXPORT	virtual gzVoid	removeDependancy(gzDynamicLoader * /*loader*/){};
};

// -------------------------- gzRoiGenericDependancyCounter --------------------------------------------

class gzRoiGenericDependancyCounter : public gzRoiDependancyInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);

	GZ_GRAPH_EXPORT	gzRoiGenericDependancyCounter();
	GZ_GRAPH_EXPORT	virtual ~gzRoiGenericDependancyCounter();

	GZ_GRAPH_EXPORT	virtual gzUInt32 getDependancyMask() override;
	GZ_GRAPH_EXPORT	virtual gzVoid	setDependancy(gzBool on) override;

	GZ_GRAPH_EXPORT	gzVoid	forceDependancy(gzUInt32 force=0);
	GZ_GRAPH_EXPORT	gzVoid	decreaseForceDependancy();

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	GZ_PRIVATE_IMPLICITS(gzRoiGenericDependancyCounter);

private:

	gzUInt32	m_counter;

	gzUInt32	m_forceDependancy;
};

// -------------------------- gzRoiQuadDependancyCounter --------------------------------------------

enum gzRoiQuadDependancyChild
{
	GZ_ROI_QUAD_DEP_CHILD_NW	=	0,
	GZ_ROI_QUAD_DEP_CHILD_NE	=	1,
	GZ_ROI_QUAD_DEP_CHILD_SW	=	2,
	GZ_ROI_QUAD_DEP_CHILD_SE	=	3,
	GZ_ROI_QUAD_DEP_MAIN		=	4,
	GZ_ROI_QUAD_DEP_BITS		=	5,

};

const gzUInt32 GZ_ROI_QUAD_DEP_CHILD_MASK = 0xf;
const gzUInt32 GZ_ROI_QUAD_DEP_MAIN_MASK = 0x10;

class gzRoiQuadDependancyCounter : public gzRoiDependancyInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);

	GZ_GRAPH_EXPORT	gzRoiQuadDependancyCounter();
	GZ_GRAPH_EXPORT	virtual ~gzRoiQuadDependancyCounter();

	GZ_GRAPH_EXPORT	virtual gzUInt32 getDependancyMask() override;

	GZ_GRAPH_EXPORT	virtual gzVoid	addDependancy(gzDynamicLoader *loader) override;
	GZ_GRAPH_EXPORT	virtual gzVoid	removeDependancy(gzDynamicLoader *loader) override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ---------- API ---------------------------------------------------

	GZ_GRAPH_EXPORT gzVoid setLoader(gzRoiQuadDependancyChild child,gzDynamicLoader *loader);

	GZ_GRAPH_EXPORT gzVoid setDependancyMask(gzUInt32 mask= GZ_ROI_QUAD_DEP_CHILD_MASK);

private:

	gzDynamicLoader *	m_loaders[GZ_ROI_QUAD_DEP_BITS];

	gzUInt32			m_dependancyMask;
};

// -------------------------- gzRoiOctDependancyCounter --------------------------------------------

enum gzRoiOctDependancyChild
{
	GZ_ROI_OCT_DEP_CHILD_0_0_0 = 0,
	GZ_ROI_OCT_DEP_CHILD_1_0_0 = 1,
	GZ_ROI_OCT_DEP_CHILD_0_1_0 = 2,
	GZ_ROI_OCT_DEP_CHILD_1_1_0 = 3,
	GZ_ROI_OCT_DEP_CHILD_0_0_1 = 4,
	GZ_ROI_OCT_DEP_CHILD_1_0_1 = 5,
	GZ_ROI_OCT_DEP_CHILD_0_1_1 = 6,
	GZ_ROI_OCT_DEP_CHILD_1_1_1 = 7,
	GZ_ROI_OCT_DEP_MAIN = 8,
	GZ_ROI_OCT_DEP_BITS = 9,
};

const gzUInt32 GZ_ROI_OCT_DEP_CHILD_MASK = 0xff;
const gzUInt32 GZ_ROI_OCT_DEP_MAIN_MASK = 0x100;

class gzRoiOctDependancyCounter : public gzRoiDependancyInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);

	GZ_GRAPH_EXPORT	gzRoiOctDependancyCounter();
	GZ_GRAPH_EXPORT	virtual ~gzRoiOctDependancyCounter();

	GZ_GRAPH_EXPORT	virtual gzUInt32 getDependancyMask() override;

	GZ_GRAPH_EXPORT	virtual gzVoid	addDependancy(gzDynamicLoader* loader) override;
	GZ_GRAPH_EXPORT	virtual gzVoid	removeDependancy(gzDynamicLoader* loader) override;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter* adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter* adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter* adapter) const override;

	// ---------- API ---------------------------------------------------

	GZ_GRAPH_EXPORT gzVoid setLoader(gzRoiOctDependancyChild child, gzDynamicLoader* loader);

	GZ_GRAPH_EXPORT gzVoid setDependancyMask(gzUInt32 mask = GZ_ROI_OCT_DEP_CHILD_MASK);

private:

	gzDynamicLoader* m_loaders[GZ_ROI_OCT_DEP_BITS];

	gzUInt32			m_dependancyMask;
};


// -------------------------- gzLoadDependancyGroup ---------------------------------------------------------

class gzLoadDependancyGroup : public gzGroup , public gzDynamicLoaderInfoInterface 
{
public:

	GZ_GRAPH_EXPORT gzLoadDependancyGroup(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT	virtual ~gzLoadDependancyGroup();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// Implementation specific methods..

	GZ_GRAPH_EXPORT virtual gzBool checkTraversePerChild() const override { return TRUE; }
	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index, gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid onDynamicLoadState(gzDynamicLoadingState state,gzDynamicLoader *loader,gzNode *node) override;

	// Dependancy management

	GZ_GRAPH_EXPORT gzVoid	setDependacyManager(gzRoiDependancyInterface *manager);
	GZ_GRAPH_EXPORT gzRoiDependancyInterface * getDependacyManager();

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ---------- Debug function ----------------------------------------
	GZ_GRAPH_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// -------- release vital shared data before thread deallocates -----
	GZ_GRAPH_EXPORT virtual gzBool releaseRefs() override;

private:

	gzMutex									m_locker;

	gzUInt32								m_pendingNodes;

	gzRefPointer<gzRoiDependancyInterface>	m_depManager;
};

GZ_DECLARE_REFPTR(gzLoadDependancyGroup);

// ----------------------------------------------------------------------------------------------

class gzRoi; // Forward decl of roi node loader

// -------------------------- gzRoiNode ---------------------------------------------------------

class gzRoiNode : public gzTransform , public gzDynamicLoaderInfoInterface 
{
public:

	GZ_GRAPH_EXPORT gzRoiNode(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT	virtual ~gzRoiNode();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// RoiNode interface ----------------------------

	GZ_GRAPH_EXPORT gzVoid	setRoiPosition(const gzDoubleXYZ & position , gzBool origoAtRoiNodePosition=TRUE);

	// Implementation specific methods..

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid onDynamicLoadState(gzDynamicLoadingState state,gzDynamicLoader *loader,gzNode *node) override;

	// Dependancy management

	GZ_GRAPH_EXPORT gzVoid	setDependacyManager(gzRoiDependancyInterface *manager);
	GZ_GRAPH_EXPORT gzRoiDependancyInterface * getDependacyManager();

	GZ_GRAPH_EXPORT gzDynamicLoader *getDynamicLoader();

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ---------- Debug function ----------------------------------------
	GZ_GRAPH_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// Properties ------------------------------------------------------

	//! If Origo is at RoiNode, the child models will be translated to the position of the RoiNode
	GZ_PROPERTY_EXPORT(gzBool,				OrigoAtRoiNodePosition,		GZ_GRAPH_EXPORT);

	//! If translation is On, child models will be translated by either Roi or RoiNode position
	GZ_PROPERTY_EXPORT(gzBool,				RoiTranslation,				GZ_GRAPH_EXPORT);

	//! LoadDistance is the range when the loader is set to active
	GZ_PROPERTY_EXPORT_(gzDouble,			LoadDistance,				GZ_GRAPH_EXPORT);

	//! PurgeDistance is the range when the loader is set to inactive
	GZ_PROPERTY_EXPORT_(gzDouble,			PurgeDistance,				GZ_GRAPH_EXPORT);

	//! Position is the pos which is compared to the camera position in the current ROI local koordinate system
	GZ_PROPERTY_EXPORT(gzDoubleXYZ,			Position,					GZ_GRAPH_EXPORT);

	//! CullRadius is the radius that the view is culled against
	GZ_PROPERTY_EXPORT(gzFloat,				CullRadius,					GZ_GRAPH_EXPORT);

	//! CullDisableDistance is the distance to camera when culling is disabled
	GZ_PROPERTY_EXPORT(gzFloat,				CullDisableDistance,		GZ_GRAPH_EXPORT);

	//! Loaders is active used loader when not first child is a loader
	GZ_PROPERTY_EXPORT(gzDynamicLoaderPtr,	Loader,						GZ_GRAPH_EXPORT);

private:

	friend class gzRoi;

	gzDouble								m_loadDistanceMag;
	gzDouble								m_purgeDistanceMag;
	gzUInt32								m_pendingNodes;
	gzDouble								m_purgeMinTime;

	gzRefPointer<gzRoiDependancyInterface>	m_depManager;
};

GZ_DECLARE_REFPTR(gzRoiNode);

// ----------------------- gzRoi ----------------------------------------------------------

class gzRoi : public gzTransform
{
public:

	GZ_GRAPH_EXPORT gzRoi(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzRoi();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Roi interface -----------------------------------------

	GZ_GRAPH_EXPORT gzVoid setRoiPosition(const gzDoubleXYZ & position);

	GZ_GRAPH_EXPORT gzRoiNode *addRoiNode(const gzDoubleXYZ & position , const gzDouble & loadDistance , const gzDouble & purgeDistance , const gzString &url , gzBool origoAtRoiNodePosition=TRUE, const gzSerializeAdapterFlags & loadFlags=GZ_DB_FLAGS_DEFAULT , const gzFloat & scale=0 , const gzFloat & heading=0 , const gzFloat & pitch=0 , const gzFloat & roll=0 , const gzDouble &loadPriority=0.0, gzRoiNode* customNode=nullptr);

	GZ_GRAPH_EXPORT gzRoiNode *addCustomRoiNode(gzRoiNode* customNode , const gzDoubleXYZ & position , const gzDouble & loadDistance , const gzDouble & purgeDistance , const gzString &url , gzBool origoAtRoiNodePosition=TRUE, const gzSerializeAdapterFlags & loadFlags=GZ_DB_FLAGS_DEFAULT , const gzFloat & scale=0 , const gzFloat & heading=0 , const gzFloat & pitch=0 , const gzFloat & roll=0 , const gzDouble &loadPriority=0.0);

	GZ_GRAPH_EXPORT gzVoid removeRoiNode(const gzDoubleXYZ & position , const gzString &url);

	GZ_GRAPH_EXPORT gzVoid removeRoiNode(gzRoiNode *node);

	GZ_GRAPH_EXPORT gzVoid setMinimumCheckDistance(gzDouble distance);

	GZ_GRAPH_EXPORT gzVoid loadAtPosition(gzContext *context,const gzDoubleXYZ & position,gzBool waitForLoad);

	GZ_GRAPH_EXPORT gzVoid useDistanceValues(gzBool useX , gzBool useY , gzBool useZ);

	GZ_GRAPH_EXPORT gzVoid restoreRoiNode(gzRoiNode *node);

	GZ_GRAPH_EXPORT gzRoiNode *getClosestRoiNode(const gzDoubleXYZ & position);

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- traversal support -------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index , gzContext *context ) override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ---------- Debug function ----------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// --------- Update of internal boundary --------------------------- 
	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- Properties --------------------------------------------

	//! The large coordinate position
	GZ_PROPERTY_EXPORT(gzDoubleXYZ,	Position,				GZ_GRAPH_EXPORT);

	//! True if only roinode children are controlled
	GZ_PROPERTY_EXPORT(gzBool,		UseOnlyRoiNodes,		GZ_GRAPH_EXPORT);

	//! The duration before roidnode children are purged
	GZ_PROPERTY_EXPORT(gzDouble,	PurgeDelayTime,			GZ_GRAPH_EXPORT);

	//! Active radius of ROI or zero
	GZ_PROPERTY_EXPORT(gzDouble,	Radius,					GZ_GRAPH_EXPORT);

	// ---------- ROI Control -------------------------------------------
	
	static GZ_GRAPH_EXPORT gzVoid setRoiCullRadiusScale(gzContext *context,gzFloat scale=1.0f);

protected:

friend class gzRoiNode;

	GZ_GRAPH_EXPORT gzBool checkRoiNodeActivation(gzContext *context,const gzDoubleXYZ &position,gzRoiNode *node,gzBool waitForLoad,const gzDouble &time);
	GZ_GRAPH_EXPORT gzVoid checkCulledRoiNodes(gzContext *context,const gzDoubleXYZ & position);

	// Possibly we need to move these to context
	gzDoubleXYZ								m_lastRoiPosition;
	gzDouble								m_lastRoiCheckTime;

	gzDouble								m_minCheckDistanceMag;

	gzBool									m_useX,m_useY,m_useZ;

	gzSpatialData<gzRefPointer<gzRoiNode> >	m_spatialRepository;

	gzDouble								m_currentInvLodFactorMag;

	gzMutex									m_nodeLocker;
};

GZ_DECLARE_REFPTR(gzRoi);



#endif
