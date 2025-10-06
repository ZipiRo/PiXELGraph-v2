#include "Core/PiXELGraph.h"

class Demo : public PiXELGraph
{
private:
    double timer = 1;

    Vector2 ScreenMousePosition;

    std::vector<Vertex> vertices;

    Shape shape;
    AABB bounds;

    void Start() override
    {
        vertices.push_back({-0.5, 0.5});
        vertices.push_back({0.5, 0.5});
        vertices.push_back({0.5, -0.5});
        vertices.push_back({-0.5, -0.5});

        shape = Shape(vertices, Color::Red, Color::Black);

        shape.transform.Scale({25, 50});
    }

    void Update() override
    {
        timer += Time::deltaTime;
        if (timer >= 1)
        {
            Window::SetTitle(L" | FPS: " + std::to_wstring(int(1.0f / Time::deltaTime)));
            Debug::Log(std::string("FPS: ") + std::to_string(int(1.0f / Time::deltaTime)));
            timer = 0;
        }

        ScreenMousePosition = Input::MousePosition / Window::WindowFontSize();

        shape.transform.SetPosition(ScreenMousePosition.x, ScreenMousePosition.y);

        if (Input::IsMouseButtonDown(MouseButton::Left))
        {
            shape.SetColor(Color::RandomColor());
            shape.SetFillColor(Color::RandomColor());
        }

        shape.transform.Rotate(PI * Time::deltaTime);
    }

    void Draw() override
    {
        std::vector<Vertex> boundBox;
        bounds = shape.GetBoundingBox();

        boundBox.push_back({bounds.left, bounds.top, Color::Black});
        boundBox.push_back({bounds.right, bounds.top, Color::Black});
        boundBox.push_back({bounds.right, bounds.bottom, Color::Black});
        boundBox.push_back({bounds.left, bounds.bottom, Color::Black});

        DrawShape(shape);
        DrawLines(boundBox);
    }

    void Quit() override
    {
    }

public:
    Demo()
    {
        MaxFPS = 9999;
        Init(812, 512, 3, L"DEMO");
    }
};

int main()
{
    Demo p;
    p.Run();

    return 0;
}