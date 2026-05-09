file(GLOB_RECURSE ASSETS_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(Assets STATIC ${ASSETS_SOURCES})

add_library(Engine::Assets ALIAS Assets)

target_include_directories(Assets
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Assets
PUBLIC
    Engine::Core
)

# tinygltf / stb / assimp si besoin

target_link_libraries(Assets
PRIVATE
    tinygltf
)

set_project_warnings(Assets)