#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// Zombie Process Function
void createZombie() {
    pid_t pid = fork(); // Parent creates a child process.

    if (pid > 0) {
        // Parent process
        printf("Parent created child (PID: %d).\n", pid); // Show child's ID.
        sleep(2); // Wait for a moment.
        printf("Parent is waiting for child...\n"); // Parent is waiting.
        wait(NULL); // Wait for child's termination (cleanup).
        printf("Child process reaped.\n"); // Child is fully terminated.
    } else if (pid == 0) {
        // Child process
        printf("Child is exiting.\n"); // Child is exiting.
        exit(0); // Child exits.
    } else {
        fprintf(stderr, "Fork failed!\n"); // If fork fails, show error.
    }
}

// Orphan Process Function
void createOrphan() {
    pid_t pid = fork(); // Parent creates a child process.

    if (pid > 0) {
        // Parent process
        printf("Parent is leaving, child became an orphan.\n"); // Parent leaves.
        exit(0); // Parent exits.
    } else if (pid == 0) {
        // Child process
        sleep(2); // Wait for a moment.
        printf("Child is now an orphan.\n"); // Child is now an orphan.
        sleep(5); // Wait to observe what happens.
    } else {
        fprintf(stderr, "Fork failed!\n"); // If fork fails, show error.
    }
}

// Kill Process Function
void killProcess() {
    pid_t pid = fork(); // Parent creates a child process.

    if (pid > 0) {
        // Parent process
        printf("Parent created child (PID: %d).\n", pid); // Show child's ID.
        sleep(2); // Wait for a moment.
        printf("Killing the child process.\n"); // Killing the child.
        kill(pid, SIGKILL); // Kill the child process.
        wait(NULL); // Wait for child's termination (cleanup).
        printf("Child process killed.\n"); // Child is terminated.
    } else if (pid == 0) {
        // Child process
        while (1) {
            printf("Child is working.\n"); // Child is doing its work.
            sleep(1); // Simulate work.
        }
    } else {
        fprintf(stderr, "Fork failed!\n"); // If fork fails, show error.
    }
}

int main() {
    printf("Demonstrating Zombie Process:\n");
    createZombie(); // Call the Zombie process function.
    
    printf("\nDemonstrating Orphan Process:\n");
    createOrphan(); // Call the Orphan process function.
    
    printf("\nDemonstrating Kill Process:\n");
    killProcess(); // Call the Kill process function.

    return 0;
}
