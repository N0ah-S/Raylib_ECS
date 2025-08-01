cmake_minimum_required(VERSION 3.28)
project(MapEntities)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        lunasvg
        GIT_REPOSITORY https://github.com/sammycage/lunasvg.git
        GIT_TAG master  # Specify the desired branch or tag
)
FetchContent_MakeAvailable(lunasvg)
#find_package(protobuf CONFIG REQUIRED)
#find_package(mapnik CONFIG REQUIRED)
find_package(flecs CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(lunasvg REQUIRED)

add_executable(MapEntities src/main.cpp
        src/util/vecmath.h
        src/sim/components.h
        src/sim/systems.h
        src/render/rendering.h)

target_link_libraries(MapEntities PRIVATE flecs::flecs_static raylib lunasvg::lunasvg glfw OpenGL::GL)