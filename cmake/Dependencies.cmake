include(FetchContent)

# =========================================================
# GLFW
# =========================================================

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

# =========================================================
# SPDLOG
# =========================================================

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.14.1
)

FetchContent_MakeAvailable(spdlog)

# =========================================================
# ENTT
# =========================================================

FetchContent_Declare(
    entt
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.13.2
)

FetchContent_MakeAvailable(entt)

# =========================================================
# TINYGLTF
# =========================================================

FetchContent_Declare(
    tinygltf
    GIT_REPOSITORY https://github.com/syoyo/tinygltf.git
    GIT_TAG release
)

FetchContent_MakeAvailable(tinygltf)