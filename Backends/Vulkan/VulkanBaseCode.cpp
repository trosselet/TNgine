#include "VulkanBaseCode.h"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <ranges>
#include <iostream>
#include <vector>

#ifdef _DEBUG
#define VULKAN_DEBUG_INFO
#endif // _DEBUG

void TNgine::VulkanInit::Init()
{
#ifdef VULKAN_DEBUG_INFO
	std::cout << "|--------------------------------------------------VULKAN---------------------------------------------------|"<< std::endl;
#endif // VULKAN_DEBUG_INFO

	InitVulkan();
	SetupDebugMessenger();

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
    constexpr vk::ApplicationInfo appInfo{
        .pApplicationName = "TNgine",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "TNgine",
        .engineVersion = VK_MAKE_VERSION(0, 1, 0),
        .apiVersion = vk::ApiVersion14
    };

    // Validation layers
    const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
    std::vector<char const*> requiredLayers;

#ifdef VULKAN_DEBUG_INFO
    requiredLayers.assign(validationLayers.begin(), validationLayers.end());
#endif

    auto layerProperties = m_Context.enumerateInstanceLayerProperties();
    auto unsupportedLayerIt = std::ranges::find_if(requiredLayers, [&layerProperties](auto const& requiredLayer)
        {
            return std::ranges::none_of(layerProperties, [requiredLayer](auto const& layerProperty)
                {
                    return strcmp(layerProperty.layerName, requiredLayer) == 0;
                });
        });

    if (unsupportedLayerIt != requiredLayers.end())
    {
        CLOG_ERROR("Required layer not supported: {}", std::string(*unsupportedLayerIt));
        return;
    }

    // Extensions
    auto requiredExtensions = GetRequiredInstanceExtensions();
    auto extensionProperties = m_Context.enumerateInstanceExtensionProperties();

#ifdef VULKAN_DEBUG_INFO
    CLOG_INFO("Available extensions:");
    for (auto& extension : extensionProperties)
    {
        CLOG_INFO("\t[VULKAN]  {}", extension.extensionName.data());
    }
#endif

    auto unsupportedExtIt = std::ranges::find_if(requiredExtensions, [&extensionProperties](auto const& requiredExtension)
        {
            return std::ranges::none_of(extensionProperties, [requiredExtension](auto const& extensionProperty)
                {
                    return strcmp(extensionProperty.extensionName, requiredExtension) == 0;
                });
        });

    if (unsupportedExtIt != requiredExtensions.end())
    {
        CLOG_ERROR("Required extension not supported: {}", std::string(*unsupportedExtIt));
        return;
    }

    vk::InstanceCreateInfo createInstanceInfo
    {
#ifdef TNGINE_OS_MAC
        .flags = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = static_cast<uint32>(requiredLayers.size()),
        .ppEnabledLayerNames = requiredLayers.data(),
        .ppEnabledExtensionNames = { vk::KHRPortabilityEnumerationExtensionName }
#else
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = static_cast<uint32>(requiredLayers.size()),
        .ppEnabledLayerNames = requiredLayers.data(),
        .enabledExtensionCount = static_cast<uint32>(requiredExtensions.size()),
        .ppEnabledExtensionNames = requiredExtensions.data()
#endif
    };

    m_Instance = vk::raii::Instance(m_Context, createInstanceInfo);
}

void TNgine::VulkanInit::SetupDebugMessenger()
{
#ifndef VULKAN_DEBUG_INFO
	return;
#endif // !VULAN_DEBUG_INFO

	vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);

	vk::DebugUtilsMessageTypeFlagsEXT     messageTypeFlags(vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);
	vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT
	{ 
		.messageSeverity = severityFlags, 
		.messageType = messageTypeFlags,
		.pfnUserCallback = &DebugCallback 
	};

	m_DebugMessenger = m_Instance.createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfoEXT);
}

std::vector<const char*> TNgine::VulkanInit::GetRequiredInstanceExtensions()
{
	uint32 glfwExtensionCount = 0;
	auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef VULKAN_DEBUG_INFO
	extensions.push_back(vk::EXTDebugUtilsExtensionName);
#endif // VULKAN_DEBUG_INFO


	return extensions;
}

VKAPI_ATTR VkBool32 VKAPI_CALL TNgine::VulkanInit::DebugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity, vk::DebugUtilsMessageTypeFlagsEXT messageType, const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
	if (messageSeverity >= vk::DebugUtilsMessageSeverityFlagBitsEXT::eError)
	{
		CLOG_ERROR("[VULKAN] validation layer : type {}, msg: {}", vk::to_string(messageType), pCallbackData->pMessage);
	}
	else if (messageSeverity >= vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning)
	{
		CLOG_WARN("[VULKAN] validation layer : type {}, msg: {}", vk::to_string(messageType), pCallbackData->pMessage);
	}
	else
	{
		CLOG_INFO("[VULKAN] validation layer : type {}, msg: {}", vk::to_string(messageType), pCallbackData->pMessage);
	}


	return vk::False;
}