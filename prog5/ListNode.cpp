#import "prog5.h"
#include <iostream>

#import "ListNode.h"
#include <iostream>
using namespace std;

//template<class data_t>
ListNode::ListNode(int DATAPTR, ListNode* NEXTPTR):
	dataPtr(DATAPTR),
	nextPtr(NEXTPTR)
{}

//default constructor
//template<class data_t>
ListNode::ListNode():
	dataPtr(NULL),
	nextPtr(NULL)
{}

/*
//destructor
template<class data_t> ListNode<data_t>::~ListNode(){
	//delete(word);
	delete(nextPtr);
}
*/
