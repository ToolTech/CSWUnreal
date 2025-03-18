// *****************************************************************************
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
// File			: gzAssembler.h
// Module		: gzBase
// Description	: Class definition of assembler opcodes.
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.231
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
// AMO	000330	Created file 
//
// ******************************************************************************

/*!	\file 
	\brief Assembler utilities for SIMD,MMX and 3DNow opcodes

Gizmo3D accellerates the WIN32 implementation with 3DNow code on AMD processor systems and
with SIMD,MMX on Intel systems.

*/

#ifndef __GZ_ASSEMBLER_H__
#define __GZ_ASSEMBLER_H__

#include "gzBasicTypes.h"


// ------------------------------------------------------------------------------------
// Assembler enumerations for various HW

typedef enum 
{
    MODEL_UNKNOWN,
    MODEL_AMD,
    MODEL_INTEL,
    MODEL_CYRIX,
    MODEL_CENTAUR
} CPU_MODELS;

typedef enum 
{
    UNKNOWN_CPU,
    AMD_Am486,
    AMD_K5,
    AMD_K6_MMX,
    AMD_K6_2,
    AMD_K6_3,
    AMD_K7,

    INTEL_486DX,
    INTEL_486SX,
    INTEL_486DX2,
    INTEL_486SL,
    INTEL_486SX2,
    INTEL_486DX2E,
    INTEL_486DX4,
    INTEL_Pentium,
    INTEL_Pentium_MMX,
    INTEL_Pentium_Pro,
    INTEL_Pentium_II,
    INTEL_Celeron,
    INTEL_Pentium_III,
	INTEL_Core_I7
} CPU_TYPES;

typedef enum CPUCAPS
{
    // Synthesized values
    CPU_MODEL,      // Manufacturer Model (returns enum CPU_MODELS)
    CPU_TYPE,       // CPU type (return enum CPU_TYPES)

    // Processor Features - returned as boolean values
    HAS_CPUID,      // Supports CPUID instruction
    HAS_FPU,        // FPU present
    HAS_VME,        // Virtual Mode Extensions
    HAS_DEBUG,      // Debug extensions
    HAS_PSE,        // Page Size Extensions
    HAS_TSC,        // Time Stamp Counter
    HAS_MSR,        // Model Specific Registers
    HAS_MCE,        // Machine Check Extensions
    HAS_CMPXCHG8,   // CMPXCHG8 instruction
    HAS_MMX,        // MMX support
    HAS_3DNOW,      // 3DNow! support
    HAS_SSE,		// SSE support
} CPUCAPS;


// Possible assembler accellerated features

GZ_BASE_EXPORT	gzUInt32 GetCPUCaps (CPUCAPS cap);

GZ_BASE_EXPORT	gzVoid		gzMemSet(gzUByte *address,gzUInt32 size,gzUByte value=0);
GZ_BASE_EXPORT	gzUInt64	gzMemBitCompare(gzUInt64 *address_a,gzUInt64 *address_b,gzUInt64 words);
GZ_BASE_EXPORT	gzUInt32	gzMemBitCompare(gzUInt32 *address_a,gzUInt32 *address_b,gzUInt32 words);

#endif
