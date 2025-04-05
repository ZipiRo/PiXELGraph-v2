#include "Console/Window.h"

#include "PiXELGraph/Timer.h"
#include "PiXELGraph/PiXELGraph.h"

void PiXELGraph::Init(int WindowWidth, int WindowHeight, int PixelSize, const std::wstring &WindowTitle)
{
    try {
        Window::GetInstance().SetParameters(WindowWidth, WindowHeight, PixelSize, WindowTitle);
    }
    catch(const std::exception& exception) {
        HandleError(exception.what());
    }
}

void PiXELGraph::Run()
{   
    try {
        Start();
        Time::GetInstance();

        while (RUNNING)
        {
            Time::Tick();

            if(Time::deltaTime >= 1.0f / MaxFPS)
            {
                Time::Reset();

                Update();
            }
        }

        Quit();
    }
    catch(const std::exception& exception) {
        HandleError(exception.what());
    }
}

void PiXELGraph::HandleError(const std::string &message)
{
    std::cerr << "ERROR: " << message << std::endl;

    Quit();
    std::cin.get();
    exit(EXIT_FAILURE);
} 