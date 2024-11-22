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
	return 0;
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

	bool registerPropertyUpdate(const FName& name, ThisPtr method)
	{
		ThisPtr *ptr = m_propMethods.find(cswHashInterface<FName>(name));

		if (ptr)
		{
			GZMESSAGE(GZ_MESSAGE_WARNING, "Property %s is already registerd", toString(name));
			return false;
		}

		m_propMethods.enter(cswHashInterface<FName>(name), &method);

		return true;
	}

	bool propertyUpdate(const FName& name)
	{
		ThisPtr *ptr = m_propMethods.find(cswHashInterface<FName>(name));

		if (!ptr)
		{
			GZMESSAGE(GZ_MESSAGE_WARNING, "Property %s is not registerd", toString(name));
			return false;
		}

		//return true;

		return (((T*)this)->*(*ptr)) ();
	}

private:

	gzDict<cswHashInterface<FName>, ThisPtr>	m_propMethods;

};
