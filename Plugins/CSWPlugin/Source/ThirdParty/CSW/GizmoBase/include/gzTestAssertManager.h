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
// File			: gzTestAssertManager.h
// Module		: gzBase
// Description	: Class definition of platform dependant test assert integrations
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.201
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
// AMO	180425	Created file 										(2.9.1)
// AMO	180502	Added assert on .. (Warning|Fatal) so we can test	(2.9.1)
//******************************************************************************
#ifndef __GZ_TEST_ASSERT_MANAGER_H__
#define __GZ_TEST_ASSERT_MANAGER_H__

#include "gzBaseLibrary.h"

#if defined GZ_WINDOWS && defined MS_CPP_UNITTESTFRAMEWORK

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	#define Assert_Fail(x) Assert::Fail(x)

#else

	// Fix this for other platforms and other test frameworks ... (amo 180425)
	#define Assert_Fail(x) GZMESSAGE(GZ_MESSAGE_ALWAYS,x);

#endif



class gzTestAssertManager : public gzMessageReceiverInterface , 
							public gzReference
{
public:

	gzTestAssertManager(gzString logname,gzBool assertOnFatal=TRUE, gzBool assertOnWarning = FALSE, gzBool immediateAssert = TRUE ):m_propertyAssertOnFatal(assertOnFatal),m_propertyAssertOnWarning(assertOnWarning),m_propertyImmediateAssert(immediateAssert)
	{
		gzMessage::addMessageReceiver(this);

		gzString logURL;

		logURL.format("%s-%s.txt", logname, gzTime::now().asString("%4d-%02d-%02d--%02d_%02d_%02d"));

		m_logger = new gzLogger(logURL);
	}
	
	virtual ~gzTestAssertManager()
	{
		gzMessage::removeMessageReceiver(this);

		reportErrors();
	}

	gzVoid onMessage(const gzString& /*sender*/, gzMessageLevel level, const char *message)
	{
		if ((level & GZ_MESSAGE_LEVEL_MASK_STD) == GZ_MESSAGE_ASSERT)
			m_asserts += message;
		else if (m_propertyAssertOnFatal && ((level & GZ_MESSAGE_LEVEL_MASK_STD) == GZ_MESSAGE_FATAL))
			m_asserts += message;
		else if (m_propertyAssertOnWarning && ((level & GZ_MESSAGE_LEVEL_MASK_STD) == GZ_MESSAGE_WARNING))
			m_asserts += message;
		else
			return;

		if (m_propertyImmediateAssert)
			reportErrors();
	}

	gzVoid reportErrors()
	{
		for (gzUInt32 i = 0; i < m_asserts.getSize(); i++)
			Assert_Fail(m_asserts[i].getWideString());

		m_asserts.setSize(0);
	}

	GZ_PROPERTY(gzBool, AssertOnFatal);
	GZ_PROPERTY(gzBool, AssertOnWarning);
	GZ_PROPERTY(gzBool, ImmediateAssert);

private:

	
	gzDynamicArray<gzString>	m_asserts;
	gzLoggerPtr					m_logger;
};

GZ_DECLARE_REFPTR(gzTestAssertManager);

#endif //__GZ_TEST_ASSERT_MANAGER_H__

