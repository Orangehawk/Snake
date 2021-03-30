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


//Constants
const int mapSizeRows = 9;
const int mapSizeColumns = 25;


//Globals
char lastInput;
GameMap* map;
GameObject* snake;

//std::vector<GameObject*> gameObjects;

void MyInit()
{
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float fov = 70;
	float aspect = 2;
	float nearVal = 0.1f;
	float farVal = 1000;
	float light_position[] = { -mapSizeRows / 2, 10, mapSizeColumns / 2, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	gluPerspective(fov, aspect, nearVal, farVal);
	//gluOrtho2D(0.0f, 1000.0f, 500.0f, 0.0f);
	gluLookAt(-mapSizeRows / 2, 20, mapSizeColumns / 2, -mapSizeRows / 2, 0, mapSizeColumns / 2, 1, 0, 0);

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
	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();
	glTranslatef(-10, 0, 0);
	RenderManager::Render();
	glPopMatrix();

	glutSwapBuffers();
}

void MapSetupTest()
{
	map = new GameMap(mapSizeRows, mapSizeColumns);
	map->AddFood(3, 15);

	map->DisplayMap();
}

void KeyboardCallback(unsigned char ch, int x, int y)
{
	std::cout << ch << std::endl;
	if (ch == 27)
	{
		glutLeaveMainLoop();
	}
	else if (ch == 'w' || ch == 'W')
	{
		map->MoveSnake(GameMap::Direction::UP);
		snake->Translate(1, 0, 0);
		system("cls");
		map->DisplayMap();
		glutPostRedisplay();
	}
	else if (ch == 'a' || ch == 'A')
	{
		map->MoveSnake(GameMap::Direction::LEFT);
		snake->Translate(0, 0, -1);
		system("cls");
		map->DisplayMap();
		glutPostRedisplay();
	}
	else if (ch == 's' || ch == 'S')
	{
		map->MoveSnake(GameMap::Direction::DOWN);
		snake->Translate(-1, 0, 0);
		system("cls");
		map->DisplayMap();
		glutPostRedisplay();
	}
	else if (ch == 'd' || ch == 'D')
	{
		map->MoveSnake(GameMap::Direction::RIGHT);
		snake->Translate(0, 0, 1);
		system("cls");
		map->DisplayMap();
		glutPostRedisplay();
	}
}

void Initialise()
{
	RenderManager::Initialise();
}

void Run()
{

}

void Shutdown()
{
	RenderManager::Shutdown();
}

int main(int argc, char** argv)
{
	std::cout << "Program Start" << std::endl;

	Initialise();

	MapSetupTest();
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(1000, 500);
	glutCreateWindow("Snake");

	glutKeyboardFunc(KeyboardCallback);

	MyInit();
	OBJFile* wall = OBJUtils::LoadOBJ("SmolCube.obj");
	OBJFile* food = OBJUtils::LoadOBJ("Sphere.obj");
	snake = new GameObject(wall);
	snake->SetPosition(map->GetSnake()->GetHead()->row, 0, map->GetSnake()->GetHead()->column);
	int** n = map->GetMap();

	for (int i = 0; i < map->GetRows(); i++)
	{
		int iconWall = map->GetIconWall();
		int iconHead = map->GetIconHead();
		int iconTail = map->GetIconTail();
		int iconFood = map->GetIconFood();

		for (int j = 0; j < map->GetColumns(); j++)
		{
			if (n[i][j] == iconWall)
			{
				GameObject* obj = new GameObject(wall);
				obj->SetPosition(i, 0, j);
			}
			else if (n[i][j] == iconHead)
			{
				snake->SetPosition(i, 0, j);
			}
			else if (n[i][j] == iconTail)
			{

			}
			else if (n[i][j] == iconFood)
			{
				//std::cout << "set " << i << ", " << j << " | pos " << i + offsetX << ", " << j + offsetZ << std::endl;
				//GameObject* obj = new GameObject(food);
				//obj->SetPosition(i + offsetX, 0, j + offsetZ);
				//gameObjects.push_back(obj);
			}
		}
	}

	glutDisplayFunc(Display);
	glutMainLoop();

	delete map;

	Shutdown();

	std::cout << "Program End" << std::endl;

	return 0;
}