#pragma once

#include <vector>

#include "Core/Color.h"

#include "Transform.h"
#include "Vertex.h"

class Shape
{
private:
    std::vector<Vertex> vertices;
    std::vector<Vertex> Tvertices;

    Color color;
    Color fillColor;

    friend void DrawShape(Shape& shape);
public:
    Transform transform;
    
    Shape() {}
    Shape(const std::vector<Vertex>& vertices, Color color, Color fillColor);
    
    std::vector<Vertex> GetTvertices();
    void SetColor(Color color);
    void SetFillColor(Color color);
};

std::vector<Vertex> UpdateVertices(Transform &transform, const std::vector<Vertex>& vertices);