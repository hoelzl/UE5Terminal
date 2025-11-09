// Copyright (c) 2025 Matthias Hölzl. Licensed under the MIT License.

using UnrealBuildTool;

public class Terminal : ModuleRules
{
	public Terminal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG",
				"CommonUI"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"InputCore"
			}
		);
	}
}
