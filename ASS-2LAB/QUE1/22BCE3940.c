#include<stdio.h>

struct Process {
    int pid;           // Process ID
    int burst_time;    // Burst Time
    int arrival_time;  // Arrival Time
    int priority;      // Priority (For priority scheduling)
    int waiting_time;  // Waiting Time
    int turnaround_time; // Turnaround Time
};


void calculateAverageTimes(struct Process proc[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_turnaround_time / n);
}

void printProcessTimes(struct Process proc[], int n) {
    printf("Process ID  Arrival Time  Priority  Waiting Time  Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("    %d           %d           %d           %d             %d\n", 
                proc[i].pid, proc[i].arrival_time, proc[i].priority, proc[i].waiting_time, proc[i].turnaround_time);
    }
}


void FCFS(struct Process proc[], int n) {
    int service_time[n];
    service_time[0] = proc[0].arrival_time;
    proc[0].waiting_time = 0;

    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i-1] + proc[i-1].burst_time;
        proc[i].waiting_time = service_time[i] - proc[i].arrival_time;
        if (proc[i].waiting_time < 0)
            proc[i].waiting_time = 0;
    }

    for (int i = 0; i < n; i++)
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;

    printProcessTimes(proc, n);
    calculateAverageTimes(proc, n);
}

void SJF(struct Process proc[], int n) {
    // Sort by arrival time, then burst time
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (proc[i].burst_time > proc[j].burst_time) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    int service_time[n];
    service_time[0] = proc[0].arrival_time;
    proc[0].waiting_time = 0;

    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i-1] + proc[i-1].burst_time;
        proc[i].waiting_time = service_time[i] - proc[i].arrival_time;
        if (proc[i].waiting_time < 0)
            proc[i].waiting_time = 0;
    }

    for (int i = 0; i < n; i++)
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;

    printProcessTimes(proc, n);
    calculateAverageTimes(proc, n);
}

void SRTF(struct Process proc[], int n) {
    int remaining_time[n], complete = 0, t = 0, minm = 9999;
    int shortest = 0, finish_time, total_wt = 0, total_tat = 0;
    int check = 0;
    
    for (int i = 0; i < n; i++)
        remaining_time[i] = proc[i].burst_time;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((proc[j].arrival_time <= t) && (remaining_time[j] < minm) && remaining_time[j] > 0) {
                minm = remaining_time[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        remaining_time[shortest]--;
        minm = remaining_time[shortest];
        
        if (minm == 0)
            minm = 9999;

        if (remaining_time[shortest] == 0) {
            complete++;
            check = 0;
            finish_time = t + 1;
            proc[shortest].waiting_time = finish_time - proc[shortest].burst_time - proc[shortest].arrival_time;
            
            if (proc[shortest].waiting_time < 0)
                proc[shortest].waiting_time = 0;
        }
        t++;
    }

    for (int i = 0; i < n; i++)
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;

    printProcessTimes(proc, n);
    calculateAverageTimes(proc, n);
}



void PriorityScheduling(struct Process proc[], int n) {
    // Sort by priority, then by arrival time
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    int service_time[n];
    service_time[0] = proc[0].arrival_time;
    proc[0].waiting_time = 0;

    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i-1] + proc[i-1].burst_time;
        proc[i].waiting_time = service_time[i] - proc[i].arrival_time;
        if (proc[i].waiting_time < 0)
            proc[i].waiting_time = 0;
    }

    for (int i = 0; i < n; i++)
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;

    printProcessTimes(proc, n);
    calculateAverageTimes(proc, n);
}


void RoundRobin(struct Process proc[], int n, int quantum) {
    int remaining_time[n];
    for (int i = 0; i < n; i++)
        remaining_time[i] = proc[i].burst_time;

    int t = 0;
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0;
                if (remaining_time[i] > quantum) {
                    t += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    t += remaining_time[i];
                    proc[i].waiting_time = t - proc[i].burst_time;
                    remaining_time[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }

    for (int i = 0; i < n; i++)
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;

    printProcessTimes(proc, n);
    calculateAverageTimes(proc, n);
}


int main() {
    struct Process proc[] = {{1, 6, 0, 2}, {2, 8, 1, 1}, {3, 7, 2, 3}, {4, 3, 3, 2}};
    int n = sizeof(proc) / sizeof(proc[0]);
    int quantum = 4;

    printf("FCFS Scheduling:\n");
    FCFS(proc, n);

    printf("\nSJF Scheduling:\n");
    SJF(proc, n);

    printf("\nSRTF Scheduling:\n");
    SRTF(proc, n);

    printf("\nPriority Scheduling:\n");
    PriorityScheduling(proc, n);

    printf("\nRound Robin Scheduling (Quantum = %d):\n", quantum);
    RoundRobin(proc, n, quantum);

    return 0;
}





