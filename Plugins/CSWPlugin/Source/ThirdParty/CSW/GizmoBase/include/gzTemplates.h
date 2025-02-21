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
// File			: gzTemplates.h
// Module		: gzBase
// Description	: Class definition of iterator utilities
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
// AMO	980915	Created file 	
// AMO	100129	Added a gzArray:remove method						(2.4.12)
// AMO	100820	Added a default value to empty gzArray::resize		(2.5.10)
// CAN	120320	Added possibility to do parallel read in gzDict		(2.6.2)
// AMO	120918	Added cleanItem to gzDataSort to allow cleanup		(2.6.12)
// AMO	121219	Fixed unaligned gzQWA_Byte in gzDynamicArray		(2.6.18)
// AMO	130212	Added fast bit counter template						(2.6.24)
// AMO	151116	Added contains method to gzDynamicArray				(2.8.1) 
// AMO	200604	Added gzDynamicArray+=gzDynamicArray				(2.10.6)
// AMO	200911	Fixed issues in gzDynamicArray with wrong size used	(2.10.6)
//
//******************************************************************************

#ifndef __GZ_TEMPLATES_H__
#define __GZ_TEMPLATES_H__


/*!	\file 
	\brief Templates for \b Gizmo3D

	The templates provides fast and easy access to linked lists, arrays and dictionaries. They all
	provide virtual methods executed at insertion and removal of items. They do also provide iterators
	for lists and dictionaries.
*/

#include "gzXYZ.h"
#include "gzMemory.h"
#include "gzAssembler.h"
#include "gzArithmetic.h"

// --------------------- Copy Instances of data from to ---------------------------

template <class T> inline gzVoid copyInstances(T *to, T *from, gzUInt32 count,gzBool clearSource=FALSE)
{
	if (!clearSource)
	{
		if (to < from)
		{
			while (count)
			{
				*to = *from;
				++to;
				++from;
				--count;
			}
		}
		else if (to > from)
		{
			to += count;
			from += count;

			while (count)
			{
				--to;
				--from;
				*to = *from;
				--count;
			}
		}
	}
	else
	{
		if (to < from)
		{
			while (count)
			{
				*to = *from;
				*from = T();
				++to;
				++from;
				--count;
			}
		}
		else if (to > from)
		{
			to += count;
			from += count;

			while (count)
			{
				--to;
				--from;
				*to = *from;
				*from = T();
				--count;
			}
		}
	}

}

template <> inline gzVoid copyInstances(gzUInt32 *to, gzUInt32 *from, gzUInt32 count, gzBool /*clearSource*/)
{
	if(count && to && from)
		memmove(to, from, count * sizeof(gzUInt32));
}

template <> inline gzVoid copyInstances(gzWideChar* to, gzWideChar* from, gzUInt32 count, gzBool /*clearSource*/)
{
	if (count && to && from)
		memmove(to, from, count * sizeof(gzWideChar));
}


template <> inline gzVoid copyInstances(gzInt32 *to, gzInt32 *from, gzUInt32 count, gzBool /*clearSource*/)
{
	if (count && to && from)
		memmove(to, from, count * sizeof(gzInt32));
}

template <> inline gzVoid copyInstances(gzUByte *to, gzUByte *from, gzUInt32 count, gzBool /*clearSource*/)
{
	if (count && to && from)
		memmove(to, from, count * sizeof(gzUByte));
}

template <> inline gzVoid copyInstances(gzFloat *to, gzFloat *from, gzUInt32 count, gzBool /*clearSource*/)
{
	if (count && to && from)
		memmove(to, from, count * sizeof(gzFloat));
}

template <> inline gzVoid copyInstances(gzDouble *to, gzDouble *from, gzUInt32 count, gzBool /*clearSource*/)
{
	if (count && to && from)
		memmove(to, from, count * sizeof(gzDouble));
}

template <> inline gzVoid copyInstances(gzQWA_UByte *to, gzQWA_UByte *from, gzUInt32 count, gzBool /*clearSource*/)
{
	if (count && to && from)
		memmove(&to->data, &from->data, count * sizeof(gzQWA_UByte));
}

template <> inline gzVoid copyInstances(gzQWA_Byte *to, gzQWA_Byte *from, gzUInt32 count, gzBool /*clearSource*/)
{
	if (count && to && from)
		memmove(&to->data, &from->data, count * sizeof(gzQWA_Byte));
}

template <> inline gzVoid copyInstances(gzQWA_UInt16 *to, gzQWA_UInt16 *from, gzUInt32 count, gzBool /*clearSource*/)
{
	if (count && to && from)
		memmove(&to->data, &from->data, count * sizeof(gzQWA_UInt16));
}

template <> inline gzVoid copyInstances(gzQWA_Int16 *to, gzQWA_Int16 *from, gzUInt32 count, gzBool /*clearSource*/)
{
	if (count && to && from)
		memmove(&to->data, &from->data, count * sizeof(gzQWA_Int16));
}


// ------------------- resize instances --------------------------------------------------

template <class T> inline T* resizeInstances(T* oldData, gzUInt32* oldSizePtr, gzUInt32 newSize)
{
	if (*oldSizePtr < newSize)	// We need new alloc
	{
		T* data = new T[newSize];

		copyInstances<T>(data, oldData, newSize);

		*oldSizePtr = newSize;

		delete[] oldData;

		return data;
	}
	else
	{
		*oldSizePtr = newSize;

		return oldData;
	}
}

// Forward prototyp
GZ_BASE_EXPORT gzVoid throwFatalTemplateError(const char *string);

template <class T> class gzListIterator;
template <class T> class gzListConstIterator;
template <class T> class gzRefList;

//******************************************************************************
// Template	: gzList
//									
// Purpose  : Linked list with index insort and reference management
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980601	Created 
//									
//******************************************************************************
/*! \brief Template class for linked lists

The gzList is a template class that contains a single linked list with fast access to retreive
and store items in the list. It does also provide the virtual functions onInsert and onRemove so the user
can derive this class and access these events.

If you want to use reference based lists you should use the gzRefList instead !

*/

template <class T> class gzList 
{
	friend class gzListIterator<T>; 
	friend class gzListConstIterator<T>; 
	friend class gzRefList<T>;

	public:

		//! Default constructor.
		gzList(const gzBool reuseLinks=FALSE);

		//! Default copy constructor.

		/*! Note that the cloning in the copy constructor depends
			on your implementation of the cloneEntry() method. By default the list shares
			each item in the list. You can provide your own derived virtual method to add
			other behaviours of the copy constructor. */

		gzList(const gzList<T> &copy)  ;

		//! Default destructor. Clears list !!
		virtual ~gzList()  ;

		//! Insert item at end of list
		gzVoid insert(T *item)  ;					// Adds at end of list

		//! Insert item at index pos starting at 0
		gzVoid insertAt(const gzUInt32 index,T *item)  ;	// Adds at index

		//! Insert item at beginning of list
		gzVoid pre_insert(T *item) ;					// Adds at beginning of list

		//! Insert item using gzUInt32 sort value

		/*! The insert method removes the old item if there is one with the same
			index sort value and returns a pointer to the item so it can be freed etc. */

		T   *insert(T *item, const gzDouble &sortval)  ;

		//! Post Insert with sorted value
		/*! If there is one or more existing items with the same sort value, the new
			item is inserted at the end of the existing items */
		gzBool post_insert(T *item, const gzDouble &sortval)  ;

		//! Pre Insert with sorted value
		/*! If there is one or more existing items with the same sort value, the new
			item is inserted at the beginning of the existing items */
 		gzBool pre_insert(T *item, const gzDouble &sortval)  ;

		//! Index operator based on index zero as first value
   		T	*operator[](const gzUInt32 i)  const ;

		//! Index operator based on index zero as first value
		gzDouble sortval(const gzUInt32 i)  const;

		//! Assignment operator
		gzList &operator=(const gzList &copy )  ;

		gzList &operator+=(const gzList &copy )  ;

		//! Clears items from list. Does NOT free item
		virtual gzVoid clear()  ;

		//! Clears item AND frees item allocated memory
		virtual gzVoid clearAndDestroy()  ;

		//! Number of item entries in list
		gzUInt32 entries() const  ;

		//! Query to see if list contains an element
		gzBool contains(const T *item) const ;

		gzInt32 index(const T *item) const ;

		T	*findSortItem(const gzDouble &sortval,const T *prevItem=nullptr);

		//! Removes first item and returns reference to item
		T	*removeFirst()  ;
		
		//! Removes last item and returns reference to item
		T	*removeLast()  ;

		//! Removes item and returns reference to item
		T	*remove( T * item )  ;
		
		//! Removes item at index pos starting at 0
		T	*removeAt( const gzUInt32 index )  ;

		//! Returns reference to last item in list
		T	*last() const;

		//! Return sortval for last item
		gzDouble lastSortval() const;

		//! Returns reference to first item in list
		T	*first() const;

		//! Return sortval for last item
		gzDouble firstSortval() const;
		
		//! Virtual method called when an item is inserted
		virtual gzVoid onInsert(T * /*item*/ ) const {};

		//! Virtual method called when an item is removed
		virtual gzVoid onRemove(T * /*item*/ ) const {};

		//! Virtual method called when an item shall be cloned.
		/*! The method implements a shared item as default. Make sure that you
			do not call e.g clearAndDestroy() on a list that is created with this default
			clone (share) method in combination with a free of your originally created list.
			You will then get two deallocations of item memory */

		virtual T* cloneEntry(T *item ) const ;

		//! Provide the ability to do a garbage collect of used item links
		gzVoid	cleanLinks()  ;

		//! Recycled usage of links. Doesn't release link memory at item removal, but uses it for next item.
		gzVoid reuseLinks(const gzBool on=FALSE) ;

		gzBool operator==(const gzList &right) const;

	protected:

		struct LinkItem
		{
			gzDouble		sortval;
			T				*item;
			LinkItem		*next;
		};

		gzVoid			disposeLink(LinkItem *link) ;
		LinkItem *		allocLink() ;


		LinkItem	*m_link;

		LinkItem	*m_last;

		LinkItem	*m_recycle;

		gzUInt32		m_entries;

		gzBool		m_reuseLinks;

};


//***********************************************************************

template <class T> inline gzBool gzList<T>::operator==(const gzList &right) const
{
	if(m_entries!=right.m_entries)
		return FALSE;

	LinkItem *a=m_link;

	LinkItem *b=right.m_link;

	while(a)
	{
		if(a->item!=b->item)
			return FALSE;

		a=a->next;
		b=b->next;
	}
	
	return TRUE;
}

template <class T> inline gzVoid gzList<T>::reuseLinks(const gzBool on) 
{
	m_reuseLinks=on;
}

template <class T> inline typename gzList<T>::LinkItem * gzList<T>::allocLink() 
{
	if(m_reuseLinks && m_recycle)
	{
		LinkItem *link=m_recycle;

		m_recycle=m_recycle->next;

		return link;
	}
	return new LinkItem;
}

template <class T> inline gzVoid gzList<T>::disposeLink(LinkItem *link) 
{ 
	if(m_reuseLinks)
	{
		link->next=m_recycle;
		m_recycle=link;
	}
	else
		delete link;
}

template <class T> inline gzVoid gzList<T>::cleanLinks() 
{
	if(m_recycle)
	{
		LinkItem *nextlink;

		while(m_recycle)
		{
			nextlink=m_recycle->next;
			delete m_recycle;
			m_recycle=nextlink;
		}
	}
}

//***********************************************************************

template <class T> inline T* gzList<T>::cloneEntry(T *item) const
{
	return item;
}

//***********************************************************************

template <class T> inline gzUInt32 gzList<T>::entries()  const 
{
	return m_entries;
}

//***********************************************************************

template <class T> inline T *gzList<T>::remove( T *item ) 
{
	LinkItem *link=m_link;
	LinkItem *prevlink=0;

	T *retitem;

	while(link)
	{
		if(item==link->item)
		{
			if(!prevlink)
			{
				m_link=link->next;
				if(!m_link)
					m_last=0;
			}
			else
			{
				prevlink->next=link->next;
				if(!prevlink->next)
					m_last=prevlink;
			}
			retitem=link->item;
			disposeLink(link);
			m_entries--;
			onRemove(retitem);
			return retitem;
		}
		prevlink=link;
		link=link->next;
	}
	return 0;
}

//***********************************************************************

template <class T> inline T *gzList<T>::removeFirst() 
{
	if(!m_link)
		return 0;

	LinkItem *link=m_link;

	T *item=link->item;
	m_link=m_link->next;
	if(!m_link)
		m_last=0;

	disposeLink(link);

	m_entries--;

	onRemove(item);
	return item;
}

//***********************************************************************

template <class T> inline T *gzList<T>::removeLast() 
{
	if(!m_link)
		return 0;

	LinkItem *link=m_link;

	T *item=m_last->item;

	if(m_link==m_last)
	{
		disposeLink(m_link);
		m_link=0;
		m_last=0;
	}
	else
	{
		while(link->next!=m_last)
			link=link->next;
		disposeLink(m_last);

		m_last=link;
		m_last->next=0;
	}

	m_entries--;

	onRemove(item);
	return item;
}

//***********************************************************************

template <class T> inline T *gzList<T>::last() const
{
	if(!m_last)
		return 0;

	return m_last->item;
}

//***********************************************************************

template <class T> inline gzDouble gzList<T>::lastSortval() const
{
	if (!m_last)
		return 0;

	return m_last->sortval;
}

//***********************************************************************

template <class T> inline T *gzList<T>::first() const
{
	if(!m_link)
		return 0;

	return m_link->item;
}

//***********************************************************************

template <class T> inline gzDouble gzList<T>::firstSortval() const
{
	if (!m_link)
		return 0;

	return m_link->sortval;
}

//***********************************************************************

template <class T> inline T *gzList<T>::operator[](const gzUInt32 i) const
{
	if(i>=m_entries)
		return NULL;

	LinkItem *link=m_link;

	gzUInt32 j;

	for(j=0;j<i;++j)
		link=link->next;

	return link->item;
}

//***********************************************************************

template <class T> inline gzDouble gzList<T>::sortval(const gzUInt32 i) const
{
	if (i >= m_entries)
		return 0;

	LinkItem* link = m_link;

	gzUInt32 j;

	for (j = 0; j < i; ++j)
		link = link->next;

	return link->sortval;
}

//***********************************************************************

template <class T> inline gzList<T>::gzList(const gzBool reuseLinks)  : m_link(0),m_last(0),m_recycle(0),m_entries(0),m_reuseLinks(reuseLinks)
{
}

//***********************************************************************

template <class T> inline gzList<T>::~gzList() 
{
	clear();
	cleanLinks();
}

//***********************************************************************

template <class T> inline gzVoid gzList<T>::insertAt(const gzUInt32 index,T *item) 
{
	if(index>=m_entries)
	{
		insert(item);
		return;
	}

	LinkItem *newlink=allocLink();
	newlink->sortval=0;
	newlink->item=item;

	LinkItem *pre_link=nullptr;
	LinkItem *post_link=m_link;

	gzUInt32 i;

	for(i=0;i<index;++i)
	{
		if(post_link)
		{
			pre_link=post_link;
			post_link=post_link->next;
		}
		else
			break;
	}

	if(pre_link)	// Not first item
	{
		newlink->next=pre_link->next;
		pre_link->next=newlink;

		if(!post_link)	// last
			m_last=newlink;
	}
	else			// First item
	{
		if(m_link)	// Not last
		{
			newlink->next=m_link;
			m_link=newlink;
		}
		else		// last
		{
			newlink->next=nullptr;
			m_last=m_link=newlink;
		}
	}
	++m_entries;
	onInsert(item);
}

//***********************************************************************

template <class T> inline T * gzList<T>::removeAt(const gzUInt32 index) 
{
	if(index>=m_entries-1)
	{
		if(index==m_entries-1)
			return removeLast();
		return NULL;
	}

	LinkItem *pre_link=nullptr;
	LinkItem *post_link=m_link;

	gzUInt32 i;

	for(i=0;i<index;++i)
	{
		if(post_link)
		{
			pre_link=post_link;
			post_link=post_link->next;
		}
		else
			break;
	}

	if(post_link)	// item to remove
	{
		if(pre_link)	// have previous item
		{
			if(!(pre_link->next=post_link->next))	// last item
				m_last=pre_link;

		}
		else	// remove first item
		{
			m_link=post_link->next;
			if(!(m_link=post_link->next))	// was last item
				m_last=nullptr;
		}
		m_entries--;

		T *item=post_link->item;

		disposeLink(post_link);

		onRemove(item);
		return item;
	}
	else
		return NULL;
}

//***********************************************************************

template <class T> inline gzVoid gzList<T>::insert( T *item) 
{
	LinkItem *newlink=allocLink();

	newlink->next=0;

	newlink->sortval=0;

	if(m_last)
		m_last->next=newlink;
	else
		m_link=newlink;

	newlink->item=item;
	m_last=newlink;

	++m_entries;
	onInsert(item);
}

//***********************************************************************

template <class T> inline gzVoid gzList<T>::pre_insert( T *item) 
{
	LinkItem *newlink=allocLink();

	newlink->next=m_link;
	newlink->sortval=0;

	m_link=newlink;

	if(!m_last)
		m_last=newlink;

	newlink->item=item;

	++m_entries;
	onInsert(item);
}

//***********************************************************************
template <class T> inline T	* gzList<T>::findSortItem(const gzDouble &sortval,const T *prevItem)
{
	const typename gzList<T>::LinkItem* link = m_link;
	
	if(prevItem)
	{
		while (link)
		{
			if (link->item == prevItem)
			{
				link = link->next;
				break;
			}

			link = link->next;
		}
	}
	
	while (link)
	{
		if (link->sortval == sortval)
		{
			return link->item;
		}

		link = link->next;
	}

	return NULL;
}

template <class T> inline T* gzList<T>::insert( T *item , const gzDouble &sortval) 
{
	LinkItem *newlink=allocLink();


	newlink->item=item;
	newlink->sortval=sortval;

	onInsert(item);

	if(m_last)
	{
		if(m_last->sortval<sortval)
		{

			m_last->next=newlink;
			newlink->next=nullptr;
			m_last=newlink;
			++m_entries;

			return NULL;
		}
	}

	T *deleteitem=0;

	LinkItem *sortitem=m_link;
	LinkItem *previtem=0;

	while(sortitem)
	{
		if(sortitem->sortval<sortval)
		{
			if(!previtem)
				previtem=sortitem;
			else
				previtem=previtem->next;
			sortitem=sortitem->next;
		}
		else if(sortitem->sortval==sortval)
		{
			deleteitem=sortitem->item;
			sortitem->item=item;
			disposeLink(newlink);
			onRemove(deleteitem);
			return deleteitem;
		}
		else
			break;
	}
	newlink->next=sortitem;
	if(!previtem)
		m_link=newlink;
	else
		previtem->next=newlink;

	if(!sortitem)
		m_last=newlink;

	++m_entries;

	return deleteitem;
}

//***********************************************************************

template <class T> inline gzBool gzList<T>::post_insert( T *item , const gzDouble &sortval) 
{
	LinkItem *newlink=allocLink();

	newlink->item=item;
	newlink->sortval=sortval;

	onInsert(item);

	if(m_last)
	{
		if(m_last->sortval<=sortval)
		{
			gzBool insert=(m_last->sortval==sortval);

			m_last->next=newlink;
			newlink->next=nullptr;
			m_last=newlink;
			++m_entries;

			return insert;
		}
	}

	LinkItem *sortitem=m_link;
	LinkItem *previtem=0;


	while(sortitem)
	{
		if(sortitem->sortval<=sortval)
		{
			if(!previtem)
				previtem=sortitem;
			else
				previtem=previtem->next;
			sortitem=sortitem->next;
		}
		else
			break;
	}

	newlink->next=sortitem;
	if(!previtem)
		m_link=newlink;
	else
		previtem->next=newlink;

	++m_entries;

	if(!sortitem)
		m_last=newlink;

	if(previtem)
	{
		if(previtem->sortval==sortval)
			return TRUE;
		else
			return FALSE;
	}

	return FALSE;

}

//***********************************************************************

template <class T> inline gzBool gzList<T>::pre_insert( T *item , const gzDouble &sortval) 
{
	LinkItem *newlink=allocLink();

	newlink->item=item;
	newlink->sortval=sortval;


	onInsert(item);

	if(m_last)
	{
		if(m_last->sortval<sortval)
		{

			m_last->next=newlink;
			newlink->next=nullptr;
			m_last=newlink;
			++m_entries;

			return FALSE;
		}
	}

	LinkItem *sortitem=m_link;
	LinkItem *previtem=0;

	while(sortitem)
	{
		if(sortitem->sortval<sortval)
		{
			if(!previtem)
				previtem=sortitem;
			else
				previtem=previtem->next;
			sortitem=sortitem->next;
		}
		else
			break;
	}

	newlink->next=sortitem;
	if(!previtem)
		m_link=newlink;
	else
		previtem->next=newlink;

	++m_entries;

	if(!sortitem)
		m_last=newlink;
	else
	{
		if(sortitem->sortval==sortval)
			return TRUE;
		else
			return FALSE;
	}

	return FALSE;
}

//***********************************************************************

template <class T> inline gzList<T> & gzList<T>::operator=(const gzList &copy ) 
{
	if(&copy==this)
		return *this;

	clear();		// rensa gammal data

	m_reuseLinks=copy.m_reuseLinks;

	LinkItem *link=copy.m_link;

	m_link=0;
	m_last=0;

	while(link)
	{
		LinkItem *newlink=allocLink();

		newlink->item=cloneEntry(link->item); // default to copy of instance

		onInsert(newlink->item);
		newlink->sortval=link->sortval;
		newlink->next=0;

		if(m_last)
			m_last->next=newlink;
		else
			m_link=newlink;

		m_last=newlink;

		link=link->next;
	}
	m_entries=copy.m_entries;

	return *this;
}

template <class T> inline gzList<T> & gzList<T>::operator+=(const gzList &copy ) 
{
	if(&copy==this)
		return *this;

	LinkItem *link=copy.m_link;

	while(link)
	{
		LinkItem *newlink=allocLink();

		newlink->item=cloneEntry(link->item); // default to copy of instance

		onInsert(newlink->item);
		newlink->sortval=link->sortval;
		newlink->next=0;

		if(m_last)
			m_last->next=newlink;
		else
			m_link=newlink;

		m_last=newlink;

		link=link->next;
	}
	m_entries+=copy.m_entries;

	return *this;
}

//***********************************************************************

template <class T> inline gzList<T>::gzList(const gzList<T> &copy) 
{
	LinkItem *link=copy.m_link;

	m_link=0;
	m_last=0;
	m_recycle=0;
	m_reuseLinks=FALSE;

	while(link)
	{
		LinkItem *newlink=allocLink();

		newlink->item=cloneEntry(link->item); // default to copy of instance

		onInsert(newlink->item);
		newlink->sortval=link->sortval;
		newlink->next=0;

		if(m_last)
			m_last->next=newlink;
		else
			m_link=newlink;

		m_last=newlink;

		link=link->next;
	}
	m_entries=copy.m_entries;
}

//***********************************************************************

template <class T> inline gzVoid gzList<T>::clearAndDestroy() 
{
	if(m_link)
	{
		LinkItem *nextlink;

		while(m_link)
		{
			nextlink=m_link->next;
			onRemove(m_link->item);
			delete m_link->item;
			disposeLink(m_link);

			m_link=nextlink;
		}
		m_entries=0;
		m_last=0;
	}
}

template <> inline gzVoid gzList<gzVoid>::clearAndDestroy() 
{
	clear();
}



//***********************************************************************

template <class T> inline gzVoid gzList<T>::clear() 
{
	if(m_link)
	{
		LinkItem *nextlink;

		while(m_link)
		{
			nextlink=m_link->next;
			onRemove(m_link->item);
			disposeLink(m_link);

			m_link=nextlink;
		}
		m_entries=0;
		m_last=0;
	}
}


//******************************************************************************
// Template	: gzListIterator
//
// Purpose  : Iterator for gzList
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	980601	Created
//
//******************************************************************************
//! Iterator class for gzList

/*! The Iterator can be used with all gzLists and its derivatives. Typical usage is to use
it as follows...

\code

	gzListIterator<MyListItemClass>	iterator(myActualList);
	MyListItemClass *item;

	while((item=iterator()))
	{
		// Do somthing with item that is iterated through the list
	}

\endcode
	
	Note that iterator can safely remove items with the remove() operator
	in the iterator while iterating the list

*/

template <class T> class gzListIterator 
{
	public:

		//! Constructor of list iterator
		gzListIterator(gzList<T> &owner);

		//! Constructor of list iterator
		gzListIterator(gzList<T> *owner);

		//! Default destructor
		~gzListIterator(){};

		//! Iterating operator
		/*! The operator () iterates one step through list and returns item 
			at current list iterator position. At end of list it returns NULL */
		T *operator()();

		T *operator++(int);	// postfix operator

		//! Circulating operator
		/*! The circulate() method iterates through the list just like the () operator, but
			it restarts at the beginnig of the list when the end is reached. */
		T *circulate();

		//! Returns item at current iterator position.
		/*! Undefined if iterator position is undefined e.g. before operator () is called. */
		T *key() const;

		//! Returns one item ahead in list. You can get the next item without iterating.
		T *next() const;

		//! Removes safely item at current iterator position.
		/*! You should no use key() etc. when you have removed current item !! */
		T *remove();

		//! Reset iterator position to start of list
		gzVoid reset();

		//! Re-use itarator with another list
		gzVoid setList(gzList<T> &owner);

		//! Get current key sortval
		gzDouble sortval() const;

		//! Insert item after current item. If no valid pos the insert is discarded
		gzVoid post_insert(T *item);

		//! Insert item before current item. If no valid pos the insert is discarded
 		gzVoid pre_insert(T *item);


	private:
	
		typename gzList<T>::LinkItem *m_link;

		typename gzList<T>::LinkItem *m_prevlink;

		gzList<T> *	m_owner;

		gzBool		m_circulating;

};

//***********************************************************************

template <class T> inline gzListIterator<T>::gzListIterator(gzList<T> &owner)
{
	m_link=0;
	m_prevlink=0;
	m_circulating=FALSE;
	m_owner=&owner;
}

//***********************************************************************

template <class T> inline gzListIterator<T>::gzListIterator(gzList<T> *owner)
{
	m_link=0;
	m_prevlink=0;
	m_circulating=FALSE;
	m_owner=owner;
}

//***********************************************************************

template <class T> inline gzVoid gzListIterator<T>::setList(gzList<T> &owner)
{
	m_link=0;
	m_prevlink=0;
	m_owner=&owner;
}

//***********************************************************************

template <class T> inline gzDouble gzListIterator<T>::sortval() const
{
	if(m_link)
		return m_link->sortval;
	else
		return 0;
}

//***********************************************************************

template <class T> inline gzVoid gzListIterator<T>::post_insert(T *item)
{
	if(m_link)
	{
		typename gzList<T>::LinkItem *link=m_owner->allocLink();

		link->next=m_link->next;

		link->sortval=0;

		link->item=item;

		m_link->next=link;

		if(m_owner->m_last==m_link)
			m_owner->m_last=link;


		m_owner->onInsert(item);

		++m_owner->m_entries;
	}
}

//***********************************************************************

template <class T> inline gzVoid gzListIterator<T>::pre_insert(T *item)
{
	if(m_link)
	{
		typename gzList<T>::LinkItem *link=m_owner->allocLink();

		link->next=m_link;

		link->sortval=0;

		link->item=item;

		if(m_prevlink)
			m_prevlink->next=link;
		else
			m_owner->m_link=link;

		m_prevlink=link;

		m_owner->onInsert(item);

		++m_owner->m_entries;
	}
}

//***********************************************************************

template <class T> inline T * gzListIterator<T>::remove()
{
	if(!m_link)
		return NULL;

	T *item=m_link->item;

	typename gzList<T>::LinkItem *link;

	if(!m_link->next)
		m_owner->m_last=m_prevlink;

	link=m_link->next;

	if(m_prevlink)
		m_prevlink->next=link;
	else
		m_owner->m_link=link;

	m_owner->onRemove(m_link->item);
	m_owner->disposeLink(m_link);
	m_owner->m_entries--;

	m_link=m_prevlink;

	return item;	//NOSONAR - We want to return whatever item points at
}

//***********************************************************************

template <class T> inline gzVoid gzListIterator<T>::reset()
{
	m_link=0;
	m_prevlink=0;
	m_circulating=FALSE;
}

//***********************************************************************

template <class T> inline T *gzListIterator<T>::operator()()
{
	if((m_prevlink=m_link))
		m_link=m_link->next;
	else
		m_link=m_owner->m_link;

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline T *gzListIterator<T>::operator++(int)
{
	return operator()();
}

//***********************************************************************

template <class T> inline T *gzListIterator<T>::circulate()
{
	m_circulating=TRUE;

	m_prevlink=m_link;

	if(m_link)
		m_link=m_link->next;

	if(!m_link)
	{
		m_link=m_owner->m_link;
		m_prevlink=0;
	}

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline T *gzListIterator<T>::key() const
{
	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline T *gzListIterator<T>::next() const
{
	if(m_link)
	{
		if(m_link->next)
			return m_link->next->item;
		else if(m_circulating)
			return m_owner->m_link->item;
	}
	return NULL;
}

//******************************************************************************
// Template	: gzListConstIterator
//									
// Purpose  : Constant Iterator for gzList
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040301	Created 
//									
//******************************************************************************
//! Const Iterator class for gzList

/*! The Iterator can be used with all gzLists and its derivatives. Typical usage is to use
it as follows...

\code

	gzListConstIterator<MyListItemClass>	iterator(myActualList);
	const MyListItemClass *item;

	while((item=iterator()))
	{
		// Do somthing with item that is iterated through the list
	}

\endcode
*/
template <class T> class gzListConstIterator 
{
	public:

		//! Constructor of list iterator
		gzListConstIterator(const gzList<T> &owner);

		//! Default destructor
		~gzListConstIterator(){};

		//! Iterating operator
		/*! The operator () iterates one step through list and returns item 
			at current list iterator position. At end of list it returns NULL */
		T *operator()();

		T *operator++(int);	// postfix operator

		//! Circulating operator
		/*! The circulate() method iterates through the list just like the () operator, but
			it restarts at the beginnig of the list when the end is reached. */
		T *circulate();

		//! Returns item at current iterator position.
		/*! Undefined if iterator position is undefined e.g. before operator () is called. */
		T *key() const;

		//! Returns one item ahead in list. You can get the next item without iterating.
		T *next() const;

		//! Reset iterator position to start of list
		gzVoid reset();

		//! Get current key sortval
		gzDouble sortval() const;

		//! Re-use itarator with another list
		gzVoid setList(const gzList<T> &owner);


	private:
	
		typename gzList<T>::LinkItem *m_link;

		typename gzList<T>::LinkItem *m_prevlink;

		const gzList<T> *	m_owner;

		gzBool		m_circulating;

};

//***********************************************************************

template <class T> inline gzBool gzList<T>::contains(const T *item) const 
{
	const typename gzList<T>::LinkItem* link = m_link;
		
	while (link)
	{
		if (link->item == item)
		{
			return TRUE;
		}

		link = link->next;
	}
	
	return FALSE;
}

//***********************************************************************

template <class T> inline gzInt32 gzList<T>::index(const T *item) const 
{
	const typename gzList<T>::LinkItem* link = m_link;

	gzInt32 index(0);
		
	while (link)
	{
		if (link->item == item)
		{
			return index;
		}

		++index;
		link = link->next;
	}
	
	return -1;
}

//***********************************************************************

template <class T> inline gzListConstIterator<T>::gzListConstIterator(const gzList<T> &owner)
{
	m_link=0;
	m_prevlink=0;
	m_circulating=FALSE;
	m_owner=&owner;
}

//***********************************************************************

template <class T> inline gzDouble gzListConstIterator<T>::sortval() const
{
	if(m_link)
		return m_link->sortval;
	else
		return 0;
}

//***********************************************************************

template <class T> inline gzVoid gzListConstIterator<T>::reset()
{
	m_link=0;
	m_prevlink=0;
	m_circulating=FALSE;
}

//***********************************************************************

template <class T> inline gzVoid gzListConstIterator<T>::setList(const gzList<T> &owner)
{
	m_link=0;
	m_prevlink=0;
	m_owner=&owner;
}

//***********************************************************************

template <class T> inline T *gzListConstIterator<T>::operator()()
{
	if((m_prevlink=m_link))
		m_link=m_link->next;
	else
		m_link=m_owner->m_link;

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline T *gzListConstIterator<T>::operator++(int)
{
	return operator()();
}

//***********************************************************************

template <class T> inline T *gzListConstIterator<T>::circulate()
{
	m_circulating=TRUE;

	m_prevlink=m_link;

	if(m_link)
		m_link=m_link->next;

	if(!m_link)
	{
		m_link=m_owner->m_link;
		m_prevlink=0;
	}

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline T *gzListConstIterator<T>::key() const
{
	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline T *gzListConstIterator<T>::next() const
{
	if(m_link)
	{
		if(m_link->next)
			return m_link->next->item;
		else if(m_circulating)
			return m_owner->m_link->item;
	}
	return NULL;
}

//***********************************************************************

template <class T> class gzDynamicArray;

//******************************************************************************
// Template	: gzArray
//									
// Purpose  : Array template
//									
// Notes	: gzArray uses storage by value, not by reference
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980601	Created 
//									
//******************************************************************************
/*! \brief Template class for arrays

The gzArray is a template class that contains an array with fast access to retreive
and store items in the array. 

*/

template <class T> class gzArray 
{
public:
	gzArray(const gzUInt32 size=0);
	virtual ~gzArray();

	gzArray( const gzArray &copy);

	const gzUInt32 &	getSize() const ;

	gzVoid		setSize(const gzUInt32 size);

	gzVoid		setPOTSize(const gzUInt32 pot_size);

	T &			operator []( const gzUInt32 index );

	const T&	get(const gzUInt32 index) const;

	const T&	operator +=(const T& value);

	gzArray&	operator +=(const gzArray &copy);

	gzArray		operator +(const gzArray &add);

	gzArray&	operator=(const gzArray &copy);

	gzBool		operator==(const gzArray &compare) const;

	gzBool		operator!=(const gzArray &compare) const;

	T *			getAddress();

	const T*	getConstAddress() const {return m_data;};

	gzVoid		resize(const gzUInt32 newSize);

	gzVoid		resize(const gzUInt32 newSize,const T& defaultValue);

	gzVoid		remove(const gzUInt32 index);

	gzBool		contains(const T &item) const;

	//! Utility to swap the contents of two instanses by exchanging data poiners
	gzVoid		swapArrayData(gzArray &swapper);

	//! Set the whole array to one value
	gzVoid		setAll(const T& data);

	//! Set some part of the array to one value
	gzVoid		setSome(gzUInt32 index,gzUInt32 size,const T& data);

	//! Multiply the whole array with one value
	gzVoid		itemMultiply(const T& data);

	//! Multiply some of the array with one value
	gzVoid		itemMultiply(gzUInt32 index,gzUInt32 size,const T& data);

	//! Utility to set size and data at once
	gzVoid		setArrayData(const T* data, gzUInt32 length);

	gzVoid		setUntouched()	{ m_untouched=TRUE; }
	gzVoid		setTouched()	{ m_untouched=FALSE; }
	gzBool		isUntouched()	const { return m_untouched; }

protected:

	friend class gzDynamicArray<T>;

	// Access without boundary check
	const T &	getItemInternal(const gzUInt32 index) const;
	gzVoid		setItemInternal(const gzUInt32 index,const T &val);

	T			*m_data;

	gzUInt32	m_size;

	gzBool		m_untouched;	// Indicates that data has not been changed since last untouch
};

//***********************************************************************

template <class T> inline gzVoid gzArray<T>::swapArrayData(gzArray<T> &swapper)
{
	T			*data(m_data);
	gzUInt32		size(m_size);

	m_data=swapper.m_data;
	m_size=swapper.m_size;

	swapper.m_data=data;
	swapper.m_size=size;

	m_untouched=FALSE;
}

//***********************************************************************

template <class T> inline gzVoid gzArray<T>::setArrayData(const T* data, gzUInt32 length)
{
	setSize(length);

	T* to=m_data;

	while(length)
	{
		*to=*data;
		++to;
		++data;
		--length;
	}

	m_untouched=FALSE;
}

//**********************************************************************

template <> inline gzVoid gzArray<gzUByte>::setArrayData(const gzUByte * data, gzUInt32 length)
{
	setSize(length);

	memcpy(m_data,data,length);

	m_untouched=FALSE;
}

template <> inline gzVoid gzArray<gzQWA_UByte>::setArrayData(const gzQWA_UByte * data, gzUInt32 length)
{
	setSize(length);

	memcpy(&m_data->data,&data->data,length);

	m_untouched=FALSE;
}

template <> inline gzVoid gzArray<gzQWA_Byte>::setArrayData(const gzQWA_Byte * data, gzUInt32 length)
{
	setSize(length);

	memcpy(&m_data->data,&data->data,length);

	m_untouched=FALSE;
}

template <> inline gzVoid gzArray<gzQWA_UInt16>::setArrayData(const gzQWA_UInt16 * data, gzUInt32 length)
{
	setSize(length);

	memcpy(&m_data->data,&data->data,length*sizeof(gzQWA_UInt16));

	m_untouched=FALSE;
}

template <> inline gzVoid gzArray<gzQWA_Int16>::setArrayData(const gzQWA_Int16 * data, gzUInt32 length)
{
	setSize(length);

	memcpy(&m_data->data,&data->data,length*sizeof(gzQWA_Int16));

	m_untouched=FALSE;
}

template <class T> inline gzVoid gzArray<T>::setAll(const T& data)
{
	T *pek=m_data;

	gzUInt32 size(m_size);

	while(size--)
	{
		*pek=data;
		++pek;
	}

	m_untouched=FALSE;
}

template <> inline gzVoid gzArray<gzDouble>::setAll(const gzDouble& data)
{
	if(data==0.0)
	{
		memset(m_data,0,m_size*sizeof(gzDouble));
	}
	else
	{
		gzDouble *pek=m_data;

		gzUInt32 size(m_size);

		while(size--)
		{
			*pek=data;
			++pek;
		}
	}

	m_untouched=FALSE;
}

template <> inline gzVoid gzArray<gzFloat>::setAll(const gzFloat& data)
{
	if(data==0.0)
	{
		memset(m_data,0,m_size*sizeof(gzFloat));
	}
	else
	{
		gzFloat *pek=m_data;

		gzUInt32 size(m_size);

		while(size--)
		{
			*pek=data;
			++pek;
		}
	}

	m_untouched=FALSE;
}

template <class T> inline gzVoid gzArray<T>::setSome(gzUInt32 index,gzUInt32 size,const T& data)
{
	if((size+index)>m_size)
		throwFatalTemplateError("gzArray::setSome() index out of bounds");

	T *pek=m_data+index;

	while(size--)
	{
		*pek=data;
		++pek;
	}

	m_untouched=FALSE;
}

template <> inline gzVoid gzArray<gzDouble>::setSome(gzUInt32 index,gzUInt32 size,const gzDouble& data)
{
	if((size+index)>m_size)
		throwFatalTemplateError("gzArray::setSome() index out of bounds");

	if(data==0.0)
	{
		memset(m_data+index,0,size*sizeof(gzDouble));
	}
	else
	{
		gzDouble *pek=m_data+index;

		while(size--)
		{
			*pek=data;
			++pek;
		}
	}

	m_untouched=FALSE;
}

template <> inline gzVoid gzArray<gzFloat>::setSome(gzUInt32 index,gzUInt32 size,const gzFloat& data)
{
	if((size+index)>m_size)
		throwFatalTemplateError("gzArray::setSome() index out of bounds");

	if(data==0.0f)
	{
		memset(m_data+index,0,size*sizeof(gzFloat));
	}
	else
	{
		gzFloat *pek=m_data+index;

		while(size--)
		{
			*pek=data;
			++pek;
		}
	}

	m_untouched=FALSE;
}

template <class T> inline gzVoid gzArray<T>::itemMultiply(const T& data)
{
	T *pek=m_data;

	gzUInt32 size(m_size);

	while(size)
	{
		*pek=*pek*data;
		++pek;
		--size;
	}

	m_untouched=FALSE;
}

template <class T> inline gzVoid gzArray<T>::itemMultiply(gzUInt32 index,gzUInt32 size,const T& data)
{
	if((size+index)>m_size)
		throwFatalTemplateError("gzArray::itemMultiply() index out of bounds");

	T *pek=m_data+index;

	while(size)
	{
		*pek=*pek*data;
		++pek;
		--size;
	}

	m_untouched=FALSE;
}

//***********************************************************************

template <class T> inline T * gzArray<T>::getAddress()
{
	m_untouched=FALSE;

	return m_data;
}

//***********************************************************************
		
template <class T> inline gzArray<T>::gzArray(const gzUInt32 size)
{
	if(size)
		m_data = new T[size];
	else
		m_data=nullptr;

	m_size=size;

	m_untouched=FALSE;
}

//***********************************************************************

template <class T> inline gzArray<T>::~gzArray()
{
	if(m_data)
		delete [] m_data;
}

//***********************************************************************

template <class T> inline gzVoid gzArray<T>::remove(const gzUInt32 index)
{
	if(m_size)
	{
		for(gzUInt32 i=index;i<m_size-1;i++)
			m_data[i]=m_data[i+1];

		m_size--;
	}
}

//***********************************************************************

template <class T> inline gzBool gzArray<T>::contains(const T &item) const
{
	for(gzUInt32 i=0;i<m_size;i++)
		if(m_data[i]==item)
			return TRUE;

	return FALSE;
}

//***********************************************************************

template <class T> inline gzBool gzArray<T>::operator==(const gzArray &compare) const
{
	if(m_size!=compare.m_size)
		return FALSE;

	gzUInt32 i;

	for(i=0;i<m_size;++i)
		if(m_data[i]!=compare.m_data[i])
			return FALSE;

	return TRUE;
}

template <> inline gzBool gzArray<gzUByte>::operator==(const gzArray &compare) const
{
	if(m_size!=compare.m_size)
		return FALSE;

	return !memcmp(m_data,compare.m_data,m_size);
}

template <> inline gzBool gzArray<gzQWA_UByte>::operator==(const gzArray &compare) const
{
	if(m_size!=compare.m_size)
		return FALSE;

	return !memcmp(m_data,compare.m_data,m_size*sizeof(gzQWA_UByte));
}

template <> inline gzBool gzArray<gzQWA_Byte>::operator==(const gzArray &compare) const
{
	if(m_size!=compare.m_size)
		return FALSE;

	return !memcmp(m_data,compare.m_data,m_size * sizeof(gzQWA_Byte));
}

template <> inline gzBool gzArray<gzQWA_UInt16>::operator==(const gzArray &compare) const
{
	if(m_size!=compare.m_size)
		return FALSE;

	return !memcmp(m_data,compare.m_data,m_size*sizeof(gzQWA_UInt16));
}

template <> inline gzBool gzArray<gzQWA_Int16>::operator==(const gzArray &compare) const
{
	if(m_size!=compare.m_size)
		return FALSE;

	return !memcmp(m_data,compare.m_data,m_size*sizeof(gzQWA_Int16));
}

template <> inline gzBool gzArray<gzFloat>::operator==(const gzArray &compare) const
{
	if(m_size!=compare.m_size)
		return FALSE;

	return !memcmp(m_data,compare.m_data,m_size * sizeof(gzFloat));
}

template <> inline gzBool gzArray<gzDouble>::operator==(const gzArray &compare) const
{
	if(m_size!=compare.m_size)
		return FALSE;

	return !memcmp(m_data,compare.m_data,m_size*sizeof(gzDouble));
}

template <> inline gzBool gzArray<gzUInt32>::operator==(const gzArray &compare) const
{
	if(m_size!=compare.m_size)
		return FALSE;

	return !memcmp(m_data,compare.m_data,m_size * sizeof(gzUInt32));
}
//***********************************************************************

template <class T> inline gzBool gzArray<T>::operator!=(const gzArray &compare) const
{
	return ! operator==(compare);
}

//***********************************************************************

template <class T> inline const T& gzArray<T>::operator +=(const T& value)
{
	T* m_new_data=new T[m_size+1];

	copyInstances<T>(m_new_data, m_data, m_size);

	m_new_data[m_size]=value;

	if(m_data)
		delete [] m_data;

	m_data=m_new_data;

	++m_size;

	m_untouched=FALSE;

	return m_new_data[m_size-1];
}

//***********************************************************************

template <class T> inline gzArray<T> & gzArray<T>::operator=(const gzArray &copy)
{
	if(&copy==this)
		return *this;

	if(m_size<copy.m_size)	// Allow shrink
	{
		if(m_data)
			delete [] m_data;

		m_size=copy.m_size;

		if(copy.m_size)
		{
			m_data = new T[copy.m_size];
		}
		else
			m_data=nullptr;
	}
	else
		m_size=copy.m_size;

	copyInstances<T>(m_data, copy.m_data, m_size);

	m_untouched=copy.m_untouched;
	
	return *this;
}

//***********************************************************************

template <class T> inline gzArray<T>::gzArray( const gzArray &copy)
{
	m_size=copy.m_size;

	if(m_size)
	{
		m_data = new T[m_size];

		copyInstances<T>(m_data, copy.m_data, m_size);
	}
	else
		m_data=nullptr;

	m_untouched=copy.m_untouched;
}

//***********************************************************************

template <class T> inline T& gzArray<T>::operator []( const gzUInt32 index )
{
	if(index>=m_size )
		throwFatalTemplateError("gzArray [] index out of bounds");

	m_untouched=FALSE;

	return m_data[index];
}

//***********************************************************************

template <class T> inline const T&	gzArray<T>::get(const gzUInt32 index) const
{
	if(index>=m_size )
		throwFatalTemplateError("gzArray get() index out of bounds");

	return m_data[index];
}

//***********************************************************************

// Access without boundary check

template <class T> inline const T & gzArray<T>::getItemInternal(const gzUInt32 index) const
{
	return m_data[index];
}

//***********************************************************************

// Access without boundary check

template <class T> inline gzVoid gzArray<T>::setItemInternal(const gzUInt32 index,const T &val)
{
	m_untouched=FALSE;
	m_data[index]=val;
}


//***********************************************************************

template <class T> inline const gzUInt32 &gzArray<T>::getSize() const
{
	return m_size;
}

//***********************************************************************

template <class T> inline gzVoid gzArray<T>::setSize(gzUInt32 size)
{
	if(size==m_size)
		return;

	if(size>m_size)
	{
		if(m_data)
			delete [] m_data;

		m_data = new T[size];
	}
	else if (!size)
	{
		if(m_data)
			delete [] m_data;

		m_data=nullptr;
	}

	m_size=size;

	m_untouched=FALSE;
}

//***********************************************************************

template <class T> inline gzVoid gzArray<T>::setPOTSize(const gzUInt32 pot_size)
{
	gzArray<T>::setSize(1UL<<pot_size);
}

//***********************************************************************
template <class T> inline gzVoid gzArray<T>::resize(gzUInt32 size,const T& defaultValue)
{
	if(size==m_size)
		return;

	if(size>m_size)
	{
		if(m_data)
		{
			T *newData=new T[size];

			gzUInt32 i;

			for(i=0;i<m_size;i++)
				newData[i]=m_data[i];

			for(i=m_size;i<size;i++)
				newData[i]=defaultValue;

			delete [] m_data;

			m_data=newData;
		}
		else
		{
			m_data = new T[size];

			for(gzUInt32 i=0;i<size;i++)
				m_data[i]=defaultValue;
		}
	}
	else if (!size)
	{
		if(m_data)
			delete [] m_data;

		m_data=nullptr;
	}

	m_size=size;

	m_untouched=FALSE;
}

//***********************************************************************

template <class T> inline gzVoid gzArray<T>::resize(gzUInt32 size)
{
	if(size==m_size)
		return;

	if(size>m_size)
	{
		if(m_data)
		{
			T *newData=new T[size];

			for(gzUInt32 i=0;i<m_size;i++)
				newData[i]=m_data[i];

			delete [] m_data;

			m_data=newData;
		}
		else
			m_data = new T[size];
	}
	else if (!size)
	{
		if(m_data)
			delete [] m_data;

		m_data=nullptr;
	}

	m_size=size;

	m_untouched=FALSE;
}

//***********************************************************************

template <class T> inline gzArray<T> gzArray<T>::operator +(const gzArray &add)
{
	gzUInt32 i;

	gzArray<T> array(m_size+add.m_size);

	for(i=0;i<m_size;++i)
		array.m_data[i]=m_data[i];

	for(i=0;i<add.m_size;++i)
		array.m_data[i+m_size]=add.m_data[i];

	return array;
}

//***********************************************************************

template <class T> inline gzArray<T> & gzArray<T>::operator +=(const gzArray &add)
{
	if(!add.m_size)
		return *this;
	
	gzUInt32 newSize=m_size+add.m_size;
	
	T *to,*from,*data=new T[newSize];

	gzUInt32 i;

	to=data;

	from=m_data;

	for(i=0;i<m_size;++i)
	{
		*to=*from;
		++to;++from;
	}

	from=add.m_data;
	
	for(i=0;i<add.m_size;++i)
	{
		*to=*from;
		++to;++from;
	}

	if(m_data)
		delete [] m_data;

	m_data=data;

	m_size=newSize;

	m_untouched=FALSE;

	return *this;
}

template <> inline gzArray<gzUByte> & gzArray<gzUByte>::operator +=(const gzArray &add)
{
	if(!add.m_size)
		return *this;

	gzUInt32 newSize=m_size+add.m_size;

	gzUByte *data=new gzUByte[newSize];

	memcpy(data,m_data,m_size);

	memcpy(data+m_size,add.m_data,add.m_size);

	if(m_data)
		delete [] m_data;

	m_data=data;

	m_size+=add.m_size;

	m_untouched=FALSE;

	return *this;
}

template <> inline gzArray<gzQWA_UByte> & gzArray<gzQWA_UByte>::operator +=(const gzArray &add)
{
	if(!add.m_size)
		return *this;

	gzUInt32 newSize=m_size+add.m_size;

	gzQWA_UByte *data=new gzQWA_UByte[newSize];

	memcpy(&data->data,&m_data->data,m_size);

	memcpy(&data->data+m_size,&add.m_data->data,add.m_size);

	if(m_data)
		delete [] m_data;

	m_data=data;

	m_size+=add.m_size;

	m_untouched=FALSE;

	return *this;
}

template <> inline gzArray<gzQWA_Byte> & gzArray<gzQWA_Byte>::operator +=(const gzArray &add)
{
	if(!add.m_size)
		return *this;

	gzUInt32 newSize=m_size+add.m_size;

	gzQWA_Byte *data=new gzQWA_Byte[newSize];

	memcpy(&data->data,&m_data->data,m_size);

	memcpy(&data->data+m_size,&add.m_data->data,add.m_size);

	if(m_data)
		delete [] m_data;

	m_data=data;

	m_size+=add.m_size;

	m_untouched=FALSE;

	return *this;
}

template <> inline gzArray<gzQWA_UInt16> & gzArray<gzQWA_UInt16>::operator +=(const gzArray &add)
{
	if(!add.m_size)
		return *this;

	gzUInt32 newSize=m_size+add.m_size;

	gzQWA_UInt16 *data=new gzQWA_UInt16[newSize];

	memcpy(&data->data,&m_data->data,m_size);

	memcpy(&data->data+m_size,&add.m_data->data,add.m_size);

	if(m_data)
		delete [] m_data;

	m_data=data;

	m_size+=add.m_size;

	m_untouched=FALSE;

	return *this;
}

template <> inline gzArray<gzQWA_Int16> & gzArray<gzQWA_Int16>::operator +=(const gzArray &add)
{
	if(!add.m_size)
		return *this;

	gzUInt32 newSize=m_size+add.m_size;

	gzQWA_Int16 *data=new gzQWA_Int16[newSize];

	memcpy(&data->data,&m_data->data,m_size);

	memcpy(&data->data+m_size,&add.m_data->data,add.m_size);

	if(m_data)
		delete [] m_data;

	m_data=data;

	m_size+=add.m_size;

	m_untouched=FALSE;

	return *this;
}

template <class T> class gzQueue;

//******************************************************************************
// Template	: gzDynamicArray
//									
// Purpose  : Fast allocation Array template
//									
// Notes	: gzDynamicArray uses storage by value, not by reference
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981201	Created 
//									
//******************************************************************************
/*! \brief Template class for dynamic arrays

The gzDynamicArray is a template class that contains a dynamic sizeable array with fast access to retreive
and store items in the array. If your index is larger than the size of the array, it automatically resizes
the array to hold the new indexed item.

*/

template <class T> class gzDynamicArray 
{
public:
	gzDynamicArray(const gzUInt32 &chunkSize=100,const gzUInt32 &realSize=0);
	~gzDynamicArray();

	gzDynamicArray( const gzDynamicArray &copy);

	gzDynamicArray( const gzArray<T> &copy);

	gzUInt32	getSize() const ;

	gzVoid		setSize( const gzUInt32 newsize, gzInt32 copy_offset = 0);

	gzUInt32	getRealSize() const ;

	gzVoid		setRealSize(const gzUInt32 size,gzInt32 copy_offset=0);

	gzVoid		setChunkSize(const gzUInt32 i){ if(i)m_chunksize=i;else m_chunksize=1; }

	gzUInt32	getChunkSize() const { return m_chunksize; }

	T &			operator []( const gzUInt32 index );

	const T&	operator []( const gzUInt32 index ) const;

	const T&	get(const gzUInt32 index) const;

	gzVoid		operator +=(const T &value);

	gzVoid		append(const gzDynamicArray& add);

	gzVoid		append(const T *data,const gzUInt32 len);

				operator gzArray<T> () const;

	gzBool		operator==(const gzDynamicArray &compare) const;

	gzBool		operator!=(const gzDynamicArray &compare) const;

	gzDynamicArray operator +(const gzDynamicArray &add);

	gzDynamicArray&	operator=(const gzDynamicArray &copy);

	T *			getAddress() { return m_data; }

	const T *	getConstAddress() const  { return m_data; };

	gzVoid		transferToArray(gzArray<T> &array) const;

	//! Set the whole array to one value
	gzVoid		setAll(const T& data);

	//! Utility to swap the contents of two instanses by exchanging data poiners
	gzVoid		swapArrayData(gzDynamicArray &swapper);

	//! Utility to swap the contents of two instanses by exchanging data poiners
	gzVoid		swapArrayData(gzArray<T>& swapper);

	//! Set size and data in array
	gzVoid		setArrayData(const T* data,const gzUInt32 length);

	T &			last();

	gzVoid		removeLast();

	gzVoid		remove(gzUInt32 index);

	gzVoid		insertAt(gzUInt32 index, const T &value);

	gzBool		contains(const T &item) const;

private:
	
	friend class gzQueue<T>;

	T *			m_data;
	gzUInt32	m_size;
	gzUInt32	m_currentSize;
	gzUInt32	m_chunksize;
};

//***********************************************************************

template <class T> inline gzVoid gzDynamicArray<T>::swapArrayData(gzDynamicArray<T> &swapper)
{
	T			*data(m_data);
	gzUInt32	size(m_size);
	gzUInt32	currentSize(m_currentSize);

	m_data=swapper.m_data;
	m_size=swapper.m_size;
	m_currentSize=swapper.m_currentSize;

	swapper.m_data=data;
	swapper.m_size=size;
	swapper.m_currentSize=currentSize;
}

//***********************************************************************

template <class T> inline gzVoid gzDynamicArray<T>::swapArrayData(gzArray<T>& swapper)
{
	T* data(m_data);
	gzUInt32	currentSize(m_currentSize);

	m_data = swapper.m_data;
	m_size = swapper.m_size;
	m_currentSize = swapper.m_size;

	swapper.m_data = data;
	swapper.m_size = currentSize;
}

//**********************************************************************

template <class T> inline gzVoid gzDynamicArray<T>::setArrayData(const T* data, gzUInt32 length)
{
	setSize(length);

	T* to=m_data;

	while(length)
	{
		*to=*data;
		++to;
		++data;
		--length;
	}
}

//**********************************************************************

template <> inline gzVoid gzDynamicArray<gzUByte>::setArrayData(const gzUByte* data, gzUInt32 length)
{
	setSize(length);

	memcpy(m_data,data,length);
}

//**********************************************************************

template <class T> inline gzVoid gzDynamicArray<T>::setAll(const T& data)
{
	T *pek=m_data;

	gzUInt32 size(m_currentSize);

	while(size--)
	{
		*pek=data;
		++pek;
	}
}

template <> inline gzVoid gzDynamicArray<gzDouble>::setAll(const gzDouble& data)
{
	if(data==0.0)
	{
		memset(m_data,0, m_currentSize *sizeof(gzDouble));
	}
	else
	{
		gzDouble *pek=m_data;

		gzUInt32 size(m_currentSize);

		while(size--)
		{
			*pek=data;
			++pek;
		}
	}
}

//*********************************************************************

template <> inline gzVoid gzDynamicArray<gzFloat>::setAll(const gzFloat& data)
{
	if(data==0.0)
	{
		memset(m_data,0, m_currentSize *sizeof(gzFloat));
	}
	else
	{
		gzFloat *pek=m_data;

		gzUInt32 size(m_currentSize);

		while(size--)
		{
			*pek=data;
			++pek;
		}
	}
}

//*********************************************************************

template <class T> inline gzDynamicArray<T>::gzDynamicArray(const gzUInt32 &chunkSize,const gzUInt32 &realSize)
{
	if(chunkSize)
		m_chunksize=chunkSize;
	else
		m_chunksize=1;

	m_data=nullptr;

	m_size=0;
	m_currentSize=0;

	if(realSize)
		setRealSize(realSize);
}

//***********************************************************************

template <class T> inline gzDynamicArray<T>::~gzDynamicArray()
{
	if(m_data)
		delete [] m_data;
}

//***********************************************************************

template <class T> inline gzVoid gzDynamicArray<T>::transferToArray(gzArray<T> &array) const
{
	array.setSize(m_currentSize);

	if(m_currentSize)
		copyInstances<T>(array.getAddress(), m_data, m_currentSize);
}

//***********************************************************************

template <class T> inline gzBool gzDynamicArray<T>::contains(const T &item) const
{
	for(gzUInt32 i=0;i< m_currentSize;i++)
		if(m_data[i]==item)
			return TRUE;

	return FALSE;
}

//***********************************************************************

template <class T> inline gzDynamicArray<T>::operator gzArray<T> () const
{
	gzArray<T> array;

	transferToArray(array);

	return array;
}

//***********************************************************************

template <class T> inline gzVoid gzDynamicArray<T>::operator +=(const T &value)
{
	(operator [](m_currentSize))=value;
}

template <class T> inline gzVoid gzDynamicArray<T>::append(const T *data,const gzUInt32 len)
{
	gzUInt32 oldlen(m_currentSize);
	setSize(oldlen+len);

	for(gzUInt32 i=0;i<len;i++)
		*(m_data+oldlen+i)=data[i];
}

template <> inline gzVoid gzDynamicArray<gzUByte>::append(const gzUByte *data,const gzUInt32 len)
{
	gzUInt32 oldlen(m_currentSize);
	setSize(oldlen+len);

	if(m_data && m_size)
		memcpy(m_data+oldlen,data,len);
}

//***********************************************************************

template <class T> inline gzDynamicArray<T>& gzDynamicArray<T>::operator=(const gzDynamicArray &copy)
{
	if(&copy==this)
		return *this;

	m_currentSize=copy.m_currentSize;

	if(m_currentSize>m_size)
	{
		if(m_data)
			delete [] m_data;

		m_data = new T[m_currentSize];

		m_size=m_currentSize;
	}

	copyInstances<T>(m_data, copy.m_data, m_currentSize);
	
	m_chunksize=copy.m_chunksize;

	return *this;
}

//***********************************************************************

template <class T> inline gzBool gzDynamicArray<T>::operator==(const gzDynamicArray &compare) const
{
	if(m_currentSize!=compare.m_currentSize)
		return FALSE;

	gzUInt32 i;

	for(i=0;i<m_currentSize;++i)
		if(m_data[i]!=compare.m_data[i])
			return FALSE;

	return TRUE;
}

//***********************************************************************

template <class T> inline gzBool gzDynamicArray<T>::operator!=(const gzDynamicArray &compare) const
{
	return ! operator==(compare);
}

//***********************************************************************

template <class T> inline gzDynamicArray<T>::gzDynamicArray( const gzArray<T> &copy)
{
	gzUInt32 i;

	if(copy.getSize())
		m_data = new T[copy.getSize()];
	else
		m_data=nullptr;

	m_size=copy.getSize();
	m_currentSize=m_size;
	m_chunksize=100;

	for(i=0;i<m_currentSize;++i)
		m_data[i]=copy.m_data[i];
}

//***********************************************************************

template <class T> inline gzDynamicArray<T>::gzDynamicArray( const gzDynamicArray &copy)
{
	gzUInt32 i;

	if(copy.m_size)
	{
		m_data = new T[copy.m_size];
		m_size=copy.m_size;
		m_currentSize=copy.m_currentSize;

		for(i=0;i<m_currentSize;++i)
			m_data[i]=copy.m_data[i];
	}
	else
	{
		m_data=nullptr;
		m_size=0;
		m_currentSize=0;
	}

	m_chunksize=copy.m_chunksize;
}

//***********************************************************************

template <class T> inline T & gzDynamicArray<T>::last()
{
	if(m_currentSize)
		return  *(m_data+m_currentSize-1);
	else
	{
		throwFatalTemplateError("no last() item in gzDynamicArray");
		return *m_data; // to avoid warning
	}
}

//***********************************************************************

template <class T> inline gzVoid gzDynamicArray<T>::removeLast()
{
	if(m_currentSize)
		--m_currentSize;
}

//***********************************************************************

template <class T> inline gzVoid gzDynamicArray<T>::remove(gzUInt32 index)
{
	if(index<m_currentSize)
	{
		--m_currentSize;
		for(gzUInt32 i=index;i<m_currentSize;i++)
			m_data[i]=m_data[i+1];
	}
}

//***********************************************************************

template <class T> inline gzVoid gzDynamicArray<T>::insertAt(gzUInt32 index, const T &value)
{
	if (index < m_currentSize)
	{
		setSize(m_currentSize + 1);

		for (gzUInt32 i = m_currentSize - 1; i > index; i--)
			m_data[i] = m_data[i - 1];

		m_data[index] = value;
	}
	else
		operator[](index) = value;
}

//***********************************************************************

template <class T> inline T& gzDynamicArray<T>::operator []( const gzUInt32 index )
{
	if (index >= m_currentSize)
	{
		if (index >= m_size)
		{
			setRealSize(((gzUInt32)(index / m_chunksize) + 1) * m_chunksize);
		}
		m_currentSize = index + 1;
	}

	if(!m_data || index>=m_size)
		throwFatalTemplateError("const gzDynamicArray::[] index out of bounds");

	return  *(m_data+index);
}

//***********************************************************************

template <class T> inline const T& gzDynamicArray<T>::operator []( const gzUInt32 index ) const
{
	if(index>=m_currentSize)
	{
		throwFatalTemplateError("const gzDynamicArray::[] index out of bounds");
	}

	return  *(m_data+index);
}

//***********************************************************************

template <class T> inline const T& gzDynamicArray<T>::get(const gzUInt32 index) const
{
	if(index>=m_currentSize)
	{
		throwFatalTemplateError("const gzDynamicArray::get() index out of bounds");
	}

	return  *(m_data+index);
}

//***********************************************************************

template <class T> inline gzUInt32 gzDynamicArray<T>::getSize() const
{
	return m_currentSize;
}

//***********************************************************************

template <class T> inline gzVoid  gzDynamicArray<T>::setSize( const gzUInt32 newsize , gzInt32 copy_offset)
{
	if (newsize > m_size)
	{
		if (newsize % m_chunksize)
			setRealSize(((gzUInt32)(newsize / m_chunksize) + 1) * m_chunksize, copy_offset);
		else
			setRealSize(newsize, copy_offset);
	}
	else if (copy_offset > 0)	// Or offset moves within same allocation up
		copyInstances<T>(m_data + copy_offset, m_data, gzMax<gzInt32>(0, gzMax<gzInt32>(newsize, m_currentSize) - copy_offset), TRUE);
	else if (copy_offset < 0)	// move down
		copyInstances<T>(m_data, m_data - copy_offset, gzMax<gzInt32>(0, gzMax<gzInt32>(newsize, m_currentSize) + copy_offset), TRUE);

	m_currentSize=newsize;
}

//***********************************************************************

template <class T> inline gzUInt32 gzDynamicArray<T>::getRealSize() const
{
	return m_size;
}

//***********************************************************************

template <class T> inline gzVoid gzDynamicArray<T>::setRealSize(const gzUInt32 size,gzInt32 copy_offset)
{
	
	T* from = m_data;
	T* to = NULL;

	if (size)	// We have a new size
		to = new T[size];

	if (m_currentSize && from && to)
	{
		if (copy_offset < 0)					// copy from source to lower indexes
			copyInstances<T>(to, from - copy_offset, gzMax<gzInt32>(0, gzMin<gzInt32>(m_currentSize + copy_offset, size)));
		else
			copyInstances<T>(to + copy_offset, from, gzMax<gzInt32>(0,gzMin<gzInt32>(m_currentSize, size - copy_offset)));
	}

	if (m_data)
		delete[] m_data;

	m_data = to;
	m_size = size;
	m_currentSize = gzMin(m_currentSize, m_size);
}


//***********************************************************************

template <class T> inline gzDynamicArray<T> gzDynamicArray<T>::operator +(const gzDynamicArray &add)
{
	gzUInt32 i;

	gzDynamicArray<T> array(*this);

	for(i=0;i<add.m_currentSize;++i)
		array[i+m_currentSize]=add.m_data[i];

	return array;
}

//***********************************************************************

template <class T> inline gzVoid gzDynamicArray<T>::append(const gzDynamicArray& add)
{
	for (gzUInt32 i = 0; i < add.m_currentSize; ++i)
		operator +=(add.m_data[i]);
}

//***********************************************************************

template <class T1 , class T2> class gzDict;
template <class T1 , class T2> class gzDictIterator;
template <class T1 , class T2> class gzDictConstIterator;
template <class T1 , class T2> class gzDictArray;

//******************************************************************************
// Template	: gzDictEntry
//									
// Purpose  : Entry private class for dictionary entries
//									
// Notes	: only accessable from gzDict
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980601	Created 
//									
//******************************************************************************
template <class T1 , class T2> class gzDictEntry 
{
public:

	gzDictEntry(const T1 &key,T2 *pek):m_key(key),m_pek(pek),m_hash(key.hash()){}
	gzDictEntry(const T1 &key,T2 *pek,gzUInt32 hash):m_key(key),m_pek(pek),m_hash(hash){}
	
	const T1 &	getKey()		const	{ return m_key;		};
	T2 *		getData()		const	{ return m_pek;		};
	const T2 *	getConstData()	const	{ return m_pek;		};
	gzUInt32	getHash()		const	{ return m_hash;	};

	gzDictEntry<T1,T2> * set(const T1 &key,T2 *pek)					{ m_key=key;m_pek=pek;m_hash=key.hash(); return this;}
	gzDictEntry<T1,T2> * set(const T1 &key,T2 *pek,gzUInt32 hash)	{ m_key=key;m_pek=pek;m_hash=hash; return this;}

private:

	friend class gzDict<T1,T2>;
	friend class gzDictIterator<T1,T2>;
	friend class gzDictArray<T1,T2>;

	T1		m_key;
	T2 *	m_pek;
	gzUInt32 m_hash;
};

//******************************************************************************
// Template	: gzDictArray and gzDictList
//									
// Purpose  : Entry private class for dictionary purposes
//									
// Notes	: only accessable from gzDict
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980601	Created 
//									
//******************************************************************************
template <class T1 , class T2> class gzDictArray;

template <class T1 , class T2> class gzDictList : public gzList< gzDictEntry<T1,T2> >
{
public:

	virtual ~gzDictList() { gzList< gzDictEntry<T1,T2> >::clear(); }

protected:

	virtual gzVoid onInsert(gzDictEntry<T1,T2> *item ) const ;

	virtual gzVoid onRemove(gzDictEntry<T1,T2> *item ) const ;

	virtual gzDictEntry<T1,T2> *cloneEntry(gzDictEntry<T1,T2> *item ) const;

private:

	friend class gzDict<T1,T2>;
	friend class gzDictIterator<T1,T2>;
	friend class gzDictArray<T1,T2>;

	gzDictList();

	gzDictList<T1,T2> & operator=(const gzDictList<T1,T2> & copy );

	gzDict<T1,T2> *m_owner;

	gzVoid clean();
};

//***********************************************************************

template <class T1 , class T2> inline gzDictList<T1,T2> & gzDictList<T1,T2>::operator=(const gzDictList<T1,T2> & copy )
{
	gzList< gzDictEntry<T1,T2> >::operator=((gzList< gzDictEntry<T1,T2> > &)copy);
	return *this;
}

//***********************************************************************

template <class T1 , class T2> inline gzDictList<T1,T2>::gzDictList()
{
	m_owner=nullptr;
}

//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDictList<T1,T2>::clean() 
{
	if(gzList<gzDictEntry<T1,T2> >::m_entries && m_owner)
		gzList<gzDictEntry<T1,T2> >::clear(); 
}

//***********************************************************************

template <class T1 , class T2> class gzDictArray
{
	// This class is fully private and can not be instantiated
private:

	friend class gzDict<T1,T2>;
	friend class gzDictIterator<T1,T2>;
	friend class gzDictConstIterator<T1,T2>;
	friend class gzDictList<T1,T2>;

	gzDictArray();
	~gzDictArray();

	gzVoid	operator=(const gzDictArray<T1,T2> &copy);

	gzVoid	setSize(gzUInt32 size);

	gzVoid	resize(gzUInt32 size);

	
	gzDictList<T1,T2>	*m_data;
	gzUInt32				m_size;

	gzDict<T1,T2>		*m_owner;
	gzBool				m_reuseLinks;
};

//***********************************************************************

template <class T1 , class T2> inline gzDictArray<T1,T2>::gzDictArray()
{
	m_size=0;
	m_owner= NULL;
	m_reuseLinks=FALSE;
}

//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDictArray<T1,T2>::setSize(gzUInt32 size)
{
	if(m_size)
		delete [] m_data;

	m_size=size;
	
	if(m_size)
	{
		gzDictList<T1,T2> *item;

		item=m_data = new  gzDictList<T1,T2>[m_size];

		gzUInt32 i(0);

		while(i<m_size)
		{
			item->m_owner=m_owner;
			item->reuseLinks(m_reuseLinks);
			++item;
			++i;
		}
	}
	else 
		m_data=nullptr;
}

template <class T1 , class T2> inline gzVoid gzDictArray<T1,T2>::resize(gzUInt32 size)
{
	gzDictList<T1,T2> * oldData=m_data;

	gzUInt32 oldSize=m_size;

	if(oldSize>size)
		oldSize=size;

	m_size=size;
	
	if(m_size)
	{
		gzDictList<T1,T2> *item;

		item=m_data = new  gzDictList<T1,T2>[m_size];

		gzUInt32 i(0);

		while(i<m_size)
		{
			item->m_owner=m_owner;
			item->reuseLinks(m_reuseLinks);
			++item;
			++i;
		}

		if(oldSize)
		{
			i=0;

			item=oldData;

			gzListIterator<gzDictEntry<T1,T2> > iterator(*item);

			gzDictEntry<T1,T2> *entry;

			gzDictEntry<T1,T2> *newentry;

			while(i<oldSize)
			{
				if(item->entries())
				{
					iterator.setList(*item);

					while((entry=iterator()))
					{
						newentry=m_owner->allocEntry(entry->m_key,entry->m_pek,entry->m_hash);

						m_data[entry->m_hash%m_size].post_insert(newentry,entry->m_hash);
					}
				}	

				++item;
				++i;
			}
		}
	}
	else 
		m_data=nullptr;

	if(oldSize)
		delete [] oldData;
}

//***********************************************************************

template <class T1 , class T2> inline gzDictArray<T1,T2>::~gzDictArray()
{
	if(m_size)
		delete [] m_data;
}

//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDictArray<T1,T2>::operator=(const gzDictArray<T1,T2> &copy)
{
	if(&copy==this)
		return;

	gzUInt32 i=0;

	if(m_size!=copy.m_size)
	{
		setSize(copy.m_size);
	}

	gzDictList<T1,T2> *to=m_data;
	gzDictList<T1,T2> *from=copy.m_data;

	while(i<m_size)
	{
		*to=*from;
		++to;
		++from;
		++i;
	}
}


//******************************************************************************
// Template	: gzDict
//									
// Purpose  : Dictionary template. Supports memory references
//									
// Notes	: gzDict requires a hash() member function in the T1 class
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980601	Created 
//									
//******************************************************************************
template <class T1 , class T2> class gzDict 
{
public:

	gzDict(gzUInt32 size=10U,gzBool useAutoResize=FALSE,gzBool useParallelRead=FALSE);

	gzDict(const gzDict<T1,T2> &copy);

	const gzDict<T1,T2> &operator=( const gzDict<T1,T2> &copy );

	virtual ~gzDict();
	
	gzVoid			clear();

	gzVoid			clearAndDestroy();

	gzVoid			enter(const T1 &,T2 *);

	T2 *			find(const T1 & , T2 *parent=nullptr) const;

	gzBool			exist(const T1 &,T2 *data=nullptr) const;

	T2 *			remove(const T1 & , T2 *data=nullptr);

	virtual gzVoid	onInsert(const T1 & , T2 *) const {};

	virtual gzVoid	onRemove(const T1 & , T2 *) const {};

	virtual gzDictEntry<T1,T2> *cloneEntry( gzDictEntry<T1,T2> *item) const ;

	gzUInt32		entries() const { return m_entries; };

	gzVoid			setSize(gzUInt32 size);

	gzUInt32		getSize() const;

	gzVoid			resize(gzUInt32 size);

	//! Provide the ability to do a garbage collect of used item links
	gzVoid			cleanLinks();

	gzVoid			reuseLinks(gzBool on=FALSE);

	gzVoid			useAutoResize(gzBool on=FALSE);

	//! Allow parallel read access via find, exist, & iterators.
	//! May affect performance negative in some cases.
	//! Default is the parallel read disabled.
	gzVoid			useParallelRead(gzBool on);

protected:

	gzDictEntry<T1,T2> * allocEntry(const T1 &key , T2 *pek , gzUInt32 hash) const;
	gzVoid disposeEntry(gzDictEntry<T1,T2> *entry) const;
	gzVoid cleanEntries();

private:

	friend class gzDictConstIterator<T1,T2>;
	friend class gzDictIterator<T1,T2>;
	friend class gzDictList<T1,T2>;
	friend class gzDictArray<T1,T2>;


	gzUInt32 m_size;

	gzUInt32 m_entries;

	mutable gzDictEntry<T1,T2>	*			m_lastEntry;

	gzDictArray<T1,T2>						m_array;

	mutable gzList<gzDictEntry<T1,T2> >		m_recycle;

	gzBool									m_reuseLinks;

	gzBool									m_useAutoResize;

	gzBool									m_useParallelRead;
};

//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDict<T1,T2>::reuseLinks(gzBool on)
{
	m_reuseLinks=on;

	gzUInt32 i(0);

	gzDictList<T1,T2> *item=m_array.m_data;

	m_array.m_reuseLinks=on;

	while(i<m_size)
	{
		item->reuseLinks(on);
		++item;
		++i;
	}

	m_recycle.reuseLinks(on);
}

template <class T1 , class T2> inline gzVoid gzDict<T1,T2>::useAutoResize(gzBool on)
{
	m_useAutoResize=on;
}

template <class T1, class T2> inline gzVoid gzDict<T1, T2>::useParallelRead(gzBool on)
{
	m_useParallelRead = on;
	m_lastEntry = NULL;
}

template <class T1 , class T2> inline gzDictEntry<T1,T2> * gzDict<T1,T2>::allocEntry(const T1 &key , T2 *pek , gzUInt32 hash) const
{
	if(m_reuseLinks && m_recycle.entries())
	{
		return m_recycle.removeFirst()->set(key,pek,hash);
	}
	return new gzDictEntry<T1,T2>(key,pek,hash);
}

template <class T1 , class T2> inline gzVoid gzDict<T1,T2>::disposeEntry(gzDictEntry<T1,T2> *entry) const
{
	if(m_reuseLinks)
		m_recycle.pre_insert(entry);
	else
		delete entry;
}

template <class T1 , class T2> inline gzVoid gzDict<T1,T2>::cleanEntries()
{
	if(m_recycle.entries())
	{
		m_recycle.clearAndDestroy();
	}
}

template <class T1 , class T2> inline gzDictEntry<T1,T2> * gzDict<T1,T2>::cloneEntry( gzDictEntry<T1,T2> *item) const 
{ 
	return allocEntry(item->getKey(),item->getData(),item->getHash());
}

template <class T1 , class T2> inline const gzDict<T1,T2> & gzDict<T1,T2>::operator=( const gzDict<T1,T2> &copy )
{
	m_array=copy.m_array;
	m_size=copy.m_size;
	m_entries=copy.m_entries;
	
	m_lastEntry=nullptr;

	return *this;
}

//***********************************************************************

template <class T1 , class T2> inline gzDict<T1,T2>::gzDict(const gzDict<T1,T2> &copy)
{
	m_array.m_owner=this;
	m_size=0;

	m_reuseLinks=FALSE;
	m_useAutoResize=FALSE;
	m_useParallelRead = FALSE;

	*this=copy;
}

//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDictList<T1,T2>::onInsert(gzDictEntry<T1,T2> *item ) const 
{
	if(m_owner)
		m_owner->onInsert(item->getKey(),item->getData());
}

//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDictList<T1,T2>::onRemove(gzDictEntry<T1,T2> *item ) const 
{
	if(m_owner)
	{
		m_owner->onRemove(item->getKey(),item->getData());
		m_owner->disposeEntry(item);
	}
	else
		delete item;
}

//***********************************************************************

template <class T1 , class T2> inline gzDictEntry<T1,T2> *gzDictList<T1,T2>::cloneEntry(gzDictEntry<T1,T2> *item) const
{
	if(m_owner)
		return m_owner->cloneEntry(item);
	else
		return new gzDictEntry<T1,T2>(item->getKey(),item->getData());
}

//***********************************************************************

template <class T1 , class T2> inline gzDict<T1,T2>::gzDict(gzUInt32 size,gzBool useAutoResize, gzBool useParallelRead)
{
	m_array.m_owner=this;
	m_size=size;

	if(m_size)
		m_array.setSize(m_size);

	m_entries = 0;
	m_lastEntry = nullptr;
	m_reuseLinks = FALSE;
	m_useAutoResize = useAutoResize;
	m_useParallelRead = useParallelRead;
}

template <class T1 , class T2> inline gzUInt32 gzDict<T1,T2>::getSize() const
{
	return m_size;
}

template <class T1 , class T2> inline gzVoid gzDict<T1,T2>::setSize(gzUInt32 size)
{
	clear();
	m_array.setSize(size);
	m_size=size;
	m_entries=0;
	m_lastEntry=nullptr;
}

template <class T1 , class T2> inline gzVoid gzDict<T1,T2>::resize(gzUInt32 size)
{
	m_array.resize(size);
	m_size=size;
	m_lastEntry=nullptr;
}

//***********************************************************************

template <class T1 , class T2> inline gzBool gzDict<T1,T2>::exist(const T1 &keyItem ,T2 *valueItem) const
{
	if(m_lastEntry)
	{
		if(valueItem)
		{
			if(m_lastEntry->m_pek==valueItem)
				if(m_lastEntry->m_key==keyItem)
					return TRUE;
		}
		else
		{
			if(m_lastEntry->m_key==keyItem)
				return TRUE;
		}
	}

	gzUInt32 hash=keyItem.hash();

	gzDictEntry<T1,T2> *entry;

	gzDictEntry<T1,T2> *prevEntry=nullptr;
	
	gzListIterator< gzDictEntry<T1,T2> > iterator(m_array.m_data[hash%m_size]);
	while((entry=iterator()))
	{
		if(entry->m_hash==hash)
		{
			if(valueItem)
			{
				if(entry->m_pek==valueItem)
					if(entry->m_key==keyItem)
					{
						if(prevEntry && !m_useParallelRead)
							if(prevEntry->m_hash!=hash)
								m_lastEntry=entry;

						return TRUE;
					}
			}
			else
			{
				if(entry->m_key==keyItem)
				{
					if(prevEntry && !m_useParallelRead)
						if(prevEntry->m_hash!=hash)
							m_lastEntry=entry;

					return TRUE;
				}
			}
		}
		prevEntry=entry;
	}
	return FALSE;
}

//***********************************************************************

template <class T1 , class T2> inline T2 * gzDict<T1,T2>::remove(const T1 &keyItem ,T2 *valueItem)
{
	gzUInt32 hash=keyItem.hash();
	gzDictEntry<T1,T2> *entry;

	T2 *retval;
	
	gzListIterator< gzDictEntry<T1,T2> > iterator(m_array.m_data[hash%m_size]);
	while((entry=iterator()))
	{
		if(entry->m_hash==hash)
		{
			if(valueItem)
			{
				if(entry->m_pek==valueItem)
					if(entry->m_key==keyItem)
					{
						if(m_lastEntry==entry)
							m_lastEntry=nullptr;

						retval=entry->getData();

						iterator.remove();
						m_entries--;
						return retval;
					}
			}
			else
			{
				if(entry->m_key==keyItem)
				{
					if(m_lastEntry==entry)
						m_lastEntry=nullptr;

					retval=entry->getData();

					iterator.remove();
					m_entries--;
					return retval;
				}
			}
		}
	}
	return NULL;
}

//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDict<T1,T2>::clear()
{
	if(m_entries)
	{
		gzUInt32 i(m_size);

		gzDictList<T1,T2> *array=m_array.m_data;

		while(i--)
		{
			array->clean();
			++array;
		}

		m_entries=0;
	}

	m_lastEntry=nullptr;
}

//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDict<T1,T2>::cleanLinks()
{
	gzUInt32 i;

	gzDictList<T1,T2> *array=m_array.m_data;

	for(i=0;i<m_size;++i)
	{
		array->cleanLinks();
		++array;
	}

	cleanEntries();
}

//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDict<T1,T2>::enter(const T1 &keyItem , T2 *valueItem)
{
	gzUInt32 hash=keyItem.hash();

	gzDictEntry<T1,T2> *entry = allocEntry(keyItem,valueItem,hash);

	if(m_useAutoResize)
	{
		if(m_entries>=(m_size<<1))
		{
			m_size=(((m_size+1)<<2)-1);
			m_array.resize(m_size);
		}
	}

	if(m_array.m_data[hash%m_size].post_insert(entry,hash))
		m_lastEntry=nullptr;
	else if (!m_useParallelRead)
		m_lastEntry=entry;

	++m_entries;
}

//***********************************************************************

template <class T1 , class T2> inline T2 * gzDict<T1,T2>::find(const T1 &keyItem, T2 *parent) const
{
	if(!m_entries)
		return 0;

	gzUInt32 hash=keyItem.hash();
	gzDictEntry<T1,T2> *entry=m_lastEntry;
	
	if(!parent)
	{
		if(entry)
		{
			if(entry->m_hash==hash)
			{
				if(entry->m_key==keyItem)
				{
					return entry->m_pek;
				}
			}
		}
	}
	
	T2 *last=nullptr;

	gzListIterator< gzDictEntry<T1,T2> > iterator(m_array.m_data[hash%m_size]);

	while((entry=iterator()))
	{
		if(entry->m_hash==hash)
		{
			if(entry->m_key==keyItem)
			{
				if((last==parent) && (entry->m_pek!=parent))
				{
					if(!parent && !m_useParallelRead)
						m_lastEntry=entry;

					return entry->m_pek;
				}
				else
					last=entry->m_pek;
			}
		}
	}
	return 0;
}

//***********************************************************************

template <class T1 , class T2> inline gzDict<T1,T2>::~gzDict()
{
	clear();
	cleanEntries();
}


//******************************************************************************
// Template	: gzDictIterator
//									
// Purpose  : Iterator for gzDict
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980601	Created 
//									
//******************************************************************************
template <class T1 , class T2> class gzDictIterator 
{
public:

	gzDictIterator(gzDict<T1,T2> &owner);

	~gzDictIterator(){};

	gzDictEntry<T1,T2> *	operator()();

	//! Re-use itarator with another dictionary
	gzVoid					setDict(gzDict<T1,T2>& owner);

	T2 *					remove();

	gzVoid					reset();

	gzDictEntry<T1,T2> *	key();

private:

	gzListIterator< gzDictEntry<T1,T2> > m_iterator;
	gzDict<T1,T2>	*m_owner;
	size_t			m_index;
	gzUInt32			m_position;
};

//***********************************************************************

template <class T1 , class T2> inline gzDictIterator<T1,T2>::gzDictIterator( gzDict<T1,T2> &owner):m_iterator(*owner.m_array.m_data)
{
	m_owner=&owner;
	m_index=0;
	m_position=0;
}

//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDictIterator<T1,T2>::setDict(gzDict<T1,T2>& owner)
{
	m_owner=&owner;
	m_index=0;
	m_position=0;
	m_iterator.setList(*owner.m_array.m_data);
}


//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDictIterator<T1,T2>::reset()
{
	m_index=0;
	m_position=0;
	m_iterator=gzListIterator< gzDictEntry<T1,T2> >(m_owner->m_array.m_data[m_index]);
}

//***********************************************************************

template <class T1 , class T2> inline gzDictEntry<T1,T2> *	gzDictIterator<T1,T2>::key()
{
	return m_iterator.key();
}

//***********************************************************************

template <class T1 , class T2> inline gzDictEntry<T1,T2> * gzDictIterator<T1,T2>::operator()()
{
	if(!m_owner->m_entries)
		return 0;

	gzDictEntry<T1,T2> *entry;

	while(1)
	{
		if(m_position>=m_owner->m_entries)
			return 0;

		entry=m_iterator();

		if(!entry)
		{
			++m_index;
//			if(m_index==m_owner->m_size)
//				return 0;
			
			while(!m_owner->m_array.m_data[m_index].entries())
			{
				++m_index;
//				if(m_index==m_owner->m_size)
//					return 0;
			}
			m_iterator.setList(m_owner->m_array.m_data[m_index]);
			continue;
		}
		else
			++m_position;

		return entry;
	}
}

//***********************************************************************

template <class T1 , class T2> inline T2 * gzDictIterator<T1,T2>::remove()
{
	if(m_owner)
	{
		gzDictEntry<T1,T2> * item;

		if( (item = m_iterator.key()) )
		{
			T2 * data = item->getData();

			m_iterator.remove();

			m_owner->m_entries--;
			if(m_owner->m_lastEntry==item)
				m_owner->m_lastEntry=nullptr;

			m_position--;
			return data;
		}
	}
	return NULL;
}

template <class T1 , class T2> inline gzVoid gzDict<T1,T2>::clearAndDestroy()
{
	gzDictIterator<T1,T2>	iterator(*this);

	while(iterator())
	{
		delete iterator.remove();
	}
}

//******************************************************************************
// Template	: gzDictConstIterator
//									
// Purpose  : Const Iterator for gzDict
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040301	Created 
//									
//******************************************************************************
template <class T1 , class T2> class gzDictConstIterator 
{
public:

	gzDictConstIterator(const gzDict<T1,T2> &owner);

	~gzDictConstIterator(){};

	const gzDictEntry<T1,T2> *	operator()();

	//! Re-use itarator with another dictionary
	gzVoid					setDict(const gzDict<T1,T2>& owner);

	gzVoid					reset();

	const gzDictEntry<T1,T2> *	key();

private:

	gzListConstIterator< gzDictEntry<T1,T2> > m_iterator;
	const gzDict<T1,T2>	*m_owner;
	size_t				m_index;
	gzUInt32				m_position;
};

//***********************************************************************

template <class T1 , class T2> inline gzDictConstIterator<T1,T2>::gzDictConstIterator( const gzDict<T1,T2> &owner):m_iterator(*owner.m_array.m_data)
{
	m_owner=&owner;
	m_index=0;
	m_position=0;
}

//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDictConstIterator<T1,T2>::setDict(const gzDict<T1,T2>& owner)
{
	m_owner=&owner;
	m_index=0;
	m_position=0;
	m_iterator.setList(*owner.m_array.m_data);
}


//***********************************************************************

template <class T1 , class T2> inline gzVoid gzDictConstIterator<T1,T2>::reset()
{
	m_index=0;
	m_position=0;
	m_iterator= gzListConstIterator< gzDictEntry<T1,T2> >(m_owner->m_array.m_data[m_index]);
}

//***********************************************************************

template <class T1 , class T2> inline const gzDictEntry<T1,T2> *	gzDictConstIterator<T1,T2>::key()
{
	return m_iterator.key();
}

//***********************************************************************

template <class T1 , class T2> inline const gzDictEntry<T1,T2> * gzDictConstIterator<T1,T2>::operator()()
{
	if(!m_owner->m_entries)
		return 0;

	gzDictEntry<T1,T2> *entry;

	while(1)
	{
		if(m_position>=m_owner->m_entries)
			return 0;

		entry=m_iterator();

		if(!entry)
		{
			++m_index;
			
			while(!m_owner->m_array.m_data[m_index].entries())
				++m_index;

			m_iterator.setList(m_owner->m_array.m_data[m_index]);
			continue;
		}
		else
			++m_position;

		return entry;
	}
}

//***********************************************************************

typedef enum { GZ_QUEUE_LIFO , GZ_QUEUE_FIFO } gzQueueMode;

//******************************************************************************
// Template	: gzQueue
//									
// Purpose  : Queue management
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981021	Created 
//									
//******************************************************************************
template <class T> class gzQueue 
{
public:
		
	gzQueue( gzQueueMode mode=GZ_QUEUE_LIFO , gzUInt32 chunkSize=100 ):m_items(chunkSize),m_mode(mode),m_start_index(0),m_stop_index(0){}

	~gzQueue() {}

	gzVoid		clear(gzBool resetDefault=TRUE);

	gzVoid		push(const T &);

	gzVoid		push(const T *, gzUInt32 entries);

	gzVoid		push_reversed(const T*, gzUInt32 entries);

	gzUInt32	pop(T *, gzUInt32 maxentries);
	
	T			pop();

	T			popNoClear();

	T &			top();

	gzVoid		drop();
	
	gzUInt32	entries();

	gzUInt32	getStartIndex() const;

	gzUInt32	getStopIndex() const;

	gzDynamicArray<T> & getArray() { return m_items; }
	
	gzVoid		setMode(gzQueueMode mode) { m_mode=mode; }

	T *	getAddress() { return m_items.getAddress()+m_start_index; }

	const T* getAddress() const { return m_items.getConstAddress() + m_start_index; }

	gzVoid		setChunkSize(gzUInt32 size);

	gzUInt32	getChunkSize() const;

	gzVoid		setRealSize(gzUInt32 size);

	gzVoid		pushEmptyItems(gzUInt32 entries);

	gzVoid		cleanUp();

	gzVoid		swapArrayData(gzDynamicArray<T>& swapper);

	gzVoid		swapArrayData(gzArray<T>& swapper);

private:
	
	gzDynamicArray<T> m_items;

	gzQueueMode m_mode;

	gzUInt32 m_start_index;
	gzUInt32 m_stop_index;

};

//***********************************************************************

template <class T> inline gzVoid gzQueue<T>::setChunkSize(gzUInt32 size) 
{ 
	m_items.setChunkSize(size); 
}

template <class T> inline gzUInt32 gzQueue<T>::getChunkSize() const 
{ 
	return m_items.getChunkSize(); 
}

template <class T> inline gzVoid gzQueue<T>::setRealSize(gzUInt32 size)
{
	clear();

	m_items.setRealSize(size);

	m_stop_index = gzMin(size - 1, m_stop_index);
}

template <class T> inline gzVoid gzQueue<T>::push(const T &val)
{
	if(m_start_index && (m_start_index==m_stop_index))
	{
		m_start_index=m_stop_index=0; 
	}
	else if (m_stop_index >= m_items.getRealSize())	// We will do a resize and move
	{
		m_items.setSize(m_stop_index - m_start_index+1, -(gzInt32)m_start_index);
		m_stop_index -= m_start_index;
		m_start_index = 0;
	}

	m_items[m_stop_index]=val;
	++m_stop_index;
}

template <class T> inline gzUInt32 gzQueue<T>::getStartIndex() const
{
	return m_start_index;
}

template <class T> inline gzUInt32 gzQueue<T>::getStopIndex() const
{
	return m_stop_index;
}

template <class T> inline gzVoid gzQueue<T>::cleanUp()
{
	gzUInt32 count=m_stop_index-m_start_index;

	T* to = m_items.getAddress();

	T* from = to + m_start_index;

	copyInstances<T>(to, from, count,TRUE);

	m_start_index=0;
	m_stop_index=count;
}

template <class T> inline gzVoid gzQueue<T>::swapArrayData(gzDynamicArray<T>& swapper)
{
	m_items.swapArrayData(swapper);

	m_start_index = 0;
	m_stop_index = m_items.getSize();
}

template <class T> inline gzVoid gzQueue<T>::swapArrayData(gzArray<T>& swapper)
{
	m_items.swapArrayData(swapper);

	m_start_index = 0;
	m_stop_index = m_items.getSize();
}

//***********************************************************************

template <class T> inline gzVoid gzQueue<T>::clear(gzBool resetDefault)
{ 
	if(resetDefault)
	{
		gzUInt32 i;

		for(i=m_start_index;i<m_stop_index;++i)
			*(m_items.getAddress()+i)=T();
	}

	m_items.setSize(0);

	m_start_index=0; m_stop_index=0; 
}

template <> inline gzVoid gzQueue<gzUByte>::clear(gzBool /*resetDefault*/)
{ 
	m_items.setSize(0);
	m_start_index=0; m_stop_index=0; 
}
//***********************************************************************

template <class T> inline gzVoid gzQueue<T>::pushEmptyItems(gzUInt32 entries)
{
	if(m_start_index==m_stop_index)
	{
		m_start_index=0; 
		m_stop_index=entries;
	}
	else
	{
		m_stop_index += entries;

		if (m_stop_index > m_items.getRealSize())	// We will do a resize and move
		{
			m_items.setSize(m_stop_index-m_start_index, -(gzInt32)m_start_index);
			m_stop_index -=m_start_index;
			m_start_index = 0;

			return;
		}
	}

	m_items.setSize(m_stop_index);
}

template <class T> inline gzVoid gzQueue<T>::push_reversed(const T* address, gzUInt32 entries)
{
	if (m_start_index == m_stop_index)
	{
		m_start_index = m_stop_index = 0;
	}


	m_items.setSize(m_stop_index + entries);


	T* to(m_items.getAddress() + m_stop_index+entries-1);

	const T* from(address);

	gzUInt32 i(entries);

	while (i)
	{
		*to = *from;
		--to; ++from;
		--i;
	}

	m_stop_index += entries;
}



template <class T> inline gzVoid gzQueue<T>::push(const T *address , gzUInt32 entries)
{
	if(m_start_index==m_stop_index)
	{
		m_start_index=m_stop_index=0; 
	}


	m_items.setSize(m_stop_index+entries);
	

	T *to(m_items.getAddress()+m_stop_index);

	const T *from(address);

	gzUInt32 i(entries);

	while(i)
	{
		*to=*from;
		++to;++from;
		--i;
	}

	m_stop_index+=entries;
}

template <> inline gzVoid gzQueue<gzUByte>::push(const gzUByte *address , gzUInt32 entries)
{
	if(m_start_index==m_stop_index)
	{
		m_start_index=m_stop_index=0; 
	}

	m_items.setSize(m_stop_index+entries);

	switch(entries)
	{
		case 0:
			break;

		case 1:
			*(m_items.getAddress()+m_stop_index)=*address;
			break;

		case 2:
			*(gzUInt16 *)(m_items.getAddress()+m_stop_index)=*(gzUInt16 *)address;
			break;

		case 4:
			*(gzUInt32 *)(m_items.getAddress()+m_stop_index)=*(gzUInt32 *)address;
			break;

#ifdef GZ_64_BITS
		case 8:
			*(gzUInt64 *)(m_items.getAddress()+m_stop_index)=*(gzUInt64 *)address;
			break;
#else
		case 8:
			*(gzUInt32*)(m_items.getAddress() + m_stop_index  ) = *(gzUInt32*)address;
			*(gzUInt32*)(m_items.getAddress() + m_stop_index + sizeof(gzUInt32)) = *((gzUInt32*)address+1);
			break;
#endif

		default:
			memcpy(m_items.getAddress()+m_stop_index,address,entries);
			break;
	}
	
	m_stop_index+=entries;
}

//***********************************************************************

template <class T> inline T & gzQueue<T>::top()
{
	if(m_mode==GZ_QUEUE_LIFO)
	{
		if(m_stop_index>m_start_index)
			return m_items[m_stop_index-1];
		else
		{
			throwFatalTemplateError("No top() item in gzQueue");
			return m_items[0];	// To avoid warning
		}
	}
	else
		return m_items[m_start_index];
}

//***********************************************************************

template <class T> inline T gzQueue<T>::pop()
{
	if(m_stop_index>m_start_index)
	{
		if(m_mode==GZ_QUEUE_LIFO)
		{
			T retval(*(m_items.getAddress()+(--m_stop_index)));
			*(m_items.getAddress()+m_stop_index)=T();
			return retval;
		}
		else
		{
			T retval(*(m_items.getAddress()+m_start_index));
			*(m_items.getAddress()+m_start_index)=T();
			++m_start_index;
			return retval;
		}
	}
	else
		throwFatalTemplateError("gzQueue:pop out of data");

	return T();
}

//***********************************************************************

template <class T> inline T gzQueue<T>::popNoClear()
{
	if(m_stop_index>m_start_index)
	{
		if(m_mode==GZ_QUEUE_LIFO)
		{
			return *(m_items.m_data+(--m_stop_index));
		}
		else
		{
			return *(m_items.m_data+m_start_index++);
		}
	}
	else
		throwFatalTemplateError("gzQueue:pop out of data");

	return T();
}

//***********************************************************************

template <class T> inline gzVoid gzQueue<T>::drop()
{
	if(m_stop_index>m_start_index)
	{
		if(m_mode==GZ_QUEUE_LIFO)
			--m_stop_index;
		else
			++m_start_index;
	}
	else
		throwFatalTemplateError("gzQueue:drop out of data");
}

//***********************************************************************

template <class T> inline gzUInt32 gzQueue<T>::pop(T *address , gzUInt32 maxcount)
{
	if(maxcount>m_stop_index-m_start_index)
		maxcount=m_stop_index-m_start_index;

	T *from;

	gzUInt32 i;

	if(m_mode==GZ_QUEUE_LIFO)
	{
		from=m_items.getAddress()+m_stop_index;

		if(address)
		{
			for(i=0;i<maxcount;++i)
			{
				--from;
				*address=*from;
				++address;
				*from=T();
			}
		}
		else
		{
			for(i=0;i<maxcount;++i)
			{
				--from;
				*from=T();
			}
		}
		m_stop_index-=maxcount;
		return maxcount;
	}
	else
	{
		from=m_items.getAddress()+m_start_index;

		if(address)
		{
			for(i=0;i<maxcount;++i)
			{
				*address=*from;
				++address;
				*from=T();
				++from;
			}
		}
		else
		{
			for(i=0;i<maxcount;++i)
			{
				*from=T();
				++from;
			}
		}
		m_start_index+=maxcount;
		return maxcount;
	}
}

//***********************************************************************

template <> inline gzUInt32 gzQueue<gzUByte>::pop(gzUByte *address , gzUInt32 maxcount)
{
	if(maxcount > (m_stop_index-m_start_index))
		maxcount = (m_stop_index-m_start_index);

	gzUByte *from;

	gzUInt32 i;

	if(m_mode==GZ_QUEUE_LIFO)
	{
		from=m_items.getAddress()+m_stop_index;

		if(address)
		{
			for(i=0;i<maxcount;++i)
			{
				--from;
				*address=*from;
				++address;
			}
		}
		m_stop_index-=maxcount;
		return maxcount;
	}
	else
	{
		from=m_items.getAddress()+m_start_index;

		if(address)
		{

			switch(maxcount)
			{
				case 0:
					break;

				case 1:
					*(address)=*from;
					break;

				case 2:
					*(gzUInt16 *)address=*(gzUInt16 *)from;
					break;

				case 4:
					*(gzUInt32 *)address=*(gzUInt32 *)from;
					break;

#ifdef GZ_64_BITS
				case 8:
					*(gzUInt64 *)address=*(gzUInt64 *)from;
					break;
#else
				case 8:
					*(gzUInt32*)address = *(gzUInt32*)from;
					*((gzUInt32*)address+1) = *((gzUInt32*)from+1);
					break;

#endif

				default:
					memcpy(address,from,maxcount);
					break;
			}
		}
		m_start_index+=maxcount;
		return maxcount;
	}
}

//***********************************************************************

template <class T> inline gzUInt32 gzQueue<T>::entries()
{
	return m_stop_index-m_start_index;
}

//***********************************************************************



//******************* Utilities *****************************************


template <class T> inline T gzAbsMax(const T &value1 , const T &value2 )
{
	return (value1>=value2)?((value1>=-value2)?value1:-value2):((value2>=-value1)?value2:-value1);
}


//***********************************************************************

template <class T> inline T gzAbsMax(const T &value1 , const T &value2 , const T &value3 )
{
	const T value_a(gzAbsMax<T>(value1,value2));
	const T value_b(gzAbs<T>(value3));

	return (value_a>value_b)?value_a:value_b;
}

//***********************************************************************

template <class T> inline T gzAbsMax(const T &value1 , const T &value2 , const T &value3 , const T &value4 )
{
	const T value_a(gzAbsMax<T>(value1,value2));
	const T value_b(gzAbsMax<T>(value3,value4));

	return (value_a>value_b)?value_a:value_b;
}


//***********************************************************************

const gzFloat s_eps=5e-5f;

template <class T> inline T gzRelativeDiff(const T &value_1 , const T &value_2)
{
	T a(gzAbs<T>(value_1-value_2));

	if(a<2*s_eps)
			return 0.0;

	return a/gzAbsMax<T>(value_1,value_2);
}

//***********************************************************************

// Used to provide a base class for deriving data from builtin primitives

template <class T> class gzBaseClass 
{
public:
	gzBaseClass(){};

	~gzBaseClass(){};

	gzBaseClass(const T &data)
	{
		m_data=data;
	}

	operator T & () 
	{ 
		return m_data; 
	}

private:

	T m_data;
};

//***********************************************************************

template <class T> class gzMemCheck : public T , public gzMemoryCheck
{
public:
	gzMemCheck(const T &base):T(base){}
	gzMemCheck(){}

};

//***********************************************************************

template <class T> class gzDListIterator;
template <class T> class gzDListConstIterator;

//******************************************************************************
// Template	: gzDList
//									
// Purpose  : Double Linked list with index insort and reference management
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
/*! \brief Template class for double linked lists

The gzDList is a template class that contains a single linked list with fast access to retreive
and store items in the list. It does also provide the virtual functions onInsert and onRemove so the user
can derive this class and access these events.

If you want to use reference based lists you should use the gzRefDList instead !

*/

template <class T> class gzDList 
{
	public:

		//! Default constructor.
		gzDList();

		//! Default copy constructor. 
		
		/*! Note that the cloning in the copy constructor depends
			on your implementation of the cloneEntry() method. By default the list shares
			each item in the list. You can provide your own derived virtual method to add
			other behaviours of the copy constructor. */

		gzDList(const gzDList<T> &copy); 
		gzDList(const gzList<T> &copy);

		//! Default destructor. Clears list !!
		virtual ~gzDList();

		//! Insert item at end of list
		gzVoid insert(T *item);			// Adds at end of list

		//! Insert item at index pos starting at 0
		gzVoid insertAt(gzUInt32 index,T *item);			// Adds at index

		//! Insert item at beginning of list
		gzVoid pre_insert(T *item);		// Adds at beginning of list

		//! Insert item using gzUInt32 sort value

		/*! The insert method removes the old item if there is one with the same
			index sort value and returns a pointer to the item so it can be freed etc. */

		T   *insert(T *item, gzDouble sortval);

		//! Post Insert with sorted value
		/*! If there is one or more existing items with the same sort value, the new
			item is inserted at the end of the existing items */
		gzBool post_insert(T *item, gzDouble sortval);

		//! Pre Insert with sorted value
		/*! If there is one or more existing items with the same sort value, the new
			item is inserted at the beginning of the existing items */
 		gzBool pre_insert(T *item, gzDouble sortval);

		//! Index operator based on index zero as first value
   		T	*operator[](gzUInt32 i);

		//! Assignment operator
		gzDList &operator=(const gzDList &copy );

		//! Assignment operator
		gzDList &operator=(const gzList<T> &copy );

		//! Clears items from list. Does NOT free item
		virtual gzVoid clear();

		//! Clears item AND frees item allocated memory
		virtual gzVoid clearAndDestroy();

		//! Number of item entries in list
		gzUInt32 entries() const;

		//! Query to see if list contains an element
		gzBool contains(const T *item) const;

		//! Query to see list index
		gzInt32 index(const T *item) const;

		//! Removes first item and returns reference to item
		T	*removeFirst();
		
		//! Removes last item and returns reference to item
		T	*removeLast();
		
		//! Removes item and returns reference to item
		T	*remove( T * item );
		
		//! Removes item at index pos starting at 0
		T	*removeAt( gzUInt32 index );

		//! Returns reference to last item in list
		T	*last();

		//! Returns reference to first item in list
		T	*first();

		//! Virtual method called when an item is inserted
		virtual gzVoid onInsert(T * /*item*/ ) const {};

		//! Virtual method called when an item is removed
		virtual gzVoid onRemove(T * /*item*/ ) const {};

		//! Virtual method called when an item shall be cloned.
		/*! The method implements a shared item as default. Make sure that you
			do not call e.g clearAndDestroy() on a list that is created with this default
			clone (share) method in combination with a free of your originally created list.
			You will then get two deallocations of item memory */

		virtual T* cloneEntry(T *item ) const;

		//! Provide the ability to do a garbage collect of used item links
		gzVoid	cleanLinks();

		gzVoid reuseLinks(gzBool on=FALSE);


	private:

		friend class gzDListIterator<T>; 
		friend class gzDListConstIterator<T>; 
		
		struct LinkItem 
		{
				gzDouble		sortval;
				T				*item;
				LinkItem		*prev;
				LinkItem		*next;

		};

		gzVoid			disposeLink(LinkItem *link);
		LinkItem *		allocLink();


		LinkItem	*m_link;

		LinkItem	*m_last;

		gzUInt32		m_entries;
		
		LinkItem	*m_recycle;

		gzBool		m_reuseLinks;
};

//***********************************************************************

template <class T> inline gzVoid gzDList<T>::reuseLinks(gzBool on)
{
	m_reuseLinks=on;
}

template <class T> inline typename gzDList<T>::LinkItem * gzDList<T>::allocLink()
{ 
	if(m_reuseLinks && m_recycle)
	{
		LinkItem *link=m_recycle;

		m_recycle=m_recycle->next;

		return link;
	}
	return new LinkItem; 
}

template <class T> inline gzVoid gzDList<T>::disposeLink(LinkItem *link)
{ 
	if(m_reuseLinks)
	{
		link->next=m_recycle;
		m_recycle=link;
	}
	else
		delete link;
}

template <class T> inline gzVoid gzDList<T>::cleanLinks()
{
	if(m_recycle)
	{
		LinkItem *nextlink;

		while(m_recycle)
		{
			nextlink=m_recycle->next;
			delete m_recycle;
			m_recycle=nextlink;
		}
	}
}

template <class T> inline T* gzDList<T>::cloneEntry(T *item) const
{ 
	return item; 
}

//***********************************************************************

template <class T> inline gzUInt32 gzDList<T>::entries() const
{
	return m_entries;
}

//***********************************************************************

template <class T> inline T *gzDList<T>::remove( T *item )
{
	if(m_link)
	{
		LinkItem *link=m_link;

		T *retitem;
		
		while(link)
		{
			if(item==link->item)
			{
				if(!link->prev)
				{
					m_link=link->next;
				}
				else
				{
					link->prev->next=link->next;
				}

				if(!link->next)
				{
					m_last=link->prev;
				}
				else
				{
					link->next->prev=link->prev;
				}

				retitem=link->item;
				disposeLink(link);
				m_entries--;
				onRemove(retitem);
				return retitem;
			}
			link=link->next;
		}
	}
	return 0;
}		

//***********************************************************************
			
template <class T> inline T *gzDList<T>::removeFirst()
{
	if(!m_link)
		return 0;

	LinkItem *link=m_link;

	T *item=link->item;

	m_link=m_link->next;

	if(!m_link)
		m_last=0;
	else
		m_link->prev=0;

	disposeLink(link);

	--m_entries;

	onRemove(item);

	return item;
}

//***********************************************************************

template <class T> inline T *gzDList<T>::removeLast()
{
	if(!m_link)
		return 0;

	LinkItem *link=m_last;

	T *item=link->item;

	m_last=link->prev;

	if(!m_last)
		m_link=0;
	else
		m_last->next=0;

	disposeLink(link);

	m_entries--;

	onRemove(item);

	return item;
}

//***********************************************************************

template <class T> inline T *gzDList<T>::last()
{
	if(!m_last)
		return 0;

	return m_last->item;
}

//***********************************************************************

template <class T> inline T *gzDList<T>::first()
{
	if(!m_link)
		return 0;

	return m_link->item;
}

//***********************************************************************

template <class T> inline T *gzDList<T>::operator[](gzUInt32 i)
{

	if(i>=m_entries)
		return NULL;

	gzUInt32 j;

	LinkItem *link=m_link;
	
	if(i<(m_entries/2))
	{
		for(j=0;j<i;++j)
			link=link->next;
	}
	else
	{
		link=m_last;
		for(j=m_entries-1;j>i;--j)
			link=link->prev;
	}

	return link->item;
}

//***********************************************************************

template <class T> inline gzDList<T>::gzDList():m_link(0),m_last(0),m_entries(0),m_recycle(0),m_reuseLinks(FALSE)
{
}

//***********************************************************************

template <class T> inline gzDList<T>::~gzDList()
{
	clear();
	cleanLinks();
}

//***********************************************************************

template <class T> inline gzVoid gzDList<T>::insertAt(gzUInt32 index,T *item)
{
	if(index>=m_entries)
	{
		insert(item);
		return;
	}

	LinkItem *newlink=allocLink();
	newlink->sortval=0;
	newlink->item=item;

	LinkItem *pre_link=nullptr;
	LinkItem *post_link=m_link;

	gzUInt32 i;

	for(i=0;i<index;++i)
	{
		if(post_link)
		{
			pre_link=post_link;
			post_link=post_link->next;
		}
		else
			break;
	}

	if(pre_link)	// Not first item
	{
		newlink->prev=pre_link;
		newlink->next=pre_link->next;
		pre_link->next=newlink;

		if(!post_link)	// last
			m_last=newlink;
	}
	else			// First item
	{
		if(m_link)	// Not last
		{
			newlink->next=m_link;
			newlink->prev=nullptr;
			m_link->prev = newlink;

			m_link=newlink;
		}
		else		// last and only
		{
			newlink->prev=nullptr;
			newlink->next=nullptr;
			m_last=m_link=newlink;
		}
	}
	++m_entries;
	onInsert(item);
}

//***********************************************************************
			
template <class T> inline T * gzDList<T>::removeAt(gzUInt32 index)
{
	if(index>=m_entries-1)
	{
		if(index==m_entries-1)
			return removeLast();
		return NULL;
	}

	LinkItem *pre_link=nullptr;
	LinkItem *post_link=m_link;

	gzUInt32 i;

	for(i=0;i<index;++i)
	{
		if(post_link)
		{
			pre_link=post_link;
			post_link=post_link->next;
		}
		else
			break;
	}

	if(post_link)	// item to remove
	{
		if(pre_link)	// have previous item
		{
			if(!(pre_link->next=post_link->next))	// last item
				m_last=pre_link;
			else
				post_link->next->prev=pre_link;
			
		}
		else	// remove first item
		{
			m_link=post_link->next;
			if(!(m_link=post_link->next))	// was last item
				m_last=nullptr;
			else
				m_link->prev=nullptr;
		}
		m_entries--;

		T *item=post_link->item;

		disposeLink(post_link);

		onRemove(item);
		return item;
	}
	else
		return NULL;
}

//***********************************************************************

template <class T> inline gzVoid gzDList<T>::insert( T *item)
{
	LinkItem *newlink=allocLink();

	newlink->next=nullptr;

	newlink->sortval=0;
	
	if(m_last)
		m_last->next=newlink;
	else
		m_link=newlink;

	newlink->prev=m_last;
	newlink->item=item;
	m_last=newlink;

	++m_entries;
	onInsert(item);
}

//***********************************************************************

template <class T> inline gzVoid gzDList<T>::pre_insert( T *item)
{
	LinkItem *newlink=allocLink();

	newlink->next=m_link;
	newlink->sortval=0;

	if(m_link)
		m_link->prev=newlink;
	
	m_link=newlink;

	if(!m_last)
		m_last=newlink;

	newlink->item=item;
	newlink->prev=nullptr;

	++m_entries;
	onInsert(item);
}

//***********************************************************************

template <class T> inline T* gzDList<T>::insert( T *item , gzDouble sortval)
{
	LinkItem *newlink=allocLink();


	newlink->item=item;
	newlink->sortval=sortval;
	
	onInsert(item);

	if(m_last)
	{
		if(m_last->sortval<sortval)
		{

			m_last->next=newlink;
			newlink->next=nullptr;
			newlink->prev=m_last;
			m_last=newlink;
			++m_entries;

			return NULL;
		}
	}


	T *deleteitem=0;

	LinkItem *sortitem=m_link;
	LinkItem *previtem=0;


	while(sortitem)
	{
		if(sortitem->sortval<sortval)
		{
			if(!previtem)
				previtem=sortitem;
			else
				previtem=previtem->next;
			sortitem=sortitem->next;
		}
		else if(sortitem->sortval==sortval)
		{
			deleteitem=sortitem->item;
			sortitem->item=item;
			disposeLink(newlink);
			onRemove(deleteitem);
			return deleteitem;
		}
		else
			break;
	}

	if(sortitem)
	{
		sortitem->prev=newlink;
	}
	newlink->prev=previtem;

	newlink->next=sortitem;

	if(!previtem)
		m_link=newlink;
	else
		previtem->next=newlink;
	
	if(!sortitem)
		m_last=newlink;

	++m_entries;

	return deleteitem;
}

//***********************************************************************

template <class T> inline gzBool gzDList<T>::post_insert( T *item , gzDouble sortval)
{
	LinkItem *newlink=allocLink();

	newlink->item=item;
	newlink->sortval=sortval;
	
	onInsert(item);
	
	if(m_last)
	{
		if(m_last->sortval<=sortval)
		{
			gzBool insert=(m_last->sortval==sortval);

			m_last->next=newlink;
			newlink->next=nullptr;
			newlink->prev=m_last;
			m_last=newlink;
			++m_entries;

			return insert;
		}
	}

	
	LinkItem *sortitem=m_link;
	LinkItem *previtem=0;

	
	while(sortitem)
	{
		if(sortitem->sortval<=sortval)
		{
			if(!previtem)
				previtem=sortitem;
			else
				previtem=previtem->next;
			sortitem=sortitem->next;
		}
		else
			break;
	}

	if(sortitem)
	{
		sortitem->prev=newlink;
	}
	newlink->prev=previtem;

	newlink->next=sortitem;

	if(!previtem)
		m_link=newlink;
	else
		previtem->next=newlink;
	
	++m_entries;

	if(!sortitem)
		m_last=newlink;

	if(previtem)
	{
		if(previtem->sortval==sortval)
			return TRUE;
		else
			return FALSE;
	}

	return FALSE;

}

//***********************************************************************

template <class T> inline gzBool gzDList<T>::pre_insert( T *item , gzDouble sortval)
{
	LinkItem *newlink=allocLink();

	newlink->item=item;
	newlink->sortval=sortval;

	onInsert(item);

	if(m_last)
	{
		if(m_last->sortval<sortval)
		{

			m_last->next=newlink;
			newlink->next=nullptr;
			newlink->prev=m_last;
			m_last=newlink;
			++m_entries;

			return FALSE;
		}
	}

	LinkItem *sortitem=m_link;
	LinkItem *previtem=0;

	
	while(sortitem)
	{
		if(sortitem->sortval<sortval)
		{
			if(!previtem)
				previtem=sortitem;
			else
				previtem=previtem->next;
			sortitem=sortitem->next;
		}
		else
			break;
	}

	if(sortitem)
	{
		sortitem->prev=newlink;
	}
	newlink->prev=previtem;

	newlink->next=sortitem;
	if(!previtem)
		m_link=newlink;
	else
		previtem->next=newlink;
	
	++m_entries;

	if(!sortitem)
		m_last=newlink;
	else
	{
		if(sortitem->sortval==sortval)
			return TRUE;
		else
			return FALSE;
	}

	return FALSE;
}

//***********************************************************************

template <class T> inline gzDList<T> & gzDList<T>::operator=(const gzList<T> &copy )
{
	clear();	// rensa gammal data

	gzListConstIterator<T>	iterator(copy);
	T *item;

	while((item=iterator()))
		insert(cloneEntry(item));

	return *this;
}

//***********************************************************************

template <class T> inline gzDList<T> & gzDList<T>::operator=(const gzDList &copy )
{
	if(&copy==this)
		return *this;

	clear();	// rensa gammal data

	LinkItem *link=copy.m_link;

	m_link=0;
	m_last=0;

	while(link)
	{
		LinkItem *newlink=allocLink();
		
		newlink->item=cloneEntry(link->item); // default to copy of instance

		onInsert(newlink->item);
		newlink->sortval=link->sortval;
		newlink->next=0;
		newlink->prev=m_last;

		if(m_last)
			m_last->next=newlink;
		else
			m_link=newlink;

		m_last=newlink;

		link=link->next;
	}
	m_entries=copy.m_entries;

	return *this;
}

//***********************************************************************

template <class T> inline gzDList<T>::gzDList(const gzList<T> &copy):m_link(0),m_last(0),m_entries(0),m_recycle(0),m_reuseLinks(FALSE)
{
	gzListConstIterator<T>	iterator(copy);
	T *item;

	while((item=iterator()))
		insert(cloneEntry(item));

}

//***********************************************************************

template <class T> inline gzDList<T>::gzDList(const gzDList<T> &copy)
{
	LinkItem *link=copy.m_link;

	m_link=0;
	m_last=0;
	m_recycle=0;
	m_reuseLinks=copy.m_reuseLinks;

	while(link)
	{
		LinkItem *newlink=allocLink();
		
		newlink->item=cloneEntry(link->item); // default to copy of instance

		onInsert(newlink->item);
		newlink->sortval=link->sortval;
		newlink->next=0;
		newlink->prev=m_last;

		if(m_last)
			m_last->next=newlink;
		else
			m_link=newlink;

		m_last=newlink;

		link=link->next;
	}
	m_entries=copy.m_entries;
}

//***********************************************************************

template <class T> inline gzVoid gzDList<T>::clearAndDestroy()
{
	if(m_link)
	{
		LinkItem *nextlink;

		while(m_link)
		{
			nextlink=m_link->next;
			onRemove(m_link->item);
			delete m_link->item;
			disposeLink(m_link);

			m_link=nextlink;
		}
		m_entries=0;
		m_last=0;
	}
}

template <> inline gzVoid gzDList<gzVoid>::clearAndDestroy()
{
	// Can not execute delete on void data
	clear();
}


//***********************************************************************

template <class T> inline gzVoid gzDList<T>::clear()
{
	LinkItem *nextlink;

	while(m_link)
	{
		nextlink=m_link->next;
		onRemove(m_link->item);
		disposeLink(m_link);

		m_link=nextlink;
	}
	m_entries=0;
	m_last=0;
}


//******************************************************************************
// Template	: gzDListIterator
//									
// Purpose  : Iterator for gzDList
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980601	Created 
//									
//******************************************************************************
//! Iterator class for gzDList

/*! The Iterator can be used with all gzDLists and its derivatives. Typical usage is to use
it as follows...

\code

	gzDListIterator<MyListItemClass>	iterator(myActualList);
	MyListItemClass *item;

	while((item=iterator()))
	{
		// Do somthing with item that is iterated through the list
	}

\endcode
	
	Note that iterator can safely remove items with the remove() operator
	in the iterator while iterating the list

*/

template <class T> class gzDListIterator 
{
	public:

		//! Constructor of list iterator
		gzDListIterator(gzDList<T> &owner);

		//! Constructor of list iterator
		gzDListIterator(gzDList<T> *owner);

		//! Default destructor
		~gzDListIterator(){};

		//! Iterating operator
		/*! The operator () iterates one step through list and returns item 
			at current list iterator position. At end of list it returns NULL */
		T *operator()();

		T *operator++(int);	// postfix operator

		T *operator--(int);	// postfix operator

		//! Circulating operator
		/*! The circulate() method iterates through the list just like the () operator, but
			it restarts at the beginnig of the list when the end is reached. */
		T *circulate();

		T *backcirculate();

		//! Returns item at current iterator position.
		/*! Undefined if iterator position is undefined e.g. before operator () is called. */
		T *key();

		//! Returns one item ahead in list. You can get the next item without iterating.
		T *next();

		T *prev();

		//! Removes safely item at current iterator position.
		/*! You should no use key() etc. when you have removed current item !! */
		T *remove();

		//! Reset iterator position to position before start of list
		gzVoid reset();

		gzVoid setList(gzDList<T> &owner);

		//! Reset iterator position to first item of list
		gzVoid setFirst();

		//! Reset iterator position to last item of list
		gzVoid setLast();

		//! Get current key sortval
		gzDouble sortval();

		//! Insert item after current item. If no valid pos the insert is discarded
		gzVoid post_insert(T *item);

		//! Insert item before current item. If no valid pos the insert is discarded
 		gzVoid pre_insert(T *item);

	private:

		typename gzDList<T>::LinkItem *m_link;

		gzDList<T> *m_owner;

		gzBool		m_circulating;

};

//***********************************************************************

template <class T> inline gzDListIterator<T>::gzDListIterator(gzDList<T> &owner)
{
	m_link=0;
	m_owner=&owner;
}

//***********************************************************************

template <class T> inline gzDListIterator<T>::gzDListIterator(gzDList<T> *owner)
{
	m_link=0;
	m_owner=owner;
}

//***********************************************************************

template <class T> inline gzDouble gzDListIterator<T>::sortval()
{
	if(m_link)
		return m_link->sortval;
	else
		return 0;
}

//***********************************************************************

template <class T> inline gzVoid gzDListIterator<T>::post_insert(T *item)
{
	if(m_link)
	{
		typename gzDList<T>::LinkItem *link=m_owner->allocLink();

		link->next=m_link->next;

		link->prev=m_link;

		link->sortval=0;

		link->item=item;


		if(!m_link->next)
			m_owner->m_last=link;
		else
			m_link->next->prev=link;


		m_link->next=link;

		m_owner->onInsert(item);

		++m_owner->m_entries;
	}
}

//***********************************************************************

template <class T> inline gzVoid gzDListIterator<T>::pre_insert(T *item)
{
	if(m_link)
	{
		typename gzDList<T>::LinkItem *link=m_owner->allocLink();

		link->next=m_link;

		link->prev=m_link->prev;

		link->sortval=0;

		link->item=item;


		if(!m_link->prev)
			m_owner->m_link=link;
		else
			m_link->prev->next=link;

		m_link->prev=link;

		m_owner->onInsert(item);

		++m_owner->m_entries;
	}
}

//***********************************************************************

template <class T> inline T * gzDListIterator<T>::remove()
{
	if(!m_link)
		return NULL;


	T *item=m_link->item;

	typename gzDList<T>::LinkItem *link;

	if(!m_link->next)
		m_owner->m_last=m_link->prev;
	else
		m_link->next->prev=m_link->prev;

	link=m_link->next;

	if(m_link->prev)
		m_link->prev->next=link;
	else
		m_owner->m_link=link;

	m_owner->onRemove(m_link->item);

	m_owner->disposeLink(m_link);

	m_owner->m_entries--;

	if(link)
		m_link=link->prev;
	else
		m_link=m_owner->m_last;

	return item;
}

//***********************************************************************

template <class T> inline gzVoid gzDListIterator<T>::reset()
{
	m_link=0;
}

//***********************************************************************

template <class T> inline gzVoid gzDListIterator<T>::setList(gzDList<T> &owner)
{
	m_link=0;
	m_owner=&owner;
}

//***********************************************************************

template <class T> inline gzVoid gzDListIterator<T>::setFirst()
{
	m_circulating=FALSE;
	m_link=m_owner->m_link;
}

//***********************************************************************

template <class T> inline gzVoid gzDListIterator<T>::setLast()
{
	m_circulating=FALSE;
	m_link=m_owner->m_last;
}

//***********************************************************************

template <class T> inline T *gzDListIterator<T>::operator()()
{
	m_circulating=FALSE;

	if(m_link)
		m_link=m_link->next;
	else
		m_link=m_owner->m_link;

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline T *gzDListIterator<T>::operator++(int)
{
	return operator()();
}

//***********************************************************************

template <class T> inline T *gzDListIterator<T>::operator--(int)
{
	m_circulating=FALSE;

	if(m_link)
		m_link=m_link->prev;
	else
		m_link=m_owner->m_last;

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************
	
template <class T> inline T *gzDListIterator<T>::circulate()
{
	m_circulating=TRUE;

	if(m_link)
		m_link=m_link->next;

	if(!m_link)
	{
		m_link=m_owner->m_link;
	}

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline T *gzDListIterator<T>::backcirculate()
{
	m_circulating=TRUE;

	if(m_link)
		m_link=m_link->prev;

	if(!m_link)
	{
		m_link=m_owner->m_last;
	}

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline T *gzDListIterator<T>::key()
{
	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline T *gzDListIterator<T>::next()
{
	if(m_link)
	{
		if(m_link->next)
			return m_link->next->item;
		else if(m_circulating)
			return m_owner->m_link->item;
	}
	return NULL;
}

//***********************************************************************

template <class T> inline T *gzDListIterator<T>::prev()
{
	if(m_link)
	{
		if(m_link->prev)
			return m_link->prev->item;
		else if(m_circulating)
			return m_owner->m_last->item;
	}
	return NULL;
}

//******************************************************************************
// Template	: gzDListConstIterator
//									
// Purpose  : Const Iterator for gzDList
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040301	Created 
//									
//******************************************************************************
//! Const Iterator class for gzDList

/*! The Iterator can be used with all gzDLists and its derivatives. Typical usage is to use
it as follows...

\code

	gzDListConstIterator<MyListItemClass>	iterator(myActualList);
	const MyListItemClass *item;

	while((item=iterator()))
	{
		// Do somthing with item that is iterated through the list
	}

\endcode
*/

template <class T> class gzDListConstIterator
{
	public:

		//! Constructor of list iterator
		gzDListConstIterator(const gzDList<T> &owner);

		//! Default destructor
		~gzDListConstIterator(){};

		//! Iterating operator
		/*! The operator () iterates one step through list and returns item 
			at current list iterator position. At end of list it returns NULL */
		T *operator()();

		T *operator++(int);	// postfix operator

		T *operator--(int);	// postfix operator

		//! Circulating operator
		/*! The circulate() method iterates through the list just like the () operator, but
			it restarts at the beginnig of the list when the end is reached. */
		const T *circulate();

		const T *backcirculate();

		//! Returns item at current iterator position.
		/*! Undefined if iterator position is undefined e.g. before operator () is called. */
		const T *key();

		//! Returns one item ahead in list. You can get the next item without iterating.
		const T *next();

		const T *prev();

		//! Reset iterator position to position before start of list
		gzVoid reset();

		//! Reset iterator position to first item of list
		gzVoid setFirst();

		//! Reset iterator position to last item of list
		gzVoid setLast();

		//! Get current key sortval
		gzDouble sortval();

	private:

		typename gzDList<T>::LinkItem *m_link;

		const gzDList<T> *	m_owner;

		gzBool				m_circulating;

};

//***********************************************************************

template <class T> inline gzBool gzDList<T>::contains(const T *item) const
{
	const typename gzDList<T>::LinkItem* link = m_link;
		
	while (link)
	{
		if (link->item == item)
		{
			return TRUE;
		}

		link = link->next;
	}
	
	return FALSE;
}

//***********************************************************************

template <class T> inline gzInt32 gzDList<T>::index(const T *item) const
{
	const typename gzDList<T>::LinkItem* link = m_link;

	gzInt32 index(0);
		
	while (link)
	{
		if (link->item == item)
		{
			return index;
		}

		++index;

		link = link->next;
	}
	
	return -1;
}

//***********************************************************************

template <class T> inline gzDListConstIterator<T>::gzDListConstIterator(const gzDList<T> &owner)
{
	m_link=0;
	m_owner=&owner;
}

//***********************************************************************

template <class T> inline gzDouble gzDListConstIterator<T>::sortval()
{
	if(m_link)
		return m_link->sortval;
	else
		return 0;
}

//***********************************************************************

template <class T> inline gzVoid gzDListConstIterator<T>::reset()
{
	m_link=0;
}

//***********************************************************************

template <class T> inline gzVoid gzDListConstIterator<T>::setFirst()
{
	m_circulating=FALSE;
	m_link=m_owner->m_link;
}

//***********************************************************************

template <class T> inline gzVoid gzDListConstIterator<T>::setLast()
{
	m_circulating=FALSE;
	m_link=m_owner->m_last;
}

//***********************************************************************

template <class T> inline T *gzDListConstIterator<T>::operator()()
{
	m_circulating=FALSE;

	if(m_link)
		m_link=m_link->next;
	else
		m_link=m_owner->m_link;

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline T *gzDListConstIterator<T>::operator++(int)
{
	return operator()();
}

//***********************************************************************

template <class T> inline T *gzDListConstIterator<T>::operator--(int)
{
	m_circulating=FALSE;

	if(m_link)
		m_link=m_link->prev;
	else
		m_link=m_owner->m_last;

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************
	
template <class T> inline const T *gzDListConstIterator<T>::circulate()
{
	m_circulating=TRUE;

	if(m_link)
		m_link=m_link->next;

	if(!m_link)
	{
		m_link=m_owner->m_link;
	}

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline const T *gzDListConstIterator<T>::backcirculate()
{
	m_circulating=TRUE;

	if(m_link)
		m_link=m_link->prev;

	if(!m_link)
	{
		m_link=m_owner->m_last;
	}

	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline const T *gzDListConstIterator<T>::key()
{
	if(m_link)
		return m_link->item;
	else
		return NULL;
}

//***********************************************************************

template <class T> inline const T *gzDListConstIterator<T>::next()
{
	if(m_link)
	{
		if(m_link->next)
			return m_link->next->item;
		else if(m_circulating)
			return m_owner->m_link->item;
	}
	return NULL;
}

//***********************************************************************

template <class T> inline const T *gzDListConstIterator<T>::prev()
{
	if(m_link)
	{
		if(m_link->prev)
			return m_link->prev->item;
		else if(m_circulating)
			return m_owner->m_last->item;
	}
	return NULL;
}

//***********************************************************************

template <class T1 , class T2> class gzHashPair
{
public:

	gzHashPair(const T1 & hashItem=T1() , const T2 & valueItem=T2()):m_hashItem(hashItem),m_valueItem(valueItem)
	{
	}
		
	gzUInt32 hash() const 
	{ 
		return m_hashItem.hash(); 
	}

 	gzBool operator ==(const gzHashPair<T1,T2> &right)
	{
		return (m_hashItem==right.m_hashItem) && (m_valueItem==right.m_valueItem);
	}

private:

	T1	m_hashItem;

	T2	m_valueItem;

};

//***********************************************************************

template <class T> class gzDoubleHash
{
public:

	gzDoubleHash(const T & hashItem1=T() , const T & hashItem2=T()):m_hashItem1(hashItem1),m_hashItem2(hashItem2)
	{
	}
		
	gzUInt32 hash() const 
	{ 
		return m_hashItem1.hash()*m_hashItem2.hash(); 
	}

 	gzBool operator ==(const gzDoubleHash<T> &right)
	{
		return	((m_hashItem1==right.m_hashItem1) && (m_hashItem2==right.m_hashItem2)) ;
				
	}

private:

	T	m_hashItem1;

	T	m_hashItem2;

};

//***********************************************************************

template <class T> class gzTripleHash
{
public:

	gzTripleHash(const T & hashItem1 = T(), const T & hashItem2 = T(), const T & hashItem3 = T()) :m_hashItem1(hashItem1), m_hashItem2(hashItem2), m_hashItem3(hashItem3)
	{
	}

	gzUInt32 hash() const
	{
		return m_hashItem1.hash()*m_hashItem2.hash()*m_hashItem3.hash();
	}

	gzBool operator ==(const gzTripleHash<T> &right)
	{
		return	((m_hashItem1 == right.m_hashItem1) && (m_hashItem2 == right.m_hashItem2) && (m_hashItem3 == right.m_hashItem3));

	}

private:

	T	m_hashItem1;

	T	m_hashItem2;

	T	m_hashItem3;

};

template <> inline gzUInt32 gzTripleHash<gzUInt32>::hash() const
{
	return m_hashItem1*m_hashItem2*m_hashItem3;
}

//***********************************************************************

template <class T> class gzLateBindData
{
public:

	gzLateBindData();

	gzLateBindData(const gzLateBindData<T> &copy);

	gzVoid operator=(const gzLateBindData<T> &copy);

	const T & operator=(const T& copy);

	~gzLateBindData();

	gzBool operator==(const gzLateBindData<T> &right) const;

	operator T&();

	gzBool isBound() const;

	gzVoid unBind();

	gzVoid bind();

	T & get();

	const T & read() const;

	T * operator ->();

private:

	T *m_pointer;

};

template <class T> inline gzLateBindData<T>::gzLateBindData():m_pointer(NULL){};

template <class T> inline gzBool gzLateBindData<T>::isBound() const
{
	return m_pointer!=nullptr;
}

template <class T> inline gzVoid gzLateBindData<T>::unBind()
{
	if(m_pointer)
	{
		delete m_pointer;
		m_pointer=nullptr;
	}
}


template <class T> inline gzLateBindData<T>::gzLateBindData(const gzLateBindData<T> &copy)
{
	if(copy.m_pointer)
	{
		m_pointer=new T(*copy.m_pointer);
	}
	else
		m_pointer=nullptr;
}

template <class T> inline const T & gzLateBindData<T>::operator=(const T& copy)
{
	if (m_pointer)
		delete m_pointer;

	m_pointer = new T(copy);

	return *m_pointer;
}

template <class T> inline gzBool gzLateBindData<T>::operator==(const gzLateBindData<T> &right) const
{
	if(!m_pointer && !right.m_pointer)
		return TRUE;

	if(m_pointer && right.m_pointer)
		return *m_pointer==*right.m_pointer;

	return FALSE;
}

template <class T> inline gzVoid gzLateBindData<T>::operator=(const gzLateBindData<T> &copy)
{
	if(copy.m_pointer)
	{
		if(!m_pointer)
			m_pointer=new T;

		*m_pointer=*copy.m_pointer;
	}
	else
	{
		if(m_pointer)
			delete m_pointer;
		m_pointer=nullptr;
	}
}

template <class T> inline gzLateBindData<T>::~gzLateBindData()
{
	if(m_pointer)
		delete m_pointer;
}

template <class T> inline gzLateBindData<T>::operator T&()
{
	if(!m_pointer)
		m_pointer=new T;

	return *m_pointer;
}


template <class T> inline T * gzLateBindData<T>::operator ->()
{
	if(!m_pointer)
		m_pointer=new T;

	return m_pointer;
}

template <class T> inline T & gzLateBindData<T>::get()
{
	if(!m_pointer)
		m_pointer=new T;

	return *m_pointer;
}

template <class T> inline gzVoid gzLateBindData<T>::bind()
{
	if (!m_pointer)
		m_pointer = new T;
}

template <class T> inline const T & gzLateBindData<T>::read() const
{
	if(!m_pointer)
		throwFatalTemplateError("Can not read non bound gzLateBind");

	return *m_pointer;
}

//***********************************************************************

template <class T> class gzLateBindArray
{
public:

	gzLateBindArray(gzUInt32 size=0);

	gzLateBindArray(const gzLateBindArray<T> &copy);

	gzVoid operator=(const gzLateBindArray<T> &copy);

	const T& operator +=(const T& value);

	~gzLateBindArray();

	T& operator [](gzUInt32 index);

	gzVoid setSize(gzUInt32 size);

	gzUInt32 getSize() const;

	gzBool isBound();

	gzVoid unBind();

private:

	gzVoid operator=(const gzUInt32 data){};	// prevent constructor mismatch

	T		*m_data;

	gzUInt32 m_size;

};

template <class T> inline gzLateBindArray<T>::gzLateBindArray(gzUInt32 size):m_data(NULL),m_size(size){};

template <class T> inline gzBool gzLateBindArray<T>::isBound()
{
	return m_data!=nullptr;
}

template <class T> inline gzVoid gzLateBindArray<T>::unBind()
{
	if(m_data)
	{
		delete [] m_data;
		m_data=nullptr;
	}
}

template <class T> inline gzLateBindArray<T>::gzLateBindArray(const gzLateBindArray<T> &copy)
{
	m_size=copy.m_size;

	if(copy.m_data)
	{
		m_data=new T[m_size];

		for(gzUInt32 i=0;i<m_size;++i)
			m_data[i]=copy.m_data[i];
	}
	else
		m_data=nullptr;
}

template <class T> inline gzVoid gzLateBindArray<T>::operator=(const gzLateBindArray<T> &copy)
{
	if(copy.m_data)
	{
		if(m_size!=copy.m_size)
		{
			if(m_data)
				delete [] m_data;

			m_data=new T[copy.m_size];

		}
		else
			if(!m_data)
				m_data=new T[copy.m_size];

		for(gzUInt32 i=0;i<copy.m_size;++i)
			m_data[i]=copy.m_data[i];
	}
	else
	{
		if(m_data)
		{
			delete [] m_data;
			m_data=nullptr;
		}
	}

	m_size=copy.m_size;
}

template <class T> inline gzLateBindArray<T>::~gzLateBindArray()
{
	if(m_data)
		delete [] m_data;
}

template <class T> inline T & gzLateBindArray<T>::operator [](gzUInt32 index) 
{
	if(index>=m_size)
		throwFatalTemplateError("gzLateBindArray [] index out of bounds");

	if(!m_data)
		m_data=new T[m_size];

	return m_data[index];
}

template <class T> inline const T& gzLateBindArray<T>::operator +=(const T& value)
{
	T* m_new_data = new T[m_size + 1];

	if(m_data)
		copyInstances<T>(m_new_data, m_data, m_size);

	m_new_data[m_size] = value;

	if (m_data)
		delete[] m_data;

	m_data = m_new_data;

	++m_size;

	return m_new_data[m_size - 1];
}

template <class T> inline gzVoid gzLateBindArray<T>::setSize(gzUInt32 size)
{
	if(size!=m_size)
	{
		if(m_data)
		{
			delete [] m_data;
			m_data=nullptr;
		}

		m_size=size;
	}
}

template <class T> inline gzUInt32 gzLateBindArray<T>::getSize() const
{
	return m_size;
}


//***********************************************************************

template <class T> class gzArray2D : public gzArray<T>
{
public:

	gzArray2D(const gzUInt32 size_x=0,const gzUInt32 size_y=0);

	const gzUInt32XY	getSize() const ;

	gzVoid	setSize(const gzUInt32 size_x, const gzUInt32 size_y);

	gzVoid	setPOTSize(const gzUInt32 pot_x_size,const gzUInt32 pot_y_size);

	T & operator()(const gzUInt32 x_index,const gzUInt32 y_index);

	const T& get(const gzUInt32 x_index,const gzUInt32 y_index) const;

	gzVoid	clear();

protected:

	// Access without boundary check
	const T &	getItemInternal(const gzUInt32 x_index,const gzUInt32 y_index) const;
	gzVoid		setItemInternal(const gzUInt32 x_index,const gzUInt32 y_index,const T &val);


	gzUInt32						m_x_size;
	gzUInt32						m_y_size;
};

template <class T> inline T & gzArray2D<T>::operator()(const gzUInt32 x_index,const gzUInt32 y_index)
{
	if(x_index>=m_x_size )
		throwFatalTemplateError("gzArray2D<T>(x,y) x index out of bounds");

	if(y_index>=m_y_size )
		throwFatalTemplateError("gzArray2D<T>(x,y) y index out of bounds");

	gzArray<T>::m_untouched=FALSE;

	if (!gzArray<T>::m_data)	// Sonar
		throwFatalTemplateError("gzArray2D<T>(x,y) null pointer");

	return *(gzArray<T>::m_data+y_index*m_x_size+x_index);
}

template <class T> inline const T & gzArray2D<T>::get(const gzUInt32 x_index,const gzUInt32 y_index) const
{
	if(x_index>=m_x_size )
		throwFatalTemplateError("gzArray2D<T>::get(x,y) x index out of bounds");

	if(y_index>=m_y_size )
		throwFatalTemplateError("gzArray2D<T>::get(x,y) y index out of bounds");

	return getItemInternal(x_index,y_index);
}

template <class T> inline gzVoid gzArray2D<T>::setItemInternal(const gzUInt32 x_index,const gzUInt32 y_index,const T &val)
{
	*(gzArray<T>::m_data+y_index*m_x_size+x_index)=val;

	gzArray<T>::m_untouched=FALSE;
}

template <class T> inline const T & gzArray2D<T>::getItemInternal(const gzUInt32 x_index,const gzUInt32 y_index) const
{
	return *(gzArray<T>::m_data+y_index*m_x_size+x_index);
}

template <class T> inline gzArray2D<T>::gzArray2D(const gzUInt32 size_x, const gzUInt32 size_y)
{
	setSize(size_x,size_y);
}

template <class T> inline gzVoid gzArray2D<T>::clear()
{
	setSize(0,0);
}

template <class T> inline gzVoid gzArray2D<T>::setSize(const gzUInt32 x_size, const gzUInt32 y_size)
{
	gzUInt64 size = (gzUInt64)x_size * (gzUInt64)y_size;

	if(size!=(gzUInt32)size)
		throwFatalTemplateError("gzArray2D<T>(x,y) size out of bounds");

	gzArray<T>::setSize((gzUInt32)size);

	m_x_size=x_size;
	m_y_size=y_size;
}

template <class T> inline gzVoid gzArray2D<T>::setPOTSize(const gzUInt32 pot_x_size,const gzUInt32 pot_y_size)
{
	m_x_size=1UL<<pot_x_size;
	m_y_size=1UL<<pot_y_size;

	gzArray<T>::setSize(m_x_size*m_y_size);
}


template <class T> inline const gzUInt32XY gzArray2D<T>::getSize() const
{
	return gzUInt32XY(m_x_size,m_y_size);
}


//***********************************************************************
// Special Quick Insertion sort invented by Anders Modén
// Copyright 1997 ToolTech Software
//***********************************************************************

const gzUInt32 GZ_DATASORT_EMPTY_INDEX=0xfffffffful;

template <class T,class SORTVAL=gzDouble> class gzDataSortIterator;

template <class T,class SORTVAL=gzDouble> class gzDataSort
{
public:

	gzDataSort(const gzUInt32 entries=100,const gzUInt32 chunkSize=100);

	gzDataSort(const gzDataSort<T,SORTVAL> &right);

	~gzDataSort();

	// methods

	gzVoid		insert(const T &item,const SORTVAL &sortval , gzBool multipleInstances=TRUE);

	gzVoid		remove(const T &item,const SORTVAL &sortval,gzBool cleanItems=FALSE);

	gzVoid		clear(gzBool cleanItems=FALSE);

	gzUInt32	getSize() const;

	gzVoid		setChunkSize(gzUInt32 size);

	gzVoid		setRealSize(gzUInt32 size);

	gzUInt32	getRemoved() const;

	gzVoid		reorder(gzBool cleanupCache=FALSE);	// removes removed entries

	gzVoid		operator=(const gzDataSort<T,SORTVAL> &copy);

	T &			operator[](gzUInt32 index);

	gzVoid		getSortedArray(gzArray<T> &arrayOut);

private:

	friend class gzDataSortIterator<T,SORTVAL>; 

	struct Item
	{
		SORTVAL		sortval;

		SORTVAL		min_interval;
		SORTVAL		max_interval;

		gzUInt32	addItem;
		gzUInt32	currAddItem;

		gzUInt32	next;
		gzUInt32	prev;
		gzUInt32	top;

		T			data;

		gzBool		removed:1;
		gzBool		valid_min:1;
		gzBool		valid_max:1;
	};

	struct AddItem
	{
		gzUInt32	nextAddItem;

		T			data;

		gzBool		removed;
		
	};

	gzDynamicArray<Item>	itemArray;
	gzUInt32				currentItemIndex;

	gzDynamicArray<AddItem>	addItemArray;
	gzUInt32				currentAddItemIndex;

	gzUInt32				currentRemoved;

	gzDataSort<T,SORTVAL>	*reorder_cache;

};

//***********************************************************************

template <class T,class SORTVAL> inline gzDataSort<T,SORTVAL>::gzDataSort(const gzDataSort<T,SORTVAL> &right):itemArray(right.itemArray.getChunkSize(),right.itemArray.getRealSize()),addItemArray(right.addItemArray.getChunkSize(),right.addItemArray.getRealSize())
{
	itemArray.setSize(0);

	addItemArray.setSize(0);

	currentRemoved=0;

	reorder_cache=nullptr;

	gzDataSortIterator<T,SORTVAL> iterator((gzDataSort<T,SORTVAL> &)right);

	T *item;

	while((item=iterator()))
		insert(*item,iterator.sortval(),TRUE);
}

template <class T,class SORTVAL> inline gzVoid gzDataSort<T,SORTVAL>::setChunkSize(gzUInt32 size)
{
	itemArray.setChunkSize(size);
	addItemArray.setChunkSize(size);
}

template <class T,class SORTVAL> inline gzVoid gzDataSort<T,SORTVAL>::setRealSize(gzUInt32 size)
{
	clear();

	itemArray.setRealSize(size);
	addItemArray.setRealSize(size);
}

template <class T,class SORTVAL> inline gzUInt32 gzDataSort<T,SORTVAL>::getSize() const
{ 
	return itemArray.getSize()+addItemArray.getSize()-currentRemoved; 
}

template <class T,class SORTVAL> inline gzVoid gzDataSort<T,SORTVAL>::clear(gzBool cleanItems)
{
	if(cleanItems)
	{
		gzDataSort<T,SORTVAL>::Item *item(itemArray.getAddress());

		gzUInt32 count(itemArray.getSize());

		while(count)
		{
			if(!item->removed)
				item->data=T();

			++item;
			--count;
		}

		gzDataSort<T,SORTVAL>::AddItem *additem(addItemArray.getAddress());

		count=addItemArray.getSize();

		while(count)
		{
			if(!additem->removed)
				additem->data=T();

			++additem;
			--count;
		}
	}

	itemArray.setSize(0);
	addItemArray.setSize(0);

	currentRemoved=0;
}

template <class T,class SORTVAL> inline gzUInt32 gzDataSort<T,SORTVAL>::getRemoved() const
{
	return currentRemoved;
}

//***********************************************************************

template <class T,class SORTVAL> inline gzDataSort<T,SORTVAL>::gzDataSort(const gzUInt32 entries,const gzUInt32 chunkSize):itemArray(gzMax(chunkSize,1U)),addItemArray(gzMax(chunkSize,1U))
{
	itemArray.setRealSize(gzMax(entries,1U));
	itemArray.setSize(0);

	addItemArray.setRealSize(gzMax(entries,1U));
	addItemArray.setSize(0);

	currentRemoved=0;

	reorder_cache=nullptr;
}

template <class T,class SORTVAL> inline gzDataSort<T,SORTVAL>::~gzDataSort()
{
	if(reorder_cache)
		delete reorder_cache;
}

//***********************************************************************

template <class T,class SORTVAL> inline gzVoid gzDataSort<T,SORTVAL>::insert(const T &data,const SORTVAL &sortval, gzBool multipleInstances)
{
	Item *item=itemArray.getAddress();

	gzInt32 size(itemArray.getSize());

	// Add first item

	if(!size)
	{
		itemArray.setSize(1);
		item=itemArray.getAddress();
		item->data=data;
		item->top=item->next=item->prev=item->addItem=GZ_DATASORT_EMPTY_INDEX;
		item->sortval=sortval;
		item->min_interval=0;
		item->max_interval=0;
		item->valid_max=FALSE;
		item->valid_min=FALSE;
		item->removed=FALSE;
		currentItemIndex=0;
		currentAddItemIndex=0;

		return;
	}

	// Search interval top node

	Item *sitem;

	SORTVAL min,max;
	gzBool valid;

	while(TRUE)
	{
		sitem=item+currentItemIndex;

		if( ((!sitem->valid_min) || (sortval>sitem->min_interval)) && ((!sitem->valid_max) || (sortval<sitem->max_interval)))
			break;

		currentItemIndex=sitem->top;
	}

	// Search sibling node and add

	while(TRUE)
	{
		if(sortval>sitem->sortval)
		{
			if(sitem->next!=GZ_DATASORT_EMPTY_INDEX)
			{
				currentItemIndex=sitem->next;
				sitem=item+currentItemIndex;
				continue;
			}
			else
			{
				sitem->next=size;
				min=sitem->sortval;
				max=sitem->max_interval;
				valid=sitem->valid_max;

				sitem=&itemArray[size];

				sitem->sortval=sortval;
				sitem->next=sitem->prev=sitem->addItem=GZ_DATASORT_EMPTY_INDEX;
				sitem->top=currentItemIndex;
				sitem->max_interval=max;
				sitem->min_interval=min;
				sitem->valid_max=valid;
				sitem->valid_min=TRUE;
				
				sitem->removed=FALSE;

				sitem->data=data;
				currentItemIndex=size;
				return;
			}
		}
		else if(sortval<sitem->sortval)
		{
			if(sitem->prev!=GZ_DATASORT_EMPTY_INDEX)
			{
				currentItemIndex=sitem->prev;
				sitem=item+currentItemIndex;
				continue;
			}
			else
			{
				sitem->prev=size;
				min=sitem->min_interval;
				max=sitem->sortval;
				valid=sitem->valid_min;

				sitem=&itemArray[size];

				sitem->sortval=sortval;
				sitem->next=sitem->prev=sitem->addItem=GZ_DATASORT_EMPTY_INDEX;
				sitem->top=currentItemIndex;
				sitem->max_interval=max;
				sitem->min_interval=min;
				sitem->valid_max=TRUE;
				sitem->valid_min=valid;

				sitem->removed=FALSE;

				sitem->data=data;
				currentItemIndex=size;
				return;
			}
		}
		else	// Same Sort Value
		{
			AddItem *aditem;

			//if(!multipleInstances)
			//{
			//	// Don't use multiple instances
			//	return;
			//}
			
			if(sitem->addItem!=GZ_DATASORT_EMPTY_INDEX)	// We have data
			{
				aditem=addItemArray.getAddress()+sitem->currAddItem;

				aditem->nextAddItem=sitem->currAddItem=currentAddItemIndex;
			}
			else
			{
				if(sitem->removed)
				{
					sitem->data=data;
					sitem->removed=FALSE;
					--currentRemoved;
					return;
				}

				if(!multipleInstances)	// We don't allow multiple instances and just update data in current instance
				{
					sitem->data=data;
					return;
				}
				
				sitem->addItem=sitem->currAddItem=currentAddItemIndex;
			}
			
			aditem=&addItemArray[currentAddItemIndex];

			aditem->nextAddItem=GZ_DATASORT_EMPTY_INDEX;
			aditem->data=data;
			aditem->removed=FALSE;

			++currentAddItemIndex;

			return;
		}
	}
}

template <class T,class SORTVAL> inline gzVoid gzDataSort<T,SORTVAL>::remove(const T &data,const SORTVAL &sortval,gzBool cleanItems)
{
	Item *item=itemArray.getAddress();

	gzInt32 size(itemArray.getSize());

	if(!size)
	{
		return;
	}

	// Search interval top node

	Item *sitem;

	while(TRUE)
	{
		sitem=item+currentItemIndex;

		if( ((!sitem->valid_min) || (sortval>sitem->min_interval)) && ((!sitem->valid_max) || (sortval<sitem->max_interval)))
			break;

		currentItemIndex=sitem->top;
	}

	// Search sibling node and add

	while(TRUE)
	{
		if(sortval>sitem->sortval)
		{
			if(sitem->next!=GZ_DATASORT_EMPTY_INDEX)
			{
				currentItemIndex=sitem->next;
				sitem=item+currentItemIndex;
				continue;
			}
			else
				return;
		}
		else if(sortval<sitem->sortval)
		{
			if(sitem->prev!=GZ_DATASORT_EMPTY_INDEX)
			{
				currentItemIndex=sitem->prev;
				sitem=item+currentItemIndex;
				continue;
			}
			else
				return;
		}
		else
		{
			if(!sitem->removed)
			{
				if(sitem->data==data)
				{
					sitem->removed=TRUE;
					++currentRemoved;

					if(cleanItems)
						sitem->data=T();
					return;
				}
			}

			AddItem *aditem;
			
			if(sitem->addItem!=GZ_DATASORT_EMPTY_INDEX)	// We have additional data for this sortval
			{
				gzUInt32 itemIndex=sitem->addItem;

				while(itemIndex!=GZ_DATASORT_EMPTY_INDEX)
				{
					aditem=addItemArray.getAddress()+itemIndex;

					if(!aditem->removed)
					{
						if(aditem->data==data)
						{
							aditem->removed=TRUE;
							++currentRemoved;

							if(cleanItems)
								aditem->data=T();

							return;
						}
					}

					itemIndex=aditem->nextAddItem;
				}
			}
			
			return;
		}
	}
}


//***********************************************************************

template <class T,class SORTVAL> class gzDataSortIterator
{
public:

	gzDataSortIterator(gzDataSort<T,SORTVAL> &owner,gzBool goforward=TRUE);

	gzVoid reset(gzBool goforward=TRUE);

	T * operator()();	// Depending on forward/backward traversal

	T *operator++(int);	// postfix forward operator

	T *operator--(int);	// postfix forward operator

	T *	key();			// current position;

	SORTVAL sortval();	// current positions sortval;

	//! Get the first item, reset the iterator to first position. Next iteration returns second iterator step
	T *	first();		

	//! Get the first item, reset the iterator to last position. Next iteration returns second iterator step
	T * last();

	gzVoid remove();

	gzBool operator==(const gzDataSortIterator<T,SORTVAL> &right) const;

	gzBool operator<(const gzDataSortIterator<T,SORTVAL> &right) const ;

	gzBool operator>(const gzDataSortIterator<T,SORTVAL> &right) const;

	gzUInt32 distance(const gzDataSortIterator<T,SORTVAL> &right) const;

	gzVoid	storePosition(gzUInt32 &currentItemIndex,gzUInt32	&currentAddItemIndex);
	gzVoid	restorePosition(gzUInt32 currentItemIndex,gzUInt32 currentAddItemIndex);

private:

	gzDataSort<T,SORTVAL>	& m_owner;

	gzUInt32			currentItemIndex;

	gzUInt32			currentAddItemIndex;

	gzBool			forward;

	gzBool			headpos;
};

//***********************************************************************

template <class T,class SORTVAL> inline gzDataSortIterator<T,SORTVAL>::gzDataSortIterator(gzDataSort<T,SORTVAL> &owner,gzBool goforward):m_owner(owner)
{
	reset(goforward);
}

template <class T,class SORTVAL> inline gzVoid gzDataSortIterator<T,SORTVAL>::storePosition(gzUInt32 &_currentItemIndex,gzUInt32 &_currentAddItemIndex)
{
	_currentItemIndex=currentItemIndex;
	_currentAddItemIndex=currentAddItemIndex;
}

template <class T,class SORTVAL> inline gzVoid gzDataSortIterator<T,SORTVAL>::restorePosition(gzUInt32 _currentItemIndex,gzUInt32 _currentAddItemIndex)
{
	currentItemIndex=_currentItemIndex;
	currentAddItemIndex=_currentAddItemIndex;
}


//***********************************************************************

template <class T,class SORTVAL> inline gzVoid gzDataSortIterator<T,SORTVAL>::reset(gzBool goforward)
{
	currentItemIndex	=GZ_DATASORT_EMPTY_INDEX;
	currentAddItemIndex	=GZ_DATASORT_EMPTY_INDEX;
	forward=goforward;
	headpos=TRUE;
}

template <class T,class SORTVAL> inline  T *	gzDataSortIterator<T,SORTVAL>::first()
{
	reset(forward);

	return operator++(0);
}

template <class T,class SORTVAL> inline  T * gzDataSortIterator<T,SORTVAL>::last()
{
	reset(forward);

	return operator--(0);
}

template <class T,class SORTVAL> inline gzVoid gzDataSortIterator<T,SORTVAL>::remove()
{
	if(currentItemIndex==GZ_DATASORT_EMPTY_INDEX)
		return;

	if(headpos)
		(m_owner.itemArray.getAddress()+currentItemIndex)->removed=TRUE;
	else
		(m_owner.addItemArray.getAddress()+currentAddItemIndex)->removed=TRUE;

	++m_owner.currentRemoved;
}

//***********************************************************************

template <class T,class SORTVAL> inline  T *	gzDataSortIterator<T,SORTVAL>::key()
{
	if(currentItemIndex==GZ_DATASORT_EMPTY_INDEX)
		return NULL;

	if(headpos)
		return &(m_owner.itemArray.getAddress()+currentItemIndex)->data;
	else 
		return &(m_owner.addItemArray.getAddress()+currentAddItemIndex)->data;
}

template <class T,class SORTVAL> inline SORTVAL gzDataSortIterator<T,SORTVAL>::sortval()
{
	if(currentItemIndex==GZ_DATASORT_EMPTY_INDEX)
		return SORTVAL();

	return (m_owner.itemArray.getAddress()+currentItemIndex)->sortval;
}

//***********************************************************************

template <class T,class SORTVAL> inline gzBool gzDataSortIterator<T,SORTVAL>::operator==(const gzDataSortIterator<T,SORTVAL> &right) const
{
	if (&right.m_owner!=&m_owner)
		throwFatalTemplateError("gzDataSortIterator must be compared with same gzDataSort instance");

	if(currentItemIndex!=right.currentItemIndex)
		return FALSE;

	return TRUE;
}

//***********************************************************************

template <class T,class SORTVAL> inline gzBool gzDataSortIterator<T,SORTVAL>::operator<(const gzDataSortIterator<T,SORTVAL> &right) const
{
	if (&right.m_owner!=&m_owner)
		throwFatalTemplateError("gzDataSortIterator must be compared with same gzDataSort instance");

	if((currentItemIndex==GZ_DATASORT_EMPTY_INDEX) || (right.currentItemIndex==GZ_DATASORT_EMPTY_INDEX))
		throwFatalTemplateError("gzDataSortIterator must have valid position to be compared");

	if(currentItemIndex!=right.currentItemIndex)
		return (m_owner.itemArray.getAddress()+currentItemIndex)->sortval<(right.m_owner.itemArray.getAddress()+right.currentItemIndex)->sortval;
	else
		return FALSE;
}

//***********************************************************************

template <class T,class SORTVAL> inline gzBool gzDataSortIterator<T,SORTVAL>::operator>(const gzDataSortIterator<T,SORTVAL> &right) const
{
	return !(operator==(right) || operator<(right));
}

//***********************************************************************

template <class T,class SORTVAL> inline gzUInt32 gzDataSortIterator<T,SORTVAL>::distance(const gzDataSortIterator<T,SORTVAL> &right) const
{

	if(m_owner.currentAddItemIndex)
		throwFatalTemplateError("gzDataSortIterator::distance() must be used with unique sort values in gzDataSort");

	if(operator==(right))
		return 0;

	gzUInt32 dist=0;

	if(operator<(right))
	{
		gzDataSortIterator<T,SORTVAL> finder(*this);

		while(finder<right)
		{
			dist++;
			finder++;
		}
		return dist;
	}
	else
	{
		gzDataSortIterator<T,SORTVAL> finder(*this);

		while(right<finder)
		{
			dist++;
			finder--;
		}
		return dist;
	}
}

//***********************************************************************

template <class T,class SORTVAL> inline T * gzDataSortIterator<T,SORTVAL>::operator++(int)	// postfix forward operator
{
	
	if(headpos)
		headpos=FALSE;
	else
		currentAddItemIndex=(m_owner.addItemArray.getAddress()+currentAddItemIndex)->nextAddItem;

	// Step additem

	if(currentAddItemIndex==GZ_DATASORT_EMPTY_INDEX) // end of parent list or non init
	{
		if(!m_owner.itemArray.getSize())		// empty
		{
			headpos=TRUE;
			return NULL;
		}

		typename gzDataSort<T,SORTVAL>::Item *item=m_owner.itemArray.getAddress();

		typename gzDataSort<T,SORTVAL>::Item *sitem;

		if(currentItemIndex==GZ_DATASORT_EMPTY_INDEX)
		{
			currentItemIndex=0;

			while(TRUE)
			{
				sitem=item+currentItemIndex;

				if(sitem->prev!=GZ_DATASORT_EMPTY_INDEX)
				{
					currentItemIndex=sitem->prev;
					continue;
				}
				break;
			}
		}
		else
		{
			sitem=item+currentItemIndex;

			if(sitem->next==GZ_DATASORT_EMPTY_INDEX)	// goto next parent
			{
				gzUInt32 prev=currentItemIndex;

				currentItemIndex=sitem->top;

				while(currentItemIndex!=GZ_DATASORT_EMPTY_INDEX)
				{
					sitem=item+currentItemIndex;

					if(sitem->next==prev)
					{
						prev=currentItemIndex;
						currentItemIndex=sitem->top;
					}
					else
						break;
				}
			}
			else
			{
				currentItemIndex=sitem->next;

				while(TRUE)
				{
					sitem=item+currentItemIndex;

					if(sitem->prev!=GZ_DATASORT_EMPTY_INDEX)
					{
						currentItemIndex=sitem->prev;
						continue;
					}
					break;
				}
			}
		}

		headpos=TRUE;	// Beginning of list

		// set add item
		if(currentItemIndex==GZ_DATASORT_EMPTY_INDEX)
			return NULL;
		else
			currentAddItemIndex=sitem->addItem;

		if(sitem->removed)
			return operator++(0);

		return &sitem->data;
	}


	typename gzDataSort<T,SORTVAL>::AddItem *additem=m_owner.addItemArray.getAddress()+currentAddItemIndex;

	if(additem->removed)
		return operator++(0);

	return &additem->data;
}

//***********************************************************************

template <class T,class SORTVAL> inline T * gzDataSortIterator<T,SORTVAL>::operator--(int)	// postfix forward operator
{
	if(headpos)
		headpos=FALSE;
	else
		currentAddItemIndex=(m_owner.addItemArray.getAddress()+currentAddItemIndex)->nextAddItem;

	// Step additem

	if(currentAddItemIndex==GZ_DATASORT_EMPTY_INDEX) // end of parent list or non init
	{
		if(!m_owner.itemArray.getSize())		// empty
		{
			headpos=TRUE;
			return NULL;
		}

		typename gzDataSort<T,SORTVAL>::Item *item=m_owner.itemArray.getAddress();

		typename gzDataSort<T,SORTVAL>::Item *sitem;

		if(currentItemIndex==GZ_DATASORT_EMPTY_INDEX)
		{
			currentItemIndex=0;

			while(TRUE)
			{
				sitem=item+currentItemIndex;

				if(sitem->next!=GZ_DATASORT_EMPTY_INDEX)
				{
					currentItemIndex=sitem->next;
					continue;
				}
				break;
			}
		}
		else
		{
			sitem=item+currentItemIndex;

			if(sitem->prev==GZ_DATASORT_EMPTY_INDEX)	// goto prev parent
			{
				gzUInt32 next=currentItemIndex;

				currentItemIndex=sitem->top;

				while(currentItemIndex!=GZ_DATASORT_EMPTY_INDEX)
				{
					sitem=item+currentItemIndex;

					if(sitem->prev==next)
					{
						next=currentItemIndex;
						currentItemIndex=sitem->top;
					}
					else
						break;
				}
			}
			else
			{
				currentItemIndex=sitem->prev;

				while(TRUE)
				{
					sitem=item+currentItemIndex;

					if(sitem->next!=GZ_DATASORT_EMPTY_INDEX)
					{
						currentItemIndex=sitem->next;
						continue;
					}
					break;
				}
			}
		}

		headpos=TRUE;	// Beginning of list

		// set add item
		if(currentItemIndex==GZ_DATASORT_EMPTY_INDEX)
			return NULL;
		else
			currentAddItemIndex=sitem->addItem;

		if(sitem->removed)
			return operator--(0);

		return &sitem->data;
	}

	typename gzDataSort<T,SORTVAL>::AddItem *additem=m_owner.addItemArray.getAddress()+currentAddItemIndex;

	if(additem->removed)
			return operator--(0);

	return &additem->data;
}

//***********************************************************************

template <class T,class SORTVAL> inline T * gzDataSortIterator<T,SORTVAL>::operator()()
{
	
	if(headpos)
		headpos=FALSE;
	else
		currentAddItemIndex=(m_owner.addItemArray.getAddress()+currentAddItemIndex)->nextAddItem;

	// Step additem

	if(currentAddItemIndex==GZ_DATASORT_EMPTY_INDEX) // end of parent list or non init
	{
		if(!m_owner.itemArray.getSize())		// empty
		{
			headpos=TRUE;
			return NULL;
		}

		typename gzDataSort<T,SORTVAL>::Item *item=m_owner.itemArray.getAddress();

		typename gzDataSort<T,SORTVAL>::Item *sitem;

		if(forward)
		{
			if(currentItemIndex==GZ_DATASORT_EMPTY_INDEX)
			{
				currentItemIndex=0;

				while(TRUE)
				{
					sitem=item+currentItemIndex;

					if(sitem->prev!=GZ_DATASORT_EMPTY_INDEX)
					{
						currentItemIndex=sitem->prev;
						continue;
					}
					break;
				}
			}
			else
			{
				sitem=item+currentItemIndex;

				if(sitem->next==GZ_DATASORT_EMPTY_INDEX)	// goto next parent
				{
					gzUInt32 prev=currentItemIndex;

					currentItemIndex=sitem->top;

					while(currentItemIndex!=GZ_DATASORT_EMPTY_INDEX)
					{
						sitem=item+currentItemIndex;

						if(sitem->next==prev)
						{
							prev=currentItemIndex;
							currentItemIndex=sitem->top;
						}
						else
							break;
					}
				}
				else
				{
					currentItemIndex=sitem->next;

					while(TRUE)
					{
						sitem=item+currentItemIndex;

						if(sitem->prev!=GZ_DATASORT_EMPTY_INDEX)
						{
							currentItemIndex=sitem->prev;
							continue;
						}
						break;
					}
				}
			}
		}
		else
		{
			if(currentItemIndex==GZ_DATASORT_EMPTY_INDEX)
			{
				currentItemIndex=0;

				while(TRUE)
				{
					sitem=item+currentItemIndex;

					if(sitem->next!=GZ_DATASORT_EMPTY_INDEX)
					{
						currentItemIndex=sitem->next;
						continue;
					}
					break;
				}
			}
			else
			{
				sitem=item+currentItemIndex;

				if(sitem->prev==GZ_DATASORT_EMPTY_INDEX)	// goto prev parent
				{
					gzUInt32 next=currentItemIndex;

					currentItemIndex=sitem->top;

					while(currentItemIndex!=GZ_DATASORT_EMPTY_INDEX)
					{
						sitem=item+currentItemIndex;

						if(sitem->prev==next)
						{
							next=currentItemIndex;
							currentItemIndex=sitem->top;
						}
						else
							break;
					}
				}
				else
				{
					currentItemIndex=sitem->prev;

					while(TRUE)
					{
						sitem=item+currentItemIndex;

						if(sitem->next!=GZ_DATASORT_EMPTY_INDEX)
						{
							currentItemIndex=sitem->next;
							continue;
						}
						break;
					}
				}
			}
		}

		headpos=TRUE;	// Beginning of list

		// set add item
		if(currentItemIndex==GZ_DATASORT_EMPTY_INDEX)
			return NULL;
		else
			currentAddItemIndex=sitem->addItem;

		if(sitem->removed)
			return operator()();

		return &sitem->data;
	}

	typename gzDataSort<T,SORTVAL>::AddItem *additem=m_owner.addItemArray.getAddress()+currentAddItemIndex;

	if(additem->removed)
			return operator()();

	return &additem->data;
}

template <class T,class SORTVAL> inline gzVoid gzDataSort<T,SORTVAL>::reorder(gzBool cleanupCache)
{
	if(!reorder_cache)
	{
		reorder_cache=new gzDataSort<T,SORTVAL>;
		reorder_cache->setChunkSize(itemArray.getChunkSize());
	}

	reorder_cache->setRealSize(getSize());

	reorder_cache->operator =(*this);

	operator =(*reorder_cache);

	reorder_cache->clear(TRUE);

	if(cleanupCache)	// If we dont want to keep the cleanup cache
	{
		delete reorder_cache;

		reorder_cache=nullptr;
	}
}

//***********************************************************************

template <class T,class SORTVAL> inline gzVoid gzDataSort<T,SORTVAL>::operator=(const gzDataSort<T,SORTVAL> & copy)
{
	clear(TRUE);

	gzDataSortIterator<T,SORTVAL> iterator((gzDataSort<T,SORTVAL> &)copy);

	T *item;

	while((item=iterator()))
		insert(*item,iterator.sortval(),TRUE);
}

template <class T,class SORTVAL> inline T & gzDataSort<T,SORTVAL>::operator[](gzUInt32 index)
{
	if(index>=getSize())
		throwFatalTemplateError("gzDataSort [] index out of bounds");

	gzDataSortIterator<T,SORTVAL> iterator(*this);

	gzUInt32 size=getSize();

	if(index<=(size>>1))
	{
		for(gzUInt32 i=0;i<=index;++i)
			iterator++;
	}
	else
	{
		index=size-index-1;

		for(gzUInt32 i=0;i<=index;++i)
			iterator--;
	}

	return *iterator.key();
}

template <class T,class SORTVAL> inline gzVoid gzDataSort<T,SORTVAL>::getSortedArray(gzArray<T> &arrayOut)
{
	gzUInt32 size=getSize();

	arrayOut.setSize(size);

	gzDataSortIterator<T,SORTVAL> iterator(*this);

	T* to=arrayOut.getAddress();

	while(size)
	{
		*to=*iterator();
		++to;
		--size;
	}
}

// --------------------- gzTriState ---------------------------

template <class T> class gzTriState
{
public:

	gzTriState():m_valid(FALSE)
	{
	}

	gzTriState(const T& right):m_value(right),m_valid(TRUE)
	{
	}

	const T& operator=(const T& right)
	{
		m_value=right;
		m_valid=TRUE;

		return m_value;
	}

	operator T () const 
	{
		return m_value;
	}

	T  value() const
	{
		return m_value;
	}

	gzBool isValid() const
	{
		return m_valid;
	}

	gzVoid clear()
	{
		m_valid = FALSE;
	}

private:

	T		m_value;
	gzBool	m_valid;
};

// --------------------- gzInitValue ---------------------------

template <class T,const T int_value> class gzInitValue
{
public:

	gzInitValue() :m_value(int_value)
	{
	}

	gzInitValue(const T& right) :m_value(right)
	{
	}

	const T& operator=(const T& right)
	{
		m_value = right;

		return m_value;
	}

	operator const T& () const
	{
		return m_value;
	}

	operator T&() 
	{
		return m_value;
	}

private:

	T		m_value;
};

// -------------- Generic bit counter -------------------------------------

template <class T> inline T gzBitCount(T v)
{
	v = v - ((v >> 1) & (T)~(T)0/3);                           
	v = (v & (T)~(T)0/15*3) + ((v >> 2) & (T)~(T)0/15*3);     
	v = (v + (v >> 4)) & (T)~(T)0/255*15;                     
	return (T)(v * ((T)~(T)0/255)) >> (sizeof(T) - 1) * CHAR_BIT;
}

template <> inline gzInt64 gzBitCount(gzInt64 v)
{
	return gzBitCount<gzUInt64>(v);
}

template <> inline gzInt32 gzBitCount(gzInt32 v)
{
	return gzBitCount<gzUInt32>(v);
}

template <> inline gzInt16 gzBitCount(gzInt16 v)
{
	return gzBitCount<gzUInt16>(v);
}

template <> inline gzInt8 gzBitCount(gzInt8 v)
{
	return gzBitCount<gzUInt8>(v);
}

#endif

