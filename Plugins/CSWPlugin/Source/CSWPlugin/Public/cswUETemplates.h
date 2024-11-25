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

