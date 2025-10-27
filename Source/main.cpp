#include "Core/PiXELGraph.h"

class Demo : public PiXELGraph
{
private:
    double timer = 1;

    Vector2 ScreenMousePosition;
    Vector2 WorldMousePosition;

    Text t1;

    Shapes::Elipse e1;

    Clip clip;

    void Start() override
    {
        Screen::GetView().SetScreenCenter(Vector2(Screen::Width() / 2, Screen::Height() / 2));

        t1.transform.SetScale(20, 20);        
        t1.SetColor(Color::Black);
        
        e1 = Shapes::Elipse(1, 1);
        e1.SetFillColor(Color::Red);

        clip = Clip("gun.mp3", 1.0);
    }

    void Event() override 
    {
        if(Event::GetEvent() == EventType::EVENT_MOUSE_LCLICK)
        {
            Screen::BacgroundColor = Color::RandomColor();
            AudioSource::PlaySound(clip);
        }
        
        if(Event::GetEvent() == EventType::EVENT_MOUSE_SCROLL_UP)
        {
            Screen::GetView().Zoom(1.0f * Time::deltaTime);
        }

        if(Event::GetEvent() == EventType::EVENT_MOUSE_SCROLL_DOWN)
        {
            Screen::GetView().Zoom(-1.0f * Time::deltaTime);
        }
    }

    void Update() override
    {
        ScreenMousePosition = Input::MousePosition / Window::WindowFontSize();
        
        timer += Time::deltaTime;
        if (timer >= 1)
        {
            int fps = 1.0f / Time::deltaTime;
            float dt = Time::deltaTime;
            
            Window::SetTitle(L" | FPS: " + std::to_wstring(fps) + L" | DEMO");
            Debug::Log(std::string("DT: ") + std::to_string(dt) + std::string(" | FPS: ") + std::to_string(fps));
            
            timer = 0;
        }

        WorldMousePosition = Screen::GetView().ScreenToWorld(ScreenMousePosition);
        e1.transform.SetPosition(WorldMousePosition);
        
        Vector2 cameraDirection;

        if(Input::IsKey(Key::Key_W))
            cameraDirection.y += -1;
        
        if(Input::IsKey(Key::Key_S))
            cameraDirection.y += 1;
        
        if(Input::IsKey(Key::Key_A))
            cameraDirection.x += -1;
        
        if(Input::IsKey(Key::Key_D))
            cameraDirection.x += 1;
            
        if(Input::IsKey(Key::Key_Q))
            AudioSource::SetVolume(AudioSource::GetVolume() - 0.1);

        if(Input::IsKey(Key::Key_E))
            AudioSource::SetVolume(AudioSource::GetVolume() + 0.1);

        if(cameraDirection.x != 0 || cameraDirection.y != 0)
        {
            Vector2::Normalize(cameraDirection);
            Vector2 newPosition = cameraDirection * 500 * Time::deltaTime;
            Screen::GetView().Move(newPosition);
        }

        t1.SetString(std::to_string(AudioSource::GetVolume()));
    }

    void Draw() override
    {        
        DrawShape(e1);

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