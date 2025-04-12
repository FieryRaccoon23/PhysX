#include "SparseClearTexture4CS_vulkan.hlsl.h"
#include "SparseClearTexture4CS_d3d12.hlsl.h"

struct SparseClearTexture4CS_Pipeline
{
	NvFlowContextInterface* contextInterface;
	NvFlowComputePipeline* pipeline;
};

inline void SparseClearTexture4CS_init(NvFlowContextInterface* contextInterface, NvFlowContext* context, SparseClearTexture4CS_Pipeline* ptr)
{
	ptr->contextInterface = contextInterface;
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowBindingDesc bindingDescs[2] = {};
	NvFlowComputePipelineDesc desc = {};
	if (config.api == eNvFlowContextApi_vulkan)
	{
		bindingDescs[0].type = eNvFlowDescriptorType_constantBuffer;
		bindingDescs[0].bindingDesc.vulkan.binding = 0;
		bindingDescs[0].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[0].bindingDesc.vulkan.set = 0;

		bindingDescs[1].type = eNvFlowDescriptorType_rwTexture;
		bindingDescs[1].bindingDesc.vulkan.binding = 1;
		bindingDescs[1].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[1].bindingDesc.vulkan.set = 0;

		desc.numBindingDescs = 2;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SparseClearTexture4CS_vulkan_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SparseClearTexture4CS_vulkan_hlsl);
	}
	if (config.api == eNvFlowContextApi_d3d12)
	{
		bindingDescs[0].type = eNvFlowDescriptorType_constantBuffer;
		bindingDescs[0].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_b;
		bindingDescs[0].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[0].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[0].bindingDesc.d3d12.space = 0;

		bindingDescs[1].type = eNvFlowDescriptorType_rwTexture;
		bindingDescs[1].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[1].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[1].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[1].bindingDesc.d3d12.space = 0;

		desc.numBindingDescs = 2;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SparseClearTexture4CS_d3d12_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SparseClearTexture4CS_d3d12_hlsl);
	}
	ptr->pipeline = ptr->contextInterface->createComputePipeline(context, &desc);
};

inline void SparseClearTexture4CS_destroy(NvFlowContext* context, SparseClearTexture4CS_Pipeline* ptr)
{
	ptr->contextInterface->destroyComputePipeline(context, ptr->pipeline);
}

struct SparseClearTexture4CS_PassParams
{
	NvFlowBufferTransient* paramsIn;
	NvFlowTextureTransient* valueOut;
};

inline void SparseClearTexture4CS_addPassCompute(NvFlowContext* context, SparseClearTexture4CS_Pipeline* ptr, NvFlowUint3 gridDim, const SparseClearTexture4CS_PassParams* params)
{
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowDescriptorWrite descriptorWrites[2] = {};
	NvFlowResource resources[2] = {};
	NvFlowPassComputeParams passComputeParams = {};
	passComputeParams.pipeline = ptr->pipeline;
	passComputeParams.gridDim = gridDim;
	if (config.api == eNvFlowContextApi_vulkan)
	{
		descriptorWrites[0].type = eNvFlowDescriptorType_constantBuffer;
		descriptorWrites[0].write.vulkan.binding = 0;
		descriptorWrites[0].write.vulkan.arrayIndex = 0;
		descriptorWrites[0].write.vulkan.set = 0;
		resources[0].bufferTransient = params->paramsIn;

		descriptorWrites[1].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[1].write.vulkan.binding = 1;
		descriptorWrites[1].write.vulkan.arrayIndex = 0;
		descriptorWrites[1].write.vulkan.set = 0;
		resources[1].textureTransient = params->valueOut;

		passComputeParams.numDescriptorWrites = 2;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SparseClearTexture4CS";
	}
	if (config.api == eNvFlowContextApi_d3d12)
	{
		descriptorWrites[0].type = eNvFlowDescriptorType_constantBuffer;
		descriptorWrites[0].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_b;
		descriptorWrites[0].write.d3d12.registerIndex = 0;
		descriptorWrites[0].write.d3d12.space = 0;
		resources[0].bufferTransient = params->paramsIn;

		descriptorWrites[1].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[1].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[1].write.d3d12.registerIndex = 0;
		descriptorWrites[1].write.d3d12.space = 0;
		resources[1].textureTransient = params->valueOut;

		passComputeParams.numDescriptorWrites = 2;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SparseClearTexture4CS";
	}
	ptr->contextInterface->addPassCompute(context, &passComputeParams);
};
