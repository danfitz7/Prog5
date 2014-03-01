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
};

#endif
