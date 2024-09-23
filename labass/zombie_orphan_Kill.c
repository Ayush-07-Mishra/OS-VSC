#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// Zombie Process Function
void createZombie() {
    pid_t pid = fork(); // Mummy-papa (parent) ek baccha (child) banate hain.

    if (pid > 0) {
        // Parent process
        printf("Parent ne child create kiya (PID: %d).\n", pid); // Bacche ka ID dikhate hain.
        sleep(2); // Thoda wait karte hain.
        printf("Parent child ka intezaar kar raha hai...\n"); // Bacche ka intezaar.
        wait(NULL); // Bacche ki report lete hain (cleanup).
        printf("Child process reaped.\n"); // Baccha puri tarah se khatam.
    } else if (pid == 0) {
        // Child process
        printf("Child ab exit ho raha hai.\n"); // Baccha ja raha hai.
        exit(0); // Baccha exit ho gaya.
    } else {
        fprintf(stderr, "Fork failed!\n"); // Agar fork nahi hota toh error.
    }
}

// Orphan Process Function
void createOrphan() {
    pid_t pid = fork(); // Mummy-papa ek baccha banate hain.

    if (pid > 0) {
        // Parent process
        printf("Parent ab ja raha hai, baccha yateem ho gaya.\n"); // Mummy-papa chale gaye.
        exit(0); // Mummy-papa exit ho gaye.
    } else if (pid == 0) {
        // Child process
        sleep(2); // Thoda wait karte hain.
        printf("Child ab yateem ho gaya.\n"); // Baccha yateem ho gaya.
        sleep(5); // Thodi der dekhte hain kya hota hai.
    } else {
        fprintf(stderr, "Fork failed!\n"); // Agar fork nahi hota toh error.
    }
}

// Kill Process Function
void killProcess() {
    pid_t pid = fork(); // Mummy-papa ek baccha banate hain.

    if (pid > 0) {
        // Parent process
        printf("Parent ne child create kiya (PID: %d).\n", pid); // Bacche ka ID dikhate hain.
        sleep(2); // Thoda wait karte hain.
        printf("Child process ko maar rahe hain.\n"); // Bacche ko kill kar rahe hain.
        kill(pid, SIGKILL); // Bacche ko kill karte hain.
        wait(NULL); // Bacche ka intezaar (cleanup).
        printf("Child process kill ho gaya.\n"); // Baccha khatam ho gaya.
    } else if (pid == 0) {
        // Child process
        while (1) {
            printf("Child kaam kar raha hai.\n"); // Baccha kaam kar raha hai.
            sleep(1); // Kaam simulate karte hain.
        }
    } else {
        fprintf(stderr, "Fork failed!\n"); // Agar fork nahi hota toh error.
    }
}

int main() {
    printf("Zombie Process dikhate hain:\n");
    createZombie(); // Zombie process function call.
    
    printf("\nOrphan Process dikhate hain:\n");
    createOrphan(); // Orphan process function call.
    
    printf("\nKill Process dikhate hain:\n");
    killProcess(); // Kill process function call.

    return 0;
}
