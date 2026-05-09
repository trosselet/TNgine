file(GLOB_RECURSE RHI_HEADERS
    CONFIGURE_DEPENDS
    *.h
)

file(GLOB_RECURSE RHI_SRCS
    CONFIGURE_DEPENDS
    *.cpp
)

if(RHI_SRCS)
    add_library(RHI STATIC ${RHI_SRCS} ${RHI_HEADERS})
    set(RHI_IS_INTERFACE OFF)
else()
    add_library(RHI INTERFACE)
    target_sources(RHI INTERFACE ${RHI_HEADERS})
    set(RHI_IS_INTERFACE ON)
endif()

add_library(TNgine::RHI ALIAS RHI)

if(RHI_IS_INTERFACE)
    target_include_directories(RHI INTERFACE ${CMAKE_SOURCE_DIR})
    target_link_libraries(RHI INTERFACE TNgine::Core TNgine::Platform)
else()
    target_include_directories(RHI
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        INTERFACE ${CMAKE_SOURCE_DIR}
    )
    target_link_libraries(RHI PUBLIC TNgine::Core TNgine::Platform)
endif()

set_project_warnings(RHI)
