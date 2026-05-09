cmake_minimum_required(VERSION 3.25)

project(TNgine
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) 

# =========================================================
# Output directories
# =========================================================

# For multi-config generators (Visual Studio/Ninja Multi-Config) put outputs in
# configuration-specific subdirectories so the linker can find them.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bin)

# =========================================================
# Modules
# =========================================================

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

include(Options)
include(CompilerWarnings)
include(Dependencies)
include(ShaderCompilation)
include(ModuleIncludes)

# =========================================================
# Subdirectories
# =========================================================

add_subdirectory(Core)
add_subdirectory(Platform)
add_subdirectory(RHI)
add_subdirectory(Assets)
add_subdirectory(Scene)
add_subdirectory(Render)

if(ENGINE_ENABLE_VULKAN)
    add_subdirectory(Backends/Vulkan)
endif()

if(ENGINE_ENABLE_OPENGL)
    add_subdirectory(Backends/OpenGL)
endif()

if(ENGINE_ENABLE_D3D12)
    add_subdirectory(Backends/D3D12)
endif()

add_subdirectory(Application)