# =========================================================
# Global Build Options
# =========================================================

option(ENGINE_BUILD_SHARED "Build engine as shared libraries" OFF)
option(ENGINE_BUILD_TESTS "Build unit tests" OFF)
option(ENGINE_BUILD_EDITOR "Build editor application" ON)

# =========================================================
# Rendering Backends
# =========================================================

option(ENGINE_ENABLE_VULKAN "Enable Vulkan backend" ON)
option(ENGINE_ENABLE_OPENGL "Enable OpenGL backend" OFF)
option(ENGINE_ENABLE_D3D12 "Enable Direct3D12 backend" OFF)

# =========================================================
# Debug / Validation
# =========================================================

option(ENGINE_ENABLE_VALIDATION "Enable graphics validation layers" ON)
option(ENGINE_ENABLE_PROFILING "Enable profiling instrumentation" ON)
option(ENGINE_ENABLE_ASSERTS "Enable runtime asserts" ON)
option(ENGINE_ENABLE_LOGGING "Enable logging system" ON)

# =========================================================
# Compiler Features
# =========================================================

option(ENGINE_ENABLE_LTO "Enable link time optimization" OFF)
option(ENGINE_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
option(ENGINE_ENABLE_PCH "Enable precompiled headers" ON)

# =========================================================
# Platform Specific
# =========================================================

if(WIN32)

    add_compile_definitions(
        ENGINE_PLATFORM_WINDOWS
        NOMINMAX
        WIN32_LEAN_AND_MEAN
    )

elseif(APPLE)

    add_compile_definitions(
        ENGINE_PLATFORM_MACOS
    )

elseif(UNIX)

    add_compile_definitions(
        ENGINE_PLATFORM_LINUX
    )

endif()

# =========================================================
# Build Type Defines
# =========================================================

if(CMAKE_BUILD_TYPE STREQUAL "Debug")

    add_compile_definitions(
        ENGINE_DEBUG
    )

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")

    add_compile_definitions(
        ENGINE_RELEASE
    )

elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")

    add_compile_definitions(
        ENGINE_RELWITHDEBINFO
    )

endif()

# =========================================================
# Assertions
# =========================================================

if(ENGINE_ENABLE_ASSERTS)

    add_compile_definitions(
        ENGINE_ENABLE_ASSERTS
    )

endif()

# =========================================================
# Logging
# =========================================================

if(ENGINE_ENABLE_LOGGING)

    add_compile_definitions(
        ENGINE_ENABLE_LOGGING
    )

endif()

# =========================================================
# Profiling
# =========================================================

if(ENGINE_ENABLE_PROFILING)

    add_compile_definitions(
        ENGINE_ENABLE_PROFILING
    )

endif()

# =========================================================
# LTO
# =========================================================

if(ENGINE_ENABLE_LTO)

    include(CheckIPOSupported)

    check_ipo_supported(
        RESULT supported
    )

    if(supported)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()

endif()

# =========================================================
# Unity Build
# =========================================================

if(ENGINE_ENABLE_UNITY_BUILD)

    set(CMAKE_UNITY_BUILD ON)

endif()