//******************************************************************************
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
// File			: gzGraphicsAbstractionLayer.h
// Module		: gzGraph
// Description	: Class implementation of the GAL classes
// Author		: Anders ModÈn		
// Product		: Gizmo3D 2.12.222
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
// AMO	990103	Created file 	
//
//******************************************************************************

#ifndef __GZ_GRAPHICS_ABSTRACTION_LAYER_H__
#define __GZ_GRAPHICS_ABSTRACTION_LAYER_H__

/*!	\file 
	\brief Low level API bridge between Gizmo3D low level API and the system API

  The user can select the type of system interface he wishes to use. E.g OpenGL or DirectX

*/

#include "gzBasicTypes.h"
#include "gzBase.h"
#include "gzMatrix.h"

// Some forward declarations for context management
class gzContext;
class gzGraphicsFormat;

//--------------------- gzGraphicsAbstractionLayer -------------------------------------------

class GZ_GRAPH_EXPORT gzGraphicsAbstractionLayer
{
public:

	static	gzVoid	(GZ_CALLBACK *	imp_gzBegin)(gzEnum);
	static  gzVoid	(GZ_CALLBACK *	imp_gzEnd)();

	static	gzVoid	(GZ_CALLBACK *	imp_gzEnable)(gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDisable)(gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzEnableClientState)(gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDisableClientState)(gzEnum);

	static	gzVoid	(GZ_CALLBACK *	imp_gzHint)(gzEnum,gzEnum);

	static	gzVoid	(GZ_CALLBACK *	imp_gzFrustum)(gzDouble,gzDouble,gzDouble,gzDouble,gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFrustumf)(gzFloat,gzFloat,gzFloat,gzFloat,gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzOrtho)(gzDouble,gzDouble,gzDouble,gzDouble,gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzOrthof)(gzFloat,gzFloat,gzFloat,gzFloat,gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzViewport)(gzInt32,gzInt32,gzInt32,gzInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzScissor)(gzInt32,gzInt32,gzInt32,gzInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDepthRange)(gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDepthRangef)(gzFloat,gzFloat);


	static	gzVoid	(GZ_CALLBACK *	imp_gzColor4d)(gzDouble,gzDouble,gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzColor4f)(gzFloat,gzFloat,gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzColor4dv)(const gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzColor4fv)(const gzFloat *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertex3d)(gzDouble,gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertex3f)(gzFloat,gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertex3dv)(const gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertex3fv)(const gzFloat*);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertex2i)(gzInt32,gzInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertex3i)(gzInt32,gzInt32,gzInt32);

	static	gzVoid	(GZ_CALLBACK *	imp_gzNormal3d)(gzDouble,gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzNormal3f)(gzFloat,gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzNormal3dv)(const gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzNormal3fv)(const gzFloat *);


	static	gzVoid	(GZ_CALLBACK *	imp_gzTexCoord2d)(gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzTexCoord2f)(gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzTexCoord2dv)(const gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzTexCoord2fv)(const gzFloat *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzEdgeFlag)(gzBool);

	static	gzVoid	(GZ_CALLBACK *	imp_gzMatrixMode)(gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzLoadIdentity)();

	static	gzVoid	(GZ_CALLBACK *	imp_gzLoadMatrixd)(const gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzLoadMatrixf)(const gzFloat *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzMultMatrixd)(const gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzMultMatrixf)(const gzFloat *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzPushMatrix)();
	static	gzVoid	(GZ_CALLBACK *	imp_gzPopMatrix)();

	static	gzVoid	(GZ_CALLBACK *	imp_gzRotated)(gzDouble,gzDouble,gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzRotatef)(gzFloat,gzFloat,gzFloat,gzFloat);

	static	gzVoid	(GZ_CALLBACK *	imp_gzTranslated)(gzDouble,gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzTranslatef)(gzFloat,gzFloat,gzFloat);

	static	gzVoid	(GZ_CALLBACK *	imp_gzScaled)(gzDouble,gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzScalef)(gzFloat,gzFloat,gzFloat);

	static	gzVoid	(GZ_CALLBACK *	imp_gzPointSize)(gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDrawBuffer)(gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzReadBuffer)(gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzLineWidth)(gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzLineStipple)(gzInt32,gzUInt16);
	

	static	gzVoid	(GZ_CALLBACK *	imp_gzPolygonMode)(gzEnum,gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzCullFace)(gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDepthFunc)(gzEnum);

	static	gzVoid	(GZ_CALLBACK *	imp_gzDepthMask)(gzBool);
	static	gzVoid	(GZ_CALLBACK *	imp_gzColorMask)(gzBool,gzBool,gzBool,gzBool);

	static	gzVoid	(GZ_CALLBACK *	imp_gzBlendFunc)(gzEnum,gzEnum);

	static	gzVoid	(GZ_CALLBACK *	imp_gzPushAttrib)(gzEnumBits);
	static	gzVoid	(GZ_CALLBACK *	imp_gzPopAttrib)();

	static	gzVoid	(GZ_CALLBACK *	imp_gzClearColor)(gzFloat,gzFloat,gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzClearDepth)(gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzClearStencil)(gzInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzClear)(gzBitfield);

	static	gzVoid	(GZ_CALLBACK *	imp_gzStencilFunc)(gzEnum,gzInt32,gzUInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzStencilOp)(gzEnum,gzEnum,gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzAlphaFunc)(gzEnum,gzFloat);

	static	gzVoid	(GZ_CALLBACK *	imp_gzTexParameteri)(gzEnum,gzEnum,gzInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzTexParameterfv)(gzEnum,gzEnum,const gzFloat *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzTexEnvi)(gzEnum,gzEnum,gzInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzTexEnvfv)(gzEnum,gzEnum,const gzFloat *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzGetTexLevelParameteriv)(gzEnum ,gzInt32 , gzEnum , gzInt32 *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzTexGenfv)(gzEnum,gzEnum,const gzFloat *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzTexGendv)(gzEnum,gzEnum,const gzDouble *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzPixelStorei)(gzEnum,gzInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzPixelMapfv)(gzEnum,gzInt32,const gzFloat *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzPixelTransferi)(gzEnum,gzInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzPixelTransferf)(gzEnum,gzFloat);

	static	gzVoid	(GZ_CALLBACK *	imp_gzTexImage1D)(gzEnum target,gzInt32 level,gzInt32 internalFormat, gzInt32 width, gzInt32 border,gzEnum format,gzEnum type,const gzVoid *data);  
	static	gzVoid	(GZ_CALLBACK *	imp_gzTexSubImage1D)(gzEnum target,gzInt32 level, gzInt32 x_offset, gzInt32 width, gzEnum format,gzEnum type,const gzVoid *data);  

	static	gzVoid	(GZ_CALLBACK *	imp_gzTexImage2D)(gzEnum target,gzInt32 level,gzInt32 internalFormat, gzInt32 width, gzInt32 height,gzInt32 border,gzEnum format,gzEnum type,const gzVoid *data);  
	static	gzVoid	(GZ_CALLBACK *	imp_gzTexSubImage2D)(gzEnum target,gzInt32 level, gzInt32 x_offset, gzInt32 y_offset, gzInt32 width,gzInt32 height,gzEnum format,gzEnum type,const gzVoid *data);  

	static	gzVoid	(GZ_CALLBACK *	imp_gzTexImage3D)(gzEnum target,gzInt32 level,gzInt32 internalFormat,gzInt32 width, gzInt32 height, gzInt32 depth,gzInt32 border,gzEnum format,gzEnum type,const gzVoid *data);  
	static	gzVoid	(GZ_CALLBACK *	imp_gzTexSubImage3D)(gzEnum target,gzInt32 level,gzInt32 x_offset, gzInt32 y_offset, gzInt32 z_offset,gzInt32 width,gzInt32 height,gzInt32 depth,gzEnum format,gzEnum type,const gzVoid *data);  

	static	gzVoid	(GZ_CALLBACK *	imp_gzCompressedTexImage1D)(gzEnum target , gzInt32 level ,gzEnum internalFormat, gzInt32 width, gzInt32 border, gzInt32 imageSize,const gzVoid * data);  
	static	gzVoid	(GZ_CALLBACK *	imp_gzCompressedTexSubImage1D)(gzEnum target , gzInt32 level ,gzInt32 x_offset , gzInt32 width , gzEnum format , gzInt32 imageSize,const gzVoid * data);  

	static	gzVoid	(GZ_CALLBACK *	imp_gzCompressedTexImage2D)(gzEnum target , gzInt32 level ,gzEnum internalFormat, gzInt32 width, gzInt32 height, gzInt32 border, gzInt32 imageSize,const gzVoid * data);  
	static	gzVoid	(GZ_CALLBACK *	imp_gzCompressedTexSubImage2D)(gzEnum target , gzInt32 level ,gzInt32 x_offset , gzInt32 y_offset, gzInt32 width , gzInt32 height , gzEnum format , gzInt32 imageSize,const gzVoid * data);  

	static	gzVoid	(GZ_CALLBACK *	imp_gzCompressedTexImage3D)(gzEnum target , gzInt32 level ,gzEnum internalFormat, gzInt32 width, gzInt32 height, gzInt32 depth , gzInt32 border, gzInt32 imageSize,const gzVoid * data);  
	static	gzVoid	(GZ_CALLBACK *	imp_gzCompressedTexSubImage3D)(gzEnum target , gzInt32 level ,gzInt32 x_offset, gzInt32 y_offset , gzInt32 z_offset , gzInt32 width , gzInt32 height, gzInt32 depth , gzEnum format , gzInt32 imageSize,const gzVoid * data);  

	static	gzVoid	(GZ_CALLBACK *	imp_gzReadPixels)(gzInt32,gzInt32, gzInt32, gzInt32,gzEnum,gzEnum,gzVoid *);  
	static	gzVoid	(GZ_CALLBACK *	imp_gzDrawPixels)(gzInt32, gzInt32,gzEnum,gzEnum,const gzVoid *);  
	static	gzVoid	(GZ_CALLBACK *	imp_gzBitmap)(gzInt32, gzInt32,gzFloat,gzFloat,gzFloat,gzFloat,const gzUByte *);  
	static	gzVoid	(GZ_CALLBACK *	imp_gzCopyPixels)(gzInt32,gzInt32,gzUInt32,gzUInt32,gzEnum);

	static	gzVoid	(GZ_CALLBACK *	imp_gzRasterPos3d)(gzDouble,gzDouble,gzDouble);  
	static	gzVoid	(GZ_CALLBACK *	imp_gzRasterPos3f)(gzFloat,gzFloat,gzFloat);  


	static	gzVoid	(GZ_CALLBACK *	imp_gzGetDoublev)(gzEnum, gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetFloatv)(gzEnum, gzFloat *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetIntegerv)(gzEnum, gzInt32 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetBooleanv)(gzEnum, gzBool *);

	static	const gzUByte *(GZ_CALLBACK * imp_gzGetString)(gzEnum);

	static	gzBool	(GZ_CALLBACK *	imp_gzIsEnabled)(gzEnum);


	static	gzVoid	(GZ_CALLBACK *	imp_gzEdgeFlagPointer)(gzInt32,const gzBool *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzColorPointer)(gzInt32,gzEnum,gzInt32,const gzVoid *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexPointer)(gzInt32,gzEnum,gzInt32,const  gzVoid *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzNormalPointer)(gzEnum,gzInt32,const gzVoid *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzIndexPointer)(gzEnum,gzInt32,const gzVoid *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzTexCoordPointer)(gzInt32,gzEnum,gzInt32,const gzVoid *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDrawArrays)(gzEnum,gzInt32,gzInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzArrayElement)(gzInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDrawElements)(gzEnum,gzInt32,gzEnum,const gzVoid *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDrawRangeElements)(gzEnum, gzUInt32 start, gzUInt32 end, gzInt32 count,  gzEnum type, const gzVoid *indices);

	static	gzVoid	(GZ_CALLBACK *	imp_gzClientActiveTexture)(gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzActiveTexture)(gzEnum);

	static	gzEnum	(GZ_CALLBACK *	imp_gzGetError)();


	static	gzVoid	(GZ_CALLBACK *	imp_gzBindTexture)(gzEnum,gzUInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGenTextures)(gzInt32,gzUInt32 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDeleteTextures)(gzInt32,const gzUInt32 *);
	static	gzBool	(GZ_CALLBACK *	imp_gzIsTexture)(gzUInt32);
	static	gzBool	(GZ_CALLBACK *	imp_gzAreTexturesResident)(gzInt32,const gzUInt32 *,gzBool *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzPrioritizeTextures)(gzInt32,const gzUInt32 *,const gzFloat *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzLightfv)(gzEnum light,gzEnum name,const gzFloat *params);
	static	gzVoid	(GZ_CALLBACK *	imp_gzLightf)(gzEnum light,gzEnum name,gzFloat param);
	static	gzVoid	(GZ_CALLBACK *	imp_gzLightModelfv)(gzEnum name,const gzFloat *params);
	static	gzVoid	(GZ_CALLBACK *	imp_gzLightModeli)(gzEnum name,gzInt32 param);

	static	gzVoid	(GZ_CALLBACK *	imp_gzClipPlane)(gzEnum face,const gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFrontFace)(gzEnum face);

	static	gzVoid	(GZ_CALLBACK *	imp_gzMaterialfv)(gzEnum face,gzEnum name,const gzFloat *params);
	static	gzVoid	(GZ_CALLBACK *	imp_gzMaterialf)(gzEnum face,gzEnum name,gzFloat param);
	static	gzVoid	(GZ_CALLBACK *	imp_gzColorMaterial)(gzEnum face,gzEnum mode);

	static	gzVoid	(GZ_CALLBACK *	imp_gzShadeModel)(gzEnum mode);

	static	gzVoid	(GZ_CALLBACK *	imp_gzFogfv)(gzEnum name,const gzFloat *params);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFogf)(gzEnum name,const gzFloat param);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFogiv)(gzEnum name,const gzInt32 *params);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFogi)(gzEnum name,const gzInt32 param);
	

	static	gzVoid	(GZ_CALLBACK *	imp_gzLockArrays)(gzInt32 first,gzInt32 count);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUnlockArrays)();

	static	gzVoid	(GZ_CALLBACK *	imp_gzPolygonOffset)(gzFloat,gzFloat);

	static	gzUInt32(GZ_CALLBACK *	imp_gzGenLists)(gzUInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDeleteLists)(gzUInt32,gzInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzNewList)(gzUInt32,gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzEndList)();
	static	gzVoid	(GZ_CALLBACK *	imp_gzCallList)(gzUInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzCallLists)(gzUInt32,gzEnum,const gzVoid *);

	//------------------- Vertex & Fragment programs -------------------------------

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib1s)(gzUInt32,gzInt16);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib1f)(gzUInt32,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib1d)(gzUInt32,gzDouble);

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib2s)(gzUInt32,gzInt16,gzInt16);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib2f)(gzUInt32,gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib2d)(gzUInt32,gzDouble,gzDouble);

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib3s)(gzUInt32,gzInt16,gzInt16,gzInt16);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib3f)(gzUInt32,gzFloat,gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib3d)(gzUInt32,gzDouble,gzDouble,gzDouble);

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4s)(gzUInt32,gzInt16,gzInt16,gzInt16,gzInt16);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4f)(gzUInt32,gzFloat,gzFloat,gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4d)(gzUInt32,gzDouble,gzDouble,gzDouble,gzDouble);

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4Nub)(gzUInt32,gzUByte,gzUByte,gzUByte,gzUByte);

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib1sv)(gzUInt32,const gzInt16 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib1fv)(gzUInt32,const gzFloat *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib1dv)(gzUInt32,const gzDouble *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib2sv)(gzUInt32,const gzInt16 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib2fv)(gzUInt32,const gzFloat *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib2dv)(gzUInt32,const gzDouble *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib3sv)(gzUInt32,const gzInt16 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib3fv)(gzUInt32,const gzFloat *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib3dv)(gzUInt32,const gzDouble *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4bv)(gzUInt32,const gzByte *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4sv)(gzUInt32,const gzInt16 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4iv)(gzUInt32,const gzInt32 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4ubv)(gzUInt32,const gzUByte *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4usv)(gzUInt32,const gzUInt16 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4uiv)(gzUInt32,const gzUInt32 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4fv)(gzUInt32,const gzFloat *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4dv)(gzUInt32,const gzDouble *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4Nbv)(gzUInt32,const gzByte *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4Nsv)(gzUInt32,const gzInt16 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4Niv)(gzUInt32,const gzInt32 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4Nubv)(gzUInt32,const gzUByte *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4Nusv)(gzUInt32,const gzUInt16 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttrib4Nuiv)(gzUInt32,const gzUInt32 *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzVertexAttribPointer)(gzUInt32,gzInt32,gzEnum,gzBool,gzUInt32,const gzVoid *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzEnableVertexAttribArray)(gzUInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDisableVertexAttribArray)(gzUInt32);

	static	gzVoid	(GZ_CALLBACK *	imp_gzProgramString)(gzEnum,gzEnum,gzUInt32,const gzVoid *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzBindProgram)(gzEnum,gzUInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDeletePrograms)(gzUInt32,const gzUInt32 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGenPrograms)(gzUInt32,gzUInt32 *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzProgramEnvParameter4d)(gzEnum,gzUInt32,gzDouble,gzDouble,gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzProgramEnvParameter4dv)(gzEnum,gzUInt32,const gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzProgramEnvParameter4f)(gzEnum,gzUInt32,gzFloat,gzFloat,gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzProgramEnvParameter4fv)(gzEnum,gzUInt32,const gzFloat *);
	
	static	gzVoid	(GZ_CALLBACK *	imp_gzProgramLocalParameter4d)(gzEnum,gzUInt32,gzDouble,gzDouble,gzDouble,gzDouble);
	static	gzVoid	(GZ_CALLBACK *	imp_gzProgramLocalParameter4dv)(gzEnum,gzUInt32,const gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzProgramLocalParameter4f)(gzEnum,gzUInt32,gzFloat,gzFloat,gzFloat,gzFloat);
	static	gzVoid	(GZ_CALLBACK *	imp_gzProgramLocalParameter4fv)(gzEnum,gzUInt32,const gzFloat *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetProgramEnvParameterdv)(gzEnum,gzUInt32,gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetProgramEnvParameterfv)(gzEnum,gzUInt32,gzFloat *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetProgramLocalParameterdv)(gzEnum,gzUInt32,gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetProgramLocalParameterfv)(gzEnum,gzUInt32,gzFloat *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzGetProgramiv)(gzEnum,gzEnum,gzInt32 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetProgramString)(gzEnum,gzEnum,gzVoid *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzGetVertexAttribdv)(gzUInt32,gzEnum,gzDouble *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetVertexAttribfv)(gzUInt32,gzEnum,gzFloat *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetVertexAttribiv)(gzUInt32,gzEnum,gzInt32 *);

	static	gzVoid	(GZ_CALLBACK *	imp_gzGetVertexAttribPointerv)(gzUInt32,gzEnum,gzVoid **);

	static	gzBool	(GZ_CALLBACK *	imp_gzIsProgram)(gzUInt32);

	//------------------- Vertex & Fragment Shaders --------------------------

	static	gzVoid	(GZ_CALLBACK *	imp_gzBindAttribLocation)(gzHandle programObj, gzUInt32 index, const gzChar *name);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetActiveAttrib)(gzHandle programObj, gzUInt32 index, gzUInt32 maxLength,gzUInt32 *length, gzInt32 *size, gzEnum *type, gzChar *name);
	static	gzInt32	(GZ_CALLBACK *	imp_gzGetAttribLocation)(gzHandle programObj, const gzChar *name);

	//------------------- Shader Objects -------------------------------------

	static	gzVoid	(GZ_CALLBACK *	imp_gzDeleteObject)(gzHandle obj);
	static	gzHandle (GZ_CALLBACK *	imp_gzGetHandle)(gzEnum pname);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDetachObject)(gzHandle containerObj, gzHandle attachedObj);
	static	gzHandle (GZ_CALLBACK *	imp_gzCreateShaderObject)(gzEnum shaderType);
	static	gzVoid	(GZ_CALLBACK *	imp_gzShaderSource)(gzHandle shaderObj, gzUInt32 count, const gzChar **string, const gzInt32 *length);
	static	gzVoid	(GZ_CALLBACK *	imp_gzCompileShader)(gzHandle shaderObj);
	static	gzHandle (GZ_CALLBACK *	imp_gzCreateProgramObject)();
	static	gzVoid	(GZ_CALLBACK *	imp_gzAttachObject)(gzHandle containerObj, gzHandle obj);
	static	gzVoid	(GZ_CALLBACK *	imp_gzLinkProgram)(gzHandle programObj);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUseProgramObject)(gzHandle programObj);
	static	gzVoid	(GZ_CALLBACK *	imp_gzValidateProgram)(gzHandle programObj);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform1f)(gzInt32 location, gzFloat v0);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform2f)(gzInt32 location, gzFloat v0, gzFloat v1);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform3f)(gzInt32 location, gzFloat v0, gzFloat v1, gzFloat v2);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform4f)(gzInt32 location, gzFloat v0, gzFloat v1, gzFloat v2, gzFloat v3);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform1i)(gzInt32 location, gzInt32 v0);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform2i)(gzInt32 location, gzInt32 v0, gzInt32 v1);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform3i)(gzInt32 location, gzInt32 v0, gzInt32 v1, gzInt32 v2);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform4i)(gzInt32 location, gzInt32 v0, gzInt32 v1, gzInt32 v2, gzInt32 v3);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform1fv)(gzInt32 location, gzUInt32 count, gzFloat *value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform2fv)(gzInt32 location, gzUInt32 count, gzFloat *value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform3fv)(gzInt32 location, gzUInt32 count, gzFloat *value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform4fv)(gzInt32 location, gzUInt32 count, gzFloat *value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform1iv)(gzInt32 location, gzUInt32 count, gzInt32 *value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform2iv)(gzInt32 location, gzUInt32 count, gzInt32 *value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform3iv)(gzInt32 location, gzUInt32 count, gzInt32 *value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniform4iv)(gzInt32 location, gzUInt32 count, gzInt32 *value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniformMatrix2fv)(gzInt32 location, gzUInt32 count, gzBool transpose, gzFloat *value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniformMatrix3fv)(gzInt32 location, gzUInt32 count, gzBool transpose, gzFloat *value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzUniformMatrix4fv)(gzInt32 location, gzUInt32 count, gzBool transpose, gzFloat *value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetObjectParameterfv)(gzHandle obj, gzEnum pname, gzFloat *params);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetObjectParameteriv)(gzHandle obj, gzEnum pname, gzInt32 *params);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetInfoLog)(gzHandle obj, gzUInt32 maxLength, gzUInt32 *length, gzChar *infoLog);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetAttachedObjects)(gzHandle containerObj, gzUInt32 maxCount, gzUInt32 *count,gzHandle *obj);
	static	gzInt32	(GZ_CALLBACK *	imp_gzGetUniformLocation)(gzHandle programObj, const gzChar *name);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetActiveUniform)(gzHandle programObj, gzUInt32 index, gzUInt32 maxLength,gzUInt32 *length, gzInt32 *size, gzEnum *type, gzChar *name);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetUniformfv)(gzHandle programObj, gzInt32 location, gzFloat *params);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetUniformiv)(gzHandle programObj, gzInt32 location, gzInt32 *params);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetShaderSource)(gzHandle obj, gzUInt32 maxLength, gzUInt32 *length,gzChar *source);

	//------------------- Vertex Buffer Object -------------------------------

	static	gzVoid	(GZ_CALLBACK *	imp_gzBindBuffer)(gzEnum,gzUInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDeleteBuffers)(gzUInt32,const gzUInt32 *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGenBuffers)(gzUInt32,gzUInt32 *);
	static	gzBool	(GZ_CALLBACK *	imp_gzIsBuffer)(gzUInt32);
	static	gzVoid	(GZ_CALLBACK *	imp_gzBufferData)(gzEnum,gzUInt32,const gzVoid *,gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzBufferSubData)(gzEnum,gzUInt32,gzUInt32,const gzVoid *);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetBufferSubData)(gzEnum,gzUInt32,gzUInt32,gzVoid *);
	static	gzVoid *(GZ_CALLBACK *	imp_gzMapBuffer)(gzEnum,gzEnum);
	static	gzBool	(GZ_CALLBACK *	imp_gzUnmapBuffer)(gzEnum);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetBufferParameteriv)(gzEnum,gzEnum,gzInt32 *params);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetBufferPointerv)(gzEnum,gzEnum,gzVoid **params);

	//------------------ has_frame_buffer_object() -----------------------------------

	static	gzBool	(GZ_CALLBACK *	imp_gzIsRenderbuffer)(gzUInt32 renderbuffer);
	static	gzVoid	(GZ_CALLBACK *	imp_gzBindRenderbuffer)(gzEnum target, gzUInt32 renderbuffer);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDeleteRenderbuffers)(gzUInt32 n, const gzUInt32 *renderbuffers);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGenRenderbuffers)(gzUInt32 n, gzUInt32 *renderbuffers);
	static	gzVoid	(GZ_CALLBACK *	imp_gzRenderbufferStorage)(gzEnum target, gzEnum internalformat,gzUInt32 width, gzUInt32 height);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetRenderbufferParameteriv)(gzEnum target, gzEnum pname, gzInt32 *params);
	static	gzBool	(GZ_CALLBACK *	imp_gzIsFramebuffer)(gzUInt32 framebuffer);
	static	gzVoid	(GZ_CALLBACK *	imp_gzBindFramebuffer)(gzEnum target, gzUInt32 framebuffer);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDeleteFramebuffers)(gzUInt32 n, const gzUInt32 *framebuffers);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGenFramebuffers)(gzUInt32 n, gzUInt32 *framebuffers);
	static	gzEnum	(GZ_CALLBACK *	imp_gzCheckFramebufferStatus)(gzEnum target);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFramebufferTexture1D)(gzEnum target, gzEnum attachment,gzEnum textarget, gzUInt32 texture,gzInt32 level);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFramebufferTexture2D)(gzEnum target, gzEnum attachment,gzEnum textarget, gzUInt32 texture,gzInt32 level);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFramebufferTexture3D)(gzEnum target, gzEnum attachment,gzEnum textarget, gzUInt32 texture,gzInt32 level, gzInt32 zoffset);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFramebufferRenderbuffer)(gzEnum target, gzEnum attachment,gzEnum renderbuffertarget, gzUInt32 renderbuffer);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGetFramebufferAttachmentParameteriv)(gzEnum target, gzEnum attachment,gzEnum pname, gzInt32 *params);
	static	gzVoid	(GZ_CALLBACK *	imp_gzGenerateMipmap)(gzEnum target);

	//------------------ has_multisample_fbo() --------------------------------------

	static	gzVoid (GZ_CALLBACK *	imp_gzRenderbufferStorageMultisample)(gzEnum target, gzUInt32 samples, gzEnum internalformat, gzUInt32 width, gzUInt32 height);
	static	gzVoid (GZ_CALLBACK *	imp_gzBlitFramebuffer)(gzInt32 srcX0, gzInt32 srcY0, gzInt32 srcX1, gzInt32 srcY1,gzInt32 dstX0, gzInt32 dstY0, gzInt32 dstX1, gzInt32 dstY1, gzBitfield mask, gzEnum filter);


	//------------------ has_geometry_shader() --------------------------------------

	static	gzVoid	(GZ_CALLBACK *	imp_gzProgramParameteri)(gzHandle program,gzEnum pname,gzInt32 value);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFramebufferTexture)(gzEnum target,gzEnum attachment,gzUInt32 texture,gzInt32 level);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFramebufferTextureLayer)(gzEnum target,gzEnum attachment,gzUInt32 texture,gzInt32 level,gzInt32 layer);
	static	gzVoid	(GZ_CALLBACK *	imp_gzFramebufferTextureFace)(gzEnum target,gzEnum attachment,gzUInt32 texture,gzInt32 level,gzEnum face);

	//------------------ has_draw_instanced() ---------------------------------------

	static	gzVoid	(GZ_CALLBACK *	imp_gzDrawArraysInstanced)(gzEnum mode, gzInt32 first, gzInt32 count, gzInt32 primcount);
	static	gzVoid	(GZ_CALLBACK *	imp_gzDrawElementsInstanced)(gzEnum mode, gzInt32 count, gzEnum type, const gzVoid *indices, gzInt32 primcount);

	//------------------ has_separate_stencil() ------------------------------------------

	static	gzVoid	(GZ_CALLBACK *	imp_gzStencilOpSeparate)(gzEnum face,gzEnum sfail,gzEnum dpfail,gzEnum dppass);
	static	gzVoid	(GZ_CALLBACK *	imp_gzStencilFuncSeparate)(gzEnum frontfunc,gzEnum backfunc,gzInt32 ref,gzUInt32 mask);

	static	gzVoid	(GZ_CALLBACK *	imp_gzActiveStencilFace)(gzEnum face);

	//---------------- context & window rendering setup -----------------------------------------

	static gzVoid			(GZ_CALLBACK *	imp_gzFlush)();
	static gzVoid			(GZ_CALLBACK *	imp_gzFinish)();
	static gzString			(GZ_CALLBACK *	imp_gzGraphicsErrorDescription)(gzInt32 error);

	//---------------- has_nonuniform_matrix_upload() ----------------------------------------------------------------

	static	gzVoid (GZ_CALLBACK * imp_gzUniformMatrix2x3fv)(gzInt32 location, gzUInt32 count, gzBool transpose, gzFloat* value);
	static	gzVoid (GZ_CALLBACK * imp_gzUniformMatrix3x2fv)(gzInt32 location, gzUInt32 count, gzBool transpose, gzFloat* value);
	static	gzVoid (GZ_CALLBACK * imp_gzUniformMatrix2x4fv)(gzInt32 location, gzUInt32 count, gzBool transpose, gzFloat* value);
	static	gzVoid (GZ_CALLBACK * imp_gzUniformMatrix4x2fv)(gzInt32 location, gzUInt32 count, gzBool transpose, gzFloat* value);
	static	gzVoid (GZ_CALLBACK * imp_gzUniformMatrix3x4fv)(gzInt32 location, gzUInt32 count, gzBool transpose, gzFloat* value);
	static	gzVoid (GZ_CALLBACK * imp_gzUniformMatrix4x3fv)(gzInt32 location, gzUInt32 count, gzBool transpose, gzFloat* value);

	static gzUInt32 gzBeginEndStack;
};


// #define GZ_DEBUG_GRAPHICS_API // To force API debugging
#ifndef GZ_DEBUG_GRAPHICS_API_STOP
	#define GZ_DEBUG_GRAPHICS_API_STOP		TRUE
#endif



// Definition of the API error macros
#ifdef GZ_DEBUG_GRAPHICS_API
#define __gz_dbg_api_incr__		++gzGraphicsAbstractionLayer::gzBeginEndStack;
#define __gz_dbg_api_start__	{ if(!gzGraphicsAbstractionLayer::gzBeginEndStack){while(long error=gzGetError()){GZTRACE("External Graphics error before:'%s' at line %ld in file %s",(const char *)gzGraphicsErrorDescription(error),__LINE__,__FILE__);while(GZ_DEBUG_GRAPHICS_API_STOP);}}

#define __gz_dbg_api_decr__		;--gzGraphicsAbstractionLayer::gzBeginEndStack;
#define __gz_dbg_api_end__		; if(!gzGraphicsAbstractionLayer::gzBeginEndStack){while(long error=gzGetError()){GZTRACE("API Graphics error:'%s' at line %ld in file %s",(const char *)gzGraphicsErrorDescription(error),__LINE__,__FILE__); while(GZ_DEBUG_GRAPHICS_API_STOP);}}}
#else
#define __gz_dbg_api_incr__
#define __gz_dbg_api_decr__
#define __gz_dbg_api_start__		
#define __gz_dbg_api_end__		
#endif

#define GZ_CHECK_GRAPHICS_API(stop) while(long error=gzGetError()){GZTRACE("External Graphics error before:'%s' at line %ld in file %s",(const char *)gzGraphicsErrorDescription(error),__LINE__,__FILE__);while(stop);}

// Function macro definitions

#ifndef GZ_NO_FUNC_MACROS

#define gzGetError()														 (gzGraphicsAbstractionLayer::imp_gzGetError)()
#define gzGraphicsErrorDescription(p1)										 (gzGraphicsAbstractionLayer::imp_gzGraphicsErrorDescription)(p1)


#define gzBegin(p1)										__gz_dbg_api_start__ __gz_dbg_api_incr__ (gzGraphicsAbstractionLayer::imp_gzBegin)(p1)					__gz_dbg_api_end__
#define gzEnd()											__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzEnd)()												__gz_dbg_api_decr__ __gz_dbg_api_end__
																																						
#define gzEnable(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzEnable)(p1)										__gz_dbg_api_end__
#define gzDisable(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDisable)(p1)									__gz_dbg_api_end__
#define gzEnableClientState(p1)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzEnableClientState)(p1)							__gz_dbg_api_end__
#define gzDisableClientState(p1)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDisableClientState)(p1)							__gz_dbg_api_end__

#define gzHint(p1,p2)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzHint)(p1,p2)									__gz_dbg_api_end__
																																						
#define gzFrustum(p1,p2,p3,p4,p5,p6)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzFrustum)(p1,p2,p3,p4,p5,p6)						__gz_dbg_api_end__
#define gzFrustumf(p1,p2,p3,p4,p5,p6)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzFrustumf)(p1,p2,p3,p4,p5,p6)					__gz_dbg_api_end__
#define gzOrtho(p1,p2,p3,p4,p5,p6)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzOrtho)(p1,p2,p3,p4,p5,p6)						__gz_dbg_api_end__
#define gzOrthof(p1,p2,p3,p4,p5,p6)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzOrthof)(p1,p2,p3,p4,p5,p6)						__gz_dbg_api_end__
#define gzViewport(p1,p2,p3,p4)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzViewport)(p1,p2,p3,p4)							__gz_dbg_api_end__
#define gzScissor(p1,p2,p3,p4)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzScissor)(p1,p2,p3,p4)							__gz_dbg_api_end__
#define gzDepthRange(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDepthRange)(p1,p2)								__gz_dbg_api_end__
#define gzDepthRangef(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDepthRangef)(p1,p2)								__gz_dbg_api_end__
																																						
#define gzColor4d(p1,p2,p3,p4)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzColor4d)(p1,p2,p3,p4)							__gz_dbg_api_end__
#define gzColor4f(p1,p2,p3,p4)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzColor4f)(p1,p2,p3,p4)							__gz_dbg_api_end__
#define gzColor4fv(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzColor4fv)(p1)									__gz_dbg_api_end__
#define gzColor4dv(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzColor4dv)(p1)									__gz_dbg_api_end__
																																						
#define gzVertex3d(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertex3d)(p1,p2,p3)								__gz_dbg_api_end__
#define gzVertex3f(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertex3f)(p1,p2,p3)								__gz_dbg_api_end__
#define gzVertex3dv(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertex3dv)(p1)									__gz_dbg_api_end__
#define gzVertex3fv(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertex3fv)(p1)									__gz_dbg_api_end__
#define gzVertex2i(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertex2i)(p1,p2)								__gz_dbg_api_end__
#define gzVertex3i(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertex3i)(p1,p2,p3)								__gz_dbg_api_end__
																																						
#define gzNormal3d(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzNormal3d)(p1,p2,p3)								__gz_dbg_api_end__
#define gzNormal3f(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzNormal3f)(p1,p2,p3)								__gz_dbg_api_end__
#define gzNormal3dv(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzNormal3dv)(p1)									__gz_dbg_api_end__
#define gzNormal3fv(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzNormal3fv)(p1)									__gz_dbg_api_end__
																																						
#define gzTexCoord2d(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexCoord2d)(p1,p2)								__gz_dbg_api_end__
#define gzTexCoord2f(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexCoord2f)(p1,p2)								__gz_dbg_api_end__
#define gzTexCoord2dv(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexCoord2dv)(p1)								__gz_dbg_api_end__
#define gzTexCoord2fv(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexCoord2fv)(p1)								__gz_dbg_api_end__
																																						
#define gzEdgeFlag(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzEdgeFlag)(p1)									__gz_dbg_api_end__

#define gzPushAttrib(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPushAttrib)(p1)									__gz_dbg_api_end__
#define gzPopAttrib()									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPopAttrib)()									__gz_dbg_api_end__
																																						
#define gzMatrixMode(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzMatrixMode)(p1)									__gz_dbg_api_end__
#define gzLoadIdentity()								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzLoadIdentity)()									__gz_dbg_api_end__
																																						
#define gzLoadMatrixd(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzLoadMatrixd)(p1)								__gz_dbg_api_end__
#define gzLoadMatrixf(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzLoadMatrixf)(p1)								__gz_dbg_api_end__
																																						
#define gzMultMatrixd(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzMultMatrixd)(p1)								__gz_dbg_api_end__
#define gzMultMatrixf(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzMultMatrixf)(p1)								__gz_dbg_api_end__
																																						
#define gzPushMatrix()									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPushMatrix)()									__gz_dbg_api_end__
#define gzPopMatrix()									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPopMatrix)()									__gz_dbg_api_end__
																																						
																																						
#define gzRotated(p1,p2,p3,p4)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzRotated)(p1,p2,p3,p4)							__gz_dbg_api_end__
#define gzRotatef(p1,p2,p3,p4)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzRotatef)(p1,p2,p3,p4)							__gz_dbg_api_end__
																																						
#define gzTranslated(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTranslated)(p1,p2,p3)							__gz_dbg_api_end__
#define gzTranslatef(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTranslatef)(p1,p2,p3)							__gz_dbg_api_end__
																																						
#define gzScaled(p1,p2,p3)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzScaled)(p1,p2,p3)								__gz_dbg_api_end__
#define gzScalef(p1,p2,p3)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzScalef)(p1,p2,p3)								__gz_dbg_api_end__
																																						
#define gzPointSize(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPointSize)(p1)									__gz_dbg_api_end__
#define gzDrawBuffer(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDrawBuffer)(p1)									__gz_dbg_api_end__
#define gzReadBuffer(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzReadBuffer)(p1)									__gz_dbg_api_end__
#define gzLineWidth(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzLineWidth)(p1)									__gz_dbg_api_end__
#define gzLineStipple(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzLineStipple)(p1,p2)								__gz_dbg_api_end__
																																						
#define gzTexParameteri(p1,p2,p3)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexParameteri)(p1,p2,p3)						__gz_dbg_api_end__
#define gzGetTexLevelParameteriv(p1,p2,p3,p4)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetTexLevelParameteriv)(p1,p2,p3,p4)			__gz_dbg_api_end__
#define gzTexParameterfv(p1,p2,p3)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexParameterfv)(p1,p2,p3)						__gz_dbg_api_end__
#define gzTexEnvi(p1,p2,p3)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexEnvi)(p1,p2,p3)								__gz_dbg_api_end__
#define gzTexEnvfv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexEnvfv)(p1,p2,p3)								__gz_dbg_api_end__
																																						
#define gzTexGenfv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexGenfv)(p1,p2,p3)								__gz_dbg_api_end__
#define gzTexGendv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexGendv)(p1,p2,p3)								__gz_dbg_api_end__
																																						
#define gzPixelStorei(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPixelStorei)(p1,p2)								__gz_dbg_api_end__
#define gzPixelMapfv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPixelMapfv)(p1,p2,p3)							__gz_dbg_api_end__
#define gzPixelTransferi(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPixelTransferi)(p1,p2)							__gz_dbg_api_end__
#define gzPixelTransferf(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPixelTransferf)(p1,p2)							__gz_dbg_api_end__
																
#define gzTexImage1D(p1,p2,p3,p4,p5,p6,p7,p8)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexImage1D)(p1,p2,p3,p4,p5,p6,p7,p8)			__gz_dbg_api_end__
#define gzTexSubImage1D(p1,p2,p3,p4,p5,p6,p7)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexSubImage1D)(p1,p2,p3,p4,p5,p6,p7)			__gz_dbg_api_end__

#define gzTexImage2D(p1,p2,p3,p4,p5,p6,p7,p8,p9)		__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexImage2D)(p1,p2,p3,p4,p5,p6,p7,p8,p9)			__gz_dbg_api_end__
#define gzTexSubImage2D(p1,p2,p3,p4,p5,p6,p7,p8,p9)		__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexSubImage2D)(p1,p2,p3,p4,p5,p6,p7,p8,p9)		__gz_dbg_api_end__

#define gzTexImage3D(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10)	__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexImage3D)(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10)		__gz_dbg_api_end__
#define gzTexSubImage3D(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11)	__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexSubImage3D)(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11)	__gz_dbg_api_end__
																
#define gzCompressedTexImage1D(p1,p2,p3,p4,p5,p6,p7)	__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzCompressedTexImage1D)(p1,p2,p3,p4,p5,p6,p7)		__gz_dbg_api_end__
#define gzCompressedTexSubImage1D(p1,p2,p3,p4,p5,p6,p7)	__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzCompressedTexSubImage1D)(p1,p2,p3,p4,p5,p6,p7)	__gz_dbg_api_end__

#define gzCompressedTexImage2D(p1,p2,p3,p4,p5,p6,p7,p8)	__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzCompressedTexImage2D)(p1,p2,p3,p4,p5,p6,p7,p8)	__gz_dbg_api_end__
#define gzCompressedTexSubImage2D(p1,p2,p3,p4,p5,p6,p7,p8,p9)	__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzCompressedTexSubImage2D)(p1,p2,p3,p4,p5,p6,p7,p8,p9)		__gz_dbg_api_end__
																
#define gzCompressedTexImage3D(p1,p2,p3,p4,p5,p6,p7,p8,p9)	__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzCompressedTexImage3D)(p1,p2,p3,p4,p5,p6,p7,p8,p9)	__gz_dbg_api_end__
#define gzCompressedTexSubImage3D(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11)	__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzCompressedTexSubImage3D)(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11)		__gz_dbg_api_end__

#define gzReadPixels(p1,p2,p3,p4,p5,p6,p7)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzReadPixels)(p1,p2,p3,p4,p5,p6,p7)				__gz_dbg_api_end__
#define gzDrawPixels(p1,p2,p3,p4,p5)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDrawPixels)(p1,p2,p3,p4,p5)						__gz_dbg_api_end__
#define gzBitmap(p1,p2,p3,p4,p5,p6,p7)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzBitmap)(p1,p2,p3,p4,p5,p6,p7)					__gz_dbg_api_end__
#define gzCopyPixels(p1,p2,p3,p4,p5)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzCopyPixels)(p1,p2,p3,p4,p5)						__gz_dbg_api_end__
																
#define gzRasterPos3d(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzRasterPos3d)(p1,p2,p3)							__gz_dbg_api_end__
#define gzRasterPos3f(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzRasterPos3f)(p1,p2,p3)							__gz_dbg_api_end__
																
#define gzGetDoublev(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetDoublev)(p1,p2)								__gz_dbg_api_end__
#define gzGetIntegerv(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetIntegerv)(p1,p2)								__gz_dbg_api_end__
#define gzGetBooleanv(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetBooleanv)(p1,p2)								__gz_dbg_api_end__
#define gzGetFloatv(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetFloatv)(p1,p2)								__gz_dbg_api_end__
																
#define gzGetString															 (gzGraphicsAbstractionLayer::imp_gzGetString)

#define gzIsEnabled(p1)														 (gzGraphicsAbstractionLayer::imp_gzIsEnabled)(p1)									
																
#define gzPolygonMode(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPolygonMode)(p1,p2)								__gz_dbg_api_end__
#define gzCullFace(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzCullFace)(p1)									__gz_dbg_api_end__
																
#define gzDepthMask(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDepthMask)(p1)									__gz_dbg_api_end__
#define gzColorMask(p1,p2,p3,p4)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzColorMask)(p1,p2,p3,p4)							__gz_dbg_api_end__
																
#define gzDepthFunc(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDepthFunc)(p1)									__gz_dbg_api_end__
#define gzBlendFunc(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzBlendFunc)(p1,p2)								__gz_dbg_api_end__
																
#define gzClearColor(p1,p2,p3,p4)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzClearColor)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzClearDepth(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzClearDepth)(p1)									__gz_dbg_api_end__
#define gzClearStencil(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzClearStencil)(p1)								__gz_dbg_api_end__
#define gzClear(p1)										__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzClear)(p1)										__gz_dbg_api_end__

#define gzStencilFunc(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzStencilFunc)(p1,p2,p3)							__gz_dbg_api_end__
#define gzStencilOp(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzStencilOp)(p1,p2,p3)							__gz_dbg_api_end__
#define gzAlphaFunc(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzAlphaFunc)(p1,p2)								__gz_dbg_api_end__
																
																
#define gzEdgeFlagPointer(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzEdgeFlagPointer)(p1,p2)							__gz_dbg_api_end__
#define gzColorPointer(p1,p2,p3,p4)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzColorPointer)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzVertexPointer(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexPointer)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzNormalPointer(p1,p2,p3)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzNormalPointer)(p1,p2,p3)						__gz_dbg_api_end__
#define gzIndexPointer(p1,p2,p3)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzIndexPointer)(p1,p2,p3)							__gz_dbg_api_end__
#define gzTexCoordPointer(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzTexCoordPointer)(p1,p2,p3,p4)					__gz_dbg_api_end__
#define gzDrawArrays(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDrawArrays)(p1,p2,p3)							__gz_dbg_api_end__
#define gzArrayElement(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzArrayElement)(p1)								__gz_dbg_api_end__
#define gzDrawElements(p1,p2,p3,p4)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDrawElements)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzDrawRangeElements(p1,p2,p3,p4,p5,p6)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDrawRangeElements)(p1,p2,p3,p4,p5,p6)			__gz_dbg_api_end__
																
#define gzClientActiveTexture(p1)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzClientActiveTexture)(p1)						__gz_dbg_api_end__
#define gzActiveTexture(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzActiveTexture)(p1)								__gz_dbg_api_end__
																
#define gzBindTexture(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzBindTexture)(p1,p2)								__gz_dbg_api_end__
#define gzGenTextures(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGenTextures)(p1,p2)								__gz_dbg_api_end__
#define gzDeleteTextures(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDeleteTextures)(p1,p2)							__gz_dbg_api_end__
#define gzIsTexture(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzIsTexture)(p1)									__gz_dbg_api_end__
#define gzAreTexturesResident(p1,p2,p3)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzAreTexturesResident)(p1,p2,p3)					__gz_dbg_api_end__
#define gzPrioritizeTextures(p1,p2,p3)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPrioritizeTextures)(p1,p2,p3)					__gz_dbg_api_end__
																
#define gzLightf(p1,p2,p3)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzLightf)(p1,p2,p3)								__gz_dbg_api_end__
#define gzLightfv(p1,p2,p3)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzLightfv)(p1,p2,p3)								__gz_dbg_api_end__
#define gzLightModelfv(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzLightModelfv)(p1,p2)							__gz_dbg_api_end__
#define gzLightModeli(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzLightModeli)(p1,p2)								__gz_dbg_api_end__
																
#define gzClipPlane(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzClipPlane)(p1,p2)								__gz_dbg_api_end__
#define gzFrontFace(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzFrontFace)(p1)									__gz_dbg_api_end__
																
#define gzMaterialf(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzMaterialf)(p1,p2,p3)							__gz_dbg_api_end__
#define gzMaterialfv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzMaterialfv)(p1,p2,p3)							__gz_dbg_api_end__
#define gzColorMaterial(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzColorMaterial)(p1,p2)							__gz_dbg_api_end__

#define gzFogf(p1,p2)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzFogf)(p1,p2)									__gz_dbg_api_end__
#define gzFogfv(p1,p2)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzFogfv)(p1,p2)									__gz_dbg_api_end__
#define gzFogi(p1,p2)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzFogi)(p1,p2)									__gz_dbg_api_end__
#define gzFogiv(p1,p2)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzFogiv)(p1,p2)									__gz_dbg_api_end__
																
#define gzShadeModel(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzShadeModel)(p1)									__gz_dbg_api_end__
																
#define gzLockArrays(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzLockArrays)(p1,p2)								__gz_dbg_api_end__
#define gzUnlockArrays()								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUnlockArrays)()									__gz_dbg_api_end__
#define gzPolygonOffset(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzPolygonOffset)(p1,p2)							__gz_dbg_api_end__
																
#define gzGenLists															 (gzGraphicsAbstractionLayer::imp_gzGenLists)
#define gzDeleteLists(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDeleteLists)(p1,p2)								__gz_dbg_api_end__
#define gzNewList(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzNewList)(p1,p2)									__gz_dbg_api_end__
#define gzEndList()										__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzEndList)()										__gz_dbg_api_end__
#define gzCallList(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzCallList)(p1)									__gz_dbg_api_end__
#define gzCallLists(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzCallLists)(p1,p2,p3)							__gz_dbg_api_end__
																
#define gzVertexAttrib1s(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib1s)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib1f(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib1f)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib1d(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib1d)(p1,p2)							__gz_dbg_api_end__
																
#define gzVertexAttrib2s(p1,p2,p3)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib2s)(p1,p2,p3)						__gz_dbg_api_end__
#define gzVertexAttrib2f(p1,p2,p3)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib2f)(p1,p2,p3)						__gz_dbg_api_end__
#define gzVertexAttrib2d(p1,p2,p3)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib2d)(p1,p2,p3)						__gz_dbg_api_end__
																
#define gzVertexAttrib3s(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib3s)(p1,p2,p3,p4)					__gz_dbg_api_end__
#define gzVertexAttrib3f(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib3f)(p1,p2,p3,p4)					__gz_dbg_api_end__
#define gzVertexAttrib3d(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib3d)(p1,p2,p3,p4)					__gz_dbg_api_end__
																
#define gzVertexAttrib4s(p1,p2,p3,p4,p5)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4s)(p1,p2,p3,p4,p5)					__gz_dbg_api_end__
#define gzVertexAttrib4f(p1,p2,p3,p4,p5)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4f)(p1,p2,p3,p4,p5)					__gz_dbg_api_end__
#define gzVertexAttrib4d(p1,p2,p3,p4,p5)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4d)(p1,p2,p3,p4,p5)					__gz_dbg_api_end__
																																						
#define gzVertexAttrib4Nub(p1,p2,p3,p4,p5)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4Nub)(p1,p2,p3,p4,p5)				__gz_dbg_api_end__
																
#define gzVertexAttrib1sv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib1sv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib1fv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib1fv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib1dv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib1dv)(p1,p2)							__gz_dbg_api_end__
																																							
#define gzVertexAttrib2sv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib2sv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib2fv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib2fv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib2dv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib2dv)(p1,p2)							__gz_dbg_api_end__
																	
#define gzVertexAttrib3sv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib3sv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib3fv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib3fv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib3dv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib3dv)(p1,p2)							__gz_dbg_api_end__
																	
#define gzVertexAttrib4bv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4bv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4sv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4sv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4iv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4iv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4ubv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4ubv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4usv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4usv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4uiv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4uiv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4fv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4fv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4dv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4dv)(p1,p2)							__gz_dbg_api_end__
																	
#define gzVertexAttrib4Nbv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4Nbv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4Nsv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4Nsv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4Niv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4Niv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4Nubv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4Nubv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4Nusv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4Nusv)(p1,p2)							__gz_dbg_api_end__
#define gzVertexAttrib4Nuiv(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttrib4Nuiv)(p1,p2)							__gz_dbg_api_end__
																	
#define gzVertexAttribPointer(p1,p2,p3,p4,p5,p6)		__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzVertexAttribPointer)(p1,p2,p3,p4,p5,p6)			__gz_dbg_api_end__
														
#define gzEnableVertexAttribArray(p1)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzEnableVertexAttribArray)(p1)						__gz_dbg_api_end__
#define gzDisableVertexAttribArray(p1)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDisableVertexAttribArray)(p1)						__gz_dbg_api_end__
														
														
#define gzProgramString(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzProgramString)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzBindProgram(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzBindProgram)(p1,p2)								__gz_dbg_api_end__
#define gzDeletePrograms(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDeletePrograms)(p1,p2)								__gz_dbg_api_end__
#define gzGenPrograms(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGenPrograms)(p1,p2)								__gz_dbg_api_end__
														
#define gzDeleteObject(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDeleteObject)(p1)									__gz_dbg_api_end__
#define gzGetHandle(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetHandle)(p1)										__gz_dbg_api_end__
#define gzDetachObject(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDetachObject)(p1,p2)								__gz_dbg_api_end__
#define gzCreateShaderObject												 (gzGraphicsAbstractionLayer::imp_gzCreateShaderObject)
#define gzShaderSource(p1,p2,p3,p4)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzShaderSource)(p1,p2,p3,p4)							__gz_dbg_api_end__
#define gzCompileShader(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzCompileShader)(p1)									__gz_dbg_api_end__
#define gzCreateProgramObject												 (gzGraphicsAbstractionLayer::imp_gzCreateProgramObject)
#define gzAttachObject(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzAttachObject)(p1,p2)								__gz_dbg_api_end__
														
														
#define gzLinkProgram(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzLinkProgram)(p1)									__gz_dbg_api_end__
#define gzUseProgramObject(p1)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUseProgramObject)(p1)								__gz_dbg_api_end__
#define gzValidateProgram(p1)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzValidateProgram)(p1)								__gz_dbg_api_end__
#define gzUniform1f(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform1f)(p1,p2)									__gz_dbg_api_end__
#define gzUniform2f(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform2f)(p1,p2,p3)								__gz_dbg_api_end__
#define gzUniform3f(p1,p2,p3,p4)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform3f)(p1,p2,p3,p4)							__gz_dbg_api_end__
#define gzUniform4f(p1,p2,p3,p4,p5)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform4f)(p1,p2,p3,p4,p5)							__gz_dbg_api_end__
#define gzUniform1i(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform1i)(p1,p2)									__gz_dbg_api_end__
#define gzUniform2i(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform2i)(p1,p2,p3)								__gz_dbg_api_end__
#define gzUniform3i(p1,p2,p3,p4)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform3i)(p1,p2,p3,p4)							__gz_dbg_api_end__
#define gzUniform4i(p1,p2,p3,p4,p5)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform4i)(p1,p2,p3,p4,p5)							__gz_dbg_api_end__
#define gzUniform1fv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform1fv)(p1,p2,p3)								__gz_dbg_api_end__
#define gzUniform2fv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform2fv)(p1,p2,p3)								__gz_dbg_api_end__
#define gzUniform3fv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform3fv)(p1,p2,p3)								__gz_dbg_api_end__
#define gzUniform4fv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform4fv)(p1,p2,p3)								__gz_dbg_api_end__
#define gzUniform1iv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform1iv)(p1,p2,p3)								__gz_dbg_api_end__
#define gzUniform2iv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform2iv)(p1,p2,p3)								__gz_dbg_api_end__
#define gzUniform3iv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform3iv)(p1,p2,p3)								__gz_dbg_api_end__
#define gzUniform4iv(p1,p2,p3)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniform4iv)(p1,p2,p3)								__gz_dbg_api_end__
#define gzUniformMatrix2fv(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniformMatrix2fv)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzUniformMatrix3fv(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniformMatrix3fv)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzUniformMatrix4fv(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniformMatrix4fv)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzGetObjectParameterfv(p1,p2,p3)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetObjectParameterfv)(p1,p2,p3)					__gz_dbg_api_end__
#define gzGetObjectParameteriv(p1,p2,p3)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetObjectParameteriv)(p1,p2,p3)					__gz_dbg_api_end__
#define gzGetInfoLog(p1,p2,p3,p4)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetInfoLog)(p1,p2,p3,p4)							__gz_dbg_api_end__
#define gzGetAttachedObjects(p1,p2,p3,p4)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetAttachedObjects)(p1,p2,p3,p4)					__gz_dbg_api_end__
#define gzGetUniformLocation												 (gzGraphicsAbstractionLayer::imp_gzGetUniformLocation)
#define gzGetActiveUniform(p1,p2,p3,p4,p5,p6,p7)		__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetActiveUniform)(p1,p2,p3,p4,p5,p6,p7)			__gz_dbg_api_end__
#define gzGetUniformfv(p1,p2,p3)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetUniformfv)(p1,p2,p3)							__gz_dbg_api_end__
#define gzGetUniformiv(p1,p2,p3)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetUniformiv)(p1,p2,p3)							__gz_dbg_api_end__
#define gzGetShaderSource(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetShaderSource)(p1,p2,p3,p4)						__gz_dbg_api_end__
																	
#define gzBindBuffer(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzBindBuffer)(p1,p2)									__gz_dbg_api_end__
#define gzDeleteBuffers(p1,p2)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDeleteBuffers)(p1,p2)								__gz_dbg_api_end__
#define gzGenBuffers(p1,p2)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGenBuffers)(p1,p2)									__gz_dbg_api_end__
#define gzIsBuffer(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzIsBuffer)(p1)										__gz_dbg_api_end__
#define gzBufferData(p1,p2,p3,p4)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzBufferData)(p1,p2,p3,p4)							__gz_dbg_api_end__
#define gzBufferSubData(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzBufferSubData)(p1,p2,p3,p4)							__gz_dbg_api_end__
#define gzGetBufferSubData(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetBufferSubData)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzMapBuffer(p1,p2)													 (gzGraphicsAbstractionLayer::imp_gzMapBuffer)(p1,p2)								
#define gzUnmapBuffer(p1)								__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUnmapBuffer)(p1)									__gz_dbg_api_end__
#define gzGetBufferParameteriv(p1,p2,p3)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetBufferParameteriv)(p1,p2,p3)						__gz_dbg_api_end__
#define gzGetBufferPointerv(p1,p2,p3)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetBufferPointerv)(p1,p2,p3)						__gz_dbg_api_end__
														
#define gzProgramEnvParameter4d(p1,p2,p3,p4,p5,p6)		__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzProgramEnvParameter4d)(p1,p2,p3,p4,p5,p6)			__gz_dbg_api_end__
#define gzProgramEnvParameter4dv(p1,p2,p3)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzProgramEnvParameter4dv)(p1,p2,p3)					__gz_dbg_api_end__
#define gzProgramEnvParameter4f(p1,p2,p3,p4,p5,p6)		__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzProgramEnvParameter4f)(p1,p2,p3,p4,p5,p6)			__gz_dbg_api_end__
#define gzProgramEnvParameter4fv(p1,p2,p3)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzProgramEnvParameter4fv)(p1,p2,p3)					__gz_dbg_api_end__
															
#define gzProgramLocalParameter4d(p1,p2,p3,p4,p5,p6)	__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzProgramLocalParameter4d)(p1,p2,p3,p4,p5,p6)		__gz_dbg_api_end__
#define gzProgramLocalParameter4dv(p1,p2,p3)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzProgramLocalParameter4dv)(p1,p2,p3)				__gz_dbg_api_end__
#define gzProgramLocalParameter4f(p1,p2,p3,p4,p5,p6)	__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzProgramLocalParameter4f)(p1,p2,p3,p4,p5,p6)		__gz_dbg_api_end__
#define gzProgramLocalParameter4fv(p1,p2,p3)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzProgramLocalParameter4fv)(p1,p2,p3)				__gz_dbg_api_end__
															
#define gzGetProgramEnvParameterdv(p1,p2,p3)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetProgramEnvParameterdv)(p1,p2,p3)				__gz_dbg_api_end__
#define gzGetProgramEnvParameterfv(p1,p2,p3)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetProgramEnvParameterfv)(p1,p2,p3)				__gz_dbg_api_end__
#define gzGetProgramLocalParameterdv(p1,p2,p3)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetProgramLocalParameterdv)(p1,p2,p3)				__gz_dbg_api_end__
#define gzGetProgramLocalParameterfv(p1,p2,p3)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetProgramLocalParameterfv)(p1,p2,p3)				__gz_dbg_api_end__
															
#define gzGetProgramiv(p1,p2,p3)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetProgramiv)(p1,p2,p3)							__gz_dbg_api_end__
#define gzGetProgramString(p1,p2,p3)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetProgramString)(p1,p2,p3)						__gz_dbg_api_end__
														
#define gzGetVertexAttribdv(p1,p2,p3)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetVertexAttribdv)(p1,p2,p3)						__gz_dbg_api_end__
#define gzGetVertexAttribfv(p1,p2,p3)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetVertexAttribfv)(p1,p2,p3)						__gz_dbg_api_end__
#define gzGetVertexAttribiv(p1,p2,p3)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetVertexAttribiv)(p1,p2,p3)						__gz_dbg_api_end__
															
#define gzGetVertexAttribPointerv(p1,p2,p3)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetVertexAttribPointerv)(p1,p2,p3)					__gz_dbg_api_end__
															
#define gzIsProgram(p1)									__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzIsProgram)(p1)										__gz_dbg_api_end__
															
#define gzStencilOpSeparate(p1,p2,p3,p4)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzStencilOpSeparate)(p1,p2,p3,p4)					__gz_dbg_api_end__
#define gzStencilFuncSeparate(p1,p2,p3,p4)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzStencilFuncSeparate)(p1,p2,p3,p4)					__gz_dbg_api_end__
															
#define gzActiveStencilFace(p1)							__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzActiveStencilFace)(p1)								__gz_dbg_api_end__
															
#define gzBindAttribLocation(p1,p2,p3)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzBindAttribLocation)(p1,p2,p3)						__gz_dbg_api_end__
#define gzGetActiveAttrib(p1,p2,p3,p4,p5,p6,p7)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetActiveAttrib)(p1,p2,p3,p4,p5,p6,p7)				__gz_dbg_api_end__
#define gzGetAttribLocation(p1,p2)						__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzGetAttribLocation)(p1,p2)							__gz_dbg_api_end__
	
#define gzProgramParameteri(p1,p2,p3)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzProgramParameteri)(p1,p2,p3)						__gz_dbg_api_end__
#define gzFramebufferTexture(p1,p2,p3,p4)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzFramebufferTexture)(p1,p2,p3,p4)					__gz_dbg_api_end__
#define gzFramebufferTextureLayer(p1,p2,p3,p4,p5)		__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzFramebufferTextureLayer)(p1,p2,p3,p4,p5)			__gz_dbg_api_end__
#define gzFramebufferTextureFace(p1,p2,p3,p4,p5)		__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzFramebufferTextureFace)(p1,p2,p3,p4,p5)				__gz_dbg_api_end__

// has_draw_instanced()
#define gzDrawArraysInstanced(p1,p2,p3,p4)				__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDrawArraysInstanced)(p1,p2,p3,p4)					__gz_dbg_api_end__
#define gzDrawElementsInstanced(p1,p2,p3,p4,p5)			__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzDrawElementsInstanced)(p1,p2,p3,p4,p5)				__gz_dbg_api_end__

// has_frame_buffer_object()
#define gzIsRenderbuffer(renderbuffer)																			(gzGraphicsAbstractionLayer::imp_gzIsRenderbuffer)(renderbuffer)
#define gzBindRenderbuffer(target,renderbuffer)											__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzBindRenderbuffer)(target,renderbuffer)										__gz_dbg_api_end__
#define gzDeleteRenderbuffers(n,renderbuffers)											__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzDeleteRenderbuffers)(n,renderbuffers)										__gz_dbg_api_end__
#define gzGenRenderbuffers(n,renderbuffers)												__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzGenRenderbuffers)(n,renderbuffers)											__gz_dbg_api_end__
#define gzRenderbufferStorage(target,internalformat,width,height)						__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzRenderbufferStorage)(target,internalformat,width,height)						__gz_dbg_api_end__
#define gzGetRenderbufferParameteriv(target,pname,params)								__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzGetRenderbufferParameteriv)(target,pname,params)								__gz_dbg_api_end__
#define	gzIsFramebuffer(framebuffer)																			(gzGraphicsAbstractionLayer::imp_gzIsFramebuffer)(framebuffer)
#define gzBindFramebuffer(target,framebuffer)											__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzBindFramebuffer)(target,framebuffer)											__gz_dbg_api_end__
#define gzDeleteFramebuffers(n,framebuffers)											__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzDeleteFramebuffers)(n,framebuffers)											__gz_dbg_api_end__
#define gzGenFramebuffers(n,framebuffers)												__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzGenFramebuffers)(n,framebuffers)												__gz_dbg_api_end__
#define gzCheckFramebufferStatus(target)																		(gzGraphicsAbstractionLayer::imp_gzCheckFramebufferStatus)(target)					
#define gzFramebufferTexture1D(target,attachment,textarget,texture,level)				__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzFramebufferTexture1D)(target,attachment,textarget,texture,level)				__gz_dbg_api_end__
#define gzFramebufferTexture2D(target,attachment,textarget,texture,level)				__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzFramebufferTexture2D)(target,attachment,textarget,texture,level)				__gz_dbg_api_end__
#define gzFramebufferTexture3D(target,attachment,textarget,texture,level,zoffset)		__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzFramebufferTexture3D)(target,attachment,textarget,texture,level,zoffset)		__gz_dbg_api_end__
#define	gzFramebufferRenderbuffer(target,attachment,renderbuffertarget,renderbuffer)	__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzFramebufferRenderbuffer)(target,attachment,renderbuffertarget,renderbuffer)	__gz_dbg_api_end__
#define gzGetFramebufferAttachmentParameteriv(target,attachment,pname, params)			__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzGetFramebufferAttachmentParameteriv)(target,attachment,pname, params)		__gz_dbg_api_end__
#define gzGenerateMipmap(target)														__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzGenerateMipmap)(target)														__gz_dbg_api_end__
#define gzFlush()																		__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzFlush)()																		__gz_dbg_api_end__
#define gzFinish()																		__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzFinish)()																	__gz_dbg_api_end__

// has_multisample_fbo()
#define gzRenderbufferStorageMultisample(target,size,internalformat,width,height)		__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzRenderbufferStorageMultisample)(target,size,internalformat,width,height)		__gz_dbg_api_end__
#define gzBlitFramebuffer(srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter)	__gz_dbg_api_start__	(gzGraphicsAbstractionLayer::imp_gzBlitFramebuffer)(srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter)__gz_dbg_api_end__

// has_nonuniform_matrix_upload()
#define gzUniformMatrix2x3fv(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniformMatrix2x3fv)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzUniformMatrix3x2fv(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniformMatrix3x2fv)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzUniformMatrix2x4fv(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniformMatrix2x4fv)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzUniformMatrix4x2fv(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniformMatrix4x2fv)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzUniformMatrix3x4fv(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniformMatrix3x4fv)(p1,p2,p3,p4)						__gz_dbg_api_end__
#define gzUniformMatrix4x3fv(p1,p2,p3,p4)					__gz_dbg_api_start__ (gzGraphicsAbstractionLayer::imp_gzUniformMatrix4x3fv)(p1,p2,p3,p4)						__gz_dbg_api_end__


#endif //GZ_NO_FUNC_MACROS

// ------------------- utilities ----------------------------

GZ_GRAPH_EXPORT gzVoid gzGetProjectionMatrix( gzMatrix4 &matrix) noexcept(TRUE);

GZ_GRAPH_EXPORT gzVoid gzGetModelMatrix(gzMatrix4 &matrix) noexcept(TRUE);

//! Load the matrix into the graphics GAL pipeline
/*! Note that it depends on the actual matrix mode which matrix is updates. See gzMatrixMode for more details */
GZ_GRAPH_EXPORT gzVoid gzLoadMatrix(const gzMatrix4 &matrix) noexcept(TRUE);


#endif // __GZ_GRAPHICS_ABSTRACTION_LAYER_H__
