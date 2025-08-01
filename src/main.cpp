#include <flecs.h>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "sim/components.h"
#include "sim/systems.h"
#include "render/rendering.h"

int main() {
    rendering::InitRaylib();
    
    flecs::world world;

    auto Base = world.prefab()
            .add<Position>()
            .set<Color>(GREEN);

    for (int i = 0; i < 16; ++i) {
        auto e = world.entity().is_a(Base);
        e.set<Position>({i * 50.f + 20.f, 20.f}).add<Velocity>();
        e.set<Target>({static_cast<float>(500. - ((i % 4) * 500.)), static_cast<float>((i % 5) * 250 + 200)});
    }

    world.import<SimulationSystems>();
    world.import<rendering::RenderingSystems>();

    while (!WindowShouldClose()) {
        world.progress(GetFrameTime());
    }
    CloseWindow();

    return 0;
}