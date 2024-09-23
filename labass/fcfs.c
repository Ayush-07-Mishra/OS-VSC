#include<stdio.h>

struct PCB {
    int pid, AT, BT, WT, TAT, CT;
};

int main() {
    int n, sumWT = 0, sumTAT = 0;
    float AvgWT, AvgTAT;

    struct PCB p[10];

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival time and Burst time for process id %d: ", i+1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].pid = i + 1;
    }

    // Sort based on Arrival Time (AT)
    struct PCB temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (p[j].AT > p[j+1].AT) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }


    p[0].CT = p[0].AT + p[0].BT;        // Completion time of the first process
    p[0].TAT = p[0].CT - p[0].AT;       // Turnaround time = CT - AT
    p[0].WT = p[0].TAT - p[0].BT;       // Waiting time = TAT - BT

    for (int i = 1; i < n; i++) {
        // Completion Time (CT)
        if (p[i].AT > p[i-1].CT) {
            p[i].CT = p[i].AT + p[i].BT; // If the process arrives after the previous one completes
        } else {
            p[i].CT = p[i-1].CT + p[i].BT; // If the process arrives while the previous is still executing
        }

        // Turnaround Time (TAT) = CT - AT
        p[i].TAT = p[i].CT - p[i].AT;

        // Waiting Time (WT) = TAT - BT
        p[i].WT = p[i].TAT - p[i].BT;
    }

    // Calculating total Waiting Time and Turn Around Time
    for (int i = 0; i < n; i++) {
        sumWT += p[i].WT;
        sumTAT += p[i].TAT;
    }

    AvgWT = (float)sumWT / n;
    AvgTAT = (float)sumTAT / n;

    // Display the results
    printf("PID \tBurst_Time \tArrival_Time \tCompletion_Time \tWaiting_Time \tTurnAround_Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t%d \t\t%d \t\t%d \t\t%d \t\t%d\n", p[i].pid, p[i].BT, p[i].AT, p[i].CT, p[i].WT, p[i].TAT);
    }

    printf("\nAverage Waiting Time: %.2f", AvgWT);
    printf("\nAverage Turn Around Time: %.2f", AvgTAT);

    return 0;
}
