#include "Core/PiXELGraph.h"

class Demo1 : public Scene
{
private:
    
    Shapes::Elipse e1;

    void Start() override
    {
        e1 = Shapes::Elipse(10, 10);
        e1.SetColor(Color::Black);
        e1.transform.SetPosition(50, 100);

        Screen::BacgroundColor = Color::Red;
        Debug::Log("Demo 1");
    }

    void Event() override 
    {
    }

    Vector2 ousepos;

    void Update() override
    {
        ousepos = Input::MousePosition;

        if(Input::IsMouseButtonDown(MouseButton::Left))
            e1.transform.SetPosition(ousepos);

        if(Input::IsKeyDown(Key::Key_Space))
            SceneManager::LoadScene(SceneManager::GetActiveScene()->buildIndex + 1);
    }

    void Draw() override
    {
        DrawShape(e1);        
    }

    void Quit() override
    {
        
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
        e1 = Shapes::Elipse(10, 10);
        e1.SetColor(Color::Black);
        e1.transform.SetPosition(100, 100);
        Screen::BacgroundColor = Color::Blue;
        Debug::Log("Demo 2");
    }

    Vector2 ousepos;
    
    void Event() override 
    {
        ousepos = Input::MousePosition;

        if(Input::IsMouseButtonDown(MouseButton::Left))
            e1.transform.SetPosition(ousepos);
    }

    void Update() override
    {
        Debug::Log("Demo 2");
        if(Input::IsKeyDown(Key::Key_Space))
            SceneManager::LoadScene(SceneManager::GetActiveScene()->buildIndex - 1);
    }

    void Draw() override
    {        
        DrawShape(e1);
    }

    void Quit() override
    {   
    }

public:
    Demo2() {}
};

class Engine : public PiXELGraph {
public:
    Engine() { Init(1280, 720, 1, L"Game"); }
};

int main()
{   
    SceneManager::AddScene<Demo1>("Scene 1");
    SceneManager::AddScene<Demo2>("Scene 2");

    SceneManager::LoadScene(0);

    Engine engine;
    engine.Run();

    return 0;
}