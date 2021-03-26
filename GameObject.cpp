#include "GameObject.h"
#include <iostream>
#include "OBJUtils.h"


GameObject::GameObject()
{

}

GameObject::GameObject(std::string fileName)
{
	LoadModel(fileName);
}

GameObject::GameObject(OBJFile* objModel)
{
	LoadModel(objModel);
}

void GameObject::Render()
{
	OBJUtils::DrawOBJ(model, position, rotation);
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

void GameObject::SetPosition(int x, int y, int z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void GameObject::Translate(int x, int y, int z)
{
	position[0] += x;
	position[1] += y;
	position[2] += z;
}

void GameObject::SetRotation(int x, int y, int z)
{
	std::cout << "Didn't bother with working this out yet, just don't rotate it, dummy =w=" << std::endl;
	/*rotation[0] = x;
	rotation[1] = y;
	rotation[2] = z;*/
}

void GameObject::Rotate(int angle, int x, int y, int z)
{
	std::cout << "Didn't bother with working this out yet, just don't rotate it, dummy =w=" << std::endl;
	/*rotation[0] = angle;
	rotation[1] = x;
	rotation[2] = y;
	rotation[3] = z;*/
}