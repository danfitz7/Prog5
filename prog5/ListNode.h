#ifndef ListNode_H
#define ListNode_H

using namespace std;

//template<class data_t> 
class ListNode{
	friend class LinkedList;
	private:
		int dataPtr;
		ListNode* nextPtr;

	public:
		ListNode(int DATAPTR, ListNode* nextPtr);	//constructor prototype
		ListNode();										//default constructor prototype
		~ListNode(){delete(nextPtr);};					//destructor prototype
};

#endif
