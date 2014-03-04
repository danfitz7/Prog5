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
		void finishPacket(Packet* packetPtr);	//gets data on a received packet instead of sending it out again like other nodes			
		Info* infoList;
	public:
		ReceiverNode(unsigned int newID, unsigned int nSources);
		char getType(){return 'R';}
};

#endif
