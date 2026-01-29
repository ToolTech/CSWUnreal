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
// File			: gzNodeGuidDict.h
// Module		: 
// Description	: Class definition of the gzNodeGuidDict class
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
// AMO	121203	Created file 	
//
//******************************************************************************
#ifndef __GZ_NODE_GUID_DICT_H__
#define __GZ_NODE_GUID_DICT_H__

/*!	\file 
	\brief Holder of gzGuidStringDict

*/

#include "gzNode.h"
#include "gzGuidStringDict.h"

class gzNodeGuidDict : public gzNode
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzNodeGuidDict(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT ~gzNodeGuidDict();

	// ------------------- Properties ------------------------------------
	GZ_PROPERTY_EXPORT(gzGuidStringDictPtr, Dictionary		, GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,				UseBasePrefix	, GZ_GRAPH_EXPORT);

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Serializing -------------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;
};

#endif // __GZ_NODE_GUID_DICT_H__

