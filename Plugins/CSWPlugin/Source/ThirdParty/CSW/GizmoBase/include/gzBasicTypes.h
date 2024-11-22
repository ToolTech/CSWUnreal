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
// File			: gzBasictypes.h
// Module		: gzBase
// Description	: Class definition of basic types
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.200
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
// AMO	980819	Created file 	
// AMO	110401	Added static property declaration									2.5.18
// AMO	111221	Changed basic types to reflect 32 and 64 bits system more properly	2.5.40
//
//******************************************************************************

#ifndef __GZ_BASIC_TYPES_H__
#define __GZ_BASIC_TYPES_H__

/*!	\file 
	\brief Type definitions and constants for \b Gizmo3D

	This file provides the abstraction layer between \b Gizmo3D and platform dependant types
	and defined constants. \b Gizmo3D uses constants and definitions simillar to \b OpenGL. \b Gizmo3D uses the 
	prefix \e GZ_ instead of the OpenGL prefix \e GL_ for constants and the prefix 
	\e gz instead of \b OpenGL \e gl for function calls.

	The \b Gizmo3D low level API is independant of the rendering architecture. Even if \b DirectX is used or
	any other simillar API instead of \b OpenGL, the low level API for \b Gizmo3D provides a uniform and fast 
	interface to the rendering architecture.

*/

#include "memory.h"
#include "limits.h"
#include "float.h"

// ------------------------- Detect Win32 environment ----------------------------------------------

#if (defined _WIN32 || defined WIN32 ) && !(defined _WIN64 || defined WIN64 || defined GZ_WIN32 || defined GZ_WINCE )
	#define GZ_WIN32
#endif

#if (defined _WIN64 || defined WIN64) && !defined GZ_WIN64
	#define GZ_WIN64
#endif


// ------------------ Check to see that a valid platform is defined ---------------------------------

#if !defined GZ_WIN32 && !defined GZ_WIN64 && !defined GZ_MAC && !defined GZ_LINUX && !defined GZ_LINUX64 && !defined GZ_SGI && !defined GZ_WINCE && !defined GZ_IOS && !defined GZ_ANDROID && !defined GZ_ANDROID64
#error "You need to define your platform (GZ_WIN32,GZ_WIN64,GZ_MAC,GZ_LINUX,GZ_LINUX64,GZ_SGI,GZ_WINCE,GZ_IOS,GZ_ANDROID,GZ_ANDROID64)"
#endif


// --------------------------- Platform settings ----------------------------------------------------

#if defined GZ_WIN32  // ---------------- WinNT , 2000, XP  ---------------

	// Disable warning about proper C++
	#pragma warning( disable : 4290 )	//! C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
	#pragma warning( disable : 4201 )	//! nonstandard extension used: nameless struct/union
	#pragma warning( disable : 4706 )	//! assignment within conditional expression
	#pragma warning( disable : 4266 )	//! no override available for virtual member function from base, We must allow a base def
	#pragma warning( disable : 4263 )	//! member function does not override any base class virtual member function, same name but different signature
	#pragma warning( disable : 4595 )	//! operator new/delete': non-member operator new or delete functions may not be declared inline
	#pragma warning( disable : 4828 )	//! The file contains a character that is illegal in the current source character set (codepage 65001)

	// !!! Some of the following warnings have been enabled due to the fact we need to identify them

	#if _MSC_VER > 1200
		//#pragma warning(disable : 4244) 
		//#pragma warning(disable : 4996) 
	#endif

	#define GZ_LIB_EXT_SEP_D	"_d"
	#define GZ_64_EXT			""
	#define GZ_LIB_PREFIX		
	#define GZ_DYLIB_EXT		".dll"
	#define GZ_EXE_EXT			".exe"

	#include <windows.h>
	#include "math.h"

	#define LL(x)			(x ## ll)		//! 64 bits constant signed (gzInt64)
	#define LLU(x)			(x ## llu)		//! 64 bits constants unsigned (gzUInt64)
	#define GZ_CALLBACK		__stdcall
	#define GZ_CALLBACK_C	__cdecl
	#define GZ_FASTCALL		__fastcall
	#define GZ_NORETURN		[[noreturn]] 
	//#define GZ_64_BITS

	#ifndef GZ_PLATFORM
		#define GZ_PLATFORM	"win32"
	#endif

	#define GZ_WINDOWS	// Common for all WINDOWS based platforms

	#define GZ_DEFAULT_ENGINE				GZ_ENGINE_OPENGL
	#define GZ_DEFAULT_AUDIO_ENGINE			GZ_AUDIO_ENGINE_OPENAL
	#define GZ_ALLOW_EXTERNAL_VERTEX_STATE	FALSE

#endif

#if defined GZ_WIN64  // ---------------- WinNT , 2000, XP  ---------------

#ifdef GZ_WIN32
#error "Multiple definitions of GZ_WIN32 and GZ_WIN64"
#endif


	// Disable warning about proper C++

	#pragma warning( disable : 4290 )	//! C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
	#pragma warning( disable : 4201 )	//! nonstandard extension used: nameless struct/union
	#pragma warning( disable : 4706 )	//! assignment within conditional expression
	#pragma warning( disable : 4266 )	//! no override available for virtual member function from base, We must allow a base def
	#pragma warning( disable : 4263 )	//! member function does not override any base class virtual member function, same name but different signature
	#pragma warning( disable : 4595 )	//! operator new/delete': non-member operator new or delete functions may not be declared inline
	#pragma warning( disable : 4828 )	//! The file contains a character that is illegal in the current source character set (codepage 65001)

	
	#define GZ_LIB_EXT_SEP_D	"_d"
	#define GZ_LIB_PREFIX		
	#define GZ_64_EXT			"64"
	#define GZ_DYLIB_EXT		".dll"
	#define GZ_EXE_EXT			".exe"

	#include <windows.h>

	#define LL(x)			(x ## ll)		//! 64 bits constant signed (gzInt64)
	#define LLU(x)			(x ## llu)		//! 64 bits constants unsigned (gzUInt64)
	#define GZ_CALLBACK		__stdcall
	#define GZ_CALLBACK_C	__cdecl
	#define GZ_FASTCALL		__fastcall
	#define GZ_64_BITS
	#define GZ_NORETURN		[[noreturn]] 

	#ifndef GZ_PLATFORM
		#define GZ_PLATFORM	"win64"
	#endif

	#define GZ_WINDOWS	// Common for all WINDOWS based platforms

	#define GZ_DEFAULT_ENGINE				GZ_ENGINE_OPENGL
	#define GZ_DEFAULT_AUDIO_ENGINE			GZ_AUDIO_ENGINE_OPENAL
	#define GZ_ALLOW_EXTERNAL_VERTEX_STATE	FALSE

#endif


#ifdef GZ_WINCE

/*
	// Disable warning about proper C++
	#pragma warning( disable : 4290 )
	#pragma warning( disable : 4786 )
*/
	// Definitions of WINNT as minimal level
	#if !defined _WIN32_WINNT | _WIN32_WINNT<0x0400
		#define _WIN32_WINNT 0x0400
	#endif

	#define GZ_LIB_EXT_SEP_D	"_d"
	#define GZ_LIB_PREFIX		
	#define GZ_64_EXT			""
	#define GZ_DYLIB_EXT		".dll"
	#define GZ_EXE_EXT			".exe"

	#include <windows.h>

	#define LL(x) x
	#define LLU(x) x
	#define GZ_CALLBACK		__stdcall
	#define GZ_CALLBACK_C	__cdecl
	#define GZ_FASTCALL		__fastcall
	#define GZ_NORETURN		[[noreturn]] 
	//#define GZ_64_BITS

	#ifndef GZ_PLATFORM
		#define GZ_PLATFORM	"wince"
	#endif

	#define GZ_WINDOWS	// Common for all WINDOWS based platforms

	#define GZ_DEFAULT_ENGINE				GZ_ENGINE_OPENGL
	#define GZ_DEFAULT_AUDIO_ENGINE			GZ_AUDIO_ENGINE_OPENAL
	#define GZ_ALLOW_EXTERNAL_VERTEX_STATE	FALSE

	#define INFINITE            0xFFFFFFFF  // Infinite timeout

#endif


#if defined GZ_LINUX // --------------- Linux on I686 HW -----------------

#ifdef GZ_LINUX64
#error "Multiple definitions of GZ_LINUX and GZ_LINUX64"
#endif

	// Some ignored warnings
	#pragma GCC diagnostic ignored "-Wconversion"				// Removes warning for typecasts used
	#pragma GCC diagnostic ignored "-Wunused-const-variable"	// Removes warning for unused const
	#pragma GCC diagnostic ignored "-Woverloaded-virtual"		// Allow overloded signatures
	#pragma GCC diagnostic ignored "-Wdeprecated-copy"			// Allow implicit constructs
	#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"		// Allow implicit fallthrough
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"			// Allow non strict aliasing


	#define LL(x)			(x ## ll)
	#define LLU(x)			(x ## llu)

	#define GZ_LIB_EXT_SEP_D	"-g"
	#define GZ_64_EXT			""
	#define GZ_LIB_PREFIX		"lib"
	#define GZ_DYLIB_EXT		".so"
	#define GZ_EXE_EXT			""

	#define GZ_UNIX			// Unix or posix like API

	#define GZ_CALLBACK
	#define GZ_CALLBACK_C
	#define GZ_FASTCALL
	#define GZ_NORETURN		/* [[noreturn]] */

	#include <sys/types.h>
    #include <unistd.h>
	#include <ctype.h>
	#include <wctype.h>
	#include <signal.h>
	#include <sys/mman.h>

	#ifndef GZ_PLATFORM
		#define GZ_PLATFORM	"linux686"
	#endif

	#define GZ_DEFAULT_ENGINE				GZ_ENGINE_OPENGL
	#define GZ_DEFAULT_AUDIO_ENGINE			GZ_AUDIO_ENGINE_OPENAL
	#define GZ_ALLOW_EXTERNAL_VERTEX_STATE	FALSE

	#define INFINITE            0xFFFFFFFF  // Infinite timeout

#endif

#if defined GZ_LINUX64 // --------------- Linux on AMD64 HW -----------------

#ifdef GZ_LINUX
	#error "Multiple definitions of GZ_LINUX and GZ_LINUX64"
#endif

	// Some ignored warnings
	#pragma GCC diagnostic ignored "-Wconversion"				// Removes warning for typecasts used
	#pragma GCC diagnostic ignored "-Wunused-const-variable"	// Removes warning for unused const
	#pragma GCC diagnostic ignored "-Woverloaded-virtual"		// Allow overloded signatures
	#pragma GCC diagnostic ignored "-Wdeprecated-copy"			// Allow implicit constructs
	#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"		// Allow implicit fallthrough
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"			// Allow non strict aliasing

	#define LL(x)			(x ## ll)
	#define LLU(x)			(x ## llu)

	#define GZ_LIB_EXT_SEP_D	"-g"
	#define GZ_64_EXT			"64"
	#define GZ_LIB_PREFIX		"lib"
	#define GZ_DYLIB_EXT		".so"
	#define GZ_EXE_EXT			""

	#define GZ_UNIX			// Unix or posix like API

	#define GZ_CALLBACK	
	#define GZ_CALLBACK_C
	#define GZ_FASTCALL
	#define GZ_NORETURN		/* [[noreturn]] */

	#include <ctype.h>
	#include <wctype.h>
	#include <signal.h>
	#include <sys/types.h>
    #include <unistd.h>
	#include <sys/mman.h>

	#define GZ_64_BITS

	#ifndef GZ_PLATFORM
		#define GZ_PLATFORM	"linux64"
	#endif

	#define GZ_DEFAULT_ENGINE				GZ_ENGINE_OPENGL
	#define GZ_DEFAULT_AUDIO_ENGINE			GZ_AUDIO_ENGINE_OPENAL
	#define GZ_ALLOW_EXTERNAL_VERTEX_STATE	FALSE

	#define INFINITE            0xFFFFFFFF  // Infinite timeout

#endif

#ifdef GZ_MAC // ---------------------- MacOSX ---------------------------
	
	// Some ignored warnings
	#pragma GCC diagnostic ignored "-Wconversion"				// Removes warning for typecasts used
	#pragma GCC diagnostic ignored "-Wunused-const-variable"	// Removes warning for unused const
	#pragma GCC diagnostic ignored "-Woverloaded-virtual"		// Allow overloded signatures
	#pragma GCC diagnostic ignored "-Wundefined-var-template"	// Allow external template vars
	#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"		// Allow implicit fallthrough
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"			// Allow non strict aliasing


	//#include <Carbon/Carbon.h>

	#define LL(x)			(x ## ll)
	#define LLU(x)			(x ## llu)
	#define GZ_UNIX			// Unix or posix like API
	#define GZ_LIB_EXT_SEP_D	"-g"
	#define GZ_64_EXT			"64"
	#define GZ_LIB_PREFIX		"lib"
	#define GZ_DYLIB_EXT		".dylib"
	#define GZ_EXE_EXT			""


	#define GZ_CALLBACK
	#define GZ_CALLBACK_C
	#define GZ_FASTCALL
	#define GZ_NORETURN		[[noreturn]] 


	#include <ctype.h>
	#include <wctype.h>
	#include <signal.h>
    
	#ifndef GZ_PLATFORM
		#define GZ_PLATFORM	"osx"
	#endif
	
	#define GZ_64_BITS

	#define GZ_DEFAULT_ENGINE				GZ_ENGINE_OPENGL
	#define GZ_DEFAULT_AUDIO_ENGINE			GZ_AUDIO_ENGINE_OPENAL
	#define GZ_ALLOW_EXTERNAL_VERTEX_STATE	FALSE

	#define INFINITE            0xFFFFFFFF  // Infinite timeout

#endif

#ifdef GZ_IOS // ---------------------- MacOSX IPHONE IPAD ---------------------------

	// Some ignored warnings
	#pragma GCC diagnostic ignored "-Wconversion"				// Removes warning for typecasts used
	#pragma GCC diagnostic ignored "-Wunused-const-variable"	// Removes warning for unused const
	#pragma GCC diagnostic ignored "-Woverloaded-virtual"		// Allow overloded signatures
	#pragma GCC diagnostic ignored "-Wundefined-var-template"	// Allow external template vars
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"			// Allow non strict aliasing


	#define LL(x)			(x ## ll)
	#define LLU(x)			(x ## llu)
	#define GZ_UNIX			// Unix or posix like API
	#define GZ_LIB_EXT_SEP_D	"-g"
	#define GZ_64_EXT			"64"
	#define GZ_LIB_PREFIX		"lib"
	#define GZ_DYLIB_EXT		".dylib"
	#define GZ_EXE_EXT			""


	#define GZ_CALLBACK
	#define GZ_CALLBACK_C
	#define GZ_FASTCALL
	#define GZ_NORETURN		[[noreturn]] 

	#include <ctype.h>
	#include <wctype.h>
	#include <signal.h>

	#ifndef GZ_PLATFORM
		#define GZ_PLATFORM	"iOS"
	#endif

	#define GZ_64_BITS

	#define GZ_DEFAULT_ENGINE				GZ_ENGINE_OPENGLES
	#define GZ_DEFAULT_AUDIO_ENGINE			GZ_AUDIO_ENGINE_OPENAL
	#define GZ_ALLOW_EXTERNAL_VERTEX_STATE	TRUE

	#define INFINITE            0xFFFFFFFF  // Infinite timeout

#endif

#if defined GZ_ANDROID // --------------- Linux on android HW -----------------

#ifdef GZ_ANDROID64
#error "Multiple definitions of GZ_ANDROID and GZ_ANDROID64"
#endif

	// Some ignored warnings
	#pragma GCC diagnostic ignored "-Wconversion"				// Removes warning for typecasts used
	#pragma GCC diagnostic ignored "-Wunused-const-variable"	// Removes warning for unused const
	#pragma GCC diagnostic ignored "-Woverloaded-virtual"		// Allow overloded signatures
	#pragma GCC diagnostic ignored "-Wundefined-var-template"	// Allow external template vars
	#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"		// Allow implicit fallthrough
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"			// Allow non strict aliasing


	#define LL(x)			(x ## ll)
	#define LLU(x)			(x ## llu)

	#define GZ_LIB_EXT_SEP_D	"-g"
	#define GZ_LIB_PREFIX		"lib"
	#define GZ_64_EXT			""
	#define GZ_DYLIB_EXT		".so"
	#define GZ_EXE_EXT			""

	#define GZ_UNIX				// Unix or posix like API

	#define GZ_CALLBACK
	#define GZ_CALLBACK_C
	#define GZ_FASTCALL
	#define GZ_ANDROID_SYST
	#define GZ_NORETURN		

	#include <sys/types.h>
    #include <unistd.h>
	#include <ctype.h>
	#include <wctype.h>
	#include <signal.h>

	#ifndef GZ_PLATFORM
		#define GZ_PLATFORM	"android"
	#endif

	#define GZ_DEFAULT_ENGINE				GZ_ENGINE_OPENGLES
	#define GZ_DEFAULT_AUDIO_ENGINE			GZ_AUDIO_ENGINE_NONE
	#define GZ_ALLOW_EXTERNAL_VERTEX_STATE	TRUE

	#define INFINITE            0xFFFFFFFF  // Infinite timeout

#endif

#if defined GZ_ANDROID64 // --------------- Linux on android 64 bits HW -----------------

#ifdef GZ_ANDROID
#error "Multiple definitions of GZ_ANDROID and GZ_ANDROID64"
#endif

	// Some ignored warnings
	#pragma GCC diagnostic ignored "-Wconversion"				// Removes warning for typecasts used
	#pragma GCC diagnostic ignored "-Wunused-const-variable"	// Removes warning for unused const
	#pragma GCC diagnostic ignored "-Woverloaded-virtual"		// Allow overloded signatures
	#pragma GCC diagnostic ignored "-Wundefined-var-template"	// Allow external template vars
	#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"		// Allow implicit fallthrough
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"			// Allow non strict aliasing


	#define LL(x)			(x ## ll)
	#define LLU(x)			(x ## llu)

	#define GZ_LIB_EXT_SEP_D	"-g"
	#define GZ_LIB_PREFIX		"lib"
	#define GZ_64_EXT			"64"
	#define GZ_DYLIB_EXT		".so"
	#define GZ_EXE_EXT			""

	#define GZ_UNIX				// Unix or posix like API

	#define GZ_CALLBACK
	#define GZ_CALLBACK_C
	#define GZ_FASTCALL
	#define GZ_ANDROID_SYST
	#define GZ_NORETURN		

	#include <sys/types.h>
	#include <unistd.h>
	#include <ctype.h>
	#include <wctype.h>
	#include <signal.h>

	#ifndef GZ_PLATFORM
		#define GZ_PLATFORM	"android64"
	#endif

	#define GZ_64_BITS

	#define GZ_DEFAULT_ENGINE				GZ_ENGINE_OPENGLES
	#define GZ_DEFAULT_AUDIO_ENGINE			GZ_AUDIO_ENGINE_NONE
	#define GZ_ALLOW_EXTERNAL_VERTEX_STATE	TRUE

	#define INFINITE            0xFFFFFFFF  // Infinite timeout

#endif


//**************** some general includes and definitions ********************

#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

//! Returns Max value from \b x or \b y
template <class T> inline const T & gzMax(const T& x , const T& y) { return x>y ? x : y; }

//! Returns Min value from \b x or \b y
template <class T> inline const T & gzMin(const T& x , const T& y) { return x<y ? x : y; }

template <class T> inline const T & gzClamp(const T& x , const T &min=(T)-1 , const T &max=(T)1 ) { return x<max ? x>min ? x : min : max; }

template <class T> inline void gzSwap(T& a , T& b ) { T temp=a;a=b;b=temp;}

template <class T> inline void gzSwapAddr(T** a) { T* addr=*a;T temp=*addr;++addr;**a=*addr;*addr=temp;*a=addr+1;}

template <class T> inline const T gzSign(const T& x ) { return x>=0 ? (T)1 : (T)-1; }

//******************* basic types for gizmo ************************************

typedef unsigned char	gzBool;			//!< Boolean type 
typedef unsigned int	gzBitfield;		//!< 32 bits bitfield
typedef signed char 	gzByte;			//!< Signed byte value -128 to +127	
typedef char 			gzChar;			//!< Signed byte char -128 to +127	
typedef unsigned char 	gzUByte;		//!< Unsigned byte value 0 to 255
typedef gzByte 			gzInt8;			//!< Compatibility with gzByte	
typedef gzUByte 		gzUInt8;		//!< Compatibility with gzUByte
typedef short			gzInt16;		//!< Signed 16 bit integer
typedef unsigned short	gzUInt16;		//!< Unsigned 16 bit integer
typedef int				gzInt32;		//!< Signed 32 bit integer 
typedef unsigned int	gzUInt32;		//!< Unsigned 32 bit integer
typedef float 			gzFloat;		//!< IEEE 754 32 bit float
typedef double			gzDouble;		//!< IEEE 754 64 bit double
typedef gzUInt32		gzHandle;		//!< Unsigned 32 bit handle
typedef gzUInt32		gzWideBool;		//!< Unsigned 32 bit bool. TRUE!=0

#if !defined GZ_USE_SHORT_WCHAR 
#define L(x)			L##x
typedef wchar_t			gzWideChar;		//!< Wide character value	(wchar_t)
#else
#define L(x)			gzString(x).getWideString()
typedef unsigned short	gzWideChar;		//!< Wide character value	(non standard gzUInt16)
#endif

#if defined GZ_UNIX 		// Check to see that wchar_t is compatible with Windows
#include "wchar.h"
#if (WCHAR_MAX!=0xFFFF) & !defined GZ_USE_SHORT_WCHAR & !defined GZ_SKIP_WCHAR_TEST	// two bytes unsigned short
	// To ensure the same compatibility with wide strings on all platforms
	#error	You need to compile GizmoSDK with -fshort-wchar or define GZ_USE_SHORT_WCHAR
#endif
#endif

#ifdef	GZ_WINDOWS
	typedef __int64				gzInt64;		//!< 64 bit signed integer
	typedef unsigned __int64	gzUInt64;		//!< 64 bit unsigned integer

	#define IP2LP(x)			((long *)x)		// On windows long==int in 64 bit build
	#define UIP2ULP(x)			((unsigned long *)x)

#else
	typedef long long			gzInt64;		//!< 64 bit signed integer
	typedef unsigned long long	gzUInt64;		//!< 64 bit unsigned integer

	#define IP2LP(x)			(x)
	#define UIP2ULP(x)			(x)

#endif

// ----------------------- Min/Max --------------------------------------------

#define GZ_MAX_UINT16		0xfffful
#define GZ_MAX_UINT32		0xfffffffful
#define GZ_MAX_UINT64		0xffffffffffffffffull

typedef void			gzVoid;				//!< Void ( no result )
typedef void *			gzMemPointer;		//!< Void * (anything)

// Temprary fix to save cast error that are controlled
#define gzCastToUInt32(x)	((gzUInt32)x)
#define gzCastToInt32(x)	((gzInt32)x)
#define gzCastToFloat(x)	((gzFloat32)x)

// Empty default val2ptr
inline gzVoid * gzVal2Ptr(gzVoid * x)					{ return x; }

#if defined GZ_64_BITS	// 64 bit pointers

inline gzUInt64 gzPtr2Val(const gzVoid * const x)	{ return (gzUInt64)x; }
inline gzVoid * gzVal2Ptr(gzUInt64 x)				{ return (gzVoid *)x; }

typedef gzUInt64	gzMemSize;		//!< Size of memory chunk       (gzUInt64)
typedef gzInt64		gzMemOffset;	//!< +- offset of memory chunk	(gzInt64)

#else					// 32 bit pointers

#if defined GZ_WINDOWS
// For a fix in VS9 ------------------------
	#pragma warning(push)
	#pragma warning(disable: 4311)
	#pragma warning(disable: 4312)
#endif // GZ_WINDOWS

inline gzUInt32 gzPtr2Val(const gzVoid * const x)		{ return (gzUInt32)(gzUInt64)x; }
inline gzVoid * gzVal2Ptr(gzUInt64 x)					{ return (gzVoid *)(gzUInt32)x; }

#if defined GZ_WINDOWS
	#pragma warning(pop)	// End fix --------
#endif // GZ_WINDOWS

typedef gzUInt32	gzMemSize;		//!< Size of memory chunk	(gzUInt32)
typedef gzInt32		gzMemOffset;	//!< +- offset of memory chunk	(gzInt32)

#endif

//! Cast a non zero value to a bool true value or false value
#define GZ_BOOL(x)	((x) ? TRUE : FALSE)

// ********************** Default Library Extension ***************************

#ifdef GZ_DEBUG
	#define GZ_LIB_EXT GZ_64_EXT GZ_LIB_EXT_SEP_D
#else
	#define GZ_LIB_EXT GZ_64_EXT ""
#endif

//************************** math constants ************************************

//! Definition of PI etc.
constexpr gzDouble		GZ_PI=3.14159265358979323846264338;
constexpr gzDouble		GZ_2PI=GZ_PI*2;
constexpr gzDouble		GZ_PI_HALF=GZ_PI/2;
constexpr gzDouble		GZ_PI_QUARTER=GZ_PI/4;
	 
constexpr gzFloat		GZ_PI_F=3.14159265358979323846264338f;
constexpr gzFloat		GZ_2PI_F=GZ_PI_F*2;
constexpr gzFloat		GZ_PI_HALF_F=GZ_PI_F/2;
constexpr gzFloat		GZ_PI_QUARTER_F=GZ_PI_F/4;
	 
	
constexpr gzDouble		GZ_INV_PI=1.0/GZ_PI;
constexpr gzDouble		GZ_INV_2PI=1.0/GZ_2PI;
constexpr gzDouble		GZ_INV_PI_HALF=1.0/GZ_PI_HALF;
constexpr gzDouble		GZ_INV_PI_QUARTER=1.0/GZ_PI_QUARTER;
	
constexpr gzFloat		GZ_INV_PI_F=1.0f/GZ_PI_F;
constexpr gzFloat		GZ_INV_2PI_F=1.0f/GZ_2PI_F;
constexpr gzFloat		GZ_INV_PI_HALF_F=1.0f/GZ_PI_HALF_F;
constexpr gzFloat		GZ_INV_PI_QUARTER_F=1.0f/GZ_PI_QUARTER_F;
	
constexpr gzFloat		GZ_INV_255=1.0f/255.0f;
constexpr gzFloat		GZ_INV_65535=1.0f/65535.0f;
	
constexpr gzFloat		GZ_FLOAT_ONE=1.0f;
constexpr gzFloat		GZ_FLOAT_ZERO=0.0f;
	 
constexpr gzDouble		GZ_DOUBLE_ONE=1.0;
constexpr gzDouble		GZ_DOUBLE_ZERO=0.0;
	 
constexpr gzDouble		GZ_DEG2RAD=0.017453292519943295769236907666667;
constexpr gzDouble		GZ_MILS2RAD=9.8174770424681038701957605625011e-4;
constexpr gzDouble		GZ_RAD2DEG=57.295779513082320876798154873916;
constexpr gzDouble		GZ_RAD2MILS=1018.5916357881301489208560866473;
	 
constexpr gzDouble		GZ_SQRT_2=1.4142135623730950488016887242097;
constexpr gzDouble		GZ_INV_SQRT_2=0.70710678118654752440084436210485;
constexpr gzDouble		GZ_SQRT_3=1.7320508075688772935274463415059;
constexpr gzDouble		GZ_INV_SQRT_3=0.57735026918962576450914878050196;
	 
constexpr gzFloat		GZ_DEG2RAD_F=0.017453292519943295769236907666667f;
constexpr gzFloat		GZ_MILS2RAD_F=9.8174770424681038701957605625011e-4f;
constexpr gzFloat		GZ_RAD2DEG_F=57.295779513082320876798154873916f;
constexpr gzFloat		GZ_RAD2MILS_F=1018.5916357881301489208560866473f;
	 
constexpr gzFloat		GZ_SQRT_2_F=1.4142135623730950488016887242097f;
constexpr gzFloat		GZ_INV_SQRT_2_F=0.70710678118654752440084436210485f;
constexpr gzFloat		GZ_SQRT_3_F=1.7320508075688772935274463415059f;
constexpr gzFloat		GZ_INV_SQRT_3_F=0.57735026918962576450914878050196f;

//************************* clamping class utilites ******************************

//! Clamps double values between 0.0 and 1.0
template <class T,int MIN_VAL=0,int MAX_VAL=1> class gzClampType
{
public:
	gzClampType(const T &val=(T)MIN_VAL) {m_val=gzMax(gzMin(val,(T)MAX_VAL),(T)MIN_VAL);}

	const gzClampType<T> & operator=(const T &val)
	{
		m_val=gzMax(gzMin(val,(T)MAX_VAL),(T)MIN_VAL);

		return *this;
	}

	operator const T &() const { return m_val; }

private:
	T m_val;
};


//! Clamps double values between 0.0 and 1.0
typedef gzClampType<gzDouble,0,1> gzClampd;

//! Clamps float values between 0.0 and 1.0
typedef gzClampType<gzFloat,0,1> gzClampf;

//******************************* constants ****************************************

// Some constants to avoid conflicts with OpenGL

/*! Constants taken from OpenGL 1.2. Note that Gizmo3D uses the same syntax for the rendering API
as OpenGL. However Gizmo3D is not dependant on using OpenGL. By using the Gizmo3D api you can change 
between OpenGL, DirectX or any other implemented low level graphics API.
*/

typedef enum : gzUInt32 
{
	/* Boolean values */
	GZ_FALSE										= 0,
	GZ_TRUE											= 1,

	/* Data types */
	GZ_BYTE											= 0x1400,
	GZ_UNSIGNED_BYTE								= 0x1401,
	GZ_SHORT										= 0x1402,
	GZ_UNSIGNED_SHORT								= 0x1403,
	GZ_INT											= 0x1404,
	GZ_UNSIGNED_INT									= 0x1405,
	GZ_FLOAT										= 0x1406,
	GZ_DOUBLE										= 0x140A,
	GZ_2_BYTES										= 0x1407,
	GZ_3_BYTES										= 0x1408,
	GZ_4_BYTES										= 0x1409,
	GZ_HALF_FLOAT									= 0x140B,

	/* Primitives */
	GZ_LINES										= 0x0001,
	GZ_POINTS										= 0x0000,
	GZ_LINE_STRIP									= 0x0003,
	GZ_LINE_LOOP									= 0x0002,
	GZ_TRIANGLES									= 0x0004,
	GZ_TRIANGLE_STRIP								= 0x0005,
	GZ_TRIANGLE_FAN									= 0x0006,
	GZ_QUADS										= 0x0007,
	GZ_QUAD_STRIP									= 0x0008,
	GZ_POLYGON										= 0x0009,
	GZ_EDGE_FLAG									= 0x0B43,

	/* Vertex Arrays */
	GZ_VERTEX_ARRAY									= 0x8074,
	GZ_NORMAL_ARRAY									= 0x8075,
	GZ_COLOR_ARRAY									= 0x8076,
	GZ_INDEX_ARRAY									= 0x8077,
	GZ_TEXTURE_COORD_ARRAY							= 0x8078,
	GZ_EDGE_FLAG_ARRAY								= 0x8079,
	GZ_VERTEX_ARRAY_SIZE							= 0x807A,
	GZ_VERTEX_ARRAY_TYPE							= 0x807B,
	GZ_VERTEX_ARRAY_STRIDE							= 0x807C,
	GZ_NORMAL_ARRAY_TYPE							= 0x807E,
	GZ_NORMAL_ARRAY_STRIDE							= 0x807F,
	GZ_COLOR_ARRAY_SIZE								= 0x8081,
	GZ_COLOR_ARRAY_TYPE								= 0x8082,
	GZ_COLOR_ARRAY_STRIDE							= 0x8083,
	GZ_INDEX_ARRAY_TYPE								= 0x8085,
	GZ_INDEX_ARRAY_STRIDE							= 0x8086,
	GZ_TEXTURE_COORD_ARRAY_SIZE						= 0x8088,
	GZ_TEXTURE_COORD_ARRAY_TYPE						= 0x8089,
	GZ_TEXTURE_COORD_ARRAY_STRIDE					= 0x808A,
	GZ_EDGE_FLAG_ARRAY_STRIDE						= 0x808C,
	GZ_VERTEX_ARRAY_POINTER							= 0x808E,
	GZ_NORMAL_ARRAY_POINTER							= 0x808F,
	GZ_COLOR_ARRAY_POINTER							= 0x8090,
	GZ_INDEX_ARRAY_POINTER							= 0x8091,
	GZ_TEXTURE_COORD_ARRAY_POINTER					= 0x8092,
	GZ_EDGE_FLAG_ARRAY_POINTER						= 0x8093,

	GZ_V2F											= 0x2A20,
	GZ_V3F											= 0x2A21,
	GZ_C4UB_V2F										= 0x2A22,
	GZ_C4UB_V3F										= 0x2A23,
	GZ_C3F_V3F										= 0x2A24,
	GZ_N3F_V3F										= 0x2A25,
	GZ_C4F_N3F_V3F									= 0x2A26,
	GZ_T2F_V3F										= 0x2A27,
	GZ_T4F_V4F										= 0x2A28,
	GZ_T2F_C4UB_V3F									= 0x2A29,
	GZ_T2F_C3F_V3F									= 0x2A2A,
	GZ_T2F_N3F_V3F									= 0x2A2B,
	GZ_T2F_C4F_N3F_V3F								= 0x2A2C,
	GZ_T4F_C4F_N3F_V4F								= 0x2A2D,

	/* Matrix Mode */
	GZ_MATRIX_MODE									= 0x0BA0,
	GZ_MODELVIEW									= 0x1700,
	GZ_PROJECTION									= 0x1701,
	GZ_TEXTURE										= 0x1702,

	/* Points */
	GZ_POINT_SMOOTH									= 0x0B10,
	GZ_POINT_SIZE									= 0x0B11,
	GZ_POINT_SIZE_GRANULARITY 						= 0x0B13,
	GZ_POINT_SIZE_RANGE								= 0x0B12,

	/* Lines */
	GZ_LINE_SMOOTH									= 0x0B20,
	GZ_LINE_STIPPLE									= 0x0B24,
	GZ_LINE_STIPPLE_PATTERN							= 0x0B25,
	GZ_LINE_STIPPLE_REPEAT							= 0x0B26,
	GZ_LINE_WIDTH									= 0x0B21,
	GZ_LINE_WIDTH_GRANULARITY						= 0x0B23,
	GZ_LINE_WIDTH_RANGE								= 0x0B22,

	/* Polygons */
	GZ_POINT										= 0x1B00,
	GZ_LINE											= 0x1B01,
	GZ_FILL											= 0x1B02,
	GZ_CCW											= 0x0901,
	GZ_CW											= 0x0900,
	GZ_FRONT										= 0x0404,
	GZ_BACK											= 0x0405,
	GZ_CULL_FACE									= 0x0B44,
	GZ_CULL_FACE_MODE								= 0x0B45,
	GZ_POLYGON_SMOOTH								= 0x0B41,
	GZ_POLYGON_STIPPLE								= 0x0B42,
	GZ_FRONT_FACE									= 0x0B46,
	GZ_POLYGON_MODE									= 0x0B40,
	GZ_POLYGON_OFFSET_FACTOR						= 0x8038,
	GZ_POLYGON_OFFSET_UNITS							= 0x2A00,
	GZ_POLYGON_OFFSET_POINT							= 0x2A01,
	GZ_POLYGON_OFFSET_LINE							= 0x2A02,
	GZ_POLYGON_OFFSET_FILL							= 0x8037,

	/* Display Lists */
	GZ_COMPILE										= 0x1300,
	GZ_COMPILE_AND_EXECUTE							= 0x1301,
	GZ_LIST_BASE									= 0x0B32,
	GZ_LIST_INDEX									= 0x0B33,
	GZ_LIST_MODE									= 0x0B30,

	/* Depth buffer */
	GZ_NEVER										= 0x0200,
	GZ_LESS											= 0x0201,
	GZ_GEQUAL										= 0x0206,
	GZ_LEQUAL										= 0x0203,
	GZ_GREATER										= 0x0204,
	GZ_NOTEQUAL										= 0x0205,
	GZ_EQUAL										= 0x0202,
	GZ_ALWAYS										= 0x0207,
	GZ_DEPTH_TEST									= 0x0B71,
	GZ_DEPTH_BITS									= 0x0D56,
	GZ_DEPTH_CLEAR_VALUE							= 0x0B73,
	GZ_DEPTH_FUNC									= 0x0B74,
	GZ_DEPTH_RANGE									= 0x0B70,
	GZ_DEPTH_WRITEMASK								= 0x0B72,
	GZ_DEPTH_COMPONENT								= 0x1902,

	/* Lighting */
	GZ_LIGHTING										= 0x0B50,
	GZ_LIGHT0										= 0x4000,
	GZ_LIGHT1										= 0x4001,
	GZ_LIGHT2										= 0x4002,
	GZ_LIGHT3										= 0x4003,
	GZ_LIGHT4										= 0x4004,
	GZ_LIGHT5										= 0x4005,
	GZ_LIGHT6										= 0x4006,
	GZ_LIGHT7										= 0x4007,
	GZ_SPOT_EXPONENT								= 0x1205,
	GZ_SPOT_CUTOFF									= 0x1206,
	GZ_CONSTANT_ATTENUATION							= 0x1207,
	GZ_LINEAR_ATTENUATION							= 0x1208,
	GZ_QUADRATIC_ATTENUATION						= 0x1209,
	GZ_AMBIENT										= 0x1200,
	GZ_DIFFUSE										= 0x1201,
	GZ_SPECULAR										= 0x1202,
	GZ_SHININESS									= 0x1601,
	GZ_EMISSION										= 0x1600,
	GZ_POSITION										= 0x1203,
	GZ_SPOT_DIRECTION								= 0x1204,
	GZ_AMBIENT_AND_DIFFUSE							= 0x1602,
	GZ_COLOR_INDEXES								= 0x1603,
	GZ_LIGHT_MODEL_TWO_SIDE							= 0x0B52,
	GZ_LIGHT_MODEL_LOCAL_VIEWER						= 0x0B51,
	GZ_LIGHT_MODEL_AMBIENT							= 0x0B53,
	GZ_FRONT_AND_BACK								= 0x0408,
	GZ_SHADE_MODEL									= 0x0B54,
	GZ_FLAT											= 0x1D00,
	GZ_SMOOTH										= 0x1D01,
	GZ_COLOR_MATERIAL								= 0x0B57,
	GZ_COLOR_MATERIAL_FACE							= 0x0B55,
	GZ_COLOR_MATERIAL_PARAMETER						= 0x0B56,
	GZ_NORMALIZE									= 0x0BA1,

	/* User clipping planes */
	GZ_CLIP_PLANE0									= 0x3000,
	GZ_CLIP_PLANE1									= 0x3001,
	GZ_CLIP_PLANE2									= 0x3002,
	GZ_CLIP_PLANE3									= 0x3003,
	GZ_CLIP_PLANE4									= 0x3004,
	GZ_CLIP_PLANE5									= 0x3005,

	/* Accumulation buffer */
	GZ_ACCUM_RED_BITS								= 0x0D58,
	GZ_ACCUM_GREEN_BITS								= 0x0D59,
	GZ_ACCUM_BLUE_BITS								= 0x0D5A,
	GZ_ACCUM_ALPHA_BITS								= 0x0D5B,
	GZ_ACCUM_CLEAR_VALUE							= 0x0B80,
	GZ_ACCUM										= 0x0100,
	GZ_ADD											= 0x0104,
	GZ_LOAD											= 0x0101,
	GZ_MULT											= 0x0103,
	GZ_RETURN										= 0x0102,

	/* Alpha testing */
	GZ_ALPHA_TEST									= 0x0BC0,
	GZ_ALPHA_TEST_REF								= 0x0BC2,
	GZ_ALPHA_TEST_FUNC								= 0x0BC1,

	/* Blending */
	GZ_BLEND										= 0x0BE2,
	GZ_BLEND_SRC									= 0x0BE1,
	GZ_BLEND_DST									= 0x0BE0,
	GZ_ZERO											= 0,
	GZ_ONE											= 1,
	GZ_SRC_COLOR									= 0x0300,
	GZ_ONE_MINUS_SRC_COLOR							= 0x0301,
	GZ_DST_COLOR									= 0x0306,
	GZ_ONE_MINUS_DST_COLOR							= 0x0307,
	GZ_SRC_ALPHA									= 0x0302,
	GZ_ONE_MINUS_SRC_ALPHA							= 0x0303,
	GZ_DST_ALPHA									= 0x0304,
	GZ_ONE_MINUS_DST_ALPHA							= 0x0305,
	GZ_SRC_ALPHA_SATURATE							= 0x0308,
	GZ_CONSTANT_COLOR								= 0x8001,
	GZ_ONE_MINUS_CONSTANT_COLOR						= 0x8002,
	GZ_CONSTANT_ALPHA								= 0x8003,
	GZ_ONE_MINUS_CONSTANT_ALPHA						= 0x8004,

	/* Render Mode */
	GZ_FEEDBACK										= 0x1C01,
	GZ_RENDER										= 0x1C00,
	GZ_SELECT										= 0x1C02,

	/* Feedback */
	GZ_2D											= 0x0600,
	GZ_3D											= 0x0601,
	GZ_3D_COLOR										= 0x0602,
	GZ_3D_COLOR_TEXTURE								= 0x0603,
	GZ_4D_COLOR_TEXTURE								= 0x0604,
	GZ_POINT_TOKEN									= 0x0701,
	GZ_LINE_TOKEN									= 0x0702,
	GZ_LINE_RESET_TOKEN								= 0x0707,
	GZ_POLYGON_TOKEN								= 0x0703,
	GZ_BITMAP_TOKEN									= 0x0704,
	GZ_DRAW_PIXEL_TOKEN								= 0x0705,
	GZ_COPY_PIXEL_TOKEN								= 0x0706,
	GZ_PASS_THROUGH_TOKEN							= 0x0700,
	GZ_FEEDBACK_BUFFER_POINTER						= 0x0DF0,
	GZ_FEEDBACK_BUFFER_SIZE							= 0x0DF1,
	GZ_FEEDBACK_BUFFER_TYPE							= 0x0DF2,

	/* Selection */
	GZ_SELECTION_BUFFER_POINTER						= 0x0DF3,
	GZ_SELECTION_BUFFER_SIZE						= 0x0DF4,

	/* Fog */
	GZ_FOG											= 0x0B60,
	GZ_FOG_MODE										= 0x0B65,
	GZ_FOG_DENSITY									= 0x0B62,
	GZ_FOG_COLOR									= 0x0B66,
	GZ_FOG_INDEX									= 0x0B61,
	GZ_FOG_START									= 0x0B63,
	GZ_FOG_END										= 0x0B64,
	GZ_LINEAR										= 0x2601,
	GZ_EXP											= 0x0800,
	GZ_EXP2											= 0x0801,

	/* Logic Ops */
	GZ_LOGIC_OP										= 0x0BF1,
	GZ_INDEX_LOGIC_OP								= 0x0BF1,
	GZ_COLOR_LOGIC_OP								= 0x0BF2,
	GZ_LOGIC_OP_MODE								= 0x0BF0,
	GZ_CLEAR										= 0x1500,
	GZ_SET											= 0x150F,
	GZ_COPY											= 0x1503,
	GZ_COPY_INVERTED								= 0x150C,
	GZ_NOOP											= 0x1505,
	GZ_INVERT										= 0x150A,
	GZ_AND											= 0x1501,
	GZ_NAND											= 0x150E,
	GZ_OR											= 0x1507,
	GZ_NOR											= 0x1508,
	GZ_XOR											= 0x1506,
	GZ_EQUIV										= 0x1509,
	GZ_AND_REVERSE									= 0x1502,
	GZ_AND_INVERTED									= 0x1504,
	GZ_OR_REVERSE									= 0x150B,
	GZ_OR_INVERTED									= 0x150D,

	/* Stencil */
	GZ_STENCIL_TEST									= 0x0B90,
	GZ_STENCIL_WRITEMASK							= 0x0B98,
	GZ_STENCIL_BITS									= 0x0D57,
	GZ_STENCIL_FUNC									= 0x0B92,
	GZ_STENCIL_VALUE_MASK							= 0x0B93,
	GZ_STENCIL_REF									= 0x0B97,
	GZ_STENCIL_FAIL									= 0x0B94,
	GZ_STENCIL_PASS_DEPTH_PASS						= 0x0B96,
	GZ_STENCIL_PASS_DEPTH_FAIL						= 0x0B95,
	GZ_STENCIL_CLEAR_VALUE							= 0x0B91,
	GZ_STENCIL_INDEX								= 0x1901,
	GZ_KEEP											= 0x1E00,
	GZ_REPLACE										= 0x1E01,
	GZ_INCR											= 0x1E02,
	GZ_DECR											= 0x1E03,

	/* Buffers, Pixel Drawing/Reading */
	GZ_NONE											= 0,
	GZ_LEFT											= 0x0406,
	GZ_RIGHT										= 0x0407,
	/*GZ_FRONT										= 0x0404, */
	/*GZ_BACK										= 0x0405, */
	/*GZ_FRONT_AND_BACK								= 0x0408, */
	GZ_FRONT_LEFT									= 0x0400,
	GZ_FRONT_RIGHT									= 0x0401,
	GZ_BACK_LEFT									= 0x0402,
	GZ_BACK_RIGHT									= 0x0403,
	GZ_AUX0											= 0x0409,
	GZ_AUX1											= 0x040A,
	GZ_AUX2											= 0x040B,
	GZ_AUX3											= 0x040C,
	GZ_COLOR_INDEX									= 0x1900,
	GZ_RED											= 0x1903,
	GZ_GREEN										= 0x1904,
	GZ_BLUE											= 0x1905,
	GZ_ALPHA										= 0x1906,
	GZ_LUMINANCE									= 0x1909,
	GZ_LUMINANCE_ALPHA								= 0x190A,
	GZ_ALPHA_BITS									= 0x0D55,
	GZ_RED_BITS										= 0x0D52,
	GZ_GREEN_BITS									= 0x0D53,
	GZ_BLUE_BITS									= 0x0D54,
	GZ_INDEX_BITS									= 0x0D51,
	GZ_SUBPIXEL_BITS								= 0x0D50,
	GZ_AUX_BUFFERS									= 0x0C00,
	GZ_READ_BUFFER									= 0x0C02,
	GZ_DRAW_BUFFER									= 0x0C01,
	GZ_DOUBLEBUFFER									= 0x0C32,
	GZ_STEREO										= 0x0C33,
	GZ_BITMAP										= 0x1A00,
	GZ_COLOR										= 0x1800,
	GZ_DEPTH										= 0x1801,
	GZ_STENCIL										= 0x1802,
	GZ_DITHER										= 0x0BD0,
	GZ_RGB											= 0x1907,
	GZ_RGBA											= 0x1908,

	/* Implementation limits */
	GZ_MAX_LIST_NESTING								= 0x0B31,
	GZ_MAX_ATTRIB_STACK_DEPTH						= 0x0D35,
	GZ_MAX_MODELVIEW_STACK_DEPTH					= 0x0D36,
	GZ_MAX_NAME_STACK_DEPTH							= 0x0D37,
	GZ_MAX_PROJECTION_STACK_DEPTH					= 0x0D38,
	GZ_MAX_TEXTURE_STACK_DEPTH						= 0x0D39,
	GZ_MAX_EVAL_ORDER								= 0x0D30,
	GZ_MAX_LIGHTS									= 0x0D31,
	GZ_MAX_CLIP_PLANES								= 0x0D32,
	GZ_MAX_TEXTURE_SIZE								= 0x0D33,
	GZ_MAX_PIXEL_MAP_TABLE							= 0x0D34,
	GZ_MAX_VIEWPORT_DIMS							= 0x0D3A,
	GZ_MAX_CLIENT_ATTRIB_STACK_DEPTH				= 0x0D3B,

	/* Gets */
	GZ_ATTRIB_STACK_DEPTH							= 0x0BB0,
	GZ_CLIENT_ATTRIB_STACK_DEPTH					= 0x0BB1,
	GZ_COLOR_CLEAR_VALUE							= 0x0C22,
	GZ_COLOR_WRITEMASK								= 0x0C23,
	GZ_CURRENT_INDEX								= 0x0B01,
	GZ_CURRENT_COLOR								= 0x0B00,
	GZ_CURRENT_NORMAL								= 0x0B02,
	GZ_CURRENT_RASTER_COLOR							= 0x0B04,
	GZ_CURRENT_RASTER_DISTANCE						= 0x0B09,
	GZ_CURRENT_RASTER_INDEX							= 0x0B05,
	GZ_CURRENT_RASTER_POSITION						= 0x0B07,
	GZ_CURRENT_RASTER_TEXTURE_COORDS 				= 0x0B06,
	GZ_CURRENT_RASTER_POSITION_VALID 				= 0x0B08,
	GZ_CURRENT_TEXTURE_COORDS						= 0x0B03,
	GZ_INDEX_CLEAR_VALUE							= 0x0C20,
	GZ_INDEX_MODE									= 0x0C30,
	GZ_INDEX_WRITEMASK								= 0x0C21,
	GZ_MODELVIEW_MATRIX								= 0x0BA6,
	GZ_MODELVIEW_STACK_DEPTH						= 0x0BA3,
	GZ_NAME_STACK_DEPTH								= 0x0D70,
	GZ_PROJECTION_MATRIX							= 0x0BA7,
	GZ_PROJECTION_STACK_DEPTH						= 0x0BA4,
	GZ_RENDER_MODE									= 0x0C40,
	GZ_RGBA_MODE									= 0x0C31,
	GZ_TEXTURE_MATRIX								= 0x0BA8,
	GZ_TEXTURE_STACK_DEPTH							= 0x0BA5,
	GZ_VIEWPORT										= 0x0BA2,


	/* Evaluators */
	GZ_AUTO_NORMAL									= 0x0D80,
	GZ_MAP1_COLOR_4									= 0x0D90,
	GZ_MAP1_GRID_DOMAIN								= 0x0DD0,
	GZ_MAP1_GRID_SEGMENTS							= 0x0DD1,
	GZ_MAP1_INDEX									= 0x0D91,
	GZ_MAP1_NORMAL									= 0x0D92,
	GZ_MAP1_TEXTURE_COORD_1							= 0x0D93,
	GZ_MAP1_TEXTURE_COORD_2							= 0x0D94,
	GZ_MAP1_TEXTURE_COORD_3							= 0x0D95,
	GZ_MAP1_TEXTURE_COORD_4							= 0x0D96,
	GZ_MAP1_VERTEX_3								= 0x0D97,
	GZ_MAP1_VERTEX_4								= 0x0D98,
	GZ_MAP2_COLOR_4									= 0x0DB0,
	GZ_MAP2_GRID_DOMAIN								= 0x0DD2,
	GZ_MAP2_GRID_SEGMENTS							= 0x0DD3,
	GZ_MAP2_INDEX									= 0x0DB1,
	GZ_MAP2_NORMAL									= 0x0DB2,
	GZ_MAP2_TEXTURE_COORD_1							= 0x0DB3,
	GZ_MAP2_TEXTURE_COORD_2							= 0x0DB4,
	GZ_MAP2_TEXTURE_COORD_3							= 0x0DB5,
	GZ_MAP2_TEXTURE_COORD_4							= 0x0DB6,
	GZ_MAP2_VERTEX_3								= 0x0DB7,
	GZ_MAP2_VERTEX_4								= 0x0DB8,
	GZ_COEFF										= 0x0A00,
	GZ_DOMAIN										= 0x0A02,
	GZ_ORDER										= 0x0A01,

	/* Hints */
	GZ_FOG_HINT										= 0x0C54,
	GZ_LINE_SMOOTH_HINT								= 0x0C52,
	GZ_PERSPECTIVE_CORRECTION_HINT					= 0x0C50,
	GZ_POINT_SMOOTH_HINT							= 0x0C51,
	GZ_POLYGON_SMOOTH_HINT							= 0x0C53,
	GZ_DONT_CARE									= 0x1100,
	GZ_FASTEST										= 0x1101,
	GZ_NICEST										= 0x1102,

	/* Scissor box */
	GZ_SCISSOR_TEST									= 0x0C11,
	GZ_SCISSOR_BOX									= 0x0C10,

	/* Pixel Mode / Transfer */
	GZ_MAP_COLOR									= 0x0D10,
	GZ_MAP_STENCIL									= 0x0D11,
	GZ_INDEX_SHIFT									= 0x0D12,
	GZ_INDEX_OFFSET									= 0x0D13,
	GZ_RED_SCALE									= 0x0D14,
	GZ_RED_BIAS										= 0x0D15,
	GZ_GREEN_SCALE									= 0x0D18,
	GZ_GREEN_BIAS									= 0x0D19,
	GZ_BLUE_SCALE									= 0x0D1A,
	GZ_BLUE_BIAS									= 0x0D1B,
	GZ_ALPHA_SCALE									= 0x0D1C,
	GZ_ALPHA_BIAS									= 0x0D1D,
	GZ_DEPTH_SCALE									= 0x0D1E,
	GZ_DEPTH_BIAS									= 0x0D1F,
	GZ_PIXEL_MAP_S_TO_S_SIZE						= 0x0CB1,
	GZ_PIXEL_MAP_I_TO_I_SIZE						= 0x0CB0,
	GZ_PIXEL_MAP_I_TO_R_SIZE						= 0x0CB2,
	GZ_PIXEL_MAP_I_TO_G_SIZE						= 0x0CB3,
	GZ_PIXEL_MAP_I_TO_B_SIZE						= 0x0CB4,
	GZ_PIXEL_MAP_I_TO_A_SIZE						= 0x0CB5,
	GZ_PIXEL_MAP_R_TO_R_SIZE						= 0x0CB6,
	GZ_PIXEL_MAP_G_TO_G_SIZE						= 0x0CB7,
	GZ_PIXEL_MAP_B_TO_B_SIZE						= 0x0CB8,
	GZ_PIXEL_MAP_A_TO_A_SIZE						= 0x0CB9,
	GZ_PIXEL_MAP_S_TO_S								= 0x0C71,
	GZ_PIXEL_MAP_I_TO_I								= 0x0C70,
	GZ_PIXEL_MAP_I_TO_R								= 0x0C72,
	GZ_PIXEL_MAP_I_TO_G								= 0x0C73,
	GZ_PIXEL_MAP_I_TO_B								= 0x0C74,
	GZ_PIXEL_MAP_I_TO_A								= 0x0C75,
	GZ_PIXEL_MAP_R_TO_R								= 0x0C76,
	GZ_PIXEL_MAP_G_TO_G								= 0x0C77,
	GZ_PIXEL_MAP_B_TO_B								= 0x0C78,
	GZ_PIXEL_MAP_A_TO_A								= 0x0C79,
	GZ_PACK_ALIGNMENT								= 0x0D05,
	GZ_PACK_LSB_FIRST								= 0x0D01,
	GZ_PACK_ROW_LENGTH								= 0x0D02,
	GZ_PACK_SKIP_PIXELS								= 0x0D04,
	GZ_PACK_SKIP_ROWS								= 0x0D03,
	GZ_PACK_SWAP_BYTES								= 0x0D00,
	GZ_UNPACK_ALIGNMENT								= 0x0CF5,
	GZ_UNPACK_LSB_FIRST								= 0x0CF1,
	GZ_UNPACK_ROW_LENGTH							= 0x0CF2,
	GZ_UNPACK_SKIP_PIXELS							= 0x0CF4,
	GZ_UNPACK_SKIP_ROWS								= 0x0CF3,
	GZ_UNPACK_SWAP_BYTES							= 0x0CF0,
	GZ_ZOOM_X										= 0x0D16,
	GZ_ZOOM_Y										= 0x0D17,

	/* Texture mapping */
	GZ_TEXTURE_ENV									= 0x2300,
	GZ_TEXTURE_ENV_MODE								= 0x2200,
	GZ_TEXTURE_1D									= 0x0DE0,
	GZ_TEXTURE_2D									= 0x0DE1,
	GZ_TEXTURE_WRAP_S								= 0x2802,
	GZ_TEXTURE_WRAP_T								= 0x2803,
	GZ_TEXTURE_MAG_FILTER							= 0x2800,
	GZ_TEXTURE_MIN_FILTER							= 0x2801,
	GZ_TEXTURE_ENV_COLOR							= 0x2201,
	GZ_TEXTURE_GEN_S								= 0x0C60,
	GZ_TEXTURE_GEN_T								= 0x0C61,
	GZ_TEXTURE_GEN_MODE								= 0x2500,
	GZ_TEXTURE_BORDER_COLOR							= 0x1004,
	GZ_TEXTURE_WIDTH								= 0x1000,
	GZ_TEXTURE_HEIGHT								= 0x1001,
	GZ_TEXTURE_BORDER								= 0x1005,
	GZ_TEXTURE_COMPONENTS							= 0x1003,
	GZ_TEXTURE_RED_SIZE								= 0x805C,
	GZ_TEXTURE_GREEN_SIZE							= 0x805D,
	GZ_TEXTURE_BLUE_SIZE							= 0x805E,
	GZ_TEXTURE_ALPHA_SIZE							= 0x805F,
	GZ_TEXTURE_LUMINANCE_SIZE						= 0x8060,
	GZ_TEXTURE_INTENSITY_SIZE						= 0x8061,
	GZ_NEAREST_MIPMAP_NEAREST						= 0x2700,
	GZ_NEAREST_MIPMAP_LINEAR						= 0x2702,
	GZ_LINEAR_MIPMAP_NEAREST						= 0x2701,
	GZ_LINEAR_MIPMAP_LINEAR							= 0x2703,
	GZ_OBJECT_LINEAR								= 0x2401,
	GZ_OBJECT_PLANE									= 0x2501,
	GZ_EYE_LINEAR									= 0x2400,
	GZ_EYE_PLANE									= 0x2502,
	GZ_SPHERE_MAP									= 0x2402,
	GZ_DECAL										= 0x2101,
	GZ_MODULATE										= 0x2100,
	GZ_NEAREST										= 0x2600,
	GZ_REPEAT										= 0x2901,
	GZ_CLAMP										= 0x2900,
	GZ_S											= 0x2000,
	GZ_T											= 0x2001,
	GZ_R											= 0x2002,
	GZ_Q											= 0x2003,
	GZ_TEXTURE_GEN_R								= 0x0C62,
	GZ_TEXTURE_GEN_Q								= 0x0C63,

	/* GL 1.1 texturing */
	GZ_PROXY_TEXTURE_1D								= 0x8063,
	GZ_PROXY_TEXTURE_2D								= 0x8064,
	GZ_TEXTURE_PRIORITY								= 0x8066,
	GZ_TEXTURE_RESIDENT								= 0x8067,
	GZ_TEXTURE_BINDING_1D							= 0x8068,
	GZ_TEXTURE_BINDING_2D							= 0x8069,
	GZ_TEXTURE_INTERNAL_FORMAT						= 0x1003,

	/* GL 1.2 texturing */
	GZ_PACK_SKIP_IMAGES								= 0x806B,
	GZ_PACK_IMAGE_HEIGHT							= 0x806C,
	GZ_UNPACK_SKIP_IMAGES							= 0x806D,
	GZ_UNPACK_IMAGE_HEIGHT							= 0x806E,
	GZ_TEXTURE_3D									= 0x806F,
	GZ_PROXY_TEXTURE_3D								= 0x8070,
	GZ_TEXTURE_DEPTH								= 0x8071,
	GZ_TEXTURE_WRAP_R								= 0x8072,
	GZ_MAX_3D_TEXTURE_SIZE							= 0x8073,
	GZ_TEXTURE_BINDING_3D							= 0x806A,

	/* Internal texture formats (GL 1.1) */
	GZ_ALPHA4										= 0x803B,
	GZ_ALPHA8										= 0x803C,
	GZ_ALPHA12										= 0x803D,
	GZ_ALPHA16										= 0x803E,
	GZ_LUMINANCE4									= 0x803F,
	GZ_LUMINANCE8									= 0x8040,
	GZ_LUMINANCE12									= 0x8041,
	GZ_LUMINANCE16									= 0x8042,
	GZ_LUMINANCE4_ALPHA4							= 0x8043,
	GZ_LUMINANCE6_ALPHA2							= 0x8044,
	GZ_LUMINANCE8_ALPHA8							= 0x8045,
	GZ_LUMINANCE12_ALPHA4							= 0x8046,
	GZ_LUMINANCE12_ALPHA12							= 0x8047,
	GZ_LUMINANCE16_ALPHA16							= 0x8048,
	GZ_INTENSITY									= 0x8049,
	GZ_INTENSITY4									= 0x804A,
	GZ_INTENSITY8									= 0x804B,
	GZ_INTENSITY12									= 0x804C,
	GZ_INTENSITY16									= 0x804D,
	GZ_R3_G3_B2										= 0x2A10,
	GZ_RGB4											= 0x804F,
	GZ_RGB5											= 0x8050,
	GZ_RGB8											= 0x8051,
	GZ_RGB10										= 0x8052,
	GZ_RGB12										= 0x8053,
	GZ_RGB16										= 0x8054,
	GZ_RGBA2										= 0x8055,
	GZ_RGBA4										= 0x8056,
	GZ_RGB5_A1										= 0x8057,
	GZ_RGBA8										= 0x8058,
	GZ_RGB10_A2										= 0x8059,
	GZ_RGBA12										= 0x805A,
	GZ_RGBA16										= 0x805B,

	/* Utility */
	GZ_VENDOR										= 0x1F00,
	GZ_RENDERER										= 0x1F01,
	GZ_VERSION										= 0x1F02,
	GZ_EXTENSIONS									= 0x1F03,

	/* Errors */
	GZ_INVALID_VALUE								= 0x0501,
	GZ_INVALID_ENUM									= 0x0500,
	GZ_INVALID_OPERATION							= 0x0502,
	GZ_STACK_OVERFLOW								= 0x0503,
	GZ_STACK_UNDERFLOW								= 0x0504,
	GZ_OUT_OF_MEMORY								= 0x0505,

	/*
	 * Extensions
	 */

	/* GZ_EXT_blend_minmax and GZ_EXT_blend_color */
	GZ_CONSTANT_COLOR_EXT							= 0x8001,
	GZ_ONE_MINUS_CONSTANT_COLOR_EXT					= 0x8002,
	GZ_CONSTANT_ALPHA_EXT							= 0x8003,
	GZ_ONE_MINUS_CONSTANT_ALPHA_EXT					= 0x8004,
	GZ_BLEND_EQUATION_EXT							= 0x8009,
	GZ_MIN_EXT										= 0x8007,
	GZ_MAX_EXT										= 0x8008,
	GZ_FUNC_ADD_EXT									= 0x8006,
	GZ_FUNC_SUBTRACT_EXT							= 0x800A,
	GZ_FUNC_REVERSE_SUBTRACT_EXT					= 0x800B,
	GZ_BLEND_COLOR_EXT								= 0x8005,

	/* GZ_EXT_polygon_offset */
	GZ_POLYGON_OFFSET_EXT							= 0x8037,
	GZ_POLYGON_OFFSET_FACTOR_EXT					= 0x8038,
	GZ_POLYGON_OFFSET_BIAS_EXT						= 0x8039,

	/* GZ_EXT_vertex_array */
	GZ_VERTEX_ARRAY_EXT								= 0x8074,
	GZ_NORMAL_ARRAY_EXT								= 0x8075,
	GZ_COLOR_ARRAY_EXT								= 0x8076,
	GZ_INDEX_ARRAY_EXT								= 0x8077,
	GZ_TEXTURE_COORD_ARRAY_EXT						= 0x8078,
	GZ_EDGE_FLAG_ARRAY_EXT							= 0x8079,
	GZ_VERTEX_ARRAY_SIZE_EXT						= 0x807A,
	GZ_VERTEX_ARRAY_TYPE_EXT						= 0x807B,
	GZ_VERTEX_ARRAY_STRIDE_EXT						= 0x807C,
	GZ_VERTEX_ARRAY_COUNT_EXT						= 0x807D,
	GZ_NORMAL_ARRAY_TYPE_EXT						= 0x807E,
	GZ_NORMAL_ARRAY_STRIDE_EXT						= 0x807F,
	GZ_NORMAL_ARRAY_COUNT_EXT						= 0x8080,
	GZ_COLOR_ARRAY_SIZE_EXT							= 0x8081,
	GZ_COLOR_ARRAY_TYPE_EXT							= 0x8082,
	GZ_COLOR_ARRAY_STRIDE_EXT						= 0x8083,
	GZ_COLOR_ARRAY_COUNT_EXT						= 0x8084,
	GZ_INDEX_ARRAY_TYPE_EXT							= 0x8085,
	GZ_INDEX_ARRAY_STRIDE_EXT						= 0x8086,
	GZ_INDEX_ARRAY_COUNT_EXT						= 0x8087,
	GZ_TEXTURE_COORD_ARRAY_SIZE_EXT					= 0x8088,
	GZ_TEXTURE_COORD_ARRAY_TYPE_EXT					= 0x8089,
	GZ_TEXTURE_COORD_ARRAY_STRIDE_EXT				= 0x808A,
	GZ_TEXTURE_COORD_ARRAY_COUNT_EXT				= 0x808B,
	GZ_EDGE_FLAG_ARRAY_STRIDE_EXT					= 0x808C,
	GZ_EDGE_FLAG_ARRAY_COUNT_EXT					= 0x808D,
	GZ_VERTEX_ARRAY_POINTER_EXT						= 0x808E,
	GZ_NORMAL_ARRAY_POINTER_EXT						= 0x808F,
	GZ_COLOR_ARRAY_POINTER_EXT						= 0x8090,
	GZ_INDEX_ARRAY_POINTER_EXT						= 0x8091,
	GZ_TEXTURE_COORD_ARRAY_POINTER_EXT				= 0x8092,
	GZ_EDGE_FLAG_ARRAY_POINTER_EXT					= 0x8093,

	/* GZ_EXT_texture_object */
	GZ_TEXTURE_PRIORITY_EXT							= 0x8066,
	GZ_TEXTURE_RESIDENT_EXT							= 0x8067,
	GZ_TEXTURE_1D_BINDING_EXT						= 0x8068,
	GZ_TEXTURE_2D_BINDING_EXT						= 0x8069,

	/* GZ_EXT_texture3D */
	GZ_PACK_SKIP_IMAGES_EXT							= 0x806B,
	GZ_PACK_IMAGE_HEIGHT_EXT						= 0x806C,
	GZ_UNPACK_SKIP_IMAGES_EXT						= 0x806D,
	GZ_UNPACK_IMAGE_HEIGHT_EXT						= 0x806E,
	GZ_TEXTURE_3D_EXT								= 0x806F,
	GZ_PROXY_TEXTURE_3D_EXT							= 0x8070,
	GZ_TEXTURE_DEPTH_EXT							= 0x8071,
	GZ_TEXTURE_WRAP_R_EXT							= 0x8072,
	GZ_MAX_3D_TEXTURE_SIZE_EXT						= 0x8073,
	GZ_TEXTURE_3D_BINDING_EXT						= 0x806A,

	/* GZ_EXT_paletted_texture */
	GZ_TABLE_TOO_LARGE								= 0x8031,
	GZ_COLOR_TABLE_FORMAT							= 0x80D8,
	GZ_COLOR_TABLE_WIDTH							= 0x80D9,
	GZ_COLOR_TABLE_RED_SIZE							= 0x80DA,
	GZ_COLOR_TABLE_GREEN_SIZE						= 0x80DB,
	GZ_COLOR_TABLE_BLUE_SIZE						= 0x80DC,
	GZ_COLOR_TABLE_ALPHA_SIZE		 				= 0x80DD,
	GZ_COLOR_TABLE_LUMINANCE_SIZE					= 0x80DE,
	GZ_COLOR_TABLE_INTENSITY_SIZE					= 0x80DF,
	GZ_TEXTURE_INDEX_SIZE							= 0x80ED,
	GZ_COLOR_INDEX1									= 0x80E2,
	GZ_COLOR_INDEX2									= 0x80E3,
	GZ_COLOR_INDEX4									= 0x80E4,
	GZ_COLOR_INDEX8									= 0x80E5,
	GZ_COLOR_INDEX12								= 0x80E6,
	GZ_COLOR_INDEX16								= 0x80E7,

	/* GZ_EXT_shared_texture_palette */
	GZ_SHARED_TEXTURE_PALETTE_EXT					= 0x81FB,

	/* GZ_EXT_point_parameters */
	GZ_POINT_SIZE_MIN_EXT							= 0x8126,
	GZ_POINT_SIZE_MAX_EXT							= 0x8127,
	GZ_POINT_FADE_THRESHOLD_SIZE_EXT				= 0x8128,
	GZ_DISTANCE_ATTENUATION_EXT						= 0x8129,

	/* GZ_EXT_rescale_normal */
	GZ_RESCALE_NORMAL_EXT							= 0x803A,

	/* GZ_EXT_abgr */
	GZ_ABGR_EXT										= 0x8000,

	/* GZ_SGIS_multitexture */
	GZ_SELECTED_TEXTURE_SGIS						= 0x835C,
	GZ_SELECTED_TEXTURE_COORD_SET_SGIS				= 0x835D,
	GZ_MAX_TEXTURES_SGIS							= 0x835E,
	GZ_TEXTURE0_SGIS								= 0x835F,
	GZ_TEXTURE1_SGIS								= 0x8360,
	GZ_TEXTURE2_SGIS								= 0x8361,
	GZ_TEXTURE3_SGIS								= 0x8362,
	GZ_TEXTURE_COORD_SET_SOURCE_SGIS				= 0x8363,

	/* GZ_EXT_multitexture */
	GZ_SELECTED_TEXTURE_EXT							= 0x83C0,
	GZ_SELECTED_TEXTURE_COORD_SET_EXT				= 0x83C1,
	GZ_SELECTED_TEXTURE_TRANSFORM_EXT				= 0x83C2,
	GZ_MAX_TEXTURES_EXT								= 0x83C3,
	GZ_MAX_TEXTURE_COORD_SETS_EXT					= 0x83C4,
	GZ_TEXTURE_ENV_COORD_SET_EXT					= 0x83C5,
	GZ_TEXTURE0_EXT									= 0x83C6,
	GZ_TEXTURE1_EXT									= 0x83C7,
	GZ_TEXTURE2_EXT									= 0x83C8,
	GZ_TEXTURE3_EXT									= 0x83C9,

	/* GZ_SGIS_texture_edge_clamp */
	GZ_CLAMP_TO_EDGE_SGIS							= 0x812F,

	/* Gizmo imp of OpenGL 1.2 */
	GZ_RESCALE_NORMAL								= 0x803A,
	GZ_CLAMP_TO_EDGE								= 0x812F,
	GZ_MAX_ELEMENTS_VERTICES						= 0x80E8,
	GZ_MAX_ELEMENTS_INDICES							= 0x80E9,
	GZ_BGR											= 0x80E0,
	GZ_BGRA											= 0x80E1,
	GZ_UNSIGNED_BYTE_3_3_2							= 0x8032,
	GZ_UNSIGNED_BYTE_2_3_3_REV						= 0x8362,
	GZ_UNSIGNED_SHORT_5_6_5							= 0x8363,
	GZ_UNSIGNED_SHORT_5_6_5_REV						= 0x8364,
	GZ_UNSIGNED_SHORT_4_4_4_4						= 0x8033,
	GZ_UNSIGNED_SHORT_4_4_4_4_REV					= 0x8365,
	GZ_UNSIGNED_SHORT_5_5_5_1						= 0x8034,
	GZ_UNSIGNED_SHORT_1_5_5_5_REV					= 0x8366,
	GZ_UNSIGNED_INT_8_8_8_8							= 0x8035,
	GZ_UNSIGNED_INT_8_8_8_8_REV						= 0x8367,
	GZ_UNSIGNED_INT_10_10_10_2						= 0x8036,
	GZ_UNSIGNED_INT_2_10_10_10_REV					= 0x8368,
	GZ_LIGHT_MODEL_COLOR_CONTROL					= 0x81F8,
	GZ_SINGLE_COLOR									= 0x81F9,
	GZ_SEPARATE_SPECULAR_COLOR						= 0x81FA,
	GZ_TEXTURE_MIN_LOD								= 0x813A,
	GZ_TEXTURE_MAX_LOD								= 0x813B,
	GZ_TEXTURE_BASE_LEVEL							= 0x813C,
	GZ_TEXTURE_MAX_LEVEL							= 0x813D,
	GL_SMOOTH_POINT_SIZE_RANGE						= 0x0B12,
	GZ_SMOOTH_POINT_SIZE_GRANULARITY				= 0x0B13,
	GZ_SMOOTH_LINE_WIDTH_RANGE						= 0x0B22,
	GZ_SMOOTH_LINE_WIDTH_GRANULARITY				= 0x0B23,
	GZ_ALIASED_LINE_WIDTH_RANGE						= 0x846E,
	GZ_ALIASED_POINT_SIZE_RANGE						= 0x846D,

	/* Gizmo imp of OpenGL 1.3 */
	GZ_NORMAL_MAP									= 0x8511,
	GZ_REFLECTION_MAP								= 0x8512,
	GZ_TEXTURE_CUBE_MAP								= 0x8513,
	GZ_TEXTURE_BINDING_CUBE_MAP						= 0x8514,
	GZ_TEXTURE_CUBE_MAP_POSITIVE_X					= 0x8515,
	GZ_TEXTURE_CUBE_MAP_NEGATIVE_X					= 0x8516,
	GZ_TEXTURE_CUBE_MAP_POSITIVE_Y					= 0x8517,
	GZ_TEXTURE_CUBE_MAP_NEGATIVE_Y					= 0x8518,
	GZ_TEXTURE_CUBE_MAP_POSITIVE_Z					= 0x8519,
	GZ_TEXTURE_CUBE_MAP_NEGATIVE_Z					= 0x851A,
	GZ_PROXY_TEXTURE_CUBE_MAP						= 0x851B,
	GZ_MAX_CUBE_MAP_TEXTURE_SIZE					= 0x851C,
	/* texture_compression */
	GZ_COMPRESSED_ALPHA								= 0x84E9,
	GZ_COMPRESSED_LUMINANCE							= 0x84EA,
	GZ_COMPRESSED_LUMINANCE_ALPHA					= 0x84EB,
	GZ_COMPRESSED_INTENSITY							= 0x84EC,
	GZ_COMPRESSED_RGB								= 0x84ED,
	GZ_COMPRESSED_RGBA								= 0x84EE,
	GZ_TEXTURE_COMPRESSION_HINT						= 0x84EF,
	GZ_TEXTURE_COMPRESSED_IMAGE_SIZE				= 0x86A0,
	GZ_TEXTURE_COMPRESSED							= 0x86A1,
	GZ_NUM_COMPRESSED_TEXTURE_FORMATS				= 0x86A2,
	GZ_COMPRESSED_TEXTURE_FORMATS					= 0x86A3,
	/* multisample */
	GZ_MULTISAMPLE									= 0x809D,
	GZ_SAMPLE_ALPHA_TO_COVERAGE						= 0x809E,
	GZ_SAMPLE_ALPHA_TO_ONE							= 0x809F,
	GZ_SAMPLE_COVERAGE								= 0x80A0,
	GZ_SAMPLE_BUFFERS								= 0x80A8,
	GZ_SAMPLES										= 0x80A9,
	GZ_SAMPLE_COVERAGE_VALUE						= 0x80AA,
	GZ_SAMPLE_COVERAGE_INVERT						= 0x80AB,

	/* transpose_matrix */
	GZ_TRANSPOSE_MODELVIEW_MATRIX					= 0x84E3,
	GZ_TRANSPOSE_PROJECTION_MATRIX					= 0x84E4,
	GZ_TRANSPOSE_TEXTURE_MATRIX						= 0x84E5,
	GZ_TRANSPOSE_COLOR_MATRIX						= 0x84E6,
	/* texture_env_combine */
	GZ_COMBINE										= 0x8570,
	GZ_COMBINE_RGB									= 0x8571,
	GZ_COMBINE_ALPHA								= 0x8572,
	GZ_SOURCE0_RGB									= 0x8580,
	GZ_SOURCE1_RGB									= 0x8581,
	GZ_SOURCE2_RGB									= 0x8582,
	GZ_SOURCE0_ALPHA								= 0x8588,
	GZ_SOURCE1_ALPHA								= 0x8589,
	GZ_SOURCE2_ALPHA								= 0x858A,
	GZ_OPERAND0_RGB									= 0x8590,
	GZ_OPERAND1_RGB									= 0x8591,
	GZ_OPERAND2_RGB									= 0x8592,
	GZ_OPERAND0_ALPHA								= 0x8598,
	GZ_OPERAND1_ALPHA								= 0x8599,
	GZ_OPERAND2_ALPHA								= 0x859A,
	GZ_RGB_SCALE									= 0x8573,
	GZ_ADD_SIGNED									= 0x8574,
	GZ_INTERPOLATE									= 0x8575,
	GZ_SUBTRACT										= 0x84E7,
	GZ_CONSTANT										= 0x8576,
	GZ_PRIMARY_COLOR								= 0x8577,
	GZ_PREVIOUS										= 0x8578,
	/* texture_env_dot3 */
	GZ_DOT3_RGB										= 0x86AE,
	GZ_DOT3_RGBA									= 0x86AF,
	/* texture_border_clamp */
	GZ_CLAMP_TO_BORDER								= 0x812D,

	/* Gizmo imp of OpenGL 1.4 */
	GZ_BLEND_DST_RGB								= 0x80C8, 
	GZ_BLEND_SRC_RGB								= 0x80C9,
	GZ_BLEND_DST_ALPHA								= 0x80CA,
	GZ_BLEND_SRC_ALPHA								= 0x80CB,
	GZ_POINT_FADE_THRESHOLD_SIZE					= 0x8128, 
	GZ_DEPTH_COMPONENT16							= 0x81A5,
	GZ_DEPTH_COMPONENT24							= 0x81A6,
	GZ_DEPTH_COMPONENT32							= 0x81A7,
	GZ_MIRRORED_REPEAT								= 0x8370,
	GZ_MAX_TEXTURE_LOD_BIAS							= 0x84FD,
	GZ_TEXTURE_LOD_BIAS								= 0x8501,
	GZ_INCR_WRAP									= 0x8507,
	GZ_DECR_WRAP									= 0x8508,
	GZ_TEXTURE_DEPTH_SIZE							= 0x884A,
	GZ_TEXTURE_COMPARE_MODE							= 0x884C,
	GZ_TEXTURE_COMPARE_FUNC							= 0x884D,
	GZ_POINT_SIZE_MIN								= 0x8126,
	GZ_POINT_SIZE_MAX								= 0x8127,
	GZ_POINT_DISTANCE_ATTENUATION					= 0x8129,
	GZ_GENERATE_MIPMAP								= 0x8191,
	GZ_GENERATE_MIPMAP_HINT							= 0x8192,
	GZ_FOG_COORDINATE_SOURCE						= 0x8450,
	GZ_FOG_COORDINATE								= 0x8451,
	GZ_FRAGMENT_DEPTH								= 0x8452,
	GZ_CURRENT_FOG_COORDINATE						= 0x8453,
	GZ_FOG_COORDINATE_ARRAY_TYPE					= 0x8454,
	GZ_FOG_COORDINATE_ARRAY_STRIDE					= 0x8455,
	GZ_FOG_COORDINATE_ARRAY_POINTER					= 0x8456,
	GZ_FOG_COORDINATE_ARRAY							= 0x8457,
	GZ_CURRENT_SECONDARY_COLOR						= 0x8459,
	GZ_SECONDARY_COLOR_ARRAY_SIZE					= 0x845A,
	GZ_SECONDARY_COLOR_ARRAY_TYPE					= 0x845B,
	GZ_SECONDARY_COLOR_ARRAY_STRIDE					= 0x845C,
	GZ_SECONDARY_COLOR_ARRAY_POINTER				= 0x845D,
	GZ_SECONDARY_COLOR_ARRAY						= 0x845E,
	GZ_TEXTURE_FILTER_CONTROL						= 0x8500,
	GZ_DEPTH_TEXTURE_MODE							= 0x884B,
	GZ_COMPARE_R_TO_TEXTURE							= 0x884E, 

	/* Gizmo imp of OpenGL 1.5 */
	GZ_QUERY_COUNTER_BITS							= 0x8864,
	GZ_CURRENT_QUERY								= 0x8865,
	GZ_QUERY_RESULT									= 0x8866,
	GZ_QUERY_RESULT_AVAILABLE						= 0x8867,
	GZ_SAMPLES_PASSED								= 0x8914,
	GZ_SRC1_ALPHA									= 0x8589,
	GZ_SECONDARY_COLOR_ARRAY_BUFFER_BINDING			= 0x889C,
	GZ_FOG_COORD_SRC								= 0x8450,
	GZ_FOG_COORD									= 0x8451,
	GZ_CURRENT_FOG_COORD							= 0x8453,
	GZ_FOG_COORD_ARRAY_TYPE							= 0x8454,
	GZ_FOG_COORD_ARRAY_STRIDE						= 0x8455,
	GZ_FOG_COORD_ARRAY_POINTER						= 0x8456,
	GZ_FOG_COORD_ARRAY								= 0x8457,
	GZ_FOG_COORD_ARRAY_BUFFER_BINDING				= 0x889D,
	GZ_SRC0_RGB										= 0x8580,
	GZ_SRC1_RGB										= 0x8581,
	GZ_SRC2_RGB										= 0x8582,
	GZ_SRC0_ALPHA									= 0x8588,
	GZ_SRC2_ALPHA									= 0x858A,

	/* Gizmo imp of OpenGL 2.0  */
	GZ_BLEND_EQUATION_RGB							= 0x8009,
	GZ_MAX_DRAW_BUFFERS								= 0x8824,
	GZ_DRAW_BUFFER0									= 0x8825,
	GZ_DRAW_BUFFER1									= 0x8826,
	GZ_DRAW_BUFFER2									= 0x8827,
	GZ_DRAW_BUFFER3									= 0x8828,
	GZ_DRAW_BUFFER4									= 0x8829,
	GZ_DRAW_BUFFER5									= 0x882A,
	GZ_DRAW_BUFFER6									= 0x882B,
	GZ_DRAW_BUFFER7									= 0x882C,
	GZ_DRAW_BUFFER8									= 0x882D,
	GZ_DRAW_BUFFER9									= 0x882E,
	GZ_DRAW_BUFFER10								= 0x882F,
	GZ_DRAW_BUFFER11								= 0x8830,
	GZ_DRAW_BUFFER12								= 0x8831,
	GZ_DRAW_BUFFER13								= 0x8832,
	GZ_DRAW_BUFFER14								= 0x8833,
	GZ_DRAW_BUFFER15								= 0x8834,
	GZ_BLEND_EQUATION_ALPHA							= 0x883D,
	GZ_MAX_TEXTURE_IMAGE_UNITS						= 0x8872,
	GZ_SHADER_TYPE									= 0x8B4F,
	GZ_BOOL											= 0x8B56,
	GZ_SAMPLER_1D									= 0x8B5D,
	GZ_SAMPLER_2D									= 0x8B5E,
	GZ_SAMPLER_3D									= 0x8B5F,
	GZ_SAMPLER_CUBE									= 0x8B60,
	GZ_SAMPLER_1D_SHADOW							= 0x8B61,
	GZ_SAMPLER_2D_SHADOW							= 0x8B62,
	GZ_DELETE_STATUS								= 0x8B80,
	GZ_COMPILE_STATUS								= 0x8B81,
	GZ_LINK_STATUS									= 0x8B82,
	GZ_VALIDATE_STATUS								= 0x8B83,
	GZ_INFO_LOG_LENGTH								= 0x8B84,
	GZ_ATTACHED_SHADERS								= 0x8B85,
	GZ_ACTIVE_UNIFORMS								= 0x8B86,
	GZ_ACTIVE_UNIFORM_MAX_LENGTH					= 0x8B87,
	GZ_SHADER_SOURCE_LENGTH							= 0x8B88,
	GZ_ACTIVE_ATTRIBUTES							= 0x8B89,
	GZ_ACTIVE_ATTRIBUTE_MAX_LENGTH					= 0x8B8A,
	GZ_FRAGMENT_SHADER_DERIVATIVE_HINT				= 0x8B8B,
	GZ_CURRENT_PROGRAM								= 0x8B8D,
	GZ_POINT_SPRITE_COORD_ORIGIN					= 0x8CA0,
	GZ_LOWER_LEFT									= 0x8CA1,
	GZ_UPPER_LEFT									= 0x8CA2,
	GZ_STENCIL_BACK_REF								= 0x8CA3,
	GZ_STENCIL_BACK_VALUE_MASK						= 0x8CA4,
	GZ_STENCIL_BACK_WRITEMASK						= 0x8CA5,
	GZ_POINT_SPRITE									= 0x8861,
	GZ_COORD_REPLACE								= 0x8862,

	/* Gizmo imp of OpenGL 2.1  */
	GZ_FLOAT_MAT2x3									= 0x8B65,
	GZ_FLOAT_MAT2x4									= 0x8B66,
	GZ_FLOAT_MAT3x2									= 0x8B67,
	GZ_FLOAT_MAT3x4									= 0x8B68,
	GZ_FLOAT_MAT4x2									= 0x8B69,
	GZ_FLOAT_MAT4x3									= 0x8B6A,
	GZ_SRGB											= 0x8C40,
	GZ_SRGB8										= 0x8C41,
	GZ_SRGB_ALPHA									= 0x8C42,
	GZ_SRGB8_ALPHA8									= 0x8C43,
	GZ_COMPRESSED_SRGB								= 0x8C48,
	GZ_COMPRESSED_SRGB_ALPHA						= 0x8C49,
	GZ_CURRENT_RASTER_SECONDARY_COLOR				= 0x845F,
	GZ_SLUMINANCE_ALPHA								= 0x8C44,
	GZ_SLUMINANCE8_ALPHA8							= 0x8C45,
	GZ_SLUMINANCE									= 0x8C46,
	GZ_SLUMINANCE8									= 0x8C47,
	GZ_COMPRESSED_SLUMINANCE						= 0x8C4A,
	GZ_COMPRESSED_SLUMINANCE_ALPHA					= 0x8C4B,

	/* Gizmo imp of OpenGL 3.0  */
	GZ_COMPARE_REF_TO_TEXTURE						= 0x884E,
	GZ_CLIP_DISTANCE0								= 0x3000,
	GZ_CLIP_DISTANCE1								= 0x3001,
	GZ_CLIP_DISTANCE2								= 0x3002,
	GZ_CLIP_DISTANCE3								= 0x3003,
	GZ_CLIP_DISTANCE4								= 0x3004,
	GZ_CLIP_DISTANCE5								= 0x3005,
	GZ_CLIP_DISTANCE6								= 0x3006,
	GZ_CLIP_DISTANCE7								= 0x3007,
	GZ_MAX_CLIP_DISTANCES							= 0x0D32,
	GZ_MAJOR_VERSION								= 0x821B,
	GZ_MINOR_VERSION								= 0x821C,
	GZ_NUM_EXTENSIONS								= 0x821D,
	GZ_CONTEXT_FLAGS								= 0x821E,
	GZ_COMPRESSED_RED								= 0x8225,
	GZ_COMPRESSED_RG								= 0x8226,
	GZ_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT			= 0x00000001,
	GZ_VERTEX_ATTRIB_ARRAY_INTEGER					= 0x88FD,
	GZ_MAX_ARRAY_TEXTURE_LAYERS						= 0x88FF,
	GZ_MIN_PROGRAM_TEXEL_OFFSET						= 0x8904,
	GZ_MAX_PROGRAM_TEXEL_OFFSET						= 0x8905,
	GZ_CLAMP_READ_COLOR								= 0x891C,
	GZ_FIXED_ONLY									= 0x891D,
	GZ_TEXTURE_1D_ARRAY								= 0x8C18,
	GZ_PROXY_TEXTURE_1D_ARRAY						= 0x8C19,
	GZ_TEXTURE_2D_ARRAY								= 0x8C1A,
	GZ_PROXY_TEXTURE_2D_ARRAY						= 0x8C1B,
	GZ_TEXTURE_BINDING_1D_ARRAY						= 0x8C1C,
	GZ_TEXTURE_BINDING_2D_ARRAY						= 0x8C1D,
	GZ_R11F_G11F_B10F								= 0x8C3A,
	GZ_UNSIGNED_INT_10F_11F_11F_REV					= 0x8C3B,
	GZ_RGB9_E5										= 0x8C3D,
	GZ_UNSIGNED_INT_5_9_9_9_REV						= 0x8C3E,
	GZ_TEXTURE_SHARED_SIZE							= 0x8C3F,
	GZ_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH		= 0x8C76,
	GZ_TRANSFORM_FEEDBACK_BUFFER_MODE				= 0x8C7F,
	GZ_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS	= 0x8C80,
	GZ_TRANSFORM_FEEDBACK_VARYINGS					= 0x8C83,
	GZ_TRANSFORM_FEEDBACK_BUFFER_START				= 0x8C84,
	GZ_TRANSFORM_FEEDBACK_BUFFER_SIZE				= 0x8C85,
	GZ_PRIMITIVES_GENERATED							= 0x8C87,
	GZ_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN		= 0x8C88,
	GZ_RASTERIZER_DISCARD							= 0x8C89,
	GZ_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS= 0x8C8A,
	GZ_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS		= 0x8C8B,
	GZ_INTERLEAVED_ATTRIBS							= 0x8C8C,
	GZ_SEPARATE_ATTRIBS								= 0x8C8D,
	GZ_TRANSFORM_FEEDBACK_BUFFER					= 0x8C8E,
	GZ_TRANSFORM_FEEDBACK_BUFFER_BINDING			= 0x8C8F,
	GZ_RGBA32UI										= 0x8D70,
	GZ_RGB32UI										= 0x8D71,
	GZ_RGBA16UI										= 0x8D76,
	GZ_RGB16UI										= 0x8D77,
	GZ_RGBA8UI										= 0x8D7C,
	GZ_RGB8UI										= 0x8D7D,
	GZ_RGBA32I										= 0x8D82,
	GZ_RGB32I										= 0x8D83,
	GZ_RGBA16I										= 0x8D88,
	GZ_RGB16I										= 0x8D89,
	GZ_RGBA8I										= 0x8D8E,
	GZ_RGB8I										= 0x8D8F,
	GZ_RED_INTEGER									= 0x8D94,
	GZ_GREEN_INTEGER								= 0x8D95,
	GZ_BLUE_INTEGER									= 0x8D96,
	GZ_RGB_INTEGER									= 0x8D98,
	GZ_RGBA_INTEGER									= 0x8D99,
	GZ_BGR_INTEGER									= 0x8D9A,
	GZ_BGRA_INTEGER									= 0x8D9B,
	GZ_SAMPLER_1D_ARRAY								= 0x8DC0,
	GZ_SAMPLER_2D_ARRAY								= 0x8DC1,
	GZ_SAMPLER_1D_ARRAY_SHADOW						= 0x8DC3,
	GZ_SAMPLER_2D_ARRAY_SHADOW						= 0x8DC4,
	GZ_SAMPLER_CUBE_SHADOW							= 0x8DC5,
	GZ_UNSIGNED_INT_VEC2							= 0x8DC6,
	GZ_UNSIGNED_INT_VEC3							= 0x8DC7,
	GZ_UNSIGNED_INT_VEC4							= 0x8DC8,
	GZ_INT_SAMPLER_1D								= 0x8DC9,
	GZ_INT_SAMPLER_2D								= 0x8DCA,
	GZ_INT_SAMPLER_3D								= 0x8DCB,
	GZ_INT_SAMPLER_CUBE								= 0x8DCC,
	GZ_INT_SAMPLER_1D_ARRAY							= 0x8DCE,
	GZ_INT_SAMPLER_2D_ARRAY							= 0x8DCF,
	GZ_UNSIGNED_INT_SAMPLER_1D						= 0x8DD1,
	GZ_UNSIGNED_INT_SAMPLER_2D						= 0x8DD2,
	GZ_UNSIGNED_INT_SAMPLER_3D						= 0x8DD3,
	GZ_UNSIGNED_INT_SAMPLER_CUBE					= 0x8DD4,
	GZ_UNSIGNED_INT_SAMPLER_1D_ARRAY				= 0x8DD6,
	GZ_UNSIGNED_INT_SAMPLER_2D_ARRAY				= 0x8DD7,
	GZ_QUERY_WAIT									= 0x8E13,
	GZ_QUERY_NO_WAIT								= 0x8E14,
	GZ_QUERY_BY_REGION_WAIT							= 0x8E15,
	GZ_QUERY_BY_REGION_NO_WAIT						= 0x8E16,
	GZ_BUFFER_ACCESS_FLAGS							= 0x911F,
	GZ_BUFFER_MAP_LENGTH							= 0x9120,
	GZ_BUFFER_MAP_OFFSET							= 0x9121,
	GZ_DEPTH_COMPONENT32F							= 0x8CAC,
	GZ_DEPTH32F_STENCIL8							= 0x8CAD,
	GZ_FLOAT_32_UNSIGNED_INT_24_8_REV				= 0x8DAD,
	GZ_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING		= 0x8210,
	GZ_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE		= 0x8211,
	GZ_FRAMEBUFFER_ATTACHMENT_RED_SIZE				= 0x8212,
	GZ_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE			= 0x8213,
	GZ_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE				= 0x8214,
	GZ_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE			= 0x8215,
	GZ_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE			= 0x8216,
	GZ_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE			= 0x8217,
	GZ_FRAMEBUFFER_DEFAULT							= 0x8218,
	GZ_FRAMEBUFFER_UNDEFINED						= 0x8219,
	GZ_DEPTH_STENCIL_ATTACHMENT						= 0x821A,
	GZ_DEPTH_STENCIL								= 0x84F9,
	GZ_UNSIGNED_INT_24_8							= 0x84FA,
	GZ_DEPTH24_STENCIL8								= 0x88F0,
	GZ_TEXTURE_STENCIL_SIZE							= 0x88F1,

	GZ_COLOR_ATTACHMENT16							= 0x8CF0,
	GZ_COLOR_ATTACHMENT17							= 0x8CF1,
	GZ_COLOR_ATTACHMENT18							= 0x8CF2,
	GZ_COLOR_ATTACHMENT19							= 0x8CF3,
	GZ_COLOR_ATTACHMENT20							= 0x8CF4,
	GZ_COLOR_ATTACHMENT21							= 0x8CF5,
	GZ_COLOR_ATTACHMENT22							= 0x8CF6,
	GZ_COLOR_ATTACHMENT23							= 0x8CF7,
	GZ_COLOR_ATTACHMENT24							= 0x8CF8,
	GZ_COLOR_ATTACHMENT25							= 0x8CF9,
	GZ_COLOR_ATTACHMENT26							= 0x8CFA,
	GZ_COLOR_ATTACHMENT27							= 0x8CFB,
	GZ_COLOR_ATTACHMENT28							= 0x8CFC,
	GZ_COLOR_ATTACHMENT29							= 0x8CFD,
	GZ_COLOR_ATTACHMENT30							= 0x8CFE,
	GZ_COLOR_ATTACHMENT31							= 0x8CFF,

	GZ_INDEX										= 0x8222,
	GZ_FRAMEBUFFER_SRGB								= 0x8DB9,
	GZ_MAP_READ_BIT									= 0x0001,
	GZ_MAP_WRITE_BIT								= 0x0002,
	GZ_MAP_INVALIDATE_RANGE_BIT						= 0x0004,
	GZ_MAP_INVALIDATE_BUFFER_BIT					= 0x0008,
	GZ_MAP_FLUSH_EXPLICIT_BIT						= 0x0010,
	GZ_MAP_UNSYNCHRONIZED_BIT						= 0x0020,
	GZ_COMPRESSED_RED_RGTC1							= 0x8DBB,
	GZ_COMPRESSED_SIGNED_RED_RGTC1					= 0x8DBC,
	GZ_COMPRESSED_RG_RGTC2							= 0x8DBD,
	GZ_COMPRESSED_SIGNED_RG_RGTC2					= 0x8DBE,
	GZ_RG											= 0x8227,
	GZ_RG_INTEGER									= 0x8228,
	GZ_R8											= 0x8229,
	GZ_R16											= 0x822A,
	GZ_RG8											= 0x822B,
	GZ_RG16											= 0x822C,
	GZ_R16F											= 0x822D,
	GZ_R32F											= 0x822E,
	GZ_RG16F										= 0x822F,
	GZ_RG32F										= 0x8230,
	GZ_R8I											= 0x8231,
	GZ_R8UI											= 0x8232,
	GZ_R16I											= 0x8233,
	GZ_R16UI										= 0x8234,
	GZ_R32I											= 0x8235,
	GZ_R32UI										= 0x8236,
	GZ_RG8I											= 0x8237,
	GZ_RG8UI										= 0x8238,
	GZ_RG16I										= 0x8239,
	GZ_RG16UI										= 0x823A,
	GZ_RG32I										= 0x823B,
	GZ_RG32UI										= 0x823C,
	GZ_VERTEX_ARRAY_BINDING							= 0x85B5,
	GZ_CLAMP_VERTEX_COLOR							= 0x891A,
	GZ_CLAMP_FRAGMENT_COLOR							= 0x891B,
	GZ_ALPHA_INTEGER								= 0x8D97,

	/* Gizmo imp of OpenGL 3.1  */
	GZ_SAMPLER_2D_RECT								= 0x8B63,
	GZ_SAMPLER_2D_RECT_SHADOW						= 0x8B64,
	GZ_SAMPLER_BUFFER								= 0x8DC2,
	GZ_INT_SAMPLER_2D_RECT							= 0x8DCD,
	GZ_INT_SAMPLER_BUFFER							= 0x8DD0,
	GZ_UNSIGNED_INT_SAMPLER_2D_RECT					= 0x8DD5,
	GZ_UNSIGNED_INT_SAMPLER_BUFFER					= 0x8DD8,
	GZ_TEXTURE_BUFFER								= 0x8C2A,
	GZ_MAX_TEXTURE_BUFFER_SIZE						= 0x8C2B,
	GZ_TEXTURE_BINDING_BUFFER						= 0x8C2C,
	GZ_TEXTURE_BUFFER_DATA_STORE_BINDING			= 0x8C2D,
	GZ_TEXTURE_RECTANGLE							= 0x84F5,
	GZ_TEXTURE_BINDING_RECTANGLE					= 0x84F6,
	GZ_PROXY_TEXTURE_RECTANGLE						= 0x84F7,
	GZ_MAX_RECTANGLE_TEXTURE_SIZE					= 0x84F8,
	GZ_R8_SNORM										= 0x8F94,
	GZ_RG8_SNORM									= 0x8F95,
	GZ_RGB8_SNORM									= 0x8F96,
	GZ_RGBA8_SNORM									= 0x8F97,
	GZ_R16_SNORM									= 0x8F98,
	GZ_RG16_SNORM									= 0x8F99,
	GZ_RGB16_SNORM									= 0x8F9A,
	GZ_RGBA16_SNORM									= 0x8F9B,
	GZ_SIGNED_NORMALIZED							= 0x8F9C,
	GZ_PRIMITIVE_RESTART							= 0x8F9D,
	GZ_PRIMITIVE_RESTART_INDEX						= 0x8F9E,
	GZ_COPY_READ_BUFFER								= 0x8F36,
	GZ_COPY_WRITE_BUFFER							= 0x8F37,
	GZ_UNIFORM_BUFFER								= 0x8A11,
	GZ_UNIFORM_BUFFER_BINDING						= 0x8A28,
	GZ_UNIFORM_BUFFER_START							= 0x8A29,
	GZ_UNIFORM_BUFFER_SIZE							= 0x8A2A,
	GZ_MAX_VERTEX_UNIFORM_BLOCKS					= 0x8A2B,
	GZ_MAX_GEOMETRY_UNIFORM_BLOCKS					= 0x8A2C,
	GZ_MAX_FRAGMENT_UNIFORM_BLOCKS					= 0x8A2D,
	GZ_MAX_COMBINED_UNIFORM_BLOCKS					= 0x8A2E,
	GZ_MAX_UNIFORM_BUFFER_BINDINGS					= 0x8A2F,
	GZ_MAX_UNIFORM_BLOCK_SIZE						= 0x8A30,
	GZ_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS		= 0x8A31,
	GZ_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS		= 0x8A32,
	GZ_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS		= 0x8A33,
	GZ_UNIFORM_BUFFER_OFFSET_ALIGNMENT				= 0x8A34,
	GZ_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH			= 0x8A35,
	GZ_ACTIVE_UNIFORM_BLOCKS						= 0x8A36,
	GZ_UNIFORM_TYPE									= 0x8A37,
	GZ_UNIFORM_SIZE									= 0x8A38,
	GZ_UNIFORM_NAME_LENGTH							= 0x8A39,
	GZ_UNIFORM_BLOCK_INDEX							= 0x8A3A,
	GZ_UNIFORM_OFFSET								= 0x8A3B,
	GZ_UNIFORM_ARRAY_STRIDE							= 0x8A3C,
	GZ_UNIFORM_MATRIX_STRIDE						= 0x8A3D,
	GZ_UNIFORM_IS_ROW_MAJOR							= 0x8A3E,
	GZ_UNIFORM_BLOCK_BINDING						= 0x8A3F,
	GZ_UNIFORM_BLOCK_DATA_SIZE						= 0x8A40,
	GZ_UNIFORM_BLOCK_NAME_LENGTH					= 0x8A41,
	GZ_UNIFORM_BLOCK_ACTIVE_UNIFORMS				= 0x8A42,
	GZ_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES			= 0x8A43,
	GZ_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER	= 0x8A44,
	GZ_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER	= 0x8A45,
	GZ_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER	= 0x8A46,
	GZ_INVALID_INDEX								= 0xFFFFFFFFu,

	/* Gizmo imp of OpenGL 3.2  */
	GZ_CONTEXT_CORE_PROFILE_BIT						= 0x00000001,
	GZ_CONTEXT_COMPATIBILITY_PROFILE_BIT			= 0x00000002,
	GZ_MAX_VERTEX_OUTPUT_COMPONENTS					= 0x9122,
	GZ_MAX_GEOMETRY_INPUT_COMPONENTS				= 0x9123,
	GZ_MAX_GEOMETRY_OUTPUT_COMPONENTS				= 0x9124,
	GZ_MAX_FRAGMENT_INPUT_COMPONENTS				= 0x9125,
	GZ_CONTEXT_PROFILE_MASK							= 0x9126,
	GZ_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION		= 0x8E4C,
	GZ_FIRST_VERTEX_CONVENTION						= 0x8E4D,
	GZ_LAST_VERTEX_CONVENTION						= 0x8E4E,
	GZ_PROVOKING_VERTEX								= 0x8E4F,
	GZ_TEXTURE_CUBE_MAP_SEAMLESS					= 0x884F,
	GZ_MAX_SERVER_WAIT_TIMEOUT						= 0x9111,
	GZ_SYNC_CONDITION								= 0x9113,
	GZ_SYNC_STATUS									= 0x9114,
	GZ_SYNC_FLAGS									= 0x9115,
	GZ_SYNC_FENCE									= 0x9116,
	GZ_SYNC_GPU_COMMANDS_COMPLETE					= 0x9117,
	GZ_UNSIGNALED									= 0x9118,
	GZ_SIGNALED										= 0x9119,
	GZ_ALREADY_SIGNALED								= 0x911A,
	GZ_TIMEOUT_EXPIRED								= 0x911B,
	GZ_CONDITION_SATISFIED							= 0x911C,
	GZ_WAIT_FAILED									= 0x911D,
//	GZ_TIMEOUT_IGNORED								= 0xFFFFFFFFFFFFFFFFull,
	GZ_SYNC_FLUSH_COMMANDS_BIT						= 0x00000001,
	GZ_SAMPLE_POSITION								= 0x8E50,
	GZ_SAMPLE_MASK									= 0x8E51,
	GZ_SAMPLE_MASK_VALUE							= 0x8E52,
	GZ_MAX_SAMPLE_MASK_WORDS						= 0x8E59,
	GZ_TEXTURE_2D_MULTISAMPLE						= 0x9100,
	GZ_PROXY_TEXTURE_2D_MULTISAMPLE					= 0x9101,
	GZ_TEXTURE_2D_MULTISAMPLE_ARRAY					= 0x9102,
	GZ_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY			= 0x9103,
	GZ_TEXTURE_BINDING_2D_MULTISAMPLE				= 0x9104,
	GZ_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY			= 0x9105,
	GZ_TEXTURE_SAMPLES								= 0x9106,
	GZ_TEXTURE_FIXED_SAMPLE_LOCATIONS				= 0x9107,
	GZ_SAMPLER_2D_MULTISAMPLE						= 0x9108,
	GZ_INT_SAMPLER_2D_MULTISAMPLE					= 0x9109,
	GZ_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE			= 0x910A,
	GZ_SAMPLER_2D_MULTISAMPLE_ARRAY					= 0x910B,
	GZ_INT_SAMPLER_2D_MULTISAMPLE_ARRAY				= 0x910C,
	GZ_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY	= 0x910D,
	GZ_MAX_COLOR_TEXTURE_SAMPLES					= 0x910E,
	GZ_MAX_DEPTH_TEXTURE_SAMPLES					= 0x910F,
	GZ_MAX_INTEGER_SAMPLES							= 0x9110,

	/* Gizmo imp of OpenGL 3.3 */
	GZ_VERTEX_ATTRIB_ARRAY_DIVISOR					= 0x88FE,
	GZ_SRC1_COLOR									= 0x88F9,
	GZ_ONE_MINUS_SRC1_COLOR							= 0x88FA,
	GZ_ONE_MINUS_SRC1_ALPHA							= 0x88FB,
	GZ_MAX_DUAL_SOURCE_DRAW_BUFFERS					= 0x88FC,
	GZ_ANY_SAMPLES_PASSED							= 0x8C2F,
	GZ_SAMPLER_BINDING								= 0x8919,
	GZ_RGB10_A2UI									= 0x906F,
	GZ_TEXTURE_SWIZZLE_R							= 0x8E42,
	GZ_TEXTURE_SWIZZLE_G							= 0x8E43,
	GZ_TEXTURE_SWIZZLE_B							= 0x8E44,
	GZ_TEXTURE_SWIZZLE_A							= 0x8E45,
	GZ_TEXTURE_SWIZZLE_RGBA							= 0x8E46,
	GZ_TIME_ELAPSED									= 0x88BF,
	GZ_TIMESTAMP									= 0x8E28,
	GZ_INT_2_10_10_10_REV							= 0x8D9F,

	/* Gizmo imp of OpenGL 4.0*/
	GZ_SAMPLE_SHADING								= 0x8C36,
	GZ_MIN_SAMPLE_SHADING_VALUE						= 0x8C37,
	GZ_MIN_PROGRAM_TEXTURE_GATHER_OFFSET			= 0x8E5E,
	GZ_MAX_PROGRAM_TEXTURE_GATHER_OFFSET			= 0x8E5F,
	GZ_TEXTURE_CUBE_MAP_ARRAY						= 0x9009,
	GZ_TEXTURE_BINDING_CUBE_MAP_ARRAY				= 0x900A,
	GZ_PROXY_TEXTURE_CUBE_MAP_ARRAY					= 0x900B,
	GZ_SAMPLER_CUBE_MAP_ARRAY						= 0x900C,
	GZ_SAMPLER_CUBE_MAP_ARRAY_SHADOW				= 0x900D,
	GZ_INT_SAMPLER_CUBE_MAP_ARRAY					= 0x900E,
	GZ_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY			= 0x900F,
	GZ_DRAW_INDIRECT_BUFFER							= 0x8F3F,
	GZ_DRAW_INDIRECT_BUFFER_BINDING					= 0x8F43,
	GZ_GEOMETRY_SHADER_INVOCATIONS					= 0x887F,
	GZ_MAX_GEOMETRY_SHADER_INVOCATIONS				= 0x8E5A,
	GZ_MIN_FRAGMENT_INTERPOLATION_OFFSET			= 0x8E5B,
	GZ_MAX_FRAGMENT_INTERPOLATION_OFFSET			= 0x8E5C,
	GZ_FRAGMENT_INTERPOLATION_OFFSET_BITS			= 0x8E5D,
	GZ_MAX_VERTEX_STREAMS							= 0x8E71,
	GZ_DOUBLE_VEC2									= 0x8FFC,
	GZ_DOUBLE_VEC3									= 0x8FFD,
	GZ_DOUBLE_VEC4									= 0x8FFE,
	GZ_DOUBLE_MAT2									= 0x8F46,
	GZ_DOUBLE_MAT3									= 0x8F47,
	GZ_DOUBLE_MAT4									= 0x8F48,
	GZ_DOUBLE_MAT2x3								= 0x8F49,
	GZ_DOUBLE_MAT2x4								= 0x8F4A,
	GZ_DOUBLE_MAT3x2								= 0x8F4B,
	GZ_DOUBLE_MAT3x4								= 0x8F4C,
	GZ_DOUBLE_MAT4x2								= 0x8F4D,
	GZ_DOUBLE_MAT4x3								= 0x8F4E,
	GZ_ACTIVE_SUBROUTINES							= 0x8DE5,
	GZ_ACTIVE_SUBROUTINE_UNIFORMS					= 0x8DE6,
	GZ_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS			= 0x8E47,
	GZ_ACTIVE_SUBROUTINE_MAX_LENGTH					= 0x8E48,
	GZ_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH			= 0x8E49,
	GZ_MAX_SUBROUTINES								= 0x8DE7,
	GZ_MAX_SUBROUTINE_UNIFORM_LOCATIONS				= 0x8DE8,
	GZ_NUM_COMPATIBLE_SUBROUTINES					= 0x8E4A,
	GZ_COMPATIBLE_SUBROUTINES						= 0x8E4B,
	GZ_PATCHES										= 0x000E,
	GZ_PATCH_VERTICES								= 0x8E72,
	GZ_PATCH_DEFAULT_INNER_LEVEL					= 0x8E73,
	GZ_PATCH_DEFAULT_OUTER_LEVEL					= 0x8E74,
	GZ_TESS_CONTROL_OUTPUT_VERTICES					= 0x8E75,
	GZ_TESS_GEN_MODE								= 0x8E76,
	GZ_TESS_GEN_SPACING								= 0x8E77,
	GZ_TESS_GEN_VERTEX_ORDER						= 0x8E78,
	GZ_TESS_GEN_POINT_MODE							= 0x8E79,
	GZ_ISOLINES										= 0x8E7A,
	GZ_FRACTIONAL_ODD								= 0x8E7B,
	GZ_FRACTIONAL_EVEN								= 0x8E7C,
	GZ_MAX_PATCH_VERTICES							= 0x8E7D,
	GZ_MAX_TESS_GEN_LEVEL							= 0x8E7E,
	GZ_MAX_TESS_CONTROL_UNIFORM_COMPONENTS			= 0x8E7F,
	GZ_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS		= 0x8E80,
	GZ_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS			= 0x8E81,
	GZ_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS		= 0x8E82,
	GZ_MAX_TESS_CONTROL_OUTPUT_COMPONENTS			= 0x8E83,
	GZ_MAX_TESS_PATCH_COMPONENTS					= 0x8E84,
	GZ_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS		= 0x8E85,
	GZ_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS		= 0x8E86,
	GZ_MAX_TESS_CONTROL_UNIFORM_BLOCKS				= 0x8E89,
	GZ_MAX_TESS_EVALUATION_UNIFORM_BLOCKS			= 0x8E8A,
	GZ_MAX_TESS_CONTROL_INPUT_COMPONENTS			= 0x886C,
	GZ_MAX_TESS_EVALUATION_INPUT_COMPONENTS			= 0x886D,
	GZ_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS = 0x8E1E,
	GZ_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS = 0x8E1F,
	GZ_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER = 0x84F0,
	GZ_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER = 0x84F1,
	GZ_TESS_EVALUATION_SHADER						= 0x8E87,
	GZ_TESS_CONTROL_SHADER							= 0x8E88,
	GZ_TRANSFORM_FEEDBACK							= 0x8E22,
	GZ_TRANSFORM_FEEDBACK_BUFFER_PAUSED				= 0x8E23,
	GZ_TRANSFORM_FEEDBACK_BUFFER_ACTIVE				= 0x8E24,
	GZ_TRANSFORM_FEEDBACK_BINDING					= 0x8E25,
	GZ_MAX_TRANSFORM_FEEDBACK_BUFFERS				= 0x8E70,

	/* Gizmo imp of OpenGL 4.1 */
	GZ_FIXED										= 0x140C,
	GZ_IMPLEMENTATION_COLOR_READ_TYPE				= 0x8B9A,
	GZ_IMPLEMENTATION_COLOR_READ_FORMAT				= 0x8B9B,
	GZ_LOW_FLOAT									= 0x8DF0,
	GZ_MEDIUM_FLOAT									= 0x8DF1,
	GZ_HIGH_FLOAT									= 0x8DF2,
	GZ_LOW_INT										= 0x8DF3,
	GZ_MEDIUM_INT									= 0x8DF4,
	GZ_HIGH_INT										= 0x8DF5,
	GZ_SHADER_COMPILER								= 0x8DFA,
	GZ_SHADER_BINARY_FORMATS						= 0x8DF8,
	GZ_NUM_SHADER_BINARY_FORMATS					= 0x8DF9,
	GZ_MAX_VERTEX_UNIFORM_VECTORS					= 0x8DFB,
	GZ_MAX_VARYING_VECTORS							= 0x8DFC,
	GZ_MAX_FRAGMENT_UNIFORM_VECTORS					= 0x8DFD,
	GZ_RGB565										= 0x8D62,
	GZ_PROGRAM_BINARY_RETRIEVABLE_HINT				= 0x8257,
	GZ_PROGRAM_BINARY_LENGTH						= 0x8741,
	GZ_NUM_PROGRAM_BINARY_FORMATS					= 0x87FE,
	GZ_PROGRAM_BINARY_FORMATS						= 0x87FF,
	GZ_VERTEX_SHADER_BIT							= 0x00000001,
	GZ_FRAGMENT_SHADER_BIT							= 0x00000002,
	GZ_GEOMETRY_SHADER_BIT							= 0x00000004,
	GZ_TESS_CONTROL_SHADER_BIT						= 0x00000008,
	GZ_TESS_EVALUATION_SHADER_BIT					= 0x00000010,
	GZ_ALL_SHADER_BITS								= 0xFFFFFFFF,
	GZ_PROGRAM_SEPARABLE							= 0x8258,
	GZ_ACTIVE_PROGRAM								= 0x8259,
	GZ_PROGRAM_PIPELINE_BINDING						= 0x825A,
	GZ_MAX_VIEWPORTS								= 0x825B,
	GZ_VIEWPORT_SUBPIXEL_BITS						= 0x825C,
	GZ_VIEWPORT_BOUNDS_RANGE						= 0x825D,
	GZ_LAYER_PROVOKING_VERTEX						= 0x825E,
	GZ_VIEWPORT_INDEX_PROVOKING_VERTEX				= 0x825F,
	GZ_UNDEFINED_VERTEX								= 0x8260,

	/* Gizmo imp of OpenGL 4.2 */
	GZ_COPY_READ_BUFFER_BINDING						= 0x8F36,
	GZ_COPY_WRITE_BUFFER_BINDING					= 0x8F37,
	GZ_TRANSFORM_FEEDBACK_ACTIVE					= 0x8E24,
	GZ_TRANSFORM_FEEDBACK_PAUSED					= 0x8E23,
	GZ_UNPACK_COMPRESSED_BLOCK_WIDTH				= 0x9127,
	GZ_UNPACK_COMPRESSED_BLOCK_HEIGHT				= 0x9128,
	GZ_UNPACK_COMPRESSED_BLOCK_DEPTH				= 0x9129,
	GZ_UNPACK_COMPRESSED_BLOCK_SIZE					= 0x912A,
	GZ_PACK_COMPRESSED_BLOCK_WIDTH					= 0x912B,
	GZ_PACK_COMPRESSED_BLOCK_HEIGHT					= 0x912C,
	GZ_PACK_COMPRESSED_BLOCK_DEPTH					= 0x912D,
	GZ_PACK_COMPRESSED_BLOCK_SIZE					= 0x912E,
	GZ_NUM_SAMPLE_COUNTS							= 0x9380,
	GZ_MIN_MAP_BUFFER_ALIGNMENT						= 0x90BC,
	GZ_ATOMIC_COUNTER_BUFFER						= 0x92C0,
	GZ_ATOMIC_COUNTER_BUFFER_BINDING				= 0x92C1,
	GZ_ATOMIC_COUNTER_BUFFER_START					= 0x92C2,
	GZ_ATOMIC_COUNTER_BUFFER_SIZE					= 0x92C3,
	GZ_ATOMIC_COUNTER_BUFFER_DATA_SIZE				= 0x92C4,
	GZ_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS = 0x92C5,
	GZ_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES = 0x92C6,
	GZ_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER = 0x92C7,
	GZ_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER = 0x92C8,
	GZ_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER = 0x92C9,
	GZ_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER = 0x92CA,
	GZ_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER = 0x92CB,
	GZ_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS			= 0x92CC,
	GZ_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS		= 0x92CD,
	GZ_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS	= 0x92CE,
	GZ_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS			= 0x92CF,
	GZ_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS			= 0x92D0,
	GZ_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS			= 0x92D1,
	GZ_MAX_VERTEX_ATOMIC_COUNTERS					= 0x92D2,
	GZ_MAX_TESS_CONTROL_ATOMIC_COUNTERS				= 0x92D3,
	GZ_MAX_TESS_EVALUATION_ATOMIC_COUNTERS			= 0x92D4,
	GZ_MAX_GEOMETRY_ATOMIC_COUNTERS					= 0x92D5,
	GZ_MAX_FRAGMENT_ATOMIC_COUNTERS					= 0x92D6,
	GZ_MAX_COMBINED_ATOMIC_COUNTERS					= 0x92D7,
	GZ_MAX_ATOMIC_COUNTER_BUFFER_SIZE				= 0x92D8,
	GZ_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS			= 0x92DC,
	GZ_ACTIVE_ATOMIC_COUNTER_BUFFERS				= 0x92D9,
	GZ_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX			= 0x92DA,
	GZ_UNSIGNED_INT_ATOMIC_COUNTER					= 0x92DB,
	GZ_VERTEX_ATTRIB_ARRAY_BARRIER_BIT				= 0x00000001,
	GZ_ELEMENT_ARRAY_BARRIER_BIT					= 0x00000002,
	GZ_UNIFORM_BARRIER_BIT							= 0x00000004,
	GZ_TEXTURE_FETCH_BARRIER_BIT					= 0x00000008,
	GZ_SHADER_IMAGE_ACCESS_BARRIER_BIT				= 0x00000020,
	GZ_COMMAND_BARRIER_BIT							= 0x00000040,
	GZ_PIXEL_BUFFER_BARRIER_BIT						= 0x00000080,
	GZ_TEXTURE_UPDATE_BARRIER_BIT					= 0x00000100,
	GZ_BUFFER_UPDATE_BARRIER_BIT					= 0x00000200,
	GZ_FRAMEBUFFER_BARRIER_BIT						= 0x00000400,
	GZ_TRANSFORM_FEEDBACK_BARRIER_BIT				= 0x00000800,
	GZ_ATOMIC_COUNTER_BARRIER_BIT					= 0x00001000,
	GZ_ALL_BARRIER_BITS								= 0xFFFFFFFF,
	GZ_MAX_IMAGE_UNITS								= 0x8F38,
	GZ_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS = 0x8F39,
	GZ_IMAGE_BINDING_NAME							= 0x8F3A,
	GZ_IMAGE_BINDING_LEVEL							= 0x8F3B,
	GZ_IMAGE_BINDING_LAYERED						= 0x8F3C,
	GZ_IMAGE_BINDING_LAYER							= 0x8F3D,
	GZ_IMAGE_BINDING_ACCESS							= 0x8F3E,
	GZ_IMAGE_1D										= 0x904C,
	GZ_IMAGE_2D										= 0x904D,
	GZ_IMAGE_3D										= 0x904E,
	GZ_IMAGE_2D_RECT								= 0x904F,
	GZ_IMAGE_CUBE									= 0x9050,
	GZ_IMAGE_BUFFER									= 0x9051,
	GZ_IMAGE_1D_ARRAY								= 0x9052,
	GZ_IMAGE_2D_ARRAY								= 0x9053,
	GZ_IMAGE_CUBE_MAP_ARRAY							= 0x9054,
	GZ_IMAGE_2D_MULTISAMPLE							= 0x9055,
	GZ_IMAGE_2D_MULTISAMPLE_ARRAY					= 0x9056,
	GZ_INT_IMAGE_1D									= 0x9057,
	GZ_INT_IMAGE_2D									= 0x9058,
	GZ_INT_IMAGE_3D									= 0x9059,
	GZ_INT_IMAGE_2D_RECT							= 0x905A,
	GZ_INT_IMAGE_CUBE								= 0x905B,
	GZ_INT_IMAGE_BUFFER								= 0x905C,
	GZ_INT_IMAGE_1D_ARRAY							= 0x905D,
	GZ_INT_IMAGE_2D_ARRAY							= 0x905E,
	GZ_INT_IMAGE_CUBE_MAP_ARRAY						= 0x905F,
	GZ_INT_IMAGE_2D_MULTISAMPLE						= 0x9060,
	GZ_INT_IMAGE_2D_MULTISAMPLE_ARRAY				= 0x9061,
	GZ_UNSIGNED_INT_IMAGE_1D						= 0x9062,
	GZ_UNSIGNED_INT_IMAGE_2D						= 0x9063,
	GZ_UNSIGNED_INT_IMAGE_3D						= 0x9064,
	GZ_UNSIGNED_INT_IMAGE_2D_RECT					= 0x9065,
	GZ_UNSIGNED_INT_IMAGE_CUBE						= 0x9066,
	GZ_UNSIGNED_INT_IMAGE_BUFFER					= 0x9067,
	GZ_UNSIGNED_INT_IMAGE_1D_ARRAY					= 0x9068,
	GZ_UNSIGNED_INT_IMAGE_2D_ARRAY					= 0x9069,
	GZ_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY			= 0x906A,
	GZ_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE			= 0x906B,
	GZ_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY		= 0x906C,
	GZ_MAX_IMAGE_SAMPLES							= 0x906D,
	GZ_IMAGE_BINDING_FORMAT							= 0x906E,
	GZ_IMAGE_FORMAT_COMPATIBILITY_TYPE				= 0x90C7,
	GZ_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE			= 0x90C8,
	GZ_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS			= 0x90C9,
	GZ_MAX_VERTEX_IMAGE_UNIFORMS					= 0x90CA,
	GZ_MAX_TESS_CONTROL_IMAGE_UNIFORMS				= 0x90CB,
	GZ_MAX_TESS_EVALUATION_IMAGE_UNIFORMS			= 0x90CC,
	GZ_MAX_GEOMETRY_IMAGE_UNIFORMS					= 0x90CD,
	GZ_MAX_FRAGMENT_IMAGE_UNIFORMS					= 0x90CE,
	GZ_MAX_COMBINED_IMAGE_UNIFORMS					= 0x90CF,
	GZ_COMPRESSED_RGBA_BPTC_UNORM					= 0x8E8C,
	GZ_COMPRESSED_SRGB_ALPHA_BPTC_UNORM				= 0x8E8D,
	GZ_COMPRESSED_RGB_BPTC_SIGNED_FLOAT				= 0x8E8E,
	GZ_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT			= 0x8E8F,
	GZ_TEXTURE_IMMUTABLE_FORMAT						= 0x912F,

	/* Gizmo imp of OpenGL 4.3 */
	GZ_NUM_SHADING_LANGUAGE_VERSIONS				= 0x82E9,
	GZ_VERTEX_ATTRIB_ARRAY_LONG						= 0x874E,
	GZ_COMPRESSED_RGB8_ETC1							= 0x8D64,
	GZ_COMPRESSED_RGB8_ETC2							= 0x9274,
	GZ_COMPRESSED_SRGB8_ETC2						= 0x9275,
	GZ_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2		= 0x9276,
	GZ_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2	= 0x9277,
	GZ_COMPRESSED_RGBA8_ETC2_EAC					= 0x9278,
	GZ_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC				= 0x9279,
	GZ_COMPRESSED_R11_EAC							= 0x9270,
	GZ_COMPRESSED_SIGNED_R11_EAC					= 0x9271,
	GZ_COMPRESSED_RG11_EAC							= 0x9272,
	GZ_COMPRESSED_SIGNED_RG11_EAC					= 0x9273,
	GZ_PRIMITIVE_RESTART_FIXED_INDEX				= 0x8D69,
	GZ_ANY_SAMPLES_PASSED_CONSERVATIVE				= 0x8D6A,
	GZ_MAX_ELEMENT_INDEX							= 0x8D6B,
	GZ_COMPUTE_SHADER								= 0x91B9,
	GZ_MAX_COMPUTE_UNIFORM_BLOCKS					= 0x91BB,
	GZ_MAX_COMPUTE_TEXTURE_IMAGE_UNITS				= 0x91BC,
	GZ_MAX_COMPUTE_IMAGE_UNIFORMS					= 0x91BD,
	GZ_MAX_COMPUTE_SHARED_MEMORY_SIZE				= 0x8262,
	GZ_MAX_COMPUTE_UNIFORM_COMPONENTS				= 0x8263,
	GZ_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS			= 0x8264,
	GZ_MAX_COMPUTE_ATOMIC_COUNTERS					= 0x8265,
	GZ_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS		= 0x8266,
	GZ_MAX_COMPUTE_WORK_GROUP_INVOCATIONS			= 0x90EB,
	GZ_MAX_COMPUTE_WORK_GROUP_COUNT					= 0x91BE,
	GZ_MAX_COMPUTE_WORK_GROUP_SIZE					= 0x91BF,
	GZ_COMPUTE_WORK_GROUP_SIZE						= 0x8267,
	GZ_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER	= 0x90EC,
	GZ_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER = 0x90ED,
	GZ_DISPATCH_INDIRECT_BUFFER						= 0x90EE,
	GZ_DISPATCH_INDIRECT_BUFFER_BINDING				= 0x90EF,
	GZ_COMPUTE_SHADER_BIT							= 0x00000020,
	GZ_DEBUG_OUTPUT_SYNCHRONOUS						= 0x8242,
	GZ_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH				= 0x8243,
	GZ_DEBUG_CALLBACK_FUNCTION						= 0x8244,
	GZ_DEBUG_CALLBACK_USER_PARAM					= 0x8245,
	GZ_DEBUG_SOURCE_API								= 0x8246,
	GZ_DEBUG_SOURCE_WINDOW_SYSTEM					= 0x8247,
	GZ_DEBUG_SOURCE_SHADER_COMPILER					= 0x8248,
	GZ_DEBUG_SOURCE_THIRD_PARTY						= 0x8249,
	GZ_DEBUG_SOURCE_APPLICATION						= 0x824A,
	GZ_DEBUG_SOURCE_OTHER							= 0x824B,
	GZ_DEBUG_TYPE_ERROR								= 0x824C,
	GZ_DEBUG_TYPE_DEPRECATED_BEHAVIOR				= 0x824D,
	GZ_DEBUG_TYPE_UNDEFINED_BEHAVIOR				= 0x824E,
	GZ_DEBUG_TYPE_PORTABILITY						= 0x824F,
	GZ_DEBUG_TYPE_PERFORMANCE						= 0x8250,
	GZ_DEBUG_TYPE_OTHER								= 0x8251,
	GZ_MAX_DEBUG_MESSAGE_LENGTH						= 0x9143,
	GZ_MAX_DEBUG_LOGGED_MESSAGES					= 0x9144,
	GZ_DEBUG_LOGGED_MESSAGES						= 0x9145,
	GZ_DEBUG_SEVERITY_HIGH							= 0x9146,
	GZ_DEBUG_SEVERITY_MEDIUM						= 0x9147,
	GZ_DEBUG_SEVERITY_LOW							= 0x9148,
	GZ_DEBUG_TYPE_MARKER							= 0x8268,
	GZ_DEBUG_TYPE_PUSH_GROUP						= 0x8269,
	GZ_DEBUG_TYPE_POP_GROUP							= 0x826A,
	GZ_DEBUG_SEVERITY_NOTIFICATION					= 0x826B,
	GZ_MAX_DEBUG_GROUP_STACK_DEPTH					= 0x826C,
	GZ_DEBUG_GROUP_STACK_DEPTH						= 0x826D,
	GZ_BUFFER										= 0x82E0,
	GZ_SHADER										= 0x82E1,
	GZ_PROGRAM										= 0x82E2,
	GZ_QUERY										= 0x82E3,
	GZ_PROGRAM_PIPELINE								= 0x82E4,
	GZ_SAMPLER										= 0x82E6,
	GZ_MAX_LABEL_LENGTH								= 0x82E8,
	GZ_DEBUG_OUTPUT									= 0x92E0,
	GZ_CONTEXT_FLAG_DEBUG_BIT						= 0x00000002,
	GZ_MAX_UNIFORM_LOCATIONS						= 0x826E,
	GZ_FRAMEBUFFER_DEFAULT_WIDTH					= 0x9310,
	GZ_FRAMEBUFFER_DEFAULT_HEIGHT					= 0x9311,
	GZ_FRAMEBUFFER_DEFAULT_LAYERS					= 0x9312,
	GZ_FRAMEBUFFER_DEFAULT_SAMPLES					= 0x9313,
	GZ_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS	= 0x9314,
	GZ_MAX_FRAMEBUFFER_WIDTH						= 0x9315,
	GZ_MAX_FRAMEBUFFER_HEIGHT						= 0x9316,
	GZ_MAX_FRAMEBUFFER_LAYERS						= 0x9317,
	GZ_MAX_FRAMEBUFFER_SAMPLES						= 0x9318,
	GZ_INTERNALFORMAT_SUPPORTED						= 0x826F,
	GZ_INTERNALFORMAT_PREFERRED						= 0x8270,
	GZ_INTERNALFORMAT_RED_SIZE						= 0x8271,
	GZ_INTERNALFORMAT_GREEN_SIZE					= 0x8272,
	GZ_INTERNALFORMAT_BLUE_SIZE						= 0x8273,
	GZ_INTERNALFORMAT_ALPHA_SIZE					= 0x8274,
	GZ_INTERNALFORMAT_DEPTH_SIZE					= 0x8275,
	GZ_INTERNALFORMAT_STENCIL_SIZE					= 0x8276,
	GZ_INTERNALFORMAT_SHARED_SIZE					= 0x8277,
	GZ_INTERNALFORMAT_RED_TYPE						= 0x8278,
	GZ_INTERNALFORMAT_GREEN_TYPE					= 0x8279,
	GZ_INTERNALFORMAT_BLUE_TYPE						= 0x827A,
	GZ_INTERNALFORMAT_ALPHA_TYPE					= 0x827B,
	GZ_INTERNALFORMAT_DEPTH_TYPE					= 0x827C,
	GZ_INTERNALFORMAT_STENCIL_TYPE					= 0x827D,
	GZ_MAX_WIDTH									= 0x827E,
	GZ_MAX_HEIGHT									= 0x827F,
	GZ_MAX_DEPTH									= 0x8280,
	GZ_MAX_LAYERS									= 0x8281,
	GZ_MAX_COMBINED_DIMENSIONS						= 0x8282,
	GZ_COLOR_COMPONENTS								= 0x8283,
	GZ_DEPTH_COMPONENTS								= 0x8284,
	GZ_STENCIL_COMPONENTS							= 0x8285,
	GZ_COLOR_RENDERABLE								= 0x8286,
	GZ_DEPTH_RENDERABLE								= 0x8287,
	GZ_STENCIL_RENDERABLE							= 0x8288,
	GZ_FRAMEBUFFER_RENDERABLE						= 0x8289,
	GZ_FRAMEBUFFER_RENDERABLE_LAYERED				= 0x828A,
	GZ_FRAMEBUFFER_BLEND							= 0x828B,
	GZ_READ_PIXELS									= 0x828C,
	GZ_READ_PIXELS_FORMAT							= 0x828D,
	GZ_READ_PIXELS_TYPE								= 0x828E,
	GZ_TEXTURE_IMAGE_FORMAT							= 0x828F,
	GZ_TEXTURE_IMAGE_TYPE							= 0x8290,
	GZ_GET_TEXTURE_IMAGE_FORMAT						= 0x8291,
	GZ_GET_TEXTURE_IMAGE_TYPE						= 0x8292,
	GZ_MIPMAP										= 0x8293,
	GZ_MANUAL_GENERATE_MIPMAP						= 0x8294,
	GZ_AUTO_GENERATE_MIPMAP							= 0x8295,
	GZ_COLOR_ENCODING								= 0x8296,
	GZ_SRGB_READ									= 0x8297,
	GZ_SRGB_WRITE									= 0x8298,
	GZ_FILTER										= 0x829A,
	GZ_VERTEX_TEXTURE								= 0x829B,
	GZ_TESS_CONTROL_TEXTURE							= 0x829C,
	GZ_TESS_EVALUATION_TEXTURE						= 0x829D,
	GZ_GEOMETRY_TEXTURE								= 0x829E,
	GZ_FRAGMENT_TEXTURE								= 0x829F,
	GZ_COMPUTE_TEXTURE								= 0x82A0,
	GZ_TEXTURE_SHADOW								= 0x82A1,
	GZ_TEXTURE_GATHER								= 0x82A2,
	GZ_TEXTURE_GATHER_SHADOW						= 0x82A3,
	GZ_SHADER_IMAGE_LOAD							= 0x82A4,
	GZ_SHADER_IMAGE_STORE							= 0x82A5,
	GZ_SHADER_IMAGE_ATOMIC							= 0x82A6,
	GZ_IMAGE_TEXEL_SIZE								= 0x82A7,
	GZ_IMAGE_COMPATIBILITY_CLASS					= 0x82A8,
	GZ_IMAGE_PIXEL_FORMAT							= 0x82A9,
	GZ_IMAGE_PIXEL_TYPE								= 0x82AA,
	GZ_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST			= 0x82AC,
	GZ_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST		= 0x82AD,
	GZ_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE			= 0x82AE,
	GZ_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE		= 0x82AF,
	GZ_TEXTURE_COMPRESSED_BLOCK_WIDTH				= 0x82B1,
	GZ_TEXTURE_COMPRESSED_BLOCK_HEIGHT				= 0x82B2,
	GZ_TEXTURE_COMPRESSED_BLOCK_SIZE				= 0x82B3,
	GZ_CLEAR_BUFFER									= 0x82B4,
	GZ_TEXTURE_VIEW									= 0x82B5,
	GZ_VIEW_COMPATIBILITY_CLASS						= 0x82B6,
	GZ_FULL_SUPPORT									= 0x82B7,
	GZ_CAVEAT_SUPPORT								= 0x82B8,
	GZ_IMAGE_CLASS_4_X_32							= 0x82B9,
	GZ_IMAGE_CLASS_2_X_32							= 0x82BA,
	GZ_IMAGE_CLASS_1_X_32							= 0x82BB,
	GZ_IMAGE_CLASS_4_X_16							= 0x82BC,
	GZ_IMAGE_CLASS_2_X_16							= 0x82BD,
	GZ_IMAGE_CLASS_1_X_16							= 0x82BE,
	GZ_IMAGE_CLASS_4_X_8							= 0x82BF,
	GZ_IMAGE_CLASS_2_X_8							= 0x82C0,
	GZ_IMAGE_CLASS_1_X_8							= 0x82C1,
	GZ_IMAGE_CLASS_11_11_10							= 0x82C2,
	GZ_IMAGE_CLASS_10_10_10_2						= 0x82C3,
	GZ_VIEW_CLASS_128_BITS							= 0x82C4,
	GZ_VIEW_CLASS_96_BITS							= 0x82C5,
	GZ_VIEW_CLASS_64_BITS							= 0x82C6,
	GZ_VIEW_CLASS_48_BITS							= 0x82C7,
	GZ_VIEW_CLASS_32_BITS							= 0x82C8,
	GZ_VIEW_CLASS_24_BITS							= 0x82C9,
	GZ_VIEW_CLASS_16_BITS							= 0x82CA,
	GZ_VIEW_CLASS_8_BITS							= 0x82CB,
	GZ_VIEW_CLASS_S3TC_DXT1_RGB						= 0x82CC,
	GZ_VIEW_CLASS_S3TC_DXT1_RGBA					= 0x82CD,
	GZ_VIEW_CLASS_S3TC_DXT3_RGBA					= 0x82CE,
	GZ_VIEW_CLASS_S3TC_DXT5_RGBA					= 0x82CF,
	GZ_VIEW_CLASS_RGTC1_RED							= 0x82D0,
	GZ_VIEW_CLASS_RGTC2_RG							= 0x82D1,
	GZ_VIEW_CLASS_BPTC_UNORM						= 0x82D2,
	GZ_VIEW_CLASS_BPTC_FLOAT						= 0x82D3,
	GZ_UNIFORM										= 0x92E1,
	GZ_UNIFORM_BLOCK								= 0x92E2,
	GZ_PROGRAM_INPUT								= 0x92E3,
	GZ_PROGRAM_OUTPUT								= 0x92E4,
	GZ_BUFFER_VARIABLE								= 0x92E5,
	GZ_SHADER_STORAGE_BLOCK							= 0x92E6,
	GZ_VERTEX_SUBROUTINE							= 0x92E8,
	GZ_TESS_CONTROL_SUBROUTINE						= 0x92E9,
	GZ_TESS_EVALUATION_SUBROUTINE					= 0x92EA,
	GZ_GEOMETRY_SUBROUTINE							= 0x92EB,
	GZ_FRAGMENT_SUBROUTINE							= 0x92EC,
	GZ_COMPUTE_SUBROUTINE							= 0x92ED,
	GZ_VERTEX_SUBROUTINE_UNIFORM					= 0x92EE,
	GZ_TESS_CONTROL_SUBROUTINE_UNIFORM				= 0x92EF,
	GZ_TESS_EVALUATION_SUBROUTINE_UNIFORM			= 0x92F0,
	GZ_GEOMETRY_SUBROUTINE_UNIFORM					= 0x92F1,
	GZ_FRAGMENT_SUBROUTINE_UNIFORM					= 0x92F2,
	GZ_COMPUTE_SUBROUTINE_UNIFORM					= 0x92F3,
	GZ_TRANSFORM_FEEDBACK_VARYING					= 0x92F4,
	GZ_ACTIVE_RESOURCES								= 0x92F5,
	GZ_MAX_NAME_LENGTH								= 0x92F6,
	GZ_MAX_NUM_ACTIVE_VARIABLES						= 0x92F7,
	GZ_MAX_NUM_COMPATIBLE_SUBROUTINES				= 0x92F8,
	GZ_NAME_LENGTH									= 0x92F9,
	GZ_TYPE											= 0x92FA,
	GZ_ARRAY_SIZE									= 0x92FB,
	GZ_OFFSET										= 0x92FC,
	GZ_BLOCK_INDEX									= 0x92FD,
	GZ_ARRAY_STRIDE									= 0x92FE,
	GZ_MATRIX_STRIDE								= 0x92FF,
	GZ_IS_ROW_MAJOR									= 0x9300,
	GZ_ATOMIC_COUNTER_BUFFER_INDEX					= 0x9301,
	GZ_BUFFER_BINDING								= 0x9302,
	GZ_BUFFER_DATA_SIZE								= 0x9303,
	GZ_NUM_ACTIVE_VARIABLES							= 0x9304,
	GZ_ACTIVE_VARIABLES								= 0x9305,
	GZ_REFERENCED_BY_VERTEX_SHADER					= 0x9306,
	GZ_REFERENCED_BY_TESS_CONTROL_SHADER			= 0x9307,
	GZ_REFERENCED_BY_TESS_EVALUATION_SHADER			= 0x9308,
	GZ_REFERENCED_BY_GEOMETRY_SHADER				= 0x9309,
	GZ_REFERENCED_BY_FRAGMENT_SHADER				= 0x930A,
	GZ_REFERENCED_BY_COMPUTE_SHADER					= 0x930B,
	GZ_TOP_LEVEL_ARRAY_SIZE							= 0x930C,
	GZ_TOP_LEVEL_ARRAY_STRIDE						= 0x930D,
	GZ_LOCATION										= 0x930E,
	GZ_LOCATION_INDEX								= 0x930F,
	GZ_IS_PER_PATCH									= 0x92E7,
	GZ_SHADER_STORAGE_BUFFER						= 0x90D2,
	GZ_SHADER_STORAGE_BUFFER_BINDING				= 0x90D3,
	GZ_SHADER_STORAGE_BUFFER_START					= 0x90D4,
	GZ_SHADER_STORAGE_BUFFER_SIZE					= 0x90D5,
	GZ_MAX_VERTEX_SHADER_STORAGE_BLOCKS				= 0x90D6,
	GZ_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS			= 0x90D7,
	GZ_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS		= 0x90D8,
	GZ_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS	= 0x90D9,
	GZ_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS			= 0x90DA,
	GZ_MAX_COMPUTE_SHADER_STORAGE_BLOCKS			= 0x90DB,
	GZ_MAX_COMBINED_SHADER_STORAGE_BLOCKS			= 0x90DC,
	GZ_MAX_SHADER_STORAGE_BUFFER_BINDINGS			= 0x90DD,
	GZ_MAX_SHADER_STORAGE_BLOCK_SIZE				= 0x90DE,
	GZ_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT		= 0x90DF,
	GZ_SHADER_STORAGE_BARRIER_BIT					= 0x00002000,
	GZ_MAX_COMBINED_SHADER_OUTPUT_RESOURCES			= 0x8F39,
	GZ_DEPTH_STENCIL_TEXTURE_MODE					= 0x90EA,
	GZ_TEXTURE_BUFFER_OFFSET						= 0x919D,
	GZ_TEXTURE_BUFFER_SIZE							= 0x919E,
	GZ_TEXTURE_BUFFER_OFFSET_ALIGNMENT				= 0x919F,
	GZ_TEXTURE_VIEW_MIN_LEVEL						= 0x82DB,
	GZ_TEXTURE_VIEW_NUM_LEVELS						= 0x82DC,
	GZ_TEXTURE_VIEW_MIN_LAYER						= 0x82DD,
	GZ_TEXTURE_VIEW_NUM_LAYERS						= 0x82DE,
	GZ_TEXTURE_IMMUTABLE_LEVELS						= 0x82DF,
	GZ_VERTEX_ATTRIB_BINDING						= 0x82D4,
	GZ_VERTEX_ATTRIB_RELATIVE_OFFSET				= 0x82D5,
	GZ_VERTEX_BINDING_DIVISOR						= 0x82D6,
	GZ_VERTEX_BINDING_OFFSET						= 0x82D7,
	GZ_VERTEX_BINDING_STRIDE						= 0x82D8,
	GZ_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET			= 0x82D9,
	GZ_MAX_VERTEX_ATTRIB_BINDINGS					= 0x82DA,
	GZ_VERTEX_BINDING_BUFFER						= 0x8F4F,
	GZ_DISPLAY_LIST									= 0x82E7,

	/* Gizmo imp of OpenGL 4.4 */
	GZ_MAX_VERTEX_ATTRIB_STRIDE						= 0x82E5,
	GZ_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED		= 0x8221,
	GZ_TEXTURE_BUFFER_BINDING						= 0x8C2A,
	GZ_MAP_PERSISTENT_BIT							= 0x0040,
	GZ_MAP_COHERENT_BIT								= 0x0080,
	GZ_DYNAMIC_STORAGE_BIT							= 0x0100,
	GZ_CLIENT_STORAGE_BIT							= 0x0200,
	GZ_CLIENT_MAPPED_BUFFER_BARRIER_BIT				= 0x00004000,
	GZ_BUFFER_IMMUTABLE_STORAGE						= 0x821F,
	GZ_BUFFER_STORAGE_FLAGS							= 0x8220,
	GZ_CLEAR_TEXTURE								= 0x9365,
	GZ_LOCATION_COMPONENT							= 0x934A,
	GZ_TRANSFORM_FEEDBACK_BUFFER_INDEX				= 0x934B,
	GZ_TRANSFORM_FEEDBACK_BUFFER_STRIDE				= 0x934C,
	GZ_QUERY_BUFFER									= 0x9192,
	GZ_QUERY_BUFFER_BARRIER_BIT						= 0x00008000,
	GZ_QUERY_BUFFER_BINDING							= 0x9193,
	GZ_QUERY_RESULT_NO_WAIT							= 0x9194,
	GZ_MIRROR_CLAMP_TO_EDGE							= 0x8743,

	/* Gizmo imp of OpenGL 4.5 */
	GZ_CONTEXT_LOST									= 0x0507,
	GZ_NEGATIVE_ONE_TO_ONE							= 0x935E,
	GZ_ZERO_TO_ONE									= 0x935F,
	GZ_CLIP_ORIGIN									= 0x935C,
	GZ_CLIP_DEPTH_MODE								= 0x935D,
	GZ_QUERY_WAIT_INVERTED							= 0x8E17,
	GZ_QUERY_NO_WAIT_INVERTED						= 0x8E18,
	GZ_QUERY_BY_REGION_WAIT_INVERTED				= 0x8E19,
	GZ_QUERY_BY_REGION_NO_WAIT_INVERTED				= 0x8E1A,
	GZ_MAX_CULL_DISTANCES							= 0x82F9,
	GZ_MAX_COMBINED_CLIP_AND_CULL_DISTANCES			= 0x82FA,
	GZ_TEXTURE_TARGET								= 0x1006,
	GZ_QUERY_TARGET									= 0x82EA,
	GZ_GUILTY_CONTEXT_RESET							= 0x8253,
	GZ_INNOCENT_CONTEXT_RESET						= 0x8254,
	GZ_UNKNOWN_CONTEXT_RESET						= 0x8255,
	GZ_RESET_NOTIFICATION_STRATEGY					= 0x8256,
	GZ_LOSE_CONTEXT_ON_RESET						= 0x8252,
	GZ_NO_RESET_NOTIFICATION						= 0x8261,
	GZ_CONTEXT_FLAG_ROBUST_ACCESS_BIT				= 0x00000004,
	GZ_COLOR_TABLE									= 0x80D0,
	GZ_POST_CONVOLUTION_COLOR_TABLE					= 0x80D1,
	GZ_POST_COLOR_MATRIX_COLOR_TABLE				= 0x80D2,
	GZ_PROXY_COLOR_TABLE							= 0x80D3,
	GZ_PROXY_POST_CONVOLUTION_COLOR_TABLE			= 0x80D4,
	GZ_PROXY_POST_COLOR_MATRIX_COLOR_TABLE			= 0x80D5,
	GZ_CONVOLUTION_1D								= 0x8010,
	GZ_CONVOLUTION_2D								= 0x8011,
	GZ_SEPARABLE_2D									= 0x8012,
	GZ_HISTOGRAM									= 0x8024,
	GZ_PROXY_HISTOGRAM								= 0x8025,
	GZ_MINMAX										= 0x802E,
	GZ_CONTEXT_RELEASE_BEHAVIOR						= 0x82FB,
	GZ_CONTEXT_RELEASE_BEHAVIOR_FLUSH				= 0x82FC,

	/* Gizmo imp of OpenGL 4.6 */

	GZ_SHADER_BINARY_FORMAT_SPIR_V					= 0x9551,
	GZ_SPIR_V_BINARY								= 0x9552,
	GZ_PARAMETER_BUFFER								= 0x80EE,
	GZ_PARAMETER_BUFFER_BINDING						= 0x80EF,
	GZ_CONTEXT_FLAG_NO_ERROR_BIT					= 0x00000008,
	GZ_VERTICES_SUBMITTED							= 0x82EE,
	GZ_PRIMITIVES_SUBMITTED							= 0x82EF,
	GZ_VERTEX_SHADER_INVOCATIONS					= 0x82F0,
	GZ_TESS_CONTROL_SHADER_PATCHES					= 0x82F1,
	GZ_TESS_EVALUATION_SHADER_INVOCATIONS			= 0x82F2,
	GZ_GEOMETRY_SHADER_PRIMITIVES_EMITTED			= 0x82F3,
	GZ_FRAGMENT_SHADER_INVOCATIONS					= 0x82F4,
	GZ_COMPUTE_SHADER_INVOCATIONS					= 0x82F5,
	GZ_CLIPPING_INPUT_PRIMITIVES					= 0x82F6,
	GZ_CLIPPING_OUTPUT_PRIMITIVES					= 0x82F7,
	GZ_POLYGON_OFFSET_CLAMP							= 0x8E1B,
	GZ_SPIR_V_EXTENSIONS							= 0x9553,
	GZ_NUM_SPIR_V_EXTENSIONS						= 0x9554,
	GZ_TEXTURE_MAX_ANISOTROPY						= 0x84FE,
	GZ_MAX_TEXTURE_MAX_ANISOTROPY					= 0x84FF,
	GZ_TRANSFORM_FEEDBACK_OVERFLOW					= 0x82EC,
	GZ_TRANSFORM_FEEDBACK_STREAM_OVERFLOW			= 0x82ED,

	// ------------------ EXTENSIONS used historically -----------------------

	/* GL_EXT_compiled_vertex_array used as default for Gizmo3D */
	/* No extension is used due to standard implementation */

	GZ_ARRAY_ELEMENT_LOCK_FIRST						= 0x81A8,
	GZ_ARRAY_ELEMENT_LOCK_COUNT						= 0x81A9,

	/* GL_ARB_multitexture used as default for Gizmo3D */
	/* No extension ARB is added due to standard implementation */

	GZ_TEXTURE0										= 0x84C0,
	GZ_TEXTURE1										= 0x84C1,
	GZ_TEXTURE2										= 0x84C2,
	GZ_TEXTURE3										= 0x84C3,
	GZ_TEXTURE4										= 0x84C4,
	GZ_TEXTURE5										= 0x84C5,
	GZ_TEXTURE6										= 0x84C6,
	GZ_TEXTURE7										= 0x84C7,
	GZ_TEXTURE8										= 0x84C8,
	GZ_TEXTURE9										= 0x84C9,
	GZ_TEXTURE10									= 0x84CA,
	GZ_TEXTURE11									= 0x84CB,
	GZ_TEXTURE12									= 0x84CC,
	GZ_TEXTURE13									= 0x84CD,
	GZ_TEXTURE14									= 0x84CE,
	GZ_TEXTURE15									= 0x84CF,
	GZ_TEXTURE16									= 0x84D0,
	GZ_TEXTURE17									= 0x84D1,
	GZ_TEXTURE18									= 0x84D2,
	GZ_TEXTURE19									= 0x84D3,
	GZ_TEXTURE20									= 0x84D4,
	GZ_TEXTURE21									= 0x84D5,
	GZ_TEXTURE22									= 0x84D6,
	GZ_TEXTURE23									= 0x84D7,
	GZ_TEXTURE24									= 0x84D8,
	GZ_TEXTURE25									= 0x84D9,
	GZ_TEXTURE26									= 0x84DA,
	GZ_TEXTURE27									= 0x84DB,
	GZ_TEXTURE28									= 0x84DC,
	GZ_TEXTURE29									= 0x84DD,
	GZ_TEXTURE30									= 0x84DE,
	GZ_TEXTURE31									= 0x84DF,
	GZ_ACTIVE_TEXTURE								= 0x84E0,
	GZ_CLIENT_ACTIVE_TEXTURE						= 0x84E1,
	GZ_MAX_TEXTURE_UNITS							= 0x84E2,

	//----------------------------------------------//
	/* Vertex Weghts used as standard for Gizmo3D */
	/* No extension EXT is added due to standard implementation */
	
	GZ_VERTEX_WEIGHTING								= 0x8509,

	// gzMatrixMode()

	GZ_MODELVIEW0									= GZ_MODELVIEW,
	GZ_MODELVIEW1									= 0x850a,

	// gets

	GZ_CURRENT_VERTEX_WEIGHT						= 0x850b,
	GZ_VERTEX_WEIGHT_ARRAY							= 0x850c,
	GZ_VERTEX_WEIGHT_ARRAY_SIZE						= 0x850d,
	GZ_VERTEX_WEIGHT_ARRAY_TYPE						= 0x850e,
	GZ_VERTEX_WEIGHT_ARRAY_STIDE					= 0x850f,
	GZ_MODELVIEW0_STACK_DEPTH						= GZ_MODELVIEW_STACK_DEPTH,
	GZ_MODELVIEW1_STACK_DEPTH						= 0x8502,

	// pointers

	GZ_VERTEX_WEIGHT_ARRAY_POINTER					= 0x8510,

	// S3TC formats , no EXT added

	GZ_COMPRESSED_RGB_S3TC_DXT1						= 0x83F0,
	GZ_COMPRESSED_RGBA_S3TC_DXT1					= 0x83F1,
	GZ_COMPRESSED_RGBA_S3TC_DXT3					= 0x83F2,
	GZ_COMPRESSED_RGBA_S3TC_DXT5					= 0x83F3,

	// Depth clamp (NV)
	GZ_DEPTH_CLAMP									= 0x864F,

	// Two sided Stencil (EXT)
	GZ_STENCIL_TEST_TWO_SIDE						= 0x8910,
	GZ_ACTIVE_STENCIL_FACE							= 0x8911,

	// Separate Stencil (ATI)
	GZ_STENCIL_BACK_FUNC							= 0x8800,
	GZ_STENCIL_BACK_FAIL							= 0x8801,
	GZ_STENCIL_BACK_PASS_DEPTH_FAIL					= 0x8802,
	GZ_STENCIL_BACK_PASS_DEPTH_PASS					= 0x8803,

	// Vertex Program & Fragment Program (ARB)

	GZ_VERTEX_PROGRAM								= 0x8620,
	GZ_FRAGMENT_PROGRAM								= 0x8804,
	GZ_VERTEX_PROGRAM_POINT_SIZE					= 0x8642,
	GZ_VERTEX_PROGRAM_TWO_SIDE						= 0x8643,
	GZ_COLOR_SUM									= 0x8458,
	GZ_PROGRAM_FORMAT_ASCII							= 0x8875,
	GZ_VERTEX_ATTRIB_ARRAY_ENABLED					= 0x8622,
	GZ_VERTEX_ATTRIB_ARRAY_SIZE						= 0x8623,
	GZ_VERTEX_ATTRIB_ARRAY_STRIDE					= 0x8624,
	GZ_VERTEX_ATTRIB_ARRAY_TYPE						= 0x8625,
	GZ_VERTEX_ATTRIB_ARRAY_NORMALIZED				= 0x886a,
	GZ_CURRENT_VERTEX_ATTRIB						= 0x8626,
	GZ_VERTEX_ATTRIB_ARRAY_POINTER					= 0x8645,
	GZ_PROGRAM_LENGTH								= 0x8627,
	GZ_PROGRAM_FORMAT								= 0x8876,
	GZ_PROGRAM_BINDING								= 0x8677,
	GZ_PROGRAM_INSTRUCTIONS							= 0x88a0,
	GZ_MAX_PROGRAM_INSTRUCTIONS						= 0x88a1,
	GZ_PROGRAM_NATIVE_INSTRUCTIONS					= 0x88a2,
	GZ_MAX_PROGRAM_NATIVE_INSTRUCTIONS				= 0x88a3,
	GZ_PROGRAM_TEMPORARIES							= 0x88a4,
	GZ_MAX_PROGRAM_TEMPORARIES						= 0x88a5,
	GZ_PROGRAM_NATIVE_TEMPORARIES					= 0x88a6,
	GZ_MAX_PROGRAM_NATIVE_TEMPORARIES				= 0x88a7,
	GZ_PROGRAM_PARAMETERS							= 0x88a8,
	GZ_MAX_PROGRAM_PARAMETERS						= 0x88a9,
	GZ_PROGRAM_NATIVE_PARAMETERS					= 0x88aa,
	GZ_MAX_PROGRAM_NATIVE_PARAMETERS				= 0x88ab,
	GZ_PROGRAM_ATTRIBS								= 0x88ac,
	GZ_MAX_PROGRAM_ATTRIBS							= 0x88ad,
	GZ_PROGRAM_NATIVE_ATTRIBS						= 0x88ae,
	GZ_MAX_PROGRAM_NATIVE_ATTRIBS					= 0x88af,
	GZ_PROGRAM_ADDRESS_REGISTERS					= 0x88b0,
	GZ_MAX_PROGRAM_ADDRESS_REGISTERS				= 0x88b1,
	GZ_PROGRAM_NATIVE_ADDRESS_REGISTERS				= 0x88b2,
	GZ_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS			= 0x88b3,
	GZ_MAX_PROGRAM_LOCAL_PARAMETERS					= 0x88b4,
	GZ_MAX_PROGRAM_ENV_PARAMETERS					= 0x88b5,
	GZ_PROGRAM_UNDER_NATIVE_LIMITS					= 0x88b6,
	GZ_PROGRAM_ALU_INSTRUCTIONS						= 0x8805,
	GZ_PROGRAM_TEX_INSTRUCTIONS						= 0x8806,
	GZ_PROGRAM_TEX_INDIRECTIONS						= 0x8807,
	GZ_PROGRAM_NATIVE_ALU_INSTRUCTIONS				= 0x8808,
	GZ_PROGRAM_NATIVE_TEX_INSTRUCTIONS				= 0x8809,
	GZ_PROGRAM_NATIVE_TEX_INDIRECTIONS				= 0x880a,
	GZ_MAX_PROGRAM_ALU_INSTRUCTIONS					= 0x880b,
	GZ_MAX_PROGRAM_TEX_INSTRUCTIONS					= 0x880c,
	GZ_MAX_PROGRAM_TEX_INDIRECTIONS					= 0x880d,
	GZ_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS			= 0x880e,
	GZ_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS			= 0x880f,
	GZ_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS			= 0x8810,
	GZ_PROGRAM_STRING								= 0x8628,
	GZ_PROGRAM_ERROR_POSITION						= 0x864b,
	GZ_CURRENT_MATRIX								= 0x8641,
	GZ_TRANSPOSE_CURRENT_MATRIX						= 0x88b7,
	GZ_CURRENT_MATRIX_STACK_DEPTH					= 0x8640,
	GZ_MAX_PROGRAM_MATRICES							= 0x862f,
	GZ_MAX_PROGRAM_MATRIX_STACK_DEPTH				= 0x862e,
	GZ_PROGRAM_ERROR_STRING							= 0x8874,
	GZ_MATRIX0										= 0x88c0,
	GZ_MATRIX1										= 0x88c1,
	GZ_MATRIX2										= 0x88c2,
	GZ_MATRIX3										= 0x88c3,
	GZ_MATRIX4										= 0x88c4,
	GZ_MATRIX5										= 0x88c5,
	GZ_MATRIX6										= 0x88c6,
	GZ_MATRIX7										= 0x88c7,
	GZ_MATRIX8										= 0x88c8,
	GZ_MATRIX9										= 0x88c9,
	GZ_MATRIX10										= 0x88ca,
	GZ_MATRIX11										= 0x88cb,
	GZ_MATRIX12										= 0x88cc,
	GZ_MATRIX13										= 0x88cd,
	GZ_MATRIX14										= 0x88ce,
	GZ_MATRIX15										= 0x88cf,
	GZ_MATRIX16										= 0x88d0,
	GZ_MATRIX17										= 0x88d1,
	GZ_MATRIX18										= 0x88d2,
	GZ_MATRIX19										= 0x88d3,
	GZ_MATRIX20										= 0x88d4,
	GZ_MATRIX21										= 0x88d5,
	GZ_MATRIX22										= 0x88d6,
	GZ_MATRIX23										= 0x88d7,
	GZ_MATRIX24										= 0x88d8,
	GZ_MATRIX25										= 0x88d9,
	GZ_MATRIX26										= 0x88da,
	GZ_MATRIX27										= 0x88db,
	GZ_MATRIX28										= 0x88dc,
	GZ_MATRIX29										= 0x88dd,
	GZ_MATRIX30										= 0x88de,
	GZ_MATRIX31										= 0x88df,

	// Vertex and Fragment shaders (ARB)

	GZ_VERTEX_SHADER								= 0x8B31,
	GZ_FRAGMENT_SHADER								= 0x8B30,

	GZ_MAX_FRAGMENT_UNIFORM_COMPONENTS				= 0x8B49,
	GZ_MAX_VERTEX_UNIFORM_COMPONENTS				= 0x8B4A,
	GZ_MAX_VARYING_FLOATS							= 0x8B4B,
	GZ_MAX_VERTEX_TEXTURE_IMAGE_UNITS				= 0x8B4C,
	GZ_MAX_COMBINED_TEXTURE_IMAGE_UNITS				= 0x8B4D,

	GZ_OBJECT_ACTIVE_ATTRIBUTES						= 0x8B89,
	GZ_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH			= 0x8B8A,

	// Shader Objects (ARB)

	GZ_PROGRAM_OBJECT								= 0x8B40,

	GZ_OBJECT_TYPE									= 0x8B4E,
	GZ_OBJECT_SUBTYPE								= 0x8B4F,
	GZ_OBJECT_DELETE_STATUS							= 0x8B80,
	GZ_OBJECT_COMPILE_STATUS						= 0x8B81,
	GZ_OBJECT_LINK_STATUS							= 0x8B82,
	GZ_OBJECT_VALIDATE_STATUS						= 0x8B83,
	GZ_OBJECT_INFO_LOG_LENGTH						= 0x8B84,

	GZ_OBJECT_ATTACHED_OBJECTS						= 0x8B85,
	GZ_OBJECT_ACTIVE_UNIFORMS						= 0x8B86,
	GZ_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH				= 0x8B87,
	GZ_OBJECT_SHADER_SOURCE_LENGTH					= 0x8B88,

	GZ_SHADER_OBJECT								= 0x8B48,

	GZ_FLOAT_VEC2									= 0x8B50,
	GZ_FLOAT_VEC3									= 0x8B51,
	GZ_FLOAT_VEC4									= 0x8B52,
	GZ_INT_VEC2										= 0x8B53,
	GZ_INT_VEC3										= 0x8B54,
	GZ_INT_VEC4										= 0x8B55,
	GZ_BOOLEAN										= 0x8B56,
	GZ_BOOL_VEC2									= 0x8B57,
	GZ_BOOL_VEC3									= 0x8B58,
	GZ_BOOL_VEC4									= 0x8B59,
	GZ_FLOAT_MAT2									= 0x8B5A,
	GZ_FLOAT_MAT3									= 0x8B5B,
	GZ_FLOAT_MAT4									= 0x8B5C,


	// Vertex Buffer Object (ARB) (1.5)

	GZ_ARRAY_BUFFER									= 0x8892,
	GZ_ELEMENT_ARRAY_BUFFER							= 0x8893,
	GZ_ARRAY_BUFFER_BINDING							= 0x8894,
	GZ_ELEMENT_ARRAY_BUFFER_BINDING					= 0x8895,
	GZ_VERTEX_ARRAY_BUFFER_BINDING					= 0x8896,
	GZ_NORMAL_ARRAY_BUFFER_BINDING					= 0x8897,
	GZ_COLOR_ARRAY_BUFFER_BINDING					= 0x8898,
	GZ_INDEX_ARRAY_BUFFER_BINDING					= 0x8899,
	GZ_TEXTURE_COORD_ARRAY_BUFFER_BINDING			= 0x889a,
	GZ_EDGE_FLAG_ARRAY_BUFFER_BINDING				= 0x889b,
	GZ_SECONDARY_ARRAY_BUFFER_BINDING				= 0x889c,
	GZ_FOG_COORDINATE_ARRAY_BUFFER_BINDING			= 0x889d,
	GZ_WEIGHT_ARRAY_BUFFER_BINDING					= 0x889e,
	GZ_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING			= 0x889f,
	GZ_STREAM_DRAW									= 0x88e0,
	GZ_STREAM_READ									= 0x88e1,
	GZ_STREAM_COPY									= 0x88e2,
	GZ_STATIC_DRAW									= 0x88e4,
	GZ_STATIC_READ									= 0x88e5,
	GZ_STATIC_COPY									= 0x88e6,
	GZ_DYNAMIC_DRAW									= 0x88e7,
	GZ_DYNAMIC_READ									= 0x88e9,
	GZ_DYNAMIC_COPY									= 0x88ea,
	GZ_READ_ONLY									= 0x88b8,
	GZ_WRITE_ONLY									= 0x88b9,
	GZ_READ_WRITE									= 0x88ba,
	GZ_BUFFER_SIZE									= 0x8764,
	GZ_BUFFER_USAGE									= 0x8765,
	GZ_BUFFER_ACCESS								= 0x88bb,
	GZ_BUFFER_MAPPED								= 0x88bc,
	GZ_BUFFER_MAP_POINTER							= 0x88bd,


	// Shading Language (ARB)

	GZ_SHADING_LANGUAGE_VERSION						= 0x8b8c,
	
	// Pixel Buffer Object (ARB)
	
	GZ_PIXEL_PACK_BUFFER							= 0x88EB,  
	GZ_PIXEL_UNPACK_BUFFER							= 0x88EC,  
	GZ_PIXEL_PACK_BUFFER_BINDING					= 0x88ED,  
	GZ_PIXEL_UNPACK_BUFFER_BINDING					= 0x88EF,  

	// Audio enumerates

	GZ_AUDIO_SOURCE_RELATIVE						= 0x202,
	GZ_AUDIO_CONE_INNER_ANGLE           		    = 0x1001,
	GZ_AUDIO_CONE_OUTER_ANGLE						= 0x1002,
	GZ_AUDIO_PITCH									= 0x1003,
	GZ_AUDIO_POSITION								= 0x1004,
	GZ_AUDIO_DIRECTION								= 0x1005,
	GZ_AUDIO_VELOCITY								= 0x1006,
	GZ_AUDIO_LOOPING                        		= 0x1007,
	GZ_AUDIO_BUFFER									= 0x1009,
	GZ_AUDIO_GAIN									= 0x100A,
	GZ_AUDIO_MIN_GAIN								= 0x100D,
	GZ_AUDIO_MAX_GAIN								= 0x100E,
	GZ_AUDIO_ORIENTATION							= 0x100F,
	GZ_AUDIO_CHANNEL_MASK							= 0x3000,
	GZ_AUDIO_SOURCE_STATE							= 0x1010,
	GZ_AUDIO_INITIAL                        		= 0x1011,
	GZ_AUDIO_PLAYING                        		= 0x1012,
	GZ_AUDIO_PAUSED                         		= 0x1013,
	GZ_AUDIO_STOPPED								= 0x1014,
	GZ_AUDIO_BUFFERS_QUEUED                 		= 0x1015,
	GZ_AUDIO_BUFFERS_PROCESSED              		= 0x1016,
	GZ_AUDIO_SEC_OFFSET								= 0x1024,
	GZ_AUDIO_SAMPLE_OFFSET                  		= 0x1025,
	GZ_AUDIO_BYTE_OFFSET                    		= 0x1026,
	GZ_AUDIO_SOURCE_TYPE                    		= 0x1027,
	GZ_AUDIO_STATIC                         		= 0x1028,
	GZ_AUDIO_STREAMING                      		= 0x1029,
	GZ_AUDIO_UNDETERMINED                   		= 0x1030,
	GZ_AUDIO_FORMAT_MONO8							= 0x1100,
	GZ_AUDIO_FORMAT_MONO16							= 0x1101,
	GZ_AUDIO_FORMAT_STEREO8							= 0x1102,
	GZ_AUDIO_FORMAT_STEREO16						= 0x1103,
	GZ_AUDIO_REFERENCE_DISTANCE						= 0x1020,
	GZ_AUDIO_ROLLOFF_FACTOR							= 0x1021,
	GZ_AUDIO_CONE_OUTER_GAIN						= 0x1022,
	GZ_AUDIO_MAX_DISTANCE							= 0x1023,
	GZ_AUDIO_FREQUENCY                      		= 0x2001,
	GZ_AUDIO_BITS									= 0x2002,
	GZ_AUDIO_CHANNELS								= 0x2003,
	GZ_AUDIO_SIZE									= 0x2004,
	GZ_AUDIO_UNUSED									= 0x2010,
	GZ_AUDIO_PENDING								= 0x2011,
	GZ_AUDIO_PROCESSED								= 0x2012,
	GZ_AUDIO_INVALID_NAME							= 0xA001,
	GZ_AUDIO_ILLEGAL_ENUM							= 0xA002,
	GZ_AUDIO_INVALID_ENUM							= 0xA002,
	GZ_AUDIO_INVALID_VALUE							= 0xA003,
	GZ_AUDIO_ILLEGAL_COMMAND						= 0xA004,
	GZ_AUDIO_INVALID_OPERATION						= 0xA004,
	GZ_AUDIO_OUT_OF_MEMORY							= 0xA005,
	GZ_AUDIO_VENDOR									= 0xB001,
	GZ_AUDIO_VERSION								= 0xB002,
	GZ_AUDIO_RENDERER								= 0xB003,
	GZ_AUDIO_EXTENSIONS								= 0xB004,
	GZ_AUDIO_DOPPLER_FACTOR							= 0xC000,
	GZ_AUDIO_DOPPLER_VELOCITY						= 0xC001,
	GZ_AUDIO_SPEED_OF_SOUND							= 0xC003,
	GZ_AUDIO_DISTANCE_MODEL							= 0xD000,
	GZ_AUDIO_INVERSE_DISTANCE						= 0xD001,
	GZ_AUDIO_INVERSE_DISTANCE_CLAMPED				= 0xD002,
	GZ_AUDIO_LINEAR_DISTANCE						= 0xD003,
	GZ_AUDIO_LINEAR_DISTANCE_CLAMPED				= 0xD004,
	GZ_AUDIO_EXPONENT_DISTANCE						= 0xD005,
	GZ_AUDIO_EXPONENT_DISTANCE_CLAMPED				= 0xD006,

	// Geometry Shaders (EXT)
	GZ_GEOMETRY_SHADER								= 0x8DD9,
	GZ_MAX_GEOMETRY_VARYING_COMPONENTS				= 0x8DDD,
	GZ_MAX_VERTEX_VARYING_COMPONENTS				= 0x8DDE,
	GZ_MAX_VARYING_COMPONENTS						= 0x8B4B,
	GZ_MAX_GEOMETRY_UNIFORM_COMPONENTS				= 0x8DDF,
	GZ_MAX_GEOMETRY_OUTPUT_VERTICES					= 0x8DE0,
	GZ_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS			= 0x8DE1,
	GZ_GEOMETRY_VERTICES_OUT						= 0x8DDA,
	GZ_GEOMETRY_INPUT_TYPE							= 0x8DDB,
	GZ_GEOMETRY_OUTPUT_TYPE							= 0x8DDC,
	GZ_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS				= 0x8C29,
	GZ_LINES_ADJACENCY								= 0xA,
	GZ_LINE_STRIP_ADJACENCY							= 0xB,
	GZ_TRIANGLES_ADJACENCY							= 0xC,
	GZ_TRIANGLE_STRIP_ADJACENCY						= 0xD,
	GZ_FRAMEBUFFER_ATTACHMENT_LAYERED				= 0x8DA7,
	GZ_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS			= 0x8DA8,
	GZ_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT			= 0x8DA9,
	GZ_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER			= 0x8CD4,
	GZ_PROGRAM_POINT_SIZE							= 0x8642,

	// Float Textures (ARB)

	GZ_TEXTURE_RED_TYPE								= 0x8C10,
	GZ_TEXTURE_GREEN_TYPE							= 0x8C11,
	GZ_TEXTURE_BLUE_TYPE							= 0x8C12,
	GZ_TEXTURE_ALPHA_TYPE							= 0x8C13,
	GZ_TEXTURE_LUMINANCE_TYPE						= 0x8C14,
	GZ_TEXTURE_INTENSITY_TYPE						= 0x8C15,
	GZ_TEXTURE_DEPTH_TYPE							= 0x8C16,

	GZ_UNSIGNED_NORMALIZED							= 0x8C17,

	GZ_RGBA32F										= 0x8814,
	GZ_RGB32F										= 0x8815,
	GZ_ALPHA32F										= 0x8816,
	GZ_INTENSITY32F									= 0x8817,
	GZ_LUMINANCE32F									= 0x8818,
	GZ_LUMINANCE_ALPHA32F							= 0x8819,
	GZ_RGBA16F										= 0x881A,
	GZ_RGB16F										= 0x881B,
	GZ_ALPHA16F										= 0x881C,
	GZ_INTENSITY16F									= 0x881D,
	GZ_LUMINANCE16F									= 0x881E,
	GZ_LUMINANCE_ALPHA16F							= 0x881F,

	// Frame Buffer Objects (EXT)

	GZ_FRAMEBUFFER									= 0x8D40,
	GZ_RENDERBUFFER									= 0x8D41,

	GZ_STENCIL_INDEX1								= 0x8D46,
	GZ_STENCIL_INDEX4								= 0x8D47,
	GZ_STENCIL_INDEX8								= 0x8D48,
	GZ_STENCIL_INDEX16								= 0x8D49,

	GZ_RENDERBUFFER_WIDTH							= 0x8D42,
	GZ_RENDERBUFFER_HEIGHT							= 0x8D43,
	GZ_RENDERBUFFER_INTERNAL_FORMAT					= 0x8D44,
	GZ_RENDERBUFFER_RED_SIZE						= 0x8D50,
	GZ_RENDERBUFFER_GREEN_SIZE						= 0x8D51,
	GZ_RENDERBUFFER_BLUE_SIZE						= 0x8D52,
	GZ_RENDERBUFFER_ALPHA_SIZE						= 0x8D53,
	GZ_RENDERBUFFER_DEPTH_SIZE						= 0x8D54,
	GZ_RENDERBUFFER_STENCIL_SIZE					= 0x8D55,

	GZ_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE			= 0x8CD0,
	GZ_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME			= 0x8CD1,
	GZ_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL			= 0x8CD2,
	GZ_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE	= 0x8CD3,
	GZ_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET	= 0x8CD4,

	GZ_COLOR_ATTACHMENT0							= 0x8CE0,
	GZ_COLOR_ATTACHMENT1							= 0x8CE1,
	GZ_COLOR_ATTACHMENT2							= 0x8CE2,
	GZ_COLOR_ATTACHMENT3							= 0x8CE3,
	GZ_COLOR_ATTACHMENT4							= 0x8CE4,
	GZ_COLOR_ATTACHMENT5							= 0x8CE5,
	GZ_COLOR_ATTACHMENT6							= 0x8CE6,
	GZ_COLOR_ATTACHMENT7							= 0x8CE7,
	GZ_COLOR_ATTACHMENT8							= 0x8CE8,
	GZ_COLOR_ATTACHMENT9							= 0x8CE9,
	GZ_COLOR_ATTACHMENT10							= 0x8CEA,
	GZ_COLOR_ATTACHMENT11							= 0x8CEB,
	GZ_COLOR_ATTACHMENT12							= 0x8CEC,
	GZ_COLOR_ATTACHMENT13							= 0x8CED,
	GZ_COLOR_ATTACHMENT14							= 0x8CEE,
	GZ_COLOR_ATTACHMENT15							= 0x8CEF,
	GZ_DEPTH_ATTACHMENT								= 0x8D00,
	GZ_STENCIL_ATTACHMENT							= 0x8D20,

	GZ_FRAMEBUFFER_COMPLETE							= 0x8CD5,
	GZ_FRAMEBUFFER_INCOMPLETE_ATTACHMENT			= 0x8CD6,
	GZ_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT	= 0x8CD7,
	GZ_FRAMEBUFFER_INCOMPLETE_DIMENSIONS			= 0x8CD9,
	GZ_FRAMEBUFFER_INCOMPLETE_FORMATS				= 0x8CDA,
	GZ_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER			= 0x8CDB,
	GZ_FRAMEBUFFER_INCOMPLETE_READ_BUFFER			= 0x8CDC,
	GZ_FRAMEBUFFER_UNSUPPORTED						= 0x8CDD,

	GZ_FRAMEBUFFER_BINDING							= 0x8CA6,
	GZ_RENDERBUFFER_BINDING							= 0x8CA7,
	GZ_MAX_COLOR_ATTACHMENTS						= 0x8CDF,
	GZ_MAX_RENDERBUFFER_SIZE						= 0x84E8,
	
	GZ_INVALID_FRAMEBUFFER_OPERATION				= 0x0506,

	// Multisample Framebuffer
	GZ_RENDERBUFFER_SAMPLES							= 0x8CAB,
	GZ_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE			= 0x8D56,
	GZ_MAX_SAMPLES  								= 0x8D57,

	GZ_READ_FRAMEBUFFER								= 0x8CA8,
	GZ_DRAW_FRAMEBUFFER								= 0x8CA9,
	GZ_DRAW_FRAMEBUFFER_BINDING						= 0x8CA6, // alias FRAMEBUFFER_BINDING_EXT
	GZ_READ_FRAMEBUFFER_BINDING						= 0x8CAA,


	
	 // OpenAL
    GZ_OPENAL_FREQUENCY								= 0x1007,
    GZ_OPENAL_REFRESH								= 0x1008,
    GZ_OPENAL_SYNC									= 0x1009,
    GZ_OPENAL_MONO_SOURCES                         	= 0x1010,
    GZ_OPENAL_STEREO_SOURCES                       	= 0x1011,
   
	GZ_OPENAL_AUDIO_NO_ERROR                       	= 0,
    GZ_OPENAL_INVALID_DEVICE                       	= 0xA001,
    GZ_OPENAL_INVALID_CONTEXT                      	= 0xA002,
    GZ_OPENAL_INVALID_ENUM                         	= 0xA003,
    GZ_OPENAL_INVALID_VALUE                        	= 0xA004,
    GZ_OPENAL_OUT_OF_MEMORY                        	= 0xA005,

    GZ_OPENAL_DEFAULT_DEVICE_SPECIFIER             	= 0x1004,
    GZ_OPENAL_DEVICE_SPECIFIER                     	= 0x1005,
    GZ_OPENAL_EXTENSIONS                           	= 0x1006,
	
    GZ_OPENAL_MAJOR_VERSION                        	= 0x1000,
    GZ_OPENAL_MINOR_VERSION                        	= 0x1001,
	
    GZ_OPENAL_ATTRIBUTES_SIZE                      	= 0x1002,
    GZ_OPENAL_ALL_ATTRIBUTES                       	= 0x1003,
	
    GZ_OPENAL_CAPTURE_DEVICE_SPECIFIER             	= 0x310,
    GZ_OPENAL_CAPTURE_DEFAULT_DEVICE_SPECIFIER     	= 0x311,
    GZ_OPENAL_CAPTURE_SAMPLES                      	= 0x312,

	

} gzEnum;

static_assert (sizeof(gzEnum) == 4, "gzEnum size is not correct");

enum gzEnumBits
{
	GZ_CURRENT_BIT			= 0x00000001,
	GZ_POINT_BIT			= 0x00000002,
	GZ_LINE_BIT				= 0x00000004,
	GZ_POLYGON_BIT			= 0x00000008,
	GZ_POLYGON_STIPPLE_BIT	= 0x00000010,
	GZ_PIXEL_MODE_BIT		= 0x00000020,
	GZ_LIGHTING_BIT			= 0x00000040,
	GZ_FOG_BIT				= 0x00000080,
	GZ_DEPTH_BUFFER_BIT		= 0x00000100,
	GZ_ACCUM_BUFFER_BIT		= 0x00000200,
	GZ_STENCIL_BUFFER_BIT	= 0x00000400,
	GZ_VIEWPORT_BIT			= 0x00000800,
	GZ_TRANSFORM_BIT		= 0x00001000,
	GZ_ENABLE_BIT			= 0x00002000,
	GZ_COLOR_BUFFER_BIT		= 0x00004000,
	GZ_HINT_BIT				= 0x00008000,
	GZ_EVAL_BIT				= 0x00010000,
	GZ_LIST_BIT				= 0x00020000,
	GZ_TEXTURE_BIT			= 0x00040000,
	GZ_SCISSOR_BIT			= 0x00080000,
	GZ_MULTISAMPLE_BIT		= 0x20000000,
	GZ_ALL_ATTRIB_BITS		= 0xffffffff
};

// Some generic macros ---------------------------------------------------------------------------

#define GZ_NO_IMPLICITS(x)			x(const x&) = delete; x& operator=(const x&) = delete; x& operator=(const x&&) = delete;					// no Copy, Assign, Move
#define GZ_PRIVATE_IMPLICITS(x)		private: x(const x&) = default; x& operator=(const x&) = default; 											// private Copy, Assign, Move
#define GZ_NO_IMPLICIT_MOVE(x)		x& operator=(const x&&) = delete;																			// no Copy, Assign, Move

#define GZ_USE_BIT_LOGIC(x)	\
	inline x operator|( const x &a,const x &b){ return (x)(((gzUInt32)a)|((gzUInt32)b)); }\
	inline x operator&( const x &a,const x &b){ return (x)(((gzUInt32)a)&((gzUInt32)b)); }\
	inline x operator^( const x &a,const x &b){ return (x)(((gzUInt32)a)^((gzUInt32)b)); }\
	inline x operator~( const x &a){ return (x)(~((gzUInt32)a)); }

#define GZ_USE_64_BIT_LOGIC(x)	\
	inline x operator|( const x &a,const x &b){ return (x)(((gzUInt64)a)|((gzUInt64)b)); }\
	inline x operator&( const x &a,const x &b){ return (x)(((gzUInt64)a)&((gzUInt64)b)); }\
	inline x operator^( const x &a,const x &b){ return (x)(((gzUInt64)a)^((gzUInt64)b)); }\
	inline x operator~( const x &a){ return (x)(~((gzUInt64)a)); }

#define GZ_USE_BIT_LOGIC_MIX(x,y)	\
	inline x operator|( const x &a,const y &b){ return (x)(((gzUInt32)a)|((gzUInt32)b)); }\
	inline x operator&( const x &a,const y &b){ return (x)(((gzUInt32)a)&((gzUInt32)b)); }\
	inline x operator^( const x &a,const y &b){ return (x)(((gzUInt32)a)^((gzUInt32)b)); }\
	inline x operator|( const y &a,const x &b){ return (x)(((gzUInt32)a)|((gzUInt32)b)); }\
	inline x operator&( const y &a,const x &b){ return (x)(((gzUInt32)a)&((gzUInt32)b)); }\
	inline x operator^( const y &a,const x &b){ return (x)(((gzUInt32)a)^((gzUInt32)b)); }

#define GZ_USE_64_BIT_LOGIC_MIX(x,y)	\
	inline x operator|( const x &a,const y &b){ return (x)(((gzUInt64)a)|((gzUInt64)b)); }\
	inline x operator&( const x &a,const y &b){ return (x)(((gzUInt64)a)&((gzUInt64)b)); }\
	inline x operator^( const x &a,const y &b){ return (x)(((gzUInt64)a)^((gzUInt64)b)); }\
	inline x operator|( const y &a,const x &b){ return (x)(((gzUInt64)a)|((gzUInt64)b)); }\
	inline x operator&( const y &a,const x &b){ return (x)(((gzUInt64)a)&((gzUInt64)b)); }\
	inline x operator^( const y &a,const x &b){ return (x)(((gzUInt64)a)^((gzUInt64)b)); }

#define GZ_USE_BIT_LOGIC_ADD(x)	\
	inline x operator+( const x &a,const x &b){ return (x)(((gzUInt32)a)+((gzUInt32)b)); }\
	inline x operator-( const x &a,const x &b){ return (x)(((gzUInt32)a)-((gzUInt32)b)); }

#define GZ_USE_BIT_LOGIC_ADD_MIX(x,y)	\
	inline x operator+( const x &a,const y &b){ return (x)(((gzUInt32)a)+((gzUInt32)b)); }\
	inline x operator-( const x &a,const y &b){ return (x)(((gzUInt32)a)-((gzUInt32)b)); }\
	inline x operator+( const y &a,const x &b){ return (x)(((gzUInt32)a)+((gzUInt32)b)); }\
	inline x operator-( const y &a,const x &b){ return (x)(((gzUInt32)a)-((gzUInt32)b)); }

GZ_USE_BIT_LOGIC(gzEnumBits);

enum gzClientEnumBits
{
	GZ_CLIENT_PIXEL_STORE_BIT	= 0x00000001,
	GZ_CLIENT_VERTEX_ARRAY_BIT	= 0x00000002,
	GZ_CLIENT_ALL_ATTRIB_BITS	= 0x0000FFFF
};

GZ_USE_BIT_LOGIC(gzClientEnumBits);

//******************************************************************
// Version and DLL information for Windows DLLs
// We are using Gizmo3D as Win32 DLLs and need to activate GZ_XXX_DLL 
// for each package

// The static libraries are available upon request

#ifdef GZ_WINDOWS
	#ifndef GZ_STATIC			// Default to use all Gizmo3D dlls
		#define GZ_BASE_DLL		// Define GZ_STATIC to use static libs
		#define GZ_GRAPH_DLL
		#define GZ_SYSTEM_DLL
		#define GZ_IMAGE_DLL
		#define GZ_DB_DLL
	#endif
#endif // GZ_WINDOWS

#ifdef GZ_BASE_DLL	//gzbase.dll
#ifdef GZBASE_EXPORTS
#define GZ_BASE_EXPORT	__declspec(dllexport)
#else
#define GZ_BASE_EXPORT	__declspec(dllimport)
#endif
#else
#define GZ_BASE_EXPORT
#endif

#ifdef GZ_IMAGE_DLL	//gzimage.dll
#ifdef GZIMAGE_EXPORTS
#define GZ_IMAGE_EXPORT __declspec(dllexport)
#else
#define GZ_IMAGE_EXPORT	__declspec(dllimport)
#endif
#else
#define GZ_IMAGE_EXPORT
#endif

#ifdef GZ_GRAPH_DLL	// gzgraph.dll
#ifdef GZGRAPH_EXPORTS
#define GZ_GRAPH_EXPORT __declspec(dllexport)
#else
#define GZ_GRAPH_EXPORT	__declspec(dllimport)
#endif
#else
#define GZ_GRAPH_EXPORT
#endif

#ifdef GZ_SYSTEM_DLL	// gzsystem.dll
#ifdef GZSYSTEM_EXPORTS
#define GZ_SYSTEM_EXPORT	__declspec(dllexport)
#else
#define GZ_SYSTEM_EXPORT	__declspec(dllimport)
#endif
#else
#define GZ_SYSTEM_EXPORT
#endif

#ifdef GZ_DB_DLL		// gzdb.dll
#ifdef GZDB_EXPORTS
#define GZ_DB_EXPORT	__declspec(dllexport)
#else
#define GZ_DB_EXPORT	__declspec(dllimport)
#endif
#else
#define GZ_DB_EXPORT
#endif


#define GZ_VERSION_STR	"2.12.200"
#define GZ_VERSION_MAJ	2
#define GZ_VERSION_MIN	12
#define GZ_VERSION_DEV	200

GZ_BASE_EXPORT const char * gzGenerateDebugString(const char *file , gzInt32 line,const char *version);
GZ_BASE_EXPORT gzVoid exitNoExceptions();

#define CONCAT_(X,Y) X##Y			// concat macro
#define CONCAT(X,Y) CONCAT_(X,Y)

#define GZ_DEBUG_INFO(version) gzGenerateDebugString(__FILE__,__LINE__,version)

//******************* basic redir of new/delete for gizmo **********************

//! Global New operator for Gizmo3D debugging purposes. 
GZ_BASE_EXPORT gzVoid *gz_new(size_t size);
//! Global Delete operator for Gizmo3D debugging purposes.
GZ_BASE_EXPORT gzVoid gz_delete(gzVoid *);
//! Global New operator for Gizmo3D debugging purposes with info 
GZ_BASE_EXPORT gzVoid *gz_new(size_t size,const char *info);


//**************** new control *************************************

// Use this setting to trace memory leaks at source code level
// #define GZ_MEM_DEBUG 1  // Debug mem trace. NOT used in release version


// Special disabling of new features for quantify/mfc memory debugging etc..

//#define GZ_ENABLE_NEW_HANDLER 1			// Enable global Gizmo3D internal management of new and delete
//#define GZ_DISABLE_MEMORY_NEW_HANDLER 1	// Disable all Gizmo3D gzMemory new and delete 
//#define GZ_NO_DEBUG_MEM 1					// Disable new/delete debug info


#ifdef GZ_MEM_DEBUG	
	
	// By default enable 
	// global memory new/delete

	#ifndef GZ_ENABLE_NEW_HANDLER 
		#define GZ_ENABLE_NEW_HANDLER 1	// makes "new int" reported and not only gizmo classes
	#endif

#endif


//*******************************************************************

//***************** Inline definitions of new/delete operators *****

#include <memory>
#include <new>

#ifdef GZ_ENABLE_NEW_HANDLER	// Use this to pinpoint mem leaks

// Clean up some old definitions of new/delete e.g. MFC (sucks)

#ifdef new
#undef new
#endif

#ifdef delete
#undef delete
#endif

#ifdef GZ_WINDOWS

inline void * operator new(size_t size)													{ return gz_new(size); };
inline void operator delete(void *address)	noexcept(TRUE)								{ gz_delete(address); };

#ifndef GZ_NO_DEBUG_MEM
inline void * operator new(size_t size, const char * info)								{ return gz_new(size,info); };
inline void operator delete(void *address, const char * /*info*/)	noexcept(TRUE)		{ gz_delete(address); };
#endif // GZ_NO_DEBUG_MEM


inline void * operator new[](size_t size)												{	return gz_new(size); }
inline void operator delete[](void* address) noexcept(TRUE)								{ gz_delete(address); }

#ifndef GZ_NO_DEBUG_MEM
inline void * operator new[](size_t size,const char *info)								{ return gz_new(size,info); }
inline void operator delete[](void *address,const char * /*info*/) noexcept(TRUE)		{ gz_delete(address); }
#endif // GZ_NO_DEBUG_MEM

#endif // GZ_WINDOWS

#endif	// GZ_ENABLE_NEW_HANDLER

#ifdef GZ_MEM_DEBUG
	#ifndef GZ_NO_DEBUG_MEM
		#define new (new (GZ_DEBUG_INFO(GZ_VERSION_STR)))
		#define gz_malloc(arg) gz_malloc(arg,GZ_DEBUG_INFO(GZ_VERSION_STR))
	#endif	// GZ_NO_DEBUG_MEM
#endif	// GZ_MEM_DEBUG

//******************** Register args passing force ********************************

//--------------- Property Macros ------------------------------------------------

// ------------------ default get/set with std implementation --------------
#define GZ_PROPERTY(type,name) public: const type &	get##name() const { return m_property##name; } gzVoid	set##name(const type &prop){ m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_VAL(type,name,value) public: const type &	get##name() const { return m_property##name; } gzVoid	set##name(const type &prop){ m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_V(type,name) public: virtual const type &	get##name() const { return m_property##name; } virtual gzVoid	set##name(const type &prop){ m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_VAL_V(type,name,value) public: virtual const type &	get##name() const { return m_property##name; } virtual gzVoid	set##name(const type &prop){ m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_EXPORT(type,name,exportDef) public: exportDef const type & get##name() const { return m_property##name; } exportDef gzVoid	set##name(const type &prop){ m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_VAL_EXPORT(type,name,value,exportDef) public: exportDef const type & get##name() const { return m_property##name; } exportDef gzVoid set##name(const type &prop){ m_property##name=prop; } private: mutable type m_property##name=value; public:
#define GZ_PROPERTY_EXPORT_V(type,name,exportDef) public: exportDef virtual const type & get##name() const { return m_property##name; } exportDef virtual gzVoid set##name(const type &prop){ m_property##name=prop; } private: mutable type m_property##name; public:
#define GZ_PROPERTY_VAL_EXPORT_V(type,name,value,exportDef) public: exportDef virtual const type & get##name() const { return m_property##name; } exportDef virtual gzVoid set##name(const type &prop){ m_property##name=prop; } private: mutable type m_property##name=value; public:
#define GZ_STATIC_PROPERTY(type,name) public: static const type &	get##name() { return s_property##name; } static gzVoid set##name(const type &prop){ s_property##name=prop; } private: static type s_property##name; public:
#define GZ_STATIC_PROPERTY_VAL(type,name,value) public: static const type &	get##name() { return s_property##name; } static gzVoid set##name(const type &prop){ s_property##name=prop; } private: static type s_property##name=value; public:
#define GZ_STATIC_PROPERTY_EXPORT(type,name,exportDef) public: exportDef static const type & get##name() { return s_property##name; } exportDef static gzVoid	set##name(const type &prop){ s_property##name=prop; } private: 	static type s_property##name; public:

// ------------------ default get/set with std implementation with mutex --------------
#define GZ_PROPERTY_MUTEX(type,name,mutex) public: const type &	get##name() const { GZ_BODYGUARD(mutex);return m_property##name; } gzVoid	set##name(const type &prop){ GZ_BODYGUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_VAL_MUTEX(type,name,value,mutex) public: const type &	get##name() const { GZ_BODYGUARD(mutex);return m_property##name; } gzVoid	set##name(const type &prop){ GZ_BODYGUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_MUTEX_V(type,name,mutex) public: virtual const type &	get##name() const { GZ_BODYGUARD(mutex);return m_property##name; } virtual gzVoid	set##name(const type &prop){ GZ_BODYGUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_VAL_MUTEX_V(type,name,value,mutex) public: virtual const type &	get##name() const { GZ_BODYGUARD(mutex);return m_property##name; } virtual gzVoid	set##name(const type &prop){ GZ_BODYGUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_MUTEX_EXPORT(type,name,mutex,exportDef) public: exportDef const type & get##name() const { GZ_BODYGUARD(mutex);return m_property##name; } exportDef gzVoid	set##name(const type &prop){ GZ_BODYGUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_VAL_MUTEX_EXPORT(type,name,value,mutex,exportDef) public: exportDef const type & get##name() const { GZ_BODYGUARD(mutex);return m_property##name; } exportDef gzVoid	set##name(const type &prop){ GZ_BODYGUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_MUTEX_EXPORT_V(type,name,mutex,exportDef) public: exportDef virtual const type & get##name() const { GZ_BODYGUARD(mutex);return m_property##name; } exportDef virtual gzVoid	set##name(const type &prop){ GZ_BODYGUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_VAL_MUTEX_EXPORT_V(type,name,value,mutex,exportDef) public: exportDef virtual const type & get##name() const { GZ_BODYGUARD(mutex);return m_property##name; } exportDef virtual gzVoid	set##name(const type &prop){ GZ_BODYGUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_STATIC_PROPERTY_MUTEX(type,name,mutex) public: static const type &	get##name() { GZ_BODYGUARD(mutex);return s_property##name; } static gzVoid set##name(const type &prop){ GZ_BODYGUARD(mutex);s_property##name=prop; } private:  static type s_property##name; public:
#define GZ_STATIC_PROPERTY_MUTEX_EXPORT(type,name,mutex,exportDef) public: exportDef static const type & get##name() { GZ_BODYGUARD(mutex);return s_property##name; } exportDef static gzVoid	set##name(const type &prop){ GZ_BODYGUARD(mutex);s_property##name=prop; } private: 	static type s_property##name; public:

// ------------------ no body, implement in .cpp file ----------------------
#define GZ_PROPERTY_(type,name) public: const type & get##name() const; gzVoid	set##name(const type &prop); private: mutable type m_property##name; public:
#define GZ_PROPERTY_VAL_(type,name,value) public: const type & get##name() const; gzVoid	set##name(const type &prop); private: mutable type m_property##name=value; public:
#define GZ_PROPERTY_EXPORT_(type,name,exportDef) public: exportDef const type &	get##name() const ; exportDef gzVoid set##name(const type &prop); private: mutable type m_property##name; public:
#define GZ_PROPERTY_VAL_EXPORT_(type,name,value,exportDef) public: exportDef const type &	get##name() const ; exportDef gzVoid set##name(const type &prop); private: mutable type m_property##name=value; public:
#define GZ_STATIC_PROPERTY_(type,name) public: static const type & get##name() ; static gzVoid set##name(const type &prop); private: static type s_property##name; public:
#define GZ_STATIC_PROPERTY_EXPORT_(type,name,exportDef) public: exportDef static const type & get##name()  ; exportDef static gzVoid set##name(const type &prop); private: type s_property##name; public:

// ----------------- SET only ----------------------------------------------
#define GZ_PROPERTY_SET(type,name) public: gzVoid	set##name(const type &prop){ m_property##name=prop; } private: mutable type m_property##name; public:
#define GZ_PROPERTY_SET_VAL(type,name,value) public: gzVoid	set##name(const type &prop){ m_property##name=prop; } private: mutable type m_property##name=value; public:
#define GZ_PROPERTY_SET_V(type,name) public: virtual gzVoid	set##name(const type &prop){ m_property##name=prop; } private: mutable type m_property##name; public:
#define GZ_PROPERTY_SET_VAL_V(type,name,value) public: virtual gzVoid	set##name(const type &prop){ m_property##name=prop; } private: mutable type m_property##name=value; public:
#define GZ_PROPERTY_SET_EXPORT(type,name,exportDef) public: exportDef gzVoid set##name(const type &prop){ m_property##name=prop; } private: mutable type m_property##name; public:
#define GZ_PROPERTY_SET_VAL_EXPORT(type,name,value,exportDef) public: exportDef gzVoid set##name(const type &prop){ m_property##name=prop; } private: mutable type m_property##name=value; public:
#define GZ_PROPERTY_SET_EXPORT_V(type,name,exportDef) public: exportDef virtual gzVoid set##name(const type &prop){ m_property##name=prop; } private: mutable type m_property##name; public:
#define GZ_PROPERTY_SET_VAL_EXPORT_V(type,name,value,exportDef) public: exportDef virtual gzVoid set##name(const type &prop){ m_property##name=prop; } private: mutable type m_property##name=value; public:
#define GZ_STATIC_PROPERTY_SET(type,name) public: static gzVoid set##name(const type &prop){ s_property##name=prop; } private: static type s_property##name; public:
#define GZ_STATIC_PROPERTY_SET_EXPORT(type,name,exportDef) public: exportDef static gzVoid set##name(const type &prop){ s_property##name=prop; } private: static type m_property##name; public:

// ----------------- SET only, no body ----------------------------------------------
#define GZ_PROPERTY_SET_(type,name) public: gzVoid	set##name(const type &prop); private: mutable type m_property##name; public:
#define GZ_PROPERTY_SET_VAL_(type,name,value) public: gzVoid	set##name(const type &prop); private: mutable type m_property##name=value; public:
#define GZ_PROPERTY_SET_EXPORT_(type,name,exportDef) public: exportDef gzVoid	set##name(const type &prop); private: mutable type m_property##name; public:
#define GZ_PROPERTY_SET_VAL_EXPORT_(type,name,value,exportDef) public: exportDef gzVoid	set##name(const type &prop); private: mutable type m_property##name=value; public:
#define GZ_STATIC_PROPERTY_SET_(type,name) public: static gzVoid set##name(const type &prop); private: static type s_property##name; public:
#define GZ_STATIC_PROPERTY_SET_EXPORT_(type,name,exportDef) public: exportDef static gzVoid	set##name(const type &prop); private: static type s_property##name; public:

// ----------------- GET only ----------------------------------------------
#define GZ_PROPERTY_GET(type,name) public: const type &	get##name() const { return m_property##name; } private: mutable type m_property##name; public:
#define GZ_PROPERTY_GET_VAL(type,name,value) public: const type &	get##name() const { return m_property##name; } private: mutable type m_property##name=value; public:
#define GZ_PROPERTY_GET_V(type,name) public: virtual const type &	get##name() const { return m_property##name; } private: mutable type m_property##name; public:
#define GZ_PROPERTY_GET_VAL_V(type,name,value) public: virtual const type &	get##name() const { return m_property##name; } private: mutable type m_property##name=value; public:
#define GZ_PROPERTY_GET_EXPORT(type,name,exportDef) public: exportDef const type &	get##name() const { return m_property##name; } private: mutable type m_property##name; public:
#define GZ_PROPERTY_GET_VAL_EXPORT(type,name,value,exportDef) public: exportDef const type &	get##name() const { return m_property##name; } private: mutable type m_property##name=value; public:
#define GZ_PROPERTY_GET_EXPORT_V(type,name,exportDef) public: exportDef virtual const type &	get##name() const { return m_property##name; } private: mutable type m_property##name; public:
#define GZ_PROPERTY_GET_VAL_EXPORT_V(type,name,value,exportDef) public: exportDef virtual const type &	get##name() const { return m_property##name; } private: mutable type m_property##name=value; public:
#define GZ_STATIC_PROPERTY_GET(type,name) public: static const type &	get##name()  { return s_property##name; } private: static type m_property##name; public:
#define GZ_STATIC_PROPERTY_GET_EXPORT(type,name,exportDef) public: exportDef static const type & get##name()  { return s_property##name; } private: static type m_property##name; public:

// ----------------- GET only, no body ----------------------------------------------
#define GZ_PROPERTY_GET_(type,name) public: const type &	get##name() const; private: mutable type m_property##name; public:
#define GZ_PROPERTY_GET_VAL_(type,name,value) public: const type &	get##name() const; private: mutable type m_property##name=value; public:
#define GZ_PROPERTY_GET_EXPORT_(type,name,exportDef) public: exportDef const type &	get##name() const; private: mutable type m_property##name; public:
#define GZ_PROPERTY_GET_VAL_EXPORT_(type,name,value,exportDef) public: exportDef const type &	get##name() const; private: mutable type m_property##name=value; public:
#define GZ_STATIC_PROPERTY_GET_(type,name) public: static const type &	get##name() ; private: static type s_property##name; public:
#define GZ_STATIC_PROPERTY_GET_EXPORT_(type,name,exportDef) public: exportDef static const type & get##name(); private: static type s_property##name; public:

// ----------------- Interface Methods Only ----------------------------
#define GZ_PROPERTY_SET_I(type,name) public:  gzVoid	set##name(const type &prop)
#define GZ_PROPERTY_SET_I_V(type,name) public:  virtual gzVoid	set##name(const type &prop)
#define GZ_PROPERTY_SET_EXPORT_I(type,name,exportDef) public: exportDef gzVoid	set##name(const type &prop)
#define GZ_PROPERTY_SET_EXPORT_I_V(type,name,exportDef) public: exportDef virtual gzVoid	set##name(const type &prop)

#define GZ_PROPERTY_GET_I(type,name) public: type	get##name() const
#define GZ_PROPERTY_GET_I_V(type,name) public: virtual type	get##name() const
#define GZ_PROPERTY_GET_EXPORT_I(type,name,exportDef) public: exportDef type	get##name() const
#define GZ_PROPERTY_GET_EXPORT_I_V(type,name,exportDef) public: exportDef virtual type	get##name() const

#define GZ_PROPERTY_I(type,name) public: type get##name() const; gzVoid	set##name(const type &prop); 
#define GZ_PROPERTY_I_V(type,name) public: virtual type get##name() const; virtual gzVoid	set##name(const type &prop); 
#define GZ_PROPERTY_EXPORT_I(type,name,exportDef) public: exportDef type	get##name() const ; exportDef gzVoid set##name(const type &prop);
#define GZ_PROPERTY_EXPORT_I_V(type,name,exportDef) public: exportDef virtual type	get##name() const ; exportDef virtual gzVoid set##name(const type &prop);

#define GZ_STATIC_PROPERTY_SET_I(type,name) public: static gzVoid set##name(const type &prop)
#define GZ_STATIC_PROPERTY_SET_EXPORT_I(type,name,exportDef) public: exportDef static gzVoid set##name(const type &prop)

#define GZ_STATIC_PROPERTY_GET_I(type,name) public: static type	get##name()
#define GZ_STATIC_PROPERTY_GET_EXPORT_I(type,name,exportDef) public: exportDef static type	get##name()

#define GZ_STATIC_PROPERTY_I(type,name) public: static type get##name(); static gzVoid	set##name(const type &prop); 
#define GZ_STATIC_PROPERTY_EXPORT_I(type,name,exportDef) public: exportDef static type	get##name() ; exportDef static gzVoid set##name(const type &prop);

// ---------------- member property only --------------------------------

#define GZ_PROPERTY_PROP(type,name) private: mutable type m_property##name; public:
#define GZ_PROPERTY_PROP_VAL(type,name,value) private: mutable type m_property##name=value; public:
#define GZ_PROPERTY_PROP_EXPORT(type,name,exportDef) private: mutable type m_property##name; public:
#define GZ_PROPERTY_PROP_VAL_EXPORT(type,name,value,exportDef) private: mutable type m_property##name=value; public:
#define GZ_STATIC_PROPERTY_PROP(type,name) private: static type s_property##name; public:
#define GZ_STATIC_PROPERTY_PROP_VAL(type,name,value) private: static type s_property##name=value; public:
#define GZ_STATIC_PROPERTY_PROP_EXPORT(type,name,exportDef) private: static type s_property##name; public:
#define GZ_STATIC_PROPERTY_PROP_VAL_EXPORT(type,name,value,exportDef) private: static type s_property##name=value; public:

// ------------------ default get/set with std implementation with read/write parallell mutex --------------
#define GZ_PROPERTY_RW_MUTEX(type,name,mutex) public: const type &	get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; } gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX(type,name,value,mutex) public: const type &	get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; } gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_RW_MUTEX_V(type,name,mutex) public: virtual const type &	get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; } virtual gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX_V(type,name,value,mutex) public: virtual const type &	get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; } virtual gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_RW_MUTEX_EXPORT(type,name,mutex,exportDef) public: exportDef const type & get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; } exportDef gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX_EXPORT(type,name,value,mutex,exportDef) public: exportDef const type & get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; } exportDef gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_RW_MUTEX_EXPORT_V(type,name,mutex,exportDef) public: exportDef virtual const type & get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; } exportDef virtual gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX_EXPORT_V(type,name,value,mutex,exportDef) public: exportDef virtual const type & get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; } exportDef virtual gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_STATIC_PROPERTY_RW_MUTEX(type,name,mutex) public: static const type &	get##name() { GZ_BODY_READ_GUARD(mutex);return s_property##name; } static gzVoid set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);s_property##name=prop; } private:  static type s_property##name; public:
#define GZ_STATIC_PROPERTY_RW_VAL_MUTEX(type,name,value,mutex) public: static const type &	get##name() { GZ_BODY_READ_GUARD(mutex);return s_property##name; } static gzVoid set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);s_property##name=prop; } private:  static type s_property##name=value; public:
#define GZ_STATIC_PROPERTY_RW_MUTEX_EXPORT(type,name,mutex,exportDef) public: exportDef static const type & get##name() { GZ_BODY_READ_GUARD(mutex);return s_property##name; } exportDef static gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);s_property##name=prop; } private: 	static type s_property##name; public:
#define GZ_STATIC_PROPERTY_RW_VAL_MUTEX_EXPORT(type,name,value,mutex,exportDef) public: exportDef static const type & get##name() { GZ_BODY_READ_GUARD(mutex);return s_property##name; } exportDef static gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);s_property##name=prop; } private: 	static type s_property##name=value; public:

#define GZ_PROPERTY_RW_MUTEX_GET(type,name,mutex) public: const type &	get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; }  private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX_GET(type,name,value,mutex) public: const type &	get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; }  private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_RW_MUTEX_GET_V(type,name,mutex) public: virtual const type &	get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; }  private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX_GET_V(type,name,value,mutex) public: virtual const type &	get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; }  private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_RW_MUTEX_GET_EXPORT(type,name,mutex,exportDef) public: exportDef const type & get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; }  private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX_GET_EXPORT(type,name,value,mutex,exportDef) public: exportDef const type & get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; }  private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_RW_MUTEX_GET_EXPORT_V(type,name,mutex,exportDef) public: exportDef virtual const type & get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; }  private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX_GET_EXPORT_V(type,name,value,mutex,exportDef) public: exportDef virtual const type & get##name() const { GZ_BODY_READ_GUARD(mutex);return m_property##name; }  private: 	mutable type m_property##name=value; public:
#define GZ_STATIC_PROPERTY_RW_MUTEX_GET(type,name,mutex) public: static const type &	get##name() { GZ_BODY_READ_GUARD(mutex);return s_property##name; }  private:  static type s_property##name; public:
#define GZ_STATIC_PROPERTY_RW_VAL_MUTEX_GET(type,name,value,mutex) public: static const type &	get##name() { GZ_BODY_READ_GUARD(mutex);return s_property##name; }  private:  static type s_property##name=value; public:
#define GZ_STATIC_PROPERTY_RW_MUTEX_GET_EXPORT(type,name,mutex,exportDef) public: exportDef static const type & get##name() { GZ_BODY_READ_GUARD(mutex);return s_property##name; } private: 	static type s_property##name; public:
#define GZ_STATIC_PROPERTY_RW_VAL_MUTEX_GET_EXPORT(type,name,value,mutex,exportDef) public: exportDef static const type & get##name() { GZ_BODY_READ_GUARD(mutex);return s_property##name; } private: 	static type s_property##name=value; public:

#define GZ_PROPERTY_RW_MUTEX_SET(type,name,mutex) public: gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX_SET(type,name,value,mutex) public: gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_RW_MUTEX_SET_V(type,name,mutex) public: virtual gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX_SET_V(type,name,value,mutex) public: virtual gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_RW_MUTEX_SET_EXPORT(type,name,mutex,exportDef) public: exportDef gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX_SET_EXPORT(type,name,value,mutex,exportDef) public: exportDef gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_PROPERTY_RW_MUTEX_SET_EXPORT_V(type,name,mutex,exportDef) public: exportDef virtual gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name; public:
#define GZ_PROPERTY_RW_VAL_MUTEX_SET_EXPORT_V(type,name,value,mutex,exportDef) public: exportDef virtual gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);m_property##name=prop; } private: 	mutable type m_property##name=value; public:
#define GZ_STATIC_PROPERTY_RW_MUTEX_SET(type,name,mutex) public: static gzVoid set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);s_property##name=prop; } private:  static type s_property##name; public:
#define GZ_STATIC_PROPERTY_RW_VAL_MUTEX_SET(type,name,value,mutex) public: static gzVoid set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);s_property##name=prop; } private:  static type s_property##name=value; public:
#define GZ_STATIC_PROPERTY_RW_MUTEX_SET_EXPORT(type,name,mutex,exportDef) public: exportDef static gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);s_property##name=prop; } private: 	static type s_property##name; public:
#define GZ_STATIC_PROPERTY_RW_VAL_MUTEX_SET_EXPORT(type,name,value,mutex,exportDef) public: exportDef static gzVoid	set##name(const type &prop){ GZ_BODY_WRITE_GUARD(mutex);s_property##name=prop; } private: 	static type s_property##name=value; public:


#endif // __GZ_BASIC_TYPES_H__







