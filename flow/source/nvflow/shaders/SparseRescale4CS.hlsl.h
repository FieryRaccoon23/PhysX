#include "SparseRescale4CS_vulkan.hlsl.h"
#include "SparseRescale4CS_d3d12.hlsl.h"

struct SparseRescale4CS_Pipeline
{
	NvFlowContextInterface* contextInterface;
	NvFlowComputePipeline* pipeline;
};

inline void SparseRescale4CS_init(NvFlowContextInterface* contextInterface, NvFlowContext* context, SparseRescale4CS_Pipeline* ptr)
{
	ptr->contextInterface = contextInterface;
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowBindingDesc bindingDescs[7] = {};
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

		bindingDescs[3].type = eNvFlowDescriptorType_structuredBuffer;
		bindingDescs[3].bindingDesc.vulkan.binding = 3;
		bindingDescs[3].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[3].bindingDesc.vulkan.set = 0;

		bindingDescs[4].type = eNvFlowDescriptorType_sampler;
		bindingDescs[4].bindingDesc.vulkan.binding = 4;
		bindingDescs[4].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[4].bindingDesc.vulkan.set = 0;

		bindingDescs[5].type = eNvFlowDescriptorType_texture;
		bindingDescs[5].bindingDesc.vulkan.binding = 5;
		bindingDescs[5].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[5].bindingDesc.vulkan.set = 0;

		bindingDescs[6].type = eNvFlowDescriptorType_rwTexture;
		bindingDescs[6].bindingDesc.vulkan.binding = 6;
		bindingDescs[6].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[6].bindingDesc.vulkan.set = 0;

		desc.numBindingDescs = 7;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SparseRescale4CS_vulkan_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SparseRescale4CS_vulkan_hlsl);
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

		bindingDescs[3].type = eNvFlowDescriptorType_structuredBuffer;
		bindingDescs[3].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		bindingDescs[3].bindingDesc.d3d12.registerBegin = 2;
		bindingDescs[3].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[3].bindingDesc.d3d12.space = 0;

		bindingDescs[4].type = eNvFlowDescriptorType_sampler;
		bindingDescs[4].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_s;
		bindingDescs[4].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[4].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[4].bindingDesc.d3d12.space = 0;

		bindingDescs[5].type = eNvFlowDescriptorType_texture;
		bindingDescs[5].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		bindingDescs[5].bindingDesc.d3d12.registerBegin = 3;
		bindingDescs[5].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[5].bindingDesc.d3d12.space = 0;

		bindingDescs[6].type = eNvFlowDescriptorType_rwTexture;
		bindingDescs[6].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[6].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[6].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[6].bindingDesc.d3d12.space = 0;

		desc.numBindingDescs = 7;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SparseRescale4CS_d3d12_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SparseRescale4CS_d3d12_hlsl);
	}
	ptr->pipeline = ptr->contextInterface->createComputePipeline(context, &desc);
};

inline void SparseRescale4CS_destroy(NvFlowContext* context, SparseRescale4CS_Pipeline* ptr)
{
	ptr->contextInterface->destroyComputePipeline(context, ptr->pipeline);
}

struct SparseRescale4CS_PassParams
{
	NvFlowBufferTransient* globalParamsIn;
	NvFlowBufferTransient* layerParamsIn;
	NvFlowBufferTransient* gTable;
	NvFlowBufferTransient* gTableOld;
	NvFlowSampler* valueSampler;
	NvFlowTextureTransient* valueIn;
	NvFlowTextureTransient* valueOut;
};

inline void SparseRescale4CS_addPassCompute(NvFlowContext* context, SparseRescale4CS_Pipeline* ptr, NvFlowUint3 gridDim, const SparseRescale4CS_PassParams* params)
{
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowDescriptorWrite descriptorWrites[7] = {};
	NvFlowResource resources[7] = {};
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

		descriptorWrites[3].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[3].write.vulkan.binding = 3;
		descriptorWrites[3].write.vulkan.arrayIndex = 0;
		descriptorWrites[3].write.vulkan.set = 0;
		resources[3].bufferTransient = params->gTableOld;

		descriptorWrites[4].type = eNvFlowDescriptorType_sampler;
		descriptorWrites[4].write.vulkan.binding = 4;
		descriptorWrites[4].write.vulkan.arrayIndex = 0;
		descriptorWrites[4].write.vulkan.set = 0;
		resources[4].sampler = params->valueSampler;

		descriptorWrites[5].type = eNvFlowDescriptorType_texture;
		descriptorWrites[5].write.vulkan.binding = 5;
		descriptorWrites[5].write.vulkan.arrayIndex = 0;
		descriptorWrites[5].write.vulkan.set = 0;
		resources[5].textureTransient = params->valueIn;

		descriptorWrites[6].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[6].write.vulkan.binding = 6;
		descriptorWrites[6].write.vulkan.arrayIndex = 0;
		descriptorWrites[6].write.vulkan.set = 0;
		resources[6].textureTransient = params->valueOut;

		passComputeParams.numDescriptorWrites = 7;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SparseRescale4CS";
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

		descriptorWrites[3].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[3].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[3].write.d3d12.registerIndex = 2;
		descriptorWrites[3].write.d3d12.space = 0;
		resources[3].bufferTransient = params->gTableOld;

		descriptorWrites[4].type = eNvFlowDescriptorType_sampler;
		descriptorWrites[4].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_s;
		descriptorWrites[4].write.d3d12.registerIndex = 0;
		descriptorWrites[4].write.d3d12.space = 0;
		resources[4].sampler = params->valueSampler;

		descriptorWrites[5].type = eNvFlowDescriptorType_texture;
		descriptorWrites[5].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[5].write.d3d12.registerIndex = 3;
		descriptorWrites[5].write.d3d12.space = 0;
		resources[5].textureTransient = params->valueIn;

		descriptorWrites[6].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[6].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[6].write.d3d12.registerIndex = 0;
		descriptorWrites[6].write.d3d12.space = 0;
		resources[6].textureTransient = params->valueOut;

		passComputeParams.numDescriptorWrites = 7;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SparseRescale4CS";
	}
	ptr->contextInterface->addPassCompute(context, &passComputeParams);
};
