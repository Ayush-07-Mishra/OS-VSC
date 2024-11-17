#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int sstf(int request[],int n,int head){
    int seekTime = 0;
    int visited[n];
    for(int i =0;i<n;i++) visited[i] = 0;
    printf("\nSSTF Disk Scheduling\n");
    for(int i =0;i<n;i++){
        int min = INT_MAX;
        int pos = -1;
        for(int j = 0;j<n;j++){
            if(visited[j] == 0 && abs(head - request[j]) < min){
                min = abs(head - request[j]);
                pos = j;
            }
        }
        visited[pos] = 1;
        seekTime += min;
        printf("Move from %d to %d with seek %d\n", head, request[pos], min);
        head = request[pos];
    }
    printf("Total seek time: %d\n", seekTime);
}

int main(){
    int n;
    printf("enter the number of request : ");
    scanf("%d",&n);
    int request[n];
    for(int i = 0;i<n;i++){
        scanf("%d", &request[i]);
    }
    int head;
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    sstf(request, n, head);
    return 0;
}