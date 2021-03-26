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

	void AddFace(unsigned int v1, unsigned int v2, unsigned int v3);
	std::vector<int*> GetFaces();

private:
		std::string name;
		std::vector<double*> vertices;
		std::vector<double*> textureVertices;
		std::vector<double*> normalVertices;
		std::vector<int*> faces;
};