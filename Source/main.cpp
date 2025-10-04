#include "PiXELGraph/PiXELGraph.h"

class Demo : public PiXELGraph
{
private:
    double timer = 1;
    int counter = 0;

    Vector2 ScreenMousePosition;

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
    }

    void Draw() override
    {

    }

    void Quit() override
    {
        
    }

public:
    Demo() {
        MaxFPS = 60;
        Init(1920, 1080, 3, L"DEMO");
    }
};

int main()
{
    Demo p;
    p.Run();

    return 0;
}