//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "SourceNode.h"
#include "Node.h"
#include "Position.h"

extern unsigned int simTime;
extern unsigned int totalEvents;

SourceNode::SourceNode(unsigned int newID, unsigned int arrival_time, unsigned int N_PACKETS, SIZE pkt_size, Node** SourceRoutArray, unsigned int routLength)://, LinkedList<Node*>  packetRoutingQueue
	Node(newID, 'S'),	//call constructor from superclass Node
	arrivalTime(arrival_time),
	nPackets(N_PACKETS),
	pktSize(pkt_size),
	SR(new Node*[routLength]),
	SR_length(routLength),
	isInSim(false)
{
	//copy the SourceRoutArray
	for (int srIndex = routLength-1;srIndex>=0;srIndex--){
		SR[srIndex]=SourceRoutArray[srIndex];
	}
	SR[0]=this;	//the last elt should be a pointer to the original sender (us), but we obviously can't have been initialized yet because this is our constructor, so make the last elt our pointer to complete the list

	placeRandomly(0);
}

bool SourceNode::update(){
	//if we've entered the simulation and haven't left it yet

	if (isInSim){
		bool stillUpdating=false;
		if (DEBUG)cout<<"\tSource Node "<<this<<" updating..."<<endl;
		
		//still something left to do - check it
		if ((eventList.isNotEmpty()) || (packetQueues[pktSize].isNotEmpty())){
			//process events and packets like a normal node (although no one should be sending us packets)
			stillUpdating|=checkEvents();
			stillUpdating|=checkPacketQueues();	
		}else{//if there's nothing left to do
			if (nPackets>0){//if we still have packets left to send
				if (!busy){	//if we're not already transmitting a packet
					sendNextPacket();//send packets if we aren't busy
					stillUpdating=true;
				}
			//no more packets to send, events to process, or packets in queue - exit	
			}else{
				cout<<"Source "<<ID+1<<" has finished transmitting all it's packets and has left the simulation at time "<<simTime<<"."<<endl;
				totalEvents++;
				isInSim=false;
			}
		}
		return stillUpdating;
		
	//not in simulation - has either not arrived yet or has left
	}else{
		//enter the simulation if it looks like we haven't sent our packets yet
		if (nPackets>0){
			if(simTime>=arrivalTime){	//make sure we don't start sending packets before we arrive on the scene
				cout<<"Source "<<ID+1<<" Entered the simulation and started sending packets at time "<<simTime<<"."<<endl;
				totalEvents++;
				isInSim=true;
			}
			return true;	//we haven't arrived yet, but we still want to be updated
		}else{
			return false;	//we've exited - nothing to update
		}
	}
}

//start transmitting the next packet
unsigned int SourceNode::nextPacketID=0;	//init static var
void SourceNode::sendNextPacket(){
	
	if (DEBUG) cout << "\t\tSource "<<ID+1<< " making new packet "<<nextPacketID<<" to "<<SR[1]<<" at time "<<simTime<<"..."<<endl;

	Packet* newPacketPtr = new Packet(nextPacketID, pktSize, simTime, this, SR, SR_length/* *Q*/);
	//if (DEBUG) cout << "\t\t\tMade packet "<<*newPacketPtr<<endl;
	//if (DEBUG) cout<< "\t\t\tNext node should have been "<<SR[0]<<endl;
	Event newEvent = Event(simTime+newPacketPtr->getTransTime(), newPacketPtr, TRANSMITTED);
	//if(DEBUG) cout<<"\t\t\tMade new event "<<newEvent<<endl;
	addEvent(newEvent);	//effectively send a packet to ourselves. This event will be processed in the future.
	if (DEBUG) cout << "\t\tAdded event to my own list: "<<newEvent<<endl;
	
	nextPacketID++;
	busy=true;	//we're transmitting - don't do anything else until the transmission complete event is processed (which should make us not busy again)
	nPackets--;	//one less left to send
}

//for printing source nodes
ostream& operator<<(ostream& os, const SourceNode& srcNode){
	os<<"SOURCE NODE: "<<(Node)srcNode<<" arrival= "<<srcNode.arrivalTime<<" nPackets="<<srcNode.nPackets<<" pksSize="<<srcNode.pktSize<<" SR={";
	for (unsigned int nodeIndex=0;nodeIndex< srcNode.SR_length; nodeIndex++){
		os<<srcNode.SR[nodeIndex]<<", ";
	}
	os<<"}";
	return os;	
}
