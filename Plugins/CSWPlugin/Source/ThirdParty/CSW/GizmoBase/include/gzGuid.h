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
// File			: gzGuid.h
// Module		: gzBase
// Description	: Class definition of GUID types
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
// AMO	980819	Created file 	
// AMO	250213	Added isValid as !isNULL							(2.12.217)
// AMO	250311	Added extra parameter to disbale format warning		(2.12.2230) 
//
//******************************************************************************

#ifndef __GZ_GUID_H__
#define __GZ_GUID_H__

#include "gzBasicTypes.h"
#include "gzTime.h"

class gzString; // Forward decl
class gzMutex;

//*********************************** GUID *************************************

class GZ_BASE_EXPORT gzGUIDBytes
{
public:

	gzGUIDBytes(gzUByte b1=0,gzUByte b2=0,gzUByte b3=0,gzUByte b4=0,gzUByte b5=0,gzUByte b6=0,gzUByte b7=0,gzUByte b8=0);

	gzUByte b1,b2,b3,b4,b5,b6,b7,b8;
};

#ifndef GZ_WINDOWS	// We don't have any built in GUID definition

	typedef struct _GUID
	{
		gzUInt32  Data1;
		gzUInt16 Data2;
		gzUInt16 Data3;
		gzUByte  Data4[8];
	} GUID;

#endif

class GZ_BASE_EXPORT gzGUID
{
public:

	// Creation

	gzGUID();
	gzGUID(const GUID & guid);
	gzGUID(const gzUInt32 data1, const gzUInt16 data2 = 0, const gzUInt16 data3 = 0, const gzGUIDBytes & data4 = 0);
	gzGUID(const gzString &format, gzBool useFormatWarning = TRUE);
	gzGUID(const gzWideChar* ustring, gzUInt32 len = 0, gzBool useFormatWarning = TRUE);
	gzGUID(const gzChar *cstring, gzUInt32 len=0, gzBool useFormatWarning = TRUE);
	gzGUID(const gzUInt64& val1, const gzUInt64& val2);


	// Casts & Tests

	gzBool operator==(const gzGUID &right) const;
	gzBool operator!=(const gzGUID &right) const;
	gzBool operator<(const gzGUID &right) const;

	gzBool operator==(const GUID &right) const;
	gzBool operator!=(const GUID &right) const;

	operator GUID & ();

	gzGUID &operator=(const GUID &right);

	// Methods

	GUID &		getGUID();
	const GUID &getConstGUID() const;
	gzVoid		generate();	// Generate a new GUID
	gzVoid		reset();	// Generate NULL guid

	gzBool		isNull()		const;
	gzBool		isValid()		const;
	gzBool		isStandardDCE() const;
	gzBool		isRandomBased() const;
	gzBool		isTimeBased()	const;
	gzBool		isNameBased()	const;

	gzTime		getGenerationTime() const;
	gzString	asString(gzBool skipCurly=FALSE) const;
	gzVoid		getGUID(gzUInt32& val1, gzUInt32& val2, gzUInt32& val3, gzUInt32& val4) const;
	gzVoid		getGUID(gzUInt64& val1, gzUInt64& val2) const;
	
	gzUInt32		hash() const;	// If the GUID value <= 32bits (gzUInt32), the value is returned unchanged.

	static gzGUID	generateGUID();	// Generate a new GUID

private:

	union
	{
		GUID guid;

		struct
		{
			gzUInt64 data1;
			gzUInt64 data2;
		} lldata;

		struct
		{
			gzUInt32 data1;
			gzUInt32 data2;
			gzUInt32 data3;
			gzUInt32 data4;
		} ldata;

	} data;
};

//******************************************************************************

class gzGUIDInstanceDictionary : public gzRefDict<gzGUID, gzReference>
{
public:
	gzGUIDInstanceDictionary(gzUInt32 size = 100) : gzRefDict<gzGUID, gzReference>(size) {};
};

class gzAdapterGUIDData : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzAdapterGUIDData(const gzGUID &_guid) : guid(_guid),encode_index(0), decode_index(0), encoded(FALSE){};

	GZ_BASE_EXPORT virtual	gzBool	useDeepCopy() override { return FALSE; }

	gzGUID				guid;

	gzUInt32			encode_index;

	gzUInt32			decode_index;

	gzBool				encoded;
};

//******************************************************************************

//! A const GUID = null
const gzGUID GZ_NULL_GUID = gzGUID();

#endif // __GZ_GUID_H__







