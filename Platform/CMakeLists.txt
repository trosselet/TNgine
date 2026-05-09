file(GLOB_RECURSE PLATFORM_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(Platform STATIC ${PLATFORM_SOURCES})

add_library(Engine::Platform ALIAS Platform)

target_include_directories(Platform
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Platform
PUBLIC
    Engine::Core
    glfw
)

set_project_warnings(Platform)