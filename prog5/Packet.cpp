//Ethan Coeytaux
//Daniel Fitzgerald

#include <iostream>
#include "Packet.h"

using namespace std;

//packet constructor
Packet::Packet(LinkedList<Node*> ROUT, int newID, int time):
	size(1),  //size always 1
	ID(newID),
	rout(ROUT),
	sentTime(time)
{}

/*
//adds Packet to packetList (returns length of queue)
int Packet::addPacket(Packet *newPacket) 
{
	if (nextPacket) return nextPacket->addPacket(newPacket) + 1; //if packet has no packets behind it
	else //if packet is last in line
	{
		nextPacket = newPacket;
		return 1; //used to calculate length of queue
	} //end else statement
} //end addPacket function
*/

ostream& operator<<(ostream& os, const Packet& packet){
	os<< "Packet " << ID << endl;
	os<<"\tsent time: "<< sentTime<<endl;
}

//prints out node final info
int Packet::print(int time) 
{
	cout << "Packet " << ID << " final info:" << endl;
	cout << "  Sender: " << "S" << sender << endl;
	int responseTime = time - sentTime;
	cout << "  Response time: " << responseTime << endl;
	return responseTime;
} //end print function
