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
// File			: gzNetwork.h
// Module		: gzBase
// Description	: Class definition of Network classes
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.223
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
// AMO	010404	Created file 	
// AMO	240328	Added blocked mode to non blocking send in socket (2.12.140)
//
//******************************************************************************

#ifndef __GZ_NETWORK_H__
#define __GZ_NETWORK_H__

#include "gzBasicTypes.h"
#include "gzMemory.h"
#include "gzDynamic.h"
#include "gzThread.h"
#include "gzNotify.h"


/*!	\file
	\brief Network utilities

*/


#ifdef GZ_WINDOWS
	typedef UINT_PTR	gzSocketHandle;
#else
	typedef gzInt32		gzSocketHandle;
#endif


//! Socket families
enum gzSocketFamily
{
	GZ_SOCKET_FAMILY_INET,	//!< IPv4
	GZ_SOCKET_FAMILY_IRDA,	//!< IrDA
	GZ_SOCKET_FAMILY_INET6,	//!< IPv6

	GZ_SOCKET_FAMILY_UNINITIALIZED	
};


//! Socket types
enum gzSocketType
{
	GZ_SOCKET_TYPE_STREAM,
	GZ_SOCKET_TYPE_DATAGRAM,
	GZ_SOCKET_TYPE_RAW,

	GZ_SOCKET_TYPE_UNINITIALIZED
};

//! Socket protocol
enum gzSocketProtocol
{
	GZ_SOCKET_PROTOCOL_IP,
	GZ_SOCKET_PROTOCOL_ICMP,
	GZ_SOCKET_PROTOCOL_IGMP,
	GZ_SOCKET_PROTOCOL_TCP,
	GZ_SOCKET_PROTOCOL_UDP,

	GZ_SOCKET_PROTOCOL_UNINITIALIZED
};


//! Socket options
enum gzSocketOption
{
	GZ_SOCKET_OPTION_BROADCAST,					//!< Enable broadcast
	GZ_SOCKET_OPTION_DONTROUTE,
	GZ_SOCKET_OPTION_USE_LINGER,				//!< Enable linger with given time value
	GZ_SOCKET_OPTION_DONT_USE_LINGER,			//!< Disable linger (value is ignored)
	GZ_SOCKET_OPTION_KEEPALIVE,
	GZ_SOCKET_OPTION_REUSE_ADDR_PORT,
	GZ_SOCKET_OPTION_MULTICAST_TTL,
	GZ_SOCKET_OPTION_MULTICAST_INTERFACE,
	GZ_SOCKET_OPTION_MULTICAST_LOOPBACK,
	GZ_SOCKET_OPTION_ADD_MULTICAST_MEMBERSHIP,
	GZ_SOCKET_OPTION_DROP_MULTICAST_MEMBERSHIP,
	GZ_SOCKET_OPTION_RECEIVE_BUFFER,			//!< Set receive buffer size
	GZ_SOCKET_OPTION_SEND_BUFFER,				//!< set send buffer size
	GZ_SOCKET_OPTION_RECEIVE_TIMEOUT,			//!< set receive timout values
	GZ_SOCKET_OPTION_IP_TTL,
	GZ_SOCKET_OPTION_TCP_NO_DELAY,				//!< disable nagle algorithm
};


//! Socket error codes
enum gzSocketError
{
	GZ_SOCKET_ERROR_NO_ERROR = 0,
	GZ_SOCKET_ERROR_CHECK_FOR_ERROR,
	GZ_SOCKET_ERROR_UNKNOWN_ERROR,
	GZ_SOCKET_ERROR_PROTOCOL_FAMILY_NOT_SUPPORTED,
	GZ_SOCKET_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED,
	GZ_SOCKET_ERROR_PERMISSION_DENIED,
	GZ_SOCKET_ERROR_PROTOCOL_NOT_SUPPORTED,
	GZ_SOCKET_ERROR_NETWORK_NOT_INITIALISED,
	GZ_SOCKET_ERROR_CONNECTION_CLOSED,
	GZ_SOCKET_ERROR_UNKNOWN_SOCKET_OPTION,
	GZ_SOCKET_ERROR_SOCKET_NOT_CONFIGURED,
	GZ_SOCKET_ERROR_HOST_UNREACHABLE,
	GZ_SOCKET_ERROR_NETWORK_UNREACHABLE,
	GZ_SOCKET_ERROR_OPTION_NOT_SUPPORTED,
	GZ_SOCKET_ERROR_INVALID_DESCRIPTOR,
	GZ_SOCKET_ERROR_INVALID_ARGUMENT,
	GZ_SOCKET_ERROR_ADDRESS_IN_USE,
	GZ_SOCKET_ERROR_ADDRESS_NOT_AVAILABLE,
	GZ_SOCKET_ERROR_IS_CONNECTED,
	GZ_SOCKET_ERROR_NOT_CONNECTED,
	GZ_SOCKET_ERROR_CONNECTION_RESET,
	GZ_SOCKET_ERROR_CONNECTION_ABORTED,
	GZ_SOCKET_ERROR_CONNECTION_REFUSED,
	GZ_SOCKET_ERROR_CONNECTION_TIMEDOUT,
	GZ_SOCKET_ERROR_WOULD_BLOCK,
	GZ_SOCKET_ERROR_MESSAGE_SIZE,
	GZ_SOCKET_ERROR_OPERTATION_ABORTED,
	GZ_SOCKET_ERROR_NO_DEVICE,
	GZ_SOCKET_ERROR_PIPE,
	GZ_SOCKET_ERROR_INTERRUPTED,
	GZ_SOCKET_ERROR_XXX
};


// ------- Notification commands -----------

const gzString GZ_NET_DATA	= "NetData";


//! Host address types
enum gzHostAddressType
{
	GZ_HOST_ADDRESS_TYPE_INVALID,
	GZ_HOST_ADDRESS_TYPE_DOT_4,
};


//! Host IP address
class gzHostAddress 
{
public:

	GZ_BASE_EXPORT gzHostAddress();

	GZ_BASE_EXPORT gzHostAddress(gzUByte a,gzUByte b,gzUByte c,gzUByte d);

	GZ_BASE_EXPORT gzHostAddress(const gzString &name);

	GZ_BASE_EXPORT explicit gzHostAddress(gzUInt32 address);

	GZ_BASE_EXPORT virtual ~gzHostAddress() { m_address.setSize(0); }


	GZ_BASE_EXPORT gzBool operator==(const gzHostAddress &right);
	GZ_BASE_EXPORT gzBool operator!=(const gzHostAddress &right) { return !operator==(right); }


	GZ_BASE_EXPORT gzString				asString() const;

	GZ_BASE_EXPORT gzHostAddressType	getHostAddressType() const;

	GZ_BASE_EXPORT gzInt64				asLongLong() const;

	GZ_BASE_EXPORT gzUInt32				asULong() const;

	GZ_BASE_EXPORT gzBool				isValid() const;

private:

	gzHostAddressType	m_type;
	gzArray<gzUByte>	m_address;
};


//! Host info
class gzHostInfo 
{
public:

	GZ_BASE_EXPORT gzHostInfo() : isValid(FALSE) {};

	gzString				hostName;

	gzArray<gzString>		hostAlias;

	gzArray<gzHostAddress>	hostAddress;

	gzBool					isValid;
};


//! Socket address types
enum gzSocketAddressType
{
	GZ_SOCKET_ADDRESS_TYPE_UNKNOWN,
	GZ_SOCKET_ADDRESS_TYPE_INET,
};


//! Socket address (host address and port)
class gzSocketAddress 
{
public:

	GZ_BASE_EXPORT gzSocketAddress();
	GZ_BASE_EXPORT virtual ~gzSocketAddress() {};

	GZ_BASE_EXPORT gzSocketAddress(gzUByte *sockaddr, gzUInt32 bytes);
	GZ_BASE_EXPORT gzSocketAddress(gzUInt16 portNumber);
	GZ_BASE_EXPORT gzSocketAddress(const gzHostAddress &address, gzUInt16 portNumber);
	GZ_BASE_EXPORT gzSocketAddress(const gzString &name, gzUInt16 portNumber);

	GZ_BASE_EXPORT gzBool operator==(const gzSocketAddress &right);
	GZ_BASE_EXPORT gzSocketAddressType getAddressType();

	GZ_BASE_EXPORT gzUInt32 getLength() const;
	GZ_BASE_EXPORT gzUByte * getData() const;

	GZ_BASE_EXPORT gzBool isNull() const;

	GZ_BASE_EXPORT gzHostAddress	getHostAddress();
	GZ_BASE_EXPORT gzUInt16			getPort();

	GZ_BASE_EXPORT	gzString		asString(const gzString &format="%s:%d");

protected:

	friend class gzSocket;

	gzArray<gzUByte>	m_addressData;
};


//! Network data
class gzNetData : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT)

	gzSocketAddress							sender;
	gzRecycleData<gzDynamicArray<gzUByte> >	data;
};


//******************************************************************************
// Class	: gzSocket
//									
// Purpose  : Binding to tcp/udp ports
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	010409	Created 
//									
//******************************************************************************
//! Socket for network communication
class	gzSocket :	public gzThreadTicker , 
					public gzNotifyManager , 
					public gzTypeInterface
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	//! Constructor
	GZ_BASE_EXPORT	gzSocket();

	//! Destructor
	GZ_BASE_EXPORT	virtual ~gzSocket();


	// --- Setup routines ---

	//! Create socket
	GZ_BASE_EXPORT	gzBool create(gzSocketFamily family , gzSocketType type=GZ_SOCKET_TYPE_STREAM , gzSocketProtocol protocol= GZ_SOCKET_PROTOCOL_IP);
	
	//! Close socket
	GZ_BASE_EXPORT	gzVoid close(gzBool waitForRemoteConnection=TRUE);

	//! Set socket option
	GZ_BASE_EXPORT	gzBool setOption(gzSocketOption option, gzDynamicType value);
 
	//! Get socket option
	GZ_BASE_EXPORT	gzDynamicType getOption(gzSocketOption option);

	//! Bind to your local network adapter
	GZ_BASE_EXPORT	gzBool bind(const gzSocketAddress &address=gzSocketAddress());

	GZ_BASE_EXPORT	gzBool is(gzSocketFamily family, gzSocketType type = GZ_SOCKET_TYPE_STREAM, gzSocketProtocol protocol = GZ_SOCKET_PROTOCOL_IP);

	// --- Connection management ---

	//! Listen for incoming connections
	GZ_BASE_EXPORT	gzBool listen(gzUInt32 maxConnections=0);

	//! Accept incoming connection
	GZ_BASE_EXPORT  gzSocket *accept();
	
	//! Connect to your destination adress
	GZ_BASE_EXPORT	gzBool connect(const gzSocketAddress &address);

	//! Check that a connection is still active
	/*!
		\sa isReadyToReceive, getPendingBytes
	*/
	GZ_BASE_EXPORT gzBool isActive();


	// --- Send and receive data ---

	//! Receive data from a connected or bound socket
	GZ_BASE_EXPORT	gzInt32 receive(gzUByte *buffer,gzUInt32 len);
	GZ_BASE_EXPORT	gzInt32 bufferReceive(gzUByte *buffer,gzUInt32 len);

	//! Receive a datagram and store the source address
	GZ_BASE_EXPORT	gzInt32 receiveFrom(gzSocketAddress & address , gzUByte *buffer,gzUInt32 len);
	GZ_BASE_EXPORT	gzInt32 bufferReceiveFrom(gzSocketAddress & address , gzUByte *buffer,gzUInt32 len);

	GZ_BASE_EXPORT  gzVoid bufferPushBack(gzUByte *buffer,gzUInt32 len);

	//! Send data on a connected socket
	GZ_BASE_EXPORT	gzInt32 send(const gzUByte *buffer,gzUInt32 len,gzBool blocking=TRUE);

	//! Send datagram to a specific destination address
	GZ_BASE_EXPORT	gzInt32 sendTo(const gzSocketAddress & address ,const gzUByte *buffer,gzUInt32 len, gzBool blocking = TRUE);


	//! Wait to be ready for receiving data.
	/*!
		Will return TRUE when:
		\li Data is available for receiving.
		\li listen has been called and a connection is pending (accept will succeed).
		\li The connection has been closed, reset or terminated.

		If the connection has been closed, reset or terminated,
		getPendingBytes will also return 0 (zero).

		\sa receive, listen, accept, isReadyToSend, isActive, getPendingBytes
	*/
	GZ_BASE_EXPORT gzBool isReadyToReceive(gzUInt32 timeout = 0);

	//! Wait to be ready for sending data.
	/*!
		Will return TRUE when:
		\li Data can be sent (space is available in the send buffer).
		\li Connection has succeeded while processing a nonblocking connect call.

		 \sa send, connect, isReadyToReceive
	*/
	GZ_BASE_EXPORT gzBool isReadyToSend(gzUInt32 timeout = 0);


	// --- Error management ---

	//! Get the last socket error
	/*!
		gzSocket stores the error code for the last operation that failed.
		Use this routine to access the error code.
		A successful function call or a call to getSocketError
		does not clear the last error code.
		Use clearSocketError or setSocketError to clear the last error.

		\return The error code for the last operation that failed.
	*/
	GZ_BASE_EXPORT	gzSocketError getSocketError() const;

	//! Check if the socket has an error
	GZ_BASE_EXPORT	gzBool hasSocketError() const;

	//! Set the last socket error. Returns TRUE if it was an error
	GZ_BASE_EXPORT	gzBool setSocketError(gzSocketError error=GZ_SOCKET_ERROR_CHECK_FOR_ERROR,gzBool blocking=FALSE);

	//! Clear the last socket error
	GZ_BASE_EXPORT	gzVoid clearSocketError();

	//! Use exceptions to report errors
	/*!
		Exceptions are not used by default.
	*/
	GZ_BASE_EXPORT	gzVoid useExceptions(gzBool on);


	// --- Utilities ---

	//! Check if the socket is bound to a given specific address
	GZ_BASE_EXPORT	gzBool isBindTo(const gzSocketAddress &address);

	//! Check if the socket is connected to a given specific address
	GZ_BASE_EXPORT	gzBool isConnectedTo(const gzSocketAddress &address);

	//! Get the address this socket is bound to
	GZ_BASE_EXPORT	gzSocketAddress getBindAddress();
	
	//! Get the address this socket is connected to
	GZ_BASE_EXPORT	gzSocketAddress getConnectAddress();


	// --- Ioctl based utilities ---

	//! Number of bytes in the socket receive buffer
	GZ_BASE_EXPORT	gzUInt32 getPendingBytes();
	GZ_BASE_EXPORT	gzUInt32 bufferGetPendingBytes();
	
	//! Set blocking or non-blocking mode
	/*!
		Blocking mode is default
	*/
	GZ_BASE_EXPORT	gzVoid setBlocking(gzBool on = TRUE);

	//! Check blocking or non-blocking mode
	GZ_BASE_EXPORT gzBool isBlocking() const;
	
	//! Get the broadcast address for this socket
	/*!
		Requires that bind has been called
	*/
	GZ_BASE_EXPORT  gzHostAddress	getBroadcastAddress();
	
	//! Get the network mask for this socket
	/*!
		Requires that bind has been called
	*/
	GZ_BASE_EXPORT  gzHostAddress	getNetworkMask();

	//! manual poll of the socket;
	GZ_BASE_EXPORT gzVoid poll();


	// --- Setup utilities ---

	//! Create a multicast socket in a singel call
	/*!	\param	group	Multicast group address
		\param	port	Port number
		\param	\ttl	Multicast TTL */
	GZ_BASE_EXPORT	gzBool enableMulticast(const gzHostAddress& group, gzUInt16 port, gzUInt32 ttl=255);
	
	//! Create a multicast socket in a singel call
	/*!	\param	group	Multicast group address
		\param	port	Port number
		\param	ttl		Multicast TTL
		\param	iface	Interface address to bind to */
	GZ_BASE_EXPORT	gzBool enableMulticast(const gzHostAddress& group, gzUInt16 port, const gzHostAddress& iface, gzUInt32 ttl=255);

	//! Create a broadcast socket in a single call
	/*! \param	port	Port number */
	GZ_BASE_EXPORT	gzBool enableBroadcast(gzUInt16 port);

	//! Create a broadcast socket in a single call
	/*! \param	port	Port number
		\param	iface	Interface address to bind to */
	GZ_BASE_EXPORT	gzBool enableBroadcast(gzUInt16 port, const gzHostAddress& iface);

	GZ_BASE_EXPORT gzVoid setReceiveBufferSize(gzUInt32 messageSize,gzUInt32 bufferSize=0);

	GZ_BASE_EXPORT static gzString getSocketErrorText(gzSocketError error);

	// ------------- Properties -----------------------------------

	GZ_PROPERTY_EXPORT(gzBool,					StopTickerOnFirstRecieve, GZ_BASE_EXPORT);

	GZ_PROPERTY_EXPORT(gzBool,					CloseOnNoConnection, GZ_BASE_EXPORT);

	GZ_PROPERTY_GET_EXPORT(gzSocketFamily,		SocketFamily, GZ_BASE_EXPORT);

	GZ_PROPERTY_GET_EXPORT(gzSocketType,		SocketType, GZ_BASE_EXPORT);

	GZ_PROPERTY_GET_EXPORT(gzSocketProtocol,	SocketProtocol, GZ_BASE_EXPORT);


private:

	GZ_BASE_EXPORT virtual gzVoid onTick() override;

	gzMutex					m_locker;

	gzSocketHandle			m_sockHandle;

	gzSocketError			m_error;

	gzSocketAddress			m_bind;

	gzSocketAddress			m_connect;

	gzBool					m_useExceptions;

	gzBool					m_blocking;

	// ----------- Buffers ----------------------------

	gzDynamicArray<gzUByte>	m_buffer;

	gzDynamicArray<gzUByte>	m_second_buffer;

	gzSocketAddress			m_buffer_address;

	gzUInt32				m_interface;
};

// ---------------- ICMP ------------------

#define PING_DEFAULT_PACKET_SIZE 32U
#define PING_DEFAULT_TTL 30
#define PING_DEFAULT_TIMEOUT 2		// 2 seconds
#define PING_MAX_DATA_SIZE 1024U
#define PING_MAX_PACKET_SIZE (PING_MAX_DATA_SIZE + sizeof(IPHeader))

#pragma pack(1)		// TODO: Check NetworkOrder på headers

// The IP header
struct IPHeader
{
	gzUInt8		h_len : 4;		// Length of the header in dwords
	gzUInt8		version : 4;	// Version of IP
	gzUInt8		tos;			// Type of service
	gzUInt16	total_len;		// Length of the packet in dwords
	gzUInt16	ident;			// unique identifier
	gzUInt16	flags;			// Flags
	gzUInt8		ttl;			// Time to live
	gzUInt8		proto;			// Protocol number (TCP, UDP etc)
	gzUInt16	checksum;		// IP checksum
	gzUInt32	source_ip;
	gzUInt32	dest_ip;
};

// ICMP header
struct ICMPHeader
{
	gzUInt8		type;		// ICMP packet type
	gzUInt8		code;		// Type sub code
	gzUInt16	checksum;
	gzUInt16	id;
	gzUInt16	seq;

	// --- payload ----

	gzDouble	timestamp;	// not part of ICMP, but we need it
};

#pragma pack()

enum gzPingError
{
	GZ_PING_ERROR_OK,
	GZ_PING_ERROR_INVALID_SOCKET_HANDLE,
	GZ_PING_ERROR_INVALID_SOCKET_TYPE,
	GZ_PING_ERROR_TTL_FAILED,
	GZ_PING_ERROR_INVALID_DESTINATION,
	GZ_PING_ERROR_CORRUPT_RESPONCE,
	GZ_PING_ERROR_DESTINATION_UNREACHABLE,
	GZ_PING_ERROR_TTL_EXPIRED,
	GZ_PING_ERROR_UNKNOWN_ICMP_REPONSE,
	GZ_PING_ERROR_NO_PACKETS_SENT,
	GZ_PING_ERROR_TIMEOUT,

};

// ---------------- Utilites ---------------------

GZ_BASE_EXPORT gzHostInfo		getHostInfo();	// Default local host
GZ_BASE_EXPORT gzHostAddress	getLocalHostAddress();
GZ_BASE_EXPORT gzHostInfo		getHostInfo(const gzString &hostName);
GZ_BASE_EXPORT gzHostInfo		getHostInfo(const gzHostAddress &hostAddress);
GZ_BASE_EXPORT gzString			getNetworkClientID();
GZ_BASE_EXPORT gzHostAddress	gzGetHostAddress(const gzString &name);
GZ_BASE_EXPORT gzDouble			gzGetPingTime(gzSocket* raw_socket, const gzSocketAddress& destination, gzUInt32 packet_size = PING_DEFAULT_PACKET_SIZE, gzUInt8 ttl = PING_DEFAULT_TTL, gzUInt32 packets = 1, gzPingError* error = NULL,gzDouble timeout= PING_DEFAULT_TIMEOUT);


// ------------- GizmoBase implementation ---------------

GZ_BASE_EXPORT gzUInt32			gzSwapNetworkBytesL(gzUInt32 value);
GZ_BASE_EXPORT gzUInt16			gzSwapNetworkBytesS(gzUInt16 value);



#endif // __GZ_NETWORK_H__
