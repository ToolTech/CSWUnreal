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
// File			: gzNodeEncoder.h
// Module		: 
// Description	: Class definition of the gzNodeEncoder class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.283
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
// AMO	021213	Created file 	
//
//******************************************************************************
#ifndef __GZ_NODE_ENCODER_H__
#define __GZ_NODE_ENCODER_H__

/*!	\file 
	\brief Base definitions for gzNodeEncoder utilites

*/


#include "gzNode.h"

class gzNodeEncoder
{
public:

	GZ_GRAPH_EXPORT gzNodeEncoder();

	GZ_GRAPH_EXPORT virtual ~gzNodeEncoder();

	// Defaulkt interface to be derived in your encoder

	GZ_GRAPH_EXPORT virtual gzNode *parseNameEncoding(const gzString &name,gzNode *node,gzSerializeAdapter *adapter,const gzDynamicType &meta )=0;

	// Utility methods

	GZ_GRAPH_EXPORT static gzNode *createNameEcodedNode(const gzString &name,gzNode *node,gzSerializeAdapter *adapter, const gzDynamicType& meta = gzDynamicType());

private:

	static gzList<gzNodeEncoder>	s_encoders;

	static gzMutex					s_locker;
};




#endif // __GZ_NODE_ENCODER_H__

