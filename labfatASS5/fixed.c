#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void firstFit(int blockSize[], int m,int processSize[] ,int n){
    int allocation[n];
    int blockUsed[m];

    for(int i = 0;i<n;i++) allocation[i] = -1;
    for(int i = 0;i<m;i++) blockUsed[i] = 0;

    for(int i= 0;i<n;i++){
        for(int j =0;j<m;j++){
            if(blockUsed[j] == 0 && blockSize[j] >= processSize[i]){
                allocation[i] = j;
                blockUsed[j] = 1;
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation :\n");
    for(int i =0;i<n;i++){
        if(allocation[i] != -1)
            printf("Process %d allocated to Block %d\n",i+1,allocation[i] + 1);
        else   
            printf("Process %d not allocated\n",i+1);
    }
}


void bestfit(int blockSize[],int m,int processSize[],int n){
    int allocation[n];
    int blockUsed[m];

    int bestIdx;

    for(int i = 0;i<n;i++) allocation[i] = -1;
    for(int i =0;i<m;i++) blockUsed[i] = 0;

    for(int i = 0;i<n;i++){
        bestIdx = -1;
        for(int j = 0;j<m;j++){
            if(blockUsed[j] == 0 && blockSize[j] >= processSize[i]){
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
    for(int i = 0;i<n;i++){
        if(allocation != -1){
            printf("Process %d allocated to Block %d\n",i+1,allocation[i]+1);
        }else{
            printf("Process %d not allocated\n",i+1);
        }
    }

}


void worstFit(int blockSize[],int m,int processSize[],int n){
    int allocation[n];
    int blockUsed[m];

    int worstIdx;
    for(int i = 0 ;i<n;i++) allocation[i] = -1;
    for(int i = 0;i<m;i++) blockUsed[i] = 0;

    for(int i = 0;i<n;i++){
        worstIdx = -1;
        for(int j = 0;j<m;j++){
            if(blockUsed[j] == 0 && blockSize[j] >= processSize[i]){
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
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }

}

int main(){
    int m, n;

    // Get block sizes from user
    printf("Enter the number of blocks: ");
    scanf("%d", &m);
    int blockSize[m];
    printf("Enter the sizes of %d blocks:\n", m);
    for (int i = 0; i < m; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Get process sizes from user
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter the sizes of %d processes:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // First Fit Allocation
    firstFit(blockSize, m, processSize, n);

    // Reset block usage for next allocation method
    printf("\n");
    bestfit(blockSize, m, processSize, n);

    // Reset block usage for next allocation method
    printf("\n");
    worstFit(blockSize, m, processSize, n);

    return 0;
}