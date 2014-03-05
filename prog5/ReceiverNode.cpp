//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "ReceiverNode.h"
#include "Node.h"
#include "Position.h"
#include "SourceNode.h"
#include "Info.h"

//constructor
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

//processes the given event
void ReceiverNode::processEvent(Event event){
	if (DEBUG) cout<<"\t\tReceiver "<<this<<" processing event " <<event<<"..."<<endl;
	EVENT_TYPE type = event.getType();
	Packet* thePacket=event.getPacket();
	switch(type){
		case ARRIVAL:	//a new packet has arrived - add it to our queue
			if (DEBUG) cout<<"\t\tPacket "<<thePacket->getID()<<" arrived at receiver - processing statistics."<<endl;
			receivePacket(thePacket);
			break;
		case TRANSMITTED:	//a packet finished transmitting within this node - send it out
			if (DEBUG) cout<<"ERROR: Receiver Transmitted a packet "<<thePacket->getID()<<endl;
			busy=false;	//we finished processing a packet! yay!
			break;
		default:
			cout<<"ERROR: BAD EVENT TYPE: "<<type<<endl;
			break;
	}
}

//override Node update function to skip packet queue processing and call the overridden checkEvents() function
bool ReceiverNode::update(){ //updates Node, returns if Node is empty
	if (DEBUG) cout<<"\tReceiver "<<this<<" updating..."<<endl;
	bool stillUpdating=false;	//flag to see if we updated ourselves or know we will again
	
	stillUpdating|=checkEvents();
	
	//receivers don't need packet queues - they don't transmit anything.
	//stillUpdating|=checkPacketQueues();
	
	return stillUpdating;

} //end update function

//receive the packet and process statistics on its travel
void ReceiverNode::receivePacket(Packet* packetPtr){
	cout<<"\tReceiver Node "<<this<<" got packet "<<packetPtr<<endl;
	
	//pop the next node off the packet's source routing queue
	Node* intendedRecipient = packetPtr->popNextNodeOnRout();	
	
	//make sure we are the intended recipient
	if (intendedRecipient != this){
		cout<<"ERROR: Packet was not sent to correct node! Packet "<<packetPtr<<" sent to "<<this<<" instead of "<<intendedRecipient<<endl;
	}
	
	//if there is nothing left on the packet's routing queue once we pop outselves off (as expected)
	if (!(packetPtr->hasMoreNodesOnRout())){
		if(DEBUG) cout<<"\t\tReceived packet "<<packetPtr<<" at final destination "<<this<<endl;
		
	//a receiver node received a packet which had additional nodes on it's routing queue
	//NOTE: this does occur in the test data. The receiver doesn't do anything with the packet, it justs 
	}else{
		cout<<"WARNING: Receiver Node "<<this<<" received a packet that still had nodes on it's routing list: "<<packetPtr<<endl;
	}
	
	//get the SourceNode that generated the packet
	SourceNode* packetSrc = packetPtr->getOriginalSource();

	//add the packet to the appropriate information stats
	packetPtr->setReceivedTime(simTime);
	infoList[packetSrc->getID()].addPacket(packetPtr->getResponseTime());
}
