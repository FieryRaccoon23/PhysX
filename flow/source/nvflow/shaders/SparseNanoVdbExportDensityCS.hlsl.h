#include "SparseNanoVdbExportDensityCS_vulkan.hlsl.h"
#include "SparseNanoVdbExportDensityCS_d3d12.hlsl.h"

struct SparseNanoVdbExportDensityCS_Pipeline
{
	NvFlowContextInterface* contextInterface;
	NvFlowComputePipeline* pipeline;
};

inline void SparseNanoVdbExportDensityCS_init(NvFlowContextInterface* contextInterface, NvFlowContext* context, SparseNanoVdbExportDensityCS_Pipeline* ptr)
{
	ptr->contextInterface = contextInterface;
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowBindingDesc bindingDescs[9] = {};
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

		bindingDescs[3].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[3].bindingDesc.vulkan.binding = 3;
		bindingDescs[3].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[3].bindingDesc.vulkan.set = 0;

		bindingDescs[4].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[4].bindingDesc.vulkan.binding = 4;
		bindingDescs[4].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[4].bindingDesc.vulkan.set = 0;

		bindingDescs[5].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[5].bindingDesc.vulkan.binding = 5;
		bindingDescs[5].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[5].bindingDesc.vulkan.set = 0;

		bindingDescs[6].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[6].bindingDesc.vulkan.binding = 6;
		bindingDescs[6].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[6].bindingDesc.vulkan.set = 0;

		bindingDescs[7].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[7].bindingDesc.vulkan.binding = 7;
		bindingDescs[7].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[7].bindingDesc.vulkan.set = 0;

		bindingDescs[8].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[8].bindingDesc.vulkan.binding = 8;
		bindingDescs[8].bindingDesc.vulkan.descriptorCount = 1;
		bindingDescs[8].bindingDesc.vulkan.set = 0;

		desc.numBindingDescs = 9;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SparseNanoVdbExportDensityCS_vulkan_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SparseNanoVdbExportDensityCS_vulkan_hlsl);
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

		bindingDescs[3].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[3].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[3].bindingDesc.d3d12.registerBegin = 0;
		bindingDescs[3].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[3].bindingDesc.d3d12.space = 0;

		bindingDescs[4].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[4].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[4].bindingDesc.d3d12.registerBegin = 1;
		bindingDescs[4].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[4].bindingDesc.d3d12.space = 0;

		bindingDescs[5].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[5].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[5].bindingDesc.d3d12.registerBegin = 2;
		bindingDescs[5].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[5].bindingDesc.d3d12.space = 0;

		bindingDescs[6].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[6].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[6].bindingDesc.d3d12.registerBegin = 3;
		bindingDescs[6].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[6].bindingDesc.d3d12.space = 0;

		bindingDescs[7].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[7].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[7].bindingDesc.d3d12.registerBegin = 4;
		bindingDescs[7].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[7].bindingDesc.d3d12.space = 0;

		bindingDescs[8].type = eNvFlowDescriptorType_rwStructuredBuffer;
		bindingDescs[8].bindingDesc.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		bindingDescs[8].bindingDesc.d3d12.registerBegin = 5;
		bindingDescs[8].bindingDesc.d3d12.numRegisters = 1;
		bindingDescs[8].bindingDesc.d3d12.space = 0;

		desc.numBindingDescs = 9;
		desc.bindingDescs = bindingDescs;
		desc.bytecode.data = SparseNanoVdbExportDensityCS_d3d12_hlsl;
		desc.bytecode.sizeInBytes = sizeof(SparseNanoVdbExportDensityCS_d3d12_hlsl);
	}
	ptr->pipeline = ptr->contextInterface->createComputePipeline(context, &desc);
};

inline void SparseNanoVdbExportDensityCS_destroy(NvFlowContext* context, SparseNanoVdbExportDensityCS_Pipeline* ptr)
{
	ptr->contextInterface->destroyComputePipeline(context, ptr->pipeline);
}

struct SparseNanoVdbExportDensityCS_PassParams
{
	NvFlowBufferTransient* paramsIn;
	NvFlowBufferTransient* tableIn;
	NvFlowTextureTransient* densityIn;
	NvFlowBufferTransient* temperatureOut;
	NvFlowBufferTransient* fuelOut;
	NvFlowBufferTransient* burnOut;
	NvFlowBufferTransient* smokeOut;
	NvFlowBufferTransient* rgbaOut;
	NvFlowBufferTransient* rgbOut;
};

inline void SparseNanoVdbExportDensityCS_addPassCompute(NvFlowContext* context, SparseNanoVdbExportDensityCS_Pipeline* ptr, NvFlowUint3 gridDim, const SparseNanoVdbExportDensityCS_PassParams* params)
{
	NvFlowContextConfig config = {};
	ptr->contextInterface->getContextConfig(context, &config);
	NvFlowDescriptorWrite descriptorWrites[9] = {};
	NvFlowResource resources[9] = {};
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

		descriptorWrites[1].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[1].write.vulkan.binding = 1;
		descriptorWrites[1].write.vulkan.arrayIndex = 0;
		descriptorWrites[1].write.vulkan.set = 0;
		resources[1].bufferTransient = params->tableIn;

		descriptorWrites[2].type = eNvFlowDescriptorType_texture;
		descriptorWrites[2].write.vulkan.binding = 2;
		descriptorWrites[2].write.vulkan.arrayIndex = 0;
		descriptorWrites[2].write.vulkan.set = 0;
		resources[2].textureTransient = params->densityIn;

		descriptorWrites[3].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[3].write.vulkan.binding = 3;
		descriptorWrites[3].write.vulkan.arrayIndex = 0;
		descriptorWrites[3].write.vulkan.set = 0;
		resources[3].bufferTransient = params->temperatureOut;

		descriptorWrites[4].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[4].write.vulkan.binding = 4;
		descriptorWrites[4].write.vulkan.arrayIndex = 0;
		descriptorWrites[4].write.vulkan.set = 0;
		resources[4].bufferTransient = params->fuelOut;

		descriptorWrites[5].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[5].write.vulkan.binding = 5;
		descriptorWrites[5].write.vulkan.arrayIndex = 0;
		descriptorWrites[5].write.vulkan.set = 0;
		resources[5].bufferTransient = params->burnOut;

		descriptorWrites[6].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[6].write.vulkan.binding = 6;
		descriptorWrites[6].write.vulkan.arrayIndex = 0;
		descriptorWrites[6].write.vulkan.set = 0;
		resources[6].bufferTransient = params->smokeOut;

		descriptorWrites[7].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[7].write.vulkan.binding = 7;
		descriptorWrites[7].write.vulkan.arrayIndex = 0;
		descriptorWrites[7].write.vulkan.set = 0;
		resources[7].bufferTransient = params->rgbaOut;

		descriptorWrites[8].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[8].write.vulkan.binding = 8;
		descriptorWrites[8].write.vulkan.arrayIndex = 0;
		descriptorWrites[8].write.vulkan.set = 0;
		resources[8].bufferTransient = params->rgbOut;

		passComputeParams.numDescriptorWrites = 9;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SparseNanoVdbExportDensityCS";
	}
	if (config.api == eNvFlowContextApi_d3d12)
	{
		descriptorWrites[0].type = eNvFlowDescriptorType_constantBuffer;
		descriptorWrites[0].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_b;
		descriptorWrites[0].write.d3d12.registerIndex = 0;
		descriptorWrites[0].write.d3d12.space = 0;
		resources[0].bufferTransient = params->paramsIn;

		descriptorWrites[1].type = eNvFlowDescriptorType_structuredBuffer;
		descriptorWrites[1].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[1].write.d3d12.registerIndex = 0;
		descriptorWrites[1].write.d3d12.space = 0;
		resources[1].bufferTransient = params->tableIn;

		descriptorWrites[2].type = eNvFlowDescriptorType_texture;
		descriptorWrites[2].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_t;
		descriptorWrites[2].write.d3d12.registerIndex = 1;
		descriptorWrites[2].write.d3d12.space = 0;
		resources[2].textureTransient = params->densityIn;

		descriptorWrites[3].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[3].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[3].write.d3d12.registerIndex = 0;
		descriptorWrites[3].write.d3d12.space = 0;
		resources[3].bufferTransient = params->temperatureOut;

		descriptorWrites[4].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[4].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[4].write.d3d12.registerIndex = 1;
		descriptorWrites[4].write.d3d12.space = 0;
		resources[4].bufferTransient = params->fuelOut;

		descriptorWrites[5].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[5].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[5].write.d3d12.registerIndex = 2;
		descriptorWrites[5].write.d3d12.space = 0;
		resources[5].bufferTransient = params->burnOut;

		descriptorWrites[6].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[6].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[6].write.d3d12.registerIndex = 3;
		descriptorWrites[6].write.d3d12.space = 0;
		resources[6].bufferTransient = params->smokeOut;

		descriptorWrites[7].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[7].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[7].write.d3d12.registerIndex = 4;
		descriptorWrites[7].write.d3d12.space = 0;
		resources[7].bufferTransient = params->rgbaOut;

		descriptorWrites[8].type = eNvFlowDescriptorType_rwStructuredBuffer;
		descriptorWrites[8].write.d3d12.registerHlsl = eNvFlowRegisterHlsl_u;
		descriptorWrites[8].write.d3d12.registerIndex = 5;
		descriptorWrites[8].write.d3d12.space = 0;
		resources[8].bufferTransient = params->rgbOut;

		passComputeParams.numDescriptorWrites = 9;
		passComputeParams.descriptorWrites = descriptorWrites;
		passComputeParams.resources = resources;
		passComputeParams.debugLabel = "SparseNanoVdbExportDensityCS";
	}
	ptr->contextInterface->addPassCompute(context, &passComputeParams);
};
