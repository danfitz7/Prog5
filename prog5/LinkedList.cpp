#import "prog5.h"
#include <iostream>

#include "LinkedList.h"
#include "ListNode.h"

using namespace std;

//template<class data_t>
LinkedList::LinkedList():
	headNodePtr(NULL)
{}

//template<class data_t>
LinkedList::LinkedList(int firstNodeDataPtr):
	headNodePtr(new ListNode(firstNodeDataPtr, NULL))
{}

//template<class data_t>
LinkedList::~LinkedList(){
	delete(headNodePtr);
}


//prints a list in order
//template<class data_t>
void LinkedList::print(){
	cout<<"int LIST: "<<endl;
	ListNode* curNodePtr=headNodePtr;
	while(curNodePtr){
		cout<<"NODE: "<<curNodePtr->dataPtr<<endl;
		//curNodePtr->dataPtr->print();
		curNodePtr=curNodePtr->nextPtr;
	}
}

//push an item to the end of the list (FIFO/FCFS Queue)
//template<class data_t>
void LinkedList::push(int dataPtr){
	headNodePtr = new ListNode(dataPtr, headNodePtr);	//make a new node and have it point to the old head	and use the new node as the new head
}

//pop an item off the from of the list
//template<class data_t>
int LinkedList::pop(){
	if (headNodePtr){								//if the list is not empty
		int oldHeadDataPtr = headNodePtr->dataPtr;//keep track of the data of the old head node that we will return
		ListNode* oldHeadPtr = headNodePtr;			//keep track of the current head node that we are popping off
		headNodePtr=oldHeadPtr->nextPtr;			//off with the old head, in with it's child
		//delete(oldHeadPtr);						//delete the old head
		return oldHeadDataPtr;						//return the old head's data
	}else{											//if the list is empty, return none
		cout<<"ERROR: Popping from empty list!"<<endl;
		return NULL;
	}
}

//insert an item in the list in order
//template<class data_t>
void LinkedList::insert(int newDataPtr){
//	cout<<endl<<"Inserting Node "<<newDataPtr->time<<endl;
	ListNode** curNodeFromPtrPtr = &headNodePtr;	//address of the pointer that was used to access the current node (usually a pointer to the nextPtr of the previous node)
	ListNode* curNodePtr=headNodePtr;						//pointer to the current node
	while (*curNodeFromPtrPtr){						//while the current node exists
		//if the current node exists, check if the new node should be before it
		if (newDataPtr < (*curNodeFromPtrPtr)->dataPtr){
		//if (*newDataPtr < *((*curNodeFromPtrPtr)->dataPtr)){
//			cout<<"\tInserting "<<newDataPtr->time<<" before " <<(*curNodeFromPtrPtr)->dataPtr->time<<"."<<endl;
			break;
		}
		curNodePtr = (*curNodeFromPtrPtr)->nextPtr;				//update the current node to the next of the current node
		curNodeFromPtrPtr = &((*curNodeFromPtrPtr)->nextPtr);	//update the pointer to the current node to the address of it's own next node
	}
	
	//insert the new node between the previous and next
	*curNodeFromPtrPtr = new ListNode(newDataPtr, curNodePtr);
}

void LinkedList::testLinkedLists(){
	LinkedList testQ = LinkedList();
	
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
