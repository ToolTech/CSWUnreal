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
// File			: gzMemory.h
// Module		: gzBase
// Description	: Class definition of memory allocation utilities
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
// AMO	980915	Created file 	
//
//******************************************************************************

#ifndef __GZ_MEMORY_H__
#define __GZ_MEMORY_H__

/*!	\file 
	\brief Memory management utilites 
*/

#include "gzBasicTypes.h"
#include "gzArgument.h"

//-------------------------- turn of mem debug for this header -------------------

#ifdef GZ_MEM_DEBUG
#undef new
#undef gz_malloc
#endif

//******************************************************************************
// Class	: gzMemoryManagerInterface
//									
// Purpose  : Memory manager interface
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created 
//									
//******************************************************************************
//! Base class for all Gizmo3D memory managed classes
class gzMemoryManagerInterface
{
public:

	GZ_BASE_EXPORT virtual gzVoid *malloc(size_t size)=0;
	GZ_BASE_EXPORT virtual gzVoid *calloc(size_t num,size_t size)=0;
	GZ_BASE_EXPORT virtual gzVoid free(gzVoid *address)=0;
	GZ_BASE_EXPORT virtual gzVoid *realloc(gzVoid *address,size_t size)=0;
};

//******************************************************************************
// Struct	: gzMemInfoItem
//									
// Purpose  : Hold memory allocation info
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	031120	Created 
//									
//******************************************************************************
struct gzMemInfoItem
{
	gzMemPointer	address;
	gzMemSize		size;
	char			*info;
	gzUInt32		pid;
	gzUInt32		counter;
	gzUInt32		state;
	gzUInt32		delta;
};


//! Default memory state for each thread.
constexpr gzUInt32 GZ_MEM_DEFAULT_STATE = 1;

//! Internal used by GizmoSDK utilities
constexpr gzUInt32 GZ_MEM_INTERNAL_STATE = 99999;

//******************************************************************************
// Class	: gzSharedMemory
//									
// Purpose  : Memory allocator from one shared pool
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created 
//									
//******************************************************************************
//! Base class for all Gizmo3D memory managed classes
/*!
The Gizmo3D toolkit uses a separate management of memory. It can automatically lock memory segments
between threads. It can also perform memory caching to store (serialise) certain parts of memory that is not used.

You should always try to use gzSharedMemory or any other gizmo derivative of gzSharedMemory to ensure proper memory allocation.

  e.g.

\code

class MyClass : public gzSharedMemory
{
};

\endcode

  or

\code

class MyRefClass : public gzReference	// Already derived from gzSharedMemory
{
};
\endcode
*/
class GZ_BASE_EXPORT gzSharedMemory 
{
public:

#ifndef GZ_DISABLE_MEMORY_NEW_HANDLER

	void * operator new(size_t size) ;
	void * operator new(size_t /*size*/, void* placement) { return placement; }

	void operator delete(void * address);
    void operator delete(void * /*address*/, void* /*placement*/) {}

#ifndef GZ_NO_DEBUG_MEM

	void * operator new(size_t size,const char *info) ;

	void operator delete(void *address,const char *info);

#endif // GZ_NO_DEBUG_MEM

	void * operator new[](size_t size) ;

	void operator delete[](void *address);

#ifndef GZ_NO_DEBUG_MEM

	void * operator new[](size_t size,const char *info) ;

	void operator delete[](void *address,const char *info);

#endif // GZ_NO_DEBUG_MEM

#endif // GZ_DISABLE_MEMORY_NEW_HANDLER

};


class GZ_BASE_EXPORT gzMemoryControl
{
public:

	//! Enable direct trace output for each mem allocation.
	/*! Use in combination with GZ_MEM_DEBUG. Remeber to have the correct message level output to GZ_MEM_DEBUG */
	static gzVoid	traceAlloc(gzBool on);

	//! Enables memory debugging and traces even if not compiled with GZ_MEM_DEBUG
	//! On by default when using GZ_ENABLE_NEW_HANDLER
	static gzVoid	debugMem(gzBool on);

	//! Reset all allocated debug memory
	static gzVoid	resetDebugMem(gzUInt32 state=0,gzUInt32 pid=0,gzBool resetInternalGizmoMem=FALSE);

	//! Dumps current allocated memory.
	/*! Use in combination with GZ_MEM_DEBUG. Remeber to have the correct message level output to GZ_MEM_DEBUG */
	static gzVoid	dumpAllocMem(gzBool deltaAlloc=TRUE,gzUInt32 state=0,gzUInt32 pid=0,gzBool dumpInternalGizmoMem=FALSE);

	//! update state var to state or increase it if state==0
	/*! By using state values for various allocation situations you can trace and dump only a subset of all allocations.
	E.g. if you wish to trace a certain function. Just set the state to a specific number when entering the function and 
	reset it to the old value as you exit. This will enable you to trace all allocations made during that function fo all threads */
	static gzUInt32	updateState(gzUInt32 state=0,gzUInt32 pid=0);

	//! Get current state.
	static gzUInt32  getState(gzUInt32 pid=0);

	//! Get number of bytes that is allocated and traced in use
	static gzUInt64	getAllocMem(gzUInt32 state=0,gzUInt32 pid=0, gzBool user_memory=TRUE, gzBool internal_memory=FALSE,gzBool deltaAlloc=FALSE);

	//! Cleanup of allocated memory
	static gzVoid	cleanAllocMem();

	//! If you wish a excel format for you trace info
	static gzVoid	useFormatOutput(gzBool on);

	//! If you wish to add info to the mem output
	static gzVoid	memprintf(gzBool trace,const char *fmt , ARG_DECL_LIST );

	static gzVoid	setMemoryManager(gzMemoryManagerInterface *manager);

	static inline	gzMemoryManagerInterface *getMemoryManagerInterface() { return s_currentMemoryManager; }

	static gzUInt32 getMemInfo(gzMemInfoItem *buffer,gzUInt32 maxBufferItems);

	static gzUInt64 getAvailableMemory(gzBool free=TRUE);

private:

	static gzMemoryManagerInterface *s_currentMemoryManager;
};

#define PUSH_INTERNAL_MEM_STATE(x)	gzUInt32 state_##x=gzMemoryControl::updateState(GZ_MEM_INTERNAL_STATE)
#define POP_INTERNAL_MEM_STATE(x)	gzMemoryControl::updateState(state_##x)

//************** Memory  Allocation utilities **********************************

extern "C"	// C functions
{
GZ_BASE_EXPORT gzVoid *gz_malloc(size_t size);
GZ_BASE_EXPORT gzVoid *gz_calloc(size_t size);
GZ_BASE_EXPORT gzVoid gz_free(gzVoid *address);
}

GZ_BASE_EXPORT gzVoid *gz_malloc(size_t size,const char *info);
GZ_BASE_EXPORT gzVoid *gz_calloc(size_t size,const char *info);

GZ_BASE_EXPORT gzVoid	*gz_malloc_aligned(size_t size,gzUInt32 align_size);
GZ_BASE_EXPORT gzVoid	*gz_malloc_aligned(size_t size,gzUInt32 align_size,const char *info);

GZ_BASE_EXPORT gzVoid	gz_free_aligned(gzVoid *address);
GZ_BASE_EXPORT gzUInt32	gz_get_alignment(gzVoid *address);



#define GZ_ALLOC_TEST(x) if(!(x)) { gzMemoryControl::memprintf(FALSE,"Bad Alloc:%s", GZ_DEBUG_INFO(GZ_VERSION_STR));throw std::bad_alloc();}


//******************************************************************************
// Class	: gzMemoryCheck
//									
// Purpose  : Checks to see if memeory is valid (allocated)
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	010720	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzMemoryCheck 
{
public:

	gzMemoryCheck();

	virtual ~gzMemoryCheck();

	gzBool isValidMemory();

private:

	gzUInt32	m_isValid;
};

//******************************************************************************
// Class	: gzQuadWordAlignedMemory
//									
// Purpose  : Aligns data to Quad Words suitable for 128 bit registers access
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	090119	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzQuadWordAlignedMemory 
{
public:

	void * operator new(size_t size) ;
    void * operator new(size_t /*size*/, void* placement) { return placement; }

	void operator delete(void *address);
    void operator delete(void* /*address*/, void* /*placement*/) {}

#ifndef GZ_NO_DEBUG_MEM

	void * operator new(size_t size,const char *info) ;

	void operator delete(void *address,const char *info);

#endif // GZ_NO_DEBUG_MEM


	void * operator new[](size_t size) ;

	void operator delete[](void *address);

#ifndef GZ_NO_DEBUG_MEM

	void * operator new[](size_t size,const char *info) ;

	void operator delete[](void *address,const char *info);

#endif // GZ_NO_DEBUG_MEM

};

//******************************************************************************
// Class	: gzQuadWordAligned
//									
// Purpose  : Template for Quad Word Alignment
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	090119	Created 
//									
//******************************************************************************
template <class T> class gzQuadWordAligned : public gzQuadWordAlignedMemory
{
public:

	inline gzQuadWordAligned():data(0) {};

	inline gzQuadWordAligned(const gzQuadWordAligned& right):data(right.data) {};

	inline gzQuadWordAligned(const T& right):data(right) {};

	inline gzQuadWordAligned& operator=(const gzQuadWordAligned& right) { data = right.data; return *this; }

	inline gzQuadWordAligned& operator=(const T& right) { data = right; return *this; }


	inline operator T & () { return data; }
	
	inline operator const T & () const { return data; }
	
	inline T * operator & () { return &data; }

	T	data;
};

typedef gzQuadWordAligned<gzUByte>	gzQWA_UByte;
typedef gzQuadWordAligned<gzUInt16>	gzQWA_UInt16;
typedef gzQuadWordAligned<gzUInt32>	gzQWA_UInt32;

typedef gzQuadWordAligned<gzByte>	gzQWA_Byte;
typedef gzQuadWordAligned<gzInt16>	gzQWA_Int16;
typedef gzQuadWordAligned<gzInt32>	gzQWA_Int32;

typedef gzQuadWordAligned<gzFloat>	gzQWA_Float;

class gzMutex;	// Forward decl
class gzString;	// The same

//******************************************************************************
// Function	: gzMemOptimizer
//									
// Purpose  : Generic accelleration of memory allocations
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011204	Created release 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzMemOptimizer
{
public:
	gzMemOptimizer(gzUInt32 slots , gzUInt32 byteSize,const char *name=nullptr,gzBool enable=FALSE);
	
	virtual ~gzMemOptimizer();

	gzBool tryResize(gzUInt32 slots);
	
	gzVoid *malloc(size_t size);
	
	gzVoid free(gzVoid *adress);
	
	gzBool isManaged(gzVoid *adress);
	
	gzVoid disable(gzBool force=FALSE);
	
	gzVoid enable();

	gzVoid setReportPercentage(gzUInt32 perc=10);
	
private:

	gzVoid enable_unsafe();

	gzUByte			*m_pMemOptimArray;

	gzMemPointer	*m_pMemOptimFreeStackIndex;

	gzUInt32		m_isInitialized;

	gzUInt32		m_stackPos;

	gzMutex			*m_locker;

	gzUInt32		m_byteSize;

	gzUInt32		m_slots;

	gzMemPointer	m_pOptimMemEnd;

	gzString		*m_name;

	gzUInt32		m_allocCount;

	gzUInt32		m_lastPerc;

	gzUInt32		m_repPerc;
};


//****************** MemBase custom allocations *********************************

#ifndef GZ_MEM_DEBUG	// In mem debug we don't want allocations to be private

#define GZ_MEMBASE(className) gzMemBaseAlloc_##className

#define GZ_MEMBASE_IMP(className) 	void * operator new(size_t size) 	\
{																						\
	return s_allocator_##className.malloc(size);										\
}																						\
																						\
void operator delete(void *address)														\
{																						\
	s_allocator_##className.free(address);												\
}


#define GZ_DECLARE_MEMBASE(className) class GZ_MEMBASE(className)			\
{																			\
public:																		\
	GZ_MEMBASE_IMP(className)												\
	static gzMemOptimizer	s_allocator_##className;						\
};

#define GZ_DECLARE_MEMBASE_EXPORT(className,export) class GZ_MEMBASE(className)		\
{																					\
public:																				\
	GZ_MEMBASE_IMP(className)														\
	export static gzMemOptimizer	s_allocator_##className;						\
};

#define GZ_DECLARE_MEMBASE_IMP(className,size) gzMemOptimizer GZ_MEMBASE(className)::s_allocator_##className(size,sizeof(className),#className,TRUE)

#else // GZ_MEM_DEBUG - no active allocators

class gzDummyMem {}; // Empty class as base to MEMBASE

#define GZ_MEMBASE(className) gzDummyMem
#define GZ_MEMBASE_IMP(className) 
#define GZ_DECLARE_MEMBASE(className)
#define GZ_DECLARE_MEMBASE_EXPORT(className,export)
#define GZ_DECLARE_MEMBASE_IMP(className,size) 

#endif // GZ_MEM_DEBUG

//--------------------- redefine memory debug info -----------------

#ifdef GZ_MEM_DEBUG
#ifndef GZ_NO_DEBUG_MEM
#define new new (GZ_DEBUG_INFO(GZ_VERSION_STR))
#define gz_malloc(arg) gz_malloc(arg,GZ_DEBUG_INFO(GZ_VERSION_STR))
#endif
#endif

#endif

