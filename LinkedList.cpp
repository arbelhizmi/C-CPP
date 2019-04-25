//
//the LinkedList.cpp file use all the functions which define in the header file.
//the file use copy constructors (with tree and list) and = operators (with tree and list)
//and use a destructor. the file also use private function which also define in the header files.

#include <iostream>
#include "LinkedList.h"
#include"btree.h"
#include <cassert>
using namespace std;


LinkedList::LinkedList() {
	length = 0;
	head = NULL;
}

//destructor. the destructor use a void function which destroy the list
//node after node, and send to the function the "this" head object
LinkedList::~LinkedList() {
	destroyList(this->head);
}

//the function would delete the list, a node after node
//witht two pointers - cur and next
void LinkedList::destroyList(Node * head)
{
	Node* next = head;
	Node* cur = NULL;
	while (next != NULL) {
		cur = next;
		next = next->next;
		delete cur;
	}
}

//copy constructor which receive a btree object and send its root
//to a private function treeToList
LinkedList::LinkedList(btree & bt)
{
	length = 0;
	treeToList(bt.root);
}

//receive a node, and copy it into a new list,
//because it called from the copy constructor which receive a tree
void LinkedList::treeToList(node* leaf)
{
	if (leaf == NULL) {
		return;
	}
	else {
		treeToList(leaf->left);
		add(leaf->key_value);
		treeToList(leaf->right);
	}
}

//copy constructor which receive a linkedList object. it checks if the 
//head is not NULL to avoid NULL copying
LinkedList::LinkedList(LinkedList & bt)
{
	length = 0;
	Node* temp = bt.head;
	if (bt.head == NULL) { //check if it tries to copy empty list
		return;
	}
	while (temp != NULL) {
		insertAtEnd(temp->data);
		temp = temp->next;
	}
}

//a function which receive an int, and add a node with this
//received int as its data, to the head of the list
void LinkedList::add(int data)
{
	Node* temp = new Node();
	assert(temp != NULL);
	temp->data = data;
	temp->next = head;
	head = temp;
	length++;
}

//recursive function which receive an int and insert
//a new node with this data to the end of the list - to the tail of the list
void LinkedList::insertAtEnd(int data) {
	Node* node = new Node();
	node->data = data;
	node->next = NULL;
	if (head == NULL) { //list is empty
		head = node;
		length++;
		return;
	}
	Node* curr = head;
	while (curr->next)
		curr = curr->next;
	curr->next = node;

	length++;
}

//ostream function for printing the list with the operator <<.
//the funcition receive a list and os object. both with reference
ostream & operator<<(ostream & os, LinkedList & l)
{
	Node* temp = l.head;
	os << "List:(";
	for (int i = 0; i < l.length; i++) {
		os << temp->data << ",";
		temp = temp->next;
	}
	os << ")" << endl;
	return os;
}

//a function to redefine the = operator. the function receive const linkedList
//objetc. the function checks if the received list is NULL for NULL copying
//or if the received list is the same as the this object for self copying.
LinkedList & LinkedList::operator=(const LinkedList & bt)
{
	if (bt.head == NULL) { //to check if it tries to copy NULL object
		destroyList(this->head);
		this->head = NULL;
		this->length = 0;
		return *this;
	} 
	if (head != bt.head) { //copy only if it's not self copying,
		destroyList(this->head);
		this->head = NULL;
		length = 0;
		Node* temp = bt.head;
		while (temp != NULL) {
			this->insertAtEnd(temp->data);
			temp = temp->next;
		}
	}
	return *this;
}

//a function to redefine the = operator. the function receive const btree
//objetc. the function checks if the received btree is NULL for NULL copying.
//it doesn't checks for self copying because it can't be the same object - the list and 
//the tree can't be the same object both are from different worlds.
LinkedList & LinkedList::operator=(const btree & bt)
{
	if (bt.root == NULL) {
		destroyList(this->head);
		this->head = NULL;
		length = 0;
		return *this;
	}
	destroyList(this->head);
	this->head = NULL;
	length = 0;
	treeToList(bt.root);
	return *this;
}

