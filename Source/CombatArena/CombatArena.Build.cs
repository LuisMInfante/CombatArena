// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CombatArena : ModuleRules
{
	public CombatArena(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", 
			"InputCore", "EnhancedInput", "Niagara", "Slate", "MultiplayerSessions", "OnlineSubsystem",
			"OnlineSubsystemSteam", "UMG", "GameplayAbilities" });
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTasks", "GameplayTags" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
