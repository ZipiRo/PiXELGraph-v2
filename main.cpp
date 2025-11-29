#include "Core/PiXELGraph.h"

class Demo1 : public Scene
{
private:
    
    Shapes::Elipse e1;

    void Start() override
    {
        e1 = Shapes::Elipse(10, 10, 10);
        e1.SetColor(Color::Black);
        e1.transform.SetPosition(50, 100);

        Screen::BackgroundColor = Color::Red;
    }

    void Event() override 
    {
    }

    Vector2 ousepos;

    float timer = 1;
    void Update() override
    {
        timer += Time::deltaTime;
        if(timer >= 1)
        {
            Debug::Log("FPS " + std::to_string(1.0f / Time::deltaTime) + " Demo 1");
            timer = 0;
        }

        ousepos = Input::MousePosition;

        if(Input::IsMouseButtonDown(MouseButton::Left))
            e1.transform.SetPosition(ousepos);

        if(Input::IsKeyDown(Key::Key_Space))
            SceneManager::LoadScene(SceneManager::GetActiveScene()->buildIndex + 1);

        if(Input::IsKeyDown(Key::Key_Escape))
            PiXELGraph::GetInstance().Exit();
    }

    void Draw() override
    {
        DrawShape(e1);        
    }

    void Quit() override
    {
        Debug::Log("SUCCESFUL");
    }

public:
    Demo1() {}
};

class Demo2 : public Scene
{
private:
    Shapes::Elipse e1;
    void Start() override
    {
        e1 = Shapes::Elipse(10, 10, 10);
        e1.SetColor(Color::Black);
        e1.transform.SetPosition(100, 100);
        Screen::BackgroundColor = Color::Blue;
    }

    Vector2 ousepos;
    
    void Event() override 
    {
        ousepos = Input::MousePosition;

        if(Input::IsMouseButtonDown(MouseButton::Left))
            e1.transform.SetPosition(ousepos);
    }

    float timer = 1;
    void Update() override
    {
        timer += Time::deltaTime;
        if(timer >= 1)
        {
            Debug::Log("FPS " + std::to_string(1.0f / Time::deltaTime) + "\nDemo 2");
            timer = 0;
        }

        ousepos = Input::MousePosition;

        if(Input::IsMouseButtonDown(MouseButton::Left))
            e1.transform.SetPosition(ousepos);

        if(Input::IsKeyDown(Key::Key_Enter))
            SceneManager::LoadScene(SceneManager::GetActiveScene()->buildIndex - 1);

        if(Input::IsKeyDown(Key::Key_Tab))
            SceneManager::LoadScene("Scene 3");
    }

    void Draw() override
    {        
        DrawShape(e1);
        PlotPixel(ousepos.x, ousepos.y, Color::Black);
    }

    void Quit() override
    {   

    }

public:
    Demo2() {}
};

class Engine : public PiXELGraph {
public:
    Engine() { Init(800, 600, 2, L"Game"); MaxFramesPerSecond = 121; }
};

int main()
{   
    SceneManager::AddScene<Demo1>("Scene 1");
    SceneManager::AddScene<Demo2>("Scene 2");
    SceneManager::AddScene<Demo2>("Scene 3");

    SceneManager::LoadScene("Scene 1");

    SceneManager::RemoveScene("Scene 3");

    Engine engine;
    engine.Run();

    return 0;
}