#include <stdio.h>

struct PCB {
    int pid, AT, BT, CT, TAT, WT, RT;
};

int main() {
    struct PCB p[10];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].pid = i + 1;
        p[i].RT = p[i].BT; // Initialize remaining time
    }

    int tq;
    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    int completed = 0; // Completed process count
    int time = 0;      // Current time
    while (completed < n) {
        int done = 0;
        for (int i = 0; i < n; i++) {
            // Check if the process is ready and has remaining burst time
            if (p[i].RT > 0 && p[i].AT <= time) {
                done = 1; // At least one process is handled in this round
                if (p[i].RT > tq) {
                    time += tq;
                    p[i].RT -= tq;
                } else {
                    time += p[i].RT;
                    p[i].RT = 0; // Process is completed
                    completed++;
                    p[i].CT = time;
                    p[i].TAT = p[i].CT - p[i].AT;
                    p[i].WT = p[i].TAT - p[i].BT;
                }
            }
        }
        // If no process was handled in this round, move the time forward
        if (!done) {
            time++;
        }
    }

    float totalWT = 0, totalTAT = 0;
    printf("\nP_ID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        totalWT += p[i].WT;
        totalTAT += p[i].TAT;
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
