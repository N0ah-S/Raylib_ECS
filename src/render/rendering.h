//
// Created by Noah on 30.07.2025.
//

#ifndef MAPENTITIES_RENDERING_H
#define MAPENTITIES_RENDERING_H

#include <flecs.h>
#include <raymath.h>
#include <GLFW/glfw3.h>
#include <cstdio>

#include "../sim/components.h"

#define RETURN it.fini();\
                return;

Camera2D camera = { 0 };
flecs::entity selected;

void InitRaylib() {
    glfwWindowHint(GLFW_SAMPLES, 8);
    InitWindow(800, 600, "Raylib FLECS Test");
    SetTargetFPS(60);

    camera.target = (Vector2){ 800/2.0f, 600/2.0f };
    camera.offset = (Vector2){ 800/2.0f, 600/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

struct InRenderRange {};

struct RenderingSystems {

    static void UnitCommand(flecs::iter& it) {
        if(!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            RETURN;
        }
        if(selected.is_valid()) {
            Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camera);
            selected.set<>((Target) mouse);
            selected.set<>(BLUE);
            selected = it.world().entity(0);
        }

        const int TOLERANCE = 10 * 10;
        Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camera) - Vector2 {5, 5};
        while (it.next()) {
            auto p = it.field<Position>(0);
            auto color = it.field<Color>(1);

            for (auto i : it) {
                if(Vector2LengthSqr((p[i] - mouse)) < TOLERANCE) {
                    selected = it.entity(i);
                    color[i] = PINK;
                    RETURN
                }
            }
        }
        selected = it.world().entity(0); // Invalid entity
    }

    explicit RenderingSystems(flecs::world& world) {
        world.module<RenderingSystems>();

        world.system<Position, Color>()
                .kind(flecs::PreUpdate)
                .with<InRenderRange>()
                .run(UnitCommand);

        world.system<Position>()
                .kind(flecs::PreStore)
                .run([](flecs::iter& it){
                    constexpr float BORDER = -30;
                    const float minX = camera.target.x - camera.offset.x - BORDER;
                    const float minY = camera.target.y - camera.offset.y - BORDER;
                    const float maxX = camera.target.x + camera.offset.x + BORDER;
                    const float maxY = camera.target.y + camera.offset.y + BORDER;

                    while (it.next()) {
                        auto p = it.field<Position>(0);

                        for (auto i: it) {
                            if (p[i].x < minX || p[i].y < minY || p[i].x > maxX || p[i].y > maxY) {
                                it.entity(i).remove<InRenderRange>();
                            } else {
                                it.entity(i).add<InRenderRange>();
                            }
                        }
                    }

                });

        world.system("Render.Setup")
                .kind(flecs::PreStore)
                .run([](flecs::iter& it) {
                    BeginDrawing();
                    ClearBackground(BROWN);
                    BeginMode2D(camera);
                });

        world.system<Position, Color>("Render")
                .kind(flecs::OnStore)
                .with<InRenderRange>()
                .each([](flecs::iter& it, size_t, Position& p, Color& color) {
                    //DrawTextureEx(texture, p, 0, 1., WHITE);
                    DrawRectangleRec({p.x, p.y, 10, 10}, color);
                });

        world.system("Render.Finalize")
                .kind(flecs::PostFrame)
                .run([](flecs::iter& it) {
                    EndMode2D();
                    DrawText("Fun Stuff", 28, 42, 20, BLACK);
                    EndDrawing();
                });
    }
};



#endif //MAPENTITIES_RENDERING_H
