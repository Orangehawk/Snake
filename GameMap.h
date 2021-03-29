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
	int GetRows();
	int GetColumns();
	Snake* GetSnake() const;
	void AddSnake(int row, int column);
	bool AddFood(int row, int column);
	bool RemoveFood(int row, int column);
	void ClearMap();
	void DisplayMap();
	int GetIconWall();
	int GetIconHead();
	int GetIconTail();
	int GetIconFood();
	void MoveSnake(Direction dir);
	//void UpdateSnake(Snake* snake);

private:
	int rows;
	int columns;
	int** gameMap; 
	Snake* snake;
	GameObject* food;

	int iconEmpty = 0;
	int iconWall = 1;
	int iconHead = 2;
	int iconTail = 3;
	int iconFood = 4;


	void CreateWalls();
	//0 - empty, 1 - wall, 2 - player head, 3 - player, 4 - food
	int CheckCell(int row, int column);
};

/*
-----Map Example-----
std::cout << "#########################" << std::endl;
std::cout << "#                 o     #" << std::endl;
std::cout << "#              oooo     #" << std::endl;
std::cout << "#      @   Ooooo        #" << std::endl;
std::cout << "#                       #" << std::endl;
std::cout << "#                       #" << std::endl;
std::cout << "#                       #" << std::endl;
std::cout << "#########################" << std::endl;
*/