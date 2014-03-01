//Ethan Coeytaux
//Daniel Fitzgerald

#include <iostream>
#include "Packet.h"
#include "Node.h"
#include "Grid.h"
#include <vector>

using namespace std;

Grid::Grid(int SIZE):
	size(SIZE),
	field(new Queue[size][10])
{
}

void Grid::addSender(Node*)
{
	int i, count = 1;
	for (i = 0; i < sources; i++)
	{
		int row = rand() % height;
		if (field[row][0] == NULL)
		{
			Queue *newNode = new Queue(count++, true, false, row, 0, rand() % 4);
			field[row][0] = newNode;
			nodes.push_back(*newNode);
		}
		else i--;
	}
}

void Grid::addMules()
{
	int i, count = sources + 1;
	for (i = 0; i < mules; i++)
	{
		int row = rand() % height;
		int col = rand() % (width - 1) + 1;
		if (field[row][col] == NULL)
		{
			Queue *newNode = new Queue(count++, false, false, row, col, rand() % 4);
			field[row][col] = newNode;
			nodes.push_back(*newNode);
		}
		else i--;
	}
}

void Grid::addReceivers()
{
	int i, count = sources + mules + 1;
	for (i = 0; i < receivers; i++)
	{
		int row = rand() % height;
		if (field[row][width - 1] == NULL)
		{
			Queue *newNode = new Queue(count++, true, false, row, 0, rand() % 4);
			field[row][width - 1] = newNode;
			nodes.push_back(*newNode);
		}
		else i--;
	}
}

void Grid::moveNodes()
{
	int i;
	for (i = sources - 1; i < sources + mules - 1; i++)
	{
		Queue *tempQueue = &nodes[i];
		int row = (*tempQueue).getRow(), col = (*tempQueue).getCol();
		int tempRow = row, tempCol = col;
		int direction = (*tempQueue).getDirection();
		switch(direction)
		{
			case 0:
			case 2:
            while (field[tempRow][tempCol]) //if moving vertically, continues until find empty space (i.e. hops over other nodes)
            {
            	if ((tempRow == 0) && (direction == 0)) direction = 2; //switches direction if against wall
            	else if ((tempRow == height - 1) && (direction == 2)) direction = 0; //switches direction if against wall
                if (direction == 0) tempRow--;
                else tempRow++;
            }
            field[row][col] = NULL;
            (*tempQueue).setRow(tempRow);
            (*tempQueue).setDirection(direction);
			break;
			case 1:
			case 3:
            while (field[tempRow][tempCol]) //if moving vertically, continues until find empty space (i.e. hops over other nodes)
            {
            	if ((tempCol == 1) && (direction == 1)) direction = 3; //switches direction if against wall
            	else if ((tempCol == width - 2) && (direction == 3)) direction = 1; //switches direction if against wall
                if (direction == 1) tempCol--;
                else tempCol++;
            }
            field[row][col] = NULL;
            (*tempQueue).setCol(tempCol);
            (*tempQueue).setDirection(direction);
			break;
		}
	}
}

void Grid::print()
{
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
	int i, j;
	for (i = 0; i < height; i++)
	{
		cout << "|";
		for (j = 0; j < width; j++)
		{
			if (field[i][j]) cout << " " << ((*field[i][j]).getID() >= 10 ? "" : " ") << (*field[i][j]).getID();
			else cout << "   ";
		}
		cout << "|" << endl;
	}
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
}
















