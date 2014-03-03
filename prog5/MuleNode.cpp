//Daniel Fitzgerald

#include "prog5.h"
#include <iostream>
#include "MuleNode.h"
#include "Node.h"
#include "Position.h"


MuleNode::MuleNode(unsigned int  newID):
	Node(newID),	//call constructor from superclass Node
	dir((Direction)(newID%4))
{
//TODO: init position so it's in a random unoccupied field space

}

void MuleNode::hop(){
	cout<<"\tMULE HOPPING"<<endl;
	//TODO: hopping logic here
}
