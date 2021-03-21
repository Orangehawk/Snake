#pragma once
#include "Snake.h"


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
	void AddSnake(int row, int column);
	bool AddFood(int row, int column);
	bool RemoveFood(int row, int column);
	void ClearMap();
	void DisplayMap();
	void SetIconWall(char wall);
	void SetIconHead(char head);
	void SetIconTail(char tail);
	void SetIconFood(char food);
	void MoveSnake(Direction dir);
	//void UpdateSnake(Snake* snake);

private:
	int rows;
	int columns;
	char** gameMap; 
	Snake* snake;

	char iconEmpty = ' ';
	char iconWall = '#';
	char iconHead = 'O';
	char iconTail = 'o';
	char iconFood = '@';


	void CreateWalls();
	//0 - empty, 1 - wall, 2 - player, 3 - food
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