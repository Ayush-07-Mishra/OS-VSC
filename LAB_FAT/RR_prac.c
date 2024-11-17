#include<stdio.h>

struct PCB{
    int pid,AT,BT,WT,TAT,RT;
};

int main(){
    struct PCB p[10];
    int n= 0;

    printf("Enter the number of process : ");
    scanf("%d",&n);

    for(int i =0;i<n;i++){
        printf("Enter the AT BT of process : %d",i+1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].RT = p[i].BT;
        p[i].pid = i+1;

    }

    int tq;
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0;

    while(completed < n){
        for(int i =0;i<n;i++){
            if(p[i].AT <= time && p[i].RT > 0){
                if(p[i].RT > tq){
                    time += tq;
                    p[i].RT -= tq;
                }else{
                    time += p[i].RT;
                    p[i].RT = 0;
                    p[i].TAT = time - p[i].at;
                    p[i]WT = p[i].TAT - p[i].BT;
                    completed++;
                }
            }
        }
    }

     // Calculate average WT and TAT
    float totalWT = 0, totalTAT = 0;
    printf("\nP_ID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        totalWT += p[i].WT;
        totalTAT += p[i].TAT;
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].WT, p[i].TAT);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);

    return 0;
}
}