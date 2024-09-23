#include<stdio.h>

struct PCB {
    int pid;            // Process ID
    int AT;             // Arrival Time
    int BT;             // Burst Time
    int WT;             // Waiting Time
    int TAT;            // Turnaround Time
    int CT;             // Completion Time
    int remaining_time; // Remaining Time for the process
};


int main() {
    struct PCB p[10]; // Array to hold up to 10 processes
    int n, quantum;   // Number of processes and time quantum
    int total_time = 0; // Total time elapsed
    int completed = 0;  // Number of completed processes

    // Input the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    // Input details for each process
    for (int i = 0; i < n; i++) {
        printf("Enter the process AT and BT for process %d: ", i + 1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].pid = i + 1; // Assign process ID
        p[i].remaining_time = p[i].BT; // Initialize remaining time to burst time
    }
    
    // Input the time quantum for scheduling
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    while(completed < n){
        for(int i =0;i<n;i++){
            if(p[i].AT <= total_time && p[i].remaining_time > 0){
                if(p[i].remaining_time > quantum){
                    p[i].remaining_time -= quantum;
                    total_time += quantum;
                }else{
                    total_time += p[i].remaining_time;
                    p[i].CT = total_time;
                    p[i].TAT = p[i].CT - p[i].AT;
                    p[i].WT = p[i].TAT - p[i].BT;
                    completed++;
                }
            }
        }
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