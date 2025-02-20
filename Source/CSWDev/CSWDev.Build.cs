
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
// File			: *.Build.cs
// Module		: CSW StreamingMap Unreal
// Description	: Build Script for Unreal Projects
// Author		: Anders Modén		
// Product		: CSW 1.1.1
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
// AMO	241107	Created file 					(1.1.1)
//
//******************************************************************************

using UnrealBuildTool;

public class CSWDev : ModuleRules
{
   
    public CSWDev(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        bEnableExceptions = true;

        // Decide debug mode here ---------------------------------

        if (Target.Configuration == UnrealTargetConfiguration.Debug ||
            Target.Configuration == UnrealTargetConfiguration.DebugGame ||
            Target.Configuration == UnrealTargetConfiguration.Development)
        {
            //PrivateDefinitions.Add("GZ_DEBUG=1");
        }

       
        // Module Dependancies
        PublicDependencyModuleNames.AddRange(new string[]
        {
             "Core",
             "CoreUObject",
             "CSWPlugin",
             "CSW",
        });

        PrivateDependencyModuleNames.AddRange(new string[] { "Shaders" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
