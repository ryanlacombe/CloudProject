using UnrealBuildTool;

public class ComputeShaders : ModuleRules
{
	public ComputeShaders (ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "CloudProject" } );
		
		PrivateDependencyModuleNames.AddRange(new string[] {});
	}
}