//Daniel Fitzgerald

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include "ListNode.h"

//forward declare friended functions
//template<data_t> ostream& operator<< <data_t>(ostream& os, const LinkedList<data_t>& LL);
	
//LinkedLists is a wrapper class for ListNode, which are nodes in a sorted LinkedList which can act as queues
template<class data_t> class LinkedList{
	
	//helper overridden stream insertion operator to print every item in a linked list
	friend ostream& operator<<(ostream& os, const LinkedList<data_t>& LL){
		os<<"LL {";
		ListNode<data_t>* curNodePtr=LL.headNodePtr;
		while(curNodePtr){
			//os<<(*curNodePtr)<<", ";
			os<<(curNodePtr->getData())<<", ";
			curNodePtr=curNodePtr->getNextPtr();
		}
		os<<"}";
		return os;
	}

	private:
		ListNode<data_t>* headNodePtr;	//pointer to the first ListNode of the list
		unsigned int curLength;			//length of the queue right now
		unsigned int longestLength; 	//the max length the queue has reached so far
		
	public:
		LinkedList():
			headNodePtr(NULL),
			curLength(0),
			longestLength(0)
		{}
		
		bool isNotEmpty(){return headNodePtr;}
		
		//copy a linked list (NOT DEEP COPY)
		/*LinkedList(const LinkedList<data_t>& other):
			headNodePtr(other.headNodePtr),
			curLength(other.curLength),
			longestLength(other.longestLength)
		{}*/
		
		//returns the first item on the list but does NOT pop it off yet
		data_t peek(){
			if (!headNodePtr){
				//we're about to crash by trying to access a NULL ListNode's data. Be nice and print out why we're crashing
				cout<<"ERROR: call to LinkedList::peek() without first checking LinkedList::isNotEmpty()"<<endl;
			}/*else if ((headNodePtr->data)){
				cout<<"ERROR: call to LinedList::peek() using first node with data=NULL"<<endl;
				return headNodePtr->data;
			}*/
			return headNodePtr->data;
		}
		
		//template<class data_t>
		/*~LinkedList(){
			delete(headNodePtr);
		}*/
		
		//returns the maximum number of elements this list has ever contained
		int getLongestLength(){
			return longestLength;
		}

		//prints a list in order
		void print(){
			cout<<"LL: {";
			ListNode<data_t>* curNodePtr=headNodePtr;
			while(curNodePtr){
				cout<<(curNodePtr->data)<<", ";
				//curNodePtr->dataPtr->print();
				curNodePtr=curNodePtr->nextPtr;
			}
			cout<<"}"<<endl;
		}
		
		//push an item to the end of the list (FIFO/FCFS Queue)
		void push(data_t data){
			headNodePtr = new ListNode<data_t>(data, headNodePtr);	//make a new node and have it point to the old head	and use the new node as the new head
			curLength++;
			if (curLength>longestLength){
				longestLength=curLength;
			}
		}
		
		//pop an item off the from of the list
		data_t pop(){
			if (headNodePtr){								//if the list is not empty
				data_t oldHeadData = headNodePtr->data;		//keep track of the data of the old head node that we will return
				ListNode<data_t>* oldHeadPtr = headNodePtr;	//keep track of the current head node that we are popping off
				headNodePtr=oldHeadPtr->nextPtr;			//off with the old head, in with it's child
				//delete(oldHeadPtr);						//delete the old head
				curLength--;
				return oldHeadData;							//return the old head's data
			}else{											//if the list is empty, return none
				//be nice and print out why things might crash after this
				cout<<"ERROR: Popping from empty list - returning data from NULL head pointer!"<<endl;
				return headNodePtr->data;
			}
		}
		
		//insert an item in the list in order
		void insert(data_t newData){
		//	cout<<endl<<"Inserting Node "<<newData->time<<endl;
			ListNode<data_t>** curNodeFromPtrPtr = &headNodePtr;	//address of the pointer that was used to access the current node (usually a pointer to the nextPtr of the previous node)
			ListNode<data_t>* curNodePtr=headNodePtr;						//pointer to the current node
			while (*curNodeFromPtrPtr){						//while the current node exists
				//if the current node exists, check if the new node should be before it
				if (newData < (*curNodeFromPtrPtr)->data){
					break;
				}
				curNodePtr = (*curNodeFromPtrPtr)->nextPtr;				//update the current node to the next of the current node
				curNodeFromPtrPtr = &((*curNodeFromPtrPtr)->nextPtr);	//update the pointer to the current node to the address of it's own next node
			}
			
			//insert the new node between the previous and next
			*curNodeFromPtrPtr = new ListNode<data_t>(newData, curNodePtr);
			
			curLength++;
			if (curLength>longestLength){
				longestLength=curLength;
			}
		}
		
		//static test function to test linked list functionality
		static void testLinkedLists(){
			LinkedList<data_t> testQ = LinkedList<data_t>();
			
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
			}
			
			cout<<"new list"<<endl;
			testQ.print();
			
			cout<<"Inserting ints..."<<endl;
			testQ.insert(1.5);
			testQ.print();
			testQ.insert(1);
			testQ.print();
			testQ.insert(3.2);
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
	//template<event> class LinkedList;
};

#endif
