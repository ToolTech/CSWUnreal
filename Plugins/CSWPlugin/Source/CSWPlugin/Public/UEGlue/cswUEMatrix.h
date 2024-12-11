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
// File			: cswUEMatrix.h
// Module		: CSW StreamingMap Unreal
// Description	: Utilities for UE Transforms from GizmoSDK
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
// AMO	241107	Created file 					(1.1.1)
//
//******************************************************************************

#pragma once

#include "Math/Matrix.h"
#include "Math/Vector.h"

#include "gzMatrix.h"

// ----------------------------------- Vec2 ------------------------------------------

template <class T> class cswVector2_
{
public:

	template <class Y> static UE::Math::TVector2<T> UEVector2(const gzVec2_<Y>& from)
	{
		return UE::Math::TVector2<T>(from.x, from.y);
	}
};

typedef cswVector2_<gzFloat>	cswVector2;
typedef cswVector2_<gzDouble>	cswVector2d;

// ----------------------------------- Vec3 ------------------------------------------

template <class T> class cswVector3_
{
public:

	template <class Y> static UE::Math::TVector<T> UEVector3(const gzVec3_<Y>& from)
	{
		return UE::Math::TVector<T>(from.x, from.y, from.z);
	}
};

typedef cswVector3_<gzFloat>	cswVector3;
typedef cswVector3_<gzDouble>	cswVector3d;

// ----------------------------------- Vec4 ------------------------------------------

template <class T> class cswVector4_
{
public:

	template <class Y> static UE::Math::TVector4<T> UEVector4(const gzVec4_<Y>& from)
	{
		return UE::Math::TVector4<T>(from.v1, from.v2, from.v3,from.v4);
	}
};

typedef cswVector4_<gzFloat>	cswVector4;
typedef cswVector4_<gzDouble>	cswVector4d;


// -----------------------------------------------------------------------------

template <class T> class cswMatrix4_
{
public:

	template <class Y> static UE::Math::TMatrix<T> UEMatrix4(const gzMatrix4_<Y>& from = gzGetUnitMatrix())
	{
		UE::Math::TMatrix<T> UEMatrix;

		UEMatrix.M[0][0] = from.v11;
		UEMatrix.M[0][1] = from.v21;
		UEMatrix.M[0][2] = from.v31;
		UEMatrix.M[0][3] = from.v41;

		UEMatrix.M[1][0] = from.v12;
		UEMatrix.M[1][1] = from.v22;
		UEMatrix.M[1][2] = from.v32;
		UEMatrix.M[1][3] = from.v42;

		UEMatrix.M[2][0] = from.v13;
		UEMatrix.M[2][1] = from.v23;
		UEMatrix.M[2][2] = from.v33;
		UEMatrix.M[2][3] = from.v43;

		UEMatrix.M[3][0] = from.v14;
		UEMatrix.M[3][1] = from.v24;
		UEMatrix.M[3][2] = from.v34;
		UEMatrix.M[3][3] = from.v44;

		return UEMatrix;
	}

	template <class Y> static gzMatrix4_<Y> GZMatrix4(const UE::Math::TMatrix<T>& from = UE::Math::TMatrix<T>::Identity)
	{
		gzMatrix4_<Y> GZMatrix;

		GZMatrix.v11 = from.M[0][0];
		GZMatrix.v21 = from.M[0][1];
		GZMatrix.v31 = from.M[0][2];
		GZMatrix.v41 = from.M[0][3];

		GZMatrix.v12 = from.M[1][0];
		GZMatrix.v22 = from.M[1][1];
		GZMatrix.v32 = from.M[1][2];
		GZMatrix.v42 = from.M[1][3];

		GZMatrix.v13 = from.M[2][0];
		GZMatrix.v23 = from.M[2][1];
		GZMatrix.v33 = from.M[2][2];
		GZMatrix.v43 = from.M[2][3];

		GZMatrix.v14 = from.M[3][0];
		GZMatrix.v24 = from.M[3][1];
		GZMatrix.v34 = from.M[3][2];
		GZMatrix.v44 = from.M[3][3];

		return GZMatrix;
	}

	static gzMatrix4_<T> GZ_2_UE();
	static gzMatrix4_<T> UE_2_GZ();

	static gzMatrix4_<T> GZ_2_UE_GEO_Flat();
	static gzMatrix4_<T> GZ_2_UE_GEO_Cartesian();

};


template <class T> inline gzMatrix4_<T>  cswMatrix4_<T>::GZ_2_UE()
{
	// Map GZ(X,Y,Z) to UE(X,Z,Y)
	return gzMatrix4D(gzVec4D(1, 0, 0, 0), gzVec4D(0, 0, 1, 0), gzVec4D(0, 1, 0, 0), gzVec4D(0, 0, 0, 1));
}

template <class T> inline gzMatrix4_<T>  cswMatrix4_<T>::UE_2_GZ()
{
	// Map UE(X,Y,Z) to GZ(X,Z,Y)
	return gzMatrix4D(gzVec4D(1, 0, 0, 0), gzVec4D(0, 0, 1, 0), gzVec4D(0, 1, 0, 0), gzVec4D(0, 0, 0, 1));
}

template <class T> inline gzMatrix4_<T>  cswMatrix4_<T>::GZ_2_UE_GEO_Cartesian()
{
	// Map GZ(X,Y,Z) to UE(X,-Y,Z)
	return gzMatrix4D(gzVec4D(1, 0, 0, 0), gzVec4D(0, -1, 0, 0), gzVec4D(0, 0, 1, 0), gzVec4D(0, 0, 0, 1));
}

typedef cswMatrix4_<gzFloat>	cswMatrix4;
typedef cswMatrix4_<gzDouble>	cswMatrix4d;