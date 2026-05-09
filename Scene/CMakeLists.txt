file(GLOB_RECURSE SCENE_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(Scene STATIC ${SCENE_SOURCES})

add_library(Engine::Scene ALIAS Scene)

target_include_directories(Scene
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Scene
PUBLIC
    Engine::Core
    Engine::Assets
    EnTT::EnTT
)

set_project_warnings(Scene)