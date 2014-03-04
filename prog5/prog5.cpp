/*
CS 2302 Progam 5
Daniel Fitzgerald
A Simulation of MANET Source Routing in C++ 
*/

//debug flag and global vars
#include "prog5.h"

//used for input and string manipulation
//Daniel Fitzgerald

// ./lab5 20 12 16 20 < prog5.txt


#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <sstream>
//#include <cstdlib>

//other classes
#include "LinkedList.h"
#include "Node.h"
#include "SourceNode.h"
#include "MuleNode.h"
#include "ReceiverNode.h"
#include "Packet.h"
using namespace std;

//global variables
unsigned int simTime =0;
Grid field = Grid();

//function prototypes
void testAll();
void testNodePointerInheritence();
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
	
	testNodePointerInheritence();
	
	
	//ensure there is the correct number of command line arguments (the first is the name of our program, the second should be the number of arguments to come from a file)
	if (argc<5){
		cout<<"ERROR: Proper usage requires at-least four arguments: <sources> <receivers> <mules> <dimension>"<<endl;
		return 0;
	}

	//randomize
	srand (time(NULL));
	
	//input parsing
	
	//char* progString=argv[0];			//the first arg is always the name of the program
	nSources	=atoi(argv[1]); 	//the number of lines should be the second argument
	nReceivers	=atoi(argv[2]); 	//the number of lines should be the second argument
	nMules		=atoi(argv[3]); 	//the number of lines should be the second argument
	gridSize	=atoi(argv[4]); 	//the number of lines should be the second argument
	
	if(DEBUG) cout<<"Using "<<nSources<<" source nodes, "<<nReceivers<<" receiver nodes, and "<<nMules<<" mule nodes. Grid size is "<<gridSize<<"."<<endl;
	
	//init the field
	if (DEBUG)cout<<"Initializing Field..."<<endl;
	field.setSize(gridSize);
	
	//init the node arrays
	if (DEBUG)cout<<"Initializing Nodes Pointers..."<<endl;
	sourceNodePtrs = new SourceNode*[nSources];
	muleNodePtrs = new MuleNode*[nMules];
	receiverNodePtrs= new ReceiverNode*[nReceivers];

	unsigned int newNodeID=nSources;
	
	//init the mule nodes
	//unsigned int lastMuleIndex=nSources+nMules;
	if (DEBUG) cout<<endl<<"\n\tInitializing "<<nMules<<" mules nodes..."<<endl;
	for (unsigned int muleID=0;muleID<nMules;muleID++){
		muleNodePtrs[muleID]=new MuleNode(newNodeID);
		newNodeID++;
	}
	
	//init the receiver nodes
	//unsigned int lastReceiverIndex=nSources+nMules+nReceivers;
	if (DEBUG) cout<<endl<<"\n\tInitializing "<<nReceivers<<" receiver nodes..."<<endl;
	for (unsigned int receiverID=0;receiverID<nReceivers; receiverID++){
		receiverNodePtrs[receiverID]=new ReceiverNode(newNodeID, nSources);
		newNodeID++;
	}
	
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
	unsigned int senderIndexCheck=0;
	while (getline(cin,strLine)){
		senderIndexCheck++;
		if (senderIndexCheck>nSources){
			cout<<"ERROR: More source node lines in file than were specified by the command line!"<<endl;
			break;
		}
		
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
		
		if(DEBUG) cout<<"\tSource Node ID "<<sourceID+1<<" arrived at time "<<arrival_time<<" and has "<<nPackets<<" packets of size "<<pktSize<<" to send through a rout of "<<SR_size<<" nodes."<<endl;
				
		//loop through nodeIDs of the routing list of each packet, adding them in reverse from the back of the array
		if(DEBUG) cout<<"\tParsing Routing Nodes of Packet: ";
		Node** sourceRoute = new Node*[SR_size];
		for (unsigned int routNode=0; routNode<SR_size;routNode++){
			ss>>nodeID;
			if(DEBUG)cout<<nodeID<<" ";
			nodeID--;	//convert 1 base to 0 bases indexing
			sourceRoute[routNode]=getPtrOfNode(nodeID);
		}
		if(DEBUG) cout<<endl;
		
		
		//TODO: get rid of self at head of queue?
		//better for nodes to pop themselves off the queue and peak at the next node on the queue, or pop the next node off and lose the source by the end?
		
		//init each source node
		if(DEBUG)cout<<"\tMaking Source Node "<<sourceID+1<<"..."<<endl;
		sourceNodePtrs[sourceID]=new SourceNode(sourceID, arrival_time, nPackets, pktSize, sourceRoute, SR_size);	//note this uses the sourceID provided by the command line, NOT the one we're looping through. We trust the testing data
		if (!sourceNodePtrs[sourceID]){
			cout<<"ERROR: Source Node creation failed!"<<endl;
		}
		if(DEBUG)cout<<"\tNew source made: "<<(*sourceNodePtrs[sourceID])<<endl;
		
	}
	
	if (senderIndexCheck!=nSources){
		cout<<"ERROR: command line specified " << nSources << " sender nodes but file provided " << senderIndexCheck << "."<<endl;
	}
	
	cout<<"\n\n\nStarting simulation at time " << simTime<<"."<<endl;
	
	bool anythingUpdated=true;
	while(anythingUpdated){
		//if (DEBUG)cout<<"Sim Time " << simTime<<"."<<endl;

		if (simTime%100==0) field.print();
		
		
		
		anythingUpdated=false;//reset every timestep
		
		//loop through all nodes and update them
		if (DEBUG)cout<<"SENDERS"<<endl;
		for (unsigned int sourceIndex=0;sourceIndex<nSources;sourceIndex++){
			anythingUpdated|=sourceNodePtrs[sourceIndex]->update();
		}
		if (DEBUG)cout<<endl<<"MULES"<<endl;
		for (unsigned int muleIndex=0;muleIndex<nMules;muleIndex++){
			anythingUpdated|=muleNodePtrs[muleIndex]->update();
		}
		if (DEBUG)cout<<endl<<"RECEIVERS"<<endl;
		for (unsigned int receiverIndex=0; receiverIndex<nReceivers; receiverIndex++){
			anythingUpdated|=receiverNodePtrs[receiverIndex]->update();
		}
		
		
		//after every 10 seconds (100 100ms units) update the mule
		if (simTime%100==0){
			if (DEBUG)cout<<endl<<"HOPPING MULES at time "<<simTime<<endl<<endl;
			for (unsigned int muleIndex=0;muleIndex<nMules;muleIndex++){
				anythingUpdated=true;
				muleNodePtrs[muleIndex]->hop();
			}
		}
		
		
		simTime++;//INCREMENT GLOBAL COUNT
	}

	//testAll();
	cout<<"Done."<<endl;
}

//nodes pointers are distributed across three arrays for the three types. Return the node* from the appropriate array based on the node's index
Node* getPtrOfNode(unsigned int index){
	if (index<nSources){
		return sourceNodePtrs[index];
	}else if ((index >= nSources) && (index < nSources+nMules)){
		return muleNodePtrs[index-nSources];
	}else if ((index >= nSources+nMules) && (index < nSources+nMules+nReceivers)){
		return receiverNodePtrs[index-(nSources+nMules)];
	}else{
		cout << "ERROR: request for Node* of node ID "<<index<<" which is out of bounds!"<<endl;
		return NULL;
	}
}


void testNodePointerInheritence(){
	cout<<endl<<"Testing Node inheritance."<<endl;
	field.setSize(10);
	Node* testNode = new MuleNode(8);
	((MuleNode*)testNode)->print();
	testNode->print();
	cout<<"Done testing inheritance."<<endl<<endl;;
}

//test all functionality of base components
void testAll(){
	//LinkedList<int>::testLinkedLists();
	testNodePointerInheritence();
}
