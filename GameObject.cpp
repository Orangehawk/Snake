#include "GameObject.h"
#include <iostream>
#include "OBJUtils.h"
#include "RenderManager.h"


GameObject::GameObject()
{
	Init();
}

GameObject::GameObject(std::string fileName)
{
	Init();
	LoadModel(fileName);
}

GameObject::GameObject(OBJFile* objModel)
{
	Init();
	LoadModel(objModel);
}

void GameObject::Render()
{
	if (isActive)
		OBJUtils::DrawOBJ(model, position, rotation);
}

void GameObject::SetActive(bool active)
{
	isActive = active;
}

bool GameObject::GetActive()
{
	return isActive;
}

void GameObject::LoadModel(std::string fileName)
{
	model = OBJUtils::LoadOBJ(fileName);
}

void GameObject::LoadModel(OBJFile* objModel)
{
	if (objModel != nullptr)
		model = objModel;
}

void GameObject::SetPosition(double x, double y, double z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void GameObject::Translate(double x, double y, double z)
{
	position[0] += x;
	position[1] += y;
	position[2] += z;
}

void GameObject::SetRotation(double x, double y, double z)
{
	std::cout << "Didn't bother with working this out yet, just don't rotate it, dummy =w=" << std::endl;
	/*rotation[0] = x;
	rotation[1] = y;
	rotation[2] = z;*/
}

void GameObject::Rotate(double angle, double x, double y, double z)
{
	std::cout << "Didn't bother with working this out yet, just don't rotate it, dummy =w=" << std::endl;
	/*rotation[0] = angle;
	rotation[1] = x;
	rotation[2] = y;
	rotation[3] = z;*/
}

void GameObject::Init()
{
	isActive = true;
	RenderManager::Register(this);
}
