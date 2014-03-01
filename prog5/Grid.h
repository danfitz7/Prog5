//Ethan Coeytaux
//Daniel Fitzgerald

#ifndef GRID_H
#define GRID_H

#include "Node.h"

using namespace std;

class Grid {
private:
	int height;
	int width;
	int size;
	Node** field;
public:
	Grid(int newSieze);
	void addSender(Node*);
	void addMule(Node*);
	void addReceiver(Node*);
	void moveNodes();
	void print();
};

#endif
