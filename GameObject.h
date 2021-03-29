#pragma once
#include "OBJFile.h"


class GameObject
{
public:
	GameObject();
	GameObject(std::string fileName);
	GameObject(OBJFile* objModel);
	void Render();
	void SetActive(bool active);
	bool GetActive();
	void LoadModel(std::string fileName);
	void LoadModel(OBJFile* objModel);
	void SetPosition(double x, double y, double z);
	void Translate(double x, double y, double z);
	void SetRotation(double x, double y, double z);
	void Rotate(double angle, double x, double y, double z);
private:
	bool isActive;
	double position[3] = { 0 };
	double rotation[4] = { 0 };
	OBJFile* model;
};