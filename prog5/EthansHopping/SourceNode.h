//Daniel Fitzgerald

#ifndef SOURCENODE_H
#define SOURCENODE_H

#include "Node.h"
#include "Position.h"

class SourceNode: public Node {
	friend ostream& operator<<(ostream& os, const SourceNode& srcNode);	//friend our printing helper function
	private:
		unsigned int arrivalTime;//time this sender node starts sending packets
		unsigned int nPackets;	//the number of packets this sender will send through the entire simulation
		SIZE pktSize;			//the size of each packet
		Node** SR;				//LinkedList<Node*> SR;	//the Source Routing List of each packet this source node will send
		unsigned int SR_length;	//number of packets on the rout (length of the SR array)
		
		void sendNextPacket();
		
		static unsigned int nextPacketID;//ID of the next packet to be created by ANY sender node - common to all
	public:
		char getType()const{return 'S';}
		SourceNode(unsigned int sourceID, unsigned int arrival_time, unsigned int nPackets, SIZE pkt_size, Node** SR, unsigned int SR_length);
		bool update();	//override Node's update function
};

#endif
