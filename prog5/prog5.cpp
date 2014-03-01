/*
CS 2302 Progam 5
Daniel Fitzgerald
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
//#include "Grid.h"

using namespace std;

//global variables
extern int simTime;

//function prototypes
void testLinkedLists();

/*
MAIN
*/
int main(int argc, char* argv[]){
	if(DEBUG){cout<<endl<<"PROG5\nProcessing "<<argc<<" inputs..."<<endl;}
	
	//ensure there is the correct number of command line arguments (the first is the name of our program, the second should be the number of arguments to come from a file)
	if (argc<2){
		printf("ERROR: Proper usage requires at-least one event argument in the format <process ID> <arrival time> <cpu time>\n");
		return 0;
	}

	testLinkedLists();
	
}


void testLinkedLists(){
	LinkedList<int> testQ = LinkedList<int>();
	
	testQ.push(0);
	testQ.push(1);
	testQ.push(3);
	testQ.push(4);
	testQ.push(2);
	testQ.push(5);
	
	cout<<"Pushed ints."<<endl;
	testQ.print();
	cout<<"Popping..."<<endl;
	
	for (size_t i=0;i<=5;i++){
		cout<<testQ.pop()<<endl;
		//testQ.pop()->print();
	}
	
	cout<<"new list"<<endl;
	testQ.print();
	
	cout<<"Inserting ints..."<<endl;
	testQ.insert(1);
	testQ.print();
	testQ.insert(1);
	testQ.print();
	testQ.insert(3);
	testQ.print();
	testQ.insert(4);
	testQ.print();
	testQ.insert(4);
	testQ.print();
	testQ.insert(2);
	testQ.print();
	testQ.insert(5);
	testQ.print();
	testQ.insert(0);
	
	cout<<"Inserted ints."<<endl;
	testQ.print();
}
