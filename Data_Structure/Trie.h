#pragma once
#include <QString>
#include <QStringList>

// define character size
#define CHAR_SIZE 256

using namespace std;
// A Class representing a Trie node
class Trie
{
private:

	bool isLeaf;
	Trie* character[CHAR_SIZE];
    QStringList path;
public:
	// Constructor
	Trie();

    void insert(QString,QString);
    QStringList search(QString);
};

// Iterative function to insert a key in the Trie
