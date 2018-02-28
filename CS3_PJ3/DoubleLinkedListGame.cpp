#include "DoubleLinkedListGame.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <time.h>
using namespace std;

Node::Node(string wordInsert, Node * anext, Node * aprev) {
	next = NULL;
	prev = NULL;
	wordladder.push_back(wordInsert);
}


//Method to add an item to end of list
void DoublyLinkedList::addToTail(string insertWord) {
	Node* n = new Node(insertWord, head, tail);
	size++;
	if (isEmpty()) {

		head = n;
		tail = n;
		return;
	}
	else {
		tail->next = n;
		tail = n;
	}
}

//Method to remove from tail
void DoublyLinkedList::remove() {
	if (isEmpty()) return;

	if (head->next == NULL) {
		delete head;
		head = NULL;
		tail = NULL;
		return;
	}
	Node* curr = head;
	while (curr->next != tail) {
		curr = curr->next;
	}
	delete tail;
	curr->next = NULL;
	tail = curr;
	return;
}

//Method to clear the list
void DoublyLinkedList::clear() {
	while (!isEmpty()) {
		remove();
	}
}

//Print the top of each Ladder, or the 
void DoublyLinkedList::printEachItem() {
	Node* curr = head;
	cout << "Displaying all one letter away possibilities: \n";
	while (curr != NULL) {
		cout << curr->wordladder[0] << endl;

		curr = curr->next;
	}
	//cout << endl;
	return;
}
