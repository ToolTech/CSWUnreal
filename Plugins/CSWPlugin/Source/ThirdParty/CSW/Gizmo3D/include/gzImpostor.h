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
// File			: gzImpostor.h
// Module		: 
// Description	: Class definition of the gzImpostor class
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
// AMO	080425	Created file 
//
//******************************************************************************
#ifndef __GZ_IMPOSTOR_H__
#define __GZ_IMPOSTOR_H__

/*!	\file 
	\brief Base definitions for impostor contents

*/


#include "gzGroup.h"
#include "gzThread.h"
#include "gzGeometry.h"

//******************************************************************************
// Class	: gzImpostor
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080425	Created 
//									
//******************************************************************************
class gzImpostor : public gzGroup , public gzThreadTicker
{
public:
	GZ_GRAPH_EXPORT gzImpostor(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzImpostor();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- gzImpostor commands ----------------------------------------

	//GZ_PROPERTY_EXPORT(gzBool,	RenderOriginal,	GZ_GRAPH_EXPORT);

	// ---------- Action Interface --------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index, gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction *actionclass , gzContext *context) override;

	// ------------- Properties -----------------------------------------

	GZ_PROPERTY_EXPORT(gzBool,	UseLodDistance,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec4,	BaseColor,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat,	Near,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,	NearFade,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat,	Far,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,	FarFade,			GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat,	MaxHalfDist,		GZ_GRAPH_EXPORT);


private:

	virtual gzVoid onTick() override;

	gzGFXProgramPtr			m_vertexProgram;

	gzBool					m_validImpostor;

	gzBool					m_pendingImpostor;
};

#endif // __GZ_IMPOSTOR_H__
