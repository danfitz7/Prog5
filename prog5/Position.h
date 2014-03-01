//Daniel Fitzgerald

#ifndef POSITION_H
#define POSITION_H


enum Direction {EAST=0, SOUTH=1, WEST=2, NORTH=3};

class Position{
	private:
		int x;
		int y;
	public:
		Position();
		Position(int X, int Y);
		double distanceFrom(Position other);
		Position neighborOn(Direction d);
		void setXY(int newX, int newY){x=newX; y=newY;}
		void setPosition(Position p){x=p.x; y=p.y;}
		int getX(){return x;}
		int getY(){return y;}
};

#endif
