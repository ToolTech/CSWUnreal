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
// File			: gzObject.h
// Module		: gzBase
// Description	: Class definition of object management
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.222
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
// AMO	121214	Added asString() method to gzObject to do a generic printout of data (2.6.18)
// AMO	130815	Added unregisterFactory for types									 (2.7.0)
//
//******************************************************************************
#ifndef __GZ_OBJECT_H__
#define __GZ_OBJECT_H__

/*!	\file 
	\brief User Objects for Gizmo3D

Gizmo3D uses the gzObject class as a base class for all scene graph nodes.
*/


#include "gzMemory.h"
#include "gzTemplates.h"
#include "gzBase.h"
#include "gzSerialize.h"
#include "gzNotify.h"
#include "gzDynamic.h"
#include "gzHashUtils.h"
#include "gzThread.h"

class gzObject;	// Forward decl of attached data to an object

//******************************************************************************
// Class	: gzUserData
//									
// Purpose  : Basic holder of all user defined data. All objects inherits from
//			  the gzObject class that has a set of UserData
//									
// Notes	: Default behaviour is to ref()/unref() on two virtual functions	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980912	Created 
//									
//******************************************************************************
//! Base class for user provided data
class  gzUserData : public gzReference , public gzSerializeData
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT virtual ~gzUserData(){};

	GZ_BASE_EXPORT virtual gzVoid onAttach( gzObject * /*object*/ , const gzString & /*attribute*/ ) { ref(); }

	GZ_BASE_EXPORT virtual gzVoid onDetach( gzObject * /*object*/ , const gzString & /*attribute*/) { unref(); }

	//! You shall make a cloned copy ( new class(*this) ) in this call
	GZ_BASE_EXPORT virtual gzReference* clone() const override=0;

	//! You shall provide a equality check in this method
	GZ_BASE_EXPORT virtual gzBool isEqualTo(const gzUserData *data) const { return data==this; }

};

GZ_DECLARE_REFPTR(gzUserData);

//******************************************************************************
// Class	: gzUserDataAttributeContainer
//									
// Purpose  : Basic holder of all user defined data. All objects inherits from
//			  the gzObject class that has a set of UserData
//									
// Notes	: Default behaviour is to ref()/unref() on two virtual functions	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980912	Created 
//									
//******************************************************************************
//! Base class for user provided data
class  gzUserDataAttributeContainer : public gzUserData , public gzDynamicTypeContainer
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzUserDataAttributeContainer();
	GZ_BASE_EXPORT gzUserDataAttributeContainer(const gzUserDataAttributeContainer& right);
	GZ_BASE_EXPORT gzUserDataAttributeContainer &operator=(const gzUserDataAttributeContainer& right);

	GZ_BASE_EXPORT virtual ~gzUserDataAttributeContainer();

	GZ_BASE_EXPORT virtual gzVoid onAttributeEvent( gzDynamicTypeEvent reason , const gzString &name) override;

	GZ_BASE_EXPORT virtual gzVoid onAttach( gzObject *object , const gzString &attribute) override;

	GZ_BASE_EXPORT virtual gzVoid onDetach( gzObject *object , const gzString &attribute) override;

	GZ_BASE_EXPORT virtual gzReference* clone() const override;

	GZ_BASE_EXPORT virtual gzBool isEqualTo(const gzUserData *data) const override;

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) override;

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const override;


private:

	gzList<gzObject>			m_attachements;
};

GZ_DECLARE_REFPTR(gzUserDataAttributeContainer);

//******************************************************************************
// Class	: gzObjectDictionary
//									
// Purpose  : Private class that hold data for gzObject
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980912	Created 
//									
//******************************************************************************
//! Base class for dictionary lookup. Used by gzObject
class  gzUserDataDictionary : public gzDict<gzString,gzUserData>
{
	virtual ~gzUserDataDictionary(){};

private:
	friend class gzObject;

	gzUserDataDictionary();
	
	gzObject *m_owner;

	virtual gzVoid onInsert(const gzString &key, gzUserData * value ) const { value->onAttach(m_owner,key);}

	virtual gzVoid onRemove(const gzString &key, gzUserData * value ) const { value->onDetach(m_owner,key);}
};


class gzObjectInvokeInterface : public gzReference , public gzDynamicInvokeInterface
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// typed interface

	GZ_BASE_EXPORT gzObjectInvokeInterface();
	GZ_BASE_EXPORT virtual ~gzObjectInvokeInterface();

	// ---------- Interface registration -------------------------------
	GZ_BASE_EXPORT static gzVoid registerInterface(gzType *type,gzObjectInvokeInterface *iface);
	GZ_BASE_EXPORT static gzVoid unRegisterInterface(gzType *ifacetype);

	// ---------- Dynamic method invokation ----------------------------

	GZ_BASE_EXPORT static gzDynamicType					instanceInvokeMethod(gzReference *instance,const gzString &IIDS_method,GZ_DYNAMIC_ATTRIBUTE_LIST);
	GZ_BASE_EXPORT static gzDynamicType					instanceInvokeMethod(gzReference *instance,gzUInt64 IID_method,GZ_DYNAMIC_ATTRIBUTE_LIST);
	GZ_BASE_EXPORT static gzBool						instanceSupportMethod(gzReference *instance,gzUInt64 IID_method);
	GZ_BASE_EXPORT static gzUInt64						instanceGetMethodIID(gzReference *instance,const gzString &IIDS_method);
	GZ_BASE_EXPORT static gzDynamicMethod				instanceGetDirectMethod(gzReference *instance,gzUInt64 IID_method);
	GZ_BASE_EXPORT static gzString						instanceGetDescription(gzReference *instance,gzUInt64 IID_method);
	GZ_BASE_EXPORT static gzArray<gzDynamicMethodID>	instanceQueryAllMethodIID(gzReference *instance);

private:

	static gzRefDict<gzType,gzObjectInvokeInterface>		s_interfaces;
};

//******************************************************************************
// Class	: gzObject
//									
// Purpose  : Base class for all Gizmo objects. 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980912	Created 
//									
//******************************************************************************
/*! \brief Base definition of a user object

The gzObject contains all nessecary functionality for an object to exist as a special Gizmo3D 
object. gzObjects uses type definition (RTTI) and they have a name. They can be notified by other
objects using the gzNotifyInterface and they can hold user data as well as attribute data.

The purpose of this object is rather complex. However if you want a generic object that can be used by
most utilites in Gizmo3D you should derive from gzObject. If you want your object to be used in a scene graph
you should select the graph node gzNode which is a special gzObject.

*/

class  gzObject : public gzUserData 
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// typed interface
	
	GZ_BASE_EXPORT gzObject();
	GZ_BASE_EXPORT gzObject( const gzObject &copy);
	GZ_BASE_EXPORT gzObject &operator=(const gzObject &copy);

	GZ_BASE_EXPORT virtual ~gzObject();

	//---------------------- custom user data ----------------------------------
	GZ_BASE_EXPORT gzVoid		addUserData(	const gzString &name , gzUserData *data);
	GZ_BASE_EXPORT gzUserData *	getUserData(	const gzString &name , gzUserData *parent=nullptr) const;
	GZ_BASE_EXPORT gzBool		existUserData(	const gzString &name , gzUserData *data = NULL) const;
	GZ_BASE_EXPORT gzBool		removeUserData( const gzString &name , gzUserData *data = NULL);
	GZ_BASE_EXPORT gzVoid		removeAllUserData();
	GZ_BASE_EXPORT gzBool		hasUserData() const;
	GZ_BASE_EXPORT gzBool		hasSameUserData(const gzObject *object) const;

	GZ_BASE_EXPORT gzVoid		copyUserDataFromObject(const gzObject* object);

	GZ_BASE_EXPORT gzUserDataDictionary *	getUserDataDictionary();


	//---------------------- Attribute data ------------------------------------

	GZ_BASE_EXPORT gzBool			setAttribute(const gzString &userdata , const gzString &name , const gzDynamicType &attribute);
	GZ_BASE_EXPORT gzDynamicType	getAttribute(const gzString &userdata ,const gzString &name) const;
	GZ_BASE_EXPORT gzBool			hasAttribute(const gzString &userdata ,const gzString &name) const;
	GZ_BASE_EXPORT gzBool			removeAttribute(const gzString &userdata ,const gzString &name);
	GZ_BASE_EXPORT gzBool			removeAllAttributes(const gzString &userdata );
	GZ_BASE_EXPORT gzUInt32			getNumberOfAttributes(const gzString &userdata) const;

	GZ_BASE_EXPORT virtual gzVoid onUserDataAttributeEvent( gzUserData * /*data*/ , gzDynamicTypeEvent /*reason*/ , const gzString & /*name*/) {};

	GZ_BASE_EXPORT virtual gzBool onSetAttribute(const gzString& /*userdata*/, const gzString& /*name*/, const gzDynamicType& /*attribute*/) { return TRUE; }
	GZ_BASE_EXPORT virtual gzBool onRemoveAttribute(const gzString& /*userdata*/, const gzString& /*name*/) { return TRUE; }
	GZ_BASE_EXPORT virtual gzBool onRemoveAllAttribute(const gzString& /*userdata*/) { return TRUE; }

	// ---------- Clone interface ---------------------------------------
	GZ_BASE_EXPORT virtual gzReference* clone() const override;

	// ---------- Factory management ------------------------------------

	GZ_BASE_EXPORT static gzUInt32		registerFactoryObject(gzReference *object);
	
	GZ_BASE_EXPORT static gzVoid		unregisterFactory(gzUInt32 id);
	GZ_BASE_EXPORT static gzVoid		unregisterFactory(gzType *type);
	GZ_BASE_EXPORT static gzVoid		unregisterFactory(const gzString &typeName);
	GZ_BASE_EXPORT static gzVoid		unregisterAllFactories();

	GZ_BASE_EXPORT static gzReference*	createFactoryObject(gzUInt32 id);
	GZ_BASE_EXPORT static gzReference*	createFactoryObject(gzType* type);
	GZ_BASE_EXPORT static gzReference*	createFactoryObject(const gzString& typeName);

	GZ_BASE_EXPORT static gzBool		hasFactory(gzUInt32 id);
	GZ_BASE_EXPORT static gzBool		hasFactory(gzType* type);
	GZ_BASE_EXPORT static gzBool		hasFactory(const gzString& typeName);

	// ---------- Serializing -------------------------------------------

	GZ_BASE_EXPORT virtual gzVoid	write(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzVoid	read(gzSerializeAdapter *adapter) override;
	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const override;
	
	// ---------- Serialize Utils ---------------------------------------

	GZ_BASE_EXPORT static	gzVoid		writeObject(gzObject *object, gzSerializeAdapter *adapter, gzUInt32 totlen=0,const gzString &banner=GZ_EMPTY_STRING,gzBool shared=TRUE);
	GZ_BASE_EXPORT static	gzObject *	readObject(gzSerializeAdapter *adapter, gzUInt32 totlen=0,const gzString &banner=GZ_EMPTY_STRING,gzBool eatObject=TRUE);
	GZ_BASE_EXPORT static	gzUInt32	getChunkSize(gzObject *object,gzSerializeAdapter *adapter);


	// ---------- Dynamic method invokation ----------------------------

	GZ_BASE_EXPORT gzDynamicType				invokeMethod(const gzString &IIDS_method,GZ_DYNAMIC_ATTRIBUTE_LIST);
	GZ_BASE_EXPORT gzDynamicType				invokeMethod(gzUInt64 IID_method,GZ_DYNAMIC_ATTRIBUTE_LIST);
	GZ_BASE_EXPORT gzDynamicType				invokeStringParamsMethod(const gzString &IIDS_method,const gzString &params);
	GZ_BASE_EXPORT gzDynamicType				invokeStringParamsMethod(gzUInt64 IID_method,const gzString &params);
	GZ_BASE_EXPORT gzBool						supportMethod(gzUInt64 IID_method);
	GZ_BASE_EXPORT gzUInt64						getMethodIID(const gzString &IIDS_method);
	GZ_BASE_EXPORT gzDynamicMethod				getDirectMethod(gzUInt64 IID_method);
	GZ_BASE_EXPORT gzString						getDescription(gzUInt64 IID_method);	
	GZ_BASE_EXPORT gzArray<gzDynamicMethodID>	queryAllMethodIID();

	// --------- Generic utils --------------------------------------------

	GZ_BASE_EXPORT gzString asString(gzBool stripXML=TRUE) const;

private:

	GZ_BASE_EXPORT virtual gzVoid	pushBack(gzSerializeAdapter *adapter) override;	//!< Not allowed to do a pushback of gzObjects

	gzUserDataDictionary	*m_userData;

	static gzRefDict< gzUInt32CompareInterface, gzReference> 	s_objectFactory;

	static gzMemCheck<gzMutex>									s_factoryLocker;
};

GZ_DECLARE_REFPTR(gzObject);

//******************************************************************************
// Class	: gzObjectSender
//									
// Purpose  : Sends objects on a url channel
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150825	Created 
//									
//******************************************************************************
class gzObjectSender
{
public:

	GZ_BASE_EXPORT gzObjectSender(const gzString &channelName,gzSerializeAdapter *adapter=nullptr);

	GZ_BASE_EXPORT gzBool openURL(const gzString &url);

	GZ_BASE_EXPORT gzBool sendObject(gzObject *object);

	//!Writes the object data to the adapter.
	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter);

	//!Reads the object data from the adapter.
	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter);

	//!Returns the size of the object data.
	GZ_BASE_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const;

private:

	gzSerializeAdapterPtr		m_adapter;

	gzSerializeAdapterQueuePtr	m_queue;

	gzSerializeAdapterCompress	m_compressor;

	gzString					m_channelName;

	gzString					m_url;
};

//******************************************************************************
// Class	: gzObjectReceiver
//									
// Purpose  : Receives objects on a url channel
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150825	Created 
//									
//******************************************************************************
class gzObjectReceiver : public gzThread
{
public:

	GZ_BASE_EXPORT gzObjectReceiver(const gzString &channelName,gzSerializeAdapter *adapter=nullptr);

	GZ_BASE_EXPORT ~gzObjectReceiver();

	GZ_BASE_EXPORT gzBool openURL(const gzString &url);

	GZ_BASE_EXPORT gzVoid virtual onObject(gzObject *object);

	//!Writes the object data to the adapter.
	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter);

	//!Reads the object data from the adapter.
	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter);

	//!Returns the size of the object data.
	GZ_BASE_EXPORT virtual gzUInt32 getDataSize(gzSerializeAdapter *adapter=nullptr) const;

private:

	GZ_BASE_EXPORT gzVoid process() override;

	gzSerializeAdapterPtr		m_adapter;

	gzDynamicArray<gzUByte>		m_queue;

	gzSerializeAdapterCompress	m_compressor;

	gzString					m_channelName;

	gzString					m_url;
};

// ------------------ dynamic cast ----------------------------------

template <> inline gzObject * gzDynamic_Cast(const gzDynamicType &data)
{
	if(data.is(GZ_DYNAMIC_TYPE_REFERENCE))
		return gzDynamic_Cast<gzObject>(data.getReference());
	
	return NULL;
}

#endif
