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
// File			: gzScene.h
// Module		: 
// Description	: Class definition of the gzScene class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.306
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
// AMO	9811222	Created file 	
//
//******************************************************************************
#ifndef __GZ_SCENE_H__
#define __GZ_SCENE_H__

/*!	\file 
	\brief Base definitions for scene management

*/

#include "gzGroup.h"

class gzCamera;	// forward decl

//******************************************************************************
// Class	: gzScene
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981122	Created 
//									
//******************************************************************************
class gzScene : public gzGroup
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzScene(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzScene();

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;


	// ---------- Scene dictionary interface ----------------------------

	GZ_GRAPH_EXPORT static gzScene *findScene( gzString name , gzScene *parent=nullptr);

	GZ_GRAPH_EXPORT virtual gzVoid renderScene( gzContext *context , gzTraverseAction *action); // virtual override possible

private:

	static gzMutex								 s_sceneLocker;
	static gzMemCheck<gzDict<gzString,gzScene> > s_sceneDictionary;
};

GZ_DECLARE_REFPTR(gzScene);


#endif
