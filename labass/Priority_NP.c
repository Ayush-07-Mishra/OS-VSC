#include <stdio.h>

struct PCB {
    int pid, AT, BT, priority, WT, TAT, CT;
};

int main() {
    int n;
    float sumWT = 0, sumTAT = 0;
    
    struct PCB p[10], temp;

    // Input number of processes and their arrival, burst time, and priority
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival time, Burst time, and Priority for process id %d: ", i + 1);
        scanf("%d %d %d", &p[i].AT, &p[i].BT, &p[i].priority);
        p[i].pid = i + 1;
    }

    // Sort processes by Priority (lower number = higher priority), if equal then by Arrival Time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority || (p[j].priority == p[j + 1].priority && p[j].AT > p[j + 1].AT)) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculate Completion Time (CT), Turnaround Time (TAT), and Waiting Time (WT)
    p[0].CT = p[0].AT + p[0].BT;  // First process completion time
    p[0].TAT = p[0].CT - p[0].AT; // Turnaround time
    p[0].WT = p[0].TAT - p[0].BT; // Waiting time
    sumWT += p[0].WT;
    sumTAT += p[0].TAT;

    for (int i = 1; i < n; i++) {
        p[i].CT = (p[i].AT > p[i - 1].CT) ? p[i].AT + p[i].BT : p[i - 1].CT + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
        sumWT += p[i].WT;
        sumTAT += p[i].TAT;
    }

    // Output the results
    printf("\nPID\tPriority\tBT\tAT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].priority, p[i].BT, p[i].AT, p[i].CT, p[i].WT, p[i].TAT);
    }

    printf("\nAverage Waiting Time: %.2f", sumWT / n);
    printf("\nAverage Turn Around Time: %.2f\n", sumTAT / n);

    return 0;
}
