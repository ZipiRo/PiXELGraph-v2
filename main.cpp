#include "Core/PiXELGraph.h"

class Demo1 : public Scene
{
private:
    
    Text default_text;

    std::string words = "The quick brown fox jumps over the lazy dog";

    void Start() override
    {
        Screen::BackgroundColor = Color::Black;

        default_text.SetString(words);
        default_text.SetFontSize(6);
        default_text.SetColor(Color::White);
        // default_text.SetFontWeight(2);
    }

    void Event() override 
    {}

    float timer = 1;
    void Update() override
    {
        timer += Time::deltaTime;
        if(timer >= 1)
        {
            Debug::Log("FPS " + std::to_string(1.0f / Time::deltaTime) + " Demo 1");
            timer = 0;
        }
    }

    void Draw() override
    {
        DrawTEXT(default_text);

        DrawThickLine(100, 100, 200, 200, 2, Color::White);
    }

    void Quit() override
    {}

public:
    Demo1() {}
};

class Engine : public PiXELGraph {
public:
    Engine() { Init(800, 600, 1, L"Game"); MaxFramesPerSecond = MaxFPS; }
};

int main()
{   
    SceneManager::AddScene<Demo1>("Scene 1");
    SceneManager::LoadScene("Scene 1");

    Engine engine;
    engine.Run();

    return 0;
}