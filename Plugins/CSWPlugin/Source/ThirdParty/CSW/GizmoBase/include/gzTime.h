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
// File			: gzTime.h
// Module		: gzBase
// Description	: Class definition of time management utilties
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
// AMO	040301	Created file 
// AMO	140321	Updated gzTime::systemSeconds in Windows	(2.7.6)
//
// ******************************************************************************

#ifndef __GZ_TIME_H__
#define __GZ_TIME_H__

/*!	\file 
	\brief Basic utilites for time management
*/

#include "gzBase.h"

//******************************************************************************
// Class	: gzTime
//									
// Purpose  : Time management
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980820	Created 
//									
//******************************************************************************

/*! \brief Provides a generic time management class

The gzTime class is Gizmo3D generic class for time management. The time can be adjusted without
intefering with system time and it does not require superuser rights.
*/
class  GZ_BASE_EXPORT gzTime 
{
public:

	gzTime();

	gzTime( gzDouble seconds );

	gzTime( gzUInt32 year ,  gzUByte month , gzUByte day , gzDouble dayseconds=0 );

	gzTime( gzUInt32 year ,  gzUByte month , gzUByte day , gzDouble hour , gzDouble minute , gzDouble second);

	gzDouble seconds() const;

	gzUInt32 year() const;

	gzUByte month() const;

	gzUByte day() const;

	gzDouble daySeconds() const;

	gzUByte hour() const;

	gzUByte minute() const;

	gzDouble minuteSeconds() const;

	gzString asString(const gzString &format="%4d-%02d-%02d %02d:%02d:%02d") const;

	//! Defaults to UTC time
	static gzTime now(gzBool localTime=FALSE);

	static gzVoid setTime(gzDouble time,gzBool localTime=FALSE);

	static gzDouble systemSeconds();

	static gzDouble uptimeSeconds();

	static gzDouble getLocalTimeOffset();

	static gzUInt16 daysPerYear(gzUInt32 year);

	static gzUByte daysPerMonth(gzUByte month,gzUInt32 year);

	static gzDouble getTimeResolution();

	static gzDouble getSystemTimeOffset();

	static void setSystemTimeOffset(gzDouble offset);

	static gzBool isSystemSynchronized();

	gzDouble operator -(const gzTime &time) const;
	gzDouble operator +(const gzTime &time) const;
	gzDouble operator -(const gzDouble &sec) const;
	gzDouble operator +(const gzDouble &sec) const;

	gzBool operator<(const gzTime &time) const;
	gzBool operator<=(const gzTime &time) const;
	gzBool operator>(const gzTime &time) const;
	gzBool operator>=(const gzTime &time) const;
	gzBool operator!=(const gzTime &time) const;
	gzBool operator==(const gzTime &time) const;

private:
	
	gzDouble		m_seconds;

	static gzDouble	s_systemTimeOffset;
	static gzDouble	s_systemStartTime;
	static gzBool	s_isSystemSynchronized;
	static gzMutex	s_syncSystemLock;
};

//******************************************************************************
// Class	: gzTimer
//									
// Purpose  : Timer measuring
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040301	Created 
//									
//******************************************************************************
/*! \brief Provides a timer instance
*/
class  gzTimer : public gzNameInterface
{
public:

	GZ_BASE_EXPORT gzTimer(const gzString &name=GZ_EMPTY_STRING):gzNameInterface(name)		
	{ 
		m_resetTime=gzTime::systemSeconds();	
		m_lastGetTime=m_resetTime;
	}

	GZ_BASE_EXPORT gzVoid	reset(gzBool resetToLastGetTime=FALSE)		
	{ 
		if(resetToLastGetTime)
			m_resetTime=m_lastGetTime;
		else
		{
			m_resetTime=gzTime::systemSeconds();			
			m_lastGetTime=m_resetTime;
		}
	}
	
	GZ_BASE_EXPORT gzVoid	setTime(const gzDouble &time)		
	{ 
		m_resetTime=gzTime::systemSeconds()-time;			
		m_lastGetTime=m_resetTime;
	}

	GZ_BASE_EXPORT gzDouble getTime(gzUInt32 loops=1)	
	{ 
		m_lastGetTime=gzTime::systemSeconds();
		return (m_lastGetTime-m_resetTime)/loops;	
	}

	GZ_BASE_EXPORT gzDouble getFrequency(gzUInt32 loops = 1)
	{
		m_lastGetTime = gzTime::systemSeconds();
		return loops / (m_lastGetTime - m_resetTime);
	}


	GZ_BASE_EXPORT gzVoid notifyTime(const gzDouble &minTime=0.0,gzMessageLevel level=GZ_MESSAGE_DEBUG,gzUInt32 loops=1)
	{
		gzDouble diff(getTime(loops));

		gzDouble freq(getFrequency(loops));

		if (diff >= minTime)
			GZMESSAGE(level, "--- GZ_TIMER '%s' Time: %g (s)  Freq: %g (hz) Loops: %d ---", (const char*)getName(), diff, freq, loops);
	}

private:

	gzDouble	m_resetTime;
	gzDouble	m_lastGetTime;
};
#endif // __GZ_TIME_H__

