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
	Position pos;
	LinkedList<Packet*>* packetQueues; 	//Array of queues of packets to rout to their destinations (three queues in this array: small medium and large)
	
	int tranTime;
	int propTime;
	
	unsigned int currentLength;
	unsigned int longestQueueLength; //longest ever length of Node's queue
	
	void placeRandomly(unsigned int minCol, unsigned int maxCol);		//place this node randomly on the field in a column such that minCol<=col<maxCol

public:
	Node(unsigned int newID); //constructor
	
	char getType() const {return 'N';}	//gets the type of the node
	
	int getID() { return ID; }
	
	int getPropTime() { return propTime; } //returns propTime
	int getTranTime() { return tranTime; } //returns tranTime
		
	Position getPosition() { return pos; }
	
	int getLongestQueueLength() { return longestQueueLength; } //returns max Node length
		
	void receivePacket(Packet* newPacket);	
		
	bool update(); //updates Node with time
};

//overload so we can cout<< nodes
//ostream& operator<<(ostream& os, const Node& node);

#endif
