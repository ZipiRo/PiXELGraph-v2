#include "PiXELGraph/PiXELGraph.h"

class Demo : public PiXELGraph
{
private:
    double timer = 1;

    void Start() override
    {

    }

    void Update() override
    {
        timer += Time::deltaTime;
        if(timer >= 2)
        {   

        } 
    }

    void Draw() override
    {
        DrawElipse(Screen::Width() / 2, Screen::Height() / 2, 20, Color::Red, 3);
    }

public:
    Demo() {
        Init(640, 480, 1, L"DEMO");
    }
};

int main()
{
    Demo p;
    p.Run();

    return 0;
}