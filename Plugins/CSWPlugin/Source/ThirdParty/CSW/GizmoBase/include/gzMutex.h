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
// File			: gzMutex.h
// Module		: gzBase
// Description	: Class definition of mutex functionality
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.201
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
// AMO	100120	Added gzCleanupReference for global singleton release
// AMO	120531	Added gzRecursiveBodyGuard							(2.6.6)
// AMO	241018	Updated levels in gzCleanupReferences				(2.12.192)
// AMO	241024	Fixed bug in gzReadWrite unlock for temp write		(2.12.194)
//
//******************************************************************************
#ifndef __GZ_MUTEX_H__
#define __GZ_MUTEX_H__

/*!	\file 
	\brief Mutex functionality for \b Gizmo3D

	The Mutex class is vital for multithread applications. If you use gzThread you must
	remember to protect your data with gzMutex or gzGuard
*/

#include "gzBasicTypes.h"
#include "gzDebug.h"
#include "gzMemory.h"
#include "gzReference.h"

// --------------------------- Sleep definitions. Always wait in milliseconds ---------------
// 
//! Sleep time for one second
const gzUInt32 GZ_SLEEP_SECOND = 1000;

//! Infinite sleep time
const gzUInt32 GZ_SLEEP_INFINITE = 0xFFFFFFFFUL;

// -----------------------------------------------------------------------------------------

#if defined GZ_WINDOWS
// --------------------------------  GZ_WINDOWS ----------------------------

	#include "windows.h"

	typedef CRITICAL_SECTION	gzSyncType;
	typedef CONDITION_VARIABLE	gzConditionType;

#elif defined GZ_UNIX 
// --------------------------------  UNIX ----------------------------------

	//#if defined GZ_MAC 				// Can not yet handle recursive mutexes
	//	#define NON_RECURSIVE_MUTEX
	//#endif

	#include "pthread.h"
	#include "sys/errno.h"

	typedef pthread_mutex_t gzSyncType;
	typedef pthread_cond_t	gzConditionType;


#endif


//******************************************************************************
// Class	: gzMutex
//									
// Purpose  : Lock and Unlock utils for mutexes
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
class  GZ_BASE_EXPORT gzMutex
{
public:
		
	gzMutex(gzBool useThreadID=TRUE);
	gzMutex(const gzMutex &copy);
	gzMutex & operator=(const gzMutex &copy);

	virtual ~gzMutex();

	gzVoid	waitLock() const;
    gzBool	tryLock() const;
    gzVoid	unLock() const;
	gzBool	isLocked() const;

	gzUInt32 getOwnerThreadID() const;

	gzUInt32 getSpinLockCount() const;

private:

	friend class gzEvent;

	gzSyncType		m_lock;

	gzUInt32		m_threadID;

	gzUInt32		m_spinLock;

	gzBool			m_useThreadID;
};

//******************************************************************************
// Class	: gzGuard
//									
// Purpose  : Guards a primitive with a mutex
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981101	Created 
//									
//******************************************************************************
template <class T> class gzGuard : public gzMutex
{
public:
	
	gzGuard(){};

	gzGuard(const T& data):m_data(data){};

	operator T&()	{ return (T &)m_data; }	

	T& get()		{ return (T &)m_data; }

	T& operator=( const T& data ){ m_data=data; return m_data; }

private:

	T m_data;
};

//******************************************************************************
// Class	: gzClassGuard
//									
// Purpose  : Guards a class
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011101	Created 
//									
//******************************************************************************
template <class T> class gzClassGuard : public T , public gzMutex
{
public:
	
	gzClassGuard(){};

	virtual ~gzClassGuard(){};

	gzClassGuard(const T& data):T(data){};
};

//******************************************************************************
// Class	: gzBodyGuard
//									
// Purpose  : Auto guard. Use to protect methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011101	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzBodyGuard 
{
public:
	gzBodyGuard(const gzMutex &guard):m_guard(&guard)	{ m_guard->waitLock(); }

	virtual ~gzBodyGuard()								{ m_guard->unLock(); }

	GZ_NO_IMPLICITS(gzBodyGuard);

private:

	const gzMutex *m_guard;
};

#define GZ_BODYGUARD	gzBodyGuard	CONCAT(_guard_,__LINE__)
#define GZ_SYNCRONIZED  static gzMutex _mutex_;gzBodyGuard	_sync_guard_(_mutex_);


//******************************************************************************
// Class	: gzTryGuard
//									
// Purpose  : Auto guard using try. Use to protect methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	230201	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzTryGuard
{
public:
	gzTryGuard(const gzMutex& guard) :m_guard(&guard),m_locked(FALSE) {}

	gzBool tryLock() { if (m_locked)return TRUE; m_locked = m_guard->tryLock(); return m_locked; }

	virtual ~gzTryGuard() { if(m_locked)m_guard->unLock(); }

	GZ_NO_IMPLICITS(gzTryGuard);

private:

	const gzMutex*	m_guard;
	gzBool			m_locked;
};

//******************************************************************************
// Class	: gzBodyGuardPause
//									
// Purpose  : Pause Auto guard. Use to protect methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	200326	Created (2.10.5)
//									
//******************************************************************************
class GZ_BASE_EXPORT gzBodyGuardPause
{
public:
	gzBodyGuardPause(const gzMutex& guard) :m_guard(&guard) { m_guard->unLock(); }

	virtual ~gzBodyGuardPause() { m_guard->waitLock(); }

private:	// Do not allow copy or assignments

	gzBodyGuardPause(const gzBodyGuardPause& /*copy*/) :m_guard(NULL) {}

	gzBodyGuardPause& operator=(const gzBodyGuardPause& /*copy*/) { return *this; }

private:

	const gzMutex* m_guard;
};

#define GZ_BODYGUARD_PAUSE	gzBodyGuardPause	CONCAT(_guard_pause_,__LINE__)

//******************************************************************************
// Class	: gzRefBodyGuard
//									
// Purpose  : Auto guard. Use to protect methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	200207	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzRefBodyGuard : public gzReference
{
public:
	gzRefBodyGuard(const gzMutex &guard) :m_guard(&guard) { m_guard->waitLock(); }

	virtual ~gzRefBodyGuard() { m_guard->unLock(); }

private:	// Do not allow copy or assignments

	gzRefBodyGuard(const gzBodyGuard & /*copy*/) :m_guard(NULL) {}

	gzRefBodyGuard & operator=(const gzBodyGuard & /*copy*/) { return *this; }

private:

	const gzMutex *m_guard;
};

GZ_DECLARE_REFPTR(gzRefBodyGuard);

#define GZ_REF_BODYGUARD	gzRefBodyGuard

//******************************************************************************
// Class	: gzAutoGuard
//									
// Purpose  : Guards a primitive with a mutex automatically
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	140514	Created 
//									
//******************************************************************************
template <class T> class gzAutoGuard : public gzMutex
{
public:
	
	gzAutoGuard(){};

	gzAutoGuard(const T& data)	{ GZ_BODYGUARD(*this);m_data=data;}

	operator T&()				{ GZ_BODYGUARD(*this);return (T &)m_data; }	

	T& get()					{ GZ_BODYGUARD(*this);return (T &)m_data; }

	T& operator=( const T& data ){ GZ_BODYGUARD(*this);m_data=data; return m_data; }

private:

	T m_data;
};

//******************************************************************************
// Class	: gzRecursiveBodyGuard
//									
// Purpose  : Auto recursive guard. Use to protect recursive methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	120531	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzRecursiveBodyGuard 
{
public:
	gzRecursiveBodyGuard(volatile gzUInt32 &guardCount):m_guardCount(guardCount)	
	{ 
		m_guardCount++; 
	}

	virtual ~gzRecursiveBodyGuard()
	{ 
		if(m_guardCount)
			m_guardCount--; 
		else
			GZMESSAGE(GZ_MESSAGE_WARNING,"RECURSIVE MISMATCH ! Left recursion with zero recursion count.");
	}

	gzUInt32 getRecursionDepth()
	{
		return m_guardCount;
	}

private:	// Do not allow copy or assignments

	gzRecursiveBodyGuard( const gzRecursiveBodyGuard & copy ):m_guardCount(copy.m_guardCount){}

	gzRecursiveBodyGuard & operator=(const gzRecursiveBodyGuard & /*copy*/ ){ return *this; }

private:

	volatile gzUInt32 &m_guardCount;
};

//! Use as an if statement. Add lines below to execute when recursion depth is too large. (GT>level) e.g. a return
#define GZ_RECURSIVE_GUARD(level)			static gzUInt32 _recursive_guard_count_=0; gzRecursiveBodyGuard _recursive_guard_(_recursive_guard_count_); if(_recursive_guard_.getRecursionDepth()>level)

//! Use as if statement. Add level and global counter. executes if counter is GT level
#define GZ_RECURSIVE_GUARD_GT(level,counter)	gzRecursiveBodyGuard _recursive_guard_(counter); if(_recursive_guard_.getRecursionDepth()>level)

//! Use as if statement. Add level and global counter. executes if counter is LTE level
#define GZ_RECURSIVE_GUARD_LTE(level,counter)	gzRecursiveBodyGuard _recursive_guard_(counter); if(_recursive_guard_.getRecursionDepth()<=level)

// ------------- Threadsafe ref macro definitions --------------------------------

#define GZ_THREADSAFE_REF(_MUTEX_)					\
													\
	virtual gzVoid	ref()  override					\
	{												\
		_MUTEX_.waitLock();							\
													\
		gzReference::ref();							\
													\
		_MUTEX_.unLock();							\
	}												\
													\
    virtual gzVoid	unref() override				\
	{												\
		_MUTEX_.waitLock();							\
													\
		gzUInt32 retval(gzReference::unrefNoDelete());\
													\
		_MUTEX_.unLock();							\
													\
		if(!retval)									\
			checkDelete();							\
	}												\
													\
    virtual gzUInt32	unrefNoDelete() override	\
	{												\
		_MUTEX_.waitLock();							\
													\
		gzUInt32 retval(gzReference::unrefNoDelete());\
													\
		_MUTEX_.unLock();							\
													\
		return retval;								\
	}												\
													\
	virtual gzBool	checkDelete() override			\
	{												\
		_MUTEX_.waitLock();							\
													\
		if(!_refCount)								\
		{											\
			_MUTEX_.unLock();						\
													\
			delete this;							\
													\
			return TRUE;							\
		}											\
													\
		_MUTEX_.unLock();							\
													\
		return FALSE;								\
	}												\
													\
    virtual gzUInt32	getRef() const override		\
	{												\
		_MUTEX_.waitLock();							\
													\
		gzUInt32 retval(gzReference::getRef());		\
													\
		_MUTEX_.unLock();							\
													\
		return retval;								\
	}												

//******************************************************************************
// Class	: gzThreadSafeReference
//									
// Purpose  : Thread safe reference class
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030305	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzThreadSafeReference : public gzReference 
{
public:

    GZ_THREADSAFE_REF(m_threadSafeLocker);

protected:

	mutable gzMutex	m_threadSafeLocker;
};

//******************************************************************************
// Class	: gzEvent
//									
// Purpose  : A waitable event that can trigger thread execution.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	020402	Created 
// AMO	180704	multiple wait to gzEvent				(2.9.1)
//									
//******************************************************************************
//! A waitable event that can trigger thread execution.
class GZ_BASE_EXPORT gzEvent : public gzReference , public gzMutex
{
public:

	GZ_THREADSAFE_REF((*(gzMutex *)this));

	//! Construction
	gzEvent();

	//! Destruction
	virtual ~gzEvent();

	//! Fire the event.
	/*!
		All threads currently waiting will be released.
	*/
	gzVoid fire();

	gzVoid fireOnlyOne();

	//! Wait for the event to be fired.
	/*!	
		\return TRUE if event was fired.
		\return FALSE if timeout occurred.
	*/
	gzBool wait(gzUInt32 timeout=GZ_SLEEP_INFINITE,gzBool alreadyLockedMutex=FALSE,gzBool return_if_signaled=FALSE);

	//! Wait for events and keep event locked
	gzBool waitAndLock(gzUInt32 timeout = GZ_SLEEP_INFINITE,gzBool alreadyLockedMutex=FALSE, gzBool return_if_signaled = FALSE) ;

	gzBool waitSignaled(gzUInt32 timeout = GZ_SLEEP_INFINITE, gzBool alreadyLockedMutex = FALSE);

	//! Wait for events and keep event locked
	gzBool waitAndLockSignaled(gzUInt32 timeout = GZ_SLEEP_INFINITE, gzBool alreadyLockedMutex = FALSE);


	static gzEvent *wait(const gzRefList<gzEvent> &list, gzUInt32 timeout= GZ_SLEEP_INFINITE);

	//! Signaled states set by fire
	gzVoid set();
	gzVoid reset();

	gzBool isSignalSet() const;

private:

	gzConditionType		m_condition;

	gzBool				m_signaled;
};

GZ_DECLARE_REFPTR(gzEvent);

//******************************************************************************
// Class	: gzEventGuard
//									
// Purpose  : Auto guard. Use to protect methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	241011	Created	gzEventGuard	(2.12.191)
//									
//******************************************************************************
class GZ_BASE_EXPORT gzEventGuard
{
public:
	gzEventGuard(gzEvent& guard, gzUInt32 timeout = GZ_SLEEP_INFINITE, gzBool alreadyLockedMutex = FALSE, gzBool return_if_signaled = FALSE) :m_guard(&guard) { m_guard->waitAndLock(timeout, alreadyLockedMutex, return_if_signaled); }

	virtual ~gzEventGuard() { m_guard->unLock(); }

	GZ_NO_IMPLICITS(gzEventGuard);

private:

	gzEvent* m_guard;
};

#define GZ_EVENTGUARD	gzEventGuard	CONCAT(_guard_,__LINE__)

//******************************************************************************
// Class	: gzSignalGuard
//									
// Purpose  : Auto guard. Use to protect methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	241011	Created	gzSignalGuard					(2.12.191)
//									
//******************************************************************************
class GZ_BASE_EXPORT gzSignalGuard
{
public:
	gzSignalGuard(gzEvent& guard, gzUInt32 timeout = GZ_SLEEP_INFINITE, gzBool alreadyLockedMutex = FALSE) :m_guard(&guard) { m_result=m_guard->waitAndLockSignaled(timeout, alreadyLockedMutex); m_guard->reset(); }

	virtual ~gzSignalGuard() { m_guard->unLock(); }

	gzBool result() { return m_result; }

	GZ_NO_IMPLICITS(gzSignalGuard);

private:

	gzEvent* m_guard;
	gzBool	 m_result;
};

#define GZ_SIGNALGUARD	gzSignalGuard	CONCAT(_guard_,__LINE__)

//******************************************************************************
// Class	: gzSemaphore
//									
// Purpose  : -
//									
// Notes	: Used to allow muliple locks per value (mode)	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981101	Created 
// AMO	221130	Added changeValue()							(2.12.35)
//									
//******************************************************************************
class GZ_BASE_EXPORT gzSemaphore
{
public:

	gzSemaphore(gzUInt32 currentValue=0,gzUInt32 currentCount=0,gzUInt32 maxCount=0);

	virtual ~gzSemaphore();

	gzVoid waitLock(gzUInt32 value) const;
	
	gzBool tryLock(gzUInt32 value,gzUInt32 waitValue=10) const;

	gzUInt32 setMaxLockCount(gzUInt32 maxCount);

    gzVoid unLock() const;

	gzUInt32 getValue() const;

	//! Get number of recursive locks
	gzUInt32 getSpinLockCount() const;

	//! allow the user to change value if there is only one owner and one lock
	gzBool changeValue(gzUInt32 value) const;

private:

	gzMutex				m_valueLock;;

	gzUInt32			m_maxCount;
	mutable gzUInt32	m_currentValue;
	mutable gzUInt32	m_counter;
	mutable gzEvent		m_waiter;
};

#define GZ_SEMA_READ			(0)
#define GZ_SEMA_SHARED_WRITE	(1)
#define GZ_SEMA_WRITE			(gzThread::getThreadID())

//******************************************************************************
// Class	: gzInstanceLockItem
//									
// Purpose  : -
//									
// Notes	: Item used to lock an instance (adress)	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	210421	Created		(2.10.20)
//									
//******************************************************************************
class GZ_BASE_EXPORT gzInstanceLockItem : public gzThreadSafeReference, public gzMutex
{
public:

	gzInstanceLockItem() : lockCount(0) {}

	gzUInt32 lockCount;
};

GZ_DECLARE_REFPTR(gzInstanceLockItem);

//******************************************************************************
// Class	: gzInstanceLock
//									
// Purpose  : -
//									
// Notes	: Used to lock an instance (adress)	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	210421	Created		(2.10.20)
//									
//******************************************************************************
class gzInstanceLock : public gzMutex
{
public:

	GZ_BASE_EXPORT	gzInstanceLock();

	GZ_BASE_EXPORT	virtual ~gzInstanceLock();

	GZ_BASE_EXPORT	gzVoid waitLock(gzVoid* instance);

	GZ_BASE_EXPORT	gzVoid unLock(gzVoid* instance);

protected:

	GZ_BASE_EXPORT	gzVoid getOrAddItem(gzVoid* instance, gzInstanceLockItemPtr& item);

	GZ_BASE_EXPORT	gzVoid removeItem(gzVoid* instance, gzInstanceLockItemPtr& item);

private:

	gzRefDict<gzInstanceCompareInterface, gzInstanceLockItem>	m_dict;
};




//******************************************************************************
// Class	: gzReadWriteMutex
//									
// Purpose  : This mutex allows many readers but only one writer at the same time
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// CAN	090503	Created 
// AMO	160113	Modified
//									
//******************************************************************************
class gzReadWriteMutex : public gzSemaphore
{
public:
	GZ_BASE_EXPORT gzVoid waitLockRead() const;

	GZ_BASE_EXPORT gzVoid waitLockWrite() const;

	GZ_BASE_EXPORT gzVoid waitLockSharedWrite() const;

	GZ_BASE_EXPORT gzBool tryLockRead() const;

	GZ_BASE_EXPORT gzBool tryLockWrite() const;

	GZ_BASE_EXPORT gzBool tryLockSharedWrite() const;
};

//******************************************************************************
// Class	: gzBodyWriteGuard
//									
// Purpose  : Auto guard. Use to protect methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011101	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzBodyWriteGuard 
{
public:
	gzBodyWriteGuard(const gzReadWriteMutex &guard):m_guard(&guard)	{ m_guard->waitLockWrite(); }

	virtual ~gzBodyWriteGuard()										{ m_guard->unLock(); }

private:	// Do not allow copy or assignments

	gzBodyWriteGuard( const gzBodyWriteGuard & /*copy*/ ):m_guard(NULL){}

	gzBodyWriteGuard & operator=(const gzBodyWriteGuard & /*copy*/ ){ return *this; }

private:

	const gzReadWriteMutex *m_guard;
};

#define GZ_BODY_WRITE_GUARD	gzBodyWriteGuard	_write_guard_

//******************************************************************************
// Class	: gzBodySharedWriteGuard
//									
// Purpose  : Auto guard. Use to protect methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011101	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzBodySharedWriteGuard 
{
public:
	gzBodySharedWriteGuard(const gzReadWriteMutex &guard):m_guard(&guard)	{ m_guard->waitLockSharedWrite(); }

	virtual ~gzBodySharedWriteGuard()										{ m_guard->unLock(); }

private:	// Do not allow copy or assignments

	gzBodySharedWriteGuard( const gzBodySharedWriteGuard & /*copy*/ ):m_guard(NULL){}

	gzBodySharedWriteGuard & operator=(const gzBodySharedWriteGuard & /*copy*/ ){ return *this; }

private:

	const gzReadWriteMutex *m_guard;
};

#define GZ_BODY_SHARED_WRITE_GUARD	gzBodySharedWriteGuard	_shared_write_guard_

//******************************************************************************
// Class	: gzBodyReadGuard
//									
// Purpose  : Auto guard. Use to protect methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011101	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzBodyReadGuard 
{
public:
	gzBodyReadGuard(const gzReadWriteMutex &guard):m_guard(&guard)	{ m_guard->waitLockRead(); }

	virtual ~gzBodyReadGuard()										{ m_guard->unLock(); }

private:	// Do not allow copy or assignments

	gzBodyReadGuard( const gzBodyReadGuard & /*copy*/ ):m_guard(NULL){}

	gzBodyReadGuard & operator=(const gzBodyReadGuard & /*copy*/ ){ return *this; }

private:

	const gzReadWriteMutex *m_guard;
};

#define GZ_BODY_READ_GUARD	gzBodyReadGuard	_read_guard_

//******************************************************************************
// Class	: gzBodyReadGuardPause
//									
// Purpose  : Auto guard. Use to protect methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	240307	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzBodyReadGuardPause
{
public:
	gzBodyReadGuardPause(const gzReadWriteMutex& guard) :m_guard(&guard) { m_guard->unLock(); }

	virtual ~gzBodyReadGuardPause() { m_guard->waitLockRead(); }

private:	// Do not allow copy or assignments

	gzBodyReadGuardPause(const gzBodyReadGuardPause& /*copy*/) :m_guard(NULL) {}

	gzBodyReadGuardPause& operator=(const gzBodyReadGuardPause& /*copy*/) { return *this; }

private:

	const gzReadWriteMutex* m_guard;
};

#define GZ_BODY_READ_GUARD_PAUSE	gzBodyReadGuardPause	_read_guard_pause_

//******************************************************************************
// Class	: gzBodyReadGuardDoWrite
//									
// Purpose  : Auto guard. Use to protect methods
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	240307	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzBodyReadGuardDoWrite
{
public:
	gzBodyReadGuardDoWrite(const gzReadWriteMutex& guard) :m_guard(&guard)
	{ 
		m_guard->unLock();		// NOTE: that this can deadlock if you have multiple levels of readlocks

		m_guard->waitLockWrite(); 
	}

	virtual ~gzBodyReadGuardDoWrite() 
	{ 
		m_guard->unLock(); 
		
		m_guard->waitLockRead();
	}

private:	// Do not allow copy or assignments

	GZ_NO_IMPLICITS(gzBodyReadGuardDoWrite);

private:

	const gzReadWriteMutex* m_guard;
};

#define GZ_BODY_READ_GUARD_DO_WRITE	gzBodyReadGuardDoWrite	_read_guard_do_write_

//******************************************************************************
// Class	: gzAutoReadWriteGuard
//									
// Purpose  : Guards a primitive with a mutex automatically
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	140514	Created 
//									
//******************************************************************************
template <class T> class gzAutoReadWriteGuard : public gzReadWriteMutex
{
public:
	
	gzAutoReadWriteGuard(){};

	gzAutoReadWriteGuard(const T& data)	{ GZ_BODY_WRITE_GUARD(*this);m_data=data;}

	operator T&()						{ GZ_BODY_READ_GUARD(*this);return (T &)m_data; }	

	T& get()							{ GZ_BODY_READ_GUARD(*this);return (T &)m_data; }

	T& operator=( const T& data )		{ GZ_BODY_WRITE_GUARD(*this);m_data=data; return m_data; }

private:

	T m_data;
};

//******************************************************************************
// Class	: gzAutoSharedReadWriteGuard
//									
// Purpose  : Guards a primitive with a mutex automatically
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	140514	Created 
//									
//******************************************************************************
template <class T> class gzAutoSharedReadWriteGuard : public gzReadWriteMutex
{
public:
	
	gzAutoSharedReadWriteGuard(){};

	gzAutoSharedReadWriteGuard(const T& data)	{ GZ_BODY_WRITE_GUARD(*this);m_data=data;}

	operator T&()								{ GZ_BODY_READ_GUARD(*this);return (T &)m_data; }	

	T& get()									{ GZ_BODY_READ_GUARD(*this);return (T &)m_data; }

	T& operator=( const T& data )				{ GZ_BODY_SHARED_WRITE_GUARD(*this);m_data=data; return m_data; }

private:

	T m_data;
};

//******************************************************************************
// Enum		: gzCleanupLevel
//									
// Purpose  : levels of cleanup
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	100120	Created 
//									
//******************************************************************************
enum gzCleanupLevel
{
	GZ_CLEANUP_ALL		=	-1,
	GZ_CLEANUP_BASE		=	0,
	GZ_CLEANUP_SYSTEM	=	1,
	GZ_CLEANUP_MEMORY	=	2,
	GZ_CLEANUP_MODULES	=	3,

	// Custom levels allowed
};

//******************************************************************************
// Class	: gzCleanupReference
//									
// Purpose  : static vars and cleanup
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	100120	Created 
//									
//******************************************************************************
class gzCleanupReference : public gzRefPointer<gzReference> 
{
public:

	GZ_BASE_EXPORT gzCleanupReference( gzReference *pointer=nullptr, gzCleanupLevel level = GZ_CLEANUP_BASE);

	GZ_BASE_EXPORT gzCleanupReference( const gzCleanupReference &copy);

	GZ_BASE_EXPORT gzCleanupReference &operator=(const gzCleanupReference &copy);

	GZ_BASE_EXPORT gzCleanupReference &operator=(gzReference *reference);
	
	GZ_BASE_EXPORT virtual ~gzCleanupReference();
	
	GZ_BASE_EXPORT static gzVoid cleanUpReferences(gzCleanupLevel level = GZ_CLEANUP_ALL);

private:

	static gzVoid checkInstance(gzBool lockMe);

	gzCleanupLevel						m_level;

	static gzList<gzCleanupReference>	*s_instances;
};

//******************************************************************************
// Class	: gzRecycleData && gzRecycleDataExport
//									
// Purpose  : Recycle data storage for faster access
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030305	Created 
//									
//******************************************************************************
#define GZ_DECLARE_RECYCLE_DATA_EXPORT(moduleName,exportDef)	template <class T> class gzRecycleData_##moduleName\
{																					\
public:																				\
																					\
	gzRecycleData_##moduleName()													\
	{																				\
		s_recycleDataLock.waitLock();												\
																					\
		if(!s_cleanUp.get())														\
			s_cleanUp=new gzRecycleCleanup();										\
																					\
		if(s_recycleData.first())													\
		{																			\
			m_data=s_recycleData.first();											\
																					\
			s_recycleData.removeFirst();											\
																					\
			m_needNew=FALSE;														\
																					\
		}																			\
		else																		\
		{																			\
			m_data=new gzRefData<T>;												\
																					\
			m_needNew=TRUE;															\
		}																			\
																					\
		m_needInit=TRUE;															\
																					\
		s_recycleDataLock.unLock();													\
	}																				\
																					\
	gzRecycleData_##moduleName(const T &copy)										\
	{																				\
		s_recycleDataLock.waitLock();												\
																					\
		if(!s_cleanUp.get())														\
			s_cleanUp=new gzRecycleCleanup();										\
																					\
		if(s_recycleData.first())													\
		{																			\
			m_data=s_recycleData.first();											\
																					\
			s_recycleData.removeFirst();											\
		}																			\
		else																		\
		{																			\
			m_data=new gzRefData<T>;												\
		}																			\
																					\
		m_needNew=FALSE;															\
		m_needInit=FALSE;															\
																					\
		*m_data.get()=copy;															\
																					\
		s_recycleDataLock.unLock();													\
	}																				\
																					\
	virtual ~gzRecycleData_##moduleName()											\
	{																				\
		s_recycleDataLock.waitLock();												\
																					\
		if(m_data && !m_needNew && s_enabled)										\
			if(s_recycleData.entries()<s_maxStorageCount)							\
				s_recycleData.pre_insert(m_data);									\
																					\
		m_data=nullptr;																\
																					\
		s_recycleDataLock.unLock();													\
	}																				\
																					\
	/* User defined callbacks */													\
	virtual gzVoid onNewItem(T & /*data*/)	const {};								\
	virtual gzVoid onInitItem(T & /*data*/)	const {};								\
																					\
	operator T &()																	\
	{																				\
		init();																		\
																					\
		return (T &)*m_data.get();													\
	}																				\
																					\
	operator const T &() const														\
	{																				\
		init();																		\
																					\
		return (T &)*m_data.get();													\
	}																				\
																					\
	T & getRecycledInstance()														\
	{																				\
		init();																		\
																					\
		return (T &)*m_data.get();													\
	}																				\
																					\
	const T & getConstRecycledInstance() const										\
	{																				\
		init();																		\
																					\
		return (const T &)*m_data.get();											\
	}																				\
																					\
	void dropRecycledInstance()														\
	{																				\
		m_data = NULL;																\
		m_needNew = TRUE;															\
		m_needInit = TRUE;															\
	}																				\
																					\
	gzVoid init() const																\
	{																				\
		if(m_needInit)																\
		{																			\
			m_needInit=FALSE;														\
																					\
			if(m_needNew)															\
			{																		\
				m_needNew=FALSE;													\
																					\
				if(!m_data)															\
					m_data = new gzRefData<T>;										\
																					\
				onNewItem(*m_data.get());											\
			}																		\
			onInitItem(*m_data.get());												\
		}																			\
	}																				\
																					\
	gzBool hasRecycledInstance() const												\
	{																				\
		return (m_data != NULL) && (!m_needNew);									\
	}																				\
																					\
	static gzVoid clearRecycledData()												\
	{																				\
		s_recycleDataLock.waitLock();												\
		s_recycleData.clear();														\
		s_recycleDataLock.unLock();													\
	}																				\
																					\
	gzRecycleData_##moduleName &operator=(const gzRecycleData_##moduleName &data)	\
	{																				\
		init();																		\
																					\
		data.init();																\
																					\
		((T &)*m_data.get())=((T &)*data.m_data.get());								\
																					\
		return *this;																\
	}																				\
																					\
	gzRecycleData_##moduleName(const gzRecycleData_##moduleName &data)				\
	{																				\
		s_recycleDataLock.waitLock();												\
																					\
		if(!s_cleanUp.get())														\
			s_cleanUp=new gzRecycleCleanup();										\
																					\
		if(s_recycleData.first())													\
		{																			\
			m_data=s_recycleData.first();											\
																					\
			s_recycleData.removeFirst();											\
																					\
		}																			\
		else																		\
		{																			\
			m_data=new gzRefData<T>;												\
		}																			\
																					\
		m_needInit=FALSE;															\
		m_needNew=FALSE;															\
																					\
		s_recycleDataLock.unLock();													\
																					\
																					\
		data.init();																\
																					\
		((T &)*m_data.get())=((T &)*data.m_data.get());								\
	}																				\
																					\
	T& operator=(const T &data)														\
	{																				\
		init();																		\
																					\
		((T &)*m_data.get())=data;													\
		return ((T &)*m_data.get());												\
	}																				\
																					\
	T * operator ->() const															\
	{																				\
		init();																		\
																					\
		return &((T &)*m_data.get());												\
	}																				\
																					\
	static gzVoid setMaxStorageCount(gzUInt32 count)								\
	{																				\
		s_recycleDataLock.waitLock();												\
		s_maxStorageCount=count;													\
		s_recycleDataLock.unLock();													\
	}																				\
																					\
  	static gzVoid enable()															\
	{																				\
		s_recycleDataLock.waitLock();												\
		s_enabled=TRUE;																\
		s_cleanUp=new gzRecycleCleanup();											\
		s_recycleDataLock.unLock();													\
	}																				\
																					\
  	static gzVoid disable()															\
	{																				\
		if(s_recycleDataLock.isValidMemory())										\
		{																			\
			s_recycleDataLock.waitLock();											\
			s_enabled=FALSE;														\
			s_recycleData.clear();													\
			s_cleanUp=nullptr;															\
			s_recycleDataLock.unLock();												\
		}																			\
	}																				\
																					\
	static gzVoid reuseLinks(gzBool on)												\
	{																				\
		s_recycleDataLock.waitLock();												\
		s_recycleData.reuseLinks(on);												\
		s_recycleDataLock.unLock();													\
	}																				\
																					\
private:																			\
																					\
	class gzRecycleCleanup : public gzReference										\
	{																				\
		public:																		\
																					\
		virtual ~gzRecycleCleanup()													\
		{																			\
			if(s_recycleDataLock.isValidMemory())									\
			{																		\
				s_recycleDataLock.waitLock();										\
				s_enabled=FALSE;													\
				s_recycleData.clear();												\
				s_recycleDataLock.unLock();											\
			}																		\
		}																			\
	};																				\
																					\
	mutable gzRefPointer<gzRefData<T> >	 m_data;									\
																					\
																					\
	mutable gzBool					m_needInit:1;									\
	mutable gzBool					m_needNew:1;									\
																					\
	exportDef static	gzBool						s_enabled;						\
	exportDef static	gzUInt32					s_maxStorageCount;				\
	exportDef static	gzMemCheck<gzMutex>			s_recycleDataLock;				\
	exportDef static	gzRefList<gzRefData<T> >	s_recycleData;					\
	exportDef static    gzCleanupReference			s_cleanUp;						\
};

#define GZ_DECLARE_RECYCLE_DATA_EXPORT_IMP(moduleName) template <class T> gzMemCheck<gzMutex> gzRecycleData_##moduleName<T>::s_recycleDataLock=gzMutex(FALSE); template <class T> gzRefList<gzRefData<T> > gzRecycleData_##moduleName<T>::s_recycleData=gzRefList<gzRefData<T> >(FALSE); template <class T> gzUInt32 gzRecycleData_##moduleName<T>::s_maxStorageCount=0xfffffffful; template <class T> gzBool gzRecycleData_##moduleName<T>::s_enabled=TRUE; template <class T> gzCleanupReference gzRecycleData_##moduleName<T>::s_cleanUp(NULL);

// Define the export naming module
#define gzRecycleDataExport(moduleName) gzRecycleData_##moduleName

// Define the standard gzBase gzRecycleData

#define COMMON_EXPORT	// Empty definition

GZ_DECLARE_RECYCLE_DATA_EXPORT(gzBase, COMMON_EXPORT);

#define gzRecycleData gzRecycleDataExport(gzBase)
#define GZ_DECLARE_RECYCLE_DATA_IMP	GZ_DECLARE_RECYCLE_DATA_EXPORT_IMP(gzBase)

//******************************************************************************
// Class	: gzDispatchLock(gzMutex& lock, gzUInt32& counter)
//									
// Purpose  : Lock Mechanism for dispatch for parallell access
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	220504	Created 
//									
//******************************************************************************
class gzDispatchLock
{
public:

	GZ_BASE_EXPORT gzDispatchLock(gzMutex& lock, gzUInt32& counter);

	GZ_BASE_EXPORT ~gzDispatchLock();

private:

	gzMutex& m_lock;
	gzUInt32& m_counter;
};

//! locks dispatch for guard lifetime but allows parellell lock
#define GZ_DISPATCHGUARD	gzDispatchLock	CONCAT(_guard_,__LINE__)

//******************************************************************************
// Class	: gzWaitDispatchLock(gzMutex& lock, gzUInt32& counter)
//									
// Purpose  : Wait function for dispatch lock until no more dispatch
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	220504	Created 
//									
//******************************************************************************
class gzWaitDispatchLock
{
public:

	//! max wait timoeout * 1/100 seconds
	GZ_BASE_EXPORT gzWaitDispatchLock(gzMutex& lock, gzUInt32& counter,const gzUInt32& timeout=500 );

	GZ_BASE_EXPORT ~gzWaitDispatchLock();

private:

	gzMutex& m_lock;
	gzUInt32& m_counter;
};

//! Exclusive lock for dispatch lock
#define GZ_WAIT_DISPATCHLOCK	gzWaitDispatchLock	CONCAT(_guard_,__LINE__)

#endif
