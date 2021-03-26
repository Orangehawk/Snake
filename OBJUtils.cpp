#include "OBJUtils.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "freeglut.h"
#include "FileUtils.h"


OBJFile* OBJUtils::LoadOBJ(std::string fileName)
{
	std::cout << "Entered \"Load OBJ\"" << std::endl;
	std::ifstream infile(fileName);
	std::string line;
	std::string token;

	if (!infile)
	{
		std::cout << "Failed to open OBJ file" << std::endl;
		return nullptr;
	}

	int totalFileLines = FileUtils::GetFileLineCount(fileName);
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

	return obj;

	std::cout << "Exiting \"Load OBJ\"" << std::endl;
}

void OBJUtils::DrawOBJ(OBJFile* obj, double* position = nullptr, double* rotation = nullptr)
{
	if (obj != nullptr)
	{
		std::vector<double*> vertices = obj->GetVertices();
		std::vector<int*> faces = obj->GetFaces();

		glPushMatrix();

		if (position != nullptr)
			glTranslated(position[0], position[1], position[2]);

		if (rotation != nullptr)
			glTranslated(rotation[0], rotation[1], rotation[2]);

		for (int i = 0; i < faces.size(); i++)
		{

			int* face = faces[i];
			glBegin(GL_TRIANGLES);
			glVertex3d(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);
			glVertex3d(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);
			glVertex3d(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);
			glEnd();

		}

		glPopMatrix();
	}
}