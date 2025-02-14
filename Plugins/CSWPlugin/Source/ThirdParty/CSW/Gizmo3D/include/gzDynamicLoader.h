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
// File			: gzDynamicLoader.h
// Module		: 
// Description	: Class definition of the gzDynamicLoader class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.220
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
// AMO	000311	Created file 	
//
//******************************************************************************
#ifndef __GZ_DYNAMIC_LOADER_H__
#define __GZ_DYNAMIC_LOADER_H__

/*!	\file 
	\brief Paged loading/unloading manager

*/

#include "gzGroup.h"
#include "gzThread.h"
#include "gzNodeOptimizer.h"

enum gzDynamicLoadingState
{ 
	GZ_DYNAMIC_LOADER_UNLOADED ,				// SYNC in NodeLock			loader has unloaded node in nodelock
	GZ_DYNAMIC_LOADER_DROPPED,					// SYNC in NodeLock			loader has been dropped (zero ref) during load
	GZ_DYNAMIC_LOADER_LOADED ,					// SYNC in NodeLock			loader has loaded node in nodelock
	GZ_DYNAMIC_LOADER_REQUEST_LOAD,				// SYNC from thread			loader is requested to load
	GZ_DYNAMIC_LOADER_REQUEST_LOAD_CANCEL,		// SYNC from thread			loader is requested to unload
	GZ_DYNAMIC_LOADER_IN_LOADING,				// ASYNC					loader in progress (async)
	GZ_DYNAMIC_LOADER_IN_DESTROY,				// SYNC in NodeLock			loader is deleted with childs
	GZ_DYNAMIC_LOADER_IN_TRAVERSAL,				// No callback
	GZ_DYNAMIC_LOADER_NOT_FOUND,				// ASYNC

};

class gzDynamicLoader;			// Forward decls
class gzDynamicLoaderManager;

//! Dynamic Loading memory state used by GizmoSDK 
const gzUInt32 GZ_MEM_DYN_LOADING_STATE = 66666;


//******************************************************************************
// Class	: gzDynamicLoaderGlobalInfoInterface
//									
// Purpose  : Interface that notifies clients about loaded dynamic data from all instances.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021119	Created 
//									
//******************************************************************************
class gzDynamicLoaderGlobalInfoInterface 
{
public:

	GZ_GRAPH_EXPORT gzDynamicLoaderGlobalInfoInterface();

	GZ_GRAPH_EXPORT virtual ~gzDynamicLoaderGlobalInfoInterface();

	GZ_GRAPH_EXPORT virtual gzVoid onDynamicLoadState(gzDynamicLoadingState state,gzDynamicLoader *loader,gzNode *node);

private:

	friend class gzDynamicLoader;

	static	gzVoid notify(gzDynamicLoadingState state,gzDynamicLoader *loader,gzNode *node);

	static	gzList<gzDynamicLoaderGlobalInfoInterface>	s_subscribers;
};

//******************************************************************************
// Class	: gzDynamicLoaderInfoInterface
//									
// Purpose  : Interface that notifies clients about loaded dynamic data from subscribed instances.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021119	Created 
//									
//******************************************************************************
class gzDynamicLoaderInfoInterface
{
public:

	GZ_GRAPH_EXPORT gzDynamicLoaderInfoInterface();

	GZ_GRAPH_EXPORT virtual ~gzDynamicLoaderInfoInterface();

	GZ_GRAPH_EXPORT virtual gzVoid onDynamicLoadState(gzDynamicLoadingState state,gzDynamicLoader *loader,gzNode *node)=0;

	GZ_GRAPH_EXPORT gzVoid lockSubscriptions();
	GZ_GRAPH_EXPORT gzVoid unLockSubscriptions();
	GZ_GRAPH_EXPORT gzVoid dropSubscriptions();

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT gzVoid write(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzVoid read(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;

private:

	friend class gzDynamicLoader;

	gzList<gzDynamicLoader>	m_pendingSubscriptions;
};

//******************************************************************************
// Class	: gzDynamicLoader
//									
// Purpose  : An instance that loads data dynamically dependant on speed and 
//			  direction of viewer
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021119	Created 
//									
//******************************************************************************
class gzDynamicLoader : public gzGroup
{
public:

	GZ_GRAPH_EXPORT gzDynamicLoader(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzDynamicLoader();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- loader interface --------------------------------------

	GZ_GRAPH_EXPORT gzVoid	setHPR(gzFloat heading=0 , gzFloat pitch=0 , gzFloat roll=0);

	GZ_GRAPH_EXPORT gzBool	waitForLoadedData(gzBool unlockRender=FALSE);

	//! Return TRUE if data set is loaded
	GZ_GRAPH_EXPORT gzBool	isLoaded();

	//! Return TRUE if data set is beeing loaded
	GZ_GRAPH_EXPORT gzBool	isInLoading();

	//! Return TRUE if is in loading or requested to load
	GZ_GRAPH_EXPORT gzBool isInLoadProgress();

	GZ_GRAPH_EXPORT gzVoid	useOptimizer(gzBool on);

	GZ_GRAPH_EXPORT gzBool	useSpecificManager(gzUByte index);

	GZ_GRAPH_EXPORT virtual gzVoid onNodeLoadState(gzNode *node,gzDynamicLoadingState state);

	GZ_GRAPH_EXPORT static	gzBool		isWorking();

	GZ_GRAPH_EXPORT static	gzDouble	getWorkDelay();
	GZ_GRAPH_EXPORT static	gzDouble	getAvgWorkDelay();
	GZ_GRAPH_EXPORT static	gzDouble	getAvgLoadSpeed();

	GZ_GRAPH_EXPORT static	gzUInt32	getPendingWork();

	GZ_GRAPH_EXPORT static	gzUInt32	getLoadCount();
	GZ_GRAPH_EXPORT static	gzVoid		resetLoadCount();

	GZ_GRAPH_EXPORT static	gzVoid		boostLoaderWork();
	GZ_GRAPH_EXPORT static	gzVoid		unBoostLoaderWork();

	GZ_GRAPH_EXPORT static	gzVoid 		usePreCache(gzBool on);

	GZ_GRAPH_EXPORT static	gzVoid 		setWaitLoadTimeout(const gzDouble &timeout);
	GZ_GRAPH_EXPORT static	gzDouble 	getWaitLoadTimeout();

	

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index , gzContext *context ) override;


	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ---------- Subscribing -------------------------------------------

	GZ_GRAPH_EXPORT gzVoid lockSubscriptions();
	GZ_GRAPH_EXPORT gzVoid unLockSubscriptions();

	GZ_GRAPH_EXPORT gzVoid addSubscriber(gzDynamicLoaderInfoInterface *subscriber);
	GZ_GRAPH_EXPORT gzVoid removeSubscriber(gzDynamicLoaderInfoInterface *subscriber);
	
	// ---------- Debug function ----------------------------------------
	GZ_GRAPH_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// --------- Subscriptions -----------------------------------------
	

	// ---------- Properties --------------------------------------------
	GZ_PROPERTY_EXPORT(gzUInt32,				AttachID,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,				LoadPriority,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_(gzString,				NodeURL,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_(gzBool,					LoadState,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,					Scale,					GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,					Heading,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,					Pitch,					GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,					Roll,					GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzSerializeAdapterFlags,	LoadFlags,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32,				Version,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,				Password,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzNodeOptimizeLevel,		OptimizerFlags,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,					Exclusive,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,					LoadOnAccess,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,					PreLoad,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,					ClearForceLocalInclude,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt64,				AccessTimeout,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32,				ForceEnableMask,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32,				ForceDisableMask,		GZ_GRAPH_EXPORT);

	// ------------- Dirty save management ------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid setDirtySaveData(gzBool dirty) override;
	GZ_GRAPH_EXPORT virtual gzBool saveDirtyData(const gzString &url) override;

	// ----------- Access Rendercount ----------------------------------

	GZ_GRAPH_EXPORT gzUInt64 getLastAccessRenderCount();

protected:

	GZ_GRAPH_EXPORT gzVoid notifyLoadState(gzDynamicLoadingState state,gzDynamicLoader *loader,gzNode *node);

	GZ_GRAPH_EXPORT gzVoid releasePendingLoads();

	GZ_GRAPH_EXPORT virtual gzBool	releaseRefs() override;

	friend class gzDynamicLoaderManager;

	// Atomic vars locked by gzNodeLock

	gzDynamicLoadingState	m_state;

	gzBool					m_optimize;

	gzBool					m_pendingWork;

	// Atomic vars locked by loader item

	gzMutex									m_subscriptionLocker;

	gzList<gzDynamicLoaderInfoInterface>	m_subscribers;

	gzDynamicLoaderManager *	m_manager;

	gzUInt64					m_lastAccessRenderCount;

	gzSerializeAdapterFlags		m_adapterFlags;

private:

	gzBool					m_inRelease;

	static gzUInt32			s_pendingWork;

	static gzUInt32			s_loadCount;

	static gzDouble			s_lastPingTime;

	static gzDouble			s_avgLoadTime;

	static gzDouble			s_avgLoadSpeed;

	static gzBool			s_usePreCache;

	static gzDouble			s_genericLoadWaitTimeout;
};

GZ_DECLARE_REFPTR(gzDynamicLoader);

//******************************************************************************
// Class	: gzDynamicLoaderManager
//
// Purpose  : The manager for dynamic loaders.
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	021119	Created
//
//******************************************************************************
class gzDynamicLoaderManager : public gzThread
{
public:

	gzDynamicLoaderManager();

	virtual ~gzDynamicLoaderManager();
	
	GZ_GRAPH_EXPORT static	gzVoid startManager(gzUByte index=0,gzBool startAll=TRUE,gzBool waitForAll = FALSE);

	GZ_GRAPH_EXPORT static	gzVoid stopManager(gzUByte index = 0, gzBool stopAll = TRUE, gzBool waitForAll = TRUE);

	GZ_GRAPH_EXPORT static	gzBool isManagerRunning(gzUByte index=0);

	GZ_GRAPH_EXPORT static	gzVoid singleStepLoading();

	GZ_GRAPH_EXPORT static	gzVoid addRenderContext(gzContext *context);

	GZ_GRAPH_EXPORT static	gzVoid removeRenderContext(gzContext *context);

	GZ_GRAPH_EXPORT static	gzVoid clearRenderContexts();

	GZ_GRAPH_EXPORT static	gzVoid preCacheTexture(gzTexture *tex);

	GZ_GRAPH_EXPORT static	gzVoid preCacheProgram(gzState *state);

	GZ_GRAPH_EXPORT static	gzVoid setNumberOfActiveLoaders(gzUByte count=1);

	GZ_GRAPH_EXPORT static	gzUByte getNumberOfActiveLoaders();

	GZ_GRAPH_EXPORT static	gzVoid allowUnload();

	GZ_GRAPH_EXPORT static	gzVoid preventUnload();

	GZ_GRAPH_EXPORT static	gzBool isUnloadAllowed();

	// Locked by Node Edit & Render 

	GZ_GRAPH_EXPORT gzBool addRenderTimeoutHandler(gzDynamicLoader* loader);

	GZ_STATIC_PROPERTY_EXPORT(gzBool,	AutoSaveDirty,			GZ_GRAPH_EXPORT);

	GZ_STATIC_PROPERTY_EXPORT(gzUInt32, AddedRemovalFrameDelay, GZ_GRAPH_EXPORT);

private:

	friend class gzDynamicLoader;

	static gzDynamicLoaderManager *  getNextLoader(const gzDouble &loadPriority);

	virtual gzVoid process();

	gzRefList<gzRefData<gzList<gzDynamicLoader> > >		m_pendingLoaders;
	gzRefList<gzRefData<gzList<gzDynamicLoader> > >		m_spareQueues;
	gzRefList<gzDynamicLoader>							m_timeOutQueue;
	gzListIterator<gzDynamicLoader>						m_timeOutIterator;

	gzDouble											m_currentLoadingPriority;

	static gzRefList<gzReference>						s_renderContexts;
	static gzMutex										s_contextLocker;

	gzEvent												m_trigger;

	gzBool												m_singleStep;

	gzBool												m_inRelease;

	static gzUByte										s_numberOfActiveLoaders;
	static gzUByte										s_currentActiveLoader;

	static gzMutex										s_exclusiveLoad;

	static gzUInt32										s_preventUnload;

	static gzMutex										s_preventUnloadLock;
};

#endif
