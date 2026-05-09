function(set_project_warnings target)

    if(MSVC)
        target_compile_options(${target} PRIVATE
            /W4
            /permissive-
            /MP
        )
    else()
        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wshadow
        )
    endif()

endfunction()