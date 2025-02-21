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
// File			: gzDbManager_gzl.h
// Module		: 
// Description	: Class definition of the gizmo xml db extension format
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
// AMO	080512	Created file 	
// AMO	140821	Added version info								2.8.0
//
//******************************************************************************
#ifndef __GZ_DB_GZL_H__
#define __GZ_DB_GZL_H__

/*!	\file 
	\brief Base definitions of a Gizmo3D xml (gzl) database 

*/

#include "gzGroup.h"
#include "gzXML.h"
#include "gzGeometry.h"
#include "gzNodeConstants.h"

// UserData Db INFO attributes
const gzString GZ_DB_INFO_TYPE_GIZMO3D_XML	="gzl";

// Version 2.8.0

//<gzFrame frames="{number of frames}" speed_factor="{speed multiply factor}" running="{Yes|No}" select_child_per_frame="{if we cycle through frames:Yes|No}" start_frame="{first frame number}" frame_type="{type of frame:gzFrameType}" frame_index="{possbly frame index:0-}" frame_fraction="{part of frame:0.0-0.9999}" next_frame_index="{next frame}" uniform_frames="{if all frames have same duration:Yes|No}" uniform_frame_duration="{uniform length in float}" frame_duration_length="{length of non uniform duration data}"}> 

//******************************************************************************
// Class	: gzDbManager_gzl
//									
// Purpose  : Reader for Gizmo3D xml file format
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	071029	Created 
//									
//******************************************************************************
class gzDbManager_gzl : public gzDbManager	
{
public:

	GZ_DB_EXPORT gzDbManager_gzl();
	GZ_DB_EXPORT virtual ~gzDbManager_gzl();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzBool		saveDB(gzNode *node , gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;

	GZ_DB_EXPORT gzVoid registerInterface(const gzString &className,gzXmlCustomDataInterface *iface);

protected:

	GZ_DB_EXPORT virtual gzVoid		registerManager(const gzString &extension) override;

private:

	gzRefList<gzXmlCustomDataInterface>		m_interfaces;
};

// ---------------------------- gzGZLReader --------------------------------

class gzGZLReader : public gzXmlSax 
{
public:

	GZ_DB_EXPORT	gzGZLReader();
	GZ_DB_EXPORT	virtual ~gzGZLReader();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_DB_EXPORT);	// RTTI

	GZ_DB_EXPORT	gzParseResult readNodeData(const gzString &className,gzRefPointer<gzReference> &value);
	
	GZ_DB_EXPORT	gzNode *getNode();

	GZ_PROPERTY_EXPORT(gzNodePtr,CurrentNode,GZ_DB_EXPORT);
	GZ_PROPERTY_EXPORT(gzObjectPtr,CurrentObject,GZ_DB_EXPORT);
	GZ_PROPERTY_EXPORT(gzGroupPtr,CurrentGroup,GZ_DB_EXPORT);
	GZ_PROPERTY_EXPORT(gzNodePtr,TopNode,GZ_DB_EXPORT);

	GZ_DB_EXPORT	gzReference *getReference(gzUInt32 id);
	GZ_DB_EXPORT	gzBool registerReference(gzUInt32 id,gzReference *ref);

	gzParseResult parseULongArray(gzUInt32 size);
	gzParseResult parseIntArray(gzUInt32 size);
	gzParseResult parseFloatArray(gzUInt32 size);
	gzParseResult parseVec2Array(gzUInt32 size);
	gzParseResult parseVec3Array(gzUInt32 size);
	gzParseResult parseVec4Array(gzUInt32 size);
	gzParseResult parseWeightArray(gzUInt32 size);

	gzParseResult parseVec4();
	gzParseResult parseMatrix4();

	gzParseResult parseVec3(const gzString &str);
	gzParseResult parseVec4(const gzString &str);
	gzParseResult parseMatrix4(const gzString &str);
	gzParseResult parseDoubleXYZ(const gzString &str);

	GZ_PROPERTY_GET_EXPORT(gzDynamicArray<gzUInt32>,CurrentULongArray,	GZ_DB_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzDynamicArray<gzInt32>,	CurrentIntArray,	GZ_DB_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzDynamicArray<gzFloat>,	CurrentFloatArray,	GZ_DB_EXPORT);

	GZ_PROPERTY_GET_EXPORT(gzVec2,					CurrentVec2,		GZ_DB_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzDynamicArray<gzVec2>,	CurrentVec2Array,	GZ_DB_EXPORT);

	GZ_PROPERTY_GET_EXPORT(gzVec3,					CurrentVec3,		GZ_DB_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzDynamicArray<gzVec3>,	CurrentVec3Array,	GZ_DB_EXPORT);

	GZ_PROPERTY_GET_EXPORT(gzVec4,					CurrentVec4,		GZ_DB_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzDynamicArray<gzVec4>,	CurrentVec4Array,	GZ_DB_EXPORT);

	GZ_PROPERTY_GET_EXPORT(gzMatrix4,				CurrentMatrix4,		GZ_DB_EXPORT);

	GZ_PROPERTY_GET_EXPORT(gzDoubleXYZ,				CurrentDoubleXYZ,	GZ_DB_EXPORT);

	GZ_PROPERTY_GET_EXPORT(gzWeightValue,			CurrentWeightValue,	GZ_DB_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzWeight,				CurrentWeight,		GZ_DB_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzDynamicArray<gzWeight>,CurrentWeightArray,	GZ_DB_EXPORT);

	GZ_PROPERTY_EXPORT(gzDbInfoStatusBits,	Status,						GZ_DB_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,			StatusMessage,				GZ_DB_EXPORT);

private:

	friend class gzGZLReaderParser;

	gzBool onElementStart(const gzString &elementName,gzUInt32 level) override;
	gzBool onElementEnd(const gzString &elementName,gzUInt32 level) override;
	gzBool onProcessingInstruction(const gzString &target,const gzString &data,gzUInt32 level) override;
	gzBool onDynamicType(const gzDynamicType &data,const gzString &name,gzUInt32 level) override;

	gzRefList<gzGroup>	m_groupStack;
	gzRefList<gzObject>	m_objectStack;

	gzRefDict<gzUInt32CompareInterface,gzReference>	m_refData;

	class gzGZLReaderParser	*m_parser;
};

// ---------------------------- gzGZLWriter --------------------------------

class gzGZLWriter : public gzXmlSax
{
public:

	GZ_DB_EXPORT	gzGZLWriter(gzNode *node);
	GZ_DB_EXPORT	~gzGZLWriter();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_DB_EXPORT);	// RTTI

	GZ_DB_EXPORT	gzVoid writeNodeData(const gzString &className,const gzReference *data,gzBool newElement,gzBool newID,gzBool instanced);

	GZ_DB_EXPORT	gzUInt32 getLinkNumber(const gzReference *data);

private:

	virtual gzVoid	onWrite() override;

	gzNodePtr m_scene;

	gzDict<gzInstanceCompareInterface,gzVoid>		m_refValue;
};


#endif //__GZ_DB_GZL_H__
