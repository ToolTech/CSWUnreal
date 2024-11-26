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
// File			: cswSceneCommands.h
// Module		: cswSceneManager
// Description	: Definition of commands from/to SceneManager
// Author		: Anders Modén		
// Product		: CSW 1.1.1
//		
//
//			
// NOTE:	CSW (Common Synthetic World) is a simulation and presentation
//			framework for large scale digital twins on multiple platforms
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	240912	Created file 					(1.1.1)
//
//******************************************************************************
#pragma once

#include "cswSceneManagerBase.h"

//******************************************************************************
// Class	: cswSceneCommand
//
// Purpose  : Base class definition of command items used in communication with scene manager
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	240912	Created		(1.1.1)
//									
//******************************************************************************
class cswSceneCommand : public gzReference
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommand();

	GZ_PROPERTY_GET_EXPORT(gzUInt32, ID, CSW_SM_EXPORT);
};

GZ_DECLARE_REFPTR(cswSceneCommand);

// ------------------------ cswSceneCommandInitialize -------------------------------

class cswSceneCommandInitialize : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandInitialize(const gzBool &CreateDefaultViewer = FALSE, gzReference* window = nullptr, gzReference* application = nullptr);

	GZ_PROPERTY_EXPORT(gzBool,				CreateDefaultViewer,	CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzReferencePtr ,		Window,					CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzReferencePtr ,		Application,			CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandUnInitialize -------------------------------

class cswSceneCommandUnInitialize : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandUnInitialize();
};

// ------------------------ cswSceneCommandSetRenderTime -------------------------------

class cswSceneCommandSetRenderTime : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandSetRenderTime(const gzDouble& time);

	GZ_PROPERTY_EXPORT(gzDouble, RenderTime, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandAddNewMap -------------------------------

class cswSceneCommandAddNewMap : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandAddNewMap(const gzString& mapURL);

	GZ_PROPERTY_EXPORT(gzString, MapURL, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandSetMapUrls -------------------------------

class cswSceneCommandSetMapUrls : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandSetMapUrls(const gzString& mapURLs);

	GZ_PROPERTY_EXPORT(gzString, MapURLs, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandRemoveMap -------------------------------

class cswSceneCommandRemoveMap : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandRemoveMap(const gzString& mapURL);

	GZ_PROPERTY_EXPORT(gzString, MapURL, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandSetCamera -------------------------------

class cswSceneCommandSetCamera : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandSetCamera(gzCamera *camera);

	GZ_PROPERTY_EXPORT(gzCameraPtr, Camera, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandRefreshScene -------------------------------

class cswSceneCommandRefreshScene : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandRefreshScene(const gzDouble& time=0, const gzUInt32 &size_x=1000, const gzUInt32 &size_y=1000, const gzUInt32 &screen_width=1000);

	GZ_PROPERTY_EXPORT(gzDouble, RenderTime, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32, SizeX, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32, SizeY, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32, ScreenWidth, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandSetOmniTraverse -------------------------------

class cswSceneCommandSetOmniTraverse : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandSetOmniTraverse(const gzBool &omniTraverse);

	GZ_PROPERTY_EXPORT(gzBool, OmniTraverse, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandSetLoaders -------------------------------

class cswSceneCommandSetLoaders : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandSetLoaders(const gzUInt32 &numberOfLoaders, const gzBool &runLoaders=TRUE, const gzBool &precacheTextures=TRUE);

	GZ_PROPERTY_EXPORT(gzUInt32, NumberOfLoaders, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool, RunLoaders, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool, PreCacheTextures, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandError -------------------------------

class cswSceneCommandErrorMessage : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandErrorMessage(const gzMessageLevel &messageLevel,const gzString &errorMessage,const gzUInt32 &commandRefID=0);

	GZ_PROPERTY_EXPORT(gzMessageLevel, MessageLevel, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzString, Message, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt32, CommandRefID, CSW_SM_EXPORT);

};

// ------------------------ cswSceneCommandCenterMaps -------------------------------

class cswSceneCommandCenterMaps : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandCenterMaps(const gzDouble &altitude=200, const gzVec3 &hpr=GZ_ZERO_VEC3);

	GZ_PROPERTY_EXPORT(gzDouble, Altitude, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzVec3, HPR, CSW_SM_EXPORT);

};

// ------------------------ cswSceneCommandGeoInfo -------------------------------

class cswSceneCommandGeoInfo : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandGeoInfo(const gzString &coordinateSystem,const gzVec3D &origin);

	GZ_PROPERTY_EXPORT(gzString, CoordinateSystem, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3D, Origin, CSW_SM_EXPORT);

};

// ------------------------ cswSceneCommandInstance -------------------------------

class cswSceneCommandInstance : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandInstance(gzNode* node, gzGroup* parent, const gzUInt64 &pathID);

	GZ_PROPERTY_EXPORT(gzNodePtr, Node, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzGroupPtr, Parent, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt64, PathID, CSW_SM_EXPORT);

};

// ------------------------ cswSceneCommandNewNode -------------------------------

class cswSceneCommandNewNode : public cswSceneCommandInstance
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandNewNode(gzNode *node,gzGroup *parent, const gzUInt64 &pathID , gzState *state);

	GZ_PROPERTY_EXPORT(gzStatePtr, State, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandDeleteNode -------------------------------

class cswSceneCommandDeleteNode : public cswSceneCommandInstance
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandDeleteNode(gzNode* node, gzGroup* parent, const gzUInt64 &pathID);
};

// ------------------------ cswSceneCommandActivation -------------------------------

class cswSceneCommandActivation : public cswSceneCommandInstance
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandActivation(gzNode* node, gzGroup* parent, const gzUInt64& pathID, const Activation& activation);

	GZ_PROPERTY_EXPORT(Activation, Activation, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandPositionCamera -------------------------------

class cswSceneCommandPositionCamera : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandPositionCamera(const gzVec3D &position , const gzVec3 &hpr = GZ_ZERO_VEC3);

	GZ_PROPERTY_EXPORT(gzVec3D, Position, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzVec3, HPR, CSW_SM_EXPORT);

};

// ------------------------ cswSceneCommandStartFrame -------------------------------

class cswSceneCommandStartFrame : public cswSceneCommandPositionCamera
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandStartFrame(const gzUInt32 &refreshID, const gzDouble &renderTime, const gzVec3D &position, const gzVec3 &hpr = GZ_ZERO_VEC3);

	GZ_PROPERTY_EXPORT(gzDouble, RenderTime, CSW_SM_EXPORT);

	GZ_PROPERTY_GET_EXPORT(gzUInt32, RefreshID, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandEndFrame -------------------------------

class cswSceneCommandEndFrame : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandEndFrame(const gzUInt32 &refreshID);

	GZ_PROPERTY_GET_EXPORT(gzUInt32, RefreshID, CSW_SM_EXPORT);
};
