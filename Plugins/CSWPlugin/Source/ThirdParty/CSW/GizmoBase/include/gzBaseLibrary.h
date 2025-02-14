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
// File			: gzBaseLibrary.h
// Module		: gzBase
// Description	: Management of the base library
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.220
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
// AMO	030423	Created file 	
//
//******************************************************************************
#ifndef __GZ_BASE_LIBRARY_H__
#define __GZ_BASE_LIBRARY_H__


/*!	\file 
	\brief Complete include for all base files. Include 'gzBaseLibrary.h' to get all functions in base included.

*/

#include "gzBasicTypes.h"			// Basic definitions of vars
#include "gzBase.h"					// Strings and utils
#include "gzArithmetic.h"			// Used arithmetics
#include "gzTime.h"					// time management
#include "gzCompress.h"				// Compression and LZH
#include "gzDebug.h"				// Debug , messages, output
#include "gzDynamic.h"				// Dynamic types
#include "gzExceptions.h"
#include "gzHashUtils.h"
#include "gzImage.h"
#include "gzLex.h"
#include "gzLicense.h"
#include "gzMatrix.h"
#include "gzMemory.h"
#include "gzModule.h"
#include "gzMutex.h"
#include "gzNetwork.h"
#include "gzNotify.h"
#include "gzObject.h"
#include "gzReference.h"
#include "gzSerialize.h"
#include "gzService.h"				// Service/Deamon interfaces
#include "gzTemplates.h"			// Reference based templates
#include "gzThread.h"				// Thread and process control
#include "gzType.h"					// Compiler independant type hierarchy
#include "gzPerformance.h"			// Performance and monitoring of data
#include "gzPipe.h"					// Pipes and IPC
#include "gzService.h"				// register a code snippet as a service
#include "gzStackInfo.h"			// Debug and stack trace info
#include "gzXML.h"					// XML Sax and Dom models
#include "gzXYZ.h"					// Def of 3d and 2d paired types (XYZ)
#include "gzSpatial.h"				// Spatial data management
#include "gzMultiSpatial.h"			// Multi Dimensional Spatial data management
#include "gzVideo.h"				// Video image 
#include "gzProtocol.h"				// Ftp, Http etc
#include "gzHalf.h"					// 16 bit float
#include "gzFixed.h"				// 16.16 bit fixed float
#include "gzThreadDeallocator.h"	// Dynamic deallocating
#include "gzSerialPort.h"			// Serial IO
#include "gzGuidStringDict.h"		// Guid Based string lookup
#include "gzHammingSort.h"			// Fast find of hamming distance min
#include "gzDataLogger.h"			// Logging utility
#include "gzInterpreter.h"			// Command line based interpreter
#include "gzTelnet.h"				// Telnet based protocols
#include "gzJson.h"					// Json parser
#include "gzTestAssertManager.h"	// Built in test bridge
#include "gzDistributor.h"			// SW distributor service
#include "gzGooble.h"				// Super large floating point precision

// -------------------------------------- Library version ---------------------------------------------------------------

GZ_BASE_EXPORT gzVoid gzCheckLibraryVersion_base(gzInt32 major=GZ_VERSION_MAJ , gzInt32 minor=GZ_VERSION_MIN , gzInt32 dev=GZ_VERSION_DEV);

GZ_BASE_EXPORT gzLibReference *gzGetLibReference_base();

// Define used library
#if !defined GZBASE_EXPORTS && !defined GZ_IGNORE_LIBDEFS && defined GZ_WINDOWS
#pragma comment( lib, "gzBase" GZ_LIB_EXT ".lib" )
#endif

#endif // __GZ_BASE_LIBRARY_H__






