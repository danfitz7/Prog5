//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "MuleNode.h"
#include "Node.h"
#include "Position.h"


MuleNode::MuleNode(unsigned int  newID):
	Node(newID, 'M'),	//call constructor from superclass Node
	dir((Direction)(newID%4))
{
//TODO: init position so it's in a random unoccupied field space
	placeRandomly(1, field.getSize());
}

void MuleNode::hop(){
	int size = field.getSize(); //get size of field
	int tempPos = (pos.getX() * (size + 2)) + pos.getY(); //position of node on field
	Node* tempNode = field.getElement(*(new Position(tempPos))); //holds node
	field.setElement(*(new Position(tempPos)), NULL); //clears spot node is currently occupying
	bool complete = false;
	switch(dir) //checks to make sure node is not backed up against wall and needs to switch direction
	{
		case EAST:
		if ((tempPos + 2) % (size + 2) == 0)
		{
			dir = WEST;
			complete = true;
		}
		break;
		case WEST:
		if ((tempPos - 1) % (size + 2) == 0)
		{
			dir = EAST;
			complete = true;
		}
		break;
		case SOUTH:
		if (tempPos >= (size - 1) * (size + 2))
		{
			dir = NORTH;
			complete = true;
		}
		break;
		case NORTH:
		if (tempPos < size + 2)
		{
			dir = SOUTH;
			complete = true;
		}
		break;
	}
	if (!complete)
	{
		do
		{
			switch(dir)
			{
				case EAST:
				if ((tempPos + 2) % (size + 2) != 0) tempPos++;
				else dir = WEST;
				break;
				case WEST:
				if ((tempPos - 1) % (size + 2) != 0) tempPos--;
				else dir = EAST;
				break;
				case SOUTH:
				if (tempPos < (size - 1) * (size + 2)) tempPos += (size + 2);
				else dir = NORTH;
				break;
				case NORTH:
				if (tempPos >= size + 2) tempPos -= (size + 2);
				else dir = SOUTH;
				break;
			}
		} while (field.getElement(*(new Position(tempPos))) != NULL); //continues until finds unoccupied spot, do while loop to ensure node will move once but can still end up where it started if neccesary
	}
	field.setElement(*(new Position(tempPos)), tempNode); //places new node
	int row = 0; //updates position inside node
	int col = tempPos;
	while (col > size + 2)
	{
		row++;
		col -= (size + 2);
	}
	pos.setXY(row, col);
}
