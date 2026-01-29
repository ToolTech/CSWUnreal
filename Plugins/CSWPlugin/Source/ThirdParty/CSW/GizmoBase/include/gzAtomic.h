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
// File			: gzAtomic.h
// Module		: gzBase
// Description	: Atomic utilities
// Author		: Anders Moden
// Product		: GizmoBase 2.12.306
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
// GPT	260119	Created file
// GPT	260119	Added 8/16-bit support and increment
//
//******************************************************************************
#ifndef __GZ_ATOMIC_H__
#define __GZ_ATOMIC_H__

/*!	ile 
	rief Atomic utilities
*/

#include "gzBasicTypes.h"

#if defined(_MSC_VER)
	#include <intrin.h>
#endif

#if defined(_MSC_VER)
	#define GZ_ATOMIC_MSVC
#elif defined(__clang__) || defined(__GNUC__)
	#define GZ_ATOMIC_GNU
#else
	#error "gzAtomic requires MSVC or GCC/Clang"
#endif

template <typename T> class gzAtomic;

//******************************************************************************
// Class	: gzAtomic<gzByte>
//******************************************************************************
template <> class gzAtomic<gzByte>
{
public:
	explicit gzAtomic(gzByte value = 0) : m_value(value) {}

	gzByte load() const
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzByte)_InterlockedCompareExchange8((volatile char*)&m_value, 0, 0);
#else
		return __atomic_load_n(&m_value, __ATOMIC_SEQ_CST);
#endif
	}

	gzVoid store(gzByte value)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzByte expected = load();
		while (!compareExchange(expected, value)) {}
#else
		__atomic_store_n(&m_value, value, __ATOMIC_SEQ_CST);
#endif
	}

	gzBool compareExchange(gzByte& expected, gzByte desired)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzByte prev = (gzByte)_InterlockedCompareExchange8((volatile char*)&m_value, (char)desired, (char)expected);
		if (prev == expected) return TRUE;
		expected = prev;
		return FALSE;
#else
		return __atomic_compare_exchange_n(&m_value, &expected, desired, FALSE, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
	}

	gzByte increment(gzByte delta = 1)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzByte prev = load();
		while (!compareExchange(prev, (gzByte)(prev + delta))) {}
		return prev;
#else
		return __atomic_fetch_add(&m_value, delta, __ATOMIC_SEQ_CST);
#endif
	}

private:
	alignas(1) volatile gzByte m_value;
};

//******************************************************************************
// Class	: gzAtomic<gzUByte>
//******************************************************************************
template <> class gzAtomic<gzUByte>
{
public:
	explicit gzAtomic(gzUByte value = 0) : m_value(value) {}

	gzUByte load() const
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzUByte)_InterlockedCompareExchange8((volatile char*)&m_value, 0, 0);
#else
		return __atomic_load_n(&m_value, __ATOMIC_SEQ_CST);
#endif
	}

	gzVoid store(gzUByte value)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzUByte expected = load();
		while (!compareExchange(expected, value)) {}
#else
		__atomic_store_n(&m_value, value, __ATOMIC_SEQ_CST);
#endif
	}

	gzBool compareExchange(gzUByte& expected, gzUByte desired)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzUByte prev = (gzUByte)_InterlockedCompareExchange8((volatile char*)&m_value, (char)desired, (char)expected);
		if (prev == expected) return TRUE;
		expected = prev;
		return FALSE;
#else
		return __atomic_compare_exchange_n(&m_value, &expected, desired, FALSE, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
	}

	gzUByte increment(gzUByte delta = 1)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzUByte prev = load();
		while (!compareExchange(prev, (gzUByte)(prev + delta))) {}
		return prev;
#else
		return __atomic_fetch_add(&m_value, delta, __ATOMIC_SEQ_CST);
#endif
	}

private:
	alignas(1) volatile gzUByte m_value;
};

//******************************************************************************
// Class	: gzAtomic<gzInt16>
//******************************************************************************
template <> class gzAtomic<gzInt16>
{
public:
	explicit gzAtomic(gzInt16 value = 0) : m_value(value) {}

	gzInt16 load() const
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzInt16)_InterlockedCompareExchange16((volatile short*)&m_value, 0, 0);
#else
		return __atomic_load_n(&m_value, __ATOMIC_SEQ_CST);
#endif
	}

	gzVoid store(gzInt16 value)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzInt16 expected = load();
		while (!compareExchange(expected, value)) {}
#else
		__atomic_store_n(&m_value, value, __ATOMIC_SEQ_CST);
#endif
	}

	gzBool compareExchange(gzInt16& expected, gzInt16 desired)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzInt16 prev = (gzInt16)_InterlockedCompareExchange16((volatile short*)&m_value, (short)desired, (short)expected);
		if (prev == expected) return TRUE;
		expected = prev;
		return FALSE;
#else
		return __atomic_compare_exchange_n(&m_value, &expected, desired, FALSE, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
	}

	gzInt16 increment(gzInt16 delta = 1)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzInt16 prev = load();
		while (!compareExchange(prev, (gzInt16)(prev + delta))) {}
		return prev;
#else
		return __atomic_fetch_add(&m_value, delta, __ATOMIC_SEQ_CST);
#endif
	}

private:
	alignas(2) volatile gzInt16 m_value;
};

//******************************************************************************
// Class	: gzAtomic<gzUInt16>
//******************************************************************************
template <> class gzAtomic<gzUInt16>
{
public:
	explicit gzAtomic(gzUInt16 value = 0) : m_value(value) {}

	gzUInt16 load() const
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzUInt16)_InterlockedCompareExchange16((volatile short*)&m_value, 0, 0);
#else
		return __atomic_load_n(&m_value, __ATOMIC_SEQ_CST);
#endif
	}

	gzVoid store(gzUInt16 value)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzUInt16 expected = load();
		while (!compareExchange(expected, value)) {}
#else
		__atomic_store_n(&m_value, value, __ATOMIC_SEQ_CST);
#endif
	}

	gzBool compareExchange(gzUInt16& expected, gzUInt16 desired)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzUInt16 prev = (gzUInt16)_InterlockedCompareExchange16((volatile short*)&m_value, (short)desired, (short)expected);
		if (prev == expected) return TRUE;
		expected = prev;
		return FALSE;
#else
		return __atomic_compare_exchange_n(&m_value, &expected, desired, FALSE, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
	}

	gzUInt16 increment(gzUInt16 delta = 1)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzUInt16 prev = load();
		while (!compareExchange(prev, (gzUInt16)(prev + delta))) {}
		return prev;
#else
		return __atomic_fetch_add(&m_value, delta, __ATOMIC_SEQ_CST);
#endif
	}

private:
	alignas(2) volatile gzUInt16 m_value;
};

//******************************************************************************
// Class	: gzAtomic<gzInt32>
//******************************************************************************
template <> class gzAtomic<gzInt32>
{
public:
	explicit gzAtomic(gzInt32 value = 0) : m_value(value) {}

	gzInt32 load() const
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzInt32)_InterlockedCompareExchange((volatile long*)&m_value, 0, 0);
#else
		return __atomic_load_n(&m_value, __ATOMIC_SEQ_CST);
#endif
	}

	gzVoid store(gzInt32 value)
	{
#if defined(GZ_ATOMIC_MSVC)
		_InterlockedExchange((volatile long*)&m_value, (long)value);
#else
		__atomic_store_n(&m_value, value, __ATOMIC_SEQ_CST);
#endif
	}

	gzBool compareExchange(gzInt32& expected, gzInt32 desired)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzInt32 prev = (gzInt32)_InterlockedCompareExchange((volatile long*)&m_value, (long)desired, (long)expected);
		if (prev == expected) return TRUE;
		expected = prev;
		return FALSE;
#else
		return __atomic_compare_exchange_n(&m_value, &expected, desired, FALSE, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
	}

	gzInt32 increment(gzInt32 delta = 1)
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzInt32)_InterlockedExchangeAdd((volatile long*)&m_value, (long)delta);
#else
		return __atomic_fetch_add(&m_value, delta, __ATOMIC_SEQ_CST);
#endif
	}

private:
	alignas(4) volatile gzInt32 m_value;
};

//******************************************************************************
// Class	: gzAtomic<gzUInt32>
//******************************************************************************
template <> class gzAtomic<gzUInt32>
{
public:
	explicit gzAtomic(gzUInt32 value = 0) : m_value(value) {}

	gzUInt32 load() const
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzUInt32)_InterlockedCompareExchange((volatile long*)&m_value, 0, 0);
#else
		return __atomic_load_n(&m_value, __ATOMIC_SEQ_CST);
#endif
	}

	gzVoid store(gzUInt32 value)
	{
#if defined(GZ_ATOMIC_MSVC)
		_InterlockedExchange((volatile long*)&m_value, (long)value);
#else
		__atomic_store_n(&m_value, value, __ATOMIC_SEQ_CST);
#endif
	}

	gzBool compareExchange(gzUInt32& expected, gzUInt32 desired)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzUInt32 prev = (gzUInt32)_InterlockedCompareExchange((volatile long*)&m_value, (long)desired, (long)expected);
		if (prev == expected) return TRUE;
		expected = prev;
		return FALSE;
#else
		return __atomic_compare_exchange_n(&m_value, &expected, desired, FALSE, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
	}

	gzUInt32 increment(gzUInt32 delta = 1)
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzUInt32)_InterlockedExchangeAdd((volatile long*)&m_value, (long)delta);
#else
		return __atomic_fetch_add(&m_value, delta, __ATOMIC_SEQ_CST);
#endif
	}

private:
	alignas(4) volatile gzUInt32 m_value;
};

//******************************************************************************
// Class	: gzAtomic<gzInt64>
//******************************************************************************
template <> class gzAtomic<gzInt64>
{
public:
	explicit gzAtomic(gzInt64 value = 0) : m_value(value) {}

	gzInt64 load() const
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzInt64)_InterlockedCompareExchange64((volatile long long*)&m_value, 0, 0);
#else
		return __atomic_load_n(&m_value, __ATOMIC_SEQ_CST);
#endif
	}

	gzVoid store(gzInt64 value)
	{
#if defined(GZ_ATOMIC_MSVC)
		_InterlockedExchange64((volatile long long*)&m_value, (long long)value);
#else
		__atomic_store_n(&m_value, value, __ATOMIC_SEQ_CST);
#endif
	}

	gzBool compareExchange(gzInt64& expected, gzInt64 desired)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzInt64 prev = (gzInt64)_InterlockedCompareExchange64((volatile long long*)&m_value, (long long)desired, (long long)expected);
		if (prev == expected) return TRUE;
		expected = prev;
		return FALSE;
#else
		return __atomic_compare_exchange_n(&m_value, &expected, desired, FALSE, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
	}

	gzInt64 increment(gzInt64 delta = 1)
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzInt64)_InterlockedExchangeAdd64((volatile long long*)&m_value, (long long)delta);
#else
		return __atomic_fetch_add(&m_value, delta, __ATOMIC_SEQ_CST);
#endif
	}

private:
	alignas(8) volatile gzInt64 m_value;
};

//******************************************************************************
// Class	: gzAtomic<gzUInt64>
//******************************************************************************
template <> class gzAtomic<gzUInt64>
{
public:
	explicit gzAtomic(gzUInt64 value = 0) : m_value(value) {}

	gzUInt64 load() const
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzUInt64)_InterlockedCompareExchange64((volatile long long*)&m_value, 0, 0);
#else
		return __atomic_load_n(&m_value, __ATOMIC_SEQ_CST);
#endif
	}

	gzVoid store(gzUInt64 value)
	{
#if defined(GZ_ATOMIC_MSVC)
		_InterlockedExchange64((volatile long long*)&m_value, (long long)value);
#else
		__atomic_store_n(&m_value, value, __ATOMIC_SEQ_CST);
#endif
	}

	gzBool compareExchange(gzUInt64& expected, gzUInt64 desired)
	{
#if defined(GZ_ATOMIC_MSVC)
		gzUInt64 prev = (gzUInt64)_InterlockedCompareExchange64((volatile long long*)&m_value, (long long)desired, (long long)expected);
		if (prev == expected) return TRUE;
		expected = prev;
		return FALSE;
#else
		return __atomic_compare_exchange_n(&m_value, &expected, desired, FALSE, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
	}

	gzUInt64 increment(gzUInt64 delta = 1)
	{
#if defined(GZ_ATOMIC_MSVC)
		return (gzUInt64)_InterlockedExchangeAdd64((volatile long long*)&m_value, (long long)delta);
#else
		return __atomic_fetch_add(&m_value, delta, __ATOMIC_SEQ_CST);
#endif
	}

private:
	alignas(8) volatile gzUInt64 m_value;
};

//******************************************************************************
// Class	: gzAtomic<T*>
//******************************************************************************
template <typename T> class gzAtomic<T*>
{
public:
	explicit gzAtomic(T* value = nullptr) : m_value(value) {}

	T* load() const
	{
#if defined(GZ_ATOMIC_MSVC)
		return (T*)_InterlockedCompareExchangePointer((void* volatile*)&m_value, nullptr, nullptr);
#else
		return __atomic_load_n(&m_value, __ATOMIC_SEQ_CST);
#endif
	}

	gzVoid store(T* value)
	{
#if defined(GZ_ATOMIC_MSVC)
		_InterlockedExchangePointer((void* volatile*)&m_value, (void*)value);
#else
		__atomic_store_n(&m_value, value, __ATOMIC_SEQ_CST);
#endif
	}

	gzBool compareExchange(T*& expected, T* desired)
	{
#if defined(GZ_ATOMIC_MSVC)
		void* prev = _InterlockedCompareExchangePointer((void* volatile*)&m_value, (void*)desired, (void*)expected);
		if (prev == expected) return TRUE;
		expected = (T*)prev;
		return FALSE;
#else
		return __atomic_compare_exchange_n(&m_value, &expected, desired, FALSE, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
	}

private:
	alignas(sizeof(void*)) T* volatile m_value;
};

#endif
