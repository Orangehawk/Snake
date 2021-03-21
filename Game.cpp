#include <iostream>
#include <Windows.h>
#include "GameMap.h"


void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

GameMap* map;
void Step()
{
	int waitTime = 500;
	Sleep(waitTime);
	ClearScreen();
	map->DisplayMap();
}

int main()
{
	std::cout << "Program Start" << std::endl;

	/*GameMap* */map = new GameMap(9, 25);
	map->AddFood(4, 11);
	ClearScreen();
	map->DisplayMap();
	Sleep(2000);
	map->MoveSnake(GameMap::Direction::LEFT);
	Step();
	map->MoveSnake(GameMap::Direction::LEFT);
	Step();
	map->MoveSnake(GameMap::Direction::LEFT);
	Step();
	map->MoveSnake(GameMap::Direction::LEFT);
	Step();
	map->MoveSnake(GameMap::Direction::LEFT);
	Step();
	delete map;

	std::cout << "End" << std::endl;

	return 0;
}