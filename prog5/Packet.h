//Daniel Fitzgerald
//Ethan Coeytaux

#ifndef PACKET_H
#define PACKET_H

#include "LinkedList.h"
#include <iostream>
using namespace std;

//forward declare class Node
class Node;		//#include "Node.h"
class SourceNode; //#include "SourceNode.h"

//size of a packet. NOTE: the testing data gives this as {1,2,3}, but it is immediately converted to {0,1,2} for internal use so we can index the priority queue arrays of Nodes with the size directly.
enum SIZE {SMALL=0, MEDIUM=1, LARGE=2};
ostream& operator<<(ostream& os, const SIZE& size);

class Packet {
	friend ostream& operator<<(ostream& os, Packet packet);
	friend ostream& operator<<(ostream& os, const Packet* const packet);
private:
	unsigned int ID; 				//ID of packet
	SIZE size; 						//size of packet
	LinkedList<Node*> routQueue;	//queue of the nodes in this packets rout - these are popped off as as each node passes on the packet
	SourceNode* originNodePtr;		//the original SourceNode of this packet
	const unsigned int sentTime;	//time atwhich the original sender first started processing this packet
	unsigned int receivedTime;		//time atwhich the eventual final receiver received the packet
public:

	Packet(unsigned int newID, SIZE size, int sent_time, SourceNode* SOURCEPTR, Node* sourceRoutArray[], unsigned int sourceRoutLength);
	
	unsigned int getID() { return ID; } 					//returns ID
	Node* popNextNodeOnRout() { return routQueue.pop(); }	//pops the next node* off the rout queue and returns it
	bool hasMoreNodesOnRout() {return routQueue.isNotEmpty();}//does the packet have more nodes on its rout queue?
	Node* getNextNodeOnRout() {return routQueue.peek();}	//returns (but does not pop) the first node* on the rout queue
	SIZE getSize(){return size;}							//returns the size of the packet
	unsigned int getTransTime(){return (unsigned int)size+1;}		//transmission time is equal to packet length (note, we subtracted one from packet sizes so we could index our priority queues with their size)
	unsigned int getSentTime() { return sentTime; } 				//returns arrivalTime
	unsigned int getReceivedTime() { return receivedTime; } 		//returns arrivalTime
	void setReceivedTime(unsigned int rTime){receivedTime=rTime;}	//set the tie this packet was received at it's final destination
	unsigned int getResponseTime(){return (receivedTime-sentTime);}	//get the response time NOTE: received time better be set and after sent time!
	SourceNode* getOriginalSource(){return originNodePtr;}			//get a pointer to the SourceNode that generated this packet
};


//overload so we can cout packets
//ostream& operator<<(ostream& os, const Packet& packet);

#endif
