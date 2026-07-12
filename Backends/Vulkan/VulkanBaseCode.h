#ifndef VulkanInit_H
#define VulkanInit_H

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>

#include <Core/include.h>

namespace TNgine
{
	class VulkanInit
	{
	public:

		VulkanInit() = default;
		~VulkanInit() = default;

		void Init();

	private:
		void InitVulkan();
		void CreateInstance();
		void SetupDebugMessenger();
		std::vector<const char*> GetRequiredInstanceExtensions();
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity, vk::DebugUtilsMessageTypeFlagsEXT messageType, const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	private:
		void PickPhysicalDevice();
		bool IsDeviceSuitable(const vk::raii::PhysicalDevice& device);

		void CreateLogicalDevice();

	private:
		vk::raii::Context m_Context;
		vk::raii::Instance m_Instance = nullptr;
		vk::raii::DebugUtilsMessengerEXT m_DebugMessenger = nullptr;

	private:
		vk::raii::PhysicalDevice m_PhysicalDevice = nullptr;
		vk::raii::Device m_LogicalDevice = nullptr;
		vk::PhysicalDeviceFeatures m_DeviceFeatures = {};
		vk::raii::Queue m_GraphicsQueue = nullptr;

	private:
		vk::raii::SurfaceKHR m_Surface = nullptr;
	};
}

#endif // !VulkanInit_H
