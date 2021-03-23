#include <iostream>
#include <Windows.h>
#include "glfw3.h"
#include "GameMap.h"


GameMap* map;


void Init()
{
	if (!glfwInit())
	{
		std::cout << "GLFW Init Failure" << std::endl;
		exit(-20);
	}
}

int main()
{
	std::cout << "Program Start" << std::endl;

	Init();

	int* nulltest = nullptr;
	if (!nulltest)
	{
		std::cout << "Seems so" << std::endl;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Snake", NULL, NULL);

	if (!window)
	{
		std::cout << "GLFW Window Create Failure" << std::endl;
		exit(-21);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	map = new GameMap(9, 25);
	map->AddFood(4, 21);
	map->AddFood(3, 6);
	map->AddFood(6, 23);
	map->AddFood(2, 1);
	map->AddFood(0, 15);

	map->DisplayMap();
	Sleep(5000);
	
	delete map;

	glfwDestroyWindow(window);
	glfwTerminate();

	std::cout << "End" << std::endl;

	return 0;
}