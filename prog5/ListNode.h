//Daniel Fitzgerald

#ifndef ListNode_H
#define ListNode_H

using namespace std;

//foreward declare LinkedList so we can use it as a friend class
//#include "LinkedList.h" //apparently this doesn't work
template<class data_t> class LinkedList;

//fundamental class for linked lists which function as Queues
template<class data_t> class ListNode{
	friend class LinkedList<data_t>;
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

		
		~ListNode(){delete(nextPtr);};					//destructor prototype
};

#endif
