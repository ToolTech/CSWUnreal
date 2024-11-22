// *****************************************************************************
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
// File			: gzThread.h
// Module		: gzBase
// Description	: Class definition of Thread classes.
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
// AMO	981104	Created file 
// AMO	240426	Added wait for at least one added Work or non		(2.12.147)	
//
// ******************************************************************************

#ifndef __GZ_THREAD_H__
#define __GZ_THREAD_H__

/*!	\file 
	
	\brief Thread Management

	GizmoSDK uses light weight treads for mulitasking.

*/

#include "gzBasicTypes.h"
#include "gzMemory.h"
#include "gzMutex.h"
#include "gzReference.h"
#include "gzStackInfo.h"


#if defined GZ_WINDOWS

#if !defined GZ_WINCE

#include <process.h>

typedef gzUInt32  gzThreadReturnValue;

typedef struct 
		{
			gzUInt32 info;		// Thread ID
			HANDLE handle;
		} gzThreadInfo;
#else

typedef gzUInt32  gzThreadReturnValue;

typedef struct 
		{
			gzUInt32 info;		// Thread ID
			HANDLE handle;
			HANDLE thread;

		} gzThreadInfo;
#endif

#elif defined GZ_UNIX

// --------------------------------  UNIX ----------------------------------

#include <unistd.h>

typedef struct 
		{
			pthread_t info;		// Thread ID

		} gzThreadInfo;

typedef gzVoid *		gzThreadReturnValue;

#endif


// ******************** class definitions ***************************************

//******************************************************************************
// Class	: gzThread
//									
// Purpose  : - 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981104	Created 
//									
//******************************************************************************
/*! \brief Base class for threads

Derive your class from gzThread and implement the virtual method process().
It should look like this.
\code

gzVoid MyClass::process()
{
	while(!isStopping())
	{
		// Do something
	}
}
\endcode

You control it by using MyClass.run() and MyClass.stop(). All methods are thread safe
*/


enum gzThreadPriority { GZ_THREAD_PRIO_LOWEST, GZ_THREAD_PRIO_LOW, GZ_THREAD_PRIO_NORMAL, GZ_THREAD_PRIO_HIGH, GZ_THREAD_PRIO_HIGHEST };

const gzUInt32 GZ_THREADSLOTS=10000;		// Number of possible enums

class  gzThread :	public gzMemoryCheck , 
					public gzProgramExecution
{
public:
	
	GZ_BASE_EXPORT	gzThread(gzThreadPriority prio=GZ_THREAD_PRIO_NORMAL);

	GZ_BASE_EXPORT	virtual ~gzThread();
	
	GZ_BASE_EXPORT	virtual gzVoid		stop(gzBool waitForStop=FALSE);

	//! Start the thread execution
	GZ_BASE_EXPORT	virtual gzBool		run(gzBool waitForRunning=FALSE);

	//! chain the thread execution and transfer control to thread loop
	GZ_BASE_EXPORT	virtual gzBool		chain();


	GZ_BASE_EXPORT	gzBool		isRunning(gzBool tick=FALSE);

	GZ_BASE_EXPORT	gzBool		isStopping(gzBool tick=FALSE);

	GZ_BASE_EXPORT	gzBool		tickAlive();

	GZ_BASE_EXPORT	gzVoid		setTickLimit(gzDouble tickLimit);

	GZ_BASE_EXPORT	gzDouble	getTickLimit();

	GZ_BASE_EXPORT	gzVoid		setThreadPriority(gzThreadPriority prio);

	GZ_BASE_EXPORT	gzVoid		kill();

	GZ_BASE_EXPORT	gzVoid		setAutoDelete(gzBool deleteAfterTermination);

	GZ_BASE_EXPORT	gzThreadInfo getThreadInfo() const;

	//! Let the system know we are working
	GZ_BASE_EXPORT	gzVoid		working(gzBool on);

	// static utilities

	GZ_BASE_EXPORT	static gzVoid 	gzDelayFunction( gzUInt32 milliseconds , gzEvent *event=nullptr);
	GZ_BASE_EXPORT	static gzVoid 	gzMicroDelayFunction( gzUInt32 microseconds);

	GZ_BASE_EXPORT	static gzUInt32	getThreadID();
	GZ_BASE_EXPORT	static gzUInt32	getThreadEnum(gzUInt32 threadID=0);

	GZ_BASE_EXPORT	static gzVoid	useThreadPriorities(gzBool on);
	
protected:

	friend gzThreadReturnValue GZ_CALLBACK sprocess(gzVoid *pek);
		
	//! -----  Override this method to get the default execution ------------------------

	GZ_BASE_EXPORT	virtual gzVoid process()=0;

	//! ---------------------------------------------------------------------------------

	GZ_BASE_EXPORT	virtual gzVoid onProgramExecution();

	GZ_BASE_EXPORT	gzVoid 		wrapproc();

private:

	gzBool		tickAlive_unsafe();
	gzBool		isRunning_unsafe(gzBool tick);
	gzBool		isStopping_unsafe(gzBool tick);

	gzMutex				m_mutex;

	gzBool				m_stop:1;

   	gzBool				m_run:1;

	gzBool				m_autoDelete:1;

	gzBool				m_working:1;
	
	gzThreadInfo		m_pInfo;

	gzDouble			m_tickAliveTime;

	gzDouble			m_tickLimit;

	gzThreadPriority	m_priority;

};

#define gzSleep gzThread::gzDelayFunction

#define gzMicroSleep gzThread::gzMicroDelayFunction

typedef enum { GZ_TICK_ACCUM , GZ_TICK_SKIP } gzTickPolicy;

const gzUInt32 POOL_ID_GUI_THREAD(0);	// The default GUI thread

//******************************************************************************
// Class	: gzThreadTicker
//									
// Purpose  : To provide a uniform ticking mechanism in combination with thread 
//			  pool management.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	001012	Created 
//									
//******************************************************************************
class gzThreadTicker
{
public:

	GZ_BASE_EXPORT gzThreadTicker(gzUInt32 pool,gzThreadPriority prio=GZ_THREAD_PRIO_NORMAL);

	GZ_BASE_EXPORT virtual ~gzThreadTicker();

	GZ_BASE_EXPORT virtual gzVoid onInitialize(){}

	GZ_BASE_EXPORT virtual gzVoid onTerminate(){}

	GZ_BASE_EXPORT virtual gzVoid onTick(){}

	GZ_BASE_EXPORT gzVoid setTickInterval(gzDouble interval);

	GZ_BASE_EXPORT gzVoid setTickPolicy(gzTickPolicy policy);

	//! Returns TRUE if a old triggerTick wait is active and is scheduled before the new triggerTick
	GZ_BASE_EXPORT gzBool triggerTick(gzDouble waitDelay=0);

	GZ_BASE_EXPORT gzVoid disableThreadTicker();

	GZ_BASE_EXPORT gzVoid enableThreadTicker();

	GZ_BASE_EXPORT gzVoid deleteThreadTicker();

	GZ_BASE_EXPORT gzBool isEnabled();

	GZ_BASE_EXPORT gzUInt32 getPoolID();

	GZ_PROPERTY_EXPORT_( gzUInt32	,	MinPoolSleepTicks	,GZ_BASE_EXPORT);

private:

	friend class gzThreadPoolTicker;

	gzDouble			m_interval;

	gzDouble			m_nextTick;

	gzDouble			m_oneShot;

	gzUInt32			m_poolID;

	gzTickPolicy		m_policy;

	gzThreadPriority	m_priority;

	gzMutex				m_lock;

	gzMutex				m_trigger;

	gzBool				m_enabled;
};

//******************************************************************************
// Class	: gzRemovedSubscriber
//									
// Purpose  : Holds a pending removed subscriber in gzThreadPoolTicker
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// CAN	090605	Created 
//									
//******************************************************************************

class gzRemovedSubscriber : public gzThreadSafeReference
{
	public:
		gzRemovedSubscriber(gzThreadTicker* ticker, gzBool deleted = FALSE) : ticker(ticker), deleted(deleted){}
		~gzRemovedSubscriber(){}

		gzThreadTicker* ticker;
		gzBool deleted;
};

//******************************************************************************
// Class	: gzThreadPoolTicker
//									
// Purpose  : Provides the tick manager for a certain thread pool
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	001012	Created 
//									
//******************************************************************************
class gzThreadPoolTicker : public gzThreadSafeReference , public gzThread
{
public:

	GZ_BASE_EXPORT virtual ~gzThreadPoolTicker();

	GZ_BASE_EXPORT virtual gzBool	useDeepCopy();

	GZ_BASE_EXPORT static gzVoid guiTick();

	GZ_BASE_EXPORT static gzVoid closeAll();

private:

	friend class gzThreadTicker;

	GZ_BASE_EXPORT gzThreadPoolTicker(gzUInt32 pool,gzThreadPriority prio);
	
	gzVoid addSubscriber(gzThreadTicker *subscriber);

	gzVoid removeSubscriber(gzThreadTicker *subscriber);

	gzBool checkSubscriptions(gzUInt32 &minSleepTicks);

	gzVoid checkMinTickDelay();

	gzBool isRemoved(gzThreadTicker* ticker);

	gzBool isDeleted(gzThreadTicker* ticker);

	gzVoid setRemoved(gzThreadTicker* ticker, gzBool deleted);

	gzVoid unRemove(gzThreadTicker* ticker);
	
	virtual gzVoid	process();

	gzBool processWork();

	gzVoid processRemoves();

	// --------------- vars ------------------

	gzUInt32				m_poolID;

	gzList<gzThreadTicker>	m_subscribers;

	gzList<gzThreadTicker>	m_addSubscribers;

	gzRefList<gzRemovedSubscriber>	m_removedSubscribers;

	gzReadWriteMutex		m_subscriberLock;

	gzMutex					m_addSubscriberLock;

	gzReadWriteMutex		m_removedSubscribersLock;

	gzDouble				m_minTickDelay;

	gzEvent					m_event;

	static gzRefPointer<gzThreadPoolTicker> getThreadPoolTicker(gzUInt32 pool,gzThreadPriority prio=GZ_THREAD_PRIO_NORMAL);

	static gzMemCheck<gzMutex>		s_threadPoolLock;

	static gzRefList<gzThreadPoolTicker> s_threadPool;
};

//******************************************************************************
// Class	: gzThreadData
//									
// Purpose  : To provide a thread local storage.- Each thread gets its own instance of data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	020525	Created 
//									
//******************************************************************************
template <class T> class gzThreadData 
{
public:

	gzThreadData(gzUByte indexCount=1);

	virtual ~gzThreadData();

	operator T &();

	T & operator[](gzUByte index);
	
	T & get() { return operator T&(); }

	gzVoid set(const T & data);

	gzVoid clean();

private:

	template <class T2> class _localData : public gzReference
	{
	public:

		_localData(gzUByte indexCount):data(indexCount),index(0)
		{
		}

		virtual ~_localData()
		{
		}

		gzArray<T2>	data;
		gzUByte		index;
	};

	gzUInt32											m_currentThreadID;

	gzRefPointer<_localData<T> >						m_currentData;

	gzRefDict<gzUInt32CompareInterface,_localData<T> >	m_dict;

	gzMutex												m_locker;

	gzUByte												m_indexCount;
};

template <class T> inline gzThreadData<T>::gzThreadData(gzUByte indexCount):
													m_currentThreadID(0),
													m_locker(FALSE),
													m_indexCount(indexCount)
{
}

template <class T> gzVoid gzThreadData<T>::clean()
{
	m_locker.waitLock();

	m_dict.clear();
	m_currentData=0;
	m_currentThreadID=0;

	m_locker.unLock();
}

template <class T> gzThreadData<T>::~gzThreadData()
{
	clean();
}

template <class T> inline gzVoid gzThreadData<T>::set(const T & data)
{
	operator T&()=data;
}

template <class T> inline gzThreadData<T>::operator T &()
{
	GZ_BODYGUARD(m_locker);

	gzUInt32	threadID=gzThread::getThreadID();

	if(m_currentThreadID!=threadID)
	{
		_localData<T> *refData=m_dict.find(threadID);

		if(!refData)
		{
			refData=new _localData<T>(m_indexCount);
			m_dict.enter(threadID,refData);
		}

		m_currentThreadID=threadID;
		m_currentData=refData;
	}

	T & retval = m_currentData->data[m_currentData->index];

	m_currentData->index=(m_currentData->index+1)%m_indexCount;

	return retval;
}

template <class T> inline T & gzThreadData<T>::operator [](gzUByte index)
{
	GZ_BODYGUARD(m_locker);

	gzUInt32	threadID=gzThread::getThreadID();

	if(m_currentThreadID!=threadID)
	{
		_localData<T> *refData=m_dict.find(threadID);

		if(!refData)
		{
			refData=new _localData<T>(m_indexCount);
			m_dict.enter(threadID,refData);
		}

		m_currentThreadID=threadID;
		m_currentData=refData;
	}

	if(index<m_indexCount)
		return m_currentData->data[index];

	throwFatalTemplateError("gzThreadData [] index out of bounds");
}

// --------------------------------- Batch management ----------------------------------------

//******************************************************************************
// Class	: gzBatchFence
//									
// Purpose  : Gateway for batch processing
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150101	Created 
//									
//******************************************************************************
class gzBatchFence : public gzThreadSafeReference
{
public:

	GZ_BASE_EXPORT	gzBatchFence();

	GZ_BASE_EXPORT	gzVoid addFence(gzUInt32 id = 0);
	GZ_BASE_EXPORT	gzVoid removeFence(gzUInt32 id = 0);

	GZ_BASE_EXPORT	gzVoid resetTriggers();

	GZ_BASE_EXPORT	gzBool wait(gzUInt32 timeout, gzUInt32 fences, gzBool atLeastOneAddedWork = TRUE, gzBool anyAdd = FALSE, gzBool anyRemove = FALSE, gzUInt32* add_id = NULL, gzUInt32* remove_id = NULL);

	GZ_BASE_EXPORT	gzUInt32 getFences();

	GZ_BASE_EXPORT	gzUInt32 getLastAddedFence();
	GZ_BASE_EXPORT	gzUInt32 getLastRemovedFence();

	GZ_BASE_EXPORT	gzBool	useDeepCopy() { return FALSE; }

private:

	gzMutex		m_locker;
	gzEvent		m_change;
	gzUInt32	m_fences;
	gzUInt32	m_lastAddedFenceId;
	gzUInt32	m_lastRemovedFenceId;
	gzBool		m_hasRemove;
	gzBool		m_hasAdd;
};

GZ_DECLARE_REFPTR(gzBatchFence);


//******************************************************************************
// Class	: gzBatchWork
//									
// Purpose  : Utility for batch processing
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150101	Created 
//									
//******************************************************************************
class gzBatchWork : public gzThreadSafeReference
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT	gzBatchWork();

	GZ_BASE_EXPORT	virtual gzVoid work()=0;

	GZ_PROPERTY_EXPORT(gzUInt32,		ID,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBatchFencePtr, Fences,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32,		ThreadID,	GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool,			Error,		GZ_BASE_EXPORT);
};

//******************************************************************************
// Class	: gzBatchThread
//									
// Purpose  : Utility for batch processing
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150101	Created 
//									
//******************************************************************************
class gzBatchThread : public gzReference , public gzThread
{
public:

	GZ_THREADSAFE_REF(m_sync);

	GZ_BASE_EXPORT	gzBatchThread(gzUInt32 threadID);

	GZ_BASE_EXPORT	virtual ~gzBatchThread();
		
	GZ_BASE_EXPORT	gzUInt32 getPendingWork();

	GZ_BASE_EXPORT	gzBool inProgress();

	GZ_BASE_EXPORT	gzUInt32 getErrors();

	GZ_BASE_EXPORT	gzVoid triggerWork();

	GZ_BASE_EXPORT	gzVoid clearWork();

	GZ_BASE_EXPORT	gzBool addWork(gzBatchWork *work,gzBool triggerWork=TRUE);

private:

	GZ_BASE_EXPORT	virtual gzVoid process() override;

	gzUInt32				m_errors;
	gzEvent					m_sync;
	gzRefList<gzBatchWork>	m_work;
	gzUInt32				m_threadID;
	gzBool					m_inProgress;
};

enum gzBatchWorkType
{
	GZ_BATCH_WORK_TYPE_BALANCED,	//!< Work added to least pending work thread
	GZ_BATCH_WORK_TYPE_UNIFORM,		//!< Work added to next thread available
};

//******************************************************************************
// Class	: gzBatchManager
//									
// Purpose  : Utility for batch processing
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150101	Created 
//									
//******************************************************************************
class gzBatchManager : public gzThreadSafeReference
{
public:

	GZ_BASE_EXPORT	gzBatchManager(gzUInt32 threads=4);

	GZ_BASE_EXPORT	virtual ~gzBatchManager();

	GZ_BASE_EXPORT	gzBool addWork(gzBatchWork *work,gzBool triggerWork=TRUE,gzBatchWorkType addedWork= GZ_BATCH_WORK_TYPE_UNIFORM ,gzBatchFence *external_fence=nullptr, gzUInt32 pool=0xFFFFFFFFUL);

	//! Manually trigger work to start
	GZ_BASE_EXPORT	gzVoid triggerWork();

	GZ_BASE_EXPORT	gzVoid clearWork();

	//! Timeout in milliseconds and count is accepted remaining fences. Default is at least one work is done and pending work - 1 is left
	//! If atLeatOneWork is true,we will await the first added work as well
	//! Return FALSE on timeout
	GZ_BASE_EXPORT	gzBool wait(gzUInt32 timeout , gzUInt32 remaining_fences=0xFFFFFFFFUL , gzBool atLeastOneAddedWork=TRUE);

	GZ_BASE_EXPORT gzUInt32 getThreadCount();

	GZ_BASE_EXPORT gzVoid start();

	GZ_BASE_EXPORT gzVoid stop(gzBool wait=TRUE);

	GZ_BASE_EXPORT gzUInt32 getPendingWork();

	GZ_BASE_EXPORT gzUInt32 getWorkInProgress();

	GZ_BASE_EXPORT gzUInt32 getErrors();

private:

	gzRefList<gzBatchThread>		m_threads;
	gzListIterator<gzBatchThread>	m_threadIterator;
	gzUInt32						m_currentID;
	gzBatchFencePtr					m_currentBatchFences;
};

GZ_DECLARE_REFPTR(gzBatchManager);

#endif //__GZ_THREAD_H__


