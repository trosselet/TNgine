file(GLOB_RECURSE RENDER_HEADERS
    CONFIGURE_DEPENDS
    *.h
)

file(GLOB_RECURSE RENDER_SRCS
    CONFIGURE_DEPENDS
    *.cpp
)

if(RENDER_SRCS)
    add_library(Render STATIC ${RENDER_SRCS} ${RENDER_HEADERS})
    set(RENDER_IS_INTERFACE OFF)
else()
    add_library(Render INTERFACE)
    target_sources(Render INTERFACE ${RENDER_HEADERS})
    set(RENDER_IS_INTERFACE ON)
endif()

add_library(TNgine::Render ALIAS Render)

if(RENDER_IS_INTERFACE)
    target_include_directories(Render INTERFACE ${CMAKE_SOURCE_DIR})
    target_link_libraries(Render INTERFACE TNgine::Core TNgine::Assets TNgine::RHI)
else()
    target_include_directories(Render
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        INTERFACE ${CMAKE_SOURCE_DIR}
    )
    target_link_libraries(Render PUBLIC TNgine::Core TNgine::Assets TNgine::RHI)
endif()

set_project_warnings(Render)
