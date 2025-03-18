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
// File			: gzLibRef.h
// Module		: gzBase
// Description	: Class definition of Library References
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.231
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
// AMO	990928	Created file 	
//
//******************************************************************************
#ifndef __GZ_LIBREF_H__
#define __GZ_LIBREF_H__

#include "gzMutex.h"
#include "gzBase.h"

class gzLibReference : public gzThreadSafeReference
{
public:

	GZ_BASE_EXPORT gzLibReference(gzString libname);
	GZ_BASE_EXPORT explicit gzLibReference(gzVoid *handle);
	GZ_BASE_EXPORT virtual ~gzLibReference();

	GZ_NO_IMPLICITS(gzLibReference);

	GZ_BASE_EXPORT virtual gzReference* clone() const;
	
	GZ_BASE_EXPORT gzVoid	delayReference();
	GZ_BASE_EXPORT gzVoid *	getHandle() const;

	GZ_BASE_EXPORT static gzVoid cleanUpDelayedLibReference();

	GZ_BASE_EXPORT static gzBool	setLibraryPath(const gzString &path);
	GZ_BASE_EXPORT static gzString	getLibraryPath();
	GZ_BASE_EXPORT static gzBool	activateLibraryPath();

private:
	
	// The platform indep handle
	gzVoid	*m_handle;
	
	// Some globals
	static gzRefPointer<gzLibReference> s_delayedLibReference;
	static gzMutex						s_delayedLocker;
	static gzString						s_libraryPath;
};

GZ_DECLARE_REFPTR(gzLibReference);


inline gzLibReference *gzGetLibReference(const gzString &libname )
{																	
	return new gzLibReference(libname+GZ_LIB_EXT);			
}

#define GZ_LIBREF_DECL(x)		gzLibReference *gzGetLibReference_##x();
#define GZ_LIBREF_IMPL(x)		gzLibReference *gzGetLibReference_##x() { return gzGetLibReference(#x); }

#ifndef GZ_STATIC
	#ifndef GZ_NOLIBREF
		#define GZ_LIBREF_IMPL_GZ(x)	gzLibReference *gzGetLibReference_##x() { return gzGetLibReference(GZ_LIB_PREFIX "gz" # x); }
	#else
		#define GZ_LIBREF_IMPL_GZ(x)	gzLibReference *gzGetLibReference_##x() { return NULL; }
	#endif
#else
	#define GZ_LIBREF_IMPL_GZ(x)	gzLibReference *gzGetLibReference_##x() { return NULL; }
#endif


#endif

