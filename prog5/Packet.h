//Ethan Coeytaux
//Daniel Fitzgerald

#ifndef PACKET_H
#define PACKET_H

#include "Node.h"

class Packet {
private:
	int size; 		//size of packet (always 1)
	int ID; 		//ID of packet
	Node* senderPtr;//sender node that sent packet
	int sentTime;	//time atwhich the original sender first started processing this packet
	int receivedTime;//time atwhich the eventual final received received the packet
public:
	Packet(Node* newSenderPtr, int newID, int time); //constructor
	int getID() { return ID; } 						//returns ID
	Node* getSender() { return senderPtr; } 		//returns sender
	int getSentTime() { return sentTime; } 			//returns arrivalTime
	int getReceivedTime() { return receivedTime; } 	//returns arrivalTime
	int print(int time); 							//prints packet info
};

#endif
