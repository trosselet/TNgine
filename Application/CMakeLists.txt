file(GLOB_RECURSE APP_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_executable(Application ${APP_SOURCES})

set_target_properties(Application
PROPERTIES
    OUTPUT_NAME "TNgine"
)

target_include_directories(Application
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Application
PRIVATE
    Engine::Core
    Engine::Platform
    Engine::RHI
    Engine::Assets
    Engine::Scene
    Engine::Render
)

if(ENGINE_ENABLE_VULKAN)
    target_link_libraries(Application
    PRIVATE
        Engine::VulkanBackend
    )
endif()

set_project_warnings(Application)