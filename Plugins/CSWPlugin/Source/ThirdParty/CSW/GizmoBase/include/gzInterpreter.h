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
// File			: gzInterpreter.h
// Module		: gzBase
// Description	: Class definition of interpreter utilities
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
// AMO	150707	Created file 									(2.8.1)
//
// ******************************************************************************
#ifndef __GZ_INTERPRETER_H__
#define __GZ_INTERPRETER_H__

/*!	\file 
	\brief Interpreter utilities

Uses BNF to create a generic interpreter class

*/

#include "gzLex.h"

enum gzParseHttpState
{
	GZ_HTTP_PARSE_STATE_RESET,
	GZ_HTTP_PARSE_STATE_PUBLIC,
	GZ_HTTP_PARSE_STATE_LAST
};

enum gzSerializeHttpState
{
	GZ_HTTP_SERIALIZE_STATE_IDLE,
	GZ_HTTP_SERIALIZE_STATE_READ,
	GZ_HTTP_SERIALIZE_STATE_WRITE,
};

class gzInterpreterDataInterface 
{
public:

	GZ_BASE_EXPORT virtual ~gzInterpreterDataInterface(){};

	GZ_BASE_EXPORT	virtual gzBool push(const gzUByte *adress,gzUInt32 len)=0;

	GZ_BASE_EXPORT	virtual gzBool push(gzUByte data);

	GZ_BASE_EXPORT	virtual gzBool quit();
};

//******************************************************************************
// Class	: gzInterpreter
//									
// Purpose  : Class for interpreting a BNF based syntax and execute callbacks
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
class gzInterpreter :	public gzReference,
						public gzInterpreterDataInterface, 
						public gzThread,
						public gzBasicParser
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);
	
	GZ_BASE_EXPORT	gzInterpreter();

	GZ_BASE_EXPORT	virtual ~gzInterpreter();

	GZ_PROPERTY_EXPORT(gzString,	StartRuleName,	GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool,		SkipToLF,		GZ_BASE_EXPORT);

	// ---------- Parse utils --------------

	GZ_BASE_EXPORT	gzParseResult fQuit();

	// -------- iface ---------------------

	//! Push data into the interpreter
	GZ_BASE_EXPORT	virtual gzBool push(const gzUByte *adress,gzUInt32 len) override;

	GZ_BASE_EXPORT	virtual gzBool push(gzUByte data) override;

	GZ_BASE_EXPORT	virtual gzBool quit() override;

	GZ_BASE_EXPORT	virtual gzParseResult parseRule(const gzString &rule);

	// ----------- Response iface --------------------

	GZ_BASE_EXPORT gzVoid setResponseInterface(gzInterpreterDataInterface *response);

	GZ_BASE_EXPORT gzBool respond(const gzUByte *adress, gzUInt32 len);

	GZ_BASE_EXPORT virtual gzBool respond(gzUByte data);

protected:

	GZ_BASE_EXPORT	virtual gzVoid process() override;

	GZ_BASE_EXPORT	virtual gzVoid onNoMatch(){};
	GZ_BASE_EXPORT	virtual gzVoid onError(){};
	GZ_BASE_EXPORT	virtual gzVoid onOK(){};

private:

	gzSerializeAdapterMuxPtr	m_adapter;

	gzInterpreterDataInterface	*m_response;
};

GZ_DECLARE_REFPTR(gzInterpreter);

//******************************************************************************
// Class	: gzFTPInterpreter
//									
// Purpose  : Class for interpreting a BNF based syntax and execute callbacks
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
class gzFTPInterpreter : public gzParserFunction<gzFTPInterpreter,gzInterpreter>
						 
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);
	
	GZ_BASE_EXPORT	gzFTPInterpreter();

	GZ_BASE_EXPORT	virtual ~gzFTPInterpreter();

	// ---------- Parse utils --------------

	GZ_BASE_EXPORT	gzParseResult fUser();
	GZ_BASE_EXPORT	gzParseResult fPassword();
	GZ_BASE_EXPORT	gzParseResult fAuth();
	GZ_BASE_EXPORT	gzParseResult fSyst();
	GZ_BASE_EXPORT	gzParseResult fStart();
	GZ_BASE_EXPORT	gzParseResult fStop();

	GZ_BASE_EXPORT virtual gzParseResult parseRule(const gzString &rule) override;

	GZ_PROPERTY_EXPORT(gzString,	User,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,	Password,	GZ_BASE_EXPORT);

	GZ_BASE_EXPORT virtual gzBool usePassword()		{ return TRUE; }
	GZ_BASE_EXPORT virtual gzBool checkUser()		{ return TRUE; }
	GZ_BASE_EXPORT virtual gzBool checkPassword()	{ return TRUE; }

private:

	gzBool	m_sentResponse;
};

GZ_DECLARE_REFPTR(gzFTPInterpreter);

//******************************************************************************
// Class	: gzHTTPInterpreter
//									
// Purpose  : Class for interpreting a BNF based syntax and execute callbacks
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
class gzHTTPInterpreter : public gzParserFunction<gzHTTPInterpreter, gzInterpreter>

{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT	gzHTTPInterpreter();

	GZ_BASE_EXPORT	virtual ~gzHTTPInterpreter();

	// -------------- Properties -------------------

	GZ_PROPERTY_GET_EXPORT(gzString, Method, GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzString, RequestURI, GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt32, MajorVersion, GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32, MinorVersion, GZ_BASE_EXPORT);

	GZ_PROPERTY_GET_EXPORT(gzString, User, GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzString, Password, GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzUInt16, HostPort, GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzString, Host, GZ_BASE_EXPORT);


	// ----------------- Content properties -----------------------

	GZ_PROPERTY_GET_EXPORT(gzUInt32, LastContentLength, GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzString, LastContentType, GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzString, LastContentBase, GZ_BASE_EXPORT);
	GZ_PROPERTY_GET_EXPORT(gzUInt32, LastErrorCode, GZ_BASE_EXPORT);


	GZ_BASE_EXPORT	gzVoid	resetLastError();

	// ---------------- Virtual Callbacks -------------------------

	GZ_BASE_EXPORT virtual gzBool onRequestMethodBegin(const gzString& /*method*/, const gzString& /*uri*/);
	GZ_BASE_EXPORT virtual gzBool onRequestMethodEnd(const gzString& /*method*/, const gzString& /*uri*/);

	GZ_BASE_EXPORT virtual gzBool onRequestMessageBody(const gzString& method, const gzString& uri, gzSerializeAdapter* adapter);

	// Errors
	GZ_BASE_EXPORT virtual gzString			getErrorMessage(gzUInt32 errorCode) const;

	// ---------- Parse utils --------------

	GZ_BASE_EXPORT virtual gzParseResult parseRule(const gzString &rule) override;


	// parsing

	GZ_BASE_EXPORT gzParseResult parseMessage();
	GZ_BASE_EXPORT gzParseResult parseMessageBody();
	GZ_BASE_EXPORT gzParseResult parseRequest();
	GZ_BASE_EXPORT gzParseResult parseRequestLine();
	GZ_BASE_EXPORT gzParseResult parseRequestHeader();
	GZ_BASE_EXPORT gzParseResult parseRequestURI();
	GZ_BASE_EXPORT gzParseResult parseResponse();
	GZ_BASE_EXPORT gzParseResult parseResponseHeader();
	GZ_BASE_EXPORT gzParseResult parseGeneralHeader();
	GZ_BASE_EXPORT gzParseResult parseEntityHeader();
	GZ_BASE_EXPORT gzParseResult parseStatusLine();
	GZ_BASE_EXPORT gzParseResult parseVersion();
	GZ_BASE_EXPORT gzParseResult parseStatusCode();
	GZ_BASE_EXPORT gzParseResult parseReasonPhrase();
	GZ_BASE_EXPORT gzParseResult parseWWWAuthenticate();
	GZ_BASE_EXPORT gzParseResult parseAllow();
	GZ_BASE_EXPORT gzParseResult parseContentBase();
	GZ_BASE_EXPORT gzParseResult parseContentEncoding();
	GZ_BASE_EXPORT gzParseResult parseContentLanguage();
	GZ_BASE_EXPORT gzParseResult parseContentLength();
	GZ_BASE_EXPORT gzParseResult parseContentLocation();
	GZ_BASE_EXPORT gzParseResult parseContentType();
	GZ_BASE_EXPORT gzParseResult parseExpires();
	GZ_BASE_EXPORT gzParseResult parseLastModified();
	GZ_BASE_EXPORT gzParseResult parseExtensionHeader();
	GZ_BASE_EXPORT gzParseResult parseCacheControl();
	GZ_BASE_EXPORT gzParseResult parseConnection();
	GZ_BASE_EXPORT gzParseResult parseDate();
	GZ_BASE_EXPORT gzParseResult parseVia();
	GZ_BASE_EXPORT gzParseResult parsePragma();
	GZ_BASE_EXPORT gzParseResult parseTrailer();
	GZ_BASE_EXPORT gzParseResult parseTransferEncoding();
	GZ_BASE_EXPORT gzParseResult parseUpgrade();
	GZ_BASE_EXPORT gzParseResult parseWarning();
	GZ_BASE_EXPORT gzParseResult parseHost();
	GZ_BASE_EXPORT gzParseResult parseProductOrComment();
	GZ_BASE_EXPORT gzParseResult parseServer();
	GZ_BASE_EXPORT gzParseResult parseVary();
	GZ_BASE_EXPORT gzParseResult parseAcceptRanges();
	GZ_BASE_EXPORT gzParseResult parseAge();
	GZ_BASE_EXPORT gzParseResult parseETag();
	GZ_BASE_EXPORT gzParseResult parseLocation();
	GZ_BASE_EXPORT gzParseResult parseRetryAfter();
	GZ_BASE_EXPORT gzParseResult parseProxyAuthenticate();
	GZ_BASE_EXPORT gzParseResult parseMethod();
	GZ_BASE_EXPORT gzParseResult parseExtensionMethod();
	GZ_BASE_EXPORT gzParseResult parseCacheDirective();
	GZ_BASE_EXPORT gzParseResult parseCacheResponse();
	GZ_BASE_EXPORT gzParseResult parseCacheRequestDirective();
	GZ_BASE_EXPORT gzParseResult parseFieldName();
	GZ_BASE_EXPORT gzParseResult parseAccept();
	GZ_BASE_EXPORT gzParseResult parseAcceptCharset();
	GZ_BASE_EXPORT gzParseResult parseAcceptEncoding();
	GZ_BASE_EXPORT gzParseResult parseAcceptLanguage();
	GZ_BASE_EXPORT gzParseResult parseAuthorization();
	GZ_BASE_EXPORT gzParseResult parseExpect();
	GZ_BASE_EXPORT gzParseResult parseFrom();
	GZ_BASE_EXPORT gzParseResult parseIfMatch();
	GZ_BASE_EXPORT gzParseResult parseIfModifiedSince();
	GZ_BASE_EXPORT gzParseResult parseIfNoneMatch();
	GZ_BASE_EXPORT gzParseResult parseIfRange();
	GZ_BASE_EXPORT gzParseResult parseIfUnmodifiedSince();
	GZ_BASE_EXPORT gzParseResult parseMaxForwards();
	GZ_BASE_EXPORT gzParseResult parseProxyAuthorization();
	GZ_BASE_EXPORT gzParseResult parseRange();
	GZ_BASE_EXPORT gzParseResult parseReferer();
	GZ_BASE_EXPORT gzParseResult parseTE();
	GZ_BASE_EXPORT gzParseResult parseUserAgent();
	

	// Basics

	GZ_BASE_EXPORT gzParseResult parseToken();

	// Compounds

	GZ_BASE_EXPORT gzParseResult parseElementList(gzHTTPInterpreter::ThisPtr element);

	GZ_BASE_EXPORT gzParseResult parseDigit_();
	GZ_BASE_EXPORT gzParseResult parseHEX_();
	GZ_BASE_EXPORT gzParseResult parseToken_();
	GZ_BASE_EXPORT gzParseResult parseTokenOrSP_();
	GZ_BASE_EXPORT gzParseResult parseLWS();
	GZ_BASE_EXPORT gzParseResult parseLWS_();
	GZ_BASE_EXPORT gzParseResult parseUpToCRLF();					//	->'\r\n'
	GZ_BASE_EXPORT gzParseResult parseText();
	GZ_BASE_EXPORT gzParseResult parseText_();
	GZ_BASE_EXPORT gzParseResult parseTSpecials();
	GZ_BASE_EXPORT gzParseResult parseCText();
	GZ_BASE_EXPORT gzParseResult parseComment();
	GZ_BASE_EXPORT gzParseResult parseDQText();
	GZ_BASE_EXPORT gzParseResult parseDQString();
	GZ_BASE_EXPORT gzParseResult parseReserved();
	
	GZ_BASE_EXPORT gzParseResult parseMediaType();
	GZ_BASE_EXPORT gzParseResult parseParameter();
	
	
	GZ_BASE_EXPORT gzParseResult parseProduct();
	
	

	// RFC 2396 URI
	GZ_BASE_EXPORT gzParseResult parseURI();
	GZ_BASE_EXPORT gzParseResult parseAbsoluteURI();
	GZ_BASE_EXPORT gzParseResult parseRelativeURI();
	GZ_BASE_EXPORT gzParseResult parseUnreserved();
	GZ_BASE_EXPORT gzParseResult parseHierPart();
	GZ_BASE_EXPORT gzParseResult parseHostName();
	GZ_BASE_EXPORT gzParseResult parseDomainLabel();
	GZ_BASE_EXPORT gzParseResult parsePathSegments();
	GZ_BASE_EXPORT gzParseResult parseSegment();
	GZ_BASE_EXPORT gzParseResult parseTopLabel();
	GZ_BASE_EXPORT gzParseResult parseRelPath();
	GZ_BASE_EXPORT gzParseResult parseRelSegment();
	GZ_BASE_EXPORT gzParseResult parseRelSegmentToken();	// token extension
	GZ_BASE_EXPORT gzParseResult parseNetPath();
	GZ_BASE_EXPORT gzParseResult parseRegName();
	GZ_BASE_EXPORT gzParseResult parseRegNameToken();		// token extension
	GZ_BASE_EXPORT gzParseResult parseAuthority();
	GZ_BASE_EXPORT gzParseResult parseServerURI();
	GZ_BASE_EXPORT gzParseResult parseHostURI();
	GZ_BASE_EXPORT gzParseResult parseHostPort();
	GZ_BASE_EXPORT gzParseResult parseAbsPath();
	GZ_BASE_EXPORT gzParseResult parseOpaquePart();
	GZ_BASE_EXPORT gzParseResult parseSchemeToken();		// token extension
	GZ_BASE_EXPORT gzParseResult parseScheme();
	GZ_BASE_EXPORT gzParseResult parseParam();
	GZ_BASE_EXPORT gzParseResult parsePChar();
	GZ_BASE_EXPORT gzParseResult parseURIChar();
	GZ_BASE_EXPORT gzParseResult parseEscaped();
	GZ_BASE_EXPORT gzParseResult parseMark();
	GZ_BASE_EXPORT gzParseResult parseUserInfo();
	GZ_BASE_EXPORT gzParseResult parseUserInfoToken();		// token extension
};

GZ_DECLARE_REFPTR(gzHTTPInterpreter);

#endif //__GZ_INTERPRETER_H__
