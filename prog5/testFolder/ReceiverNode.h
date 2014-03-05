//Daniel Fitzgerald
//Ethan Coeytaux

#ifndef RECEIVERNODE_H
#define RECEIVERNODE_H

#include "Node.h"
#include "Position.h"
#include "Info.h"

//ReceiverNode extends base class Node and overrides ARRIVAL event handling behaviour to collect statistics on packets instead of sending the packets out again.
class ReceiverNode: public Node {
	friend ostream& operator<<(ostream& os, const ReceiverNode& rcvrNode);	//friend our printing helper function
	private:
		LinkedList<Packet*> receiverPackets;	//the Source Routing List of each packet this source node will send
		Info* infoList;							//Array of Infos about each source node.
		unsigned int infoListLength;			//number of sources to keep track of
	public:
		ReceiverNode(unsigned int newID, unsigned int nSources);
		char getType(){return 'R';}
		void printInfo();

		void receivePacket(Packet* packetPtr);	//overridden from Node - gets data on a received packet instead of sending it out again like other nodes			
};

#endif
