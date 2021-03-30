#pragma once
#include <string>
#include "OBJFile.h"


class OBJUtils
{
public:
	static OBJFile* LoadOBJ(std::string fileName);
	static void DrawOBJ(OBJFile* obj, double* position, double* rotation);
};