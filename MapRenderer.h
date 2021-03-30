#pragma once
#include <string>
#include <vector>
#include "GameMap.h"
#include "OBJFile.h"


class MapRenderer
{
public:
	MapRenderer(const GameMap* map);
	void SetOffset(double x, double y, double z);
	//void SetModelWall(OBJFile* wall);
	//void SetModelSnakeHead(OBJFile* snakeHead);
	//void SetModelSnakeTail(OBJFile* snakeTail);
	//void SetModelFood(OBJFile* food);
	void UpdateMap();

private:
	const GameMap* storedMap;
	int rows, columns;
	int iconWall;
	int iconHead;
	int iconTail;
	int iconFood;

	std::vector<GameObject*> snake;
	GameObject* food;

	double offset[3] = { 0 };

	const std::string modelWall = "SmolCube.obj";
	const std::string modelHead = "SmolCube.obj";
	const std::string modelTail = "SmolCube.obj";
	const std::string modelFood = "Sphere.obj";
};