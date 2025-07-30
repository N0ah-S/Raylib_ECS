//
// Created by Noah on 30.07.2025.
//

#ifndef MAPENTITIES_VECMATH_H
#define MAPENTITIES_VECMATH_H

#include "raylib.h"

Vector2& operator+=(Vector2& a, const Vector2 b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

Vector2 operator*(Vector2 a, float scale) {
    return {a.x * scale, a.y * scale};
}

#endif //MAPENTITIES_VECMATH_H
