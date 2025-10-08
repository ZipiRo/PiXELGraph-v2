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

        Audio::PlaySound("mus.wav");
    }

    void Update() override
    {
        timer += Time::deltaTime;
        if (timer >= 1)
        {
            Window::SetTitle(L" | FPS: " + std::to_wstring(int(1.0f / Time::deltaTime)) + L" | DEMO");
            Debug::Log(std::string("DT: ") + std::to_string(Time::deltaTime) + std::string(" | FPS: ") + std::to_string(int(1.0f / Time::deltaTime)));

            rect.SetFillColor(Color::RandomColor());

            timer = 0;
        }

        if(Input::IsMouseButtonDown(MouseButton::Left))
        {
            Debug::Log("Slash");
            Audio::PlaySound("slash.mp3");
        }

        if(Input::IsKeyDown(Key::Key_Space))
        {
            Debug::Log("Ding");
            Audio::PlaySound("sound.mp3");
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
        MaxFPS = 60;
        Init(1280, 720, 10, L"DEMO");
    }
};

int main()
{
    Demo p;
    p.Run();

    return 0;
}