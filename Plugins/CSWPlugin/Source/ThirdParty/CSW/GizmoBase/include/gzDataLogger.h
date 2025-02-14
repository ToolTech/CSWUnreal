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
// File			: gzDataLogger.h
// Module		: gzBase
// Description	: Class definition of logging features
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.220
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
// AMO	131113	Created file 											(2.7.2)
//
//******************************************************************************
#ifndef __GZ_DATA_LOGGER_H__
#define __GZ_DATA_LOGGER_H__

#include "gzTime.h"
#include "gzSerialize.h"
#include "gzDynamic.h"

//******************************************************************************
// Class	: gzDataLogFormat
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	131113	Created 
//									
//******************************************************************************
class gzDataLogFormat : public gzReference
{
public:

	GZ_BASE_EXPORT virtual gzVoid log(gzDouble timestamp,GZ_DYNAMIC_ATTRIBUTE_LIST,gzSerializeAdapter *adapter=nullptr)=0;
};

GZ_DECLARE_REFPTR(gzDataLogFormat);

//******************************************************************************
// Class	: gzDataLogFormatAscii
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	131113	Created 
//									
//******************************************************************************
class gzDataLogFormatAscii : public gzDataLogFormat
{
public:

	GZ_BASE_EXPORT	gzDataLogFormatAscii(gzString separator="," , gzString terminator="\r\n");

	GZ_BASE_EXPORT	virtual gzVoid log(gzDouble timestamp,GZ_DYNAMIC_ATTRIBUTE_LIST,gzSerializeAdapter *adapter=nullptr);

private:

	gzString	m_separator;
	gzString	m_terminator;
};

//******************************************************************************
// Class	: gzDataLogger
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	131113	Created 
//									
//******************************************************************************
class gzDataLogger : public gzReference , public gzMessageReceiverInterface
{
public:

	GZ_BASE_EXPORT gzDataLogger(gzString URL=GZ_EMPTY_STRING,gzDataLogFormat *format=new gzDataLogFormatAscii);

	GZ_BASE_EXPORT virtual ~gzDataLogger();

	GZ_BASE_EXPORT gzDouble log(GZ_DYNAMIC_ATTRIBUTE_LIST);

	GZ_BASE_EXPORT gzVoid enableMessageReceiver();

	GZ_BASE_EXPORT gzVoid disableMessageReceiver();

	GZ_PROPERTY_EXPORT(gzBool,	UseTimeTag,	GZ_BASE_EXPORT);

protected:
	
	// ------------ the receiver --------------------
	virtual gzVoid onMessage(const gzString& sender , gzMessageLevel level , const char *message);

private:

	gzSerializeAdapterPtr	m_adapter;
	gzDataLogFormatPtr		m_format;

};

GZ_DECLARE_REFPTR(gzDataLogger);

#endif // __GZ_DATA_LOGGER_H__

