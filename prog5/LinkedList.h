#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ListNode.h"

//template<class data_t>
class LinkedList{
	private:
		ListNode* headNodePtr;
		//listNode<data_t>* tailNodePtr;
	
	public:
		LinkedList();
		LinkedList(int firstNodeDataPtr);
		~LinkedList();
		
		void print();
		void push(int dataPtr);
		int pop();
		void insert(int dataPtr);
		
		static void testLinkedLists();
	//template<event> class LinkedList;
};

#endif
