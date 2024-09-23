#include <stdio.h>

// Define the PCB structure to hold process information
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

    // Process scheduling loop
    while (completed < n) { // Continue until all processes are completed
        for (int i = 0; i < n; i++) {
            // Check if the process has arrived and has remaining time
            if (p[i].AT <= total_time && p[i].remaining_time > 0) {
                // If remaining time is greater than the time quantum
                if (p[i].remaining_time > quantum) {
                    total_time += quantum; // Increment total time by quantum
                    p[i].remaining_time -= quantum; // Reduce remaining time
                } else {
                    // Process will finish in this cycle
                    total_time += p[i].remaining_time; // Increment total time by remaining time
                    p[i].CT = total_time; // Set completion time
                    p[i].TAT = p[i].CT - p[i].AT; // Calculate turnaround time
                    p[i].WT = p[i].TAT - p[i].BT; // Calculate waiting time
                    p[i].remaining_time = 0; // Mark process as completed
                    completed++; // Increment completed processes count
                }
            }
        }
    }

    // Output results
    printf("\nProcess ID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        // Print each process's details
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }
    return 0; // Indicate successful completion
}
