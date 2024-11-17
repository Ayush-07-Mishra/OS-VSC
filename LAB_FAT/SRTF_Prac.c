#include<stdio.h>

struct PCB{
    int pid, AT,BT,PRI,CT,TAT,WT, RT;
};

int main(){
    struct PCB p[10];
    int n = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(int i = 0;i<n;i++){
        printf("enter the value of AT BT : ");
        scanf("%d %d",&p[i].AT,&p[i].BT);
        p[i].RT = p[i].BT;
        p[i].pid = i+1;
    }
    int completed = 0;
    int time = 0;
    while(completed < n){
        int shortest_remaining_time = -1;
        int shortest_process = -1;

        for(int i = 0;i<n;i++){
            if(p[i].AT <= time && p[i].RT > 0){
                if(shortest_remaining_time == -1 || shortest_remaining_time > p[i].RT){
                    shortest_remaining_time = p[i].RT;
                    shortest_process = i;
                }
            }
        }
        if(shortest_process != -1){
            time++;
            printf("%d\n",p[shortest_process].pid);
            p[shortest_process].RT--;

            if(p[shortest_process].RT == 0){
                completed++;
                p[shortest_process].CT = time;
                p[shortest_process].TAT = p[shortest_process].CT - p[shortest_process].AT;
                p[shortest_process].WT = p[shortest_process].TAT - p[shortest_process].BT;
            }
        }else{
            time++;
        }
    }
   printf("\nProcess ID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    return 0;


}