#include <stdio.h>
#include <limits.h>

struct PCB {
    int pid, AT, BT, CT, WT, TAT, RT, remaining_BT;
};

int main() {
    int n, completed = 0, currentTime = 0;
    float sumWT = 0, sumTAT = 0;

    struct PCB p[10];
    int isCompleted[10] = {0};

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival time and Burst time for process id %d: ", i + 1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].pid = i + 1;
        p[i].remaining_BT = p[i].BT;
        p[i].RT = -1; // Indicates response time hasn't been set yet
    }

    // SRTF Scheduling
    while (completed != n) {
        int min_BT = INT_MAX, shortest = -1;

        // Find the process with the shortest remaining time that's ready
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= currentTime && !isCompleted[i] && p[i].remaining_BT < min_BT) {
                min_BT = p[i].remaining_BT;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++; // No process is ready, so move the clock forward
            continue;
        }

        // If this is the first time the process is executing, set response time
        if (p[shortest].RT == -1) {
            p[shortest].RT = currentTime - p[shortest].AT;
        }

        // Process execution
        p[shortest].remaining_BT--;
        currentTime++;

        // If the process is completed
        if (p[shortest].remaining_BT == 0) {
            completed++;
            isCompleted[shortest] = 1;
            p[shortest].CT = currentTime;
            p[shortest].TAT = p[shortest].CT - p[shortest].AT;
            p[shortest].WT = p[shortest].TAT - p[shortest].BT;

            sumWT += p[shortest].WT;
            sumTAT += p[shortest].TAT;
        }
    }

    // Calculate average waiting time and turnaround time
    float AvgWT = sumWT / n;
    float AvgTAT = sumTAT / n;

    // Print the results
    printf("\nPID \tBurst_Time \tArrival_Time \tCompletion_Time \tWaiting_Time \tTurnAround_Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t%d \t\t%d \t\t%d \t\t%d \t\t%d\n", p[i].pid, p[i].BT, p[i].AT, p[i].CT, p[i].WT, p[i].TAT);
    }

    // Print average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f", AvgWT);
    printf("\nAverage Turn Around Time: %.2f", AvgTAT);

    return 0;
}
