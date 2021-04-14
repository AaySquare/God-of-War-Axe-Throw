// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GodofWarAxeThrow : ModuleRules
{
	public GodofWarAxeThrow(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
