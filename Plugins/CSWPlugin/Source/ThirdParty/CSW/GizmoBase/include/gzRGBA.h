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
// File			: gzRGBA.h
// Module		: gzBase
// Description	: Class definition of the gzRGBA class
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.211
//		
//
//			
// NOTE:	GizmoBase is a platform abstraction utility layer for C++. It contains 
//			design patterns and C++ solutions for the advanced programmer.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990223	Created file 	
// AMO	091014	Dont force RGBA::add to update to floats		(2.4.12)
//
//******************************************************************************
#ifndef __GZ_RGBA_H__
#define __GZ_RGBA_H__

/*!	\file 
	\brief RGBA utilites 

 
*/

#include "gzBasicTypes.h"
#include "gzHalf.h"

enum gzRGBASwizzle
{
	GZ_MAP_NOTHING	=	0,

	GZ_MAP_R_TO_R	=	(1<<0),
	GZ_MAP_G_TO_R	=	(1<<1),
	GZ_MAP_B_TO_R	=	(1<<2),
	GZ_MAP_A_TO_R	=	(1<<3),

	GZ_MAP_R_TO_G	=	(1<<4),
	GZ_MAP_G_TO_G	=	(1<<5),
	GZ_MAP_B_TO_G	=	(1<<6),
	GZ_MAP_A_TO_G	=	(1<<7),

	GZ_MAP_R_TO_B	=	(1<<8),
	GZ_MAP_G_TO_B	=	(1<<9),
	GZ_MAP_B_TO_B	=	(1<<10),
	GZ_MAP_A_TO_B	=	(1<<11),

	GZ_MAP_R_TO_A	=	(1<<12),
	GZ_MAP_G_TO_A	=	(1<<13),
	GZ_MAP_B_TO_A	=	(1<<14),
	GZ_MAP_A_TO_A	=	(1<<15),

	GZ_MAP_C_TO_R	=	(1<<16),
	GZ_MAP_C_TO_G	=	(1<<17),
	GZ_MAP_C_TO_B	=	(1<<18),
	GZ_MAP_C_TO_A	=	(1<<19),
	
	GZ_MAP_R_TO_FPX	=	(1<<20),
	GZ_MAP_G_TO_FPX	=	(1<<21),
	GZ_MAP_B_TO_FPX	=	(1<<22),
	GZ_MAP_A_TO_FPX	=	(1<<23),
	GZ_MAP_C_TO_FPX	=	(1<<24),

	GZ_MAP_FPX_TO_R	=	(1<<25),
	GZ_MAP_FPX_TO_G	=	(1<<26),
	GZ_MAP_FPX_TO_B	=	(1<<27),
	GZ_MAP_FPX_TO_A	=	(1<<28),


	GZ_MAP_RGB_TO_RGBA = (GZ_MAP_R_TO_R+GZ_MAP_G_TO_G+GZ_MAP_B_TO_B+GZ_MAP_C_TO_A),
	GZ_MAP_RGBA_TO_RGBA = (GZ_MAP_R_TO_R+GZ_MAP_G_TO_G+GZ_MAP_B_TO_B+GZ_MAP_A_TO_A)
};

GZ_USE_BIT_LOGIC(gzRGBASwizzle);

class gzRGBA
{
public:
	inline GZ_BASE_EXPORT gzRGBA(gzUByte red_component,gzUByte green_component,gzUByte blue_component,gzUByte alpha_component=255);

	inline GZ_BASE_EXPORT gzRGBA(const gzFloat &red_component,const gzFloat &green_component,const gzFloat & blue_component,const gzFloat & alpha_component);

	inline GZ_BASE_EXPORT gzRGBA(const gzVec4 &copy);

	inline GZ_BASE_EXPORT gzRGBA(const gzVec3& copy);

	inline GZ_BASE_EXPORT gzRGBA(gzUByte *adress , gzUByte count=4 , gzUByte def_red=255 , gzUByte def_green=255 , gzUByte def_blue=255 , gzUByte def_alpha=255);

	inline GZ_BASE_EXPORT gzRGBA(gzUInt16 *adress , gzUByte count=4 , gzUInt16 def_red=65535 , gzUInt16 def_green=65535 , gzUInt16 def_blue=65535 , gzUInt16 def_alpha=65535);

	inline GZ_BASE_EXPORT gzRGBA(gzFloat *adress , gzUByte count=4 , gzFloat def_red=GZ_FLOAT_ONE , gzFloat def_green=GZ_FLOAT_ONE , gzFloat def_blue=GZ_FLOAT_ONE , gzFloat def_alpha=GZ_FLOAT_ONE);

	inline GZ_BASE_EXPORT gzRGBA(gzHalf *adress , gzUByte count=4 , gzFloat def_red=GZ_FLOAT_ONE , gzFloat def_green=GZ_FLOAT_ONE , gzFloat def_blue=GZ_FLOAT_ONE , gzFloat def_alpha=GZ_FLOAT_ONE);

	inline GZ_BASE_EXPORT gzRGBA(gzUInt32 rgba=0);


	inline GZ_BASE_EXPORT gzFloat	gray() const;

	inline GZ_BASE_EXPORT gzUByte	grayByte() const;

	inline GZ_BASE_EXPORT gzVoid	invert();

	inline GZ_BASE_EXPORT gzVoid	toGray();

	inline GZ_BASE_EXPORT gzVoid	clamp();

	inline GZ_BASE_EXPORT gzVoid	alphaDiv();
	
	inline GZ_BASE_EXPORT gzVoid	resetFloat();
	
	inline GZ_BASE_EXPORT gzVoid	resetByte();

	inline GZ_BASE_EXPORT gzVoid	mul(const gzFloat	&val);

	inline GZ_BASE_EXPORT gzVoid	add(const gzRGBA	&val);

	inline GZ_BASE_EXPORT gzVoid	convertToFloat();

	inline GZ_BASE_EXPORT gzFloat *	getColorVector() const;

	inline GZ_BASE_EXPORT gzVec4	getColor() const;

	inline GZ_BASE_EXPORT gzVoid	mulAlpha();
	inline GZ_BASE_EXPORT gzVoid	divAlpha();

	// math
	inline GZ_BASE_EXPORT gzRGBA	operator+(const gzRGBA &right);
	inline GZ_BASE_EXPORT gzRGBA	operator/(const gzFloat &f);
	inline GZ_BASE_EXPORT gzRGBA	operator*(const gzFloat &f);


	// Float settings 0 <-> 1
	inline GZ_BASE_EXPORT gzVoid setRed(gzFloat redComponent);
	inline GZ_BASE_EXPORT gzVoid setGreen(gzFloat greenComponent);
	inline GZ_BASE_EXPORT gzVoid setBlue(gzFloat blueComponent);
	inline GZ_BASE_EXPORT gzVoid setAlpha(gzFloat alphaComponent);
	inline GZ_BASE_EXPORT gzVoid setComponents(gzFloat red_component,gzFloat green_component,gzFloat blue_component,gzFloat alpha_component=1.0f);

	inline GZ_BASE_EXPORT gzFloat getRed() const;
	inline GZ_BASE_EXPORT gzFloat getGreen() const;
	inline GZ_BASE_EXPORT gzFloat getBlue() const;
	inline GZ_BASE_EXPORT gzFloat getAlpha() const;

	// Byte settings 0 <-> 255
	inline GZ_BASE_EXPORT gzVoid setRed(gzUByte redComponent);
	inline GZ_BASE_EXPORT gzVoid setGreen(gzUByte greenComponent);
	inline GZ_BASE_EXPORT gzVoid setBlue(gzUByte blueComponent);
	inline GZ_BASE_EXPORT gzVoid setAlpha(gzUByte alphaComponent);
	inline GZ_BASE_EXPORT gzVoid setComponents(gzUByte red_component,gzUByte green_component,gzUByte blue_component,gzUByte alpha_component=255);

	inline GZ_BASE_EXPORT gzUByte getRedByte() const;
	inline GZ_BASE_EXPORT gzUByte getGreenByte() const;
	inline GZ_BASE_EXPORT gzUByte getBlueByte() const;
	inline GZ_BASE_EXPORT gzUByte getAlphaByte() const;

	inline GZ_BASE_EXPORT gzBool isAlphaNonZero() const;

	inline GZ_BASE_EXPORT gzVoid getRGBA(gzUByte *adress, gzUByte count=4 ) const;
	inline GZ_BASE_EXPORT gzVoid getRGBA(gzFloat *adress, gzUByte count=4 ) const;
	inline GZ_BASE_EXPORT gzVoid getRGBA(gzHalf *adress, gzUByte count=4 ) const;
	inline GZ_BASE_EXPORT gzVoid getRGBA(gzUInt16 *adress, gzUByte count=4 ) const;

	inline GZ_BASE_EXPORT gzBool operator==(const gzRGBA &right) const;

	inline GZ_BASE_EXPORT gzBool operator!=(const gzRGBA &right) const { return !operator==(right); }

	inline GZ_BASE_EXPORT gzRGBA getSwizzledRGBA(gzRGBASwizzle swizzle=GZ_MAP_RGB_TO_RGBA , gzFloat R_factor =GZ_FLOAT_ONE, gzFloat G_factor =GZ_FLOAT_ONE, gzFloat B_factor =GZ_FLOAT_ONE, gzFloat A_factor =GZ_FLOAT_ONE , gzFloat C_value=GZ_FLOAT_ONE) const;

	inline GZ_BASE_EXPORT gzString asString(const gzString &format="(%lf %lf %lf %lf)") const ;

private:

	union
	{
		struct 
		{
			gzFloat red;
			gzFloat green;
			gzFloat blue;
			gzFloat alpha;
		} floatVal;

		struct
		{
			gzUInt32 red;
			gzUInt32 green;
			gzUInt32 blue;
			gzUInt32 alpha;
		} byteVal;

	} components;

	union
	{
		struct
		{
			gzBool	hasRedByte:2;
			gzBool	hasGreenByte:2;
			gzBool	hasBlueByte:2;
			gzBool	hasAlphaByte:2;
		} byteVal;
		gzUByte	byteMask;
	} byteSetting;
};

inline gzRGBA::gzRGBA(gzFloat *adress , gzUByte count , gzFloat def_red , gzFloat def_green , gzFloat def_blue , gzFloat def_alpha)
{
	switch(count)
	{
		case 0 :
			components.floatVal.red=def_red;
			components.floatVal.green=def_green;
			components.floatVal.blue=def_blue;
			components.floatVal.alpha=def_alpha;
			break;

		case 1 :
			components.floatVal.red=*adress;
			components.floatVal.green=def_green;
			components.floatVal.blue=def_blue;
			components.floatVal.alpha=def_alpha;
			break;

		case 2 :
			components.floatVal.red=*adress;
			components.floatVal.green=*(++adress);
			components.floatVal.blue=def_blue;
			components.floatVal.alpha=def_alpha;
			break;

		case 3 :
			components.floatVal.red=*adress;
			components.floatVal.green=*(++adress);
			components.floatVal.blue=*(++adress);
			components.floatVal.alpha=def_alpha;
			break;

		case 4 :
			components.floatVal.red=*adress;
			components.floatVal.green=*(++adress);
			components.floatVal.blue=*(++adress);
			components.floatVal.alpha=*(++adress);
			break;
	}

	byteSetting.byteMask=0;
}

inline gzRGBA::gzRGBA(gzHalf *adress , gzUByte count , gzFloat def_red , gzFloat def_green , gzFloat def_blue , gzFloat def_alpha)
{
	switch(count)
	{
		case 0 :
			components.floatVal.red=def_red;
			components.floatVal.green=def_green;
			components.floatVal.blue=def_blue;
			components.floatVal.alpha=def_alpha;
			break;

		case 1 :
			components.floatVal.red=*adress;
			components.floatVal.green=def_green;
			components.floatVal.blue=def_blue;
			components.floatVal.alpha=def_alpha;
			break;

		case 2 :
			components.floatVal.red=*adress;
			components.floatVal.green=*(++adress);
			components.floatVal.blue=def_blue;
			components.floatVal.alpha=def_alpha;
			break;

		case 3 :
			components.floatVal.red=*adress;
			components.floatVal.green=*(++adress);
			components.floatVal.blue=*(++adress);
			components.floatVal.alpha=def_alpha;
			break;

		case 4 :
			components.floatVal.red=*adress;
			components.floatVal.green=*(++adress);
			components.floatVal.blue=*(++adress);
			components.floatVal.alpha=*(++adress);
			break;
	}

	byteSetting.byteMask=0;
}

inline gzRGBA::gzRGBA(gzUInt16 *adress , gzUByte count , gzUInt16 def_red , gzUInt16 def_green , gzUInt16 def_blue , gzUInt16 def_alpha)
{
	switch(count)
	{
		case 0 :
			components.floatVal.red=def_red*GZ_INV_65535;
			components.floatVal.green=def_green*GZ_INV_65535;
			components.floatVal.blue=def_blue*GZ_INV_65535;
			components.floatVal.alpha=def_alpha*GZ_INV_65535;
			break;

		case 1 :
			components.floatVal.red=*adress*GZ_INV_65535;
			components.floatVal.green=def_green*GZ_INV_65535;
			components.floatVal.blue=def_blue*GZ_INV_65535;
			components.floatVal.alpha=def_alpha*GZ_INV_65535;
			break;

		case 2 :
			components.floatVal.red=*adress*GZ_INV_65535;
			components.floatVal.green=*(++adress)*GZ_INV_65535;
			components.floatVal.blue=def_blue*GZ_INV_65535;
			components.floatVal.alpha=def_alpha*GZ_INV_65535;
			break;

		case 3 :
			components.floatVal.red=*adress*GZ_INV_65535;
			components.floatVal.green=*(++adress)*GZ_INV_65535;
			components.floatVal.blue=*(++adress)*GZ_INV_65535;
			components.floatVal.alpha=def_alpha*GZ_INV_65535;
			break;

		case 4 :
			components.floatVal.red=*adress*GZ_INV_65535;
			components.floatVal.green=*(++adress)*GZ_INV_65535;
			components.floatVal.blue=*(++adress)*GZ_INV_65535;
			components.floatVal.alpha=*(++adress)*GZ_INV_65535;
			break;
	}

	byteSetting.byteMask=0;
}

inline gzRGBA::gzRGBA(gzUInt32 rgba)
{
	components.byteVal.alpha=rgba&0xff;
	rgba>>=8;
	components.byteVal.blue=rgba&0xff;
	rgba>>=8;
	components.byteVal.green=rgba&0xff;
	rgba>>=8;
	components.byteVal.red=rgba&0xff;
	byteSetting.byteMask=0xff;
}

inline gzRGBA::gzRGBA(gzUByte *adress , gzUByte count , gzUByte def_red , gzUByte def_green , gzUByte def_blue , gzUByte def_alpha)
{
	switch(count)
	{
		case 0 :
			components.byteVal.red=def_red;
			components.byteVal.green=def_green;
			components.byteVal.blue=def_blue;
			components.byteVal.alpha=def_alpha;
			break;

		case 1 :
			components.byteVal.red=*adress;
			components.byteVal.green=def_green;
			components.byteVal.blue=def_blue;
			components.byteVal.alpha=def_alpha;
			break;

		case 2 :
			components.byteVal.red=*adress;
			components.byteVal.green=*(++adress);
			components.byteVal.blue=def_blue;
			components.byteVal.alpha=def_alpha;
			break;

		case 3 :
			components.byteVal.red=*adress;
			components.byteVal.green=*(++adress);
			components.byteVal.blue=*(++adress);
			components.byteVal.alpha=def_alpha;
			break;

		case 4 :
			components.byteVal.red=*adress;
			components.byteVal.green=*(++adress);
			components.byteVal.blue=*(++adress);
			components.byteVal.alpha=*(++adress);
			break;
	}

	byteSetting.byteMask=0xff;
}


inline gzBool gzRGBA::operator==(const gzRGBA &right) const
{
	return	(getRed()==right.getRed()) &&
			(getBlue()==right.getBlue()) &&
			(getGreen()==right.getGreen()) &&
			(getAlpha()==right.getAlpha()) ;
}

inline gzRGBA gzRGBA::operator+(const gzRGBA &right)
{
	return gzRGBA(getRed()+right.getRed(),getGreen()+right.getGreen(),getBlue()+right.getBlue(),getAlpha()+right.getAlpha());
}

inline gzRGBA gzRGBA::operator/(const gzFloat &f)
{
	return gzRGBA(getRed()/f,getGreen()/f,getBlue()/f,getAlpha()/f);
}

inline gzRGBA gzRGBA::operator*(const gzFloat &f)
{
	return gzRGBA(getRed()*f,getGreen()*f,getBlue()*f,getAlpha()*f);
}


inline gzVoid gzRGBA::convertToFloat()
{
	if(!byteSetting.byteMask)
		return;

	if(byteSetting.byteVal.hasRedByte)
		((gzRGBA *)this)->setRed((gzFloat)components.byteVal.red * GZ_INV_255);

	if(byteSetting.byteVal.hasGreenByte)
		((gzRGBA *)this)->setGreen((gzFloat)components.byteVal.green * GZ_INV_255);

	if(byteSetting.byteVal.hasBlueByte)
		((gzRGBA *)this)->setBlue((gzFloat)components.byteVal.blue * GZ_INV_255);

	if(byteSetting.byteVal.hasAlphaByte)
		((gzRGBA *)this)->setAlpha((gzFloat)components.byteVal.alpha * GZ_INV_255);

	byteSetting.byteMask=0;
}

inline gzVec4 gzRGBA::getColor() const
{
	return gzVec4(getRed(),getGreen(),getBlue(),getAlpha());
}

inline gzFloat *gzRGBA::getColorVector() const
{ 
	if(byteSetting.byteMask)
		((gzRGBA *)this)->convertToFloat();

	return (gzFloat *)&components.floatVal.red; 
}

inline gzRGBA::gzRGBA(gzUByte red_component,gzUByte green_component,gzUByte blue_component,gzUByte alpha_component)
{
	components.byteVal.red=red_component;
	components.byteVal.green=green_component;
	components.byteVal.blue=blue_component;
	components.byteVal.alpha=alpha_component;

	byteSetting.byteMask=0xff;
}

inline gzRGBA::gzRGBA(const gzFloat & red_component,const gzFloat & green_component,const gzFloat & blue_component,const gzFloat & alpha_component)
{
	components.floatVal.red=red_component;
	components.floatVal.green=green_component;
	components.floatVal.blue=blue_component;
	components.floatVal.alpha=alpha_component;

	byteSetting.byteMask=0;
}

inline GZ_BASE_EXPORT gzRGBA::gzRGBA(const gzVec4 &copy)
{
	components.floatVal.red=(gzFloat)copy.v1;
	components.floatVal.green=(gzFloat)copy.v2;
	components.floatVal.blue=(gzFloat)copy.v3;
	components.floatVal.alpha=(gzFloat)copy.v4;

	byteSetting.byteMask=0;
}

inline GZ_BASE_EXPORT gzRGBA::gzRGBA(const gzVec3& copy)
{
	components.floatVal.red = (gzFloat)copy.v1;
	components.floatVal.green = (gzFloat)copy.v2;
	components.floatVal.blue = (gzFloat)copy.v3;
	components.floatVal.alpha = 1.0f;

	byteSetting.byteMask = 0;
}

inline gzBool gzRGBA::isAlphaNonZero() const
{
	if(byteSetting.byteVal.hasAlphaByte)
		return components.byteVal.alpha!=0;
	else
		return components.floatVal.alpha!=0.0f;
}

inline gzVoid gzRGBA::setRed(gzFloat redComponent)
{
	components.floatVal.red=redComponent;
	byteSetting.byteVal.hasRedByte=FALSE;
}

inline gzVoid gzRGBA::setGreen(gzFloat greenComponent)
{
	components.floatVal.green=greenComponent;
	byteSetting.byteVal.hasGreenByte=FALSE;
}

inline gzVoid gzRGBA::setBlue(gzFloat blueComponent)
{
	components.floatVal.blue=blueComponent;
	byteSetting.byteVal.hasBlueByte=FALSE;
}

inline gzVoid gzRGBA::setAlpha(gzFloat alphaComponent)
{
	components.floatVal.alpha=alphaComponent;
	byteSetting.byteVal.hasAlphaByte=FALSE;
}

inline gzVoid gzRGBA::setComponents(gzFloat red_component,gzFloat green_component,gzFloat blue_component,gzFloat alpha_component)
{
	components.floatVal.red=red_component;
	components.floatVal.green=green_component;
	components.floatVal.blue=blue_component;
	components.floatVal.alpha=alpha_component;

	byteSetting.byteMask=0;
}


inline gzFloat gzRGBA::getRed() const
{
	if(byteSetting.byteVal.hasRedByte)
		((gzRGBA *)this)->setRed((gzFloat)components.byteVal.red * GZ_INV_255);

	return components.floatVal.red;
}

inline gzFloat gzRGBA::getGreen() const
{
	if(byteSetting.byteVal.hasGreenByte)
		((gzRGBA *)this)->setGreen((gzFloat)components.byteVal.green*GZ_INV_255);

	return components.floatVal.green;
}

inline gzFloat gzRGBA::getBlue() const
{
	if(byteSetting.byteVal.hasBlueByte)
		((gzRGBA *)this)->setBlue((gzFloat)components.byteVal.blue*GZ_INV_255);

	return components.floatVal.blue;
}

inline gzFloat gzRGBA::getAlpha() const
{
	if(byteSetting.byteVal.hasAlphaByte)
		((gzRGBA *)this)->setAlpha((gzFloat)components.byteVal.alpha*GZ_INV_255);

	return components.floatVal.alpha;
}


inline gzVoid gzRGBA::setRed(gzUByte redComponent)
{
	components.byteVal.red=redComponent;
	byteSetting.byteVal.hasRedByte=TRUE;
}

inline gzVoid gzRGBA::setGreen(gzUByte greenComponent)
{
	components.byteVal.green=greenComponent;
	byteSetting.byteVal.hasGreenByte=TRUE;
}

inline gzVoid gzRGBA::setBlue(gzUByte blueComponent)
{
	components.byteVal.blue=blueComponent;
	byteSetting.byteVal.hasBlueByte=TRUE;
}

inline gzVoid gzRGBA::setAlpha(gzUByte alphaComponent)
{
	components.byteVal.alpha=alphaComponent;
	byteSetting.byteVal.hasAlphaByte=TRUE;
}

inline gzVoid gzRGBA::setComponents(gzUByte red_component,gzUByte green_component,gzUByte blue_component,gzUByte alpha_component)
{
	components.byteVal.red=red_component;
	components.byteVal.green=green_component;
	components.byteVal.blue=blue_component;
	components.byteVal.alpha=alpha_component;

	byteSetting.byteMask=0xff;
}

inline gzUByte gzRGBA::getRedByte() const
{
	if(!byteSetting.byteVal.hasRedByte)
		return (gzUByte)gzMax(gzMin((long)(components.floatVal.red*255),255L),0L);
	else
		return (gzUByte)components.byteVal.red;
}

inline gzUByte gzRGBA::getGreenByte() const
{
	if(!byteSetting.byteVal.hasGreenByte)
		return (gzUByte)gzMax(gzMin((long)(components.floatVal.green*255),255L),0L);
	else 
		return (gzUByte)components.byteVal.green;
}

inline gzUByte gzRGBA::getBlueByte() const
{
	if(!byteSetting.byteVal.hasBlueByte)
		return (gzUByte)gzMax(gzMin((long)(components.floatVal.blue*255),255L),0L);
	else
		return (gzUByte)components.byteVal.blue;
}

inline gzUByte gzRGBA::getAlphaByte() const
{
	if(!byteSetting.byteVal.hasAlphaByte)
		return (gzUByte)gzMax(gzMin((long)(components.floatVal.alpha*255),255L),0L);

	return (gzUByte)components.byteVal.alpha;
}

inline gzVoid gzRGBA::getRGBA(gzUByte *adress, gzUByte count ) const
{
	switch(count)
	{
		case 0:
			break;

		case 1:

			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzUByte)components.byteVal.red;
			else
				*(adress)=(gzUByte)gzMax(gzMin((long)(components.floatVal.red*255),255L),0L);
			break;

		case 2:
			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzUByte)components.byteVal.red;
			else
				*(adress)=(gzUByte)gzMax(gzMin((long)(components.floatVal.red*255),255L),0L);
			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzUByte)components.byteVal.green;
			else
				*(++adress)=(gzUByte)gzMax(gzMin((long)(components.floatVal.green*255),255L),0L);
			break;

		case 3:
			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzUByte)components.byteVal.red;
			else
				*(adress)=(gzUByte)gzMax(gzMin((long)(components.floatVal.red*255),255L),0L);

			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzUByte)components.byteVal.green;
			else
				*(++adress)=(gzUByte)gzMax(gzMin((long)(components.floatVal.green*255),255L),0L);

			if(byteSetting.byteVal.hasBlueByte)
				*(++adress)=(gzUByte)components.byteVal.blue;
			else
				*(++adress)=(gzUByte)gzMax(gzMin((long)(components.floatVal.blue*255),255L),0L);
			break;

		case 4:
			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzUByte)components.byteVal.red;
			else
				*(adress)=(gzUByte)gzMax(gzMin((long)(components.floatVal.red*255),255L),0L);

			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzUByte)components.byteVal.green;
			else
				*(++adress)=(gzUByte)gzMax(gzMin((long)(components.floatVal.green*255),255L),0L);

			if(byteSetting.byteVal.hasBlueByte)
				*(++adress)=(gzUByte)components.byteVal.blue;
			else
				*(++adress)=(gzUByte)gzMax(gzMin((long)(components.floatVal.blue*255),255L),0L);

			if(byteSetting.byteVal.hasAlphaByte)
				*(++adress)=(gzUByte)components.byteVal.alpha;
			else
				*(++adress)=(gzUByte)gzMax(gzMin((long)(components.floatVal.alpha*255),255L),0L);
			break;
	}
}

inline gzVoid gzRGBA::getRGBA(gzFloat *adress, gzUByte count ) const
{
	switch(count)
	{
		case 0:
			break;

		case 1:

			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzFloat)components.byteVal.red * GZ_INV_255;
			else
				*(adress)=components.floatVal.red;
			break;

		case 2:
			if (byteSetting.byteVal.hasRedByte)
				*(adress) = (gzFloat)components.byteVal.red * GZ_INV_255;
			else
				*(adress) = components.floatVal.red;

			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzFloat)components.byteVal.green * GZ_INV_255;
			else
				*(++adress)=components.floatVal.green;
			break;

		case 3:
			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzFloat)components.byteVal.red * GZ_INV_255;
			else
				*(adress)=components.floatVal.red;

			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzFloat)components.byteVal.green * GZ_INV_255;
			else
				*(++adress)=components.floatVal.green;

			if(byteSetting.byteVal.hasBlueByte)
				*(++adress)=(gzFloat)components.byteVal.blue * GZ_INV_255;
			else
				*(++adress)=components.floatVal.blue;
			break;

		case 4:
			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzFloat)components.byteVal.red * GZ_INV_255;
			else
				*(adress)=components.floatVal.red;

			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzFloat)components.byteVal.green * GZ_INV_255;
			else
				*(++adress)=components.floatVal.green;

			if(byteSetting.byteVal.hasBlueByte)
				*(++adress)=(gzFloat)components.byteVal.blue * GZ_INV_255;
			else
				*(++adress)=components.floatVal.blue;

			if(byteSetting.byteVal.hasAlphaByte)
				*(++adress)=(gzFloat)components.byteVal.alpha * GZ_INV_255;
			else
				*(++adress)=components.floatVal.alpha;
			break;
	}
}

inline gzVoid gzRGBA::getRGBA(gzHalf *adress, gzUByte count ) const
{
	switch(count)
	{
		case 0:
			break;

		case 1:

			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzFloat)components.byteVal.red * GZ_INV_255;
			else
				*(adress)=components.floatVal.red;
			break;

		case 2:
			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzFloat)components.byteVal.red * GZ_INV_255;
			else
				*(adress)=(gzUByte)gzMax(gzMin((long)(components.floatVal.red*255),255L),0L);
			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzFloat)components.byteVal.green * GZ_INV_255;
			else
				*(++adress)=components.floatVal.green;
			break;

		case 3:
			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzFloat)components.byteVal.red * GZ_INV_255;
			else
				*(adress)=components.floatVal.red;

			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzFloat)components.byteVal.green * GZ_INV_255;
			else
				*(++adress)=components.floatVal.green;

			if(byteSetting.byteVal.hasBlueByte)
				*(++adress)=(gzFloat)components.byteVal.blue * GZ_INV_255;
			else
				*(++adress)=components.floatVal.blue;
			break;

		case 4:
			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzFloat)components.byteVal.red * GZ_INV_255;
			else
				*(adress)=components.floatVal.red;

			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzFloat)components.byteVal.green * GZ_INV_255;
			else
				*(++adress)=components.floatVal.green;

			if(byteSetting.byteVal.hasBlueByte)
				*(++adress)=(gzFloat)components.byteVal.blue * GZ_INV_255;
			else
				*(++adress)=components.floatVal.blue;

			if(byteSetting.byteVal.hasAlphaByte)
				*(++adress)=(gzFloat)components.byteVal.alpha * GZ_INV_255;
			else
				*(++adress)=components.floatVal.alpha;
			break;
	}
}

inline gzVoid gzRGBA::getRGBA(gzUInt16 *adress, gzUByte count ) const
{
	switch(count)
	{
		case 0:
			break;

		case 1:

			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzUInt16)(components.byteVal.red * 257);
			else
				*(adress)=(gzUInt16)(components.floatVal.red*65535);
			break;

		case 2:
			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzUInt16)(components.byteVal.red * 257);
			else
				*(adress)=(gzUInt16)(components.floatVal.red*65535);

			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzUInt16)(components.byteVal.green * 257);
			else
				*(++adress)=(gzUInt16)(components.floatVal.green*65535);
			break;

		case 3:
			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzUInt16)(components.byteVal.red * 257);
			else
				*(adress)=(gzUInt16)(components.floatVal.red*65535);

			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzUInt16)(components.byteVal.green * 257);
			else
				*(++adress)=(gzUInt16)(components.floatVal.green*65535);

			if(byteSetting.byteVal.hasBlueByte)
				*(++adress)=(gzUInt16)(components.byteVal.blue * 257);
			else
				*(++adress)=(gzUInt16)(components.floatVal.blue*65535);
			break;

		case 4:
			if(byteSetting.byteVal.hasRedByte)
				*(adress)=(gzUInt16)(components.byteVal.red * 257);
			else
				*(adress)=(gzUInt16)(components.floatVal.red*65535);

			if(byteSetting.byteVal.hasGreenByte)
				*(++adress)=(gzUInt16)(components.byteVal.green * 257);
			else
				*(++adress)=(gzUInt16)(components.floatVal.green*65535);

			if(byteSetting.byteVal.hasBlueByte)
				*(++adress)=(gzUInt16)(components.byteVal.blue * 257);
			else
				*(++adress)=(gzUInt16)(components.floatVal.blue*65535);

			if(byteSetting.byteVal.hasAlphaByte)
				*(++adress)=(gzUInt16)(components.byteVal.alpha * 257);
			else
				*(++adress)=(gzUInt16)(components.floatVal.alpha*65535);
			break;
	}
}

inline gzVoid gzRGBA::invert()
{
	components.floatVal.red=1-getRed();
	components.floatVal.green=1-getGreen();
	components.floatVal.blue=1-getBlue();
	components.floatVal.alpha=1-getAlpha();
}

inline gzVoid gzRGBA::clamp()
{
	components.floatVal.red=gzClamp(getRed(),0.0f,1.0f);
	components.floatVal.green=gzClamp(getGreen(),0.0f,1.0f);
	components.floatVal.blue=gzClamp(getBlue(),0.0f,1.0f);
	components.floatVal.alpha=gzClamp(getAlpha(),0.0f,1.0f);
}

inline gzVoid gzRGBA::mulAlpha()
{
	if(byteSetting.byteVal.hasAlphaByte && (components.byteVal.alpha==255))
		return;

	gzFloat alpha=getAlpha();

	components.floatVal.red=getRed()*alpha;
	components.floatVal.green=getGreen()*alpha;
	components.floatVal.blue=getBlue()*alpha;
}

inline gzVoid gzRGBA::divAlpha()
{
	if(byteSetting.byteVal.hasAlphaByte && (components.byteVal.alpha==255))
		return;

	gzFloat alpha=getAlpha();

	if(alpha)
	{
		alpha=1.0f/alpha;

		components.floatVal.red=getRed()*alpha;
		components.floatVal.green=getGreen()*alpha;
		components.floatVal.blue=getBlue()*alpha;
	}
}

inline gzVoid gzRGBA::mul(const gzFloat &value)
{
	if(value<0.0f)
	{
		components.floatVal.red=getRed()*value;
		components.floatVal.green=getGreen()*value;
		components.floatVal.blue=getBlue()*value;
		components.floatVal.alpha=getAlpha()*value;
	}
	else if(value==1.0f)
	{
		return;
	}
	else if(value==0.0f)
	{
		if(byteSetting.byteVal.hasRedByte)
			components.byteVal.red=0;
		else
			components.floatVal.red=0.0f;

		if(byteSetting.byteVal.hasGreenByte)
			components.byteVal.green=0;
		else
			components.floatVal.green=0.0f;

		if(byteSetting.byteVal.hasBlueByte)
			components.byteVal.blue=0;
		else
			components.floatVal.blue=0.0f;

		if(byteSetting.byteVal.hasAlphaByte)
			components.byteVal.alpha=0;
		else
			components.floatVal.alpha=0.0f;
	}
	else if(value==0.25f)
	{
		if(byteSetting.byteVal.hasRedByte)
			components.byteVal.red=(components.byteVal.red>>2);
		else
			components.floatVal.red=getRed()*value;

		if(byteSetting.byteVal.hasGreenByte)
			components.byteVal.green=(components.byteVal.green>>2);
		else
			components.floatVal.green=getGreen()*value;

		if(byteSetting.byteVal.hasBlueByte)
			components.byteVal.blue=(components.byteVal.blue>>2);
		else
			components.floatVal.blue=getBlue()*value;

		if(byteSetting.byteVal.hasAlphaByte)
			components.byteVal.alpha=(components.byteVal.alpha>>2);
		else
			components.floatVal.alpha=getAlpha()*value;
	}
	else if(value==0.5f)
	{
		if(byteSetting.byteVal.hasRedByte)
			components.byteVal.red=(components.byteVal.red>>1);
		else
			components.floatVal.red=getRed()*value;

		if(byteSetting.byteVal.hasGreenByte)
			components.byteVal.green=(components.byteVal.green>>1);
		else
			components.floatVal.green=getGreen()*value;

		if(byteSetting.byteVal.hasBlueByte)
			components.byteVal.blue=(components.byteVal.blue>>1);
		else
			components.floatVal.blue=getBlue()*value;

		if(byteSetting.byteVal.hasAlphaByte)
			components.byteVal.alpha=(components.byteVal.alpha>>1);
		else
			components.floatVal.alpha=getAlpha()*value;
	}
	else 
	{
		if(byteSetting.byteVal.hasRedByte)
			components.byteVal.red=(gzUInt32)(components.byteVal.red*value);
		else
			components.floatVal.red=getRed()*value;

		if(byteSetting.byteVal.hasGreenByte)
			components.byteVal.green=(gzUInt32)(components.byteVal.green*value);
		else
			components.floatVal.green=getGreen()*value;

		if(byteSetting.byteVal.hasBlueByte)
			components.byteVal.blue=(gzUInt32)(components.byteVal.blue*value);
		else
			components.floatVal.blue=getBlue()*value;

		if(byteSetting.byteVal.hasAlphaByte)
			components.byteVal.alpha=(gzUInt32)(components.byteVal.alpha*value);
		else
			components.floatVal.alpha=getAlpha()*value;
	}
}

inline gzVoid gzRGBA::add(const gzRGBA	&value)
{
	if(value.byteSetting.byteVal.hasRedByte)
	{
		if(	byteSetting.byteVal.hasRedByte)
			components.byteVal.red+=value.components.byteVal.red;
		else
			components.floatVal.red=getRed()+((gzFloat)value.components.byteVal.red*GZ_INV_255);
	}
	else
		components.floatVal.red=getRed()+value.getRed();

	if(value.byteSetting.byteVal.hasGreenByte)
	{
		if(byteSetting.byteVal.hasGreenByte)
			components.byteVal.green+=value.components.byteVal.green;
		else
			components.floatVal.green=getGreen()+((gzFloat)value.components.byteVal.green*GZ_INV_255);
	}
	else
		components.floatVal.green=getGreen()+value.getGreen();

	if(value.byteSetting.byteVal.hasBlueByte)
	{
		if(byteSetting.byteVal.hasBlueByte)
			components.byteVal.blue+=value.components.byteVal.blue;
		else
			components.floatVal.blue=getBlue()+((gzFloat)value.components.byteVal.blue*GZ_INV_255);
	}
	else
		components.floatVal.blue=getBlue()+value.getBlue();

	if(value.byteSetting.byteVal.hasAlphaByte)
	{
		if(byteSetting.byteVal.hasAlphaByte)
			components.byteVal.alpha+=value.components.byteVal.alpha;
		else
			components.floatVal.alpha=getAlpha()+((gzFloat)value.components.byteVal.alpha*GZ_INV_255);
	}
	else
		components.floatVal.alpha=getAlpha()+value.getAlpha();
}


inline gzFloat gzRGBA::gray() const
{
	return gzClampf(0.311f*getRed()+0.614f*getGreen()+0.075f*getBlue());
}

inline gzVoid gzRGBA::resetByte() 
{
	components.byteVal.red=components.byteVal.green=components.byteVal.blue=components.byteVal.alpha=0;
	byteSetting.byteMask=0xff;
}

inline gzVoid gzRGBA::resetFloat() 
{
	components.byteVal.red=components.byteVal.green=components.byteVal.blue=components.byteVal.alpha=0;
	byteSetting.byteMask=0;
}

inline gzUByte gzRGBA::grayByte() const
{
	return (gzUByte)(0.311f*getRedByte()+0.614f*getGreenByte()+0.075f*getBlueByte());
}


inline gzVoid gzRGBA::toGray()
{
	gzFloat g=gray();

	setComponents(g,g,g);
}

inline gzVoid gzRGBA::alphaDiv()
{
	gzFloat a=getAlpha();

	if(a>0)
	{
		setComponents(getRed()/a,getGreen()/a,getBlue()/a,a);
	}
}

inline gzRGBA gzRGBA::getSwizzledRGBA(gzRGBASwizzle swizzle , gzFloat R_factor , gzFloat G_factor , gzFloat B_factor , gzFloat A_factor , gzFloat C_value) const
{
	if((swizzle==GZ_MAP_RGBA_TO_RGBA) && (R_factor==GZ_FLOAT_ONE) && (G_factor==GZ_FLOAT_ONE) && (B_factor==GZ_FLOAT_ONE) && (A_factor==GZ_FLOAT_ONE))
		return *this;

	gzFloat R(0),G(0),B(0),A(0),FPX(0);
	gzUByte IR(0),IG(0),IB(0);

	// red component

	if(swizzle & GZ_MAP_R_TO_R)
	{
		if(byteSetting.byteVal.hasRedByte)
			R+=(R_factor*components.byteVal.red*GZ_INV_255);
		else 
			R+=(R_factor*components.floatVal.red);
	}

	if(swizzle & GZ_MAP_R_TO_G)
	{
		if(byteSetting.byteVal.hasRedByte)
			G+=(R_factor*components.byteVal.red*GZ_INV_255);
		else 
			G+=(R_factor*components.floatVal.red);
	}

	if(swizzle & GZ_MAP_R_TO_B)
	{
		if(byteSetting.byteVal.hasRedByte)
			B+=(R_factor*components.byteVal.red*GZ_INV_255);
		else 
			B+=(R_factor*components.floatVal.red);
	}

	if(swizzle & GZ_MAP_R_TO_A)
	{
		if(byteSetting.byteVal.hasRedByte)
			A+=(R_factor*components.byteVal.red*GZ_INV_255);
		else 
			A+=(R_factor*components.floatVal.red);
	}


	// green component

	if(swizzle & GZ_MAP_G_TO_R)
	{
		if(byteSetting.byteVal.hasGreenByte)
			R+=(G_factor*components.byteVal.green*GZ_INV_255);
		else 
			R+=(G_factor*components.floatVal.green);
	}

	if(swizzle & GZ_MAP_G_TO_G)
	{
		if(byteSetting.byteVal.hasGreenByte)
			G+=(G_factor*components.byteVal.green*GZ_INV_255);
		else 
			G+=(G_factor*components.floatVal.green);
	}

	if(swizzle & GZ_MAP_G_TO_B)
	{
		if(byteSetting.byteVal.hasGreenByte)
			B+=(G_factor*components.byteVal.green*GZ_INV_255);
		else 
			B+=(G_factor*components.floatVal.green);
	}

	if(swizzle & GZ_MAP_G_TO_A)
	{
		if(byteSetting.byteVal.hasGreenByte)
			A+=(G_factor*components.byteVal.green*GZ_INV_255);
		else 
			A+=(G_factor*components.floatVal.green);
	}

	// blue component

	if(swizzle & GZ_MAP_B_TO_R)
	{
		if(byteSetting.byteVal.hasBlueByte)
			R+=(B_factor*components.byteVal.blue*GZ_INV_255);
		else 
			R+=(B_factor*components.floatVal.blue);
	}

	if(swizzle & GZ_MAP_B_TO_G)
	{
		if(byteSetting.byteVal.hasBlueByte)
			G+=(B_factor*components.byteVal.blue*GZ_INV_255);
		else 
			G+=(B_factor*components.floatVal.blue);
	}

	if(swizzle & GZ_MAP_B_TO_B)
	{
		if(byteSetting.byteVal.hasBlueByte)
			B+=(B_factor*components.byteVal.blue*GZ_INV_255);
		else 
			B+=(B_factor*components.floatVal.blue);
	}

	if(swizzle & GZ_MAP_B_TO_A)
	{
		if(byteSetting.byteVal.hasBlueByte)
			A+=(B_factor*components.byteVal.blue*GZ_INV_255);
		else 
			A+=(B_factor*components.floatVal.blue);
	}

	// alpha component

	if(swizzle & GZ_MAP_A_TO_R)
	{
		if(byteSetting.byteVal.hasAlphaByte)
			R+=(A_factor*components.byteVal.alpha*GZ_INV_255);
		else 
			R+=(A_factor*components.floatVal.alpha);
	}

	if(swizzle & GZ_MAP_A_TO_G)
	{
		if(byteSetting.byteVal.hasAlphaByte)
			G+=(A_factor*components.byteVal.alpha*GZ_INV_255);
		else 
			G+=(A_factor*components.floatVal.alpha);
	}

	if(swizzle & GZ_MAP_A_TO_B)
	{
		if(byteSetting.byteVal.hasAlphaByte)
			B+=(A_factor*components.byteVal.alpha*GZ_INV_255);
		else 
			B+=(A_factor*components.floatVal.alpha);
	}

	if(swizzle & GZ_MAP_A_TO_A)
	{
		if(byteSetting.byteVal.hasAlphaByte)
			A+=(A_factor*components.byteVal.alpha*GZ_INV_255);
		else 
			A+=(A_factor*components.floatVal.alpha);
	}

	// const component

	if(swizzle & GZ_MAP_C_TO_R)
		R+=C_value;

	if(swizzle & GZ_MAP_C_TO_G)
		G+=C_value;

	if(swizzle & GZ_MAP_C_TO_B)
		B+=C_value;

	if(swizzle & GZ_MAP_C_TO_A)
		A+=C_value;
		
	if(swizzle & GZ_MAP_R_TO_FPX)
	{
		if(byteSetting.byteVal.hasRedByte)
			FPX+=(R_factor*components.byteVal.red*GZ_INV_255);
		else 
			FPX+=(R_factor*components.floatVal.red);
	}

	if(swizzle & GZ_MAP_G_TO_FPX)
	{
		if(byteSetting.byteVal.hasGreenByte)
			FPX+=(G_factor*components.byteVal.green*GZ_INV_255);
		else 
			FPX+=(G_factor*components.floatVal.green);
	}

	if(swizzle & GZ_MAP_B_TO_FPX)
	{
		if(byteSetting.byteVal.hasBlueByte)
			FPX+=(B_factor*components.byteVal.blue*GZ_INV_255);
		else 
			FPX+=(B_factor*components.floatVal.blue);
	}

	if(swizzle & GZ_MAP_A_TO_FPX)
	{
		if(byteSetting.byteVal.hasAlphaByte)
			FPX+=(A_factor*components.byteVal.alpha*GZ_INV_255);
		else 
			FPX+=(A_factor*components.floatVal.alpha);
	}

	if(swizzle & GZ_MAP_C_TO_FPX)
		FPX+=C_value;
	
	if(swizzle & (GZ_MAP_R_TO_FPX|GZ_MAP_G_TO_FPX|GZ_MAP_B_TO_FPX|GZ_MAP_A_TO_FPX|GZ_MAP_C_TO_FPX))
	{
		gzUInt32 IFPX=(gzUInt32)(FPX*0xFFFFFFUL);
		gzUByte SHIFT=1;

		for(gzUInt32 i=0;i<8;i++)
		{
			IB+= (gzUByte)(SHIFT * (IFPX&1));
			IFPX>>=1;
			
			IG+= (gzUByte)(SHIFT * (IFPX&1));
			IFPX>>=1;

			IR+= (gzUByte)(SHIFT * (IFPX&1));
			IFPX>>=1;

			SHIFT<<=1;
		}

		R=IR*GZ_INV_255;
		G=IG*GZ_INV_255;
		B=IB*GZ_INV_255;
	}

	if(swizzle & (GZ_MAP_FPX_TO_R|GZ_MAP_FPX_TO_G|GZ_MAP_FPX_TO_B|GZ_MAP_FPX_TO_A))
	{
		if(byteSetting.byteVal.hasRedByte)
			IR=(gzUByte)components.byteVal.red;
		else 
			IR=(gzUByte)(components.floatVal.red*255);

		if(byteSetting.byteVal.hasGreenByte)
			IG=(gzUByte)components.byteVal.green;
		else 
			IG=(gzUByte)(components.floatVal.green*255);

		if(byteSetting.byteVal.hasBlueByte)
			IB=(gzUByte)components.byteVal.blue;
		else 
			IB=(gzUByte)(components.floatVal.blue*255);


		gzUByte SHIFT=128;
		gzUInt32 IFPX=0;

		for(gzUInt32 i=0;i<8;i++)
		{
			IFPX+=(IR&SHIFT);
			IFPX<<=1;

			IFPX+=(IG&SHIFT);
			IFPX<<=1;

			IFPX+=(IB&SHIFT);

			SHIFT>>=1;
		}

		FPX=(IFPX/(gzFloat)0xFFFFFF);
	}

	if(swizzle & GZ_MAP_FPX_TO_R)
		R+=(R_factor*FPX);

	if(swizzle & GZ_MAP_FPX_TO_G)
		G+=(G_factor*FPX);

	if(swizzle & GZ_MAP_FPX_TO_B)
		B+=(B_factor*FPX);

	if(swizzle & GZ_MAP_FPX_TO_A)
		A+=(A_factor*FPX);


	return gzRGBA(R,G,B,A);
}

inline gzString gzRGBA::asString(const gzString &format) const
{
	gzString result;
	return result.format(format,getRed(),getGreen(),getBlue(),getAlpha());
}


			
#endif //__GZ_RGBA_H__
