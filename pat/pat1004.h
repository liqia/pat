//
// Created by gary on 18-7-10.
//

#ifndef PAT_PAT1004_H
#define PAT_PAT1004_H

#include <iostream>
#include <string.h>
using namespace std;

int stroke[65][1290][130];
int m=0;
int n=0;
int l=0;
int t=0;

int sizeofC(int i,int j,int k){
    if (i>-1&&i<l&&j>-1&&j<m&&k>-1&&k<n&&stroke[i][j][k]!=0){
        stroke[i][j][k]=0;
        return 1+sizeofC(i-1,j,k)+sizeofC(i+1,j,k)+sizeofC(i,j+1,k)+sizeofC(i,j-1,k)+sizeofC(i,j,k-1)+sizeofC(i,j,k+1);
    } else{
        return 0;
    }
}

void pat1004(){
    scanf("%d%d%d%d",&m,&n,&l,&t);
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                scanf("%d",&stroke[i][j][k]);
            }
        }
    }
    int volume=0;
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                int num=sizeofC(i,j,k);
                if (num>=t)
                {
                    volume+=num;
                }
            }
        }
    }
    cout<<volume;

}

#endif //PAT_PAT1004_H
