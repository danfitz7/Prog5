//Daniel Fitzgerald

#ifndef ListNode_H
#define ListNode_H

#include "LinkedList.h"
#include <iostream>
using namespace std;

//foreward declare LinkedList so we can use it as a friend class
//#include "LinkedList.h" //apparently this doesn't work
template<class data_t> class LinkedList;

//fundamental class for linked lists which function as Queues
template<class data_t> class ListNode{
	friend class LinkedList<data_t>;
	
	//template<class data_t> friend ostream& operator<<(ostream& os, const LinkedList<data_t>& LL);
	
	//friend our printing helper function
	friend ostream& operator<<(ostream& os, const ListNode<data_t>& lstNode){
		os<<lstNode.data;
		return os;
	}
	
	friend ostream& operator<<(ostream& os, const ListNode<data_t>* lstNodePtr){
		os<<(*lstNodePtr);
		return os;
	}
	
	//friend ostream& operator<< <data_t>(ostream& os, const ListNode<data_t>& lstNode);	//friend our printing helper function
	//friend ostream& operator<< <data_t>(ostream& os, const LinkedList<data_t>& LL);	//give the LinkedList printer funciton access to a node's private vars
	
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

		ListNode* getNextPtr(){return nextPtr;}
		data_t getData(){return data;}
		
		~ListNode(){delete(nextPtr);};					//destructor prototype
};

#endif
