# Helper to set up include directories so consumers can use <Module/header.hpp>
# This file is intentionally simple: it doesn't create files, but provides a function

function(setup_module_includes target)
    # Expose project root to consumers so they can include with <Module/...>
    # and ensure the target itself uses its current source dir for building.
    get_target_property(_type ${target} TYPE)
    if(_type STREQUAL "INTERFACE_LIBRARY")
        target_include_directories(${target} INTERFACE ${CMAKE_SOURCE_DIR})
    else()
        target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
        target_include_directories(${target} PUBLIC  ${CMAKE_SOURCE_DIR})
    endif()
endfunction()
