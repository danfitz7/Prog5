#ifndef ListNode_H
#define ListNode_H

//#include "LinkedList.h"

using namespace std;

template<class data_t>
class LinkedList;

template<class data_t> class ListNode{
	friend class LinkedList<data_t>;
	private:
		data_t data;
		ListNode<data_t>* nextPtr;

	public:
		ListNode<data_t>(data_t DATA, ListNode<data_t>* nextPtr);	//constructor prototype
		ListNode();										//default constructor prototype
		~ListNode(){delete(nextPtr);};					//destructor prototype
};

#endif
