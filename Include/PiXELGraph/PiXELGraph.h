#pragma once

#include <iostream>
#include <string>

#include "Console/ErrorSystem.h"
#include "Console/Window.h"
#include "Timer.h"

class PiXELGraph
{
private:
    bool RUNNING = true;

    void HandleError(const std::string &message);

protected:
    double MaxFPS = 60; 

    void Init(int WindowWidth, int WindowHeight, int PixelSize, const std::wstring &title);

    virtual void Start() {}
    virtual void Update() {}
    virtual void Draw() {} 
    virtual void Quit() {}

public:

    void Run();
};