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
// File			: gzShadow.h
// Module		: 
// Description	: Class definition of the gzShadow class
// Author		: Anders Mod�n		
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
// AMO	121221	Created file 	
//
//******************************************************************************
#ifndef __GZ_SHADOW_H__
#define __GZ_SHADOW_H__

/*!	\file 
	\brief Base definitions for masked rendering nodes in volumes

*/

#include "gzTexture.h"

GZ_GRAPH_EXPORT gzTexture*	getGlobalShadowTexture();
GZ_GRAPH_EXPORT gzVoid		setGlobalShadowTexture(gzTexture* texture);

#endif //__GZ_SHADOW_H__
