#import "prog5.h"
#include <iostream>

#import "ListNode.h"
#include <iostream>
using namespace std;

template<class data_t> ListNode<data_t>::ListNode(data_t DATA, ListNode<data_t>* NEXTPTR):
	data(DATA),
	nextPtr(NEXTPTR)
{}

//default constructor
template<class data_t> ListNode<data_t>::ListNode():
	data(),
	nextPtr(NULL)
{}

//instantiate this class on the type int
template class ListNode<int>;

/*
//destructor
template<class data_t> ListNode<data_t>::~ListNode(){
	//delete(word);
	delete(nextPtr);
}
*/
