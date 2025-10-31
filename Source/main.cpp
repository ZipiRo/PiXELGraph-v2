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
        
        e1 = Shapes::Elipse(50, 50);
        e1.SetFillColor(Color(255, 0, 0, 0.1));

        // clip = Clip("gun.mp3", 1.0);
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
            Debug::Log(std::to_string(Screen::GetView().GetZoom()));
        }

        if(Event::GetEvent() == EventType::EVENT_MOUSE_SCROLL_DOWN)
        {
            Screen::GetView().Zoom(-1.0f * Time::deltaTime);
            Debug::Log(std::to_string(Screen::GetView().GetZoom()));
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
        {
            AudioSource::SetVolume(AudioSource::GetVolume() - 0.1);
            t1.SetString(std::to_string(AudioSource::GetVolume()));
        }

        if(Input::IsKey(Key::Key_E))
        {
            AudioSource::SetVolume(AudioSource::GetVolume() + 0.1);
            t1.SetString(std::to_string(AudioSource::GetVolume()));
        }

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
        
        DrawLine(0, 0, Screen::Width(), Screen::Height(), Color(0, 0, 0, 0.5));
        DrawLine(0, Screen::Height(), Screen::Width(), 0, Color(0, 0, 0, 0.5));

        DrawShape(e1);
    }

    void Quit() override
    {
        
    }

public:
    Demo()
    {
        MaxFPS = 60;
        Init(1280, 720, 2, L"DEMO");
    }
};

int main()
{
    Demo demo;
    demo.Run();

    return 0;
}