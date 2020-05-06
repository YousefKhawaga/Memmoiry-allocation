
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int main(void)
{
	int memorySize,numberOfHoles,numberOfProcesses,numberOfSegments;
	cin>>memorySize;
	cin>>numberOfHoles;
	map<int,int> holes;//(starting address, size)
	map<int,map<string,int>> processes;//(index of process,name of segment, size of segment)
	//map<int,int> occupied;//(starting address, size of segment)
	int temp1,temp2;
	for(int i=0;i<numberOfHoles;i++)
	{
		cin>>temp1;
		cin>>temp2;
		holes[temp1]=temp2;
	}
	cin>>numberOfProcesses;

	for(int i=0;i<numberOfProcesses;i++)
	{
		cin>>numberOfSegments;
		for(int j=0;j<numberOfSegments;j++)
		{
			map<string,int> temp;
			string strTemp;
			cin>>strTemp>>temp1;
			temp[strTemp]=temp1;
			processes[i]=temp;
			auto it=temp.begin();
			auto it2=holes.begin();
			for(int k=0;k<numberOfHoles;k++)
			{
				if(it->second<=it2->second)
				{
					temp2=it2->first+it->second;
					it2->second-=it->second;
					holes[temp2]=it2->second;
					holes.erase(it2);
					cout<<it2->first<<"    "<<it->second<<endl;
					if(it2->second==0)
					{
						holes.erase(it2);
					}
					temp.clear();
					break;
				}
				it2++;	// mehtagin n5ls el deallocatation

			}
			if(!temp.empty())
			{
				cout<<"Holes don't fit"<<endl;
			}
		}
	}




}
