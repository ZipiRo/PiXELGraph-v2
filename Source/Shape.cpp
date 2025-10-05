#include "Graphics/Transform.h"
#include "Graphics/Shape.h"

Shape::Shape(const std::vector<Vertex> &vertices, Color color, Color fillColor) 
{
    this->vertices = vertices;
    this->color = color;
    this->fillColor = fillColor;

    for(auto& vertex : this->vertices)
        vertex.color = this->color;
}