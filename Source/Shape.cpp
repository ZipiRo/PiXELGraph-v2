#include "Graphics/Transform.h"
#include "Graphics/Shape.h"

#include "Console/Debug.h"

Shape::Shape(const std::vector<Vertex> &vertices, Color color, Color fillColor) 
{
    this->vertices = vertices;

    this->color = color;
    this->fillColor = fillColor;

    for(auto& vertex : this->vertices)
        vertex.color = this->color;
}

std::vector<Vertex> UpdateVertices(Transform &transfrom, const std::vector<Vertex> &vertices)
{
    std::vector<Vertex> Tvertices;

    transfrom.SinCosUpdate();

    for (auto& vertex : vertices){
        Tvertices.emplace_back(Vertex(
            TransformVertex(transfrom, vertex.position),
            vertex.color
        ));
        
    }
    
    return Tvertices;
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