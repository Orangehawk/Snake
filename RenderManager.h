#pragma once
#include <vector>
#include <map>
#include "GameObject.h"


class RenderManager
{
public:
	static void Initialise();
	static void Shutdown();
	static int Register(GameObject* gameObject);
	static int UnRegister(int id);
	static void Render();

private:
	static int incrementalID;
	static std::map<int, GameObject*> gameObjects;
};