//
//the file btree.h define struce ode with the data members of node* right, node* left and int key value.
//it also have a class of btree with the data member node* root for the root of the tree,
//and the boolean "isMirror" to know if mirror function was activated.
//in the file can be found method which defined for us in the assignment, and private method 
//i created to use in the cpp file. explanation for each method can be found in the cpp file

#pragma once
#include <iostream>
class LinkedList;
#ifndef _BTREE_H
#define _BTREE_H
//#include "LinkedList.h"

using namespace std;

 typedef struct node
{
	int key_value;
	node *left;
	node *right;
} node;

class btree
{
	node* root;
	bool isMirror;
	friend class LinkedList;
	node* copyTree(const node* leaf);
	void destroy_tree(node *leaf);
	void insert(int key, node *leaf);
	friend ostream& print_inorder(ostream& os, node* dt);
	void mirror_tree(node* node);
	int maxDepth(node *& temp);
	void byDepth(LinkedList* arr, node* leaf, int index);
public:
	
	// Default constructor
	btree();
	~btree();

	// Copy Constructor by list
	btree(LinkedList &list);

	// Copy Constructor by tree
	btree(btree & bt);

	// assignment operator from linked list
	btree & operator=(const LinkedList & ls);

	// assignment operator from tree
	btree& operator=(const btree &bt);

	// insert new value to binary tree
	void insert(int key);

	// mirror the tree
	void mirror();

	LinkedList* Tree2linkListbyDepth();
	int getTreeDepth();

	// print tree (in order)
	friend ostream& operator<<(ostream& os, btree& dt);
};

#endif //_BTREE_H

