//Ethan Coeytaux
//Daniel Fitzgerald

#ifndef GRID_H
#define GRID_H

#include "Node.h"
#include "Position.h"
using namespace std;

class Grid {
private:
	int size;
	Node** field;
public:
	Grid();
	void setSize(int newSize);
	int getSize() { return size; }
	void setElement(Position p, Node* element);	//get's the "occupant" of the given grid cell
	Node* getElement(Position p);
	void print();
};

#endif
