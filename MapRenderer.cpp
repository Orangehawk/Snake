#include "MapRenderer.h"


MapRenderer::MapRenderer(const GameMap* map)
{
	storedMap = map;
	int** mapRaw = storedMap->GetMap();
	rows = storedMap->GetRows();
	columns = storedMap->GetColumns();
	iconWall = storedMap->GetIconWall();
	iconHead = storedMap->GetIconHead();
	iconTail = storedMap->GetIconTail();
	iconFood = storedMap->GetIconFood();

	food = new GameObject(modelFood);
	food->SetActive(false);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (mapRaw[i][j] == iconWall)
			{
				GameObject* obj = new GameObject(modelWall);
				obj->SetPosition(i, 0, j);
			}
			else if (mapRaw[i][j] == iconHead)
			{
				GameObject* obj = new GameObject(modelHead);
				obj->SetPosition(i, 0, j);
				snake.push_back(obj);
			}
			else if (mapRaw[i][j] == iconTail)
			{
				GameObject* obj = new GameObject(modelTail);
				obj->SetPosition(i, 0, j);
				snake.push_back(obj);
			}
			else if (mapRaw[i][j] == iconFood)
			{
				food->SetPosition(i, 0, j);
			}
		}
	}
}

void MapRenderer::SetOffset(double x, double y, double z)
{
	offset[0] = x;
	offset[1] = y;
	offset[2] = z;
}

void MapRenderer::UpdateMap()
{
	int** mapRaw = storedMap->GetMap();
	
	int snakeIterator = 1;
	food->SetActive(false);

	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < columns - 1; j++)
		{
			if (mapRaw[i][j] == iconHead)
			{
				GameObject* obj = snake[0];
				obj->SetPosition(i, 0, j);
			}
			else if (mapRaw[i][j] == iconTail)
			{
				GameObject* obj;

				if(snakeIterator < snake.size())
					obj = snake[snakeIterator];
				else
				{
					obj = new GameObject(modelTail);
					snake.push_back(obj);
				}

				obj->SetPosition(i, 0, j);
				snakeIterator++;
			}
			else if (mapRaw[i][j] == iconFood)
			{
				food->SetPosition(i, 0, j);
				food->SetActive(true);
			}
		}
	}
}