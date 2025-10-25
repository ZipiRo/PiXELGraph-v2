#pragma once 

#include <string>
#include <vector>

#include "Vertex.h"
#include "Transform.h"
#include "AABB.h"

class Text
{
protected:
    std::vector<Vertex> vertices;

private:
    std::vector<Vertex> Tvertices;
    std::vector<Vertex> cameraTvertices;

    std::vector<int> indices;

    AABB boundingBox;
    AABB cameraBoundingBox;

    Color color;
    Color fillColor;

    std::string string;

    friend void DrawText(Text& text);

public:
    Text();

    Transform transform;

    std::vector<Vertex> GetTvertices();
    AABB GetBoundingBox();

    void SetString(const std::string &text);

    void SetColor(Color color);
    void SetFillColor(Color color);
};