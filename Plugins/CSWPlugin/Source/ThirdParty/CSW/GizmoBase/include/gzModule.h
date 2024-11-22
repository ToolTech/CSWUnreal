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
// File			: gzModule.h
// Module		: gzBase
// Description	: Class definition of dynamic plugin modules
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.200
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
// AMO	990928	Created file 	
//
//******************************************************************************
#ifndef __GZ_MODULE_H__
#define __GZ_MODULE_H__

#include "gzDynamic.h"
#include "gzNotify.h"
#include "gzLibRef.h"


//! Points out a comma separated user key entry with dynamic modules to load
const gzString GZ_DEFAULT_MODULE_KEY="GIZMO_MODULES";

//! Events for the adding/removing a module
enum gzModuleEvent
{ 
	GZ_MODULE_ADD , 
	GZ_MODULE_REMOVE 
} ;

class gzModule : public gzDynamicInvokeInterface  , public gzDynamicEventInterface , public gzThreadSafeReference
{
public:

	GZ_BASE_EXPORT gzModule();
	GZ_BASE_EXPORT virtual ~gzModule();

	//! derive this to get load (GZ_MODULE_ADD) / unload (GZ_MODULE_REMOVE) events
	GZ_BASE_EXPORT gzVoid virtual onEvent(gzModuleEvent /*event*/){};
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);


	GZ_BASE_EXPORT gzVoid			unLoad();
	GZ_BASE_EXPORT gzString			getClassName();
	GZ_BASE_EXPORT gzString			getModuleName();

	GZ_BASE_EXPORT gzLibReference *	getLibReference();

	GZ_BASE_EXPORT gzReference *	getBaseClassReference() override;

	GZ_THREADSAFE_REF(m_ThreadSafeRefLock);

	//-------------------- global methods ------------------------------------
	
	GZ_BASE_EXPORT static gzModule *	getModule(gzString moduleName,gzBool quietError=FALSE);
	GZ_BASE_EXPORT static gzModule *	getClass(const gzString & className);
	GZ_BASE_EXPORT static gzUInt32		loadModules(const gzString& moduleKey = GZ_DEFAULT_MODULE_KEY, gzBool quietError = FALSE, gzBool add_LibPrefix = FALSE, gzBool add_LibExtension = FALSE,const gzString &start_command=GZ_EMPTY_STRING, GZ_DYNAMIC_ATTRIBUTE_LIST);
	GZ_BASE_EXPORT static gzVoid		unLoadModules();
	GZ_BASE_EXPORT static gzBool		isModuleLoaded(const gzString & moduleName);
	GZ_BASE_EXPORT static gzBool		isClassLoaded(const gzString & className);

	GZ_BASE_EXPORT static gzBool		existModule(const gzString &moduleName);
	
	//! aaa:bbb invoke method bbb in class aaa
	GZ_BASE_EXPORT static gzDynamicType	invokeClassMethod(const gzString &method,GZ_DYNAMIC_ATTRIBUTE_LIST);
	
	GZ_BASE_EXPORT static gzDynamicType	invokeModuleMethod(const gzString &moduleName,const gzString &methodName,GZ_DYNAMIC_ATTRIBUTE_LIST);
	GZ_BASE_EXPORT static gzDynamicType	invokeClassMethodSpec(const gzString &className,const gzString &methodName,GZ_DYNAMIC_ATTRIBUTE_LIST);
	
	GZ_BASE_EXPORT static gzDynamicType	invokeModuleStringParamsMethod(const gzString &moduleName,const gzString &methodName,const gzString &params);
	GZ_BASE_EXPORT static gzDynamicType	invokeClassStringParamsMethod(const gzString &className,const gzString &methodName,const gzString &params);
	
	GZ_BASE_EXPORT static gzDynamicType	invokeModuleAutoTest(const gzString &moduleName);

	GZ_BASE_EXPORT static gzDynamicType	invokeModuleAutoTest(gzModule *module);

	GZ_BASE_EXPORT static gzDynamicType invokeAutoTest();

	// All modules

	GZ_BASE_EXPORT static gzArray<gzString> getLoadedModuleNames();

	// Module Packages

	GZ_BASE_EXPORT static gzBool updateModulePackage(const gzString &url_package, const gzString &moduleName, const gzString &platform,const gzString &url_module,gzBool replace=FALSE);
	GZ_BASE_EXPORT static gzModule * loadModulePackage(gzSerializeAdapter *adapter);

	// External executables
	GZ_BASE_EXPORT static gzBool exec(const gzString &executable,gzBool waitForTermination=FALSE,gzBool quiet=FALSE,gzInt32 *exitCode=nullptr);

	// Static instance register
	GZ_BASE_EXPORT static gzBool registerModuleInstance(gzModule *module,gzString moduleName,gzString className,gzBool initialize);

	GZ_BASE_EXPORT static gzVoid setPrefix(const gzString &prefix);

private:

	gzString						m_className;	
	gzString						m_moduleName;	
	gzMutex							m_ThreadSafeRefLock;
    
    gzBool                          m_isInitialized;

	gzRefPointer<gzLibReference>	m_libRef;

	static gzRefDict<gzString,gzModule>		s_classList;
	static gzRefDict<gzString,gzModule>		s_moduleList;
	static gzMutex							s_moduleLock;
	static gzString							s_prefix;
};

GZ_DECLARE_REFPTR(gzModule);


class gzStaticModuleInitializer
{
public:

	gzStaticModuleInitializer(gzRefPointer<gzModule> &moduleInstance,gzString moduleName,gzString instanceName)
	{
		gzModule::registerModuleInstance(moduleInstance,moduleName,instanceName,FALSE);
        moduleInstance=nullptr;
	}
};

#ifdef GZ_WINDOWS 
#define GZ_MODULE_EXPORT __declspec(dllexport)
#else
#define GZ_MODULE_EXPORT
#endif


#ifndef GZ_STATIC_MODULES

#define GZ_DECLARE_MODULE(x)	GZ_MODULE_EXPORT gzRefPointer<x> gzmoduleinstance=new x;\
								GZ_MODULE_EXPORT gzString gzmoduleinstancename=#x;\
								gzInt32 GZ_CALLBACK DllMain( gzVoid * /*handle*/, gzUInt32 /*reason*/ , gzVoid * /*reserved*/ ){return TRUE;}

#else

#define GZ_DECLARE_MODULE(x)	gzRefPointer<gzModule> gzmoduleinstance_##x=new x;\
								gzStaticModuleInitializer moduleInit_##x=gzStaticModuleInitializer(gzmoduleinstance_##x,#x GZ_LIB_EXT,#x);

#endif // GZ_STATIC_MODULES

// registration macros

// Dummy class initialisation
template<class T> inline gzVoid gzDynamic_Init(T &/*var*/){}
template<> inline gzVoid gzDynamic_Init(gzBool &var){var=FALSE;}
template<> inline gzVoid gzDynamic_Init(gzUInt16 &var){var=0;}
template<> inline gzVoid gzDynamic_Init(gzDouble &var){var=0.0;}

// Built in types
#define GZ_MODULE_PROPERTY_REG(type,name,className)		{registerMethod("get"#name,&className::getDynamicProperty##name);registerMethod("set"#name,&className::setDynamicProperty##name);type val;gzDynamic_Init(val);setArgCheck("set"#name,gzDynamicType(val).getDynamicType());}
#define GZ_MODULE_PROPERTY_REG_SET(type,name,className) {registerMethod("set"#name,&className::setDynamicProperty##name);type val;gzDynamic_Init(val);setArgCheck("set"#name,gzDynamicType(val).getDynamicType());}
#define GZ_MODULE_PROPERTY_REG_GET(type,name,className) {registerMethod("get"#name,&className::getDynamicProperty##name);}

// Custom types
#define GZ_MODULE_PROPERTY_REG_C(type,name,className)		{registerMethod("get"#name,&className::getDynamicProperty##name);registerMethod("set"#name,&className::setDynamicProperty##name);type val;gzDynamic_Init(val);setArgCheck("set"#name,gzDynamicTypeCustom<type>(val).getDynamicType());}
#define GZ_MODULE_PROPERTY_REG_SET_C(type,name,className)	{registerMethod("set"#name,&className::setDynamicProperty##name);type val;gzDynamic_Init(val);setArgCheck("set"#name,gzDynamicTypeCustom<type>(val).getDynamicType());}
#define GZ_MODULE_PROPERTY_REG_GET_C(type,name,className)	{registerMethod("get"#name,&className::getDynamicProperty##name);}

// Built in types with description
#define GZ_MODULE_PROPERTY_REG_DESC(type,name,className,desc)	  {registerMethod("get"#name,&className::getDynamicProperty##name);registerDescription("get"#name,"get:" desc);registerMethod("set"#name,&className::setDynamicProperty##name);registerDescription("set"#name,"set:" desc);type val;gzDynamic_Init(val);setArgCheck("set"#name,gzDynamicType(val).getDynamicType());}
#define GZ_MODULE_PROPERTY_REG_DESC_SET(type,name,className,desc) {registerMethod("set"#name,&className::setDynamicProperty##name);registerDescription("set"#name,"set:" desc);type val;gzDynamic_Init(val);setArgCheck("set"#name,gzDynamicType(val).getDynamicType());}
#define GZ_MODULE_PROPERTY_REG_DESC_GET(type,name,className,desc) {registerMethod("get"#name,&className::getDynamicProperty##name);registerDescription("get"#name,"get:" desc);}

// Custom types with description
#define GZ_MODULE_PROPERTY_REG_DESC_C(type,name,className,desc)		{registerMethod("get"#name,&className::getDynamicProperty##name);registerDescription("get"#name,"get:" desc);registerMethod("set"#name,&className::setDynamicProperty##name);registerDescription("set"#name,"set:" desc);type val;gzDynamic_Init(val);setArgCheck("set"#name,gzDynamicTypeCustom<type>(val).getDynamicType());}
#define GZ_MODULE_PROPERTY_REG_DESC_SET_C(type,name,className,desc)	{registerMethod("set"#name,&className::setDynamicProperty##name);registerDescription("set"#name,"set:" desc);type val;gzDynamic_Init(val);setArgCheck("set"#name,gzDynamicTypeCustom<type>(val).getDynamicType());}
#define GZ_MODULE_PROPERTY_REG_DESC_GET_C(type,name,className,desc)	{registerMethod("get"#name,&className::getDynamicProperty##name);registerDescription("get"#name,"get:" desc);}

// Built in types (properties)
#define GZ_MODULE_PROPERTY(type,name) GZ_PROPERTY(type,name) gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){return m_property##name;} gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E1){m_property##name=gzDynamic_Cast<type>(a0);return GZ_DYN_VOID;}
#define GZ_MODULE_PROPERTY_EXPORT(type,name,exportDef) GZ_PROPERTY_EXPORT(type,name,exportDef) exportDef gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){return m_property##name;} exportDef gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E1){m_property##name=gzDynamic_Cast<type>(a0);return GZ_DYN_VOID;}

#define GZ_MODULE_PROPERTY_FLAGGED(type,name,boolvar) GZ_PROPERTY(type,name) gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){return m_property##name;} gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST){m_property##name=gzDynamic_Cast<type>(a0);boolvar=TRUE;return GZ_DYN_VOID;}
#define GZ_MODULE_PROPERTY_FLAGGED_EXPORT(type,name,boolvar,exportDef) GZ_PROPERTY_EXPORT(type,name,exportDef) exportDef gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){return m_property##name;} exportDef gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E1){m_property##name=gzDynamic_Cast<type>(a0);boolvar=TRUE;return GZ_DYN_VOID;}

#define GZ_MODULE_PROPERTY_MUTEX(type,name,mutex) GZ_PROPERTY_MUTEX(type,name,mutex) gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){GZ_BODYGUARD(mutex);return m_property##name;} gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E1){GZ_BODYGUARD(mutex);m_property##name=gzDynamic_Cast<type>(a0);return GZ_DYN_VOID;}
#define GZ_MODULE_PROPERTY_MUTEX_EXPORT(type,name,mutex,exportDef) GZ_PROPERTY_MUTEX_EXPORT(type,name,mutex,exportDef) exportDef gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){GZ_BODYGUARD(mutex);return m_property##name;} exportDef gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E1){GZ_BODYGUARD(mutex);m_property##name=gzDynamic_Cast<type>(a0);return GZ_DYN_VOID;}

// Custom types (properties)
#define GZ_MODULE_PROPERTY_C(type,name) GZ_PROPERTY(type,name) gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){return gzDynamicTypeCustom<type>(m_property##name);} gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E1){m_property##name=gzDynamic_Cast<type>(a0);return GZ_DYN_VOID;}
#define GZ_MODULE_PROPERTY_EXPORT_C(type,name,exportDef) GZ_PROPERTY_EXPORT(type,name,exportDef) exportDef gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){return gzDynamicTypeCustom<type>(m_property##name);} exportDef gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E1){m_property##name=gzDynamic_Cast<type>(a0);return GZ_DYN_VOID;}

// ------------------ no body, implement in .cpp file ----------------------

#define GZ_MODULE_PROPERTY_(type,name) GZ_PROPERTY_(type,name) gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E); gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E);
#define GZ_MODULE_PROPERTY_EXPORT_(type,name,exportDef) GZ_PROPERTY_EXPORT_(type,name,exportDef) exportDef gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E); exportDef gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E);

// ----------------- SET only ----------------------------------------------

#define GZ_MODULE_PROPERTY_SET(type,name) GZ_PROPERTY_SET(type,name) gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E1){m_property##name=gzDynamic_Cast<type>(a0);return GZ_DYN_VOID;}
#define GZ_MODULE_PROPERTY_SET_EXPORT(type,name,exportDef) GZ_PROPERTY_SET_EXPORT(type,name,exportDef) exportDef gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E1){m_property##name=gzDynamic_Cast<type>(a0);return GZ_DYN_VOID;}

// ------------------ no body, implement in .cpp file ----------------------

#define GZ_MODULE_PROPERTY_SET_(type,name) GZ_PROPERTY_SET_(type,name) gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E);
#define GZ_MODULE_PROPERTY_SET_EXPORT_(type,name,exportDef) GZ_PROPERTY_SET_EXPORT_(type,name,exportDef) exportDef gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTGZ_DYNAMIC_ATTRIBUTE_LIST_IMP_ERIBUTE_LIST);

// !!! No custom types in SET

// ----------------- GET only ----------------------------------------------

#define GZ_MODULE_PROPERTY_GET(type,name) GZ_PROPERTY_GET(type,name) gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){return m_property##name;} 
#define GZ_MODULE_PROPERTY_GET_EXPORT(type,name,exportDef) GZ_PROPERTY_GET_EXPORT(type,name,exportDef) exportDef gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){return m_property##name;} 

#define GZ_MODULE_PROPERTY_GET_(type,name) GZ_PROPERTY_GET_(type,name) gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E); 
#define GZ_MODULE_PROPERTY_GET_EXPORT_(type,name,exportDef) GZ_PROPERTY_GET_EXPORT_(type,name,exportDef) exportDef gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E);

#define GZ_MODULE_PROPERTY_GET_C(type,name) GZ_PROPERTY_GET(type,name) gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){return gzDynamicTypeCustom<type>(m_property##name);} 
#define GZ_MODULE_PROPERTY_GET_EXPORT_C(type,name,exportDef) GZ_PROPERTY_GET_EXPORT(type,name,exportDef) exportDef gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E){return gzDynamicTypeCustom<type>(m_property##name);} 

// ----------------- Interface Methods Only ----------------------------

#define GZ_MODULE_PROPERTY_SET_I(type,name) GZ_PROPERTY_SET_I(type,name) gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E);
#define GZ_MODULE_PROPERTY_SET_EXPORT_I(type,name,exportDef) GZ_PROPERTY_SET_EXPORT_I(type,name,exportDef) exportDef gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E);

#define GZ_MODULE_PROPERTY_GET_I(type,name) GZ_PROPERTY_GET_I(type,name) gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E); 
#define GZ_MODULE_PROPERTY_GET_EXPORT_I(type,name,exportDef) GZ_PROPERTY_GET_EXPORT_I(type,name,exportDef) exportDef gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E);

#define GZ_MODULE_PROPERTY_I(type,name) GZ_PROPERTY_I(type,name) gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E); gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E);
#define GZ_MODULE_PROPERTY_EXPORT_I(type,name,exportDef) GZ_PROPERTY_EXPORT_I(type,name,exportDef) exportDef gzDynamicType getDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E); exportDef gzDynamicType setDynamicProperty##name(GZ_DYNAMIC_ATTRIBUTE_LIST_IMP_E);

// !!! No custom types in Interface Only Methods

#endif

