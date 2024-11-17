#include<stdio.h>

struct PCB{
    int pid,AT,BT,CT,TAT,WT,RT;
};

int main(){
    struct PCB p[10];
    int n;
    printf("Enter the number of process : ");
    scanf("%d",&n);

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].pid= i + 1;
        p[i].RT = p[i].BT; // Initialize remaining time
    }
    int tq;
    printf("Enter Time Qunatum: ");
    scanf("%d", &tq);
    int time = 0;
    int completed = 0;
    while(completed < n){
        for(int i = 0;i<n;i++){
            if(p[i].AT <= time && p[i].RT > 0){
                if(p[i].RT > tq){
                    time += tq;
                    p[i].RT -= tq;
                }else{
                    time += p[i].RT;
                    p[i].RT = 0;
                    p[i].CT = time;
                    p[i].TAT = p[i].CT - p[i].AT;
                    p[i].WT = p[i].TAT - p[i].BT;
                    completed++;
                }
            }
        }
    }

}