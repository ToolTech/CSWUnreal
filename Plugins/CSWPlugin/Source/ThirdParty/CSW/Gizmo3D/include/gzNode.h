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
// File			: gzNode.h
// Module		: 
// Description	: Class definition of the gzNode class
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
// AMO	981014	Created file 	
// AMO	101021	Added a releaseRefs to node action interface		(2.5.14)
// AMO	240423	Added collider masks to intersector and culler		(2.12.145)
// AMO	240618	Added GROUND_CONSTRUCTION to identify bridges etc	(2.12.159)
// AMO	241016	Added GZ_CULL_MASK_VEGETATION to identify grass etc	(2.12.191)
// AMO	241016	Added TACTICAL and OVERLAY , identify map items etc	(2.12.191)
//
//******************************************************************************
#ifndef __GZ_NODE_H__
#define __GZ_NODE_H__

/*!	\file 
	\brief Base definitions for scene graph nodes

*/

#include "gzObject.h"
#include "gzMatrix.h"
#include "gzState.h"
#include "gzDbFlags.h"

class gzContext;	// Forward decl
class gzNode;		// Forward declaraton


//! Definition of current version for cache creation. Uses a stable level
//! Compare with GZ_GZD_VERSION in gzd format
#define GZ_GZD_CACHE_VERSION	16


// Additional Node gzDebugFlags
const gzDebugFlags GZ_DEBUG_RECURSIVE			=(gzDebugFlags)(1<<0);
const gzDebugFlags GZ_DEBUG_SHOW_ATTRIBUTES		=(gzDebugFlags)(1<<1);
const gzDebugFlags GZ_DEBUG_SHOW_GEOMETRY		=(gzDebugFlags)(1<<2);
const gzDebugFlags GZ_DEBUG_SHOW_USERDATA		=(gzDebugFlags)(1<<3);
const gzDebugFlags GZ_DEBUG_SHOW_STATE			=(gzDebugFlags)(1<<4);
const gzDebugFlags GZ_DEBUG_SHOW_NODE_ACTIONS	=(gzDebugFlags)(1<<5);


//! Intersector mask values. Can be replaced with custom types and uses bitwise masking
enum gzIntersectMaskValue
{
	//! Your own definition
	GZ_INTERSECT_MASK_CUSTOM				= (1 << 0),

	//! Generic ground
	GZ_INTERSECT_MASK_GROUND				= (1 << 1),

	//! Generic water. Excluded from ground
	GZ_INTERSECT_MASK_WATER					= (1 << 2),

	//! Generic man made constructions
	GZ_INTERSECT_MASK_BUILDING				= (1 << 3),

	//! Generic Forest
	GZ_INTERSECT_MASK_FOREST				= (1 << 4),

	//! Generic humans
	GZ_INTERSECT_MASK_HUMAN					= (1 << 5),

	//! Generic animals
	GZ_INTERSECT_MASK_ANIMAL				= (1 << 6),

	//! Generic vehicles
	GZ_INTERSECT_MASK_VEHICLE				= (1 << 7),

	//! Sum of all dynamic objects
	GZ_INTERSECT_MASK_DYNAMIC_OBJECT		= GZ_INTERSECT_MASK_HUMAN | GZ_INTERSECT_MASK_ANIMAL | GZ_INTERSECT_MASK_VEHICLE,

	//! Generic overlay info 
	GZ_INTERSECT_MASK_OVERLAY_OBJECT		= (1 << 8),

	//! Generic underlay info 
	GZ_INTERSECT_MASK_UNDERLAY_OBJECT		= (1 << 9),

	//! Generic collider geometry
	GZ_INTERSECT_MASK_COLLIDER				= (1 << 10),

	//! Bridges, Constructions
	GZ_INTERSECT_MASK_GROUND_CONSTRUCTION	= (1 << 11),

	//! Scattered Objects
	GZ_INTERSECT_MASK_SCATTERED_OBJECT		= (1 << 12),

	//! Sum of all ground surface objects
	GZ_INTERSECT_MASK_MAP_SURFACE			= GZ_INTERSECT_MASK_GROUND | GZ_INTERSECT_MASK_WATER | GZ_INTERSECT_MASK_GROUND_CONSTRUCTION | GZ_INTERSECT_MASK_SCATTERED_OBJECT,

	//! Generic static objects on ground surface
	GZ_INTERSECT_MASK_STATIC_OBJECT			= GZ_INTERSECT_MASK_FOREST | GZ_INTERSECT_MASK_BUILDING | GZ_INTERSECT_MASK_GROUND_CONSTRUCTION | GZ_INTERSECT_MASK_SCATTERED_OBJECT,


	//! Generic screen oriented objects
	GZ_INTERSECT_MASK_SCREEN_OBJECT			= GZ_INTERSECT_MASK_OVERLAY_OBJECT | GZ_INTERSECT_MASK_UNDERLAY_OBJECT,

	//! Includes all objects
	GZ_INTERSECT_MASK_ALL					= -1,

	//! Exclude all (Pretty useless ;-)
	GZ_INTERSECT_MASK_NOTHING				= 0
};

GZ_USE_BIT_LOGIC(gzIntersectMaskValue);

enum gzCullMaskValue
{
	//! Your own definition
	GZ_CULL_MASK_CUSTOM						= (1 << 0),

	//! Generic ground
	GZ_CULL_MASK_GROUND						= (1 << 1),

	//! Generic water. Excluded from ground
	GZ_CULL_MASK_WATER						= (1 << 2),

	//! Generic man made constructions
	GZ_CULL_MASK_BUILDING					= (1 << 3),

	//! Generic Forest
	GZ_CULL_MASK_FOREST						= (1 << 4),

	//! Cull Colliders
	GZ_CULL_MASK_COLLIDER					= (1 << 5),

	//! Ground Construction
	GZ_CULL_MASK_GROUND_CONSTRUCTION		= (1 << 6),

	//! Scattered Object
	GZ_CULL_MASK_SCATTERED_OBJECT			= (1 << 7),

	//! Small Vegetation (not large tress forrest)
	GZ_CULL_MASK_SMALL_VEGETATION			= (1 << 8),

	//! Encoded mask for overlay objects
	GZ_CULL_MASK_OVERLAY					= (1 << 15),

	//! Encoded mask for tactical information
	GZ_CULL_MASK_TACTICAL					= (1 << 16),

	//! All vegetation
	GZ_CULL_MASK_VEGETATION					= GZ_CULL_MASK_FOREST|GZ_CULL_MASK_SMALL_VEGETATION,

	//! Sum of all ground surface objects
	GZ_CULL_MASK_MAP_SURFACE				= GZ_CULL_MASK_GROUND | GZ_CULL_MASK_WATER | GZ_CULL_MASK_GROUND_CONSTRUCTION | GZ_CULL_MASK_SCATTERED_OBJECT,

	

	GZ_CULL_MASK_ALL						= -1,
	GZ_CULL_MASK_NOTHING					= 0
};

GZ_USE_BIT_LOGIC(gzCullMaskValue);

//************** Common defined performance sections ******************

const gzString GZ_SECTION_RENDER				="_render";
const gzString GZ_SECTION_CULL					="_cull";
const gzString GZ_SECTION_NODE_DATA				="_node_upd";
const gzString GZ_SECTION_DYNLOAD				="_dynload";
const gzString GZ_SECTION_REFRESH				="_refresh";
const gzString GZ_SECTION_IMAGE_GET				="_get_image_from_gpu";
const gzString GZ_SECTION_FINISH				="_finish";
const gzString GZ_SECTION_SHADOW_VOLUME_CREATE	="_shad_vol_cr";
const gzString GZ_SECTION_SHADOW_VOLUME_RENDER	="_shad_vol_re";

//******************************************************************************
// Class	: gzIntersectMask
//									
// Purpose  : To keep a definition of what kind of intersect object it is.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000828	Created 
//									
//******************************************************************************
class GZ_GRAPH_EXPORT gzIntersectMask
{
public:

	inline gzIntersectMask():m_mask(GZ_INTERSECT_MASK_ALL){}

	inline virtual ~gzIntersectMask(){}

	inline gzVoid setIntersectMask( const gzIntersectMaskValue & mask )
	{
		m_mask=mask;
	}

	inline gzIntersectMaskValue getIntersectMask() const
	{
		return m_mask;
	}

	inline gzBool isIntersecting( const gzIntersectMaskValue & mask )
	{
		return (mask&m_mask)!=0;
	}

	inline gzBool isIntersecting( gzIntersectMask * imask )
	{
		return (m_mask&imask->m_mask)!=0;
	}

private:

	gzIntersectMaskValue	m_mask;
};

//******************************************************************************
// Class	: gzCullMask
//									
// Purpose  : To keep a definition of what shall be culled or not
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050209	Created 
//									
//******************************************************************************
class GZ_GRAPH_EXPORT gzCullMask
{
public:

	inline gzCullMask():m_mask(GZ_CULL_MASK_NOTHING){}

	inline virtual ~gzCullMask(){}

	inline gzVoid setCullMask( const gzCullMaskValue & mask )
	{
		m_mask=mask;
	}

	inline gzCullMaskValue getCullMask() const
	{
		return m_mask;
	}

	inline gzBool isCulled( const gzCullMaskValue & mask )
	{
		return (mask&m_mask)!=0;
	}

	inline gzBool isCulled( gzCullMask * mask )
	{
		return (m_mask&mask->m_mask)!=0;
	}

private:

	gzCullMaskValue	m_mask;
};


/*! Copy modes available for gzNode based scene graph contents. Use setCopyMode() to change 
	cloning behaviour on nodes and node children 
*/

const gzCopyMode	GZ_CLONE_SHARE_STATE		= (gzCopyMode)(1 << 0);
const gzCopyMode	GZ_CLONE_SHARE_GEOMETRY		= (gzCopyMode)(1 << 1);
const gzCopyMode	GZ_CLONE_SHARE_TEXTURE		= (gzCopyMode)(1 << 2);
const gzCopyMode	GZ_CLONE_SHARE_MATERIAL		= (gzCopyMode)(1 << 3);
const gzCopyMode	GZ_CLONE_SHARE_TEXENV		= (gzCopyMode)(1 << 4);
const gzCopyMode	GZ_CLONE_SHARE_TEXGEN		= (gzCopyMode)(1 << 5);
const gzCopyMode	GZ_CLONE_SHARE_GFX_PROGRAM	= (gzCopyMode)(1 << 6);
const gzCopyMode	GZ_CLONE_SHARE_FONT			= (gzCopyMode)(1 << 7);

//******************************************************************************
// Class	: gzNodeLock
//									
// Purpose  : To lock scene graph nodes between rendering and editing threads
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991123	Created 
// AMO	221130	Added cap. to change a edit lock to a render lock etc. (2.12.35)
//									
//******************************************************************************

/*!	Protect rendering threads from editing threads. Note that several editing threads can 
	have shared access simultaneously 

	Its ok to work with a private scene graph tree outside locks but YOU MUST NOT change any
	refcounts on shared objects. Only do that in locked edit mode

	Multiple Render locked scenens can be traversed in parallell as long as no data is changed except
	in private contexts (gzContext)

	In single threaded apps no locks are needed
	
*/

class gzNodeLock
{
public:

	//! wait for rendering purposes, Used by window refresh
	GZ_GRAPH_EXPORT static gzVoid waitLockRender();

	//! wait for scene graph editing purposes, Locks window refresh
	GZ_GRAPH_EXPORT static gzVoid waitLockEdit();

	//! change a edit lock to a render lock if allowed
	GZ_GRAPH_EXPORT static gzBool changeToRenderLock();

	//! change a edit lock to a render lock if allowed
	GZ_GRAPH_EXPORT static gzBool changeToEditLock();

	//! try to wait for rendering purposes, Used by window refresh
	GZ_GRAPH_EXPORT static gzBool tryLockRender(gzUInt32 waitValue=10);

	//! try to wait for scene graph editing purposes, Locks window refresh
	GZ_GRAPH_EXPORT static gzBool tryLockEdit(gzUInt32 waitValue=10);

	//! Unlock
	GZ_GRAPH_EXPORT static gzVoid unLock();

	//! Tells if the lock is locked.
	GZ_GRAPH_EXPORT static gzBool isLocked();

	//! Tells if the lock is locked by calling thread.
	GZ_GRAPH_EXPORT static gzBool isLockedByMe();

	//! If system is locked for rendering 
	GZ_GRAPH_EXPORT static gzBool isLockedRender();

	//! If system is locked for editing 
	GZ_GRAPH_EXPORT static gzBool isLockedEdit();

	//! Get possible thread id for editng thread
	GZ_GRAPH_EXPORT static gzUInt32 getLockedEditThreadID();

	//! Get number of locks
	GZ_GRAPH_EXPORT static gzUInt32 getLockCount();

	//! Get number of locks in thread
	GZ_GRAPH_EXPORT static gzUInt32 getThreadLockCount();

private:

	static gzSemaphore g_lock;

	GZ_GRAPH_EXPORT static gzThreadData<gzInitValue<gzUInt32,0> >	g_thread_lockcount;
};

// Node Edit lock AUTO ---------------------------------------------------------

class gzNodeEditLock
{
public:
    
    gzNodeEditLock()    { gzNodeLock::waitLockEdit(); }
    
    ~gzNodeEditLock()   { gzNodeLock::unLock(); }

	GZ_NO_IMPLICITS(gzNodeEditLock);
};

//! Scoped GUARDS exception safe
#define GZ_EDIT_GUARD gzNodeEditLock _editlock_
#define GZ_EDIT_GUARD2 gzNodeEditLock _editlock2_

// Node Render lock AUTO --------------------------------------------------------

class gzNodeRenderLock
{
public:
    
    gzNodeRenderLock()    { gzNodeLock::waitLockRender(); }
    
    ~gzNodeRenderLock()   { gzNodeLock::unLock(); }

	GZ_NO_IMPLICITS(gzNodeRenderLock);
};

#define GZ_RENDER_GUARD gzNodeRenderLock _renderlock_

// Node Render&Edit lock AUTO --------------------------------------------------------

class gzNodeEditRenderLock
{
public:
    
    gzNodeEditRenderLock():m_isLocked(FALSE) {}

	gzVoid waitLockRender()	{ gzNodeLock::waitLockRender(); m_isLocked=TRUE; }

	gzVoid waitLockEdit()	{ gzNodeLock::waitLockEdit(); m_isLocked=TRUE; }

	gzBool tryLockRender(gzUInt32 waitValue = 10) { if (gzNodeLock::tryLockRender(waitValue)){m_isLocked = TRUE;return TRUE;}else return FALSE;	}

	gzBool tryLockEdit(gzUInt32 waitValue = 10) { if (gzNodeLock::tryLockEdit(waitValue)) { m_isLocked = TRUE; return TRUE; } else return FALSE; }
    
    ~gzNodeEditRenderLock()	{ if(m_isLocked) gzNodeLock::unLock(); }

	GZ_NO_IMPLICITS(gzNodeEditRenderLock);

private:

	gzBool	m_isLocked;
};

#define GZ_EDIT_RENDER_GUARD	gzNodeEditRenderLock _editrenderlock_
#define GZ_EDIT_LOCK			_editrenderlock_.waitLockEdit()
#define GZ_RENDER_LOCK			_editrenderlock_.waitLockRender()
#define GZ_EDIT_TRY_LOCK		_editrenderlock_.tryLockEdit()
#define GZ_RENDER_TRYE_LOCK		_editrenderlock_.tryLockRender()

// Node Edit pause unlock AUTO ---------------------------------------------------------

class gzNodeEditLockPause
{
public:

	gzNodeEditLockPause() { gzNodeLock::unLock(); }

	~gzNodeEditLockPause() { gzNodeLock::waitLockEdit(); }

	GZ_NO_IMPLICITS(gzNodeEditLockPause);
};

#define GZ_EDIT_GUARD_PAUSE gzNodeEditLockPause _editlock_pause_

// Node Render pause unlock AUTO --------------------------------------------------------

class gzNodeRenderLockPause
{
public:

	gzNodeRenderLockPause() { gzNodeLock::unLock(); }

	~gzNodeRenderLockPause() { gzNodeLock::waitLockRender(); }

	GZ_NO_IMPLICITS(gzNodeRenderLockPause);
};

#define GZ_RENDER_GUARD_PAUSE gzNodeRenderLockPause _renderlock_pause_

// ------------------------------------------------------------------------------------

typedef class gzCamera * gzCameraPointer;

//******************************************************************************
// Class	: gzTraverseAction
//									
// Purpose  : To traverse a graph of nodes
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981126	Created 
//									
//******************************************************************************
class gzTraverseAction : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	//! Call to init settings in context
	GZ_GRAPH_EXPORT virtual gzVoid initTraversal(gzContext * /*context*/) {};

	//! Call to traverse scene
	GZ_GRAPH_EXPORT gzVoid traverse(gzNode *node,gzContext *context);

	//! Implement to answer traversal descicions
	GZ_GRAPH_EXPORT virtual gzBool isTransformTraverser() const		= 0;
	GZ_GRAPH_EXPORT virtual gzBool isRenderTraverser() const		= 0;
	GZ_GRAPH_EXPORT virtual gzBool isIntersectorTraverser() const	= 0;

	GZ_GRAPH_EXPORT virtual gzBool useNodeActions()	const										{ return TRUE; }

	GZ_GRAPH_EXPORT virtual gzBool isIntersecting(gzNode* /*node*/)	const						{ return TRUE; }
	GZ_GRAPH_EXPORT virtual gzBool isIntersecting(const gzIntersectMaskValue &/*value*/) const	{ return TRUE; }

protected:
	
	GZ_GRAPH_EXPORT virtual gzBool checkBoundary(gzContext * /*context*/, gzNode * /*node*/) { return TRUE; }	// default TRUE

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzNode *node , gzContext *context);
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzNode *node , gzContext *context);
};

GZ_DECLARE_REFPTR(gzTraverseAction);

enum gzBoundaryMode
{
	GZ_BOUNDARY_DEFAULT,
	GZ_BOUNDARY_ZERO_Y
};
	
//******************************************************************************
// Class	: gzBoundary
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981202	Created 
//									
//******************************************************************************
class gzBoundary
{
public:

	GZ_GRAPH_EXPORT gzBoundary():	m_center(gzVec3(0,0,0)),m_baseOffset(0),m_radius(0.0f),m_mode(GZ_BOUNDARY_DEFAULT),m_accumIncludeBoundary(FALSE),
									m_recursiveIncludeBoundary(FALSE),m_childRecursiveIncludeBoundary(FALSE),m_isReset(TRUE),m_localIncludeBoundary(FALSE),m_useRadius(TRUE){}

	GZ_GRAPH_EXPORT const  gzVec3 & getBoundaryCenter() const	{ return m_center; }
	GZ_GRAPH_EXPORT const  gzFloat & getBoundaryRadius() const	{ return m_radius; }

	GZ_GRAPH_EXPORT gzVoid setBoundaryCenter( gzVec3 center );

	GZ_GRAPH_EXPORT gzVoid setBoundaryRadius( gzFloat radius );

	GZ_GRAPH_EXPORT gzVoid resetBoundary()						{ m_isReset = TRUE ; m_radius=GZ_FLOAT_ZERO; m_center=gzVec3(0,0,0); m_childRecursiveIncludeBoundary=FALSE; m_accumIncludeBoundary=m_recursiveIncludeBoundary|m_localIncludeBoundary; }

	GZ_GRAPH_EXPORT gzVoid unResetBoundary()					{ m_isReset = FALSE;  }

	GZ_GRAPH_EXPORT gzBool isReset()							{ return m_isReset;  }

	GZ_GRAPH_EXPORT gzVoid includeBoundary(const gzVec3 &center , const gzFloat &radius );

	GZ_GRAPH_EXPORT gzVoid includeBoundary(const gzVec3 &center , const gzFloat &radius , const gzVec3 &offset);

	GZ_GRAPH_EXPORT gzVoid includeMaxBoundary(const gzVec3 &center , const gzFloat &radius , const gzVec3 &offset=gzVec3(0,0,0));

	GZ_GRAPH_EXPORT gzVoid includeBoundary(const gzBoundary *boundary , gzMatrix4 *transform , gzFloat maxScale);

	GZ_GRAPH_EXPORT gzVoid includeMaxBoundary(const gzBoundary *boundary , gzMatrix4 *transform, gzFloat maxScale , const gzVec3 &offset=gzVec3(0,0,0));


	//! TRUE if children or node wants to be recursively included
	GZ_GRAPH_EXPORT inline gzBool getRecursiveIncludeBoundary() const			{ return m_recursiveIncludeBoundary|m_childRecursiveIncludeBoundary; }

	//! True if node wants to be recursively included
	GZ_GRAPH_EXPORT inline gzBool getForceRecursiveIncludeBoundary() const		{ return m_recursiveIncludeBoundary; }

	//! TRUE if children wants to be recursively included
	GZ_GRAPH_EXPORT inline gzBool getForceChildRecursiveIncludeBoundary() const	{ return m_childRecursiveIncludeBoundary; }

	//! TRUE if node wants to be included when drawn but not possibly recursive
	GZ_GRAPH_EXPORT inline gzBool getForceLocalIncludeBoundary() const			{ return m_localIncludeBoundary; }

	//! TRUE if node is forced to be drawn
	GZ_GRAPH_EXPORT inline gzBool getForceIncludeBoundary() const				{ return m_accumIncludeBoundary; }

	//! Enable forced recursive inclusion. Even if outside boundary, the node will be included.
	GZ_GRAPH_EXPORT gzVoid setForceRecursiveIncludeBoundary(gzBool on)			{ m_recursiveIncludeBoundary=on; m_accumIncludeBoundary=m_recursiveIncludeBoundary|m_childRecursiveIncludeBoundary|m_localIncludeBoundary; }

	//! Set if children wants to use recursive inclusion
	GZ_GRAPH_EXPORT gzVoid setForceChildRecursiveIncludeBoundary(gzBool on)		{ m_childRecursiveIncludeBoundary=on; m_accumIncludeBoundary=m_recursiveIncludeBoundary|m_childRecursiveIncludeBoundary|m_localIncludeBoundary; }

	//! Set to include if parent containing boundary is included.
	GZ_GRAPH_EXPORT gzVoid setForceLocalIncludeBoundary(gzBool on)				{ m_localIncludeBoundary = on; m_accumIncludeBoundary=m_recursiveIncludeBoundary|m_childRecursiveIncludeBoundary|m_localIncludeBoundary; }


	GZ_GRAPH_EXPORT gzVoid setBaseOffsetBoundary(gzFloat offset)				{ m_baseOffset=offset; }

	GZ_GRAPH_EXPORT gzFloat getBaseOffsetBoundary()								{ return m_baseOffset; }

	GZ_GRAPH_EXPORT gzVoid setBoundaryMode(gzBoundaryMode mode)					{ m_mode=mode; }

	GZ_GRAPH_EXPORT gzVoid adjustBoundary();

	// --------- set to false if object doesn't have a radius -----

	//! Set to false if object doesn't use inclusion boundary
	GZ_GRAPH_EXPORT	gzVoid useRadius(gzBool on)									{ m_useRadius=on; }

	GZ_GRAPH_EXPORT	inline gzBool useRadius() const								{ return m_useRadius; }

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT gzVoid write(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzVoid read(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;

private:

	gzVec3			m_center;
	gzFloat			m_baseOffset;
	gzFloat			m_radius;
	
	gzBoundaryMode	m_mode;
	
	gzBool	m_accumIncludeBoundary:1;
	gzBool	m_recursiveIncludeBoundary:1;
	gzBool	m_childRecursiveIncludeBoundary:1;
	gzBool	m_isReset:1;
	gzBool	m_localIncludeBoundary:1;
	gzBool	m_useRadius:1;
};

//! Callback actions activated by nodes
 enum gzNodeActionEvent
 {	
	// Subscribeable options
	GZ_NODE_ACTION_BEFORE_PRE_TRAVERSE	= 0 		, 
	GZ_NODE_ACTION_AFTER_PRE_TRAVERSE				,
	GZ_NODE_ACTION_BEFORE_POST_TRAVERSE				,
	GZ_NODE_ACTION_AFTER_POST_TRAVERSE				,
	GZ_NODE_ACTION_SHADER_UPDATE					,
	GZ_NODE_ACTION_BEFORE_RENDER					,
	GZ_NODE_ACTION_AFTER_RENDER						,

	GZ_NODE_ACTION_BEFORE_SCENE_RENDER				,
	GZ_NODE_ACTION_AFTER_SCENE_RENDER				,

	GZ_NODE_ACTION_BEFORE_SCENE_UPDATE_NODE_DATA	,
	GZ_NODE_ACTION_AFTER_SCENE_UPDATE_NODE_DATA		,

	GZ_NODE_ACTION_BEFORE_NODE_DATA_UPDATE			,
	GZ_NODE_ACTION_AFTER_NODE_DATA_UPDATE			,

	GZ_NODE_ACTION_REF								,
	GZ_NODE_ACTION_UNREF							,
	GZ_NODE_ACTION_NODE_ID_CHANGE					,
	GZ_NODE_ACTION_ATTACH_REF						,	// Signaled when RefNod gets shared node id attached
	GZ_NODE_ACTION_DEATTACH_REF						,	// Signaled when RefNod gets shared node id removed
	GZ_NODE_ACTION_IS_TRAVERSABLE					,	// extended_data is parent
	GZ_NODE_ACTION_IS_NOT_TRAVERSABLE				,	// extended_data is parent


	// Internal action , no use
	GZ_NODE_ACTION_COUNT					,

	// Default Actions, always active
	GZ_NODE_ACTION_ADD						,
	GZ_NODE_ACTION_REMOVE				
};

class gzNodeActionInterface;	// Forward

//******************************************************************************
// Class	: gzNodeActionInterfaceHandle
//									
// Purpose  : Holds data of active actions combined with user data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000602	Created 
//									
//******************************************************************************
class gzNodeActionInterfaceHandle
{
public:

	gzRefPointer<gzNodeActionInterface>	receiver;
	gzVoid								*userdata;
};

//******************************************************************************
// Class	: gzNodeActionProvider
//									
// Purpose  : The node action provider
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000602	Created 
//									
//******************************************************************************
class gzNodeActionProvider : public gzObject
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT	gzNodeActionProvider();

	GZ_GRAPH_EXPORT	virtual ~gzNodeActionProvider();

	GZ_GRAPH_EXPORT	gzNodeActionProvider(const gzNodeActionProvider & copy);

	GZ_GRAPH_EXPORT	gzNodeActionProvider &operator=(const gzNodeActionProvider & copy);

	GZ_GRAPH_EXPORT	virtual gzVoid ref() override;		// Ref/Unref detection
    GZ_GRAPH_EXPORT	virtual gzVoid unref() override;

	// ---------- Node action interface --------------------------------

	GZ_GRAPH_EXPORT	gzVoid action(gzNodeActionEvent action , gzContext *context ,gzTraverseAction *actionclass);

	GZ_GRAPH_EXPORT gzBool	hasActiveActions()	{ return m_receivers!=nullptr; }

	GZ_GRAPH_EXPORT gzBool	hasActiveAction(gzNodeActionEvent action);

	GZ_GRAPH_EXPORT	gzVoid addActionInterface(gzNodeActionInterface *receiver , gzNodeActionEvent action , gzVoid *userdata=nullptr);
	GZ_GRAPH_EXPORT	gzVoid removeActionInterface(gzNodeActionInterface *receiver , gzNodeActionEvent action );
	GZ_GRAPH_EXPORT gzVoid removeAllActionInterfaces(gzType *type=nullptr);
	GZ_GRAPH_EXPORT gzBool hasActionInterfaceType(gzType *type);

	GZ_GRAPH_EXPORT gzArray<gzNodeActionInterfaceHandle> getActionInterfaces(gzNodeActionEvent action);

	// ---------- Debug functions ----------------------------------------

	GZ_GRAPH_EXPORT virtual	gzVoid		debugOutput(gzString base , gzString anchor , gzDebugFlags features);
	GZ_GRAPH_EXPORT virtual	gzString	nodeInfo();

	GZ_GRAPH_EXPORT virtual gzBool releaseRefs() override;

private:

	gzList<gzNodeActionInterfaceHandle>	*m_receivers;
};

//******************************************************************************
// Class	: gzNodeActionInterface
//									
// Purpose  : Derive from this interface to get node actions
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000602	Created 
//									
//******************************************************************************
class gzNodeActionInterface : public gzReference
{
public:

	GZ_GRAPH_EXPORT	gzNodeActionInterface():m_activeProviders(NULL){};

	GZ_GRAPH_EXPORT	gzNodeActionInterface(const gzNodeActionInterface &copy);

	GZ_GRAPH_EXPORT	gzNodeActionInterface & operator=(const gzNodeActionInterface &copy);

	GZ_GRAPH_EXPORT	virtual ~gzNodeActionInterface();

	GZ_GRAPH_EXPORT	virtual gzVoid onAction(gzNodeActionEvent /*action*/ , gzContext * /*context*/ , gzNodeActionProvider * /*trigger*/ , gzTraverseAction * /*actionclass*/ , gzVoid * /*userdata*/ )=0;

	GZ_GRAPH_EXPORT gzDict<gzInstanceCompareInterface, gzNodeActionProvider>* getActionProviderInterfaces();

	GZ_GRAPH_EXPORT gzVoid removeAllActions();

	GZ_GRAPH_EXPORT virtual gzBool releaseRefs() override;

private:

	friend class gzNodeActionProvider;

	gzDict<gzInstanceCompareInterface, gzNodeActionProvider>	*m_activeProviders;
};


// Forward declaration of a group
class gzGroup;

// Disable clear and destroy for gzGroup
template <> inline gzVoid gzList<gzGroup>::clearAndDestroy() 
{
}

//******************************************************************************
// Class	: gzNode
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980912	Created 
//									
//******************************************************************************
class gzNode :	public gzBoundary , public gzNodeActionProvider , 
				public gzNameInterface , public gzDebugInterface , 
				public gzIntersectMask , public gzUpdateIDInterface , 
				public gzCullMask
{
public:

	GZ_GRAPH_EXPORT gzNode(const gzString & name=GZ_EMPTY_STRING);
	GZ_GRAPH_EXPORT virtual ~gzNode();

	GZ_GRAPH_EXPORT gzNode(const gzNode &copy);
	GZ_GRAPH_EXPORT gzNode & operator=(const gzNode &copy);


	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
	GZ_GRAPH_EXPORT virtual gzVoid	setCopyMode(const gzCopyMode &mode) override;
	GZ_GRAPH_EXPORT virtual gzBool	useDeepCopy() override;

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction * /*actionclass*/ , gzContext * /*context*/) {};
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction * /*actionclass*/ , gzContext * /*context*/) {};
	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction * /*actionclass*/ , gzContext * /*context*/) { return GZ_ACTION_STAGE_TRAVERSE; }
	GZ_GRAPH_EXPORT virtual gzBool isGroupNode() const { return FALSE; }	// Speed up RTTI

	// ---------- Common graph functions --------------------------------

	//! Default initialise a state or using null to use virtual setstate to set vars
	GZ_GRAPH_EXPORT gzVoid initializeState(gzState *state=nullptr);
	
	//! Can be derived to set additional state data
	GZ_GRAPH_EXPORT virtual gzVoid setState( gzState *state );
	GZ_GRAPH_EXPORT gzVoid	setStateID( gzUInt32 stateID );
	GZ_GRAPH_EXPORT gzBool	getStateID( gzUInt32 &stateID );
	GZ_GRAPH_EXPORT gzBool	hasStateID();
	GZ_GRAPH_EXPORT gzState *getState();

	//! Return TRUE if object needs a custom state
	GZ_GRAPH_EXPORT virtual gzBool retainState() { return FALSE; }

	GZ_GRAPH_EXPORT virtual gzNode *find(const gzString &path,gzBool recursive=TRUE);

	// ----------- Parent Utilities --------------------------------------

	GZ_GRAPH_EXPORT gzVoid				removeFromParents();
	GZ_GRAPH_EXPORT gzList<gzGroup> &	getParentGroupList();
	GZ_GRAPH_EXPORT gzGroup *			getFirstParent() const;
	GZ_GRAPH_EXPORT gzUInt32			getNumberOfParents() const;	
	GZ_GRAPH_EXPORT gzBool				isShared();
	GZ_GRAPH_EXPORT gzBool				isHierarchicalChildOf(gzGroup *group);
	GZ_GRAPH_EXPORT gzVoid				replaceWith(gzNode* newChild);

	// ---------- Debug functions ----------------------------------------

	GZ_GRAPH_EXPORT virtual	gzVoid		debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;
	GZ_GRAPH_EXPORT virtual	gzString	nodeInfo() override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;


	// ---------- Node identities ---------------------------------------

	GZ_GRAPH_EXPORT	gzBool	registerNodeID(gzUInt32 id, gzBool forceUpdate=FALSE);
	GZ_GRAPH_EXPORT gzBool	unregisterNodeID();
	GZ_GRAPH_EXPORT gzBool	getNodeID(gzUInt32 &id);
	GZ_GRAPH_EXPORT gzBool	hasNodeID();
	static GZ_GRAPH_EXPORT	gzNode *findNode(gzUInt32 id);
	static GZ_GRAPH_EXPORT	gzUInt32 getMaxUsedNodeID();
	static GZ_GRAPH_EXPORT	gzVoid preAllocateNodeID(gzUInt32 id);
	static GZ_GRAPH_EXPORT	gzVoid clearAllNodeID(gzBool force=FALSE);
	
	// ---------- Boundary management -----------------------------------
	
	//! A virtual callback for node data updates. Called by updateNodeData() if we got dirty data
	//! Updates the current node itself and its boundary
	GZ_GRAPH_EXPORT virtual gzVoid updateNode() {};

	//! Trigger a recursive node update. Clears dirty state. Calculates boundaries, center etc.
	//! Traverses the tree
	GZ_GRAPH_EXPORT virtual gzVoid updateNodeData(gzBool forceBoundaryUpdate=FALSE);

	GZ_GRAPH_EXPORT gzVoid setDirtyNodeData(gzBool dirty);		
	GZ_GRAPH_EXPORT gzBool hasDirtyNodeData();
	GZ_GRAPH_EXPORT gzVoid enableNodeDataUpdate(gzBool on);		// Update data in a node
	GZ_GRAPH_EXPORT gzBool doUpdateNodeData();

	// -------------- Node visibility extent -----------------------------
	//! Returns false if visibility extent not defined or infinite
	GZ_GRAPH_EXPORT virtual gzBool getVisibilityExtent(gzVec3 &min,gzVec3 &max) const;

	// release vital shared data before thread deallocates
	GZ_GRAPH_EXPORT virtual gzBool releaseRefs() override;


	// ------------- Dirty save management ------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid setDirtySaveData(gzBool dirty);		// Sets upwards in tree
	GZ_GRAPH_EXPORT virtual gzBool hasDirtySaveData() const;			// Looks downwards in tree
	GZ_GRAPH_EXPORT virtual gzBool saveDirtyData(const gzString &url=GZ_EMPTY_STRING);

protected:

	// ---------- Protected Boundary management -----------------------------------

	friend class gzGroup;
	
	GZ_GRAPH_EXPORT gzVoid addParentGroup(gzGroup *parent);
	GZ_GRAPH_EXPORT gzVoid removeParentGroup(gzGroup *parent);

private:

	gzBool	getNodeID_unsafe(gzUInt32 &id);

	// ---------- common node members -----------------------------------

	gzRefPointer<gzState> m_state;

	// Boundary Group info

	gzList<gzGroup>		m_parents;
	gzUInt32			m_nodeID;
	gzUInt32			m_stateID;
	gzUByte				m_dirtyNodeData:1;
	gzUByte				m_updateNodeData:1;

	// Static vars

	static gzMutex										nodeIDLocker;
	static gzDict<gzUInt32CompareInterface,gzNode>		nodeIDStorage;
	static gzDict<gzInstanceCompareInterface,gzVoid>	IDNodeStorage;

};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzNode);


//******************************************************************************
// Class	: gzDbManager_BaseTransform
//									
// Purpose  : Provides base transform for all read geometry vertex values
//									
// Notes	: Added by providing a ref to it as assoc data
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	240502	Created 
//									
//******************************************************************************
class gzDbManager_BaseTransform : public gzReference, public gzMatrix4D
{
public:

	GZ_GRAPH_EXPORT gzDbManager_BaseTransform(const gzMatrix4D& matrix) :gzMatrix4D(matrix) {}

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);
};

GZ_DECLARE_REFPTR(gzDbManager_BaseTransform);

//******************************************************************************
// Class	: gzDbManager
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980912	Created 
//									
//******************************************************************************
class gzDbManager : public gzThreadSafeReference
{
public:

	GZ_GRAPH_EXPORT virtual ~gzDbManager(){};

	GZ_GRAPH_EXPORT static gzVoid	registerManager(gzDbManager *manager);

	GZ_GRAPH_EXPORT static gzBool	unregisterManager(gzDbManager *manager);

	GZ_GRAPH_EXPORT static gzBool	unregisterExtension(const gzString &extension);

	GZ_GRAPH_EXPORT static gzVoid	unregisterManagers();
		
	GZ_GRAPH_EXPORT static gzNode	*loadDB(const gzString &url , gzString extension=GZ_EVALUATE_EXTENSION , gzSerializeAdapterFlags flags=GZ_DB_FLAGS_DEFAULT , gzUInt32 version=0 , const gzString &password=GZ_EMPTY_STRING , gzReference *associatedData=nullptr,gzUInt32 *adapterLength=nullptr, gzString* errorString = NULL, gzSerializeAdapterError* errorType = NULL);

	GZ_GRAPH_EXPORT virtual gzNode	*loadDB(gzSerializeAdapter *adapter );

	GZ_GRAPH_EXPORT static gzBool	saveDB(gzNode *node , const gzString &url , gzString extension=GZ_EVALUATE_EXTENSION , gzSerializeAdapterFlags flags=GZ_DB_FLAGS_DEFAULT, gzUInt32 version=0 , const gzString &password=GZ_EMPTY_STRING, gzString* errorString = NULL, gzSerializeAdapterError* errorType = NULL);

	GZ_GRAPH_EXPORT virtual gzBool  saveDB(gzNode *node , gzSerializeAdapter *adapter);

	//!Returns the db extension. ("3ds:wrl") etc..
	GZ_GRAPH_EXPORT virtual gzString	getExtensions()=0;

	//!Returns the db version for a certain extension
	GZ_GRAPH_EXPORT virtual gzUInt32	getVersion(const gzString &extension)=0;

	GZ_GRAPH_EXPORT static gzRefPointer<gzDbManager> getDbManager(const gzString& extension, gzUInt32 version = 0);

	GZ_GRAPH_EXPORT static gzString getAllExtensions(gzBool onlySavers=FALSE);

	GZ_GRAPH_EXPORT static gzBool	createCachedModel(const gzString &url,gzSerializeAdapterFlags flags,gzNode *node);
	GZ_GRAPH_EXPORT static gzNode*	loadCachedModel(const gzString &url,gzSerializeAdapterFlags flags);

	//! return true if class can save db
	GZ_BASE_EXPORT virtual gzBool	canSave() = 0;

	GZ_GRAPH_EXPORT virtual	gzBool	useDeepCopy() { return FALSE; }	// Default behaviour is shallow share

	GZ_STATIC_PROPERTY_EXPORT(gzBool, KeepRetryLoading, GZ_GRAPH_EXPORT);

protected:

	//! displays info about registration for a certain extension
	GZ_GRAPH_EXPORT virtual gzVoid	registerManager(const gzString &extension);


	static gzRefDict<gzString,gzDbManager>	s_registeredDbManagers;
	static gzMutex							s_managerLock;
};	

GZ_DECLARE_REFPTR(gzDbManager);

#endif // __GZ_NODE_H__

