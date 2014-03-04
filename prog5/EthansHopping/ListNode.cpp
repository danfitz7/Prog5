//Daniel Fitzgerald

#import "prog5.h"
#include <iostream>

#import "ListNode.h"

//printing List Nodes just prints their data
/*
template<data_t> ostream& operator<<(ostream& os, const ListNode<data_t>& lstNode){
	os<<lstNode.data;
	return os;
}
*/

//NOTE: all this is commented and instead implemented inLinkedList.h
//This forces the compiler to implement this templated class for whatever types are necessary
//May cause slower compilation times, but it avoids the need to explicitly instantiate this class for every type we want to use, which is buggy anyway

/*
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

//template class ListNode<float>;
template class ListNode<Node*>;
template class ListNode<int>;

//destructor
template<class data_t> ListNode<data_t>::~ListNode(){
	//delete(word);
	delete(nextPtr);
}
*/
