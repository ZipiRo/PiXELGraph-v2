#include "Console/Window.h"
#include "Core/PiXELGraph.h"

void PiXELGraph::Init(int WindowWidth, int WindowHeight, int PixelSize, const std::wstring &WindowTitle)
{
    try
    {
        Window::GetInstance().SetParameters(WindowWidth, WindowHeight, PixelSize, WindowTitle);
        Screen::GetInstance().SetParameters(WindowWidth / Window::WindowFontSize(), WindowHeight / Window::WindowFontSize());
        Event::GetInstance();
        Input::GetInstance();
        AudioSource::GetInstance();
        Font::GetInstance();
    }
    catch (const std::exception &exception)
    {
        HandleError(exception.what());
    }
}

void PiXELGraph::Run()
{
    try
    {
        Start();
        Time::GetInstance();

        InputThread = std::thread(&PiXELGraph::InputLoop, this);
        EventThread = std::thread(&PiXELGraph::EventLoop, this);

        while (RUNNING)
        {
            Time::Tick();

            Event();
            if (Time::deltaTime >= 1.0f / MaxFPS)
            {
                Time::Reset();

                Update();

                Screen::Clear();

                Draw();

                Screen::Display();
                Screen::GetView().update = false;
            }
        }

        AudioSource::Dispose();

        Quit();
    }
    catch (const std::exception &exception)
    {
        HandleError(exception.what());
    }
}

void PiXELGraph::InputLoop()
{
    while (RUNNING)
    {
        if(!Window::Focused()) continue;
        Input::FetchInputData();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void PiXELGraph::EventLoop()
{
    while (RUNNING)
    {
        if(!Window::Focused()) continue;
        Event::FetchEventData();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void PiXELGraph::HandleError(const std::string &message)
{
    Debug::Log("ERROR: " + message);

    Quit();
    exit(EXIT_FAILURE);
}

void PiXELGraph::Exit()
{
    RUNNING = false;
}