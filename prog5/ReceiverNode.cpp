//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "ReceiverNode.h"
#include "Node.h"
#include "Position.h"
#include "SourceNode.h"
#include "Info.h"


ReceiverNode::ReceiverNode(unsigned int newID, unsigned int nSources):
	Node(newID, 'R')	//call constructor from superclass Node
{
	placeRandomly(field.getLength()-1);
	infoList = new Info [nSources];
}


//for printing source nodes
ostream& operator<<(ostream& os, const ReceiverNode& rcvrNode){
	os<<"RECEIVER NODE: "<<(Node)rcvrNode;
	return os;	
}

bool ReceiverNode::update(){ //updates Node, returns if Node is empty
	if (DEBUG) cout<<"\tReceiver "<<ID+1<<" updating..."<<endl;
	bool stillUpdating=false;	//flag to see if we updated ourselves or know we will again
	
	stillUpdating|=checkEvents();
	
	//receivers don't need packet queues - they don't transmit anything.
	//stillUpdating|=checkPacketQueues();
	
	return stillUpdating;

} //end update function

void ReceiverNode::receivePacket(Packet* packetPtr){
	cout<<"\tReceiver Node "<<this<<" got packet "<<packetPtr<<endl;
	Node* intendedRecipient = packetPtr->popNextNodeOnRout();	//pop the next node off the packet's source routing queue
	if (intendedRecipient != this){
		cout<<"ERROR: Packet was not sent to correct node! Packet "<<packetPtr<<" sent to "<<this<<" instead of "<<intendedRecipient<<endl;
	}
	Node* nextNodePtr=packetPtr->getNextNodeOnRout();	//peek (but don't pop) the next node on this pointer's journey, if there is one (which there shouldn't be!)
	if (!nextNodePtr){
		if(DEBUG) cout<<"\t\tReceived packet "<<packetPtr<<" at final destination "<<this<<endl;
		
		SourceNode* packetSrc = packetPtr->getOriginalSource();

		//add the packet to stats
		packetPtr->setReceivedTime(simTime);
		infoList[packetSrc->getID()].addPacket(packetPtr->getResponseTime());
	}else{
		cout<<"ERROR: Receiver Node "<<this<<" received a packet that still has nodes on it's routing list: "<<packetPtr<<endl;
	}
}
