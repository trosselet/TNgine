file(GLOB_RECURSE RHI_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(RHI STATIC ${RHI_SOURCES})

add_library(Engine::RHI ALIAS RHI)

target_include_directories(RHI
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(RHI
PUBLIC
    Engine::Core
    Engine::Platform
)

set_project_warnings(RHI)