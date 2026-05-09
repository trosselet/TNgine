file(GLOB_RECURSE ASSETS_HEADERS
    CONFIGURE_DEPENDS
    *.h
)

file(GLOB_RECURSE ASSETS_SRCS
    CONFIGURE_DEPENDS
    *.cpp
)

if(ASSETS_SRCS)
    add_library(Assets STATIC ${ASSETS_SRCS} ${ASSETS_HEADERS})
    set(ASSETS_IS_INTERFACE OFF)
else()
    add_library(Assets INTERFACE)
    target_sources(Assets INTERFACE ${ASSETS_HEADERS})
    set(ASSETS_IS_INTERFACE ON)
endif()

add_library(TNgine::Assets ALIAS Assets)

if(ASSETS_IS_INTERFACE)
    target_include_directories(Assets INTERFACE ${CMAKE_SOURCE_DIR})
    target_link_libraries(Assets INTERFACE TNgine::Core)
else()
    target_include_directories(Assets
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        INTERFACE ${CMAKE_SOURCE_DIR}
    )
    target_link_libraries(Assets PUBLIC TNgine::Core)
endif()

# tinygltf / stb / assimp
if(ASSETS_IS_INTERFACE)
    target_link_libraries(Assets INTERFACE tinygltf)
else()
    target_link_libraries(Assets PRIVATE tinygltf)
endif()

set_project_warnings(Assets)
