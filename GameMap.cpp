#include "GameMap.h"
#include <iostream>
#include <random>


GameMap::GameMap(int mapRows, int mapColumns)
{
	rows = mapRows;
	columns = mapColumns;

	gameMap = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		gameMap[i] = new int[columns];
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

int** GameMap::GetMap() const
{
	return gameMap;
}

int GameMap::GetRows() const
{
	return rows;
}

int GameMap::GetColumns() const
{
	return columns;
}

Snake* GameMap::GetSnake() const
{
	return snake;
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
	if (gameMap[row][column] == iconFood)
	{
		gameMap[row][column] = iconEmpty;
		return true;
	}
	else
	{
		return false;
	}
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

int GameMap::GetIconWall() const
{
	return iconWall;
}

int GameMap::GetIconHead() const
{
	return iconHead;
}

int GameMap::GetIconTail() const
{
	return iconTail;
}

int GameMap::GetIconFood() const
{
	return iconFood;
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

	if (CheckCell(newRow, newColumn) == iconWall || CheckCell(newRow, newColumn) == iconTail)
	{
		std::cout << "GameOver" << std::endl;
		exit(0);
	}
	else if (CheckCell(newRow, newColumn) == iconFood)
	{
		snake->AddTail();
		RemoveFood(newRow, newColumn);
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> randRow(1.0, rows);
		std::uniform_real_distribution<double> randColumn(1.0, columns);

		int r, c;

		do
		{
			r = randRow(mt);
			c = randColumn(mt);
		} while (CheckCell(r, c) != iconEmpty);


		AddFood(r, c);
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
		return iconEmpty;
	else if (gameMap[row][column] == iconWall)
		return iconWall;
	else if (gameMap[row][column] == iconTail)
		return iconTail;
	else if (gameMap[row][column] == iconFood)
		return iconFood;
	else
		return -1;
}