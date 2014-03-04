//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "ReceiverNode.h"
#include "Node.h"
#include "Position.h"
#include "Info.h"


ReceiverNode::ReceiverNode(unsigned int newID, unsigned int nSources):
	Node(newID)	//call constructor from superclass Node
{
//TODO: receiver stuff here
	infoList = new Info [nSources];
}


//for printing source nodes
ostream& operator<<(ostream& os, const ReceiverNode& rcvrNode){
	os<<"RECEIVER NODE: "<<(Node)rcvrNode;
	return os;	
}

void ReceiverNode::finishPacket(Packet* packetPtr){
	cout<<"Receiver Node "<<this<<" got packet "<<packetPtr<<endl;
}
