//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "Packet.h"
#include "SourceNode.h"
using namespace std;

//print packet sizes for readability
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

Packet::Packet(unsigned int newID, SIZE size, int sent_time, SourceNode* SOURCEPTR, Node** sourceRoutArray, unsigned int sourceRoutLength):
	ID(newID),
	size(size),
	originNodePtr(SOURCEPTR),
	sentTime(sent_time),
	receivedTime(0)				//this should be set by the ReceiverNode when it finally receives the packet
{
	//if (DEBUG)cout<<"\t\t\tInitializing packet "<<ID<<"'s source rout queue ["<<sourceRoutLength<<"]..."<<endl;
	//make the packet's Routing Queue (just copy our array)
	routQueue = LinkedList<Node*>();
	for (int SRnodeIndex=sourceRoutLength-1;SRnodeIndex>=0;SRnodeIndex--){
		//if(DEBUG)cout<<"\t\t\t\tPushing Elt "<<SRnodeIndex<<endl;
		//cout<<"\t\t\t\t"<<sourceRoutArray[SRnodeIndex]<<endl;
		routQueue.push(sourceRoutArray[SRnodeIndex]);
	}
}

//overload the stream output operator so we can easily print packets.
ostream& operator<<(ostream& os, Packet packet){
	os<< "Packet{" << packet.ID << " from "<<packet.originNodePtr<<" sent at t="<<packet.sentTime<<" through rout "<<packet.routQueue<<"}";
	return os;
}

//overload the stream output operator so we can easily print packets pointers.
ostream& operator<<(ostream& os, const Packet* const packetPtr){
	if (packetPtr){
		os << "*"<<*packetPtr;
	}else{
		os<<"UNINITIALIZED PACKET";
	}
	return os;
}
