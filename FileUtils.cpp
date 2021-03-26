#include "FileUtils.h"
#include <fstream>


int FileUtils::GetFileLineCount(std::string fileName)
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