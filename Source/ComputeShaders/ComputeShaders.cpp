#include "ComputeShaders.h"

DEFINE_LOG_CATEGORY(ComputeShaders);

void FComputeShaders::StartupModule()
{
	UE_LOG(ComputeShaders, Warning, TEXT("Compute Shader module has started!"));
}

void FComputeShaders::ShutdownModule()
{
	UE_LOG(ComputeShaders, Warning, TEXT("Compute Shader module has shut down."));
}

IMPLEMENT_MODULE(FComputeShaders, ComputeShaders)