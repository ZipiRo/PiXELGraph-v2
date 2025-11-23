#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <vector>
#include <limits>

#include "EngineSettings.h"

#include "UMath.h"
#include "Vector2.h"

#include "Console/ErrorSystem.h"
#include "Console/EventSystem.h"
#include "Console/InputSystem.h"
#include "Console/Window.h"
#include "Console/Debug.h"

class PiXELGraph;
class SceneManager;

#include "Timer.h"
#include "Color.h"
#include "ViewPort.h"
#include "Screen.h"

#ifdef USE_AUDIO
#include "Audio/AudioClip.h"
#include "Audio/AudioSource.h"
#endif

#include "Graphics/Font.h"

#include "Graphics/Vertex.h"
#include "Graphics/Transform.h"
#include "Graphics/AABB.h"
#include "Graphics/Shape.h"
#include "Graphics/Rectangle.h"
#include "Graphics/Elipse.h"
#include "Graphics/Text.h"

#ifdef USE_SCENE
#include "SceneManager.h"
#endif

class PiXELGraph
{
private:
    static PiXELGraph* activeInstance;
    std::atomic<bool> RUNNING;
    std::thread InputThread;
    std::thread EventThread;

    void InputLoop();
    void EventLoop();

    void HandleError(const std::string &message);

    friend BOOL WINAPI ConsoleHandler(DWORD signal);
    friend class SceneManager;
    
protected:
    PiXELGraph();

    void Init(int WindowWidth, int WindowHeight, int PixelSize, const std::wstring &title);
    void Exit();

#ifndef USE_SCENE
    virtual void Start() {}
    virtual void Event() {}
    virtual void Update() {}
    virtual void Draw() {}
    virtual void Quit() {}
#endif

public:
    PiXELGraph(const PiXELGraph&) = delete;
    PiXELGraph& operator=(const PiXELGraph&) = delete;
    static PiXELGraph &GetInstance();
    
    void Run();
};