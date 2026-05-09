file(GLOB_RECURSE RENDER_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(Render STATIC ${RENDER_SOURCES})

add_library(Engine::Render ALIAS Render)

target_include_directories(Render
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Render
PUBLIC
    Engine::Core
    Engine::Assets
    Engine::RHI
)

set_project_warnings(Render)