// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BeltScrollAction : ModuleRules
{
	public BeltScrollAction(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"BeltScrollAction",
			"BeltScrollAction/Variant_Platforming",
			"BeltScrollAction/Variant_Platforming/Animation",
			"BeltScrollAction/Variant_Combat",
			"BeltScrollAction/Variant_Combat/AI",
			"BeltScrollAction/Variant_Combat/Animation",
			"BeltScrollAction/Variant_Combat/Gameplay",
			"BeltScrollAction/Variant_Combat/Interfaces",
			"BeltScrollAction/Variant_Combat/UI",
			"BeltScrollAction/Variant_SideScrolling",
			"BeltScrollAction/Variant_SideScrolling/AI",
			"BeltScrollAction/Variant_SideScrolling/Gameplay",
			"BeltScrollAction/Variant_SideScrolling/Interfaces",
			"BeltScrollAction/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
