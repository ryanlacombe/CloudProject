#include "ShadersDeclarations.h"
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
#include "RenderGraphUtils.h"
#include "RenderTargetPool.h"
#include "Modules/ModuleManager.h"

#define NUM_THREADS_PER_GROUP_DIMENSION 32

//Internal class to hold parameters and connect HLSL Shader to engine
class FCloudShader : public FGlobalShader
{
public:

	//declare class as Global Shader
	DECLARE_GLOBAL_SHADER(FCloudShader);

	//Tells engine shader uses a struct for parameters
	SHADER_USE_PARAMETER_STRUCT(FCloudShader, FGlobalShader);

	//Delcaration of Parameter Struct
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_UAV(RWTexture2D<float>, OutputTexture)
		SHADER_PARAMETER(FVector2D, Dimensions)
		SHADER_PARAMETER(UINT, TimeStamp)
	END_SHADER_PARAMETER_STRUCT()

	//Called by engine to detere how to compile for this shader
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}

	//Modifies compilations enviroment of shader
	static inline void ModifyCompilationEnviroment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEniviroment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEniviroment);

		OutEniviroment.SetDefine(TEXT("THREADGROUPSIZE_X"), NUM_THREADS_PER_GROUP_DIMENSION);
		OutEniviroment.SetDefine(TEXT("THREADGROUPSIZE_Y"), NUM_THREADS_PER_GROUP_DIMENSION);
		OutEniviroment.SetDefine(TEXT("THREADGROUPSIZE_Z"), 1);
	}
};

//Will tell engine to create shader and where it is
IMPLEMENT_GLOBAL_SHADER(FCloudShader, "/CustomShaders/Private/CloudShader.usf", "MainComputeShader", SF_Compute);

//Static members
FCloudShaderManager* FCloudShaderManager::instance = nullptr;

//Begin execution of Compute Shader each frame
void FCloudShaderManager::BeginRendering()
{
	//If handle is intialized and valid, don't do anything
	if (OnPostResolvedSceneColorHandle.IsValid())
	{
		return;
	}
	bCachedParamsAreValid = false;

	//Get Renderer Module and add entry to callbacks to be executed each frame
	const FName RendererModuleName("Renderer");
	IRendererModule* RendererModule = FModuleManager::GetModulePtr<IRendererModule>(RendererModuleName);
	if (RendererModule)
	{
		OnPostResolvedSceneColorHandle = RendererModule->GetResolvedSceneColorCallbacks().AddRaw(this, &FCloudShaderManager::Execute_RenderThread);
	}
}

//Stop Compute Shader execution
void FCloudShaderManager::EndRendering()
{
	//If handle is not valid, do nothing
	if (!OnPostResolvedSceneColorHandle.IsValid())
	{
		return;
	}

	//Get Renderer module and remove entry from ResolvedSceneColorCallbacks
	const FName RendererModuleName("Renderer");
	IRendererModule* RendererModule = FModuleManager::GetModulePtr<IRendererModule>(RendererModuleName);
	if (RendererModule)
	{
		RendererModule->GetResolvedSceneColorCallbacks().Remove(OnPostResolvedSceneColorHandle);
	}

	OnPostResolvedSceneColorHandle.Reset();
}

//Update parameters by providing instance of Parameters Struct
void FCloudShaderManager::UpdateParameters(FCloudShaderParameters& params)
{
	cachedParams = params;
	bCachedParamsAreValid = true;
}

//Cretes instance of Shader type Parameter Struct and fills it
void FCloudShaderManager::Execute_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneRenderTargets& SceneContext)
{
	//If there's no cached parameters and Render Target, do nothing
	if (!(bCachedParamsAreValid && cachedParams.RenderTarget))
	{
		return;
	}

	//Render Thread assertion
	check(IsInRenderingThread());

	//If Render Target is not vaild, get element from Render Target Pool
	if (!ComputeShaderOutput.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not valid"));
		FPooledRenderTargetDesc ComputeShaderOutputDesc(FPooledRenderTargetDesc::Create2DDesc(cachedParams.GetRedngerTargetSize(), cachedParams.RenderTarget->GetRenderTargetResource()->TextureRHI->GetFormat(),
			FClearValueBinding::None, TexCreate_None, TexCreate_ShaderResource | TexCreate_UAV, false));
		ComputeShaderOutputDesc.DebugName = TEXT("CloudShader_Output_RenderTarget");
		GRenderTargetPool.FindFreeElement(RHICmdList, ComputeShaderOutputDesc, ComputeShaderOutput, TEXT("CloudShader_Output_RenderTarget"));
	}

	//Unbind previously bound Render Targets
	UnbindRenderTargets(RHICmdList);

	//Specify resource transition
	RHICmdList.TransitionResource(EResourceTransitionAccess::ERWBarrier, EResourceTransitionPipeline::EGfxToCompute, ComputeShaderOutput->GetRenderTargetItem().UAV);

	//Fill Shader Parameters Struct with chached data supplied by client
	FCloudShader::FParameters PassParamaters;
	PassParamaters.OutputTexture = ComputeShaderOutput->GetRenderTargetItem().UAV;
	PassParamaters.Dimensions = FVector2D(cachedParams.GetRedngerTargetSize().X, cachedParams.GetRedngerTargetSize().Y);
	PassParamaters.TimeStamp = cachedParams.TimeStamp;

	//Get reference to Shder Type from Global Shader
	TShaderMapRef<FCloudShader> cloudShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	//Dsipatch Compute Shader
	FComputeShaderUtils::Dispatch(RHICmdList, cloudShader, PassParamaters,
		FIntVector(FMath::DivideAndRoundUp(cachedParams.GetRedngerTargetSize().X, NUM_THREADS_PER_GROUP_DIMENSION),
			FMath::DivideAndRoundUp(cachedParams.GetRedngerTargetSize().Y, NUM_THREADS_PER_GROUP_DIMENSION), 1));

	//Copy Shhader's output to Render target
	RHICmdList.CopyTexture(ComputeShaderOutput->GetRenderTargetItem().ShaderResourceTexture, cachedParams.RenderTarget->GetRenderTargetResource()->TextureRHI, FRHICopyTextureInfo());
}
