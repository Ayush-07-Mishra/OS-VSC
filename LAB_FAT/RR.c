#include <stdio.h>

struct Process {
    int id;   // Process ID
    int at;   // Arrival Time
    int bt;   // Burst Time
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
    int rt;   // Remaining Time
};

int main() {
    struct Process p[10];  // Array for processes
    int n, tq, time = 0, completed = 0; // Number of processes, time quantum, current time, completed processes

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
        p[i].rt = p[i].bt; // Initialize remaining time
    }

    // Input time quantum
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Round Robin scheduling
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) { // If process has remaining time and has arrived
                if (p[i].rt > tq) {
                    time += tq;  // Process runs for time quantum
                    p[i].rt -= tq;
                } else {
                    time += p[i].rt;  // Process completes
                    p[i].rt = 0;
                    p[i].tat = time - p[i].at; // Turnaround Time
                    p[i].wt = p[i].tat - p[i].bt; // Waiting Time
                    completed++;
                }
            }
        }
    }

    // Calculate average WT and TAT
    float totalWT = 0, totalTAT = 0;
    printf("\nP_ID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);

    return 0;
}
