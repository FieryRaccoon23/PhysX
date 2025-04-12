#include "PressureRestrictCS_vulkan.hlsl.h"
#include "PressureRestrictCS_d3d12.hlsl.h"

struct PressureRestrictCS_Pipeline
{
	NvFlowContextInterface* contextInterface;
	NvFlowComputePipeline* pipeline;
};

inline void PressureRestrictCS_init(NvFlowContextInterface* contextInterface, NvFlowContext* context, PressureRestrictCS_Pipeline* ptr)
{
	ptr->contextInterface = contextInterface;
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowBindingDesc bindingDescs[5] = {};
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

		bindingDescs[2].type = eNvFlowDescriptorType_texture;
		bindingDescs[2].bindingDesc.vulkan.binding = 2;
		bindingDescs[2].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[2].bindingDesc.vulkan.set = 0;

		bindingDescs[3].type = eNvFlowDescriptorType_sampler;
		bindingDescs[3].bindingDesc.vulkan.binding = 3;
		bindingDescs[3].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[3].bindingDesc.vulkan.set = 0;

		bindingDescs[4].type = eNvFlowDescriptorType_rwTexture;
		bindingDescs[4].bindingDesc.vulkan.binding = 4;
		bindingDescs[4].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[4].bindingDesc.vulkan.set = 0;

		desc.numBindingDescs = 5;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = PressureRestrictCS_vulkan_hlsl;
		desc.bytecode.sizeInBytes = sizeof(PressureRestrictCS_vulkan_hlsl);
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

		bindingDescs[2].type = eNvFlowDescriptorType_texture;
		bindingDescs[2].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		bindingDescs[2].bindingDesc.d3d12.registerBegin = 1;
		bindingDescs[2].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[2].bindingDesc.d3d12.space = 0;

		bindingDescs[3].type = eNvFlowDescriptorType_sampler;
		bindingDescs[3].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_s;
		bindingDescs[3].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[3].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[3].bindingDesc.d3d12.space = 0;

		bindingDescs[4].type = eNvFlowDescriptorType_rwTexture;
		bindingDescs[4].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[4].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[4].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[4].bindingDesc.d3d12.space = 0;

		desc.numBindingDescs = 5;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = PressureRestrictCS_d3d12_hlsl;
		desc.bytecode.sizeInBytes = sizeof(PressureRestrictCS_d3d12_hlsl);
	}
	ptr->pipeline = ptr->contextInterface->createComputePipeline(context, &desc);
};

inline void PressureRestrictCS_destroy(NvFlowContext* context, PressureRestrictCS_Pipeline* ptr)
{
	ptr->contextInterface->destroyComputePipeline(context, ptr->pipeline);
}

struct PressureRestrictCS_PassParams
{
	NvFlowBufferTransient* gParams;
	NvFlowBufferTransient* gTable;
	NvFlowTextureTransient* residualIn;
	NvFlowSampler* valueSampler;
	NvFlowTextureTransient* pressureOut;
};

inline void PressureRestrictCS_addPassCompute(NvFlowContext* context, PressureRestrictCS_Pipeline* ptr, NvFlowUint3 gridDim, const PressureRestrictCS_PassParams* params)
{
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowDescriptorWrite descriptorWrites[5] = {};
	NvFlowResource resources[5] = {};
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
		resources[1].bufferTransient = params->gTable;

		descriptorWrites[2].type = eNvFlowDescriptorType_texture;
		descriptorWrites[2].write.vulkan.binding = 2;
		descriptorWrites[2].write.vulkan.arrayIndex = 0;
		descriptorWrites[2].write.vulkan.set = 0;
		resources[2].textureTransient = params->residualIn;

		descriptorWrites[3].type = eNvFlowDescriptorType_sampler;
		descriptorWrites[3].write.vulkan.binding = 3;
		descriptorWrites[3].write.vulkan.arrayIndex = 0;
		descriptorWrites[3].write.vulkan.set = 0;
		resources[3].sampler = params->valueSampler;

		descriptorWrites[4].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[4].write.vulkan.binding = 4;
		descriptorWrites[4].write.vulkan.arrayIndex = 0;
		descriptorWrites[4].write.vulkan.set = 0;
		resources[4].textureTransient = params->pressureOut;

		passComputeParams.numDescriptorWrites = 5;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "PressureRestrictCS";
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
		resources[1].bufferTransient = params->gTable;

		descriptorWrites[2].type = eNvFlowDescriptorType_texture;
		descriptorWrites[2].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[2].write.d3d12.registerIndex = 1;
		descriptorWrites[2].write.d3d12.space = 0;
		resources[2].textureTransient = params->residualIn;

		descriptorWrites[3].type = eNvFlowDescriptorType_sampler;
		descriptorWrites[3].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_s;
		descriptorWrites[3].write.d3d12.registerIndex = 0;
		descriptorWrites[3].write.d3d12.space = 0;
		resources[3].sampler = params->valueSampler;

		descriptorWrites[4].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[4].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[4].write.d3d12.registerIndex = 0;
		descriptorWrites[4].write.d3d12.space = 0;
		resources[4].textureTransient = params->pressureOut;

		passComputeParams.numDescriptorWrites = 5;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "PressureRestrictCS";
	}
	ptr->contextInterface->addPassCompute(context, &passComputeParams);
};
