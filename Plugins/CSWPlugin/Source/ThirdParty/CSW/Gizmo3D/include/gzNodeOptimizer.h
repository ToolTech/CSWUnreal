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
// File			: gzNodeOptimizer.h
// Module		: 
// Description	: Class definition of the gzNodeOptimizer class
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
// AMO	011017	Created file 	
//
//******************************************************************************
#ifndef __GZ_NODE_OPTIMIZER_H__
#define __GZ_NODE_OPTIMIZER_H__

/*!	\file 
	\brief Base definitions for node optimization classes

*/

#include "gzNode.h"

#include "gzDbFlags.h"

typedef enum {	
				GZ_NODE_OPTIMIZE_DEFAULT					=	0,			// Default
				GZ_NODE_OPTIMIZE_ONLY_STATES				=	(1<<0),		// Only work on state sharing
				GZ_NODE_OPTIMIZE_DONT_COMBINE_NAME_ENCODED	=	(1<<1),		// Don't combine name encoded nodes
				GZ_NODE_OPTIMIZE_DONT_CONCAT_GEOMETRY		=	(1<<2),		// Don't concat simillar geometry
				GZ_NODE_OPTIMIZE_USE_INDEXED_GEOMETRY		=	(1<<3),		// Try to use indexed geometry
				GZ_NODE_OPTIMIZE_USE_DISPLAYLIST_GEOMETRY	=	(1<<4),		// Try to use DisplayLists
				GZ_NODE_OPTIMIZE_USE_BUFFERED_GEOMETRY		=	(1<<5),		// Try to use VBO
				GZ_NODE_OPTIMIZE_STRIP_USER_DATA			=	(1<<6),		// Strip user data from model to save mem
				GZ_NODE_OPTIMIZE_EXCLUDE_TREE				=	(1<<7),		// Excludes entire tree
				GZ_NODE_OPTIMIZE_NO_PROGRESS_REPORT			=	(1<<8),		// Silent progress
				GZ_NODE_OPTIMIZE_NO_BOUNDARY_CALC			=	(1<<9),		// Silent progress
				GZ_NODE_OPTIMIZE_DONT_FLATTEN_GEOMETRY		=	(1<<10),	// Exclude flatten transforms into sub geometry
				GZ_NODE_OPTIMIZE_DONT_CHANGE_RENDER_ORDER	=	(1<<11),	// Dont do optims that changes render order
				GZ_NODE_OPTIMIZE_DONT_OPTIMIZE_GEOMETRY		=	(1<<12),	// Dont optimize or change geom primitives
				GZ_NODE_OPTIMIZE_STRIP_NODE_NAME			=	(1<<13),	// Remove Node name
				GZ_NODE_OPTIMIZE_SMALLEST_SIZE				=	(1<<14),	// Favour smallest size objects
				GZ_NODE_OPTIMIZE_STRIP_COLLIDERS			=	(1<<15),	// Remove colliders from tree

				} gzNodeOptimizeLevel;

//! Use Bit Logics for optimizer flags
GZ_USE_BIT_LOGIC(gzNodeOptimizeLevel);

//******************************************************************************
// Class	: gzNodeOptimizer
//									
// Purpose  : Utility class to optimize scene graph data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011017	Created 
//									
//******************************************************************************
class gzNodeOptimizer
{
public:

	GZ_GRAPH_EXPORT gzNodeOptimizer();

	GZ_GRAPH_EXPORT virtual ~gzNodeOptimizer();

	//! Optimization of scene graph hierarchy
	/*! An efficient way to reduce the scene graph. A model loaded from a file is often not optimal for rendering
	so by using \code

	gzNodeOptimizer optim;
	optim.exclude("SwitchA");
	pNode=optim.optimize(pNode);

	\endcode You will end up with a optimized graph but with switch "SwitchA" preserved*/
	GZ_GRAPH_EXPORT gzNode *optimize(gzNode *node , gzNodeOptimizeLevel level=GZ_NODE_OPTIMIZE_DEFAULT);

	GZ_GRAPH_EXPORT gzBool subOptimize(gzNode *subnode,gzNodeOptimizeLevel level=GZ_NODE_OPTIMIZE_DEFAULT);

	//! Exclusion of vital nodes using names
	/*! Use this method to exclude vital nodes. Use the gzNode::find syntax "aa:bb:cc" to preserve
	node aa and aa's child bb and bb's child cc from being optimized */
	GZ_GRAPH_EXPORT gzVoid exclude(const gzString &pathName);

	//! Exclusion of vital nodes using the node pointer
	GZ_GRAPH_EXPORT gzVoid exclude(gzNode *node);

	GZ_GRAPH_EXPORT gzVoid addCompileCandidate(const gzString &nodeName);
	GZ_GRAPH_EXPORT gzVoid removeCompileCandidate(const gzString &nodeName);

	//! Returns TRUE if node is excluded
	/*! The method is used internally within the optimize call, but can also be used after an optimization to see 
	if a node was excluded by name
	\return TRUE if it was excluded */
	GZ_GRAPH_EXPORT gzBool isExcluded(gzNode *node,gzNodeOptimizeLevel level);

	GZ_GRAPH_EXPORT gzBool isCompileCandidate(const gzString &nodeName);

	//! Recursion depth settings. Default to 3
	GZ_GRAPH_EXPORT gzVoid	setMaxRecursionDepth(gzUInt32 depth);

	GZ_GRAPH_EXPORT gzUInt32	getMaxRecursionDepth() const;

	GZ_GRAPH_EXPORT gzVoid optimizeState(gzNode *node);

	GZ_GRAPH_EXPORT gzVoid clearStateOptims();

	GZ_GRAPH_EXPORT gzVoid reportProgress(gzUByte progress);

	GZ_GRAPH_EXPORT gzFloat getMaxCombineRadius();
	GZ_GRAPH_EXPORT gzVoid setMaxCombineRadius(gzFloat radius);

	GZ_GRAPH_EXPORT gzUInt32 getMaxCombinations();
	GZ_GRAPH_EXPORT gzVoid	setMaxCombinations(gzUInt32 combs);

private:

	gzDynamicArray<gzString>						m_excludePaths;

	gzDict<gzInstanceCompareInterface,gzVoid>		m_excludeNodes;

	gzDict<gzString,gzVoid>							m_compileCandidate;

	gzUInt32											m_maxRecursionDepth;

	gzRefDict<gzInstanceCompareInterface,gzState>	m_stateDict;

	gzRefDict<gzInstanceCompareInterface,gzState>	m_convertStateDict;

	gzUByte											m_lastProgress;

	gzFloat											m_maxCombineRadius;

	gzUInt32											m_maxCombinations;
};

GZ_GRAPH_EXPORT gzNodeOptimizeLevel getNodeOptimizerFlagsFromDbFlags(const gzSerializeAdapterFlags &dbflags);

#endif // __GZ_NODE_OPTIMIZER_H__
