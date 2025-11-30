#pragma once 

#include <string>
#include <vector>

#include "Vertex.h"
#include "Transform.h"
#include "BoundingBox.h"

class Text
{
protected:
    std::vector<Vertex> vertices;

private:
    std::vector<Vertex> Tvertices;
    std::vector<int> indices;

    BoundingBox boundingBox;

    Color color;

    int font_weight;
    int font_size;

    std::string string;

    friend void DrawTEXT(Text& text);

public:
    Text();

    Transform transform;

    std::vector<Vertex> GetTvertices();
    BoundingBox GetBoundingBox();

    void SetString(const std::string &text);
    void SetFontSize(int size);
    void SetFontWeight(int weight);

    void SetColor(Color color);
};