#ifdef asd

#include <backends/imgui_impl_vulkan.h>

#include "vk_imgui.h"
#include <malloc.h>

#define countof( _Arr ) sizeof( _Arr ) / sizeof( _Arr[ 0 ] );

struct VkImGui_t
{
	VkDescriptorPool descriptorPool;
};

void vkCreateImGui( vkImGuiCreateInfo* _pInfo, VkImGui* _pImGui )
{
	VkImGui_t* imgui = (VkImGui_t*)malloc( sizeof( VkImGui_t ) );

	/**
	* this is very much overkill
	* I just copied it from the vulkan example
	*/
	VkDescriptorPoolSize poolSizes[] = {
		{ VK_DESCRIPTOR_TYPE_SAMPLER,                1000 },
		{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
		{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,          1000 },
		{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,          1000 },
		{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,   1000 },
		{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,   1000 },
		{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1000 },
		{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         1000 },
		{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
		{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
		{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,       1000 }
	};

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	poolInfo.maxSets = 1000;
	poolInfo.poolSizeCount = (uint32_t)countof( poolSizes );
	poolInfo.pPoolSizes = poolSizes;

	vkCreateDescriptorPool( _pInfo->device, &poolInfo, nullptr, &imgui->descriptorPool );

	ImGui::CreateContext();


	ImGui_ImplVulkan_InitInfo initInfo{};
	initInfo.Instance = _pInfo->instance;
	initInfo.PhysicalDevice = _pInfo->physicalDevice;
	initInfo.Device = _pInfo->device;
	initInfo.Queue = _pInfo->queue;
	initInfo.DescriptorPool = imgui->descriptorPool;
	initInfo.MinImageCount = 3;
	initInfo.ImageCount = 3;
	initInfo.UseDynamicRendering = true;

	initInfo.PipelineRenderingCreateInfo = {};
	initInfo.PipelineRenderingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO;
	initInfo.PipelineRenderingCreateInfo.colorAttachmentCount = 1;
	initInfo.PipelineRenderingCreateInfo.pColorAttachmentFormats = &_pInfo->format;

	initInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

	ImGui_ImplVulkan_Init( &initInfo );
	ImGui_ImplVulkan_CreateFontsTexture();

	*_pImGui = imgui;

}

void vkDestroyImGui( VkDevice _device, VkImGui _imgui )
{
	ImGui_ImplVulkan_Shutdown();
	
	vkDestroyDescriptorPool( _device, _imgui->descriptorPool, nullptr );
}

void vkImGuiBeginFrame()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui::NewFrame();
}

void vkImGuiEndFrame( VkCommandBuffer _cmd, VkImageView _targetImageView, VkExtent2D _extent )
{
	ImGui::Render();

	VkRenderingAttachmentInfo colorAttachment{};
	colorAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
	colorAttachment.pNext = nullptr;

	colorAttachment.imageView = _targetImageView;
	colorAttachment.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

	VkRenderingInfo renderInfo{};
	renderInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
	renderInfo.pNext = nullptr;

	renderInfo.renderArea = VkRect2D{ VkOffset2D { 0, 0 }, _extent };
	renderInfo.layerCount = 1;
	renderInfo.colorAttachmentCount = 1;
	renderInfo.pColorAttachments = &colorAttachment;
	renderInfo.pDepthAttachment = nullptr;
	renderInfo.pStencilAttachment = nullptr;

	vkCmdBeginRendering( _cmd, &renderInfo );
	ImGui_ImplVulkan_RenderDrawData( ImGui::GetDrawData(), _cmd );
	vkCmdEndRendering( _cmd );
}

#endif