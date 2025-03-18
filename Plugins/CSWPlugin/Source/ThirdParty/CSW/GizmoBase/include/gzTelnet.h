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
// File			: gzTelnet.h
// Module		: gzBase
// Description	: Class definition of telnet based communication
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
// AMO	150707	Created file 									(2.8.1)
//
// ******************************************************************************
#ifndef __GZ_TELNET_H__
#define __GZ_TELNET_H__

/*!	\file 
	\brief Telnet based communication protocol and TCP/IP stack management

Implements the TELNET protocol as base for TCP/IP communication

*/

#include "gzNetwork.h"
#include "gzInterpreter.h"


class gzTcpConnectionServer; // Forw decl

//******************************************************************************
// Class	: gzTcpConnectionInterface
//									
// Purpose  : Base class for a TCP/IP server based connection
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150707	Created 
//									
//******************************************************************************
class gzTcpConnectionInterface :	public gzThreadSafeReference,
									public gzThread,
									public gzNameInterface
								
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT	gzTcpConnectionInterface();

	GZ_BASE_EXPORT	virtual ~gzTcpConnectionInterface();

	// ---- utils --------

	GZ_BASE_EXPORT	gzVoid runConnection(gzSocket *socket);

	GZ_BASE_EXPORT	gzVoid cleanSocket();

	GZ_BASE_EXPORT	gzInt32 send(const gzUByte *adress,gzUInt32 len);

	GZ_BASE_EXPORT	gzVoid setParentServer(gzTcpConnectionServer *parent,gzBool removeFromServer=TRUE);

	GZ_BASE_EXPORT  gzTcpConnectionServer *getParentServer();

	GZ_BASE_EXPORT	gzVoid triggerGotData();

	GZ_BASE_EXPORT	gzBool waitForData(gzUInt32 timeout=10000,gzBool alreadyLocked=FALSE);
		
	//! Factory
	GZ_BASE_EXPORT	virtual gzReference *clone() const override =0 ;

	GZ_PROPERTY_EXPORT(gzBool, BoostConnection, GZ_BASE_EXPORT);

protected:

	friend gzTcpConnectionServer;

	// ---- callbacks ----

	GZ_BASE_EXPORT	virtual gzVoid onData(gzSocketAddress &from, gzUByte *adress,gzUInt32 len)=0;

	GZ_BASE_EXPORT	virtual gzVoid onInitialize(){};

	GZ_BASE_EXPORT	virtual gzVoid onProcess() {};
	
	GZ_BASE_EXPORT	virtual gzVoid onFinalize() {};

	gzSocket *				m_socket;

	gzMutex					m_socketLocker;

private:

	// Hide run interface
	GZ_BASE_EXPORT virtual gzBool	run(gzBool waitForRunning=FALSE) override;

	GZ_BASE_EXPORT virtual gzVoid	process() override;

	gzEvent					m_gotData;

	gzMutex					m_parentLocker;		// Locks access to our parent server pointer

	gzTcpConnectionServer *	m_parentServer;

};

GZ_DECLARE_REFPTR(gzTcpConnectionInterface);

//******************************************************************************
// Class	: gzTcpConnectionWriter
//									
// Purpose  : A batch work that can be added to write from another thread to a connection
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	190131	Created 
//									
//******************************************************************************
class gzTcpConnectionWriter : public gzBatchWork
{
public:

	GZ_BASE_EXPORT	virtual gzVoid work() override;

	// Some public data
	// data is written to adapter once using a batch manager
	gzRecycledBuffer			data;
	gzTcpConnectionInterfacePtr	connection;
};

//******************************************************************************
// Class	: gzTcpConnectionServer
//									
// Purpose  : A server that creates connections for requests at a certain port and interface
//									
// Notes	: You need to register a connection factory first
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150707	Created 
//									
//******************************************************************************
class gzTcpConnectionServer :	public gzThreadSafeReference,
								public gzThread
{
public:
	
	GZ_BASE_EXPORT	gzTcpConnectionServer(gzUInt16 port,const gzHostAddress &iface=gzHostAddress(0));
	GZ_BASE_EXPORT	virtual ~gzTcpConnectionServer();

	GZ_PROPERTY_GET_EXPORT(gzUInt16,					Port,		GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzHostAddress,				Interface,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzTcpConnectionInterfacePtr	,	Connection,	GZ_BASE_EXPORT);

	GZ_BASE_EXPORT	gzBool	open(gzUInt16 port,const gzHostAddress &iface=gzHostAddress(0));
	GZ_BASE_EXPORT	gzVoid	stop(gzBool waitForStop = FALSE);

	GZ_BASE_EXPORT	gzBool	removeConnection(gzTcpConnectionInterface *child);
	GZ_BASE_EXPORT	gzVoid	removeAllConnections();
	GZ_BASE_EXPORT	gzVoid	cleanupRemovedConnections();

	GZ_BASE_EXPORT	gzUInt32 getActiveConnections();
	
		
protected:

	GZ_BASE_EXPORT	virtual gzVoid onNewConnection(gzTcpConnectionInterface * /*connection*/) {};
	GZ_BASE_EXPORT	virtual gzVoid onRemovedConnection(gzTcpConnectionInterface* /*connection*/) {};

	GZ_BASE_EXPORT	virtual void process();


	gzRefList<gzTcpConnectionInterface>		m_connections;
	gzRefList<gzTcpConnectionInterface>		m_removedConnections;
	gzMutex									m_connectionLocker;			// Locks access to list change

};

GZ_DECLARE_REFPTR(gzTcpConnectionServer);

// ------------------------ gzTelnetConnection ---------------------------------

enum gzTelnetStates
{
	GZ_TELNET_STATE_NORMAL,
	GZ_TELNET_STATE_COMMAND,
	GZ_TELNET_STATE_WILL,
	GZ_TELNET_STATE_WONT,
	GZ_TELNET_STATE_DO,
	GZ_TELNET_STATE_DONT,
};

enum TelnetCommand
{
	GZ_TEL_CMD_WILL	=0xFB,
	GZ_TEL_CMD_WONT	=0xFC,
	GZ_TEL_CMD_DO	=0xFD,
	GZ_TEL_CMD_DONT	=0xFE,
};


//******************************************************************************
// Class	: gzTelnetConnection
//									
// Purpose  : Base class for a TELNET based communication. Routes input to installed interpreter
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150707	Created 
//									
//******************************************************************************
class gzTelnetConnection :	public gzTcpConnectionInterface,
							public gzInterpreterDataInterface
{
public:

	GZ_BASE_EXPORT	gzTelnetConnection();
	GZ_BASE_EXPORT	~gzTelnetConnection();

	GZ_PROPERTY(gzTriState<gzBool>,	RemoteEcho);
	GZ_PROPERTY(gzTriState<gzBool>,	LocalEcho);

	//! Factory
	GZ_BASE_EXPORT	virtual gzReference *clone() const override;


	GZ_BASE_EXPORT gzVoid sendCommand(TelnetCommand cmd,gzUByte feature);

	// Response
	GZ_BASE_EXPORT	virtual gzBool push(const gzUByte *adress,gzUInt32 len) override;

	GZ_BASE_EXPORT	virtual gzBool quit() override;

protected:

	GZ_BASE_EXPORT	virtual gzVoid onInitialize() override;

	GZ_BASE_EXPORT	virtual gzVoid onFinalize() override;

	GZ_BASE_EXPORT	virtual gzVoid onData(gzSocketAddress &from, gzUByte *adress,gzUInt32 len) override;

	GZ_BASE_EXPORT	virtual gzVoid installInterpreter();
	GZ_BASE_EXPORT	virtual gzVoid unInstallInterpreter();

	gzTelnetStates		m_state;

	gzInterpreterPtr	m_interpreter;
};

//******************************************************************************
// Class	: gzFtpConnection
//									
// Purpose  : Base class for a FTP based communication. Routes input to installed interpreter
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150707	Created 
//									
//******************************************************************************
class gzFtpConnection :	public gzTelnetConnection
{
public:

	GZ_BASE_EXPORT	gzFtpConnection();

	GZ_BASE_EXPORT	~gzFtpConnection();

	//! Factory
	GZ_BASE_EXPORT	virtual gzReference *clone() const;

protected:

	GZ_BASE_EXPORT	virtual gzVoid onInitialize();

	GZ_BASE_EXPORT	virtual gzVoid onFinalize();

	GZ_BASE_EXPORT	virtual gzVoid installInterpreter();

	GZ_BASE_EXPORT	virtual gzVoid unInstallInterpreter();

};

//******************************************************************************
// Class	: gzHTTPConnection
//									
// Purpose  : Base class for a HTTP based communication. Routes input to installed interpreter
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	190207	Created 
//									
//******************************************************************************
class gzHTTPConnection :	public gzTcpConnectionInterface,
							public gzInterpreterDataInterface
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT	gzHTTPConnection();

	//! Factory
	GZ_BASE_EXPORT	virtual gzReference *clone() const override;


	// Response
	GZ_BASE_EXPORT	virtual gzBool push(const gzUByte *adress, gzUInt32 len) override;

	GZ_BASE_EXPORT	virtual gzBool quit() override;

protected:

	GZ_BASE_EXPORT	virtual gzVoid onInitialize() override;

	GZ_BASE_EXPORT	virtual gzVoid onFinalize() override;

	GZ_BASE_EXPORT	virtual gzVoid onData(gzSocketAddress &from, gzUByte *adress, gzUInt32 len) override;

	GZ_BASE_EXPORT	virtual gzVoid installInterpreter();
	GZ_BASE_EXPORT	virtual gzVoid unInstallInterpreter();

	gzInterpreterPtr	m_interpreter;

	gzBatchManagerPtr	m_sender;
};


#endif //__GZ_TELNET_H__
