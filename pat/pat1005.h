//
// Created by gary on 18-7-10.
//

#ifndef PAT_PAT1005_H
#define PAT_PAT1005_H

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int tree[101][101];
void pat1005(){
    memset(tree,0, sizeof(tree));
    int parents;
    int whole;
    scanf("%d%d",&whole,&parents);
    for (int i = 0; i < parents; ++i) {
        int index,childs;
        scanf("%d%d",&index,&childs);
        tree[index][0]=childs;
        while (childs!=0){
            scanf("%d",&tree[index][childs]);
            childs--;
        }
    }
    queue<int> queue1;
    queue1.push(1);
    int maxNum=0;
    int maxGeneration=0;
    int generation=0;
    while(!queue1.empty()){
        generation++;
        int num=queue1.size();
        if (num>maxNum){
            maxGeneration=generation;
            maxNum=num;
        }
        for (int i = 0; i < num; ++i) {
            int a=queue1.front();
            queue1.pop();
            for (int j = 1; j <= tree[a][0]; ++j) {
                queue1.push(tree[a][j]);
            }
        }
    }
    cout<<maxNum<<" "<<maxGeneration;
}

#endif //PAT_PAT1005_H
