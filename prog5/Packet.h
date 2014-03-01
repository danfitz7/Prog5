//Ethan Coeytaux
//Daniel Fitzgerald

#ifndef PACKET_H
#define PACKET_H

#include <iostream>
using namespace std;

//foreward declare class Node
class Node;//#include "Node.h"
#include "LinkedList.h"

//size of a packet. NOTE: the testing data gives this as {1,2,3}, but it is immediately converted to {0,1,2}
enum SIZE {SMALL=0, MEDIUM=1, LARGE=2};

class Packet {
	friend ostream& operator<<(ostream& os, const Packet& packet);
private:
	unsigned int ID; 				//ID of packet
	SIZE size; 						//size of packet
	LinkedList<Node*> routQueue;	//queue of the nodes in this packets rout - these are popped off as as each node passes on the packet
	const unsigned int sentTime;	//time atwhich the original sender first started processing this packet
	unsigned int receivedTime;		//time atwhich the eventual final received received the packet
public:
	Packet(unsigned int newID, SIZE size, int arrival_time, LinkedList<Node*> routQueue);
	Packet(LinkedList<Node*> rout, int newID, int time); //constructor
	int getID() { return ID; } 							//returns ID
	LinkedList<Node*> getRout() { return routQueue; } 	//returns routQueue
	int getSize();										//returns the size of the packet
	int getSentTime() { return sentTime; } 				//returns arrivalTime
	int getReceivedTime() { return receivedTime; } 		//returns arrivalTime
	int print(int time); 								//prints packet info
};


//overload so we can cout packets
ostream& operator<<(ostream& os, const Packet& packet);

#endif
