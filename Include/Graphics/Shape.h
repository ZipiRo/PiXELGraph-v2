#pragma once

#include <vector>

#include "Core/Color.h"

#include "Transform.h"
#include "Vertex.h"

class Shape
{
private:
    std::vector<Vertex> vertices;

    Color color;
    Color fillColor;

    friend void DrawShape(Shape& shape);
public:
    Transform transform;
    
    Shape() {}
    Shape(const std::vector<Vertex>& vertices, Color color, Color fillColor);
};