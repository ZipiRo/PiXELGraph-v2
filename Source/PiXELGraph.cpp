#include "Console/Window.h"
#include "PiXELGraph/PiXELGraph.h"

void PiXELGraph::Init(int WindowWidth, int WindowHeight, int PixelSize, const std::wstring &WindowTitle)
{
    try {
        Window::GetInstance().SetParameters(WindowWidth, WindowHeight, PixelSize, WindowTitle);
        Screen::GetInstance().SetParameters(WindowWidth / Window::WindowFontSize(), WindowHeight / Window::WindowFontSize());
        Input::GetInstance();
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

        InputThread = std::thread(&PiXELGraph::InputLoop, this);

        while (RUNNING)
        {
            Time::Tick();

            if(Time::deltaTime >= 1.0f / MaxFPS)
            {
                Time::Reset();

                Update();

                Screen::Clear();

                Draw();

                Screen::Display();
            }
        }

        Quit();
    }
    catch(const std::exception& exception) {
        HandleError(exception.what());
    }
}

void PiXELGraph::InputLoop()
{
    while (RUNNING)
    {
        Input::FetchInputData();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void PiXELGraph::HandleError(const std::string &message)
{
    Window::GetInstance().ResetConsole();
    std::cout << "ERROR: " << message << std::endl;

    Quit();
    std::cin.get();
    exit(EXIT_FAILURE);
} 

void PiXELGraph::Exit()
{
    RUNNING = false;
}