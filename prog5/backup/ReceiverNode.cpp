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
	Node(newID, 'R'),	//call constructor from superclass Node
	infoListLength(nSources)
{
	placeRandomly(field.getLength()-1);
	infoList = new Info [nSources];
	for (unsigned int i = 0; i < nSources; i++)
	{
		infoList[i].setSenderID(i + 1);
	}
}

//for printing source nodes
ostream& operator<<(ostream& os, const ReceiverNode& rcvrNode){
	os<<"RECEIVER NODE: "<<(Node)rcvrNode;
	return os;	
}

//receive the packet and process statistics on its travel
void ReceiverNode::receivePacket(Packet* packetPtr){
	if(DEBUG) cout<<"\t\t\tReceiver Node "<<this<<" got packet "<<packetPtr<<endl;
	
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
		if(DEBUG) cout<<"WARNING: Receiver Node "<<this<<" received a packet that still had nodes on it's routing list: "<<packetPtr<<endl;
	}
	
	//get the SourceNode that generated the packet
	SourceNode* packetSrc = packetPtr->getOriginalSource();

	//add the packet to the appropriate information stats
	packetPtr->setReceivedTime(simTime);
	infoList[packetSrc->getID()].addPacket(packetPtr->getResponseTime());
	delete(packetPtr);
}


void ReceiverNode::printInfo()
{
	cout << "\n\tFinal Statistics for R" << ID << endl;
	for (unsigned int i = 0; i < infoListLength; i++)
	{
		infoList[i].print();
	}
}
