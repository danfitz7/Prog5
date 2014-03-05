//Daniel Fitzgerald

//debug flag and global vars
#include "prog5.h"

#include <math.h>
#include <iostream>
#include "Packet.h"
#include "Position.h"
#include "SourceNode.h"
#include "ReceiverNode.h"
#include "Node.h"
#include "Event.h"

using namespace std;

#include "Grid.h"
extern unsigned int simTime;
extern Grid field;
extern unsigned int totalEvents;

//constructor
Node::Node(unsigned int  newID, char newType):
	ID(newID),									//unique ID of this node (NOTE: this *should* correspond to it's index in the master Node* array)
	pos(Position()),							//position of his node on the field
	eventList(LinkedList<Event>()),				//each Node has it's own event list
	packetQueues(new LinkedList<Packet*>[3]),	//small, medium, and large packet queues in an array of queues
	busy(false),								//flag to prevent the Node from processing more packets if it is alredy busy transmitting one
	type(newType)								//either 'S', 'M', or 'R' for SourceNodes, MuleNodes, or ReceiverNodes. 'N' for unspecified Node.
{
	if(DEBUG)cout<<"\t\tNode "<<this<<" initialized."<<endl;
}

void Node::print(){
	cout<<"Node "<<ID<<"."<<endl;
}

//place the node one the field at the given position
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
	if(DEBUG) cout<<"\t\t\tPlacing node randomly at "<<p<<endl;
	place(p);
}

//places this node in a random unoccupied position on the global field within the given column
void Node::placeRandomly(unsigned int col){
	Position p =field.getUnoccupiedPosition(col);
	if(DEBUG) cout<<"\t\t\tPlacing node randomly at "<<p<<endl;
	place(p);
}

//add this event to the event queue, or deal with it if it's happening right now
void Node::addEvent(Event event){
	if (event.getTime() == simTime){
		processEvent(event);
	}else if (event.getTime()<simTime){
		if (DEBUG) cout<<"ERROR: adding event from the past: "<<event<<endl;
		processEvent(event);
	}else{
		eventList.insert(event);
	}
}

//add this packet to one the appropriate priority queue
void Node::receivePacket(Packet* newPacket){
	if (type == 'R'){
		((ReceiverNode*)this)->receivePacket(newPacket);			//receive packets as a ReceiverNode
	}else{
		packetQueues[newPacket->getSize()].insert(newPacket);
		currentLength++;
		if (currentLength>longestQueueLength){
			longestQueueLength=currentLength;
		}
	}
}	

//if we are the end receiver of a packet (Overridden by SenderNodes)
void Node::finishPacket(Packet* packetPtr){
	cout<<"ERROR: regular node "<<this<<" received packet ["<<packetPtr<<"] with no more nodes on rout!"<<endl; //reminds us to override this function for receiver nodes
}

//returns the time of propagation between this node and the given other node
unsigned int Node::calcPropagationTimeTo(Node* otherNode){
	return (int)ceil(log2(pos.distanceFrom(otherNode->pos))); //TODO: is this right?
}

//sends sends the given event out to it's next stop by adding an arrival event for the packet to that node
void Node::processPacket(Packet* packetPtr){
	Node* intendedRecipient = packetPtr->popNextNodeOnRout();	//pop ourselves off the packet's source routing queue
	if (intendedRecipient != this){
		cout<<"ERROR: Packet was not sent to correct node! Packet "<<packetPtr<<" sent to "<<this<<" instead of "<<intendedRecipient<<endl;
	}
	Node* nextNodePtr=packetPtr->getNextNodeOnRout();	//peek (but don't pop) the next node on this pointer's journey
	if (nextNodePtr){
		unsigned int estimatedArrivalTime = simTime+calcPropagationTimeTo(nextNodePtr);
		Event newEvent=Event(estimatedArrivalTime, packetPtr, ARRIVAL);
		nextNodePtr->addEvent(newEvent);
	}else{
		finishPacket(packetPtr);
	}
}

//processes the given event
void Node::processEvent(Event event){
	//if this node is a receiver, process as a receiver, otherwise
	if (DEBUG) cout<<"\t\tNode "<<this<<" processing event " <<event<<"..."<<endl;
	
	cout<<"Node "<<this<<" processing event " <<event<<endl;
	totalEvents++;	//we processed another event. Add to the global count.
	
	EVENT_TYPE type = event.getType();
	Packet* thePacket=event.getPacket();
	switch(type){
		case ARRIVAL:	//a new packet has arrived - add it to our queue
			if (DEBUG)cout<<"\t\tPacket "<<thePacket->getID()<<" arrived - receiving..."<<endl;
			receivePacket(thePacket);
			break;
		case TRANSMITTED:	//a packet finished transmitting within this node - send it out
			if (DEBUG) cout<<"\t\tPacket "<<thePacket->getID()<<" finished transmitting - sending to next Node."<<endl;
			processPacket(thePacket);
			busy=false;	//we finished processing a packet! yay!
			break;
		default:
			cout<<"ERROR: BAD EVENT TYPE: "<<type<<endl;
			break;
	}
}

//check the event list for new events
bool Node::checkEvents(){
	if (DEBUG) cout<<"\t\tNode "<<this<<" checking event list..."<<endl;
	bool stillUpdating=false;
	//check if there's any new events to process
	while(eventList.isNotEmpty()){					//if there's another event on the queue
		stillUpdating=true;							//if there's anything left on our event list then we will need to update again
		if (eventList.peek().getTime() > simTime){	//the next event hasn't happened yet
			break;									//then we can't do anything until it happens - try processing some packets on our queue while we wait.
		}
		processEvent(eventList.pop());				//if the next event does happen now, pop it and deal with it! 
	}
	return stillUpdating;
}

//process any packets on the packet queues (if we aren't already busy with a packet)
bool Node::checkPacketQueues(){
	bool stillUpdating=false;
	//check if there's anything in our priority queues, smallest first
	if (!busy){	//if we're not busy already processing (transmitting) a packet
		if (DEBUG) cout<<"\t\tNode "<<this<<" checking packet queues..."<<endl;
		unsigned int priorityQueueIndex;
		for (priorityQueueIndex=0; priorityQueueIndex<3; priorityQueueIndex++){
			if (packetQueues[priorityQueueIndex].isNotEmpty()){
				stillUpdating=true;	//there's still atleast one packet to process
				
				//process the next packet from the most prioritized non-empty queue
				Packet* nextPacketToSendPtr = packetQueues[priorityQueueIndex].pop();	//pop the packet off the queue
				addEvent(Event(simTime+nextPacketToSendPtr->getTransTime(), nextPacketToSendPtr, TRANSMITTED));	//start processing this packet
				busy=true;
				break;	//don't keep popping from any more of our priority queues
			}
		}
	}else{
		if (DEBUG) cout<<"\tBUSY"<<endl;
	}
	return stillUpdating;
}

//main update function for all nodes - called directly in main simulaiton loop. Overridden for each Node derived class.
bool Node::update(){ //updates Node, returns if Node is empty
	if (DEBUG) cout<<"\tNode "<<this<<" updating..."<<endl;
	bool stillUpdating=false;	//flag to see if we updated ourselves or know we will again
	
	stillUpdating|=checkEvents();
	
	stillUpdating|=checkPacketQueues();
	
	return stillUpdating;

} //end update function

//overload the steam out operator so we can cout<<Node
ostream& operator<<(ostream& os, const Node& node){
	os<<node.type<<(node.ID+1); //add one to the ID to make it 1-based again as it was in the input data
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

