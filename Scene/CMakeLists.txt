file(GLOB_RECURSE SCENE_HEADERS
    CONFIGURE_DEPENDS
    *.h
)

file(GLOB_RECURSE SCENE_SRCS
    CONFIGURE_DEPENDS
    *.cpp
)

if(SCENE_SRCS)
    add_library(Scene STATIC ${SCENE_SRCS} ${SCENE_HEADERS})
    set(SCENE_IS_INTERFACE OFF)
else()
    add_library(Scene INTERFACE)
    target_sources(Scene INTERFACE ${SCENE_HEADERS})
    set(SCENE_IS_INTERFACE ON)
endif()

add_library(TNgine::Scene ALIAS Scene)

if(SCENE_IS_INTERFACE)
    target_include_directories(Scene INTERFACE ${CMAKE_SOURCE_DIR})
    target_link_libraries(Scene INTERFACE TNgine::Core TNgine::Assets EnTT::EnTT)
else()
    target_include_directories(Scene
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        INTERFACE ${CMAKE_SOURCE_DIR}
    )
    target_link_libraries(Scene PUBLIC TNgine::Core TNgine::Assets EnTT::EnTT)
endif()

set_project_warnings(Scene)
