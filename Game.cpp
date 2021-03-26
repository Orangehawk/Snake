#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "glut.h"
#include "GameMap.h"
#include "OBJFile.h"


GameMap* map;
OBJFile* cube;

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

OBJFile* LoadOBJ(std::string fileName)
{
	std::cout << "Entered \"Load OBJ\"" << std::endl;
	std::ifstream infile(fileName);
	std::string line;
	std::string token;

	if (!infile)
	{
		//std::cout << "Failed to open OBJ file" << std::endl;
	}

	int totalFileLines = GetFileLineCount(fileName);
	std::cout << totalFileLines << std::endl;

	OBJFile* obj = new OBJFile();
	int count = 0;
	while (getline(infile, line, '\n'))
	{
		std::istringstream is(line);

		getline(is, token, ' ');
		if (token == "o")
		{
			getline(is, token, ' ');
			obj->SetName(token);
		}
		else if (token == "v")
		{
			double x, y, z;

			getline(is, token, ' ');
			x = std::stof(token);

			getline(is, token, ' ');
			y = std::stof(token);

			getline(is, token, ' ');
			z = std::stof(token);

			obj->AddVertice(x, y, z);
		}
		else if (token == "vt")
		{
			//std::cout << "vt unsupported currently" << std::endl;
		}
		else if (token == "vn")
		{
			//std::cout << "vn unsupported currently" << std::endl;

		}
		else if (token == "f")
		{
			int vertices[3];

			for (int i = 0; i < 3; i++)
			{
				getline(is, token, ' ');
				vertices[i] = std::stof(token) - 1;
			}

			obj->AddFace(vertices[0], vertices[1], vertices[2]);
		}
		else
		{
			//std::cout << "unsupported token" << std::endl;
		}
	}

	for (int i = 0; i < obj->GetVertices().size(); i++)
	{
	}

	return obj;

	std::cout << "Exiting \"Load OBJ\"" << std::endl;
}

void DrawOBJ(OBJFile* obj)
{
	std::vector<double*> vertices = obj->GetVertices();
	std::vector<int*> faces = obj->GetFaces();

	for (int i = 0; i < faces.size(); i++)
	{
		glBegin(GL_TRIANGLES);
		int* face = faces[i];
		glVertex3d(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);
		glVertex3d(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);
		glVertex3d(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);
		glEnd();
	}
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

	glPushMatrix();
	DrawOBJ(cube);
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
	glutCreateWindow("Snake");

	MyInit();

	cube;
	cube = LoadOBJ("Sphere.obj");
	glutDisplayFunc(Display);
	glutMainLoop();

	delete map;


	std::cout << "End" << std::endl;

	return 0;
}