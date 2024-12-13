#ifndef _VK_IMGUI_H
#define _VK_IMGUI_H

#include <imgui.h>
#include <vulkan/vulkan_core.h>

#ifdef __cplusplus
extern "C" {
#endif

class GLFWwindow;

typedef void ( *PFN_vkImGui_ImplInit )( );
typedef void ( *PFN_vkImGui_ImplShutdown )( );

struct vkImGuiCreateInfo
{
	VkDevice device;

	VkInstance instance;
	VkPhysicalDevice physicalDevice;
	VkQueue queue;

	VkFormat format;

	PFN_vkImGui_ImplInit fpInit;
	PFN_vkImGui_ImplInit fpShutdown;
};

typedef struct VkImGui_t* VkImGui;

void vkCreateImGui( vkImGuiCreateInfo* _pInfo, VkImGui* _pImGui );
void vkDestroyImGui( VkDevice _device, VkImGui _imgui );

void vkImGuiBeginFrame();
void vkImGuiEndFrame( VkCommandBuffer _cmd, VkImageView _targetImageView, VkExtent2D _extent );

#ifdef __cplusplus
}
#endif

#endif