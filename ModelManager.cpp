#include "ModelManager.h"
#include "OBJUtils.h"


std::map<std::string, OBJFile*> ModelManager::models;


void ModelManager::Shutdown()
{
	std::map<std::string, OBJFile*>::iterator it;

	for (it = models.begin(); it != models.end(); it++)
	{
		delete it->second;
	}

	models.clear();
}

OBJFile* ModelManager::GetModel(std::string fileName)
{
	if (models.find(fileName) != models.end())
	{
		return models[fileName];
	}
	else
	{
		OBJFile* model = OBJUtils::LoadOBJ(fileName);

		if (model == nullptr)
		{
			return nullptr;
		}
		else
		{
			models[fileName] = model;
			return model;
		}
	}
}