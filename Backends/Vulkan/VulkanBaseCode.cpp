#include "VulkanBaseCode.h"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <ranges>
#include <iostream>

#define VULKAN_DEBUG_INFO

void TNgine::VulkanInit::Init()
{
#ifdef VULKAN_DEBUG_INFO
	std::cout << "|--------------------------------------------------VULKAN---------------------------------------------------|"<< std::endl;
#endif // VULKAN_DEBUG_INFO

	InitVulkan();


#ifdef VULKAN_DEBUG_INFO
	std::cout << "|-----------------------------------------------------------------------------------------------------------|" << std::endl;
#endif // VULKAN_DEBUG_INFO
}

void TNgine::VulkanInit::InitVulkan()
{
	CreateInstance();
}

/*Create the vk instance*/
void TNgine::VulkanInit::CreateInstance()
{

	//Only some information that can be used by the driver to optimize our app
	constexpr vk::ApplicationInfo appInfo{
		.pApplicationName = "TNgine",
		.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName = "TNgine",
		.engineVersion = VK_MAKE_VERSION(0, 1, 0),
		.apiVersion = vk::ApiVersion14
	};

#ifndef TNGINE_OS_MAC
	uint32 glfwExtensionCount = 0;
	auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	auto extensionProperties = m_Context.enumerateInstanceExtensionProperties();
	for (uint32 i = 0; i < glfwExtensionCount; ++i)
	{
		if (std::none_of(extensionProperties.begin(), extensionProperties.end(), [glfwExtension = glfwExtensions[i]](auto const& extensionProperty) { return strcmp(extensionProperty.extensionName.data(), glfwExtension) == 0;}))
		{
			CLOG_ERROR("Required GLFW extension not supported: {}", std::string(glfwExtensions[i]));
		}
	}
#endif // !TNGINE_OS_MAC

	vk::InstanceCreateInfo createInstanceInfo
	{
#ifdef TNGINE_OS_MAC
		.flags = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
		.pApplicationInfo = &appInfo,
		.ppEnabledExtensionNames = { vk::KHRPortabilityEnumerationExtensionName }
#else
		.pApplicationInfo = &appInfo,
		.enabledExtensionCount = glfwExtensionCount,
		.ppEnabledExtensionNames = glfwExtensions
#endif // TNGINE_OS_MAC

	};

	m_Instance = vk::raii::Instance(m_Context, createInstanceInfo);

#ifdef VULKAN_DEBUG_INFO
	CLOG_INFO("Available extension : ");
	for (auto& extension : extensionProperties)
	{
		CLOG_INFO("\t[VULKAN]  {}", extension.extensionName.data());
	}
#endif // VULKAN_DEBUG_INFO
}
