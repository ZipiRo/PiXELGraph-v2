#include "Core/PiXELGraph.h"

class Demo : public PiXELGraph
{
private:
    double timer = 1;

    Vector2 ScreenMousePosition;

    Shapes::Elipse elipse1;
    Shapes::Elipse elipse2;
    Shapes::Elipse elipse3;

    Text t1;

    void Start() override
    {
        Screen::GetView().SetScreenCenter(Vector2(Screen::Width() / 2, Screen::Height() / 2));

        t1.SetString("PULA MARE IN PARCARE\nCE DRQ VREI?");

        t1.transform.SetScale(10, 10);
        
        t1.SetColor(Color::Black);
    }

    void Event() override 
    {
        if(Event::GetEvent() == EventType::EVENT_MOUSE_LCLICK)
        {
            Screen::BacgroundColor = Color::RandomColor();
        }
        if(Event::GetEvent() == EventType::EVENT_MOUSE_SCROLL_UP)
        {
            elipse1.transform.Rotate(PI / 2 * Time::deltaTime);
        }
        if(Event::GetEvent() == EventType::EVENT_MOUSE_SCROLL_DOWN)
        {
            elipse1.transform.Rotate(-PI / 2 * Time::deltaTime);
        }
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

        elipse2.transform.Rotate(PI * Time::deltaTime);
        
        elipse3.transform.Rotate(PI / 3 * Time::deltaTime);
        elipse3.transform.Move(elipse3.transform.Right() * 300 * Time::deltaTime);

        if(Input::IsKey(Key::Key_W))
            cameraDirection.y += -1;
        
        if(Input::IsKey(Key::Key_S))
            cameraDirection.y += 1;
        
        if(Input::IsKey(Key::Key_A))
            cameraDirection.x += -1;
        
        if(Input::IsKey(Key::Key_D))
            cameraDirection.x += 1;
            
        if(Input::IsKey(Key::Key_Q))
            Screen::GetView().Zoom(-1.0f * Time::deltaTime);

        if(Input::IsKey(Key::Key_E))
            Screen::GetView().Zoom(1.0f * Time::deltaTime);

        if(Input::IsKey(Key::Key_Z))
            Screen::GetView().Rotate(PI / 3 * Time::deltaTime);

        if(Input::IsKey(Key::Key_X))
            Screen::GetView().Rotate(-PI / 3 * Time::deltaTime);

        if(cameraDirection.x != 0 || cameraDirection.y != 0)
        {
            Vector2::Normalize(cameraDirection);
            Vector2 newPosition = cameraDirection * 500 * Time::deltaTime;
            Screen::GetView().Move(newPosition);
        }
    }

    void Draw() override
    {        
        DrawTEXT(t1);
        
        DrawLine(0, 0, Screen::Width(), Screen::Height(), Color::Black);
        DrawLine(0, Screen::Height(), Screen::Width(), 0, Color::Black);
    }

    void Quit() override
    {

    }

public:
    Demo()
    {
        MaxFPS = 60;
        Init(800, 600, 3, L"DEMO");
    }
};

int main()
{
    Demo demo;
    demo.Run();

    return 0;
}