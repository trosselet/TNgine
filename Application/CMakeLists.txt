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
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(Application
PRIVATE
    TNgine::Core
    TNgine::Platform
    TNgine::RHI
    TNgine::Assets
    TNgine::Scene
    TNgine::Render
)

if(ENGINE_ENABLE_VULKAN)
    target_link_libraries(Application
    PRIVATE
        TNgine::VulkanBackend
    )
endif()
if(ENGINE_ENABLE_OPENGL)
    target_link_libraries(Application
    PRIVATE
        TNgine::OpenGLBackend
    )
endif()

if(ENGINE_ENABLE_D3D12)
    target_link_libraries(Application
    PRIVATE
        TNgine::D3D12Backend
    )
endif()

# =========================================================
# Assets
# =========================================================

set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Content/Assets")
set(ASSETS_OUTPUT_DIR "$<TARGET_FILE_DIR:Application>/Assets")

add_custom_command(TARGET Application POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${ASSETS_SOURCE_DIR}"
            "${ASSETS_OUTPUT_DIR}"
    COMMENT "Copying assets..."
)

set_project_warnings(Application)