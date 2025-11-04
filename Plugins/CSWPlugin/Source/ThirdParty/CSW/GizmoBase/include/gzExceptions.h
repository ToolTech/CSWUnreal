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
// File			: gzExceptions.h
// Module		: gzBase
// Description	: Class definition of exception classes
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.283
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
// AMO	210521	Added callstack to gzBaseException					(2.11.6)
// AMO	210928	Added special exception error for exhausted streams	(2.11.36)
// AMO	211117	Added reset of stream in stream exception			(2.11.49)
//
//******************************************************************************

#ifndef __GZ_EXCEPTIONS_H__
#define __GZ_EXCEPTIONS_H__

#include "gzBase.h"
#include "gzDebug.h"

/*!	\file 
	\brief Basic classes for exception management

 The purpose of these classes is to define the base class for warnings and fatal 
 errors. A warning is typically used whenever some error occurs and the software
 can handle the situation without terminating the application
 Fatal errors should clean up but terminates the software.
*/

//******************************************************************************
// Class	: gzStackItem
//									
// Purpose  : Information about an execution line in code
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050211	Created 
//									
//******************************************************************************
class gzStackItem : public gzReference
{
public:

	GZ_BASE_EXPORT gzStackItem() :lineNumber(0), functionOffset(0) {}

	GZ_BASE_EXPORT	virtual	gzBool	useDeepCopy() override { return FALSE; }

	gzString	functionName;
	gzString	fileName;
	gzUInt32	lineNumber;
	gzString	moduleName;
	gzUInt64	functionOffset;
};

//******************************************************************************
// Class	: gzStackInfo
//									
// Purpose  : A hierarchical execution stack
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050211	Created 
//									
//******************************************************************************
class gzStackInfo : public gzReference
{
public:

	GZ_BASE_EXPORT gzStackInfo(gzBool _stripPaths = TRUE) : stripPaths(_stripPaths) {};

	GZ_BASE_EXPORT	virtual	gzBool	useDeepCopy() override { return FALSE; }

	GZ_BASE_EXPORT gzVoid dumpStack(gzSerializeAdapter* adapter) const;

	gzRefList<gzStackItem>	itemList;

	gzString				causedBy;
	gzBool					stripPaths;

};

GZ_DECLARE_REFPTR(gzStackInfo);




//******************************************************************************
// Class	: gzBaseError
//									
// Purpose  : Base class for gizmo exceptions
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980912	Created 
//									
//******************************************************************************
//! Base class for Gizmo3D exceptions
class gzBaseError : public gzTypeInterface
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzBaseError(const char *, gzInt32 errcode = 0 , gzMessageEncoding enc=GZ_MESSAGE_ENCODING_UTF8, gzBool generateStack = TRUE);
	GZ_BASE_EXPORT virtual ~gzBaseError();

	GZ_BASE_EXPORT virtual gzVoid		reportError()=0;
	GZ_BASE_EXPORT gzInt32				getErrorCode() const;
	GZ_BASE_EXPORT gzString				getErrorString() const;
	GZ_BASE_EXPORT gzMessageEncoding	getMessageEncoding() const;
	GZ_BASE_EXPORT gzStackInfo *		getStackInfo() const;

protected:

	gzInt32				m_errCode;
	gzString			m_errString;
	gzMessageEncoding	m_errMessEncode;
	gzStackInfoPtr		m_stackInfo;
};


// **************** Warning exceptions *****************************************

//******************************************************************************
// Class	: gzWarningError
//									
// Purpose  : Warning exception
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980912	Created 
//									
//******************************************************************************
//! Exception class for warning messages 
class gzWarningError : public gzBaseError
{
public:
	typedef gzVoid (* ReportFunc)(const gzWarningError&);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzWarningError(const char *, gzInt32 errcode = 0, gzMessageEncoding enc=GZ_MESSAGE_ENCODING_UTF8, gzBool generateStack = TRUE);
	GZ_BASE_EXPORT virtual ~gzWarningError();

	GZ_BASE_EXPORT virtual gzVoid		reportError() override;
	GZ_BASE_EXPORT static gzVoid		setReportFunction(ReportFunc foo);

private:
	static ReportFunc	s_reportFunc;
};


// **************** FATAL! exceptions *****************************************

//******************************************************************************
// Class	: gzFatalError
//									
// Purpose  : Fatal exception
//									
// Notes	: Does not return. Terminates program.	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980912	Created 
//									
//******************************************************************************
//! Exception class for warning messages 
class gzFatalError : public gzBaseError
{
public:
	typedef gzVoid (* ReportFunc)(const gzFatalError&);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzFatalError(const char *, gzInt32 errcode = 0, gzMessageEncoding enc=GZ_MESSAGE_ENCODING_UTF8,gzBool generateStack=TRUE);
	GZ_BASE_EXPORT virtual ~gzFatalError();

	GZ_BASE_EXPORT virtual gzVoid		reportError() override;
	GZ_BASE_EXPORT static gzVoid		setReportFunction(ReportFunc foo);

private:
	static ReportFunc s_reportFunc;
};

//! Special errcodes
enum GZ_SYSTEM_ERRCODE
{
	GZ_SYSTEM_ERRCODE_GENERIC = 0,
	GZ_SYSTEM_ERRCODE_SEH_HANDLER = 918273645,
};

// These functions can be overrided to provide custom gzInterface
// to exception reporting ...

//! Default Warning Exception handler
GZ_BASE_EXPORT gzVoid gzDefaultWarningHandler( const gzWarningError & );

//! Default Fatal Exception handler
GZ_BASE_EXPORT gzVoid gzDefaultFatalHandler( const gzFatalError & );

// **************** Adapter Serialize exceptions for controlled execution ****************

//! Possible exceptions during read/write of an adapter
enum gzStreamErrorType
{
	GZ_STREAM_ERROR_OUT_OF_DATA,			// adapter stream has ended or is exhausted
	GZ_STREAM_ERROR_DATA_IS_DISCARDED,		// data has been discarded by user through flush etc..
	GZ_STREAM_ERROR_USER_EXIT,				// Exit of stream reading requested by user code
	GZ_STREAM_ERROR_INPUT_STREAM_IS_RESET,	// Input Stream was reset
	GZ_STREAM_ERROR_OUTPUT_STREAM_IS_RESET,	// Output Stream was reset
	GZ_STREAM_ERROR_REQUIRE_LARGE_ACCESS,	// Error when using standard access and stream require large access
	GZ_STREAM_ERROR_GENERIC_ERROR			// Error is found in adapter
};

//******************************************************************************
// Class	: gzStreamError
//									
// Purpose  : Catch netsted adapter stream serialize events
//									
// Notes	: Used to control execution and unwind code
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	210928	Created 
//									
//******************************************************************************
class gzStreamError : public gzBaseError
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzStreamError(const gzStreamErrorType &error, gzBool generateStack = TRUE);

	GZ_BASE_EXPORT virtual gzVoid		reportError() override;

	GZ_BASE_EXPORT gzStreamErrorType	getStreamError() const;
};

// ********************* THROW macros *****************************************

//! Formatted throw of Warning Exceptions

GZ_BASE_EXPORT gzVoid gzThrowWarning(const char * fmt , ARG_DECL_LIST);
GZ_BASE_EXPORT gzVoid gzThrowWarning(gzMessageEncoding encoding , const char * fmt , ARG_DECL_LIST);

GZ_BASE_EXPORT gzVoid gzThrowWarning(const gzWideChar * fmtWide , ARG_DECL_LIST);
GZ_BASE_EXPORT gzVoid gzThrowWarning(gzMessageEncoding encoding , const gzWideChar * fmtWide , ARG_DECL_LIST);

//! Formatted throw of Fatal Exceptions
GZ_BASE_EXPORT gzVoid gzThrowFatal(const char * fmt , ARG_DECL_LIST);
GZ_BASE_EXPORT gzVoid gzThrowFatal(gzMessageEncoding encoding , const char * fmt , ARG_DECL_LIST);

GZ_BASE_EXPORT gzVoid gzThrowFatal(const gzWideChar * fmtWide, ARG_DECL_LIST);
GZ_BASE_EXPORT gzVoid gzThrowFatal(gzMessageEncoding encoding , const gzWideChar * fmtWide , ARG_DECL_LIST);

#endif
