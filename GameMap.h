#pragma once
#include "Snake.h"
#include "GameObject.h"


class GameMap
{
public:
	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	GameMap(int mapRows, int mapColumns);
	~GameMap();
	int** GetMap() const;
	int GetRows() const;
	int GetColumns() const;
	Snake* GetSnake() const;
	//void AddSnake(int row, int column);
	bool AddFood(int row, int column);
	bool RemoveFood(int row, int column);
	void ClearMap();
	void DisplayMap();
	int GetIconWall() const;
	int GetIconHead() const;
	int GetIconTail() const;
	int GetIconFood() const;
	bool MoveSnake(Direction dir);

private:
	int rows;
	int columns;
	int** gameMap; 
	Snake* snake;

	int iconEmpty = 0;
	int iconWall = 1;
	int iconHead = 2;
	int iconTail = 3;
	int iconFood = 4;

	void CreateWalls();
	int CheckCell(int row, int column);
};