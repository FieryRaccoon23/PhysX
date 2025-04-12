#include "SparseInplaceRescale4dCS_vulkan.hlsl.h"
#include "SparseInplaceRescale4dCS_d3d12.hlsl.h"

struct SparseInplaceRescale4dCS_Pipeline
{
	NvFlowContextInterface* contextInterface;
	NvFlowComputePipeline* pipeline;
};

inline void SparseInplaceRescale4dCS_init(NvFlowContextInterface* contextInterface, NvFlowContext* context, SparseInplaceRescale4dCS_Pipeline* ptr)
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

		bindingDescs[2].type = eNvFlowDescriptorType_structuredBuffer;
		bindingDescs[2].bindingDesc.vulkan.binding = 2;
		bindingDescs[2].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[2].bindingDesc.vulkan.set = 0;

		bindingDescs[3].type = eNvFlowDescriptorType_texture;
		bindingDescs[3].bindingDesc.vulkan.binding = 3;
		bindingDescs[3].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[3].bindingDesc.vulkan.set = 0;

		bindingDescs[4].type = eNvFlowDescriptorType_rwTexture;
		bindingDescs[4].bindingDesc.vulkan.binding = 4;
		bindingDescs[4].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[4].bindingDesc.vulkan.set = 0;

		desc.numBindingDescs = 5;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SparseInplaceRescale4dCS_vulkan_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SparseInplaceRescale4dCS_vulkan_hlsl);
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

		bindingDescs[4].type = eNvFlowDescriptorType_rwTexture;
		bindingDescs[4].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[4].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[4].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[4].bindingDesc.d3d12.space = 0;

		desc.numBindingDescs = 5;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SparseInplaceRescale4dCS_d3d12_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SparseInplaceRescale4dCS_d3d12_hlsl);
	}
	ptr->pipeline = ptr->contextInterface->createComputePipeline(context, &desc);
};

inline void SparseInplaceRescale4dCS_destroy(NvFlowContext* context, SparseInplaceRescale4dCS_Pipeline* ptr)
{
	ptr->contextInterface->destroyComputePipeline(context, ptr->pipeline);
}

struct SparseInplaceRescale4dCS_PassParams
{
	NvFlowBufferTransient* globalParamsIn;
	NvFlowBufferTransient* layerParamsIn;
	NvFlowBufferTransient* gTable;
	NvFlowTextureTransient* valueIn;
	NvFlowTextureTransient* valueOut;
};

inline void SparseInplaceRescale4dCS_addPassCompute(NvFlowContext* context, SparseInplaceRescale4dCS_Pipeline* ptr, NvFlowUint3 gridDim, const SparseInplaceRescale4dCS_PassParams* params)
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

		descriptorWrites[3].type = eNvFlowDescriptorType_texture;
		descriptorWrites[3].write.vulkan.binding = 3;
		descriptorWrites[3].write.vulkan.arrayIndex = 0;
		descriptorWrites[3].write.vulkan.set = 0;
		resources[3].textureTransient = params->valueIn;

		descriptorWrites[4].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[4].write.vulkan.binding = 4;
		descriptorWrites[4].write.vulkan.arrayIndex = 0;
		descriptorWrites[4].write.vulkan.set = 0;
		resources[4].textureTransient = params->valueOut;

		passComputeParams.numDescriptorWrites = 5;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SparseInplaceRescale4dCS";
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

		descriptorWrites[3].type = eNvFlowDescriptorType_texture;
		descriptorWrites[3].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[3].write.d3d12.registerIndex = 2;
		descriptorWrites[3].write.d3d12.space = 0;
		resources[3].textureTransient = params->valueIn;

		descriptorWrites[4].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[4].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[4].write.d3d12.registerIndex = 0;
		descriptorWrites[4].write.d3d12.space = 0;
		resources[4].textureTransient = params->valueOut;

		passComputeParams.numDescriptorWrites = 5;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SparseInplaceRescale4dCS";
	}
	ptr->contextInterface->addPassCompute(context, &passComputeParams);
};
