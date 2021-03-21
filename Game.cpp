#include <iostream>
#include <Windows.h>
#include "GameMap.h"


GameMap* map;


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

	HANDLE hstdin;
	DWORD  mode;

	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hstdin, &mode);
	SetConsoleMode(hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);

	map = new GameMap(9, 25);
	map->AddFood(4, 21);
	map->AddFood(3, 6);
	map->AddFood(6, 23);
	map->AddFood(2, 1);
	map->AddFood(0, 15);

	while (true)
	{
		ClearScreen();
		map->DisplayMap();

		char ch = std::cin.get();

		switch (ch)
		{
		case 'w':
			map->MoveSnake(GameMap::Direction::UP);
			break;
		case 's':
			map->MoveSnake(GameMap::Direction::DOWN);
			break;
		case 'a':
			map->MoveSnake(GameMap::Direction::LEFT);
			break;
		case 'd':
			map->MoveSnake(GameMap::Direction::RIGHT);
			break;
		}

	}
	
	delete map;

	std::cout << "End" << std::endl;

	SetConsoleMode(hstdin, mode);
	return 0;
}