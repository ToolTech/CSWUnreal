//******************************************************************************
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
// File			: gzHashUtils.h
// Module		: gzBase
// Description	: Utility file to handle hash comparing etc..
// Author		: Anders Modén		
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
// AMO	010315	Created file 
// AMO	251004	Updated hash patterns to use gzGetHash			(2.12.274)
//
//******************************************************************************

#ifndef __GZ_HASH_UTILS_H__
#define __GZ_HASH_UTILS_H__

/*!	\file 
	\brief Basic utilites for hash compare management
	
*/

#include "gzBasicTypes.h"

//******************************************************************************
// Class	: gzInstanceCompareInterface
//									
// Purpose  : Class to enable comparison of instances 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981122	Created 
//									
//******************************************************************************

/*! \brief Provides a base interface for instance comparing using hash values

Derive your class from this inteface to get the hash() function. Your class can then
be used by templates like gzDict etc. that requires the hash() comparing method.
*/

class  GZ_BASE_EXPORT gzInstanceCompareInterface
{
public:

	//! Default constructor, Creates unique instance hash value 
	gzInstanceCompareInterface() { m_address = this; }

	//! Generic constructor, Creates unique instance hash value from your supplied address
	gzInstanceCompareInterface(const gzVoid* address) { m_address = address; }

	//! returns the hash value of your instance
	gzUInt32 hash() const { return (gzUInt32)gzPtr2Val(m_address); }

	//! returns the instance address
	const gzVoid* getInstance() const { return m_address; }

	//! equality operator
	gzBool operator ==(const gzInstanceCompareInterface& right) const
	{
		return (m_address == right.m_address);
	}

private:

	const gzVoid* m_address;

};

//******************************************************************************
// Template	: gzGetHash<T>
//									
// Purpose  : Template to enable hash function of <T> values 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	251002	Created 
//									
//******************************************************************************
template <class K> inline gzUInt32 gzGetHash(const K & k)
{
	// Retunerar defalt hash value through the hash() method of the class
	return k.hash();
}

// ------------------- Special hash values ----------------------------------

template <> inline gzUInt32 gzGetHash(const gzUInt16& k){ return (gzUInt32)k; }
template <> inline gzUInt32 gzGetHash(const gzUInt32& k){ return (gzUInt32)k; }
template <> inline gzUInt32 gzGetHash(const gzInt32& k) { return (gzUInt32)k; }
template <> inline gzUInt32 gzGetHash(const gzUInt64& k){ return (gzUInt32)(k & 0xffffffff) + (gzUInt32)((k >> 32) & 0xffffffff); }
template <> inline gzUInt32 gzGetHash(const gzInt64& k) { return (gzUInt32)(k & 0xffffffff) + (gzUInt32)((k >> 32) & 0xffffffff); }
template <> inline gzUInt32 gzGetHash(const gzDouble& k){ return (gzUInt32)((*(gzInt64*)&k) & 0xffffffff) + (gzUInt32)(((*(gzInt64*)&k) >> 32) & 0xffffffff); }
template <> inline gzUInt32 gzGetHash(const gzFloat& k) { return *(gzUInt32*)&k; }

#endif // __GZ_HASH_UTILS_H__

