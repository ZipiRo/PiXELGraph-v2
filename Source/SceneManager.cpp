#include <vector>

#include "Console/ErrorSystem.h"
#include "Console/Debug.h"

#include "Core/Timer.h"
#include "Core/Screen.h"
#include "Core/ViewPort.h"

#include "EngineSettings.h"
#include "Core/SceneManager.h"

const double MaxFPS = MaxFramesPerSecond;

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

    Scene &scene = *instance.GetActiveScene();
    instance.changeScene = false;

    scene.Start();

    while (!instance.changeScene)
    {
        Time::Tick();
        
        scene.Event();
        if (Time::deltaTime >= 1.0f / MaxFPS)
        {
            Time::Reset();

            scene.Update();

            Screen::Clear();

            scene.Draw();

            Screen::Display();
            Screen::GetView().update = false;
        }
    }
}

void SceneManager::LoadScene(int buildIndex)
{
    auto &instance = GetInstance();
 
    if(buildIndex < 0 && buildIndex >= instance.scenes.size())
        throw Error("This scene index does not exist!");
    
    SceneInfo &scene = instance.scenes[buildIndex];
    
    instance.currentScene = scene.createFunction();
    instance.currentScene->buildIndex = scene.buildIndex;
    instance.currentScene->name = scene.name;

    instance.changeScene = true;
}

Scene *SceneManager::GetActiveScene()
{
    auto &instance = GetInstance();

    if(instance.currentScene == nullptr)
        instance.currentScene = new Scene();

    return instance.currentScene;
}