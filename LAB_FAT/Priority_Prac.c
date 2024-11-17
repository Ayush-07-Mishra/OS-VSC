#include<stdio.h>

struct PCB{
    int pid, AT, BT, PRI, WT, TAT,CT,RT;
};

int main(){
    struct PCB p[10];
    struct PCB temp;
    int n = 0;
    int time = 0;
    int completed =0;

    printf("Enter Number of Processes: ");
    scanf("%d",&n);

    for(int i = 0;i<n;i++){
        printf("Enter the process AT, BT and Priority %d: ",i+1);
        scanf("%d %d %d",&p[i].AT,&p[i].BT,&p[i].PRI);
        p[i].pid = i+1;
        p[i].RT = p[i].BT;
    }

    // for(int i =0;i<n;i++){
    //     for(int j =0;j<n-i-1;j++){
    //         if(p[j].PRI > p[j+1].PRI || (p[j].PRI == p[j+1].PRI && p[j].AT > p[j+1].AT)){
    //             temp = p[j];
    //             p[j] = p[j+1];
    //             p[j+1] = temp;
    //         }
    //     }
    // }

    while(completed < n){
        int highest_priority = -1;
        int highest_process = -1;

        for(int i =0;i<n;i++){
            if(p[i].AT <= time && p[i].RT > 0){
                if (highest_priority < p[i].PRI) {
                    highest_priority = p[i].PRI;
                    highest_process = i;
                }
            }
        }

        if(highest_process != -1){
            time++;
            p[highest_process].RT--;
            printf("%d\n",p[highest_process].pid);

            if(p[highest_process].RT == 0){
                completed++;
                p[highest_process].CT = time;
                p[highest_process].TAT = p[highest_process].CT - p[highest_process].AT;
                p[highest_process].WT = p[highest_process].TAT - p[highest_process].BT;
            }
        }else{
            time++;
        }
    }

    // Result print karo
    printf("\nProcess ID\tAT\tBT\tPRI\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].PRI, p[i].CT, p[i].TAT, p[i].WT);
    }

    return 0;
}