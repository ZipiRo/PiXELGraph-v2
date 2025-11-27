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

PiXELGraph::PiXELGraph() : RUNNING(true), MaxFramesPerSecond(60) { activeInstance = this; }

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

#ifdef USE_AUDIO
        AudioSource::GetInstance();
#endif

    }
    catch (const std::exception &exception)
    {
        HandleError(exception.what());
    }
}

void PiXELGraph::Exit()
{
    RUNNING = false;

#ifdef USE_SCENE
    SceneManager::GetActiveScene()->Quit();
    SceneManager::StopScene();
#else
    activeInstance->Quit();
#endif

#ifdef USE_AUDIO
    AudioSource::Dispose();
#endif

#ifdef USE_DEBUGER
    Debug::Kill();
#endif

}

#ifndef USE_SCENE
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
                if (Time::deltaTime >= 1.0f / MaxFramesPerSecond)
                {
                    Time::Reset();

                    Update();

                    Screen::Clear();

                    Draw();

                    Screen::Display();
                    Screen::GetView().update = false;
                }  
            }
        }
        catch (const std::exception &exception)
        {
            HandleError(exception.what());
        } 

        if(InputThread.joinable()) InputThread.join();
        if(EventThread.joinable()) EventThread.join();
}
#else
void PiXELGraph::Run()
{
    try
    {
        Time::GetInstance();

        InputThread = std::thread(&PiXELGraph::InputLoop, this);
        EventThread = std::thread(&PiXELGraph::EventLoop, this);

        while (RUNNING)
            SceneManager::RunScene(MaxFramesPerSecond);
    }
    catch (const std::exception &exception)
    {
        HandleError(exception.what());
    }

    if(InputThread.joinable()) InputThread.join();
    if(EventThread.joinable()) EventThread.join();
}
#endif

void PiXELGraph::InputLoop()
{
    try 
    {
        while (RUNNING)
        {
            if(!Window::Focused()) continue;
            Input::FetchInputData();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    } catch(const std::exception &exception)
    {
        HandleError(exception.what());
    }
}

void PiXELGraph::EventLoop()
{
    try 
    {
        while (RUNNING)
        {
            if(!Window::Focused()) continue;
            Event::FetchEventData();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    } catch(const std::exception &exception)
    {
        HandleError(exception.what());
    }
}

void PiXELGraph::HandleError(const std::string &message)
{
    RUNNING = false;

#ifdef USE_DEBUGER
    Debug::Log("ERROR: " + message);
#endif

    if(InputThread.joinable()) InputThread.join();
    if(EventThread.joinable()) EventThread.join();

    #ifdef USE_SCENE
        if(SceneManager::HasActiveScene())
            SceneManager::GetActiveScene()->Quit();

        SceneManager::StopScene();
    #else
        activeInstance->Quit();
    #endif

    #ifdef USE_AUDIO
        AudioSource::Dispose();
    #endif
}