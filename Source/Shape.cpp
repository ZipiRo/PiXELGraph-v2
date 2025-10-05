#include <limits>

#include "Graphics/Transform.h"
#include "Graphics/Shape.h"

#include "Console/Debug.h"

Shape::Shape(const std::vector<Vertex> &vertices, Color color, Color fillColor) 
{
    this->vertices = vertices;

    this->color = color;
    this->fillColor = fillColor;

    boundingBox = UpdateAABB(vertices);

    for(auto& vertex : this->vertices)
        vertex.color = this->color;
}

std::vector<Vertex> UpdateVertices(Transform &transfrom, const std::vector<Vertex> &vertices)
{
    std::vector<Vertex> Tvertices;

    transfrom.SinCosUpdate();

    for (auto& vertex : vertices)
        Tvertices.emplace_back(Vertex(
            TransformVertex(transfrom, vertex.position),
            vertex.color
        ));
    
    return Tvertices;
}

AABB UpdateAABB(const std::vector<Vertex> &vertices)
{
    int left = INT_MAX;
    int top = INT_MAX;
    int right = INT_MIN;
    int bottom = INT_MIN;

    for(const auto& vertex : vertices)
    {
        if(vertex.position.x < left) left = vertex.position.x;
        if(vertex.position.y < top) top = vertex.position.y;

        if(vertex.position.x > right) right = vertex.position.x;
        if(vertex.position.y > bottom) bottom = vertex.position.y;
    }

    return AABB(left, top, right, bottom);
}

std::vector<Vertex> Shape::GetTvertices()
{
    if(transform.update)
    {
        Tvertices = UpdateVertices(transform, vertices);
        transform.update = false;
    }

    return Tvertices;
}

AABB Shape::GetBoundingBox()
{
    if(transform.update)
    {
        Tvertices = UpdateVertices(transform, vertices);
        boundingBox = UpdateAABB(Tvertices);
        transform.update = false;
    }

    return boundingBox;
}

void Shape::SetColor(Color color)
{
    this->color = color;
    for(auto& vertex : vertices)
        vertex.color = this->color;
}


void Shape::SetFillColor(Color color)
{
    fillColor = color;
}