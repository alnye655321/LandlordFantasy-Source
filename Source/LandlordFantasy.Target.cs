// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class LandlordFantasyTarget : TargetRules
{
	public LandlordFantasyTarget(TargetInfo Target) : base(Target)
	{
        //bUseLoggingInShipping = true;
        Type = TargetType.Game;
        ExtraModuleNames.AddRange(new string[] { "LandlordFantasy" });
		//bUsePCHFiles = false;
		//bUseUnityBuild = false;
    }

	//
	// TargetRules interface.
	//

	/*public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "LandlordFantasy" } );
	}*/
}
