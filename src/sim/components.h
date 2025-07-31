//
// Created by Noah on 30.07.2025.
//

#ifndef MAPENTITIES_COMPONENTS_H
#define MAPENTITIES_COMPONENTS_H
#include "raylib.h"

constexpr float POSITION_TOLERANCE = 1;

struct Position : Vector2 {};
struct Velocity : Vector2 {};

struct Target : Vector2 {};

#endif //MAPENTITIES_COMPONENTS_H
