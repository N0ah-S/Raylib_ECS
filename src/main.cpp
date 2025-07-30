#include <flecs.h>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "sim/components.h"
#include "sim/systems.h"
#include "render/rendering.h"

int main() {

    InitWindow(800, 600, "Raylib FLECS Test");
    SetTargetFPS(60);

    flecs::world world;
    auto e = world.entity();
    e.set<Position>({10, 20})
            .set<Velocity>({10, 20});

    world.import<SimulationSystems>();
    world.import<RenderingSystems>();


    while (!WindowShouldClose()) {
        world.progress(GetFrameTime());
    }

    CloseWindow();


    return 0;
}