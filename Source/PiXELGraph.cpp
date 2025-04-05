#include "PiXELGraph/Timer.h"
#include "PiXELGraph/PiXELGraph.h"

#include <iostream>

void PiXELGraph::Init()
{
    Time::GetInstance();
}

void PiXELGraph::Run()
{   
    while (RUNNING)
    {
        Time::Tick();

        if(Time::deltaTime >= 1.0f / MaxFPS)
        {
            Time::Reset();

            Update();
        }
    }
}