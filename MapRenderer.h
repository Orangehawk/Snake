#pragma once
#include <string>
#include "GameMap.h"
#include "OBJFile.h"


class MapRenderer
{
public:
	MapRenderer(const GameMap* map);
	void SetOffset(double x, double y, double z);
	void SetModelWall(OBJFile* wall);
	void SetModelSnakeHead(OBJFile* snakeHead);
	void SetModelSnakeTail(OBJFile* snakeTail);
	void SetModelFood(OBJFile* food);
	void UpdateMap();

private:
	const GameMap* storedMap;
};