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
// File			: gzReference.h
// Module		: gzBase
// Description	: Class definition of reference handle
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.211
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
// AMO	101021	Added a releaseRefs to gzReference					(2.5.14)
// AMO	200408	Added some conveniet operators for gzRefPointer<T>	(2.10.5)
//
//******************************************************************************
#ifndef __GZ_REFERENCE_H__
#define __GZ_REFERENCE_H__

/*!	\file 
	\brief Reference management of objects (smart pointers)

Gizmo3D uses gzReference for all objects created on the heap. With this technique, Gizmo3D
eliminates memory leaks and simplifies the management for object Factories, Cloning and Referencing.

*/

#include "gzMemory.h"
#include "gzTemplates.h"
#include "gzDebug.h"
#include "gzType.h"


enum gzCopyMode
{	
	GZ_CLONE_NO_SHARE	= (0),			// Node share modes 
	GZ_CLONE_SHARE_ALL	= 0xFFFFFFFFUL,	// Everything is shared
};

GZ_USE_BIT_LOGIC(gzCopyMode);

//******************************************************************************
// Class	: gzReference
//									
// Purpose  : Holds reference count to objects
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
//! Base class for referenced managed objects.
/*! The gzReference class keeps a reference counter and increments/decrements when
	external classes references/unreferences the gzReference class.
	When reference count reaches 0 count, the gzReference can delete the object
	by calling a virtual destructor.

	The gzReference class inherits from gzMemory to allow memory caching etc.
	The gzReference class also has a base definition of the RTTI information by
	using the gzTypeInterface.

	If you derive from the gzreference class you can provide your own RTTI information 
	by using the following code snippet..

\code

class MyClass : public gzReference
{
	GZ_DECLARE_TYPE_INTERFACE;		// Add RTTI to your class

	...
}

\endcode

	and in your cpp body you should add the RTTI info by using...

\code

  GZ_DECLARE_TYPE_CHILD(gzReference,MyClass,"MyClassName");

\endcode

  The gzReference class also provides the clone() ability. The default clone()
  method deadlocks just to notify you that you have no implementation of the clone() method.

  You should add a virtual clone method like...

\code

	gzReference* clone() const
	{
		return (gzReference*) new MyClass(this);
	}

\endcode


	The gzReference class is also the base class used by all reference lists
	and dictionaries. They use the method useDeepCopy() to get information of
	how to handle cloning. Default behaviour is to return TRUE so the reference 
	lists etc. uses the clone method you have provided. If you derive this method and
	return FALSE, you will get a reference share insted of a reference clone(). The
	reference count is incremented and the item is shared between the lists etc.

*/

class  GZ_BASE_EXPORT gzReference : public gzSharedMemory , public gzTypeInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE;		//!< Provides Run Time Type Info (RTTI) for the gzTypeInterface

	//! Default constructor
	gzReference();

	//! Default copy constructor
	gzReference(const gzReference &copy);

	//! Default assignment operator
	gzReference &operator=(const gzReference &copy);

	//! Default destructor (Virtual !!!)
	virtual ~gzReference();
	
	//! Default clone method
	/*! The clone method deadlocks (halt execution) if it is called for an object
		That has no own clone method. You must add your own clone method if you want to
		use gzRefList etc. with copy constructors etc. (Shared/Cloned lists) */
	virtual gzReference* clone() const;

	// ----- Class dependant copy behaviour --------------------------
	// Each class can override deep copy to implement shared resources
	// ---------------------------------------------------------------

	//! Returns copy mode
	/*! The copymode value is a generic value that can be used to control your own
		implementation of the useDeepCopy. The Gizmo3D scene graph uses this to control
		sharing of common resources like geometry etc. */
	const gzCopyMode &	getCopyMode() const { return m_copyMode; }

	//! Set copy mode value
	/*! This method is also user defined just like getCopyMode() */
	virtual gzVoid	setCopyMode(const gzCopyMode & mode) { m_copyMode = mode&GZ_CLONE_SHARE_ALL; }
	
	//! Provides information to shared lists etc. 
	/*! If the item method returns TRUE, shared lists etc. uses the clone method to make a
		copy of the item. If the item method returns FALSE, shared lists etc. uses ref()
		to add a reference and shares the item instance */
	virtual	gzBool	useDeepCopy() { return m_copyMode==GZ_CLONE_NO_SHARE; }	// Default behaviour is to deep copy

	//! Add reference count
	/*! If you call ref() on a gzReference derived object instance, you increment the reference count
		and the item will not be deleted as long as you have a reference (until you call unref()) */
    virtual gzVoid ref();

	//! Remove a reference count
	/*! If you call unref() and the reference count decrements to zero, the gzReference class will 
		automatically call the virtual destructor */
    virtual gzVoid unref();

	//! Remove a reference count without deallocation
	/*! If you call unref() and the reference count decrements to zero, the gzReference class will 
		NOT automatically call the virtual destructor. You will have to call checkDelete to remove instance */
    virtual gzUInt32	unrefNoDelete();

	//! Checks reference count and deletes if reference count is zero.
	/*! If the instance has a reference count equal to zero, the instance will be deleted
		and the method returns TRUE. If the reference count is not zero, the method will return
		FALSE */
	virtual gzBool	checkDelete();

	//! Called when system wants to release external references without deleting it yet (e.g. thread dealloc pool)
	/*! If you can not release it you should return FALSE*/
	virtual gzBool	releaseRefs() { return TRUE; }

	//! Returns refrence count
    virtual gzUInt32	getRef() const { return _refCount; }

protected:

    gzUInt32			_refCount;

	// Protected utility function

	static gzVoid throwFatalException(const char* str1, const char* str2 = NULL);

private:

	gzCopyMode		m_copyMode;	// class dependant
};


//******************************************************************************
// Function	: gzReference::gzReference()
//									
// Purpose  : Constructor
//									
// Params   : -			
//										
// Result	: -					
//										
// Notes	: sets reference count to zero. Allows usage of class without references	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created release 
//									
//******************************************************************************
inline gzReference::gzReference():_refCount(0),m_copyMode(GZ_CLONE_NO_SHARE)
{
}

//******************************************************************************
// Function	: gzReference(gzReference &copy)
//									
// Purpose  : Copy Constructor
//									
// Params   : -			
//										
// Result	: -					
//										
// Notes	: sets reference count to zero. Allows usage of class without references	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created release 
//									
//******************************************************************************
inline gzReference::gzReference(const gzReference &copy):gzTypeInterface(),_refCount(0),m_copyMode(copy.m_copyMode)
{}

//******************************************************************************
// Function	: gzReference & gzReference::operator=(const gzReference &copy)
//									
// Purpose  : Assignment operator
//									
// Params   : -			
//										
// Result	: -					
//										
// Notes	: Do not change reference count. Allows usage of class without references	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created release 
//									
//******************************************************************************
inline gzReference & gzReference::operator=(const gzReference &copy)
{
	m_copyMode=copy.m_copyMode;
	return *this;
}

//******************************************************************************
// Function	: gzReference::~gzReference()
//									
// Purpose  : Destructor
//									
// Params   : -			
//										
// Result	: -					
//										
// Notes	: if deleted when reference count !=0 exits software hard !	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created release 
//									
//******************************************************************************
inline gzReference::~gzReference()
{
	if(_refCount)
	{
		throwFatalException("REFERENCE MISMATCH ! Deleted referenced object with nonzero reference count"); //NOSONAR - We want this exception to happend even in destructor
	}
}

//******************************************************************************
// Function	: gzReference::clone()
//									
// Purpose  :	throws an exception if somebody tries to clone this object
//				User must provide an implementation if clone should be used !
//									
// Params   : -			
//										
// Result	: -					
//										
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created release 
//									
//******************************************************************************
inline gzReference* gzReference::clone() const
{
	throwFatalException("Unimplemented clone called for type '%s'", (const char*)getTypeName());
	return NULL;
}

//******************************************************************************
// Function	: gzReference::ref()
//									
// Purpose  : Increases reference count
//									
// Params   : -			
//										
// Result	: -
//										
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created release 
//									
//******************************************************************************
inline gzVoid gzReference::ref()
{
	if(_refCount<0xFFFFFFFFUL)
		++_refCount;
	else
		throwFatalException("Too many ref called for type '%s'", (const char*)getTypeName());
}

//******************************************************************************
// Function	: gzReference::checkDelete()
//									
// Purpose  : Checks if reference count is zero and deletes it if that is true
//									
// Params   : -			
//										
// Result	: gzBool - true if deleted			
//										
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created release 
//									
//******************************************************************************
inline gzBool gzReference::checkDelete()
{
	if(!_refCount)
	{
		delete this;
		return TRUE;
	}
	return FALSE;
}

//******************************************************************************
// Function	: gzReference::unref()
//									
// Purpose  : Decrease reference count. If zero then deleted
//									
// Params   : -			
//										
// Result	: -			
//										
// Notes	: if unmatched references found then an exception is thrown	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created release 
//									
//******************************************************************************
inline gzVoid gzReference::unref()
{
	if(_refCount)
	{
		if(!(--_refCount))
			delete this;
	}
	else
	{
		throwFatalException("REFERENCE MISMATCH ! Unref an object with zero reference count."); //NOSONAR - We want this exception to happend even in destructor
	}
}

//******************************************************************************
// Function	: gzReference::unrefNoDelete()
//									
// Purpose  : Decrease reference count. 
//									
// Params   : -			
//										
// Result	: int - number of remaining references			
//										
// Notes	: if unmatched references exits software	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created release 
//									
//******************************************************************************
inline gzUInt32 gzReference::unrefNoDelete()
{
	if(_refCount)
	{
		--_refCount;
	}
	else
	{
		throwFatalException("REFRENCE MISMATCH ! Unref an object with zero reference count.");
	}
	return _refCount;
}

// ********** Referenced utility templates **************************************

//******************************************************************************
// Class	: gzRefPointer
//									
// Purpose  : Container with copy constructors etc. for referenced managed pointers
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981127	Created 
//									
//******************************************************************************
//! Container with copy constructors etc. for referenced managed pointers
template <class T> class gzRefPointer
{
public:

	//! Default zero constructor
	gzRefPointer();

	//! Copy construct and assign for container class
	gzRefPointer( const gzRefPointer<T> &copy);
	gzRefPointer & operator=(const gzRefPointer<T> &copy);

	//! Copy construct and assign for pointer class
	gzRefPointer( T *pointer);
	gzRefPointer & operator=(T* pointer);

	~gzRefPointer();

	gzVoid	set(T *pointer);

	inline T *		get()		const { return m_pointer; }

	inline operator T *()		const { return m_pointer; }

	inline T * operator ->()	const { return m_pointer;	}

	inline gzBool operator !()	const { return m_pointer == NULL; }

	virtual gzVoid	setCopyMode(const gzCopyMode & mode)
	{
		if(m_pointer)
			m_pointer->setCopyMode(mode);
	}

private:

	T *m_pointer;
};

//******************************************************************************

template <class T> inline gzRefPointer<T>::gzRefPointer():m_pointer(NULL)
{
}

//******************************************************************************

template <class T> inline gzRefPointer<T>::gzRefPointer( const gzRefPointer<T> &copy)
{
	if(copy.m_pointer)
	{
		if(copy.m_pointer->useDeepCopy())
			m_pointer=(T *)copy.m_pointer->clone();
		else
			m_pointer=copy.m_pointer;
	}
	else
		m_pointer=nullptr;

	if(m_pointer)
		m_pointer->ref();
}

//******************************************************************************

template <class T> inline gzRefPointer<T>::gzRefPointer( T *pointer)
{
	m_pointer=pointer;

	if(m_pointer)
		m_pointer->ref();
}

//******************************************************************************

template <class T> inline gzRefPointer<T> & gzRefPointer<T>::operator=(T* pointer)
{
	set(pointer);

	return *this;
}

//******************************************************************************

template <class T> inline gzRefPointer<T> & gzRefPointer<T>::operator =(const gzRefPointer<T> &copy)
{
	if(copy.m_pointer==m_pointer)
		return *this;

	if(copy.m_pointer)
		copy.m_pointer->ref();

	if(m_pointer)
		m_pointer->unref();

	m_pointer=copy.m_pointer;
	
	return *this;
}

//******************************************************************************

template <class T> inline gzVoid gzRefPointer<T>::set(T *pointer)
{
	if(pointer==m_pointer)
		return;

	if(pointer)
		pointer->ref();

	if(m_pointer)
		m_pointer->unref();

	m_pointer=pointer;
}

//******************************************************************************

template <class T> inline gzRefPointer<T>::~gzRefPointer()
{
	if(m_pointer)
		m_pointer->unref();	//NOSONAR - We want this exception to happend even in destructor
}

#define GZ_DECLARE_REFPTR(x)	typedef gzRefPointer<x> x##Ptr

GZ_DECLARE_REFPTR(gzReference);

//******************************************************************************
// Class	: gzRefList
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981127	Created 
//									
//******************************************************************************
//! Special referenced managed list
template <class T> class gzRefList : public gzList<T>
{
public:
	
	gzRefList(gzBool reuseLinks=FALSE):gzList<T>(reuseLinks),m_useDelayedRemove(FALSE){};

	// Special initializers

	//! Uses cloneEntry to copy from one list to another. This can be shared or copied depending on the result from useDeepCopy()
	gzRefList( const gzRefList<T> &copy ):gzList<T>(),m_useDelayedRemove(FALSE){ gzList<T>::operator=((const gzList<T> &)copy); }

	//! Uses cloneEntry to copy from one list to another. This can be shared or copied depending on the result from useDeepCopy()
	gzRefList<T> &operator=(const gzRefList<T> &copy ) { gzList<T>::operator=((const gzList<T> &)copy); return *this; }

	//! Uses shared instances and just moves the pointers from gzList to gzRefList and 
	gzRefList( const gzList<T> &copy ):m_useDelayedRemove(FALSE){ operator=((const gzList<T> &)copy); }

	//! Uses shared instances and just moves the pointers from gzList to gzRefList and 
	gzRefList<T> &operator=(const gzList<T> &copy ) 
	{
		if(&copy==this)
			return *this;

		clear();	// rensa gammal data

		typename gzList<T>::LinkItem *link=copy.m_link;

		gzList<T>::m_link=0;
		gzList<T>::m_last=0;

		while(link)
		{
			typename gzList<T>::LinkItem *newlink=gzList<T>::allocLink();

			newlink->item=link->item; // default share instance

			onInsert(newlink->item);

			newlink->sortval=link->sortval;

			newlink->next=0;

			if(gzList<T>::m_last)
				gzList<T>::m_last->next=newlink;
			else
				gzList<T>::m_link=newlink;

			gzList<T>::m_last=newlink;

			link=link->next;
		}
		gzList<T>::m_entries=copy.m_entries;

		return *this;
	}

	virtual ~gzRefList()
	{ 
		clear(); //NOSONAR - We want this exception to happend even in destructor
	}

	gzVoid useDelayedRemove(gzBool on)
	{
		m_useDelayedRemove=on;
	}

	virtual gzVoid onInsert(T *item ) const 
	{
		if(item)
			item->ref();
	}

	virtual gzVoid onRemove(T *item ) const 
	{
		if(m_useDelayedRemove)
			((gzRefList<T> *)this)->m_delayedRemove.set(item);

		if(item)
			item->unref();
	}

	virtual T *cloneEntry(T *item ) const 
	{ 
		if(item)
		{
			if(item->useDeepCopy())
				return (T *)item->clone();
			else
				return item;
		}
		else
			return NULL;
	}
	virtual gzVoid	setCopyMode(const gzCopyMode & mode)
	{
		T *entry;
		
		gzListIterator<T> iterator(*this);
		
		while((entry=iterator()))
		{
			entry->setCopyMode(mode);
		}
	}

	virtual gzVoid clear()
	{
		gzList<T>::clear();
		cleanDelayedRemove();
	}

	gzVoid cleanDelayedRemove()
	{
		m_delayedRemove=nullptr;
	}


private:

	gzRefPointer<T>	m_delayedRemove;

	gzBool			m_useDelayedRemove;

};

//******************************************************************************
// Class	: gzRefDList
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	010222	Created 
//									
//******************************************************************************
//! Special referenced managed list
template <class T> class gzRefDList : public gzDList<T>
{
public:
	
	gzRefDList():m_useDelayedRemove(FALSE){};
	gzRefDList( const gzRefDList &copy ):gzDList<T>(),m_useDelayedRemove(FALSE){  gzDList<T>::operator=((const gzDList<T> &)copy); }
	gzRefDList( const gzRefList<T> &copy ):m_useDelayedRemove(FALSE){  gzDList<T>::operator=((const gzList<T> &)copy); }
	
	virtual ~gzRefDList()
	{ 
		clear(); //NOSONAR - We want this exception to happend even in destructor
	}

	gzVoid useDelayedRemove(gzBool on)
	{
		m_useDelayedRemove=on;
	}
	
	virtual gzVoid onInsert(T *item ) const 
	{
		if(item)
			item->ref();
	}

	virtual gzVoid onRemove(T *item ) const
	{
		if(m_useDelayedRemove)
			((gzRefDList<T> *)this)->m_delayedRemove.set(item);

		if(item)
			item->unref();
	}

	virtual T *cloneEntry(T *item ) const 
	{ 
		if(item)
		{
			if(item->useDeepCopy())
				return (T *)item->clone();
			else
				return item;
		}
		else
			return NULL;
	}
	virtual gzVoid	setCopyMode(const gzCopyMode & mode)
	{
		T *entry;
		
		gzDListIterator<T> iterator(*this);
		
		while((entry=iterator()))
		{
			entry->setCopyMode(mode);
		}
	}

	virtual gzVoid clear()
	{
		gzDList<T>::clear();
		cleanDelayedRemove();
	}

	gzVoid cleanDelayedRemove()
	{
		m_delayedRemove=nullptr;
	}

private:

	gzRefPointer<T>	m_delayedRemove;

	gzBool			m_useDelayedRemove;

};

//******************************************************************************
// Class	: gzRefDict
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981127	Created 
//									
//******************************************************************************
//! Special referenced managed dictionary
template <class T1 , class T2> class gzRefDict : public gzDict<T1,T2>
{
public:
	gzRefDict(gzUInt32 size=10U,gzBool useAutoResize=FALSE, gzBool useParallelRead=FALSE):gzDict<T1,T2>(size,useAutoResize,useParallelRead),m_useDelayedRemove(FALSE){};

	gzRefDict( const gzRefDict &copy ):gzDict<T1,T2>(0U),m_useDelayedRemove(FALSE)	{  gzDict<T1,T2>::operator=((const gzDict<T1,T2> &)copy); }

	virtual ~gzRefDict() 
	{ 
		clear(); //NOSONAR - We want this exception to happend even in destructor
	}

	gzVoid onInsert(const T1 & , T2 *item) const { if(item)item->ref();};

	gzVoid onRemove(const T1 & , T2 *item) const 
	{ 
		if(m_useDelayedRemove)
			((gzRefDict<T1,T2> *)this)->m_delayedRemove.set(item);

		if(item)item->unref();
	}

	virtual gzDictEntry<T1,T2> *cloneEntry( gzDictEntry<T1,T2> *item) const 
	{
		if(item)
		{
			if(item->getData()->useDeepCopy())
				return this->allocEntry(item->getKey(),(T2 *)item->getData()->clone(),item->getKey().hash());
			else
				return gzDict<T1,T2>::allocEntry(item->getKey(),item->getData(),item->getKey().hash()); 
		}
		else
			return NULL;
	}

	virtual gzVoid	setCopyMode(const gzCopyMode & mode)
	{
		gzDictEntry<T1,T2>		*entry;
		gzDictIterator<T1,T2>	iterator(*this);

		while((entry=iterator()))
		{
			if(entry->getData())
				entry->getData()->setCopyMode(mode);
		}
	}

	gzVoid cleanDelayedRemove()
	{
		m_delayedRemove=nullptr;
	}

	gzVoid useDelayedRemove(gzBool on)
	{
		m_useDelayedRemove=on;
	}

	virtual gzVoid clear()
	{
		gzDict<T1,T2>::clear();
		cleanDelayedRemove();
	}


private:

	gzRefPointer<T2>	m_delayedRemove;

	gzBool			m_useDelayedRemove;
};


//******************************************************************************
// Class	: gzRefData
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000101	Created 
//									
//******************************************************************************
//! Special referenced managed list
template <class T1 , class T2=gzReference > class gzRefData : public T1 , public gzReference 
{
public:

	gzRefData() {};

	gzRefData(const T1& copy) :T1(copy) {};

	gzRefData(const gzRefData& copy): T1(copy.getValue()) {};

	virtual ~gzRefData() = default;

	virtual gzReference* clone() const
	{
		return new gzRefData(*this);
	}

	virtual gzVoid	setCopyMode(const gzCopyMode& mode)
	{
		gzReference::setCopyMode(mode);
	}

	T1 getValue() const { return (T1)*this; }

	static gzType* getClassType() { return T2::getClassType(); }

	virtual gzType* getType() const { return T2::getClassType(); }
};

//******************************************************************************

class gzRefInstanceDictionary : public gzRefDict<gzInstanceCompareInterface,gzReference> 
{
public:
	gzRefInstanceDictionary(gzUInt32 size=100):gzRefDict<gzInstanceCompareInterface,gzReference>(size){};
};

class gzRefInstanceArray : public gzDynamicArray< gzRefPointer<gzReference> > 
{
public:
	gzRefInstanceArray(gzUInt32 size=100) : gzDynamicArray< gzRefPointer<gzReference> >(size) {};
};

//******************************************************************************

//******************************************************************************
// Class	: gzRefIdStorage
//									
// Purpose  : Reference counted storage of UInt IDs
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030422	Created 
//									
//******************************************************************************
class gzRefIdStorage : public gzReference
{
public:

	gzRefIdStorage():id(GZ_QUEUE_LIFO,1000)
	{
	}
	
	virtual ~gzRefIdStorage()
	{
	}

	gzQueue<gzUInt32>		id;
};

//******************************************************************************
// Class	: gzRefListData
//									
// Purpose  : Reference based list of items
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030422	Created 
//									
//******************************************************************************
class gzRefListData : public gzReference
{
	public:

		GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);		//!< Provides Run Time Type Info (RTTI) for the gzTypeInterface

		virtual gzBool useDeepCopy() override { return FALSE; }

		gzBool hasType(gzType* type, gzBool exact = FALSE)
		{
			gzListConstIterator<gzReference> iterator(list);
			const gzReference* ref;

			while ((ref = iterator()))
			{
				if (exact)
				{
					if (ref->isExactType(type))
						return TRUE;
				}
				else
				{
					if (ref->isOfType(type))
						return TRUE;
				}
			}

			return FALSE;
		}

		gzRefList<gzReference> list;
};

// ----------------- Debug Macros for reference count in classes -----------------------

#define GZ_DEBUG_REF(refhandler)					\
													\
	virtual gzVoid	ref()  override					\
	{												\
		refhandler::ref();							\
	}												

#define GZ_DEBUG_UNREF(refhandler)					\
													\
    virtual gzVoid	unref() override				\
	{												\
		refhandler::unref();						\
	}												

#define GZ_DEBUG_UNREF_NO_DELETE(refhandler)		\
													\
    virtual gzUInt32	unrefNoDelete() override	\
	{												\
		refhandler::unrefNoDelete();				\
	}												

#define GZ_DEBUG_CHECK_DELETE(refhandler)			\
													\
	virtual gzBool	checkDelete() override			\
	{												\
		refhandler::checkDelete();					\
	}												

#define GZ_DEBUG_GET_REF(refhandler)				\
													\
    virtual gzUInt32	getRef() const override		\
	{												\
		refhandler::checkDelete();					\
	}												

#endif // __GZ_REFERENCE_H__
