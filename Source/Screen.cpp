#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include "UMath.h"
#include "Console/Debug.h"

#include "Graphics/Vertex.h"
#include "Core/ViewPort.h"
#include "Core/Screen.h"

#define RESET_CURSOR_POSITION "\033[H";

int Screen::ScreenWidth = 0;
int Screen::ScreenHeight = 0;
Color Screen::BacgroundColor = Color::White;

Screen &Screen::GetInstance()
{
    static Screen instance;
    return instance;
}

void Screen::SetView(const View &view)
{
    auto &instance = GetInstance();
    instance.viewPort = view;
}

View &Screen::GetView()
{
    auto &instance = GetInstance();
    return instance.viewPort;
}

void Screen::SetParameters(int WindowWidth, int WindowHeight)
{
    ScreenWidth = WindowWidth;
    ScreenHeight = WindowHeight;

    ScreenBuffer = std::vector<Color>(ScreenWidth * ScreenHeight);
}

void Screen::Display()
{
    auto &instance = GetInstance();

    std::ostringstream buffer;
    buffer << RESET_CURSOR_POSITION;

    Color lastColor = Color(-1, -1, -1);
    for (int i = 0; i < instance.ScreenWidth * instance.ScreenHeight; i++)
    {
        if (instance.ScreenBuffer[i] != lastColor)
        {
            buffer << "\033[48;2;" << instance.ScreenBuffer[i].r << ';' << instance.ScreenBuffer[i].g << ';' << instance.ScreenBuffer[i].b << "m";
            lastColor = instance.ScreenBuffer[i];
        }
        buffer << ' ';

        if ((i + 1) % instance.ScreenWidth == 0 && (i + 1) % (instance.ScreenWidth * instance.ScreenHeight) != 0)
            buffer << '\n';
    }

    std::cout << buffer.str();
}

void Screen::Clear()
{
    auto &instance = GetInstance();
    std::fill(instance.ScreenBuffer.begin(), instance.ScreenBuffer.end(), BacgroundColor);
}

int Screen::Width() { return ScreenWidth - 1; }
int Screen::Height() { return ScreenHeight - 1; }

void PlotPixel(int x, int y, Color color)
{
    auto& screenInstance = Screen::GetInstance();

    Color pixelColor = color;

    if (x >= 0 && x < Screen::ScreenWidth && y >= 0 && y < Screen::ScreenHeight)
    {
        
#ifdef TRANSPARENCY
        Color lastColor = screenInstance.ScreenBuffer[y * Screen::ScreenWidth + x];

        float inverseAlpha = 1.0f - color.a;

        pixelColor = Color(
            (color.r * color.a) + (lastColor.r * inverseAlpha), 
            (color.g * color.a) + (lastColor.g * inverseAlpha), 
            (color.b * color.a) + (lastColor.b * inverseAlpha),
            color.a
        );
#endif

        screenInstance.ScreenBuffer[y * Screen::ScreenWidth + x] = pixelColor;        
    }
}

void DrawLine(int x1, int y1, int x2, int y2, Color color)
{
    // Initialize variables
    int x, y;               // Current pixel coordinates
    int dx = x2 - x1;       // Difference in x-coordinates
    int dy = y2 - y1;       // Difference in y-coordinates
    int dx1 = abs(dx);      // Absolute value of dx
    int dy1 = abs(dy);      // Absolute value of dy
    int px = 2 * dy1 - dx1; // Decision parameter for shallow slopes
    int py = 2 * dx1 - dy1; // Decision parameter for steep slopes
    int xe, ye, i;          // Loop control variables

    // Case 1: Line with a shallow slope (|dy| <= |dx|)
    if (dy1 <= dx1)
    {
        // Determine starting and ending points for iteration
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        {
            x = x2;
            y = y2;
            xe = x1;
        }

        // Draw the first pixel
        PlotPixel(x, y, color);

        // Draw the rest of the line
        for (i = 0; x < xe; ++i)
        {
            x = x + 1; // Increment x-coordinate
            if (px < 0)
            {
                // Keep y constant
                px = px + 2 * dy1;
            }
            else
            {
                // Increment or decrement y based on line direction
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    y = y + 1;
                else
                    y = y - 1;

                px = px + 2 * (dy1 - dx1);
            }

            // Draw the current pixel
            PlotPixel(x, y, color);
        }
    }
    // Case 2: Line with a steep slope (|dy| > |dx|)
    else
    {
        // Determine starting and ending points for iteration
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }

        // Draw the first pixel
        PlotPixel(x, y, color);

        // Draw the rest of the line
        for (i = 0; y < ye; ++i)
        {
            y = y + 1; // Increment y-coordinate
            if (py <= 0)
            {
                // Keep x constant
                py = py + 2 * dx1;
            }
            else
            {
                // Increment or decrement x based on line direction
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    x = x + 1;
                else
                    x = x - 1;

                py = py + 2 * (dx1 - dy1);
            }

            // Draw the current pixel
            PlotPixel(x, y, color);
        }
    }
}

void DrawRectangle(int x, int y, int width, int height, Color color)
{
    width = width + x;
    height = height + y;

    DrawLine(x, y, width, y, color);
    DrawLine(width, y, width, height, color);
    DrawLine(width, height, x, height, color);
    DrawLine(x, height, x, y, color);
}

void DrawElipse(int x, int y, int radius, Color color, int point_count)
{
    float rez = (2 * PI) / point_count;
    float last_X, last_Y, f_X, f_Y;

    for (float angle = 0.0f; angle <= 2 * PI; angle += rez)
    {
        float new_X = cos(angle) * radius;
        float new_Y = sin(angle) * radius;

        if (angle <= 0.0f)
        {
            last_X = new_X;
            last_Y = new_Y;
            f_X = new_X;
            f_Y = new_Y;

            continue;
        }

        DrawLine(last_X + x, last_Y + y, new_X + x, new_Y + y, color);

        last_X = new_X;
        last_Y = new_Y;
    }

    DrawLine(last_X + x, last_Y + y, f_X + x, f_Y + y, color);
}

void DrawLines(const std::vector<Vertex> &vertices, bool closed)
{
    for (auto vertex = vertices.begin(); vertex != vertices.end(); ++vertex)
    {
        auto next_vertex = std::next(vertex);
        if (next_vertex == vertices.end())
        {
            if (closed)
                next_vertex = vertices.begin();
            else
                return;
        }

        Vertex vertexA = *vertex;
        Vertex vertexB = *next_vertex;

        Vector2 A = Screen::GetView().WorldToScreen(vertexA.position);
        Vector2 B = Screen::GetView().WorldToScreen(vertexB.position);

        DrawLine(A.x, A.y, B.x, B.y, vertexA.color);
    }
}

void Fill(const std::vector<Vertex> &vertices, const AABB& boundingBox, Color color)
{
    int minY = boundingBox.top;
    int maxY = boundingBox.bottom;

    if (minY > maxY)
        std::swap(minY, maxY);

    if (minY < 0 && maxY >= 0)
        minY = 0;
    else if (minY < 0 || maxY < 0)
        return;

    const int maxSize = maxY * 2 + 5;
    int *intersections = new int[maxSize];

    for (int y = minY; y <= maxY; y++)
    {
        int count = 0;

        for (auto vertex = vertices.begin(); vertex != vertices.end(); ++vertex)
        {
            auto next_vertex = std::next(vertex);
            if (next_vertex == vertices.end())
                next_vertex = vertices.begin();

            Vertex vertexA = *vertex;
            Vertex vertexB = *next_vertex;

            if (vertexA.position.y == vertexB.position.y)
                continue;

            if (y >= std::min(vertexA.position.y, vertexB.position.y) && y < std::max(vertexB.position.y, vertexA.position.y))
            {
                int x = vertexA.position.x + (y - vertexA.position.y) * (vertexB.position.x - vertexA.position.x) / (vertexB.position.y - vertexA.position.y);
                intersections[count++] = x;
            }
        }

        HeapSort(intersections, count);
                    
        for (int i = 0; i + 1 < count; i += 2)
        {
            int xStart = intersections[i];
            int xEnd = std::floor(intersections[i + 1]);

            for (int x = xStart; x <= xEnd; x++)
                PlotPixel(x, y, color);
        }
    }

    delete[] intersections;
}

void DrawShape(Shape &shape)
{
    if (shape.transform.update)
    {
        shape.Tvertices = UpdateVertices(shape.transform, shape.vertices);
        shape.boundingBox = UpdateAABB(shape.Tvertices);
    }

    if (shape.fillColor != Color::Transparent)
    {
        if (shape.transform.update || Screen::GetView().update)
        {
            std::vector<Vertex> cameraVertices;
            for(auto vertex : shape.Tvertices)
                cameraVertices.emplace_back(Screen::GetView().WorldToScreen(vertex.position), vertex.color);

            shape.cameraTvertices = cameraVertices;
            shape.cameraBoundingBox = UpdateAABB(cameraVertices);
        }
     
        Fill(shape.cameraTvertices, shape.cameraBoundingBox, shape.fillColor);
    }

    if (shape.color != Color::Transparent)
        DrawLines(shape.Tvertices);
    
    shape.transform.update = false;
}

void DrawTEXT(Text &text)
{
    if(text.string.empty()) return;

    if (text.transform.update)
    {
        text.Tvertices = UpdateVertices(text.transform, text.vertices);
        text.boundingBox = UpdateAABB(text.Tvertices);
        
        text.transform.update = false;
    }
    
    if (text.color != Color::Transparent)
    {    
        for(int i = 0; i < text.indices.size() - 1; i += 2)
        {
            std::vector<Vertex>line;
            line.emplace_back(text.Tvertices[text.indices[i]]);
            line.emplace_back(text.Tvertices[text.indices[i + 1]]);

            DrawLines(line, false);
        }
    }
}