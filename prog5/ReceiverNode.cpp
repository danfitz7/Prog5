//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "ReceiverNode.h"
#include "Node.h"
#include "Position.h"


ReceiverNode::ReceiverNode(unsigned int newID):
	Node(newID)	//call constructor from superclass Node
{
//TODO: receiver stuff here

}


//for printing source nodes
ostream& operator<<(ostream& os, const ReceiverNode& rcvrNode){
	os<<"RECEIVER NODE: "<<(Node)rcvrNode;
	return os;	
}
