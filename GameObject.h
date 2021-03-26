#pragma once
#include "OBJFile.h"


class GameObject
{
public:
	GameObject();
	GameObject(std::string fileName);
	GameObject(OBJFile* objModel);
	void Render();
	void LoadModel(std::string fileName);
	void LoadModel(OBJFile* objModel);
	void SetPosition(int x, int y, int z);
	void Translate(int x, int y, int z);
	void SetRotation(int x, int y, int z);
	void Rotate(int angle, int x, int y, int z);
private:
	double position[3] = { 0 };
	double rotation[4] = { 0 };
	OBJFile* model;
};