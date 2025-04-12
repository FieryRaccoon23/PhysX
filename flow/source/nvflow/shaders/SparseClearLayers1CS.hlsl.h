#include "SparseClearLayers1CS_vulkan.hlsl.h"
#include "SparseClearLayers1CS_d3d12.hlsl.h"

struct SparseClearLayers1CS_Pipeline
{
	NvFlowContextInterface* contextInterface;
	NvFlowComputePipeline* pipeline;
};

inline void SparseClearLayers1CS_init(NvFlowContextInterface* contextInterface, NvFlowContext* context, SparseClearLayers1CS_Pipeline* ptr)
{
	ptr->contextInterface = contextInterface;
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowBindingDesc bindingDescs[4] = {};
	NvFlowComputePipelineDesc desc = {};
	if (config.api == eNvFlowContextApi_vulkan)
	{
		bindingDescs[0].type = eNvFlowDescriptorType_constantBuffer;
		bindingDescs[0].bindingDesc.vulkan.binding = 0;
		bindingDescs[0].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[0].bindingDesc.vulkan.set = 0;

		bindingDescs[1].type = eNvFlowDescriptorType_structuredBuffer;
		bindingDescs[1].bindingDesc.vulkan.binding = 1;
		bindingDescs[1].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[1].bindingDesc.vulkan.set = 0;

		bindingDescs[2].type = eNvFlowDescriptorType_structuredBuffer;
		bindingDescs[2].bindingDesc.vulkan.binding = 2;
		bindingDescs[2].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[2].bindingDesc.vulkan.set = 0;

		bindingDescs[3].type = eNvFlowDescriptorType_rwTexture;
		bindingDescs[3].bindingDesc.vulkan.binding = 3;
		bindingDescs[3].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[3].bindingDesc.vulkan.set = 0;

		desc.numBindingDescs = 4;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SparseClearLayers1CS_vulkan_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SparseClearLayers1CS_vulkan_hlsl);
	}
	if (config.api == eNvFlowContextApi_d3d12)
	{
		bindingDescs[0].type = eNvFlowDescriptorType_constantBuffer;
		bindingDescs[0].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_b;
		bindingDescs[0].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[0].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[0].bindingDesc.d3d12.space = 0;

		bindingDescs[1].type = eNvFlowDescriptorType_structuredBuffer;
		bindingDescs[1].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		bindingDescs[1].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[1].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[1].bindingDesc.d3d12.space = 0;

		bindingDescs[2].type = eNvFlowDescriptorType_structuredBuffer;
		bindingDescs[2].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		bindingDescs[2].bindingDesc.d3d12.registerBegin = 1;
		bindingDescs[2].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[2].bindingDesc.d3d12.space = 0;

		bindingDescs[3].type = eNvFlowDescriptorType_rwTexture;
		bindingDescs[3].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[3].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[3].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[3].bindingDesc.d3d12.space = 0;

		desc.numBindingDescs = 4;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SparseClearLayers1CS_d3d12_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SparseClearLayers1CS_d3d12_hlsl);
	}
	ptr->pipeline = ptr->contextInterface->createComputePipeline(context, &desc);
};

inline void SparseClearLayers1CS_destroy(NvFlowContext* context, SparseClearLayers1CS_Pipeline* ptr)
{
	ptr->contextInterface->destroyComputePipeline(context, ptr->pipeline);
}

struct SparseClearLayers1CS_PassParams
{
	NvFlowBufferTransient* globalParamsIn;
	NvFlowBufferTransient* layerParamsIn;
	NvFlowBufferTransient* gTable;
	NvFlowTextureTransient* valueOut;
};

inline void SparseClearLayers1CS_addPassCompute(NvFlowContext* context, SparseClearLayers1CS_Pipeline* ptr, NvFlowUint3 gridDim, const SparseClearLayers1CS_PassParams* params)
{
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowDescriptorWrite descriptorWrites[4] = {};
	NvFlowResource resources[4] = {};
	NvFlowPassComputeParams passComputeParams = {};
	passComputeParams.pipeline = ptr->pipeline;
	passComputeParams.gridDim = gridDim;
	if (config.api == eNvFlowContextApi_vulkan)
	{
		descriptorWrites[0].type = eNvFlowDescriptorType_constantBuffer;
		descriptorWrites[0].write.vulkan.binding = 0;
		descriptorWrites[0].write.vulkan.arrayIndex = 0;
		descriptorWrites[0].write.vulkan.set = 0;
		resources[0].bufferTransient = params->globalParamsIn;

		descriptorWrites[1].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[1].write.vulkan.binding = 1;
		descriptorWrites[1].write.vulkan.arrayIndex = 0;
		descriptorWrites[1].write.vulkan.set = 0;
		resources[1].bufferTransient = params->layerParamsIn;

		descriptorWrites[2].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[2].write.vulkan.binding = 2;
		descriptorWrites[2].write.vulkan.arrayIndex = 0;
		descriptorWrites[2].write.vulkan.set = 0;
		resources[2].bufferTransient = params->gTable;

		descriptorWrites[3].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[3].write.vulkan.binding = 3;
		descriptorWrites[3].write.vulkan.arrayIndex = 0;
		descriptorWrites[3].write.vulkan.set = 0;
		resources[3].textureTransient = params->valueOut;

		passComputeParams.numDescriptorWrites = 4;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SparseClearLayers1CS";
	}
	if (config.api == eNvFlowContextApi_d3d12)
	{
		descriptorWrites[0].type = eNvFlowDescriptorType_constantBuffer;
		descriptorWrites[0].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_b;
		descriptorWrites[0].write.d3d12.registerIndex = 0;
		descriptorWrites[0].write.d3d12.space = 0;
		resources[0].bufferTransient = params->globalParamsIn;

		descriptorWrites[1].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[1].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[1].write.d3d12.registerIndex = 0;
		descriptorWrites[1].write.d3d12.space = 0;
		resources[1].bufferTransient = params->layerParamsIn;

		descriptorWrites[2].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[2].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[2].write.d3d12.registerIndex = 1;
		descriptorWrites[2].write.d3d12.space = 0;
		resources[2].bufferTransient = params->gTable;

		descriptorWrites[3].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[3].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[3].write.d3d12.registerIndex = 0;
		descriptorWrites[3].write.d3d12.space = 0;
		resources[3].textureTransient = params->valueOut;

		passComputeParams.numDescriptorWrites = 4;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SparseClearLayers1CS";
	}
	ptr->contextInterface->addPassCompute(context, &passComputeParams);
};
