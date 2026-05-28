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


	private:
		vk::raii::Context m_Context;
		vk::raii::Instance m_Instance = nullptr;

	};
}

#endif // !VulkanInit_H
