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
// File			: gzTexGen.h
// Module		: 
// Description	: Class definition of the gzTexGen class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.224
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
// AMO	010110	Created file 	
//
//******************************************************************************
#ifndef __GZ_TEXGEN_H__
#define __GZ_TEXGEN_H__

/*!	\file 
	\brief Base definitions texture coordinate generation (TexGen)

*/


#include "gzObject.h"
#include "gzMatrix.h"
#include "gzImage.h"

class gzContext;

class gzTexGenData
{
public:

	gzTexGenData();

	gzVec4	param;

	gzInt16	coordType;

	gzInt16	paramType;

	gzInt16	enableFlag;

	gzBool	enable;

	GZ_GRAPH_EXPORT gzBool operator==(const gzTexGenData &right) const;
	GZ_GRAPH_EXPORT gzBool operator!=(const gzTexGenData &right) const { return !operator==(right); }
};

//******************************************************************************
// Class	: gzTexGen
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	010110	Created 
//									
//******************************************************************************
class gzTexGen : public gzObject
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzTexGen();
	GZ_GRAPH_EXPORT virtual ~gzTexGen(){};

	GZ_GRAPH_EXPORT gzVoid	virtual activate(gzContext *context);

	GZ_GRAPH_EXPORT static gzVoid deactivate(gzContext *context); 

	GZ_GRAPH_EXPORT gzVoid	setParam(gzInt16 coordType,gzBool enable,gzInt16 paramType=GZ_EYE_PLANE,const gzVec4 &param=gzVec4(0,0,0,0), gzInt16 enableFlag=(gzInt16)0);

	GZ_GRAPH_EXPORT gzVoid	setParam(gzInt16 coordType,gzBool enable,gzInt16 paramType=GZ_TEXTURE_GEN_MODE,gzInt16 param=GZ_EYE_LINEAR, gzInt16 enableFlag=(gzInt16)0);

	GZ_GRAPH_EXPORT gzVoid	resetParams();

	GZ_GRAPH_EXPORT gzBool operator==(const gzTexGen &right) const;

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
	GZ_GRAPH_EXPORT virtual gzBool useDeepCopy() override;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const override;


private:

	gzDynamicArray<gzTexGenData>	m_data;
};


#endif
