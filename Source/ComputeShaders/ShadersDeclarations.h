// Fill out your copyright notice in the Description page of Project Settings.

//#pragma once
//
//#include "CoreMinimal.h"
//#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"
//
//
////Struct acts as a container for the parameters to be passed to the Compute Shader Manager
//struct FCloudShaderParameters
//{
//	UTextureRenderTarget2D* RenderTarget;
//
//	FIntPoint GetRenderTargetSize() const
//	{
//		return CachedRenderTargetSize;
//	}
//
//	FCloudShaderParameters() {}
//	FCloudShaderParameters(UTextureRenderTarget2D* IORenderTarget) : RenderTarget(IORenderTarget)
//	{
//		CachedRenderTargetSize = RenderTarget ? FIntPoint(RenderTarget->SizeX, RenderTarget->SizeY) : FIntPoint::ZeroValue;
//	}
//
//public:
//	uint32 TimeStamp;
//
//private:
//	FIntPoint CachedRenderTargetSize;
//};
//
////Shader Manager for the Shader Type
//class COMPUTESHADERS_API FCloudShaderManager
//{
//public:
//
//	//Gets the instance
//	static FCloudShaderManager* Get()
//	{
//		if (!instance)
//		{
//			instance = new FCloudShaderManager();
//		}
//
//		return instance;		
//	};
//
//	//Call when hooking onto renderer and start exexuting the Compute Shader
//	void BeginRendering();
//
//	//Stops Compute Shader execution
//	void EndRendering();
//
//	//Call when new parameters to share
//	void UpdateParameters(FCloudShaderParameters& DrawParameters);
//
//	//Grabs the Render thread
//	void Execute_RenderThread(FRHICommandListImmediate& RHICmdList, class FSceneRenderTargets& SceneContext);
//
//private:
//
//	//Private constructor to prevent client instanciating
//	FCloudShaderManager() = default;
//
//	//Single instance
//	static FCloudShaderManager* instance;
//
//	//Delegate Handle to function that will execute eaxh frame by the Renderer
//	FDelegateHandle OnPostResolvedSceneColorHandle;
//
//	//Cached Shader Manager Parameters
//	FCloudShaderParameters cachedParams;
//
//	//Checks if there is cached parameters to pass to shader
//	volatile bool bCachedParamsAreValid;
//
//	//Reference to pooled render target where shader will write output
//	TRefCountPtr<IPooledRenderTarget> ComputeShaderOutput;
//};
