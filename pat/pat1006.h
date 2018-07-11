//
// Created by gary on 18-7-10.
//

#ifndef PAT_PAT1006_H
#define PAT_PAT1006_H

#include <iostream>
#include <map>
#include <cstring>
#include <algorithm>
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
    timeStatus operator-(const timeStatus &a){
        timeStatus timeStatus1;
        timeStatus1.hours=this->hours-a.hours;
        timeStatus1.minutes=this->minutes-a.minutes;
        timeStatus1.seconds=this->seconds-a.seconds;
        return timeStatus1;
    }
    timeStatus operator=(const timeStatus &a){
        timeStatus timeStatus1;
        timeStatus1.hours=a.hours;
        timeStatus1.minutes=a.minutes;
        timeStatus1.seconds=a.seconds;
        return timeStatus1;
    }
    bool operator>(const timeStatus a){
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

    bool operator<(const timeStatus a){
        if ((this->hours)<a.hours)
            return true;
        else if((this->hours)==a.hours){
            if (this->minutes<a.minutes)
                return true;
            else if (this->minutes==a.minutes)
                if (this->seconds<a.seconds)
                    return true;
        }
        return false;
    }
};
bool comp(const timeStatus &a, const timeStatus &b){
    if ((a.hours)>b.hours)
        return true;
    else if((a.hours)==b.hours){
        if (a.minutes>b.minutes)
            return true;
        else if (a.minutes==b.minutes)
            if (a.seconds>b.seconds)
                return true;
    }
    return false;
}

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
    vector<timeStatus> queryTimes;
    for (int j = 0; j < queries; ++j) {
        char b[9];
        scanf("%s",b);
        string a=b;
        timeStatus timeStatus1;
        sscanf(a.substr(0,2).c_str(),"%d",&timeStatus1.hours);
        sscanf(a.substr(3,2).c_str(),"%d",&timeStatus1.minutes);
        sscanf(a.substr(6,2).c_str(),"%d",&timeStatus1.seconds);
        queryTimes.push_back(timeStatus1);
    }
    vector<timeStatus> a=map1.begin()->second;
    sort(a.begin(),a.end(),comp);
    vector<map<string,vector<timeStatus>>::iterator> deletes;
    for (map<string,vector<timeStatus>>::iterator iter = map1.begin() ;iter!=map1.end();iter++) {
        sort(iter->second.begin(),iter->second.end());
        int a=0;
        for (int i = 0; i < iter->second.size(); ++i) {
            if (iter->second[i].status== true){
                a++;
            } else{
                a--;
            }
            if (abs(a)>1){
                deletes.push_back(iter);
                break;
            }
        }
    }
    for (int m = 0; m < deletes.size(); ++m) {
        map1.erase(deletes[m]);
    }
    int carNum[100];
    memset(carNum,0,sizeof(carNum));
    map<string,timeStatus> parkTimes;
    for (int k = 0; k < queryTimes.size(); ++k) {
        for (map<string,vector<timeStatus>>::iterator iter = map1.begin() ;iter!=map1.end();iter++) {
            for (int i = 0; i < iter->second.size(); ++i) {
                if (iter->second[i]<queryTimes[k]){
                    carNum[k]+=iter->second[i].status== true?1:-1;
                }
            }
            timeStatus parktime;
            parktime.seconds=0;
            parktime.minutes=0;
            parktime.hours=0;
            for (int j = 0; j < iter->second.size(); j+=2) {
                parktime=parktime+iter->second[j+1]-iter->second[j];
            }
        }
    }
    for (int l = 0; l < queryTimes.size(); ++l) {
        cout<<carNum[l]<<endl;
    }
}

#endif //PAT_PAT1006_H
