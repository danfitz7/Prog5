/*
CS 2302 Progam 5
Daniel Fitzgerald
A Simulation of MANET Source Routing in C++ 
*/

//debug flag and global vars
#include "prog5.h"

//used for input and string manipulation
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <sstream>

//other classes
#include "LinkedList.h"
#include "Node.h"
#include "Packet.h"
using namespace std;

//global variables
int simTime =0;

//function prototypes
void testAll();

/*
Event-Driven simulation of MANET nodes
*/
int main(int argc, char* argv[]){
	if(DEBUG){cout<<endl<<"PROG5\nProcessing "<<argc<<" inputs..."<<endl;}
	
	//ensure there is the correct number of command line arguments (the first is the name of our program, the second should be the number of arguments to come from a file)
	if (argc<5){
		cout<<"ERROR: Proper usage requires at-least four earguments: <sources> <receivers> <mules> <dimension>"<<endl;
		return 0;
	}

	//input parsing
	
	//char* progString=argv[0];			//the first arg is always the name of the program
	unsigned int nSources	=atoi(argv[1]); 	//the number of lines should be the second argument
	unsigned int nReceivers	=atoi(argv[2]); 	//the number of lines should be the second argument
	unsigned int nMules		=atoi(argv[3]); 	//the number of lines should be the second argument
	unsigned int gridSize	=atoi(argv[4]); 	//the number of lines should be the second argument
	
	cout<<"Using "<<nSources<<" source nodes, "<<nReceivers<<" receiver nodes, and "<<nMules<<" mule nodes. Grid size is "<<gridSize<<"."<<endl;
	
	//init the nodes
	Node** sourceNodePtrs 	= new Node*[nSources];
	Node** muleNodePtrs 	= new Node*[nMules];
	Node** receiverNodesPtrs= new Node*[nReceivers];
	
	//init the field
	
	//variables to store packet properties
	unsigned int sourceID, arrival_time, nPackets;	//source node
	unsigned int pkt_size, SR_size;					//packets
	LinkedList<Node*> packetRoutingQueue;			//Source routing Queue of each packet
	unsigned int nodeID;							//rout of packets
	
	//read all lines of the file. Each line specifies a Source Node
	string strLine;
	stringstream ss;
	unsigned int packetID =0;	//id to assign to all packets
	for (unsigned int sNode=0;sNode<nSources;sNode++){
	//while (getline(cin,strLine)){
		if(DEBUG) cout<<"Line is "<<strLine<<endl;	//get each line, where a line represents one packet's information
		ss.clear();
		ss<<strLine;
		
		ss>>sourceID;		//get the ID
		ss>>arrival_time;	//get the arrival time of the node itself (acts as an offset to all the subsiquent packet sending times)		
		ss>>nPackets;
		
		if(DEBUG) cout<<"\tSource ID "<<sourceID<<" arrived at time "<<arrival_time<<" and has "<<nPackets<<" packets to send."<<endl;
		
		//init each source node
		if(DEBUG)cout<<"\tMaking Source Node..."<<endl;
		sourceNodePtrs[sourceID]=new Node(sourceID);	//note this uses the sourceID provided by the command line, NOT the one we're looping through. We trust the testing data

		//loop through packets of this sender node
		for (unsigned int packet=0;packet<nPackets;packet++){
			ss>>pkt_size;	//get the size of the packet
			pkt_size--;		//the given sizes are 1 based. convert to 0 based so they can be used as array indeces
			ss>>SR_size;	//get the number of nodes on it's routing list
					
			//loop through nodeIDs of the routing list of each packet
			if(DEBUG) cout<<"\tRouting nodes:"<<endl;
			for (unsigned int routNode=0; routNode<SR_size;routNode++){
				ss>>nodeID;
				if(DEBUG)cout<<nodeID<<" ";
				packetRoutingQueue.push(sourceNodePtrs[nodeID]);
			}
			if(DEBUG) cout<<endl;
			
			//initialize this packet and push it on this node's packet queue
			if(DEBUG)cout<<"\t...done parsing this packet's source routing list. Adding packet to Node's packet queue..."<<endl;
			sourceNodePtrs[sourceID]->receivePacket(new Packet(packetID, (SIZE)pkt_size, arrival_time, packetRoutingQueue));
			
			packetID++;
		}
		
		//field.placeSenderNode(sourceNodePtrs[sourceID]);

	}
	
	cout<<"Starting simulation at time " << simTime<<"."<<endl;
	
	//testAll();
	cout<<"Done."<<endl;
}


//test all functionality of base components
void testAll(){
	LinkedList<float>::testLinkedLists();
}
