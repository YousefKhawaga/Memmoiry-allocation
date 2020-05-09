#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "Trie.h"


using namespace std;
namespace fs = std::filesystem;


int main()
{
    Trie* head = new Trie();
    string x;
    ifstream inFile;
    string path = "C:/Users/youse/OneDrive/Desktop/questions/0.txt";
    inFile.open(path);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (inFile >> x) {
        head->insert(x,path);
    }
    list<string> paths = head->search("What");
    for (auto i = paths.begin(); i != paths.end(); i++)
    {
        cout << *i << endl;
    }
    //for (const auto& entry : fs::directory_iterator(path))
       // cout << entry.path() << endl;

}
