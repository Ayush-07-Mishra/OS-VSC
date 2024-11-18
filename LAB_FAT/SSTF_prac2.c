#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int sstf(int request[],int n,int head){
    int seektime = 0;
    int visited[n];

    for(int i = 0;i<n;i++) visited[i] = 0;

    for(int i =0;i<n;i++){
        int min = INT_MAX;
        int pos = -1;
        for(int j =0;j<n;j++){
            if(visited[j] == 0 && abs(head - request) < min){
                min = abs(head - request);
                pos = j;
            }
        }
        visited[pos] = 1;
        seekTime += min;
        head = request[pos];
    }
}