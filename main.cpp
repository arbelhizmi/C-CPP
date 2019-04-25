//
//the main use functions and methods from the LinkedList and btree files.
//specification for methods and funcitons can be found in the other files

#include <iostream>
#include "btree.h"
#include "LinkedList.h"
using namespace std;

int main() {
	btree *tree = new btree();
	tree->insert(10);
	tree->insert(6);
	tree->insert(14);
	tree->insert(5);
	tree->insert(8);
	tree->insert(12);
	tree->insert(16);
	LinkedList* l = tree->Tree2linkListbyDepth();
	int dp = tree->getTreeDepth();
	for (int i = 0; i < dp; i++) {
		cout << l[i];
	}
	cout << *tree;
	tree->mirror();
	cout << *tree;
	btree *tree1 = new btree(l[dp - 1]);
	cout << *tree1;
	btree *tree2 = new btree(*tree1);
	tree2->insert(100);
	cout << *tree1;
	cout << *tree2;
	LinkedList* l1 = new LinkedList(*tree1);
	LinkedList* l2 = new LinkedList(*l1);
	l2->add(99); cout << *l1;
	cout << *l2;
	delete tree;

	return 0;
}
