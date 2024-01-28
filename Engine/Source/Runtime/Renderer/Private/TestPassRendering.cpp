#include "TestPassRendering.h"
#include "ScenePrivate.h"
#include "SceneRendering.h"

#include "Shader.h"
#include "GlobalShader.h"
#include "MeshMaterialShader.h"
#include "MeshPassProcessor.h"
#include "MeshPassProcessor.inl"

IMPLEMENT_GLOBAL_SHADER_PARAMETER_STRUCT(FTestPassUniformParameters, "TestPassUniformParametersParams");


class FTestPassVS : public FMeshMaterialShader
{
	DECLARE_SHADER_TYPE(FTestPassVS, MeshMaterial);

	/** Default constructor. */
	FTestPassVS() {}

public:

	FTestPassVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FMeshMaterialShader(Initializer)
	{
		PassUniformBuffer.Bind(Initializer.ParameterMap, FTestPassUniformParameters::StaticStructMetadata.GetShaderVariableName());
	}

	static bool ShouldCompilePermutation(const FMeshMaterialShaderPermutationParameters& Parameters)
	{
		return IsPCPlatform(Parameters.Platform) && Parameters.VertexFactoryType->SupportsPositionOnly();
	}

	void GetShaderBindings(const FScene* Scene, ERHIFeatureLevel::Type FeatureLevel, const FPrimitiveSceneProxy* PrimitiveSceneProxy, const FMaterialRenderProxy& MaterialRenderProxy, const FMaterial& Material, const FMeshPassProcessorRenderState& DrawRenderState, const FMeshMaterialShaderElementData& ShaderElementData, FMeshDrawSingleShaderBindings& ShaderBindings)
	{
		FMeshMaterialShader::GetShaderBindings(Scene, FeatureLevel, PrimitiveSceneProxy, MaterialRenderProxy, Material, DrawRenderState, ShaderElementData, ShaderBindings);
	}

private:

};

class FTestPassPS : public FMeshMaterialShader
{
	DECLARE_SHADER_TYPE(FTestPassPS, MeshMaterial);
public:

	FTestPassPS() { }
	FTestPassPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FMeshMaterialShader(Initializer)
	{
		PassUniformBuffer.Bind(Initializer.ParameterMap, FTestPassUniformParameters::StaticStructMetadata.GetShaderVariableName());
	}

	static bool ShouldCompilePermutation(const FMeshMaterialShaderPermutationParameters& Parameters)
	{
		return IsPCPlatform(Parameters.Platform) && Parameters.VertexFactoryType->SupportsPositionOnly();
	}
	void GetShaderBindings(const FScene* Scene, ERHIFeatureLevel::Type FeatureLevel, const FPrimitiveSceneProxy* PrimitiveSceneProxy, const FMaterialRenderProxy& MaterialRenderProxy, const FMaterial& Material, const FMeshPassProcessorRenderState& DrawRenderState, const FMeshMaterialShaderElementData& ShaderElementData, FMeshDrawSingleShaderBindings& ShaderBindings)
	{
		FMeshMaterialShader::GetShaderBindings(Scene, FeatureLevel, PrimitiveSceneProxy, MaterialRenderProxy, Material, DrawRenderState, ShaderElementData, ShaderBindings);
	}
	/** The parameter to use for setting the draw Color. */
	//FShaderParameter ColorParameter;
};

IMPLEMENT_MATERIAL_SHADER_TYPE(, FTestPassVS, TEXT("/Engine/Private/TestPass.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_MATERIAL_SHADER_TYPE(, FTestPassPS, TEXT("/Engine/Private/TestPass.usf"), TEXT("MainPS"), SF_Pixel);
IMPLEMENT_SHADERPIPELINE_TYPE_VSPS(TestPassPipeline, FTestPassVS, FTestPassPS, true);

FTestPassProcessor::FTestPassProcessor(
	const FScene* Scene,
	const FSceneView* InViewIfDynamicMeshCommand,
	const FMeshPassProcessorRenderState& InPassDrawRenderState,
	const bool InbRespectUseAsOccluderFlag,
	const bool InbEarlyZPassMoveabe,
	FMeshPassDrawListContext* InDrawListContext
)
	:FMeshPassProcessor(
		Scene
		, Scene->GetFeatureLevel()
		, InViewIfDynamicMeshCommand
		, InDrawListContext
	)
	, bRespectUseAsOccluderFlag(InbRespectUseAsOccluderFlag)
	, bEarlyZPassMoveable(InbEarlyZPassMoveabe)
{
	PassDrawRenderState = InPassDrawRenderState;
	// UniformBuffer准备
	// ViewUniformBuffer 主要包含了一些Render时需要的变换矩阵
	PassDrawRenderState.SetViewUniformBuffer(Scene->UniformBuffers.ViewUniformBuffer);
	PassDrawRenderState.SetInstancedViewUniformBuffer(Scene->UniformBuffers.InstancedViewUniformBuffer);
}

void FTestPassProcessor::AddMeshBatch(const FMeshBatch& RESTRICT MeshBatch, uint64 BatchElementMask, const FPrimitiveSceneProxy* RESTRICT PrimitiveSceneProxy, int32 StaticMeshId)
{
	const FMaterialRenderProxy* FallbackMaterialRenderProxyPtr = nullptr;
	const FMaterial& Material = MeshBatch.MaterialRenderProxy->GetMaterialWithFallback(Scene->GetFeatureLevel(), FallbackMaterialRenderProxyPtr);
	const FMaterialRenderProxy& MaterialRenderProxy = FallbackMaterialRenderProxyPtr ? *FallbackMaterialRenderProxyPtr : *MeshBatch.MaterialRenderProxy;

	const EBlendMode BlendMode = Material.GetBlendMode();
	const bool bIsTranslucent = IsTranslucentBlendMode(BlendMode);

	if (
		!bIsTranslucent
		&& (!PrimitiveSceneProxy || PrimitiveSceneProxy->ShouldRenderInMainPass())
		&& ShouldIncludeDomainInMeshPass(Material.GetMaterialDomain())
		)
	{
		if (BlendMode == BLEND_Opaque)
		{
			//const FMaterialRenderProxy& DefualtProxy = *UMaterial::GetDefaultMaterial(MD_Surface)->GetRenderProxy();
			//const FMaterial& DefaltMaterial = *DefualtProxy.GetMaterial(Scene->GetFeatureLevel());

			Process(
				MeshBatch,
				BatchElementMask,
				StaticMeshId,
				PrimitiveSceneProxy,
				MaterialRenderProxy,
				Material
			);
		}
	}

}


static FORCEINLINE bool UseShaderPipelines(ERHIFeatureLevel::Type InFeatureLevel)
{
	static const auto* CVar = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.ShaderPipelines"));
	return RHISupportsShaderPipelines(GShaderPlatformForFeatureLevel[InFeatureLevel]) && CVar && CVar->GetValueOnAnyThread() != 0;
}

bool _UseShaderPipelines()
{
	static const auto* CVar = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.ShaderPipelines"));
	return CVar && CVar->GetValueOnAnyThread() != 0;
}

void GetTestPassShaders(
	const FMaterial& material,
	FVertexFactoryType* VertexFactoryType,
	ERHIFeatureLevel::Type FeatureLevel,
	TShaderRef<FBaseHS>& HullShader,
	TShaderRef<FBaseDS>& DomainShader,
	TShaderRef<FTestPassVS>& VertexShader,
	TShaderRef<FTestPassPS>& PixleShader,
	FShaderPipelineRef& ShaderPipeline 
)
{
	//bool bUsedShaderPipeline = _UseShaderPipelines();
	//if (bUsedShaderPipeline)
	//{
	//	ShaderPipeline = material.GetShaderPipeline(&TestPassPipeline, VertexFactoryType);
	//}
	//else
	//{
	//	ShaderPipeline = FShaderPipelineRef();
	//}
	//// ShaderPipeline = _UseShaderPipelines() ? material.GetShaderPipeline(&TestPassPipeline, VertexFactoryType) : FShaderPipelineRef();

	//VertexShader = ShaderPipeline.IsValid() ? ShaderPipeline.GetShader<FTestPassVS>() : material.GetShader<FTestPassVS>(VertexFactoryType);
	//PixleShader = ShaderPipeline.IsValid() ? ShaderPipeline.GetShader<FTestPassPS>() : material.GetShader<FTestPassPS>(VertexFactoryType);
}

void FTestPassProcessor::Process(
	const FMeshBatch& MeshBatch,
	uint64 BatchElementMask,
	int32 StaticMeshId,
	const FPrimitiveSceneProxy* RESTRICT PrimitiveSceneProxy,
	const FMaterialRenderProxy& RESTRICT MaterialRenderProxy,
	const FMaterial& RESTRICT MaterialResource
)
{
	const FVertexFactory* VertexFactory = MeshBatch.VertexFactory;

	TMeshProcessorShaders<
		FTestPassVS,
		FBaseHS,
		FBaseDS,
		FTestPassPS
	>MyPassShaders;

	FShaderPipelineRef ShaderPipeline;

	/*GetTestPassShaders(
		MaterialResource,
		VertexFactory->GetType(),
		FeatureLevel,
		MyPassShaders.HullShader,
		MyPassShaders.DomainShader,
		MyPassShaders.VertexShader,
		MyPassShaders.PixelShader,
		ShaderPipeline
	);*/
	bool bUsedShaderPipeline = _UseShaderPipelines();
	if (bUsedShaderPipeline)
	{
		ShaderPipeline = MaterialResource.GetShaderPipeline(&TestPassPipeline, VertexFactory->GetType());
	}
	else
	{
		ShaderPipeline = FShaderPipelineRef();
	}
	// ShaderPipeline = _UseShaderPipelines() ? material.GetShaderPipeline(&TestPassPipeline, VertexFactoryType) : FShaderPipelineRef();

	MyPassShaders.VertexShader = ShaderPipeline.IsValid() ? ShaderPipeline.GetShader<FTestPassVS>() : MaterialResource.GetShader<FTestPassVS>(VertexFactory->GetType());
	MyPassShaders.PixelShader = ShaderPipeline.IsValid() ? ShaderPipeline.GetShader<FTestPassPS>() : MaterialResource.GetShader<FTestPassPS>(VertexFactory->GetType());

	const FMeshDrawingPolicyOverrideSettings OverrideSettings = ComputeMeshOverrideSettings(MeshBatch);
	const ERasterizerFillMode MeshFillMode = ComputeMeshFillMode(MeshBatch, MaterialResource, OverrideSettings);
	const ERasterizerCullMode MeshCullMode = ComputeMeshCullMode(MeshBatch, MaterialResource, OverrideSettings);

	// 初始化Shader的材质数据
	FMeshMaterialShaderElementData ShaderElementData;
	ShaderElementData.InitializeMeshMaterialData(ViewIfDynamicMeshCommand, PrimitiveSceneProxy, MeshBatch, StaticMeshId, true);
	// 处理排序键值。
	const FMeshDrawCommandSortKey SortKey = CalculateMeshStaticSortKey(MyPassShaders.VertexShader, MyPassShaders.PixelShader);

	BuildMeshDrawCommands(
		MeshBatch,
		BatchElementMask,
		PrimitiveSceneProxy,
		MaterialRenderProxy,
		MaterialResource,
		PassDrawRenderState,
		MyPassShaders,
		MeshFillMode,
		MeshCullMode,
		SortKey,
		EMeshPassFeatures::PositionOnly,
		ShaderElementData
	);


}


// 向引擎的全局manager注册我们添加的MeshDrawProcessor
FMeshPassProcessor* CreateTestPassProcessor(
	const FScene* Scene,
	const FSceneView* InViewIfDynamicMeshCommand,
	FMeshPassDrawListContext* InDrawListContext
)
{
	// 渲染状态处理。
	FMeshPassProcessorRenderState TestPassState(Scene->UniformBuffers.ViewUniformBuffer);
	TestPassState.SetInstancedViewUniformBuffer(Scene->UniformBuffers.InstancedViewUniformBuffer);
	TestPassState.SetBlendState(TStaticBlendStateWriteMask<CW_RGBA>::GetRHI());
	TestPassState.SetDepthStencilAccess(Scene->DefaultBasePassDepthStencilAccess);
	TestPassState.SetDepthStencilState(TStaticDepthStencilState<true, CF_DepthNearOrEqual>::GetRHI());

	return new(FMemStack::Get()) FTestPassProcessor(
		Scene,
		InViewIfDynamicMeshCommand,
		TestPassState,
		true,
		Scene->bEarlyZPassMovable,
		InDrawListContext
	);
}

FRegisterPassProcessorCreateFunction RegisterTestPass(
	&CreateTestPassProcessor,
	EShadingPath::Deferred,
	EMeshPass::TestPass,
	EMeshPassFlags::CachedMeshCommands | EMeshPassFlags::MainView
);