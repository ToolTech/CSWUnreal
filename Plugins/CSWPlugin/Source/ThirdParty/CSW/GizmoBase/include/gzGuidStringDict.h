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
// File			: gzGuidStringDict.h
// Module		: gzBase
// Description	: Class definition of GUID - String dictionary classes
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
// AMO	121130	Created file 										(2.6.18)
//
// ******************************************************************************

#ifndef __GZ_GUID_STRING_DICT_H__
#define __GZ_GUID_STRING_DICT_H__

/*!	\file 
	\brief GUID String dictionary lookup

A fast way to cross refrence unique string lookups

*/

#include "gzSerialize.h"

class gzGuidStringDict :	public gzReference,
							public gzSerializeData
{
public:
	
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);

	GZ_BASE_EXPORT gzGuidStringDict();

	GZ_BASE_EXPORT virtual ~gzGuidStringDict();

	// ------------- local methods ----------------

	GZ_BASE_EXPORT gzVoid	enter(const gzGUID &guid,const gzString &string);

	GZ_BASE_EXPORT gzString find(const gzGUID &guid);

	GZ_BASE_EXPORT gzUInt32 entries() const;

	// ------------- Serializing ------------------

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const  override;

	// -------------- Properties ----------------------

	GZ_PROPERTY_MUTEX_EXPORT(gzString,	Prefix,		m_threadSafeLocker,		GZ_BASE_EXPORT);
	GZ_PROPERTY_MUTEX_EXPORT(gzString,	Postfix,	m_threadSafeLocker,		GZ_BASE_EXPORT);
	
	// -------------- global methods --------------

	GZ_BASE_EXPORT static gzVoid addDictionary(gzGuidStringDict *dict);

	GZ_BASE_EXPORT static gzVoid removeDictionary(gzGuidStringDict *dict);

	GZ_BASE_EXPORT static gzString lookup(const gzGUID &guid);

	// ------- Thread safe ref -------------------

	GZ_THREADSAFE_REF(m_threadSafeLocker);

protected:

	gzMutex									m_threadSafeLocker;

	gzRefDict<gzGUID,gzRefData<gzString> >	m_dictionary;

	// ----------------- globals ----------------------

	static gzMutex							s_locker;

	static gzRefList<gzGuidStringDict>		s_list;

};

GZ_DECLARE_REFPTR(gzGuidStringDict);

#endif //__GZ_GUID_STRING_DICT_H__
