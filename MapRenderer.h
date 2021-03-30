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

	const std::string modelWall = "Models/Wall.obj";
	const std::string modelHead = "Models/SnakeHead.obj";
	const std::string modelTail = "Models/SnakeTail.obj";
	const std::string modelFood = "Models/Food.obj";
};