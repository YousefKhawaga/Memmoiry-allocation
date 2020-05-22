#ifndef MEMMORY_H
#define MEMMORY_H

#include <map>
#include <vector>
#include <QString>
#include <struct.h>
using namespace std;





bool firstFit(int i,map<QString,int> &temp,map<int,int> &holes,map<int,indexSize> &occupied) {
    auto it = temp.begin();
    auto it2 = holes.begin();
    indexSize tempStruct;
    int temp2;
    for (int k = 0; k < holes.size(); k++)
    {
        if (it->second <= it2->second && it2->second > 0)
        {
            temp2 = it2->first + it->second;
            it2->second -= it->second;
            if (it2->second > 0)
                holes[temp2] = it2->second;
            tempStruct.index = i;
            tempStruct.size = it->second;
            tempStruct.name = it->first;
            occupied[it2->first] = tempStruct;
            temp.clear();
            holes.erase(it2);
            break;
        }
        it2++;
    }
    if (!temp.empty())
        return false;
    return true;
}

bool bestFit(int i, map<QString, int>& temp, map<int, int>& holes, map<int, indexSize>& occupied) {
    if (holes.empty())
        return false;
    auto segmentIt = temp.begin();
    auto holesIt = holes.begin();
    indexSize tempStruct;
    int temp2, holeTemp;
    auto it3 = holesIt;
    holeTemp = it3->second;
    for(int i = 1; i< holes.size();i++)
    {
        it3++;
        if (it3->second < holeTemp && segmentIt->second <= it3->second)
            holeTemp = it3->second;
    }
    for (int k = 0; k < holes.size(); k++)
    {
        if (segmentIt->second <= holesIt->second && holesIt->second > 0 && holesIt->second == holeTemp)
        {
            temp2 = holesIt->first + segmentIt->second;
            holesIt->second -= segmentIt->second;
            if (holesIt->second > 0)
                holes[temp2] = holesIt->second;
            tempStruct.index = i;
            tempStruct.size = segmentIt->second;
            tempStruct.name = segmentIt->first;
            occupied[holesIt->first] = tempStruct;
            temp.clear();
            holes.erase(holesIt);
            break;
        }
        holesIt++;
    }
    if (!temp.empty())
        return false;
    return true;
}

void deallocation(int index, map<int,int> &holes, map<int,indexSize> &occupied)
{
    auto occupiedIt = occupied.begin();
    int occupiedTemp;
    for (; occupiedIt != occupied.end();)
    {
        if (occupiedIt->second.index == index)
        {
            occupiedTemp = occupiedIt->first;
            holes[occupiedTemp] = occupiedIt->second.size;
            occupiedIt = occupied.erase(occupiedIt);   ///////////
        }
        else                   ///////////
            occupiedIt++;
    }
    auto holesIt = holes.begin();
    auto holesIt2 = holesIt;
    int holeAccumelate;
    for (int i = 1; i < holes.size(); i++)
    {
        holeAccumelate = holesIt->first + holesIt->second;
        holesIt2++;
        if (holesIt2->first == holeAccumelate)
        {
            holesIt->second += holesIt2->second;
            holesIt2 = holes.erase(holesIt2);    /////////////
        }
        holesIt++;
    }
}
#endif
