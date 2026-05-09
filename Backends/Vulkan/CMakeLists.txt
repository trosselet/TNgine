find_package(Vulkan REQUIRED)

file(GLOB_RECURSE VULKAN_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(VulkanBackend STATIC ${VULKAN_SOURCES})

add_library(Engine::VulkanBackend ALIAS VulkanBackend)

target_include_directories(VulkanBackend
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(VulkanBackend
PUBLIC
    Engine::Core
    Engine::RHI
    Vulkan::Vulkan
)

# VMA
# spirv-cross
# volk

target_compile_definitions(VulkanBackend
PRIVATE
    VK_NO_PROTOTYPES
)

set_project_warnings(VulkanBackend)