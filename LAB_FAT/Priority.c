#include <stdio.h>

struct PCB {
    int pid, AT, BT, PRI, WT, TAT, CT, RT;
};

int main() {
    struct PCB p[10];
    struct PCB temp;
    int n, time = 0, completed = 0;

    printf("Enter Number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the process AT, BT and priority %d: ", i + 1);
        scanf("%d %d %d", &p[i].AT, &p[i].BT, &p[i].PRI);
        p[i].pid = i + 1;
        p[i].RT = p[i].BT; // Initialize remaining time
    }

    // Sorting processes based on priority and then arrival time
    // for (int i = 0; i < n - 1; i++) {
    //     for (int j = 0; j < n - i - 1; j++) {
    //         if (p[j].PRI > p[j + 1].PRI || (p[j].PRI == p[j + 1].PRI && p[j].AT > p[j + 1].AT)) {
    //             temp = p[j];
    //             p[j] = p[j + 1];
    //             p[j + 1] = temp;
    //         }
    //     }
    // }

    // Preemptive Priority Scheduling
    while (completed < n) { // Jab tak saare processes complete na ho jaye
        int highest_priority = -1, highest_process = -1;

        // Har time par highest priority wale process ko find karo jo execute ho sakta ho
        for (int i = 0; i < n; i++) {
            // Agar process ka arrival time current time se chhota hai aur remaining time zyada hai
            if (p[i].AT <= time && p[i].RT > 0) {
                // Sabse high priority ko check karo
                if (highest_priority < p[i].PRI) {
                    highest_priority = p[i].PRI;
                    highest_process = i;
                }
            }
        }

        if (highest_process != -1) { // Agar koi process mila jo execute ho sakta hai
            time++;                  // Ek unit time ke liye process execute karo
            p[highest_process].RT--; // Remaining Time ko ek se kam karo

            // Agar process complete ho gaya
            if (p[highest_process].RT == 0) {
                completed++; // Completed processes ka count badhao
                p[highest_process].CT = time; // Completion Time set karo
                p[highest_process].TAT = p[highest_process].CT - p[highest_process].AT; // Turnaround Time = Completion Time - Arrival Time
                p[highest_process].WT = p[highest_process].TAT - p[highest_process].BT; // Waiting Time = Turnaround Time - Burst Time
            }
        } else {
            time++; // Agar koi process ready nahi hai, to time badha do (CPU idle hai)
        }
    }

    // Result print karo
    printf("\nProcess ID\tAT\tBT\tPRI\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].PRI, p[i].CT, p[i].TAT, p[i].WT);
    }

    return 0;
}