#include "PiXELGraph/PiXELGraph.h"

#include <iostream>

class Demo : public PiXELGraph
{
private:
    double timer = 1;
    int counter = 0;
    
    void Update() override
    {
        timer += Time::deltaTime;
        if(timer >= 1)
        {
            counter++;
            timer = 0;
        } 
    }

public:
    Demo() {
        Init();
    }
};

int main()
{
    Demo p;
    p.Run();

    return 0;
}