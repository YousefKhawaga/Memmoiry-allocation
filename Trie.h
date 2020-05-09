#pragma once
#include <string>
#include <list>

// define character size
#define CHAR_SIZE 128

using namespace std;
// A Class representing a Trie node
class Trie
{
private:

	bool isLeaf;
	Trie* character[CHAR_SIZE];
	list<string> path;
public:
	// Constructor
	Trie();

	void insert(string,string);
	bool deletion(Trie*&, string);
	list<string> search(string);
	bool haveChildren(Trie const*);
};

// Iterative function to insert a key in the Trie
