#pragma once

#include "Core/Color.h"
#include "Vector2.h"

class Vertex
{
public:
    Vector2 position;
    Color color;

    Vertex();
    Vertex(float x, float y, Color color);
    Vertex(Vector2 position, Color color);
};