//
//the file LinkedList.h define class Node with the data members of Node* next, and int data.
//it also have a class of LinkedList with the data members of int length, and Node* for the head 
//of the list as a pointer.
//in the file can be found method which defined for us in the assignment, and private method 
//i created to use in the cpp file. explanation for each method can be found in the cpp file

#pragma once
#include <iostream>
#ifndef _LinkedList_h
#define _LinkedList_h
#include "btree.h"
class btree;
using namespace std;

class Node
{
public:
	Node* next;
	int data;
};


class LinkedList
{
	friend class btree;
	void treeToList(node *tree);
	void insertAtEnd(int data);
	void destroyList(Node* head);

public:
	int length;
	Node* head;

	LinkedList(btree &bt);
	LinkedList(LinkedList &bt);

	LinkedList();
	~LinkedList();

	void add(int data);
	LinkedList & operator=(const LinkedList & bt);
	LinkedList& operator=(const btree &bt); 
	friend ostream& operator<<(ostream& os, LinkedList& l);
};

#endif //_LinkedList_h



