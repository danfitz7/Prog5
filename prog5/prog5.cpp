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
#include "SourceNode.h"
#include "MuleNode.h"
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
	
	if(DEBUG) cout<<"Using "<<nSources<<" source nodes, "<<nReceivers<<" receiver nodes, and "<<nMules<<" mule nodes. Grid size is "<<gridSize<<"."<<endl;
	
	//init the nodes
	if (DEBUG)cout<<"Initializing Nodes Pointers..."<<endl;
	SourceNode** sourceNodePtrs = new SourceNode*[nSources];
	MuleNode** muleNodePtrs = new MuleNode*[nMules];
	Node** receiverNodesPtrs= new Node*[nReceivers];
	
	//init the field
	if (DEBUG)cout<<"Initializing Field..."<<endl;
	//TODO: init the field here
	
	//variables to store packet properties as they are read in from the input file
	unsigned int sourceID, arrival_time, nPackets;	//source node properties
	unsigned int iPkt_size, SR_size;				//packet properties
	SIZE pktSize;									//size of the packet as a size
	LinkedList<Node*> packetRoutingQueue;			//Source routing Queue of each packet
	unsigned int nodeID;							//rout of packets
	
	//read all lines of the file. Each line specifies a Source Node
	string strLine;
	stringstream ss;
	unsigned int packetID =0;	//IDs to assign to all packets so we can keep track of them
	if (DEBUG)cout<<"Parsing Source Nodes..."<<endl;
	//for (unsigned int sNode=0;sNode<nSources;sNode++){
	while (getline(cin,strLine)){
		if(DEBUG) cout<<"\n\n\tLine is "<<strLine<<endl;	//get each line, where a line represents one packet's information
		ss.clear();
		ss<<strLine;
		
		ss>>sourceID;		//get the ID
		sourceID--;			//the test data give source IDas 1-based. we want 0 based to use them for our array indeces
		ss>>arrival_time;	//get the arrival time of the node itself (acts as an offset to all the subsiquent packet sending times)		
		ss>>nPackets;		//get the number of packets
		ss>>iPkt_size;		//get the size of the packet
		pktSize=(SIZE)(iPkt_size-1);//the given sizes are 1 based. convert to 0 based so they can be converted to our SIZE enum and used as array indeces for priority queue arrays
		ss>>SR_size;		//get the number of nodes on it's routing list
		
		packetRoutingQueue=LinkedList<Node*>();	//reset routing queue.
		
		if(DEBUG) cout<<"\tSource Node ID "<<sourceID<<" arrived at time "<<arrival_time<<" and has "<<nPackets<<" packets if size "<<pktSize<<" to send through a rout of "<<SR_size<<" nodes."<<endl;
				
		//loop through nodeIDs of the routing list of each packet
		if(DEBUG) cout<<"\tParsing Routing Nodes of Packet: ";
		for (unsigned int routNode=0; routNode<SR_size;routNode++){
			ss>>nodeID;
			if(DEBUG)cout<<nodeID<<" ";
			packetRoutingQueue.push(sourceNodePtrs[nodeID]);
		}
		if(DEBUG) cout<<endl;
		
		//init each source node
		if(DEBUG)cout<<"\tMaking Source Node..."<<endl;
		sourceNodePtrs[sourceID]=new SourceNode(sourceID, arrival_time, nPackets, pktSize, packetRoutingQueue);	//note this uses the sourceID provided by the command line, NOT the one we're looping through. We trust the testing data

		if(DEBUG)cout<<"\tNew source Packet:"<<*sourceNodePtrs[sourceID]<<endl;
		
		//field.placeSenderNode(*sourceNodePtrs[sourceID]);
	}
	
	cout<<"Starting simulation at time " << simTime<<"."<<endl;
	
	//testAll();
	cout<<"Done."<<endl;
}


//test all functionality of base components
void testAll(){
	//LinkedList<int>::testLinkedLists();
}
