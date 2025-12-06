#include "Core/PiXELGraph.h"

class Demo1 : public Scene
{
private:
    
    Text default_text;
    Text bold_text;

    Shapes::Rectangle rect;

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

        rect = Shapes::Rectangle(100, 100);
        rect.SetFillColor(Color::Red);
        rect.SetColor(Color::Black);
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

        if(Input::IsKey(Key::Key_W))
            Screen::GetView().Move(Vector2::UP * 100 * Time::deltaTime);
        if(Input::IsKey(Key::Key_S))
            Screen::GetView().Move(Vector2::DOWN * 100 * Time::deltaTime);
        if(Input::IsKey(Key::Key_A))
            Screen::GetView().Move(Vector2::LEFT * 100 * Time::deltaTime);
        if(Input::IsKey(Key::Key_D))
            Screen::GetView().Move(Vector2::RIGHT * 100 * Time::deltaTime);
    }

    void Draw() override
    {
        DrawTEXT(default_text);
        DrawTEXT(bold_text);

        DrawShape(rect);
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