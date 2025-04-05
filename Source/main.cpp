#include "PiXELGraph/PiXELGraph.h"

class Demo : public PiXELGraph
{
private:
    double timer = 1;
    int counter = 0;

    void Start()
    {
        
    }

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
        Init(100, 100, 2, L"DEMO");
    }
};

int main()
{
    Demo p;
    p.Run();

    return 0;
}