#include "PiXELGraph/PiXELGraph.h"

class Demo : public PiXELGraph
{
private:
    double timer = 1;
    int counter = 0;
    void Start() override
    {

    }

    void Update() override
    {
        timer += Time::deltaTime;
        if(timer >= 1)
        {
            Window::SetTitle(L"FPS: " + std::to_wstring(int(1.0f / Time::deltaTime)));
            timer = 0;
        }
    }

    void Draw() override
    {
        if(Input::IsKeyDown(Key::Key_Space))
        {
            Screen::BacgroundColor = Color::Red;
        }
        else if(Input::IsKeyUp(Key::Key_Space))
        {
            Screen::BacgroundColor = Color::White;
        }
    }

    void Quit() override
    {
        
    }

public:
    Demo() {
        Init(1280, 720, 1, L"DEMO");
    }
};

int main()
{
    Demo p;
    p.Run();

    return 0;
}