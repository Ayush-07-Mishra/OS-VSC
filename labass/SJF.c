#include <stdio.h>

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
        printf("Enter Arrival time and Burst time for process id %d: ", i + 1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].pid = i + 1;
    }

    // Sort processes by Burst Time (BT)
    struct PCB temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].BT > p[j + 1].BT) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculate Completion Time (CT), Turnaround Time (TAT), and Waiting Time (WT)
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].AT){
            currentTime = p[i].AT;  // Idle time if no process has arrived yet
        }
        p[i].CT = currentTime + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
        currentTime = p[i].CT;

        sumWT += p[i].WT;
        sumTAT += p[i].TAT;
    }

    // Calculate averages
    AvgWT = (float)sumWT / n;
    AvgTAT = (float)sumTAT / n;

    // Print the results
    printf("PID \tBurst_Time \tArrival_Time \tCompletion_Time \tWaiting_Time \tTurnAround_Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t%d \t\t%d \t\t%d \t\t%d \t\t%d\n", p[i].pid, p[i].BT, p[i].AT, p[i].CT, p[i].WT, p[i].TAT);
    }

    // Print average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f", AvgWT);
    printf("\nAverage Turn Around Time: %.2f", AvgTAT);

    return 0;
}
