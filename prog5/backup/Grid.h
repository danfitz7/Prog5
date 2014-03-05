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
	Node** field;		//represent the 2D feld as a 1D array of occupants (Nodes)
public:
	Grid();
	void setSize(int newSize);					//set the length and height such that the main grid is a square of the given size but has an additional column at the left for senders and at the right for receivers
	int getHeight(){return height;}				//vertical height of the field
	int getLength(){return length;}				//horizontal length of the field
	void setElement(Position p, Node* element);	//set the occupant at the given position
	Node* getElement(Position p);				//get the occupant (Node*) at the given position
	void print();								//print the whole field for visualization
	Position getUnoccupiedPosition(int minCol, int maxCol);	//returns a random unoccupied position with column c where minCol<c<=maxCol
	Position getUnoccupiedPosition(int col);				//returns a random unoccupied position in the given column
};

#endif
