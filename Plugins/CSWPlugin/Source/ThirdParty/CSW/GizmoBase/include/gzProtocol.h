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
// File			: gzProtocol.h
// Module		: gzBase
// Description	: Class definition of serialize protocol classes
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.275
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
// AMO	981019	Created file 	
// AMO	130103	Added faster handling of message body in entire packets (2.6.20)
// AMO	140117	Added gzSerializeAdapterUDP with default blocking read (2.7.4)
//
// ******************************************************************************

#ifndef __GZ_PROTOCOL_H__
#define __GZ_PROTOCOL_H__

/*!	\file 
	\brief Serialized Management of protocol based classes

*/

#include "gzSerialize.h"
#include "gzNotify.h"
#include "gzLex.h"
#include "gzNetwork.h"
#include "gzInterpreter.h"

//******************************************************************************
// Class	: gzSerializeAdapterHttp
//									
// Purpose  : Class for Serialize data to Web Server
//									
// Notes	: This class is responsible to write/read data to a http adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040203	Created 
//									
//******************************************************************************
class  gzSerializeAdapterHttp : public gzSerializeAdapter , 
								public gzNotifyInterface , 
								public gzParserFunction<gzSerializeAdapterHttp,gzBasicParser>
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterHttp(const gzString &url,gzSerializeAction action,gzSerializeAdapterFlags flags, const gzString &password, gzString *errorString=nullptr, gzSerializeAdapterError *errorType=nullptr);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterHttp();

	GZ_BASE_EXPORT virtual gzVoid flush() override;

	GZ_BASE_EXPORT gzBool openURL(const gzString &url);

	GZ_PROPERTY_GET_EXPORT(	gzString,		User				,GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzString,		Password			,GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzUInt16,		HostPort			,GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzString,		Host				,GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzString,		Path				,GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(		gzString,		AttributeString		,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzUInt32,		MajorVersion		,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzUInt32,		MinorVersion		,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzString,		UserAgent			,GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(		gzString,		DefaultUser			,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzUInt16,		DefaultHostPort		,GZ_BASE_EXPORT);

	
	GZ_PROPERTY_GET_EXPORT(	gzUInt32,		LastContentLength	,GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzString,		LastContentType		,GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzString,		LastContentBase		,GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(	gzUInt32,		LastErrorCode		,GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(		gzBool,			BlockingRead		,GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(		gzBool,			PacketMessageBody	,GZ_BASE_EXPORT);

    GZ_PROPERTY_EXPORT(		gzString,		NicAddress			,GZ_BASE_EXPORT);

	GZ_BASE_EXPORT	gzBool	hasPublicMethod(const gzString &methodName);
	GZ_BASE_EXPORT	gzVoid	addPublicMethod(const gzString &methodName);

	GZ_BASE_EXPORT	gzVoid	resetLastError();	

	// Errors
	GZ_BASE_EXPORT virtual gzString			getErrorMessage(gzUInt32 errorCode) const;

protected:

	// Utilities
	GZ_BASE_EXPORT			gzBool		waitForAnswer( gzUInt32 timeOut=GZ_WAIT_INFINITE);

	GZ_BASE_EXPORT virtual	gzVoid		initConnection();
	GZ_BASE_EXPORT virtual	gzVoid		sendOptionRequest();
	GZ_BASE_EXPORT virtual	gzVoid		sendGetRequest();
		
	// Adapter
	GZ_BASE_EXPORT	virtual gzVoid		write_imp(gzUByte data) override;
	GZ_BASE_EXPORT	virtual gzUByte		read_imp() override;

	GZ_BASE_EXPORT	virtual gzVoid		write_imp(const gzUByte *data,gzUInt32 count) override;
	GZ_BASE_EXPORT	virtual gzUInt32	read_imp(gzUByte *data,gzUInt32 maxcount) override;
	GZ_BASE_EXPORT	virtual gzUInt32	length_imp() override;
	GZ_BASE_EXPORT	virtual gzBool		hasData_imp() override;

	// parsing

	GZ_BASE_EXPORT virtual gzParseResult parseMessage();
	GZ_BASE_EXPORT virtual gzParseResult parseRequest();
	GZ_BASE_EXPORT virtual gzParseResult parseRequestLine();
	GZ_BASE_EXPORT virtual gzParseResult parseRequestHeader();
	GZ_BASE_EXPORT virtual gzParseResult parseRequestURI();
	GZ_BASE_EXPORT virtual gzParseResult parseResponse();
	GZ_BASE_EXPORT virtual gzParseResult parseResponseHeader();
	GZ_BASE_EXPORT virtual gzParseResult parseGeneralHeader();
	GZ_BASE_EXPORT virtual gzParseResult parseEntityHeader();
	GZ_BASE_EXPORT virtual gzParseResult parseStatusLine();
	GZ_BASE_EXPORT virtual gzParseResult parseMessageBody();
	GZ_BASE_EXPORT virtual gzParseResult parseVersion();
	GZ_BASE_EXPORT virtual gzParseResult parseStatusCode();
	GZ_BASE_EXPORT virtual gzParseResult parseReasonPhrase();
	GZ_BASE_EXPORT virtual gzParseResult parseWWWAuthenticate();
	GZ_BASE_EXPORT virtual gzParseResult parseAllow();
	GZ_BASE_EXPORT virtual gzParseResult parseContentBase();
	GZ_BASE_EXPORT virtual gzParseResult parseContentEncoding();
	GZ_BASE_EXPORT virtual gzParseResult parseContentLanguage();
	GZ_BASE_EXPORT virtual gzParseResult parseContentLength();
	GZ_BASE_EXPORT virtual gzParseResult parseContentLocation();
	GZ_BASE_EXPORT virtual gzParseResult parseContentType();
	GZ_BASE_EXPORT virtual gzParseResult parseExpires();
	GZ_BASE_EXPORT virtual gzParseResult parseLastModified();
	GZ_BASE_EXPORT virtual gzParseResult parseExtensionHeader();
	GZ_BASE_EXPORT virtual gzParseResult parseCacheControl();
	GZ_BASE_EXPORT virtual gzParseResult parseConnection();
	GZ_BASE_EXPORT virtual gzParseResult parseDate();
	GZ_BASE_EXPORT virtual gzParseResult parseVia();
	GZ_BASE_EXPORT virtual gzParseResult parseProductOrComment();
	GZ_BASE_EXPORT virtual gzParseResult parseServer();
	GZ_BASE_EXPORT virtual gzParseResult parseVary();
	GZ_BASE_EXPORT virtual gzParseResult parseRetryAfter();
	GZ_BASE_EXPORT virtual gzParseResult parsePublic();
	GZ_BASE_EXPORT virtual gzParseResult parseProxyAuthenticate();
	GZ_BASE_EXPORT virtual gzParseResult parseLocation();
	GZ_BASE_EXPORT virtual gzParseResult parseMethod();
	GZ_BASE_EXPORT virtual gzParseResult parseExtensionMethod();
	GZ_BASE_EXPORT virtual gzParseResult parseMethodList();
	GZ_BASE_EXPORT virtual gzParseResult parseCacheDirectiveList();
	GZ_BASE_EXPORT virtual gzParseResult parseCacheDirective();
	GZ_BASE_EXPORT virtual gzParseResult parseCacheResponse();
	GZ_BASE_EXPORT virtual gzParseResult parseCacheRequestDirective();
	GZ_BASE_EXPORT virtual gzParseResult parseFieldName();

	// Basics

	GZ_BASE_EXPORT gzParseResult parseToken();
	
	// Compounds

	GZ_BASE_EXPORT gzParseResult parseDigit_();
	GZ_BASE_EXPORT gzParseResult parseHEX_();
	GZ_BASE_EXPORT gzParseResult parseToken_();
	GZ_BASE_EXPORT gzParseResult parseTokenOrSP_();
	GZ_BASE_EXPORT gzParseResult parseLWS();
	GZ_BASE_EXPORT gzParseResult parseLWS_();
	GZ_BASE_EXPORT gzParseResult parseText();
	GZ_BASE_EXPORT gzParseResult parseText_();
	GZ_BASE_EXPORT gzParseResult parseTSpecials();
	GZ_BASE_EXPORT gzParseResult parseCText();
	GZ_BASE_EXPORT gzParseResult parseComment();
	GZ_BASE_EXPORT gzParseResult parseDQText();
	GZ_BASE_EXPORT gzParseResult parseDQString();
	GZ_BASE_EXPORT gzParseResult parseAbsoluteURI();
	GZ_BASE_EXPORT gzParseResult parseReserved();
	GZ_BASE_EXPORT gzParseResult parseSchemeToken();
	GZ_BASE_EXPORT gzParseResult parseScheme();
	GZ_BASE_EXPORT gzParseResult parseUChar();
	GZ_BASE_EXPORT gzParseResult parseEscaped();
	GZ_BASE_EXPORT gzParseResult parseUnreserved();
	GZ_BASE_EXPORT gzParseResult parseSafe();
	GZ_BASE_EXPORT gzParseResult parseUnsafe();
	GZ_BASE_EXPORT gzParseResult parseExtra();
	GZ_BASE_EXPORT gzParseResult parseNational();
	GZ_BASE_EXPORT gzParseResult parseMediaType();
	GZ_BASE_EXPORT gzParseResult parseParameter();
	GZ_BASE_EXPORT gzParseResult parseHostURI();
	GZ_BASE_EXPORT gzParseResult parseHostName();
	GZ_BASE_EXPORT gzParseResult parseDomainLabel();
	GZ_BASE_EXPORT gzParseResult parseTopLabel();
	GZ_BASE_EXPORT gzParseResult parseProduct();


	GZ_BASE_EXPORT gzBool checkMethod(const gzString &methodName);


	// Socket callback
	GZ_BASE_EXPORT virtual gzVoid onNotify(gzNotifyManager *master,gzRefPointer<gzNotifyMessage> &data,gzUInt64 senderClass) override;

	// parse callback
	GZ_BASE_EXPORT virtual gzVoid parseInput(gzUByte *buffer,gzUInt32 len);

	//! Part of message is message body
	GZ_BASE_EXPORT virtual gzVoid onMessageBody(gzUByte *buffer,gzUInt32 len);

	//! Entire packet is message body
	GZ_BASE_EXPORT virtual gzVoid onMessageBody(gzNetData *packet);

	// Must be called from inherited classes to permit destroy crashes.
	GZ_BASE_EXPORT gzVoid close();

	gzSerializeHttpState		m_serializeState;

	gzSerializeAction			m_action;

	gzSocket					m_socket;

	gzDict<gzString,gzVoid>		m_publicMethods;

	gzQueue<gzParseHttpState>	m_currentState;

	gzEvent						m_event;

	// data to be read from server
	gzUInt32					m_pendingBodyData;


	// Data items when used as HTTP adapter

	// data left to read from adapter

	// Moves packet from packets to adapter
	GZ_BASE_EXPORT	gzVoid takePacket();

	// Check current serialize state
	GZ_BASE_EXPORT	gzVoid checkSerializeState();

	gzUInt32					m_pendingBytes;

	gzMutex						m_dataLocker;

	gzRefList<gzNetData>		m_packets;

	gzRefPointer<gzNetData>		m_current;

	gzSerializeAdapterMemory	m_adapter;

private:

	gzBool						m_active;
};

//******************************************************************************
// Class	: gzSerializeAdapterUDP
//									
// Purpose  : Class for Serialize data to an UDP port
//									
// Notes	: This class is responsible to write/read data to a udp adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	131219	Created					(2.7.4)
//									
//******************************************************************************
class  gzSerializeAdapterUDP :	public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterUDP(const gzString &url,gzSerializeAction action=GZ_SERIALIZE_INPUT,gzSerializeAdapterFlags flags=GZ_SERIALIZE_ADAPTER_FLAGS_DEFAULT, const gzString &password=GZ_EMPTY_STRING, gzString *errorString = NULL, gzSerializeAdapterError *errorType = NULL);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterUDP();


	GZ_BASE_EXPORT gzBool openURL(const gzString &url);

	GZ_BASE_EXPORT gzVoid close();

	GZ_PROPERTY_EXPORT(		gzUInt16,		Port				,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzString,		AttributeString		,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzString,		DestinationAddress	,GZ_BASE_EXPORT);
    GZ_PROPERTY_EXPORT(		gzString,		NicAddress			,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzBool,			BlockingRead		,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzDouble,		BlockingTimeout		,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzUInt32,		MaxMTU				,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzUInt32,		MaxFetchPackets		,GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(		gzUInt32,       SendBufferSize,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzUInt32,		ReceiveBufferSize,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzUInt32,		TTL,				GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(		gzBool,			Echo,				GZ_BASE_EXPORT);

	GZ_BASE_EXPORT	gzVoid checkPacket();

	GZ_BASE_EXPORT gzBool	isActive() const override;

	GZ_BASE_EXPORT gzBool	hasError() const override;

protected:  

	// Adapter
	GZ_BASE_EXPORT	virtual gzVoid		write_imp(gzUByte data) override;
	GZ_BASE_EXPORT	virtual gzUByte		read_imp() override;

	GZ_BASE_EXPORT	virtual gzVoid		write_imp(const gzUByte *data,gzUInt32 count) override;
	GZ_BASE_EXPORT	virtual gzUInt32	read_imp(gzUByte *data,gzUInt32 maxcount) override;
	GZ_BASE_EXPORT	virtual gzUInt32	length_imp() override;
	GZ_BASE_EXPORT	virtual gzBool		hasData_imp() override;

	// Moves packet from packets to adapter
	GZ_BASE_EXPORT	gzVoid takePacket();

	gzUInt32					m_pendingBytes;

	gzMutex						m_dataLocker;

	gzRefList<gzNetData>		m_packets;

	gzRefPointer<gzNetData>		m_current;

	gzSerializeAdapterMemory	m_adapter;

	gzDynamicArray<gzUByte>		m_buffer;


	gzSocketAddress				m_destinationAddress;
	gzHostAddress				m_interfaceAddress;

	gzSocket					m_sendSocket;
	gzSocketAddress				m_sendSocketAddress;

	gzSocket					m_receiveSocket;
	gzSocketAddress				m_receiveSocketAddress;

	gzSocketAddress				m_senderAddress;

};

GZ_DECLARE_REFPTR(gzSerializeAdapterUDP);

//******************************************************************************
// Class	: gzSerializeAdapterTCP
//									
// Purpose  : Class for Serialize data to an TCP port
//									
// Notes	: This class is responsible to write/read data to a udp adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	190109	Created					(2.10.1)
//									
//******************************************************************************
class  gzSerializeAdapterTCP : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterTCP(const gzString &url, gzSerializeAction action = GZ_SERIALIZE_INPUT, gzSerializeAdapterFlags flags = GZ_SERIALIZE_ADAPTER_FLAGS_DEFAULT, const gzString &password = GZ_EMPTY_STRING, gzString *errorString = NULL, gzSerializeAdapterError *errorType = NULL);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterTCP();


	GZ_BASE_EXPORT gzBool openURL(const gzString &url);

	GZ_BASE_EXPORT gzVoid close();

	GZ_PROPERTY_EXPORT(gzUInt16,	Port,					GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,	AttributeString,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,	Address,				GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,	NicAddress,				GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,	UnicastAddress,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,		BlockingRead,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,		CloseOnNoConnection,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,		NoDelay,				GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,	BlockingTimeout,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32,	MaxFetchPackets,		GZ_BASE_EXPORT);

	GZ_BASE_EXPORT	gzVoid checkPacket();

	GZ_BASE_EXPORT gzBool	isActive() const override;

	GZ_BASE_EXPORT gzBool	hasError() const override;

protected:

	// Adapter
	GZ_BASE_EXPORT	virtual gzVoid		write_imp(gzUByte data) override;
	GZ_BASE_EXPORT	virtual gzUByte		read_imp() override;

	GZ_BASE_EXPORT	virtual gzVoid		write_imp(const gzUByte *data, gzUInt32 count) override;
	GZ_BASE_EXPORT	virtual gzUInt32	read_imp(gzUByte *data, gzUInt32 maxcount) override;
	GZ_BASE_EXPORT	virtual gzUInt32	length_imp() override;
	GZ_BASE_EXPORT	virtual gzBool		hasData_imp() override;

	// Moves packet from packets to adapter
	GZ_BASE_EXPORT	gzVoid takePacket();

	gzUInt32					m_pendingBytes;

	gzMutex						m_dataLocker;

	gzRefList<gzNetData>		m_packets;

	gzRefPointer<gzNetData>		m_current;

	gzSerializeAdapterMemory	m_adapter;

	gzDynamicArray<gzUByte>		m_buffer;

	gzSocket m_socket;

	gzMutex						m_writeLock;

};

GZ_DECLARE_REFPTR(gzSerializeAdapterTCP);

//******************************************************************************
// Class	: gzCommandStation
//									
// Purpose  : Class for remote command execution
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	160929	Created					(2.8.5)
//									
//******************************************************************************
class gzCommandStation : public gzThread
{
public:

	GZ_BASE_EXPORT gzCommandStation(gzString url = "con:", gzBool echo = TRUE);

	GZ_BASE_EXPORT virtual ~gzCommandStation();

	GZ_BASE_EXPORT gzBool open(gzString url, gzBool echo = FALSE);

	GZ_BASE_EXPORT gzVoid message(const gzString &message);

	GZ_BASE_EXPORT gzVoid process();

	GZ_BASE_EXPORT gzBool exec();

	GZ_BASE_EXPORT virtual gzBool onCommand(const gzString &command);

private:

	gzSerializeAdapterPtr			m_adapter;
	gzMutex							m_locker;
	gzString						m_currentCommand;
	gzRefList<gzRefData<gzString> > m_commandList;
	gzBool							m_echo;
	gzBool							m_commandMode;
	gzBool							m_needNewLine;
	gzEvent							m_trigger;
};

//******************************************************************************
// Class	: gzDebugCommandStation
//									
// Purpose  : Class for remote debug command execution
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	191206	Created					(2.10.5)
//									
//******************************************************************************
class gzDebugCommandStation :	public gzReference,
								public gzCommandStation, 
								public gzParserFunction<gzDebugCommandStation, gzBasicParser>
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzDebugCommandStation(gzString url = "con:", gzBool echo = TRUE);

	GZ_BASE_EXPORT virtual gzBool onExec(const gzString &execCommand);

	GZ_PROPERTY_EXPORT(gzBool,		UseNoMatchResponse, GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,	Alias,				GZ_BASE_EXPORT);


protected:

	GZ_BASE_EXPORT gzParseResult fReset();
	GZ_BASE_EXPORT gzParseResult fHelp();
	GZ_BASE_EXPORT gzParseResult fResetReg();
	GZ_BASE_EXPORT gzParseResult fSetAlias();
	GZ_BASE_EXPORT gzParseResult fSetReg();
	GZ_BASE_EXPORT gzParseResult fGetAlias();
	GZ_BASE_EXPORT gzParseResult fGetReg();
	GZ_BASE_EXPORT gzParseResult fVersion();
	GZ_BASE_EXPORT gzParseResult fQuit();
	GZ_BASE_EXPORT gzParseResult fAlias();
	GZ_BASE_EXPORT gzParseResult fExec();
	
	GZ_BASE_EXPORT virtual gzBool onCommand(const gzString &command) override;
};

GZ_DECLARE_REFPTR(gzDebugCommandStation);

#endif // __GZ_PROTOCOL_H__
