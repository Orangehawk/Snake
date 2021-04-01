#include "RenderManager.h"


int RenderManager::incrementalID;
std::map<int, GameObject*> RenderManager::gameObjects;


void RenderManager::Initialise()
{
    incrementalID = 0;
}

void RenderManager::Shutdown()
{
    std::map<int, GameObject*>::iterator it;

    for (it = gameObjects.begin(); it != gameObjects.end(); it++)
    {
        delete it->second;
    }

    gameObjects.clear();
}

int RenderManager::Register(GameObject* gameObject)
{
    gameObjects[incrementalID] = gameObject;
    return incrementalID++;
}

int RenderManager::UnRegister(int id)
{
    return gameObjects.erase(id);
}

void RenderManager::Render()
{
    std::map<int, GameObject*>::iterator it;

    for (it = gameObjects.begin(); it != gameObjects.end(); it++)
    {
        it->second->Render();
    }
}
