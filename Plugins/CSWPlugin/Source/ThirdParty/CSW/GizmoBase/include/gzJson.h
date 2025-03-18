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
// File			: gzJSON.h
// Module		: gzBase
// Description	: Class definition of JSON parser and utils
// Author		: Anders Modén
// Product		: GizmoBase 2.12.231
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
// AMO	180419	Created file											(2.9.1)
//
// ******************************************************************************

#ifndef __GZ_JSON_H__
#define __GZ_JSON_H__

#include "gzLex.h"
#include "gzObject.h"



//******************************************************************************
// Class	: gzJSON
//									
// Purpose  : Basic parser for JSON syntax
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	180419	Created (2.9.1)
//									
//******************************************************************************
class gzJSON : public gzBasicParser , public gzSerializeData , public gzTypeInterface
{
public:

	GZ_BASE_EXPORT gzJSON(gzUInt32 chunkSize=1000);
	GZ_BASE_EXPORT virtual ~gzJSON();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT virtual gzVoid	write(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzVoid	read(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzVoid	pushBack(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

	GZ_BASE_EXPORT gzDynamicType	getData();
	GZ_BASE_EXPORT gzVoid			setData(const gzDynamicType &data);

	GZ_PROPERTY_EXPORT(gzBool, Formatted, GZ_BASE_EXPORT);

protected:

	gzParseResult parseDocument();				// document ::= value* 
	gzParseResult parseObject();				// object	::= '{' member* '}'
	gzParseResult parseMember();				// member	::= pair ( ',' member )?
	gzParseResult parsePair();					// pair		::= string ':' value
	gzParseResult parseArray();					// array	::= '[' element* ']'
	gzParseResult parseElement();				// element	::= value (',' element)?
	gzParseResult parseValue();					// value	::= (string|number|object|array|true|false|null)
	gzParseResult parseString();				// string	::= '"' [^"]* '"'

	gzVoid writeDynamic(const gzDynamicType & data, gzSerializeAdapter *adapter, gzUInt16 level = 0);

private:
		
	gzString			m_currentString;
	gzArray<gzUByte>	m_currentStringArray;

	gzDynamicType		m_currentValue;
	gzUInt16			m_currentLevel;

	gzDynamicArray<gzDynamicTypeContainer>			m_currentObject;
	gzDynamicArray<gzDynamicArray<gzDynamicType> >	m_currentArray;

	gzDynamicArray<gzDynamicType>					m_results;

	gzBool			m_firstWrite;
};



#endif //__GZ_JSON_H__
