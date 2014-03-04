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
	size = newSize;
	field = new Node*[size * (size + 2)];
}

void Grid::setElement(Position p, Node* element)
{
	int row=p.getX();
	int col=p.getY();
	int pos = (row * (size + 2)) + col;
	field[pos] = element;
}

Node* Grid::getElement(Position p)
{
	int row=p.getX();
	int col=p.getY();
	int pos = (row * (size + 2)) + col;
	return field[pos];
}

void Grid::print()
{
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
	int i, j;
	for (i = 0; i < size; i++)
	{
		cout << "|";
		for (j = 0; j < size + 2; j++)
		{
			if (field[(i * (size + 2)) + j]) cout << ((*field[(i * (size + 2)) + j]).getID() >= 9 ? "" : " ") << *field[(i * (size + 2)) + j];
			else cout << "   ";
		}
		cout << "|" << endl;
	}
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
}
















