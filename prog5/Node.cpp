//Ethan Coeytaux
//Daniel Fitzgerald

#include <iostream>
#include "Packet.h"
#include "Position.h"
#include "Node.h"

using namespace std;

//constructor
Node::Node(unsigned int  newID):
	ID(newID),									//unique ID of this node (NOTE: this *should* correspond to it's index in the master Node* array)
	pos(Position()),								//position of his node on the field
	packetQueues(new LinkedList<Packet*>[3])	//small, medium, and large packet queues in an array of queues
{}

//add this packet to one of our queues
void Node::receivePacket(Packet* newPacket){
	packetQueues[newPacket->getSize()].insert(newPacket);
	longestQueueLength++;
}	

//places this node in a random unoccupied position on the global field such that the column, col, of this node's position is minCol<=col<maxCol
void placeRandomly(unsigned int minCol, unsigned int maxCol){
	//TODO: fill this in
}

bool Node::update(int time, int *packetID, int *S1average, int *S2average){ //updates Node, returns if Node is empty
	//TODO: Update logic here
	
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
	return true;
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

