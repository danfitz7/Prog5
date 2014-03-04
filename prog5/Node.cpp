//Ethan Coeytaux
//Daniel Fitzgerald

//debug flag and global vars
#include "prog5.h"

#include <math.h>
#include <iostream>
#include "Packet.h"
#include "Position.h"
#include "Node.h"
#include "Event.h"

using namespace std;

#include "Grid.h"
extern unsigned int simTime;
extern Grid field;

//constructor
Node::Node(unsigned int  newID, char newType):
	ID(newID),									//unique ID of this node (NOTE: this *should* correspond to it's index in the master Node* array)
	pos(Position()),								//position of his node on the field
	eventList(LinkedList<Event>()),
	packetQueues(new LinkedList<Packet*>[3]),	//small, medium, and large packet queues in an array of queues
	tranTime(0),
	propTime(0),
	busy(false),
	type(newType)
{
	if(DEBUG)cout<<"\t\tNode "<<ID+1<<" initialized."<<endl;
}

void Node::place(Position p){
	if (!field.getElement(p)){
		field.setElement(p, this);
		pos.setPosition(p);
	}else{
		cout<<"ERROR: attempted to place node in occupied field position!"<<endl;
	}
}

//places this node in a random unoccupied position on the global field such that the column, col, of this node's position is minCol<=col<maxCol
void Node::placeRandomly(unsigned int minCol, unsigned int maxCol){
	Position p =field.getUnoccupiedPosition(minCol, maxCol);
	cout<<"\t\t\tPlacing node randomly at "<<p<<endl;
	place(p);
}

void Node::placeRandomly(unsigned int col){
	Position p =field.getUnoccupiedPosition(col);
	cout<<"\t\t\tPlacing node randomly at "<<p<<endl;
	place(p);
}

//add this event to the event queue, or deal with it if it's happening right now
void Node::addEvent(Event event){
	if (event.getTime() <= simTime){
		processEvent(event);
	}else{
		eventList.insert(event);
	}
}

//add this packet to one of our queues
void Node::addPacket(Packet* newPacket){
	packetQueues[newPacket->getSize()].insert(newPacket);
	currentLength++;
	if (currentLength>longestQueueLength){
		longestQueueLength=currentLength;
	}
}	

//if we are the end receiver of a packet
void Node::finishPacket(Packet* packetPtr){
	cout<<"ERROR: regular node "<<this<<" received packet ["<<packetPtr<<"] with no more nodes on rout!"<<endl; //reminds us to override this function for receiver nodes
}

//returns the time of propagation between this node and the given other node
unsigned int Node::calcPropagationTimeTo(Node* otherNode){
	return (int)ceil(log2(pos.distanceFrom(otherNode->pos))); //TODO: is this right?
}

//sends sends the given event out to it's next stop by adding an arrival event for the packet to that node
void Node::sendOutPacket(Packet* packetPtr){
	Node* nextNodePtr=packetPtr->popNextNodeOnRout();	//pop the next node off the packet's source routing queue
	if (nextNodePtr){
		unsigned int estimatedArrivalTime = simTime+calcPropagationTimeTo(nextNodePtr);
		nextNodePtr->addEvent(Event(estimatedArrivalTime, packetPtr, ARRIVAL));
	}else{
		finishPacket(packetPtr);
	}
}

//processes the given event
void Node::processEvent(Event event){
	if (DEBUG) cout<<"\tNode "<<ID<<" checking event list..."<<endl;
	EVENT_TYPE type = event.getType();
	Packet* thePacket=event.getPacket();
	switch(type){
		case ARRIVAL:	//a new packet has arrived - add it to our queue
			if (DEBUG) cout<<"\t\t\tPacket "<<thePacket->getID()<<" arrived- adding to queue."<<endl;
			addPacket(thePacket);
			break;
		case TRANSMITTED:	//a packet finished transmitting within this node - send it out
			if (DEBUG) cout<<"\t\t\tPacket "<<thePacket->getID()<<" finished transmitting - sending to next Node."<<endl;
			sendOutPacket(thePacket);
			busy=false;	//we finished processing a packet! yay!
			break;
		default:
			cout<<"ERROR: BAD EVENT TYPE: "<<type<<endl;
			break;
	}
}

bool Node::checkEvents(){
	if (DEBUG) cout<<"\t\tNode "<<ID<<" checking event list..."<<endl;
	bool stillUpdating=false;
	//check if there's any new events to process
	while(eventList.isNotEmpty()){					//if there's another event on the queue
		stillUpdating=true;							//if there's anything left on our event list then we will need to update again
		if (eventList.peak().getTime() > simTime){	//the next event hasn't happened yet
			break;									//then we can't do anything until it happens - try processing some packets on our queue while we wait.
		}
		processEvent(eventList.pop());				//if the next event does happen now, pop it and deal with it! 
	}
	return stillUpdating;
}

bool Node::checkPacketQueues(){
	if (DEBUG) cout<<"\t\tNode "<<ID<<" checking packet queues..."<<endl;
	bool stillUpdating=false;
	//check if there's anything in our priority queues, smallest first
	if (!busy){	//if we're not busy already processing (transmitting) a packet
		unsigned int priorityQueueIndex;
		for (priorityQueueIndex=0; priorityQueueIndex<3; priorityQueueIndex++){
			if (packetQueues[priorityQueueIndex].isNotEmpty()){
				stillUpdating=true;	//there's still packets to process
				Packet* nextPacketToSendPtr = packetQueues[priorityQueueIndex].pop();	//pop the packet off the queue
				addEvent(Event(simTime+tranTime, nextPacketToSendPtr, TRANSMITTED));	//start processing this packet
				busy=true;
				break;	//don't keep popping from any more of our priority queues
			}
		}
	}
	return stillUpdating;
}

bool Node::update(){ //updates Node, returns if Node is empty
	if (DEBUG) cout<<"\tNode "<<ID<<" updating..."<<endl;
	bool stillUpdating=false;	//flag to see if we updated ourselves or know we will again
	
	stillUpdating|=checkEvents();
	
	stillUpdating|=checkPacketQueues();
	
	return stillUpdating;
	
	/*
	bool packetToProcess = false;
	Packet* sPacket;
	if (packetQueues[0].isNotEmpty())
	{
		packetToProcess = true;
		sPacket = packetQueues[0].pop();
	}
	else if (packetQueues[1].isNotEmpty())
	{
		packetToProcess = true;
		sPacket = packetQueues[1].pop();
	}
	else if (packetQueues[2].isNotEmpty())
	{
		packetToProcess = true;
		sPacket = packetQueues[2].pop();
	}
	if ((packetToProcess)// && (internalTime != time))
	{
		//internalTime++;
		if (propTime) propTime--;
		else if (tranTime) tranTime--;
		else
		{
			int currentQueue = sPacket->getSize();
			Node* nextNode = sPacket->popRout();
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
				propTime = ceil(log2(pos.distanceFrom(nextNode->pos)))-1;//ceil(log2(sqrt(pow(pos.getX() - sPacket->routQueue.firstElement()->getPos().getX(), 2) + pow(pos.getY() - sPacket->routQueue.firstElement()->getPos().getY(), 2)))) - 1;
			}
		}
		return true;
	}
	else return false;*/

} //end update function

//overload the steam out operator so we can cout<<Node
ostream& operator<<(ostream& os, const Node& node){
	os<<node.getType()/*"Node "*/<<(node.ID+1); //add one to the ID to make it 1-based again as it was in the input data
	return os;
}

//overload the steam out operator so we can cout<<Node*
ostream& operator<<(ostream& os, const Node* nodePtr){
	os<<"*";
	if (nodePtr){
		os<<(*nodePtr);	
	}else{
		os<<"UNININITIALIZED NODE";
	}
	return os;
}

