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
// File			: gzPerformanceInfo.h
// Module		: 
// Description	: Class definition of the gzPerformanceInfo class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.262
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
// AMO	001016	Created file 	
//
//******************************************************************************
#ifndef __GZ_PERFORMANCE_INFO_H__
#define __GZ_PERFORMANCE_INFO_H__

/*!	\file 
	\brief Base definitions for performance nodes

*/

#include "gzText.h"

//******************************************************************************
// Class	: gzPerformanceInfo
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	001016	Created 
//									
//******************************************************************************
class gzPerformanceInfo : public gzText
{
public:
	GZ_GRAPH_EXPORT gzPerformanceInfo(const gzString &name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzPerformanceInfo(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- gzPerformanceInfo interface ---------------------------

	GZ_GRAPH_EXPORT gzVoid addInfo(const gzString &performanceSectionName,gzUInt32 threadID=gzThread::getThreadID());

	GZ_GRAPH_EXPORT gzVoid removeInfo(const gzString &performanceSectionName);

	GZ_GRAPH_EXPORT gzVoid showAllocMem(gzBool show);

	GZ_GRAPH_EXPORT gzVoid showText(gzBool show);

	GZ_GRAPH_EXPORT gzVoid showRefreshRate(gzBool show);

	GZ_GRAPH_EXPORT gzVoid dumpPerformanceInfo(gzBool on);

	GZ_GRAPH_EXPORT gzVoid enableOutput(gzBool on=TRUE);

	GZ_GRAPH_EXPORT gzVoid showAllSections(gzBool on=FALSE);

	// ------------------- Properties ---------------------

	GZ_PROPERTY_EXPORT(gzUInt16,		MaxRows,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt16,		FrameIterations,		GZ_GRAPH_EXPORT);	// Defaults to 100

protected:

	gzRefList<gzSectionInfo>	m_perfData;

	gzUInt16					m_currentFrameIteration;

	gzBool						m_showAllocMem;

	gzBool						m_showText;

	gzBool						m_showRefreshRate;

	gzBool						m_dumpPerfInfo;

	gzBool						m_enabled;

	gzBool						m_showAllSections;

	gzDouble					m_lastRender;
};

GZ_DECLARE_REFPTR(gzPerformanceInfo);

class gzPerformanceMonitorValue : public gzReference
{
public:
		gzPerformanceMonitorValue(){}
		virtual ~gzPerformanceMonitorValue(){}
		virtual	gzBool	useDeepCopy() { return FALSE; }

		// --------- Data ---------

		gzDouble	value;
		gzDouble	time;
};

enum gzPerformanceMonitorType
{
	GZ_PERF_MON_TYPE_TIMING,
	GZ_PERF_MON_TYPE_ITERATIONS,
	GZ_PERF_MON_TYPE_STACK_DEPTH,
};

//******************************************************************************
// Class	: gzPerformanceMonitor
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	001016	Created 
//									
//******************************************************************************
class gzPerformanceMonitor : public gzNode , public gzMutex
{
public:
	GZ_GRAPH_EXPORT gzPerformanceMonitor(const gzString &name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzPerformanceMonitor(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	
	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Monitoring Interface ----------------------------------
	
	GZ_GRAPH_EXPORT gzVoid addValue(const gzDynamicType &value,const gzDouble &time=-1,const gzUInt32 &instanceID=0);
	
	GZ_GRAPH_EXPORT gzDouble getLastSampleValue();
	GZ_GRAPH_EXPORT gzDouble getLastSampleTime();
	
	GZ_GRAPH_EXPORT gzVoid enter();
	GZ_GRAPH_EXPORT gzVoid leave();
	
	GZ_GRAPH_EXPORT gzVoid registerMonitor(const gzString &name);
	GZ_GRAPH_EXPORT gzVoid unregisterMonitor();
	
	
	GZ_PROPERTY_EXPORT(gzUInt32,					MaxSamples,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec2,						Position,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,						Origo,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec2,						Scale,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec4,						Color,				GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool,						ScaleAverage,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,						AutoScale,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,					AverageFactor,		GZ_GRAPH_EXPORT);	//!< Default 0.01 so new data updates the mean with 1 percent
	GZ_PROPERTY_EXPORT(gzDouble,					VarianceFactor,		GZ_GRAPH_EXPORT);	//!< Default 0.01 so new data updates the variance with 1 percent
	GZ_PROPERTY_EXPORT(gzBool,						ShowAverage,		GZ_GRAPH_EXPORT);

	GZ_PROPERTY_EXPORT(gzString,					Label,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,					Interval,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32,					IntervalTicks,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec4,						IntervalColor,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32,					SampleLevel,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzPerformanceMonitorType,	SampleType,			GZ_GRAPH_EXPORT);


	GZ_GRAPH_EXPORT static gzVoid enter(const gzString &name);
	GZ_GRAPH_EXPORT static gzVoid leave(const gzString &name);
	GZ_GRAPH_EXPORT static gzVoid addValue(const gzString &name,const gzDynamicType &value,const gzDouble &time=-1,const gzUInt32 &instanceID=0);
	
	GZ_GRAPH_EXPORT static gzVoid setEnabledMonitoring(gzBool on=TRUE);
	GZ_GRAPH_EXPORT static gzVoid installMonitoring();
	GZ_GRAPH_EXPORT static gzVoid uninstallMonitoring();
	
private:
	
	gzRefList<gzPerformanceMonitorValue>			m_data;
	
	gzDouble										m_averageValue;

	gzDouble										m_varianceValue;

	gzRefPointer<gzPerformanceMonitorValue>			m_cacheItem;
	
	gzUInt32										m_stackDepth;
	
	gzDouble										m_accumData;
	
	gzTimer											m_timer;
	
	static gzRefDict<gzString,gzPerformanceMonitor>	s_registeredMonitors;
	
	static gzMutex									s_locker;
	
	static	gzBool									s_enabled;

};

GZ_DECLARE_REFPTR(gzPerformanceMonitor);


#endif
