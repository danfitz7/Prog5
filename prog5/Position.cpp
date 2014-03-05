//Daniel Fitzgerald

#include <cmath>
#include "prog5.h"
#include "Position.h"

//default constructor - should never be used without subsequently changing the position, as nodes do when they assigne themselves random positions on the field.
Position::Position():
	x(-1),	//set both to -1 so if a Position is ever constructed but not later set we will get errors as we should
	y(-1)
{}

//constructor for normal XY 2D position
Position::Position(int X, int Y):
	x(X),
	y(Y)
{}

//constructor if given position in terms of field array index
Position::Position(int index) 
{
	int length=field.getLength();
	x=index%length;
	y=index/length;
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

