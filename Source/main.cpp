#include "Core/PiXELGraph.h"

class Demo : public PiXELGraph
{
private:
    double timer = 1;

    Vector2 ScreenMousePosition;

    std::vector<Vertex> vertices;

    Shape shape;

    void Start() override
    {      
        vertices.push_back({-0.5, 0.5});
        vertices.push_back({0.5, 0.5});
        vertices.push_back({0.5, -0.5});
        vertices.push_back({-0.5, -0.5});
        vertices.push_back({-1, -1});

        shape = Shape(vertices, Color::Red, Color::Green);
        
        shape.transform.Scale({20, 30});
        shape.transform.Move({50, 50});
    }

    void Update() override
    {
        timer += Time::deltaTime;
        if(timer >= 1)
        {
            Window::SetTitle(L" | FPS: " + std::to_wstring(int(1.0f / Time::deltaTime)));
            Debug::Log(std::string("FPS: ") + std::to_string(int(1.0f / Time::deltaTime)));
            timer = 0;
        }

        ScreenMousePosition = Input::MousePosition / Window::WindowFontSize();
        shape.transform.Rotate(PI * Time::deltaTime);
    }

    void Draw() override
    {
        DrawShape(shape);
    }

    void Quit() override
    {
        
    }

public:
    Demo() {
        MaxFPS = 9999;
        Init(512, 512, 3, L"DEMO");
    }
};

int main()
{
    Demo p;
    p.Run();

    return 0;
}