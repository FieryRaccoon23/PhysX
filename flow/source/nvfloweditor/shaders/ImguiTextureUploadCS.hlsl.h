#include "ImguiTextureUploadCS_vulkan.hlsl.h"
#include "ImguiTextureUploadCS_d3d12.hlsl.h"

struct ImguiTextureUploadCS_Pipeline
{
	NvFlowContextInterface* contextInterface;
	NvFlowComputePipeline* pipeline;
};

inline void ImguiTextureUploadCS_init(NvFlowContextInterface* contextInterface, NvFlowContext* context, ImguiTextureUploadCS_Pipeline* ptr)
{
	ptr->contextInterface = contextInterface;
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowBindingDesc bindingDescs[2] = {};
	NvFlowComputePipelineDesc desc = {};
	if (config.api == eNvFlowContextApi_vulkan)
	{
		bindingDescs[0].type = eNvFlowDescriptorType_structuredBuffer;
		bindingDescs[0].bindingDesc.vulkan.binding = 0;
		bindingDescs[0].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[0].bindingDesc.vulkan.set = 0;

		bindingDescs[1].type = eNvFlowDescriptorType_rwTexture;
		bindingDescs[1].bindingDesc.vulkan.binding = 1;
		bindingDescs[1].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[1].bindingDesc.vulkan.set = 0;

		desc.numBindingDescs = 2;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = ImguiTextureUploadCS_vulkan_hlsl;
		desc.bytecode.sizeInBytes = sizeof(ImguiTextureUploadCS_vulkan_hlsl);
	}
	if (config.api == eNvFlowContextApi_d3d12)
	{
		bindingDescs[0].type = eNvFlowDescriptorType_structuredBuffer;
		bindingDescs[0].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
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
		desc.bytecode.data = ImguiTextureUploadCS_d3d12_hlsl;
		desc.bytecode.sizeInBytes = sizeof(ImguiTextureUploadCS_d3d12_hlsl);
	}
	ptr->pipeline = ptr->contextInterface->createComputePipeline(context, &desc);
};

inline void ImguiTextureUploadCS_destroy(NvFlowContext* context, ImguiTextureUploadCS_Pipeline* ptr)
{
	ptr->contextInterface->destroyComputePipeline(context, ptr->pipeline);
}

struct ImguiTextureUploadCS_PassParams
{
	NvFlowBufferTransient* uploadIn;
	NvFlowTextureTransient* colorOut;
};

inline void ImguiTextureUploadCS_addPassCompute(NvFlowContext* context, ImguiTextureUploadCS_Pipeline* ptr, NvFlowUint3 gridDim, const ImguiTextureUploadCS_PassParams* params)
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
		descriptorWrites[0].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[0].write.vulkan.binding = 0;
		descriptorWrites[0].write.vulkan.arrayIndex = 0;
		descriptorWrites[0].write.vulkan.set = 0;
		resources[0].bufferTransient = params->uploadIn;

		descriptorWrites[1].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[1].write.vulkan.binding = 1;
		descriptorWrites[1].write.vulkan.arrayIndex = 0;
		descriptorWrites[1].write.vulkan.set = 0;
		resources[1].textureTransient = params->colorOut;

		passComputeParams.numDescriptorWrites = 2;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "ImguiTextureUploadCS";
	}
	if (config.api == eNvFlowContextApi_d3d12)
	{
		descriptorWrites[0].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[0].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[0].write.d3d12.registerIndex = 0;
		descriptorWrites[0].write.d3d12.space = 0;
		resources[0].bufferTransient = params->uploadIn;

		descriptorWrites[1].type = eNvFlowDescriptorType_rwTexture;
		descriptorWrites[1].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[1].write.d3d12.registerIndex = 0;
		descriptorWrites[1].write.d3d12.space = 0;
		resources[1].textureTransient = params->colorOut;

		passComputeParams.numDescriptorWrites = 2;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "ImguiTextureUploadCS";
	}
	ptr->contextInterface->addPassCompute(context, &passComputeParams);
};
