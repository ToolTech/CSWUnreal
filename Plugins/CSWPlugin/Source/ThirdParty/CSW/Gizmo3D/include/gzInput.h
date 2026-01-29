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
// File			: gzInput.h
// Module		: 
// Description	: Class definition of the gzInput Management classes
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.306
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
// AMO	011026	Created file 	
// AMO	111107	Added external platform dependent event handler interface in gzInput	(2.5.30)
//
//******************************************************************************
#ifndef __GZ_INPUT_H__
#define __GZ_INPUT_H__

#include "gzMemory.h"
#include "gzTemplates.h"
#include "gzType.h"
#include "gzBase.h"
#include "gzXYZ.h"

/*!	\file 
	\brief Basic management of input


*/
//! Key codes for onKey() virtual method

enum gzKeyValueGroups
{
	GZ_KEY_VALUE_GROUP_CONTROL		= 0x0000,
	GZ_KEY_VALUE_GROUP_PRINTABLE	= 0x0020,		//0b00100000
	GZ_KEY_VALUE_GROUP_EXTENDED		= 0x0080,		//0b10000000

	GZ_KEY_VALUE_GROUP_FUNCTION		= 0x1000,
	GZ_KEY_VALUE_GROUP_MOUSE		= 0x1100,
	GZ_KEY_VALUE_GROUP_NUM_KEYS		= 0x1200,
	GZ_KEY_VALUE_GROUP_INVALID		= 0x2000,

	GZ_KEY_VALUE_GROUP_KEY_MASK		= 0x00FF,
	GZ_KEY_VALUE_GROUP_TYPE_MASK	= 0xFF00,
};

enum gzKeyValue 
{
	GZ_KEY_SHIFT=0x10,
	GZ_KEY_CONTROL=0x11,
	// Some standard keys
    GZ_KEY_ESC=27,

	GZ_KEY_SPACE = ' ',
	GZ_KEY_SPACE_PLUS = '+',
	GZ_KEY_SPACE_MINUS = '-',

	GZ_KEY_0 = '0',
	GZ_KEY_1 = '1',
	GZ_KEY_2 = '2',
	GZ_KEY_3 = '3',
	GZ_KEY_4 = '4',
	GZ_KEY_5 = '5',
	GZ_KEY_6 = '6',
	GZ_KEY_7 = '7',
	GZ_KEY_8 = '8',
	GZ_KEY_9 = '9',

	GZ_KEY_a = 'a',
	GZ_KEY_b = 'b',
	GZ_KEY_c = 'c',
	GZ_KEY_d = 'd',
	GZ_KEY_e = 'e',
	GZ_KEY_f = 'f',
	GZ_KEY_g = 'g',
	GZ_KEY_h = 'h',
	GZ_KEY_i = 'i',
	GZ_KEY_j = 'j',
	GZ_KEY_k = 'k',
	GZ_KEY_l = 'l',
	GZ_KEY_m = 'm',
	GZ_KEY_n = 'n',
	GZ_KEY_o = 'o',
	GZ_KEY_p = 'p',
	GZ_KEY_q = 'q',
	GZ_KEY_r = 'r',
	GZ_KEY_s = 's',
	GZ_KEY_t = 't',
	GZ_KEY_u = 'u',
	GZ_KEY_v = 'v',
	GZ_KEY_w = 'w',
	GZ_KEY_x = 'x',
	GZ_KEY_y = 'y',
	GZ_KEY_z = 'z',

	GZ_KEY_A = 'A',
	GZ_KEY_B = 'B',
	GZ_KEY_C = 'C',
	GZ_KEY_D = 'D',
	GZ_KEY_E = 'E',
	GZ_KEY_F = 'F',
	GZ_KEY_G = 'G',
	GZ_KEY_H = 'H',
	GZ_KEY_I = 'I',
	GZ_KEY_J = 'J',
	GZ_KEY_K = 'K',
	GZ_KEY_L = 'L',
	GZ_KEY_M = 'M',
	GZ_KEY_N = 'N',
	GZ_KEY_O = 'O',
	GZ_KEY_P = 'P',
	GZ_KEY_Q = 'Q',
	GZ_KEY_R = 'R',
	GZ_KEY_S = 'S',
	GZ_KEY_T = 'T',
	GZ_KEY_U = 'U',
	GZ_KEY_V = 'V',
	GZ_KEY_W = 'W',
	GZ_KEY_X = 'X',
	GZ_KEY_Y = 'Y',
	GZ_KEY_Z = 'Z',

	GZ_KEY_LT = '<',
	GZ_KEY_GT = '>',
	GZ_KEY_OR = '|',
    
	GZ_KEY_F1 = GZ_KEY_VALUE_GROUP_FUNCTION,
	GZ_KEY_F2,GZ_KEY_F3,GZ_KEY_F4,GZ_KEY_F5,GZ_KEY_F6,
	GZ_KEY_F7,GZ_KEY_F8,GZ_KEY_F9,GZ_KEY_F10,GZ_KEY_F11,GZ_KEY_F12,GZ_KEY_LEFT,
	GZ_KEY_UP,GZ_KEY_RIGHT,GZ_KEY_DOWN,GZ_KEY_PAGE_UP,GZ_KEY_PAGE_DOWN,GZ_KEY_HOME,
	GZ_KEY_END,GZ_KEY_INSERT,GZ_KEY_DELETE,GZ_KEY_LEFT_ALT,GZ_KEY_LEFT_CTRL,GZ_KEY_RIGHT_CTRL,

	// Mouse keys
	GZ_KEY_LBUTTON=GZ_KEY_VALUE_GROUP_MOUSE,
	GZ_KEY_MBUTTON ,
	GZ_KEY_RBUTTON ,

	// Num keys
	GZ_KEY_MULTIPLY=GZ_KEY_VALUE_GROUP_NUM_KEYS,
	GZ_KEY_ADD,
	GZ_KEY_SEPARATOR,
	GZ_KEY_SUBTRACT,
	GZ_KEY_DECIMAL,
	GZ_KEY_DIVIDE,

	// Error in key
	GZ_KEY_INVALID = GZ_KEY_VALUE_GROUP_INVALID,

};

//! Key states for onKey() virtual method

enum gzKeyState
{	
	GZ_KEY_STATE_PRESSED 	= (1<<0),
	GZ_KEY_STATE_RELEASED   = (1<<1),
	GZ_KEY_STATE_REPEATED   = (1<<2)
};

class gzInputProvider;

//! Generic interface to receive input from gzInputProviders
/*! Add this interface as a base class and register your interface as a input interface to e.g. a gzWindow to get 
	key input etc. without deriving from gzWindow */
class gzInputInterface : public gzTypeInterface
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_SYSTEM_EXPORT);	// typed interface

	GZ_SYSTEM_EXPORT gzInputInterface();
	GZ_SYSTEM_EXPORT virtual ~gzInputInterface();

	GZ_SYSTEM_EXPORT virtual gzBool onKey(gzKeyValue /*key*/ , gzKeyState /*keystate*/ , const gzInt32XY & /*mousePos*/ , const gzInt32XY & /*centerMousePos*/ , gzTypeInterface * /*sender*/){return FALSE;}
	GZ_SYSTEM_EXPORT virtual gzVoid onMouseMove(const gzInt32XY & /*mousePos*/ , const gzInt32XY & /*centerMousePos*/ , gzTypeInterface * /*sender*/){};
	GZ_SYSTEM_EXPORT virtual gzVoid onMouseWheel(const gzInt32 & /*delta*/, const gzInt32XY & /*mousePos*/ , const gzInt32XY & /*centerMousePos*/ , gzTypeInterface * /*sender*/){};

	GZ_SYSTEM_EXPORT virtual gzVoid onKeyEvaluation(){};
	GZ_SYSTEM_EXPORT virtual gzVoid onKeyFocus(gzBool /*gotKeyFocus*/ , gzTypeInterface * /*sender*/){};

	// Platform dependant input event
	GZ_SYSTEM_EXPORT virtual gzVoid onPlatformEvent(const gzUInt32 & /*p1*/ , const gzUInt32 & /*p2*/ , const gzUInt32 & /*p3*/ , gzTypeInterface * /*sender*/){};

private:

	friend class gzInputProvider;
	gzList<gzInputProvider>	m_providers;
};

//! Generic class to implement a source for key inputs
/*! Use this class to add prossible gzInputInterface recievers to you in a observer/notifier design pattern */
class gzInputProvider 
{
public:

	GZ_SYSTEM_EXPORT gzInputProvider();
	GZ_SYSTEM_EXPORT virtual ~gzInputProvider();

	GZ_SYSTEM_EXPORT gzBool triggerOnKey(gzKeyValue key , gzKeyState keystate , const gzInt32XY &mousePos , const gzInt32XY &centerMousePos,gzTypeInterface *sender=NULL);
	GZ_SYSTEM_EXPORT gzVoid triggerOnMouseMove(const gzInt32XY &mousePos , const gzInt32XY &centerMousePos,gzTypeInterface *sender=NULL);
	GZ_SYSTEM_EXPORT gzVoid triggerOnMouseWheel(const gzInt32 &delta , const gzInt32XY &mousePos , const gzInt32XY &centerMousePos,gzTypeInterface *sender=NULL);

	// Platform dependant event
	GZ_SYSTEM_EXPORT gzVoid triggerOnPlatformEvent(const gzUInt32 & p1 , const gzUInt32 & p2 , const gzUInt32 & p3 , gzTypeInterface *sender=NULL);

	GZ_SYSTEM_EXPORT gzVoid triggerKeyEvaluation();

	GZ_SYSTEM_EXPORT gzVoid triggerKeyFocus( gzBool gotKeyFocus ,gzTypeInterface *sender=NULL);

	GZ_SYSTEM_EXPORT gzVoid addInputInterface(gzInputInterface *iface,gzBool first=FALSE);

	GZ_SYSTEM_EXPORT gzVoid removeInputInterface(gzInputInterface *iface);

private:

	friend class gzInputInterface;
	gzList<gzInputInterface>		m_ifaces;

};

class gzInputAction : public gzInputInterface
{
public:

	GZ_SYSTEM_EXPORT gzInputAction(gzKeyValue key, gzKeyState keystate=GZ_KEY_STATE_PRESSED);
	GZ_SYSTEM_EXPORT virtual ~gzInputAction();

	GZ_SYSTEM_EXPORT virtual gzVoid onAction(gzTypeInterface *sender)=0;

	GZ_SYSTEM_EXPORT virtual gzBool onKey(gzKeyValue key , gzKeyState keystate , const gzInt32XY &mousePos , const gzInt32XY &centerMousePos , gzTypeInterface *sender);

private:

	gzKeyValue m_key;
	gzKeyState m_keystate;
};

#endif // __GZ_INPUT_H__







