#include <string>
#include <vector>
#include <iostream>

using namespace std;
#ifndef DOUBLELINKEDLISTGAME_H
#define DOUBLELINKEDLISTGAME_H

//Used for entries into dictionary

class Node {
public:
	vector<string> wordladder;
	Node* next;
	Node* prev;
	Node(string word, Node* newNext = NULL, Node* newPrev = NULL);
};

class DoublyLinkedList {
public:
	int size;
	Node* head;
	Node* tail;

	DoublyLinkedList() {
		head = NULL;
		size = 0;
		tail = NULL;
	}
	void addToTail(string x);
	void remove();
	void clear();
	bool isEmpty() { return head == NULL; }
	void printEachItem();
	
};

#endif
