#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <queue>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;


int main()
{
	map<string,queue<int>> invertedIndex;



    string path = "C:/Users/Seif/Desktop/Talta Comp/2nd Term/Data Structures/questions/questions";
    for (const auto & entry : fs::directory_iterator(path))
        cout << entry.path() << endl;

}
