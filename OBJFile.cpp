#include "OBJFile.h"

OBJFile::OBJFile()
{
	
}

OBJFile::~OBJFile()
{
	unsigned int i;

	for (i = 0; i < vertices.size(); i++)
	{
		delete[] vertices[i];
	}

	for (i = 0; i < textureVertices.size(); i++)
	{
		delete[] textureVertices[i];
	}

	for (i = 0; i < normalVertices.size(); i++)
	{
		delete[] normalVertices[i];
	}

	for (i = 0; i < faces.size(); i++)
	{
		delete[] faces[i];
	}

	for (i = 0; i < normalFaces.size(); i++)
	{
		delete[] normalFaces[i];
	}
}

void OBJFile::SetName(std::string objName)
{
	name = objName;
}

std::string OBJFile::GetName()
{
	return name;
}

void OBJFile::AddVertice(double x, double y, double z)
{
	double* vertice = new double[3];
	vertice[0] = x;
	vertice[1] = y;
	vertice[2] = z;
	vertices.push_back(vertice);
}

std::vector<double*> OBJFile::GetVertices()
{
	return vertices;
}

void OBJFile::AddTextureVertice(double x, double y, double z)
{
	double* vertice = new double[3];
	vertice[0] = x;
	vertice[1] = y;
	vertice[2] = z;
	textureVertices.push_back(vertice);
}

std::vector<double*> OBJFile::GetTextureVertices()
{
	return textureVertices;
}

void OBJFile::AddNormalVertice(double x, double y, double z)
{
	double* vertice = new double[3];
	vertice[0] = x;
	vertice[1] = y;
	vertice[2] = z;
	normalVertices.push_back(vertice);
}

std::vector<double*> OBJFile::GetNormalVertices()
{
	return normalVertices;
}

void OBJFile::AddFace(unsigned int v1, unsigned int v2, unsigned int v3)
{
	int* face = new int[3];
	face[0] = v1;
	face[1] = v2;
	face[2] = v3;
	faces.push_back(face);
}

std::vector<int*> OBJFile::GetFaces()
{
	return faces;
}

void OBJFile::AddNormalFace(unsigned int v1, unsigned int v2, unsigned int v3)
{
	int* face = new int[3];
	face[0] = v1;
	face[1] = v2;
	face[2] = v3;
	normalFaces.push_back(face);
}

std::vector<int*> OBJFile::GetNormalFaces()
{
	return normalFaces;
}