#pragma once
#include <string>
#include <vector>

class OBJFile
{
public:
	OBJFile();
	~OBJFile();

	void SetName(std::string name);
	std::string GetName();

	void AddVertice(double x, double y, double z);
	std::vector<double*> GetVertices();

	void AddTextureVertice(double x, double y, double z);
	std::vector<double*> GetTextureVertices();

	void AddNormalVertice(double x, double y, double z);
	std::vector<double*> GetNormalVertices();

	void AddFace(unsigned int v1, unsigned int v2, unsigned int v3);
	std::vector<int*> GetFaces();

	void AddNormalFace(unsigned int v1, unsigned int v2, unsigned int v3);
	std::vector<int*> GetNormalFaces();

private:
		std::string name;
		std::vector<double*> vertices;
		std::vector<double*> textureVertices;
		std::vector<double*> normalVertices;
		std::vector<int*> faces;
		std::vector<int*> normalFaces;
};