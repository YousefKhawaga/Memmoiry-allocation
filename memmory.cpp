
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;


struct indexSize {
	int index;
	int size;
};

void firstFit(int i, int numberOfHoles, map<string, int> &temp, map<int, int> &holes, map<int, indexSize> &occupied);

void bestFit(int i, int numberOfHoles, map<string, int>& temp, map<int, int>& holes, map<int, indexSize>& occupied);

int main(void)
{
	int memorySize, numberOfHoles, numberOfProcesses, numberOfSegments;
	cin >> memorySize;
	cin >> numberOfHoles;
	map<int, int> holes;//(starting address, size)
	map<int, map<string, int>> processes;//(index of process,name of segment, size of segment)
	map<int, indexSize> occupied;//(starting address, size of segment)
	int temp1, temp2;
	for (int i = 0; i < numberOfHoles; i++)
	{
		cin >> temp1;
		cin >> temp2;
		holes[temp1] = temp2;
	}
	cin >> numberOfProcesses;

	for (int i = 0; i < numberOfProcesses; i++)
	{
		cin >> numberOfSegments;
		for (int j = 0; j < numberOfSegments; j++)
		{
			map<string, int> temp;
			string strTemp;
			cin >> strTemp >> temp1;
			temp[strTemp] = temp1;
			processes[i] = temp;
			numberOfHoles = holes.size();
			bestFit(i, numberOfHoles, temp, holes, occupied);
		}
	}
}


	void firstFit(int i, int numberOfHoles,map<string,int> &temp,map<int,int> &holes,map<int,indexSize> &occupied) {
		auto it = temp.begin();
		auto it2 = holes.begin();
		indexSize tempStruct;
		int temp2;
		for (int k = 0; k < numberOfHoles; k++)
		{
			if (it->second <= it2->second && it2->second > 0)
			{
				temp2 = it2->first + it->second;
				it2->second -= it->second;
				if (it2->second > 0)
					holes[temp2] = it2->second;
				tempStruct.index = i;
				tempStruct.size = it->second;
				occupied[it2->first] = tempStruct;
				cout << it2->first << "    " << it->second << endl;
				temp.clear();
				holes.erase(it2);
				break;
			}
			it2++;	// mehtagin n5ls el deallocatation
		}
		if (!temp.empty())
		{
			cout << "Holes don't fit" << endl;
		}
	}

	void bestFit(int i, int numberOfHoles, map<string, int>& temp, map<int, int>& holes, map<int, indexSize>& occupied) {
		auto segmentIt = temp.begin();
		auto holesIt = holes.begin();
		indexSize tempStruct;
		int temp2, holeTemp;
		auto it3 = holesIt;
		for(int i = 1; i<numberOfHoles;i++)
		{
			holeTemp = it3->second;
			it3++;
			if (it3->second < holeTemp && segmentIt->second <= it3->second)
				holeTemp = it3->second;
		} 
		for (int k = 0; k < numberOfHoles; k++)
		{
			if (segmentIt->second <= holesIt->second && holesIt->second > 0 && holesIt->second == holeTemp)
			{
				temp2 = holesIt->first + segmentIt->second;
				holesIt->second -= segmentIt->second;
				if (holesIt->second > 0)
					holes[temp2] = holesIt->second;
				tempStruct.index = i;
				tempStruct.size = segmentIt->second;
				occupied[holesIt->first] = tempStruct;
				cout << holesIt->first << "    " << segmentIt->second << endl;
				temp.clear();
				holes.erase(holesIt);
				break;
			}
			holesIt++;	// mehtagin n5ls el deallocatation
		}
		if (!temp.empty())
		{
			cout << "Holes don't fit" << endl;
		}
	}
