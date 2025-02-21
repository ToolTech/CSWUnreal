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
// File			: gzSpatial.h
// Module		: gzBase
// Description	: Class definition of spatial data storage templates
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
// AMO	050222	Created file 
// AMO	100420	Added a line segment intersector					(2.5.4) 
// AMO	100614	Updated gzSPatial with faster indexing				(2.5.8)
//
// ******************************************************************************

#ifndef __GZ_SPATIAL_H__
#define __GZ_SPATIAL_H__

/*!	\file 
	\brief Templates for spatial data management. Pat Pending..

*/

#include "gzBasicTypes.h"
#include "gzXYZ.h"

// Forward decl
template <class T> class gzSpatialDataIterator;
template <class T> class gzSpatialDataIntersectIterator;

//******************************************************************************
// Class	: gzSpatialData
//									
// Purpose  : Template for spatial located data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050222	Created 
//									
//******************************************************************************
template <class T> class gzSpatialData
{
public:

	gzSpatialData(const gzDoubleXYZ& position_1=gzDoubleXYZ(0,0,0) , const gzDoubleXYZ& position_2=gzDoubleXYZ(1,1,1),gzUInt32 divisions=3,gzUInt32 splitItems=0);

	~gzSpatialData();

	gzVoid		insert(const gzDoubleXYZ &position,const T &data,const gzDoubleXYZ &delta=gzDoubleXYZ(0,0,0));

	gzUInt32		entries() const;

	gzVoid		clear();

private:

	friend class gzSpatialDataIterator<T>;
	friend class gzSpatialDataIntersectIterator<T>;

	class _item;

	class _holder
	{
	public:

		_holder(const gzDoubleXYZ &min , const gzDoubleXYZ &max,_holder *parent):m_subspace(NULL),m_parent(parent),m_next(0),m_max(max),m_min(min),m_firstIndex(0),m_lastIndex(0)
		{
			m_itemList.reuseLinks(TRUE);
		}

		~_holder()
		{
			if(m_subspace)
			{
				for(gzUInt32 i=m_firstIndex;i<=m_lastIndex;i++)
					if(m_subspace[i])
						delete m_subspace[i];

				delete [] m_subspace;
			}

			m_itemList.clearAndDestroy();
		}

		gzVoid createSubspace(gzUInt32 divisions)
		{
			if(!m_subspace)
			{
				m_size=divisions*divisions*divisions;
				m_firstIndex=m_lastIndex=0;

				m_subspace=new _holder *[m_size];
				memset(m_subspace,0,m_size*sizeof(_holder *));
			}
		}

		gzList<_item>		m_itemList;
		_holder **			m_subspace;
		_holder *			m_parent;
		gzUInt32			m_next;
		gzDoubleXYZ			m_max;
		gzDoubleXYZ			m_min;
		gzUInt32			m_size;
		gzUInt32			m_firstIndex;
		gzUInt32			m_lastIndex;
	};

	class _item
	{
	public:

		T					m_data;
		gzDoubleXYZ			m_position;
		gzDoubleXYZ			m_delta;
	};

	_holder *		m_space;

	gzDoubleXYZ			m_minPosition;

	gzDoubleXYZ			m_stepping;

	gzUInt32			m_divisions;

	gzUInt32			m_splitItems;

	gzUInt32			m_entries;
};

template <class T> inline gzSpatialData<T>::gzSpatialData(const gzDoubleXYZ& position_1 , const gzDoubleXYZ& position_2,gzUInt32 divisions,gzUInt32 splitItems)
{
	m_minPosition=gzDoubleXYZ(gzMin(position_1.x,position_2.x),gzMin(position_1.y,position_2.y),gzMin(position_1.z,position_2.z));

	m_stepping=(gzDoubleXYZ(gzMax(position_1.x,position_2.x),gzMax(position_1.y,position_2.y),gzMax(position_1.z,position_2.z))-m_minPosition)/divisions;

	if(!m_stepping.x)
		m_stepping.x=1;

	if(!m_stepping.y)
		m_stepping.y=1;

	if(!m_stepping.z)
		m_stepping.z=1;

	m_divisions=divisions;

	m_splitItems=splitItems;

	m_space=nullptr;

	m_entries=0;
}

template <class T> inline gzSpatialData<T>::~gzSpatialData()
{
	if(m_space)
		delete m_space;
}

template <class T> inline gzVoid gzSpatialData<T>::clear()
{
	if(m_space)
		delete m_space;

	m_space=nullptr;
	m_entries=0;
}

template <class T> inline gzUInt32 gzSpatialData<T>::entries() const
{
	return m_entries;
}

template <class T> inline gzVoid gzSpatialData<T>::insert(const gzDoubleXYZ &position,const T &data,const gzDoubleXYZ &delta)
{
	if(		((position.x+delta.x)>=(m_minPosition.x+m_divisions*m_stepping.x))	// We are located outside max extent. Need to rebuild tree
		||	((position.y+delta.y)>=(m_minPosition.y+m_divisions*m_stepping.y))
		||	((position.z+delta.z)>=(m_minPosition.z+m_divisions*m_stepping.z)) )
	{
		_holder *old=m_space;
		gzUInt32 index=(m_divisions-1)/2;

		gzUInt32 mixIndex=index*(m_divisions*m_divisions)+index*m_divisions+index;
		

		m_stepping=m_stepping*m_divisions;
		m_minPosition=m_minPosition-m_stepping*index;

		m_space=new _holder(m_minPosition,m_minPosition+m_stepping*m_divisions,NULL);
		
		if(old)
		{
			m_space->createSubspace(m_divisions);
			m_space->m_subspace[mixIndex]=old;
			m_space->m_firstIndex=mixIndex;
			m_space->m_lastIndex=mixIndex;
			old->m_parent=m_space;
		}

		insert(position,data,delta);
		return;
	}

	if(		((position.x-delta.x)<m_minPosition.x)
		||	((position.y-delta.y)<m_minPosition.y)
		||	((position.z-delta.z)<m_minPosition.z)	)
	{
		_holder *old=m_space;
		gzUInt32 index=m_divisions/2;
		gzUInt32 mixIndex=index*(m_divisions*m_divisions)+index*m_divisions+index;
		
		m_stepping=m_stepping*m_divisions;
		m_minPosition=m_minPosition-m_stepping*index;

		m_space=new _holder(m_minPosition,m_minPosition+m_stepping*m_divisions,NULL);

		if(old)
		{
			m_space->createSubspace(m_divisions);
			m_space->m_subspace[mixIndex]=old;
			m_space->m_firstIndex=mixIndex;
			m_space->m_lastIndex=mixIndex;
			old->m_parent=m_space;
		}
	
		insert(position,data,delta);
		return;
	}

	gzUInt32 index_x=0,index_y=0,index_z=0;

	_holder *holder=m_space,*parent=nullptr;

	gzDoubleXYZ stepping=m_stepping;
	gzDoubleXYZ minPosition=m_minPosition;

	while(holder)
	{
		index_x=(gzUInt32)((position.x-delta.x-minPosition.x)/stepping.x);
		index_y=(gzUInt32)((position.y-delta.y-minPosition.y)/stepping.y);
		index_z=(gzUInt32)((position.z-delta.z-minPosition.z)/stepping.z);

		if( ((gzUInt32)((position.x+delta.x-minPosition.x)/stepping.x))!=index_x)
			break;

		if( ((gzUInt32)((position.y+delta.y-minPosition.y)/stepping.y))!=index_y)
			break;

		if( ((gzUInt32)((position.z+delta.z-minPosition.z)/stepping.z))!=index_z)
			break;

		if(holder->m_itemList.entries()>=m_splitItems)	// go to subchild
		{
			minPosition.x=minPosition.x+index_x*stepping.x;
			minPosition.y=minPosition.y+index_y*stepping.y;
			minPosition.z=minPosition.z+index_z*stepping.z;

			stepping=stepping/m_divisions;

			gzUInt32 mixIndex=index_x*(m_divisions*m_divisions)+index_y*m_divisions+index_z;

			if(!holder->m_subspace)
			{
				holder->createSubspace(m_divisions);
				holder->m_firstIndex=mixIndex;
				holder->m_lastIndex=mixIndex;
			}


			parent=holder;
			holder=holder->m_subspace[mixIndex];

			continue;
		}
		else
			break;
	}

	if(!holder)
	{
		gzUInt32 mixIndex=index_x*(m_divisions*m_divisions)+index_y*m_divisions+index_z;

		holder=new _holder(minPosition,minPosition+stepping*m_divisions,parent);

		if(!parent)
			m_space=holder;
		else
		{
			if(parent->m_firstIndex>mixIndex)
			{
				holder->m_next=parent->m_firstIndex;
				parent->m_firstIndex=mixIndex;
			}
			else if(parent->m_lastIndex<mixIndex)
			{
				parent->m_subspace[parent->m_lastIndex]->m_next=mixIndex;
				parent->m_lastIndex=mixIndex;
			}
			else if(parent->m_firstIndex!=mixIndex)
			{
				gzUInt32 prev(0);
				gzUInt32 index=parent->m_firstIndex;

				while(index<mixIndex)
				{
					prev=index;
					index=parent->m_subspace[index]->m_next;
				}

				holder->m_next=parent->m_subspace[prev]->m_next;
				parent->m_subspace[prev]->m_next=mixIndex;
			}

			parent->m_subspace[mixIndex]=holder;
		}
	}

	// Insert item

	_item *item=new _item;

	holder->m_itemList.insert(item);

	item->m_data=data;
	item->m_position=position;
	item->m_delta=delta;

	++m_entries;
}


//******************************************************************************
// Class	: gzSpatialDataIterator
//									
// Purpose  : Box iterator for spatial located data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050222	Created 
//									
//******************************************************************************
template <class T> class gzSpatialDataIterator
{
public:

	gzSpatialDataIterator(gzSpatialData<T> &owner,const gzDoubleXYZ& position=gzDoubleXYZ(0,0,0) , const gzDoubleXYZ& delta=gzDoubleXYZ(DBL_MAX,DBL_MAX,DBL_MAX));

	~gzSpatialDataIterator();

	gzBool operator()(T &data,gzDoubleXYZ *pos=nullptr,gzDoubleXYZ *delta=nullptr);

	gzVoid remove();

private:

	gzSpatialData<T> &			m_owner;

	const gzDoubleXYZ			m_position;
	const gzDoubleXYZ			m_delta;
	const gzDouble				dx_p,dy_p,dz_p,dx_m,dy_m,dz_m;
	
	typename gzSpatialData<T>::_holder *				m_currentHolder;
//	gzUInt32												m_maxIndex;
	gzListIterator<typename gzSpatialData<T>::_item>	m_iterator;
	gzBool												m_validIterator;
};

template <class T> inline gzSpatialDataIterator<T>::gzSpatialDataIterator(gzSpatialData<T> &owner,const gzDoubleXYZ& position , const gzDoubleXYZ& delta)
		:m_owner(owner),
		m_position(position),
		m_delta(delta),
		dx_p(position.x+delta.x),
		dy_p(position.y+delta.y),
		dz_p(position.z+delta.z),
		dx_m(position.x-delta.x),
		dy_m(position.y-delta.y),
		dz_m(position.z-delta.z),
		m_iterator(NULL),
		m_validIterator(FALSE)
{
//	m_maxIndex=m_owner.m_divisions*m_owner.m_divisions*m_owner.m_divisions;
	m_currentHolder=m_owner.m_space;
}

template <class T> inline gzSpatialDataIterator<T>::~gzSpatialDataIterator()
{
}

template <class T> inline gzVoid gzSpatialDataIterator<T>::remove()
{
	if(m_validIterator)
	{
		delete m_iterator.remove();
		--m_owner.m_entries;
	}
}

template <class T> inline gzBool gzSpatialDataIterator<T>::operator()(T &data,gzDoubleXYZ *pos,gzDoubleXYZ *delta)
{
	if(!m_currentHolder)		// Assume a valid holder
		return FALSE;

	gzBool isValid;

	typename gzSpatialData<T>::_item *item;

	while(TRUE)
	{
		// Check to see if holder is valid first time

		if(!m_validIterator)
		{
			isValid=TRUE;

			if( m_currentHolder->m_max.x < dx_m ) // left of us
				isValid=FALSE;
			else if( m_currentHolder->m_min.x > dx_p ) // right of us
				isValid=FALSE;
			else if( m_currentHolder->m_max.y < dy_m) // under us
				isValid=FALSE;
			else if( m_currentHolder->m_min.y > dy_p) // top of us
				isValid=FALSE;
			else if( m_currentHolder->m_max.z < dz_m) 
				isValid=FALSE;
			else if( m_currentHolder->m_min.z > dz_p) 
				isValid=FALSE;

			if(!isValid)
			{
				// Go to next neighbour

				while(TRUE)
				{
					if(!m_currentHolder->m_parent)	// check if we hit top
					{
						return FALSE;
					}

					if(m_currentHolder->m_next)
					{
						m_currentHolder=m_currentHolder->m_parent->m_subspace[m_currentHolder->m_next];

						if( m_currentHolder->m_max.x < dx_m ) // left of us
							continue;
						if( m_currentHolder->m_min.x > dx_p ) // right of us
							continue;
						if( m_currentHolder->m_max.y < dy_m) // under us
							continue;
						if( m_currentHolder->m_min.y > dy_p) // top of us
							continue;
						if( m_currentHolder->m_max.z < dz_m) 
							continue;
						if( m_currentHolder->m_min.z > dz_p) 
							continue;

						break;
					}

					// We have no neighbour; check parent neighbour
					m_currentHolder=m_currentHolder->m_parent;
				}

				// we have a new holder

				continue;
			}

			// Set up valid iterator for holder

			m_validIterator=TRUE;
			m_iterator.setList(m_currentHolder->m_itemList);
		}

		// Iterate over list for a valid holder

		item=m_iterator();

		if(!item)		// End of list
		{
			// Clean up
			m_validIterator=FALSE;

			// go to first sibling

			if(m_currentHolder->m_subspace)
			{
				// Select first child
				m_currentHolder=m_currentHolder->m_subspace[m_currentHolder->m_firstIndex];
			}
			else
			{
				// go to next neighour

				while(TRUE)
				{
					if(!m_currentHolder->m_parent)	// check if we hit top
					{
						return FALSE;
					}

					if(m_currentHolder->m_next)
					{
						m_currentHolder=m_currentHolder->m_parent->m_subspace[m_currentHolder->m_next];

						if( m_currentHolder->m_max.x < dx_m ) // left of us
							continue;
						if( m_currentHolder->m_min.x > dx_p ) // right of us
							continue;
						if( m_currentHolder->m_max.y < dy_m) // under us
							continue;
						if( m_currentHolder->m_min.y > dy_p) // top of us
							continue;
						if( m_currentHolder->m_max.z < dz_m) 
							continue;
						if( m_currentHolder->m_min.z > dz_p) 
							continue;

						break;
					}

					// We have no neighbour; check parent neighbour
					m_currentHolder=m_currentHolder->m_parent;
				}

				// we have a new holder

				continue;
			}
		}
		else	// Check to se if valid
		{
			if( (item->m_position.x+item->m_delta.x) < dx_m ) // left of us
				continue;

			if( (item->m_position.x-item->m_delta.x) > dx_p ) // right of us
				continue;

			if( (item->m_position.y+item->m_delta.y) < dy_m ) // bottom of us
				continue;

			if( (item->m_position.y-item->m_delta.y) > dy_p ) // top of us
				continue;

			if( (item->m_position.z+item->m_delta.z) < dz_m ) // left of us
				continue;

			if( (item->m_position.z-item->m_delta.z) > dz_p ) // right of us
				continue;

			// We have an intersection

			if(pos)
				*pos=item->m_position;

			if(delta)
				*delta=item->m_delta;

			data=item->m_data;

			return TRUE;
		}
	} 
}

//******************************************************************************
// Class	: gzSpatialDataIntersectIterator
//									
// Purpose  : Line Intersector iterator for spatial located data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	100420	Created 
//									
//******************************************************************************
template <class T> class gzSpatialDataIntersectIterator
{
public:

	gzSpatialDataIntersectIterator(gzSpatialData<T> &owner,const gzDoubleXYZ& position , const gzDoubleXYZ& direction);

	~gzSpatialDataIntersectIterator();

	gzBool operator()(T &data,gzDoubleXYZ *pos=nullptr,gzDoubleXYZ *delta=nullptr);

	gzVoid remove();

private:

	gzSpatialData<T> &			m_owner;

	const gzDoubleXYZ			m_position;
	const gzDoubleXYZ			m_direction;

	gzDouble					m_dirInvMag;
	
	typename gzSpatialData<T>::_holder *				m_currentHolder;
	gzUInt32											m_maxIndex;
	gzListIterator<typename gzSpatialData<T>::_item>	m_iterator;
	gzBool												m_validIterator;
};

template <class T> inline gzSpatialDataIntersectIterator<T>::gzSpatialDataIntersectIterator(gzSpatialData<T> &owner,const gzDoubleXYZ& position , const gzDoubleXYZ& direction)
		:m_owner(owner),
		m_position(position),
		m_direction(direction),
		m_iterator(NULL)
{
	m_maxIndex=m_owner.m_divisions*m_owner.m_divisions*m_owner.m_divisions;
	m_currentHolder=m_owner.m_space;
	m_validIterator=FALSE;
	m_dirInvMag=1.0/(direction.x*direction.x+direction.y*direction.y+direction.z*direction.z);
}

template <class T> inline gzSpatialDataIntersectIterator<T>::~gzSpatialDataIntersectIterator()
{
}

template <class T> inline gzVoid gzSpatialDataIntersectIterator<T>::remove()
{
	if(m_validIterator)
	{
		delete m_iterator.remove();
		--m_owner.m_entries;
	}
}

template <class T> inline gzBool gzSpatialDataIntersectIterator<T>::operator()(T &data,gzDoubleXYZ *pos,gzDoubleXYZ *delta)
{
	if(!m_currentHolder)		// Assume a valid holder
		return FALSE;

	gzBool isValid;

	typename gzSpatialData<T>::_item *item;

	gzDouble k,x,y,z,dx,dy,dz;

	while(TRUE)
	{
		// Check to see if holder is valid first time

		if(!m_validIterator)
		{
			isValid=FALSE;	// Assume miss

			// Check global radius

			x=0.5*(m_currentHolder->m_max.x+m_currentHolder->m_min.x);
			y=0.5*(m_currentHolder->m_max.y+m_currentHolder->m_min.y);
			z=0.5*(m_currentHolder->m_max.z+m_currentHolder->m_min.z);

			k=((x-m_position.x)*m_direction.x+(y-m_position.y)*m_direction.y+(z-m_position.z)*m_direction.z)*m_dirInvMag;

			dx=(m_position.x+k*m_direction.x-x);
			dy=(m_position.y+k*m_direction.y-y);
			dz=(m_position.z+k*m_direction.z-z);

			x=0.5*(m_currentHolder->m_max.x-m_currentHolder->m_min.x);
			y=0.5*(m_currentHolder->m_max.y-m_currentHolder->m_min.y);
			z=0.5*(m_currentHolder->m_max.z-m_currentHolder->m_min.z);

			if( (dx*dx+dy*dy+dz*dz) <= (x*x+y*y+z*z) )
			{
				if(m_direction.x!=0)
				{
					k=(m_currentHolder->m_max.x-m_position.x)/m_direction.x;
					y=m_position.y+k*m_direction.y;
					z=m_position.z+k*m_direction.z;

					if( (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
						isValid=TRUE;
					else
					{
						k=(m_currentHolder->m_min.x-m_position.x)/m_direction.x;
						y=m_position.y+k*m_direction.y;
						z=m_position.z+k*m_direction.z;

						if( (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
							isValid=TRUE;
					}
				}

				if(!isValid && (m_direction.y!=0))
				{
					k=(m_currentHolder->m_max.y-m_position.y)/m_direction.y;
					x=m_position.x+k*m_direction.x;
					z=m_position.z+k*m_direction.z;

					if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
						isValid=TRUE;
					else
					{
						k=(m_currentHolder->m_min.y-m_position.y)/m_direction.y;
						x=m_position.x+k*m_direction.x;
						z=m_position.z+k*m_direction.z;

						if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
							isValid=TRUE;
					}
				}

				if(!isValid && (m_direction.z!=0))
				{
					k=(m_currentHolder->m_max.z-m_position.z)/m_direction.z;
					x=m_position.x+k*m_direction.x;
					y=m_position.y+k*m_direction.y;

					if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y))
						isValid=TRUE;
					else
					{
						k=(m_currentHolder->m_min.z-m_position.z)/m_direction.z;
						x=m_position.x+k*m_direction.x;
						y=m_position.y+k*m_direction.y;

						if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y))
							isValid=TRUE;
					}
				}
			}

			if(!isValid)
			{
				// Go to next neighbour

				while(TRUE)
				{
					if(!m_currentHolder->m_parent)	// check if we hit top
					{
						return FALSE;
					}

					if(m_currentHolder->m_next)
					{
						m_currentHolder=m_currentHolder->m_parent->m_subspace[m_currentHolder->m_next];

						// Check global radius

						x=0.5*(m_currentHolder->m_max.x+m_currentHolder->m_min.x);
						y=0.5*(m_currentHolder->m_max.y+m_currentHolder->m_min.y);
						z=0.5*(m_currentHolder->m_max.z+m_currentHolder->m_min.z);

						k=((x-m_position.x)*m_direction.x+(y-m_position.y)*m_direction.y+(z-m_position.z)*m_direction.z)*m_dirInvMag;

						dx=(m_position.x+k*m_direction.x-x);
						dy=(m_position.y+k*m_direction.y-y);
						dz=(m_position.z+k*m_direction.z-z);

						x=0.5*(m_currentHolder->m_max.x-m_currentHolder->m_min.x);
						y=0.5*(m_currentHolder->m_max.y-m_currentHolder->m_min.y);
						z=0.5*(m_currentHolder->m_max.z-m_currentHolder->m_min.z);

						if( (dx*dx+dy*dy+dz*dz) > (x*x+y*y+z*z) )
							continue;

						if(m_direction.x!=0)
						{
							k=(m_currentHolder->m_max.x-m_position.x)/m_direction.x;
							y=m_position.y+k*m_direction.y;
							z=m_position.z+k*m_direction.z;

							if( (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
								break;
							else
							{
								k=(m_currentHolder->m_min.x-m_position.x)/m_direction.x;
								y=m_position.y+k*m_direction.y;
								z=m_position.z+k*m_direction.z;

								if( (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
									break;
							}
						}

						if(m_direction.y!=0)
						{
							k=(m_currentHolder->m_max.y-m_position.y)/m_direction.y;
							x=m_position.x+k*m_direction.x;
							z=m_position.z+k*m_direction.z;

							if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
								break;
							else
							{
								k=(m_currentHolder->m_min.y-m_position.y)/m_direction.y;
								x=m_position.x+k*m_direction.x;
								z=m_position.z+k*m_direction.z;

								if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
									break;
							}
						}

						if(m_direction.z!=0)
						{
							k=(m_currentHolder->m_max.z-m_position.z)/m_direction.z;
							x=m_position.x+k*m_direction.x;
							y=m_position.y+k*m_direction.y;

							if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y))
								break;
							else
							{
								k=(m_currentHolder->m_min.z-m_position.z)/m_direction.z;
								x=m_position.x+k*m_direction.x;
								y=m_position.y+k*m_direction.y;

								if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y))
									break;
							}
						}

						continue;
					}

					// We have no neighbour; check parent neighbour
					m_currentHolder=m_currentHolder->m_parent;
				}

				// we have a new holder

				continue;
			}

			// Set up valid iterator for holder

			m_validIterator=TRUE;
			m_iterator.setList(m_currentHolder->m_itemList);
		}

		// Iterate over list for a valid holder

		item=m_iterator();

		if(!item)		// End of list
		{
			// Clean up
			m_validIterator=FALSE;

			// go to first sibling

			if(m_currentHolder->m_subspace)
			{
				// Select first child
				m_currentHolder=m_currentHolder->m_subspace[m_currentHolder->m_firstIndex];
			}
			else
			{
				// go to next neighour

				while(TRUE)
				{
					if(!m_currentHolder->m_parent)	// check if we hit top
					{
						return FALSE;
					}

					if(m_currentHolder->m_next)
					{
						m_currentHolder=m_currentHolder->m_parent->m_subspace[m_currentHolder->m_next];

						// Check global radius

						x=0.5*(m_currentHolder->m_max.x+m_currentHolder->m_min.x);
						y=0.5*(m_currentHolder->m_max.y+m_currentHolder->m_min.y);
						z=0.5*(m_currentHolder->m_max.z+m_currentHolder->m_min.z);

						k=((x-m_position.x)*m_direction.x+(y-m_position.y)*m_direction.y+(z-m_position.z)*m_direction.z)*m_dirInvMag;

						dx=(m_position.x+k*m_direction.x-x);
						dy=(m_position.y+k*m_direction.y-y);
						dz=(m_position.z+k*m_direction.z-z);

						x=0.5*(m_currentHolder->m_max.x-m_currentHolder->m_min.x);
						y=0.5*(m_currentHolder->m_max.y-m_currentHolder->m_min.y);
						z=0.5*(m_currentHolder->m_max.z-m_currentHolder->m_min.z);

						if( (dx*dx+dy*dy+dz*dz) > (x*x+y*y+z*z) )
							continue;

						if(m_direction.x!=0)
						{
							k=(m_currentHolder->m_max.x-m_position.x)/m_direction.x;
							y=m_position.y+k*m_direction.y;
							z=m_position.z+k*m_direction.z;

							if( (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
								break;
							else
							{
								k=(m_currentHolder->m_min.x-m_position.x)/m_direction.x;
								y=m_position.y+k*m_direction.y;
								z=m_position.z+k*m_direction.z;

								if( (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
									break;
							}
						}

						if(m_direction.y!=0)
						{
							k=(m_currentHolder->m_max.y-m_position.y)/m_direction.y;
							x=m_position.x+k*m_direction.x;
							z=m_position.z+k*m_direction.z;

							if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
								break;
							else
							{
								k=(m_currentHolder->m_min.y-m_position.y)/m_direction.y;
								x=m_position.x+k*m_direction.x;
								z=m_position.z+k*m_direction.z;

								if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (z>=m_currentHolder->m_min.z) && (z<=m_currentHolder->m_max.z))
									break;
							}
						}

						if(m_direction.z!=0)
						{
							k=(m_currentHolder->m_max.z-m_position.z)/m_direction.z;
							x=m_position.x+k*m_direction.x;
							y=m_position.y+k*m_direction.y;

							if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y))
								break;
							else
							{
								k=(m_currentHolder->m_min.z-m_position.z)/m_direction.z;
								x=m_position.x+k*m_direction.x;
								y=m_position.y+k*m_direction.y;

								if( (x>=m_currentHolder->m_min.x) && (x<=m_currentHolder->m_max.x) && (y>=m_currentHolder->m_min.y) && (y<=m_currentHolder->m_max.y))
									break;
							}
						}

						continue;
					}

					// We have no neighbour; check parent neighbour
					m_currentHolder=m_currentHolder->m_parent;
				}

				// we have a new holder

				continue;
			}
		}
		else	// Check to se if valid
		{

			isValid=FALSE;

			// Check global radius
			
			k=((item->m_position.x-m_position.x)*m_direction.x+(item->m_position.y-m_position.y)*m_direction.y+(item->m_position.z-m_position.z)*m_direction.z)*m_dirInvMag;

			dx=(m_position.x+k*m_direction.x-item->m_position.x);
			dy=(m_position.y+k*m_direction.y-item->m_position.y);
			dz=(m_position.z+k*m_direction.z-item->m_position.z);

			if( (dx*dx+dy*dy+dz*dz) <= (item->m_delta.x*item->m_delta.x+item->m_delta.y*item->m_delta.y+item->m_delta.z*item->m_delta.z) )	
			{
				if(m_direction.x!=0)
				{
					k=(item->m_position.x+item->m_delta.x-m_position.x)/m_direction.x;
					y=m_position.y+k*m_direction.y;
					z=m_position.z+k*m_direction.z;

					if( (y>=(item->m_position .y-item->m_delta.y)) && (y<=(item->m_position.y+item->m_delta.y)) && (z>=(item->m_position.z-item->m_delta.z)) && (z<=(item->m_position.z+item->m_delta.z)))
						isValid=TRUE; 
					else
					{
						k=(item->m_position.x-item->m_delta.x-m_position.x)/m_direction.x;
						y=m_position.y+k*m_direction.y;
						z=m_position.z+k*m_direction.z;

						if( (y>=(item->m_position.y-item->m_delta.y)) && (y<=(item->m_position.y+item->m_delta.y)) && (z>=(item->m_position.z-item->m_delta.z)) && (z<=(item->m_position.z+item->m_delta.z)))
							isValid=TRUE;
					}
				}

				if(!isValid && (m_direction.y!=0))
				{
					k=(item->m_position.y+item->m_delta.y-m_position.y)/m_direction.y;
					x=m_position.x+k*m_direction.x;
					z=m_position.z+k*m_direction.z;

					if( (x>=(item->m_position.x-item->m_delta.x)) && (x<=(item->m_position.x+item->m_delta.x)) && (z>=(item->m_position.z-item->m_delta.z)) && (z<=(item->m_position.z+item->m_delta.z)))
						isValid=TRUE;
					else
					{
						k=(item->m_position.y-item->m_delta.y-m_position.y)/m_direction.y;
						x=m_position.x+k*m_direction.x;
						z=m_position.z+k*m_direction.z;

						if( (x>=(item->m_position.x-item->m_delta.x)) && (x<=(item->m_position.x+item->m_delta.x)) && (z>=(item->m_position.z-item->m_delta.z)) && (z<=(item->m_position.z+item->m_delta.z)))
							isValid=TRUE;
					}
				}

				if(!isValid && (m_direction.z!=0))
				{
					k=(item->m_position.z+item->m_delta.z-m_position.z)/m_direction.z;
					x=m_position.x+k*m_direction.x;
					y=m_position.y+k*m_direction.y;

					if( (x>=(item->m_position.x-item->m_delta.x)) && (x<=(item->m_position.x+item->m_delta.x)) && (y>=(item->m_position.y-item->m_delta.y)) && (y<=(item->m_position.y+item->m_delta.y)))
						isValid=TRUE;
					else
					{
						k=(item->m_position.z-item->m_delta.z-m_position.z)/m_direction.z;
						x=m_position.x+k*m_direction.x;
						y=m_position.y+k*m_direction.y;

						if( (x>=(item->m_position.x-item->m_delta.x)) && (x<=(item->m_position.x+item->m_delta.x)) && (y>=(item->m_position.y-item->m_delta.y)) && (y<=(item->m_position.y+item->m_delta.y)))
							isValid=TRUE;
					}
				}
			}

			if(!isValid)
				continue;

			// We have an intersection

			if(pos)
				*pos=item->m_position;

			if(delta)
				*delta=item->m_delta;

			data=item->m_data;

			return TRUE;
		}
	} 
}

#endif // __GZ_SPATIAL_H__
