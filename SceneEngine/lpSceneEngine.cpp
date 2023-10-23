#include "lpsmpch.h"
#include "lpSceneEngine.h"

LP_Export void SceneManager::LoadSceneAsActive(Scene* scene)
{
    if(activeScene != nullptr)
    {
	    
    }
    activeScene = scene;
    
}

LP_Export void SceneManager::LoadSceneAsActive(int sceneIndex)
{
    
}

LP_Export void Scene::OnLoad()
{
    for(MonoBehaviour* behaviour : mono_behaviours_in_the_scene)
    {
       MonoObject* object =  behaviour->CreateInstance(activeScriptingEngine);
       mono_runtime_invoke(behaviour->startMethod, nullptr, nullptr, &object);
       created_objects[behaviour] = object;
    }
}

LP_Export void Scene::OnUnload()
{
    
}
