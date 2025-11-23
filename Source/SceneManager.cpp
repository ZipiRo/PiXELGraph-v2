#include <vector>

#include "Console/ErrorSystem.h"
#include "Console/Debug.h"

#include "Core/Timer.h"
#include "Core/Screen.h"
#include "Core/ViewPort.h"

#include "EngineSettings.h"
#include "Core/SceneManager.h"

SceneManager::SceneManager()
{ currentScene = nullptr; changeScene = false;}

SceneManager &SceneManager::GetInstance()
{
    static SceneManager instance;
    return instance;
}

void SceneManager::RunScene()
{
    auto &instance = GetInstance(); 

    Scene *scene = instance.GetActiveScene();
    instance.changeScene = false;

    scene->Start();

    while (!instance.changeScene)
    {
        Time::Tick();
        
        if(instance.changeScene) continue;
        scene->Event();

        if (Time::deltaTime >= 1.0f / FPS)
        {
            Time::Reset();

            if(instance.changeScene) continue;
            scene->Update();

            Screen::Clear();

            if(instance.changeScene) continue;
            scene->Draw();

            Screen::Display();
            Screen::GetView().update = false;
        }
    }
}

void SceneManager::LoadScene(int buildIndex)
{
    auto &instance = GetInstance();
 
    if(buildIndex < 0 || buildIndex >= instance.scenes.size())
        throw Error("This scene index does not exist!");
    
    instance.currentScene = instance.scenes[buildIndex].createFunction();

    instance.currentScene->buildIndex = instance.scenes[buildIndex].buildIndex;
    instance.currentScene->name = instance.scenes[buildIndex].name;

    instance.changeScene = true;
}

void SceneManager::LoadScene(const std::string &name)
{
    auto &instance = GetInstance();

    int index = 0;
    for(; index <= instance.scenes.size() && instance.scenes[index].name != name; index++);
    LoadScene(index);
}

Scene *SceneManager::GetActiveScene()
{
    auto &instance = GetInstance();

    if(instance.currentScene == nullptr)
        throw Error("There is no active scene loaded!");

    return instance.currentScene.get();
}