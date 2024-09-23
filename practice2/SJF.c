#include<stdio.h>

struct PCB{
    int pid,AT,BT,WT,TAT,CT;
};

int main() {
    struct PCB p[10];
    int n;
    printf("Enter he number of Process: ");
    scanf("%d",&n);

    for(int i =0;i<n;i++){
        printf("Enter Arrival time and Burst time for process id %d: ",i+1);
        scanf("%d %d",&p[i].AT,&p[i].BT);
        p[i].pid = i+1;
    }

    struct PCB temp;
    for(int i =0;i<n-1;i++){
        for(int j =0;j<n-i-1;j++){
            if(p[j].AT > p[j+1].AT || ((p[j].AT == p[j+1].AT) && (p[j].BT > p[j+1].BT))){
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }

    }

    int currentTime = 0;
    for(int i =0;i<n;i++){
        if(currentTime < p[i].AT){
            currentTime += p[i].AT;
        }
        p[i].CT = currentTime + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
        currentTime = p[i].CT;
    }

    float sumTAT = 0.0;
    float sumWT = 0.0;
    for(int i =0;i<n;i++){
        sumTAT += p[i].TAT;
        sumWT += p[i].WT;
    }

    float AvgTAT = sumTAT/n;
    float AvgWT = sumWT/n;

    printf("Average TAT : %.2f\n", AvgTAT);
    printf("Average Wt : %.2f", AvgWT);
}