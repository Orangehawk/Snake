#include "Snake.h"


Snake::Snake(int mapRows, int mapColumns)
{
	head = new Tail;
	tailLast = head;
	tailSize = 1;
	head->row = mapRows;
	head->column = mapColumns;
}

Snake::~Snake()
{
	Tail* current;
	if (tailLast->prev != nullptr)
		current = tailLast->prev;
	else
		current = tailLast;

	do
	{
		if (current->next != nullptr)
		{
			delete current->next;
			if (current->prev != nullptr)
				current = current->prev;
		}
	} while (current->prev != nullptr);

	delete current;
}

void Snake::MoveSnake(int row, int column)
{
	if (tailSize > 1)
	{
		Tail* currentHead = head;
		Tail* currentTail = tailLast;

		tailLast = currentTail->prev; //Move tail to new tail end
		currentTail->row = row;
		currentTail->column = column;
		currentTail->prev = nullptr; //Disconnect old tail end from tail
		currentTail->next = currentHead; //Start setting the old tail up as the new head
		currentHead->prev = currentTail; //Old head is now tail segment
		head = currentTail; //Set head pointing to new head
	}
	else
	{
		head->row = row;
		head->column = column;
	}

	//Tail* currentTail = tailLast;
	//Tail* nextTail = currentTail->prev;

	////Might just remove endtail and add head, would save performance

	//for (int i = 0; i < tailSize; i++)
	//{
	//	currentTail->row = nextTail->row;
	//	currentTail->column = nextTail->column;
	//	currentTail = nextTail;
	//	nextTail = nextTail->prev;
	//}
}

Tail* Snake::GetHead() const
{
	return head;
}

Tail* Snake::GetTail() const
{
	return tailLast;
}

int Snake::GetTailSize()
{
	return tailSize;
}

void Snake::AddTail()
{
	Tail* nextTail = new Tail;
	nextTail->row = tailLast->row;
	nextTail->column = tailLast->column;
	nextTail->prev = tailLast;

	tailLast->next = nextTail;
	tailLast = nextTail;

	tailSize++;
}