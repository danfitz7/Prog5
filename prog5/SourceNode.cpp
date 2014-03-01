//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "SourceNode.h"
#include "Node.h"
#include "Position.h"


SourceNode::SourceNode(unsigned int newID, unsigned int arrival_time, unsigned int N_PACKETS, SIZE pkt_size, LinkedList<Node*>  packetRoutingQueue):
	Node(newID),	//call constructor from superclass Node
	arrivalTime(arrival_time),
	nPackets(N_PACKETS),
	pktSize(pkt_size),
	SR(packetRoutingQueue)
{
//TODO: init position so it's in a random unoccupied field space

}


//for printing source nodes
ostream& operator<<(ostream& os, const SourceNode& srcNode){
	os<<"SOURCE NODE: "<<(Node)srcNode<<" arrival= "<<srcNode.arrivalTime<<" nPackets="<<srcNode.nPackets<<" pksSize="<<srcNode.pktSize;//<<" SR={"<<srcNode.SR<<"}"
	return os;	
}
