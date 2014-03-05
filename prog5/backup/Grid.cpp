//Ethan Coeytaux
//Daniel Fitzgerald

#include <iostream>
#include "Packet.h"
#include "Node.h"
#include "Grid.h"
#include <vector>

using namespace std;

Grid::Grid()
{ }

void Grid::setSize(int newSize)
{
	height = newSize;
	length=height+2;
	field = new Node*[height * length];
}

void Grid::setElement(Position p, Node* element)
{
	int row=p.getY();
	int col=p.getX();
	int pos = (row * length) + col;
	field[pos] = element;
}

Node* Grid::getElement(Position p)
{
	int row=p.getY();
	int col=p.getX();
	int pos = (row * length) + col;
	return field[pos];
}

//returns a random position between with a column col where minCol<=col<maxCol
Position Grid::getUnoccupiedPosition(int minCol, int maxCol){
	int row, col;
	int range=maxCol-minCol;
	do{
		row = rand() % height;
		col = (rand() % range) + minCol;
	}while (getElement(Position(col,row)));
	return Position(col, row);
}

Position Grid::getUnoccupiedPosition(int col){
	int row;
	do{
		row = rand() % height;
	}while (getElement(Position(col,row)));
	return Position(col, row);
}

void Grid::print()
{
	cout<<"\nFIELD"<<endl;
	int i, j;
	for (i = 0; i < length; i++)
	{
		cout << "---";
	}
	cout << "--" << endl;
	for (i = 0; i < height; i++)
	{
		cout << "|";
		for (j = 0; j < length; j++)
		{
			int index=(i * length) + j;
			if (field[index]) cout << ((field[index]->getID() >= 9) ? "" : " ") << *field[index];
			else cout << "   ";
		}
		cout << "|" << endl;
	}
	for (i = 0; i < length; i++)
	{
		cout << "---";
	}
	cout << "--\n\n" << endl;
}

