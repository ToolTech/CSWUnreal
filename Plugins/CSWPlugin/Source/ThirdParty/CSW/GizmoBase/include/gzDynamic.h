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
// File			: gzDynamic.h
// Module		: gzBase
// Description	: Class definition of dynamic methods and vars
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
// AMO	991002	Created file
// AMO	110608	Added support for XY and XYZ data in dynamic types  (2.5.20)
// AMO	121214	Added asString() method to gzDynamicType to do a generic printout of data (2.6.18)
// AMO	131009	Fixed bug in description of query of all module descriptions		(2.7.0)
// AMO	150413	Added macros for array and container								(2.8.1)
// AMO	150923	Added dynamic cast for arrays of std data							(2.8.1)
// AMO	210420	Added encoders/decoders for compressed streams						(2.10.23)
// AMO	210429	Optimized serialisation ( Breaks compatibility with old version )	(2.11.1)
//
// ******************************************************************************

#ifndef __GZ_DYNAMIC_H__
#define __GZ_DYNAMIC_H__

#include "gzBase.h"
#include "gzSerialize.h"
#include "gzExceptions.h"
#include "gzReference.h"
#include "gzNotify.h"
#include "gzGuid.h"
#include "gzUniqueStrings.h"	// All unique strings defs

class gzDynamicType;			// Foward decl

//------------------------- IID --------------------------------------------------
// Generic commands

//! Send "debug" command to module
const gzString	IIDS_DEBUG					= "debug";
const gzUInt64	IID_DEBUG					= LLU(0x7fffffff00000001);

//! Get version of module or print version
const gzString	IIDS_VERSION				= "version";
const gzUInt64	IID_VERSION					= LLU(0x7fffffff00000002);

//! Get license expiration
const gzString	IIDS_LICENSE_EXPIRE_DAYS	= "licenseExpireDays";
const gzUInt64	IID_LICENSE_EXPIRE_DAYS		= LLU(0x7fffffff00000003);

//! Send "test" command to module
const gzString	IIDS_TEST					= "test";
const gzUInt64	IID_TEST					= LLU(0x7fffffff00000004);

//! Get description of module
const gzString	IIDS_DESCRIPTION			= "description";
const gzUInt64	IID_DESCRIPTION				= LLU(0x7fffffff00000005);

//! Get information about module license
const gzString	IIDS_LICENSE_INFO			= "licenseInfo";
const gzUInt64	IID_LICENSE_INFO			= LLU(0x7fffffff00000006);

//! Get notify about module is sucessfully loaded
const gzString	IIDS_LOADED					= "loaded";
const gzUInt64	IID_LOADED					= LLU(0x7fffffff00000007);

//! Get compound module info
const gzString	IIDS_MODULE_INFO			= "moduleInfo";
const gzUInt64	IID_MODULE_INFO				= LLU(0x7fffffff00000008);

const gzUInt64	IID_NOT_SUPPORTED			= LLU(0xFFFFFFFFFFFFFFFF);

//! Dynamic String Serialize esquape secuence
const gzUByte GZ_UNIQUE_ID_ESCAPE_TOKEN=0xfc;

//! Default tag name when dyn tag is not used
const gzString GZ_SKIP_DYN_TAG="data";

//******************************************************************************
// Class	: gzDynRefList
//									
// Purpose  : Internal utility class that manages reference counting in dynamic types
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	001030	Created 
//									
//******************************************************************************
class gzDynRefList : public gzList<gzReference>
{
public:
	
	gzDynRefList(){};

	gzDynRefList( const gzDynRefList &copy ):gzList<gzReference>(){ *this=copy; }

	virtual ~gzDynRefList(){ clear(); }

	virtual gzVoid onInsert(gzReference *item ) const {item->ref(); }

	virtual gzVoid onRemove(gzReference *item ) const {item->unref(); }

	virtual gzReference *cloneEntry(gzReference *item ) const { return item; }
};

//******************************************************************************
// Class	: gzDynamicTypeEncoderInterface
//									
// Purpose  : Interface for dynamic type compression and decompression
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	210416	Created 
//									
//******************************************************************************
class gzDynamicTypeEncoderInterface : public gzReference
{
public:

	//! Write payload data incluse var len size at start or return false
	virtual gzBool		write(gzSerializeAdapter* adapter,gzDynamicType *data)=0;

	//! Read payload given length {len} or return false
	virtual gzBool		read(gzSerializeAdapter* adapter, gzDynamicType* data,gzUInt32 len)=0;
};

//******************************************************************************
// Class	: gzDynamicType
//									
// Purpose  : Base class for gizmo dynamic data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980912	Created 
//									
//******************************************************************************
class  gzDynamicType : public gzSerializeData , public gzTypeInterface
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzDynamicType(const gzDouble		&value);
	GZ_BASE_EXPORT gzDynamicType(const gzString		&value);
	GZ_BASE_EXPORT gzDynamicType(const gzVoid		*value);
	GZ_BASE_EXPORT gzDynamicType(const gzReference	*value);
	GZ_BASE_EXPORT gzDynamicType(const gzVec2		&value);
	GZ_BASE_EXPORT gzDynamicType(const gzVec3		&value);
	GZ_BASE_EXPORT gzDynamicType(const gzVec4		&value);
	GZ_BASE_EXPORT gzDynamicType(const gzVec2D		&value);
	GZ_BASE_EXPORT gzDynamicType(const gzVec3D		&value);
	GZ_BASE_EXPORT gzDynamicType(const gzVec4D		&value);
	GZ_BASE_EXPORT gzDynamicType(const gzQuaternion	&value);
	GZ_BASE_EXPORT gzDynamicType(const char			*value);
	GZ_BASE_EXPORT gzDynamicType(const gzGUID		&value);

	GZ_BASE_EXPORT gzDynamicType();

	GZ_BASE_EXPORT gzDynamicType(const gzDynamicType & copy);

	GZ_BASE_EXPORT gzDynamicType & operator=(const gzDynamicType & copy);

	GZ_BASE_EXPORT virtual ~gzDynamicType();

	GZ_BASE_EXPORT gzBool					is(const gzString & dynamicType) const;
	GZ_BASE_EXPORT const gzString &			getDynamicType() const;
	GZ_BASE_EXPORT const gzArray<gzUByte> &	getDynamicData() const;
	GZ_BASE_EXPORT const gzDynRefList &		getDynamicReferences() const;
	GZ_BASE_EXPORT gzBool					hasDynamicReferences() const;

	// Serializing -------------------------------------------------------------------

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

	GZ_BASE_EXPORT gzString			getString()		const;
	GZ_BASE_EXPORT gzDouble			getNumber()		const;
	GZ_BASE_EXPORT gzVoid *			getPointer()	const;
	GZ_BASE_EXPORT gzReference *	getReference()	const;

	GZ_BASE_EXPORT gzVec2 			getVec2()		const;
	GZ_BASE_EXPORT gzVec3 			getVec3()		const;
	GZ_BASE_EXPORT gzVec4 			getVec4()		const;
	GZ_BASE_EXPORT gzVec2D 			getVec2D()		const;
	GZ_BASE_EXPORT gzVec3D 			getVec3D()		const;
	GZ_BASE_EXPORT gzVec4D 			getVec4D()		const;
	GZ_BASE_EXPORT gzQuaternion		getQuaternion()	const;
	GZ_BASE_EXPORT gzGUID 			getGUID()		const;

	GZ_BASE_EXPORT gzBool	operator ==(const gzDynamicType & compare) const;
	GZ_BASE_EXPORT gzBool	operator !=(const gzDynamicType & compare) const;

	GZ_BASE_EXPORT gzVoid			reset();

	GZ_BASE_EXPORT gzString					asString(gzBool stripXML=TRUE,gzBool skipDynTag=TRUE,const gzString &tagName=GZ_SKIP_DYN_TAG)		const;
	GZ_BASE_EXPORT gzString					asJSON(gzBool formatted=TRUE)		const;

	GZ_BASE_EXPORT gzBool					asStream(gzSerializeAdapter *adapter, gzBool wideChar = FALSE, gzBool skipDynTag = TRUE, const gzString& tagName = GZ_SKIP_DYN_TAG)		const;
	GZ_BASE_EXPORT gzBool					asJSON(gzSerializeAdapter * adapter, gzBool formatted)		const;

	GZ_BASE_EXPORT static gzDynamicType		fromString(const gzString &type, const gzString &string, gzBool *ok = NULL, gzBool skipDynTag = TRUE);
	GZ_BASE_EXPORT static gzDynamicType		fromXML(const gzString &xml,gzBool *ok=nullptr,gzBool skipDynTag=TRUE);
	GZ_BASE_EXPORT static gzDynamicType		fromJSON(const gzString& json, gzBool* ok = NULL, gzBool useEscapeUnicode = FALSE);

	GZ_BASE_EXPORT static gzDynamicType		fromXML(gzSerializeAdapter *adapter, gzBool* ok = NULL, gzBool skipDynTag = TRUE);
	GZ_BASE_EXPORT static gzDynamicType		fromJSON(gzSerializeAdapter* adapter, gzBool* ok = NULL);

	GZ_BASE_EXPORT static gzBool registerEncoder(const gzString& type, gzDynamicTypeEncoderInterface* iface);
	GZ_BASE_EXPORT static gzBool unregisterEncoder(const gzString& type);
	GZ_BASE_EXPORT static gzVoid unregisterAllEncoders();
	GZ_BASE_EXPORT static gzDynamicTypeEncoderInterface* getEncoder(const gzString& type);

protected:
	
	gzString							m_type;
	gzArray<gzUByte>					m_data;
	gzLateBindData<gzDynRefList>		m_references;
};

//******************************************************************************
// Class	: gzDynamicTypeVoid
//									
// Purpose  : gzVoid
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000602	Created 
//									
//******************************************************************************
class  gzDynamicTypeVoid : public gzDynamicType
{
public:
	GZ_BASE_EXPORT gzDynamicTypeVoid();
	GZ_BASE_EXPORT gzDynamicTypeVoid(const gzDynamicType &copy);
};

//******************************************************************************
// Class	: gzDynamicTypeChain
//									
// Purpose  : Chain a possible result evaluation to a higher level of command
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	031217	Created 
//									
//******************************************************************************
//! A dynamic method invokation can resturn this to chain the result evaluation to a higher level
class  gzDynamicTypeChain : public gzDynamicType
{
public:
	GZ_BASE_EXPORT gzDynamicTypeChain();
	GZ_BASE_EXPORT gzDynamicTypeChain(const gzDynamicType &copy);
};


//******************************************************************************
// Class	: gzDynamicTypeError
//									
// Purpose  :  Dynamic Errors
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000602	Created 
//									
//******************************************************************************
class  gzDynamicTypeError : public gzDynamicType
{
public:
	GZ_BASE_EXPORT gzDynamicTypeError(const gzString &errorvalue);
	GZ_BASE_EXPORT gzDynamicTypeError(const gzChar *errorvalue);
	GZ_BASE_EXPORT gzDynamicTypeError(const gzDynamicType &copy);

	GZ_BASE_EXPORT gzString getError() const;
	GZ_BASE_EXPORT gzVoid	setError(const gzString &error);
	GZ_BASE_EXPORT operator gzString () const { return getError(); }
	GZ_BASE_EXPORT gzBool	isError() const;
};

//******************************************************************************
// Class	: gzDynamicTypeInt64
//									
// Purpose  : Large Long Numbers
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000602	Created 
//									
//******************************************************************************
class  gzDynamicTypeInt64 : public gzDynamicType
{
public:
	GZ_BASE_EXPORT gzDynamicTypeInt64(const gzInt64 &value);
	GZ_BASE_EXPORT gzDynamicTypeInt64(const gzDynamicType &copy);

	GZ_BASE_EXPORT gzInt64 getInt64() const;
	GZ_BASE_EXPORT operator gzInt64 () const { return getInt64(); }
};

//******************************************************************************
// Class	: gzDynamicTypeTimeTagged
//									
// Purpose  : A Time tagged dynamic type
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	180314	Created 
//									
//******************************************************************************
class  gzDynamicTypeTimeTagged : public gzDynamicType
{
public:
	GZ_BASE_EXPORT gzDynamicTypeTimeTagged(const gzDouble &time=0.0, const gzDynamicType &data = gzDynamicType());
	GZ_BASE_EXPORT gzDynamicTypeTimeTagged(const gzDynamicType &copy);

	GZ_BASE_EXPORT gzDouble			getTimeTag() const;
	GZ_BASE_EXPORT gzDynamicType	getData() const;
	GZ_BASE_EXPORT gzUByte			getTagDataSize() const;
	GZ_BASE_EXPORT gzDoubleEncoding	getTagEncoding() const;
};

//******************************************************************************
// Class	: gzDynamicTypeArray
//									
// Purpose  : Dynamic Array
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000623	Created 
//									
//******************************************************************************
class  gzDynamicTypeArray : public gzDynamicType
{
public:
	GZ_BASE_EXPORT gzDynamicTypeArray(const gzArray<gzDynamicType> &array);
	GZ_BASE_EXPORT gzDynamicTypeArray(const gzDynamicArray<gzDynamicType> &array);
	GZ_BASE_EXPORT gzDynamicTypeArray(const gzDynamicType &copy);
	GZ_BASE_EXPORT gzDynamicTypeArray();

	GZ_BASE_EXPORT gzArray<gzDynamicType> getArray() const;
	GZ_BASE_EXPORT operator gzArray<gzDynamicType> () const { return getArray(); }
};

//----------------------------------------------------------------------------------

//! Default no error (Ok value) in a gzDynamicTypeError
const gzDynamicTypeError	GZ_DYN_ERR_OK(GZ_DYNAMIC_ERROR_NO_ERROR);
const gzDynamicTypeError	GZ_DYN_ERR_FAIL(GZ_DYNAMIC_ERROR_FAIL);
const gzDynamicTypeError	GZ_DYN_TEST_OK(GZ_DYNAMIC_ERROR_TEST_OK);
const gzDynamicTypeError	GZ_DYN_TEST_FAIL(GZ_DYNAMIC_ERROR_TEST_FAIL);
const gzDynamicTypeError	GZ_DYN_MISSING(GZ_DYNAMIC_ERROR_VALUE_NOT_SET);
const gzDynamicTypeVoid		GZ_DYN_VOID;

GZ_BASE_EXPORT gzBool GZ_FAIL			(const gzDynamicType &result);	// TRUE if error but not  GZ_DYN_ERR_OK and not GZ_DYN_TEST_OK
GZ_BASE_EXPORT gzBool GZ_TEST_FAIL		(const gzDynamicType &result);	// TRUE if GZ_DYN_TEST_FAIL
GZ_BASE_EXPORT gzBool GZ_SUCCESS		(const gzDynamicType &result);	// TRUE if non error or GZ_DYN_ERR_OK or GZ_DYN_TEST_OK
GZ_BASE_EXPORT gzBool GZ_TEST_SUCCESS	(const gzDynamicType &result);	// TRUE if GZ_DYN_TEST_OK

#define GZ_DYN_ARG(n)			const gzDynamicType &a##n
#define GZ_DYN_ARG_E(n)			const gzDynamicType &
#define GZ_DYN_ARG_TYPE(n)		const gzString &t##n
#define GZ_DYN_ARG_TYPE_E(n)	const gzString &
#define GZ_DYN_ARG_NULL(n)		const gzString &t##n=GZ_EMPTY_STRING

#define GZ_DYN_ARG_VOID(n)		GZ_DYN_ARG(n)=GZ_DYN_VOID
#define GZ_DYN_ARG_TYPE_VOID(n) GZ_DYN_ARG_TYPE(n)=GZ_DYNAMIC_TYPE_VOID



#define GZ_DYNAMIC_ATTRIBUTE_LIST	GZ_DYN_ARG_VOID(0),\
									GZ_DYN_ARG_VOID(1),\
									GZ_DYN_ARG_VOID(2),\
									GZ_DYN_ARG_VOID(3),\
									GZ_DYN_ARG_VOID(4),\
									GZ_DYN_ARG_VOID(5),\
									GZ_DYN_ARG_VOID(6),\
									GZ_DYN_ARG_VOID(7),\
									GZ_DYN_ARG_VOID(8),\
									GZ_DYN_ARG_VOID(9)

#define GZ_DYNAMIC_ATTRIBUTE_TYPE_LIST	GZ_DYN_ARG_TYPE_VOID(0),\
										GZ_DYN_ARG_TYPE_VOID(1),\
										GZ_DYN_ARG_TYPE_VOID(2),\
										GZ_DYN_ARG_TYPE_VOID(3),\
										GZ_DYN_ARG_TYPE_VOID(4),\
										GZ_DYN_ARG_TYPE_VOID(5),\
										GZ_DYN_ARG_TYPE_VOID(6),\
										GZ_DYN_ARG_TYPE_VOID(7),\
										GZ_DYN_ARG_TYPE_VOID(8),\
										GZ_DYN_ARG_TYPE_VOID(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP	GZ_DYN_ARG(0),\
										GZ_DYN_ARG(1),\
										GZ_DYN_ARG(2),\
										GZ_DYN_ARG(3),\
										GZ_DYN_ARG(4),\
										GZ_DYN_ARG(5),\
										GZ_DYN_ARG(6),\
										GZ_DYN_ARG(7),\
										GZ_DYN_ARG(8),\
										GZ_DYN_ARG(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E	GZ_DYN_ARG_E(0),\
										GZ_DYN_ARG_E(1),\
										GZ_DYN_ARG_E(2),\
										GZ_DYN_ARG_E(3),\
										GZ_DYN_ARG_E(4),\
										GZ_DYN_ARG_E(5),\
										GZ_DYN_ARG_E(6),\
										GZ_DYN_ARG_E(7),\
										GZ_DYN_ARG_E(8),\
										GZ_DYN_ARG_E(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E1	GZ_DYN_ARG(0),\
											GZ_DYN_ARG_E(1),\
											GZ_DYN_ARG_E(2),\
											GZ_DYN_ARG_E(3),\
											GZ_DYN_ARG_E(4),\
											GZ_DYN_ARG_E(5),\
											GZ_DYN_ARG_E(6),\
											GZ_DYN_ARG_E(7),\
											GZ_DYN_ARG_E(8),\
											GZ_DYN_ARG_E(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E2	GZ_DYN_ARG(0),\
											GZ_DYN_ARG(1),\
											GZ_DYN_ARG_E(2),\
											GZ_DYN_ARG_E(3),\
											GZ_DYN_ARG_E(4),\
											GZ_DYN_ARG_E(5),\
											GZ_DYN_ARG_E(6),\
											GZ_DYN_ARG_E(7),\
											GZ_DYN_ARG_E(8),\
											GZ_DYN_ARG_E(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E3	GZ_DYN_ARG(0),\
											GZ_DYN_ARG(1),\
											GZ_DYN_ARG(2),\
											GZ_DYN_ARG_E(3),\
											GZ_DYN_ARG_E(4),\
											GZ_DYN_ARG_E(5),\
											GZ_DYN_ARG_E(6),\
											GZ_DYN_ARG_E(7),\
											GZ_DYN_ARG_E(8),\
											GZ_DYN_ARG_E(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E4	GZ_DYN_ARG(0),\
											GZ_DYN_ARG(1),\
											GZ_DYN_ARG(2),\
											GZ_DYN_ARG(3),\
											GZ_DYN_ARG_E(4),\
											GZ_DYN_ARG_E(5),\
											GZ_DYN_ARG_E(6),\
											GZ_DYN_ARG_E(7),\
											GZ_DYN_ARG_E(8),\
											GZ_DYN_ARG_E(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E5	GZ_DYN_ARG(0),\
											GZ_DYN_ARG(1),\
											GZ_DYN_ARG(2),\
											GZ_DYN_ARG(3),\
											GZ_DYN_ARG(4),\
											GZ_DYN_ARG_E(5),\
											GZ_DYN_ARG_E(6),\
											GZ_DYN_ARG_E(7),\
											GZ_DYN_ARG_E(8),\
											GZ_DYN_ARG_E(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E6	GZ_DYN_ARG(0),\
											GZ_DYN_ARG(1),\
											GZ_DYN_ARG(2),\
											GZ_DYN_ARG(3),\
											GZ_DYN_ARG(4),\
											GZ_DYN_ARG(5),\
											GZ_DYN_ARG_E(6),\
											GZ_DYN_ARG_E(7),\
											GZ_DYN_ARG_E(8),\
											GZ_DYN_ARG_E(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E7	GZ_DYN_ARG(0),\
											GZ_DYN_ARG(1),\
											GZ_DYN_ARG(2),\
											GZ_DYN_ARG(3),\
											GZ_DYN_ARG(4),\
											GZ_DYN_ARG(5),\
											GZ_DYN_ARG(6),\
											GZ_DYN_ARG_E(7),\
											GZ_DYN_ARG_E(8),\
											GZ_DYN_ARG_E(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E8	GZ_DYN_ARG(0),\
											GZ_DYN_ARG(1),\
											GZ_DYN_ARG(2),\
											GZ_DYN_ARG(3),\
											GZ_DYN_ARG(4),\
											GZ_DYN_ARG(5),\
											GZ_DYN_ARG(6),\
											GZ_DYN_ARG(7),\
											GZ_DYN_ARG_E(8),\
											GZ_DYN_ARG_E(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E9	GZ_DYN_ARG(0),\
											GZ_DYN_ARG(1),\
											GZ_DYN_ARG(2),\
											GZ_DYN_ARG(3),\
											GZ_DYN_ARG(4),\
											GZ_DYN_ARG(5),\
											GZ_DYN_ARG(6),\
											GZ_DYN_ARG(7),\
											GZ_DYN_ARG(8),\
											GZ_DYN_ARG_E(9)

#define GZ_DYNAMIC_ATTRIBUTE_TYPE_LIST_IMP	GZ_DYN_ARG_TYPE(0),\
											GZ_DYN_ARG_TYPE(1),\
											GZ_DYN_ARG_TYPE(2),\
											GZ_DYN_ARG_TYPE(3),\
											GZ_DYN_ARG_TYPE(4),\
											GZ_DYN_ARG_TYPE(5),\
											GZ_DYN_ARG_TYPE(6),\
											GZ_DYN_ARG_TYPE(7),\
											GZ_DYN_ARG_TYPE(8),\
											GZ_DYN_ARG_TYPE(9)

#define GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_FORWARD		a0,a1,a2,a3,a4,a5,a6,a7,a8,a9
#define GZ_DYNAMIC_ATTRIBUTE_TYPE_LIST_IMP_FORWARD	t0,t1,t2,t3,t4,t5,t6,t7,t8,t9

#define GZ_DYA_9 gzDynamicTypeVoid()
#define GZ_DYA_8 GZ_DYA_9,gzDynamicTypeVoid()
#define GZ_DYA_7 GZ_DYA_8,gzDynamicTypeVoid()
#define GZ_DYA_6 GZ_DYA_7,gzDynamicTypeVoid()
#define GZ_DYA_5 GZ_DYA_6,gzDynamicTypeVoid()
#define GZ_DYA_4 GZ_DYA_5,gzDynamicTypeVoid()
#define GZ_DYA_3 GZ_DYA_4,gzDynamicTypeVoid()
#define GZ_DYA_2 GZ_DYA_3,gzDynamicTypeVoid()
#define GZ_DYA_1 GZ_DYA_2,gzDynamicTypeVoid()
#define GZ_DYA_0 GZ_DYA_1,gzDynamicTypeVoid()

#define GZ_DYT_9 GZ_DYNAMIC_TYPE_VOID
#define GZ_DYT_8 GZ_DYT_9,GZ_DYNAMIC_TYPE_VOID
#define GZ_DYT_7 GZ_DYT_8,GZ_DYNAMIC_TYPE_VOID
#define GZ_DYT_6 GZ_DYT_7,GZ_DYNAMIC_TYPE_VOID
#define GZ_DYT_5 GZ_DYT_6,GZ_DYNAMIC_TYPE_VOID
#define GZ_DYT_4 GZ_DYT_5,GZ_DYNAMIC_TYPE_VOID
#define GZ_DYT_3 GZ_DYT_4,GZ_DYNAMIC_TYPE_VOID
#define GZ_DYT_2 GZ_DYT_3,GZ_DYNAMIC_TYPE_VOID
#define GZ_DYT_1 GZ_DYT_2,GZ_DYNAMIC_TYPE_VOID
#define GZ_DYT_0 GZ_DYT_1,GZ_DYNAMIC_TYPE_VOID

class gzDynamicInvokeInterface; // Forward decl .

typedef  gzDynamicType (GZ_CALLBACK  * gzDynamicMethod)(gzDynamicInvokeInterface *,GZ_DYNAMIC_ATTRIBUTE_LIST_IMP) ;

const gzString GZ_UNDEFINED_METHOD_NAME	=	"UnDefMethod";

//******************************************************************************
// Class	: gzDynamicMethodID
//									
// Purpose  : Dynamic invokation method identity
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000602	Created 
//									
//******************************************************************************
class gzDynamicMethodID 
{
public:
	gzDynamicMethodID():IID_method(0),IIDS_method(GZ_UNDEFINED_METHOD_NAME),method(0){};

	gzBool operator==(const gzDynamicMethodID &right) { return IID_method==right.IID_method; }
	gzBool operator!=(const gzDynamicMethodID &right) { return IID_method!=right.IID_method; }

	gzUInt64			IID_method;			//!< The unique ID of the method
	gzString			IIDS_method;		//!< The unique String Name of the method
	gzDynamicMethod		method;				//!< The direct method pointer (RAW)
	gzString			description;		//!< A description of the method
	gzString			argTypeCheck[10];	//!< Possible argument checks
};


//******************************************************************************
// Class	: gzDynamicEventData
//									
// Purpose  : Dynamic event response data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000602	Created 
//									
//******************************************************************************
class gzDynamicEventData : public gzReference
{
public:

	gzUInt64 IID_event;
	gzDynamicType GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_FORWARD;
};


class gzDynamicEventInterface; // Forward decl for slave interface

//******************************************************************************
// Class	: gzDynamicEventNotifyInterface
//									
// Purpose  : Dynamic event response from dynamic interface
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000602	Created 
//									
//******************************************************************************
class gzDynamicEventNotifyInterface : public gzNotifySlave<gzDynamicEventInterface,gzDynamicEventNotifyInterface,gzRefPointer<gzDynamicEventData> >
{
public:

	GZ_BASE_EXPORT virtual gzVoid onEvent( gzDynamicEventInterface * source , gzUInt64 IID_event , GZ_DYNAMIC_ATTRIBUTE_LIST) = 0;

private:

	friend class gzNotifyMaster<gzDynamicEventInterface,gzDynamicEventNotifyInterface,gzRefPointer<gzDynamicEventData> >;
	GZ_BASE_EXPORT virtual gzVoid onNotify(gzDynamicEventInterface *master,gzRefPointer<gzDynamicEventData> &data,gzUInt64 senderClass);

};

GZ_BASE_EXPORT gzArray<gzDynamicType> gzGetStringArguments(const gzString &params);

//******************************************************************************
// Class	: gzDynamicInvokeInterface
//									
// Purpose  : Dynamic invokation
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000602	Created 
//									
//******************************************************************************
class  gzDynamicInvokeInterface
{
public:

	//---------------------- dynamic object methods ----------------------------
	GZ_BASE_EXPORT virtual	gzDynamicType				invokeMethod(const gzString &IIDS_method,GZ_DYNAMIC_ATTRIBUTE_LIST);
	GZ_BASE_EXPORT virtual	gzDynamicType				invokeMethod(gzUInt64 IID_method,GZ_DYNAMIC_ATTRIBUTE_LIST);
	GZ_BASE_EXPORT virtual	gzDynamicType				invokeStringParamsMethod(const gzString &IIDS_method,const gzString &params);
	GZ_BASE_EXPORT virtual	gzDynamicType				invokeStringParamsMethod(gzUInt64 IID_method,const gzString &params);
	GZ_BASE_EXPORT virtual	gzBool						supportMethod(gzUInt64 IID_method);
	GZ_BASE_EXPORT virtual	gzUInt64					getMethodIID(const gzString &IIDS_method);
	GZ_BASE_EXPORT virtual	gzDynamicMethod				getDirectMethod(gzUInt64 IID_method);
	GZ_BASE_EXPORT virtual	gzString					getDescription(gzUInt64 IID_method);	
	GZ_BASE_EXPORT virtual	gzArray<gzDynamicMethodID>	queryAllMethodIID();
	GZ_BASE_EXPORT virtual	gzString					getMethodArgType(const gzString &IIDS_method, gzUInt32 index);
	GZ_BASE_EXPORT virtual	gzString					getMethodArgType(gzUInt64 IID_method, gzUInt32 index);
};

//******************************************************************************
// Class	: gzDynamicEventInterface
//									
// Purpose  : Dynamic invokation
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000602	Created 
//									
//******************************************************************************
class  gzDynamicEventInterface : public gzNotifyMaster<gzDynamicEventInterface,gzDynamicEventNotifyInterface,gzRefPointer<gzDynamicEventData> >
{
public:

	//---------------------- dynamic events ------------------------------------

	GZ_BASE_EXPORT gzVoid           sendEvent(gzUInt64 IID_event , GZ_DYNAMIC_ATTRIBUTE_LIST);
    
    GZ_BASE_EXPORT virtual gzVoid   onNotifyStatus(gzDynamicEventNotifyInterface * /*slave*/ ,gzNotifyState /*state*/ ){};

	GZ_BASE_EXPORT virtual gzReference *getBaseClassReference() { return NULL; }
};


//******************************************************************************
// Class	: gzDynamicTypeCustom
//									
// Purpose  : Template for general purpose dynvars
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000624	Created 
//									
//******************************************************************************
template <class T> class  gzDynamicTypeCustom : public gzDynamicType
{
public:
	gzDynamicTypeCustom(const T &data);
	gzDynamicTypeCustom(const gzDynamicType &copy);
	gzDynamicTypeCustom();

	operator T () const;
	const gzDynamicTypeCustom<T> & operator =(const T &data);
};

template <class T> inline gzDynamicTypeCustom<T>::gzDynamicTypeCustom(const T &data)
{
	m_type=T::getDataTag();

	T & copy=(T &)data;

	m_data.setSize(copy.getDataSize());

	gzSerializeAdapterMemory mem(m_data.getAddress(),m_data.getSize());

	copy.write(&mem);
}

template <class T> inline gzDynamicTypeCustom<T>::gzDynamicTypeCustom(const gzDynamicType &copy)
{
	if(copy.getDynamicType()!=T::getDataTag())
		gzThrowFatal("Can not convert dynamic argument type '%s' to gzDynamicTypeCustom type '%s'!!",(const char *)copy.getDynamicType(),(const char *)T::getDataTag());

	m_data=copy.getDynamicData();
	m_type=copy.getDynamicType();

	if(copy.hasDynamicReferences())
	{
		if(copy.getDynamicReferences().entries())
		{
			m_references.get()=copy.getDynamicReferences();
		}
	}
}

template <class T> inline gzDynamicTypeCustom<T>::gzDynamicTypeCustom()
{
	m_type=T::getDataTag();

	T data;

	m_data.setSize(data.getDataSize());

	gzSerializeAdapterMemory mem(m_data.getAddress(),m_data.getSize());

	data.write(&mem);
}

template <class T> inline gzDynamicTypeCustom<T>::operator T () const
{
	T data;
	
	gzSerializeAdapterMemory mem(((gzArray<unsigned char> &)m_data).getAddress(),m_data.getSize());

	data.read(&mem);

	return data;
}

template <class T> inline const gzDynamicTypeCustom<T>  & gzDynamicTypeCustom<T>::operator =(const T &data)
{
	m_type=T::getDataTag();

	T & copy=(T &)data;

	m_data.setSize(copy.getDataSize());

	gzSerializeAdapterMemory mem(m_data.getAddress(),m_data.getSize());

	copy.write(&mem);

	return *this;
}

//! Events generated from the gzDynamicTypeContainer
enum gzDynamicTypeEvent
{
	GZ_DYNAMIC_EVENT_REMOVE_ATTRIBUTE,
	GZ_DYNAMIC_EVENT_SET_ATTRIBUTE,
	GZ_DYNAMIC_EVENT_REMOVE_ALL_ATTRIBUTES,
	GZ_DYNAMIC_EVENT_ADD_USERDATA,				//!< Only valid for gzObject's gzUserData
	GZ_DYNAMIC_EVENT_REMOVE_USERDATA			//!< Only valid for gzObject's gzUserData
};

//******************************************************************************
// Class	: gzDynamicTypeContainer
//									
// Purpose  : A generic serializeable dictionary for gzDynamicTypes
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011026	Created 
//									
//******************************************************************************
//! A generic serializeable dictionary for gzDynamicTypes
/*! Use this contaner to store and look up dynamic values. You can iterate over the values
by using the gzDynamicTypeContainerIterator. By storing values like "adam:eve:util" you will 
be able to iterate over a subset of attributes. */
class gzDynamicTypeContainer : public gzSerializeData 
{
public:

	// Creation

	GZ_BASE_EXPORT gzDynamicTypeContainer(gzUInt32 hashsize=10);	// Lets default to size 10 (2.12.209)

	GZ_BASE_EXPORT virtual ~gzDynamicTypeContainer();

	GZ_BASE_EXPORT gzDynamicTypeContainer( const gzDynamicTypeContainer & copy);

	GZ_BASE_EXPORT gzDynamicTypeContainer & operator=(const gzDynamicTypeContainer & copy);

	// Attrib management

	GZ_BASE_EXPORT gzVoid setAttribute(const gzString &name , const gzDynamicType &attribute);

	GZ_BASE_EXPORT gzDynamicType getAttribute(const gzString &name,const gzDynamicType &missingDefault = GZ_DYN_MISSING) const;

	GZ_BASE_EXPORT gzBool hasAttribute(const gzString &name) const;

	GZ_BASE_EXPORT gzBool removeAttribute(const gzString &name);

	GZ_BASE_EXPORT gzVoid removeAllAttributes();

	GZ_BASE_EXPORT gzUInt32 getNumberOfAttributes() const;

	GZ_BASE_EXPORT virtual gzVoid onAttributeEvent( gzDynamicTypeEvent /*reason*/ , const gzString & /*name*/) {};

	GZ_BASE_EXPORT gzVoid clear() { removeAllAttributes(); }	// Added clear for convenience

	// serializing

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

	// dynamic info

	GZ_BASE_EXPORT static const gzString getDataTag() { return GZ_DYNAMIC_TYPE_CONTAINER; }

	GZ_BASE_EXPORT gzString asString(gzBool stripXML = TRUE, gzBool skipDynTag = TRUE, const gzString &tagName = GZ_SKIP_DYN_TAG);

private:

	friend class gzDynamicTypeContainerIterator;

	gzUInt32											m_hashSize;

	gzRefDict< gzString , gzRefData< gzDynamicType > > *m_dict;

};

//******************************************************************************
// Class	: gzDynamicTypeContainerIterator
//									
// Purpose  : Utility to iterator over a dynamic container
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011201	Created 
//									
//******************************************************************************
class gzDynamicTypeContainerIterator 
{
public:

	GZ_BASE_EXPORT	gzDynamicTypeContainerIterator(const gzDynamicTypeContainer &container , const gzString &prefix="");

	GZ_BASE_EXPORT	gzDynamicTypeContainerIterator(const gzDynamicTypeContainerIterator &copy);

	GZ_BASE_EXPORT	virtual ~gzDynamicTypeContainerIterator();

	GZ_BASE_EXPORT	gzDynamicType *operator()(gzString *name=nullptr);

	GZ_BASE_EXPORT	gzDynamicType *current();

	GZ_BASE_EXPORT	gzRefData< gzDynamicType > *currentItem();

	GZ_BASE_EXPORT	gzString currentName();

	GZ_BASE_EXPORT	gzVoid reset();

	GZ_BASE_EXPORT	gzVoid remove();

	GZ_BASE_EXPORT	gzVoid setPrefix(const gzString &prefix);

private:

	gzDynamicTypeContainer & m_owner;

	gzDictIterator<gzString , gzRefData< gzDynamicType > >	*m_iterator;

	gzString m_prefix;
};

typedef gzDynamicTypeCustom<gzDynamicTypeContainer> gzDynamicTypeContainerData;

// Error string for missing attribute exception
const gzString GZ_MISSING_ATTRIBUTE			= "Missing attribute '%s' in property";
const gzString GZ_FAIL_CONVERT_ATTRIBUTE	= "Failed to convert attribute '%s' in property";

// Container properties -------------------------------------------

#define GZ_CONT_PROPERTY(type, name) public: const type get##name() const { type val; if (hasAttribute(#name)) { if (gzDynamic_Cast<type>(getAttribute(#name), val)) return val; else gzThrowFatal(GZ_FAIL_CONVERT_ATTRIBUTE, #name); throw 0; } else { gzThrowFatal(GZ_MISSING_ATTRIBUTE, #name); throw 0; } } gzVoid set##name(const type& prop) { setAttribute(#name, gzDynamic_Cast<type>(prop)); }
#define GZ_CONT_PROPERTY_EXPORT(type, name, exportDef) public: exportDef const type get##name() const { type val; if (hasAttribute(#name)) { if (gzDynamic_Cast<type>(getAttribute(#name), val)) return val; else gzThrowFatal(GZ_FAIL_CONVERT_ATTRIBUTE, #name); throw 0; } else { gzThrowFatal(GZ_MISSING_ATTRIBUTE, #name); throw 0; } } exportDef gzVoid set##name(const type& prop) { setAttribute(#name, gzDynamic_Cast<type>(prop)); }

// Object properties ----------------------------------------------

#define GZ_OBJECT_PROPERTY(type, userdata,name)	public: gzBool has##name() const { return hasAttribute(#userdata, #name); } const type get##name() const { type val; if (hasAttribute(#userdata, #name)) { if (gzDynamic_Cast<type>(getAttribute(#userdata, #name), val)) return val; else gzThrowFatal(GZ_FAIL_CONVERT_ATTRIBUTE, #name); throw 0; } else { gzThrowFatal(GZ_MISSING_ATTRIBUTE, #name); throw 0; } } gzVoid set##name(const type& prop) { setAttribute(#userdata, #name, gzDynamic_Cast<type>(prop)); }
#define GZ_OBJECT_PROPERTY_EXPORT(type, userdata,name, exportDef) public: exportDef gzBool has##name() const { return hasAttribute(#userdata, #name); } exportDef const type get##name() const { type val; if (hasAttribute(#userdata, #name)) { if (gzDynamic_Cast<type>(getAttribute(#userdata, #name), val)) return val; else gzThrowFatal(GZ_FAIL_CONVERT_ATTRIBUTE, #name); throw 0; } else { gzThrowFatal(GZ_MISSING_ATTRIBUTE, #name); throw 0; } } exportDef gzVoid set##name(const type& prop) { setAttribute(#userdata, #name, gzDynamic_Cast<type>(prop)); }


//******************************************************************************
// Class	: gzDynamicClassInfo
//									
// Purpose  : A dynamic class that doesnt need to be instatiated by GZ_DECLARE_CHILD etc.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	180314	Created 
// AMO	210917	Changed to use thread safe reference to handle dealloc/alloc shared		(2.11.33)
//									
//******************************************************************************
class gzDynamicClassInfo : public gzThreadSafeReference
{
public:

	gzDynamicClassInfo(gzString className, gzType *parent) : m_className(className)
	{
		m_classType = new gzType(parent, m_className);
	}

	virtual ~gzDynamicClassInfo()
	{
		delete m_classType;
	}

	virtual gzType	*getType() const
	{
		return m_classType;
	}

	virtual	gzBool	useDeepCopy()
	{
		return FALSE;
	}

	gzUInt32 id()
	{
		return m_className.hash();
	}

private:

	gzType * m_classType;
	gzString	m_className;
};

GZ_DECLARE_REFPTR(gzDynamicClassInfo);

//******************************************************************************
// Class	: gzDynamicClass
//									
// Purpose  : A dynamic template class that doesnt need to be instatiated by GZ_DECLARE_CHILD etc.
//			  Typically used in factories when no static def is available
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	180314	Created 
//									
//******************************************************************************
template <class T> class gzDynamicClass : public T
{
public:

	gzDynamicClass(gzString className, gzType *parent) :m_classInfo(new gzDynamicClassInfo(className, parent))
	{

	}

	gzDynamicClass(gzString className, gzType *parent, const T& base) :T(base), m_classInfo(new gzDynamicClassInfo(className, parent))
	{

	}

	gzDynamicClass(gzString objectName,gzString className, gzType *parent) :T(objectName),m_classInfo(new gzDynamicClassInfo(className, parent))
	{

	}

	gzDynamicClass(gzString objectName, gzString className, gzType *parent, const T& base) :T(base), m_classInfo(new gzDynamicClassInfo(className, parent))
	{
		T::setName(objectName);
	}
		
	virtual ~gzDynamicClass()
	{

	}

	gzDynamicClass(gzString className) :m_classInfo(new gzDynamicClassInfo(className, T::getClassType()))
	{

	}

	gzUInt32 id()
	{
		return m_classInfo->id();
	}

	virtual gzType	*getType() const
	{
		return (gzType *)m_classInfo->getType();
	}

	virtual gzReference* clone() const
	{
		return new gzDynamicClass<T>(*this);
	}

private:

	gzDynamicClassInfoPtr m_classInfo;

};

// Dynamic caster utilities ---------------------------------------------------

//******************************************************************************
// Class	: gzDynamic_Cast<CastToClass>
//									
// Purpose  : Utility to do a checked dynamic cast of dynamic typed data
//									
// Notes	: Throws exception if not possible	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021201	Created 
//									
//******************************************************************************
template<class T> inline T gzDynamic_Cast(const gzDynamicType &data)
{
	return (T)(gzDynamicTypeCustom<T>)data;
}

//******************************************************************************
// Class	: gzDynamic_Cast<CastToClass>
//									
// Purpose  : Utility to do a checked dynamic cast of dynamic typed data
//									
// Notes	: returns TRUE if types matches
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021201	Created 
//									
//******************************************************************************
template<class T> inline gzBool gzDynamic_Cast(const gzDynamicType &data,T &result)
{
	if(data.is(T::getDataTag()))
	{
		result=(T)(gzDynamicTypeCustom<T>)data;
		return TRUE;
	}
	return FALSE;
}

// Special string cast of dynamic data

template <> inline gzString gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_STRING))
		return data.getString();

	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
		return gzString(data.getNumber());

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
		return gzString(gzDynamicTypeInt64(data).getInt64(),10);

	return data.asString();
}

template <> inline gzDouble gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
		return data.getNumber();

	if(data.is(GZ_DYNAMIC_TYPE_STRING))
		return data.getString().real();

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
		return (gzDouble)gzDynamicTypeInt64(data).getInt64();

	return 0.0;
}

template <> inline gzFloat gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
		return (gzFloat)data.getNumber();

	if(data.is(GZ_DYNAMIC_TYPE_STRING))
		return (gzFloat)data.getString().real();

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
		return (gzFloat)gzDynamicTypeInt64(data).getInt64();

	return 0.0f;
}

template <> inline gzUInt32 gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
		return (gzUInt32)data.getNumber();

	if(data.is(GZ_DYNAMIC_TYPE_STRING))
		return (gzUInt32)data.getString().num();

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
		return (gzUInt32)gzDynamicTypeInt64(data).getInt64();

	return 0;
}

template <> inline gzInt32 gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
		return (gzInt32)data.getNumber();

	if(data.is(GZ_DYNAMIC_TYPE_STRING))
		return (gzInt32)data.getString().num();

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
		return (gzInt32)gzDynamicTypeInt64(data).getInt64();

	return 0;
}

template <> inline gzBool gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
		return (gzBool)data.getNumber();

	if(data.is(GZ_DYNAMIC_TYPE_STRING))
		return data.getString().yesNo();

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
		return (gzBool)gzDynamicTypeInt64(data).getInt64();

	return FALSE;
}

template <> inline gzUInt16 gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
		return (gzUInt16)data.getNumber();

	if(data.is(GZ_DYNAMIC_TYPE_STRING))
		return (gzUInt16)data.getString().num();

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
		return (gzUInt16)gzDynamicTypeInt64(data).getInt64();

	return 0;
}

template <> inline gzInt16 gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
		return (gzInt16)data.getNumber();

	if(data.is(GZ_DYNAMIC_TYPE_STRING))
		return (gzInt16)data.getString().num();

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
		return (gzInt16)gzDynamicTypeInt64(data).getInt64();

	return 0;
}

template <> inline gzUInt64 gzDynamic_Cast(const gzDynamicType &data)
{
	if (data.is(GZ_DYNAMIC_TYPE_NUMBER))
		return (gzUInt64)data.getNumber();

	if (data.is(GZ_DYNAMIC_TYPE_STRING))
		return (gzUInt64)data.getString().num();

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
		return (gzUInt64)gzDynamicTypeInt64(data).getInt64();

	return 0;
}

template <> inline gzInt64 gzDynamic_Cast(const gzDynamicType &data)
{
	if (data.is(GZ_DYNAMIC_TYPE_NUMBER))
		return (gzInt64)data.getNumber();

	if (data.is(GZ_DYNAMIC_TYPE_STRING))
		return (gzInt64)data.getString().num();

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
		return (gzInt64)gzDynamicTypeInt64(data).getInt64();

	return 0;
}

template <> inline gzVec2 gzDynamic_Cast(const gzDynamicType &data)
{
	if (data.is(GZ_DYNAMIC_TYPE_VEC2))
		return data.getVec2();

	return GZ_ZERO_VEC2;
}

template <> inline gzVec3 gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_VEC3))
		return data.getVec3();

	return GZ_ZERO_VEC3;
}

template <> inline gzVec4 gzDynamic_Cast(const gzDynamicType &data)
{
	if (data.is(GZ_DYNAMIC_TYPE_VEC4))
		return data.getVec4();

	return GZ_ZERO_VEC4;
}

template <> inline gzVec2D gzDynamic_Cast(const gzDynamicType& data)
{
	if (data.is(GZ_DYNAMIC_TYPE_VEC2D))
		return data.getVec2D();

	return GZ_ZERO_VEC2D;
}

template <> inline gzVec3D gzDynamic_Cast(const gzDynamicType& data)
{
	if (data.is(GZ_DYNAMIC_TYPE_VEC3D))
		return data.getVec3D();

	return GZ_ZERO_VEC3D;
}

template <> inline gzVec4D gzDynamic_Cast(const gzDynamicType& data)
{
	if (data.is(GZ_DYNAMIC_TYPE_VEC4D))
		return data.getVec4D();

	return GZ_ZERO_VEC4D;
}

template <> inline gzQuaternion gzDynamic_Cast(const gzDynamicType& data)
{
	if (data.is(GZ_DYNAMIC_TYPE_QUAT))
		return data.getQuaternion();

	return GZ_ZERO_QUAT;
}


template <> inline gzReference * gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_REFERENCE))
		return data.getReference();

	return NULL;
}


template <> inline gzGUID gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_GUID))
		return data.getGUID();

	return gzGUID();
}

template <> inline gzDynamicTypeTimeTagged gzDynamic_Cast(const gzDynamicType &data)
{
	if (data.is(GZ_DYNAMIC_TYPE_TIME_TAGGED))
		return gzDynamicTypeTimeTagged(data);

	return gzDynamicTypeTimeTagged();
}

template <> inline gzDynamicTypeError gzDynamic_Cast(const gzDynamicType &data)
{
	if (data.is(GZ_DYNAMIC_TYPE_ERROR))
		return gzDynamicTypeError(data);

	return gzDynamicTypeError(GZ_DYNAMIC_ERROR_NO_ERROR);
}

template <> inline gzDynamicTypeArray gzDynamic_Cast(const gzDynamicType& data)
{
	if (data.is(GZ_DYNAMIC_TYPE_ARRAY))
		return gzDynamicTypeArray(data);

	return gzDynamicTypeArray();
}

template <> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzDynamicTypeError &result)
{
	if (data.is(GZ_DYNAMIC_TYPE_ERROR))
	{
		result = gzDynamicTypeError(data);
		return TRUE;
	}

	return FALSE;
}

// Special casts of bool results

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzString &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result=data.getString();
		return TRUE;
	}

	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result=data.getNumber();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
	{
		result = gzString(gzDynamicTypeInt64(data).getInt64(),10);
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_ERROR))
	{
		gzDynamicTypeError err(data);

		result = err.getError();

		return !err.isError();
	}

	result = data.asString();

	return TRUE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzDouble &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result=data.getNumber();
		return TRUE;
	}
	
	if (data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result = (gzDouble)data.getString().real();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
	{
		result = (gzDouble)gzDynamicTypeInt64(data).getInt64();
		return TRUE;
	}

	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzFloat &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result=(gzFloat)data.getNumber();
		return TRUE;
	}
	
	if (data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result = (gzFloat)data.getString().real();
		return TRUE;
	}

	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzUInt32 &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result=(gzUInt32)data.getNumber();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result = (gzUInt32)data.getString().num();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
	{
		result = (gzUInt32)gzDynamicTypeInt64(data).getInt64();
		return TRUE;
	}

	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzInt32 &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result=(gzInt32)data.getNumber();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result = (gzInt32)data.getString().num();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
	{
		result = (gzInt32)gzDynamicTypeInt64(data).getInt64();
		return TRUE;
	}

	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data, gzUInt64 &result)
{
	if (data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result = (gzUInt64)data.getNumber();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result = (gzUInt64)data.getString().num();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
	{
		result = (gzUInt64)gzDynamicTypeInt64(data).getInt64();
		return TRUE;
	}

	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data, gzInt64 &result)
{
	if (data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result = (gzInt64)data.getNumber();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result = (gzInt64)data.getString().num();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
	{
		result = (gzInt64)gzDynamicTypeInt64(data).getInt64();
		return TRUE;
	}

	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzUInt16 &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result=(gzUInt16)data.getNumber();
		return TRUE;
	}
	
	if (data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result = (gzUInt16)data.getString().num();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
	{
		result = (gzUInt16)gzDynamicTypeInt64(data).getInt64();
		return TRUE;
	}

	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzInt16 &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result=(gzInt16)data.getNumber();
		return TRUE;
	}
	
	if (data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result = (gzInt16)data.getString().num();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
	{
		result = (gzInt16)gzDynamicTypeInt64(data).getInt64();
		return TRUE;
	}

	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType& data, gzEnum& result)
{
	if (data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result = (gzEnum)data.getNumber();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result = (gzEnum)data.getString().num();
		return TRUE;
	}

	if (data.is(GZ_DYNAMIC_TYPE_INT64))
	{
		result = (gzEnum)gzDynamicTypeInt64(data).getInt64();
		return TRUE;
	}

	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzChar &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result=(gzChar)data.getNumber();
		return TRUE;
	}
	if (data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result = (gzChar)data.getString().num();
		return TRUE;
	}
	if (data.is(GZ_DYNAMIC_TYPE_INT64))
	{
		result = (gzChar)gzDynamicTypeInt64(data).getInt64();
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzUByte &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_NUMBER))
	{
		result=(gzUByte)data.getNumber();
		return TRUE;
	}
	if (data.is(GZ_DYNAMIC_TYPE_STRING))
	{
		result = (gzUByte)data.getString().num();
		return TRUE;
	}
	if (data.is(GZ_DYNAMIC_TYPE_INT64))
	{
		result = (gzUByte)gzDynamicTypeInt64(data).getInt64();
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzGUID &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_GUID))
	{
		result=data.getGUID();
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzVec2 &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_VEC2))
	{
		result=data.getVec2();
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzVec3 &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_VEC3))
	{
		result=data.getVec3();
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzVec4 &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_VEC4))
	{
		result=data.getVec4();
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType& data, gzVec2D& result)
{
	if (data.is(GZ_DYNAMIC_TYPE_VEC2D))
	{
		result = data.getVec2D();
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType& data, gzVec3D& result)
{
	if (data.is(GZ_DYNAMIC_TYPE_VEC3D))
	{
		result = data.getVec3D();
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType& data, gzVec4D& result)
{
	if (data.is(GZ_DYNAMIC_TYPE_VEC4D))
	{
		result = data.getVec4D();
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType& data, gzQuaternion& result)
{
	if (data.is(GZ_DYNAMIC_TYPE_QUAT))
	{
		result = data.getQuaternion();
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data, gzDynamicTypeTimeTagged &result)
{
	if (data.is(GZ_DYNAMIC_TYPE_TIME_TAGGED))
	{
		result = gzDynamicTypeTimeTagged(data);
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzArray<gzDynamicType> &result)
{
	if(data.is(GZ_DYNAMIC_TYPE_ARRAY))
	{
		result=gzDynamicTypeArray(data).getArray();
		return TRUE;
	}
	return FALSE;
}

template<> inline gzBool gzDynamic_Cast(const gzDynamicType& data, gzDynamicTypeArray& result)
{
	if (data.is(GZ_DYNAMIC_TYPE_ARRAY))
	{
		result = gzDynamicTypeArray(data);
		return TRUE;
	}
	return FALSE;
}

// Utiltiy macro to fix platform dependant method pointers

#if defined GZ_WINDOWS
	#define gzMethodPtr(x)  x
#else
	#define gzMethodPtr(x)  &x
#endif

//! Check function for dynamic attributes
GZ_BASE_EXPORT gzDynamicTypeError gzCheckDynamicArgumentList(GZ_DYNAMIC_ATTRIBUTE_TYPE_LIST_IMP,GZ_DYNAMIC_ATTRIBUTE_LIST_IMP);

#define DYN_ARG_CHECK(n)	if(t##n.length()){data->useArgTypeCheck=TRUE;data->argTypeCheck[n]=t##n;}

//******************************************************************************
// Class	: gzDynamicMethodChain<MyClass,BaseClass>
//									
// Purpose  : Add thread safe automatic command chain
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	031217	Created 
//									
//******************************************************************************
template <class T , class Base> class gzDynamicMethodChain : public Base
{
public:

	gzDynamicMethodChain():m_methodDict(100),m_throwArgumentFailException(FALSE){}

	virtual ~gzDynamicMethodChain()
	{
		GZ_BODYGUARD(m_locker);
		m_methodDict.clear();
	}

private:

	typedef gzDynamicType (T::* ThisPtr)(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP);

	class gzDynamicMethodChainData : public gzThreadSafeReference
	{
	public:

		gzDynamicMethodChainData():methodPointer(NULL),directMethodPointer(NULL),useArgTypeCheck(FALSE)
		{
		}

		virtual ~gzDynamicMethodChainData(){};

		gzString			IIDS_method;

		ThisPtr				methodPointer;

		gzDynamicMethod		directMethodPointer;

		gzString			argTypeCheck[10];

		gzString			description;

		gzBool				useArgTypeCheck;

		gzReference * clone() const
		{
			return (gzReference *)new gzDynamicMethodChainData(*this);
		}
	};


public:

	gzBool registerMethod(const gzUInt64 & IID_method,const gzString & IIDS_method ,ThisPtr methodPointer,gzBool replace=FALSE)
	{
		GZ_BODYGUARD(m_locker);

		gzDynamicMethodChainData *data=m_methodDict.find(IID_method);

		if(!data)
		{
			data=new gzDynamicMethodChainData;

			data->directMethodPointer=nullptr;

			m_methodDict.enter(IID_method,data);
		}
		else if(!replace)
			return FALSE;

		data->IIDS_method=IIDS_method;

		data->methodPointer=methodPointer;

		return TRUE;
	}

	gzVoid registerMethod(const gzString & IIDS_method ,ThisPtr methodPointer)
	{
		gzUInt64 IID=IIDS_method.hash();

		while(TRUE)
		{
			if(registerMethod(IID,IIDS_method,methodPointer))
				return;

			++IID;
		}
	}

	gzBool registerDescription(const gzUInt64 & IID_method,const gzString & description )
	{
		GZ_BODYGUARD(m_locker);

		gzDynamicMethodChainData *data=m_methodDict.find(IID_method);

		if(!data)
			return FALSE;

		data->description=description;

		return TRUE;
	}

	gzBool registerDescription(const gzString & IIDS_method ,const gzString &description)
	{
		gzUInt64 IID=getMethodIID(IIDS_method);

		if(IID==IID_NOT_SUPPORTED)
			return FALSE;

		return registerDescription(IID,description);
	}

	gzVoid throwArgumentFailException(gzBool throwIt)
	{
		m_throwArgumentFailException=throwIt;
	}

	gzVoid registerDirectMethod(const gzUInt64 & IID_method,gzDynamicMethod directMethodPointer)
	{
		GZ_BODYGUARD(m_locker);

		gzDynamicMethodChainData *data=m_methodDict.find(IID_method);

		if(!data)
		{
			data=new gzDynamicMethodChainData;

			data->IIDS_method=GZ_EMPTY_STRING;
			data->methodPointer=nullptr;

			m_methodDict.enter(IID_method,data);
		}

		data->directMethodPointer=directMethodPointer;
	}

	gzVoid setArgCheck(const gzString & IIDS_method,GZ_DYN_ARG_NULL(0),GZ_DYN_ARG_NULL(1),GZ_DYN_ARG_NULL(2),GZ_DYN_ARG_NULL(3),GZ_DYN_ARG_NULL(4),GZ_DYN_ARG_NULL(5),GZ_DYN_ARG_NULL(6),GZ_DYN_ARG_NULL(7),GZ_DYN_ARG_NULL(8),GZ_DYN_ARG_NULL(9))
	{
		GZ_BODYGUARD(m_locker);

		gzUInt64 IID_method=getMethodIID(IIDS_method);

		if(IID_method==IID_NOT_SUPPORTED)
			return;

		setArgCheck(IID_method,GZ_DYNAMIC_ATTRIBUTE_TYPE_LIST_IMP_FORWARD);
	}

	gzVoid setArgCheck(const gzUInt64 & IID_method,GZ_DYN_ARG_NULL(0),GZ_DYN_ARG_NULL(1),GZ_DYN_ARG_NULL(2),GZ_DYN_ARG_NULL(3),GZ_DYN_ARG_NULL(4),GZ_DYN_ARG_NULL(5),GZ_DYN_ARG_NULL(6),GZ_DYN_ARG_NULL(7),GZ_DYN_ARG_NULL(8),GZ_DYN_ARG_NULL(9))
	{
		GZ_BODYGUARD(m_locker);

		gzDynamicMethodChainData *data=m_methodDict.find(IID_method);

		if(!data)
			return;

		data->useArgTypeCheck=FALSE;

		DYN_ARG_CHECK(0);
		DYN_ARG_CHECK(1);
		DYN_ARG_CHECK(2);
		DYN_ARG_CHECK(3);
		DYN_ARG_CHECK(4);
		DYN_ARG_CHECK(5);
		DYN_ARG_CHECK(6);
		DYN_ARG_CHECK(7);
		DYN_ARG_CHECK(8);
		DYN_ARG_CHECK(9);
	}

	gzVoid unRegisterMethod(const gzUInt64 & IID_method)
	{
		GZ_BODYGUARD(m_locker); 

		m_methodDict.remove(IID_method);

	}

	virtual	gzDynamicType	invokeMethod(const gzString &IIDS_method,GZ_DYNAMIC_ATTRIBUTE_LIST)
	{
		gzUInt64 iid=getMethodIID(IIDS_method);

		return invokeMethod(iid,GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_FORWARD);
	}

	virtual gzString getMethodArgType(const gzString &IIDS_method, gzUInt32 index)
	{
		gzUInt64 iid = getMethodIID(IIDS_method);

		return getMethodArgType(iid,index);
	}

	virtual gzString getMethodArgType(gzUInt64 IID_method, gzUInt32 index)
	{
		if (index > 9)
			return "Index out of range (0-9)";

		m_locker.waitLock();

		gzRefPointer<gzDynamicMethodChainData> data = m_methodDict.find(IID_method);

		if (data)
		{
			m_locker.unLock();

			if (data->useArgTypeCheck)
				return data->argTypeCheck[index];
			else
				return GZ_DYNAMIC_TYPE_VOID;
		}

		m_locker.unLock();

		return GZ_DYNAMIC_TYPE_VOID;
	}

	// derived methods from gzDynamicInvokeInterface 
	virtual	gzDynamicType	invokeMethod(gzUInt64 IID_method,GZ_DYNAMIC_ATTRIBUTE_LIST)
	{
		m_locker.waitLock();

		gzRefPointer<gzDynamicMethodChainData> data=m_methodDict.find(IID_method);

		if(data)
		{
			m_locker.unLock();

			if(data->useArgTypeCheck)
			{
				gzDynamicTypeError error=gzCheckDynamicArgumentList(data->argTypeCheck[0],
																	data->argTypeCheck[1],
																	data->argTypeCheck[2],
																	data->argTypeCheck[3],
																	data->argTypeCheck[4],
																	data->argTypeCheck[5],
																	data->argTypeCheck[6],
																	data->argTypeCheck[7],
																	data->argTypeCheck[8],
																	data->argTypeCheck[9],
																	GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_FORWARD);

				if(error.isError())
				{
					if(m_throwArgumentFailException)
						gzThrowWarning((const char *)error.getError());

					return error;
				}
			}

			gzDynamicType result=(((T*)this)->*data->methodPointer)(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_FORWARD);

			if(result.is(GZ_DYNAMIC_TYPE_CHAIN))
				return Base::invokeMethod(IID_method,GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_FORWARD);
			else
				return result;
		}

		m_locker.unLock();

		return Base::invokeMethod(IID_method,GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_FORWARD);
	}

	virtual	gzBool supportMethod(gzUInt64 IID_method)
	{
		m_locker.waitLock();

		gzRefPointer<gzDynamicMethodChainData> data=m_methodDict.find(IID_method);

		m_locker.unLock();

		if(data)
			if(data->methodPointer)
				return TRUE;

		return Base::supportMethod(IID_method);
	}

	virtual	gzString getDescription(gzUInt64 IID_method)
	{
		m_locker.waitLock();

		gzRefPointer<gzDynamicMethodChainData> data=m_methodDict.find(IID_method);

		m_locker.unLock();

		if(data)
			return data->description;

		return Base::getDescription(IID_method);
	}

	virtual	gzUInt64 getMethodIID(const gzString &IIDS_method)
	{
		{
			GZ_BODYGUARD(m_locker);
			
			gzDictIterator<gzUInt64CompareInterface,gzDynamicMethodChainData> iterator(m_methodDict);
			gzDictEntry<gzUInt64CompareInterface,gzDynamicMethodChainData> *entry;

			while((entry=iterator()))
			{
				if(entry->getData()->IIDS_method==IIDS_method)
					return entry->getKey().getValue();
			}
		}

		return Base::getMethodIID(IIDS_method);
	}

	virtual	gzDynamicMethod getDirectMethod(gzUInt64 IID_method)
	{
		m_locker.waitLock();

		gzRefPointer<gzDynamicMethodChainData> data=m_methodDict.find(IID_method);

		m_locker.unLock();

		if(data)
			if(data->directMethodPointer)
				return data->directMethodPointer;

		return Base::getDirectMethod(IID_method);
	}

	virtual	gzArray<gzDynamicMethodID> queryAllMethodIID()
	{
		gzArray<gzDynamicMethodID> baseArray=Base::queryAllMethodIID();

		m_locker.waitLock();

		gzArray<gzDynamicMethodID> localArray(m_methodDict.entries());

		gzDynamicMethodID *methodData=localArray.getAddress();

		gzDictIterator<gzUInt64CompareInterface,gzDynamicMethodChainData> iterator(m_methodDict);
		gzDictEntry<gzUInt64CompareInterface,gzDynamicMethodChainData> *entry;

		while((entry=iterator()))
		{
			methodData->IID_method=entry->getKey().getValue();
			methodData->IIDS_method=entry->getData()->IIDS_method;
			methodData->method=entry->getData()->directMethodPointer;
			methodData->description=entry->getData()->description;

			for(gzUInt32 i=0;i<10;i++)
				methodData->argTypeCheck[i]=entry->getData()->argTypeCheck[i];

			++methodData;
		}
		
		m_locker.unLock();

		return baseArray+localArray;
	}

private:

	gzRefDict<gzUInt64CompareInterface,gzDynamicMethodChainData>		m_methodDict;

	gzMutex																m_locker;

	gzBool																m_throwArgumentFailException;

};

// ------------------------------- serializers ------------------------------------------

template <> inline gzVoid writeAdapter(gzSerializeAdapter *adapter, const gzDynamicType &data,const gzBool /*useBigEndian*/)
{
	((gzDynamicType &)data).write(adapter);
}

template <> inline gzVoid pushBackAdapter(gzSerializeAdapter *adapter, const gzDynamicType &data,const gzBool /*useBigEndian*/)
{
	((gzDynamicType &)data).pushBack(adapter);
}

template <> inline gzBool readAdapter(gzSerializeAdapter *adapter, gzDynamicType &data,const gzBool /*useBigEndian*/)
{
	data.read(adapter);
	return TRUE;
}

template <> inline gzUInt32 getDataSize( gzSerializeAdapter *adapter , const gzDynamicType &data,const gzBool /*useBigEndian*/)
{
	return data.getDataSize(adapter);
}

// Template based dynamic type caster ------------------------------------

template<class T> inline gzDynamicType gzDynamic_Cast(const T &data)
{
	return gzDynamicType(data);
}

template<> inline gzDynamicType gzDynamic_Cast(const gzInt64 &data)
{
	return gzDynamicTypeInt64(data);
}

template<> inline gzDynamicType gzDynamic_Cast(const gzUInt64 &data)
{
	return gzDynamicTypeInt64((gzInt64)data);
}

template<> inline gzDynamicType gzDynamic_Cast(const gzArray<gzDynamicType> &data)
{
	return gzDynamicTypeArray(data);
}

template<> inline gzDynamicType gzDynamic_Cast(const gzDynamicArray<gzDynamicType> &data)
{
	return gzDynamicTypeArray(data);
}

template<> inline gzDynamicType gzDynamic_Cast(const gzDynamicTypeContainer &data)
{
	return gzDynamicTypeCustom<gzDynamicTypeContainer>(data);
}

// Define default enum unpack 
#define GZ_DECLARE_DYNAMIC_ENUM(type) template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data, type &result){if (data.is(GZ_DYNAMIC_TYPE_NUMBER)){result = (type)(gzUInt32)data.getNumber();return TRUE;}else if (data.is(GZ_DYNAMIC_TYPE_INT64)){result = (type)(gzUInt32)gzDynamicTypeInt64(data).getInt64();return TRUE;}else if (data.is(GZ_DYNAMIC_TYPE_STRING)){result = (type)(gzUInt32)data.getString().num();}return FALSE;}

#define GZ_DECLARE_DYNAMIC_ENUM_64(type) template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data, type &result){if (data.is(GZ_DYNAMIC_TYPE_NUMBER)){result = (type)(gzUInt64)data.getNumber();return TRUE;}else if (data.is(GZ_DYNAMIC_TYPE_INT64)){result = (type)gzDynamicTypeInt64(data).getInt64();return TRUE;}else if (data.is(GZ_DYNAMIC_TYPE_STRING)){result = (type)(gzUInt64)data.getString().num();}return FALSE;}template<> inline gzDynamicType gzDynamic_Cast(const type & data){	return gzDynamicTypeInt64(data);}


// Define default custom Cast functions
#define GZ_DECLARE_DYNAMIC_CUSTOM_TYPE(type) template<> inline gzDynamicType gzDynamic_Cast(const type &data){return gzDynamicTypeCustom<type>(data);}

// Define default array
#define GZ_DECLARE_DYNAMIC_ARRAY(theClass) template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,theClass &result) { if(data.is(GZ_DYNAMIC_TYPE_ARRAY)) { ((gzArray<gzDynamicType> &)result)=gzDynamicTypeArray(data).getArray(); return TRUE; } return FALSE; } template<> inline gzDynamicType gzDynamic_Cast(const theClass &data) { return gzDynamicTypeArray(data); }

// Define default container
#define GZ_DECLARE_DYNAMIC_CONTAINER(theClass) template<> inline gzDynamicType gzDynamic_Cast(const theClass &data) { return gzDynamicTypeCustom<gzDynamicTypeContainer>(data); } 

// Defaine default nativ to custom pack/unpack
#define GZ_DECLARE_DYNAMIC_CUSTOM_TYPE_NATIVE(custom_type,native_type) template<> inline gzDynamicType gzDynamic_Cast(const native_type &data){return gzDynamicTypeCustom<custom_type>(data);}
#define GZ_DECLARE_DYNAMIC_CUSTOM_TYPE_NATIVE_UNPACK(custom_type,native_type) template<> inline gzBool gzDynamic_Cast<native_type>(const gzDynamicType &data, native_type &dest) { custom_type custom; if (gzDynamic_Cast(data, custom)){ dest = custom; return TRUE;} return FALSE;}


// XML type conversions --------------------------------------------------

GZ_BASE_EXPORT gzVoid gzDynamicType2Xml(const gzDynamicType &data, gzDynamicArray<gzUByte> &retdata, gzBool wideChar = FALSE, gzBool skipDynTag = FALSE, const gzString &tagName=GZ_SKIP_DYN_TAG);

GZ_BASE_EXPORT gzDynamicType gzXml2DynamicType(const gzArray<gzUByte> &xml, gzBool *gotData = NULL, gzBool skipDynTag = FALSE);
GZ_BASE_EXPORT gzDynamicType gzXml2DynamicType(const gzChar *string, gzUInt32 length, gzBool *gotData = NULL, gzBool skipDynTag = FALSE);
GZ_BASE_EXPORT gzDynamicType gzXml2DynamicType(const gzWideChar *string, gzUInt32 length, gzBool *gotData = NULL, gzBool skipDynTag = FALSE);

// ----- Dynamic Type utilites for XY and XYZ pairs ---------------------------

template <class T> class gzSerializeXY : public gzXY<T>
{
public:

	gzSerializeXY(const gzXY<T> &right=gzXY<T>(0,0)):gzXY<T>(right)
	{
	}

	gzVoid write(gzSerializeAdapter *adapter)
	{
		writeAdapter(adapter,*this);
	}

	gzVoid read(gzSerializeAdapter *adapter)
	{
		readAdapter(adapter,*this);
	}

	gzVoid pushBack(gzSerializeAdapter *adapter)
	{
		pushBackAdapter(adapter,*this);
	}

	gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const
	{
		return ::getDataSize(adapter,*this);
	}
};


#define GZ_DECLARE_XY_SERIALIZER(type) class gzSerialize##type##XY : public gzSerializeXY<gz##type>{public:gzSerialize##type##XY(const gz##type##XY &right=gz##type##XY(0,0)):gzSerializeXY<gz##type>(right){}static gzString getDataTag(){return gzString::checkUnique(#type "XY");}}; template<> inline gzDynamicType gzDynamic_Cast(const gz##type##XY &data){return gzDynamicTypeCustom<gzSerialize##type##XY>(gzSerialize##type##XY(data));} template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gz##type##XY &result){if(data.is(gzSerialize##type##XY::getDataTag())){result=(gzSerialize##type##XY)(gzDynamicTypeCustom<gzSerialize##type##XY>)data;return TRUE;}return FALSE;}

GZ_DECLARE_XY_SERIALIZER(UInt32);
GZ_DECLARE_XY_SERIALIZER(Int32);
GZ_DECLARE_XY_SERIALIZER(Float);
GZ_DECLARE_XY_SERIALIZER(Double);

GZ_DECLARE_XY_SERIALIZER(UInt16);
GZ_DECLARE_XY_SERIALIZER(Int16);

template <class T> class gzSerializeXYZ : public gzXYZ<T>
{
public:

	gzSerializeXYZ(const gzXYZ<T> &right=gzXYZ<T>(0,0)):gzXYZ<T>(right)
	{
	}

	gzVoid write(gzSerializeAdapter *adapter)
	{
		writeAdapter(adapter,*this);
	}

	gzVoid read(gzSerializeAdapter *adapter)
	{
		readAdapter(adapter,*this);
	}

	gzVoid pushBack(gzSerializeAdapter *adapter)
	{
		pushBackAdapter(adapter,*this);
	}

	gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const
	{
		return ::getDataSize(adapter,*this);
	}
};

#define GZ_DECLARE_XYZ_SERIALIZER(type) class gzSerialize##type##XYZ : public gzSerializeXYZ<gz##type>{public:gzSerialize##type##XYZ(const gz##type##XYZ &right=gz##type##XYZ(0,0,0)):gzSerializeXYZ<gz##type>(right){}static gzString getDataTag(){return gzString::checkUnique(#type "XYZ");}}; template<> inline gzDynamicType gzDynamic_Cast(const gz##type##XYZ &data){return gzDynamicTypeCustom<gzSerialize##type##XYZ>(gzSerialize##type##XYZ(data));} template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gz##type##XYZ &result){if(data.is(gzSerialize##type##XYZ::getDataTag())){result=(gzSerialize##type##XYZ)(gzDynamicTypeCustom<gzSerialize##type##XYZ>)data;return TRUE;}return FALSE;}

GZ_DECLARE_XYZ_SERIALIZER(UInt32);
GZ_DECLARE_XYZ_SERIALIZER(Int32);
GZ_DECLARE_XYZ_SERIALIZER(Float);
GZ_DECLARE_XYZ_SERIALIZER(Double);
GZ_DECLARE_XYZ_SERIALIZER(UInt16);
GZ_DECLARE_XYZ_SERIALIZER(Int16);

// --------------------------------------- Array of data ----------------------------------------------

template <class T> class gzSerializeArrayData : public gzArray<T>
{
public:

	gzSerializeArrayData(const gzArray<T> &right = gzArray<T>()) : gzArray<T>(right)
	{
	}

	gzVoid write(gzSerializeAdapter *adapter)
	{
		writeAdapter(adapter, (gzArray<T> &)*this);
	}

	gzVoid read(gzSerializeAdapter *adapter)
	{
		readAdapter(adapter, (gzArray<T> &)*this);
	}

	gzVoid pushBack(gzSerializeAdapter *adapter)
	{
		pushBackAdapter(adapter, (gzArray<T> &)*this);
	}

	gzUInt32	getDataSize(gzSerializeAdapter *adapter = NULL) const
	{
		return ::getDataSize(adapter, (gzArray<T> &)*this);
	}
};

#define GZ_DECLARE_ARRAY_SERIALIZER(type) class gzSerialize##type##Array : public gzSerializeArrayData<gz##type>{public:gzSerialize##type##Array(const gzArray<gz##type> &right=gzArray<gz##type>()):gzSerializeArrayData<gz##type>(right){}static gzString getDataTag(){return  gzString::checkUnique(#type "Array");}}; template<> inline gzDynamicType gzDynamic_Cast(const gzArray<gz##type> &data){return gzDynamicTypeCustom<gzSerialize##type##Array>(gzSerialize##type##Array(data));} template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzArray<gz##type> &result){if(data.is(gzSerialize##type##Array::getDataTag())){result=(gzSerialize##type##Array)(gzDynamicTypeCustom<gzSerialize##type##Array>)data;return TRUE;}return FALSE;}
#define GZ_DECLARE_ARRAY_SERIALIZER_EXTERN(type) class gzSerialize##type##Array : public gzSerializeArrayData<type>{public:gzSerialize##type##Array(const gzArray<type> &right=gzArray<type>()):gzSerializeArrayData<type>(right){}static gzString getDataTag(){return  gzString::checkUnique(#type "Array");}}; template<> inline gzDynamicType gzDynamic_Cast(const gzArray<type> &data){return gzDynamicTypeCustom<gzSerialize##type##Array>(gzSerialize##type##Array(data));} template<> inline gzBool gzDynamic_Cast(const gzDynamicType &data,gzArray<type> &result){if(data.is(gzSerialize##type##Array::getDataTag())){result=(gzSerialize##type##Array)(gzDynamicTypeCustom<gzSerialize##type##Array>)data;return TRUE;}return FALSE;}

// Create array serializers for a number of custom types
GZ_DECLARE_ARRAY_SERIALIZER(UByte);
GZ_DECLARE_ARRAY_SERIALIZER(Int32);
GZ_DECLARE_ARRAY_SERIALIZER(UInt32);
GZ_DECLARE_ARRAY_SERIALIZER(Float);
GZ_DECLARE_ARRAY_SERIALIZER(FloatXY);
GZ_DECLARE_ARRAY_SERIALIZER(FloatXYZ);

GZ_DECLARE_ARRAY_SERIALIZER(Vec2);
GZ_DECLARE_ARRAY_SERIALIZER(Vec3);
GZ_DECLARE_ARRAY_SERIALIZER(Vec4);

// Create custom native casts for above types
GZ_DECLARE_DYNAMIC_CUSTOM_TYPE(gzSerializeUByteArray);
GZ_DECLARE_DYNAMIC_CUSTOM_TYPE(gzSerializeInt32Array);
GZ_DECLARE_DYNAMIC_CUSTOM_TYPE(gzSerializeUInt32Array);
GZ_DECLARE_DYNAMIC_CUSTOM_TYPE(gzSerializeFloatArray);
GZ_DECLARE_DYNAMIC_CUSTOM_TYPE(gzSerializeFloatXYArray);
GZ_DECLARE_DYNAMIC_CUSTOM_TYPE(gzSerializeFloatXYZArray);

GZ_DECLARE_DYNAMIC_CUSTOM_TYPE(gzSerializeVec2Array);
GZ_DECLARE_DYNAMIC_CUSTOM_TYPE(gzSerializeVec3Array);
GZ_DECLARE_DYNAMIC_CUSTOM_TYPE(gzSerializeVec4Array);



enum gzStreamEncoding
{
	GZ_STREAM_NO_ENCODING		= 0,
	GZ_STREAM_ENCODE			= 1<<0,
	GZ_STREAM_DECODE			= 1<<1,
	GZ_STREAM_DUPLEX_ENCODING	= GZ_STREAM_ENCODE| GZ_STREAM_DECODE,
};

GZ_USE_BIT_LOGIC(gzStreamEncoding);

// Custom encoder control
GZ_BASE_EXPORT gzVoid gzSetTimeTagEncodeInfo(gzSerializeAdapter *adapter, gzStreamEncoding encoding = GZ_STREAM_DUPLEX_ENCODING, gzDouble precision = 0.001, gzDouble encodeStartTimeTagValue = 0.0);


#endif // __GZ_DYNAMIC_H__
