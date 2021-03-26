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


GameMap* map;

std::vector<GameObject*> gameObjects;

void MyInit()
{
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float fov = 70;
	float aspect = 1;
	float nearVal = 0.1f;
	float farVal = 1000;

	gluPerspective(fov, aspect, nearVal, farVal);
	gluLookAt(5, 3, 5, 0, 0, 0, 0, 1, 0);

	glEnable(GL_DEPTH_TEST);
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
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DrawAxis(20);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Render();
	}

	glutSwapBuffers();
}

void MapSetupTest()
{
	map = new GameMap(9, 25);
	map->AddFood(4, 21);
	map->AddFood(3, 6);
	map->AddFood(6, 23);
	map->AddFood(2, 1);
	map->AddFood(0, 15);

	map->DisplayMap();
}

void KeyboardCallback(unsigned char ch, int x, int y)
{
	std::cout << ch << std::endl;
	if (ch == 27)
	{
		glutLeaveMainLoop();
	}
}

int main(int argc, char** argv)
{
	std::cout << "Program Start" << std::endl;
	MapSetupTest();
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Snake");

	glutKeyboardFunc(KeyboardCallback);

	MyInit();
	OBJFile* wall = OBJUtils::LoadOBJ("Cube.obj");
	GameObject* cube = new GameObject(wall);
	gameObjects.push_back(cube);

	glutDisplayFunc(Display);
	glutMainLoop();

	delete map;

	for (int i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}

	std::cout << "Program End" << std::endl;

	return 0;
}