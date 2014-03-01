//Ethan Coeytaux
//Daniel Fitzgerald

#ifndef GRID_H
#define GRID_H

#include "Node.h"

using namespace std;

class Grid {
private:
	int size;
	Node** field;
public:
	Grid();
	void setSize(int newSize);
	int getSize() { return size; }
	void setElement(int row, int col, Node* element);
	Node* getElement(int row, int col);
	void print();
};

#endif
