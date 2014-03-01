//Ethan Coeytaux
//Daniel Fitzgerald

#ifndef NODE_H
#define NODE_H

#include "Packet.h"
#include "Position.h"

class Node {
	friend ostream& operator<<(ostream& os, const Node& node);	//make the stream printing function a friend so it has access to private vars
	friend ostream& operator<<(ostream& os, const Node* node);	//make the stream printing function a friend so it has access to private vars
private:
	int ID;
	int internalTime;
	Position pos;
	LinkedList<Packet*>* packetQueues; 	//Array of queues of packets to rout to their destinations (three queues in this array: small medium and large)
	
	int tranTime;
	int propTime;
		
	int longestQueueLength; //longest ever length of Node's queue
	
	
public:
	Node(unsigned int newID); //constructor
	
	Position getPos() { return pos; }
	int getID() { return ID; }
	
	int getPropTime() { return propTime; } //returns propTime
	int getTranTime() { return tranTime; } //returns tranTime
	
	void placeRandomly(unsigned int minCol, unsigned int maxCol);		//place this node randomly on the field in a column such that minCol<=col<maxCol
	
	//get/set position	
	Position getPosition() { return pos; }
	//void setposition(Position p) { pos=p; }	//we don;t want to ever set a Node's position, because we should always make sure the field reflects the node's new position. 
	
	int getLongestQueueLength() { return longestQueueLength; } //returns max Node length
		
	void receivePacket(Packet* newPacket);	
		
	bool update(int time, int *packetID); //updates Node with time
};

//overload so we can cout<< nodes
//ostream& operator<<(ostream& os, const Node& node);

#endif
