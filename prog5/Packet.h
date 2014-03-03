//Ethan Coeytaux
//Daniel Fitzgerald

#ifndef PACKET_H
#define PACKET_H

#include <iostream>
using namespace std;

//foreward declare class Node
class Node;			//#include "Node.h"
class SourceNode; //#include "SourceNode.h"
//#include "Node.h"
#include "LinkedList.h"


//size of a packet. NOTE: the testing data gives this as {1,2,3}, but it is immediately converted to {0,1,2}
enum SIZE {SMALL=0, MEDIUM=1, LARGE=2};
ostream& operator<<(ostream& os, const SIZE& size);

class Packet {
	friend ostream& operator<<(ostream& os, const Packet& packet);
	friend ostream& operator<<(ostream& os, const Packet* const packet);
private:
	unsigned int ID; 				//ID of packet
	SIZE size; 						//size of packet
	LinkedList<Node*> routQueue;	//queue of the nodes in this packets rout - these are popped off as as each node passes on the packet
	SourceNode* originNodePtr;		//the original SourceNode of this packet
	const unsigned int sentTime;	//time atwhich the original sender first started processing this packet
	unsigned int receivedTime;		//time atwhich the eventual final received received the packet
public:
	Packet(unsigned int newID, SIZE size, int sent_time, SourceNode* sourcePtr, LinkedList<Node*> routQueue);
	Packet(LinkedList<Node*> rout, int newID, int time); //constructor
	unsigned int getID() { return ID; } 							//returns ID
	Node* popNextNodeOnRout() { return routQueue.pop(); }//pops the next node* off the rout queue and returns it
	SIZE getSize(){return size;}						//returns the size of the packet
	unsigned int getSentTime() { return sentTime; } 				//returns arrivalTime
	unsigned int getReceivedTime() { return receivedTime; } 		//returns arrivalTime
};


//overload so we can cout packets
//ostream& operator<<(ostream& os, const Packet& packet);

#endif
