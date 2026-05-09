file(GLOB_RECURSE CORE_HEADERS
    CONFIGURE_DEPENDS
    *.h
    *.hpp
)

file(GLOB_RECURSE CORE_SRCS
    CONFIGURE_DEPENDS
    *.cpp
)

if(CORE_SRCS)
    add_library(Core STATIC ${CORE_SRCS} ${CORE_HEADERS})
    set(CORE_IS_INTERFACE OFF)
else()
    # Header-only / interface library
    add_library(Core INTERFACE)
    target_sources(Core INTERFACE ${CORE_HEADERS})
    set(CORE_IS_INTERFACE ON)
endif()

add_library(TNgine::Core ALIAS Core)

if(CORE_IS_INTERFACE)
    # Header-only: expose project root so consumers can include <Core/...>
    target_include_directories(Core INTERFACE ${CMAKE_SOURCE_DIR})
    target_link_libraries(Core INTERFACE spdlog::spdlog)
    target_compile_definitions(Core INTERFACE NOMINMAX)
else()
    # For compiled library: use module dir for building, expose project root to consumers
    target_include_directories(Core
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        INTERFACE ${CMAKE_SOURCE_DIR}
    )
    target_link_libraries(Core PUBLIC spdlog::spdlog)
    target_compile_definitions(Core PUBLIC NOMINMAX)
endif()

message(STATUS "Core headers: ${CORE_HEADERS}")
message(STATUS "Core sources: ${CORE_SRCS}")

set_project_warnings(Core)
