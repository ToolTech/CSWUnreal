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
// File			: gzContext.h
// Module		: 
// Description	: Class definition of the gzContext class
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
// AMO	991101	Created file 	
//
//******************************************************************************
#ifndef __GZ_CONTEXT_H__
#define __GZ_CONTEXT_H__

/*!	\file 
	\brief Base definitions of multithread graphics contexts

*/

#include "gzBaseLibrary.h"

#include "gzGraphicsEngine.h"
#include "gzState.h"
#include "gzLight.h"
#include "gzClipPlane.h"
#include "gzRenderAction.h"
#include "gzCuller.h"
#include "gzRoi.h"
#include "gzEnvironment.h"
#include "gzRecursive.h"
#include "gzTexture.h"
#include "gzFont.h"
#include "gzLod.h"

//******************************************************************************
// Class	: gzContext
//									
// Purpose  : 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	020204	Created 
//									
//******************************************************************************
class gzContext : public gzReference
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);

	// ------------------ General methods --------------------

	GZ_GRAPH_EXPORT gzContext();

	GZ_GRAPH_EXPORT gzContext(const gzContext &copy);

	GZ_GRAPH_EXPORT virtual ~gzContext();

	//! Transfer the nessesary attributes to a second context
	GZ_GRAPH_EXPORT gzVoid transferStateTo(gzContext *context);

	//! Contexts are always shared
	GZ_GRAPH_EXPORT virtual	gzBool	useDeepCopy() override { return FALSE; }	


	//! Get the default context for a certain thread ID
	GZ_GRAPH_EXPORT static gzContext *getCurrentContext(gzUInt32 threadID);

	//! Get the current thread default context
	GZ_GRAPH_EXPORT static gzContext *getCurrentContext();	// gets default context on a TID basis

	//! Set the current thread default context
	GZ_GRAPH_EXPORT static gzVoid	  setCurrentContext(gzContext *context);

	//! Clear the storage of available contexts
	GZ_GRAPH_EXPORT static gzVoid	  clearContextStorage();

	GZ_GRAPH_EXPORT static gzUInt64 getCurrentRenderCount();	// gets default render counter

	GZ_GRAPH_EXPORT static gzVoid	updateCurrentRenderCount();	// updates default render counter

	//! Remove a lot of dependecies in the context
	GZ_GRAPH_EXPORT	gzVoid	cleanContext();

	GZ_GRAPH_EXPORT gzVoid  cleanStateAttributes();

	GZ_GRAPH_EXPORT gzVoid	resetTraversalIndex(gzTraverseAction *action);		//!< reset the current context (all internal states) 

	GZ_GRAPH_EXPORT gzVoid	resetRenderingIndex();								//!< Reset all indices used for rendering control

	GZ_GRAPH_EXPORT gzVoid	reactivate();	//!< reactivates the current context (all internal states) 

	GZ_GRAPH_EXPORT gzVoid	resetFrame();	//!< Reset every frame for data calculated per frame

	// ---------------- Common methods ---------------------------------------------

	GZ_GRAPH_EXPORT gzVoid setColorMask(gzBool redMask , gzBool greenMask , gzBool blueMask , gzBool alphaMask );

	GZ_GRAPH_EXPORT gzVoid setMaxTransparencySortDistance(const gzFloat & distance);

	GZ_GRAPH_EXPORT gzVoid setMinCullFactorSize(const gzFloat & size);
	GZ_GRAPH_EXPORT gzVoid setCullMask(const gzCullMaskValue &cullMask);

	//! Get pathID for a selected hierarchy of nodes. History is e.g. output from a gzIntersector
	static GZ_GRAPH_EXPORT gzUInt64 getPathID(gzList<gzNode> &history);

	//! Set context selected path to a specific gzNode. History is e.g. output from a gzIntersector
	GZ_GRAPH_EXPORT gzVoid	setSelectedNode(gzList<gzNode> &history);
	GZ_GRAPH_EXPORT gzVoid	setNoSelectedNode();

	// Counters
	GZ_GRAPH_EXPORT gzVoid setUpdateRenderCount(gzBool on);

	//! Restore the internal vars back to current state
	GZ_GRAPH_EXPORT gzVoid	readBackState(gzEnumBits bits);

	//! General attribute container so you can store additional data with your context
	gzDynamicTypeContainer	attributeContainer;

	// ---------------- Common Attributes ------------------------------------------

	// Platform dependant implementation of rendering context control

	gzReferencePtr					activeRenderContext;

	// General vars

	gzContext						*mainContext;		//!< Pointer to default main context;

	gzBool							activeRenderState;

	// State vars

	gzState*						currentState;
	gzRefPointer<gzState>			globalState;

	gzQueue<gzState *>				stackState;
	gzBool							stateChange;

	// Depth State Bits
	gzEnum							currentDepthFunc;
	gzBool							enabledDepthTest;
	gzBool							enabledDepthWriteMask;

	gzBool							useDepthBuffer;		//!< capability if we shall use depth

	// StateAttribute vars

	gzArray< gzTexture * >			currentTexture;

	gzMaterial *					currentMaterial;
	gzMaterial *					currentBackMaterial;

	gzArray< gzTexEnv * >			currentTexEnv;

	gzArray< gzTexGen * >			currentTexGen;

	gzGFXProgram *					currentGFXPrograms[GZ_NUMBER_OF_GFX_PROGRAM_TYPES];				// Contains activated program, Fixed size
	gzGFXProgram *					pendingGFXPrograms[GZ_NUMBER_OF_GFX_PROGRAM_TYPES];				// Contains programs about to be activated, Fixed size

	gzBool							hasActiveGFXPrograms;

	gzBool							activeSeparation;

	gzTexture *						currentStateTexture;
	gzMaterial *					currentStateMaterial;

	// state

	gzUInt32						activeStateAttributeIndex;

	gzDynamicArray<gzStateAttribute>	currentStateAttributeStack;
	gzUInt32						currentStateAttributeIndex;
	gzStateAttribute *				currentStateAttribute;
	
	// Vertex Arrays
	gzFlag							enabledColorArray;
	gzFlag							enabledNormalArray;
	gzDynamicArray<gzFlag>			enabledTexCoordArray;
	gzFlag							enabledIndexArray;
	gzFlag							enabledVertexArray;
	gzFlag							enabledEdgeFlagArray;


	// Blending

	gzBool							currentStipple;
	gzBool							currentBlend;
	gzBool							currentPolygonMode;

	// Alpha Func
	gzBool							currentAlphaFunc;

	gzUByte							currentHalfAlphaStage;

	gzFloat							currentLineWidth;
	gzFloat							currentPointSize;

	// LightState

	gzDynamicArray<gzLightState>	currentLightStateStack;
	gzUInt32						currentLightStateIndex;
	gzLightState					currentLightState;
	gzUInt32						activeLightStateIndex;
	gzQueue<gzLightState>			currentLightStateStorage;

	gzLightState					mainLightState;

	// Lights
	gzBool							enabledLight[GZ_NUMBER_OF_ACTIVE_LIGHTS];

	// Flag for depth only rendering
	gzBool							depthRender;

	// Generic lighting

	gzRGBA							globalAmbient;
	gzBool							localViewer;
	gzBool							twoSideLighting;
	gzBool							stateDisabledLighting;

	// ClipState

	gzDynamicArray<gzClipState>		currentClipStateStack;
	gzUInt32						currentClipStateIndex;
	gzClipState						currentClipState;
	gzUInt32						activeClipStateIndex;
	gzQueue<gzClipState>			currentClipStateStorage;

	gzClipState						mainClipState;

	gzBool							enabledClipStates[GZ_NUMBER_OF_ACTIVE_CLIP_PLANES];

	// Fog

	gzDynamicArray<gzFogInfo>		currentFogStateStack;
	gzUInt32						currentFogStateIndex;
	gzFogInfo						currentFogState;
	gzUInt32						activeFogStateIndex;
	gzQueue<gzFogInfo>				currentFogStateStorage;

	// Transform

	gzDynamicArray<gzMatrix4>		currentTransformStack;
	gzQueue<gzMatrix4>				currentTransformStorage;

	gzUInt32						currentTransformIndex;
	gzQueue<gzUInt32>				currentTransformIndexStorage;
	gzUInt32						nextTransformIndex;
	gzUInt32						activeTransformIndex;

	gzMatrix4						currentTransform;
	gzMatrix4						currentInvertedTransform;
	gzUInt32						currentInvertedIndex;

	gzFloat							currentMaxScale;
	gzQueue<gzFloat>				currentMaxScaleStorage;
	gzDynamicArray<gzFloat>			currentMaxScaleStack;

	gzFloat							mainMaxScale;
	gzMatrix4						mainTransform;
	gzMatrix4						mainInvertedTransform;

	gzMatrix4						mainProjTransform;
	gzMatrix4						mainInvertedProjTransform;

	gzUInt32						reservedTransforms;
	
	// Transform UpdateID
	
	gzDynamicArray<gzUInt32>		currentTransformUpdateIDStack;
	gzQueue<gzUInt32>				currentTransformUpdateIDStorage;
	gzUInt32						currentTransformUpdateID;

	// Frame

	gzUInt32						currentFrameIndex;
	gzDouble						currentFrameFraction;
	gzUInt32						currentNextFrameIndex;

	gzQueue<gzUInt32>				currentFrameIndexStorage;
	gzQueue<gzUInt32>				currentNextFrameIndexStorage;
	gzQueue<gzDouble>				currentFrameFractionStorage;


	// General vars

	gzUInt32						pid;
	gzUInt32						enumerator;
	gzDouble						renderTime;
	gzDouble						nowTime;
	gzUInt32						renderID;
	gzBool							updateRenderCount;
	gzUInt64						renderCount;
	gzUInt32						stencilMaxValue;
	gzUInt32						multiPassNumber;
	gzUInt32						winWidth;
	gzUInt32						winHeight;
	gzInt32							winOffsetX;
	gzInt32							winOffsetY;


	gzBool							compiled;

	// general transparency
	gzBool							useTransparency;
	gzFloat							transparency;
	gzFloat							currentMaterialTransparency;

	// unique identifier
	gzUInt32						contextID;

	// Portal Recursive Mask 
	gzUInt32						currentStencilValue;

	// Recursive depth

	gzFloat							currentRecursiveDepth;
	gzQueue<gzFloat>				currentRecursiveDepthStorage;
	gzDynamicArray<gzRecursiveData>	recursiveDataStorage;

	gzFloat							currentRecursiveDepthScaleFactor;
	gzQueue<gzFloat>				currentRecursiveDepthScaleFactorStorage;


	// Render engine
	gzUByte							reverseRenderTextures;

	gzDataSort<gzRenderNode>		sortedNodes[GZ_ACTION_STAGE_COUNT];

	gzCamera						* currentCamera;
	gzRefPointer<gzContext>			recursiveContext;

	// Cullers

	gzRefList<gzCuller>				cullers;

	// Lods

	gzBool							hasCalculatedInvScaleMag;
	gzFloat							invScaleMag;
	gzFloat							invLodFactorMag;
	gzFloat							invLodFactor;

	gzFloat							currentLodDistance;
	gzQueue<gzFloat>				currentLodDistanceStorage;

	gzFloat							genericFadeDistance;

	// Sorting far distance for transparent objects
	gzDouble						maxTransparencySortDistanceFactor;

	// minimal feature culling size
	gzFloat							minCullFactorSize;


	// Polygon Offset

	gzPolyOffsetMode				currentPolygonOffsetMode;
	gzActionStage					actionStage;


	// Texture IDs
	gzRefPointer<gzRefIdStorage>	unboundTextureID;

	// Texture precache
	gzTexturePreCache				tex_pre_cache;

	// Program precache
	gzGFXProgramPreCache			prog_pre_cache;

	// DisplayList IDs
	gzRefPointer<gzRefIdStorage>	unboundDisplayListID;

	// VBO IDs
	gzRefPointer<gzRefIdStorage>	unboundVboID;
	gzUInt32						currentVBOBindArrayBufferID;
	gzUInt32						currentVBOBindElementArrayBufferID;

	// FBO IDs
	gzRefPointer<gzRefIdStorage>	unboundFboID;

	// Intersector Busy in same thread

	gzBool							inIntersector;

	gzUInt32						currentIntersectorsPerFrame;

	// Roi information

	gzDoubleXYZ						currentRoiPosition;
	gzBool							isCameraRoiPositioned;

	// ROI Culling
	gzFloat							roiCullRadiusScale;

	// Update dynamic loading in ROIs
	gzBool							updateDynamicLoading;
	gzBool							waitForDynamicData;

	// ROI level
	gzUInt32						currentRoiRecursionLevel;

	gzUInt32						forceTraverseMask;

	// Lod forced renering
	gzQueue<gzUInt32>				forceLodMaskStorage;

	gzBool							infiniteFarPlane;

	// Index utility
	gzDynamicArray<gzUInt32>		indArray;

	// ColorMask						

	gzBool							redMask;
	gzBool							greenMask;
	gzBool							blueMask;
	gzBool							alphaMask;

	// Stereo info
	gzBool							stereo;

	// State info about currentCulling modes
	gzInt32							currentCull;					// GZ_BACK,GZ_FRONT,GZ_FRONT_AND_BACK
	gzInt32							currentPolygonModeBack;
	gzInt32							currentPolygonModeFront;


	// Stats
	gzUInt32						numberOfDrawnTris;	// All primitives

	gzUInt32						primTriCount;
	gzUInt32						primQuadCount;
	gzUInt32						primQuadStripCount;
	gzUInt32						primTriFanCount;
	gzUInt32						primTriStripCount;
	gzUInt32						primPointCount;
	gzUInt32						primLineCount;
	gzUInt32						primLineStripCount;
	gzUInt32						primLineLoopCount;
	gzUInt32						primPolyCount;

	gzDouble						cullTime;
	gzDouble						drawTime;
	gzDouble						appTime;
	gzDouble						lockTime;
	gzDouble						nodeDataTime;
	gzDouble						uploadTime;

	gzDouble						avgCullTime;
	gzDouble						avgDrawTime;
	gzDouble						avgAppTime;
	gzDouble						avgLockTime;
	gzDouble						avgNodeDataTime;


	gzUInt32						textureTransfers;
	gzUInt32						textureActivations;
	gzUInt32						textureSize;

	// Random sequence

	gzUInt32						currentRandomSeed;
	gzQueue<gzUInt32>				currentRandomSeedStorage;

	// Sequence ordering
	gzUInt32						currentSequence;
	gzQueue<gzUInt32>				currentSequenceStorage;

	// Origin

	gzUInt32						currentOriginID;
	gzQueue<gzUInt32>				currentOriginIDStorage;
	gzFloat							currentOriginScale;


	// Update max count numbers per frame

	gzUInt32						maxVBOGeomPerFrame;
	gzUInt32						currentVBOGeomPerFrame;

	gzUInt32						maxDisplayListGeomPerFrame;
	gzUInt32						currentDisplayListGeomPerFrame;

	// GLSL

	gzHandle						currentProgramObject;
	gzInt32							currentInvertedTransformUniformID;

	// Particled
	gzFloat							currentFuzzyDepthScale;

	// Transform Base

	gzUInt32						currentTransformBaseIndex;
	gzUInt32						nextTransformBaseIndex;
	gzQueue<gzUInt32>				currentTransformBaseIndexStorage;
	gzUInt32						activeTransformBaseIndex;

	gzUInt32						currentNumberOfTransformBases;
	gzQueue<gzUInt32>				currentTransformBaseSizeStorage;

	gzDynamicArray<gzTransformID>	currentTransformBaseStack;


	// Path ID 
	gzUInt64						pathID;

	// Selection
	gzNode	*						selectedNode;
	gzUInt64						selectedPathID;


	// Culling

	gzCullMaskValue					cullMask;
	
	// Texture transfer
	
	gzUInt32						textureBufferID;

	// Write/read locks

	gzBool							useEditLockedRender;
    gzBool                          allowMultiThreadRender;

	// Shared data attached that can be used by context users

	gzReferencePtr					userData;

private:

	gzVoid init();

	gzRefPointer<gzLibReference>	m_libref;

	friend class gzContextStore;

	static gzRefDict<gzUInt32CompareInterface,gzContext>	s_contextList;

	static	gzUInt32				s_lastPid;
	static	gzContext *				s_lastContext;

	static gzUniqueIDManager		s_idManager;

	static	gzUInt32				s_enumerator;

	static gzMutex					s_contextMutex;

	static gzMutex					s_contextRenderMutex;
	static gzUInt64					s_renderCount;

};

GZ_DECLARE_REFPTR(gzContext);

#endif

