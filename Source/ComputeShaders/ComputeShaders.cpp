#include "ComputeShaders.h"
#include "Modules/ModuleManager.h"
#include "Misc/Paths.h"
#include "GlobalShader.h"
#include "Containers/UnrealString.h"

//DEFINE_LOG_CATEGORY(ComputeShaders);

void FComputeShaders::StartupModule()
{
	//UE_LOG(ComputeShaders, Warning, TEXT("Compute Shader module has started!"));
	
	//Finds the shaders directory for use
	FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("CustomShaders/Private"));
	AddShaderSourceDirectoryMapping("/CustomShaders", ShaderDirectory);
}

void FComputeShaders::ShutdownModule()
{
	//UE_LOG(ComputeShaders, Warning, TEXT("Compute Shader module has shut down."));

	ResetAllShaderSourceDirectoryMappings();
}

IMPLEMENT_MODULE(FComputeShaders, ComputeShaders);