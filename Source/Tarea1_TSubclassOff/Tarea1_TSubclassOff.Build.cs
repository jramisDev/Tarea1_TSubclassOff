// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tarea1_TSubclassOff : ModuleRules
{
	public Tarea1_TSubclassOff(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
