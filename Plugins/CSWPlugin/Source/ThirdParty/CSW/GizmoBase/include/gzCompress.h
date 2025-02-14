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
// File			: gzCompress.h
// Module		: gzBase
// Description	: Class definitions for compress utility
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
// AMO	980819	Created file 	
// AMO	000531	Restructured Message Receivers, Allow multiple instances
//
//******************************************************************************

#ifndef __GZ_COMPRESS_H__
#define __GZ_COMPRESS_H__

#include "gzTemplates.h"
#include "gzSerialize.h"

/*!	\file 
	\brief Basic utilites for byte stream compress/uncompress

*/

enum gzCompressLevel
{
	GZ_CL_NO_COMPRESSION        = 0,
	GZ_CL_BEST_SPEED            = 1,
	GZ_CL_LEVEL_1				= 1,
	GZ_CL_LEVEL_2				= 2,
	GZ_CL_LEVEL_3				= 3,
	GZ_CL_LEVEL_4				= 4,
	GZ_CL_LEVEL_5				= 5,
	GZ_CL_LEVEL_6				= 6,
	GZ_CL_LEVEL_7				= 7,
	GZ_CL_LEVEL_8				= 8,
	GZ_CL_LEVEL_9				= 9,
	GZ_CL_BEST_COMPRESSION      = 9,
	GZ_CL_DEFAULT_COMPRESSION   =-1,
};

GZ_BASE_EXPORT gzBool gzCompress(const gzArray<gzUByte> &from , gzArray<gzUByte> &to, gzDynamicArray<gzUByte> *buffer=nullptr, const gzCompressLevel& level = GZ_CL_DEFAULT_COMPRESSION);
GZ_BASE_EXPORT gzBool gzCompress(const gzArray<gzQWA_UByte> &from , gzArray<gzQWA_UByte> &to, gzDynamicArray<gzQWA_UByte> *buffer=nullptr, const gzCompressLevel& level = GZ_CL_DEFAULT_COMPRESSION);

GZ_BASE_EXPORT gzBool gzUnCompress(const gzArray<gzUByte> &from , gzArray<gzUByte> &to);
GZ_BASE_EXPORT gzBool gzUnCompress(const gzArray<gzQWA_UByte> &from , gzArray<gzQWA_UByte> &to);

GZ_BASE_EXPORT gzBool gzCompress(const gzDynamicArray<gzUByte> &from , gzDynamicArray<gzUByte> &to, gzDynamicArray<gzUByte> *buffer=nullptr, const gzCompressLevel& level = GZ_CL_DEFAULT_COMPRESSION);
GZ_BASE_EXPORT gzBool gzCompress(const gzDynamicArray<gzQWA_UByte> &from , gzDynamicArray<gzQWA_UByte> &to, gzDynamicArray<gzQWA_UByte> *buffer=nullptr,const gzCompressLevel& level = GZ_CL_DEFAULT_COMPRESSION);

GZ_BASE_EXPORT gzBool gzUnCompress(const gzDynamicArray<gzUByte> &from , gzDynamicArray<gzUByte> &to);
GZ_BASE_EXPORT gzBool gzUnCompress(const gzDynamicArray<gzQWA_UByte> &from , gzDynamicArray<gzQWA_UByte> &to);

GZ_BASE_EXPORT gzBool gzCompress(const gzUByte *from , gzUInt32 len_in , gzUByte *to , gzUInt32 &len_out, const gzCompressLevel& level= GZ_CL_DEFAULT_COMPRESSION);

GZ_BASE_EXPORT gzBool gzUnCompress(const gzUByte *from , gzUInt32 len_in , gzUByte *to , gzUInt32 &len_out);

//! CRC32 polynom x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1.
GZ_BASE_EXPORT gzUInt32 gzCRC32(gzUInt32 crc,const gzUByte *buffer , gzUInt32 len);


// --------- Def of adapters -----------------------------

//******************************************************************************
// Class	: gzSerializeAdapterZIP
//									
// Purpose  : class for Serialize Adapter compression using zip archive
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	110208	Created 
//									
//******************************************************************************
class  gzSerializeAdapterZIP : public gzSerializeAdapter 
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI
		
	GZ_BASE_EXPORT gzSerializeAdapterZIP(gzSerializeAdapter *parent,gzSerializeAction action=GZ_SERIALIZE_INPUT);

	GZ_BASE_EXPORT virtual ~gzSerializeAdapterZIP();

	GZ_BASE_EXPORT gzBool setCurrentItem(const gzString &item);

	GZ_PROPERTY_GET_EXPORT(gzString,	CurrentItem,	GZ_BASE_EXPORT);
	GZ_PROPERTY_EXPORT(gzString,		Comment,		GZ_BASE_EXPORT);

	//! Default to streamed input/output
	GZ_BASE_EXPORT virtual	gzBool		canSeek() override;
	GZ_BASE_EXPORT gzVoid	setError(const gzString& error) override;


	//! Default to support all directions
	GZ_BASE_EXPORT virtual gzBool		supportAction(gzSerializeAction action) override;

	GZ_BASE_EXPORT virtual	gzVoid		flush() override;

	//! Use this to signal close to inherited classes.
	GZ_BASE_EXPORT virtual gzBool aboutToClose(gzBool wait ) override;
	
	// Internal utilities to write/read RAW zip
	GZ_BASE_EXPORT gzVoid		writeZIP(gzUByte *data,gzUInt32 count);
	GZ_BASE_EXPORT gzUInt32		readZIP(gzUByte *data,gzUInt32 maxcount);
	GZ_BASE_EXPORT gzMemSize	seekZIP(gzMemOffset offset, gzOriginPos origin=GZ_ORIGIN_SET);

protected:

	GZ_BASE_EXPORT virtual	gzMemSize	seek_imp(gzMemOffset offset, gzOriginPos origin = GZ_ORIGIN_SET) override;
		
	GZ_BASE_EXPORT virtual gzVoid		write_imp(gzUByte data) override;
	GZ_BASE_EXPORT virtual gzUByte		read_imp() override;

	GZ_BASE_EXPORT virtual gzVoid		write_imp(const gzUByte *data,gzUInt32 count) override;
	GZ_BASE_EXPORT virtual gzUInt32		read_imp(gzUByte *data,gzUInt32 maxcount) override;

	GZ_BASE_EXPORT virtual gzUInt32		length_imp() override;

	GZ_BASE_EXPORT gzVoid setAdapter(gzSerializeAdapter *parent,gzSerializeAction action=GZ_SERIALIZE_INPUT);

private:

	gzBool checkInputService(const gzString& url);
	gzBool checkOutputService(const gzString& url);

	gzSerializeAdapterPtr		m_adapter;
	gzVoid					*	m_zipHandle;
	gzString					m_currentItem;
	gzSerializeAction			m_action;
	gzArray<gzUByte>			m_data;
	gzSerializeAdapterMemory	m_memoryAdapter;

};

GZ_DECLARE_REFPTR(gzSerializeAdapterZIP);


#endif // __GZ_COMPRESS_H__
