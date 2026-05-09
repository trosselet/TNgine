file(GLOB_RECURSE PLATFORM_HEADERS
    CONFIGURE_DEPENDS
    *.h
)

file(GLOB_RECURSE PLATFORM_SRCS
    CONFIGURE_DEPENDS
    *.cpp
)

if(PLATFORM_SRCS)
    add_library(Platform STATIC ${PLATFORM_SRCS} ${PLATFORM_HEADERS})
    set(PLATFORM_IS_INTERFACE OFF)
else()
    add_library(Platform INTERFACE)
    target_sources(Platform INTERFACE ${PLATFORM_HEADERS})
    set(PLATFORM_IS_INTERFACE ON)
endif()

add_library(TNgine::Platform ALIAS Platform)

if(PLATFORM_IS_INTERFACE)
    target_include_directories(Platform INTERFACE ${CMAKE_SOURCE_DIR})
    target_link_libraries(Platform INTERFACE TNgine::Core glfw)
else()
    target_include_directories(Platform
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        INTERFACE ${CMAKE_SOURCE_DIR}
    )
    target_link_libraries(Platform PUBLIC TNgine::Core glfw)
endif()

set_project_warnings(Platform)
