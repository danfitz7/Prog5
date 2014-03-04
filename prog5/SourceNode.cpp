//Daniel Fitzgerald
//Ethan Coeytaux

#include "prog5.h"
#include <iostream>
#include "SourceNode.h"
#include "Node.h"
#include "Position.h"

extern unsigned int simTime;

SourceNode::SourceNode(unsigned int newID, unsigned int arrival_time, unsigned int N_PACKETS, SIZE pkt_size, Node** SourceRoutArray, unsigned int routLength)://, LinkedList<Node*>  packetRoutingQueue
	Node(newID, 'S'),	//call constructor from superclass Node
	arrivalTime(arrival_time),
	nPackets(N_PACKETS),
	pktSize(pkt_size),
	SR(new Node*[routLength]),
	SR_length(routLength)
{
	//copy the SourceRoutArray
	for (int srIndex = routLength-1;srIndex>=0;srIndex--){
		SR[srIndex]=SourceRoutArray[srIndex];
	}
	SR[0]=this;	//the last elt should be a pointer to the original sender (us), but we obviously can't have been initialized yet because this is our constructor, so make the last elt our pointer to complete the list

	placeRandomly(0);
}

bool SourceNode::update(){
	if (DEBUG)cout<<"\tSource Node "<<this<<" updating..."<<endl;
	
	bool stillUpdating=false;
	
	//send packets if we aren't busy
	if (nPackets>0){//if we still have packets left to send
		if (!busy){	//if we're not already transmitting a packet
			sendNextPacket();
		}
	}
	
	//process events and packets like a normal node (although no one should be sending us packets)
	stillUpdating|=checkEvents();
	stillUpdating|=checkPacketQueues();
	
	return stillUpdating;
}

//start transmitting the next packet
unsigned int SourceNode::nextPacketID=0;
void SourceNode::sendNextPacket(){
	if (simTime>=arrivalTime){	//make sure we don't start sending packets before we arrive on the scene
		if (DEBUG) cout << "\t\tSource "<<ID+1<< " making new packet "<<nextPacketID<<" to "<<SR[1]<<" at time "<<simTime<<"..."<<endl;

		nPackets--;	//one less left to send
		
		Packet* newPacketPtr = new Packet(nextPacketID, pktSize, simTime, /*this,*/ SR, SR_length/* *Q*/);
		//if (DEBUG) cout << "\t\t\tMade packet "<<*newPacketPtr<<endl;
		//if (DEBUG) cout<< "\t\t\tNext node should have been "<<SR[0]<<endl;
		Event newEvent = Event(simTime+newPacketPtr->getTransTime(), newPacketPtr, TRANSMITTED);
		//if(DEBUG) cout<<"\t\t\tMade new event "<<newEvent<<endl;
		addEvent(newEvent);	//start processing this packet. next time we deal with it it will be transmitted
		if (DEBUG) cout << "\t\tAdded event to my own list: "<<newEvent<<endl;
		
		nextPacketID++;
	}
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
