//Ethan Coeytaux
//Daniel Fitzgerald

#include <iostream>
#include "Packet.h"
#include "Node.h"

using namespace std;

//constructor
Node::Node(unsigned int  newID):
	ID(newID),
	packetQueues(new LinkedList<Packet*>[3]),	//small, medium, and large packet queues
	sender(true),
	receiver(false),
	row(0),
	col(0),
	direction(0)
{}
	

//constructor
Node::Node(int newID, bool isSender, bool isReceiver, int newRow, int newCol, int newDirection):
	ID(newID),
	packetQueues(new LinkedList<Packet*>[3]),	//small, medium, and large packet queues
	sender(isSender),
	receiver(isReceiver),
	row(newRow),
	col(newCol),
	direction(newDirection)
{}
	
void Node::receivePacket(Packet* newPacket){
	packetQueues[newPacket->getSize()].insert(newPacket);
}	
/*	
void Node::addPacket(Packet *newPacket) //adds Packet to Node
{
	int lengthOfNode = 1; //used to determine length of Node
	if (sPacket) lengthOfNode = sPacket->addPacket(newPacket) + 1; //if Node contains a packet, adds Packet to the packet list
	else sPacket = newPacket; //if Node is empty
	if (lengthOfNode > maxNode) maxNode = lengthOfNode; //updates maxNode length
} //end addPacket function
*/
bool Node::update(int time, int *packetID, int *S1average, int *S2average) //updates Node, returns if Node is empty
{
	//if (sPacket) //is Node is not empty
	//{
		/*if (propTime > 0) propTime--; //decreases propTime
		else if (tranTime > 0) tranTime--; //decreases tranTime
		else //if both propTime and tranTime are complete
		{
			propTime = propTimeSet - 1; //resets propTime
			tranTime = tranTimeSet; //resets tranTime
			cout << "At time " << time << " packet " << sPacket->getID() << " completed from " << (sender ? 'S' : 'M') << ID;
			if (!nextNode) cout << " and reached R1!"; //if Node is last in line
			cout << endl;
			if (sender) //if Node is S1 or S2
				if (count) //if sender still has packets to send
				{
					sPacket->addPacket(new Packet(ID, *packetID, time)); //sends new packet
					(*packetID)++;
					count--;
				}
			if (nextNode) nextNode->addPacket(new Packet(sPacket->getSender(), sPacket->getID(), sPacket->getArrivalTime())); //if Node is not last in line
			else //if Node is last in line
			{
				int responseTime = sPacket->print(time); //prints Packet data
				sPacket->getSender() == 1 ? *S1average += responseTime : *S2average += responseTime; //used to calculate average response time
			}
			sPacket = sPacket->nextPacket; //starts processing next packet
		} //end else statement
		return true;
	}
	else return false;*/
	//} return false;
} //end update function

//overload the steam out operator so we can cout<<Node
ostream& operator<<(ostream& os, const Node& node){
	os<<"Node "<</*node.getID()<<*/endl;
}
