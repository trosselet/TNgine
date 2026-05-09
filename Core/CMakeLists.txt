file(GLOB_RECURSE CORE_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
    *.hpp
)

add_library(Core STATIC ${CORE_SOURCES})

add_library(Engine::Core ALIAS Core)

# =========================================================
# Includes
# =========================================================

target_include_directories(Core
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# =========================================================
# Dependencies
# =========================================================

target_link_libraries(Core
PUBLIC
    spdlog::spdlog
)

# =========================================================
# Compile Definitions
# =========================================================

target_compile_definitions(Core
PUBLIC
    NOMINMAX
)

# =========================================================
# Warnings
# =========================================================

set_project_warnings(Core)