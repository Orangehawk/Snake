#include "OBJUtils.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "freeglut.h"
#include "FileUtils.h"


OBJFile* OBJUtils::LoadOBJ(std::string fileName)
{
	std::cout << "Loading OBJ \"" << fileName << "\"" << std::endl;
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
			double x, y, z;

			getline(is, token, ' ');
			x = std::stof(token);

			getline(is, token, ' ');
			y = std::stof(token);

			getline(is, token, ' ');
			z = std::stof(token);

			obj->AddTextureVertice(x, y, z);
		}
		else if (token == "vn")
		{
			double x, y, z;

			getline(is, token, ' ');
			x = std::stof(token);

			getline(is, token, ' ');
			y = std::stof(token);

			getline(is, token, ' ');
			z = std::stof(token);

			obj->AddNormalVertice(x, y, z);

		}
		else if (token == "f")
		{
			int vertices[3] = { 0 };
			int normalVertices[3] = { 0 };

			for (int i = 0; i < 3; i++)
			{
				getline(is, token, ' ');
				std::istringstream is2(token);


				getline(is2, token, '/');
				vertices[i] = std::stoi(token) - 1;

				if (getline(is2, token, '/'))
				{

				}

				if (getline(is2, token, '/'))
					normalVertices[i] = std::stoi(token) - 1;
			}

			obj->AddFace(vertices[0], vertices[1], vertices[2]);
			obj->AddNormalFace(normalVertices[0], normalVertices[1], normalVertices[2]);
		}
		else
		{
			//std::cout << "unsupported token" << std::endl;
		}
	}

	return obj;
}

void OBJUtils::DrawOBJ(OBJFile* obj, double* position = nullptr, double* rotation = nullptr)
{
	if (obj != nullptr)
	{
		std::vector<double*> vertices = obj->GetVertices();
		std::vector<double*> normals = obj->GetNormalVertices();
		std::vector<int*> faces = obj->GetFaces();
		std::vector<int*> normalFaces = obj->GetNormalFaces();

		glPushMatrix();

		if (position != nullptr)
			glTranslated(position[0], position[1], position[2]);

		if (rotation != nullptr)
			glTranslated(rotation[0], rotation[1], rotation[2]);

		for (unsigned int i = 0; i < faces.size(); i++)
		{
			int* face = faces[i];
			int* normalFace = normalFaces[i];

			glBegin(GL_TRIANGLES);
			glNormal3d(normals[normalFace[0]][0], normals[normalFace[0]][1], normals[normalFace[0]][2]);
			glVertex3d(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);
			glNormal3d(normals[normalFace[1]][0], normals[normalFace[1]][1], normals[normalFace[1]][2]);
			glVertex3d(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);
			glNormal3d(normals[normalFace[2]][0], normals[normalFace[2]][1], normals[normalFace[2]][2]);
			glVertex3d(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);
			glEnd();
		}

		glPopMatrix();
	}
}