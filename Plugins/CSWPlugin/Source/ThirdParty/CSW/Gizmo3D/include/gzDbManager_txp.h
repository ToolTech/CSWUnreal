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
// File			: gzDbManager_txp.h
// Module		: 
// Description	: Class definition of the TerraPage format
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
// AMO	000226	Created file
// TSV  140109  Added methods
//				gzVoid processLabelPropertyTable(const gzUInt32 & size)
//				gzVoid processSupportStyleTable(const gzUInt32 & size)
//
//******************************************************************************
#ifndef __GZ_DB_TXP_H__
#define __GZ_DB_TXP_H__

/*!	\file 
	\brief Base definitions of a TerraPage database 

*/

#include "gzNode.h"
#include "gzGroup.h"
#include "gzGeometry.h"

// UserData Db INFO attributes
const gzString GZ_DB_INFO_TYPE_TERRAPAGE	="txp";

class gzTxpTileOffset
{
public:

	gzUInt32		fileID;
	gzUInt32		offset;
};

class gzTxpLodInfo
{
public:

	gzInt32XY					size;

	gzDouble					range;

	gzDoubleXY					tileSize;

	gzArray2D<gzTxpTileOffset>	offsetInfo;

	gzFloat						elevMax;

	gzFloat						elevMin;
};

class gzTxpMaterial : public gzReference
{
public:

	gzTxpMaterial():
		texID(-1),
		texEnvMode(3),
		minFilter(1),
		magFilter(1)
	{};

	virtual ~gzTxpMaterial(){};

	gzRefPointer<gzMaterial>	material;

	gzRefPointer<gzTexture>		texture;

	gzVec4						color;

	gzInt32						texID;

	gzUByte						texEnvMode:3;

	gzUByte						minFilter:3;

	gzUByte						magFilter:3;

	gzUByte						repeatS:1;

	gzUByte						repeatT:1;

	gzUByte						cullMode:2;


};

class gzTxpLocalMaterial : public gzReference
{
public:

	gzTxpLocalMaterial(){};
	virtual ~gzTxpLocalMaterial(){};

	gzInt32	baseMatTable;
	gzInt32	baseMat;

	gzArray<gzUInt32>			file;
	gzArray<gzUInt32>			offset;

	gzRefPointer<gzTexture>		texture;

};

class gzTxpTexture : public gzReference
{
public:

	gzTxpTexture()			{};
	virtual ~gzTxpTexture() {};

	gzString				image;
	gzBool					isMipMap;
	gzUByte					mode;
	gzUByte					type;
	gzUByte					layers;

	gzUInt32					sizeX;
	gzUInt32					sizeY;

	gzUInt32					file;
	gzUInt32					offset;
	
};


class gzTxpInfo : public gzReference
{
public:

	gzTxpInfo(const gzString &dir):	currentDirectory(dir)
									{};

	virtual ~gzTxpInfo(){};

	// All public valiables....

	gzInt32										numberOfLodLevels;
	gzInt32										numberOfMaterialTables;
	gzInt32										numberOfMaterialInTable;
							
	gzDoubleXYZ									origin;

	gzDoubleXY									sw;
	gzDoubleXY									ne;

	gzArray<gzTxpLodInfo>						lodInfo;

	gzInt32										numberOfSetLodLevels;

	gzString									currentDirectory;

	gzArray<gzRefPointer<gzTxpMaterial> >		materialArray;
	gzArray<gzRefPointer<gzTxpTexture> >		textureArray;
	gzArray<gzRefPointer<gzNode> >				modelArray;

	// Shared states created out of materials
	gzArray<gzRefPointer<gzState> >				stateArray;

	gzUByte										tileOriginType;

	gzBool										isArchived;

	gzUInt32										nodeIdBase;

	gzDouble									version;

	gzRoi										*roi;

	gzArray< gzArray2D<gzRefPointer<gzRoiNode> >	>					nodes;
	gzArray< gzArray2D<gzRefPointer<gzRoiDependancyInterface> >	>	dependencies;
};

class gzTptInfo : public gzReference
{
public:

	gzTptInfo(){};

	virtual ~gzTptInfo(){};

	gzUInt32XY									pos;

	gzDoubleXY									center;

	gzUInt32										lodLevel;

	gzDoubleXY									size;

	gzArray<gzRefPointer<gzTxpLocalMaterial> >	localMaterialArray;
	gzArray<gzRefPointer<gzState> >				stateArray;
	gzRefPointer<gzTxpLocalMaterial>			currentLocalMaterial;

	gzRoiNode									*roiNode;
};

class gzDbManager_txp_reader : public gzProgressInterface
{
public:

	gzDbManager_txp_reader(gzSerializeAdapter *adapter);
	
	virtual ~gzDbManager_txp_reader(){};

	gzNode	*loadDB();

	gzNode	*loadTile();

	gzVoid	setTxpInfo(gzTxpInfo *info);

private:

	gzNode *buildRoiGroup();

	gzSerializeAdapter *m_adapter;
	gzUInt32				m_fileSize;

	// Common private methods

	gzVoid processTokens(const gzUInt32 & size);
	gzVoid processHeader(const gzUInt32 & size);
	gzVoid processLodInfo(const gzUInt32 & size);

	gzVoid processMaterialTable(const gzUInt32 & size);
	gzVoid processMaterialTable2(const gzUInt32 & size);

	gzVoid processBasicMaterial(const gzUInt32 & size);
	gzVoid processShadeMaterial(const gzUInt32 & size);
	gzVoid processSizeMaterial(const gzUInt32 & size);
	gzVoid processCullMaterial(const gzUInt32 & size);
	gzVoid processAlphaMaterial(const gzUInt32 & size);
	gzVoid processNormalMaterial(const gzUInt32 & size);
	gzVoid processTextureMaterial(const gzUInt32 & size);
	gzVoid processBumpMaterial(const gzUInt32 & size);
	gzVoid processAttrMaterial(const gzUInt32 & size);

	gzVoid processModeTexEnv(const gzUInt32 & size);
	gzVoid processFilterTexEnv(const gzUInt32 & size);
	gzVoid processWrapTexEnv(const gzUInt32 & size);
	gzVoid processBorderTexEnv(const gzUInt32 & size);

	gzVoid processTexTable(const gzUInt32 & size);
	gzVoid processTexture(const gzUInt32 & size);

	gzVoid processTexTable2(const gzUInt32 & size);
	gzVoid processTexture2(const gzUInt32 & size);

	gzVoid processModelTable(const gzUInt32 & size);
	gzVoid processModelRef(const gzUInt32 & size);
	gzVoid processModelRefDef1(const gzUInt32 & size);
	gzVoid processModelRefDef2(const gzUInt32 & size);
	gzVoid processLight(const gzUInt32 & size);
	gzVoid processLabel(const gzUInt32 & size);
	gzVoid processLabelPropertyTable(const gzUInt32 & size);
	gzVoid processTileTable2(const gzUInt32 & size);
	gzVoid processLightTable(const gzUInt32 & size);
	gzVoid processRangeTable(const gzUInt32 & size);
	gzVoid processRange(const gzUInt32 & size);
	gzVoid processTextStyleTable(const gzUInt32 & size);
	gzVoid processTextStyle(const gzUInt32 & size);
	gzVoid processSupportStyleTable(const gzUInt32 & size);

	gzVoid processTileHeader(const gzUInt32 & size);
	gzVoid processTileMaterialList(const gzUInt32 & size);
	gzVoid processTileModelList(const gzUInt32 & size);
	gzVoid processTileDate(const gzUInt32 & size);
	gzVoid processTileLocalMaterialList(const gzUInt32 & size);
	gzVoid processLocalMaterial(const gzUInt32 & size);
	gzVoid processChildReference(const gzUInt32 & size);

	gzVoid processGroup(const gzUInt32 & size);
	gzVoid processBillboard(const gzUInt32 & size);
	gzVoid processAttach(const gzUInt32 & size);
	gzVoid processLod(const gzUInt32 & size);

	gzVoid	processGeometry(const gzUInt32 & size);
	gzVoid	processGeometryPrim(const gzUInt32 & size);
	gzVoid	processGeometryMaterial(const gzUInt32 & size);
	gzVoid	processGeometryVert32(const gzUInt32 & size);
	gzVoid	processGeometryVert64(const gzUInt32 & size);
	gzVoid	processGeometryNorm32(const gzUInt32 & size);
	gzVoid	processGeometryNorm64(const gzUInt32 & size);
	gzVoid	processGeometryColor(const gzUInt32 & size);
	gzVoid	processGeometryTex32(const gzUInt32 & size);
	gzVoid	processGeometryTex64(const gzUInt32 & size);


	gzVoid	processPush();
	gzVoid	processPop();


	// Common serializers

	gzSerializeBinary<gzUInt32>		s_ulong;
	gzSerializeBinary<gzUInt64>	s_ulonglong;
	gzSerializeBinary<gzInt32>		s_long;
	gzSerializeBinary<gzDouble>		s_double;
	gzSerializeBinary<gzFloat>		s_float;
	gzSerializeBinary<gzUByte>		s_ubyte;

	gzArray<gzUByte>				s_data;
	gzSerializeString				s_string;

	// processed data

	gzRefPointer<gzTxpInfo>		m_txpInfo;

	gzRefPointer<gzTptInfo>		m_tptInfo;

	// Work Data

	gzVoid clean();

	gzRefPointer<gzGroup>			currentParent;

	gzRefPointer<gzNode>			currentNode;

	gzRefPointer<gzGroup>			topGroup;

	gzRefList<gzGroup>				stack;

	// Current geometry info

	gzDynamicArray<gzUInt32>					geoPrimLens;

	gzDynamicArray<gzInt32>					geoPrimMaterials;

	gzDynamicArray<gzVec3>					geoPrimCoordinates;

	gzDynamicArray<gzVec3>					geoPrimNormals;

	gzDynamicArray<gzVec4>					geoPrimColors;

	gzDynamicArray<gzDynamicArray<gzVec2> >	geoPrimTexCoords;

	gzGeoPrimType							geoPrimType;

	// State & Material

	gzRefPointer<gzTxpMaterial>		m_currentMaterial;
	gzRefPointer<gzTxpTexture>		m_currentTexture;

};

//----------------------------------------------------------------------------------------------------

class gzDbManager_txp : public gzDbManager	
{
public:

	GZ_DB_EXPORT gzDbManager_txp();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	//GZ_DB_EXPORT virtual gzBool		saveDB(gzNode *node ,gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;
};

class gzDbManager_tpt : public gzDbManager	
{
public:

	GZ_DB_EXPORT gzDbManager_tpt();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	//GZ_DB_EXPORT virtual gzBool		saveDB(gzNode *node ,gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;
};

#endif
