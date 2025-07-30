cmake_minimum_required(VERSION 3.28)
project(MapEntities)

set(CMAKE_CXX_STANDARD 20)

#find_package(protobuf CONFIG REQUIRED)
#find_package(mapnik CONFIG REQUIRED)
find_package(flecs CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)

add_executable(MapEntities src/main.cpp
        src/util/vecmath.h
        src/sim/components.h
        src/sim/systems.h
        src/render/rendering.h)

target_link_libraries(MapEntities PRIVATE flecs::flecs_static raylib)