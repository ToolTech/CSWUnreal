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
// File			: gzNodeInterfaces.h
// Module		: 
// Description	: Class definition of the different node interfaces
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.222
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
// AMO	050609	Created file 	
//
//******************************************************************************
#ifndef __GZ_NODE_INTERFACES_H__
#define __GZ_NODE_INTERFACES_H__

/*!	\file 
	\brief Definitions of "soft" (dynamic) interfaces used by the graph lib

*/

#include "gzBaseLibrary.h"

GZ_GRAPH_EXPORT gzVoid gzRegisterNodeInterfaces();
GZ_GRAPH_EXPORT gzVoid gzUnregisterNodeInterfaces();

#endif //__GZ_NODE_INTERFACES_H__

