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
// File			: gzDbManager_gzd.h
// Module		: 
// Description	: Class definition of the gizmo db format
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.211
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
// AMO	990401	Created file 	
// AMO	101224	Version 3										(2.5.16)
// AMO	111107	Version 5										(2.5.28)
// AMO	111201	Version 6										(2.5.33)
// AMO	120614	Version 7										(2.6.8)
// AMO	120626	Version 8										(2.6.8)
// AMO	121016	Version 9										(2.6.16)
// AMO	121120	Version 10										(2.6.18)
// TSV	140131	Version 11										(2.7.5)
// AMO	140730	Version 12										(2.7.9)
// AMO	180604	Version 13										(2.9.1)
// AMO	181213	Version 14										(2.10.1)
// AMO	200318	Version 15										(2.10.5)
// AMO	200520	Version 16										(2.10.5)
// AMO	200703	Version 17										(2.10.6)
// AMO	230527	Version 18										(2.12.81)
// AMO	231129	Setting default version to version 18			(2.12.125)
//
//******************************************************************************
#ifndef __GZ_DB_GZD_H__
#define __GZ_DB_GZD_H__

/*!	\file 
	\brief Base definitions of a Gizmo3D (gzd) database 

*/

#include "gzNode.h"

// Current Version Defines
#define GZ_GZD_VERSION			18
#define GZ_GZD_MAGIC_NUMBER LLU(0x196806012537BADA)

// Version 2 - First public release
// This release was primarily intended to store some basic 
// features used by the Rapid Mapping format and some simple models

// Version 3 - added features
//		gzState: separate front and back render 
//		gzSwitch: New
//		gzRoi: property UseOnlyRoiNodes
//		gzParticleSystem: New
//		gzParticleSystemSmoke: New
//		gzParticleEmitter: New
//		gzParticlePointEmitter: New
//		gzParticleSpace: New
//		gzRoi: CullDisableDistance

// Version 4 - added features
//		gzFaceboard: new
//		gzGeometrySphere: new
//		gzGeometryTube: new
//		gzGeometryAxis: new

// Version 5 - added features
//		gzGeometry: updated with smoothing info, shadow info etc.
//		gzFrameTransform: new
//		gzFrame: new
//		gzCrossVolume: new

// Version 6 - added features
//		gzParticleSmoke: fuzzyDepth
//		gzGFXProgram: FeatureVariant
//		gzRefImage: new

// Version 7 - added features
//		gzLod: TranspLodStage
//		gzDummyBoundary: new
//		gzResourceGroup: new

// Version 8 - added features
//		gzCrossVolume: CrossVolumeTextureData
//		gzCrossBoard: CrossBoardTextureData

// Version 9 - added features
//		gzDynamicLoad: Exclusive load

// Version 10 - added features
//		gzDynamicLoad: LoadOnAccess and Timeout
//		gzLoadDependancyGroup: new

// Version 11 - added features
//		gzParticleSmoke: LocalWindSpeed
//		gzParticleSmoke: LocalGravity
//		gzParticleEmitter: ParticleType
//		gzFontInfo: new
//		gzText: new

// Version 12 - added features
//		gzTexture: Compare Mode
//		gzTexture: Compare Func
//		gzRotor: new
//		gzParticleEmitter: ParticleColor

// Version 13 - added features
//		gzMatrix: removed all refs to faceMatrixMode and dirty flags - purify
//		gzRoi: added radius
//		gzExtRef : new

// Version 14 - added features
//		gzCrossboard: changed lod use to colors and disable lod for older db versions, disable min/max size
//		gzFaceboard: changed lod use to colors and disable lod for older db versions, disable min/max size
//		gzCrossVolume: changed lod use to colors and disable lod for older db versions, disable min/max size

// Version 15 - added features
//		gzImage now supports ETC2 compressed images

// Version 16 - added features	(DEFAULT WE)
//		gzDynamicLoader : now supports saving/loading child hierarch
//		gzDynamicLoaded : added force enable/disable lod masks
//		gzDynamicLoader : added ClearForceLocalInclude that clears local force include if we have a radius
//		gzRoiQuadDependancyCounter : now supports main dependancy 
//		gzForceTraverse : new

// Version 17 - added features
//		gzGeometry : now with added instance counter

// Version 18 - added features
//		gzText : now with center position
//		gzTexture : texture has name
//		gzVertexAttribute: vertex attributes correctly saved with binding etc.
//		gzFrameTransform : now uses interpolation modes
//		gzFrame : now saves uniform frame duration

// Version 19 - added features (in progress)
//		gzImage : subImageType
//
// 

// UserData Db INFO attributes
const gzString GZ_DB_INFO_TYPE_GIZMO3D				= "gzd";
const gzString GZ_DB_INFO_TYPE_GIZMO3D_COMPRESSED	= "zzd";
const gzString GZ_LICENSE_PREFIX					= "LICENSE_";

//******************************************************************************
// Class	: gzDbManager_gzd
//									
// Purpose  : Reader/Writer for Gizmo3D file format
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	010508	Created 
//									
//******************************************************************************
class gzDbManager_gzd : public gzDbManager	
{
public:

	GZ_DB_EXPORT gzDbManager_gzd();
	GZ_DB_EXPORT virtual ~gzDbManager_gzd();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzBool		saveDB(gzNode *node , gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;

	//----- Module dependency ------

	GZ_DB_EXPORT static gzVoid registerModuleDependency(const gzString &module);
	GZ_DB_EXPORT static gzVoid unregisterModuleDependency(const gzString &module);
	GZ_DB_EXPORT static gzVoid clearModuleDependencies();
	GZ_DB_EXPORT static gzBool hasModuleDependency(const gzString &module);



protected:

	GZ_DB_EXPORT virtual gzVoid		registerManager(const gzString &extension) override;

private:
	
	static gzMutex					s_moduleDependancyLocker;
	static gzDict<gzString,gzVoid>  s_moduleDependencyDict;
};

//******************************************************************************
// Class	: gzDbManager_zzd
//									
// Purpose  : Reader/Writer for Gizmo3D file format, compressed
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	090129	Created 
//									
//******************************************************************************
class gzDbManager_zzd : public gzDbManager	
{
public:

	GZ_DB_EXPORT gzDbManager_zzd();
	GZ_DB_EXPORT virtual ~gzDbManager_zzd();

	GZ_DB_EXPORT virtual gzNode	*	loadDB(gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzBool		saveDB(gzNode *node , gzSerializeAdapter *adapter) override;

	GZ_DB_EXPORT virtual gzString	getExtensions() override;

	GZ_DB_EXPORT virtual gzUInt32	getVersion(const gzString &extension) override;

	GZ_DB_EXPORT virtual gzBool		canSave() override;

protected:

	GZ_DB_EXPORT virtual gzVoid		registerManager(const gzString &extension) override;
};

#endif // __GZ_DB_GZD_H__

