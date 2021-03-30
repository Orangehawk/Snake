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


void SetupGlut()
{
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
	//gluOrtho2D(0.0f, 1000.0f, 500.0f, 0.0f);
	gluLookAt(-mapSizeRows / 2, 20, mapSizeColumns / 2, -mapSizeRows / 2, 0, mapSizeColumns / 2, 1, 0, 0);

	glEnable(GL_DEPTH_TEST);
}

void Initialise()
{
	RenderManager::Initialise();

	map = new GameMap(mapSizeRows, mapSizeColumns);
	map->AddFood(3, 15);
	map->DisplayMap();

	mapRenderer = new MapRenderer(map);
}

void Run()
{

}

void Shutdown()
{
	delete map;
	delete mapRenderer;
	RenderManager::Shutdown();
}

void DrawAxis(float distance)
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(distance, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, distance, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, distance);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DrawAxis(20);

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

	if (lastInput == 'w' || lastInput == 'W')
	{
		map->MoveSnake(GameMap::Direction::UP);
	}
	else if (lastInput == 'a' || lastInput == 'A')
	{
		map->MoveSnake(GameMap::Direction::LEFT);
	}
	else if (lastInput == 's' || lastInput == 'S')
	{
		map->MoveSnake(GameMap::Direction::DOWN);
	}
	else if (lastInput == 'd' || lastInput == 'D')
	{
		map->MoveSnake(GameMap::Direction::RIGHT);
	}

	lockInput = false;
	system("cls");
	map->DisplayMap();
	glutPostRedisplay();
}

void KeyboardCallback(unsigned char ch, int x, int y)
{
	if (!lockInput)
	{
		std::cout << ch << std::endl;
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

int main(int argc, char** argv)
{
	std::cout << "Program Start" << std::endl;
	Initialise();

	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(1000, 500);
	glutCreateWindow("Snake");

	glutKeyboardFunc(KeyboardCallback);

	SetupGlut();
	glutDisplayFunc(Display);
	glutTimerFunc(updateTimer, Move, -1);
	glutMainLoop();

	Shutdown();
	std::cout << "Program End" << std::endl;

	return 0;
}