#include<stdio.h>

struct PCB{
    int pid,AT,BT,CT,TAT,WT,RT;
};


int main(){
    struct PCB p[10];
    int n;
    printf("Enter number of process : ");
    scanf("%d",&n);

    for(int i =0;i<n;i++){
        printf("enter AT BT of process %d : ",i+1);
        scanf("%d %d",&p[i].AT,&p[i].BT);
        p[i].pid = i+1;
        p[i].RT = p[i].BT;
    }

    int completed = 0;
    int time = 0;

    while(completed < n){
        int shortest_remaining_time = -1;
        int shortest_process = -1;

        for(int i =0;i<n;i++){
            if(p[i].AT <= time && p[i].RT > 0){
                if(shortest_remaining_time == -1 || p[i].RT < shortest_remaining_time){
                    shortest_remaining_time = p[i].RT;
                    shortest_process = i;
                }
            }
        }

        if(shortest_process != -1){
            time++;
            p[shortest_process].RT --;

            if(p[shortest_process].RT == 0){
                completed++;
                p[shortest_process].CT = time;
                p[shortest_process].TAT = p[shortest_process].CT - p[shortest_process].AT;
                p[shortest_process].WT = p[shortest_process].TAT - p[shortest_process].BT;
            }
        }else{
            time++;
        }

        printf("\nproces ID\t AT\t BT\t CT\t TAT\t WT\n");
        for(int i =0;i<n;i++){
            printf("%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
        }

        return 0;

    }
}