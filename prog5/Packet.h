//Ethan Coeytaux
//Daniel Fitzgerald

#ifndef PACKET_H
#define PACKET_H

#include <iostream>
using namespace std;

//foreward declare class Node
class Node;//#include "Node.h"
#include "LinkedList.h"

class Packet {
private:
	int size; 		//size of packet (always 1)
	int ID; 		//ID of packet
	//Node* senderPtr;//sender node that sent packet
	LinkedList<Node*> routQueue;	//list of the nodes in this packets rout - these are popped off as as each node passes on the packet
	int sentTime;	//time atwhich the original sender first started processing this packet
	int receivedTime;//time atwhich the eventual final received received the packet
public:
	Packet(LinkedList<Node*> rout, int newID, int time); //constructor
	int getID() { return ID; } 							//returns ID
	LinkedList<Node*> getRout() { return routQueue; } 	//returns routQueue
	int getSentTime() { return sentTime; } 				//returns arrivalTime
	int getReceivedTime() { return receivedTime; } 		//returns arrivalTime
	int print(int time); 								//prints packet info
};


//overload so we can cout packets
ostream& operator<<(ostream& os, const Packet& packet);

#endif
