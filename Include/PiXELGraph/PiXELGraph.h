#pragma once

#include "Timer.h"

class PiXELGraph
{
private:
    bool RUNNING = true;
    double MaxFPS = 60;

protected:
    
    void Init();

    virtual void Start() {}
    virtual void Update() {}
    virtual void Draw() {} 
    virtual void Quit() {}

public:

    void Run();
};