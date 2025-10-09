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
// File			: gzType.h
// Module		: gzBase
// Description	: Class definition of type info utilities
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
// AMO	980915	Created file 	
//
//******************************************************************************
#ifndef __GZ_TYPE_H__
#define __GZ_TYPE_H__

/*!	\file 
	\brief Run Time Type Info (RTTI) implementation

Gizmo3D uses the gzTypeInterface to query a certain object of its type. It can also manage hierarchical 
inheritance not nessecary the same as the C++ inheritance.

You should use it like this.
\code

class MyClass : public gzTypeInterface
{
public:
	MyClass(){};			// or whatever

	virtual ~MyClass(){};	// or whatever


	GZ_DECLARE_TYPE_INTERFACE;	// This is IMPORTANT
};

\endcode

You Should also in the implementation file write this.

\code

GZ_DECLARE_TYPE_BASE(gzMyClass,"MyClassName");

// or if you have derived it from another class

GZ_DECLARE_TYPE_CHILD(MyParentClass,MyClass,"MyClassName");

\endcode
*/

#include "gzBasicTypes.h"

const gzUInt32 GZ_TYPE_MAX_NAME_LEN=100;

#define GZ_DECLARE_TYPE_INTERFACE_EXPORT(exporter)	exporter static gzType s_type;\
													exporter static gzType *getClassType() { return &s_type; }\
													exporter virtual gzType *getType() const override { return getClassType(); }

#define GZ_DECLARE_TYPE_INTERFACE_EXPORT_(exporter)	exporter static gzType s_type;\
													exporter static gzType *getClassType() { return &s_type; }\
													exporter virtual gzType *getType() const { return getClassType(); }

#define GZ_DECLARE_TYPE_INTERFACE	static gzType s_type;\
									static gzType *getClassType() { return &s_type; }\
									virtual gzType *getType() const override { return getClassType(); }

#define GZ_DECLARE_TYPE_INTERFACE_	static gzType s_type;\
									static gzType *getClassType() { return &s_type; }\
									virtual gzType *getType() const { return getClassType(); }

#define GZ_DECLARE_TYPE_BASE(base,name) gzType base::s_type(0,name)

#define GZ_DECLARE_TYPE_CHILD(parent,child,name) gzType child::s_type(&parent::s_type,name)
		
//******************************************************************************
// Class	: gzType
//									
// Purpose  : Run Time Type Information 
//									
// Notes	: RTTI can be supported on various compilers but this provides a generic
//			  interface.	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created 
//									
//******************************************************************************
class  GZ_BASE_EXPORT gzType
{
public:
	gzType(gzType *parent, const char *name );
	gzType(const gzType &right );
	gzType &operator=(const gzType &right );
	virtual ~gzType();

	const char *getName() const;

	gzType *getParent() const;

	gzBool isDerivedFrom(gzType *ancestor) const;

	gzUInt32	hash() const;

	inline gzBool operator==(const gzType &type)
	{
		return (m_name==type.m_name);
	}


private:

	gzType	*m_parent;
	char	*m_name; 
	gzBool	m_created;

};

//! Type definition pointer
typedef gzType * gzTypePtr;


//******************************************************************************
// Class	: gzTypeInterface
//									
// Purpose  : Interface functions for RTTI 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzTypeInterface 
{
public:

	inline gzBool	isExactType( gzType *type ) const 
	{
		if(getType()==type)
			return TRUE;
		else
			return FALSE;
	}

	gzBool			isOfType(gzType *type ) const;

	virtual gzType	*getType() const = 0;

	const char		*getTypeName() const;
};

//******************************************************************************
// Class	: gzTypeContainer
//									
// Purpose  : Encapsule Type Interface functions for RTTI 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	181116	Created 
//									
//******************************************************************************
template <class T> class gzTypeContainer : public T, public gzTypeInterface
{
public:

	gzTypeContainer()
	{
	};

	gzTypeContainer(const T & copy) :T(copy)
	{
	};

	virtual ~gzTypeContainer()
	{
	};
	
	static gzType *getClassType()
	{
		return T::getClassType();
	}

	virtual gzType *getType() const
	{
		return T::getClassType();
	}
};

//******************************************************************************
// Class	: gzDynamic_Cast<CastToClass>
//									
// Purpose  : Utility to do a checked dynamic cast 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011105	Created 
//									
//******************************************************************************
template<class T> T * gzDynamic_Cast(gzTypeInterface* pObject)
{
	if (pObject == NULL)
		return NULL;

	if ( pObject->isOfType( T::getClassType() ) )
		return (T *)pObject;

	return NULL;
}

//******************************************************************************
// Class	: gzDynamic_Instance_Cast<CastToClass>
//									
// Purpose  : Utility to do a checked dynamic cast of instance to pointer
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	011105	Created 
//									
//******************************************************************************
template<class T1 , class T2> T2 * gzDynamic_Instance_Cast(gzTypeInterface* pObject)
{
	if (pObject == NULL)
		return NULL;

	if ( pObject->isOfType( T1::getClassType() ) )
		return (T2 *)(*(T1 *)pObject);

	return NULL;
}


#endif
