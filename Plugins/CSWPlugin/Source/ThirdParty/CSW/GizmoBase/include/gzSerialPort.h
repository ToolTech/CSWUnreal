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
// File			: gzSerialPort.h
// Module		: gzBase
// Description	: Class definition of serial IO
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.262
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
// AMO	110623	Created file 										(2.5.20)
//
//******************************************************************************
#ifndef __GZ_SERIAL_PORT_H__
#define __GZ_SERIAL_PORT_H__

/*!	\file 
	\brief xx

	
*/

#include "gzSerialize.h"

enum gzParity
{
	GZ_PARITY_NONE,
	GZ_PARITY_ODD,
	GZ_PARITY_EVEN,
	GZ_PARITY_MARK,
	GZ_PARITY_SPACE
};

enum gzStopBits
{
	GZ_STOP_BITS_ONE,	// 1 stopbit
	GZ_STOP_BITS_ONE5,	// 1.5 stopbits
	GZ_STOP_BITS_TWO,	// 2 stopbits
};

//! SerialPor error codes
enum gzSerialPortError
{
	GZ_SERIAL_PORT_ERROR_NO_ERROR = 0,
	GZ_SERIAL_PORT_ERROR_CHECK_FOR_ERROR,
	GZ_SERIAL_PORT_ERROR_PORT_NOT_FOUND,
	GZ_SERIAL_PORT_ERROR_WRONG_PARAMETER,
	GZ_SERIAL_PORT_ERROR_OPERATION_ABORTED,
	GZ_SERIAL_PORT_ERROR_INVALID_PORT_HANDLE,
	GZ_SERIAL_PORT_ERROR_DATA_TIMEOUT,
	GZ_SERIAL_PORT_ERROR_CHECKSUM,
	GZ_SERIAL_PORT_UNKNOWN_ERROR,
	GZ_SERIAL_PORT_PERMISSION_DENIED,
	GZ_SERIAL_PORT_UNSUPPORTED_BAUDRATE,
};

//******************************************************************************
// Class	: gzSerialPort
//									
// Purpose  : HW abstaction for platfor serial IO
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	110623	Created 
//									
//******************************************************************************
//! A serial port allows RS232 etc. communication between clients
/*!
	blah...
*/

class gzSerialPort : public gzSerializeAdapter
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerialPort(const gzString &portName);

	GZ_BASE_EXPORT virtual	~gzSerialPort();

	GZ_BASE_EXPORT gzBool	open(gzUInt32 baudRate=115200,gzUByte charSize=8,gzParity parity=GZ_PARITY_NONE,gzStopBits stopBits=GZ_STOP_BITS_ONE,gzUInt32 inputBufferSize=1024,gzUInt32 outputBufferSize=1024);

	GZ_BASE_EXPORT gzVoid	close();

	GZ_BASE_EXPORT gzBool	setBufferSizes(gzUInt32 inputBufferSize=1024,gzUInt32 outputBufferSize=1024);

	GZ_BASE_EXPORT gzBool	setComParameters(gzUInt32 baudRate=115200,gzUByte charSize=8,gzParity parity=GZ_PARITY_NONE,gzStopBits stopBits=GZ_STOP_BITS_ONE);

	GZ_BASE_EXPORT gzBool	setComTimeout(gzUInt32 readTimoutInMilliseconds=50,gzUInt32 writeTimoutInMilliseconds=50);

	//! Get error code for last failed operation
	GZ_BASE_EXPORT	gzSerialPortError getSerialPortError() const;

	//! Check if the port has an error
	GZ_BASE_EXPORT	gzBool hasSerialPortError() const;

	//! Set the last port error
	GZ_BASE_EXPORT	gzVoid setSerialPortError(gzSerialPortError error=GZ_SERIAL_PORT_ERROR_CHECK_FOR_ERROR);

	//! Clear the last serial port error
	GZ_BASE_EXPORT	gzVoid clearSerialPortError();

	//! Flush and reset of stream
	GZ_BASE_EXPORT virtual	gzVoid flush() override;

	//! Routing of serial errors to adapter level
	GZ_BASE_EXPORT virtual gzBool	hasError() const override;
	GZ_BASE_EXPORT virtual gzString getError() const override;

private:

	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;
	GZ_BASE_EXPORT virtual gzVoid	write_imp(const gzUByte *data,gzUInt32 count) override;
	GZ_BASE_EXPORT virtual gzUInt32	read_imp(gzUByte *data,gzUInt32 maxcount) override;
	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;
	GZ_BASE_EXPORT virtual gzBool	hasData_imp() override;

	gzVoid *			m_portHandle;

	gzSerialPortError	m_error;
};

GZ_DECLARE_REFPTR(gzSerialPort);

#endif // __GZ_SERIAL_PORT_H__







