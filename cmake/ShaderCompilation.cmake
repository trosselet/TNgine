function(compile_shader TARGET SHADER)

    get_filename_component(FILE_NAME ${SHADER} NAME)

    set(SPIRV "${CMAKE_BINARY_DIR}/Shaders/${FILE_NAME}.spv")

    add_custom_command(
        OUTPUT ${SPIRV}

        COMMAND dxc
        -spirv
        -T vs_6_0
        ${SHADER}
        -Fo ${SPIRV}

        DEPENDS ${SHADER}
    )

    target_sources(${TARGET} PRIVATE ${SPIRV})

endfunction()