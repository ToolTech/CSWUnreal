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
// File			: CSW.Build.cs
// Module		: CSW Native Unreal
// Description	: Build Script for CSW/GizmoSDK Native Libs
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
// AMO	241112	Created file 							(1.1.1)
//
//******************************************************************************

using System.IO;
using UnrealBuildTool;

public class CSW : ModuleRules
{
    string _libPath;
    string _buildExt;
    string _buildPrefix;
    string _dynExt;
    string _libExt;

    private void AddImportLib(string Component, string libName)
    {
        // Right now we build source code with unreal project
        string componentLibPath = Path.Combine("$(PluginDir)/Source/ThirdParty/CSW" ,Component,"libs",_libPath);

        // Add the import library    
        PublicAdditionalLibraries.Add(Path.Combine(componentLibPath, _buildPrefix + libName + _buildExt + _libExt));
        // Add the shared library
        RuntimeDependencies.Add("$(BinaryOutputDir)/" + _buildPrefix + libName + _buildExt + _dynExt, Path.Combine( componentLibPath , _buildPrefix + libName + _buildExt + _dynExt), StagedFileType.NonUFS);
    }

    private void SetupWindows64(bool debug)
    {
        _buildExt = debug ? "64_d" : "64";
        _libPath = "windows/x64";
        _dynExt = ".dll";
        _libExt = ".lib";
        _buildPrefix = "";
    }

    private void SetupAndroidARM64(bool debug)
    {
        _buildExt = debug ? "64-g" : "64";
        _libPath = "android/ARM64";
        _dynExt = ".so";
        _libExt = ".lib";
        _buildPrefix = "";
    }

    public CSW(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		PublicSystemIncludePaths.Add("$(ModuleDir)/GizmoBase/include");
        PublicSystemIncludePaths.Add("$(ModuleDir)/Gizmo3D/include");
        PublicSystemIncludePaths.Add("$(ModuleDir)/Coordinate/include");
        PublicSystemIncludePaths.Add("$(ModuleDir)/SceneManager/include");

        bool debugMode = false;

        // Decide debug mode here ---------------------------------

        if (Target.Configuration == UnrealTargetConfiguration.Debug ||
            Target.Configuration == UnrealTargetConfiguration.DebugGame ||
            Target.Configuration == UnrealTargetConfiguration.Development)
        {
            debugMode = true;
            PrivateDefinitions.Add("GZ_DEBUG=1");
        }

        // Add more platforms here -------------------------------

        if (Target.Platform == UnrealTargetPlatform.Win64)
            SetupWindows64(debugMode);
        else if (Target.Platform == UnrealTargetPlatform.Android)
            SetupAndroidARM64(debugMode);
        else
            throw new BuildException("CSW Unsupported Platform");

        // Possibly extend libPath here -------------------------

        _libPath = Path.Combine(_libPath, debugMode ? "debug" : "release");


        if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			//PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "ExampleLibrary.lib"));

			// Delay-load the DLL, so we can load it from the right place first
			//PublicDelayLoadDLLs.Add("ExampleLibrary.dll");

			// Ensure that the DLL is staged along with the executable
			//RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/StreamingMapLibrary/Win64/ExampleLibrary.dll");
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			//PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libExampleLibrary.dylib"));
			//RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/StreamingMapLibrary/Mac/Release/libExampleLibrary.dylib");
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			//string ExampleSoPath = Path.Combine("$(PluginDir)", "Binaries", "ThirdParty", "StreamingMapLibrary", "Linux", "x86_64-unknown-linux-gnu", "libExampleLibrary.so");
			//PublicAdditionalLibraries.Add(ExampleSoPath);
			//PublicDelayLoadDLLs.Add(ExampleSoPath);
			//RuntimeDependencies.Add(ExampleSoPath);
		}

        // Add the import libraries -----------------------
        
        AddImportLib("GizmoBase","gzBase");                 // GizmoBase libs

        AddImportLib("Gizmo3D", "gzGraph");                 // Gizmo3D
        AddImportLib("Gizmo3D", "gzImage");
        AddImportLib("Gizmo3D", "gzDB");
        AddImportLib("Gizmo3D", "gzSystem");

        AddImportLib("Coordinate", "gzCoordinate");         // Plugin

        AddImportLib("SceneManager", "cswSceneManager");    // CSW SceneManager libs
    }
}
