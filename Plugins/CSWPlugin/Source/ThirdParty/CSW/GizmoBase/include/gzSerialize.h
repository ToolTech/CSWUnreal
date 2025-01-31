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
// File			: gzSerialize.h
// Module		: gzBase
// Description	: Class definition of serialize classes
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
// AMO	981019	Created file 	
// AMO	110209	Added support for ZIP files and gzSerializeAdapterZIP	(2.5.18)
// AMO	110210	Added gzSerializeBinaryDynamicArray so we dont need 
//				to convert arrays										(2.5.18)
// AMO	110913	Added error message return in getURLAdapter				(2.5.20)
// AMO	131211	Updated gzSerializeAdapterStdIO with conios for UNIX	(2.7.4)
// AMO	131219	Added UDP serialize adapter								(2.7.4)
// AMO	210521	Changed writing bufferd data to const in adapter		(2.11.6)
// AMO	210820	Fixed conflict in compress dynamic flag for adapter		(2.11.22)
// AMO	211117	Added reset of stream in adapter						(2.11.49)
// AMO	230330	Added zip and service									(2.12.69)
//
// ******************************************************************************

#ifndef __GZ_SERIALIZE_H__
#define __GZ_SERIALIZE_H__

/*!	\file 
	\brief Serialized Management

Gizmo3D uses serialize patterns for file and data storage/retreival

*/

#include "gzBasicTypes.h"
#include "gzMemory.h"
#include "gzBase.h"
#include "gzTemplates.h"
#include "gzMatrix.h"
#include "gzMutex.h"
#include "gzGuid.h"
#include "gzXYZ.h"
#include "gzIO.h"
#include "gzRGBA.h"
#include "gzExceptions.h"

//#include <stdio.h>

enum gzSerializeAction { GZ_SERIALIZE_NONE=0 , GZ_SERIALIZE_OUTPUT=1 , GZ_SERIALIZE_INPUT=2 , GZ_SERIALIZE_DUPLEX=GZ_SERIALIZE_OUTPUT|GZ_SERIALIZE_INPUT} ;

GZ_USE_BIT_LOGIC(gzSerializeAction);

const gzString	GZ_LOG_NAME				="gizmosdk.log";

class gzSerializeData;

const gzString	GZ_URLBASE_FILE				= "file:";	// path/file name?append=true/false or service
const gzString	GZ_URLBASE_HTTP				= "http:";	// http url
const gzString	GZ_URLBASE_UDP				= "udp:";	// udp multicast or broadcast {multicast adress:port?nic} url
const gzString	GZ_URLBASE_TCP				= "tcp:";	// tcp {adress:port?nic} url
const gzString	GZ_URLBASE_FTP				= "ftp:";	// ftp url
const gzString	GZ_URLBASE_MEMORY			= "mem:";	// address,length
const gzString	GZ_URLBASE_REGISTRY			= "reg:";	// name of registry key
const gzString	GZ_URLBASE_PIPE				= "pipe:";	// name of pipe
const gzString	GZ_URLBASE_PIPESERVER		= "psrv:";	// name of pipe
const gzString	GZ_URLBASE_PURL				= "purl:";	// pipename,url
const gzString	GZ_URLBASE_CONSOLE			= "con:";	// console {?lf=no&echo=yes}
const gzString	GZ_URLBASE_CACHE			= "cache:";	// offset,len,url
const gzString	GZ_URLBASE_ADAPTER			= "adapt:";	// address of adapter
const gzString	GZ_URLBASE_RANDOM_ACCESS	= "rand:";	// add random access
const gzString	GZ_URLBASE_ZIP				= "zip:";	// url,subfile or service or *
const gzString	GZ_URLBASE_DUMMY			= "dummy:";	// size
const gzString	GZ_URLBASE_NULL				= "null:";	// Empty adapter, just to get a handle
const gzString	GZ_URLBASE_SERIAL			= "ser:";	// connection parameters {tbd}
const gzString	GZ_URLBASE_REMOTE			= "remote:";// remote located


// --------------- Defined Input Services --------------------

// Directory listing (2.12.17)
// URL="{base}{path}[dir:recursive=no&showpath=yes&showdir=yes&verbose=no&showsize=no&bnf=]");
// resursive	: traverses down
// showpath		: show complete path
// showdir		: includes dir as items
// verbose		: a more verbose output
// showsize		: shows filesize
// bnf			: bnf to match items

// CRC number of file content(2.12.117)
// URL="{base}{path}filename[crc:verbose=no&showsize=no]");
// verbose		: a more verbose output
// showsize		: shows filesize

// --------------- Defined Output Services --------------------


//******************************************************************************
// Class	: gzAdapterSharedData
//									
// Purpose  : Utility data holder for serializing adapters
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	010508	Created 
//									
//******************************************************************************
class gzAdapterSharedData : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzAdapterSharedData():index(0),size(0),saved(FALSE){};

	gzUInt32	index;
	gzUInt32	size;
	gzBool		saved;
};

// !Serialize Adapter loader flags
/*! These flags defines the behaviour of how the loader processes at load time */
typedef gzUInt64 gzSerializeAdapterFlags;

const gzSerializeAdapterFlags	GZ_SERIALIZE_ADAPTER_FLAGS_DEFAULT				=	0;
const gzSerializeAdapterFlags	GZ_SERIALIZE_ADAPTER_NO_ERROR_MSG				=	(1<<0);
const gzSerializeAdapterFlags	GZ_SERIALIZE_ADAPTER_WIDECHAR					=	(1<<1);
const gzSerializeAdapterFlags	GZ_SERIALIZE_ADAPTER_BIG_ENDIAN					=	(1<<2);
const gzSerializeAdapterFlags	GZ_SERIALIZE_ADAPTER_NO_PROGRESS_REPORT			=	(1<<3);
const gzSerializeAdapterFlags	GZ_SERIALIZE_ADAPTER_NO_ALTERNATE_SEARCH_PATH	=	(1<<4);
const gzSerializeAdapterFlags	GZ_SERIALIZE_ADAPTER_RETRY_WAIT_LOAD			=	(1<<5);

//! Special defined allocated flag (last flag)
const gzSerializeAdapterFlags	GZ_SERIALIZE_ADAPTER_COMPRESS_DYNAMIC_TYPES		=	LLU(0x8000000000000000);


//! Definition of how many flags there are in gzImageFlags
const gzUInt32 GZ_SERIALIZE_ADAPTER_FLAG_MAX_SIZE			=	6;	// Number of flags in image flag set

// Extensions (same flag as db or above db ) ---------------------------------------------

// Fixed. Do not change !
const gzSerializeAdapterFlags	GZ_SERIALIZE_ADAPTER_READ_ONLY_HEADER = LLU(1) << (20 + 6 + 6); //GZ_DB_FLAGS_READ_ONLY_HEADER

// ---------------------------- Utility for recycled dynamic array buffers -----------------------

#define MAX_DATA_IN_RECYCLE 1000	// How large is the largest chunk in recycle data

//! Recycled memory chunks 
class gzRecycledBuffer : public gzRecycleData<gzDynamicArray<gzUByte> >
{
public:

	~gzRecycledBuffer()
	{
		if (hasRecycledInstance() && (getRecycledInstance().getSize() > MAX_DATA_IN_RECYCLE))
			dropRecycledInstance(); //NOSONAR - We want this exception to happend even in destructor
	}
};

//! Recycled memory chunks that are reference based
class gzRecycledReferenceBuffer : public gzRecycleData<gzDynamicArray<gzUByte> >, public gzReference
{
public:

	~gzRecycledReferenceBuffer()
	{
		if (hasRecycledInstance() && (getRecycledInstance().getSize() > MAX_DATA_IN_RECYCLE))
			dropRecycledInstance(); //NOSONAR - We want this exception to happend even in destructor
	}
};

GZ_DECLARE_REFPTR(gzRecycledReferenceBuffer);

//******************************************************************************
// Class	: gzSerializeURLManagerInterface
//									
// Purpose  : Base interface fro registered URL managers
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	060817	Created 
//									
//******************************************************************************
class gzSerializeURLManagerInterface : public gzThreadSafeReference
{
public:

	GZ_BASE_EXPORT virtual gzSerializeAdapter *getURLAdapter(const gzString &url,gzSerializeAction action,gzSerializeAdapterFlags flags, const gzString &password, gzString *errorString, gzSerializeAdapterError* errorType)=0;

	GZ_BASE_EXPORT virtual gzBool getURLBaseEncoding(const gzString& _url, gzBool& _isAbsolute, gzString& _urlBase, gzString& _urlPath, gzString& _urlName, gzString& _urlAttributes, gzBool& _syntax_OK);
};

//******************************************************************************
// Class	: gzSerializeAdapterProgressInfo
//									
// Purpose  : Base class for Serialize Adapter associated info
//									
// Notes	: the gzUInt32 size provides for larger token sizes
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	090213	Created 
//									
//******************************************************************************
class gzSerializeAdapterProgressInfo : public gzReference
{
public:

	GZ_BASE_EXPORT gzSerializeAdapterProgressInfo(){};
	GZ_BASE_EXPORT virtual ~gzSerializeAdapterProgressInfo(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzString,		Banner,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32,		TotalLength,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,		Time,			GZ_BASE_EXPORT);
};

//******************************************************************************
// Class	: gzSerializeAdapter
//									
// Purpose  : Base class for Serialize Adapter
//									
// Notes	: the gzUInt32 size provides for larger token sizes
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981019	Created 
//									
//******************************************************************************
// An adapter is operated in INPUT or OUTPUT or DUPLEX mode
// If an adapter allows DUPLEX mode, the adapter will ensure that correct read and write lock will be used
class  gzSerializeAdapter : public gzThreadSafeReference , public gzNameInterface 
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI
		
	GZ_BASE_EXPORT gzSerializeAdapter(const gzString & name);
	GZ_BASE_EXPORT gzSerializeAdapter();

	GZ_BASE_EXPORT virtual ~gzSerializeAdapter(){};

	GZ_BASE_EXPORT gzVoid	serialize(gzSerializeData *data , gzSerializeAction action);

	GZ_BASE_EXPORT gzVoid	write(gzUByte data);
	GZ_BASE_EXPORT gzUByte	read();

	GZ_BASE_EXPORT gzVoid	write(const gzUByte *data,gzUInt32 count);
	GZ_BASE_EXPORT gzUInt32	read(gzUByte *data,gzUInt32 maxcount);
	
	GZ_BASE_EXPORT gzVoid	pushBack(gzUByte value);
	GZ_BASE_EXPORT gzVoid	pushBack(const gzUByte *data,gzUInt32 maxcount);
	GZ_BASE_EXPORT gzVoid	pushBackAdapterData();

	GZ_BASE_EXPORT gzVoid	allocPushBack(gzUInt32 size);

	GZ_BASE_EXPORT gzBool	hasData(gzUInt32 mincount=1);	// mincount==0 returns isActive()

	//! Default to streamed input/output
	GZ_BASE_EXPORT virtual	gzBool		canSeek()					{ return FALSE; }	// Default adapter can not seek

	//! Set seekmode to TRUE if you intend to use seek
	GZ_BASE_EXPORT virtual	gzVoid		setSeekMode(gzBool /*on*/)	{ };

	GZ_BASE_EXPORT gzMemSize			seek(gzMemOffset offset, gzOriginPos origin = GZ_ORIGIN_SET);

	GZ_BASE_EXPORT gzBool				eof();

	//! Default to support all directions
	GZ_BASE_EXPORT virtual gzBool		supportAction(gzSerializeAction /*action*/)	{return TRUE;}

	GZ_BASE_EXPORT virtual gzVoid		mergeAssociatedData(gzReference *newData);

	GZ_BASE_EXPORT gzUInt32	length();
	
	GZ_BASE_EXPORT virtual	gzVoid flush();

	//! Use this to signal close to inherited classes.
	GZ_BASE_EXPORT virtual gzBool aboutToClose(gzBool /*wait*/ )	{return TRUE;}

	//! Use this to signal to check active stream.
	GZ_BASE_EXPORT virtual gzBool isActive() const					{ return TRUE; }

	// ------------- Errors ------------------------------------------------------------------------------
	
	GZ_BASE_EXPORT virtual gzBool	hasError() const;
	GZ_BASE_EXPORT virtual gzString getError() const;
	GZ_BASE_EXPORT virtual gzVoid	setError(const gzString &error);

	GZ_BASE_EXPORT gzSerializeAdapterError getErrorType() const;
	GZ_BASE_EXPORT gzVoid setErrorType(const gzSerializeAdapterError &errorType);

	// ------------- Flags and Version -------------------------------------------------------------------
	
	GZ_PROPERTY_EXPORT(gzSerializeAdapterFlags,		AdapterFlags		,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32,					AdapterVersion		,GZ_BASE_EXPORT);

	//---- Generic utilities for sharing GUIDs used in serialization ------------------------------------------

	GZ_BASE_EXPORT virtual gzGUIDInstanceDictionary& getGUIDWriteInstanceDictionary();

	GZ_BASE_EXPORT virtual gzGUIDInstanceDictionary& getGUIDReadInstanceDictionary();

	//---- Generic utilities for sharing references used in serialization ------------------------------------------

	GZ_BASE_EXPORT virtual gzRefInstanceDictionary& getRefWriteInstanceDictionary();

	GZ_BASE_EXPORT virtual gzRefInstanceDictionary& getRefReadInstanceDictionary();

	GZ_BASE_EXPORT virtual gzRefInstanceArray &		getRefWriteInstanceArray();

	GZ_BASE_EXPORT virtual gzRefInstanceArray&		getRefReadInstanceArray();

	GZ_BASE_EXPORT virtual gzUInt32					getNewInstanceID();

	// --------------------------------------------------------------------------------------------------------

	GZ_BASE_EXPORT virtual gzVoid					clearSharedInstanceData(gzSerializeAction action=GZ_SERIALIZE_DUPLEX);
	
	GZ_BASE_EXPORT virtual gzVoid					copySharedInstanceData(gzSerializeAdapter * from, gzSerializeAction action);

	// --------------------------------------------------------------------------------------------------------

	//! set the adapter in a reset state. Tells that the underlying stream has been restarted
	GZ_BASE_EXPORT virtual gzVoid					resetStream(gzSerializeAction action=GZ_SERIALIZE_DUPLEX);

	//! return true if stream is in reset state. A consecutive read or write will throw stream exception
	GZ_BASE_EXPORT gzBool							isStreamReset(gzSerializeAction action = GZ_SERIALIZE_DUPLEX);

	//! Handles the pending reset, shall be called when reset has occurred and beeing handled
	GZ_BASE_EXPORT virtual	gzVoid					handleReset(gzSerializeAction action);

	//! Return to a adapter lock mechanism. Might allow paralell access or block
	GZ_BASE_EXPORT virtual gzMutex&					getAdapterLock() const;

	//--- Generic utils for URL management --------------------------------------------------------------

	// URL

	//! Get complete URL
	GZ_BASE_EXPORT gzString							getURL(gzBool skipAttributes=FALSE);

	//! Get adapter path of current attributes 
	GZ_BASE_EXPORT gzString							getURLPath();

	//! Get URL for relative file
	GZ_BASE_EXPORT gzString							getRelativeURL(const gzString &relativeFileName);

	GZ_PROPERTY_EXPORT(gzString,					URLBase				,GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,					DefaultPath			,GZ_BASE_EXPORT);

	//! Password management
	GZ_PROPERTY_EXPORT(gzString,					Password			,GZ_BASE_EXPORT);

	//! Attributes management
	GZ_PROPERTY_EXPORT(gzString,					Attributes			,GZ_BASE_EXPORT);

	//! Controller Interface
	GZ_PROPERTY_EXPORT(gzRefPointer<gzReference>,	AssociatedData		,GZ_BASE_EXPORT);

	//! Check if adapter changes url extension
	GZ_BASE_EXPORT virtual gzString useExtension(const gzString &extension_in);		

	//! Positions 
	GZ_BASE_EXPORT const gzUInt64& getReadPosition() const;
	GZ_BASE_EXPORT const gzUInt64& getWritePosition() const;

	//! Total length of data previously read and remaining
	GZ_BASE_EXPORT gzUInt64 getAccumReadLength();

	//--- The VERY generic URL based adaptor factory ----------------------------------------------------

	GZ_BASE_EXPORT static gzSerializeAdapter *getURLAdapter(const gzString &url,gzSerializeAction action=GZ_SERIALIZE_INPUT,gzSerializeAdapterFlags flags=GZ_SERIALIZE_ADAPTER_FLAGS_DEFAULT, const gzString &password=GZ_EMPTY_STRING,gzString *errorString=nullptr, gzSerializeAdapterError *errorType=nullptr);
	GZ_BASE_EXPORT static gzVoid registerURLManager(const gzString &urlBase,gzSerializeURLManagerInterface *manager);
	GZ_BASE_EXPORT static gzVoid unregisterURLManager(const gzString &urlBase,gzSerializeURLManagerInterface *manager);
	GZ_BASE_EXPORT static gzBool hasRegisteredURLManager(const gzString &urlBase);
	GZ_BASE_EXPORT static gzSerializeURLManagerInterface *getURLManager(const gzString &urlBase,gzSerializeURLManagerInterface *prev=nullptr);

	//! Returns a URL encoding. Forward Slashes
	/*!
		\return TRUE means that the URL is an Absolute path
	*/
	GZ_BASE_EXPORT static gzBool	getURLBaseEncoding(const gzString &url, gzString *_urlBase=nullptr,gzString * _urlPath=nullptr,gzString *_urlName=nullptr,gzString *_urlAttributes=nullptr,gzBool *_syntax_OK=nullptr,gzBool enablePathExtension=TRUE);
	GZ_BASE_EXPORT static gzString	getURLAttributeValue(const gzString &attributeName,const gzString &urlAttributes,const gzString &defaultValue=GZ_EMPTY_STRING);
	GZ_BASE_EXPORT static gzBool	hasURLAttributeValue(const gzString &attributeName, const gzString &urlAttributes);

	//! Blocking control , returns TRUE is state was changed
	GZ_BASE_EXPORT virtual gzBool setBlocking(gzBool blocking = TRUE);
	GZ_BASE_EXPORT virtual gzBool isBlocking() const;

protected:
		
	//! Provide this writer in your derived adapter
	GZ_BASE_EXPORT virtual gzVoid		write_imp(gzUByte data)=0;

	//! provide this reader in yor derived adapter
	GZ_BASE_EXPORT virtual gzUByte		read_imp()=0;

	//! If you want blocked fast access, you can provide this writer too.
	GZ_BASE_EXPORT virtual gzVoid		write_imp(const gzUByte *data,gzUInt32 count);
	
	//! If you want blocked fast access, you can provide this writer too.
	GZ_BASE_EXPORT virtual gzUInt32		read_imp(gzUByte *data,gzUInt32 maxcount);
	
	//! provide this length implementation of your adapter if it is capable of length prediction
	GZ_BASE_EXPORT virtual gzUInt32		length_imp();

	GZ_BASE_EXPORT virtual gzBool		hasData_imp();

	//! provide this seek impl of your adapter if its capable of seek (RandomAccess) and provide canSeek() as TRUE
	GZ_BASE_EXPORT virtual gzMemSize	seek_imp(gzMemOffset offset, gzOriginPos origin);

	//! provide this eof impl of your adapter if its eof differs from standard eof use (eof = TRUE when read beyond end )
	GZ_BASE_EXPORT virtual gzBool		eof_imp();

	gzVoid	checkResetStream(gzSerializeAction action);		// Internal check of reset

	// -----------------------------------------

	gzQueue<gzUByte>			m_pushback;
	gzString					m_propertyError;
	gzSerializeAdapterError		m_propertyErrorType;

	// Generic adapter utilites

	gzLateBindData<gzRefInstanceDictionary>		m_refWriteDict;		// Generic reference dictionary
	gzLateBindData<gzRefInstanceDictionary>		m_refReadDict;		// Generic reference dictionary
	gzLateBindData<gzRefInstanceArray>			m_refWriteArray;	// Generic reference array
	gzLateBindData<gzRefInstanceArray>			m_refReadArray;		// Generic reference array
	gzLateBindData<gzGUIDInstanceDictionary>	m_guidWriteDict;	// Generic GUID dictionary
	gzLateBindData<gzGUIDInstanceDictionary>	m_guidReadDict;		// Generic GUID dictionary

	// Intsance id
	gzUInt32									m_instanceID;

	// Position
	gzUInt64									m_readPosition;
	gzUInt64									m_writePosition;

	gzSerializeAction							m_pendingReset;

	// Access lock
	mutable gzMutex								m_adapterLock;

	// Blocking state
	gzBool										m_blocking;
	gzBool										m_eof_state;		// True when read ahead of eof

	static gzRefDict<gzString,gzSerializeURLManagerInterface>	s_urlManagers;
};

GZ_DECLARE_REFPTR(gzSerializeAdapter);

// ------------------------ conio imp --------------------------------------------

GZ_BASE_EXPORT void gz_gotoxy(int x, int y);
GZ_BASE_EXPORT void gz_clrscr();
GZ_BASE_EXPORT void gz_putch(int c);
GZ_BASE_EXPORT int	gz_getch();
GZ_BASE_EXPORT int	gz_getche();
GZ_BASE_EXPORT int	gz_kbhit();

//******************************************************************************
// Class	: gzSerializeAdapterStdIO
//									
// Purpose  : Class for Serialize data to STDIO
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981019	Created 
//									
//******************************************************************************
class  gzSerializeAdapterStdIO : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterStdIO();

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterStdIO();

	GZ_PROPERTY_EXPORT(gzBool, LF, GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool, Echo, GZ_BASE_EXPORT);

protected:
		
	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;
	GZ_BASE_EXPORT virtual gzBool	hasData_imp() override;
	GZ_BASE_EXPORT virtual gzUInt32 length_imp() override;
};

//******************************************************************************
// Class	: gzSerializeAdapterMemory
//									
// Purpose  : Class for Serialize data to memory
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981019	Created 
//									
//******************************************************************************
class  gzSerializeAdapterMemory : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterMemory(gzVoid *adress,gzUInt32 maxlen);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterMemory();

	GZ_BASE_EXPORT gzVoid reset(gzVoid *adress=nullptr,gzUInt32 maxlen=0);

	GZ_BASE_EXPORT virtual gzVoid move(gzInt32 steps);

	GZ_BASE_EXPORT virtual gzVoid flush()  override;

	GZ_PROPERTY_EXPORT(gzBool, DeleteMemOnDestruction, GZ_BASE_EXPORT);

	GZ_BASE_EXPORT virtual	gzBool		canSeek() override { return TRUE; }
	GZ_BASE_EXPORT virtual	gzVoid		setSeekMode(gzBool on) override ;

	GZ_BASE_EXPORT gzUInt16	checksum();

	GZ_BASE_EXPORT gzUByte *getCurrentAddress();
	GZ_BASE_EXPORT gzUInt32 getCurrentPos();

protected:

	GZ_BASE_EXPORT virtual	gzMemSize	seek_imp(gzMemOffset offset, gzOriginPos origin = GZ_ORIGIN_SET) override;
		
	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzVoid	write_imp(const gzUByte *data,gzUInt32 count) override;
	GZ_BASE_EXPORT virtual gzUInt32	read_imp(gzUByte *data,gzUInt32 maxcount) override;
	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

	gzUByte *	m_adress;
	gzUInt32	m_len;
	gzUInt32	m_currentPos;
};

GZ_DECLARE_REFPTR(gzSerializeAdapterMemory);

//******************************************************************************
// Class	: gzSerializeAdapterMux
//									
// Purpose  : Class for multiplexing data from several writers into one reader
//									
// Notes	: This class is responsible to read/write thread safely
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150707	Created 
//									
//******************************************************************************
class gzSerializeAdapterMux : public gzSerializeAdapter
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterMux();

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterMux();

	GZ_BASE_EXPORT virtual gzMutex& getAdapterLock() const override;

	GZ_PROPERTY_EXPORT(gzDouble,	BlockingTimeout,	GZ_BASE_EXPORT);

protected:
		
	GZ_BASE_EXPORT	virtual gzVoid		write_imp(gzUByte data) override;
	GZ_BASE_EXPORT	virtual gzVoid		write_imp(const gzUByte *data,gzUInt32 len) override;
	GZ_BASE_EXPORT	virtual gzUInt32	read_imp(gzUByte* data, gzUInt32 len) override;
	GZ_BASE_EXPORT	virtual gzUByte		read_imp() override;


	GZ_BASE_EXPORT	virtual gzUInt32	length_imp() override;

	GZ_BASE_EXPORT	gzVoid addPackage(const gzUByte* adress, gzUInt32 len);
	GZ_BASE_EXPORT	gzVoid takePacket();

private:

	// -------------------- data packet ----------------

	gzUInt32									m_pendingBytes;

	gzEvent										m_dataLocker;

	gzRefList<gzRecycledReferenceBuffer>		m_packets;

	gzRefPointer<gzRecycledReferenceBuffer>		m_current;

	gzSerializeAdapterMemory					m_adapter;

	gzDynamicArray<gzUByte>						m_buffer;
};

GZ_DECLARE_REFPTR(gzSerializeAdapterMux);

//******************************************************************************
// Class	: gzSerializeAdapterFile
//									
// Purpose  : Class for Serialize data to File
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981019	Created 
//									
//******************************************************************************
class  gzSerializeAdapterFile : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterFile(const gzString &filename,gzSerializeAction action=GZ_SERIALIZE_INPUT,gzBool append=FALSE,gzSerializeAdapterFlags flags=GZ_SERIALIZE_ADAPTER_FLAGS_DEFAULT);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterFile();

	GZ_BASE_EXPORT virtual gzVoid flush() override;

	GZ_BASE_EXPORT virtual gzBool reset(gzMemSize position=0);

	GZ_BASE_EXPORT static gzVoid cleanUpLargeFiles();

	GZ_BASE_EXPORT	gzBool	readLargeChunks();
	GZ_BASE_EXPORT	gzVoid	readLargeChunks(gzBool on=TRUE);

	GZ_BASE_EXPORT virtual	gzBool canSeek() override;
	GZ_BASE_EXPORT virtual	gzVoid setSeekMode(gzBool on) override;

	GZ_BASE_EXPORT virtual gzBool supportAction(gzSerializeAction action) override;

protected:

	GZ_BASE_EXPORT virtual	gzMemSize seek_imp(gzMemOffset offset, gzOriginPos origin = GZ_ORIGIN_SET) override;
		
	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzVoid	write_imp(const gzUByte *data,gzUInt32 count) override;
	GZ_BASE_EXPORT virtual gzUInt32	read_imp(gzUByte *data,gzUInt32 maxcount) override;
	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

private:

	gzBool checkInputService(const gzString &url);
	gzBool checkOutputService(const gzString& url);
	
	class gzFileQueue : public gzRecycleData<gzQueue<gzUByte> >
	{
		public:
			virtual gzVoid onInitItem(gzQueue<gzUByte> & data) const;
	};
	

	gzFileQueue 			m_data;
	gzString				m_file;
	gzSerializeAction		m_mode;
	gzFileHandle			m_filehandle;
	gzMemSize				m_leftOnDisc;	
	gzBool					m_readLargeChunks;
	gzBool					m_append;
};

GZ_DECLARE_REFPTR(gzSerializeAdapterFile);

//******************************************************************************
// Class	: gzSerializeData
//									
// Purpose  : Base class for Serialize data
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981019	Created 
//									
//******************************************************************************
class  gzSerializeData 
{
public:

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter)=0;

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter)=0;

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter)=0;

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const =0;
};

//******************************************************************************
// Class	: gzSerializePacketInterface
//									
// Purpose  : Interface that can be implemented by some adapters
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981019	Created 
//									
//******************************************************************************
class gzSerializePacketInterface
{
public:

	virtual gzUInt32 getDroppedPackets(gzBool clearDroppedPackages=TRUE)=0;

	virtual gzDouble getAveragePacketSize()=0;

	virtual gzDouble getAveragePacketsPerSecond()=0;
};

typedef gzSerializePacketInterface * gzSerializePacketInterfacePtr;

const gzString GZ_SERIALIZE_PACKET_INTERFACE="gzSerializePacketInterface";


//******************************************************************************
// Class	: gzSerializeBinary
//									
// Purpose  : Template for binary storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990301	Created 
//									
//******************************************************************************
template <class T> class gzSerializeBinary : public gzSerializeData
{
public:

	explicit gzSerializeBinary<T>(const gzBool useBigEndian=TRUE):m_useBigEndian(useBigEndian){};

	gzSerializeBinary<T>(const T &val, const gzBool useBigEndian) : m_useBigEndian(useBigEndian),m_data(val){};

	gzBool operator==(const gzSerializeBinary<T> &right) { return m_data==right.m_data; }

	gzBool operator!=(const gzSerializeBinary<T> &right) { return m_data!=right.m_data; }

	virtual ~gzSerializeBinary<T>(){};

	virtual gzVoid write(gzSerializeAdapter *adapter) override;

	virtual gzVoid read(gzSerializeAdapter *adapter) override;

	virtual gzVoid pushBack(gzSerializeAdapter *adapter) override;

	virtual gzUInt32	getDataSize(gzSerializeAdapter * /*adapter*/=nullptr) 	const override	{ return sizeof(m_data); }

	T & getRef()																{return m_data; }

	operator  T () const														{ return m_data; }

	T & operator = (const T &data)												{ m_data=data; return m_data; }
	
	gzVoid setBigEndian(gzBool useBigEndian)									{ m_useBigEndian = useBigEndian; }

private:

	gzBool	m_useBigEndian;

	T		m_data;
};	

// Initialisation of data member m_data
template <> inline gzSerializeBinary<gzUByte>::gzSerializeBinary(const gzBool useBigEndian) :m_useBigEndian(useBigEndian), m_data(0) {}
template <> inline gzSerializeBinary<gzFloat>::gzSerializeBinary(const gzBool useBigEndian) : m_useBigEndian(useBigEndian), m_data(0) {}
template <> inline gzSerializeBinary<gzDouble>::gzSerializeBinary(const gzBool useBigEndian) : m_useBigEndian(useBigEndian), m_data(0) {}
template <> inline gzSerializeBinary<gzUInt32>::gzSerializeBinary(const gzBool useBigEndian) : m_useBigEndian(useBigEndian), m_data(0) {}
template <> inline gzSerializeBinary<gzInt32>::gzSerializeBinary(const gzBool useBigEndian) : m_useBigEndian(useBigEndian), m_data(0) {}
template <> inline gzSerializeBinary<gzInt16>::gzSerializeBinary(const gzBool useBigEndian) : m_useBigEndian(useBigEndian), m_data(0) {}
template <> inline gzSerializeBinary<gzWideChar>::gzSerializeBinary(const gzBool useBigEndian) : m_useBigEndian(useBigEndian), m_data(0) {}
template <> inline gzSerializeBinary<gzUInt64>::gzSerializeBinary(const gzBool useBigEndian) : m_useBigEndian(useBigEndian), m_data(0) {}
template <> inline gzSerializeBinary<gzInt64>::gzSerializeBinary(const gzBool useBigEndian) : m_useBigEndian(useBigEndian), m_data(0) {}
template <> inline gzSerializeBinary<gzVoid*>::gzSerializeBinary(const gzBool useBigEndian) : m_useBigEndian(useBigEndian), m_data(0) {}

#ifndef GZ_USE_SHORT_WCHAR
template <> inline gzSerializeBinary<gzUInt16>::gzSerializeBinary(const gzBool useBigEndian) : m_useBigEndian(useBigEndian), m_data(0) {}
#endif


inline gzVoid gzSwapBytes(gzUByte	*data,gzUInt32 size)
{
	if(size<2)
		return;
	
	if(size==2)
	{
		gzUByte temp(*data);
		gzUByte *dest(data+1);
		*data=*dest;
		*dest=temp;
		
		return;
	}
	
	gzUInt32 len(size>>1);
	
	gzUByte *swapByte(data+size);
	gzUByte temp;
	
	while(len--)
	{
		temp=*data;
		*data++=*(--swapByte);
		*swapByte=temp;
	}
}

template <class T> inline gzVoid gzSerializeBinary<T>::write(gzSerializeAdapter *adapter)
{
	if(gzBigEndian()==m_useBigEndian)
		adapter->write((gzUByte *)&m_data,sizeof(m_data));
	else
	{
		T buf(m_data);
		gzSwapBytes((gzUByte *)&buf,sizeof(m_data));
		adapter->write((gzUByte *)&buf,sizeof(m_data));
	}
}

template <class T> inline gzVoid gzSerializeBinary<T>::pushBack(gzSerializeAdapter *adapter)
{
	gzUByte	*data=(gzUByte *)&m_data;

	if(gzBigEndian())	// Irix etc..
	{
		if(!m_useBigEndian)
		{
			for(gzUInt32 i=0;i<sizeof(m_data);++i)
			{
				adapter->pushBack(*data);
				++data;
			}
		}
		else
		{
			data+=(sizeof(m_data)-1);

			for(gzUInt32 i=0;i<sizeof(m_data);++i)
			{
				adapter->pushBack(*data);
				--data;
			}
		}
	}
	else	// Intel
	{
		if(m_useBigEndian)
		{
			for(gzUInt32 i=0;i<sizeof(m_data);++i)
			{
				adapter->pushBack(*data);
				++data;
			}
		}
		else
		{
			data+=(sizeof(m_data)-1);

			for(gzUInt32 i=0;i<sizeof(m_data);++i)
			{
				adapter->pushBack(*data);
				--data;
			}
		}
	}
}


template <class T> inline gzVoid gzSerializeBinary<T>::read(gzSerializeAdapter *adapter)
{
	if (adapter->read((gzUByte*)&m_data, sizeof(m_data)) != sizeof(m_data))
		throw gzStreamError(GZ_STREAM_ERROR_OUT_OF_DATA);

	if(gzBigEndian()!=m_useBigEndian)
		gzSwapBytes((gzUByte *)&m_data,sizeof(m_data));
}	

//******************************************************************************
// Class	: gzVarUInt64
//									
// Purpose  : -
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000531	Created 
//									
//******************************************************************************
class gzVarUInt64 : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzVarUInt64(const gzUInt64 &value=0);

	GZ_BASE_EXPORT operator gzUInt64 ();

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

private:

	gzUInt64	m_value;
};

//******************************************************************************
// Class	: gzSerializeArray
//									
// Purpose  : Template for storage of arrays of serialize data
//									
// Notes	: This class is responsible to write/read data to adapter
//			  YOU HAVE TO SET THE SIZE before reading. No storage of size
//			  See also gzSerializeBinaryArray
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000531	Created 
//									
//******************************************************************************
template <class T> class gzSerializeArray : public gzSerializeData
{
public:
	
	gzSerializeArray<T>(gzUInt32 size=0):m_data(size){};

	virtual gzVoid write(gzSerializeAdapter *adapter) 
	{
		gzUInt32 i;
		for(i=0;i<m_data.getSize();i++)
			m_data[i].write(adapter);
	}

	virtual gzVoid read(gzSerializeAdapter *adapter)
	{
		gzUInt32 i;
		for(i=0;i<m_data.getSize();i++)
			m_data[i].read(adapter);
	}

	virtual gzVoid pushBack(gzSerializeAdapter *adapter)
	{
		gzUInt32 i;
		for(i=0;i<m_data.getSize();i++)
			m_data[m_data.getSize()-1-i].pushBack(adapter);
	}


	virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const 
	{
		gzUInt32 i,size=0;
		gzArray<T> &ptr=(gzArray<T> &)m_data;
		for(i=0;i<ptr.getSize();i++)
			size+=ptr[i].getDataSize(adapter);
		return size;
	}

	
	T & operator [](gzUInt32 index)										{ return m_data[index]; }

	operator const gzArray<T> & () const								{ return m_data; }

	const gzArray<T> & operator = (const gzArray<T>& data)				{ m_data=data; return m_data; }

	operator	gzString ();

	gzVoid		setSize(gzUInt32 size)									{ m_data.setSize(size); }

	gzUInt32		getSize()		const								{ return m_data.getSize(); }

private:

	gzArray<T>		m_data;

};

template <class T> inline gzSerializeArray<T>::operator gzString()
{
	gzUInt32 len=getDataSize();

	char *buffer=new char[len+1];

	gzSerializeAdapterMemory adapter(buffer,len);

	write(&adapter);

	buffer[len]='\0';

	gzString result(buffer);

	delete [] buffer;

	return result;	// If string data contains a zero byte data it will be terminated
}

//******************************************************************************
// Class	: gzSerializeList
//									
// Purpose  : Template for storage of Lists of serialize data. No referencing
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	111013	Created 
//									
//******************************************************************************
template <class T> class gzSerializeList : public gzSerializeData
{
public:
	
	virtual gzVoid write(gzSerializeAdapter *adapter)
	{
		gzVarUInt64 len(m_data.entries());

		len.write(adapter);

		gzListIterator<T>	iterator(m_data);
		T*					item;

		while((item=iterator()))
			item->write(adapter);
	}

	virtual gzVoid read(gzSerializeAdapter *adapter)
	{
		m_data.clear();

		gzVarUInt64 len;

		len.read(adapter);

		T* item;

		for(gzUInt64 i=0;i<len;i++)
		{
			item=new T;
			item->read(adapter);
			m_data.insert(item);
		}	
	}

	virtual gzVoid pushBack(gzSerializeAdapter *adapter)
	{
		throwFatalTemplateError("No pushBack in gzSerializeList");
	}


	virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const 
	{
		gzUInt32 size=0;

		gzVarUInt64 len(m_data.entries());
		size+=len.getDataSize(adapter);

		gzListConstIterator<T>	iterator(m_data);
		const T*				item;

		while((item=iterator()))
			size+=item->getDataSize(adapter);

		return size;
	}

	
	operator const gzList<T> & () const								{ return m_data; }

	const gzList<T> & operator = (const gzList<T>& data)			{ m_data=data; return m_data; }

private:

	gzList<T>		m_data;

};

//******************************************************************************
// Class	: gzSerializeRefList
//									
// Purpose  : Template for storage of Lists of serialize data. No referencing
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	111013	Created 
//									
//******************************************************************************
template <class T> class gzSerializeRefList : public gzSerializeData
{
public:
	
	virtual gzVoid write(gzSerializeAdapter *adapter)
	{
		gzVarUInt64 len(m_data.entries());

		len.write(adapter);

		gzListIterator<T>	iterator(m_data);
		T*					item;

		while((item=iterator()))
			item->write(adapter);
	}

	virtual gzVoid read(gzSerializeAdapter *adapter)
	{
		m_data.clear();

		gzVarUInt64 len;

		len.read(adapter);

		T* item;

		for(gzUInt64 i=0;i<len;i++)
		{
			item=new T;
			item->read(adapter);
			m_data.insert(item);
		}	
	}

	virtual gzVoid pushBack(gzSerializeAdapter *adapter)
	{
		throwFatalTemplateError("No pushBack in gzSerializeRefList");
	}


	virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const 
	{
		gzUInt32 size=0;

		gzVarUInt64 len(m_data.entries());
		size+=len.getDataSize(adapter);

		gzListConstIterator<T>	iterator(m_data);
		const T*				item;

		while((item=iterator()))
			size+=item->getDataSize(adapter);

		return size;
	}

	
	operator const gzRefList<T> & () const						{ return m_data; }

	const gzRefList<T> & operator = (const gzRefList<T>& data)	{ m_data=data; return m_data; }

private:

	gzRefList<T>		m_data;

};

//******************************************************************************
// Class	: gzSerializeDList
//									
// Purpose  : Template for storage of Lists of serialize data. No referencing
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	111013	Created 
//									
//******************************************************************************
template <class T> class gzSerializeDList : public gzSerializeData
{
public:
	
	virtual gzVoid write(gzSerializeAdapter *adapter)
	{
		gzVarUInt64 len(m_data.entries());

		len.write(adapter);

		gzDListIterator<T>	iterator(m_data);
		T*					item;

		while((item=iterator()))
			item->write(adapter);
	}

	virtual gzVoid read(gzSerializeAdapter *adapter)
	{
		m_data.clear();

		gzVarUInt64 len;

		len.read(adapter);

		T* item;

		for(gzUInt64 i=0;i<len;i++)
		{
			item=new T;
			item->read(adapter);
			m_data.insert(item);
		}	
	}

	virtual gzVoid pushBack(gzSerializeAdapter *adapter)
	{
		gzDListIterator<T>	iterator(m_data);
		T*					item;

		while((item=iterator--))
			item->pushBack(adapter);

		gzVarUInt64 len(m_data.entries());
		len.pushBack(adapter);
	}


	virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const 
	{
		gzUInt32 size=0;

		gzVarUInt64 len(m_data.entries());
		size+=len.getDataSize(adapter);

		gzDListConstIterator<T>	iterator(m_data);
		const T*				item;

		while((item=iterator()))
			size+=item->getDataSize(adapter);

		return size;
	}

	
	operator const gzDList<T> & () const					{ return m_data; }

	const gzDList<T> & operator = (const gzDList<T>& data)	{ m_data=data; return m_data; }

private:

	gzDList<T>		m_data;

};

//******************************************************************************
// Class	: gzSerializeRefDList
//									
// Purpose  : Template for storage of Lists of serialize data. No referencing
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	111013	Created 
//									
//******************************************************************************
template <class T> class gzSerializeRefDList : public gzSerializeData
{
public:
	
	virtual gzVoid write(gzSerializeAdapter *adapter)
	{
		gzVarUInt64 len(m_data.entries());

		len.write(adapter);

		gzDListIterator<T>	iterator(m_data);
		T*					item;

		while((item=iterator()))
			item->write(adapter);
	}

	virtual gzVoid read(gzSerializeAdapter *adapter)
	{
		m_data.clear();

		gzVarUInt64 len;

		len.read(adapter);

		T* item;

		for(gzUInt64 i=0;i<len;i++)
		{
			item=new T;
			item->read(adapter);
			m_data.insert(item);
		}	
	}

	virtual gzVoid pushBack(gzSerializeAdapter *adapter)
	{
		gzDListIterator<T>	iterator(m_data);
		T*					item;

		while((item=iterator--))
			item->pushBack(adapter);

		gzVarUInt64 len(m_data.entries());
		len.pushBack(adapter);
	}


	virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const 
	{
		gzUInt32 size=0;

		gzVarUInt64 len(m_data.entries());
		size+=len.getDataSize(adapter);

		gzDListConstIterator<T>	iterator(m_data);
		const T*					item;

		while((item=iterator()))
			size+=item->getDataSize(adapter);

		return size;
	}

	
	operator const gzRefDList<T> & () const							{ return m_data; }

	const gzRefDList<T> & operator = (const gzRefDList<T>& data)	{ m_data=data; return m_data; }

private:

	gzRefDList<T>		m_data;

};

//******************************************************************************
// Class	: gzSerializeDynamicArray
//									
// Purpose  : Template for storage of arrays of serialize data
//									
// Notes	: This class is responsible to write/read data to adapter
//			  YOU HAVE TO SET THE SIZE before reading. No storage of size
//			  See also gzSerializeBinaryArray
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000531	Created 
//									
//******************************************************************************
template <class T> class gzSerializeDynamicArray : public gzSerializeData
{
public:
	
	gzSerializeDynamicArray<T>(gzUInt32 size=0):m_data(size){};

	virtual gzVoid write(gzSerializeAdapter *adapter)
	{
		gzUInt32 i;
		for(i=0;i<m_data.getSize();i++)
			m_data[i].write(adapter);
	}

	virtual gzVoid read(gzSerializeAdapter *adapter)
	{
		gzUInt32 i;
		for(i=0;i<m_data.getSize();i++)
			m_data[i].read(adapter);
	}

	virtual gzVoid pushBack(gzSerializeAdapter *adapter)
	{
		gzUInt32 i;
		for(i=0;i<m_data.getSize();i++)
			m_data[m_data.getSize()-1-i].pushBack(adapter);
	}


	virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const 
	{
		gzUInt32 i,size(0);
		for(i=0;i<m_data.getSize();i++)
			size+=m_data.get(i).getDataSize(adapter);
		return size;
	}

	
	T & operator [](gzUInt32 index)											{ return m_data[index]; }

	operator const gzDynamicArray<T> & () const								{ return m_data; }

	const gzDynamicArray<T> & operator = (const gzDynamicArray<T>& data)	{ m_data=data; return m_data; }

	operator	gzString ();
	
	gzVoid		setSize(gzUInt32 size)										{ m_data.setSize(size); }

	gzUInt32		getSize()		const										{ return m_data.getSize(); }

private:

	gzDynamicArray<T>		m_data;

};

template <class T> inline gzSerializeDynamicArray<T>::operator gzString()
{
	gzUInt32 len=getDataSize();

	char *buffer=new char[len+1];

	gzSerializeAdapterMemory adapter(buffer,len);

	write(&adapter);

	buffer[len]='\0';

	gzString result(buffer);

	delete [] buffer;

	return result;	// If string data contains a zero byte data it will be terminated
}

//******************************************************************************
// Class	: gzSerializeString
//									
// Purpose  : Help class for null terminated string storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990401	Created 
//									
//******************************************************************************
class  gzSerializeString : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeString(gzUByte terminator=0):m_terminator(terminator),m_useTerminator(TRUE){};

	GZ_BASE_EXPORT gzSerializeString(const gzString &string,gzUByte terminator=0):m_data(string),m_terminator(terminator),m_useTerminator(TRUE){};

	GZ_BASE_EXPORT virtual ~gzSerializeString(){};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter * /*adapter*/ =nullptr) const override { return (gzUInt32)(m_data.length()+1); }

	GZ_BASE_EXPORT operator const gzString & () const		{ return m_data; }

	GZ_BASE_EXPORT operator gzString & ()					{ return m_data; }

	GZ_BASE_EXPORT const char * getString() const			{ return m_data.getString(); }

	GZ_BASE_EXPORT gzVoid setTerminator(gzUByte terminator) { m_terminator=terminator; }

	GZ_BASE_EXPORT gzVoid useTerminator(gzBool on){ m_useTerminator=on; }

	GZ_BASE_EXPORT const gzString & operator = (const gzString & data) { m_data=data; return m_data; }

	GZ_BASE_EXPORT gzBool createUnique(gzUInt16 uniqueID)	{ m_data.clear();return m_data.makeUnique(uniqueID); }

	GZ_BASE_EXPORT gzVoid format(const gzString &format,ARG_DECL_LIST);

private:

	gzString	m_data;
	
	gzUByte		m_terminator;

	gzBool		m_useTerminator;

};

class gzSerializeStringWide : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeStringWide(gzUInt16 terminator=0,gzBool bigEndian=FALSE):m_terminator(terminator),m_bigEndian(bigEndian){};

	GZ_BASE_EXPORT virtual ~gzSerializeStringWide(){};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

	GZ_BASE_EXPORT operator const gzString & () const { return m_data; }

	GZ_BASE_EXPORT const gzWideChar * getWideString() const { return m_data.getWideString(); }

	GZ_BASE_EXPORT gzVoid setTerminator(gzUInt16 terminator) { m_terminator=terminator; }

	GZ_BASE_EXPORT const gzString & operator = (const gzString & data) { m_data=data; return m_data; }
	
	GZ_BASE_EXPORT gzVoid setBigEndian(gzBool useBigEndian){ m_bigEndian = useBigEndian; }

	GZ_BASE_EXPORT gzBool createUnique(gzUInt16 uniqueID)	{ m_data.clear();return m_data.makeUnique(uniqueID); }

	GZ_BASE_EXPORT gzVoid format(const gzString &format,ARG_DECL_LIST);

private:

	gzString	m_data;
	
	gzUInt16	m_terminator;
	
	gzBool		m_bigEndian;
};


//******************************************************************************
// Class	: gzSerializeVec2
//									
// Purpose  : Help class for gzVec2 storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990401	Created 
//									
//******************************************************************************
class  gzSerializeVec2 : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeVec2(gzBool useBigEndian=TRUE):v1(useBigEndian),v2(useBigEndian){};

	GZ_BASE_EXPORT virtual ~gzSerializeVec2(){};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) { v1.write(adapter); v2.write(adapter) ; }

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) { v1.read(adapter); v2.read(adapter) ; }

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) { v2.pushBack(adapter) ; v1.pushBack(adapter); }

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter * /*adapter*/=nullptr) const { return 2 * sizeof(gzFloat); }

	GZ_BASE_EXPORT operator gzVec2 () const { return gzVec2((gzFloat)v1,(gzFloat)v2); }

	GZ_BASE_EXPORT const gzVec2 & operator = (const gzVec2 &data) { v1=data.v1; v2=data.v2; return data; }

	GZ_BASE_EXPORT gzVoid setBigEndian(gzBool useBigEndian){ v1.setBigEndian(useBigEndian); v2.setBigEndian(useBigEndian);  }


	gzSerializeBinary<gzFloat> v1,v2;
};

//******************************************************************************
// Class	: gzSerializeVec3
//									
// Purpose  : Help class for gzVec3 storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990401	Created 
//									
//******************************************************************************
class  gzSerializeVec3 : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeVec3(gzBool useBigEndian=TRUE):v1(useBigEndian),v2(useBigEndian),v3(useBigEndian){};

	GZ_BASE_EXPORT virtual ~gzSerializeVec3(){};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) { v1.write(adapter); v2.write(adapter) ; v3.write(adapter); }

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) { v1.read(adapter); v2.read(adapter) ; v3.read(adapter); }

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) { v3.pushBack(adapter); v2.pushBack(adapter) ; v1.pushBack(adapter); }

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter * /*adapter*/=nullptr) const { return 3 * sizeof(gzFloat); }

	GZ_BASE_EXPORT operator gzVec3 () const { return gzVec3((gzFloat)v1,(gzFloat)v2,(gzFloat)v3); }

	GZ_BASE_EXPORT const gzVec3  & operator = (const gzVec3 &data) { v1=data.v1; v2=data.v2; v3=data.v3; return data; }

	GZ_BASE_EXPORT gzVoid setBigEndian(gzBool useBigEndian){ v1.setBigEndian(useBigEndian); v2.setBigEndian(useBigEndian); v3.setBigEndian(useBigEndian); }

	gzSerializeBinary<gzFloat> v1,v2,v3;
};

//******************************************************************************
// Class	: gzSerializeVec4
//									
// Purpose  : Help class for gzVec4 storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990401	Created 
//									
//******************************************************************************
class  gzSerializeVec4 : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeVec4(gzBool useBigEndian=TRUE):v1(useBigEndian),v2(useBigEndian),v3(useBigEndian),v4(useBigEndian){};

	GZ_BASE_EXPORT virtual ~gzSerializeVec4(){};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) { v1.write(adapter); v2.write(adapter) ; v3.write(adapter); v4.write(adapter); }

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) { v1.read(adapter); v2.read(adapter) ; v3.read(adapter); v4.read(adapter);}

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) { v4.pushBack(adapter); v3.pushBack(adapter); v2.pushBack(adapter) ; v1.pushBack(adapter); }

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter * /*adapter*/=nullptr) const { return 4 * sizeof(gzFloat); }

	GZ_BASE_EXPORT operator gzVec4() const { return gzVec4((gzFloat)v1,(gzFloat)v2,(gzFloat)v3,(gzFloat)v4); }

	GZ_BASE_EXPORT const gzVec4 & operator = (const gzVec4 &data) { v1=data.v1; v2=data.v2; v3=data.v3; v4=data.v4; return data; }

	GZ_BASE_EXPORT gzVoid setBigEndian(gzBool useBigEndian){ v1.setBigEndian(useBigEndian); v2.setBigEndian(useBigEndian); v3.setBigEndian(useBigEndian); v4.setBigEndian(useBigEndian);}

	gzSerializeBinary<gzFloat> v1,v2,v3,v4;
};

//******************************************************************************
// Class	: gzSerializegzQuaternion
//									
// Purpose  : Help class for gzQuat storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	220223	Created 
//									
//******************************************************************************
class  gzSerializeQuaternion : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeQuaternion(gzBool useBigEndian = TRUE) :w(useBigEndian), x(useBigEndian), y(useBigEndian), z(useBigEndian) {};

	GZ_BASE_EXPORT virtual ~gzSerializeQuaternion() {};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter* adapter) { w.write(adapter); x.write(adapter); y.write(adapter); z.write(adapter); }

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter* adapter) { w.read(adapter); x.read(adapter); y.read(adapter); z.read(adapter); }

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter* adapter) { z.pushBack(adapter); y.pushBack(adapter); x.pushBack(adapter); w.pushBack(adapter); }

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter* /*adapter*/ = NULL) const { return 4*sizeof(gzFloat); }

	GZ_BASE_EXPORT operator gzQuaternion() const { return gzQuaternion(w, x, y, z); }

	GZ_BASE_EXPORT const gzQuaternion& operator = (const gzQuaternion& data) { w = data.w; x = data.x; y = data.y; z = data.z; return data; }

	GZ_BASE_EXPORT gzVoid setBigEndian(gzBool useBigEndian) { w.setBigEndian(useBigEndian); x.setBigEndian(useBigEndian); y.setBigEndian(useBigEndian); z.setBigEndian(useBigEndian); }

	gzSerializeBinary<gzFloat> w, x, y, z;
};

//******************************************************************************
// Class	: gzSerializeVec2D
//									
// Purpose  : Help class for gzVec2D storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	220221	Created				(2.11.71)
//									
//******************************************************************************
class  gzSerializeVec2D : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeVec2D(gzBool useBigEndian = TRUE) :v1(useBigEndian), v2(useBigEndian) {};

	GZ_BASE_EXPORT virtual ~gzSerializeVec2D() {};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter* adapter) { v1.write(adapter); v2.write(adapter); }

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter* adapter) { v1.read(adapter); v2.read(adapter); }

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter* adapter) { v2.pushBack(adapter); v1.pushBack(adapter); }

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter* /*adapter*/ = NULL) const { return 2 * sizeof(gzDouble);	}

	GZ_BASE_EXPORT operator gzVec2D () const { return gzVec2D((gzDouble)v1, (gzDouble)v2); }

	GZ_BASE_EXPORT const gzVec2D& operator = (const gzVec2D& data) { v1 = data.v1; v2 = data.v2; return data; }

	GZ_BASE_EXPORT gzVoid setBigEndian(gzBool useBigEndian) { v1.setBigEndian(useBigEndian); v2.setBigEndian(useBigEndian); }


	gzSerializeBinary<gzDouble> v1, v2;
};

//******************************************************************************
// Class	: gzSerializeVec3D
//									
// Purpose  : Help class for gzVec3D storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	220221	Created					(2.11.71) 
//									
//******************************************************************************
class  gzSerializeVec3D : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeVec3D(gzBool useBigEndian = TRUE) :v1(useBigEndian), v2(useBigEndian), v3(useBigEndian) {};

	GZ_BASE_EXPORT virtual ~gzSerializeVec3D() {};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter* adapter) { v1.write(adapter); v2.write(adapter); v3.write(adapter); }

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter* adapter) { v1.read(adapter); v2.read(adapter); v3.read(adapter); }

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter* adapter) { v3.pushBack(adapter); v2.pushBack(adapter); v1.pushBack(adapter); }

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter* /*adapter*/ = NULL) const { return 3 * sizeof(gzDouble); }

	GZ_BASE_EXPORT operator gzVec3D () const { return gzVec3D((gzDouble)v1, (gzDouble)v2, (gzDouble)v3); }

	GZ_BASE_EXPORT const gzVec3D& operator = (const gzVec3D& data) { v1 = data.v1; v2 = data.v2; v3 = data.v3; return data; }

	GZ_BASE_EXPORT gzVoid setBigEndian(gzBool useBigEndian) { v1.setBigEndian(useBigEndian); v2.setBigEndian(useBigEndian); v3.setBigEndian(useBigEndian); }

	gzSerializeBinary<gzDouble> v1, v2, v3;
};

//******************************************************************************
// Class	: gzSerializeVec4D
//									
// Purpose  : Help class for gzVec4D storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	220221	Created				(2.11.71)
//									
//******************************************************************************
class  gzSerializeVec4D : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeVec4D(gzBool useBigEndian = TRUE) :v1(useBigEndian), v2(useBigEndian), v3(useBigEndian), v4(useBigEndian) {};

	GZ_BASE_EXPORT virtual ~gzSerializeVec4D() {};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter* adapter) { v1.write(adapter); v2.write(adapter); v3.write(adapter); v4.write(adapter); }

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter* adapter) { v1.read(adapter); v2.read(adapter); v3.read(adapter); v4.read(adapter); }

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter* adapter) { v4.pushBack(adapter); v3.pushBack(adapter); v2.pushBack(adapter); v1.pushBack(adapter); }

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter* /*adapter*/ = NULL) const { return 4 * sizeof(gzDouble); }

	GZ_BASE_EXPORT operator gzVec4D() const { return gzVec4D((gzDouble)v1, (gzDouble)v2, (gzDouble)v3, (gzDouble)v4); }

	GZ_BASE_EXPORT const gzVec4D& operator = (const gzVec4D& data) { v1 = data.v1; v2 = data.v2; v3 = data.v3; v4 = data.v4; return data; }

	GZ_BASE_EXPORT gzVoid setBigEndian(gzBool useBigEndian) { v1.setBigEndian(useBigEndian); v2.setBigEndian(useBigEndian); v3.setBigEndian(useBigEndian); v4.setBigEndian(useBigEndian); }

	gzSerializeBinary<gzDouble> v1, v2, v3, v4;
};

//******************************************************************************
// Class	: gzSerializeGUID
//									
// Purpose  : Help class for gzGUID storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	051206	Created 
//									
//******************************************************************************
class  gzSerializeGUID : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeGUID(){};

	GZ_BASE_EXPORT gzSerializeGUID(const gzGUID &copy):m_data(copy){};

	GZ_BASE_EXPORT virtual ~gzSerializeGUID(){};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override; 

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter * /*adapter*/ =nullptr) const override { return sizeof(gzGUID); }

	GZ_BASE_EXPORT operator const gzGUID & () const { return m_data;}

	GZ_BASE_EXPORT gzGUID & operator = (const gzGUID &data) { m_data=data; return m_data;}

private:

	gzGUID	m_data;

};

//******************************************************************************
// Class	: gzSerializeMatrix3
//									
// Purpose  : Help class for gzMatrix3 storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080521	Created 
//									
//******************************************************************************
class  gzSerializeMatrix3 : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeMatrix3(gzBool useBig=TRUE):
	v11(useBig),v21(useBig),v31(useBig),
	v12(useBig),v22(useBig),v32(useBig),
	v13(useBig),v23(useBig),v33(useBig){};

	GZ_BASE_EXPORT virtual ~gzSerializeMatrix3(){};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) 
	{ 
		v11.write(adapter); v21.write(adapter) ; v31.write(adapter);
		v12.write(adapter); v22.write(adapter) ; v32.write(adapter);
		v13.write(adapter); v23.write(adapter) ; v33.write(adapter);
	}

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) 
	{ 
		v11.read(adapter); v21.read(adapter) ; v31.read(adapter); 
		v12.read(adapter); v22.read(adapter) ; v32.read(adapter);
		v13.read(adapter); v23.read(adapter) ; v33.read(adapter);
	}

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) 
	{
		v33.pushBack(adapter); v23.pushBack(adapter); v13.pushBack(adapter);
		v32.pushBack(adapter); v22.pushBack(adapter); v12.pushBack(adapter);
		v31.pushBack(adapter); v21.pushBack(adapter); v11.pushBack(adapter);
	}

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter * /*adapter*/=nullptr) const 
	{ 
		return	sizeof(gzFloat)*9;
	}

	GZ_BASE_EXPORT operator gzMatrix3 () const
	{ 
		gzMatrix3 retmat;

		retmat.v11=(gzFloat)v11;
		retmat.v12=(gzFloat)v12;
		retmat.v13=(gzFloat)v13;
		retmat.v21=(gzFloat)v21;
		retmat.v22=(gzFloat)v22;
		retmat.v23=(gzFloat)v23;
		retmat.v31=(gzFloat)v31;
		retmat.v32=(gzFloat)v32;
		retmat.v33=(gzFloat)v33;

		return retmat; 
	}

	GZ_BASE_EXPORT const gzMatrix3 & operator = (const gzMatrix3 &data) 
	{ 
		v11=data.v11;
		v12=data.v12;
		v13=data.v13;
		v21=data.v21;
		v22=data.v22;
		v23=data.v23;
		v31=data.v31;
		v32=data.v32;
		v33=data.v33;

		return data;
	}

	GZ_BASE_EXPORT gzVoid setBigEndian(gzBool useBigEndian)
	{ 
		v11.setBigEndian(useBigEndian); v12.setBigEndian(useBigEndian); v13.setBigEndian(useBigEndian); 
		v21.setBigEndian(useBigEndian); v22.setBigEndian(useBigEndian); v23.setBigEndian(useBigEndian); 
		v31.setBigEndian(useBigEndian); v32.setBigEndian(useBigEndian); v33.setBigEndian(useBigEndian); 
	}


	gzSerializeBinary<gzFloat> v11,v21,v31;
	gzSerializeBinary<gzFloat> v12,v22,v32;
	gzSerializeBinary<gzFloat> v13,v23,v33;
	gzSerializeBinary<gzFloat> v14,v24,v34;
};

//******************************************************************************
// Class	: gzSerializeMatrix4
//									
// Purpose  : Help class for gzMatrix4 storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990401	Created 
//									
//******************************************************************************
class  gzSerializeMatrix4 : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeMatrix4(gzBool useBig=TRUE):
	v11(useBig),v21(useBig),v31(useBig),v41(useBig),
	v12(useBig),v22(useBig),v32(useBig),v42(useBig),
	v13(useBig),v23(useBig),v33(useBig),v43(useBig),
	v14(useBig),v24(useBig),v34(useBig),v44(useBig){};

	GZ_BASE_EXPORT virtual ~gzSerializeMatrix4(){};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) 
	{ 
		v11.write(adapter); v21.write(adapter) ; v31.write(adapter); v41.write(adapter); 
		v12.write(adapter); v22.write(adapter) ; v32.write(adapter); v42.write(adapter); 
		v13.write(adapter); v23.write(adapter) ; v33.write(adapter); v43.write(adapter); 
		v14.write(adapter); v24.write(adapter) ; v34.write(adapter); v44.write(adapter); 
	}

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) 
	{ 
		v11.read(adapter); v21.read(adapter) ; v31.read(adapter); v41.read(adapter); 
		v12.read(adapter); v22.read(adapter) ; v32.read(adapter); v42.read(adapter); 
		v13.read(adapter); v23.read(adapter) ; v33.read(adapter); v43.read(adapter); 
		v14.read(adapter); v24.read(adapter) ; v34.read(adapter); v44.read(adapter); 
	}

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) 
	{ 
		v44.pushBack(adapter); v34.pushBack(adapter); v24.pushBack(adapter); v14.pushBack(adapter);
		v43.pushBack(adapter); v33.pushBack(adapter); v23.pushBack(adapter); v13.pushBack(adapter);
		v42.pushBack(adapter); v32.pushBack(adapter); v22.pushBack(adapter); v12.pushBack(adapter);
		v41.pushBack(adapter); v31.pushBack(adapter); v21.pushBack(adapter); v11.pushBack(adapter);
	}

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter * /*adapter*/=nullptr) const 
	{ 
		return	sizeof(gzFloat)<<4UL;
	}

	GZ_BASE_EXPORT operator gzMatrix4 () const
	{ 
		gzMatrix4 retmat;

		retmat.v11=(gzFloat)v11;
		retmat.v12=(gzFloat)v12;
		retmat.v13=(gzFloat)v13;
		retmat.v14=(gzFloat)v14;
		retmat.v21=(gzFloat)v21;
		retmat.v22=(gzFloat)v22;
		retmat.v23=(gzFloat)v23;
		retmat.v24=(gzFloat)v24;
		retmat.v31=(gzFloat)v31;
		retmat.v32=(gzFloat)v32;
		retmat.v33=(gzFloat)v33;
		retmat.v34=(gzFloat)v34;
		retmat.v41=(gzFloat)v41;
		retmat.v42=(gzFloat)v42;
		retmat.v43=(gzFloat)v43;
		retmat.v44=(gzFloat)v44;

		return retmat; 
	}

	GZ_BASE_EXPORT const gzMatrix4 & operator = (const gzMatrix4 &data) 
	{ 
		v11=data.v11;
		v12=data.v12;
		v13=data.v13;
		v14=data.v14;
		v21=data.v21;
		v22=data.v22;
		v23=data.v23;
		v24=data.v24;
		v31=data.v31;
		v32=data.v32;
		v33=data.v33;
		v34=data.v34;
		v41=data.v41;
		v42=data.v42;
		v43=data.v43;
		v44=data.v44;

		return data;
	}

	GZ_BASE_EXPORT gzVoid setBigEndian(gzBool useBigEndian)
	{ 
		v11.setBigEndian(useBigEndian); v12.setBigEndian(useBigEndian); v13.setBigEndian(useBigEndian); v14.setBigEndian(useBigEndian);
		v21.setBigEndian(useBigEndian); v22.setBigEndian(useBigEndian); v23.setBigEndian(useBigEndian); v24.setBigEndian(useBigEndian);
		v31.setBigEndian(useBigEndian); v32.setBigEndian(useBigEndian); v33.setBigEndian(useBigEndian); v34.setBigEndian(useBigEndian);
		v41.setBigEndian(useBigEndian); v42.setBigEndian(useBigEndian); v43.setBigEndian(useBigEndian); v44.setBigEndian(useBigEndian);
	}


	gzSerializeBinary<gzFloat> v11,v21,v31,v41;
	gzSerializeBinary<gzFloat> v12,v22,v32,v42;
	gzSerializeBinary<gzFloat> v13,v23,v33,v43;
	gzSerializeBinary<gzFloat> v14,v24,v34,v44;
};

// Specials

template <> inline gzVoid gzSerializeBinary<gzVec2>::write(gzSerializeAdapter *adapter)
{
	gzSerializeVec2 data(m_useBigEndian);
	data=m_data;
	data.write(adapter);
}

template <> inline gzVoid gzSerializeBinary<gzVec2>::read(gzSerializeAdapter *adapter)
{
	gzSerializeVec2 data(m_useBigEndian);
	data.read(adapter);
	m_data=data;
}

template <> inline gzVoid gzSerializeBinary<gzVec2>::pushBack(gzSerializeAdapter *adapter)
{
	gzSerializeVec2 data(m_useBigEndian);
	data=m_data;
	data.pushBack(adapter);
}

template <> inline gzVoid gzSerializeBinary<gzVec3>::write(gzSerializeAdapter *adapter)
{
	gzSerializeVec3 data(m_useBigEndian);
	data=m_data;
	data.write(adapter);
}

template <> inline gzVoid gzSerializeBinary<gzVec3>::read(gzSerializeAdapter *adapter)
{
	gzSerializeVec3 data(m_useBigEndian);
	data.read(adapter);
	m_data=data;
}

template <> inline gzVoid gzSerializeBinary<gzVec3>::pushBack(gzSerializeAdapter *adapter)
{
	gzSerializeVec3 data(m_useBigEndian);
	data=m_data;
	data.pushBack(adapter);
}

template <> inline gzVoid gzSerializeBinary<gzVec4>::write(gzSerializeAdapter *adapter)
{
	gzSerializeVec4 data(m_useBigEndian);
	data=m_data;
	data.write(adapter);
}

template <> inline gzVoid gzSerializeBinary<gzVec4>::read(gzSerializeAdapter *adapter)
{
	gzSerializeVec4 data(m_useBigEndian);
	data.read(adapter);
	m_data=data;
}

template <> inline gzVoid gzSerializeBinary<gzVec4>::pushBack(gzSerializeAdapter *adapter)
{
	gzSerializeVec4 data(m_useBigEndian);
	data=m_data;
	data.pushBack(adapter);
}


//******************************************************************************
// Class	: gzSerializeBinaryArray
//									
// Purpose  : Help class for binary array storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990401	Created 
//									
//******************************************************************************
template <class T> class gzSerializeBinaryArray : public gzSerializeData
{
public:
	
	gzSerializeBinaryArray<T>(gzBool useSizeInfo=TRUE,gzBool useBigEndian=TRUE):m_useSizeInfo(useSizeInfo),m_useBigEndian(useBigEndian),m_data(&m_local){};

	gzSerializeBinaryArray<T>(const gzSerializeBinaryArray<T> &right):m_useSizeInfo(right.m_useSizeInfo),m_useBigEndian(right.m_useBigEndian),m_data(&m_local)
	{
		setData(right);
	}

	gzSerializeBinaryArray<T> &operator=(const gzSerializeBinaryArray<T> &right)
	{
		setData(right);

		return *this;
	}

	virtual gzVoid write(gzSerializeAdapter *adapter) override;

	virtual gzVoid read(gzSerializeAdapter *adapter) override;

	virtual gzVoid pushBack(gzSerializeAdapter *adapter) override
	{
		gzUInt32 i;
		
		gzSerializeBinary<T> data(m_useBigEndian);

		for(i=0;i<m_data->getSize();i++)
		{
			data=(*m_data)[m_data->getSize()-1-i];
			data.pushBack(adapter);
		}

		if(m_useSizeInfo)
		{
			gzVarUInt64 size;
			size=m_data->getSize();
			size.pushBack(adapter);
		}
	}

	virtual gzUInt32	getDataSize(gzSerializeAdapter * /*adapter*/=nullptr) const override
	{
		if(m_useSizeInfo)
		{
			gzVarUInt64 size;

			size=m_data->getSize();
			
			return sizeof(T)*m_data->getSize()+size.getDataSize();
		}
		else
			return sizeof(T)*m_data->getSize();

	}


	operator const gzArray<T> & () const			
	{
		return *m_data; 
	}

	operator gzArray<T> & () 			
	{
		return *m_data; 
	}

	gzVoid setArray(const gzArray<T> & data)
	{
		m_data=&(gzArray<T> &)data;
	}

	gzVoid setData(const gzArray<T> & data)
	{
		m_data=&m_local;	// use local storage
		(*m_data)=data;
	}

	gzVoid setData(const T * data,gzUInt32 length) 
	{
		m_data=&m_local;	// use local storage

		m_data->setSize(length);

		for(gzUInt32 i=0;i<length;i++)
			m_data[i]=data[i];
	}

	gzVoid		setSize(gzUInt32 size)									
	{ 
		m_data=&m_local;	// use local storage
		m_data->setSize(size); 
	}

	gzUInt32		getSize()		const									{ return m_data->getSize(); }

	T *			getAddress()											{ return m_data->getAddress(); }

	T & operator [](gzUInt32 index)										{ return (*m_data)[index]; }

private:

	gzBool			m_useSizeInfo;

	gzBool			m_useBigEndian;

	gzArray<T> *	m_data;

	gzArray<T>		m_local;

};

template <class T> inline gzVoid gzSerializeBinaryArray<T>::write(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{

		gzVarUInt64 size;

		size=m_data->getSize();
		size.write(adapter);
	}

	if (m_useBigEndian == gzBigEndian())
	{
		adapter->write((gzUByte*)m_data->getAddress(), m_data->getSize() * sizeof(T));
	}
	else
	{
		gzSerializeBinary<T> data(m_useBigEndian);

		for (gzUInt32 i = 0; i < m_data->getSize(); i++)
		{
			data = (*m_data)[i];
			data.write(adapter);
		}
	}
}

template <> inline gzVoid gzSerializeBinaryArray<gzUByte>::write(gzSerializeAdapter* adapter)
{
	if (m_useSizeInfo)
	{

		gzVarUInt64 size;

		size = m_data->getSize();
		size.write(adapter);
	}

	adapter->write((gzUByte*)m_data->getAddress(), m_data->getSize());
}


template <class T> inline gzVoid gzSerializeBinaryArray<T>::read(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{
		gzVarUInt64 size;

		size.read(adapter);
		m_data->setSize((gzUInt32)size);
	}

	if (gzBigEndian() == m_useBigEndian)
	{
		adapter->read((gzUByte*)m_data->getAddress(), m_data->getSize() * sizeof(T));
	}
	else
	{
		gzSerializeBinary<T> data(m_useBigEndian);

		for (gzUInt32 i = 0; i < m_data->getSize(); i++)
		{
			data.read(adapter);
			(*m_data)[i] = data;
		}
	}
}


template <> inline gzVoid gzSerializeBinaryArray<gzUByte>::read(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{
		gzVarUInt64 size;

		size.read(adapter);
		m_data->setSize(gzCastToUInt32(size));
	}

	adapter->read(m_data->getAddress(),m_data->getSize());
}

//******************************************************************************
// Class	: gzSerializeBinaryDynamicArray
//									
// Purpose  : Help class for binary dynamic array storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990401	Created 
//									
//******************************************************************************
template <class T> class gzSerializeBinaryDynamicArray : public gzSerializeData
{
public:
	
	gzSerializeBinaryDynamicArray<T>(gzBool useSizeInfo=TRUE,gzBool useBigEndian=TRUE):m_useSizeInfo(useSizeInfo),m_useBigEndian(useBigEndian),m_data(&m_local){};

	gzSerializeBinaryDynamicArray<T>(const gzSerializeBinaryDynamicArray<T> &right):m_useSizeInfo(right.m_useSizeInfo),m_useBigEndian(right.m_useBigEndian),m_data(&m_local)
	{
		setData(right);
	}

	gzSerializeBinaryDynamicArray<T> &operator=(const gzSerializeBinaryDynamicArray<T> &right)
	{
		setData(right);

		return *this;
	}

	virtual gzVoid write(gzSerializeAdapter *adapter) override;

	virtual gzVoid read(gzSerializeAdapter *adapter) override;

	virtual gzVoid pushBack(gzSerializeAdapter *adapter) override
	{
		gzUInt32 i;
		
		gzSerializeBinary<T> data(m_useBigEndian);

		for(i=0;i<m_data->getSize();i++)
		{
			data=(*m_data)[m_data->getSize()-1-i];
			data.pushBack(adapter);
		}

		if(m_useSizeInfo)
		{
			gzVarUInt64 size;
			size=m_data->getSize();
			size.pushBack(adapter);
		}
	}

	virtual gzUInt32	getDataSize(gzSerializeAdapter * /*adapter*/=nullptr) const override
	{
		if(m_useSizeInfo)
		{
			gzVarUInt64 size;

			size=m_data->getSize();
			
			return sizeof(T)*m_data->getSize()+size.getDataSize();
		}
		else
			return sizeof(T)*m_data->getSize();

	}


	operator const gzDynamicArray<T> & () const			
	{
		return *m_data; 
	}

	operator gzDynamicArray<T> & () 			
	{
		return *m_data; 
	}

	gzVoid setArray(const gzDynamicArray<T> & data)
	{
		m_data=&(gzDynamicArray<T> &)data;
	}

	gzVoid setData(const gzDynamicArray<T> & data)
	{
		m_data=&m_local;	// use local storage
		(*m_data)=data;
	}

	gzVoid setData(const T * data,gzUInt32 length) 
	{
		m_data=&m_local;	// use local storage

		m_data->setSize(length);

		for(gzUInt32 i=0;i<length;i++)
			m_data[i]=data[i];
	}

	gzVoid		setSize(gzUInt32 size)									
	{ 
		m_data=&m_local;	// use local storage
		m_data->setSize(size); 
	}

	gzUInt32		getSize()		const									{ return m_data->getSize(); }

	T *			getAddress()											{ return m_data->getAddress(); }

	T & operator [](gzUInt32 index)										{ return (*m_data)[index]; }

private:

	gzBool					m_useSizeInfo;

	gzBool					m_useBigEndian;

	gzDynamicArray<T> *		m_data;

	gzDynamicArray<T>		m_local;

};

template <class T> inline gzVoid gzSerializeBinaryDynamicArray<T>::write(gzSerializeAdapter *adapter)
{
	gzUInt32 i;

	if(m_useSizeInfo)
	{

		gzVarUInt64 size;

		size=m_data->getSize();
		size.write(adapter);
	}

	gzSerializeBinary<T> data(m_useBigEndian);

	for(i=0;i<m_data->getSize();i++)
	{
		data=(*m_data)[i];
		data.write(adapter);
	}
}

template <> inline gzVoid gzSerializeBinaryDynamicArray<gzUInt32>::write(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{

		gzVarUInt64 size;

		size=m_data->getSize();
		size.write(adapter);
	}

	if(gzBigEndian()==m_useBigEndian)	// We can do a binary Write
	{
		adapter->write((gzUByte *)m_data->getAddress(),m_data->getSize()*sizeof(gzUInt32));
	}
	else
	{
		gzSerializeBinary<gzUInt32> data(m_useBigEndian);

		gzUInt32 i;

		for(i=0;i<m_data->getSize();i++)
		{
			data=(*m_data)[i];
			data.write(adapter);
		}
	}
}

template <> inline gzVoid gzSerializeBinaryDynamicArray<gzVec2>::write(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{

		gzVarUInt64 size;

		size=m_data->getSize();
		size.write(adapter);
	}

	if(gzBigEndian()==m_useBigEndian)	// We can do a binary Write
	{
		adapter->write((gzUByte *)m_data->getAddress(),m_data->getSize()*sizeof(gzVec2));
	}
	else
	{
		gzSerializeBinary<gzVec2> data(m_useBigEndian);

		gzUInt32 i;

		for(i=0;i<m_data->getSize();i++)
		{
			data=(*m_data)[i];
			data.write(adapter);
		}
	}
}

template <> inline gzVoid gzSerializeBinaryDynamicArray<gzVec3>::write(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{

		gzVarUInt64 size;

		size=m_data->getSize();
		size.write(adapter);
	}

	if(gzBigEndian()==m_useBigEndian)	// We can do a binary Write
	{
		adapter->write((gzUByte *)m_data->getAddress(),m_data->getSize()*sizeof(gzVec3));
	}
	else
	{
		gzSerializeBinary<gzVec3> data(m_useBigEndian);

		gzUInt32 i;

		for(i=0;i<m_data->getSize();i++)
		{
			data=(*m_data)[i];
			data.write(adapter);
		}
	}
}

template <> inline gzVoid gzSerializeBinaryDynamicArray<gzVec4>::write(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{

		gzVarUInt64 size;

		size=m_data->getSize();
		size.write(adapter);
	}

	if(gzBigEndian()==m_useBigEndian)	// We can do a binary Write
	{
		adapter->write((gzUByte *)m_data->getAddress(),m_data->getSize()*sizeof(gzVec4));
	}
	else
	{
		gzSerializeBinary<gzVec4> data(m_useBigEndian);

		gzUInt32 i;

		for(i=0;i<m_data->getSize();i++)
		{
			data=(*m_data)[i];
			data.write(adapter);
		}
	}
}

template <> inline gzVoid gzSerializeBinaryDynamicArray<gzUByte>::write(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{

		gzVarUInt64 size;

		size=m_data->getSize();
		size.write(adapter);
	}

	adapter->write(m_data->getAddress(),m_data->getSize());
}

template <class T> inline gzVoid gzSerializeBinaryDynamicArray<T>::read(gzSerializeAdapter *adapter)
{
	gzUInt32 i;

	if(m_useSizeInfo)
	{
		gzVarUInt64 size;

		size.read(adapter);
		m_data->setSize((gzUInt32)size);
	}

	gzSerializeBinary<T> data(m_useBigEndian);

	for(i=0;i<m_data->getSize();i++)
	{
		data.read(adapter);
		(*m_data)[i]=data;
	}
}

template <> inline gzVoid gzSerializeBinaryDynamicArray<gzUInt32>::read(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{
		gzVarUInt64 size;

		size.read(adapter);
		m_data->setSize((gzUInt32)size);
	}

	if(gzBigEndian()==m_useBigEndian)
	{
		adapter->read((gzUByte *)m_data->getAddress(),m_data->getSize()*sizeof(gzUInt32));
	}
	else
	{
		gzSerializeBinary<gzUInt32> data(m_useBigEndian);

		gzUInt32 i;

		for(i=0;i<m_data->getSize();i++)
		{
			data.read(adapter);
			(*m_data)[i]=data;
		}
	}
}

template <> inline gzVoid gzSerializeBinaryDynamicArray<gzVec2>::read(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{
		gzVarUInt64 size;

		size.read(adapter);
		m_data->setSize((gzUInt32)size);
	}

	if(gzBigEndian()==m_useBigEndian)
	{
		adapter->read((gzUByte *)m_data->getAddress(),m_data->getSize()*sizeof(gzVec2));
	}
	else
	{
		gzSerializeBinary<gzVec2> data(m_useBigEndian);

		gzUInt32 i;

		for(i=0;i<m_data->getSize();i++)
		{
			data.read(adapter);
			(*m_data)[i]=data;
		}
	}
}

template <> inline gzVoid gzSerializeBinaryDynamicArray<gzVec3>::read(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{
		gzVarUInt64 size;

		size.read(adapter);
		m_data->setSize((gzUInt32)size);
	}

	if(gzBigEndian()==m_useBigEndian)
	{
		adapter->read((gzUByte *)m_data->getAddress(),m_data->getSize()*sizeof(gzVec3));
	}
	else
	{
		gzSerializeBinary<gzVec3> data(m_useBigEndian);

		gzUInt32 i;

		for(i=0;i<m_data->getSize();i++)
		{
			data.read(adapter);
			(*m_data)[i]=data;
		}
	}
}

template <> inline gzVoid gzSerializeBinaryDynamicArray<gzVec4>::read(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{
		gzVarUInt64 size;

		size.read(adapter);
		m_data->setSize((gzUInt32)size);
	}

	if(gzBigEndian()==m_useBigEndian)
	{
		adapter->read((gzUByte *)m_data->getAddress(),m_data->getSize()*sizeof(gzVec4));
	}
	else
	{
		gzSerializeBinary<gzVec4> data(m_useBigEndian);

		gzUInt32 i;

		for(i=0;i<m_data->getSize();i++)
		{
			data.read(adapter);
			(*m_data)[i]=data;
		}
	}
}

template <> inline gzVoid gzSerializeBinaryDynamicArray<gzUByte>::read(gzSerializeAdapter *adapter)
{
	if(m_useSizeInfo)
	{
		gzVarUInt64 size;

		size.read(adapter);
		m_data->setSize(gzCastToUInt32(size));
	}
	adapter->read(m_data->getAddress(),m_data->getSize());
}

// ------------------------ Cascaded Adapter -----------------------------------
// Adapters that contains a sub adapter and adds compression/encoding etc. 

//! Use this macros to move data storage to sub adapter
#define GZ_ROUTE_ADAPTER(ADAPT,EXPORT)	EXPORT virtual gzMutex& getAdapterLock() const override { return ADAPT->getAdapterLock(); } \
										EXPORT virtual gzGUIDInstanceDictionary& getGUIDWriteInstanceDictionary() override { return ADAPT->getGUIDWriteInstanceDictionary(); } \
										EXPORT virtual gzGUIDInstanceDictionary& getGUIDReadInstanceDictionary() override { return ADAPT->getGUIDReadInstanceDictionary(); } \
										EXPORT virtual gzRefInstanceDictionary& getRefWriteInstanceDictionary() override { return ADAPT->getRefWriteInstanceDictionary(); } \
										EXPORT virtual gzRefInstanceDictionary& getRefReadInstanceDictionary() override { return ADAPT->getRefReadInstanceDictionary(); } \
										EXPORT virtual gzRefInstanceArray& getRefWriteInstanceArray() override { return ADAPT->getRefWriteInstanceArray(); } \
										EXPORT virtual gzRefInstanceArray& getRefReadInstanceArray() override { return ADAPT->getRefReadInstanceArray(); } \
										EXPORT virtual gzUInt32 getNewInstanceID() override { return ADAPT->getNewInstanceID();} \
										EXPORT virtual gzVoid clearSharedInstanceData(gzSerializeAction action) override { ADAPT->clearSharedInstanceData(action); } \
										EXPORT virtual gzVoid copySharedInstanceData(gzSerializeAdapter* from,gzSerializeAction action) override { ADAPT->copySharedInstanceData(from,action);} \
										EXPORT virtual gzBool isBlocking() const override { return ADAPT->isBlocking();} \
										EXPORT virtual gzBool setBlocking(gzBool on) override { return ADAPT->setBlocking(on);} 

//******************************************************************************
// Class	: gzSerializeAdapterEncoder
//									
// Purpose  : Help class for scrambled storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011025	Created 
//									
//******************************************************************************
class  gzSerializeAdapterEncoder : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterEncoder(gzSerializeAdapter *sub,gzUInt64 encode=0);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterEncoder();

	GZ_BASE_EXPORT gzVoid setAdapter(gzSerializeAdapter* sub, gzUInt64 encode = 0);

	GZ_ROUTE_ADAPTER(m_adapter, GZ_BASE_EXPORT);

protected:
		
	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

private:

	gzUInt64				m_encode;

	gzSerializeAdapterPtr	m_adapter;
	
	gzUByte					m_last;

};

GZ_DECLARE_REFPTR(gzSerializeAdapterEncoder);

//******************************************************************************
// Class	: gzSerializeAdapterSimulator
//									
// Purpose  : Class for simulating errors in adapter stream
//									
// Notes	: This class routes to a sub adapter and can be used in combonation with any sub adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	211209	Created					(2.11.61) 
//									
//******************************************************************************
class gzSerializeAdapterSimulator : public gzSerializeAdapter
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterSimulator(gzSerializeAdapter* sub);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterSimulator();

	GZ_BASE_EXPORT gzVoid setAdapter(gzSerializeAdapter* sub);

	GZ_ROUTE_ADAPTER(m_adapter, GZ_BASE_EXPORT);

	GZ_BASE_EXPORT virtual gzBool isActive() const override;

	// --------------- Settings ----------------

	GZ_PROPERTY_EXPORT(gzUInt64, BytesReadBeforeStreamError, GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt64, BytesWrittenBeforeStreamError, GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzStreamErrorType, ReadError, GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzStreamErrorType, WriteError, GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt64, BytesReadBeforeClose, GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt64, BytesWrittenBeforeClose, GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt32, BytesReadBetweenDelay, GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32, BytesWrittenBetweenDelay, GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt64, BytesReadBeforeEOF, GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt64, SimulatedLength, GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzFloat, ReadErrorProbability, GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat, WriteErrorProbability, GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzUInt32, ReadDelay, GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32, WriteDelay, GZ_BASE_EXPORT);

protected:

	GZ_BASE_EXPORT	virtual gzVoid		write_imp(gzUByte data) override;
	GZ_BASE_EXPORT	virtual gzUByte		read_imp() override;
	GZ_BASE_EXPORT	virtual gzUInt32	length_imp() override;

private:

	gzUInt64				m_readDelayCounter;
	gzUInt64				m_writeDelayCounter;

	gzSerializeAdapterPtr	m_adapter;

};

GZ_DECLARE_REFPTR(gzSerializeAdapterSimulator);

//******************************************************************************
// Class	: gzSerializeAdapterBCDEncoder
//									
// Purpose  : Help class for byte Binary Coded Decimal pack/unpack in a string
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	060105	Created 
//									
//******************************************************************************
class  gzSerializeAdapterBCDEncoder : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterBCDEncoder(gzSerializeAdapter* sub);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterBCDEncoder();

	GZ_BASE_EXPORT gzVoid setAdapter(gzSerializeAdapter* sub);

	GZ_ROUTE_ADAPTER(m_adapter, GZ_BASE_EXPORT);

protected:

	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;

	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

private:

	gzSerializeAdapterPtr	m_adapter;
};

GZ_DECLARE_REFPTR(gzSerializeAdapterBCDEncoder);

//******************************************************************************
// Class	: gzSerializeAdapterBase64Encoder
//									
// Purpose  : Help class for base64 pack/unpack in a string
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	060105	Created 
//									
//******************************************************************************
class  gzSerializeAdapterBase64Encoder : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterBase64Encoder(gzSerializeAdapter* sub);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterBase64Encoder();

	GZ_BASE_EXPORT virtual	gzVoid flush() override;

	GZ_BASE_EXPORT gzVoid setAdapter(gzSerializeAdapter* sub);

	GZ_ROUTE_ADAPTER(m_adapter, GZ_BASE_EXPORT);

protected:

	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

private:

	gzSerializeAdapterPtr	m_adapter;
	gzUByte					m_state;
	gzUInt32				m_data;
};

GZ_DECLARE_REFPTR(gzSerializeAdapterBase64Encoder);

//******************************************************************************
// Class	: gzSerializeAdapterCompress
//									
// Purpose  : Help class for compressed storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011025	Created 
//									
//******************************************************************************
class  gzSerializeAdapterCompress : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterCompress(gzSerializeAdapter* sub);

	GZ_BASE_EXPORT virtual	~gzSerializeAdapterCompress();

	GZ_BASE_EXPORT virtual	gzVoid flush() override;

	GZ_BASE_EXPORT gzVoid	setChunkSize(gzUInt32 size);

	GZ_BASE_EXPORT gzVoid	setAdapter(gzSerializeAdapter* sub);

	GZ_ROUTE_ADAPTER(m_adapter, GZ_BASE_EXPORT);

protected:

	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzVoid	write_imp(const gzUByte* data, gzUInt32 count) override;
	GZ_BASE_EXPORT virtual gzUInt32	read_imp(gzUByte* data, gzUInt32 maxcount) override;

	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

private:

	gzVoid	compress();

	gzVoid	uncompress();

	gzSerializeAdapterPtr	m_adapter;

	gzQueue<gzUByte>		m_data;

	gzDynamicArray<gzUByte>	m_compress, m_uncompress, m_buffer;

	gzBool					m_pendingCompress;
};

GZ_DECLARE_REFPTR(gzSerializeAdapterCompress);

//******************************************************************************
// Class	: gzSerializeAdapterPartial
//									
// Purpose  : Help class for partial access to a parent adapter
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	231114	Created 
//									
//******************************************************************************
class  gzSerializeAdapterPartial : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterPartial(gzSerializeAdapter* sub,gzUInt32 length);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterPartial();

	GZ_BASE_EXPORT gzVoid setAdapter(gzSerializeAdapter* sub);

	GZ_ROUTE_ADAPTER(m_adapter, GZ_BASE_EXPORT);

protected:

	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;

	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

	GZ_BASE_EXPORT virtual gzVoid write_imp(const gzUByte* data, gzUInt32 count) override;

	GZ_BASE_EXPORT virtual gzUInt32 read_imp(gzUByte* data, gzUInt32 maxcount) override;

private:

	gzSerializeAdapterPtr	m_adapter;

	gzUInt32				m_length;
};

GZ_DECLARE_REFPTR(gzSerializeAdapterPartial);

class gzPipe;	// Forward decl

//******************************************************************************
// Class	: gzSerializeAdapterPurl
//									
// Purpose  : Help class for purl storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	200330	Created 
//									
//******************************************************************************
class  gzSerializeAdapterPurl : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterPurl(gzSerializeAdapter* sub);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterPurl();

	GZ_PROPERTY_EXPORT(gzBool,						WriteOnDelete,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,						Accnowledge,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,					PurlLookupName,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,					Topic,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,					SubUrl,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,					Password,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzSerializeAdapterFlags,		Flags,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,					Options,		GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzUInt32,					ThreadID,		GZ_BASE_EXPORT);

	GZ_BASE_EXPORT virtual	gzVoid flush() override;

	GZ_BASE_EXPORT gzVoid setAdapter(gzSerializeAdapter* sub);

	GZ_ROUTE_ADAPTER(m_adapter, GZ_BASE_EXPORT);

	GZ_BASE_EXPORT static gzVoid setAdapterPipe(const gzString& name, gzPipe* pipe);
	GZ_BASE_EXPORT static gzPipe *getAdapterPipe(const gzString& name);

protected:

	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzVoid	write_imp(const gzUByte* data, gzUInt32 count) override;
	GZ_BASE_EXPORT virtual gzUInt32	read_imp(gzUByte* data, gzUInt32 maxcount) override;

	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

private:

	gzSerializeAdapterPtr	m_adapter;
};

GZ_DECLARE_REFPTR(gzSerializeAdapterPurl);

//******************************************************************************
// Class	: gzSerializeAdapterRandomAccess
//									
// Purpose  : Help class for random access to stream
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	060105	Created 
//									
//******************************************************************************
class  gzSerializeAdapterRandomAccess : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterRandomAccess(gzSerializeAdapter *sub);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterRandomAccess();
	
	GZ_BASE_EXPORT virtual	gzBool canSeek() override;

	GZ_ROUTE_ADAPTER(m_adapter, GZ_BASE_EXPORT);

protected:

	GZ_BASE_EXPORT virtual	gzMemSize seek_imp(gzMemOffset offset, gzOriginPos origin = GZ_ORIGIN_SET) override;
		
	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

	GZ_BASE_EXPORT virtual gzVoid	write_imp(const gzUByte *data,gzUInt32 count) override;
	GZ_BASE_EXPORT virtual gzUInt32	read_imp(gzUByte *data,gzUInt32 maxcount) override;

private:

	gzSerializeAdapterPtr	m_adapter;
	gzMemOffset				m_offset;
	gzDynamicArray<gzUByte>	m_data;
	gzBool					m_written;
};

GZ_DECLARE_REFPTR(gzSerializeAdapterRandomAccess);

//******************************************************************************
// Class	: gzSerializeAdapterQueue
//									
// Purpose  : Help class for queue storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011025	Created 
//									
//******************************************************************************
class  gzSerializeAdapterQueue : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterQueue(gzQueueMode mode=GZ_QUEUE_LIFO , gzUInt32 chunkSize=100);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterQueue();

	GZ_BASE_EXPORT gzVoid	getQueueData(gzArray<gzUByte> &array);

	GZ_BASE_EXPORT gzVoid	getQueueData(gzArray<gzQWA_UByte> &array);

	GZ_BASE_EXPORT gzVoid	getQueueData(gzDynamicArray<gzUByte> &array);

	GZ_BASE_EXPORT gzVoid	getQueueData(gzDynamicArray<gzQWA_UByte> &array);

	GZ_BASE_EXPORT gzVoid	clear();				// Clears data but not pushback

	GZ_BASE_EXPORT gzVoid	setChunkSize(gzUInt32 size);

	GZ_BASE_EXPORT gzVoid	setRealSize(gzUInt32 size);

	GZ_BASE_EXPORT gzUByte *getAddress();

	GZ_BASE_EXPORT gzVoid	cleanUp();

	GZ_BASE_EXPORT gzVoid	flush() override;		// Performs a clear and clears pushback

	GZ_BASE_EXPORT gzVoid	swapArrayData(gzDynamicArray<gzUByte>& swapper);

	GZ_BASE_EXPORT gzVoid	swapArrayData(gzArray<gzUByte>& swapper);

protected:
		
	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzVoid	write_imp(const gzUByte *data,gzUInt32 count) override;
	GZ_BASE_EXPORT virtual gzUInt32	read_imp(gzUByte *data,gzUInt32 maxcount) override;

	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;


	gzQueue<gzUByte>	m_queue;
};

GZ_DECLARE_REFPTR(gzSerializeAdapterQueue);

//******************************************************************************
// Class	: gzSerializeAdapterPacket
//									
// Purpose  : Help class for packet storage
//									
// Notes	: This class is responsible to write/read data to adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	100215	Created 
//									
//******************************************************************************
class  gzSerializeAdapterPacket : public gzSerializeAdapter
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterPacket(gzUInt32 chunksize=1000 );

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterPacket();

protected:
		
	GZ_BASE_EXPORT virtual gzVoid	write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte	read_imp() override;

	GZ_BASE_EXPORT virtual gzVoid	write_imp(const gzUByte *data,gzUInt32 count) override;
	GZ_BASE_EXPORT virtual gzUInt32	read_imp(gzUByte *data,gzUInt32 maxcount) override;

	GZ_BASE_EXPORT virtual gzUInt32	length_imp() override;

	class gzPacketAdapterData : public gzRecycleData<gzDynamicArray<gzUByte> > , public gzReference
	{
	public:

		gzPacketAdapterData(gzUInt32 chunksize):m_chunksize(chunksize){} 
		virtual ~gzPacketAdapterData(){};

		virtual gzVoid onNewItem(gzDynamicArray<gzUByte>  &item) const
		{
			item.setChunkSize(m_chunksize);
		}

	private:

		gzUInt32 m_chunksize;
	};

	gzMutex								m_lock;
	gzRefList<gzPacketAdapterData>		m_packets;
	gzRefPointer<gzPacketAdapterData>	m_current;
	gzUInt32							m_chunksize;
	gzSerializeAdapterMemory			m_adapter;
	gzUInt32							m_size;
};

GZ_DECLARE_REFPTR(gzSerializeAdapterPacket);

//******************************************************************************
// Class	: gzSerializeAdapterString
//									
// Purpose  : Class for Serialize a gzString
//									
// Notes	: This class is responsible to write/read data to a gzString
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981019	Created 
//									
//******************************************************************************
class gzSerializeAdapterString : public gzSerializeAdapterQueue
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterString(const gzString *data=nullptr);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterString(){};

	GZ_BASE_EXPORT operator gzString ();

	GZ_BASE_EXPORT gzSerializeAdapterString & operator =(const gzString &str);
};

GZ_DECLARE_REFPTR(gzSerializeAdapterString);

//******************************************************************************
// Class	: gzLogger
//									
// Purpose  : Loggs output from gzMessage
//									
// Notes	: This class is responsible to write data to log adapter
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030217	Created 
//									
//******************************************************************************
class gzLogger : public gzReference , public gzMessageReceiverInterface
{
public:

	GZ_BASE_EXPORT gzLogger(const gzString &url=GZ_LOG_NAME,gzBool includeMachID=FALSE,gzDouble reconnectTime=0);

	GZ_BASE_EXPORT	virtual ~gzLogger();

	GZ_BASE_EXPORT gzVoid message(const gzString &message);

	GZ_BASE_EXPORT gzVoid enable(gzBool on);

	GZ_PROPERTY_EXPORT(gzString,	URL,			GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,	ReconnectTime,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,		IncludeMachID,	GZ_BASE_EXPORT);

protected:
		// ------------ the receiver --------------------
	virtual gzVoid onMessage(const gzString& sender , gzMessageLevel level , const char *message);

private:

	gzMutex				m_threadLock;

	gzSerializeAdapter	*m_adapter;

	gzDouble			m_connectTime;

	gzBool				m_enabled;
};

GZ_DECLARE_REFPTR(gzLogger);

//******************************************************************************
// Class	: gzMessageDatabase
//									
// Purpose  : Class for message information
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040203	Created 
//									
//******************************************************************************
class gzMessageDatabase : public gzReference , public gzMessageReceiverInterface
{
public:

	GZ_BASE_EXPORT gzMessageDatabase(gzBool useDefaultOutput=TRUE);
	GZ_BASE_EXPORT virtual ~gzMessageDatabase();


	GZ_BASE_EXPORT gzVoid message(const gzString &message);
	GZ_BASE_EXPORT gzVoid enable(gzBool on=TRUE);
	GZ_BASE_EXPORT gzVoid useDefaultOutput(gzBool on=TRUE);
	GZ_BASE_EXPORT gzVoid clearMessages();

	GZ_BASE_EXPORT gzVoid dumpMessages(const gzString &sender=GZ_EMPTY_STRING,gzMessageLevel level=(gzMessageLevel)0,gzSerializeAdapter *adapter=gzSerializeAdapter::getURLAdapter("con:"));

	GZ_BASE_EXPORT gzUInt32	getNumberOfSenders();
	GZ_BASE_EXPORT gzString	getSender(gzUInt32 senderIndex);

	GZ_BASE_EXPORT gzUInt32			getNumberOfLevels(const gzString &sender);
	GZ_BASE_EXPORT gzMessageLevel	getMessageLevel(const gzString &sender,gzUInt32 levelIndex);

	GZ_BASE_EXPORT gzUInt32	getNumberOfMessages(const gzString& sender,gzMessageLevel level);
	GZ_BASE_EXPORT gzString	getMessage(const gzString& sender,gzMessageLevel level,gzUInt32 messageIndex);
	GZ_BASE_EXPORT gzDouble	getMessageTime(const gzString& sender,gzMessageLevel level,gzUInt32 messageIndex);

private:

	virtual gzVoid onMessage(const gzString& sender , gzMessageLevel level , const char *message);

	class gzMessageDatabaseEntry
	{
	public:

		gzMessageDatabaseEntry(const char *message=nullptr);

		gzBool operator !=(const gzMessageDatabaseEntry &right) { return (time!=right.time) || (message!=right.message); }

		gzDouble	time;
		gzString	message;
	};

	class gzMessageDatabaseLevel : public gzReference
	{
	public:

		gzMessageDatabaseLevel(){}

		virtual ~gzMessageDatabaseLevel(){}

		gzQueue<gzMessageDatabaseEntry>	entries;

	};

	class gzMessageDatabaseSender : public gzReference
	{
	public:

		gzMessageDatabaseSender():levels(10){}

		virtual ~gzMessageDatabaseSender(){}

		gzRefDict<gzUInt32CompareInterface,gzMessageDatabaseLevel> levels;
	};

	gzRefDict<gzString,gzMessageDatabaseSender>	m_senders;

	gzBool	m_enabled:1;

	gzBool	m_useDefaultOutput:1;
};

// -------------------------- read/write utility functions ---------------------------


// writers --

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const T &data,const gzBool useBigEndian=TRUE)
{
	gzSerializeBinary<T> writer(useBigEndian);

	writer=data;

	writer.write(adapter);
}

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter* adapter, const gzTriState<T> & data, const gzBool useBigEndian = TRUE)
{
	adapter->write(data.isValid());

	if (data.isValid())
	{
		gzSerializeBinary<T> writer(useBigEndian);

		writer = data.value();

		writer.write(adapter);
	}
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzGUID &data,const gzBool /*useBigEndian*/)
{
	gzSerializeGUID writer;

	writer=data;

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzString &data,const gzBool /*useBigEndian*/)
{
	gzSerializeString writer;

	writer=data;

	writer.write(adapter);
}

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzXY<T> &data,const gzBool useBigEndian=TRUE)
{
	gzSerializeBinary<T> writer(useBigEndian);

	writer=data.x;

	writer.write(adapter);

	writer=data.y;

	writer.write(adapter);
}

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzXYZ<T> &data,const gzBool useBigEndian=TRUE)
{
	gzSerializeBinary<T> writer(useBigEndian);

	writer=data.x;

	writer.write(adapter);

	writer=data.y;

	writer.write(adapter);

	writer=data.z;

	writer.write(adapter);
}

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzSerializeList<T> writer;

	writer=data;

	writer.write(adapter);
}

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzDList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzSerializeDList<T> writer;

	writer=data;

	writer.write(adapter);
}

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzRefList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzSerializeRefList<T> writer;

	writer=data;

	writer.write(adapter);
}

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzRefDList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzSerializeRefDList<T> writer;

	writer=data;

	writer.write(adapter);
}

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzVarUInt64 len(data.getSize());

	len.write(adapter);

	gzSerializeArray<T> writer;

	writer=data;

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray<gzString> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	len.write(adapter);

	gzSerializeString writer;

	for(gzUInt32 i=0;i<data.getSize();i++)
	{
		writer=data.get(i);
		writer.write(adapter);
	}
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray<gzGUID> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	len.write(adapter);

	gzSerializeGUID writer;

	for(gzUInt32 i=0;i<data.getSize();i++)
	{
		writer=data.get(i);
		writer.write(adapter);
	}
}


template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray<gzUByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	len.write(adapter);

	adapter->write( ((gzArray<gzUByte> &)data).getAddress(),gzCastToUInt32(len));
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray<gzQWA_UByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	len.write(adapter);

	adapter->write( (gzUByte *)((gzArray<gzQWA_UByte> &)data).getAddress(),gzCastToUInt32(len));
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray<gzFloatXY> &data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzFloatXY> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter* adapter, const gzArray<gzFloatXYZ>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzFloatXYZ> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray<gzUInt32> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzUInt32> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray<gzInt32> &data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzInt32> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray<gzFloat> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzFloat> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter* adapter, const gzArray<gzDouble>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzDouble> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter* adapter, const gzArray<gzVec2>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzVec2> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter* adapter, const gzArray<gzVec3>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzVec3> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter* adapter, const gzArray<gzVec4>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzVec4> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray2D<gzFloat> &data,const gzBool useBigEndian)
{
	gzSerializeBinary<gzUInt32>	size(useBigEndian);

	size=data.getSize().x;

	size.write(adapter);

	size=data.getSize().y;

	size.write(adapter);

	gzSerializeBinaryArray<gzFloat> writer(FALSE,useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}



template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray<gzMatrix3> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzMatrix3>	writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzArray<gzMatrix4> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzMatrix4>	writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzSerializeArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	((gzSerializeArray<T> &)data).write(adapter);
}

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzVarUInt64 len(data.getSize());

	len.write(adapter);

	gzSerializeDynamicArray<T> writer;

	writer=data;

	writer.write(adapter);
}


template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzUByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	len.write(adapter);

	adapter->write( ((gzDynamicArray<gzUByte> &)data).getAddress(),gzCastToUInt32(len));
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzQWA_UByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());
	
	len.write(adapter);
	
	adapter->write((gzUByte *)((gzDynamicArray<gzQWA_UByte> &)data).getAddress(),gzCastToUInt32(len));
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzUInt32> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzUInt32> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzFloat> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzFloat> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzDouble> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzDouble> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzVec3> &data, const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzVec3> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzVec3 &data,const gzBool useBigEndian)
{
	gzSerializeVec3 writer(useBigEndian);

	writer=data;

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzVec4 &data,const gzBool useBigEndian)
{
	gzSerializeVec4 writer(useBigEndian);

	writer=data;

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzMatrix3 &data,const gzBool useBigEndian)
{
	gzSerializeMatrix3 writer(useBigEndian);

	writer=data;

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzMatrix4 &data,const gzBool useBigEndian)
{
	gzSerializeMatrix4 writer(useBigEndian);

	writer=data;

	writer.write(adapter);
}

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzRGBA &data,const gzBool useBigEndian)
{
	gzSerializeBinary<gzFloat> writer(useBigEndian);

	writer=data.getRed();
	writer.write(adapter);

	writer=data.getGreen();
	writer.write(adapter);

	writer=data.getBlue();
	writer.write(adapter);

	writer=data.getAlpha();
	writer.write(adapter);
}

template <class T> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzLateBindData<T> &data,const gzBool useBigEndian=TRUE)
{
	if(data.isBound())
	{
		writeAdapter(adapter,(gzUByte)1,useBigEndian);
		writeAdapter(adapter,data.read(),useBigEndian);
	}
	else
		writeAdapter(adapter,(gzUByte)0,useBigEndian);
}



// pushback --

template <class T> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const T &data,const gzBool useBigEndian=TRUE)
{
	gzSerializeBinary<T> writer(useBigEndian);

	writer=data;

	writer.pushBack(adapter);
}

template <class T> inline gzVoid pushBackAdapter(gzSerializeAdapter* adapter, const gzTriState<T>& data, const gzBool useBigEndian = TRUE)
{
	if (data.isValid())
	{
		gzSerializeBinary<T> writer(useBigEndian);

		writer = data.value();

		writer.pushBack(adapter);
	}

	adapter->pushBack(data.isValid());
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzGUID &data,const gzBool /*useBigEndian*/)
{
	gzSerializeGUID writer;

	writer=data;

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzString &data,const gzBool /*useBigEndian*/)
{
	gzSerializeString writer;

	writer=data;

	writer.pushBack(adapter);
}


template <class T> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzDList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzSerializeDList<T> writer;

	writer=data;

	writer.pushBack(adapter);
}

template <class T> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzRefDList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzSerializeRefDList<T> writer;

	writer=data;

	writer.pushBack(adapter);
}

template <class T> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzVarUInt64 len(data.getSize());

	gzSerializeArray<T> writer;

	writer=data;

	writer.pushBack(adapter);

	len.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray<gzUInt32> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzUInt32> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray<gzFloatXY> &data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzFloatXY> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter* adapter, const gzArray<gzFloatXYZ>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzFloatXYZ> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray<gzInt32> &data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzInt32> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray<gzFloat> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzFloat> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter* adapter, const gzArray<gzVec2>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzVec2> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter* adapter, const gzArray<gzVec3>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzVec3> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter* adapter, const gzArray<gzVec4>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzVec4> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray2D<gzFloat> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzFloat> writer(FALSE,useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);

	gzSerializeBinary<gzUInt32>	size(useBigEndian);

	size=data.getSize().y;

	size.pushBack(adapter);

	size=data.getSize().x;

	size.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray<gzString> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	gzSerializeString writer;

	gzUInt32 i=gzCastToUInt32(len);

	while(i)
	{
		writer=data.get(i);
		writer.pushBack(adapter);
		--i;
	}

	len.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray<gzGUID> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	gzSerializeGUID writer;

	gzUInt32 i=gzCastToUInt32(len);

	while(i)
	{
		writer=data.get(i);
		writer.pushBack(adapter);
		--i;
	}

	len.pushBack(adapter);
}


template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray<gzUByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	gzUInt32 i=gzCastToUInt32(len);

	while(i)
	{
		adapter->pushBack(*(((gzArray<gzUByte> &)data).getAddress()+i));
		--i;
	}

	len.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray<gzQWA_UByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	gzUInt32 i=gzCastToUInt32(len);

	while(i)
	{
		adapter->pushBack((gzUByte)*(((gzArray<gzUByte> &)data).getAddress()+i));
		--i;
	}

	len.pushBack(adapter);
}


template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray<gzMatrix3> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzMatrix3> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzArray<gzMatrix4> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzMatrix4> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <class T> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzSerializeArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	((gzSerializeArray<T> &)data).pushBack(adapter);
}


template <class T> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzVarUInt64 len(data.getSize());

	gzSerializeArray<T> writer;

	writer=data;

	writer.pushBack(adapter);

	len.pushBack(adapter);
}


template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzUByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	gzUInt32 i=gzCastToUInt32(len);

	while(i)
	{
		adapter->pushBack(*(((gzDynamicArray<gzUByte> &)data).getAddress()+i));
		--i;
	}

	len.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzQWA_UByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());
	
	gzUInt32 i=gzCastToUInt32(len);
	
	while(i)
	{
		adapter->pushBack(*(((gzDynamicArray<gzQWA_UByte> &)data).getAddress()+i));
		--i;
	}
	
	len.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzUInt32> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzUInt32> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzFloat> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzFloat> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzDouble> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzDouble> writer(TRUE,useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzDynamicArray<gzVec3> &data, const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzVec3> writer(TRUE, useBigEndian);

	writer.setArray(data);

	writer.pushBack(adapter);
}

template <class T> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzXY<T> &data,const gzBool useBigEndian=TRUE)
{
	gzSerializeBinary<T> writer(useBigEndian);

	writer=data.y;

	writer.pushBack(adapter);

	writer=data.x;

	writer.pushBack(adapter);

}

template <class T> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzXYZ<T> &data,const gzBool useBigEndian=TRUE)
{
	gzSerializeBinary<T> writer(useBigEndian);

	writer=data.z;

	writer.pushBack(adapter);

	writer=data.y;

	writer.pushBack(adapter);

	writer=data.x;

	writer.pushBack(adapter);

}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzVec3 &data,const gzBool useBigEndian)
{
	gzSerializeVec3 writer(useBigEndian);

	writer=data;

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzVec4 &data,const gzBool useBigEndian)
{
	gzSerializeVec4 writer(useBigEndian);

	writer=data;

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzMatrix3 &data,const gzBool useBigEndian)
{
	gzSerializeMatrix3 writer(useBigEndian);

	writer=data;

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzMatrix4 &data,const gzBool useBigEndian)
{
	gzSerializeMatrix4 writer(useBigEndian);

	writer=data;

	writer.pushBack(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzRGBA &data,const gzBool useBigEndian)
{
	gzSerializeBinary<gzFloat> writer(useBigEndian);

	writer=data.getAlpha();
	writer.pushBack(adapter);

	writer=data.getBlue();
	writer.pushBack(adapter);

	writer=data.getGreen();
	writer.pushBack(adapter);

	writer=data.getRed();
	writer.pushBack(adapter);
}


template <class T> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzLateBindData<T> &data,const gzBool useBigEndian=TRUE)
{
	if(data.isBound())
	{
		pushBackAdapter(adapter,data.read(),useBigEndian);
		pushBackAdapter(adapter,(gzUByte)1,useBigEndian);
	}
	else
		pushBackAdapter(adapter,(gzUByte)0,useBigEndian);
}


// readers ----------------------------------------------------

template <class T> inline gzBool readAdapter(gzSerializeAdapter *adapter, T &data,const gzBool useBigEndian=TRUE)
{
	gzSerializeBinary<T> reader(useBigEndian);

	if(!adapter->hasData(reader.getDataSize()))
		return FALSE;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <class T> inline gzBool readAdapter(gzSerializeAdapter* adapter, gzTriState<T> &data, const gzBool useBigEndian = TRUE)
{
	if (!adapter->hasData(1))
		return FALSE;

	gzBool valid(FALSE);

	readAdapter(adapter, valid);

	if (valid)
	{
		gzSerializeBinary<T> reader(useBigEndian);

		if (!adapter->hasData(reader.getDataSize()))
			return FALSE;

		reader.read(adapter);

		data = reader;
	}
	else
		data.clear();

	return TRUE;
}


template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzGUID &data,const gzBool /*useBigEndian*/)
{
	gzSerializeGUID reader;

	if(!adapter->hasData(reader.getDataSize()))
		return FALSE;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzString &data,const gzBool /*useBigEndian*/)
{
	gzSerializeString reader;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <class T> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzXY<T> &data,const gzBool useBigEndian=TRUE)
{
	gzSerializeBinary<T> reader(useBigEndian);

	if (!adapter->hasData(reader.getDataSize()))
		return FALSE;

	reader.read(adapter);

	data.x=reader;

	if (!adapter->hasData(reader.getDataSize()))
		return FALSE;

	reader.read(adapter);

	data.y=reader;

	return TRUE;
}

template <class T> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzXYZ<T> &data,const gzBool useBigEndian=TRUE)
{
	gzSerializeBinary<T> reader(useBigEndian);

	if (!adapter->hasData(reader.getDataSize()))
		return FALSE;

	reader.read(adapter);

	data.x=reader;

	if (!adapter->hasData(reader.getDataSize()))
		return FALSE;

	reader.read(adapter);

	data.y=reader;

	if (!adapter->hasData(reader.getDataSize()))
		return FALSE;

	reader.read(adapter);

	data.z=reader;

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzVec3 &data,const gzBool useBigEndian)
{
	gzSerializeVec3 reader(useBigEndian);

	if (!adapter->hasData(reader.getDataSize()))
		return FALSE;

	reader.read(adapter);

	data=reader;

	return TRUE;
}


template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzVec4 &data,const gzBool useBigEndian)
{
	gzSerializeVec4 reader(useBigEndian);

	if (!adapter->hasData(reader.getDataSize()))
		return FALSE;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzMatrix3 &data,const gzBool useBigEndian)
{
	gzSerializeMatrix3 reader(useBigEndian);

	if (!adapter->hasData(reader.getDataSize()))
		return FALSE;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzMatrix4 &data,const gzBool useBigEndian)
{
	gzSerializeMatrix4 reader(useBigEndian);

	if (!adapter->hasData(reader.getDataSize()))
		return FALSE;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <class T> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	if (!adapter->hasData(1))
		return FALSE;

	gzSerializeList<T> reader;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <class T> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzDList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	if (!adapter->hasData(1))
		return FALSE;

	gzSerializeDList<T> reader;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <class T> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzRefList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	if (!adapter->hasData(1))
		return FALSE;

	gzSerializeRefList<T> reader;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <class T> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzRefDList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	if (!adapter->hasData(1))
		return FALSE;

	gzSerializeRefDList<T> reader;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <class T> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzVarUInt64 len;

	if (!adapter->hasData(1))
		return FALSE;

	len.read(adapter);

	gzSerializeArray<T> reader;

	reader.setSize(gzCastToUInt32(len));

	reader.read(adapter);

	data=reader;

	return TRUE;
}


template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray<gzUByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len;

	if (!adapter->hasData(1))
		return FALSE;

	len.read(adapter);

	if (!adapter->hasData(gzCastToUInt32(len)))
		return FALSE;

	data.setSize(gzCastToUInt32(len));

	adapter->read(data.getAddress(), gzCastToUInt32(len));

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray<gzQWA_UByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len;

	if (!adapter->hasData(1))
		return FALSE;

	len.read(adapter);

	if (!adapter->hasData(gzCastToUInt32(len)))
		return FALSE;

	data.setSize(gzCastToUInt32(len));

	adapter->read((gzUByte *)data.getAddress(),gzCastToUInt32(len));

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray<gzInt32> &data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzInt32> reader(TRUE, useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray<gzUInt32> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzUInt32> reader(TRUE,useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray<gzFloatXY> &data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzFloatXY> reader(TRUE, useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter* adapter, gzArray<gzFloatXYZ>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzFloatXYZ> reader(TRUE, useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray<gzFloat> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzFloat> reader(TRUE,useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter* adapter, gzArray<gzVec2>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzVec2> reader(TRUE, useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter* adapter, gzArray<gzVec3>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzVec3> reader(TRUE, useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter* adapter, gzArray<gzVec4>& data, const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzVec4> reader(TRUE, useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray2D<gzFloat> &data,const gzBool useBigEndian)
{
	gzSerializeBinary<gzUInt32>	size(useBigEndian);

	size.read(adapter);

	gzUInt32 sizeX=size;

	size.read(adapter);

	gzUInt32 sizeY=size;

	data.setSize(sizeX,sizeY);

	gzSerializeBinaryArray<gzFloat> reader(FALSE,useBigEndian);

	reader.setArray(data);

	reader.read(adapter);
	
	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray<gzString> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	if (!adapter->hasData(1))
		return FALSE;

	len.read(adapter);

	if (!adapter->hasData(gzCastToUInt32(len)))
		return FALSE;

	data.setSize(gzCastToUInt32(len));

	gzSerializeString reader;

	for(gzUInt32 i=0;i<data.getSize();i++)
	{
		reader.read(adapter);
		data[i]=reader;
	}

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray<gzGUID> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	if (!adapter->hasData(1))
		return FALSE;

	len.read(adapter);

	if (!adapter->hasData(gzCastToUInt32(len)))
		return FALSE;

	data.setSize(gzCastToUInt32(len));

	gzSerializeGUID reader;

	for(gzUInt32 i=0;i<data.getSize();i++)
	{
		reader.read(adapter);
		data[i]=reader;
	}

	return TRUE;
}


template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray<gzMatrix3> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzMatrix3> reader(TRUE,useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzArray<gzMatrix4> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryArray<gzMatrix4> reader(TRUE,useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <class T> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzSerializeArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	((gzSerializeArray<T> &)data).read(adapter);

	return TRUE;
}

template <class T> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzDynamicArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzVarUInt64 len;

	if (!adapter->hasData(1))
		return FALSE;

	len.read(adapter);

	gzSerializeDynamicArray<T> reader;

	reader.setSize(gzCastToUInt32(len));

	reader.read(adapter);

	data=reader;

	return TRUE;
}


template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzDynamicArray<gzUByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len;

	if (!adapter->hasData(1))
		return FALSE;

	len.read(adapter);

	if (!adapter->hasData(gzCastToUInt32(len)))
		return FALSE;

	data.setSize(gzCastToUInt32(len));

	adapter->read(data.getAddress(), gzCastToUInt32(len));

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzDynamicArray<gzUInt32> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzUInt32> reader(TRUE,useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzDynamicArray<gzInt32> &data, const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzInt32> reader(TRUE, useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzDynamicArray<gzFloat> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzFloat> reader(TRUE,useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzDynamicArray<gzDouble> &data,const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzDouble> reader(TRUE,useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzDynamicArray<gzVec3> &data, const gzBool useBigEndian)
{
	gzSerializeBinaryDynamicArray<gzVec3> reader(TRUE, useBigEndian);

	reader.setArray(data);

	reader.read(adapter);

	return TRUE;
}
template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzDynamicArray<gzQWA_UByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len;
	
	if (!adapter->hasData(1))
		return FALSE;
	
	len.read(adapter);
	
	if (!adapter->hasData(gzCastToUInt32(len)))
		return FALSE;
	
	data.setSize(gzCastToUInt32(len));
	
	adapter->read((gzUByte *)data.getAddress(), gzCastToUInt32(len));
	
	return TRUE;
}

template <class T> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzLateBindData<T> &data,const gzBool useBigEndian=TRUE)
{
	gzUByte sw(FALSE);

	readAdapter(adapter,sw);

	if(sw)
		readAdapter(adapter,data.get(),useBigEndian);
	else
		data.unBind();

	return TRUE;
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzRGBA &data,const gzBool useBigEndian)
{
	if (!adapter->hasData(4*sizeof(gzFloat)))
		return FALSE;

	gzSerializeBinary<gzFloat> reader(useBigEndian);

	reader.read(adapter);
	data.setRed(reader);

	reader.read(adapter);
	data.setGreen(reader);

	reader.read(adapter);
	data.setBlue(reader);

	reader.read(adapter);
	data.setAlpha(reader);

	return TRUE;
}

// Size --------------------------------------------------------------------

template <class T> inline gzUInt32 getDataSize( gzSerializeAdapter * /*adapter*/ , const T &data,const gzBool /*useBigEndian*/=TRUE)
{
	return sizeof(data);
}

template <class T> inline gzUInt32 getDataSize(gzSerializeAdapter* /*adapter*/, const gzTriState<T> &data, const gzBool /*useBigEndian*/ = TRUE)
{
	if (data.isValid())
		return sizeof(T) + 1;
	else
		return 1;
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter * /*adapter*/ , const gzGUID & /*data*/,const gzBool /*useBigEndian*/)
{
	return sizeof(gzGUID);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter * /*adapter*/ , const gzString &data,const gzBool /*useBigEndian*/)
{
	return data.length()+1;
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter * /*adapter*/ , const gzMatrix3 & /*data*/ ,const gzBool /*useBigEndian*/)
{
	return sizeof(gzFloat)*9;
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter * /*adapter*/ , const gzMatrix4 & /*data*/,const gzBool /*useBigEndian*/)
{
	return sizeof(gzFloat)<<4UL;
}

template <class T> inline gzUInt32 getDataSize(gzSerializeAdapter *adapter, const gzList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzSerializeList<T> writer;

	writer=data;

	return writer.getDataSize(adapter);
}

template <class T> inline gzUInt32 getDataSize(gzSerializeAdapter *adapter, const gzDList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzSerializeDList<T> writer;

	writer=data;

	return writer.getDataSize(adapter);
}

template <class T> inline gzUInt32 getDataSize(gzSerializeAdapter *adapter, const gzRefList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzSerializeRefList<T> writer;

	writer=data;

	return writer.getDataSize(adapter);
}

template <class T> inline gzUInt32 getDataSize(gzSerializeAdapter *adapter, const gzRefDList<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzSerializeRefDList<T> writer;

	writer=data;

	return writer.getDataSize(adapter);
}


template <class T> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzVarUInt64 len(data.getSize());
	gzSerializeArray<T>	writer;
	writer=data;
	return writer.getDataSize(adapter)+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize(gzSerializeAdapter *adapter, const gzArray<gzString> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	gzUInt32 size=len.getDataSize(adapter);

	for(gzUInt32 i=0;i<data.getSize();i++)
	{
		size+=(data.get(i).length()+1);
	}

	return size;
}

template <> inline gzUInt32 getDataSize(gzSerializeAdapter *adapter, const gzArray<gzGUID> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len(data.getSize());

	gzUInt32 size=len.getDataSize(adapter);

	size+=(data.getSize()*sizeof(gzGUID));

	return size;
}


template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzArray<gzUByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len=data.getSize();
	return data.getSize()+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzArray<gzQWA_UByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len=data.getSize();
	return data.getSize()+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzArray<gzUInt32> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len=data.getSize();
	return data.getSize()*sizeof(gzUInt32)+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize(gzSerializeAdapter *adapter, const gzArray<gzInt32> &data, const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len = data.getSize();
	return data.getSize()*sizeof(gzInt32) + len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize(gzSerializeAdapter *adapter, const gzArray<gzFloatXY> &data, const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len = data.getSize();
	return data.getSize()*sizeof(gzFloatXY) + len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize(gzSerializeAdapter* adapter, const gzArray<gzFloatXYZ>& data, const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len = data.getSize();
	return data.getSize() * sizeof(gzFloatXYZ) + len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzArray<gzFloat> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len=data.getSize();
	return data.getSize()*sizeof(gzFloat)+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize(gzSerializeAdapter* adapter, const gzArray<gzVec2>& data, const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len = data.getSize();
	return data.getSize() * sizeof(gzVec2) + len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize(gzSerializeAdapter* adapter, const gzArray<gzVec3>& data, const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len = data.getSize();
	return data.getSize() * sizeof(gzVec3) + len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize(gzSerializeAdapter* adapter, const gzArray<gzVec4>& data, const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len = data.getSize();
	return data.getSize() * sizeof(gzVec4) + len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter * /*adapter*/ , const gzArray2D<gzFloat> &data,const gzBool /*useBigEndian*/)
{
	return data.gzArray<gzFloat>::getSize()*sizeof(gzFloat)+2*sizeof(gzUInt32);
}



template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzArray<gzMatrix3> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len=data.getSize();
	return data.getSize()*(sizeof(gzFloat)*9)+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzArray<gzMatrix4> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len=data.getSize();
	return data.getSize()*(sizeof(gzFloat)<<4UL)+len.getDataSize(adapter);
}

template <class T> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzSerializeArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	return ((gzSerializeArray<T> &)data).getDataSize(adapter);
}

template <class T> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzDynamicArray<T> &data,const gzBool /*useBigEndian*/=TRUE)
{
	gzVarUInt64 len=data.getSize();
	gzSerializeDynamicArray<T>	writer;
	writer=data;
	return writer.getDataSize(adapter)+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzDynamicArray<gzUByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len=data.getSize();
	return data.getSize()+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzDynamicArray<gzQWA_UByte> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len=data.getSize();
	return data.getSize()+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzDynamicArray<gzUInt32> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len=data.getSize();
	return data.getSize()*sizeof(gzUInt32)+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzDynamicArray<gzFloat> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len=data.getSize();
	return data.getSize()*sizeof(gzFloat)+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzDynamicArray<gzDouble> &data,const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len=data.getSize();
	return data.getSize()*sizeof(gzDouble)+len.getDataSize(adapter);
}

template <> inline gzUInt32 getDataSize(gzSerializeAdapter *adapter, const gzDynamicArray<gzVec3> &data, const gzBool /*useBigEndian*/)
{
	gzVarUInt64 len = data.getSize();
	return data.getSize() * sizeof(gzVec3) + len.getDataSize(adapter);
}

template <class T> inline gzUInt32 getDataSize(gzSerializeAdapter *adapter, const gzLateBindData<T> &data,const gzBool useBigEndian=TRUE)
{
	if(data.isBound())
	{
		return 1+getDataSize(adapter,data.read(),useBigEndian);
	}
	else
		return 1;
}

template <class T> inline gzUInt32 getDataSize(gzSerializeAdapter *adapter, const gzRGBA &data,const gzBool useBigEndian=TRUE)
{
	return 4*sizeof(gzFloat);
}


// ---------------------- fully generic ---------------------------------

template <class T1,class T2> inline gzVoid _writeAdapter(gzSerializeAdapter *adapter, const T1 &data)
{
	T2 writer;

	writer=data;

	writer.write(adapter);
}

template <class T1,class T2> inline gzVoid _pushBackAdapter(gzSerializeAdapter *adapter, const T1 &data)
{
	T2 writer;

	writer=data;

	writer.pushBack(adapter);
}

template <class T1,class T2> inline gzBool _readAdapter(gzSerializeAdapter *adapter, T1 &data)
{
	T2 reader;

	if (!adapter->hasData(1))
		return FALSE;

	reader.read(adapter);

	data=reader;

	return TRUE;
}

template <class T1,class T2> inline gzUInt32 _getDataSize(  gzSerializeAdapter *adapter , const T1 &data)
{
	T2 writer;

	writer=data;

	return writer.getDataSize(adapter);
}

// ---- String based features ----------------------------------------------------------------------

class gzWriteAdapterStringUtils
{
public:

	GZ_BASE_EXPORT static gzVoid writeAdapterString(gzSerializeAdapter *adapter,const char *format,ARG_DECL_LIST);

	GZ_BASE_EXPORT static gzVoid writeAdapterString(gzSerializeAdapter *adapter,const gzWideChar *format,ARG_DECL_LIST);

	GZ_BASE_EXPORT static gzVoid writeAdapterString(gzSerializeAdapter *adapter,const gzBool useBigEndian,const gzWideChar *format,ARG_DECL_LIST);
};

#define writeAdapterString gzWriteAdapterStringUtils::writeAdapterString

GZ_BASE_EXPORT gzBool readLine(gzString &result,gzSerializeAdapter *adapter=gzSerializeAdapter::getURLAdapter("con:"),gzFloat timeOut=10);
GZ_BASE_EXPORT gzBool writeLine(const gzString& output, gzSerializeAdapter* adapter = gzSerializeAdapter::getURLAdapter("con:"));

GZ_BASE_EXPORT gzBool copyAdapters(gzSerializeAdapter *to, gzSerializeAdapter *from, gzString *errorString = NULL);
GZ_BASE_EXPORT gzBool copyAdapters(const gzString &toURL, const gzString &fromURL, gzString *errorString = NULL);
GZ_BASE_EXPORT gzBool copyAdapters(const gzString &toURL , const gzString &fromURL, gzString *errorString , gzSerializeAdapterFlags output_flags, gzSerializeAdapterFlags input_flags);

GZ_BASE_EXPORT gzBool gzURLExist(const gzString &url);

//******************************************************************************
// Class	: gzCacheData
//									
// Purpose  : Class to maintain recycled dynamic array data
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	051124	Created 
//									
//******************************************************************************
class gzCacheData : public gzRecycleData<gzDynamicArray<gzUByte> > , public gzReference
{
public:

	GZ_BASE_EXPORT	gzCacheData(){};

	GZ_BASE_EXPORT	virtual ~gzCacheData(){};

	GZ_BASE_EXPORT	virtual gzVoid onNewItem(gzDynamicArray<gzUByte> & data) const
	{
		data.setChunkSize(1000);
	}

	GZ_BASE_EXPORT	virtual gzVoid onInitItem(gzDynamicArray<gzUByte> & data) const
	{
		data.setSize(0);
	}

	gzRefPointer<gzRefData<gzString> > listItem;
};


//******************************************************************************
// Class	: gzSerializeAdapterCache
//									
// Purpose  : Class for Serialize data from a cached in memory area
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	051124	Created 
//									
//******************************************************************************
class  gzSerializeAdapterCache : public gzSerializeAdapterMemory
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzSerializeAdapterCache(const gzString &cache_url,gzUInt32 offset,gzUInt32 len,gzBool readLenFromData=FALSE,gzSerializeAdapterFlags flags=GZ_SERIALIZE_ADAPTER_FLAGS_DEFAULT, const gzString &password=GZ_EMPTY_STRING);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterCache();

	GZ_BASE_EXPORT static gzVoid setMaxSizeOfCachedData(gzUInt32 bytes);

	GZ_BASE_EXPORT static gzVoid resetCaches();

	GZ_BASE_EXPORT static gzBool parseCacheURL(const gzString &url,gzUInt32 &offset,gzInt32 &length,gzString &cacheURL);

private:

	gzRefPointer<gzCacheData>					m_cache;

	static gzRefDict<gzString,gzCacheData>		s_cacheItems;
	static gzMutex								s_cacheLocker;
	static gzRefList<gzRefData<gzString> >		s_cacheList;
	static gzUInt32								s_maxBytes;
	static gzUInt32								s_currentBytes;
};

// Big Endian versions

#define GZ_DECLARE_SERIALIZE_15(type,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);writeAdapter(adapter,x4);writeAdapter(adapter,x5);writeAdapter(adapter,x6);writeAdapter(adapter,x7);writeAdapter(adapter,x8);writeAdapter(adapter,x9);writeAdapter(adapter,x10);writeAdapter(adapter,x11);writeAdapter(adapter,x12);writeAdapter(adapter,x13);writeAdapter(adapter,x14);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);readAdapter(adapter,x4);readAdapter(adapter,x5);readAdapter(adapter,x6);readAdapter(adapter,x7);readAdapter(adapter,x8);readAdapter(adapter,x9);readAdapter(adapter,x10);readAdapter(adapter,x11);readAdapter(adapter,x12);readAdapter(adapter,x13);readAdapter(adapter,x14);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x14);pushBackAdapter(adapter,x13);pushBackAdapter(adapter,x12);pushBackAdapter(adapter,x11);pushBackAdapter(adapter,x10);pushBackAdapter(adapter,x9);pushBackAdapter(adapter,x8);pushBackAdapter(adapter,x7);pushBackAdapter(adapter,x6);pushBackAdapter(adapter,x5);pushBackAdapter(adapter,x4);pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);size+=::getDataSize(adapter,x4);size+=::getDataSize(adapter,x5);size+=::getDataSize(adapter,x6);size+=::getDataSize(adapter,x7);size+=::getDataSize(adapter,x8);size+=::getDataSize(adapter,x9);size+=::getDataSize(adapter,x10);size+=::getDataSize(adapter,x11);size+=::getDataSize(adapter,x12);size+=::getDataSize(adapter,x13);size+=::getDataSize(adapter,x14);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_14(type,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);writeAdapter(adapter,x4);writeAdapter(adapter,x5);writeAdapter(adapter,x6);writeAdapter(adapter,x7);writeAdapter(adapter,x8);writeAdapter(adapter,x9);writeAdapter(adapter,x10);writeAdapter(adapter,x11);writeAdapter(adapter,x12);writeAdapter(adapter,x13);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);readAdapter(adapter,x4);readAdapter(adapter,x5);readAdapter(adapter,x6);readAdapter(adapter,x7);readAdapter(adapter,x8);readAdapter(adapter,x9);readAdapter(adapter,x10);readAdapter(adapter,x11);readAdapter(adapter,x12);readAdapter(adapter,x13);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x13);pushBackAdapter(adapter,x12);pushBackAdapter(adapter,x11);pushBackAdapter(adapter,x10);pushBackAdapter(adapter,x9);pushBackAdapter(adapter,x8);pushBackAdapter(adapter,x7);pushBackAdapter(adapter,x6);pushBackAdapter(adapter,x5);pushBackAdapter(adapter,x4);pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);size+=::getDataSize(adapter,x4);size+=::getDataSize(adapter,x5);size+=::getDataSize(adapter,x6);size+=::getDataSize(adapter,x7);size+=::getDataSize(adapter,x8);size+=::getDataSize(adapter,x9);size+=::getDataSize(adapter,x10);size+=::getDataSize(adapter,x11);size+=::getDataSize(adapter,x12);size+=::getDataSize(adapter,x13);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_13(type,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);writeAdapter(adapter,x4);writeAdapter(adapter,x5);writeAdapter(adapter,x6);writeAdapter(adapter,x7);writeAdapter(adapter,x8);writeAdapter(adapter,x9);writeAdapter(adapter,x10);writeAdapter(adapter,x11);writeAdapter(adapter,x12);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);readAdapter(adapter,x4);readAdapter(adapter,x5);readAdapter(adapter,x6);readAdapter(adapter,x7);readAdapter(adapter,x8);readAdapter(adapter,x9);readAdapter(adapter,x10);readAdapter(adapter,x11);readAdapter(adapter,x12);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x12);pushBackAdapter(adapter,x11);pushBackAdapter(adapter,x10);pushBackAdapter(adapter,x9);pushBackAdapter(adapter,x8);pushBackAdapter(adapter,x7);pushBackAdapter(adapter,x6);pushBackAdapter(adapter,x5);pushBackAdapter(adapter,x4);pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);size+=::getDataSize(adapter,x4);size+=::getDataSize(adapter,x5);size+=::getDataSize(adapter,x6);size+=::getDataSize(adapter,x7);size+=::getDataSize(adapter,x8);size+=::getDataSize(adapter,x9);size+=::getDataSize(adapter,x10);size+=::getDataSize(adapter,x11);size+=::getDataSize(adapter,x12);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_12(type,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);writeAdapter(adapter,x4);writeAdapter(adapter,x5);writeAdapter(adapter,x6);writeAdapter(adapter,x7);writeAdapter(adapter,x8);writeAdapter(adapter,x9);writeAdapter(adapter,x10);writeAdapter(adapter,x11);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);readAdapter(adapter,x4);readAdapter(adapter,x5);readAdapter(adapter,x6);readAdapter(adapter,x7);readAdapter(adapter,x8);readAdapter(adapter,x9);readAdapter(adapter,x10);readAdapter(adapter,x11);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x11);pushBackAdapter(adapter,x10);pushBackAdapter(adapter,x9);pushBackAdapter(adapter,x8);pushBackAdapter(adapter,x7);pushBackAdapter(adapter,x6);pushBackAdapter(adapter,x5);pushBackAdapter(adapter,x4);pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);size+=::getDataSize(adapter,x4);size+=::getDataSize(adapter,x5);size+=::getDataSize(adapter,x6);size+=::getDataSize(adapter,x7);size+=::getDataSize(adapter,x8);size+=::getDataSize(adapter,x9);size+=::getDataSize(adapter,x10);size+=::getDataSize(adapter,x11);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_11(type,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);writeAdapter(adapter,x4);writeAdapter(adapter,x5);writeAdapter(adapter,x6);writeAdapter(adapter,x7);writeAdapter(adapter,x8);writeAdapter(adapter,x9);writeAdapter(adapter,x10);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);readAdapter(adapter,x4);readAdapter(adapter,x5);readAdapter(adapter,x6);readAdapter(adapter,x7);readAdapter(adapter,x8);readAdapter(adapter,x9);readAdapter(adapter,x10);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x10);pushBackAdapter(adapter,x9);pushBackAdapter(adapter,x8);pushBackAdapter(adapter,x7);pushBackAdapter(adapter,x6);pushBackAdapter(adapter,x5);pushBackAdapter(adapter,x4);pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);size+=::getDataSize(adapter,x4);size+=::getDataSize(adapter,x5);size+=::getDataSize(adapter,x6);size+=::getDataSize(adapter,x7);size+=::getDataSize(adapter,x8);size+=::getDataSize(adapter,x9);size+=::getDataSize(adapter,x10);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_10(type,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);writeAdapter(adapter,x4);writeAdapter(adapter,x5);writeAdapter(adapter,x6);writeAdapter(adapter,x7);writeAdapter(adapter,x8);writeAdapter(adapter,x9);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);readAdapter(adapter,x4);readAdapter(adapter,x5);readAdapter(adapter,x6);readAdapter(adapter,x7);readAdapter(adapter,x8);readAdapter(adapter,x9);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x9);pushBackAdapter(adapter,x8);pushBackAdapter(adapter,x7);pushBackAdapter(adapter,x6);pushBackAdapter(adapter,x5);pushBackAdapter(adapter,x4);pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);size+=::getDataSize(adapter,x4);size+=::getDataSize(adapter,x5);size+=::getDataSize(adapter,x6);size+=::getDataSize(adapter,x7);size+=::getDataSize(adapter,x8);size+=::getDataSize(adapter,x9);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_9(type,x0,x1,x2,x3,x4,x5,x6,x7,x8) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);writeAdapter(adapter,x4);writeAdapter(adapter,x5);writeAdapter(adapter,x6);writeAdapter(adapter,x7);writeAdapter(adapter,x8);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);readAdapter(adapter,x4);readAdapter(adapter,x5);readAdapter(adapter,x6);readAdapter(adapter,x7);readAdapter(adapter,x8);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x8);pushBackAdapter(adapter,x7);pushBackAdapter(adapter,x6);pushBackAdapter(adapter,x5);pushBackAdapter(adapter,x4);pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);size+=::getDataSize(adapter,x4);size+=::getDataSize(adapter,x5);size+=::getDataSize(adapter,x6);size+=::getDataSize(adapter,x7);size+=::getDataSize(adapter,x8);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_8(type,x0,x1,x2,x3,x4,x5,x6,x7) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);writeAdapter(adapter,x4);writeAdapter(adapter,x5);writeAdapter(adapter,x6);writeAdapter(adapter,x7);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);readAdapter(adapter,x4);readAdapter(adapter,x5);readAdapter(adapter,x6);readAdapter(adapter,x7);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x7);pushBackAdapter(adapter,x6);pushBackAdapter(adapter,x5);pushBackAdapter(adapter,x4);pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);size+=::getDataSize(adapter,x4);size+=::getDataSize(adapter,x5);size+=::getDataSize(adapter,x6);size+=::getDataSize(adapter,x7);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_7(type,x0,x1,x2,x3,x4,x5,x6) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);writeAdapter(adapter,x4);writeAdapter(adapter,x5);writeAdapter(adapter,x6);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);readAdapter(adapter,x4);readAdapter(adapter,x5);readAdapter(adapter,x6);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x6);pushBackAdapter(adapter,x5);pushBackAdapter(adapter,x4);pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);size+=::getDataSize(adapter,x4);size+=::getDataSize(adapter,x5);size+=::getDataSize(adapter,x6);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_6(type,x0,x1,x2,x3,x4,x5) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);writeAdapter(adapter,x4);writeAdapter(adapter,x5);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);readAdapter(adapter,x4);readAdapter(adapter,x5);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x5);pushBackAdapter(adapter,x4);pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);size+=::getDataSize(adapter,x4);size+=::getDataSize(adapter,x5);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_5(type,x0,x1,x2,x3,x4) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);writeAdapter(adapter,x4);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);readAdapter(adapter,x4);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x4);pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);size+=::getDataSize(adapter,x4);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_4(type,x0,x1,x2,x3) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);writeAdapter(adapter,x3);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);readAdapter(adapter,x3);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x3);pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);size+=::getDataSize(adapter,x3);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_3(type,x0,x1,x2) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);writeAdapter(adapter,x2);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);readAdapter(adapter,x2);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x2);pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);size+=::getDataSize(adapter,x2);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_2(type,x0,x1) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);writeAdapter(adapter,x1);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);readAdapter(adapter,x1);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x1);pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);size+=::getDataSize(adapter,x1);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_1(type,x0) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x0);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0);return size;}static gzString getDataTag() { return type; }

// Little endian versions

#define GZ_DECLARE_SERIALIZE_10_LE(type,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0,FALSE);writeAdapter(adapter,x1,FALSE);writeAdapter(adapter,x2,FALSE);writeAdapter(adapter,x3,FALSE);writeAdapter(adapter,x4,FALSE);writeAdapter(adapter,x5,FALSE);writeAdapter(adapter,x6,FALSE);writeAdapter(adapter,x7,FALSE);writeAdapter(adapter,x8,FALSE);writeAdapter(adapter,x9,FALSE);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0,FALSE);readAdapter(adapter,x1,FALSE);readAdapter(adapter,x2,FALSE);readAdapter(adapter,x3,FALSE);readAdapter(adapter,x4,FALSE);readAdapter(adapter,x5,FALSE);readAdapter(adapter,x6,FALSE);readAdapter(adapter,x7,FALSE);readAdapter(adapter,x8,FALSE);readAdapter(adapter,x9,FALSE);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x9,FALSE);pushBackAdapter(adapter,x8,FALSE);pushBackAdapter(adapter,x7,FALSE);pushBackAdapter(adapter,x6,FALSE);pushBackAdapter(adapter,x5,FALSE);pushBackAdapter(adapter,x4,FALSE);pushBackAdapter(adapter,x3,FALSE);pushBackAdapter(adapter,x2,FALSE);pushBackAdapter(adapter,x1,FALSE);pushBackAdapter(adapter,x0,FALSE);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0,FALSE);size+=::getDataSize(adapter,x1,FALSE);size+=::getDataSize(adapter,x2,FALSE);size+=::getDataSize(adapter,x3,FALSE);size+=::getDataSize(adapter,x4,FALSE);size+=::getDataSize(adapter,x5,FALSE);size+=::getDataSize(adapter,x6,FALSE);size+=::getDataSize(adapter,x7,FALSE);size+=::getDataSize(adapter,x8,FALSE);size+=::getDataSize(adapter,x9,FALSE);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_9_LE(type,x0,x1,x2,x3,x4,x5,x6,x7,x8) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0,FALSE);writeAdapter(adapter,x1,FALSE);writeAdapter(adapter,x2,FALSE);writeAdapter(adapter,x3,FALSE);writeAdapter(adapter,x4,FALSE);writeAdapter(adapter,x5,FALSE);writeAdapter(adapter,x6,FALSE);writeAdapter(adapter,x7,FALSE);writeAdapter(adapter,x8,FALSE);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0,FALSE);readAdapter(adapter,x1,FALSE);readAdapter(adapter,x2,FALSE);readAdapter(adapter,x3,FALSE);readAdapter(adapter,x4,FALSE);readAdapter(adapter,x5,FALSE);readAdapter(adapter,x6,FALSE);readAdapter(adapter,x7,FALSE);readAdapter(adapter,x8,FALSE);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x8,FALSE);pushBackAdapter(adapter,x7,FALSE);pushBackAdapter(adapter,x6,FALSE);pushBackAdapter(adapter,x5,FALSE);pushBackAdapter(adapter,x4,FALSE);pushBackAdapter(adapter,x3,FALSE);pushBackAdapter(adapter,x2,FALSE);pushBackAdapter(adapter,x1,FALSE);pushBackAdapter(adapter,x0,FALSE);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0,FALSE);size+=::getDataSize(adapter,x1,FALSE);size+=::getDataSize(adapter,x2,FALSE);size+=::getDataSize(adapter,x3,FALSE);size+=::getDataSize(adapter,x4,FALSE);size+=::getDataSize(adapter,x5,FALSE);size+=::getDataSize(adapter,x6,FALSE);size+=::getDataSize(adapter,x7,FALSE);size+=::getDataSize(adapter,x8,FALSE);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_8_LE(type,x0,x1,x2,x3,x4,x5,x6,x7) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0,FALSE);writeAdapter(adapter,x1,FALSE);writeAdapter(adapter,x2,FALSE);writeAdapter(adapter,x3,FALSE);writeAdapter(adapter,x4,FALSE);writeAdapter(adapter,x5,FALSE);writeAdapter(adapter,x6,FALSE);writeAdapter(adapter,x7,FALSE);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0,FALSE);readAdapter(adapter,x1,FALSE);readAdapter(adapter,x2,FALSE);readAdapter(adapter,x3,FALSE);readAdapter(adapter,x4,FALSE);readAdapter(adapter,x5,FALSE);readAdapter(adapter,x6,FALSE);readAdapter(adapter,x7,FALSE);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x7,FALSE);pushBackAdapter(adapter,x6,FALSE);pushBackAdapter(adapter,x5,FALSE);pushBackAdapter(adapter,x4,FALSE);pushBackAdapter(adapter,x3,FALSE);pushBackAdapter(adapter,x2,FALSE);pushBackAdapter(adapter,x1,FALSE);pushBackAdapter(adapter,x0,FALSE);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0,FALSE);size+=::getDataSize(adapter,x1,FALSE);size+=::getDataSize(adapter,x2,FALSE);size+=::getDataSize(adapter,x3,FALSE);size+=::getDataSize(adapter,x4,FALSE);size+=::getDataSize(adapter,x5,FALSE);size+=::getDataSize(adapter,x6,FALSE);size+=::getDataSize(adapter,x7,FALSE);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_7_LE(type,x0,x1,x2,x3,x4,x5,x6) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0,FALSE);writeAdapter(adapter,x1,FALSE);writeAdapter(adapter,x2,FALSE);writeAdapter(adapter,x3,FALSE);writeAdapter(adapter,x4,FALSE);writeAdapter(adapter,x5,FALSE);writeAdapter(adapter,x6,FALSE);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0,FALSE);readAdapter(adapter,x1,FALSE);readAdapter(adapter,x2,FALSE);readAdapter(adapter,x3,FALSE);readAdapter(adapter,x4,FALSE);readAdapter(adapter,x5,FALSE);readAdapter(adapter,x6,FALSE);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x6,FALSE);pushBackAdapter(adapter,x5,FALSE);pushBackAdapter(adapter,x4,FALSE);pushBackAdapter(adapter,x3,FALSE);pushBackAdapter(adapter,x2,FALSE);pushBackAdapter(adapter,x1,FALSE);pushBackAdapter(adapter,x0,FALSE);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0,FALSE);size+=::getDataSize(adapter,x1,FALSE);size+=::getDataSize(adapter,x2,FALSE);size+=::getDataSize(adapter,x3,FALSE);size+=::getDataSize(adapter,x4,FALSE);size+=::getDataSize(adapter,x5,FALSE);size+=::getDataSize(adapter,x6,FALSE);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_6_LE(type,x0,x1,x2,x3,x4,x5) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0,FALSE);writeAdapter(adapter,x1,FALSE);writeAdapter(adapter,x2,FALSE);writeAdapter(adapter,x3,FALSE);writeAdapter(adapter,x4,FALSE);writeAdapter(adapter,x5,FALSE);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0,FALSE);readAdapter(adapter,x1,FALSE);readAdapter(adapter,x2,FALSE);readAdapter(adapter,x3,FALSE);readAdapter(adapter,x4,FALSE);readAdapter(adapter,x5,FALSE);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x5,FALSE);pushBackAdapter(adapter,x4,FALSE);pushBackAdapter(adapter,x3,FALSE);pushBackAdapter(adapter,x2,FALSE);pushBackAdapter(adapter,x1,FALSE);pushBackAdapter(adapter,x0,FALSE);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0,FALSE);size+=::getDataSize(adapter,x1,FALSE);size+=::getDataSize(adapter,x2,FALSE);size+=::getDataSize(adapter,x3,FALSE);size+=::getDataSize(adapter,x4,FALSE);size+=::getDataSize(adapter,x5,FALSE);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_5_LE(type,x0,x1,x2,x3,x4) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0,FALSE);writeAdapter(adapter,x1,FALSE);writeAdapter(adapter,x2,FALSE);writeAdapter(adapter,x3,FALSE);writeAdapter(adapter,x4,FALSE);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0,FALSE);readAdapter(adapter,x1,FALSE);readAdapter(adapter,x2,FALSE);readAdapter(adapter,x3,FALSE);readAdapter(adapter,x4,FALSE);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x4,FALSE);pushBackAdapter(adapter,x3,FALSE);pushBackAdapter(adapter,x2,FALSE);pushBackAdapter(adapter,x1,FALSE);pushBackAdapter(adapter,x0,FALSE);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0,FALSE);size+=::getDataSize(adapter,x1,FALSE);size+=::getDataSize(adapter,x2,FALSE);size+=::getDataSize(adapter,x3,FALSE);size+=::getDataSize(adapter,x4,FALSE);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_4_LE(type,x0,x1,x2,x3) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0,FALSE);writeAdapter(adapter,x1,FALSE);writeAdapter(adapter,x2,FALSE);writeAdapter(adapter,x3,FALSE);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0,FALSE);readAdapter(adapter,x1,FALSE);readAdapter(adapter,x2,FALSE);readAdapter(adapter,x3,FALSE);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x3,FALSE);pushBackAdapter(adapter,x2,FALSE);pushBackAdapter(adapter,x1,FALSE);pushBackAdapter(adapter,x0,FALSE);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0,FALSE);size+=::getDataSize(adapter,x1,FALSE);size+=::getDataSize(adapter,x2,FALSE);size+=::getDataSize(adapter,x3,FALSE);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_3_LE(type,x0,x1,x2) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0,FALSE);writeAdapter(adapter,x1,FALSE);writeAdapter(adapter,x2,FALSE);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0,FALSE);readAdapter(adapter,x1,FALSE);readAdapter(adapter,x2,FALSE);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x2,FALSE);pushBackAdapter(adapter,x1,FALSE);pushBackAdapter(adapter,x0,FALSE);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0,FALSE);size+=::getDataSize(adapter,x1,FALSE);size+=::getDataSize(adapter,x2,FALSE);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_2_LE(type,x0,x1) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0,FALSE);writeAdapter(adapter,x1,FALSE);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0,FALSE);readAdapter(adapter,x1,FALSE);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x1,FALSE);pushBackAdapter(adapter,x0,FALSE);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0,FALSE);size+=::getDataSize(adapter,x1,FALSE);return size;}static gzString getDataTag() { return type; }
#define GZ_DECLARE_SERIALIZE_1_LE(type,x0) gzVoid write(gzSerializeAdapter *adapter) { writeAdapter(adapter,x0,FALSE);}gzVoid read(gzSerializeAdapter *adapter){readAdapter(adapter,x0,FALSE);}gzVoid pushBack(gzSerializeAdapter *adapter){pushBackAdapter(adapter,x0,FALSE);}gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const{gzUInt32 size(0);size+=::getDataSize(adapter,x0,FALSE);return size;}static gzString getDataTag() { return type; }

// ----------------------------- Asset Url Registration -----------------------------------------

GZ_BASE_EXPORT gzBool gzSetAssetManagerHandle(gzVoid *handle1,gzVoid *handle2=nullptr);
GZ_BASE_EXPORT gzVoid gzInitializePlatformLogging();
GZ_BASE_EXPORT gzVoid gzUnInitializePlatformLogging();


// --------------------------- Encoded double -------------------------------

class gzEncodedDouble
{
public:

	gzEncodedDouble()
	{
		m_data = 0;
	}

	gzEncodedDouble(const gzDouble& value)
	{
		m_data = value;
	}

	operator gzDouble () const { return m_data; }

	gzDouble& operator = (const gzDouble& data)
	{
		m_data = data;
		return m_data;
	}

private:

	gzDouble	m_data;

};

enum gzDoubleEncoding
{
	GZ_DOUBLE_ENCODE_NO_ENCODING = 0,
	GZ_DOUBLE_ENCODE_INTEGER = 1 << 4,
	GZ_DOUBLE_ENCODE_DELTA = 1 << 5,
	GZ_DOUBLE_ENCODE_ZERO = 1 << 6,
};

GZ_USE_BIT_LOGIC(gzDoubleEncoding);

GZ_BASE_EXPORT gzVoid	gzEncodeDouble(const gzDouble& value, gzDoubleEncoding& encode, gzUByte& size, gzBool useDelta=FALSE, const gzDouble& base = 0.0);
GZ_BASE_EXPORT gzDouble gzReadEncodedDouble(gzSerializeAdapter* adapter, gzBool bigEndian=TRUE,const gzDouble& base=0.0);
GZ_BASE_EXPORT gzVoid	gzWriteEncodedDouble(gzSerializeAdapter* adapter, const gzDouble& value, gzDoubleEncoding encode, gzUByte size,gzBool bigEndian=TRUE, const gzDouble& base=0.0 );
GZ_BASE_EXPORT gzVoid	gzPushBackEncodedDouble(gzSerializeAdapter* adapter, const gzDouble& value, gzDoubleEncoding encode, gzUByte size, gzBool bigEndian = TRUE);

class gzSerializeEncodedDouble : public gzSerializeData
{
public:

	GZ_BASE_EXPORT	explicit gzSerializeEncodedDouble(const gzBool useBigEndian = TRUE);

	GZ_BASE_EXPORT	gzSerializeEncodedDouble(const gzDouble& val, const gzBool useBigEndian);

	GZ_BASE_EXPORT	gzBool operator==(const gzSerializeEncodedDouble& right);
	
	GZ_BASE_EXPORT	gzBool operator!=(const gzSerializeEncodedDouble& right);

	GZ_BASE_EXPORT	virtual gzVoid write(gzSerializeAdapter* adapter) override;

	GZ_BASE_EXPORT	virtual gzVoid read(gzSerializeAdapter* adapter) override;

	GZ_BASE_EXPORT	virtual gzVoid pushBack(gzSerializeAdapter* adapter) override;

	GZ_BASE_EXPORT	virtual gzUInt32	getDataSize(gzSerializeAdapter* /*adapter*/ = NULL) const override;

	GZ_BASE_EXPORT	operator gzEncodedDouble () const;

	GZ_BASE_EXPORT	gzEncodedDouble& operator = (const gzEncodedDouble& data);

	GZ_PROPERTY(gzBool, BigEndian);
	GZ_PROPERTY(gzBool, IsDelta);

private:

	gzEncodedDouble	m_data;
};


template <> inline gzVoid writeAdapter(gzSerializeAdapter* adapter, const gzEncodedDouble& data, const gzBool useBigEndian)
{
	gzSerializeEncodedDouble writer(useBigEndian);

	writer = data;

	writer.write(adapter);
}


template <> inline gzBool readAdapter(gzSerializeAdapter* adapter, gzEncodedDouble& data, const gzBool useBigEndian)
{
	gzSerializeEncodedDouble reader(useBigEndian);

	if (!adapter->hasData(1))
		return FALSE;

	reader.read(adapter);

	data = reader;

	return TRUE;
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter* adapter, const gzEncodedDouble& data, const gzBool useBigEndian)
{
	gzSerializeEncodedDouble writer(useBigEndian);

	writer = data;

	writer.pushBack(adapter);
}

template <> inline gzUInt32 getDataSize(gzSerializeAdapter* adapter, const gzEncodedDouble& data, const gzBool useBigEndian)
{
	gzSerializeEncodedDouble writer(useBigEndian);

	writer = data;

	return writer.getDataSize(adapter);
}

// ------------------ Blocked communication ------------------------

//******************************************************************************
// Class	: gzBlockAdapter
//									
// Purpose  : Auto blocker of reading/writing a stream. 
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	211210	Created							(2.11.61)
//									
//******************************************************************************
class gzBlockAdapter
{
public:

	GZ_BASE_EXPORT gzBlockAdapter(gzSerializeAdapter* adapter) : m_adapter(adapter)
	{
		if (m_adapter)
		{
			m_adapter->ref();
			m_blocked = m_adapter->isBlocking();
			m_adapter->setBlocking(TRUE);
		}
	}

	GZ_BASE_EXPORT virtual ~gzBlockAdapter() 
	{ 
		if (m_adapter)
		{
			m_adapter->setBlocking(m_blocked);
			m_adapter->unrefNoDelete();
		}
	}

	GZ_NO_IMPLICITS(gzBlockAdapter);

private:

	gzBool					m_blocked;
	gzSerializeAdapter*		m_adapter;
};

#define GZ_BLOCKADAPTER	gzBlockAdapter	CONCAT(_guard_,__LINE__)

// ------------------ URL Syncronisation ------------------------

//******************************************************************************
// Class	: gzURLSyncronizer
//									
// Purpose  : Auto sync of source and destination URL 
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	240327	Created							(2.12.140)
//									
//******************************************************************************
class gzURLSyncronizer : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT	gzURLSyncronizer() : m_syncronized(0), m_already_syncronized(0) {}

	GZ_BASE_EXPORT	gzBool syncronize(const gzString& source, const gzString& destination, gzBool verbose = TRUE, gzBool useCRC = FALSE, gzString* errorString = NULL, gzSerializeAdapterError* errorType = NULL);

	GZ_BASE_EXPORT	virtual gzVoid onStatus(const gzUByte& progress, const gzString& item, const gzUInt32& syncronised, const gzUInt32& already_syncronised, const gzFloat& speed, gzBool verbose);

private:

	gzUInt32	m_syncronized;
	gzUInt32	m_already_syncronized;

	gzString					m_currentSource;
	gzDynamicArray<gzString>	m_currentEntries;
};

#endif
