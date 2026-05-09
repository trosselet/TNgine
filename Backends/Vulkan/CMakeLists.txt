find_package(Vulkan REQUIRED)

file(GLOB_RECURSE VULKAN_HEADERS
    CONFIGURE_DEPENDS
    *.h
)

file(GLOB_RECURSE VULKAN_SRCS
    CONFIGURE_DEPENDS
    *.cpp
)

if(VULKAN_SRCS)
    add_library(VulkanBackend STATIC ${VULKAN_SRCS} ${VULKAN_HEADERS})
    set(VULKAN_IS_INTERFACE OFF)
else()
    add_library(VulkanBackend INTERFACE)
    target_sources(VulkanBackend INTERFACE ${VULKAN_HEADERS})
    set(VULKAN_IS_INTERFACE ON)
endif()

add_library(TNgine::VulkanBackend ALIAS VulkanBackend)

if(VULKAN_IS_INTERFACE)
    # Header-only: expose project root so consumers can include <VulkanBackend/...>
    target_include_directories(VulkanBackend INTERFACE ${CMAKE_SOURCE_DIR})
    target_link_libraries(VulkanBackend INTERFACE TNgine::Core TNgine::RHI Vulkan::Vulkan)
else()
    # Use module dir for building, expose project root to consumers
    target_include_directories(VulkanBackend
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        INTERFACE ${CMAKE_SOURCE_DIR}
    )
    target_link_libraries(VulkanBackend PUBLIC TNgine::Core TNgine::RHI Vulkan::Vulkan)
endif()

if(VULKAN_IS_INTERFACE)
    target_compile_definitions(VulkanBackend INTERFACE VK_NO_PROTOTYPES)
else()
    target_compile_definitions(VulkanBackend PRIVATE VK_NO_PROTOTYPES)
endif()

set_project_warnings(VulkanBackend)
