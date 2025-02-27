#pragma once

#include "CoreMinimal.h"
#include "gzBaseLibrary.h"

inline gzString toString(const FName& name)
{
	return gzString(*name.ToString());
}

inline gzString toString(const FString& string)
{
	return gzString(*string);
}

inline gzString toString(const TCHAR *string)
{
	return gzString((gzWideChar *)string);
}

//******************************************************************************
// Template	: cswHashInterface<T>
//									
// Purpose  : Template to enable hash function of <T> values 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	241122	Created 
//									
//******************************************************************************
template <class T> class cswHashInterface : public T
{
public:

	gzUInt32	hash() const;
};

template <> inline gzUInt32 cswHashInterface<FName>::hash() const
{
	return (gzUInt32)GetNumber();
}

//******************************************************************************
// Class	: cswUEPropertyChain<MyClass>
//									
// Purpose  : register methods on property updates
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	241122	Created 
//									
//******************************************************************************
template <class T> class cswUEPropertyChain 
{
public:

	cswUEPropertyChain(){}

	typedef bool(T::* ThisPtr)();

	class cswUEPropertyChainData : public gzThreadSafeReference
	{
	public:
		
		ThisPtr				methodPointer;

		gzReference* clone() const
		{
			return (gzReference*)new cswUEPropertyChainData(*this);
		}
	};

	bool registerPropertyUpdate(const FName& name, ThisPtr method)
	{
		cswUEPropertyChainData *ptr = m_propMethods.find(cswHashInterface<FName>(name));

		if (ptr)
		{
			GZMESSAGE(GZ_MESSAGE_WARNING, "Property %s is already registerd", toString(name));
			return false;
		}

		ptr = new cswUEPropertyChainData;

		ptr->methodPointer = method;

		m_propMethods.enter(cswHashInterface<FName>(name), ptr);

		return true;
	}

	bool propertyUpdate(const FName& name)
	{
		cswUEPropertyChainData *ptr = m_propMethods.find(cswHashInterface<FName>(name));

		if (!ptr)			// if not registered just fall through
			return true;

		return (((T*)this)->*ptr->methodPointer)();
	}

	bool propertyUpdate()
	{
		gzDictIterator<cswHashInterface<FName>, cswUEPropertyChainData> iterator(m_propMethods);
		gzDictEntry<cswHashInterface<FName>, cswUEPropertyChainData>* entry;

		while (entry = iterator())
		{
			bool result = (((T*)this)->*entry->getData()->methodPointer)();

			if (!result)
			{
				GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to update property %s", toString(entry->getKey()));
				return false;
			}
		}

		return true;
	}

private:

	gzRefDict<cswHashInterface<FName>, cswUEPropertyChainData>	m_propMethods;

};

//******************************************************************************
// Class	: cswUEReference<MyClass>
//									
// Purpose  : gzReference management of objects
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	241122	Created 
//									
//******************************************************************************
template <class T> class cswUEReference : public gzReference
{
public:

	//! Default constructor
	cswUEReference() {}

	//! Default copy constructor
	cswUEReference(const T* handle):m_handle(handle){};

	//! Default assignment operator
	cswUEReference& operator=(const T* handle) { m_handle = handle; return *this; }
	
	virtual gzVoid unref()
	{
		if (_refCount)
		{
			if (!(--_refCount))
				destroyHandle();
		}
		else
		{
			gzReference::throwFatalException("REFERENCE MISMATCH ! Unref an object with zero reference count."); //NOSONAR - We want this exception to happend even in destructor
		}
	}

	gzBool checkDelete()
	{
		if (!_refCount)
		{
			destroyHandle();
			return TRUE;
		}
		return FALSE;
	}


	virtual gzVoid destroyHandle()
	{
		// right now just zero out handle
		m_handle = nullptr;
	}

private:

	const T* m_handle=nullptr;

};

