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
// File			: gzXML.h
// Module		: gzBase
// Description	: Class definition of XML parser and utils
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
// AMO	050527	Created file
// AMO	090820	Added management for standard Entity References			(2.4.8)
// AMO	100616	Added attribute name in gzXmlElement::getNextAttribute	(2.5.10)
//
// ******************************************************************************

#ifndef __GZ_XML_H__
#define __GZ_XML_H__

#include "gzLex.h"
#include "gzObject.h"



#define XML_READ_RULE(n)	GZ_BASE_EXPORT gzParseResult XML_read_##n()
#define XML_READ_RULE_10	XML_READ_RULE(01);XML_READ_RULE(02);XML_READ_RULE(03);XML_READ_RULE(04);XML_READ_RULE(05);XML_READ_RULE(06);XML_READ_RULE(07);XML_READ_RULE(08);XML_READ_RULE(09);XML_READ_RULE(10);
#define XML_READ_RULE_20	XML_READ_RULE(11);XML_READ_RULE(12);XML_READ_RULE(13);XML_READ_RULE(14);XML_READ_RULE(15);XML_READ_RULE(16);XML_READ_RULE(17);XML_READ_RULE(18);XML_READ_RULE(19);XML_READ_RULE(20);
#define XML_READ_RULE_30	XML_READ_RULE(21);XML_READ_RULE(22);XML_READ_RULE(23);XML_READ_RULE(24);XML_READ_RULE(25);XML_READ_RULE(26);XML_READ_RULE(27);XML_READ_RULE(28);XML_READ_RULE(29);XML_READ_RULE(30);
#define XML_READ_RULE_40	XML_READ_RULE(31);XML_READ_RULE(32);XML_READ_RULE(33);XML_READ_RULE(34);XML_READ_RULE(35);XML_READ_RULE(36);XML_READ_RULE(37);XML_READ_RULE(38);XML_READ_RULE(39);XML_READ_RULE(40);
#define XML_READ_RULE_50	XML_READ_RULE(41);XML_READ_RULE(42);XML_READ_RULE(43);XML_READ_RULE(45);XML_READ_RULE(46);XML_READ_RULE(47);XML_READ_RULE(48);XML_READ_RULE(49);XML_READ_RULE(50);
#define XML_READ_RULE_60	XML_READ_RULE(51);XML_READ_RULE(52);XML_READ_RULE(53);XML_READ_RULE(54);XML_READ_RULE(55);XML_READ_RULE(56);XML_READ_RULE(57);XML_READ_RULE(58);XML_READ_RULE(59);XML_READ_RULE(60);
#define XML_READ_RULE_70	XML_READ_RULE(61);XML_READ_RULE(62);XML_READ_RULE(63);XML_READ_RULE(64);XML_READ_RULE(65);XML_READ_RULE(66);XML_READ_RULE(67);XML_READ_RULE(68);XML_READ_RULE(69);XML_READ_RULE(70);
#define XML_READ_RULE_80	XML_READ_RULE(71);XML_READ_RULE(72);XML_READ_RULE(73);XML_READ_RULE(74);XML_READ_RULE(75);XML_READ_RULE(76);XML_READ_RULE(77);XML_READ_RULE(78);XML_READ_RULE(79);XML_READ_RULE(80);
#define XML_READ_RULE_90	XML_READ_RULE(81);XML_READ_RULE(82);XML_READ_RULE(83);XML_READ_RULE(84);XML_READ_RULE(85);XML_READ_RULE(86);XML_READ_RULE(87);XML_READ_RULE(88);XML_READ_RULE(89);XML_READ_RULE(90);
#define XML_READ_RULE_100	XML_READ_RULE(91);XML_READ_RULE(92);XML_READ_RULE(93);
#define XML_READ_RULES		XML_READ_RULE_10 XML_READ_RULE_20 XML_READ_RULE_30 XML_READ_RULE_40	XML_READ_RULE_50 XML_READ_RULE_60 XML_READ_RULE_70 XML_READ_RULE_80 XML_READ_RULE_90 XML_READ_RULE_100


enum gzXmlItemType
{
	XML_ITEM_ELEMENT				=	1<<0,
	XML_ITEM_ELEMENT_CONTENTS		=	1<<1,
	XML_ITEM_ATTRIBUTE				=	1<<2,
	XML_ITEM_ELEMENT_ATTRIBUTE_END	=	1<<3,
	XML_ITEM_HEADER					=	1<<4,
	XML_ITEM_CHAR_DATA				=	1<<5,
	XML_ITEM_CDATA					=	1<<6,
	XML_ITEM_COMMENT				=	1<<7,
	XML_ITEM_PI						=	1<<8,
	XML_ITEM_ENTITY_REFERENCE		=	1<<9,
	XML_ITEM_ELEMENT_CONTENTS_START	=	1<<10,
	XML_ITEM_ELEMENT_CONTENTS_END	=	1<<11,
	XML_ITEM_DEFAULT				=	XML_ITEM_ELEMENT|XML_ITEM_ATTRIBUTE|XML_ITEM_HEADER|XML_ITEM_CHAR_DATA|XML_ITEM_CDATA|XML_ITEM_COMMENT|XML_ITEM_PI|XML_ITEM_ENTITY_REFERENCE
};

enum gzXmlWriteState
{
	XML_WRITE_STATE_IDLE,
	XML_WRITE_STATE_DTD,
	XML_WRITE_STATE_ELEMENT,
	XML_WRITE_STATE_ELEMENT_CONTENTS,
	XML_WRITE_STATE_ELEMENT_START,
	XML_WRITE_STATE_ELEMENT_END,
	XML_WRITE_STATE_ATTRIBUTE,
};

GZ_USE_BIT_LOGIC(gzXmlItemType);	// So you can combine types

const gzString	GZ_DYNAMIC_TYPE		="gzDyn";
const gzString	GZ_OBJECT			="gzObj";
const gzString	GZ_ARRAY_ITEM_NAME	="item";

const gzString	GZ_BASE_TYPE	="type";
const gzString	GZ_BASE_NAME	="name";
const gzString	GZ_BASE_INDEX	="index";
const gzString	GZ_BASE_SIZE	="size";
const gzString	GZ_BASE_TIME	="time";

const gzString	GZ_BASE_64		="b64";
const gzString	GZ_BASE_HEX		="hex";
const gzString	GZ_BASE_ENCODING="encoding";


class gzXmlDynamicTypeInterface;	// Forward decl
class gzXmlObjectInterface;			// Forward decl
class gzXmlCustomDataInterface;		// Forward decl

// Some defined PIs
const gzString XML_PI_INCLUDE			= "include";
const gzString XML_PI_CHECKSUM			= "checksum";

// Some other predefined keywords
const gzString XML_KEYWORD_FUNCTION		= "function:";

//******************************************************************************
// Class	: gzXmlSax
//									
// Purpose  : Basic SAX callback interface for XML parser 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class gzXmlSax : public gzBasicParser , public gzSerializeData , public gzTypeInterface
{
public:

	GZ_BASE_EXPORT gzXmlSax();
	GZ_BASE_EXPORT virtual ~gzXmlSax();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT virtual gzVoid	write(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzVoid	read(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzVoid	pushBack(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const override;

	// Dynamic Type custom parsers
	GZ_BASE_EXPORT static gzBool	registerDynamicTypeInterface(const gzString &typeName , gzXmlDynamicTypeInterface *iface, gzBool replace=FALSE);
	GZ_BASE_EXPORT static gzVoid	unregisterDynamicTypeInterface(gzXmlDynamicTypeInterface *iface);
	GZ_BASE_EXPORT static gzXmlDynamicTypeInterface *getDynamicTypeInterface(const gzString &type=GZ_EMPTY_STRING);

	// Object custom parsers
	GZ_BASE_EXPORT static gzBool	registerObjectInterface(const gzString &typeName , gzXmlObjectInterface *iface, gzBool replace = FALSE);
	GZ_BASE_EXPORT static gzVoid	unregisterObjectInterface(gzXmlObjectInterface *iface);
	GZ_BASE_EXPORT static gzXmlObjectInterface *getObjectInterface(const gzString &typeName);

	// Custom data parsers
	GZ_BASE_EXPORT static gzBool	registerCustomDataInterface(const gzString &typeName , gzXmlCustomDataInterface *iface, gzBool replace = FALSE);
	GZ_BASE_EXPORT static gzVoid	unregisterCustomDataInterface(gzXmlCustomDataInterface *iface);
	GZ_BASE_EXPORT static gzXmlCustomDataInterface *getCustomDataInterface(const gzString &typeName);


	// Control notifications
	GZ_BASE_EXPORT gzVoid	enableNotifyItemType(gzXmlItemType types=XML_ITEM_DEFAULT);
	GZ_BASE_EXPORT gzVoid	disableNotifyItemType(gzXmlItemType types);

	GZ_BASE_EXPORT gzBool	isNotifyingItemType(gzXmlItemType type);

	GZ_BASE_EXPORT gzXmlItemType getNotifyItemTypes();
	GZ_BASE_EXPORT gzVoid setNotifyItemTypes(gzXmlItemType types);
	GZ_BASE_EXPORT gzBool enableNotifying(gzBool on = TRUE);

	// Get some properties
	GZ_BASE_EXPORT const gzString &	getVersion();
	GZ_BASE_EXPORT const gzString &	getEncoding();
	GZ_BASE_EXPORT gzBool			isStandalone();
	GZ_BASE_EXPORT gzBool			isPlainOutput();

	// Set some properties
	GZ_BASE_EXPORT gzVoid	setVersion(const gzString &version);
	GZ_BASE_EXPORT gzVoid	setEncoding(const gzString &encoding);
	GZ_BASE_EXPORT gzVoid	setStandalone(gzBool standalone);
	GZ_BASE_EXPORT gzVoid	setPlainOutput(gzBool plain);


	// Virtual callbacks for SAX alike parsing

	// Header part
	GZ_BASE_EXPORT virtual	gzBool onVersion(const gzString & /*version*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onEncoding(const gzString & /*encoding*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onStandalone(gzBool /*standalone*/) {return TRUE;}

	// Element part
	GZ_BASE_EXPORT virtual	gzBool onElementStart(const gzString & /*elementName*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onElementAttributeEnd(const gzString & /*elementName*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onElementContents(const gzString & /*elementName*/,const gzString & /*contents*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onElementContentsStart(const gzString & /*elementName*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onElementContentsEnd(const gzString & /*elementName*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onElementEnd(const gzString & /*elementName*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onAttribute(const gzString & /*attributeName*/,const gzString & /*attributeValue*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onCharData(const gzString & /*charData*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onEntityReference(const gzString & /*name*/,gzUInt32 /*level*/,gzBool /*inAttribute*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onProcessingInstruction(const gzString & /*target*/,const gzString & /*data*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onCDATA(const gzString & /*CDATA*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onComment(const gzString & /*comment*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onDynamicType(const gzDynamicType & /*data*/,const gzString & /*name*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onObject(gzObject * /*object*/,const gzString & /*name*/,gzUInt32 /*level*/) {return TRUE;}
	GZ_BASE_EXPORT virtual	gzBool onCustomData(gzReference * /*data*/,const gzString & /*elementName*/,gzUInt32 /*level*/) {return TRUE;}

	GZ_BASE_EXPORT virtual	gzString onFunction(const gzString &function,gzUInt32 level);
	
	// Virtual callbacks for Writing

	GZ_BASE_EXPORT virtual	gzVoid	onWrite(){};

	// Write Control

	GZ_BASE_EXPORT	gzVoid	writeXmlHeader();
	GZ_BASE_EXPORT	gzVoid	writeElementStart(const gzString &elementName);
	GZ_BASE_EXPORT	gzVoid	writeAttribute(const gzString &attributeName,const gzString &attributeValue);
	GZ_BASE_EXPORT	gzVoid	writeElementEnd();
	GZ_BASE_EXPORT	gzVoid	writeCharData(const gzString &charData);
	GZ_BASE_EXPORT	gzVoid	writeEntityReference(const gzString &name);
	GZ_BASE_EXPORT	gzVoid	writePI(const gzString &target,const gzString &data);
	GZ_BASE_EXPORT	gzVoid	writeCDATA(const gzString &CDATA);
	GZ_BASE_EXPORT	gzVoid	writeDynamicType(const gzDynamicType &data,const gzString &attribName=GZ_EMPTY_STRING,const gzString &elementTag=GZ_DYNAMIC_TYPE);
	GZ_BASE_EXPORT	gzVoid	writeObject(const gzObject *object,const gzString &objectName=GZ_EMPTY_STRING,const gzString &elementTag=GZ_OBJECT);
	GZ_BASE_EXPORT	gzVoid	writeComment(const gzString &comment);
	GZ_BASE_EXPORT	gzVoid	writeCustomData(const gzString &elementName,const gzReference *data,gzBool newElement=TRUE);
	GZ_BASE_EXPORT	gzVoid	writeCharDataElement(const gzString &elementName,const gzString &elementData);

	GZ_BASE_EXPORT	gzVoid	writeGenericString(const gzString &string);

	// Utilities for parsing
	
	XML_READ_RULES;

	// Additional Parse utilities

	GZ_BASE_EXPORT gzParseResult XML_read_Test_ETag();

	// Control

	GZ_BASE_EXPORT	gzVoid	beginElementContents();

	GZ_BASE_EXPORT	gzBool	useBase64();
	GZ_BASE_EXPORT	gzVoid	useBase64(gzBool on);

	GZ_BASE_EXPORT	gzBool	useDynOnly();
	GZ_BASE_EXPORT	gzVoid	useDynOnly(gzBool on);

	GZ_BASE_EXPORT gzUInt32										getCurrentElementLevel();

	GZ_BASE_EXPORT gzString										getCurrentAttribute(const gzString &attributeName);
	GZ_BASE_EXPORT gzBool										hasCurrentAttribute(const gzString &attributeName);
	GZ_BASE_EXPORT gzString										getCurrentElementName();
	GZ_BASE_EXPORT gzRefDict<gzString,gzRefData<gzString> >		getCurrentAttributeSet();

	GZ_BASE_EXPORT gzString										getAttribute(gzUInt32 level,const gzString &attributeName);
	GZ_BASE_EXPORT gzBool										hasAttribute(gzUInt32 level,const gzString &attributeName);
	GZ_BASE_EXPORT gzString										getElementName(gzUInt32 level);
	GZ_BASE_EXPORT gzRefDict<gzString,gzRefData<gzString> >		getAttributeSet(gzUInt32 level);

private:

	gzString	getItemStartString(gzUInt32 level);

	// Current values
	gzDynamicArray<gzString>	m_currentElement;
	gzString					m_currentVersion;
	gzString					m_currentEncoding;
	
	gzXmlItemType				m_notifyTypes;

	gzUInt32					m_elementLevel;

	gzBool						m_isStandalone:1;
	gzBool						m_gotBase64Attribute:1;
	gzBool						m_gotHexAttribute:1;
	gzBool						m_useBase64:1;
	gzBool						m_useDynOnly : 1;
	gzBool						m_plainOutput:1;

	gzBool						m_inAttribute:1;
	gzBool						m_isNotifying:1;

	gzXmlWriteState				m_state;

	gzDynamicArray<gzRefDict<gzString,gzRefData<gzString> > >	m_currentAttributes;

	static gzMutex												s_ifaceLocker;
	static gzRefDict<gzString,gzXmlDynamicTypeInterface>		s_dynamicTypeInterfaces;
	static gzRefDict<gzString,gzXmlObjectInterface>				s_objectInterfaces;
	static gzRefDict<gzString,gzXmlCustomDataInterface>			s_customDataInterfaces;

	friend class CleanUpXml;
};

const gzDebugFlags GZ_DEBUG_XML_HIERARCHY	=(gzDebugFlags)(1<<0);
const gzDebugFlags GZ_DEBUG_XML_ATTRIBUTES	=(gzDebugFlags)(1<<1);
const gzDebugFlags GZ_DEBUG_XML_CHAR_DATA	=(gzDebugFlags)(1<<2);
const gzDebugFlags GZ_DEBUG_XML_CDATA		=(gzDebugFlags)(1<<3);
const gzDebugFlags GZ_DEBUG_XML_PI_DATA		=(gzDebugFlags)(1<<4);

enum gzXmlStringFlags
{
	GZ_XML_STRING_FLAG_SHOW_TYPE = 1 << 0,
	GZ_XML_STRING_FLAG_SHOW_NAME = 1 << 1,
	GZ_XML_STRING_FLAG_SHOW_ATTRIBUTES = 1 << 2,
	GZ_XML_STRING_FLAG_SHOW_RECURSIVE = 1 << 3,
	GZ_XML_STRING_FLAG_SHOW_HIERARCHY = 1 << 4,
	GZ_XML_STRING_FLAG_SHOW_DECORATED_VALUE = 1 << 5,
	GZ_XML_STRING_FLAG_SHOW_CHAR_DATA = 1 << 6,
	GZ_XML_STRING_FLAG_SHOW_CDATA = 1 << 7,
	GZ_XML_STRING_FLAG_SHOW_ENTITY_REF = 1 << 8,
	GZ_XML_STRING_FLAG_SHOW_PI = 1 << 9,
	GZ_XML_STRING_FLAG_SHOW_COMMENT = 1 << 10,
	GZ_XML_STRING_FLAG_SHOW_DYNAMIC_DATA = 1 << 11,
	GZ_XML_STRING_FLAG_SHOW_OBJECT = 1 << 12,
	GZ_XML_STRING_FLAG_SHOW_CUSTOM = 1 << 13,
	GZ_XML_STRING_FLAG_SHOW_ALL = GZ_XML_STRING_FLAG_SHOW_RECURSIVE| GZ_XML_STRING_FLAG_SHOW_CHAR_DATA,
};

GZ_USE_BIT_LOGIC(gzXmlStringFlags);

//******************************************************************************
// Class	: gzXmlItem
//									
// Purpose  : Base item class 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class gzXmlItem : public gzReference , public gzNameInterface , public gzDebugInterface
{
public:
	GZ_BASE_EXPORT gzXmlItem(const gzString &name);
	GZ_BASE_EXPORT gzXmlItem(const gzXmlItem &copy);
	GZ_BASE_EXPORT virtual ~gzXmlItem();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI
	
	GZ_BASE_EXPORT gzVoid addChild(gzXmlItem *child);
	GZ_BASE_EXPORT gzVoid removeChild(gzXmlItem *child);
	GZ_BASE_EXPORT gzVoid removeChildren();
	
	GZ_BASE_EXPORT gzXmlItem *	getParent();
	GZ_BASE_EXPORT gzXmlItem *	getNextChild();
	GZ_BASE_EXPORT gzVoid		resetChildIterator();
	GZ_BASE_EXPORT gzVoid		resetAllChildIterators();
	GZ_BASE_EXPORT gzUInt32		childEntries() const;

	GZ_BASE_EXPORT virtual gzVoid write(gzXmlSax *writer);
	
	//! A XPath alike query to find the first matching item e.g. "nisse/hult/<char_data>"
	GZ_BASE_EXPORT virtual gzXmlItem *findItem(const gzString &path);

	// Add a item at path location
	GZ_BASE_EXPORT virtual gzVoid addItem(const gzString &path,gzXmlItem *item);

	GZ_BASE_EXPORT virtual gzUInt32 indexEvalExpression(const gzString &item,const gzString &expression);

	//! Merges in standard references into text data
	GZ_BASE_EXPORT gzVoid mergeStandardReferencesAndText();

	// -------------- gzDebugInterface ----------------------------------
	GZ_BASE_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;
	GZ_BASE_EXPORT virtual	gzVoid	debugOutputTraverse(gzString base , gzString anchor , gzDebugFlags features) override;

	// ------------- asString simillar to debug but as a string --------
	GZ_BASE_EXPORT virtual gzString asString(gzXmlStringFlags flags = GZ_XML_STRING_FLAG_SHOW_ALL);

private:
	
	gzXmlItem *					m_parent;
	gzRefList<gzXmlItem>		m_childList;
	gzListIterator<gzXmlItem>	m_iterator;
};

GZ_DECLARE_REFPTR(gzXmlItem);

//******************************************************************************
// Class	: gzXmlAttribute
//
// Purpose  : Internal attribute class
//
//******************************************************************************

class gzXmlAttribute : public gzReference
{
public:
	gzXmlAttribute(const gzString& name, const gzString& value) : name(name), value(value){}

	gzString name;
	gzString value;
};

//******************************************************************************
// Class	: gzXmlElement
//									
// Purpose  : Element item class 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class gzXmlElement : public gzXmlItem
{
public:
	GZ_BASE_EXPORT gzXmlElement(const gzString &name);
	GZ_BASE_EXPORT virtual ~gzXmlElement();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzVoid			setAttribute(const gzString &name, const gzString &value, ARG_DECL_LIST);
	GZ_BASE_EXPORT const gzString&	getAttribute(const gzString &name, const gzString &defaultValue = GZ_EMPTY_STRING) const;
	GZ_BASE_EXPORT gzBool			hasAttribute(const gzString &name) const;
	GZ_BASE_EXPORT gzVoid			removeAttribute(const gzString &name);

	GZ_BASE_EXPORT gzBool getNextAttribute(gzString &name, gzString &data);
	GZ_BASE_EXPORT gzVoid resetAttributeIterator();
	GZ_BASE_EXPORT gzRefList<gzXmlAttribute>& getAttributeList();

	GZ_BASE_EXPORT virtual gzVoid write(gzXmlSax *writer) override;

	// -------------- gzDebugInterface ----------------------------------
	GZ_BASE_EXPORT virtual	gzVoid	debugOutput(gzString base, gzString anchor, gzDebugFlags features) override;

	// ------------- asString simillar to debug but as a string --------
	GZ_BASE_EXPORT virtual gzString asString(gzXmlStringFlags flags = GZ_XML_STRING_FLAG_SHOW_ALL) override;

private:

	gzRefList<gzXmlAttribute> m_attributes;
	gzListIterator<gzXmlAttribute> m_iterator;
};

GZ_DECLARE_REFPTR(gzXmlElement);

//******************************************************************************
// Class	: gzXmlCharData
//									
// Purpose  : Char Data item class 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class gzXmlCharData : public gzXmlItem
{
public:
	GZ_BASE_EXPORT gzXmlCharData();
	GZ_BASE_EXPORT virtual ~gzXmlCharData();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT	gzVoid				setCharData(const gzString &data);
	GZ_BASE_EXPORT	const gzString &	getCharData();

	GZ_BASE_EXPORT virtual gzVoid write(gzXmlSax *writer) override;

	// -------------- gzDebugInterface ----------------------------------
	GZ_BASE_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ------------- asString simillar to debug but as a string --------
	GZ_BASE_EXPORT virtual gzString asString(gzXmlStringFlags flags = GZ_XML_STRING_FLAG_SHOW_ALL) override;

private:

	gzString	m_charData;
};

GZ_DECLARE_REFPTR(gzXmlCharData);

//******************************************************************************
// Class	: gzXmlEntityReference
//									
// Purpose  : Store entity ref data 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	090820	Created 
//									
//******************************************************************************
class gzXmlEntityReference : public gzXmlItem
{
public:
	GZ_BASE_EXPORT gzXmlEntityReference();
	GZ_BASE_EXPORT virtual ~gzXmlEntityReference();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_PROPERTY_EXPORT(gzString	,		Name,		GZ_BASE_EXPORT);

	GZ_BASE_EXPORT virtual gzVoid write(gzXmlSax *writer) override;

	// -------------- gzDebugInterface ----------------------------------
	GZ_BASE_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ------------- asString simillar to debug but as a string --------
	GZ_BASE_EXPORT virtual gzString asString(gzXmlStringFlags flags = GZ_XML_STRING_FLAG_SHOW_ALL) override;

};

GZ_DECLARE_REFPTR(gzXmlEntityReference);

//******************************************************************************
// Class	: gzXmlPI
//									
// Purpose  : Processing Instruction (PI) item class 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	071120	Created 
//									
//******************************************************************************
class gzXmlPI : public gzXmlItem
{
public:
	GZ_BASE_EXPORT gzXmlPI();
	GZ_BASE_EXPORT virtual ~gzXmlPI();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT	gzVoid				setTarget(const gzString &target);
	GZ_BASE_EXPORT	const gzString &	getTarget();

	GZ_BASE_EXPORT	gzVoid				setData(const gzString &data);
	GZ_BASE_EXPORT	const gzString &	getData();

	GZ_BASE_EXPORT virtual gzVoid write(gzXmlSax *writer) override;

	// -------------- gzDebugInterface ----------------------------------
	GZ_BASE_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ------------- asString simillar to debug but as a string --------
	GZ_BASE_EXPORT virtual gzString asString(gzXmlStringFlags flags = GZ_XML_STRING_FLAG_SHOW_ALL) override;

private:

	gzString	m_target;
	gzString	m_data;
};

GZ_DECLARE_REFPTR(gzXmlPI);

//******************************************************************************
// Class	: gzXmlCDATA
//									
// Purpose  : CDATA item class 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class gzXmlCDATA : public gzXmlItem
{
public:
	GZ_BASE_EXPORT gzXmlCDATA();
	GZ_BASE_EXPORT virtual ~gzXmlCDATA();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT	gzVoid				setCDATA(const gzString &data);
	GZ_BASE_EXPORT	const gzString &	getCDATA();

	GZ_BASE_EXPORT virtual gzVoid write(gzXmlSax *writer) override;

	// -------------- gzDebugInterface ----------------------------------
	GZ_BASE_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ------------- asString simillar to debug but as a string --------
	GZ_BASE_EXPORT virtual gzString asString(gzXmlStringFlags flags = GZ_XML_STRING_FLAG_SHOW_ALL) override;

private:

	gzString	m_CDATA;
};

GZ_DECLARE_REFPTR(gzXmlCDATA);

//******************************************************************************
// Class	: gzXmlComment
//									
// Purpose  : Comment item class 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class gzXmlComment : public gzXmlItem
{
public:
	GZ_BASE_EXPORT gzXmlComment();
	GZ_BASE_EXPORT virtual ~gzXmlComment();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT	gzVoid				setComment(const gzString &data);
	GZ_BASE_EXPORT	const gzString &	getComment();

	GZ_BASE_EXPORT virtual gzVoid write(gzXmlSax *writer) override;

	// -------------- gzDebugInterface ----------------------------------
	GZ_BASE_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ------------- asString simillar to debug but as a string --------
	GZ_BASE_EXPORT virtual gzString asString(gzXmlStringFlags flags = GZ_XML_STRING_FLAG_SHOW_ALL) override;

private:

	gzString	m_comment;
};

GZ_DECLARE_REFPTR(gzXmlComment);

//******************************************************************************
// Class	: gzXmlDynamicType
//									
// Purpose  : gzDynamicType item class 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class gzXmlDynamicType : public gzXmlItem
{
public:
	GZ_BASE_EXPORT gzXmlDynamicType(const gzString &name);
	GZ_BASE_EXPORT virtual ~gzXmlDynamicType();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT	gzVoid					setDynamicType(const gzDynamicType &data);
	GZ_BASE_EXPORT	const gzDynamicType &	getDynamicType();

	GZ_BASE_EXPORT virtual gzVoid write(gzXmlSax *writer) override;

	// -------------- gzDebugInterface ----------------------------------
	GZ_BASE_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ------------- asString simillar to debug but as a string --------
	GZ_BASE_EXPORT virtual gzString asString(gzXmlStringFlags flags = GZ_XML_STRING_FLAG_SHOW_ALL) override;

private:

	gzDynamicType	m_data;
};

GZ_DECLARE_REFPTR(gzXmlDynamicType);

//******************************************************************************
// Class	: gzXmlObject
//									
// Purpose  : gzObject item class 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class gzXmlObject : public gzXmlItem
{
public:
	GZ_BASE_EXPORT gzXmlObject(const gzString &name);
	GZ_BASE_EXPORT virtual ~gzXmlObject();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT	gzVoid		setObject(gzObject *object);
	GZ_BASE_EXPORT	gzObject *	getObject();

	GZ_BASE_EXPORT virtual gzVoid write(gzXmlSax *writer) override;

	// -------------- gzDebugInterface ----------------------------------
	GZ_BASE_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ------------- asString simillar to debug but as a string --------
	GZ_BASE_EXPORT virtual gzString asString(gzXmlStringFlags flags = GZ_XML_STRING_FLAG_SHOW_ALL) override;

private:

	gzRefPointer<gzObject>	m_object;
};

GZ_DECLARE_REFPTR(gzXmlObject);

//******************************************************************************
// Class	: gzXmlCustomData
//									
// Purpose  : gzReference custom item class 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	070108	Created 
//									
//******************************************************************************
class gzXmlCustomData : public gzXmlElement
{
public:
	GZ_BASE_EXPORT gzXmlCustomData(const gzString &name);
	GZ_BASE_EXPORT gzXmlCustomData(const gzXmlElement &copy);
	GZ_BASE_EXPORT virtual ~gzXmlCustomData();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_PROPERTY_EXPORT(gzRefPointer<gzReference>,	Data,			GZ_BASE_EXPORT);

	GZ_BASE_EXPORT virtual gzVoid write(gzXmlSax *writer) override;

	// -------------- gzDebugInterface ----------------------------------
	GZ_BASE_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// ------------- asString simillar to debug but as a string --------
	GZ_BASE_EXPORT virtual gzString asString(gzXmlStringFlags flags = GZ_XML_STRING_FLAG_SHOW_ALL) override;
};

GZ_DECLARE_REFPTR(gzXmlCustomData);


//******************************************************************************
// Class	: gzXmlDom
//									
// Purpose  : Basic object model for Gizmo XML parser 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class gzXmlDom : public gzXmlSax , public gzXmlItem
{
public:

	GZ_BASE_EXPORT	gzXmlDom();
	GZ_BASE_EXPORT	virtual ~gzXmlDom();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI
	
	GZ_BASE_EXPORT virtual gzVoid	write(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzVoid	read(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzVoid	pushBack(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const override;
	
	// Header part
	GZ_BASE_EXPORT virtual	gzBool onVersion(const gzString &version) override;
	GZ_BASE_EXPORT virtual	gzBool onEncoding(const gzString &encoding) override;
	GZ_BASE_EXPORT virtual	gzBool onStandalone(gzBool standalone) override;

	// Element part
	GZ_BASE_EXPORT virtual	gzBool onElementStart(const gzString &elementName,gzUInt32 level) override;
	GZ_BASE_EXPORT virtual	gzBool onElementContents(const gzString &elementName,const gzString &contents,gzUInt32 level) override;
	GZ_BASE_EXPORT virtual	gzBool onElementEnd(const gzString &elementName,gzUInt32 level) override;
	GZ_BASE_EXPORT virtual	gzBool onAttribute(const gzString &attributeName,const gzString &attributeValue,gzUInt32 level) override;
	GZ_BASE_EXPORT virtual	gzBool onCharData(const gzString &charData,gzUInt32 level) override;
	GZ_BASE_EXPORT virtual	gzBool onEntityReference(const gzString &charData,gzUInt32 level,gzBool inAttribute) override;
	GZ_BASE_EXPORT virtual	gzBool onCDATA(const gzString &CDATA,gzUInt32 level) override;
	GZ_BASE_EXPORT virtual	gzBool onProcessingInstruction(const gzString &target,const gzString &data,gzUInt32 level) override;
	GZ_BASE_EXPORT virtual	gzBool onComment(const gzString &comment,gzUInt32 level) override;
	GZ_BASE_EXPORT virtual	gzBool onDynamicType(const gzDynamicType &data,const gzString &name,gzUInt32 level) override;
	GZ_BASE_EXPORT virtual	gzBool onObject(gzObject *object,const gzString &name,gzUInt32 level) override;
	GZ_BASE_EXPORT virtual	gzBool onCustomData(gzReference *data,const gzString &elementName,gzUInt32 level) override;

	GZ_BASE_EXPORT gzUInt32 getCheckSum() const;
	GZ_BASE_EXPORT gzBool setValidCheckSum(gzUInt32 checkSum);
	GZ_BASE_EXPORT gzBool hasValidCheckSum();

	GZ_PROPERTY_EXPORT(gzBool,		SkipWhiteSpaceCharData,		GZ_BASE_EXPORT);	//!< Default:TRUE
	GZ_PROPERTY_EXPORT(gzBool,		WriteIncludedXml,			GZ_BASE_EXPORT);	//!< Default:FALSE
	GZ_PROPERTY_EXPORT(gzBool,		ReadIncludedXml,			GZ_BASE_EXPORT);	//!< Default:TRUE
	GZ_PROPERTY_EXPORT(gzBool,		MergeStandardReferences,	GZ_BASE_EXPORT);	//!< Default:TRUE
	
	// Virtual callbacks for Writing

	GZ_BASE_EXPORT virtual	gzVoid	onWrite() override;
	GZ_BASE_EXPORT virtual	gzVoid	write(gzXmlSax *writer) override;

private:

	gzDynamicArray<gzRefPointer<gzXmlItem> >	m_itemStack;

	gzUInt32									m_checkSum;

};

GZ_DECLARE_REFPTR(gzXmlDom);

//******************************************************************************
// Class	: gzXMLDomIterator
//									
// Purpose  : Iterator class for gzXmlDom
//									
// Notes	: A line-for-line iterator for gzXmlDom. Iterates from current
//			  position in the document.
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// CAN	080519	Created 
//									
//******************************************************************************
class gzXMLDomIterator
{
	public:
		GZ_BASE_EXPORT gzXMLDomIterator(gzXmlDom& dom);
		
		GZ_BASE_EXPORT virtual ~gzXMLDomIterator();
		
		GZ_BASE_EXPORT gzXmlItem* operator()();		

		GZ_BASE_EXPORT gzVoid remove();	

		//! Return the parent path
		GZ_BASE_EXPORT gzString getContext();

		//! return the complete path to the item
		GZ_BASE_EXPORT gzString getContextName();

	private:

		gzXmlDom*	m_dom;
		gzXmlItem*	m_current;
		gzString	m_context;
};

//******************************************************************************
// Class	: gzXmlDynamicTypeInterface
//									
// Purpose  : Base class for dynamic type parsers 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzXmlDynamicTypeInterface : public gzReference
{
public:
	gzXmlDynamicTypeInterface(){};
	virtual ~gzXmlDynamicTypeInterface(){};

	virtual gzParseResult	read(gzXmlSax *sax,const gzString &type,gzDynamicType &value)=0;

	virtual gzVoid			write(gzXmlSax *sax,const gzDynamicType &data)=0;

	virtual gzUInt32		getDataSize(gzXmlSax *sax,const gzDynamicType &data) const=0;
};

GZ_DECLARE_REFPTR(gzXmlDynamicTypeInterface);

//******************************************************************************
// Class	: gzXmlObjectInterface
//									
// Purpose  : Base class for object parsers 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzXmlObjectInterface : public gzReference
{
public:
	gzXmlObjectInterface(){};
	virtual ~gzXmlObjectInterface(){};

	virtual gzParseResult	read(gzXmlSax *sax,const gzString &type,gzRefPointer<gzObject> &value)=0;

	virtual gzVoid			write(gzXmlSax *sax,const gzObject *object)=0;

	virtual gzUInt32		getDataSize(gzXmlSax *sax,const gzObject *object) const=0;
};

GZ_DECLARE_REFPTR(gzXmlObjectInterface);

//******************************************************************************
// Class	: gzXmlCustomDataInterface
//									
// Purpose  : Base class for element parsers 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050108	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzXmlCustomDataInterface : public gzReference
{
public:
	
	gzXmlCustomDataInterface();
	virtual ~gzXmlCustomDataInterface();

	virtual gzParseResult	read(gzXmlSax *sax,gzRefPointer<gzReference> &value)=0;
	virtual gzVoid			write(gzXmlSax *sax,const gzReference *data)=0;
};

GZ_DECLARE_REFPTR(gzXmlCustomDataInterface);


const gzString GZ_XML_NAME_CHAR_DATA			=	"<char_data>";
const gzString GZ_XML_NAME_CDATA				=	"<cdata>";
const gzString GZ_XML_NAME_COMMENT				=	"<comment>";
const gzString GZ_XML_NAME_PI					=	"<pi>";
const gzString GZ_XML_NAME_ENTITY_REFERENCE		=	"<entity_ref>";

#endif //__GZ_XML_H__
