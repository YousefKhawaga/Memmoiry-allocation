#include "Trie.h"
#include <QString>


using namespace std;

Trie::Trie()
{
    this->isLeaf = false;

    for (int i = 0; i < CHAR_SIZE; i++)
        this->character[i] = nullptr;
}
void Trie::insert(QString key,QString path)
{
    // start from root node
    if (path == "C:\\Users\\youse\\OneDrive\\Desktop\\questions\\10446.txt")
    {
        int i = 0;
    }
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // create a new node if path doesn't exists
        unsigned char x = key.at(i).toLatin1();
        if (curr->character[x] == nullptr)
            curr->character[x] = new Trie();

        // go to next node
        curr = curr->character[x];
    }

    // mark current node as leaf
    curr->isLeaf = true;
//    if (!curr->path.contains(path))
        curr->path.push_back(path);
}

// Iterative function to search a key in Trie. It returns true
// if the key is found in the Trie, else it returns false
QStringList Trie::search(QString key)
{
    // return false if Trie is empty
    if (this == nullptr)
        return {};

    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // go to next node
        curr = curr->character[key.at(i).toLatin1()];

        // if QString is invalid (reached end of path in Trie)
        if (curr == nullptr)
            return {};
    }

    // if current node is a leaf and we have reached the
    // end of the QString, return true
    return curr->path;
}

// returns true if given node has any children
