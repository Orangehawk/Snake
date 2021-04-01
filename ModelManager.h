#pragma once
#include <string>
#include <map>
#include "OBJFile.h"


class ModelManager
{
public:
	static void Shutdown();
	static OBJFile* GetModel(std::string fileName);

private:
	static std::map<std::string, OBJFile*> models;
};