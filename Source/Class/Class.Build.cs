// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Class : ModuleRules
{
	public Class(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" ,"UMG"}); // UMG�߰�

		//PrivateDependencyModuleNames.AddRange(new string[] {  }); �ּ�ó��

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" }); //�ּ�Ǯ��
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
