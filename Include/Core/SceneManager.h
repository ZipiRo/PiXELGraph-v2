#pragma once

#include <vector>
#include <string>
#include <functional>

class Scene
{
private:
    friend class PiXELGraph;
    friend class SceneManager;
    
    virtual void Start() {}
    virtual void Event() {}
    virtual void Update() {}
    virtual void Draw() {}
    virtual void Quit() {} 

public:
    std::string name;
    int buildIndex;
};

struct SceneInfo
{
    std::string name;
    int buildIndex;
    std::function<Scene*()> createFunction;
};

class SceneManager
{
private:
    Scene *currentScene;
    std::vector<SceneInfo> scenes;
    bool changeScene;
    
    SceneManager();
    static void RunScene();

    friend class PiXELGraph;
public:
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    static SceneManager &GetInstance();
    
    template <typename T>
    static void AddScene(const std::string &sceneName);

    static void LoadScene(int buildIndex);
    static Scene* GetActiveScene();
};

template <typename T>
void SceneManager::AddScene(const std::string &sceneName)
{
    auto &instance = GetInstance();
    int buildIndex = instance.scenes.size();

    SceneInfo new_scene;
    new_scene.buildIndex = buildIndex;
    new_scene.name = sceneName;
    new_scene.createFunction = [=]() { return new T(); };

    instance.scenes.push_back(new_scene);
}