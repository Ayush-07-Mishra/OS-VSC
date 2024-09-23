#include<stdio.h>
struct PCB{
    int pid,AT,BT,PRI, WT, TAT, CT;
};

int main(){
    struct PCB p[10];
    struct PCB temp;
    int n;

    printf("Enter Number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the process AT, BT and priority %d: ", i + 1);
        scanf("%d %d %d", &p[i].AT, &p[i].BT, &p[i].PRI);
        p[i].pid = i + 1;
    }

    for(int i =0;i<n-1;i++){
        for(int j =0;j<n-1-i;j++){
            if(p[j].PRI > p[j+1].PRI || (p[j].PRI == p[j+1].PRI) && (p[j].AT > p[j+1].AT)){
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp; 
            }
        }
    }
    p[0].CT = p[0].BT + p[0].AT;
    p[0].TAT = p[0].CT - p[0].AT;
    p[0].WT = p[0].TAT - p[0].BT;

    for (int i = 1; i < n; i++) {
        if (p[i].AT > p[i - 1].CT) {
            p[i].CT = p[i].AT + p[i].BT; // If the process arrives after the last one completes
        } else {
            p[i].CT = p[i - 1].CT + p[i].BT; // If the process can start right after the last one
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

    printf("Average TAT : %.2f\n", AvgTAT);
    printf("Average Wt : %.2f", AvgWT);
}