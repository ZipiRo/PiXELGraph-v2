HOW TO BUILD USING THE BASH BUILD
build.bat R -> for release
build.bat -> for debug


BASH BUILD APP
============================================================
@echo off
setlocal

set BUILD_TYPE=%1

cd Build
if errorlevel 1 (
    mkdir Build
)

if "%BUILD_TYPE%"=="R" (
    cmake ..
    cmake --build . --config Release
    
    cd Release
    start PiXELGraph
    cd ../..
) else (
    cmake ..
    cmake --build . --config Debug

    cd Debug
    start PiXELGraph
    cd ../..
)
============================================================

BASH RUN APP
============================================================
@echo off
setlocal

set BUILD_TYPE=%1

cd Build

if "%BUILD_TYPE%"=="R" (
    cd Release
    start PiXELGraph
    cd ../..
) else (
    cd Debug
    start PiXELGraph
    cd ../..
)

============================================================

BASE RUNTIME
============================================================
#include "Core/PiXELGraph.h"

class GameScene : public PiXELGraph
{
private:
    Shapes::Elipse e1;

    void Start() override
    {
        Screen::GetView().SetScreenCenter(Vector2(Screen::Width() / 2, Screen::Height() / 2));
        e1 = Shapes::Elipse(10, 10, 3);
        e1.SetColor(Color::Black);
        e1.SetFillColor(Color::Red);
    }

    void Update() override
    {

    }

    void Draw() override
    {
        DrawShape(e1);
    }

public:
    GameScene()
    {
        MaxFPS = 60;
        Init(1280, 720, 3, L"DEMO");
    }
}; 
============================================================

By ZipiRo
