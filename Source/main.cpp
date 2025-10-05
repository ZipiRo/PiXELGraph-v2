#include "PiXELGraph/PiXELGraph.h"

class Demo : public PiXELGraph
{
private:
    double timer = 1;
    int counter = 0;

    Vector2 ScreenMousePosition;

    Vector2 position;
    float speed = 100;
    float size = 10;

    void Start() override
    {

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

        Vector2 direction;
        if(Input::IsKey(Key_A))
            direction.x += -1;
        if(Input::IsKey(Key_D))
            direction.x += 1;
        if(Input::IsKey(Key_W))
            direction.y += -1;
        if(Input::IsKey(Key_S))
            direction.y += 1;

        if(Input::IsKey(Key::Key_Q))
            size-=1;
        if(Input::IsKey(Key::Key_E))
            size+=1;

        if(direction.x != 0 || direction.y != 0)
        {
            Vector2::Normalize(direction);
            position += direction * speed * Time::deltaTime;
    
            Debug::Log("X: " + std::to_string(position.x) + " Y: " + std::to_string(position.y));
        }
    }

    void Draw() override
    {
        DrawElipse(position.x, position.y, size, Color::Red);
    }

    void Quit() override
    {
        
    }

public:
    Demo() {
        MaxFPS = 60;
        Init(512, 512, 3, L"DEMO");
    }
};

int main()
{
    Demo p;
    p.Run();

    return 0;
}