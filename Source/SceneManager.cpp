#include <vector>

#include "Console/ErrorSystem.h"
#include "Console/Debug.h"

#include "Core/Timer.h"
#include "Core/Screen.h"
#include "Core/ViewPort.h"

#include "EngineSettings.h"
#include "Core/SceneManager.h"

SceneManager::SceneManager()
{ currentScene = nullptr; SceneManagerChanges = false;}

SceneManager &SceneManager::GetInstance()
{
    static SceneManager instance;
    return instance;
}

void SceneManager::RunScene(int FramesPerSecond)
{
    auto &instance = GetInstance(); 

    Scene *scene = instance.GetActiveScene();
    instance.SceneManagerChanges = false;
    
    scene->Start();

    while (!instance.SceneManagerChanges)
    {
        Time::Tick();
        
        if(instance.SceneManagerChanges) continue;
        scene->Event();

        if (Time::deltaTime >= 1.0f / FramesPerSecond)
        {
            Time::Reset();

            if(instance.SceneManagerChanges) continue;
            scene->Update();

            Screen::Clear();

            if(instance.SceneManagerChanges) continue;
            scene->Draw();

            Screen::Display();
            Screen::GetView().update = false;
        }
    }
}

void SceneManager::RemoveScene(int buildIndex)
{
    auto &instance = GetInstance();

    if(buildIndex < 0 || buildIndex >= instance.scenes.size())
        throw Error("This scene index does not exist!");

    instance.scenes.erase(instance.scenes.begin() + buildIndex);
}

void SceneManager::RemoveScene(const std::string &name)
{
    auto &instance = GetInstance();

    int index = 0;
    for(; index <= instance.scenes.size() && instance.scenes[index].name != name; index++);
    RemoveScene(index);
}

void SceneManager::LoadScene(int buildIndex) 
{
    auto &instance = GetInstance();
 
    if(buildIndex < 0 || buildIndex >= instance.scenes.size())
        throw Error("This scene index does not exist!");
    
    instance.currentScene = instance.scenes[buildIndex].createFunction();

    instance.currentScene->buildIndex = instance.scenes[buildIndex].buildIndex;
    instance.currentScene->name = instance.scenes[buildIndex].name;

    instance.SceneManagerChanges = true;
}

void SceneManager::LoadScene(const std::string &name)
{
    auto &instance = GetInstance();

    int index = 0;
    for(; index <= instance.scenes.size() && instance.scenes[index].name != name; index++);
    LoadScene(index);
}

bool SceneManager::HasActiveScene()
{
    auto &instance = GetInstance();
    return instance.currentScene != nullptr;
}

void SceneManager::StopScene()
{
    auto &instance = GetInstance();
    instance.SceneManagerChanges = true;
}

Scene *SceneManager::GetActiveScene()
{
    auto &instance = GetInstance();

    if(instance.currentScene == nullptr)
        throw Error("There is no active scene loaded!");

    return instance.currentScene.get();
}