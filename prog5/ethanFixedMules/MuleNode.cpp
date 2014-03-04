//Daniel Fitzgerald
//Ethan Coeytaux

#include "prog5.h"
#include <iostream>
#include "MuleNode.h"
#include "Node.h"
#include "Position.h"


MuleNode::MuleNode(unsigned int  newID):
	Node(newID, 'M'),	//call constructor from superclass Node
	dir((Direction)(newID%4))
{
	placeRandomly(1, field.getLength()-1);
}

void MuleNode::hop(){
	int height = field.getHeight(); //get height of field (vertical)
	int length=field.getLength();	//get length of field (horizontal)
	int tempPos = (pos.getY() * length) + pos.getX(); //position of node on field
	Node* tempNode = field.getElement(*(new Position(tempPos))); //holds node
	field.setElement(*(new Position(tempPos)), NULL); //clears spot node is currently occupying
	bool complete = false;
	switch(dir) //checks to make sure node is not backed up against wall and needs to switch direction
	{
		case EAST:
		if ((tempPos + 2) % length == 0)
		{
			dir = WEST;
			complete = true;
		}
		break;
		case WEST:
		if ((tempPos - 1) % length == 0)
		{
			dir = EAST;
			complete = true;
		}
		break;
		case SOUTH:
		if (tempPos >= (height - 1) * length)
		{
			dir = NORTH;
			complete = true;
		}
		break;
		case NORTH:
		if (tempPos < length)
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
				if ((tempPos + 2) % length != 0) tempPos++;
				else dir = WEST;
				break;
				case WEST:
				if ((tempPos - 1) % length != 0) tempPos--;
				else dir = EAST;
				break;
				case SOUTH:
				if (tempPos < (height - 1) * length) tempPos += length;
				else dir = NORTH;
				break;
				case NORTH:
				if (tempPos >= length) tempPos -= length;
				else dir = SOUTH;
				break;
			}
		} while (field.getElement(*(new Position(tempPos))) != NULL); //continues until finds unoccupied spot, do while loop to ensure node will move once but can still end up where it started if neccesary
	}
	field.setElement(*(new Position(tempPos)), tempNode); //places new node
	int row = 0; //updates position inside node
	int col = tempPos;
	
	while (col > length)
	{
		row++;
		col -= length;
	}
	pos.setXY(col, row);
}
