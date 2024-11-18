#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2]; // File descriptors for the pipe
    pid_t pid; // Process ID
    char write_msg[] = "Hello from parent process!";
    char read_msg[100];

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Create a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) { 
        // Parent process
        close(fd[0]); // Close the read end of the pipe
        printf("Parent: Writing to pipe: %s\n", write_msg);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]); // Close the write end after writing
    } else {
        // Child process
        close(fd[1]); // Close the write end of the pipe
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child: Read from pipe: %s\n", read_msg);
        close(fd[0]); // Close the read end after reading
    }

    return 0;
}
