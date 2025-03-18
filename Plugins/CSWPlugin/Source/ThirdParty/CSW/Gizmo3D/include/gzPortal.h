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
// File			: gzPortal.h
// Module		: 
// Description	: Class definition of the gzPortal class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.231
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
// AMO	991123	Created file 	
//
//******************************************************************************
#ifndef __GZ_PORTAL_H__
#define __GZ_PORTAL_H__

/*!	\file 
	\brief Base definitions for masked rendering nodes

*/

#include "gzRecursive.h"
#include "gzGeometry.h"

class gzPortal : public gzRecursive
{
public:
	GZ_GRAPH_EXPORT gzPortal(const gzString & name=GZ_EMPTY_STRING);
	GZ_GRAPH_EXPORT virtual ~gzPortal(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
	GZ_GRAPH_EXPORT virtual gzVoid	setCopyMode(const gzCopyMode &mode) override;


	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction * /*actionclass*/ , gzContext * /*context*/) override {};


	// ---------- Stencil Mask API --------------------------------------

	GZ_GRAPH_EXPORT gzVoid useMaskState (gzBool on);
	GZ_GRAPH_EXPORT gzVoid setNormalBase( const gzVec3 &norm , const gzVec3 &base);

	// --------- Properties --------------------------------------------

	GZ_PROPERTY_EXPORT_(gzGeometryPtr,		MaskGeometry,			GZ_GRAPH_EXPORT);	//!< The portal geometry used as mask for rendering
	GZ_PROPERTY_EXPORT(gzBool,				ShowPortalMask,			GZ_GRAPH_EXPORT);	//!< Default:FALSE, Renders portal mask visibly for debugging purposes or with geom texture
	GZ_PROPERTY_EXPORT(gzBool,				EnabledPortalMask,		GZ_GRAPH_EXPORT);	//!< Default:TRUE,Active if stencils are avail in graphic context
	GZ_PROPERTY_EXPORT(gzBool,				PortalUpdateDepth,		GZ_GRAPH_EXPORT);	//!< Default:TRUE,Updates the depth buffer if possibly with the portal geom 
	GZ_PROPERTY_EXPORT(gzBool,				UseMaskState,			GZ_GRAPH_EXPORT);	//!< Default:FALSE,Renders portal mask with activated gzState
	
protected:

	GZ_GRAPH_EXPORT virtual gzVoid calculateTransform(gzContext *context);	// Override to calculate other transform

	gzVec3		m_normal,m_base;

};


#endif
