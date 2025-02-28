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
// File			: gzVertexAttributes.h
// Module		: 
// Description	: Class definition of the gzVertexAttributes class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.224
//		
//
//			
// NOTE:	Gizmo3D is a high performance 3D Scene Graph and effect visualisation 
//			C++ toolkit for Linux, Mac OS X, Windows, Android, iOS and HoloLens for  
//			usage in Game or VisSim development.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030704	Created file 	
//
//******************************************************************************
#ifndef __GZ_VERTEX_ATTRIBUTES_H__
#define __GZ_VERTEX_ATTRIBUTES_H__

/*!	\file 
	\brief Base definitions for geometry classes

*/


#include "gzMatrix.h"
#include "gzObject.h"

enum gzGeoAttribBinding
{  
	GZ_BIND_OFF			= 0 ,	// No binding. The attributes are off				
	GZ_BIND_OVERALL		= 1 ,	// One per complete geometry
	GZ_BIND_PER_PRIM	= 2 ,	// One per primitive. Multiple primitives per geometry
	GZ_BIND_ON			= 3 ,	// One per vertex
	GZ_BIND_PER_VERTEX	= 3		// One per vertex
				
};

//----------------- Vertex Attributes for vertex programs -----------------------

enum
{
	GZ_VERTEX_ATTRIBUTE_LIST_POSITION			= 0,
	GZ_VERTEX_ATTRIBUTE_LIST_WEIGHT				= 1,
	GZ_VERTEX_ATTRIBUTE_LIST_NORMAL				= 2,
	GZ_VERTEX_ATTRIBUTE_LIST_PRIMARY_COLOR		= 3,
	GZ_VERTEX_ATTRIBUTE_LIST_SECONDARY_COLOR	= 4,
	GZ_VERTEX_ATTRIBUTE_LIST_FOG_COORD			= 5,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_0		= 8,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_1		= 9,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_2		= 10,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_3		= 11,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_4		= 12,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_5		= 13,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_6		= 14,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_7		= 15,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_8		= 16,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_9		= 17,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_10		= 18,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_11		= 19,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_12		= 20,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_13		= 21,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_14		= 22,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_15		= 23,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_16		= 24,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_17		= 25,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_18		= 26,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_19		= 27,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_20		= 28,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_21		= 29,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_22		= 30,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_23		= 31,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_24		= 32,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_25		= 33,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_26		= 34,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_27		= 35,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_28		= 36,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_29		= 37,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_30		= 38,
	GZ_VERTEX_ATTRIBUTE_LIST_TEX_COORD_31		= 39,
	GZ_VERTEX_ATTRIBUTE_LIST_GENERIC_0			= 40
};

//******************************************************************************
// Class	: gzVertexAttributeList
//									
// Purpose  : Generic container class for generic vertex attributes
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030707	Created 
//									
//******************************************************************************
class gzVertexAttributeList : public gzObject
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzVertexAttributeList():m_listIndex(1),m_bind(GZ_BIND_ON),m_normalized(FALSE){};

	GZ_GRAPH_EXPORT virtual ~gzVertexAttributeList(){};

	// identify the list type

	GZ_GRAPH_EXPORT gzVoid setListIndex(gzUInt32 listIndex);
	
	GZ_GRAPH_EXPORT gzUInt32 getListIndex();


	GZ_GRAPH_EXPORT gzVoid setNormalized(gzBool on = TRUE);


	// Binding of attributes

	GZ_GRAPH_EXPORT gzVoid setBind(gzGeoAttribBinding bind);

	GZ_GRAPH_EXPORT gzGeoAttribBinding getBind() { return m_bind; }


	GZ_GRAPH_EXPORT virtual gzVoid activate()=0;

	GZ_GRAPH_EXPORT virtual gzVoid activateIndex(gzUInt32 index)=0;

	GZ_GRAPH_EXPORT virtual gzVoid deactivate();

	GZ_GRAPH_EXPORT	virtual gzReference* clone() const override =0;

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

protected:

	gzUInt32				m_listIndex;

	gzGeoAttribBinding		m_bind;

	gzBool					m_normalized;
};

GZ_DECLARE_REFPTR(gzVertexAttributeList);

//******************************************************************************
// Class	: gzVertexAttributeListTemplate<>
//									
// Purpose  : Template container class for generic vertex attributes.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030707	Created 
//									
//******************************************************************************
template <class T> class gzVertexAttributeListTemplate : public gzVertexAttributeList
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	gzVertexAttributeListTemplate(gzUInt32 index=1, gzGeoAttribBinding bind=GZ_BIND_ON)
	{
		setListIndex(index);
		setBind(bind);
	}

	gzVertexAttributeListTemplate(const gzArray<T> & data,gzUInt32 index=1, gzGeoAttribBinding bind = GZ_BIND_ON):m_data(data)
	{
		setListIndex(index);
		setBind(bind);
	}

	virtual ~gzVertexAttributeListTemplate()
	{
	}
	
	operator gzArray<T> & () 
	{ 
		return m_data; 
	}

	const gzVertexAttributeListTemplate<T> & operator =( const gzArray<T> &right) 
	{ 
		m_data=right; 
		return *this; 
	}
	

	GZ_GRAPH_EXPORT virtual gzVoid activate() override;	

	GZ_GRAPH_EXPORT virtual gzVoid activateIndex(gzUInt32 index) override;	

	
	gzReference* clone() const override
	{
		return (gzReference *)new gzVertexAttributeListTemplate<T>(*this);
	}


	gzVoid	setSize(gzUInt32 size)	
	{ 
		m_data.setSize(size);			
	}

	gzUInt32	getSize()				
	{ 
		return m_data.getSize();		
	}

	T *		getAddress()			
	{ 
		return m_data.getAddress();	
	}

	// ---------- Serializing -------------------------------------------

	virtual gzVoid write(gzSerializeAdapter *adapter) override
	{
		gzVertexAttributeList::write(adapter);

		gzSerializeBinaryArray<T> writer(TRUE,FALSE);

		writer.setArray(m_data);

		writer.write(adapter);
	}
	
	virtual gzVoid read(gzSerializeAdapter *adapter) override
	{
		gzVertexAttributeList::read(adapter);

		gzSerializeBinaryArray<T> reader(TRUE,FALSE);

		reader.setArray(m_data);

		reader.read(adapter);
	}

	gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override
	{
		gzUInt32 size= gzVertexAttributeList::getDataSize(adapter);

		gzSerializeBinaryArray<T> sizer(TRUE,FALSE);

		sizer.setArray(m_data);

		size += sizer.getDataSize(adapter);

		return size;
	}


protected:

	gzArray<T>	m_data;
};

//--------------------------------- Template Specifics ------------------------------------------------------

// -------------------------------- copyInstances -----------------------------------------------------------

template <> inline gzVoid copyInstances(gzGeoAttribBinding* to, gzGeoAttribBinding* from, gzUInt32 count, gzBool /*clearSource*/)
{
	memmove(to, from, count * sizeof(gzGeoAttribBinding));
}

// ---------------------------- End of template specifics ---------------------------------------------------

#endif

