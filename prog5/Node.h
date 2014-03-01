//Ethan Coeytaux
//Daniel Fitzgerald

#ifndef NODE_H
#define NODE_H

#include "Packet.h"

class Node {
private:
	int ID;
	int internalTime;
	Packet *sPacket; //first packet in Node
	int tranTime;
	int propTime;
	bool sender; //if Node is a sender (ie S1 or S2)
	bool receiver; //if Node is a sender (ie S1 or S2)
	int row; //row position of Node
	int col; //col position of Node
	int direction; //0 = North, 1 = East, 2 = South, 3 = West
	int maxNode; //longest ever length of Node
public:
	Node(int newID, bool isSender, bool isReceiver, int newRow, int newCol, int newDirection); //constructor
	int getPropTime() { return propTime; } //returns propTime
	int getTranTime() { return tranTime; } //returns tranTime
	int getID() { return ID; }
	int getRow() { return row; }
	void setRow(int newRow) { row = newRow; }
	int getCol() { return col; }
	void setCol(int newCol) { col = newCol; }
	int getDirection() { return direction; }
	void setDirection(int newDirection) { direction = newDirection; }
	int getNodeSize() { return maxNode; } //returns max Node length
	void addPacket(Packet *newPacket); //adds packet to Node
	bool update(int time, int *packetID, int *S1average, int *S2average); //updates Node with time
};

//overload so we can cout packets
ostream& operator<<(ostream& os, const Node& node);

#endif
