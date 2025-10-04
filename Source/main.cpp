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
            Window::SetTitle(L"FPS: " + std::to_wstring(int(1.0f / Time::deltaTime)));
            timer = 0;
        }
        
        counter++;
        ScreenMousePosition = Input::MousePosition / Window::WindowFontSize();
    }

    void Draw() override
    {
        for(int i = 0; i <= Screen::Height(); i++)
        {
            for(int j = 0; j <= Screen::Width(); j++)
            {
                PlotPixel(j, i, Color::RandomColor());
            }
        }
    }

    void Quit() override
    {
        
    }

public:
    Demo() {
        MaxFPS = 60;
        Init(512, 512, 1, L"DEMO");
    }
};

int main()
{
    Demo p;
    p.Run();

    return 0;
}