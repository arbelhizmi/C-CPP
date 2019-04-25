//
//the btree.cpp file use all the functions which define in the header file.
//the file use copy constructors(with tree and list) and = operators(with tree and list)
//and use a destructor. the file also use private function which also define in the header files.


#include <iostream>
#include "btree.h"
#include "LinkedList.h"
#include <cassert>
using namespace std;

btree::btree() {
	root = NULL;
	isMirror = false;
}

//recursive function that receive a node as a leaf of the tree, 
//and would destroy the tree leaf by leaf
void btree::destroy_tree(node *leaf)
{
	if (leaf != NULL)
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

//destructor. the destructor use the private function of destroy_tree
//which receive the root of the this object
btree::~btree()
{
	destroy_tree(root);
}

//insert function, which receive a leaf as node, and int key,
//and insert in a recursive way to the tree.
void btree::insert(int key, node * leaf)
{
	if (key < leaf->key_value)
	{
		if (leaf->left != NULL)
			insert(key, leaf->left);
		else
		{
			leaf->left = new node;
			leaf->left->key_value = key;
			leaf->left->left = NULL;    //Sets the left child of the child node to null
			leaf->left->right = NULL;   //Sets the right child of the child node to null
		}
	}
	else if (key >= leaf->key_value)
	{
		if (leaf->right != NULL)
			insert(key, leaf->right);
		else
		{
			leaf->right = new node;
			leaf->right->key_value = key;
			leaf->right->left = NULL;  //Sets the left child of the child node to null
			leaf->right->right = NULL; //Sets the right child of the child node to null
		}
	}
}

//the function use another private method which also called insert, but receive
//int key, and a node as the leaf of the tree. at the beginning we send the root of the 
//this object, and then the function called in a recursive way. we also checks the
//isMirror data member of the class btree to see if mirror function was already activated
void btree::insert(int key)
{
	if (root != NULL) {
		if (isMirror == false) {
			insert(key, root);
		}
		else {
			this->mirror();
			insert(key, root);
			this->mirror();
		}
	}
	else
	{
		root = new node;
		root->key_value = key;
		root->left = NULL;
		root->right = NULL;
	}
}

//copy constructor by tree. checks for NULL object to avoid NULL copying
btree::btree(btree &bt) { 
	if (bt.root == NULL) { //if the object bt is NULL, it means the constructor trying to copy null
		root = NULL;
	}
	else {
		root = copyTree(bt.root);
		this->isMirror = bt.isMirror;
	}
}

//private recursive function, which receive a reference of pointer, so it 
//won't copy the address - copy the valaue itself and copy in recursion way the tree
//leaf by leaf and return the new tree afterwards.
node* btree::copyTree(const node* leaf) {
	if (leaf == NULL) {
		return NULL;
	}
	node* newTree = new node();
	assert(newTree != NULL);
	newTree->key_value = leaf->key_value;
	newTree->left = copyTree(leaf->left);
	newTree->right = copyTree(leaf->right);
	return newTree;
}

//assignment of the = operator. the function receive a const of btree object.
//first checks of NULL to avoid NULL copying.
//then it checks if the btree received object different from the this object
//to avoid self copying
btree& btree::operator=(const btree& bt) {
	if (bt.root == NULL) { //a check to see it tries to copy NULL object
		destroy_tree(this->root);
		this->root = NULL;
		this->isMirror = false;
		return *this;
	}
	if (root != bt.root) { //a check to see if their is self copying
		destroy_tree(this->root);
		root = copyTree(bt.root);
		this->isMirror = bt.isMirror;
	}
	return *this;
}

//copy constructor which gets a reference to a list and build tree.
//it checks if the list is NULL to avoid self copying. it can't be the same as the this
//object for the tree, because both of them different objects
btree::btree(LinkedList &list) {
	Node* temp = list.head;
	if (temp == NULL) {
		return;
	}
	while (temp != NULL) {
		insert(temp->data);
		temp = temp->next;
	}
	this->isMirror = false;

}

//because we're creating tree from a list, it can't be the same object,
//both "living" in different worlds, we don't need to check if their is 
//self copdo in = operator
btree & btree::operator=(const LinkedList & ls)
{
	Node* temp = ls.head;
	if (temp == NULL) {
		destroy_tree(this->root);
		this->root = NULL;
		this->isMirror = false;
		return *this;
	}
	destroy_tree(this->root);
	this->root = NULL;
	this->isMirror = false;
	while (temp != NULL) {
		insert(temp->data);
		temp = temp->next;
	}
	return *this;
}

//recursive function which return os, receive os, and a node, and print
//with inorder way, the received btree from the function below
//the fucntion receive os reference and node* as leaf. 
ostream & print_inorder(ostream & os, node * dt)
{
	if (dt == NULL) {
		return os;
	}
	else {
		print_inorder(os, dt->left);
		os << dt->key_value << ",";
		print_inorder(os, dt->right);
	}
	return os;

}

//print operator for btree.
//use a private function to print the received btree object with in - order way
ostream& operator<<(ostream& os, btree& dt) {
	os << "Tree: ";
	return print_inorder(os, dt.root) << endl;
}

//the mirror function mirror the tree. makes all the right leafs - left leafs
//and all the left leafs - makes them right leafs. it change the data member "isMirror"
//it use the private method mirror_tree
void btree::mirror()
{
	if (isMirror == false) {
		isMirror = true;
	}
	else {
		isMirror = false;
	}
	mirror_tree(root);
}

//recursive function which receive a node* as leaf, and mirroring the given tree
//in a recusive way.
void btree:: mirror_tree(node* leaf) {
	if (leaf == NULL) {
		return;
	}
	else {
		node* temp;
		/* recurse to do the subtrees */
		mirror_tree(leaf->left);
		mirror_tree(leaf->right);
		/* swap the pointers in this node */
		temp = leaf->left;
		leaf->left = leaf->right;
		leaf->right = temp;
	}
}

//the functiong create a new array of lists, in the size of the depth of the tree.
//it creates index variable, and use a recursive fucntion to fill the array
//with lists of the different levels of the tree.
LinkedList * btree::Tree2linkListbyDepth()
{
	LinkedList* arr = new LinkedList[getTreeDepth()];
	int index = 0;
	byDepth(arr, this->root, index);
	return arr;
}

//recursive function which receive an array of linkedList, an node (which first time sent as root)
//and the index of the array (which first time sent as 0).
//it add the key value in the index - if it's different from NULL - and go to it's 
//most left sun, and on it's way down add the key-value to the index + 1 (the next index).
//then it does the same with the right sun. and add to the right place in the array 
void btree::byDepth(LinkedList * arr, node * leaf, int index)
{
	if (leaf == NULL) {
		return;
	}
	arr[index].add(leaf->key_value);
	byDepth(arr, leaf->left, index + 1);
	byDepth(arr, leaf->right, index + 1);
}

//a fucntion which return the depth of a tree, using recursive funcion maxDepth
//and send the root to the function
int btree::getTreeDepth()
{
	int treeDepth = 0;
	if (root != NULL) {
		treeDepth = maxDepth(root);
	}
	else {
		treeDepth = 0;
	}
	return treeDepth;
}

//recursive fucntion that get a reference to a node and return
//the depth of a given tree, assuming it receive its root for the first time
int btree::maxDepth(node *& temp)
{
	if (temp == NULL) {
		return 0;
	}
	int lchild = maxDepth(temp->left) + 1;	
	int rchild = maxDepth(temp->right) + 1;

	if (lchild <= rchild) {
		return rchild;
	}
}


