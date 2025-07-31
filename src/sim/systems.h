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

        world.system<Position, const Velocity>("Move").kind(flecs::PostUpdate)
                .each([](flecs::iter& it, size_t, Position& p, const Velocity &v) {
                    p += v * it.delta_time();
                });

        world.system<const Position, Velocity, Target>("ToTarget").kind(flecs::OnUpdate)
                .each([](flecs::iter& it, size_t id, const Position& pos, Velocity &vel, const Target& target) {
                    if(Vector2DistanceSqr(pos, target) < POSITION_TOLERANCE) {
                        vel = {0,0};
                        printf("Bye");
                        it.entity(id).remove<Target>();
                    } else {
                        //ToDo:: Do once or at target change
                        Vector2 diff = Vector2Add(pos * (-1), target);
                        vel = (Velocity) (diff * 50 / Vector2Length(diff));
                    }
                });
    }
};

#endif //MAPENTITIES_SYSTEMS_H
