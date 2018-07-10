//
// Created by gary on 18-7-10.
//

#ifndef PAT_PAT1006_H
#define PAT_PAT1006_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;
struct timeStatus{
    int hours;
    int minutes;
    int seconds;
    bool status;
    timeStatus operator+(const timeStatus &a){
        timeStatus timeStatus1;
        timeStatus1.hours=this->hours+a.hours;
        timeStatus1.minutes=this->minutes+a.minutes;
        timeStatus1.seconds=this->seconds+a.seconds;
        return timeStatus1;
    }
    bool operator>(const timeStatus &a){
        if ((this->hours)>a.hours)
            return true;
        else if((this->hours)==a.hours){
            if (this->minutes>a.minutes)
                return true;
            else if (this->minutes==a.minutes)
                if (this->seconds>a.seconds)
                    return true;
        }
        return false;
    }
};
map<string,vector<timeStatus>> map1;
void pat1006(){
    int records,queries;
    scanf("%d%d",&records,&queries);
    for (int i = 0; i < records; ++i) {
        string plate,timeD,status;
        timeStatus timeStatus1;
        char a[8],b[9],c[4];
        scanf("%s%s%s",a,b,c);
        plate=a;
        timeD=b;
        status=c;
        sscanf(timeD.substr(0,2).c_str(),"%d",&timeStatus1.hours);
        sscanf(timeD.substr(3,2).c_str(),"%d",&timeStatus1.minutes);
        sscanf(timeD.substr(6,2).c_str(),"%d",&timeStatus1.seconds);
        if (status.compare("in")==0){
            timeStatus1.status=true;
        } else
            timeStatus1.status=false;
        map1[plate].push_back(timeStatus1);
    }
    vector<string> queryTimes;
    for (int j = 0; j < queries; ++j) {
        string a;
        scanf("%s",&a);
        queryTimes.push_back(a);
    }

}

#endif //PAT_PAT1006_H
