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
// File			: gzGraphLibrary.h
// Module		: 
// Description	: Management of the graph library
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
// AMO	030423	Created file 	
//
//******************************************************************************
#ifndef __GZ_GRAPH_LIBRARY_H__
#define __GZ_GRAPH_LIBRARY_H__

/*!	\file 
	\brief Management of the graph library

*/

#include "gzBaseLibrary.h"

#include "gzGraphicsAbstractionLayer.h"
#include "gzAudioAbstractionLayer.h"

#include "gzGraphicsEngine.h"
#include "gzAudioEngine.h"

#include "gzNode.h"
#include "gzDynamicLoader.h"
#include "gzTransform.h"
#include "gzSwitch.h"
#include "gzLod.h"
#include "gzFrame.h"
#include "gzLayer.h"
#include "gzOrigin.h"
#include "gzAttach.h"
#include "gzSplit.h"
#include "gzBillboard.h"
#include "gzCrossboard.h"
#include "gzFaceboard.h"
#include "gzCrossVolume.h"
#include "gzContextSelect.h"

#include "gzSeedTransform.h"
#include "gzSeedSwitch.h"
#include "gzSeedControl.h"

#include "gzShader.h"
#include "gzShadow.h"

#include "gzRecursive.h"
#include "gzRecursiveSwitch.h"
#include "gzRefractor.h"
#include "gzMirror.h"

#include "gzRenderBase.h"
#include "gzTextureRender.h"
#include "gzImageRender.h"

#include "gzNodeOptimizer.h"
#include "gzNodeAction.h"
#include "gzNodeConstants.h"
#include "gzNodeEncoder.h"

#include "gzLight.h"

#include "gzIntersector.h"

#include "gzGeometry.h"
#include "gzGeometryUtils.h"
#include "gzGeometryVolume.h"
#include "gzGeometryOptimizer.h"
#include "gzParametric.h"
#include "gzBezier.h"
#include "gzParticles.h"
#include "gzVertexAttributes.h"
#include "gzImpostor.h"

#include "gzCompileGroup.h"
#include "gzRefNode.h"

#include "gzFont.h"
#include "gzText.h"
#include "gzPerformanceInfo.h"

#include "gzTexture.h"
#include "gzTexEnv.h"
#include "gzMaterial.h"

#include "gzNodeInterfaces.h"

#include "gzAudioSource.h"
#include "gzAudioListener.h"

#include "gzNodeGuidDict.h"				// Holder of gzGuidStringDict

#include "gzThreadNodeDeallocator.h"	// Added thread node locked deallocations

#include "gzExtRef.h"					// External references

#include "gzForceTraverse.h"			// Force group render by force_traverese

#include "gzGeoSceneOptimizer.h"		// optimize a global scene with respect to geometry

// -------------------------------------- Library version ---------------------------------------------------------------

GZ_GRAPH_EXPORT gzVoid gzCheckLibraryVersion_graph(gzInt32 major=GZ_VERSION_MAJ , gzInt32 minor=GZ_VERSION_MIN , gzInt32 dev=GZ_VERSION_DEV);
GZ_GRAPH_EXPORT gzLibReference *gzGetLibReference_graph();

// Define used library
#if !defined GZGRAPH_EXPORTS && !defined GZ_IGNORE_LIBDEFS && defined GZ_WINDOWS
#pragma comment( lib, "gzGraph" GZ_LIB_EXT ".lib" )
#endif

#endif // __GZ_GRAPH_LIBRARY_H__






