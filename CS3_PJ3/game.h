#include <string>
#include <vector>
#include <iostream>
#include "DoubleLinkedListGame.h"
#include "avlTreeLadder.h"

using namespace std; 
//word stored in dictionary via WordStore
class WordStore {
public:
	WordStore();
	WordStore(string insertWord);
	string word;
	bool used;
	friend bool compareByWordValue(const WordStore &a, const WordStore &b);
};

//Stores words best used postion, used with AVL solution
struct WordPos{
public:
	WordPos() {}
	WordPos(string toWord) {
		word = toWord;
	}
	WordPos(string toWord,int position) {
		word = toWord;
		pos = position;
	}
	string word;
	int pos;
	friend bool compareByWordValuePos(const WordPos &a, const WordPos &b);
};


//Method to compare the words via their integer value
//Used with binary search

class Game {
public:
	// Constructor loads dictionary into vector
	Game(string file);

	//Method to list first ten words as a test for dictionary
	void listWords();
	void playDLL(string firstWord);
	void playDLL(string firstWord, string secondWord);
	bool checkWordsCreateDiction(string firstWord, string secondWord);
	void buildLadderDLL(string firstWord, string secondWord);
	bool findWordMarkUsed(int dictionaryLength, string firstWord, vector<WordStore> &dictionary);
	bool findWord(int dictionaryLength, string firstWord, vector<WordStore>& dictionary);
	bool findSolutionDLL(string firstWord, string secondWord = NULL);
	

	vector<WordStore> fullDictionary;
	vector<WordStore> shortDictionary;

	void avlTestandDisplay();
	void playAVL(string firstWord, string secondWord);

	int avlPosCheck(string word,vector<WordPos>);

	void play(string firstWord, string secondWord);

	bool intitFirstLaddersAVL(string firstWord, string secondWord);


	int fullDictionaryLength;
	int shortDictionaryLength;
	DoublyLinkedList ladderList;
	bool solveItAVL(string firstWord, string secondWord, bool solveFirstTime, int priority = 0);
	
	AvlPriorityWord<WordLadderState> avlLadder;
	vector<WordPos> wordPosition;
	int bruteLaddersEnqueued = 0;
	int bruteLaddersDequeued = 0;
	int greedyLaddersEnqueued = 0;
	int greedyLaddersDequeued = 0;
};