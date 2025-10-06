#include "Core/PiXELGraph.h"

class Demo : public PiXELGraph
{
private:
    double timer = 1;

    Vector2 ScreenMousePosition;

    Shapes::Rectangle rect;
    Shapes::Elipse regpol;

    void Start() override
    {
        rect = Shapes::Rectangle(10, 10);
        rect.SetColor(Color::Black);
        rect.SetFillColor(Color::Red);

        regpol = Shapes::Elipse(10, 5);
        regpol.SetColor(Color::Black);
        regpol.SetFillColor(Color::Red);

        rect.transform.SetPosition(Screen::Width() / 2, Screen::Height() / 2);
        regpol.transform.SetPosition(30, 50);
    }

    void Update() override
    {
        timer += Time::deltaTime;
        if (timer >= 1)
        {
            Window::SetTitle(L" | FPS: " + std::to_wstring(int(1.0f / Time::deltaTime)));
            Debug::Log(std::string("FPS: ") + std::to_string(int(1.0f / Time::deltaTime)));

            rect.SetFillColor(Color::RandomColor());

            timer = 0;
        }

        ScreenMousePosition = Input::MousePosition / Window::WindowFontSize();

        rect.transform.Rotate(PI * Time::deltaTime);

        regpol.transform.Rotate(PI / 2 * Time::deltaTime);
    }

    void Draw() override
    {
        DrawShape(rect);
        DrawShape(regpol);
    }

    void Quit() override
    {

    }

public:
    Demo()
    {
        MaxFPS = 31;
        Init(812, 512, 2, L"DEMO");
    }
};

int main()
{
    Demo p;
    p.Run();

    return 0;
}