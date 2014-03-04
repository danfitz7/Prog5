//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "SourceNode.h"
#include "Node.h"
#include "Position.h"


SourceNode::SourceNode(unsigned int newID, unsigned int arrival_time, unsigned int N_PACKETS, SIZE pkt_size, Node** SourceRoutArray, unsigned int routLength)://, LinkedList<Node*>  packetRoutingQueue
	Node(newID, 'S'),	//call constructor from superclass Node
	arrivalTime(arrival_time),
	nPackets(N_PACKETS),
	pktSize(pkt_size),
	SR(SourceRoutArray),
	SR_length(routLength)
{
	SR[SR_length-1]=this;	//the last eld should be a pointer to the original sender (us), but we obviously can't have been initialized yet because this is our constructor, so make the last elt our pointer to complete the list

//TODO: init position so it's in a random unoccupied field space

}

bool SourceNode::update(){
	if (DEBUG)cout<<"\tSender"<<endl;
	
	bool stillUpdating = (Node*)this->update();	//Works like Java super (maybe?) - process events and packets like a normal node (although no one should be sending us packets)
	if (nPackets>0){//if we still have packets left to send
		if (!busy){	//if we're not already transmitting a packet
			sendNextPacket();
		}
	}
	return stillUpdating;
}

//start transmitting the next packet
unsigned int SourceNode::nextPacketID=0;
void SourceNode::sendNextPacket(){
	nPackets--;	//one less left to send
	
	//make the packet's Routing Queue (just copy our array)
	LinkedList<Node*> Q = LinkedList<Node*>();
	for (unsigned int SRnodeIndex=0;SRnodeIndex<SR_length;SRnodeIndex++){
		Q.push(SR[SRnodeIndex]);
	}

	Packet* newPacket = new Packet(nextPacketID, pktSize, simTime, this, Q);
	
	sendOutPacket(newPacket);
	
	nextPacketID++;
}

//for printing source nodes
ostream& operator<<(ostream& os, const SourceNode& srcNode){
	os<<"SOURCE NODE: "<<(Node)srcNode<<" arrival= "<<srcNode.arrivalTime<<" nPackets="<<srcNode.nPackets<<" pksSize="<<srcNode.pktSize<<" SR={";
	for (unsigned int nodeIndex=0;nodeIndex< srcNode.SR_length; nodeIndex++){
		os<<srcNode.SR[nodeIndex]<<", "; //
	}
	os<<"}";
	return os;	
}
