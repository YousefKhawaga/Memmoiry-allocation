//#include <iostream>
//#include <string>
//#include <fstream>
//#include <filesystem>
//#include "Trie.h"


//using namespace std;
//namespace fs = std::filesystem;


////int main()
////{
////    Trie* head = new Trie();
////    string x;
////    ifstream inFile;
////    string path = "C:\\Users\\youse\\OneDrive\\Desktop\\questions";
////	int i = 0;
////	for (const auto& entry : fs::directory_iterator(path))
////	{
////		inFile.open(entry.path());
////		if (!inFile) {
////			cout << entry.path();
////			exit(1); // terminate with error
////		}
////		while (inFile >> x)
////			head->insert(x, entry.path().string());
////		inFile.close();
////		i++;
////	}
////	list<string> paths = head->search("What");
////	for (auto i = paths.begin(); i != paths.end(); i++)
////	{
////		cout << *i << endl;
////	}
////    //for (const auto& entry : fs::directory_iterator(path))
////       // cout << entry.path() << endl;

////}
