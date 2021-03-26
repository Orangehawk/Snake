#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "GameMap.h"
#include "glut.h"


GameMap* map;

struct OBJ
{
	std::string name;
	int** vertices;
	int** textureVertices;
	int** normalVertices;
	int** faces;
};


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

int GetFileLineCount(std::string fileName)
{
	std::ifstream infile(fileName);
	std::string line;

	int count = 0;

	while (getline(infile, line, '\n'))
	{
		count++;
	}

	return count + 1; //Add extra 1 because there's no newline at the end of the file
}

void LoadOBJ(std::string fileName)
{
	std::cout << "enter" << std::endl;
	std::ifstream infile(fileName);
	std::string line;
	std::string token;

	if (!infile)
	{
		std::cout << "failed" << std::endl;
	}

	int row = 0;
	int column = 0;
	int totalFileLines = GetFileLineCount(fileName);

	std::cout << totalFileLines << std::endl;
	std::string** obj;

	//obj = new std::string* [totalFileLines];
	for (int i = 0; i < totalFileLines; i++)
	{
		obj[i] = new std::string[50];
	}

	struct OBJ obj;

	while (getline(infile, line, '\n'))
	{
		if (row > totalFileLines - 1)
			exit(-100);

		std::istringstream is(line);

		getline(is, token, ' ');
		obj[row][column] = token;
		std::cout << "r: " << row << " | c: " << column << " | " << token << " | " << obj[row][column] << std::endl;
		column++;

		while (getline(is, token, ' '))
		{
			obj[row][column] = token;
			std::cout << obj[row][column] << std::endl;
			column++;
		}
		column = 0;
		row++;
	}

	std::cout << "exit" << std::endl;
}

void DrawOBJ()
{

}

void DrawCube(float x, float y, float z, float size)
{
	float radius = size / 2;
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);

	glColor3f(1.0f, 0, 0);

	glVertex3f(x + radius, y + radius, z - radius);
	glVertex3f(x - radius, y + radius, z - radius);
	glVertex3f(x + radius, y + radius, z + radius);
	glVertex3f(x - radius, y + radius, z + radius);

	glVertex3f(x + radius, y - radius, z + radius);
	glVertex3f(x - radius, y - radius, z + radius);

	glColor3f(0, 1.0f, 0);

	glVertex3f(x - radius, y + radius, z - radius);
	glVertex3f(x - radius, y - radius, z - radius);





	glVertex3f(x + radius, y - radius, z - radius);
	glVertex3f(x + radius, y + radius, z - radius);

	glVertex3f(x + radius, y - radius, z + radius);
	glVertex3f(x + radius, y + radius, z + radius);


	glEnd();
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

	int camX = 5;
	int camY = 3;
	int camZ = 5;
	gluLookAt(5, 3, 5, 0, 0, 0, 0, 1, 0);



	//glutWireCube(1);
	DrawAxis(20);
	glPushMatrix();
	DrawCube(0, 0, 0, 1);
	glPopMatrix();

	glutSwapBuffers();
}

void TestInit()
{
	map = new GameMap(9, 25);
	map->AddFood(4, 21);
	map->AddFood(3, 6);
	map->AddFood(6, 23);
	map->AddFood(2, 1);
	map->AddFood(0, 15);

	map->DisplayMap();
}

int main(int argc, char** argv)
{
	std::cout << "Program Start" << std::endl;
	TestInit();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Test");

	MyInit();

	glutDisplayFunc(Display);
	glutMainLoop();

	delete map;

	LoadOBJ("cube.obj");

	std::cout << "End" << std::endl;

	return 0;
}