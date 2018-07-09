//
// Created by gary on 18-7-8.
//

#ifndef PAT_1002_H
#define PAT_1002_H

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct ArcNode{
    string adjCity;
    int cost;
    ArcNode* next;
};
struct VNode{
    string city;
    int happiness;
    ArcNode* first;
};
struct ALGraph{
    vector<VNode> nodes;
    int vertex;
    int edge;
};
ALGraph alGraph;

int hashTable[26*3];
int hashF(string cityName){//用于快速根据名字找到城市在cityList中的位置
    int sum=0;
    for (int i = 0; i < cityName.size(); ++i) {
        sum=cityName[i]+sum;
    }
    return sum%(26*3);
}

void pat1002(){
    //process input
     string startCity;
     char city[4];
     scanf("%d%d%s",&alGraph.vertex,&alGraph.edge,city);
     startCity=city;
     alGraph.nodes.resize(alGraph.vertex);
     alGraph.nodes.at(0).city=startCity;
     alGraph.nodes.at(0).happiness=0;
     hashTable[hashF(startCity)]=0;
    for (int i = 1; i < alGraph.vertex; ++i) {
        scanf("%s%d",city,&alGraph.nodes.at(i).happiness);
        alGraph.nodes.at(i).city=city;
        hashTable[hashF(alGraph.nodes.at(i).city)]=i;
        alGraph.nodes.at(i).first=NULL;
    }
    for (int j = 0; j < alGraph.edge; ++j) {
        ArcNode* arcNode=(ArcNode*)malloc(sizeof(ArcNode));
        char start[4],end[4];
        int cost;
        scanf("%s%s%d",start,end,&cost);
        arcNode->adjCity=end;
        arcNode->cost=cost;
        arcNode->next=alGraph.nodes.at(hashTable[hashF(start)]).first;
        alGraph.nodes.at(hashTable[hashF(start)]).first=arcNode;
    }

    //dijkstra
    vector<int> cost(alGraph.vertex,1<<29);
    cost.at(hashTable[hashF(startCity)])=0;
    struct name_cost{
        string name;
        int cost;
        string fatherName;
        bool operator > (name_cost a) const {
            return cost>a.cost;
        }
        bool operator < (name_cost a) const {
            return a.cost > cost;
        }
    };
    priority_queue<name_cost,vector<name_cost>,greater<name_cost>> priorityQueue;
    vector<name_cost> costList(alGraph.vertex);
    costList[0].name=startCity;
    costList[0].cost=0;
    costList[0].fatherName="NOT";
    for (int k = 1; k < alGraph.vertex; ++k) {
        costList[k].cost=1<<30;
        costList[k].fatherName="NOT";
    }
    priorityQueue.push(costList[0]);
    while(!priorityQueue.empty()){
        name_cost nameCost;
        nameCost=priorityQueue.top();priorityQueue.pop();
        if (nameCost.name=="ROM"){
            break;
        }
        ArcNode* first=alGraph.nodes.at(hashTable[hashF(nameCost.name)]).first;
        while(first!=NULL){
            if (nameCost.cost+first->cost < costList[hashTable[hashF(first->adjCity)]].cost) {
                costList[hashTable[hashF(first->adjCity)]].cost=nameCost.cost+first->cost;
                costList[hashTable[hashF(first->adjCity)]].name=first->adjCity;
                costList[hashTable[hashF(first->adjCity)]].fatherName=nameCost.name;
                priorityQueue.push(costList[hashTable[hashF(first->adjCity)]]);
            }
            first=first->next;
        }
    }
}


#endif //PAT_1002_H
