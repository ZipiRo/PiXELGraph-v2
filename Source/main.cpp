#include "Core/PiXELGraph.h"

class Demo : public PiXELGraph
{
private:
    double timer = 1;

    Vector2 ScreenMousePosition;

    Shapes::Elipse elipse1;
    Shapes::Elipse elipse2;
    Shapes::Elipse elipse3;

    void Start() override
    {
        Screen::GetView().SetScreenCenter(Vector2(Screen::Width() / 2, Screen::Height() / 2));

        elipse1 = Shapes::Elipse(10, 10);
        elipse1.SetColor(Color::Black);
        elipse1.SetFillColor(Color::Red);
        elipse1.transform.SetPosition(0, 0);

        elipse2 = Shapes::Elipse(100, 100, 3);
        elipse2.SetColor(Color::Black);
        elipse2.SetFillColor(Color::Blue);
        elipse2.transform.SetPosition(100, 0);
        
        elipse3 = Shapes::Elipse(10, 10, 5);
        elipse3.SetColor(Color::Black);
        elipse3.SetFillColor(Color::Green);
        elipse3.transform.SetPosition(-100, 0);
        elipse3.transform.Rotate(PI / 3);
    }

    void Update() override
    {
        ScreenMousePosition = Input::MousePosition / Window::WindowFontSize();
        timer += Time::deltaTime;
        if (timer >= 1)
        {
            Window::SetTitle(L" | FPS: " + std::to_wstring(int(1.0f / Time::deltaTime)) + L" | DEMO");
            Debug::Log(std::string("DT: ") + std::to_string(Time::deltaTime) + std::string(" | FPS: ") + std::to_string(int(1.0f / Time::deltaTime)));
            timer = 0;
        }

        Vector2 cameraDirection;

        elipse1.transform.Move(Vector2::RIGHT * 9.81 * Time::deltaTime * 20);
        elipse2.transform.Rotate(PI / 2 * Time::deltaTime);
        elipse3.transform.Move(elipse3.transform.Right() * 9.81 * Time::deltaTime * 3);

        Vector2 worldMousePosition = Screen::GetView().ScreenToWorld(ScreenMousePosition);
        elipse2.transform.SetPosition(worldMousePosition);

        if(Input::IsKey(Key::Key_W))
            cameraDirection.y += -1;
        
        if(Input::IsKey(Key::Key_S))
            cameraDirection.y += 1;
        
        if(Input::IsKey(Key::Key_A))
            cameraDirection.x += -1;
        
        if(Input::IsKey(Key::Key_D))
            cameraDirection.x += 1;

        if(Input::IsKey(Key::Key_Q))
            Screen::GetView().Zoom(-1 * Time::deltaTime);

        if(Input::IsKey(Key::Key_E))
            Screen::GetView().Zoom(1 * Time::deltaTime);

        if(cameraDirection.x != 0 || cameraDirection.y != 0)
        {
            Vector2::Normalize(cameraDirection);
            Vector2 newPosition = cameraDirection * 500 * Time::deltaTime;
            Screen::GetView().Move(newPosition);
        }
    }

    void Draw() override
    {
        DrawShape(elipse1);
        DrawShape(elipse2);
        DrawShape(elipse3);
    }

    void Quit() override
    {

    }

public:
    Demo()
    {
        MaxFPS = 60;
        Init(1280, 720, 4, L"DEMO");
    }
};

int main()
{
    Demo demo;
    demo.Run();

    return 0;
}