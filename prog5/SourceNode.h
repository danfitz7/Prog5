//Daniel Fitzgerald

#ifndef SOURCENODE_H
#define SOURCENODE_H

#include "Node.h"
#include "Position.h"

class SourceNode: public Node {
	friend ostream& operator<<(ostream& os, const SourceNode& srcNode);	//friend our printing helper function
	private:
		unsigned int arrivalTime;	//time this sender node starts sending packets
		unsigned int nPackets;		//the number of packets this sender will send through the entire simulation
		SIZE pktSize;				//the size of each packet
		Node** SR;					//the Source Routing List (stored as array) of each packet this source node will send
		unsigned int SR_length;		//number of packets on the rout (length of the SR array)
		bool isInSim;				//is the source node still in the simulation?
		void sendNextPacket();		//generate new packets for the simulation.
		
		static unsigned int nextPacketID;//ID of the next packet to be created by ANY sender node - common to all Senders so all packets have unique IDs
	public:
		SourceNode(unsigned int sourceID, unsigned int arrival_time, unsigned int nPackets, SIZE pkt_size, Node** SR, unsigned int SR_length);
		bool update();	//override Node's update function so Senders generate new packets.
};

#endif
