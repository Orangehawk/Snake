#include <iostream>
#include <Windows.h>
#include "GameMap.h"


GameMap* map;

//Swap for glut/glfw
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
	int waitTime = 100;
	Sleep(waitTime);
	ClearScreen();
	map->DisplayMap();
}

TCHAR getkeypress()
{
	DWORD mode, count;
	HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
	if (h == NULL) return 0;  // not a console
	GetConsoleMode(h, &mode);
	SetConsoleMode(h, 0);
	TCHAR c = 0;
	ReadConsole(h, &c, 1, &count, NULL);
	SetConsoleMode(h, mode);
	return c;
}

int main()
{
	std::cout << "Program Start" << std::endl;

	map = new GameMap(9, 25);
	map->AddFood(4, 21);
	map->AddFood(3, 6);
	map->AddFood(6, 23);
	map->AddFood(2, 1);
	map->AddFood(0, 15);

	ClearScreen();
	map->DisplayMap();
	Sleep(2000);

	char ch = 'a';
	char dir = ' ';
	while (true)
	{
		ch = getkeypress();

		if (dir != ch && (ch == 'w' || ch == 's' || ch == 'a' || ch == 'd'))
			dir = ch;

		switch (dir)
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

		Step();
		std::cout << dir << std::endl;
		std::cout << dir << std::endl;
		std::cout << dir << std::endl;
	}
	
	delete map;

	std::cout << "End" << std::endl;

	return 0;
}