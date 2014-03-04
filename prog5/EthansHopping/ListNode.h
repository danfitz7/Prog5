//Daniel Fitzgerald

#ifndef ListNode_H
#define ListNode_H

#include "LinkedList.h"
#include <iostream>
using namespace std;

//forward declare LinkedList so we can use it as a friend class
//#include "LinkedList.h" //apparently this doesn't work - glitch
template<class data_t> class LinkedList;

//fundamental class for linked lists which function as Queues
template<class data_t> class ListNode{
	friend class LinkedList<data_t>;
		
	//friend string stream insertion printing helper function to print nodes
	friend ostream& operator<<(ostream& os, const ListNode<data_t>& lstNode){
		os<<lstNode.data;
		return os;
	}
	
	//friend string stream insertion printing helper function to print node pointers
	friend ostream& operator<<(ostream& os, const ListNode<data_t>* lstNodePtr){
		os<<(*lstNodePtr);
		return os;
	}
	
	private:
		data_t data;
		ListNode<data_t>* nextPtr;

	public:
		//main constructor
		ListNode(data_t DATA, ListNode<data_t>* NEXTPTR):
			data(DATA),
			nextPtr(NEXTPTR)
		{}
		
		//default constructor prototype
		ListNode():
			data(),
			nextPtr(NULL)
		{}		

		ListNode* getNextPtr(){return nextPtr;}			//get a pointer to the next node in the list
		data_t getData(){return data;}					//get this node's data
		
		~ListNode(){delete(nextPtr);};					//destructor prototype
};

#endif
