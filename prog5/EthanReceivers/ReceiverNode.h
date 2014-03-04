//Daniel Fitzgerald

#ifndef RECEIVERNODE_H
#define RECEIVERNODE_H

#include "Node.h"
#include "Position.h"
#include "Info.h"

class ReceiverNode: public Node {
	friend ostream& operator<<(ostream& os, const ReceiverNode& rcvrNode);	//friend our printing helper function
	
	private:
		LinkedList<Packet*> receiverPackets;	//the Source Routing List of each packet this source node will send
		void finishPacket(Packet* packetPtr);
		Info* infoList;
	public:
		char getType(){return 'R';}
		ReceiverNode(unsigned int sourceID, unsigned int nSources);
};

#endif
