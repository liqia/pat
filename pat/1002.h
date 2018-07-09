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
int hash(string cityName){//用于快速根据名字找到城市在cityList中的位置
    int sum=0;
    for (int i = 0; i < cityName.size(); ++i) {
        sum=cityName[i]+sum;
    }
    return sum%(26*3);
}

void pat1002(){
    //process input
     string startCity;
     scanf("%d%d%s",&alGraph.vertex,&alGraph.edge,&startCity);
     alGraph.nodes.at(0).city=startCity;
     alGraph.nodes.at(0).happiness=0;
     hashTable[hash(startCity)]=0;
    for (int i = 1; i < alGraph.vertex; ++i) {
        scanf("%s%d",&alGraph.nodes.at(i).city,&alGraph.nodes.at(i).happiness);
        hashTable[hash(alGraph.nodes.at(i).city)]=i;
        alGraph.nodes.at(i).first=NULL;
    }
    for (int j = 0; j < alGraph.edge; ++j) {
        ArcNode* arcNode=(ArcNode*) sizeof(ArcNode);
        string start,end;
        int cost;
        scanf("%s%s%d",&start,&end,&cost);
        arcNode->adjCity=end;
        arcNode->cost=cost;
        arcNode->next=alGraph.nodes.at(hashTable[hash(start)]).first;
        alGraph.nodes.at(hashTable[hash(start)]).first=arcNode;
    }

    //dijkstra
    vector<int> cost(alGraph.vertex,1<<29);
    cost.at(hashTable[hash(startCity)])=0;
    struct name_cost{
        string name;
        int cost;
        bool operator > (name_cost &a,name_cost &b){
            return a.cost>b.cost;
        }
        bool operator < (name_cost &a,name_cost &b){
            return a.cost<b.cost;
        }

        void operator = (name_cost &a, name_cost &b){
            a.name=b.name;
            a.cost=b.cost;
        }
    };
    priority_queue<name_cost,vector<name_cost>,greater<name_cost>> priorityQueue;
    name_cost nameCost;
    nameCost.cost=0;
    nameCost.name=startCity;
    priorityQueue.push(nameCost);
    while(!priorityQueue.empty()){
        nameCost=priorityQueue.top();
    }
}


#endif //PAT_1002_H
