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
// File			: gzExtRef.h
// Module		: 
// Description	: Class definition of the ExtRef class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.223
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
// AMO	180620	Created file 						(2.9.1)
//
//******************************************************************************
#ifndef __GZ_EXTREF_H__
#define __GZ_EXTREF_H__

/*!	\file 
	\brief Definitions of external references to 3rd part data

*/

#include "gzNode.h"

//******************************************************************************
// Class	: gzExtRef
//									
// Purpose  : Holds external reference data to 3rd part tools or assets
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	180620	Created 
//									
//******************************************************************************
class gzExtRef : public gzNode
{
public:
	GZ_GRAPH_EXPORT gzExtRef(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzExtRef();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- No cloning of base - pure virtual ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- The control API ---------------------------------------
	
	GZ_PROPERTY_EXPORT(gzString,	ResourceURL,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,	ObjectID,			GZ_GRAPH_EXPORT);

	// ---------- Serializing -------------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

private:

};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzExtRef);

#endif // __GZ_EXTREF_H__

