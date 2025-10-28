BASH BUILD APP
============================================================
@echo off

g++ DebugWindow.cpp -o Build/Debug/DebugWindow.exe

cd Build 
cmake ..
cmake --build . 

cd Debug
start PiXELGraph
cd ../..
============================================================

BASH RUN APP
============================================================
@echo off

cd Build/Debug
start PiXELGraph
cd ../..
============================================================

BASE RUNTIME
============================================================
#include "Core/PiXELGraph.h"

class GameScene : public PiXELGraph
{
private:
    double timer = 1;

    Vector2 ScreenMousePosition;
    Vector2 WorldMousePosition;

    void Start() override
    {
        Screen::GetView().SetScreenCenter(Vector2(Screen::Width() / 2, Screen::Height() / 2));
    }

    void Event() override 
    {

    }

    void Update() override
    {
        ScreenMousePosition = Input::MousePosition / Window::WindowFontSize();
        WorldMousePosition = Screen::GetView().ScreenToWorld(ScreenMousePosition);
        
        timer += Time::deltaTime;
        if (timer >= 1)
        {
            int fps = 1.0f / Time::deltaTime;
            float dt = Time::deltaTime;
            
            Window::SetTitle(L" | FPS: " + std::to_wstring(fps) + L" | DEMO");
            Debug::Log(std::string("DT: ") + std::to_string(dt) + std::string(" | FPS: ") + std::to_string(fps));
            
            timer = 0;
        }
    }

    void Draw() override
    {
                
    }

    void Quit() override
    {

    }

public:
    GameScene()
    {
        MaxFPS = 60;
        Init(1280, 720, 5, L"DEMO");
    }
}; 
============================================================

By ZipiRo
