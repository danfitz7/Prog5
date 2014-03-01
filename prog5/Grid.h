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
	Grid(int newSize);
	void addSender(Node*);
	void addMule(Node*);
	void addReceiver(Node*);
	void print();
};

#endif
