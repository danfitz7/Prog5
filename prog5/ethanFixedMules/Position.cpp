//Daniel Fitzgerald
//Ethan Coeytaux

#include <cmath>

#include "prog5.h"
#include "Position.h"

Position::Position():
	x(-1),	//set both to -1 so if a Position is ever constructed but not later set we will get errors as we should
	y(-1)
{}


Position::Position(int X, int Y):
	x(X),
	y(Y)
{}

Position::Position(int pos) //constructor if given position in terms of field position
{
	int length=field.getLength();
	x=pos%length;
	y=pos/length;
}

//euclidean distance to the given position
double Position::distanceFrom(Position other){
	int xdiff = x-other.x;
	int ydiff = y-other.y;
	xdiff*=xdiff;
	ydiff*=ydiff;
	return sqrt(xdiff+ydiff);
}

//gets the immediately neighbouring position in the given direction
Position Position::neighborOn(Direction d){
	int neighborX=x;
	int neighborY=y;
	switch(d){
		case NORTH:
			neighborY++;
			break;
		case EAST:
			neighborX++;
			break;
		case SOUTH:
			neighborY--;
			break;
		case WEST:
			neighborX--;
			break;
		default:
			break;
	}
	return Position(neighborX, neighborY);
}

