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
// File			: cswSceneManager.h
// Module		: cswSceneManager
// Description	: Management of the SceneManager library
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
// AMO	240912	Created file 					(1.1.1)
//
//******************************************************************************
#pragma once

#include "cswSceneManagerBase.h"
#include "cswCommandBuffer.h"
#include "cswCullTraverseAction.h"

class cswCommandReceiverInterface;

enum cswCapability
{
	CSW_CAPABILITY_OFF						= 0,			// No features activated
	CSW_CAPABILITY_CONVERT_TO_TRIANGLE		= 1 << 0,		// Converts all surface rendering primitives to triangles
	CSW_CAPABILITY_OPTIMIZE_GEOMETRY		= 1 << 1,		// Optimize a geometry to fastest rendering (tristrip etc)
	CSW_CAPABILITY_REMOVE_NAME				= 1 << 2,		// Removes node name to free up memory
	CSW_CAPABILITY_REMOVE_META_DATA			= 1 << 3,		// Removes all nmeta data connected to node
	CSW_CAPABILITY_INDEX_GEOMETRY			= 1 << 4,		// Create index geom
	CSW_CAPABILITY_REBUILD_INDEX_GEOMETRY	= 1 << 5,		// Rebuild already indexed TRIS
};

GZ_USE_BIT_LOGIC(cswCapability);

enum cswTraverseReason
{
	CSW_TRAVERSE_NEW,
	CSW_TRAVERSE_DELETE,
};

//******************************************************************************
// Class	: cswSceneManager
//
// Purpose  : The SceneManager
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	240912	Created		(1.1.1)
//									
//******************************************************************************
class cswSceneManager : public gzNodeActionInterface,
						public gzThread,
						public gzDynamicLoaderInfoInterface
{
public:

	CSW_SM_EXPORT	cswSceneManager();
	CSW_SM_EXPORT	virtual ~cswSceneManager();

	CSW_SM_EXPORT	void shutdown();

	// When buffer is added, it is owned by the manager
	CSW_SM_EXPORT	gzVoid addCommandBuffer(cswCommandBuffer* buffer,gzBool fireProcess=TRUE);
	CSW_SM_EXPORT	gzBool hasPendingCommands();

	CSW_SM_EXPORT	gzVoid addSingleCommand(cswSceneCommand* command, gzBool fireProcess = TRUE, const cswCommandBufferType& type = CSW_BUFFER_TYPE_GENERIC);

	CSW_SM_EXPORT	gzVoid addCommandReceiver(cswCommandReceiverInterface* receiver);
	CSW_SM_EXPORT	gzVoid removeCommandReceiver(cswCommandReceiverInterface* receiver);

	CSW_SM_EXPORT	gzVoid clearCommandBufferIn();
	CSW_SM_EXPORT	gzVoid clearCommandBufferOut();

	//! Non bufferd commands
	CSW_SM_EXPORT	gzVoid setRenderTime(const gzDouble& time, const gzUInt32 &refCommandID = 0);
	CSW_SM_EXPORT	gzVoid setOmniTraverse(const gzBool &omniTraverse, const gzUInt32 &refCommandID = 0);
	CSW_SM_EXPORT	gzVoid setCamera(gzPerspCamera *camera, const gzUInt32 &refCommandID = 0);
	CSW_SM_EXPORT	gzVoid setCameraPosition(const gzVec3D &position, const gzVec3 &hpr=GZ_ZERO_VEC3, const gzFloat& hfov=50, const gzFloat& vfov=50, const gzUInt32 &refCommandID = 0);
	CSW_SM_EXPORT	gzVoid setCameraSettings(const gzFloat& nearDistance,const gzFloat &farDistance, const gzBool infinite,  const gzUInt32& refCommandID = 0);
	CSW_SM_EXPORT	gzVoid refreshScene(const gzDouble& time, const gzUInt32 &size_x, const gzUInt32 &size_y, const gzUInt32 &screen_width, const gzUInt32 &refCommandID = 0);

	CSW_SM_EXPORT	gzVoid addMap(const gzString & mapURL, const gzUInt32 &refCommandID = 0);
	CSW_SM_EXPORT	gzVoid setMapURLs(const gzString& mapURLs, const gzUInt32& refCommandID = 0);
	CSW_SM_EXPORT	gzVoid removeMap(const gzString& mapURL, const gzUInt32 &refCommandID = 0);
	CSW_SM_EXPORT	gzVoid removeAllMaps(const gzUInt32& refCommandID = 0);
	CSW_SM_EXPORT	gzVoid centerMap(const gzUInt32 &refCommandID = 0);

	CSW_SM_EXPORT	gzVoid enableCapabilities(cswCapability caps);
	CSW_SM_EXPORT	gzVoid disableCapabilities(cswCapability caps);

	CSW_SM_EXPORT	virtual gzVoid checkCapability(gzNode* node, gzState* state);

	GZ_PROPERTY_GET_EXPORT(gzString,		CoordinateSystem,	CSW_SM_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzUInt32,		TopBits,			CSW_SM_EXPORT);
	GZ_PROPERTY_GET_EXPORT(cswCapability,	Capabilities,		CSW_SM_EXPORT);

	CSW_SM_EXPORT	static gzBool initializeSceneSystem();
	CSW_SM_EXPORT	static gzBool unInitializeSceneSystem();

	GZ_THREADSAFE_REF(m_threadSafeLocker);


protected:

	CSW_SM_EXPORT virtual gzVoid initializeSceneManager(const gzBool &createDefaultViewer=FALSE,gzReference* window = nullptr, gzReference* application = nullptr);
	CSW_SM_EXPORT virtual gzVoid unInitializeSceneManager();

	CSW_SM_EXPORT gzBool traverse(const cswTraverseReason &reason, gzNode* node, gzGroup *parent, gzState *state, cswCommandBuffer* buffer,const gzUInt64 &pathID=0, const gzUInt64& parentPathID = 0);

	mutable gzMutex	m_threadSafeLocker;

private:

	CSW_SM_EXPORT	gzVoid addCommandBufferOut(cswCommandBuffer* buffer);
	CSW_SM_EXPORT	gzVoid process() override;

	CSW_SM_EXPORT	gzVoid onDynamicLoadState(gzDynamicLoadingState state, gzDynamicLoader* loader, gzNode* node) override;

	CSW_SM_EXPORT	gzVoid onAction(gzNodeActionEvent action, gzContext* context, gzNodeActionProvider* trigger, gzTraverseAction* actionclass, gzVoid* userdata) override;


	CSW_SM_EXPORT	gzVoid returnErrorMessage(const gzMessageLevel &messageLevel, const gzString& errorMessage, const gzUInt32 &commandRefID);

	// When process runs the buffer 
	gzVoid processCommandBufferIn(cswCommandBuffer* buffer);
	gzVoid processCommandBufferOut(cswCommandBuffer* buffer);


	friend class cswCommandReceiverInterface;

	gzList<cswCommandReceiverInterface>	m_receivers;

	gzRefList<cswCommandBuffer>			m_commandBuffersIn;

	gzRefList<cswCommandBuffer>			m_commandBuffersOut;

	gzEvent								m_commandBuffersInLock;		// locks buffers in 

	gzMutex								m_commandBuffersOutLock;	// locks buffers out 

	// ----------------- VARS -----------------------------------

	gzContextPtr				m_context;

	gzReferencePtr				m_window;

	gzReferencePtr				m_application;

	gzPerspCameraPtr			m_camera;

	gzScenePtr					m_scene;

	gzRoiPtr					m_root;

	cswCullTraverseActionPtr	m_traverser;

	gzRefDict<PathIDReference, PathIDActivation> m_activations;

	gzDict<gzInstanceCompareInterface, gzVoid>	m_pathIDLookup;
};

GZ_DECLARE_REFPTR(cswSceneManager);
