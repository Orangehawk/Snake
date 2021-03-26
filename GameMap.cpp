#include "GameMap.h"
#include <iostream>


GameMap::GameMap(int mapRows, int mapColumns)
{
	rows = mapRows;
	columns = mapColumns;

	gameMap = new char* [rows];
	for (int i = 0; i < rows; i++)
	{
		gameMap[i] = new char[columns];
	}

	ClearMap();
	CreateWalls();

	std::cout << "Snake starts at row: " << (int)round(mapRows / 2) << ", column: " << (int)round(mapColumns / 2) << std::endl;
	snake = new Snake((int)round(mapRows / 2), (int)round(mapColumns / 2));
	gameMap[snake->GetHead()->row][snake->GetHead()->column] = iconHead;
}

GameMap::~GameMap()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] gameMap[i];
	}
	delete[] gameMap;
	delete snake;
}

void GameMap::AddSnake(int row, int column)
{

}

bool GameMap::AddFood(int row, int column)
{
	if (gameMap[row][column] == iconEmpty)
	{
		gameMap[row][column] = iconFood;
		return true;
	}
	else
	{
		return false;
	}
}

bool GameMap::RemoveFood(int row, int column)
{
	std::cout << "RemoveFood: Not Implemented Yet" << std::endl;
	return false;
}

void GameMap::ClearMap()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			gameMap[i][j] = iconEmpty;
		}
	}
}

void GameMap::DisplayMap()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << gameMap[i][j];
		}
		std::cout << std::endl;
	}
}

void GameMap::MoveSnake(Direction dir)
{
	Tail* currentHead = snake->GetHead();
	Tail* currentTailEnd = snake->GetTail();

	gameMap[currentHead->row][currentHead->column] = iconTail;
	gameMap[currentTailEnd->row][currentTailEnd->column] = iconEmpty;

	int newRow = currentHead->row;
	int newColumn = currentHead->column;

	switch (dir)
	{
	case Direction::UP:
		newRow = currentHead->row - 1;
		break;
	case Direction::DOWN:
		newRow = currentHead->row + 1;
		break;
	case Direction::LEFT:
		newColumn = currentHead->column - 1;
		break;
	case Direction::RIGHT:
		newColumn = currentHead->column + 1;
		break;
	default:
		std::cout << "Invalid Direction" << std::endl;
	}

	if (CheckCell(newRow, newColumn) == 1 || CheckCell(newRow, newColumn) == 2)
	{
		std::cout << "GameOver" << std::endl;
		exit(0);
	}
	else if (CheckCell(newRow, newColumn) == 3)
	{
		snake->AddTail();
	}

	snake->MoveSnake(newRow, newColumn);

	currentHead = snake->GetHead();
	gameMap[currentHead->row][currentHead->column] = iconHead;
}

//void GameMap::UpdateSnake(Snake* snake)
//{
//	Tail* currentHead = snake->GetHead();
//	Tail* currentTailEnd = snake->GetTail();
//	Tail* newHead = snake->GetHead();
//
//	gameMap[currentHead->row][currentHead->column] = iconTail;
//	gameMap[currentTailEnd->row][currentTailEnd->column] = iconEmpty;
//	gameMap[newHead->row][newHead->column] = iconHead;
//
//	currentSnake = snake;
//}

void GameMap::CreateWalls()
{
	//Top row
	for (int i = 0; i < columns; i++)
	{
		gameMap[0][i] = iconWall;
	}

	//Bottom row
	for (int i = 0; i < columns; i++)
	{
		gameMap[rows - 1][i] = iconWall;
	}

	//Left column
	for (int i = 0; i < rows; i++)
	{
		gameMap[i][0] = iconWall;
	}

	//Right column
	for (int i = 0; i < rows; i++)
	{
		gameMap[i][columns - 1] = iconWall;
	}
}

int GameMap::CheckCell(int row, int column)
{
	if (gameMap[row][column] == iconEmpty)
		return 0;
	else if (gameMap[row][column] == iconWall)
		return 1;
	else if (gameMap[row][column] == iconTail)
		return 2;
	else if (gameMap[row][column] == iconFood)
		return 3;
	else
		return -1;
}