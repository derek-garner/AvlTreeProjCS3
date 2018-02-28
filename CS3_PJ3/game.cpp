#include "Game.h"
#include "avlTreeLadder.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <time.h>
using namespace std;

//Constructor for wordStore object
WordStore::WordStore(){
	word = "";
	used = false;
}

WordStore::WordStore(string insertWord){
	word = insertWord;
	used = false;
}

bool compareByWordValue(const WordStore & a, const WordStore & b) {
	return  b.word > a.word;
}

bool compareByWordValuePos(const WordPos & a, const WordPos & b)
{
	return  b.word > a.word;
}



//Method to check for solution in ladders
bool Game::findSolutionDLL(string firstWord, string secondWord) {
	Node* curr = ladderList.head;

	//Temporary while loop fix to stop out of bounds
	while (curr != NULL) {
		for (int i = 0; i < curr->wordladder.size(); i++) {
			if (curr->wordladder[i] == secondWord) {
				cout << "Solution Found"<< endl;
				cout << firstWord<<" ";
				for (int j = 0; j < curr->wordladder.size(); j++) {
					cout << curr->wordladder[j]<<" ";
				}
				cout << endl;
				cout << "Brute Ladders enqueued " << bruteLaddersEnqueued<<endl;
				cout << "Brute Ladders dequeued " << bruteLaddersDequeued<<endl;

				return true;
			}
		}
		curr = curr->next;
	}
	return false;
}

//Game constructor
Game::Game(string file) {
	fullDictionaryLength = 0;
	ifstream fin(file);
	fin.clear();

	while (!fin.eof()) {
		WordStore temp;
		getline(fin, temp.word);
		fullDictionary.push_back(temp);
		fullDictionaryLength++;
	}
	//Sort used to ensure words are searchable by their numerical value
	sort(fullDictionary.begin(), fullDictionary.end(), compareByWordValue);
	cout << "Dictionary loaded " << fullDictionaryLength << " words." << endl;
};

//Method to search dictionary for word,
bool Game::findWordMarkUsed(int dictionaryLength, string firstWord, vector<WordStore> &dictionary) {

	int low = 0;
	int high = dictionaryLength - 1;
	int mid;
	while (low <= high) {

		mid = low + (high - low) / 2;
		if (dictionary[mid].word == firstWord) {
			if (dictionary[mid].used == false) {
				dictionary[mid].used = true;
				return true;
			}
			return false;
		}
		else if (dictionary[mid].word < firstWord) {
			low = mid + 1;
		}
		else if (dictionary[mid].word>firstWord) {
			high = mid - 1;
		}
	}
	return false;
}
//Same as findWordMarkUsed but doesnt mark dictionary or check for marked word
bool Game::findWord(int dictionaryLength, string firstWord, vector<WordStore> &dictionary) {

	int low = 0;
	int high = dictionaryLength - 1;
	int mid;
	while (low <= high) {

		mid = low + (high - low) / 2;
		if (dictionary[mid].word == firstWord) {
			return true;
		}
		else if (dictionary[mid].word < firstWord) {
			low = mid + 1;
		}
		else if (dictionary[mid].word>firstWord) {
			high = mid - 1;
		}
	}
	return false;
}

//Method to list first ten words in dictionary as a test
void Game::listWords() {
	cout << "Printing first 10 words of dictionary as test: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << fullDictionary[i].word << endl;
	}
}

//Runs doublyLinkedList solution
void Game::playDLL(string firstWord) {
	srand(time(NULL));
	int firstWordLength;
	string secondWord;
	shortDictionaryLength = 0;
	firstWordLength = firstWord.length();
	for (int i = 0; i < fullDictionaryLength; i++) {
		fullDictionary[i].used = false;
		if (fullDictionary[i].word.length() == firstWord.length()) {
			shortDictionary.push_back(fullDictionary[i]);
			shortDictionaryLength++;
		}
	}
	firstWord = shortDictionary[rand() % shortDictionaryLength - 1].word;
	secondWord = shortDictionary[rand() % shortDictionaryLength - 1].word;

	playDLL(firstWord, secondWord);

}

//Produces word ladder when taking in two strings as parameters
//Checks for valid words
void Game::playDLL(string firstWord, string secondWord) {

	if(checkWordsCreateDiction(firstWord, secondWord))
	{
	buildLadderDLL(firstWord, secondWord);
	findSolutionDLL(firstWord, secondWord); 
	}
	
}

//Checks words for validity and creates both long and short dictionary
bool Game::checkWordsCreateDiction(string firstWord, string secondWord) {
	bool soulution = false;
	int lettersInAlpha = 26;
	shortDictionaryLength = 0;
	shortDictionary.clear();
	ladderList.clear();

	cout << "==============Testing words: " << firstWord << " " << secondWord << "==================" << endl;
	if (firstWord.length() != secondWord.length()) {
		cout << "Words are not the same length!\n" << endl;
		return false;
	}
	if (!findWordMarkUsed(fullDictionaryLength, firstWord, fullDictionary)) {
		cout << "First word not found in dictionary" << endl;
		if (!findWordMarkUsed(fullDictionaryLength, secondWord, fullDictionary))
			cout << "and second word not found in dictionary\n" << endl;
		return false;
	}
	if (!findWordMarkUsed(fullDictionaryLength, secondWord, fullDictionary)) {
		cout << "Second word not found in dictionary\n" << endl;
		return false;
	}
	for (int i = 0; i < fullDictionaryLength; i++) {
		fullDictionary[i].used = false;
		if (fullDictionary[i].word.length() == firstWord.length()) {
			shortDictionary.push_back(fullDictionary[i]);
			shortDictionaryLength++;
			shortDictionary[shortDictionaryLength - 1].used = false;
		}
	}
	return true;
}

//Method to build all ladders in attempt to find solution
void Game::buildLadderDLL(string firstWord, string secondWord) {
	string tempFirstWord = firstWord;
	int lettersInAlpha = 26;
	bool solutionFoundFirst = false;
	

	//Create initial ladders check for all 1 way words for head of each ladder
	for (int i = 0; i < firstWord.length(); i++) {
		for (int j = 97; j < lettersInAlpha + 97; j++) {
			tempFirstWord[i] = j;

			if (findWordMarkUsed(shortDictionaryLength, tempFirstWord, shortDictionary)) {
				ladderList.addToTail(tempFirstWord);
				bruteLaddersEnqueued++;
				if (tempFirstWord == secondWord) solutionFoundFirst = true;
			}
		}
		tempFirstWord = firstWord;
	}
	if (solutionFoundFirst) {
		ladderList.printEachItem();
		return;
	}

	//Build subsequent steps for each ladder until solution found
	//or no new steps for any ladder can be created
	//Below only executes if the ladder isn't solved in one step

	int stepInLadder = 0;
	int newSteps = 0;
	bool currFound = false;
	bool noLadder = false;
	//ladderList.printEachItem();

	Node* curr = ladderList.head;
	string tempWord;
	while (!noLadder) {
		curr = ladderList.head;
		currFound = false;
		newSteps = 0;
		while (curr != NULL) {
			stepInLadder = curr->wordladder.size();
			stepInLadder--;
			tempWord = curr->wordladder[stepInLadder];

			for (int i = 0; i < firstWord.length(); i++) {
				for (int j = 97; j < lettersInAlpha + 97; j++) {
					tempWord[i] = j;

					if (currFound == false) {
						if (findWordMarkUsed(shortDictionaryLength, tempWord, shortDictionary)) {
							curr->wordladder.push_back(tempWord);
							currFound = true;
							newSteps++;
							if (tempWord == secondWord) {
								cout << " Enqueued:" << bruteLaddersEnqueued << " Dequeued: " << bruteLaddersDequeued << endl;
								return;
							}
						}
					}
					else if (findWordMarkUsed(shortDictionaryLength, tempWord, shortDictionary)) {
						bruteLaddersEnqueued++;
						ladderList.addToTail(curr->wordladder[0]);
						for (int i = 1; i < curr->wordladder.size(); i++) {
							ladderList.tail->wordladder.push_back(curr->wordladder[i]);
						}

						ladderList.tail->wordladder.push_back(tempWord);
						if (tempWord == secondWord)return;
						currFound = true;
						newSteps++;
					}
				}
				tempWord = curr->wordladder[stepInLadder];
			}
			bruteLaddersDequeued++;
			curr = curr->next;
		}
		if (newSteps == 0) noLadder = true;
	}
	cout << "No Ladder Found" <<" Enqueued:"<< bruteLaddersEnqueued <<" Dequeued: "<< bruteLaddersDequeued <<endl;
}

//Part 1 test remove, display tree
void Game::avlTestandDisplay() {
	AvlPriorityWord<int> avlTestLadder;
	avlTestLadder.insert(1);
	avlTestLadder.insert(3);
	avlTestLadder.insert(5);
	avlTestLadder.insert(7);
	avlTestLadder.insert(9);
	avlTestLadder.insert(9);
	avlTestLadder.insert(9);
	avlTestLadder.insert(2);
	avlTestLadder.insert(9);
	avlTestLadder.insert(4);
	avlTestLadder.insert(8);
	avlTestLadder.remove(7);
	avlTestLadder.remove(9);
	cout << avlTestLadder.toString();
	avlTestLadder.removeMin();
	cout << avlTestLadder.toString();
	avlTestLadder.removeMin();
	cout << avlTestLadder.toString();
	avlTestLadder.removeMin();
	cout << avlTestLadder.toString();
	avlTestLadder.insert(17);
	cout << avlTestLadder.toString();
}
bool Game::intitFirstLaddersAVL(string firstWord, string secondWord) {

	string tempFirstWord = firstWord;
	int lettersInAlpha = 26;
	bool solutionFoundFirst = false;

	//Create initial ladders check for all 1 way words for head of each ladder
	for (int i = 0; i < firstWord.length(); i++) {
		for (int j = 97; j < lettersInAlpha + 97; j++) {
			tempFirstWord[i] = j;

			if (findWordMarkUsed(shortDictionaryLength, tempFirstWord, shortDictionary)&&tempFirstWord!=firstWord) {
				wordPosition.emplace_back(tempFirstWord);
				wordPosition[wordPosition.size() - 1].pos = 0;
				int tempPriority = 0;
				WordLadderState temp = WordLadderState(tempFirstWord);
				//Check priority
				for (int g = 0; g < firstWord.length(); g++) {
					if (tempFirstWord[g] != secondWord[g]) {
						tempPriority++;
					}	
				}
				temp.priority = tempPriority;
				avlLadder.insert(temp);
				greedyLaddersEnqueued++;
				if (tempFirstWord == secondWord) solutionFoundFirst = true;
			}
		}
		tempFirstWord = firstWord;
	}
	if (solutionFoundFirst) {
		return true;
	}
	return false;
}


//Solve for using AVL priority queue, reduces total number of ladders enqueued by only never
//using words that have been previously used in a better position
bool Game::solveItAVL(string firstWord, string secondWord, bool solveFirstTime,int priority)
{
	//cout << firstWord << " ";
	bool noSolution = true;
	int lettersInAlpha = 26;
	//Case for solve on first try
	if (solveFirstTime) {
		avlLadder.traverse = avlLadder.root;
		while (avlLadder.traverse->left != NULL) {
			avlLadder.traverse = avlLadder.traverse->left;
		}
		cout << "Solution: \n" << firstWord<<endl;
		avlLadder.minToString();
		cout << endl;
	}
	else {
		while (avlLadder.root!=NULL) {
			bool wordInCurrLadder = false;
			//cout << "PRINT Ladder:\n";
			//cout << firstWord << " ";
			WordLadderState curr;
			curr = avlLadder.findMin();
			avlLadder.removeMin();
			greedyLaddersDequeued++;
			//cout << curr << endl;
			string tempWord = curr.wordLadder[curr.wordLadder.size() - 1];
			for (int i = 0; i < firstWord.length(); i++) {
				tempWord = curr.wordLadder[curr.wordLadder.size() - 1];
				for (int j = 97; j < lettersInAlpha + 97; j++) {
					tempWord[i] = j;
				
					//Check for valid word and if word previously used in a better position,
					if (findWord(shortDictionaryLength, tempWord, shortDictionary)) {
						if (avlPosCheck(tempWord, wordPosition) <= curr.wordLadder.size() - 1) {
							wordInCurrLadder = true;
						}
						// if value returns -1
						//word is previously unused
						if (avlPosCheck(tempWord, wordPosition) ==-1) {
							wordInCurrLadder = false;
							wordPosition.push_back(WordPos(tempWord, curr.wordLadder.size()));
							
						}
						//Check if word already used in current ladder
						for (int i = 0; i < curr.wordLadder.size(); i++) {
							if (tempWord == curr.wordLadder[i])
								wordInCurrLadder = true;
						}
						if (tempWord == firstWord)wordInCurrLadder = true;
						//Check priority with current word which is (work Done) + (min Work) needed				
						int toInsertPriority = curr.wordLadder.size()+1;
						for (int i = 0; i < firstWord.size(); i++) {
							if (tempWord[i] != secondWord[i])toInsertPriority++;
						}
						vector<string> wordLadderInsert = curr.wordLadder;
						wordLadderInsert.push_back(tempWord);
						WordLadderState toBeInserted = WordLadderState(wordLadderInsert, toInsertPriority);
						if (!wordInCurrLadder&&toInsertPriority<=curr.priority+1) {
							greedyLaddersEnqueued++;
							avlLadder.insert(toBeInserted);
						}
							wordInCurrLadder = false;
						//If Solution found, print ladder and return
						if (tempWord == secondWord) {
							cout <<"Solution: "<<firstWord<<" "<< toBeInserted << endl;
							cout << "Greedy Ladders Dequeued: " << greedyLaddersDequeued<<" "<<endl;
							cout << "Greedy Ladders Enqueued: " << greedyLaddersEnqueued << " "<<endl;
							return true;
						}
					}
				}
			}	
		}
		cout << "No solution" << endl;
		return false;
	}
}
//Runs AVL solution
void Game::playAVL(string firstWord, string secondWord)
{
	bool solutionFirstTime = false;
	wordPosition.clear();
	if (checkWordsCreateDiction(firstWord, secondWord)) {
		solutionFirstTime = intitFirstLaddersAVL(firstWord, secondWord);
		solveItAVL(firstWord, secondWord, solutionFirstTime);
	}
	
}

//Linear search used for checking if word have been used in
//better position, greatly reducing number of ladders enqueued
int Game::avlPosCheck(string word,vector<WordPos> wordPos){
	for (int i = 0; i < wordPos.size(); i++) {
		if (word == wordPos[i].word) {
			return wordPos[i].pos;
		}
	}
	 return -1;
}

//Runs both DoublyLinkedList solution from first assignment and AVL tree solution
void Game::play(string firstWord, string secondWord) {
	playDLL(firstWord, secondWord);
	playAVL(firstWord, secondWord);
}