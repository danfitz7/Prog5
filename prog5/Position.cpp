//Daniel Fitzgerald

#include <cmath>

#include "prog5.h"
#include "Position.h"

Position::Position():
	x(-1),	//set both to -1 so if a Position is ever constructed but not later set we will get errors as we should
	y(-1)
{}

/*
Position::Position(int X, int Y):
	x(X),
	y(Y)
{}

double Position::distanceFrom(Position other){
	int xdiff=x-other.x;
	int ydiff=y=other.y;
	xdiff*=xdiff;
	ydiff*=ydiff;
	return sqrt(xdiff+ydiff);
}

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
*/
