//Ethan Coeytaux
//Daniel Fitzgerald

#ifndef NODE_H
#define NODE_H

#include "Packet.h"
#include "Event.h"
#include "Position.h"

class Node {
	friend ostream& operator<<(ostream& os, const Node& node);	//make the stream printing function a friend so it has access to private vars
	friend ostream& operator<<(ostream& os, const Node* node);	//make the stream printing function a friend so it has access to private vars

protected:
	int ID;
	Position pos;
	LinkedList<Event> eventList; 	  //sorted event queue
	LinkedList<Packet*>* packetQueues; //Array of queues of packets to rout to their destinations (three queues in this array: small medium and large)
	unsigned int currentLength;
	unsigned int longestQueueLength; //longest ever length of Node's queue
	
	//updating
	void addEvent(Event newEvent);			//other node's can add events to our event list
	void receivePacket(Packet*);				//we can add packets to our packet list
	void finishPacket(Packet* packetPtr);	//what we do with a packet when we receive it and it has nowhere more to go
	void processPacket(Packet*);			//send a packet that still has some source rout nodes on it's queue
	void processEvent(Event event);			//process an event
	bool checkEvents();						//check if there's any more events to do right now
	bool checkPacketQueues();				//check if there's any backlog of packets to process
	bool busy;								//is this node currently busy transmitting a packet
	char type;								//'S', 'M', or 'R' for Source/Senders, Mules, and Receivers (used for debug printing)
	
	//misc helper
	void place(Position p);
	void placeRandomly(unsigned int minCol, unsigned int maxCol);		//place this node randomly on the field in a column such that minCol<=col<maxCol
	void placeRandomly(unsigned int row);
	unsigned int calcPropagationTimeTo(Node* otherNode);
	
public:
	Node(unsigned int newID, char newType); //constructor
	void print();
	char getType() const {return type;}	//gets the type of the node
	int getID() { return ID; }
	int getLongestQueueLength() { return longestQueueLength; } //returns max Node length
	
	//int getPropTime() { return propTime; } //returns propTime
	//int getTranTime() { return tranTime; } //returns tranTime
		
	Position getPosition() { return pos; }

	//MAIN UPDATE FUNCTION FOR ALL NODES
	bool update(); 
};

//overload so we can cout<< nodes
//ostream& operator<<(ostream& os, const Node& node);

#endif
