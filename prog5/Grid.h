//Ethan Coeytaux
//Daniel Fitzgerald

#ifndef GRID_H
#define GRID_H

#include "Node.h"
#include "Position.h"
using namespace std;

class Grid {
private:
	int height, length;
	Node** field;
public:
	Grid();
	void setSize(int newSize);
	int getHeight(){return height;}
	int getLength(){return length;}
	void setElement(Position p, Node* element);	//get's the "occupant" of the given grid cell
	Node* getElement(Position p);
	void print();
	Position getUnoccupiedPosition(int minCol, int maxCol);
	Position getUnoccupiedPosition(int col);
};

#endif
