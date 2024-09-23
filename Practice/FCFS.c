#include<stdio.h>

struct PCB{
    int pid,AT,BT,CT,TAT,WT;
};

int main(){
    struct PCB p[10];
    struct PCB temp;
    int n;
    printf("Enter the number of process : ");
    scanf("%d",&n);
    for(int i =0;i<n;i++){
        printf("Enter Arrival time and Burst time for process id %d: ", i+1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].pid = i + 1;
    }

    for(int i =0;i<n-1;i++){
        for(int j =0;j<n-1-i;i++){
            if(p[j].AT > p[j+1].AT){
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    p[0].CT = p[0].BT + p[0].AT;
    p[0].TAT = p[0].CT - p[0].AT;
    p[0].WT = p[0].TAT - p[0].BT;

    for(int i =1;i<n;i++){
        if(p[i].AT > p[i-1].CT){
            p[i].CT = p[i].AT + p[i].BT;
        }else{
            p[i].CT = p[i-1].CT + p[i].BT;
        }
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
    }

    float sumTAT = 0.0;
    float sumWT = 0.0;
    for(int i =0;i<n;i++){
        sumTAT += p[i].TAT;
        sumWT += p[i].WT;
    }
    float AvgTAT = sumTAT/n;
    float AvgWT = sumWT/n;

    printf("Average TAT : %.2f", AvgTAT);
    printf("Average Wt : %.2f", AvgWT);


    return 0;
}