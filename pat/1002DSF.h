//
// Created by gary on 18-7-9.
//

#ifndef PAT_1002DSF_H
#define PAT_1002DSF_H
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

//邻接表
struct AdjNode{
    char cityName[4];
    int cost;
    AdjNode* next;
};
struct Node{
    char cityName[4];
    int happiness;
    AdjNode* first;
};
struct Graph{
    vector<Node> nodes;
    int vertex;
    int edge;
};

int hashTable[26*3];
Graph graph;
char startCity[4];
char endcity[4]={'R','O','M'};
int hashD(char* name){
    int sum=0;
    for (int i = 0; i < 3; ++i) {
        sum=sum+*(name+i);
    }
    return sum%(26*3);
};

vector<pair<queue<char*>,int >> roads;
void DFS(vector<bool> &visited,char *start,queue<char*> queue1,int cost){
    if(!strcmp(start,"ROM")){
        pair<queue<char*>,int > pair1;
        pair1.first=queue1;
        pair1.second=cost;
        roads.push_back(pair1);
        return;
    }
    visited[hashTable[hashD(start)]]=true;
    queue1.push(start);
    for (AdjNode* i =graph.nodes[hashTable[hashD(start)]].first ; i !=NULL ; i=i->next) {
        if(visited[hashTable[hashD(i->cityName)]]==false)
            DFS(visited,i->cityName,queue1,cost+i->cost);
    }
}

int DFS1002(){
    //process input
    scanf("%d%d%s",&graph.vertex,&graph.edge,startCity);
    hashTable[hashD(startCity)]=0;
    graph.nodes=vector<Node>(graph.vertex);
    graph.nodes[0].first=NULL;
    graph.nodes[0].happiness=0;
    strcpy(graph.nodes[0].cityName,startCity);
    for (int i = 1; i < graph.vertex; ++i) {
        scanf("%s%d",graph.nodes[i].cityName,&graph.nodes[i].happiness);
        graph.nodes[i].first=NULL;
        hashTable[hashD(graph.nodes[i].cityName)]=i;
    }
    for (int j = 0; j < graph.edge; ++j) {
        char start[4],end[4];
        int cost;
        scanf("%s%s%d",start,end,&cost);
        AdjNode* adjNode=(AdjNode*)malloc(sizeof(AdjNode));
        strcpy(adjNode->cityName,end);
        adjNode->cost=cost;
        adjNode->next=graph.nodes[hashTable[hashD(start)]].first;
        graph.nodes[hashTable[hashD(start)]].first=adjNode;
        AdjNode* adjNode1=(AdjNode*)malloc(sizeof(AdjNode));
        strcpy(adjNode1->cityName,start);
        adjNode1->next=graph.nodes[hashTable[hashD(end)]].first;
        adjNode1->cost=cost;
        graph.nodes[hashTable[hashD(end)]].first=adjNode1;
    };
    graph.edge*=2;

    //DFS
    vector<bool> visited(graph.vertex, false);
    queue<char*> queue1;
    DFS(visited,startCity,queue1,0);

    vector<pair<queue<char*>,int >>roads1=roads;
    int minCost=1<<27;
    for (int k = 0; k < roads1.size(); ++k) {
        if (minCost>roads1[k].second){
            minCost=roads1[k].second;
        }
    }
    int leastCost=0;
    vector<int*> indexHappinessNumAverage;
    for (int l = 0; l < roads1.size(); ++l) {
        if (minCost==(roads1[l].second)){
            int* a=(int*)malloc(sizeof(int)*4);
            a[0]=l;
            a[1]=0;a[2]=0;a[3]=0;
            while(!roads1[l].first.empty()){
                a[2]++;
                a[1]+=graph.nodes[hashTable[hashD(roads1[l].first.front())]].happiness;
                roads1[l].first.pop();
            }
            a[2];
            a[1]+=graph.nodes[hashTable[hashD(endcity)]].happiness;
            a[3]=a[1]/a[2];
            indexHappinessNumAverage.push_back(a);
        }
    }
    for (int m = 1; m < indexHappinessNumAverage.size(); ++m) {
        int a[4];
        memcpy(a,indexHappinessNumAverage[m], sizeof(a));
        int b;
        for (int i = m-1; i >=0 ; i--) {
            b=i+1;
            if (a[3]<indexHappinessNumAverage[i][3])
                memcpy(indexHappinessNumAverage[i+1],indexHappinessNumAverage[i],sizeof(a));
            else
                break;
        }
        memcpy(indexHappinessNumAverage[b],a,sizeof(a));
    }
    for (int m = 1; m < indexHappinessNumAverage.size(); ++m) {
        int a[4];
        memcpy(a,indexHappinessNumAverage[m], sizeof(a));
        int b;
        for (int i = m-1; i >=0 ; i--) {
            b=i+1;
            if (a[1]<indexHappinessNumAverage[i][1])
                memcpy(indexHappinessNumAverage[i+1],indexHappinessNumAverage[i],sizeof(a));
            else
                break;
        }
        memcpy(indexHappinessNumAverage[b],a,sizeof(a));
    }

}

#endif //PAT_1002DSF_H
