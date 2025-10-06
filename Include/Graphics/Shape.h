#pragma once

#include <vector>

#include "Core/Color.h"

#include "Transform.h"
#include "AABB.h"
#include "Vertex.h"

class Shape
{
private:
    std::vector<Vertex> vertices;
    std::vector<Vertex> Tvertices;

    AABB boundingBox;

    Color color;
    Color fillColor;

    friend void FillShape(Shape& shape);
    friend void DrawShape(Shape& shape);
public:
    Transform transform;
    
    Shape() {}
    Shape(const std::vector<Vertex>& vertices, Color color = Color::Transparent, Color fillColor = Color::Transparent);
    
    std::vector<Vertex> GetTvertices();
    AABB GetBoundingBox();
    
    void SetColor(Color color);
    void SetFillColor(Color color);
};

std::vector<Vertex> UpdateVertices(Transform &transform, const std::vector<Vertex>& vertices);
AABB UpdateAABB(const std::vector<Vertex>& vertices);