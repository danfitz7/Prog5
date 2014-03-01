#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ListNode.h"

template<class data_t> class LinkedList{
	private:
		ListNode<data_t>* headNodePtr;
		//listNode<data_t>* tailNodePtr;
	
	public:
		LinkedList();
		~LinkedList();
		
		void print();
		void push(data_t data);
		data_t pop();
		void insert(data_t data);
		
		//static void testLinkedLists();
	//template<event> class LinkedList;
};

#endif
