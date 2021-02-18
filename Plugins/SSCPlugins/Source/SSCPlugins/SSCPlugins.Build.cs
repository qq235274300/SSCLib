// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;



public class SSCPlugins : ModuleRules
{
	public SSCPlugins(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
      //  PrivatePCHHeaderFile = "Public/MultiViews.h";  private head file 
        PublicIncludePaths.AddRange(
			new string[] {
               // "SSCPlugins/Public",
            }
			);
        //string EnginePath = Path.GetFullPath(Target.RelativeEnginePath);
      //  string PrivateBSD = EnginePath + "Source/Runtime/Sockets/Private";


        PrivateIncludePaths.AddRange(
			new string[] {
                "SSCPlugins",
                "SSCPlugins/Private",
                "SSCPlugins/Public",
                "SSCPlugins/Public/SSCCommon",
                "SSCPlugins/Private/SSCCommon",
                "SSCPlugins/Public/SSCCore",
                "SSCPlugins/Private/SSCCore",
                "SSCPlugins/Public/SSCGame",
                "SSCPlugins/Private/SSCGame",
                "SSCPlugins/Public/SSCObject",
                "SSCPlugins/Private/SSCObject",
                "SSCPlugins/Public/SSCTest",
                "SSCPlugins/Private/SSCTest",
                 "SSCPlugins/SSCInventory/Public",
                "SSCPlugins/SSCInventory/Private",
                 "SSCPlugins/SimpleGizmo/Public",
                "SSCPlugins/SimpleGizmo/Private",
                "SSCPlugins/VisualCustomWidget/Public",
                "SSCPlugins/VisualCustomWidget/Private",
                "SSCPlugins/MultiViewPort/Public",
                "SSCPlugins/MultiViewPort/Private",
                 "SSCPlugins/RunTimeCamera/Public",
                "SSCPlugins/RunTimeCamera/Private",
                 "SSCPlugins/CommandShop/Public",
                "SSCPlugins/CommandShop/Private",
            }
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
                "Engine"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "UMG",
                "InputCore",
                "XmlParser",
                "Sockets",
                "Json",
                "Http",
                "JsonUtilities",
                "MoviePlayer",
                "AIModule",
                "GameplayTasks",
                "HeadMountedDisplay",
                "ProceduralMeshComponent",
               

               
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
