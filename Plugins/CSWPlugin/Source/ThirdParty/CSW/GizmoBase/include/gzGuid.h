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
// Author		: Anders Mod�n		
// Product		: GizmoBase 2.12.306
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
// AMO	251231	Added Doxygen for gzGUID API					(2.12.297)
//
//******************************************************************************

#ifndef __GZ_GUID_H__
#define __GZ_GUID_H__

#include "gzBasicTypes.h"
#include "gzTime.h"

class gzString; // Forward decl
class gzMutex;

//*********************************** GUID *************************************

/*! \brief Byte container for GUID Data4 field.

Stores the 8 byte sequence used in the GUID Data4 field.
*/
class GZ_BASE_EXPORT gzGUIDBytes
{
public:

	//! Construct from 8 byte values for Data4.
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

/*! \brief GUID wrapper with parse, format, and generation helpers.

Provides constructors from native GUID, strings, and raw fields. Supports
formatting and version/variant inspection.
*/
class GZ_BASE_EXPORT gzGUID
{
public:

	// Creation

	gzGUID();
	gzGUID(const GUID & guid);
	gzGUID(const gzUInt32 data1, const gzUInt16 data2 = 0, const gzUInt16 data3 = 0, const gzGUIDBytes & data4 = 0);
	//! Parse GUID from gzString (formats with/without curly braces).
	gzGUID(const gzString &format, gzBool useFormatWarning = TRUE);
	//! Parse GUID from wide string (formats with/without curly braces).
	gzGUID(const gzWideChar* ustring, gzUInt32 len = 0, gzBool useFormatWarning = TRUE);
	//! Parse GUID from narrow string (formats with/without curly braces).
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
	//! Generate a new time-based GUID.
	gzVoid		generate();	// Generate a new GUID
	//! Reset to NULL GUID.
	gzVoid		reset();	// Generate NULL guid

	//! True if all fields are zero.
	gzBool		isNull()		const;
	//! True if any field is non-zero.
	gzBool		isValid()		const;
	//! True if variant is DCE standard (RFC4122).
	gzBool		isStandardDCE() const;
	//! True if version is random-based (v4).
	gzBool		isRandomBased() const;
	//! True if version is time-based (v1).
	gzBool		isTimeBased()	const;
	//! True if version is name-based (v3).
	gzBool		isNameBased()	const;

	//! Extract generation time for time-based GUIDs.
	gzTime		getGenerationTime() const;
	//! Format GUID as string, optionally without curly braces.
	gzString	asString(gzBool skipCurly=FALSE) const;
	gzVoid		getGUID(gzUInt32& val1, gzUInt32& val2, gzUInt32& val3, gzUInt32& val4) const;
	gzVoid		getGUID(gzUInt64& val1, gzUInt64& val2) const;
	
	//! Hash value based on 128-bit GUID contents.
	gzUInt32		hash() const;	// If the GUID value <= 32bits (gzUInt32), the value is returned unchanged.

	//! Convenience factory for a new GUID.
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

/*! \brief Dictionary mapping GUID to reference instances. */
class gzGUIDInstanceDictionary : public gzRefDict<gzGUID, gzReference>
{
public:
	gzGUIDInstanceDictionary(gzUInt32 size = 100) : gzRefDict<gzGUID, gzReference>(size) {};
};

/*! \brief Adapter data for GUID serialization.

Holds GUID and encode/decode state for serialization.
*/
class gzAdapterGUIDData : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzAdapterGUIDData(const gzGUID &_guid) : guid(_guid),encode_index(0), decode_index(0), encoded(FALSE){};

	//! Disable deep copy for adapter data.
	GZ_BASE_EXPORT virtual	gzBool	useDeepCopy() override { return FALSE; }

	gzGUID				guid;

	gzUInt32			encode_index;

	gzUInt32			decode_index;

	gzBool				encoded;
};

//******************************************************************************

//! Constant null GUID value.
const gzGUID GZ_NULL_GUID = gzGUID();

#endif // __GZ_GUID_H__







