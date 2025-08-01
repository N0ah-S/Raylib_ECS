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
#include "lunasvg.h"

Camera2D camera = { 0 };
Texture2D texture;
lunasvg::Bitmap bitmap;
void InitRaylib() {
    glfwWindowHint(GLFW_SAMPLES, 8);
    InitWindow(800, 600, "Raylib FLECS Test");
    SetTargetFPS(60);

    auto document = lunasvg::Document::loadFromFile("../assets/svg/Rettungswesen_Fahrzeuge/KTW.svg");

     bitmap = document->renderToBitmap(32,32);
    //bitmap.writeToPng("../assets/png/s/KTW.png");

    Image image = {
            .data = bitmap.data(),
            .width = bitmap.width(),
            .height = bitmap.height(),
            .mipmaps = 1, //ARGB32_
            .format = PIXELFORMAT_UNCOMPRESSED_R16G16B16A16   ,
    };     // Loaded in CPU memory (RAM)
    texture = LoadTextureFromImage(image);


    camera.target = (Vector2){ 800/2.0f, 600/2.0f };
    camera.offset = (Vector2){ 800/2.0f, 600/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

struct InRenderRange {};

struct RenderingSystems {
    explicit RenderingSystems(flecs::world& world) {
        world.module<RenderingSystems>();

        world.system<Position, Color>()
                .kind(flecs::PreStore)
                .each([](flecs::entity e, const Position& p, Color& c){
                    constexpr float BORDER = -30;
                    const float minX = camera.target.x - camera.offset.x - BORDER;
                    const float minY = camera.target.y - camera.offset.y - BORDER;
                    const float maxX = camera.target.x + camera.offset.x + BORDER;
                    const float maxY = camera.target.y + camera.offset.y + BORDER;
                    if(p.x < minX || p.y < minY || p.x > maxX || p.y > maxY) {
                        e.remove<InRenderRange>();
                    } else {
                        e.add<InRenderRange>();
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
                    DrawTextureEx(texture, p, 0, 1., WHITE);
                    DrawRectangleRec({p.x, p.y, 10, 10}, color);
                });

        world.system("Render.Finalize")
                .kind(flecs::PostFrame)
                .run([](flecs::iter& it) {
                    //EndMode2D();
                    DrawText("Fun Stuff", 28, 42, 20, BLACK);
                    EndDrawing();
                });
    }
};



#endif //MAPENTITIES_RENDERING_H
