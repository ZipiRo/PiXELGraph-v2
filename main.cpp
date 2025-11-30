#include "Core/PiXELGraph.h"

class Demo1 : public Scene
{
private:
    
    Text default_text;
    Text bold_text;

    std::string words = "The quick brown fox jumps over the lazy dog!";

    void Start() override
    {
        Screen::BackgroundColor = Color::White;

        default_text.SetString(words);
        default_text.transform.SetPosition(5, 5);

        bold_text.SetString(words);
        bold_text.transform.SetPosition(5, 20);
        bold_text.SetFontSize(9);
        bold_text.SetFontWeight(2);
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
        DrawTEXT(bold_text);
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