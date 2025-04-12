#include "SummaryCS_vulkan.hlsl.h"
#include "SummaryCS_d3d12.hlsl.h"

struct SummaryCS_Pipeline
{
	NvFlowContextInterface* contextInterface;
	NvFlowComputePipeline* pipeline;
};

inline void SummaryCS_init(NvFlowContextInterface* contextInterface, NvFlowContext* context, SummaryCS_Pipeline* ptr)
{
	ptr->contextInterface = contextInterface;
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowBindingDesc bindingDescs[6] = {};
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

		bindingDescs[3].type = eNvFlowDescriptorType_texture;
		bindingDescs[3].bindingDesc.vulkan.binding = 3;
		bindingDescs[3].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[3].bindingDesc.vulkan.set = 0;

		bindingDescs[4].type = eNvFlowDescriptorType_texture;
		bindingDescs[4].bindingDesc.vulkan.binding = 4;
		bindingDescs[4].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[4].bindingDesc.vulkan.set = 0;

		bindingDescs[5].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[5].bindingDesc.vulkan.binding = 5;
		bindingDescs[5].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[5].bindingDesc.vulkan.set = 0;

		desc.numBindingDescs = 6;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SummaryCS_vulkan_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SummaryCS_vulkan_hlsl);
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

		bindingDescs[3].type = eNvFlowDescriptorType_texture;
		bindingDescs[3].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		bindingDescs[3].bindingDesc.d3d12.registerBegin = 2;
		bindingDescs[3].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[3].bindingDesc.d3d12.space = 0;

		bindingDescs[4].type = eNvFlowDescriptorType_texture;
		bindingDescs[4].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		bindingDescs[4].bindingDesc.d3d12.registerBegin = 3;
		bindingDescs[4].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[4].bindingDesc.d3d12.space = 0;

		bindingDescs[5].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[5].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[5].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[5].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[5].bindingDesc.d3d12.space = 0;

		desc.numBindingDescs = 6;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SummaryCS_d3d12_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SummaryCS_d3d12_hlsl);
	}
	ptr->pipeline = ptr->contextInterface->createComputePipeline(context, &desc);
};

inline void SummaryCS_destroy(NvFlowContext* context, SummaryCS_Pipeline* ptr)
{
	ptr->contextInterface->destroyComputePipeline(context, ptr->pipeline);
}

struct SummaryCS_PassParams
{
	NvFlowBufferTransient* gParams;
	NvFlowBufferTransient* gLayerParams;
	NvFlowBufferTransient* gTable;
	NvFlowTextureTransient* velocityIn;
	NvFlowTextureTransient* densityCoarseIn;
	NvFlowBufferTransient* summaryOut;
};

inline void SummaryCS_addPassCompute(NvFlowContext* context, SummaryCS_Pipeline* ptr, NvFlowUint3 gridDim, const SummaryCS_PassParams* params)
{
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowDescriptorWrite descriptorWrites[6] = {};
	NvFlowResource resources[6] = {};
	NvFlowPassComputeParams passComputeParams = {};
	passComputeParams.pipeline = ptr->pipeline;
	passComputeParams.gridDim = gridDim;
	if (config.api == eNvFlowContextApi_vulkan)
	{
		descriptorWrites[0].type = eNvFlowDescriptorType_constantBuffer;
		descriptorWrites[0].write.vulkan.binding = 0;
		descriptorWrites[0].write.vulkan.arrayIndex = 0;
		descriptorWrites[0].write.vulkan.set = 0;
		resources[0].bufferTransient = params->gParams;

		descriptorWrites[1].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[1].write.vulkan.binding = 1;
		descriptorWrites[1].write.vulkan.arrayIndex = 0;
		descriptorWrites[1].write.vulkan.set = 0;
		resources[1].bufferTransient = params->gLayerParams;

		descriptorWrites[2].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[2].write.vulkan.binding = 2;
		descriptorWrites[2].write.vulkan.arrayIndex = 0;
		descriptorWrites[2].write.vulkan.set = 0;
		resources[2].bufferTransient = params->gTable;

		descriptorWrites[3].type = eNvFlowDescriptorType_texture;
		descriptorWrites[3].write.vulkan.binding = 3;
		descriptorWrites[3].write.vulkan.arrayIndex = 0;
		descriptorWrites[3].write.vulkan.set = 0;
		resources[3].textureTransient = params->velocityIn;

		descriptorWrites[4].type = eNvFlowDescriptorType_texture;
		descriptorWrites[4].write.vulkan.binding = 4;
		descriptorWrites[4].write.vulkan.arrayIndex = 0;
		descriptorWrites[4].write.vulkan.set = 0;
		resources[4].textureTransient = params->densityCoarseIn;

		descriptorWrites[5].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[5].write.vulkan.binding = 5;
		descriptorWrites[5].write.vulkan.arrayIndex = 0;
		descriptorWrites[5].write.vulkan.set = 0;
		resources[5].bufferTransient = params->summaryOut;

		passComputeParams.numDescriptorWrites = 6;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SummaryCS";
	}
	if (config.api == eNvFlowContextApi_d3d12)
	{
		descriptorWrites[0].type = eNvFlowDescriptorType_constantBuffer;
		descriptorWrites[0].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_b;
		descriptorWrites[0].write.d3d12.registerIndex = 0;
		descriptorWrites[0].write.d3d12.space = 0;
		resources[0].bufferTransient = params->gParams;

		descriptorWrites[1].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[1].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[1].write.d3d12.registerIndex = 0;
		descriptorWrites[1].write.d3d12.space = 0;
		resources[1].bufferTransient = params->gLayerParams;

		descriptorWrites[2].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[2].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[2].write.d3d12.registerIndex = 1;
		descriptorWrites[2].write.d3d12.space = 0;
		resources[2].bufferTransient = params->gTable;

		descriptorWrites[3].type = eNvFlowDescriptorType_texture;
		descriptorWrites[3].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[3].write.d3d12.registerIndex = 2;
		descriptorWrites[3].write.d3d12.space = 0;
		resources[3].textureTransient = params->velocityIn;

		descriptorWrites[4].type = eNvFlowDescriptorType_texture;
		descriptorWrites[4].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[4].write.d3d12.registerIndex = 3;
		descriptorWrites[4].write.d3d12.space = 0;
		resources[4].textureTransient = params->densityCoarseIn;

		descriptorWrites[5].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[5].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[5].write.d3d12.registerIndex = 0;
		descriptorWrites[5].write.d3d12.space = 0;
		resources[5].bufferTransient = params->summaryOut;

		passComputeParams.numDescriptorWrites = 6;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SummaryCS";
	}
	ptr->contextInterface->addPassCompute(context, &passComputeParams);
};
