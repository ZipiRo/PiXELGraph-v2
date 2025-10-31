#include "Console/Window.h"
#include "Core/PiXELGraph.h"

PiXELGraph* PiXELGraph::activeInstance = nullptr;

BOOL WINAPI ConsoleHandler(DWORD signal)
{
    switch (signal)
    {
    case CTRL_CLOSE_EVENT:
        PiXELGraph::GetInstance().Exit();
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

PiXELGraph::PiXELGraph() { activeInstance = this; }

PiXELGraph &PiXELGraph::GetInstance()
{
    return *activeInstance;
}

void PiXELGraph::Init(int WindowWidth, int WindowHeight, int PixelSize, const std::wstring &WindowTitle)
{
    try
    {
        SetConsoleCtrlHandler(ConsoleHandler, TRUE);

        Window::GetInstance().SetParameters(WindowWidth, WindowHeight, PixelSize, WindowTitle);
        Screen::GetInstance().SetParameters(WindowWidth / Window::WindowFontSize(), WindowHeight / Window::WindowFontSize());
        Event::GetInstance();
        Input::GetInstance();
        Font::GetInstance();
        AudioSource::GetInstance();
    }
    catch (const std::exception &exception)
    {
        HandleError(exception.what());
    }
}

void PiXELGraph::Exit()
{
    if(!RUNNING) return;
    RUNNING = false;
    Debug::KillDebuger();

    activeInstance->Quit();

    AudioSource::Dispose();
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

        if(InputThread.joinable()) InputThread.join();
        if(EventThread.joinable()) EventThread.join();
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
        
    if(InputThread.joinable()) InputThread.join();
    if(EventThread.joinable()) EventThread.join();

    Exit();
}