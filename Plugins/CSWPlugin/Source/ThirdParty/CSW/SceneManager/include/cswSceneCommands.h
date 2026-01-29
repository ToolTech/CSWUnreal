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
// ------------------------ cswSceneCommandResponse -------------------------------

class cswSceneCommandResponse : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandResponse(const gzUInt32 commandRefID = 0);
	GZ_PROPERTY_EXPORT(gzUInt32, CommandRefID, CSW_SM_EXPORT);

};

GZ_DECLARE_REFPTR(cswSceneCommandResponse);

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

// ------------------------ cswSceneCommandRemoveObject -------------------------------

class cswSceneCommandRemoveObject : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandRemoveObject(const gzString& objectName);

	GZ_PROPERTY_EXPORT(gzString, Name, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandClearMaps -------------------------------

class cswSceneCommandClearMaps : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandSetCamera -------------------------------

class cswSceneCommandSetCamera : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandSetCamera(gzPerspCamera *camera);

	GZ_PROPERTY_EXPORT(gzPerspCameraPtr, Camera, CSW_SM_EXPORT);
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

// ------------------------ cswSceneCommandSetLodFactor -------------------------------

class cswSceneCommandSetLodFactor : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandSetLodFactor(const gzFloat& lodFactor);

	GZ_PROPERTY_EXPORT(gzFloat, LodFactor, CSW_SM_EXPORT);
};


// ------------------------ cswSceneCommandError -------------------------------

class cswSceneCommandErrorMessage : public cswSceneCommandResponse
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandErrorMessage(const gzMessageLevel &messageLevel,const gzString &errorMessage,const gzUInt32 &commandRefID=0);

	GZ_PROPERTY_EXPORT(gzMessageLevel, MessageLevel, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzString, Message, CSW_SM_EXPORT);


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

class cswSceneCommandGeoInfo : public cswSceneCommandResponse
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandGeoInfo(const gzString &coordinateSystem,const gzVec3D &origin, const gzUInt32 commandRefID = 0);

	GZ_PROPERTY_EXPORT(gzString, CoordinateSystem, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3D, Origin, CSW_SM_EXPORT);

};


// ------------------------ cswSceneCommandAddObject -------------------------------

class cswSceneCommandAddObject : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandAddObject(const gzString &name, gzNode* node, const gzVec3D& position, const gzDouble& loadDistance = 10000, const gzDouble& purgeDistance = 10000);

	GZ_PROPERTY_EXPORT(gzString,	Name, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzNodePtr,	Node, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3D,		Position, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,	LoadDistance, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,	PurgeDistance, CSW_SM_EXPORT);

};

// ------------------------ cswSceneCommandInstance -------------------------------

class cswSceneCommandInstance : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandInstance(gzNode* node, const gzUInt64& pathID);

	GZ_PROPERTY_EXPORT(gzNodePtr, Node, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt64, PathID, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandHierarchyInstance -------------------------------

class cswSceneCommandHierarchyInstance : public cswSceneCommandInstance
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandHierarchyInstance(gzNode* node, const gzUInt64& pathID, gzGroup* parent, const gzUInt64& parentPathID);

	// -------------------- Parent -----------------------------------------------

	GZ_PROPERTY_EXPORT(gzGroupPtr, Parent, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt64, ParentPathID, CSW_SM_EXPORT);
};


// ------------------------ cswSceneCommandNewNode -------------------------------

class cswSceneCommandNewNode : public cswSceneCommandHierarchyInstance
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandNewNode(gzNode *node, const gzUInt64& pathID, gzGroup *parent, const gzUInt64& parentPathID, gzState *state, const gzUInt32 commandRefID = 0);

	GZ_PROPERTY_EXPORT(gzStatePtr, State, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandDeleteNode -------------------------------

class cswSceneCommandDeleteNode : public cswSceneCommandInstance
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandDeleteNode(gzNode* node, const gzUInt64& pathID);
};

// ------------------------ cswSceneCommandActivation -------------------------------

class cswSceneCommandActivation : public cswSceneCommandInstance
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandActivation(gzNode* node, const gzUInt64& pathID, const Activation& activation);

	GZ_PROPERTY_EXPORT(Activation, Activation, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandPositionCamera -------------------------------

class cswSceneCommandPositionCamera : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandPositionCamera(const gzVec3D &position , const gzVec3 &hpr = GZ_ZERO_VEC3 , const gzFloat &hfov=50,const gzFloat& vfov=50);

	GZ_PROPERTY_EXPORT(gzVec3D,		Position, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzVec3,	HPR, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat, HFOV, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat, VFOV, CSW_SM_EXPORT);

};

// ------------------------ cswSceneCommandCameraSettings -------------------------------

class cswSceneCommandCameraSettings : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandCameraSettings(const gzFloat& nearDistance,const gzFloat &farDistance, const gzBool infiniteFar=FALSE);

	GZ_PROPERTY_EXPORT(gzFloat, NearDistance, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat, FarDistance, CSW_SM_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool, InfiniteFar, CSW_SM_EXPORT);

};

// ------------------------ cswSceneCommandRequestCameraPosition -------------------------------

class cswSceneCommandRequestCameraPosition : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandRequestCameraPosition();
};

// ------------------------ cswSceneCommandCameraPositionResponse -------------------------------

class cswSceneCommandCameraPositionResponse : public cswSceneCommandResponse
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandCameraPositionResponse(gzPerspCamera* camera, const gzBool status = TRUE, const gzUInt32 commandRefID = 0);

	GZ_PROPERTY_EXPORT(gzBool,	Status, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3D,		Position, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,	HPR, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat, HFOV, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat, VFOV, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandRequestGroundClampPosition -------------------------------

class cswSceneCommandRequestGroundClampPosition : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandRequestGroundClampPosition(const gzDouble& latitude, const gzDouble& longitude, const gzDouble& heightAboveGround = 1000, const gzBool& waitForData = FALSE);

	GZ_PROPERTY_EXPORT(gzDouble,	Latitude, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,	Longitude, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,	HeightAboveGround, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,		WaitForData, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandGroundClampPositionResponse -------------------------------

class cswSceneCommandGroundClampPositionResponse : public cswSceneCommandResponse
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandGroundClampPositionResponse(const gzBool& clampResult, const gzVec3D& position, const gzVec3& normal, const gzVec3& up, const gzUInt32 commandRefID = 0);

	GZ_PROPERTY_EXPORT(gzBool,	ClampResult, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3D,		Position, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,	Normal, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,	Up, CSW_SM_EXPORT);
};

// ------------------------ cswSceneCommandKeyPressed -------------------------------

class cswSceneCommandKeyPressed : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandKeyPressed(const gzUInt32 key, const gzUInt32 keyState, const gzInt32 mouseX, const gzInt32 mouseY);

	GZ_PROPERTY_EXPORT(gzUInt32, Key, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32, KeyState, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzInt32, MouseX, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzInt32, MouseY, CSW_SM_EXPORT);
};
// ------------------------ cswSceneCommandIntersect -------------------------------

class cswSceneCommandIntersect : public cswSceneCommand
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandIntersect(const gzVec3D& start, const gzVec3& direction, const gzBool waitForData = FALSE, const gzIntersectMaskValue& intersectMask = (gzIntersectMaskValue)(GZ_INTERSECT_MASK_GROUND | GZ_INTERSECT_MASK_WATER));

	GZ_PROPERTY_EXPORT(gzVec3D, Start,			CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,	Direction,		CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,	WaitForData,	CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzIntersectMaskValue,	IntersectMask,	CSW_SM_EXPORT);
};
// ------------------------ cswSceneCommandIntersectResponse -------------------------------

class cswSceneCommandIntersectResponse : public cswSceneCommandResponse
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandIntersectResponse(const gzBool status = FALSE, const gzVec3D& position = gzVec3D(0,0,0), const gzVec3& normal = GZ_ZERO_VEC3, const gzFloat& distance = 0, const gzVec3& a = GZ_ZERO_VEC3, const gzVec3& b = GZ_ZERO_VEC3, const gzVec3& c = GZ_ZERO_VEC3, gzNode* hitNode = nullptr, const gzUInt32 commandRefID = 0);

	GZ_PROPERTY_EXPORT(gzBool,	Status,		CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3D,		Position, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,	Normal,		CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat, Distance,	CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,	A,			CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,	B,			CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,	C,			CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(gzNodePtr,	HitNode,	CSW_SM_EXPORT);
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

class cswSceneCommandEndFrame : public cswSceneCommandResponse
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSW_SM_EXPORT);

	CSW_SM_EXPORT cswSceneCommandEndFrame(const gzUInt32 &refreshID);

	GZ_PROPERTY_GET_EXPORT(gzUInt32, RefreshID, CSW_SM_EXPORT);
};
