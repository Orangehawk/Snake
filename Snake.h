#pragma once

struct Tail
{
	int row;
	int column;
	Tail* next = nullptr;
	Tail* prev = nullptr;
	bool freeze = true; //Used for when adding a new tail segment, compare and then set to false when moving the snake
};

class Snake
{
public:
	Snake(int mapRows, int mapColumns);
	~Snake();
	void MoveSnake(int row, int column); //Move from back of tail to front, ending with head
	Tail* GetHead() const;
	Tail* GetTail() const;
	int GetTailSize();
	void AddTail(); //Add a tail segment in the same position as the end of the current tail and freeze it
private:
	int tailSize = 0;
	Tail* head; //First node is head, all others are tail
	Tail* tailLast;
};