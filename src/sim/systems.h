//
// Created by Noah on 30.07.2025.
//

#ifndef MAPENTITIES_SYSTEMS_H
#define MAPENTITIES_SYSTEMS_H

#include <flecs.h>
#include <raymath.h>

#include "components.h"

struct SimulationSystems {
    explicit SimulationSystems(flecs::world& world) {
        world.module<SimulationSystems>();

        world.system<Position, const Velocity>("Move").kind(flecs::OnUpdate)
                .each([](flecs::iter& it, size_t, Position& p, const Velocity &v) {
                    p += v * it.delta_time();
                });
    }
};

#endif //MAPENTITIES_SYSTEMS_H
