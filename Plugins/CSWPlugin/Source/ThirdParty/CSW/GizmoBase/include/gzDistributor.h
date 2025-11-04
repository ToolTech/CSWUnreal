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
// File			: gzDistributor.h
// Module		: gzBase
// Description	: Class definition of SW distribution service
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
// AMO	190107	Created file 	
// AMO	191022	Changed to 1.22 as we need to update time protocol (2.10.4)
// AMO	191929	Changed API for response boost (2.10.4)
// AMO	201126	Added ServerBroadcastMessage ->1.30 (2.10.6)
// AMO	220902	Changed to version 1.35 with changed scenebuilderclient behaviour	(2.12.1)
// AMO	230906	Added version check of gzBase library (2.12.97)
//
//******************************************************************************

#ifndef __GZ_DISTRIBUTOR_H__
#define __GZ_DISTRIBUTOR_H__

#include "gzLex.h"
#include "gzService.h"
#include "gzModule.h"
#include "gzTelnet.h"

const gzString GZ_DEFAULT_DISTRIBUTOR_COM_URL = "udp:235.6.6.6:65432?blocking=no";

const gzUInt32 GZ_DISTRIBUTOR_PROTOCOL_VERSION = 137;		// version 1.37 -> (2.12.97)

const gzUInt64 GZ_DISTRIBUTOR_PROTOCOL_MAGIC = LLU(0xABDEF18569FBA39F);

const gzUInt32 GZ_DISTRIBUTOR_HEADER_SIZE = 16;	

const gzString GZ_NO_EXIST_FILE = "xx";

const gzString GZ_DISTRIBUTOR_CONNECT_ANY = "any";

// Reg Keys entries

const gzString GZ_DISTRIBUTOR_REG_KEY_CONNECTION	= "distributor/connection/";
const gzString GZ_DISTRIBUTOR_REG_KEY_COM_URL		= "distributor/communication/url";
const gzString GZ_DISTRIBUTOR_REG_KEY_CAP_WORK		= "distributor/capabilities/workers";

// File times

enum gzDistributorCommand
{
	GZ_DC_SERVER_ID,				// 0
	GZ_DC_PING_REQUEST,				// 1
	GZ_DC_PING_REPLY,				// 2
	GZ_DC_FILE_INFO,				// 3
	GZ_DC_FILE_REQUEST,				// 4
	GZ_DC_FILE_DATA,				// 5
	GZ_DC_QUERY_CAPS,				// 6
	GZ_DC_CAPABILITY,				// 7
	GZ_DC_TIME,						// 8
	GZ_DC_WORK,						// 9
	GZ_DC_WORK_RESULT,				// 10
	GZ_DC_ALIVE,					// 11
	GZ_DC_CONFIG,					// 12
	GZ_DC_DATA_REQUEST,				// 13
	GZ_DC_DATA,						// 14
	GZ_DC_APPEND_WORK,				// 15
	GZ_DC_START_SERVER,				// 16
	GZ_DC_STOP_SERVER,				// 17
	GZ_DC_START_WORKING,			// 18
	GZ_DC_READY_TO_WORK,			// 19
	GZ_DC_REST_COMMAND,				// 20
	GZ_DC_REGISTER_MESSAGE,			// 21
	GZ_DC_UNREGISTER_MESSAGE,		// 22
	GZ_DC_MESSAGE,					// 23
	GZ_DC_SERVER_BROADCAST,			// 24
	GZ_DC_CLIENT_REBOOT,			// 25
	GZ_DC_CLIENT_RESET,				// 26

	GZ_DC_INVALID_COMMAND=9999,
};

class gzDistributorCommandServerId : public gzSerializeData
{
public:

	gzString	name;
	gzString	ip;
	gzString	url;
	gzGUID		guid;
	gzUInt32	protocol_version;

	gzUInt32	major_version;
	gzUInt32	minor_version;
	gzUInt32	variant_version;

	GZ_DECLARE_SERIALIZE_8("SERVER_ID", name, ip, url, guid,protocol_version,major_version,minor_version,variant_version);
};

class gzDistributorCommandPingRequest : public gzSerializeData
{
public:

	gzGUID		guid;
	gzUInt32	protocol_version;
	
	GZ_DECLARE_SERIALIZE_2("PING_REQUEST", guid, protocol_version);
};

class gzDistributorCommandPingReply : public gzSerializeData
{
public:
	
	gzUInt32	protocol_version;	// Version

	gzString	classid;			// What type of class we are
	gzString	ip;
	gzString	host;
	gzGUID		guid;
	

	GZ_DECLARE_SERIALIZE_5("PING_REPLY", protocol_version,classid,ip,host,guid);
};

class gzDistributorCommandFileInfo : public gzSerializeData
{
public:

	gzString	url;
	gzUInt32	crc;
	gzUInt64	length;
	gzBool		local;
	gzBool		immediateLoad;

	GZ_DECLARE_SERIALIZE_5("FILE_INFO",url,crc,length,local, immediateLoad);
};

class gzDistributorCommandFileRequest : public gzSerializeData
{
public:

	gzString				url;			// url local or global
	gzSerializeAdapterFlags flags;			// adapter flags
	gzGUID					requestID;		// id of request
	gzGUID					batchID;		// id of batch work
	gzDouble				time;			// timestamp systemSeconds
	gzUInt64				offset;			// =0 for full file
	gzUInt32				length;			// =0 for full file	, Can only request UInt32 size
	gzBool					check;			// = TRUE for file length or exist
	gzBool					local;			// = TRUE for local file storage
	gzBool					store;			// = TRUE for immediate store
	gzBool					immediateLoad;	// = TRUE for immediate load. Just load current url as is

	GZ_DECLARE_SERIALIZE_11("FILE_REQUEST", url,flags,requestID,batchID,time,offset,length,check,local,store,immediateLoad);
};

class gzDistributorCommandFileData : public gzSerializeData
{
public:

	gzString				url;
	gzString				error;
	gzSerializeAdapterFlags	flags;
	gzGUID					requestID;		// id of request
	gzGUID					batchID;		// id of batch work
	gzDouble				time;			// timestamp from request system
	gzArray<gzUByte>		data;
	gzUInt64				offset;			// =0 for full file
	gzUInt64				length;			// total length of file when check=TRUE
	gzBool					check;			// = TRUE for file length or exist
	gzBool					local;
	gzBool					store;
	gzBool					immediateLoad;

	GZ_DECLARE_SERIALIZE_13("FILE_REPLY", url,error,flags,requestID,batchID,time,data,offset,length,check,local,store,immediateLoad);
};

enum gzDistributorCapability
{
	GZ_DISTRIBUTOR_CAPS_ALL,
	GZ_DISTRIBUTOR_CAPS_WORKERS,		// Query number of workers
};

class gzDistributorCommandQueryCapability : public gzSerializeData
{
public:

	gzDistributorCapability		capability;

	GZ_DECLARE_SERIALIZE_1("QUERY_CAPS", capability);
};

class gzDistributorCommandCapability : public gzSerializeData
{
public:

	gzDistributorCapability		capability;

	gzDynamicType				value;

	GZ_DECLARE_SERIALIZE_2("CAPS", capability,value);
};

class gzDistributorCommandTime : public gzSerializeData
{
public:

	gzDouble		systemTime;

	gzDouble		offset;

	gzDouble		latency;

	gzDouble		systemTimeDiff;

	GZ_DECLARE_SERIALIZE_4("TIME", systemTime, offset, latency, systemTimeDiff);
};

class gzDistributorCommandWork : public gzSerializeData
{
public:

	gzString		module;
	gzString		method;
	gzDynamicType	a0;
	gzDynamicType	a1;
	gzDynamicType	a2;
	gzDynamicType	a3;
	gzGUID			workID;
	gzGUID			batchID;
	gzDouble		startTime;
	gzString		host;

	GZ_DECLARE_SERIALIZE_10("WORK", module, method, a0, a1, a2, a3, workID, batchID, startTime, host);
};

class gzDistributorCommandWorkResult : public gzSerializeData
{
public:

	gzString		error;
	gzString		worker;
	gzString		ip;
	gzGUID			workID;
	gzGUID			batchID;
	gzDouble		processTime;
	gzDouble		latency;
	gzDynamicType	result;

	GZ_DECLARE_SERIALIZE_8("WORK_RESULT", error,worker,ip,workID,batchID, processTime,latency,result);
};

class gzDistributorCommandConfiguration : public gzSerializeData
{
public:

	gzString		url;
	gzBool			local;

	GZ_DECLARE_SERIALIZE_2("CONFIG", url,local);
};

class gzDistributorCommandDataRequest : public gzSerializeData
{
public:

	gzString		name;
	gzDynamicType	parameters;
	gzGUID			requestID;

	GZ_DECLARE_SERIALIZE_3("DATA_REQ", name,parameters, requestID);
};

class gzDistributorCommandData : public gzSerializeData
{
public:

	gzString			name;
	gzDynamicType		data;
	gzGUID				requestID;

	GZ_DECLARE_SERIALIZE_3("DATA", name, data, requestID);
};

class gzDistributorCommandAppendWork : public gzSerializeData
{
public:

	gzString		module;
	gzString		method;
	gzDynamicType	a0;
	gzDynamicType	a1;
	gzDynamicType	a2;
	gzDynamicType	a3;
	gzGUID			workID;
	gzString		host;
	gzString		classid;			// What type of class we are

	GZ_DECLARE_SERIALIZE_9("APPEND_WORK", module, method, a0, a1, a2, a3, workID,host,classid);
};


class gzDistributorCommandServer : public gzSerializeData
{
public:

	gzString	host;
	gzString	classid;			// What type of class we are		

	GZ_DECLARE_SERIALIZE_2("SERVER", host,classid);
};

enum gzRestCommands 
{
	GZ_REST_OPTIONS, 
	GZ_REST_GET, 
	GZ_REST_HEAD, 
	GZ_REST_POST, 
	GZ_REST_PUT, 
	GZ_REST_DEL
};

class gzDistributorCommandREST : public gzSerializeData
{
public:

	gzRestCommands	command;
	gzString		uri;			
	gzString		json;

	GZ_DECLARE_SERIALIZE_3("REST", command, uri, json);
};

class gzDistributorCommandMessage : public gzSerializeData
{
public:

	gzString		sender;
	gzMessageLevel	level;
	gzString		message;

	GZ_DECLARE_SERIALIZE_3("MESS", sender,level,message);
};

class gzDistributorCommandServerBroadcast : public gzSerializeData
{
public:

	gzString		message;

	gzDynamicType	parameter;

	GZ_DECLARE_SERIALIZE_2("BROADCAST", message, parameter);
};

class gzDistributorCommandClientReboot : public gzSerializeData
{
public:

	gzString		message;

	GZ_DECLARE_SERIALIZE_1("REBOOT", message);
};

// ----------------------------------------------------------------------------------------------------------------

GZ_BASE_EXPORT gzBool gzSendDistributorCommand(gzSerializeAdapter *adapter, gzDistributorCommand command, gzSerializeData *data);

// ----------------------------------------------------------------------------------------------------------------

class gzDistributorFileData : public gzThreadSafeReference
{
public:

	gzString				url;
	gzGUID					requestID;
	gzString				error;
	gzBool					check;
	gzUInt64				length;
	gzUInt64				offset;
	gzArray<gzUByte>		data;
	gzDouble				systime;
};

GZ_DECLARE_REFPTR(gzDistributorFileData);

// -------------------- State --------------------------------------------------------------------------------------

enum gzDistributorState
{
	GZ_DISTRIBUTOR_STATE_NOT_INITIALIZED,
	GZ_DISTRIBUTOR_STATE_WAITING_FOR_CONNECTION,
	GZ_DISTRIBUTOR_STATE_RUNNING,
	GZ_DISTRIBUTOR_STATE_CONNECTION_ERROR,
	GZ_DISTRIBUTOR_STATE_COMM_ERROR,
	GZ_DISTRIBUTOR_STATE_LOST_CONNECTION,
	GZ_DISTRIBUTOR_STATE_REBOOT,
};


// ------------------------------------------- gzDistributor -------------------------------------------------------

class gzDistributor :	public gzService,
						public gzSerializeURLManagerInterface,
						public gzMessageReceiverInterface
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzDistributor(const gzString &name, const gzString &info);

	GZ_BASE_EXPORT virtual ~gzDistributor();
	
	//! Main Loop
	GZ_BASE_EXPORT virtual gzVoid process(const gzArgumentParser &args, gzBool runAsService) override;

	GZ_PROPERTY_EXPORT(gzString, ConfigURL, GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzBool pollCommands(gzSerializeAdapter *adapter,gzBool *gotCommand);

	GZ_BASE_EXPORT virtual gzBool onCommand(gzDistributorCommand command, gzUInt32 length,gzSerializeAdapter *adapter);
	GZ_BASE_EXPORT virtual gzBool onServerId(gzDistributorCommandServerId *mess);
	GZ_BASE_EXPORT virtual gzBool onPingRequest(gzDistributorCommandPingRequest *mess);
	GZ_BASE_EXPORT virtual gzBool onPingReply(gzDistributorCommandPingReply *mess);
	GZ_BASE_EXPORT virtual gzBool onFileInfo(gzDistributorCommandFileInfo *mess);
	GZ_BASE_EXPORT virtual gzBool onFileData(gzDistributorCommandFileData *mess);
	GZ_BASE_EXPORT virtual gzBool onQueryCapability(gzDistributorCommandQueryCapability *mess);
	GZ_BASE_EXPORT virtual gzBool onTime(gzDistributorCommandTime *mess);
	GZ_BASE_EXPORT virtual gzBool onWork(gzDistributorCommandWork *mess);
	GZ_BASE_EXPORT virtual gzBool onConfiguration(gzDistributorCommandConfiguration *mess);
	GZ_BASE_EXPORT virtual gzBool onServerBroadcast(gzDistributorCommandServerBroadcast* mess);
	GZ_BASE_EXPORT virtual gzBool onClientReboot(gzDistributorCommandClientReboot* mess);
	GZ_BASE_EXPORT virtual gzBool onClientReset();
	GZ_BASE_EXPORT virtual gzBool onProtocolMismatch(gzUInt32 currentVersion,gzUInt32 serverVersion);
	GZ_BASE_EXPORT virtual gzBool onVersionMismatch(gzUInt32 major, gzUInt32 minor, gzUInt32 variant);
	GZ_BASE_EXPORT virtual gzBool onMessage(gzDistributorCommandMessage* mess);


	GZ_BASE_EXPORT virtual gzBool onStartWorking();

	GZ_BASE_EXPORT virtual gzBool onDataRequest(gzDistributorCommandDataRequest * /*mess*/) { return TRUE; }
	GZ_BASE_EXPORT virtual gzBool onData(gzDistributorCommandData * /*mess*/) { return TRUE; }

	//! Called on new connection
	GZ_BASE_EXPORT virtual gzBool onNewConnection() {  return TRUE; }

	//! Called on lost connection
	GZ_BASE_EXPORT virtual gzBool onLostConnection();

	//! Init of a distributor
	GZ_BASE_EXPORT virtual gzBool onInitialize(const gzArgumentParser &args, gzBool runAsService);
	//! UnInit of a distributor
	GZ_BASE_EXPORT virtual gzVoid onUninitialize();
		
	GZ_BASE_EXPORT gzDistributorState getDistributorState();
	
	GZ_BASE_EXPORT gzBool sendDistributorCommand(gzDistributorCommand command, gzSerializeData *data, gzBool useConnection=TRUE);
	GZ_BASE_EXPORT gzBool sendCapsWorkers();
	GZ_BASE_EXPORT gzBool sendAlive();
	GZ_BASE_EXPORT gzBool sendPing();
	GZ_BASE_EXPORT gzBool sendDataRequest(const gzString &name,const gzGUID &id,const gzDynamicType &parameters=GZ_DYN_VOID);
	GZ_BASE_EXPORT gzBool sendData(const gzString &name, const gzGUID &id, const gzDynamicType& data);

	GZ_BASE_EXPORT gzVoid registerURLManager();
	GZ_BASE_EXPORT gzVoid unregisterURLManager();

	GZ_BASE_EXPORT gzVoid setResponseBoostDuration(const gzDouble& duration);
	GZ_BASE_EXPORT gzDouble getResponseBoostDuration() const;

	GZ_PROPERTY_EXPORT(gzDouble, Latency,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble, SystemTimeDiff,	GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzString, RemoteURLBase,		GZ_BASE_EXPORT);	// Deafult to remote:

	GZ_BASE_EXPORT gzSerializeAdapter*	getCommunicationAdapter() const;
	GZ_BASE_EXPORT gzSerializeAdapter*	getConnectionAdapter() const;
	GZ_BASE_EXPORT gzGUID				getGUID() const;

	GZ_BASE_EXPORT gzBool getFileData(gzSerializeAdapter* channel, gzDistributorCommandFileRequest* request, gzDistributorFileDataPtr& fileData, const gzDouble& timeOut, gzUInt32 timeoutLoops=1, gzString* errorString=nullptr, gzSerializeAdapterError* errorType=nullptr);

protected:

	// Url interface
	GZ_BASE_EXPORT virtual gzSerializeAdapter* getURLAdapter(const gzString& url, gzSerializeAction action, gzSerializeAdapterFlags flags, const gzString& password, gzString* errorString, gzSerializeAdapterError* errorType) override;
	GZ_BASE_EXPORT virtual gzBool getURLBaseEncoding(const gzString& _url, gzBool& _isAbsolute, gzString& _urlBase, gzString& _urlPath, gzString& _urlName, gzString& _urlAttributes, gzBool& _syntax_OK) override;

	// Message interface
	GZ_BASE_EXPORT gzVoid onMessage(const gzString& sender, gzMessageLevel level, const char* message) override;

	//! Called on every process cycle
	GZ_BASE_EXPORT virtual gzBool onProcess() { return TRUE; }

	gzSerializeAdapterPtr				m_communicationAdapter;
	gzSerializeAdapterPtr				m_connectionAdapter;
	gzMutex								m_connectionLock;

	gzDistributorState					m_state;

	gzGUID								m_guid;

	gzEvent								m_fileDataLock;
	gzRefList<gzDistributorFileData>	m_fileData;

	gzBatchManagerPtr					m_batchManager;

	gzMutex								m_responseBoostLock;
	gzDouble							m_responseBoostStartTime;
	gzDouble							m_responseBoostDuration;

	gzLoggerPtr							m_logger;
};

GZ_DECLARE_REFPTR(gzDistributor);

class gzDistributorAdapterRead : public gzSerializeAdapterPacket
{
public:

	GZ_BASE_EXPORT gzDistributorAdapterRead(gzDistributor* distributor, gzSerializeAdapter* channel, gzUInt64 length, const gzGUID& batchID);

	GZ_BASE_EXPORT virtual gzVoid onRequestData(gzUInt64 len) override;

private:

	virtual gzBool			can_seek_imp() override { return TRUE; }

	virtual gzMemSize		seek_imp(gzMemOffset offset, gzOriginPos origin) override;

	virtual gzUByte			read_imp() override;

	virtual gzUInt32		read_imp(gzUByte *adress,gzUInt32 len) override;

	virtual gzUInt32		length_imp() override;

	virtual gzUInt64		length_large_imp() override;

	virtual gzBool			eof_imp() override;

	gzDistributorPtr		m_distributor;

	gzSerializeAdapterPtr	m_channel;

	gzUInt64				m_length;

	gzUInt64				m_offset;

	gzGUID					m_batchID;
};

class gzDistributorAdapterWrite : public gzSerializeAdapterPacket
{
public:

	GZ_BASE_EXPORT gzDistributorAdapterWrite(gzSerializeAdapter* channel,const gzGUID & batchID):gzSerializeAdapterPacket(10000),m_channel(channel),m_batchID(batchID){}

	GZ_BASE_EXPORT virtual ~gzDistributorAdapterWrite();

private:

	gzSerializeAdapterPtr		m_channel;

	gzGUID						m_batchID;
};

// ------------------- Utility class for async sending data --------------------------

class gzThreadAdapterWriter : public gzBatchWork
{
public:

	GZ_BASE_EXPORT	virtual gzVoid work() override;

	// Some public data
	// data is written to adapter once using a batch manager
	gzRecycledBuffer		data;
	gzSerializeAdapterPtr	adapter;
};

#endif // __GZ_DISTRIBUTOR_H__
