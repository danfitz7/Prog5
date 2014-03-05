//Daniel Fitzgerald

#ifndef POSITION_H
#define POSITION_H

//direction of travel on the field (used by MuleNodes)
enum Direction {EAST=0, SOUTH=1, WEST=2, NORTH=3};

//defines a 2D position on the field, and converts between 2D coordinates and the index of the 1D array that is the internal implementation of the field.
class Position{
	friend ostream& operator<<(ostream& os, const Position& p){
		os<<'('<<p.x<<','<<p.y<<')';
		return os;
	}
	
	private:
		int x;
		int y;
	public:
		Position();
		Position(int X, int Y);
		Position(int pos);
		
		double distanceFrom(Position other);
		Position neighborOn(Direction d);
		
		void setXY(int newX, int newY){x=newX; y=newY;}
		void setPosition(Position p){x=p.x; y=p.y;}
		
		int getX(){return x;}
		int getY(){return y;}
};

#endif
