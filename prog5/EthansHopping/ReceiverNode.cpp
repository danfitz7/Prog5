//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "ReceiverNode.h"
#include "Node.h"
#include "Position.h"


ReceiverNode::ReceiverNode(unsigned int newID):
	Node(newID, 'R')	//call constructor from superclass Node
{
//TODO: receiver stuff here
	placeRandomly(field.getSize() + 1, 1);
}


//for printing source nodes
ostream& operator<<(ostream& os, const ReceiverNode& rcvrNode){
	os<<"RECEIVER NODE: "<<(Node)rcvrNode;
	return os;	
}

void ReceiverNode::finishPacket(Packet* packetPtr){
	cout<<"Receiver Node "<<this<<" got packet "<<packetPtr<<endl;
}
