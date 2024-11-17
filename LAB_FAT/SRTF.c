#include <stdio.h>

struct PCB {
    int pid, AT, BT, PRI, CT, TAT, WT, RT;
};

int main() {
    struct PCB p[10];
    int n = 0, time = 0, completed = 0;

    // Taking input for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Taking input for arrival time, burst time
    for (int i = 0; i < n; i++) {
        printf("Enter AT, BT of Process %d: ", i + 1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].pid = i + 1;  // Assigning process ID
        p[i].RT = p[i].BT;  // Initialize remaining time with burst time
    }

    // SRTF Scheduling
    while (completed < n) {
        int shortest_remaining_time = -1;
        int shortest_process = -1;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= time && p[i].RT > 0) {
                if (shortest_remaining_time == -1 || p[i].RT < shortest_remaining_time) {
                    shortest_remaining_time = p[i].RT;
                    shortest_process = i;
                }
            }
        }

        // If a process is found to execute
        if (shortest_process != -1) {
            time++;  // CPU time increments
            p[shortest_process].RT--;  // Decrease the remaining time of the process

            // If the process finishes execution
            if (p[shortest_process].RT == 0) {
                completed++;
                p[shortest_process].CT = time;  // Completion time
                p[shortest_process].TAT = p[shortest_process].CT - p[shortest_process].AT;  // Turnaround time
                p[shortest_process].WT = p[shortest_process].TAT - p[shortest_process].BT;  // Waiting time
            }
        } else {
            time++;  // CPU is idle, no process is ready to execute
        }
    }

    // Print the results
    printf("\nProcess ID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    return 0;
}
