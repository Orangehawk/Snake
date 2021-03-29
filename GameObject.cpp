#include "GameObject.h"
#include <iostream>
#include "OBJUtils.h"


GameObject::GameObject()
{
	isActive = true;
}

GameObject::GameObject(std::string fileName)
{
	isActive = true;
	LoadModel(fileName);
}

GameObject::GameObject(OBJFile* objModel)
{
	isActive = true;
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