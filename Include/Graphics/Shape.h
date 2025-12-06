#pragma once

#include <vector>

#include "Core/Color.h"

#include "Transform.h"
#include "BoundingBox.h"
#include "Vertex.h"

class Shape
{
protected:
    std::vector<Vertex> vertices;

private:
    std::vector<Vertex> Tvertices;
    std::vector<Vertex> VTvertices;

    BoundingBox boundingBox;
    BoundingBox VBoundingBox;

    Color color;
    Color fillColor;

    int lineThickness;

    friend void DrawShape(Shape &shape);
    Shape() {}

public:
    Transform transform;

    Shape(const std::vector<Vertex> &vertices);

    std::vector<Vertex> GetTvertices();
    BoundingBox GetBoundingBox();

    void SetColor(Color color);
    void SetFillColor(Color color);
    void SetLineThickness(int thickness);
};

std::vector<Vertex> UpdateVertices(Transform &transform, const std::vector<Vertex> &vertices);
BoundingBox UpdateAABB(const std::vector<Vertex> &vertices);