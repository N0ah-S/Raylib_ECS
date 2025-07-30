//
// Created by Noah on 30.07.2025.
//

#ifndef MAPENTITIES_RENDERING_H
#define MAPENTITIES_RENDERING_H

#include <flecs.h>
#include <raymath.h>

#include "../sim/components.h"

struct RenderingSystems {
    explicit RenderingSystems(flecs::world& world) {
        world.module<RenderingSystems>();


        world.system("Render.Setup")
                .kind(flecs::PreStore)
                .run([](flecs::iter& it) {
                    BeginDrawing();
                    ClearBackground(RAYWHITE);
                    DrawText("raylib colors palette", 28, 42, 20, BLACK);
                });

        world.system<Position>("Render").kind(flecs::OnStore)
                .run([](flecs::iter& it) {
                    while (it.next()) {
                        auto p = it.field<Position>(0);

                        DrawRectangleRec({p->x, p->y, 10, 10}, RED);
                    }

                });

        world.system("Render.Finalize")
                .kind(flecs::PostFrame)
                .run([](flecs::iter& it) {
                    EndDrawing();
                });
    }
};

#endif //MAPENTITIES_RENDERING_H
