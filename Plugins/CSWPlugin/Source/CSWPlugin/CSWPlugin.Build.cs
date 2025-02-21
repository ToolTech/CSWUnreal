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
// File			: StreamingMap.Build.cs
// Module		: CSW StreamingMap Unreal
// Description	: Build Script for StreamingMap
// Author		: Anders Modén		
// Product		: CSW 1.1.2
//		
//
//			
// NOTE:	CSW (Common Synthetic World) is a simulation and presentation
//			framework for large scale digital twins on multiple platforms
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	241112	Created file 							(1.1.1)
//
//******************************************************************************

using System.Collections.Generic;
using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class CSWPlugin : ModuleRules
{
	public CSWPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // Decide debug mode here ---------------------------------

        if (Target.Configuration == UnrealTargetConfiguration.Debug 
            || Target.Configuration == UnrealTargetConfiguration.DebugGame 
			//|| Target.Configuration == UnrealTargetConfiguration.Development
			)
        {
           PrivateDefinitions.Add("GZ_DEBUG");
        }

		// Performance instrumentation ?
        //PrivateDefinitions.Add("GZ_INSTRUMENT_CODE");

        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
                //"InputCore",
				
                "MeshDescription",
				//"RenderCore",
				//"RHI",
				"StaticMeshDescription",
				//"PhysicsCore",
                "CSW",
				"Projects",				// Plugins
				"MeshConversion",
                // ... add other public dependencies that you statically link with here ...
				     
            }
			);

		if (Target.bBuildEditor)
		{
			PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"UnrealEd",             // for GEditor
			});
		}


        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
