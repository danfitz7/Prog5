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
//#include "Node.h"
//#include "Packet.h"
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
	if (argc<2){
		printf("ERROR: Proper usage requires at-least one event argument in the format <process ID> <arrival time> <cpu time>\n");
		return 0;
	}

	
	cout<<"Starting simulation at time " << simTime<<"."<<endl;
	
	testAll();
	
}


//test all functionality of base components
void testAll(){
	LinkedList<float>::testLinkedLists();
}
