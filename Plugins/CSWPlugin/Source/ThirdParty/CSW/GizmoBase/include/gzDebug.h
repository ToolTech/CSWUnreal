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
// File			: gzDebug.h
// Module		: gzBase
// Description	: Class definitions and macros for debugging aid
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.211
//		
// 
//			
// NOTE:	GizmoBase is a platform abstraction utility layer for C++. It contains 
//			design patterns and C++ solutions for the advanced programmer.
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created file 	
// AMO	000531	Restructured Message Receivers, Allow multiple instances
// AMO	120911	Added GZ_MESSAGE_HEAVY_TRACE for intensive message output	(2.6.11)
//
//******************************************************************************

#ifndef __GZ_DEBUG_H__
#define __GZ_DEBUG_H__

/*!	\file 
	\brief Basic utilites for debug management

	There are two types of debug information that can be reported by the system. The first
	type is the GZTRACE() macro debug information. This type of debug information is automatically
	removed from the code when you compile a release version (GZ_DEBUG shall not be defined in a release version)

	The second type of debug information are the notification messages. They are defined as
	GZ_NOTIFY_DEBUG , GZ_NOTIFY_NOTICE , GZ_NOTIFY_WARNING , GZ_NOTIFY_FATAL , GZ_NOTIFY_ALWAYS
	levels. The system shall be set to a propriate level by the setNotifyLevel(). All messages
	with the same or higher priority is then reported by the system. These messages are not
	removed in a release version of the code.
*/
#include "gzBasicTypes.h"
#include "gzTemplates.h"
#include "gzHashUtils.h"
#include "gzMemory.h"
#include "gzReference.h"
#include "gzArgument.h"

//********************* DEBUG macros *****************************************

//! Used by the GZTRACE() macro
class  GZ_BASE_EXPORT gzTrace
{
public:
        static gzVoid TraceMessage(const char * pszFormat, ARG_DECL_LIST );
        static gzVoid NoTraceMessage(const char * /*pszFormat*/, ARG_DECL_LIST_E ){};
		static gzVoid TraceMessageSender(const gzString& sender ,const char * pszFormat, ARG_DECL_LIST );
        static gzVoid NoTraceMessageSender(const gzString& /*sender*/ ,const char * /*pszFormat*/, ARG_DECL_LIST_E ){};

};

/*! \brief Debug arguments for debug output

You can examine tree structures etc. by using the debug() command

*/

//! Debug flags used in the debug method to select output
enum gzDebugFlags
{ 
	GZ_DEBUG_OFF				= 0,
	GZ_DEBUG_SHOW_ALL			= 0xffffffff,
};

GZ_USE_BIT_LOGIC(gzDebugFlags);

/*! \brief Base interface for debug output.

  You can use this interface to support the method debug(). E.g all scene graph nodes gzNode etc.
  uses this interface to provide generic debug information
*/

class gzString;

//******************************************************************************
// Class	: gzDebugInterface
//									
// Purpose  : Interface to present debug information 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981104	Created 
//									
//******************************************************************************
class  GZ_BASE_EXPORT gzDebugInterface
{
public:
	gzVoid	debug(gzDebugFlags features=GZ_DEBUG_SHOW_ALL);
	virtual ~gzDebugInterface(){};

	//! Outputs debug information about instance
	virtual gzVoid debugOutput(gzString base , gzString anchor , gzDebugFlags features);

	//! Traverses debug output to sibling childs, Should only be used in hierarchy implementation
	virtual	gzVoid debugOutputTraverse(gzString base , gzString anchor , gzDebugFlags features);
};


#ifdef GZ_DEBUG
#define GZTRACE gzTrace::TraceMessage
#define GZTRACES gzTrace::TraceMessageSender
#else
#define GZTRACE gzTrace::NoTraceMessage
#define GZTRACES gzTrace::NoTraceMessageSender
#endif

//! Debug output levels
/*! 
	You can add your own levels by adding offset values to the base level.
	e.g. My_MESSAGE_DEBUG_LEVEL = GZ_MESSAGE_DEBUG+1 up to +127;

	Add gzMessageEncoding to the level to set various formats in string
*/
typedef enum {							 //LXNN		L=Level, 1 bit internal ,3 bit X=Encoding ,NN=user defined max 0x7f
				GZ_MESSAGE_MEM_DEBUG		=0x1000 , 
				GZ_MESSAGE_PERF_DEBUG		=0x1001 , 
				GZ_MESSAGE_DETAIL_DEBUG		=0x1002 ,
				GZ_MESSAGE_DEBUG			=0x2000 , 
				GZ_MESSAGE_TRACE_DEBUG		=0x2001 ,
				GZ_MESSAGE_NOTICE			=0x3000 , 
				GZ_MESSAGE_WARNING			=0x4000 , 
				GZ_MESSAGE_FATAL			=0x5000 , 
				GZ_MESSAGE_ASSERT			=0x6000 , 
				GZ_MESSAGE_ALWAYS			=0x7000 ,
				GZ_MESSAGE_LEVEL_MASK		=0xf07f ,
				GZ_MESSAGE_LEVEL_MASK_STD	=0xf000 ,

			} gzMessageLevel;


typedef enum { 
				GZ_MESSAGE_ENCODING_UTF8			= 0,		// Default message encoding
				GZ_MESSAGE_ENCODING_ASCII			= (1<<8),	// Plain Ascii
				GZ_MESSAGE_ENCODING_NO_TRANSLATE	= (1<<9),	// Skip translation
				GZ_MESSAGE_ENCODING_NO_FORMAT		= (1<<10),	// Skip formatting options
				GZ_MESSAGE_ENCODING_MASK			= 0x0700,	// 

			} gzMessageEncoding;

typedef enum {
				GZ_MESSAGE_API_INTERNAL				= (1<<11),	// Internal information about API etc.

				// ------------------- Optional bits used instead of user defined

				GZ_MESSAGE_HEAVY_TRACE				= (1 << 7),	// Heavy trace information, Heavy load on output
				GZ_MESSAGE_JSON						= (1 << 6),	// Output formatted as JSON
				GZ_MESSAGE_XML						= (1 << 5),	// Output formatted as XML

			 } gzMessageType;

//! Define the gzMessageLevel as a combined set with gzMessageEncoding and gzMessageType
GZ_USE_BIT_LOGIC_MIX(gzMessageLevel,gzMessageEncoding);
GZ_USE_BIT_LOGIC_MIX(gzMessageLevel,gzMessageType);



//******************************************************************************
// Class	: gzMessageReceiverInterface
//
// Purpose  : Utility class for message dispatching
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	000531	Created 
//									
//******************************************************************************
class GZ_BASE_EXPORT gzMessageReceiverInterface 
{
public:

	gzMessageReceiverInterface();
	virtual ~gzMessageReceiverInterface();

	// ------------ the receiver --------------------
	virtual gzVoid onMessage(const gzString& sender , gzMessageLevel level , const char *message)=0;

};

//******************************************************************************
// Class	: gzMessageTranslatorInterface
//
// Purpose  : Utility class for message translation
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	000531	Created 
//									
//******************************************************************************
class gzMessageTranslatorInterface 
{
public:

	GZ_BASE_EXPORT gzMessageTranslatorInterface();
	GZ_BASE_EXPORT virtual ~gzMessageTranslatorInterface();

	// ------------ the translator interface --------------------
	GZ_BASE_EXPORT virtual gzString onTranslate(const gzString& sender , gzMessageLevel level , const gzString &message)=0;

	GZ_BASE_EXPORT virtual gzVoid setTranslation(const gzString& sender , const gzString &language,const gzString &text,const gzString &translation)=0;

	GZ_BASE_EXPORT static gzVoid setCurrentLanguage(const gzString &language);

	GZ_BASE_EXPORT static gzString getCurrentLanguage();

	GZ_BASE_EXPORT static gzVoid useDefaultTranslator(gzBool on);

private:

	GZ_BASE_EXPORT static gzString	s_currentLanguage;
};

/*! \brief Debug output notification messages

The Gizmo3D system outputs information that can be grouped into different output levels. The user
can set the level of interest as well as catch the output messages with a callback function. The user 
can also set a sender id to notify the recevier about his identity so several code modules can share
the same message presentation output. Most users add a GUI presentation on top of their application so
they can present warnings and fatal messages directly to the application user.
*/

//******************************************************************************
// Class	: gzMessage
//
// Purpose  : Utility class for message dispatching
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	990622	Created 
//									
//******************************************************************************
class gzMessage 
{
public:
	//! Set the global message level. All messages with a "lower" priority level are discarded
	GZ_BASE_EXPORT static gzVoid setMessageLevel(gzMessageLevel level);

	//! Get the global message level.
	/*! \sa setMessageLevel() */
	GZ_BASE_EXPORT static gzMessageLevel getMessageLevel();
	
	//! Adds another message receiver interface. The first interface added replaces the Gizmo3D default message receiver.
	GZ_BASE_EXPORT static gzVoid addMessageReceiver(gzMessageReceiverInterface *foo);

	//! Removes a message receiver. If the last receiver is removed, the Gizmo3D default receiver is added
	GZ_BASE_EXPORT static gzVoid removeMessageReceiver(gzMessageReceiverInterface *foo);

	//! sets a message translator interface.
	GZ_BASE_EXPORT static gzVoid setMessageTranslator(gzMessageTranslatorInterface *foo);
	GZ_BASE_EXPORT static gzMessageTranslatorInterface* getMessageTranslator();
	GZ_BASE_EXPORT static gzString translate(const gzString& user,const gzString &message);
	GZ_BASE_EXPORT static gzVoid setTranslation(const gzString& user,const gzString &language,const gzString &message,const gzString &translation);


	GZ_BASE_EXPORT static gzMessageTranslatorInterface * getDefaultMessageTranslator();

	//! Sends a message from sender at a message level
	GZ_BASE_EXPORT static gzVoid message(const gzString& sender , gzMessageLevel level , const char *fmt , ARG_DECL_LIST );
	GZ_BASE_EXPORT static gzVoid message(gzMessageLevel level , const char *fmt , ARG_DECL_LIST );

	GZ_BASE_EXPORT static gzVoid message(const gzString& sender , gzMessageLevel level , const gzWideChar *fmtWide , ARG_DECL_LIST );
	GZ_BASE_EXPORT static gzVoid message(gzMessageLevel level , const gzWideChar *fmtWide  , ARG_DECL_LIST );

	GZ_BASE_EXPORT static gzMessageReceiverInterface * getDefaultMessageReceiver();

	//! Locks the messaging
	GZ_BASE_EXPORT static gzVoid waitLock();
	GZ_BASE_EXPORT static gzVoid unLock();

private:

	static gzMessageLevel						s_messageLevel;
	static gzList<gzMessageReceiverInterface>	s_messageReceivers;
	static gzMessageTranslatorInterface			*s_messageTranslator;
};

//! Short Macro for message sending e.g. GZMESSAGE(GZ_MESSAGE_DEBUG,"MyDebug");
#define GZMESSAGE	gzMessage::message

//! Short Macro for message translation of GizmoSDK system messages;
#define GZ_TR(__x)	gzMessage::translate("GizmoSDK",__x)

//! Short Macro for message translation of general messages;
#define GZTR(__sender,__x)	gzMessage::translate(__sender,__x)

//******************************************************************************
// Class	: gzProgressInterface
//									
// Purpose  : Handle progress in Gizmo3D 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990622	Created 
//									
//******************************************************************************

//! Virtual interface for gzProgress messages
class  gzProgressInterface 
{
public:

	GZ_BASE_EXPORT gzProgressInterface();

	GZ_BASE_EXPORT virtual ~gzProgressInterface();

	GZ_BASE_EXPORT virtual gzVoid onProgress( gzUByte percent , const char *message );

	GZ_BASE_EXPORT gzVoid activateProgressInterface();

	GZ_BASE_EXPORT gzVoid deactivateProgressInterface();

	GZ_BASE_EXPORT gzVoid routeProgress(gzUByte percent , const char *message);

private:

	gzProgressInterface *m_currentDefaultProgressInterface;

	gzBool	m_hasDefaultInterface:1;

	gzBool	m_threadAware:1;
};

/*! \brief Progress output notification messages

The Gizmo3D system outputs information about progress of certain tasks. E.g loading a database
or calculating normals are typically output from the progress interface. The user can catch these
messages by a callback function per separate threads. E.g you can redirect the loading messages
from a database loading task to a nice window progress meter.

*/

class  gzProgress
{
public:
	//! Set the current Progress Interface Handler
	/*! There is one current progress interface per Thread ID. The return value is a reference pointer to the previous
		interface for the current Thread ID */
	GZ_BASE_EXPORT static gzProgressInterface *setProgressInterface(gzProgressInterface *progress_interface);

	//! Get the current progress interface
	GZ_BASE_EXPORT static gzProgressInterface *getProgressInterface();

	//! Set the default progress interface
	/*! If there is no progress interface define for the current thread, the default progress
		interface is used. There can be only one ! */
	GZ_BASE_EXPORT static gzProgressInterface *setDefaultProgressInterface(gzProgressInterface *progress_interface);

	//! Progress method to send progress messages to other clients.
	/*! The method takes a percent value of 0-100. Use the values 0-99 as a progress value
		of how much progress is done. Use value 100 as a progress value that means that the 
		method is done (100% completed, finished)
		\param percent 0-99 for progress, 100 for done
		\param message Identifier for progress */
	GZ_BASE_EXPORT static gzVoid progress(gzUByte percent , const char *message );

private:

	friend class gzProgressInterface;

	static gzDict<gzUInt32CompareInterface,gzProgressInterface> s_progressInterfaces;
	static gzProgressInterface * s_defaultProgressInterface;

};

#if defined GZ_WINDOWS
	#if _MSC_VER < 1300
		#define GZBREAK {__asm int 3}
	#else  
		#define GZBREAK __debugbreak()
	#endif
#elif defined GZ_UNIX 
	#define GZBREAK ::raise(SIGTRAP)
#else
	#define GZBREAK
#endif

#if defined GZ_WINDOWS
	#if _MSC_VER < 1300
		#define GZBRKTST if(err.getErrorCode()==9999){__asm int 3}else throw;
	#else  
		#define GZBRKTST if(err.getErrorCode()==9999)__debugbreak();else throw;
	#endif
#elif defined GZ_UNIX 
	#define GZBRKTST if(err.getErrorCode()==9999) ::raise(SIGTRAP);else throw;
#else
	#define GZBRKTST
#endif

#define GZ_STOPPER(x)	static gzBool _stopper = x;while (_stopper)gzSleep(100);

#define GZ_VAR_LINE_2(x,y) x##y								// A Line dependant variable
#define GZ_VAR_LINE_1(x,y) GZ_VAR_LINE_2(x,y)
#define GZ_VAR_LINE(x) GZ_VAR_LINE_1(x,__LINE__)

// {} based
#define gzAssert_(test)											gzBool GZ_VAR_LINE(_test_);GZ_VAR_LINE(_test_)=(gzBool)!(test);if(GZ_VAR_LINE(_test_))try{GZMESSAGE(GZ_MESSAGE_ASSERT|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert (%s) at line %ld in file %s",#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}if(GZ_VAR_LINE(_test_))
#define gzAssertText_(test,text)								gzBool GZ_VAR_LINE(_test_);GZ_VAR_LINE(_test_)=(gzBool)!(test);if(GZ_VAR_LINE(_test_))try{GZMESSAGE(GZ_MESSAGE_ASSERT|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert '%s' (%s) at line %ld in file %s",text,#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}if(GZ_VAR_LINE(_test_))

#define gzModuleAssert_(__module,test)							gzBool GZ_VAR_LINE(_test_);GZ_VAR_LINE(_test_)=(gzBool)!(test);if(GZ_VAR_LINE(_test_))try{GZMESSAGE(__module,GZ_MESSAGE_ASSERT|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert (%s) at line %ld in file %s",#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}if(GZ_VAR_LINE(_test_))
#define gzModuleAssertText_(__module,test,text)					gzBool GZ_VAR_LINE(_test_);GZ_VAR_LINE(_test_)=(gzBool)!(test);if(GZ_VAR_LINE(_test_))try{GZMESSAGE(__module,GZ_MESSAGE_ASSERT|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert '%s' (%s) at line %ld in file %s",text,#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}if(GZ_VAR_LINE(_test_))

#define gzLevelAssert_(__level,test)							gzBool GZ_VAR_LINE(_test_);GZ_VAR_LINE(_test_)=(gzBool)!(test);if(GZ_VAR_LINE(_test_))try{GZMESSAGE(__level|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert (%s) at line %ld in file %s",#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}if(GZ_VAR_LINE(_test_))
#define gzLevelAssertText_(__level,test,text)					gzBool GZ_VAR_LINE(_test_);GZ_VAR_LINE(_test_)=(gzBool)!(test);if(GZ_VAR_LINE(_test_))try{GZMESSAGE(__level|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert '%s' (%s) at line %ld in file %s",text,#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}if(GZ_VAR_LINE(_test_))

#define gzModuleLevelAssert_(__module,__level,test)				gzBool GZ_VAR_LINE(_test_);GZ_VAR_LINE(_test_)=(gzBool)!(test);if(GZ_VAR_LINE(_test_))try{GZMESSAGE(__module,__level|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert (%s) at line %ld in file %s",#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}if(GZ_VAR_LINE(_test_))
#define gzModuleLevelAssertText_(__module,__level,test,text)	gzBool GZ_VAR_LINE(_test_);GZ_VAR_LINE(_test_)=(gzBool)!(test);if(GZ_VAR_LINE(_test_))try{GZMESSAGE(__module,__level|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert '%s' (%s) at line %ld in file %s",text,#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}if(GZ_VAR_LINE(_test_))

// Plain
#define gzAssert(test)											try{if(!(test))GZMESSAGE(GZ_MESSAGE_ASSERT|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert (%s) at line %ld in file %s",#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}
#define gzAssertText(test,text)									try{if(!(test))GZMESSAGE(GZ_MESSAGE_ASSERT|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert '%s' (%s) at line %ld in file %s",text,#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}

#define gzModuleAssert(__module,test)							try{if(!(test))GZMESSAGE(__module,GZ_MESSAGE_ASSERT|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert (%s) at line %ld in file %s",#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}
#define gzModuleAssertText(__module,test,text)					try{if(!(test))GZMESSAGE(__module,GZ_MESSAGE_ASSERT|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert '%s' (%s) at line %ld in file %s",text,#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}

#define gzLevelAssert(__level,test)								try{if(!(test))GZMESSAGE(__level|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert (%s) at line %ld in file %s",#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}
#define gzLevelAssertText(__level,test,text)					try{if(!(test))GZMESSAGE(__level|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert '%s' (%s) at line %ld in file %s",text,#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}

#define gzModuleLevelAssert(__module,level,test)				try{if(!(test))GZMESSAGE(__module,level|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert (%s) at line %ld in file %s",#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}
#define gzModuleLevelAssertText(__module,level,test,text)		try{if(!(test))GZMESSAGE(__module,level|GZ_MESSAGE_ENCODING_NO_TRANSLATE,"Assert '%s' (%s) at line %ld in file %s",text,#test,__LINE__,__FILE__);}catch(gzBaseError &err){GZBRKTST}


#ifdef GZ_DEBUG

#define GZ_ERRORTEST											{while(long error=gzGetError())GZTRACE("Graphics error:%ld at line %ld in file %s",error,__LINE__,__FILE__);}
#define GZ_ERRORTEST_STOP										{if(long error=gzGetError()){GZTRACE("Graphics error:%ld at line %ld in file %s",error,__LINE__,__FILE__);while(1);}}
#define GZ_TIMER_START(a)										gzTimer timerCounter_##a(#a);
#define GZ_TIMER_STOP(a,b)										timerCounter_##a.notifyTime(b);

// Asserts

// {} based
#define GZ_ASSERT_(test)										gzAssert_(test)
#define GZ_ASSERT_TEXT_(test,text)								gzAssertText_(test,text)

#define GZ_MODULE_ASSERT_(module,test)							gzModuleAssert_(module,test)
#define GZ_MODULE_ASSERT_TEXT_(module,test,text)				gzModuleAssertText_(module,test,text)

#define GZ_LEVEL_ASSERT_(level,test)							gzLevelAssert_(level,test)
#define GZ_LEVEL_ASSERT_TEXT_(level,test,text)					gzLevelAssertText_(level,test,text)

#define GZ_MODULE_LEVEL_ASSERT_(module,level,test)				gzModuleLevelAssert_(module,level,test)
#define GZ_MODULE_LEVEL_ASSERT_TEXT_(module,level,test,text)	gzModuleLevelAssertText_(module,level,test,text)

// Plain
#define GZ_ASSERT(test)											gzAssert(test)
#define GZ_ASSERT_TEXT(test,text)								gzAssertText(test,text)

#define GZ_MODULE_ASSERT(module,test)							gzModuleAssert(module,test)
#define GZ_MODULE_ASSERT_TEXT(module,test,text)					gzModuleAssertText(module,test,text)

#define GZ_LEVEL_ASSERT(level,test)								gzLevelAssert(level,test)
#define GZ_LEVEL_ASSERT_TEXT(level,test,text)					gzLevelAssertText(level,test,text)

#define GZ_MODULE_LEVEL_ASSERT(module,level,test)				gzModuleLevelAssert(module,level,test)
#define GZ_MODULE_LEVEL_ASSERT_TEXT(module,level,test,text)		gzModuleLevelAssertText(module,level,test,text)

#else

#define GZ_ERRORTEST				;
#define GZ_ERRORTEST_STOP			;
#define GZ_TIMER_START(a)			;
#define GZ_TIMER_STOP(a,b)			;

// {} based
#define GZ_ASSERT_(a)							if(FALSE)
#define GZ_ASSERT_TEXT_(a,b)					if(FALSE)
#define GZ_MODULE_ASSERT_(a,b)					if(FALSE)
#define GZ_MODULE_ASSERT_TEXT_(a,b,c)			if(FALSE)
#define GZ_LEVEL_ASSERT_(a,b)					if(FALSE)
#define GZ_LEVEL_ASSERT_TEXT_(a,b,c)			if(FALSE)
#define GZ_MODULE_LEVEL_ASSERT_(a,b,c)			if(FALSE)
#define GZ_MODULE_LEVEL_ASSERT_TEXT_(a,b,c,d)	if(FALSE)

// Plain
#define GZ_ASSERT(a)							{}
#define GZ_ASSERT_TEXT(a,b)						{}
#define GZ_MODULE_ASSERT(a,b)					{}
#define GZ_MODULE_ASSERT_TEXT(a,b,c)			{}
#define GZ_LEVEL_ASSERT(a,b)					{}
#define GZ_LEVEL_ASSERT_TEXT(a,b,c)				{}
#define GZ_MODULE_LEVEL_ASSERT(a,b,c)			{}
#define GZ_MODULE_LEVEL_ASSERT_TEXT(a,b,c,d)	{}

#endif

// Unimplemented code path macro in debug only
#define GZ_XXX  GZ_ASSERT_TEXT(FALSE,"Unimplemented Code Path")

#define GZ_VAL_OK(x) if(!isfinite(x))GZBREAK;

#endif
