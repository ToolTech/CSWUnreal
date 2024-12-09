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
// File			: gzPerformance.h
// Module		: gzBase
// Description	: Class definition of performance measure functionality
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
// AMO	030612	Created file 	
//
//******************************************************************************
#ifndef __GZ_PERFORMANCE_H__
#define __GZ_PERFORMANCE_H__

/*!	\file 
	\brief Performance measurement functionality for \b Gizmo3D

	As Gizmo3D is plattform independant, we need a way to do performance measurement independantly of the HW platform.
	By using this module, we can measure the time spend in code snippets etc. and get info about bottlenecks etc.
*/

#include "gzBase.h"
#include "gzThread.h"
#include "gzReference.h"
#include "gzDynamic.h"

enum gzPerformanceDumpFlags
{ 	
		GZ_PERF_DUMP_RUNNING				=	(1<<0),
		GZ_PERF_DUMP_STOPPED				=	(1<<1),
		GZ_PERF_DUMP_ACCUMULATED_SECTIONS	=	(1<<2),
		GZ_PERF_DUMP_HIERARCHICAL_SECTIONS	=	(1<<3),
		GZ_PERF_DUMP_ALL					=	0xFFFFFFFFUL,
};

GZ_USE_BIT_LOGIC(gzPerformanceDumpFlags);
	 
//******************************************************************************
// Class	: gzPerformanceResult
//									
// Purpose  : Structure to keep result data of a performance section
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030623	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzPerformanceResult 
{
public:

	gzUInt32	iterations;				//!< Number of times the section has been called non recursive	
	gzUInt32	recursive;				//!< Number of times the section has been called resursively 

	gzDouble	execTotTime;			//!< Total time spent in section or child sections
	gzDouble	execSelfTime;			//!< Total time spent in section exclusive time spent in child sections
	gzDouble	execParentTime;			//!< Total time spent in section parents

	gzFloat		execTotPercentage;		//!< Percentage of total time relative to thread time 
	gzFloat		execSelfPercentage;		//!< percentage of self time relative to thread time
	gzFloat		execParentPercentage;	//!< percentage of self time relative to parent time

	gzUInt32	callers;				//!< Number of calling parent sections

	gzUInt32	threadID;				//!< Thread ID

	gzDouble	systemTime;				//!< Current sample systemTime
};

//******************************************************************************
// Class	: gzSectionInfo
//									
// Purpose  : Structure to keep name and thread info of sections
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050209	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzSectionInfo : public gzReference
{
public:

	gzSectionInfo(const gzString &name, gzUInt32 treadID);

	virtual ~gzSectionInfo();


	gzString	sectionName;
	gzUInt32	threadID;
};

GZ_DECLARE_REFPTR(gzSectionInfo);

GZ_BASE_EXPORT gzVoid gzEnterPerformanceSection(const gzString & sectionName);

GZ_BASE_EXPORT gzVoid gzLeavePerformanceSection();

GZ_BASE_EXPORT gzVoid gzStartPerformanceThread();

GZ_BASE_EXPORT gzVoid gzStopPerformanceThread();

GZ_BASE_EXPORT gzVoid gzEnablePerformanceSections(gzBool on=TRUE);

GZ_BASE_EXPORT gzBool gzEnabledPerformanceSections();

GZ_BASE_EXPORT gzVoid gzDumpPerformanceInfo(gzPerformanceDumpFlags dumpFlags=GZ_PERF_DUMP_ALL,gzMessageLevel level=GZ_MESSAGE_PERF_DEBUG);

GZ_BASE_EXPORT gzString gzCreatePerfLineInfo(const char *file,gzUInt32 line);

GZ_BASE_EXPORT gzPerformanceResult gzGetPerformanceResult(const gzString &sectionName,gzUInt32 threadID=gzThread::getThreadID());

GZ_BASE_EXPORT gzArray<gzPerformanceResult> gzGetAllPerformanceResults(const gzString& sectionName);

//! Gett all performance sections for a specific thread or use threadID = 0 gives all threads
GZ_BASE_EXPORT gzVoid gzGetAllPerformanceSections(gzRefList<gzSectionInfo> &perfSecList,gzUInt32 threadID=gzThread::getThreadID());

GZ_BASE_EXPORT gzVoid gzClearPerformanceSection(const gzString &name=GZ_EMPTY_STRING,gzUInt32 threadID=gzThread::getThreadID());

GZ_BASE_EXPORT gzVoid gzSetPerformanceThreadName(const gzString &name,gzUInt32 threadID=gzThread::getThreadID());


//******************************************************************************
// Class	: gzPerformanceBody
//									
// Purpose  : Class to manage section enter/exit code
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030623	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzPerformanceBody 
{
public:
	gzPerformanceBody(const gzString &sectionName)
	{
		gzEnterPerformanceSection(sectionName);
	}

	virtual ~gzPerformanceBody()
	{ 
		gzLeavePerformanceSection();
	}

private:	// Do not allow copy or assignments

	gzPerformanceBody( const gzPerformanceBody & /*copy*/) {}

	gzPerformanceBody & operator=(const gzPerformanceBody & /*copy*/) { return *this; }
};

//******************************************************************************
// Class	: gzPerformanceMonitorInterface
//									
// Purpose  : Interface to external monitor
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030623	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzPerformanceMonitorInterface
{
public:

	virtual gzVoid enter(const gzString &monitor)=0;
	virtual gzVoid leave(const gzString &monitor)=0;
	virtual gzVoid addValue(const gzString &monitor,const gzDynamicType &value,const gzDouble &time,const gzUInt32 &instanceID)=0;

	static gzVoid setPerformanceMonitor(gzPerformanceMonitorInterface *monitor);
};

GZ_BASE_EXPORT gzVoid gzEnterMonitor(const gzString & monitor);
GZ_BASE_EXPORT gzVoid gzLeaveMonitor(const gzString & monitor);
GZ_BASE_EXPORT gzVoid gzAddMonitorValue(const gzString & monitor,const gzDynamicType &value,const gzDouble &time=-1,const gzUInt32 &instanceID=0);
GZ_BASE_EXPORT gzVoid gzAddMonitorValueOpt(gzBool test,const gzString & monitor, const gzDynamicType &value, const gzDouble &time = -1, const gzUInt32 &instanceID = 0);

//******************************************************************************
// Class	: gzPerformanceTracer
//									
// Purpose  : Class to view performance info using performance moitor
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	200514	Created 
//									
//******************************************************************************
class gzPerformanceTracer : public gzThreadSafeReference,
							public gzThread
{
public:

	GZ_BASE_EXPORT gzPerformanceTracer();
	GZ_BASE_EXPORT virtual ~gzPerformanceTracer();

	GZ_BASE_EXPORT gzVoid process() override;

	GZ_PROPERTY_EXPORT(gzUInt32, SleepTicks, GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzBool addSection(const gzString& name, gzUInt32 threadID = gzThread::getThreadID());
	GZ_BASE_EXPORT gzBool removeSection(const gzString& name, gzUInt32 threadID = gzThread::getThreadID());

	GZ_BASE_EXPORT gzBool addAll(gzUInt32 threadID = gzThread::getThreadID());

	GZ_BASE_EXPORT gzVoid present(const gzString &name,const gzPerformanceResult& result,gzUInt32 index);

private:

	gzEvent						m_trigger;

	gzRefList<gzSectionInfo>	m_perfSecList;

	gzDouble					m_startTime;

};

GZ_DECLARE_REFPTR(gzPerformanceTracer);

//******************************************************************************
// Class	: gzMonitorBody
//									
// Purpose  : Class to manage section enter/exit code
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030623	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzMonitorBody 
{
public:
	gzMonitorBody(const gzString &monitor):m_name(monitor)
	{
		gzEnterMonitor(monitor);
	}

	virtual ~gzMonitorBody()
	{ 
		gzLeaveMonitor(m_name);
	}

private:	// Do not allow copy or assignments

	gzMonitorBody( const gzMonitorBody & /*copy*/) {}

	gzMonitorBody & operator=(const gzMonitorBody & /*copy*/) { return *this; }

	gzString	m_name;
};

//! Defines for instrumentation that is active during GZ_INSTRUMENT_CODE

#if defined GZ_INSTRUMENT_CODE

	#define GZ_INSTRUMENT_AUTO				gzPerformanceBody	CONCAT(_instrument_,__LINE__)(x)(gzCreatePerfLineInfo(__FILE__,__LINE__))
	#define GZ_INSTRUMENT_NAME(x)			gzPerformanceBody	CONCAT(_instrument_,__LINE__)(x)
	#define GZ_ENTER_PERFORMANCE_SECTION(x)	gzEnterPerformanceSection(x)
	#define GZ_LEAVE_PERFORMANCE_SECTION	gzLeavePerformanceSection()

	#define GZ_MONITOR_AUTO					gzMonitorBody	CONCAT(_instrument_,__LINE__)(x)(gzCreatePerfLineInfo(__FILE__,__LINE__))
	#define GZ_MONITOR_NAME(x)				gzMonitorBody	CONCAT(_instrument_,__LINE__)(x)
	#define GZ_ENTER_MONITOR(x)				gzEnterMonitor(x)
	#define GZ_LEAVE_MONITOR(x)				gzLeaveMonitor(x)
	#define GZ_ADD_MONITOR_VALUE(x,y)		gzAddMonitorValue(x,y)

#else

	#define GZ_INSTRUMENT_AUTO	
	#define GZ_INSTRUMENT_NAME(x)	
	#define GZ_ENTER_PERFORMANCE_SECTION(x)
	#define GZ_LEAVE_PERFORMANCE_SECTION	

	#define GZ_MONITOR_AUTO					
	#define GZ_MONITOR_NAME(x)				
	#define GZ_ENTER_MONITOR(x)				
	#define GZ_LEAVE_MONITOR(x)				
	#define GZ_ADD_MONITOR_VALUE(x,y)		

#endif

#endif // __GZ_PERFORMANCE_H__
