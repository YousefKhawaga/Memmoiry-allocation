#include <list>
#include <string>
#include <mainwindow.h>
using namespace std;

struct properties {
    double arrivalTime;
    double burstTime;
    int priority;
    int index;
    double startTime;
};

bool compareArrivalTime(const properties& a, const properties& b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurstTime(const properties& a, const properties& b) {
    return a.burstTime < b.burstTime;
}

bool comparePriority(const properties& a, const properties& b) {
    return a.priority < b.priority;
}

double avwt(list<properties> temp2, list<properties> process, int numberOfProcesses)
{
    list<properties>::iterator it3;
    list<properties>::reverse_iterator it;
    double ft, arv, burs;
    double avwt = 0;
    it = temp2.rbegin();
    for (int i = 1; i <= numberOfProcesses; i++)
    {
        it = temp2.rbegin();

        for (; it != temp2.rend(); it++)
        {
            if (i == it->index)
            {

                ft = it->startTime + it->burstTime;
                break;
            }

        }

        it3 = process.begin();
        for (; it3 != process.end();)
        {
            if (i == it3->index)
            {
                burs = it3->burstTime;
                arv = it3->arrivalTime;
                break;
            }
            it3++;
        }
        avwt = avwt + (ft - arv - burs);
    }
    avwt = avwt / numberOfProcesses;
    return avwt;
}


 list<properties> Calc(int numberOfProcesses, QString type, double q, QList<QDoubleSpinBox*> Arrival, QList<QDoubleSpinBox*> Burst, QList<QDoubleSpinBox*> Priority,double& avg) {
    list<properties> process, temp2, temp;
    list<properties>::iterator it, it2, it3;
    properties property;
    double  propertyTemp;
    for (int i = 0; i < numberOfProcesses; i++)
    {
        property.arrivalTime = Arrival[i]->value();
        property.burstTime = Burst[i]->value();
        if(type == "Non Preemptive Priority" || type == "Preemptive Priority")
            property.priority = Priority[i]->value();
        property.index = i + 1;
        process.push_back(property);
    }
    if (type == "FCFS" || type == "fcfs")
    {
        double sum;
        process.sort(compareArrivalTime);
        temp = process;
        it = temp.begin();
        sum = it->arrivalTime;
        it->startTime = it->arrivalTime;
        for (int i = 0; i < temp.size(); i++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            sum = (it2->arrivalTime > (it->startTime + it->burstTime)) ? sum + it->burstTime + it2->arrivalTime - (it->startTime + it->burstTime) : sum + it->burstTime;
            it2->startTime = (it2->arrivalTime > (it->startTime + it->burstTime)) ? it2->arrivalTime : sum;
            it++;
        }
        // law feh process fadya
        if (temp.begin()->startTime > 0)
        {
            property.arrivalTime = property.startTime = 0;
            property.burstTime = temp.begin()->startTime;
            property.index = -1;
            temp.insert(temp.begin(), property);
        }
        for (it = temp.begin(); it != temp.end(); it++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            if (it2->startTime - it->startTime > it->burstTime)
            {
                property.burstTime = it2->startTime - (it->startTime + it->burstTime);
                property.arrivalTime = property.startTime = it2->startTime - property.burstTime;
                property.index = -1;
                temp.insert(it2, property);
            }
        }
    }

    else if (type == "Non Preemptive SJF" || type == "n")
    {
        process.sort(compareArrivalTime);
        double sum = 0;
        double initialTime, referenceArrival, timeNow = 0;
        bool flag = false;
        it = process.begin();
        sum = it->arrivalTime;
        for (int i = 0; i < numberOfProcesses; i++)
        {
            it2 = it;
            it2++;
            //sum += (it2 == process.end())? it->burstTime : (it2->arrivalTime > (it->arrivalTime + it->burstTime))? it2->arrivalTime - it->arrivalTime : it->burstTime;
            sum = (it2 == process.end()) ? (sum + it->burstTime) : (it2->arrivalTime > (sum + it->burstTime)) ? it2->arrivalTime : (sum + it->burstTime);
            it++;
        }
        it = process.begin();
        timeNow = referenceArrival = initialTime = it->arrivalTime;
        while (timeNow - sum > 0.00001 || sum - timeNow > 0.00001)
        {
            for (; it != process.end(); it++)
            {
                if (it->arrivalTime <= timeNow)
                {
                    property.arrivalTime = it->arrivalTime;
                    property.index = it->index;
                    property.burstTime = it->burstTime;
                    temp2.push_back(property);
                }
                else break;
            }
            if (it == process.end())
                flag = true;
            else
                referenceArrival = it->arrivalTime;
            temp2.sort(compareBurstTime);
            while ((timeNow < referenceArrival || flag) && !temp2.empty())
            {
                timeNow += temp2.begin()->burstTime;
                property.arrivalTime = temp2.begin()->arrivalTime;
                property.index = temp2.begin()->index;
                property.burstTime = temp2.begin()->burstTime;
                temp.push_back(property);
                temp2.erase(temp2.begin());
                //////
                if (temp2.empty() && timeNow < referenceArrival)
                {
                    property.arrivalTime = timeNow;
                    property.index = -1;
                    property.burstTime = referenceArrival - timeNow;
                    temp.push_back(property);
                    timeNow += property.burstTime;
                }
                //////
            }
        }
        it = temp.begin();
        sum = it->arrivalTime;
        it->startTime = it->arrivalTime;
        for (int i = 0; i < temp.size(); i++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            sum = (it2->arrivalTime > (it->startTime + it->burstTime)) ? sum + it->burstTime + it2->arrivalTime - (it->startTime + it->burstTime) : sum + it->burstTime;
            it2->startTime = (it2->arrivalTime > (it->startTime + it->burstTime)) ? it2->arrivalTime : sum;
            it++;
        }
        // law feh process fadya
        if (temp.begin()->startTime > 0)
        {
            property.arrivalTime = property.startTime = 0;
            property.burstTime = temp.begin()->startTime;
            property.index = -1;
            temp.insert(temp.begin(), property);
        }
        for (it = temp.begin(); it != temp.end(); it++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            if (it2->startTime - it->startTime > it->burstTime)
            {
                property.burstTime = it2->startTime - (it->startTime + it->burstTime);
                property.arrivalTime = property.startTime = it2->startTime - property.burstTime;
                property.index = -1;
                temp.insert(it2, property);
            }
        }
    }

    else if (type == "Preemptive SJF" || type == "s")
    {
        process.sort(compareArrivalTime);
        double sum = 0;
        double initialTime, referenceArrival, timeNow = 0;
        bool flag = false;
        it = process.begin();
        sum = it->arrivalTime;
        for (int i = 0; i < numberOfProcesses; i++)
        {
            it2 = it;
            it2++;
            sum = (it2 == process.end()) ? (sum + it->burstTime) : (it2->arrivalTime > (sum + it->burstTime)) ? it2->arrivalTime : (sum + it->burstTime);
            it++;
        }
        it = process.begin();
        timeNow = initialTime = referenceArrival = it->arrivalTime;
        while (timeNow - sum > 0.00001 || sum - timeNow > 0.00001)
        {
            for (; it != process.end(); it++)
            {
                if (it->arrivalTime <= timeNow)
                {
                    property.arrivalTime = it->arrivalTime;
                    property.index = it->index;
                    property.burstTime = it->burstTime;
                    temp2.push_back(property);
                }
                else break;
            }
            if (it == process.end())
                flag = true;
            else
                referenceArrival = it->arrivalTime;
            temp2.sort(compareBurstTime);
            while ((timeNow < referenceArrival || flag) && !temp2.empty())
            {
                if ((timeNow + temp2.begin()->burstTime > referenceArrival) && !flag)
                {
                    property.burstTime = referenceArrival - timeNow;
                    property.arrivalTime = temp2.begin()->arrivalTime;
                    property.index = temp2.begin()->index;
                    temp.push_back(property);
                    temp2.begin()->burstTime -= (referenceArrival - timeNow);
                    timeNow += referenceArrival - timeNow;
                }
                else
                {
                    timeNow += temp2.begin()->burstTime;
                    property.burstTime = temp2.begin()->burstTime;
                    property.arrivalTime = temp2.begin()->arrivalTime;
                    property.index = temp2.begin()->index;
                    temp.push_back(property);
                    temp2.erase(temp2.begin());
                    if (temp2.empty() && timeNow < referenceArrival)
                    {
                        property.arrivalTime = timeNow;
                        property.index = -1;
                        property.burstTime = referenceArrival - timeNow;
                        temp.push_back(property);
                        timeNow += property.burstTime;
                    }
                }
            }
        }
        it = temp.begin();
        sum = it->arrivalTime;
        it->startTime = it->arrivalTime;
        for (int i = 0; i < temp.size(); i++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            sum = (it2->arrivalTime > (it->startTime + it->burstTime)) ? sum + it->burstTime + it2->arrivalTime - (it->startTime + it->burstTime) : sum + it->burstTime;
            it2->startTime = (it2->arrivalTime > (it->startTime + it->burstTime)) ? it2->arrivalTime : sum;
            it++;
        }
        // law feh process fadya
        if (temp.begin()->startTime > 0)
        {
            property.arrivalTime = property.startTime = 0;
            property.burstTime = temp.begin()->startTime;
            property.index = -1;
            temp.insert(temp.begin(), property);
        }
        for (it = temp.begin(); it != temp.end(); it++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            if (it2->startTime - it->startTime > it->burstTime)
            {
                property.burstTime = it2->startTime - (it->startTime + it->burstTime);
                property.arrivalTime = property.startTime = it2->startTime - property.burstTime;
                property.index = -1;
                temp.insert(it2, property);
            }
        }
    }
    else if (type == "RR" || type == "rr")
    {
        process.sort(compareArrivalTime);
        int counter = 0;
        double sum = 0, a;
        double initialTime, referenceArrival, lastArrival, timeNow = 0;
        bool flag = false;
        lastArrival = process.back().arrivalTime;
        it = process.begin();
        sum = it->arrivalTime;
        for (int i = 0; i < numberOfProcesses; i++)
        {
            it2 = it;
            it2++;
            sum = (it2 == process.end()) ? (sum + it->burstTime) : (it2->arrivalTime > (sum + it->burstTime)) ? it2->arrivalTime : (sum + it->burstTime);
            it++;
        }
        it = process.begin();
        timeNow = referenceArrival = initialTime = it->arrivalTime;
        while (timeNow - sum > 0.00001 || sum - timeNow > 0.00001)
        {
            for (int i = 0; it != process.end(); it++, i++)
            {
                if (it->arrivalTime <= timeNow)
                {
                    property.arrivalTime = it->arrivalTime;
                    property.index = it->index;
                    property.burstTime = it->burstTime;
                    if (i == 0)
                    {
                        temp2.push_front(property);
                        it2 = temp2.begin();
                        it2++;
                    }
                    else		temp2.insert(it2, property);
                }
                else break;
            }
            if (it == process.end())
                flag = true;
            else
                referenceArrival = it->arrivalTime;
            counter = 0;
            it2 = temp2.begin();
            do
            {
                if (it2 != temp2.end())
                {
                    if (it2->burstTime > 0.0001)
                    {
                        property.arrivalTime = it2->arrivalTime;
                        property.index = it2->index;
                        property.burstTime = (q >= it2->burstTime) ? it2->burstTime : q;
                        timeNow += property.burstTime;
                        if (q > it2->burstTime)
                        {
                            it2 = temp2.erase(it2);
                            ///////
                            if (temp2.empty() && timeNow < referenceArrival)
                            {
                                property.arrivalTime = timeNow;
                                property.index = -1;
                                property.burstTime = referenceArrival - timeNow;
                                timeNow += property.burstTime;
                            }
                            //////
                        }
                        else
                        {
                            it2->burstTime -= q;
                            it2++;
                        }
                        temp.push_back(property);
                    }
                    else
                    {
                        it2 = temp2.erase(it2);
                        /////
                        if (temp2.empty() && timeNow < referenceArrival)
                        {
                            property.arrivalTime = timeNow;
                            property.index = -1;
                            property.burstTime = referenceArrival - timeNow;
                            temp.push_back(property);
                            timeNow += property.burstTime;
                        }
                        /////
                    }
                }
                else
                    it2 = temp2.begin();
            } while ((counter != temp2.size() || flag) && (timeNow < referenceArrival || (flag && timeNow >= lastArrival)) && !temp2.empty());
        }
        it = temp.begin();
        sum = it->arrivalTime;
        it->startTime = it->arrivalTime;
        for (int i = 0; i < temp.size(); i++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            sum = (it2->arrivalTime > (it->startTime + it->burstTime)) ? sum + it->burstTime + it2->arrivalTime - (it->startTime + it->burstTime) : sum + it->burstTime;
            it2->startTime = (it2->arrivalTime > (it->startTime + it->burstTime)) ? it2->arrivalTime : sum;
            it++;
        }
        // law feh process fadya
        if (temp.begin()->startTime > 0)
        {
            property.arrivalTime = property.startTime = 0;
            property.burstTime = temp.begin()->startTime;
            property.index = -1;
            temp.insert(temp.begin(), property);
        }
        for (it = temp.begin(); it != temp.end(); it++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            if (it2->startTime - it->startTime > it->burstTime)
            {
                property.burstTime = it2->startTime - (it->startTime + it->burstTime);
                property.arrivalTime = property.startTime = it2->startTime - property.burstTime;
                property.index = -1;
                temp.insert(it2, property);
            }
        }
    }

    else if (type == "Non Preemptive Priority" || type == "t")
    {
        process.sort(compareArrivalTime);
        double sum = 0;
        double initialTime, referenceArrival, timeNow = 0;
        bool flag = false;
        it = process.begin();
        sum = it->arrivalTime;
        for (int i = 0; i < numberOfProcesses; i++)
        {
            it2 = it;
            it2++;
            sum = (it2 == process.end()) ? (sum + it->burstTime) :
                  (it2->arrivalTime > (sum + it->burstTime)) ? it2->arrivalTime : (sum + it->burstTime);
            it++;
        }
        it = process.begin();
        timeNow = referenceArrival = initialTime = it->arrivalTime;
        while (timeNow - sum > 0.00001 || sum - timeNow > 0.00001)
        {
            for (; it != process.end(); it++)
            {
                if (it->arrivalTime <= timeNow)
                {
                    property.arrivalTime = it->arrivalTime;
                    property.index = it->index;
                    property.burstTime = it->burstTime;
                    property.priority = it->priority;
                    temp2.push_back(property);
                }
                else break;
            }
            if (it == process.end())
                flag = true;
            else
                referenceArrival = it->arrivalTime;
            temp2.sort(comparePriority);
            while ((timeNow < referenceArrival || flag) && !temp2.empty())
            {
                timeNow += temp2.begin()->burstTime;
                property.arrivalTime = temp2.begin()->arrivalTime;
                property.index = temp2.begin()->index;
                property.burstTime = temp2.begin()->burstTime;
                property.priority = temp2.begin()->priority;
                temp.push_back(property);
                temp2.erase(temp2.begin());
                if (temp2.empty() && timeNow < referenceArrival)
                {
                    property.arrivalTime = timeNow;
                    property.index = -1;
                    property.burstTime = referenceArrival - timeNow;
                    temp.push_back(property);
                    timeNow += property.burstTime;
                }
            }
        }
        it = temp.begin();
        sum = it->arrivalTime;
        it->startTime = it->arrivalTime;
        for (int i = 0; i < temp.size(); i++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            sum = (it2->arrivalTime > (it->startTime + it->burstTime)) ? sum + it->burstTime + it2->arrivalTime - (it->startTime + it->burstTime) : sum + it->burstTime;
            it2->startTime = (it2->arrivalTime > (it->startTime + it->burstTime)) ? it2->arrivalTime : sum;
            it++;
        }
        // law feh process fadya
        if (temp.begin()->startTime > 0)
        {
            property.arrivalTime = property.startTime = 0;
            property.burstTime = temp.begin()->startTime;
            property.index = -1;
            temp.insert(temp.begin(), property);
        }
        for (it = temp.begin(); it != temp.end(); it++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            if (it2->startTime - it->startTime > it->burstTime)
            {
                property.burstTime = it2->startTime - (it->startTime + it->burstTime);
                property.arrivalTime = property.startTime = it2->startTime - property.burstTime;
                property.index = -1;
                temp.insert(it2, property);
            }
        }
    }

    else if (type == "Preemptive Priority" || type == "p")
    {
        process.sort(compareArrivalTime);
        double sum = 0, lastArrival = process.back().arrivalTime;
        int counter = 0, referencePriority;
        double initialTime, referenceArrival, timeNow = 0;
        bool flag = false;
        it = process.begin();
        sum = it->arrivalTime;
        for (int i = 0; i < numberOfProcesses; i++)
        {
            it2 = it;
            it2++;
            sum = (it2 == process.end()) ? (sum + it->burstTime) : (it2->arrivalTime > (sum + it->burstTime)) ? it2->arrivalTime : (sum + it->burstTime);
            it++;
        }
        it = process.begin();
        timeNow = referenceArrival = initialTime = it->arrivalTime;
        while (timeNow - sum > 0.00001 || sum - timeNow > 0.00001)
        {
            for (int i = 0; it != process.end(); it++, i++)
            {
                if (it->arrivalTime <= timeNow)
                {
                    property.arrivalTime = it->arrivalTime;
                    property.index = it->index;
                    property.burstTime = it->burstTime;
                    property.priority = it->priority;
                    if (i == 0)
                    {
                        temp2.push_front(property);
                        it2 = temp2.begin();
                        it2++;
                    }
                    else		temp2.insert(it2, property);
                }
                else break;
            }
            if (it == process.end())
                flag = true;
            else
                referenceArrival = it->arrivalTime;
            temp2.sort(comparePriority);
            while ((timeNow < referenceArrival || flag) && !temp2.empty())
            {
                it2 = temp2.begin();
                referencePriority = it2->priority;
                do
                {
                    if (it2 != temp2.end())
                    {
                        if (it2->burstTime > 0.0001)
                        {
                            property.arrivalTime = it2->arrivalTime;
                            property.index = it2->index;
                            property.burstTime = (q >= it2->burstTime) ? it2->burstTime : q;
                            property.priority = it2->priority;
                            timeNow += property.burstTime;
                            if (q > it2->burstTime)
                            {
                                it2 = temp2.erase(it2);
                                if (temp2.empty() && timeNow < referenceArrival)
                                {
                                    property.arrivalTime = timeNow;
                                    property.index = -1;
                                    property.burstTime = referenceArrival - timeNow;
                                    timeNow += property.burstTime;
                                }
                            }
                            else
                            {
                                it2->burstTime -= q;
                                it2++;
                            }
                            temp.push_back(property);
                        }
                        else
                        {
                            it2 = temp2.erase(it2);
                            if (temp2.empty() && timeNow < referenceArrival)
                            {
                                property.arrivalTime = timeNow;
                                property.index = -1;
                                property.burstTime = referenceArrival - timeNow;
                                temp.push_back(property);
                                timeNow += property.burstTime;
                            }
                        }
                    }
                    else
                        it2 = temp2.begin();
                    if (it2 != temp2.end())
                        if (it2->priority > referencePriority)
                            break;
                } while ((timeNow < referenceArrival || flag) && !temp2.empty());
            }
        }
        it = temp.begin();
        sum = it->arrivalTime;
        it->startTime = it->arrivalTime;
        for (int i = 0; i < temp.size(); i++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            sum = (it2->arrivalTime > (it->startTime + it->burstTime)) ? sum + it->burstTime + it2->arrivalTime - (it->startTime + it->burstTime) : sum + it->burstTime;
            it2->startTime = (it2->arrivalTime > (it->startTime + it->burstTime)) ? it2->arrivalTime : sum;
            it++;
        }
        // law feh process fadya
        if (temp.begin()->startTime > 0)
        {
            property.arrivalTime = property.startTime = 0;
            property.burstTime = temp.begin()->startTime;
            property.index = -1;
            temp.insert(temp.begin(), property);
        }
        for (it = temp.begin(); it != temp.end(); it++)
        {
            it2 = it;
            it2++;
            if (it2 == temp.end()) break;
            if (it2->startTime - it->startTime > it->burstTime)
            {
                property.burstTime = it2->startTime - (it->startTime + it->burstTime);
                property.arrivalTime = property.startTime = it2->startTime - property.burstTime;
                property.index = -1;
                temp.insert(it2, property);
            }
        }
    }

    avg = avwt(temp, process, numberOfProcesses) ;
    return temp;
}
