//
// Created by gary on 18-7-8.
//

#ifndef PAT_1002_H
#define PAT_1002_H

#include <iostream>
#include <vector>
using namespace std;

struct ArcNode{
    string adjCity;
    int cost;
    ArcNode* next;
};
struct VNode{
    string city;
    ArcNode* first;
};
struct ALGraph{
    vector<VNode> nodes;
    int vertex;
    int edge;
};
ALGraph alGraph;
typedef pair<string,int> CityHappiness;
vector<CityHappiness> cityList;

int hashTable[26*3];
int hash(string cityName){//用于快速根据名字找到城市在cityList中的位置
    int sum=0;
    for (int i = 0; i < cityName.size(); ++i) {
        sum=cityName[i]+sum;
    }
    return sum%(26*3);
}

void pat1002(){
     CityHappiness cityHappiness;
     scanf("%d%d%s",&alGraph.vertex,&alGraph.edge,&cityHappiness.first);
     cityHappiness.second=0;
     cityList.push_back(cityHappiness);
     hashTable[hash(cityHappiness.first)]=0;
    for (int i = 0; i < alGraph.vertex- 1; ++i) {
        scanf("%s%d",&cityHappiness.first,&cityHappiness.second);
        cityList.push_back(cityHappiness);
        hashTable[hash(cityHappiness.first)]=i+1;
    }
    for (int j = 0; j < alGraph.edge; ++j) {
        ArcNode* arcNode=(ArcNode*) sizeof(ArcNode);
        string start,end;
        int cost;
        scanf("%s%s%d",&start,&end,&cost);
        alGraph.nodes.at(hashTable[hash(start)]).city=start;
        arcNode->adjCity=end;
        arcNode->cost=cost;
        arcNode->next=alGraph.nodes.at(hashTable[hash(start)]).first;
        alGraph.nodes.at(hashTable[hash(start)]).first=arcNode;
    }
}


#endif //PAT_1002_H
