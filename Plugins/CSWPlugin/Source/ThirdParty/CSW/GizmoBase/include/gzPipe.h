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
// File			: gzPipe.h
// Module		: gzBase
// Description	: Class definition of Pipes classes
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
// AMO	030912	Created file 	
// AMO	240327	Added GZ_PIPE_QUERY_CUSTOM_INFO as custom query (2.12.140)
//
//******************************************************************************

#ifndef __GZ_PIPE_H__
#define __GZ_PIPE_H__

#include "gzBasicTypes.h"
#include "gzMemory.h"
#include "gzDynamic.h"
#include "gzThread.h"
#include "gzNotify.h"

/*!	\file
	\brief Pipe utilities
*/


class gzPipe; // Forward decl

class gzSocket; // Forward decl (from gzNetwork.h)


//! Pipe connection types
enum gzPipeConnection
{
	GZ_PIPE_LOCAL,
	GZ_PIPE_GLOBAL,
    GZ_PIPE_GLOBAL_IFACE
};

enum gzPipeQueryType
{
	GZ_PIPE_QUERY_BASIC,			//<! Query only name and ID
	GZ_PIPE_QUERY_DESCRIPTION,		//<! Query name,ID and description (+ public token)
	GZ_PIPE_QUERY_CUSTOM_INFO,		//<! Query custom information
};


//******************************************************************************
// Class	: gzPipeData
//									
// Purpose  : A data container used by the gzPipeServer
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030917	Created 
//									
//******************************************************************************
class gzPipeData
{
public:

	gzUByte *memory;
	gzUInt32 len;
};

typedef gzPipeData * gzPipeDataPtr;


//******************************************************************************
// Class	: gzPipeRecieveDataInterface
//									
// Purpose  : Interface to receive data from a pipe through a callback
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030917	Created 
//									
//******************************************************************************
//! Data reciever interface for a gzPipe
/*!
	Derive from this interface to get a thread driven reciever that gets notified
	by a gzPipe whenever there is new data or a gzPipe is closed.
*/
class gzPipeRecieveDataInterface : public gzNotifySlave<gzPipe,gzPipeRecieveDataInterface,gzPipeDataPtr>
{
public:

	//! override this method to recieve data from a pipe. Add receiver by the addSubscriber method in pipe
	virtual GZ_BASE_EXPORT gzVoid onPipeRecieveData(gzPipe *pipe, gzUByte *adress , gzUInt32 len)=0;

	//! override this method to recieve info when a pipe is broken
	virtual GZ_BASE_EXPORT gzVoid onPipeTerminate(gzPipe * /*pipe*/){};


	//! Used by the subscription mechanism. Do not use !
	gzVoid GZ_BASE_EXPORT onNotify(gzPipe *notifier,gzPipeDataPtr &data,gzUInt64 senderClass);

};

class gzPipeControlInterface;	// Forward decl

//******************************************************************************
// Class	: gzPipe
//									
// Purpose  : Actual named pipe implementation
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030917	Created 
// AMO	211111	Added startConnecting() to pipe and made stopConnecting() work on client	(2.11.47)
//									
//******************************************************************************
//! A named pipe class that implements bi-directional point-to-point communication
/*!
	A pipe can either local or global... \n

	Any number of instances can be created... \n

	blah...
*/
class gzPipe : public gzThread , public gzNotifyMaster<gzPipe,gzPipeRecieveDataInterface,gzPipeDataPtr> , public gzSerializeAdapter 
{
public:

	GZ_BASE_EXPORT gzPipe(gzPipeControlInterface *pipeControl=nullptr);

	GZ_BASE_EXPORT virtual ~gzPipe();

	//! Connect to a named pipe with name pipeName.
	/*! Set createPipe to TRUE to actually create the pipe.  */
	GZ_BASE_EXPORT gzBool connect( const gzString &name, gzBool create=FALSE, gzPipeConnection connection=GZ_PIPE_GLOBAL, gzUInt32 timeOutRetry=50 , const gzString &optionString=GZ_EMPTY_STRING);

	//! Connect to a named pipe with name pipeName using dedicated iface.
	/*! Set createPipe to TRUE to actually create the pipe.  */
	GZ_BASE_EXPORT gzBool connect(const gzString &name, const gzString & address, gzBool create=FALSE, gzUInt32 timeOutRetry=50,const gzString & optionString=GZ_EMPTY_STRING);

    //! Direct create a pipe
	GZ_BASE_EXPORT gzBool createPipe(const gzUInt16 port,gzUInt32 timeOutRetry=50);

	//! Direct open a pipe
	GZ_BASE_EXPORT gzBool openPipe(const gzString &address,gzUInt16 port,gzUInt32 timeOutRetry=50,const gzString & nic=GZ_EMPTY_STRING);

	//! Returns status if a pipe is connected.
	/*! A pipe can be connected/disconnected multiple times. */
	GZ_BASE_EXPORT gzBool isConnected() const;

	//! Tells the system to stop waiting in blocking connect pipes
	GZ_BASE_EXPORT gzVoid stopConnecting();

	//! Tells the system to start waiting in blocking connect pipes
	GZ_BASE_EXPORT gzVoid startConnecting();

	//! Force disconnection of pipe.
	GZ_BASE_EXPORT gzVoid disconnect(gzBool waitForRemoteConnection=TRUE);

	//! Write len bytes at adress.
	GZ_BASE_EXPORT gzUInt32 writePipe(const gzUByte *adress, gzUInt32 len);

	//! Read max maxlen len bytes to adress.
	/*! Default to blocking mode TRUE. Returns number of read bytes. */
	GZ_BASE_EXPORT gzUInt32 readPipe( gzUByte *adress, gzUInt32 maxlen, gzBool blocking=TRUE);

	//! Tell you how many bytes there are pending in the pipe to be read.
	GZ_BASE_EXPORT gzUInt32 pendingBytes();

	GZ_BASE_EXPORT gzBool terminate( const gzString &name,const gzString &address=GZ_EMPTY_STRING);
    
    GZ_BASE_EXPORT virtual gzVoid onNotifyStatus(gzPipeRecieveDataInterface * /*slave*/ ,gzNotifyState /*state*/ ) override {};

	GZ_BASE_EXPORT gzBool isActive() const override { return isConnected(); }

	// Control blocking
	GZ_BASE_EXPORT virtual gzBool setBlocking(gzBool blocking) override;
	GZ_BASE_EXPORT virtual gzBool isBlocking() const override;

	GZ_BASE_EXPORT gzSocket* getActiveSocket();
    
	// properties

	GZ_PROPERTY_EXPORT(		gzString,		PipeName,		GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzString,		PipeID,			GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzString,		RemotePipeID,	GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT( gzString,		Interface,		GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT( gzString,		Destination,	GZ_BASE_EXPORT);

	GZ_PROPERTY_GET_EXPORT(	gzUInt16,		PipePort,		GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT( gzUInt32,		TTL,			GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzBool,			DirectConnect,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzBool,			AutoReConnect,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzBool,			ConnectAsServer,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzBool,			NoDelay,		GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(		gzString,		Description,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzString,		Token,			GZ_BASE_EXPORT);

	GZ_PROPERTY_GET_EXPORT( gzUInt32,		Retry,			GZ_BASE_EXPORT);

	GZ_PROPERTY_MUTEX_EXPORT( gzBool,	AllocReceiveData,	m_threadSafeLocker,		GZ_BASE_EXPORT);

	GZ_PROPERTY_MUTEX_EXPORT(gzDouble,	ReceiveTimeout,		m_threadSafeLocker,		GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT_I(gzBool, CloseOnNoConnection, GZ_BASE_EXPORT);

	GZ_BASE_EXPORT static gzString queryNamedPipe(const gzString & address = GZ_EMPTY_STRING, gzUInt32 retry = 10,gzBool extended=FALSE, gzPipeQueryType type= GZ_PIPE_QUERY_DESCRIPTION);

	// --------------------- Port Control ------------------------

	GZ_BASE_EXPORT static gzBool	setPortStart(gzUInt16 port);
	GZ_BASE_EXPORT static gzUInt16	getPortStart();

	GZ_BASE_EXPORT static gzBool	setPortRange(gzUInt16 count);
	GZ_BASE_EXPORT static gzUInt16	getPortRange();

	GZ_BASE_EXPORT static gzBool	hasAllocatedPorts();

	GZ_BASE_EXPORT static gzString	getProcessID();

	// Error interface

	GZ_BASE_EXPORT virtual gzBool	hasError() const override;
	GZ_BASE_EXPORT virtual gzString getError() const override;

	// Custom information

	GZ_BASE_EXPORT virtual gzString getCustomInfo();

protected:

	// Serialize interface

	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;

	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzVoid	write_imp(const gzUByte *data, gzUInt32 count) override;
	
	GZ_BASE_EXPORT virtual gzUInt32	read_imp(gzUByte *data, gzUInt32 maxcount) override;
	
	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

	GZ_BASE_EXPORT virtual gzBool	hasData_imp() override;
	
	GZ_BASE_EXPORT virtual gzVoid sub_process() {};	// Override when you need periodic ticking
	
private:

	gzBool createNamedPipe();
	gzBool openNamedPipe();

	GZ_BASE_EXPORT virtual gzVoid process() override;

	gzSocket*							m_pipeSocket;

	gzBool								m_createPipe;

	gzPipeConnection					m_connection:8;

	gzList<gzPipeRecieveDataInterface>	m_subscribers;

	gzString							m_optionString;

	gzPipeControlInterface				*m_pipeControl;
	
	gzUInt32							m_pipeRequestID;

	gzBool								m_stopConnecting;

	static gzMutex						s_lastRequestIDLocker;

	static gzDict<gzString,gzVoid>		s_lastRequestID;

	static	gzMutex						s_pipePortLocker;

	static gzQueue<gzUInt16>			s_pipePortStack;

	static gzBool						s_pipePortStackInitialised;

	static gzUInt16						s_pipePortStart;

	static gzUInt16						s_pipePortRange;
};

GZ_DECLARE_REFPTR(gzPipe);

//******************************************************************************
// Class	: gzPipeConnectionInterface
//									
// Purpose  : Controls the connection
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030917	Created 
//									
//******************************************************************************
class gzPipeControlInterface
{
public:
	// Connection management
	GZ_BASE_EXPORT virtual gzBool	onPipeOpenRequest(const gzPipe* /*pipe*/, const gzString& /*pipeID*/, const gzString& /*optionString*/) { return TRUE; }
	GZ_BASE_EXPORT virtual gzBool	onPipeOpenAck(const gzPipe* /*pipe*/, const gzString& /*pipeID*/, const gzString& /*optionString*/) { return TRUE; }
	GZ_BASE_EXPORT virtual gzString onPipeCustomInfo(const gzPipe* pipe) { return pipe->getDescription(); }
};

//******************************************************************************
// Class	: gzPipePacket
//									
// Purpose  : A data container used by the gzPipeServer
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030917	Created 
//									
//****************************************************************************** 
class gzPipePacket : public gzReference
{
public:

	gzPipePtr								sender;

	gzRecycleData<gzDynamicArray<gzUByte> >	data;
};

//******************************************************************************
// Class	: gzPipeServer
//									
// Purpose  : Actual named pipe server implementation. Echoes between all pipes
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030917	Created 
//									
//******************************************************************************
//! A named pipe server class that echoes all data to all pipe clients
/*! 
	Data sent from one client is routed by the server to all other clients.
	The actual client doesn't recieve  its own data.
	Only clients on the actual instance of the server, gets notified.
*/
class gzPipeServer : public gzThread , public gzPipeRecieveDataInterface , public gzPipeControlInterface , public gzSerializeAdapter
{
public:

	GZ_BASE_EXPORT gzPipeServer(const gzString &pipeName,const gzString &options=GZ_EMPTY_STRING,gzBool allocReceiveData=TRUE);

	GZ_BASE_EXPORT virtual ~gzPipeServer();

	GZ_BASE_EXPORT gzVoid doEchoPipeData(gzBool on);

	GZ_BASE_EXPORT virtual gzVoid stop(gzBool waitForStop=FALSE) override;

	GZ_BASE_EXPORT gzBool isActive() const override;

	GZ_BASE_EXPORT gzString getPipeName() const;

	GZ_PROPERTY_EXPORT(gzBool,		BlockingRead,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,		Echo,				GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,		AllocReceiveData,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,	BlockingTimeout,	GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzString,	Description,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,	Token,				GZ_BASE_EXPORT);

protected:

	// Serialize interface

	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;

	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzVoid	write_imp(const gzUByte *data, gzUInt32 count) override;
	
	GZ_BASE_EXPORT virtual gzUInt32	read_imp(gzUByte *data, gzUInt32 maxcount) override;
	
	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

	
	GZ_BASE_EXPORT gzVoid addPackage(gzPipe *sender, const gzUByte *adress, gzUInt32 len);


	virtual GZ_BASE_EXPORT gzVoid onPipeRecieveData(gzPipe *pipe, gzUByte *adress, gzUInt32 len) override;

	virtual GZ_BASE_EXPORT gzVoid onPipeTerminate(gzPipe *pipe) override;

	virtual GZ_BASE_EXPORT gzVoid process() override;

	GZ_BASE_EXPORT	gzVoid takePacket();

	gzString				m_pipeName;	

	gzRefList<gzPipe>		m_pipeList;

	gzPipe*					m_currentPipe;

	gzMutex					m_pipeLocker;

	gzBool					m_checkPipeRemoval:1;

	gzBool					m_doEchoPipeData:1;

	gzString				m_options;

	// -------------------- data packet ----------------

	gzUInt32					m_pendingBytes;

	gzMutex						m_dataLocker;

	gzRefList<gzPipePacket>		m_packets;

	gzRefPointer<gzPipePacket>	m_current;

	gzSerializeAdapterMemory	m_adapter;

//	gzDynamicArray<gzUByte>		m_buffer;

	// ------------------- batch ------------------------

	gzBatchManagerPtr			m_batchManager;

};


//******************************************************************************
// Class	: gzPipeURLServer
//									
// Purpose  : Works like a pipe URL server on remote hosts
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030917	Created 
//									
//******************************************************************************
class gzPipeURLServer : public gzPipeServer
{
public:

	GZ_BASE_EXPORT gzPipeURLServer(const gzString &pipeName,const gzString &options=GZ_EMPTY_STRING);

	GZ_BASE_EXPORT virtual ~gzPipeURLServer();

	GZ_PROPERTY_EXPORT(gzString,	AllowedGUID,		GZ_BASE_EXPORT);		// Only Allow a specific client pipe id separated by commas etc
	GZ_PROPERTY_EXPORT(gzBool,		AllowAbsoluteURL,	GZ_BASE_EXPORT);		// Shall we allow absolute path lookup
	GZ_PROPERTY_EXPORT(gzBool,		AllowBackstepURL,	GZ_BASE_EXPORT);		// Shall we allow .. path lookup
	GZ_PROPERTY_EXPORT(gzBool,		AllowRegistryURL,	GZ_BASE_EXPORT);		// Shall we allow $(xx) path lookup
	GZ_PROPERTY_EXPORT(gzBool,		AllowWrite,			GZ_BASE_EXPORT);		// Shall we allow writing to URL
	GZ_PROPERTY_EXPORT(gzString,	AllowedURLBases,	GZ_BASE_EXPORT);		// Only Allow a specific set of URL bases C:,D: separated by comma etc.
	GZ_PROPERTY_EXPORT(gzString,	BasePath,			GZ_BASE_EXPORT);		// When relative, the base path is used as relative search URL
	GZ_PROPERTY_EXPORT(gzString,	WhileListMach,		GZ_BASE_EXPORT);		// Only Allow a specific client mach id separated by commas etc
	GZ_PROPERTY_EXPORT(gzString,	BlackListMach,		GZ_BASE_EXPORT);		// Disallow a specific client mach id separated by commas etc
	GZ_PROPERTY_EXPORT(gzBool,		RequireMachID,		GZ_BASE_EXPORT);		// If true the server requires machid=xxx
	GZ_PROPERTY_EXPORT(gzString,	ClientOptions,		GZ_BASE_EXPORT);		// Set to client options when client connects OK

protected:

	GZ_BASE_EXPORT virtual gzBool	onPipeOpenRequest(const gzPipe *pipe,const gzString &pipeID , const gzString &optionString) override;
	GZ_BASE_EXPORT virtual gzBool	onPipeOpenAck(const gzPipe* pipe,const gzString &pipeID , const gzString &optionString) override;

	GZ_BASE_EXPORT virtual gzVoid	onPipeRecieveData(gzPipe *pipe, gzUByte *adress , gzUInt32 len) override;

	GZ_BASE_EXPORT virtual gzString onPipeCustomInfo(const gzPipe* pipe) override;

private:

	gzBool checkURL(gzString &url);  // Check and modify URL
};

GZ_DECLARE_REFPTR(gzPipeURLServer);

// ---------------------------- Purl 2.0 management ---------------------------------------------

const gzUInt8	GZ_PURL_PROTOCOL_VERSION =	2;		// NEW version 2

const gzUInt32	GZ_PURL_PROTOCOL_MAGIC = 0xFCDBA576u;

const gzUInt32	GZ_PURL_BUFFER_LEN = 500;

const gzDouble	GZ_PURL_PROTOCOL_TIMEOUT = 0.1;


enum gzPurlCommand : gzUInt8
{
	GZ_PURL_COMMAND_REQUEST_FILE,			// 0
	GZ_PURL_COMMAND_FILE_DATA,				// 1
	GZ_PURL_COMMAND_ERROR,					// 2
	GZ_PURL_COMMAND_SAVE_FILE,				// 3	
	GZ_PURL_COMMAND_OK,						// 4
	GZ_PURL_COMMAND_REQUEST_SAVE_FILE,		// 5
	GZ_PURL_COMMAND_REQUEST_DATA,			// 6			// Request data
	GZ_PURL_COMMAND_DATA,					// 7			// Data as answer on request
	GZ_PURL_COMMAND_AVAIL_DATA,				// 8			// Spontaneous publish by time or on connect
	GZ_PURL_COMMAND_SUBSCRIBE_DATA,			// 9			// Subscribe AVAIL 
	GZ_PURL_COMMAND_UNSUBSCRIBE_DATA,		// 10			// Unsubscribe AVAIL 
	GZ_PURL_COMMAND_DELETE_FILE,			// 11			// Delete file if allowed save/modify
};

// --------------- GZ_PURL_COMMAND_REQUEST_FILE ---------------------

class gzPurlCommandRequestFile : public gzSerializeData		
{
public:

	gzString					url;

	gzSerializeAdapterFlags		flags;

	gzString					password;

	GZ_DECLARE_SERIALIZE_3("RequestFile", url,flags,password);
};

// --------------- GZ_PURL_COMMAND_ERROR ---------------------

class gzPurlCommandError : public gzSerializeData
{
public:

	gzMessageLevel				level;

	gzString					error;

	gzString					sender;

	gzSerializeAdapterError		errorType;		// Set to GZ_SERIALIZE_ADAPTER_ERROR_OTHER if not related to URL ADAPTER

	GZ_DECLARE_SERIALIZE_4("Error", level,error,sender,errorType);
};

// --------------- GZ_PURL_COMMAND_SAVE_FILE ---------------------

class gzPurlCommandSaveFile : public gzSerializeData
{
public:

	gzString					url;

	gzSerializeAdapterFlags		flags;

	gzString					password;

	gzBool						accnowledge;	// True means we want answers back that everything went ok or errors

	GZ_DECLARE_SERIALIZE_4("SaveFile", url,flags,password,accnowledge);
};

// --------------- GZ_PURL_COMMAND_REQUEST_SAVE_FILE ---------------------

class gzPurlCommandRequestSaveFile : public gzSerializeData
{
public:
	 
	gzString					url;
	
	GZ_DECLARE_SERIALIZE_1("RequestSaveFile", url);
};

// --------------- GZ_PURL_COMMAND_REQUEST_DATA ---------------------

class gzPurlCommandRequestData : public gzSerializeData
{
public:

	gzGUID			id;

	gzString		topic;

	gzDynamicType	parameters;

	GZ_DECLARE_SERIALIZE_3("RequestData", id, topic, parameters);
};

// --------------- GZ_PURL_COMMAND_DATA ---------------------

class gzPurlCommandData : public gzSerializeData
{
public:

	gzGUID			id;

	gzString		topic;

	gzDynamicType	result;

	GZ_DECLARE_SERIALIZE_3("Data", id, topic, result);
};

// --------------- GZ_PURL_COMMAND_AVAIL_DATA ---------------------

class gzPurlCommandAvailableData : public gzSerializeData
{
public:

	gzGUID			id;

	gzString		topic;

	gzDouble		time;

	gzDynamicType	parameters;


	GZ_DECLARE_SERIALIZE_4("Avail", id, topic, time, parameters);
};

// --------------- GZ_PURL_COMMAND_SUBSCRIBE_DATA ---------------------

class gzPurlCommandSubscribeData : public gzSerializeData
{
public:

	gzGUID			subscriber_id;

	gzString		topic;

	gzDynamicType	parameters;


	GZ_DECLARE_SERIALIZE_3("Sub", subscriber_id, topic, parameters);
};

// --------------- GZ_PURL_COMMAND_UNSUBSCRIBE_DATA ---------------------

class gzPurlCommandUnSubscribeData : public gzSerializeData
{
public:

	gzGUID			subscriber_id;

	gzString		topic;

	gzDynamicType	parameters;


	GZ_DECLARE_SERIALIZE_3("UnSub", subscriber_id, topic, parameters);
};

// --------------- GZ_PURL_COMMAND_DELETE_FILE ---------------------

class gzPurlCommandDeleteFile : public gzSerializeData
{
public:

	gzString					url;

	GZ_DECLARE_SERIALIZE_1("DelFile", url);
};

// ------------------------------ Purl Serialize Command Utilities --------------------------------------

// Adapter version ------------

GZ_BASE_EXPORT gzBool gzSendPurlCommand(gzSerializeAdapter* pipe, gzPurlCommand command, gzUInt32 payload_size = 0, gzSerializeData* command_payload = NULL);
GZ_BASE_EXPORT gzBool gzSendPurlPayload(gzSerializeAdapter* pipe, gzSerializeAdapter* adapter);
GZ_BASE_EXPORT gzBool gzSendPurlError(gzSerializeAdapter* pipe, const gzString& error,const gzSerializeAdapterError &errorType = GZ_SERIALIZE_ADAPTER_ERROR_OTHER, gzMessageLevel level = GZ_MESSAGE_FATAL, const gzString& sender = "GizmoSDK", gzBool echo = TRUE);

// Receivers -----------------

//! data_payload_length is the expected remaining bytes to read
GZ_BASE_EXPORT gzBool gzReceivePurlCommand(gzSerializeAdapter* pipe, gzPurlCommand& command, gzUInt32& data_payload_length, gzUInt32 retry = 50, gzString* errorString = NULL);
GZ_BASE_EXPORT gzBool gzReceivePurlCommandPayload(gzSerializeAdapter* pipe, gzSerializeData* data, gzUInt32 &data_payload_length, gzUInt32 retry = 50, gzString* errorString = NULL);
GZ_BASE_EXPORT gzBool gzReceivePurlPayload(gzSerializeAdapter* pipe, gzSerializeAdapter* adapter, gzUInt32 &data_payload_length, gzUInt32 retry = 50, gzString* errorString = NULL, gzString* progressString=nullptr);

//******************************************************************************
// Class	: gzPipeWriter
//									
// Purpose  : A batch work that can be added to write from another thread to a pipe
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
class gzPipeWriter : public gzBatchWork
{
public:

	GZ_BASE_EXPORT	virtual gzVoid work() override;

	// Some public data
	// data is written to adapter once using a batch manager

	gzRecycledBuffer			data;
	gzPipePtr					connection;
};

// ------ Enums for expected data -------------------------------------------------------------------------

enum gzExpectedPurlCommandBits
{

	GZ_EXPECT_PURL_COMMAND_REQUEST_FILE			= 1 << GZ_PURL_COMMAND_REQUEST_FILE,			// 0
	GZ_EXPECT_PURL_COMMAND_FILE_DATA			= 1 << GZ_PURL_COMMAND_FILE_DATA,				// 1
	GZ_EXPECT_PURL_COMMAND_ERROR				= 1 << GZ_PURL_COMMAND_ERROR,					// 2
	GZ_EXPECT_PURL_COMMAND_SAVE_FILE			= 1 << GZ_PURL_COMMAND_SAVE_FILE,				// 3	
	GZ_EXPECT_PURL_COMMAND_OK					= 1 << GZ_PURL_COMMAND_OK,						// 4
	GZ_EXPECT_PURL_COMMAND_REQUEST_SAVE_FILE	= 1 << GZ_PURL_COMMAND_REQUEST_SAVE_FILE,		// 5
	GZ_EXPECT_PURL_COMMAND_REQUEST_DATA			= 1 << GZ_PURL_COMMAND_REQUEST_DATA,			// 6			// Request data
	GZ_EXPECT_PURL_COMMAND_DATA					= 1 << GZ_PURL_COMMAND_DATA,					// 7			// Data as answer on request
	GZ_EXPECT_PURL_COMMAND_AVAIL_DATA			= 1 << GZ_PURL_COMMAND_AVAIL_DATA,				// 8			// Spontaneous publish by time or on connect
	GZ_EXPECT_PURL_COMMAND_SUBSCRIBE_DATA		= 1 << GZ_PURL_COMMAND_SUBSCRIBE_DATA,			// 9			// Subscribe AVAIL 
	GZ_EXPECT_PURL_COMMAND_UNSUBSCRIBE_DATA		= 1 << GZ_PURL_COMMAND_UNSUBSCRIBE_DATA,		// 10			// Unsubscribe AVAIL 

	GZ_EXPECT_PURL_COMMAND_ALL = 0xffff,	// All bits set
	GZ_EXPECT_PURL_COMMAND_NOTHING = 0,		// No bits set, All messages through mux
};

GZ_USE_BIT_LOGIC(gzExpectedPurlCommandBits);

// ------ Purl Mux so we can work async -------------------------------------------------------------------

class gzPurlMux
{
public:

	// To get payload, you must provide a buffer in (receive topic or query topic)

	virtual gzBool onCommandData(const gzPurlCommandData& /*data*/, gzArray<gzUByte>* /*payload*/) { return TRUE; }
	virtual gzBool onCommandAvail(const gzPurlCommandAvailableData& /*avail*/, gzArray<gzUByte>* /*payload*/) { return TRUE; }
	virtual gzBool onCommandRequest(const gzPurlCommandRequestData& /*request*/, gzArray<gzUByte>* /*payload*/) { return TRUE; }
	virtual gzBool onCommandSubscribe(const gzPurlCommandSubscribeData& /*subscribe*/, gzArray<gzUByte>* /*payload*/) { return TRUE; }
	virtual gzBool onCommandUnSubscribe(const gzPurlCommandUnSubscribeData& /*unsubscribe*/, gzArray<gzUByte>* /*payload*/) { return TRUE; }
	virtual gzBool onCommandError(const gzPurlCommandError& /*error*/, gzArray<gzUByte>* /*payload*/) { return TRUE; }

	virtual gzBool stopPolling() { return FALSE; }
};

// ---------------------------------------- Topic Utilties ------------------------------------------------

GZ_BASE_EXPORT gzBool			gzSubscribeTopic(gzSerializeAdapter* adapter, const gzString& topic, const gzGUID& subscriber_id, const gzDynamicType& parameters = gzDynamicTypeVoid(), const gzArray<gzUByte>* payload = NULL);
GZ_BASE_EXPORT gzBool			gzUnSubscribeTopic(gzSerializeAdapter* adapter, const gzString& topic, const gzGUID& subscriber_id, const gzDynamicType& parameters = gzDynamicTypeVoid(), const gzArray<gzUByte>* payload = NULL);
GZ_BASE_EXPORT gzBool			gzRequestData(gzSerializeAdapter* adapter, const gzString& topic, const gzGUID& id, const gzDynamicType& parameters = gzDynamicTypeVoid(), const gzArray<gzUByte>* payload = NULL);
GZ_BASE_EXPORT gzBool			gzAvailableData(gzSerializeAdapter* adapter, const gzString& topic, const gzGUID& id, const gzDouble& time = 0, const gzDynamicType& parameters = gzDynamicTypeVoid(), const gzArray<gzUByte>* payload = NULL);
GZ_BASE_EXPORT gzDynamicType	gzReceiveTopic(gzSerializeAdapter* adapter, const gzGUID& id, gzArray<gzUByte>* payload = NULL, gzPurlMux *mux=nullptr, gzUInt32 retry = 50, gzDouble timeOut = 10 , gzExpectedPurlCommandBits expect=GZ_EXPECT_PURL_COMMAND_ALL);
GZ_BASE_EXPORT gzDynamicType	gzQueryTopic(gzSerializeAdapter* adapter, const gzString& topic, const gzDynamicType& parameters = gzDynamicTypeVoid(), const gzGUID& id = gzGUID::generateGUID(), gzArray<gzUByte>* payload = NULL, gzPurlMux *mux=nullptr, gzUInt32 retry = 50, gzDouble timeOut = 10);


#endif // __GZ_PIPE_H__

