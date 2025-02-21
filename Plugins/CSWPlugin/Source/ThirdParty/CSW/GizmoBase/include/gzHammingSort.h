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
// File			: gzHammingSort.h
// Module		: gzBase
// Description	: Class definition of hamming sort
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
// AMO	120221	Created file 										(2.6.24)
//******************************************************************************

#ifndef __GZ_HAMMING_H__
#define __GZ_HAMMING_H__


/*!	\file 
	\brief Hamming sort utility

	The templates provides an extremly fast find utility for least pair finding using Hamming distances
	The algorithm is based on Anders Modén theory of hyper plane walking buckets
*/

#include "gzTemplates.h"

//----------------------------------------------------------------
// Callback interface for sorted items

template <int T=4> class gzHammingSortItem : public gzReference
{
public:

	gzHammingSortItem()
	{
		
	}

	virtual ~gzHammingSortItem() 
	{
	}

	//! Provide this method and fill in bit index localised in each bin
	virtual gzVoid getIndex(gzInt32 (&index) [T])=0; 

	// Provide this method as a measue of distance between two items in hamming distance space
	virtual gzInt32 distance(gzHammingSortItem<T> *right)=0;

	// Return two if two or more instances represent same data
	virtual gzBool isSame(gzHammingSortItem<T> * /*right*/)
	{
		return FALSE;
	}

	//! Always use shared referencing
	virtual gzBool useDeepCopy()
	{
		return FALSE;
	}
};

//---------------------------------------------------------------

template <int T=4,class ITEM=gzHammingSortItem<T> > class gzHammingSort
{
public:

	gzHammingSort():m_iterator(NULL)
	{
		memset(m_min,0,sizeof(m_min));
		memset(m_max,0,sizeof(m_max));
		m_index=nullptr;
	}

	~gzHammingSort()
	{
		if(m_index)
			delete [] m_index;
	}

	gzVoid setSize(gzInt32 (&max) [T],gzInt32 (&min) [T]) 
	{
		if(m_index)
			delete [] m_index;

		gzInt32 indexSize(1);

		for(gzInt32 i=0;i<T;i++)
		{
			gzInt32 size=(max[i]-min[i]+1);

			gzInt32 shifts(0),powsize(1);

			gzBool rest(FALSE);

			while(size)
			{
				if((size!=1)&&(size&1))
					rest=TRUE;

				powsize<<=1;
				size>>=1;
				++shifts;
			}
	
			if(!rest)
			{
				powsize>>=1;
				--shifts;
			}
			
			indexSize=indexSize*powsize;
			m_shifts[i]=shifts;
		}

		m_index=new gzRefList<ITEM>[indexSize];
	}

	inline gzRefList<ITEM> & getIndex(gzInt32 (&index) [T])
	{
		gzInt32 pos(0);

		gzInt32 i(T),*p_index(index),*p_shifts(m_shifts),*p_min(m_min),*p_max(m_max);
		
		while(i)
		{
			--i;

			if( (*p_index>*p_max) || (*p_index<*p_min) )
				throwFatalTemplateError("Hamming index out of range");

			pos=pos<<*p_shifts;
			pos+=(*p_index-*p_min);
			++p_index;
			++p_min;
			++p_max;
			++p_shifts;
		}

		return m_index[pos];
	}
	
	gzVoid addItem(ITEM *item,gzInt32 (&index) [T])
	{
		getIndex(index).insert(item);
	}

	gzVoid addItems(gzRefList<ITEM> &list)
	{
		gzListIterator<ITEM> iterator(list);
		ITEM *item;

		gzInt32 index[T];

		gzBool first(TRUE);

		while((item=iterator()))
		{
			item->getIndex(index);

			if(first)
			{
				for(gzInt32 i=0;i<T;i++)
				{
					m_max[i]=m_min[i]=index[i];
				}
			}
			else
			{
				for(gzInt32 i=0;i<T;i++)
				{
					m_min[i]=gzMin(m_min[i],index[i]);
					m_max[i]=gzMax(m_max[i],index[i]);
				}
			}

			first=FALSE;
		}

		setSize(m_max,m_min);

		iterator.reset();

		while((item = iterator()))
		{
			item->getIndex(index);

			addItem(item,index);
		}
	}

	ITEM * findMatch(ITEM *finditem,gzInt32 dmax=INT_MAX,gzFloat ratio_f=GZ_FLOAT_ONE,gzFloat *ratio_out=nullptr)
	{
		if(!finditem)
			return NULL;


		// Init vars
		m_d1=dmax;
		m_d2=INT_MAX;

		m_bestMatch=nullptr;
		m_findItem=finditem;
		m_fail=FALSE;
		m_exit=FALSE;

		// 3 decimals (1024 factor)

		m_ratio=(gzInt32)((1<<10)*ratio_f);
		m_iratio=(gzInt32)((1<<10)/ratio_f);

		m_d2_max=m_d2_calc=((dmax*m_iratio)>>10);
		m_d1_max=dmax;

		finditem->getIndex(m_center);


		// Adjust min/max

		m_dist_0=0;

		gzInt32	i;

		for(i=0;i<T;i++)
		{
			if(m_center[i]>m_max[i])
			{
				m_dist_0+=(m_center[i]-m_max[i]);
				m_center[i]=m_max[i];
			}
			else if(m_center[i]<m_min[i])
			{
				m_dist_0+=(m_min[i]-m_center[i]);
				m_center[i]=m_min[i];
			}
		}

		gzInt32 dd=0;

		while((dd+m_dist_0)<m_d2_max)	// Maximum search radius. dist will never be less than dd
		{
			// Do a search using traversal of volume

			traverseVolumeBase(&dd,1,dd);

			if(m_fail)
				return NULL;

			if(m_exit)
				break;

			if(((dd+m_dist_0)>m_d1_max) && (m_d1>m_d1_max))
			{
				// No valid solution will be found
				m_exit=TRUE;
				m_fail=TRUE;
				break;
			}

			++dd;
		}

		if(!m_d1)
		{
			if(m_d2 || (m_ratio>=(1<<10)))
			{
				if(ratio_out)
					*ratio_out=0;

				return m_bestMatch;
			}
		}
		else if(m_d1<=((m_d2*m_ratio)>>10))
		{
			if(ratio_out)
				*ratio_out=((gzFloat)m_d1)/m_d2;

			return m_bestMatch;
		}

		return NULL;
	}

protected:

	gzVoid testItem(gzInt32 (&index) [T],gzInt32 distance)
	{
		gzInt32		*p_index,i,
					*p_test_index,
					test_index[T],
					*p_center,*p_max,*p_min,
					val,bitdiff;

		gzInt8 sign[T],*p_sign;
		memset(sign,-1,sizeof(sign));

		gzBool carry,outbound;

		gzInt32 dist=distance+m_dist_0;
				
		while(TRUE)
		{
			// ---------------- Test -----------------------

			outbound=FALSE;

            p_index=index;
			p_center=m_center;
			p_test_index=test_index;
			p_max=m_max;
			p_min=m_min;
			p_sign=sign;

			i=T;

            while(i)
            {
                --i;

                val=*p_center+*p_index * *p_sign;

                if(val>*p_max)
                {
                    outbound=TRUE;
                    break;
                }
                else if(val<*p_min)
                {
                    outbound=TRUE;
                    break;
                }
                else
                    *p_test_index=val;
                
                if(i)
                {
                    ++p_max;
                    ++p_min;
                    ++p_index;
                    ++p_center;
                    ++p_test_index;
					++p_sign;
                }
            }

            if(!outbound)
            {
                gzRefList<ITEM> &list=getIndex(test_index);

				ITEM *item;

                if(list.entries())
                {
                    m_iterator.setList(list);
                    
                    while((item=m_iterator()))
                    {
                        bitdiff=m_findItem->distance(item);

                        if(bitdiff<m_d1)
                        {
                            // Check if we are the same
                            if(m_bestMatch && m_bestMatch->isSame(item))
                            {
                                m_d1=bitdiff;
                                m_bestMatch=item;
                            }
                            else
                            {
                                m_d2=m_d1;
                                m_d1=bitdiff;
                                m_bestMatch=item;
                            }

                            m_d2_calc=((m_d1*m_iratio)>>10);
                            m_d2_max=gzMin(m_d2,m_d2_calc);
						}
                        else if(bitdiff<m_d2)
                        {
                            if(m_bestMatch && m_bestMatch->isSame(item))
                                continue;

                            m_d2=bitdiff;
                            m_d2_max=gzMin(m_d2,m_d2_calc);
                            m_d1_max=((m_d2*m_ratio)>>10);
                        
							if((dist>m_d1_max) && (m_d1>m_d1_max))
							{
								// No valid solution will be found
								m_exit=TRUE;
								m_fail=TRUE;
								break;
							}
						}

                        if(dist>=m_d2_max)
						{
							// We dont need to iterate further
							m_exit=TRUE;
                            break;
						}
                    }
                }
            }
        
			if(m_exit)
				break;

			if(!distance)
				break;
			
			// ---------------- Update sign ------------------

			carry=TRUE;
			p_sign=sign;
			p_index=index;

			i=T;

			while(i)
			{
				--i;

				if(carry && *p_index)
				{
					carry=FALSE;

					if(*p_sign==-1)
					{
						*p_sign=1;
						break;
					}
					else
					{
						*p_sign=-1;
						carry=TRUE;
					}
				}

				++p_index;
				++p_sign;
			}

			if(carry)
				break;
		}
	}

	gzVoid traverseVolumeBase(gzInt32 *coord,gzInt32 dimension,gzInt32 distance)
	{
		if(T>1)
		{
			gzInt32 k[T];

			memcpy(k,coord,sizeof(k));

			while(TRUE)
			{
				hyperBase(k,dimension,distance);

				if(m_exit)
					return;
			
				if(!*k)
					break;

				--*k;
			}
		}
		else
			hyperBase(coord,dimension,distance);
	}

	gzVoid hyperBase(gzInt32 *coord,gzInt32 dimension,gzInt32 distance)
	{
		gzInt32 result[T],i,j;

		gzInt32 *p_coord,*p_result,*p_base,*p_vec;

		if(dimension<T)
		{
			gzInt32 base[T];
			gzInt32 vec[T][T];
		
			memset(base,0,sizeof(base));
			memset(vec,0,sizeof(vec));

			// set base
			p_base=base;

			*p_base=distance;

			p_vec=vec[0];

			// set vec
			i=0;

			while(i<dimension)
			{
				p_vec[0]=-1;
				p_vec[i+1]=1;

				p_vec+=T;
				++i;
			}

			// Generate new vector

			p_result=result;
			i=0;

			while(i<dimension+1)
			{

				*p_result=*p_base;

				p_coord=coord;

				j=0;

				while(j<dimension)
				{
					*p_result+=*p_coord*vec[j][i];
					++p_coord;
					++j;
				}

				++i;

				++p_base;
				++p_result;
			}
		}
		else
			memcpy(result,coord,sizeof(result));

		if(dimension+1<T)
			traverseVolumeBase(result,dimension+1,distance);
		else
			testItem(result,distance);
	}

	
private:

	gzListIterator<ITEM>			m_iterator;

	gzRefList<ITEM>					*m_index;

	gzInt32							m_max[T];

	gzInt32							m_min[T];

	gzInt32							m_shifts[T];

	gzInt32							m_center[T];

	gzInt32							m_dist_0;

	gzInt32							m_d1,m_d2;

	gzInt32							m_d2_max,m_d2_calc,m_d1_max;

	gzInt32							m_ratio,m_iratio;

	ITEM							*m_bestMatch;

	ITEM							*m_findItem;

	gzBool							m_fail;

	gzBool							m_exit;

};

//---------------------------------------------------------------

template <int T=4,int DIVS=4,class ITEM=gzHammingSortItem<T>,int SPLITS=0,int MIN_LEV=0 > class gzSpatialHammingSort
{
public:

	gzSpatialHammingSort():m_data(0,1,SPLITS,MIN_LEV)
	{
	}

	~gzSpatialHammingSort()
	{
	}

	
	gzVoid addItem(ITEM *item,gzInt32 (&index) [T])
	{
		m_data.insert(index,item);
	}

	gzVoid addItems(gzRefList<ITEM> &list)
	{
		gzListIterator<ITEM> iterator(list);
		ITEM *item;

		gzInt32 index[T];

		while((item=iterator()))
		{
			item->getIndex(index);

			addItem(item,index);
		}
	}

	ITEM * findMatch(ITEM *finditem,gzInt32 dmax=INT_MAX,gzFloat ratio_f=GZ_FLOAT_ONE,gzFloat *ratio_out=nullptr)
	{
		if(!finditem)
			return NULL;

		// Init vars
		m_d1=dmax;
		m_d2=INT_MAX;

		m_bestMatch=nullptr;

		// 3 decimals (1024 factor)

		m_ratio=(gzInt32)((1<<10)*ratio_f);
		m_iratio=(gzInt32)((1<<10)/ratio_f);

		m_d2_max=m_d2_calc=((dmax*m_iratio)>>10);

		gzInt32 index[T],bitdiff;

		finditem->getIndex(index);


		gzMultiSpatialIterator<ITEM *,T,gzInt32,DIVS> iterator(m_data,index,0);
	
		ITEM *item;

		iterator.setMaxSum(INT_MAX);

		while(iterator(item))
		{
			bitdiff=item->distance(finditem);

			if(bitdiff<m_d1)
			{
				// Check if we are the same
				if(m_bestMatch && m_bestMatch->isSame(item))
				{
					m_d1=bitdiff;
					m_bestMatch=item;
				}
				else
				{
					m_d2=m_d1;
					m_d1=bitdiff;
					m_bestMatch=item;
				}

				m_d2_calc=((m_d1*m_iratio)>>10);
				m_d2_max=gzMin(m_d2,m_d2_calc);

				iterator.setMaxSum(m_d2_max);
			}
			else if(bitdiff<m_d2)
			{
				if(m_bestMatch && m_bestMatch->isSame(item))
					continue;

				m_d2=bitdiff;
				m_d2_max=gzMin(m_d2,m_d2_calc);

				iterator.setMaxSum(m_d2_max);
                     
			}
		}


		if(!m_d1)
		{
			if(m_d2 || (m_ratio>=(1<<10)))
			{
				if(ratio_out)
					*ratio_out=0;

				return m_bestMatch;
			}
		}
		else if(m_d1<=((m_d2*m_ratio)>>10))
		{
			if(ratio_out)
				*ratio_out=((gzFloat)m_d1)/m_d2;

			return m_bestMatch;
		}

		return NULL;
	}


	
private:

	gzMultiSpatial<ITEM *,T,gzInt32,DIVS>	m_data;

	gzInt32									m_d1,m_d2;

	gzInt32									m_d2_max,m_d2_calc;

	gzInt32									m_ratio,m_iratio;

	ITEM									*m_bestMatch;
};

//---------------------------------------------------------------

template <int T=4,class ITEM=gzHammingSortItem<T> > class gzPlainHammingSort
{
public:

	gzPlainHammingSort()
	{
	}

	~gzPlainHammingSort()
	{
	}

	
	gzVoid addItems(gzRefList<ITEM> &list)
	{
		m_data=list;
	}

	ITEM * findMatch(ITEM *finditem,gzInt32 dmax=INT_MAX,gzFloat ratio_f=GZ_FLOAT_ONE,gzFloat *ratio_out=nullptr)
	{
		if(!finditem)
			return NULL;

		// Init vars
		m_d1=dmax;
		m_d2=INT_MAX;

		m_bestMatch=nullptr;

		// 3 decimals (1024 factor)

		m_ratio=(gzInt32)((1<<10)*ratio_f);
		m_iratio=(gzInt32)((1<<10)/ratio_f);

		m_d2_max=m_d2_calc=((dmax*m_iratio)>>10);

		gzInt32 bitdiff;

		gzListIterator<ITEM>	iterator(m_data);
		ITEM *item;


		while((item=iterator()))
		{
			bitdiff=item->distance(finditem);

			if(bitdiff<m_d1)
			{
				// Check if we are the same
				if(m_bestMatch && m_bestMatch->isSame(item))
				{
					m_d1=bitdiff;
					m_bestMatch=item;
				}
				else
				{
					m_d2=m_d1;
					m_d1=bitdiff;
					m_bestMatch=item;
				}

				m_d2_calc=((m_d1*m_iratio)>>10);
				m_d2_max=gzMin(m_d2,m_d2_calc);
			}
			else if(bitdiff<m_d2)
			{
				if(m_bestMatch && m_bestMatch->isSame(item))
					continue;

				m_d2=bitdiff;
				m_d2_max=gzMin(m_d2,m_d2_calc);                     
			}
		}

		if(!m_d1)
		{
			if(m_d2 || (m_ratio>=(1<<10)))
			{
				if(ratio_out)
					*ratio_out=0;

				return m_bestMatch;
			}
		}
		else if(m_d1<=((m_d2*m_ratio)>>10))
		{
			if(ratio_out)
				*ratio_out=((gzFloat)m_d1)/m_d2;

			return m_bestMatch;
		}

		return NULL;
	}


	
private:

	gzRefList<ITEM>							m_data;

	gzInt32									m_d1,m_d2;

	gzInt32									m_d2_max,m_d2_calc;

	gzInt32									m_ratio,m_iratio;

	ITEM									*m_bestMatch;
};




#endif //__GZ_HAMMING_H__

