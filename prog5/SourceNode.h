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
		LinkedList<Node*> SR;	//the Source Routing List of each packet this source node will send
	public:
		char getType(){return 'S';}
		SourceNode(unsigned int sourceID, unsigned int arrival_time, unsigned int nPackets, SIZE pkt_size);
		//void sendNextPacket();
		
		void pushSR(Node* nodePtr){
			SR.push(nodePtr);
		}
		
		LinkedList<Node*> getSR(){
			return SR;
		}
};

#endif
