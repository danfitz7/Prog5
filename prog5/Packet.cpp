//Ethan Coeytaux
//Daniel Fitzgerald

#include <iostream>
#include "Packet.h"
#include "SourceNode.h"
using namespace std;

ostream& operator<<(ostream& os, const SIZE& size){
	switch(size){
		case SMALL:
			os<<"SMALL";
			break;
		case MEDIUM:
			os<<"MEDIUM";
			break;
		case LARGE:
			os<<"LARGE";
			break;
		default:
			os<<"ERROR: bad size: "<<(int)size;
	}
	return os;
}

Packet::Packet(unsigned int newID, SIZE size, int sent_time, SourceNode* SOURCEPTR, LinkedList<Node*> ROUTQ):
	ID(newID),
	size(size),
	routQueue(ROUTQ),
	originNodePtr(SOURCEPTR),
	sentTime(sent_time),
	receivedTime(0)
{}

//packet constructor
Packet::Packet(LinkedList<Node*> ROUT, int newID, int time):
	ID(newID),
	size(SMALL),  //size always 1
	routQueue(ROUT),
	sentTime(time)
{}

//overload the stream output operator so we can easily print packets.
ostream& operator<<(ostream& os, const Packet& packet){
	os<< "Packet " << packet.ID << endl;
	os<<"\tsent time: "<< packet.sentTime<<endl;
	return os;
}

//overload the stream output operator so we can easily print packets pointers.
ostream& operator<<(ostream& os, const Packet* const packetPtr){
	if (packetPtr){
		os << "PktPtr: {"<<*packetPtr<<"}";
	}else{
		os<<"UNINITIALIZED PACKET";
	}
	return os;
}
