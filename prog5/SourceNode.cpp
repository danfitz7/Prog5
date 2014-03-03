//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "SourceNode.h"
#include "Node.h"
#include "Position.h"


SourceNode::SourceNode(unsigned int newID, unsigned int arrival_time, unsigned int N_PACKETS, SIZE pkt_size, Node** SourceRoutArray, unsigned int routLength)://, LinkedList<Node*>  packetRoutingQueue
	Node(newID),	//call constructor from superclass Node
	arrivalTime(arrival_time),
	nPackets(N_PACKETS),
	pktSize(pkt_size),
	SR(SourceRoutArray),
	SR_length(routLength)
{
	SR[SR_length-1]=this;	//the last eld should be a pointer to the original sender (us), but we obviously can't have been initialized yet because this is our constructor, so make the last elt our pointer to complete the list

//TODO: init position so it's in a random unoccupied field space

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
