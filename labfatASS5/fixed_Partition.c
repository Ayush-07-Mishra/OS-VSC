#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


void firstfit(int blockSize[],int m ,int processSize[],int n){
    int allocation[n];
    int blockUsed[m];

    for(int i = 0;i<n;i++) allocation[i] = -1;
    for(int i =0;i<n;i++) blockUsed[i] = 0;

    for(int i =0;i<n;i++){
        for(int j =0;j<m;j++){
            if(blockUsed[i] == 0 && blockSize[j] >= processSize){
                allocation[i] = j;
                blockUsed[j] = 1;
                break;
            }
        }
    }
    printf("First Fit allocation\n");
    for(int i =0;i<n;i++){
        if(allocation[i] != -1){
            printf("process %d allocated to block %d\n",i+1,allocated[i]+1);
        }
        else{
            printf("process %d not allocated\n",i+1);
        }
    }
}


void bestfit(int blockSize[],int m,int processSize[],int n){
    int allocation[n];
    int blockUsed[m];

    for(int i =0;i<n;i++) allocation[i] = -1;
    for(int i =0;i<m;i++) blockUsed[i] = 0;

    for(int i =0;i<n;i++){
        int bestIdx = -1;
        for(int j =0;j<m;j++){
            if(blockUsed[j]==0 && processSize[i] <= blockSize[j]){
                if(bestIdx == -1 || blockSize[j] < blockSize[bestIdx]){
                    bestIdx = j;
                }
            }
        }
        if(bestIdx != -1){
            allocation[i] = bestIdx;
            blockUsed[bestIdx] = 1;
        }
    }

    printf("\nBest Fit allocation\n");
    for(int i =0;i<n;i++){
        if(allocation != -1){
            printf("process %d allocated to block %d \n",i+1,allocation[i]);
        }else{
            printf("process %d not allocated\n",i+1);
        }
    }
}

void worstFit(int blockSize[],int m,int processSize[],int n){
    int allocation[n];
    int blockUsed[m];

    for(int i =0;i<n;i++) allocation[i] = -1;
    for(int i =0;i<m;i++) blockUsed[i] = 0;

    for(int i = 0;i<n;i++){
        int worstIdx = -1;
        for(int j =0;j<m;j++){
            if(blockUsed == 0 && blocksize[j] >= processSize[i]){
                if(worstIdx == -1 || blockSize[j] > blockSize[worstIdx]){
                    worstIdx = j;
                }
            }
        }
        if(worstIdx != -1){
            allocation[i] = worstIdx;
            blockUsed[worstIdx] = 1;
        }
    }

    printf("\nWorst Fit Allocation:\n");
    for(int i =0;i<n;i++){
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}