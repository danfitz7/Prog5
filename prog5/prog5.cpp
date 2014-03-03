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
#include "ReceiverNode.h"
#include "Packet.h"
using namespace std;

//global variables
int simTime =0;
Grid field = Grid();

//function prototypes
void testAll();
Node* getPtrOfNode(unsigned int index);

unsigned int nSources; //the number of lines should be the second argument
unsigned int nReceivers; //the number of lines should be the second argument
unsigned int nMules; 	//the number of lines should be the second argument
unsigned int gridSize; 	//the number of lines should be the second argument
SourceNode** sourceNodePtrs;
MuleNode** muleNodePtrs;
ReceiverNode** receiverNodePtrs;

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
	nSources	=atoi(argv[1]); 	//the number of lines should be the second argument
	nReceivers	=atoi(argv[2]); 	//the number of lines should be the second argument
	nMules		=atoi(argv[3]); 	//the number of lines should be the second argument
	gridSize	=atoi(argv[4]); 	//the number of lines should be the second argument
	
	if(DEBUG) cout<<"Using "<<nSources<<" source nodes, "<<nReceivers<<" receiver nodes, and "<<nMules<<" mule nodes. Grid size is "<<gridSize<<"."<<endl;
	
	//init the nodes
	if (DEBUG)cout<<"Initializing Nodes Pointers..."<<endl;
	sourceNodePtrs = new SourceNode*[nSources];
	muleNodePtrs = new MuleNode*[nMules];
	receiverNodePtrs= new ReceiverNode*[nReceivers];
	
	//init the mule nodes
	unsigned int lastMuleIndex=nSources+nMules;
	for (unsigned int muleID=nMules;muleID<lastMuleIndex;muleID++){
		muleNodePtrs[muleID]=new MuleNode(muleID);
	}
	
	//init the receiver nodes
	unsigned int lastReceiverIndex=nSources+nMules+nReceivers;
	for (unsigned int receiverID=lastMuleIndex;receiverID<lastReceiverIndex; receiverID++){
		receiverNodePtrs[receiverID]=new ReceiverNode(receiverID);
	}
	
	//init the field
	if (DEBUG)cout<<"Initializing Field..."<<endl;
	//TODO: init the field here
	//field=new grid(gridSize);
	
	//variables to store packet properties as they are read in from the input file
	unsigned int sourceID, arrival_time, nPackets;	//source node properties
	unsigned int iPkt_size, SR_size;				//packet properties
	SIZE pktSize;									//size of the packet as a size		
	unsigned int nodeID;							//rout of packets
	
	//Init the source nodes by reading the input file
	string strLine;
	stringstream ss;
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
		
		//LinkedList<Node*> packetRoutingQueue=LinkedList<Node*>();	//Source routing Queue of each packet
		
		if(DEBUG) cout<<"\tSource Node ID "<<sourceID+1<<" arrived at time "<<arrival_time<<" and has "<<nPackets<<" packets if size "<<pktSize<<" to send through a rout of "<<SR_size<<" nodes."<<endl;
				
		//loop through nodeIDs of the routing list of each packet
		if(DEBUG) cout<<"\tParsing Routing Nodes of Packet: ";
		unsigned int routingNodeIndexArray[SR_size];//= new unsigned int[SR_size];
		for (unsigned int routNode=0; routNode<SR_size;routNode++){
			ss>>nodeID;
			if(DEBUG)cout<<nodeID<<" ";
			routingNodeIndexArray[routNode]=nodeID-1;
		}
		if(DEBUG) cout<<endl;
		
		if (DEBUG) cout<<"\tPushing on the array in reverse order."<<endl;
		Node** sourceRoute = new Node*[SR_size];
		unsigned int lastNodeArrayIndex=SR_size-1;
		for (int routNode=lastNodeArrayIndex; routNode>=0;routNode--){
			sourceRoute[lastNodeArrayIndex-routNode]=getPtrOfNode(routingNodeIndexArray[routNode]);
		}
		
		//init each source node
		if(DEBUG)cout<<"\tMaking Source Node "<<sourceID+1<<"..."<<endl;
		sourceNodePtrs[sourceID]=new SourceNode(sourceID, arrival_time, nPackets, pktSize, sourceRoute, SR_size);	//note this uses the sourceID provided by the command line, NOT the one we're looping through. We trust the testing data
		
		/*
		//push the routing nodes in reverse order
//		cout<<"\tPushing in reverse order: ";
		for (int routNode=SR_size-1; routNode>=0;routNode--){
//			cout<<(routingNodeIndexArray[routNode]+1)<<", ";
			sourceNodePtrs[sourceID]->pushSR(getPtrOfNode(routingNodeIndexArray[routNode]));
		}
		cout<<endl;
		*/
		
		//cout<<"\tFinal routing Queue is: ";
		//packetRoutingQueue.print();
		
		if(DEBUG)cout<<"\tNew source made: "<<(*sourceNodePtrs[sourceID])<<endl;
	}
	
	cout<<"Starting simulation at time " << simTime<<"."<<endl;
	
	//TODO: run the simulation here - should be similar to lab5
	
	//testAll();
	cout<<"Done."<<endl;
}

//nodes pointers are distributed across three arrays for the three types. Return the node* from the appropriate array based on the node's index
Node* getPtrOfNode(unsigned int index){
	if (index<nSources){
		return sourceNodePtrs[index];
	}else if (index>=(nSources+nMules)){
		return receiverNodePtrs[index];
	}else{
		return muleNodePtrs[index];
	}
}

//test all functionality of base components
void testAll(){
	//LinkedList<int>::testLinkedLists();
}
