#include<stdio.h>

struct PCB{
    int pid,AT,BT,CT,TAT,WT;
};

int main(){

    struct PCB p[10];
    struct PCB temp;
    int n;
    printf("enter the number of process : ");
    scanf("%d",&n);
    for(int i =0;i<n;i++){
        printf("enter the process AT and BT of %d : ",i+1);
        scanf("%d %d",&p[i].AT,&p[i].BT);
        p[i].pid = i+1;
    }

    for(int i = 0;i<n-1;i++){
        for(int j =0;j<(n-i-1);j++){
            if(p[j].AT > p[j+1].AT){
                temp = p[i];
                p[i] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    p[0].CT = p[0].AT + p[0].BT;
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

    float sumWT = 0;
    float sumTAT = 0;

    for(int i =0;i<n;i++){
        sumWT += p[i].WT;
        sumTAT += p[i].TAT;
    }

    float AvgWT = sumWT/n;
    float AvgTAT = sumTAT/n;

    printf("\nAverage Waiting Time: %.2f", AvgWT);
    printf("\nAverage Turn Around Time: %.2f", AvgTAT);


}