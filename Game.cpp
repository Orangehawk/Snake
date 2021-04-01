#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "freeglut.h"
#include "GameMap.h"
#include "OBJUtils.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "ModelManager.h"
#include "MapRenderer.h"


//Constants
const int mapSizeRows = 9;
const int mapSizeColumns = 25;
const int updateTimer = 400;

//Globals
char lastInput = ' ';
bool lockInput = false;
GameMap* map;
MapRenderer* mapRenderer;

//Settings
bool EnableConsoleGame = true;


void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (EnableConsoleGame)
	{
		system("cls");
		map->DisplayMap();
	}

	mapRenderer->UpdateMap();
	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	RenderManager::Render();
	glPopMatrix();

	glutSwapBuffers();
}

void Move(int value)
{
	glutTimerFunc(updateTimer, Move, -1);

	bool success = true;

	if (lastInput == 'w' || lastInput == 'W')
	{
		success = map->MoveSnake(GameMap::Direction::UP);
	}
	else if (lastInput == 'a' || lastInput == 'A')
	{
		success = map->MoveSnake(GameMap::Direction::LEFT);
	}
	else if (lastInput == 's' || lastInput == 'S')
	{
		success = map->MoveSnake(GameMap::Direction::DOWN);
	}
	else if (lastInput == 'd' || lastInput == 'D')
	{
		success = map->MoveSnake(GameMap::Direction::RIGHT);
	}

	lockInput = false;
	glutPostRedisplay();

	//Game over
	if (!success)
		glutLeaveMainLoop();
}

void KeyboardCallback(unsigned char ch, int x, int y)
{
	if (!lockInput)
	{
		if (ch == 27)
		{
			glutLeaveMainLoop();
		}
		else if (ch == 'w' || ch == 'W')
		{
			if (lastInput != 's' && lastInput != 'S')
				lastInput = ch;
		}
		else if (ch == 'a' || ch == 'A')
		{
			if (lastInput != 'd' && lastInput != 'D')
				lastInput = ch;
		}
		else if (ch == 's' || ch == 'S')
		{
			if (lastInput != 'w' && lastInput != 'W')
				lastInput = ch;
		}
		else if (ch == 'd' || ch == 'D')
		{
			if (lastInput != 'a' && lastInput != 'A')
				lastInput = ch;
		}

		lockInput = true;
	}
}

void SetupGlut(int& argc, char** argv)
{
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(1000, 500);
	glutCreateWindow("Snake");

	glutKeyboardFunc(KeyboardCallback);


	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float fov = 70;
	float aspect = 2;
	float nearVal = 0.1f;
	float farVal = 1000;
	float light_position[] = { 0.5, 1, 0.5, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	gluPerspective(fov, aspect, nearVal, farVal);
	gluLookAt(-mapSizeRows / 2, 20, mapSizeColumns / 2, -mapSizeRows / 2, 0, mapSizeColumns / 2, 1, 0, 0);

	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(Display);
	glutTimerFunc(updateTimer, Move, -1);
}

void Initialise(int& argc, char** argv)
{
	RenderManager::Initialise();

	map = new GameMap(mapSizeRows, mapSizeColumns);
	map->AddFood(3, 15);

	if(EnableConsoleGame)
		map->DisplayMap();

	mapRenderer = new MapRenderer(map);

	SetupGlut(argc, argv);
}

void Run()
{
	glutMainLoop();
}

void Shutdown()
{
	delete map;
	delete mapRenderer;
	RenderManager::Shutdown();
	ModelManager::Shutdown();
}

int main(int argc, char** argv)
{
	Initialise(argc, argv);

	Run();

	Shutdown();

	return 0;
}