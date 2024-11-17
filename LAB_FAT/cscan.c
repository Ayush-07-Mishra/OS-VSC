#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int compare(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

void cscan(int requests[],int n,int head,int diskSize,int direction){
    int seektime = 0;
    int sorted[n+3];
    for(int i = 0;i<n;i++) sorted[i] = requests[i];
    sorted[n] = head;
    sorted[n+1] = 0;
    sorted[n+2] = diskSize - 1;

    qsort(sorted,n+3,sizeof(int),compare);
    
    int headIndex = 0;
    for(int i = 0;i<n+3;i++){
        if(sorted[i] == head){
            headIndex = i;
            break;
        }
    }
   
    printf("\nCSCAN Disk Scheduling\n");
    if(direction == 1){
        for(int i = headIndex;i<n+3;i++){
            printf("MOve from %d to %d with seektime %d\n",head,sorted[i],abs(head - sorted[i]));
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
        for(int i = headIndex -1;i>0;i--){
            printf("MOve from %d to %d with seektime %d\n",head,sorted[i],abs(head - sorted[i]));
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
    }else{
        for(int i = headIndex;i>=0;i--){
            printf("MOve from %d to %d with seektime %d\n",head,sorted[i],abs(head - sorted[i]));
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
        for(int i = headIndex+1;i<n+2;i++){
            seektime = abs(head - sorted[i]);
            printf("MOve from %d to %d with seektime %d\n",head,sorted[i],abs(head - sorted[i]));
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
    }
    printf("Seek time = %d\n",seektime);

}



int main(){
    int n,head,direction,diskSize;
    printf("number of request : ");
    scanf("%d\n",&n);
    int requests[n];

    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size: ");
    scanf("%d", &diskSize);

    printf("Enter the direction (0 - towards lower values, 1 - towards higher values): ");
    scanf("%d", &direction);

    cscan(requests, n, head, diskSize, direction);

    return 0;


}