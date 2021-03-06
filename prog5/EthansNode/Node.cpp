//Ethan Coeytaux
//Daniel Fitzgerald

#include <math.h>
#include <iostream>
#include "Packet.h"
#include "Position.h"
#include "Node.h"
#include "prog5.h"

using namespace std;

//constructor
Node::Node(unsigned int  newID):
	ID(newID),										//position of his node on the field
	packetQueues(new LinkedList<Packet*>[3]),	//small, medium, and large packet queues in an array of queues
	tranTime(0),
	propTime(0)
{}

//add this packet to one of our queues
void Node::receivePacket(Packet* newPacket){
	packetQueues[newPacket->getSize()].insert(newPacket);
	longestQueueLength++;
}	

//places this node in a random unoccupied position on the global field such that the column, col, of this node's position is minCol<=col<maxCol
void Node::placeRandomly(unsigned int minCol, unsigned int maxCol){
	int row = rand() % field.getSize();
	int col = (rand() % maxCol) + minCol;
	while (field.getElement(row, col))
	{
		row = rand() % field.getSize();
		col = (rand() % maxCol) + minCol;
	}
	field.setElement(row, col, this);
	pos.setXY(row, col);
}

bool Node::update(int time, int *packetID){ //updates Node, returns if Node is empty
	bool packetToProcess = false;
	Packet* sPacket;
	if (packetQueues[0].firstElement())
	{
		packetToProcess = true;
		sPacket = packetQueues[0].pop();
	}
	else if (packetQueues[1].firstElement())
	{
		packetToProcess = true;
		sPacket = packetQueues[1].pop();
	}
	else if (packetQueues[2].firstElement())
	{
		packetToProcess = true;
		sPacket = packetQueues[2].pop();
	}
	if ((packetToProcess) && (internalTime != time))
	{
		internalTime++;
		if (propTime) propTime--;
		else if (tranTime) tranTime--;
		else
		{
			int currentQueue = sPacket->getSize();
			Node* nextNode = sPacket->routQueue.pop();
			if (nextNode) nextNode->receivePacket(sPacket);
			sPacket = packetQueues[currentQueue].pop();
			while ((!sPacket) && (currentQueue < 3))
			{
				sPacket = packetQueues[currentQueue].pop();
				currentQueue++;
			}
			if (sPacket)
			{
				tranTime = sPacket->getSize();
				propTime = ceil(log2(sqrt(pow(pos.getX() - sPacket->routQueue.firstElement()->getPos().getX(), 2) + pow(pos.getY() - sPacket->routQueue.firstElement()->getPos().getY(), 2)))) - 1;
			}
		}
		return true;
	}
	else return false;
} //end update function

//overload the steam out operator so we can cout<<Node
ostream& operator<<(ostream& os, const Node& node){
	os<<"Node "<<node.ID;
	return os;
}

//overload the steam out operator so we can cout<<Node*
ostream& operator<<(ostream& os, const Node* nodePtr){
	os<<"NodePtr "<<(nodePtr->ID+1);	//add one to the ID to make it 1-based again as it was in the input data
	return os;
}

