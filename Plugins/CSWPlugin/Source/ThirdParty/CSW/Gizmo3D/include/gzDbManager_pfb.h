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
// File			: gzDbManager_pfb.h
// Module		: 
// Description	: Class definition of the Pfb binary format
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
// AMO	000105	Created file 	
//
//******************************************************************************
#ifndef __GZ_DB_PFB_H__
#define __GZ_DB_PFB_H__

/*!	\file 
	\brief Base definitions of a Pfb binary database 

*/

#include "gzNode.h"
#include "gzGeometry.h"

// UserData Db INFO attributes
const gzString GZ_DB_INFO_TYPE_PERFORMER	="pfb";

class gzDbManager_pfb : public gzDbManager	
{
public:

	GZ_DB_EXPORT gzDbManager_pfb();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	//GZ_DB_EXPORT virtual gzBool		saveDB(gzNode *node ,gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;


protected:

	// Utility Functions

	gzUInt32 read_VLIST( gzUInt32 length , gzUInt32 list_number);
	gzUInt32 read_NLIST( gzUInt32 length , gzUInt32 list_number);
	gzUInt32 read_LLIST( gzUInt32 length , gzUInt32 list_number);
	gzUInt32 read_CLIST( gzUInt32 length , gzUInt32 list_number);
	gzUInt32 read_TLIST( gzUInt32 length , gzUInt32 list_number);
	gzUInt32 read_ILIST( gzUInt32 length , gzUInt32 list_number);


	gzUInt32 read_MTL(	gzUInt32 length , gzUInt32 list_number);
	gzUInt32 read_TEX(	gzUInt32 length , gzUInt32 list_number);
	gzUInt32 read_TENV(  gzUInt32 length , gzUInt32 list_number);
	gzUInt32 read_GSET(  gzUInt32 length , gzUInt32 list_number);
	gzUInt32 read_GSTATE(gzUInt32 length , gzUInt32 list_number);
	gzUInt32 read_NODE(  gzUInt32 length , gzUInt32 list_number);
	gzUInt32 read_IMAGE( gzUInt32 length , gzUInt32 list_number);

	gzUInt32 read_Shared_List_Type( gzUInt32 length, gzInt32 *size);


	gzVoid resolveChildren();

private:

	gzDynamicArray< gzArray< gzVec3 > >		m_list_VLIST;
	gzDynamicArray< gzArray< gzVec3 > >		m_list_NLIST;
	gzDynamicArray< gzArray< gzVec4 > >		m_list_CLIST;
	gzDynamicArray< gzArray< gzUInt16 > >	m_list_ILIST;
	gzDynamicArray< gzArray< gzVec2 > >		m_list_TLIST;
	gzDynamicArray< gzArray< gzUInt32 > >	m_list_LLIST;

	gzDynamicArray< gzRefPointer< gzMaterial > >	m_list_MTL;
	gzDynamicArray< gzRefPointer< gzTexEnv > >		m_list_TENV;
	gzDynamicArray< gzRefPointer< gzTexture > >		m_list_TEX;
	gzDynamicArray< gzRefPointer< gzGeometry > >	m_list_GEOM;
	gzDynamicArray< gzRefPointer< gzNode > >		m_list_NODES;
	gzDynamicArray< gzRefPointer< gzState > >		m_list_STATES;

	gzDynamicArray< gzRefPointer< gzRefData< gzArray<gzUByte> > > >	m_list_IMAGES;

	gzDynamicArray< gzArray<gzUInt32> >				m_list_CHILD;

	gzUInt32											m_currentVersion;

	gzBool											m_useBigEndian;

	gzMutex											m_locker;

	gzSerializeAdapter *							m_adapter;

};




#endif
