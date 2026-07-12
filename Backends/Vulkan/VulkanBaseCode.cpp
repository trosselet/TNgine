#include "VulkanBaseCode.h"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <ranges>
#include <iostream>
#include <vector>
#include <map>

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
    PickPhysicalDevice();
    CreateLogicalDevice();

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
		//CLOG_INFO("[VULKAN] validation layer : type {}, msg: {}", vk::to_string(messageType), pCallbackData->pMessage);
	}


	return vk::False;
}


void TNgine::VulkanInit::PickPhysicalDevice()
{
	auto physicalDevices = m_Instance.enumeratePhysicalDevices();

    if (physicalDevices.empty())
    { 
        TNGINE_ASSERT(false, "Failed to find GPUs with Vulkan support!");
    }

    std::multimap<int32, uint64> candidates;
     
    for (uint64 i = 0; i < physicalDevices.size(); i++)
	{
		auto properties = physicalDevices[i].getProperties();
		auto features = physicalDevices[i].getFeatures();
		CLOG_INFO("Found GPU: {}", properties.deviceName.data());

        uint32 score = 0;

        if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) 
        {
            score += 1000;
        }

        score += properties.limits.maxImageDimension2D;

        if (!features.geometryShader)
        {
            continue;
        }
        candidates.insert(std::make_pair(score, i));

	}

    if (!candidates.empty() && candidates.rbegin()->first > 0)
    {
        uint64 bestIndex = candidates.rbegin()->second;

        m_PhysicalDevice = std::move(physicalDevices[bestIndex]);

		if (IsDeviceSuitable(m_PhysicalDevice))
		{
			CLOG_INFO("Selected GPU: {}", m_PhysicalDevice.getProperties().deviceName.data());
		}
		else
		{
			TNGINE_ASSERT(false, "Selected GPU is not suitable!");
		} 
    }
    else
    {
        TNGINE_ASSERT(false, "Failed to find a suitable GPU!");
    }

    
     
}

bool TNgine::VulkanInit::IsDeviceSuitable(const vk::raii::PhysicalDevice& device)
{
    bool supportsVulkan1_3 = device.getProperties().apiVersion >= vk::ApiVersion13;

    auto queueFamilies = device.getQueueFamilyProperties();
    bool queueSupportsGraphics = std::ranges::any_of(queueFamilies, [](auto const& qfp)
        { return !!(qfp.queueFlags & vk::QueueFlagBits::eGraphics); });

    std::vector<const char*> requiredDeviceExtension =
    {
        vk::KHRSwapchainExtensionName,
        vk::EXTExtendedDynamicStateExtensionName 
    };

    auto availableExtensions = device.enumerateDeviceExtensionProperties();

    bool supportsAllRequiredExtensions = std::ranges::all_of(requiredDeviceExtension,
        [&availableExtensions](auto const& requiredDeviceExtension)
        {
            return std::ranges::any_of(availableExtensions,
                [requiredDeviceExtension](auto const& availableDeviceExtension)
                { return strcmp(availableDeviceExtension.extensionName, requiredDeviceExtension) == 0; });
        });
     
    if (!supportsVulkan1_3 || !queueSupportsGraphics || !supportsAllRequiredExtensions)
    {
        return false;
    }

    auto features = device.template getFeatures2<
        vk::PhysicalDeviceFeatures2,
        vk::PhysicalDeviceVulkan11Features,
        vk::PhysicalDeviceVulkan13Features,
        vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT
    >();

    bool supportsRequiredFeatures =
        features.template get<vk::PhysicalDeviceVulkan11Features>().shaderDrawParameters &&
        features.template get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering &&
        features.template get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>().extendedDynamicState;

    return supportsRequiredFeatures;
}

void TNgine::VulkanInit::CreateLogicalDevice()
{
	std::vector<vk::QueueFamilyProperties> queueFamilies = m_PhysicalDevice.getQueueFamilyProperties();

	auto graphicsQueueFamilyIt = std::ranges::find_if(queueFamilies, [](auto const& qfp)
		{ 
            return !!(qfp.queueFlags & vk::QueueFlagBits::eGraphics);
        }
    );

    auto graphicsIndex = static_cast<uint32>(std::distance(queueFamilies.begin(), graphicsQueueFamilyIt));

    float32 queuePriority = 0.5f;
    vk::DeviceQueueCreateInfo info{ .queueFamilyIndex = graphicsIndex, .queueCount = 1, .pQueuePriorities = &queuePriority };

    vk::StructureChain<
        vk::PhysicalDeviceFeatures2,
        vk::PhysicalDeviceVulkan11Features,
        vk::PhysicalDeviceVulkan13Features,
        vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT
    > featureChain = {
        {},
        {.shaderDrawParameters = true   },
        {.dynamicRendering = true       },
        {.extendedDynamicState = true   }
    };

    std::vector<const char*> requiredDeviceExtension = { vk::KHRSwapchainExtensionName };

    vk::DeviceCreateInfo createInfo{
        .pNext = &featureChain.get<vk::PhysicalDeviceFeatures2>(),
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &info,
        .enabledExtensionCount = static_cast<uint32>(requiredDeviceExtension.size()),
        .ppEnabledExtensionNames = requiredDeviceExtension.data()
    };

    m_LogicalDevice = vk::raii::Device{ m_PhysicalDevice, createInfo };

    m_GraphicsQueue = vk::raii::Queue{ m_LogicalDevice, graphicsIndex, 0 }; 
}