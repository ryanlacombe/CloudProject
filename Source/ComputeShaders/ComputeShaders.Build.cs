using UnrealBuildTool;

public class ComputeShaders : ModuleRules
{
	public ComputeShaders (ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] 
		{"Core", "CoreUObject", "Engine", "CloudProject", "Renderer", "RenderCore", "RHI", "Projects"} );
		
		PrivateDependencyModuleNames.AddRange(new string[] {});
	}
}