#include <stdio.h>

// First Fit Allocation Function
void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int blockUsed[m]; // Block usage tracker (0: free, 1: allocated)

    for (int i = 0; i < n; i++) allocation[i] = -1; // Initially, no process is allocated
    for (int i = 0; i < m; i++) blockUsed[i] = 0;  // Initially, all blocks are free

    for (int i = 0; i < n; i++) { // For each process
        for (int j = 0; j < m; j++) { // Check all blocks
            if (blockUsed[j] == 0 && blockSize[j] >= processSize[i]) { // If block is free and suitable
                allocation[i] = j;      // Allocate process to block
                blockUsed[j] = 1;       // Mark block as allocated
                break;                  // Move to the next process
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

// Best Fit Allocation Function
void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int blockUsed[m]; // Block usage tracker (0: free, 1: allocated)

    for (int i = 0; i < n; i++) allocation[i] = -1; // Initially, no process is allocated
    for (int i = 0; i < m; i++) blockUsed[i] = 0;  // Initially, all blocks are free

    for (int i = 0; i < n; i++) { // For each process
        int bestIdx = -1;         // Index of the best block for current process
        for (int j = 0; j < m; j++) {
            if (blockUsed[j] == 0 && blockSize[j] >= processSize[i]) { // If block is free and suitable
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j; // Find the smallest suitable block
            }
        }
        if (bestIdx != -1) {      // If a suitable block is found
            allocation[i] = bestIdx;
            blockUsed[bestIdx] = 1; // Mark block as allocated
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

// Worst Fit Allocation Function
void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int blockUsed[m]; // Block usage tracker (0: free, 1: allocated)

    for (int i = 0; i < n; i++) allocation[i] = -1; // Initially, no process is allocated
    for (int i = 0; i < m; i++) blockUsed[i] = 0;  // Initially, all blocks are free

    for (int i = 0; i < n; i++) { // For each process
        int worstIdx = -1;        // Index of the worst block for current process
        for (int j = 0; j < m; j++) {
            if (blockUsed[j] == 0 && blockSize[j] >= processSize[i]) { // If block is free and suitable
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j; // Find the largest suitable block
            }
        }
        if (worstIdx != -1) {      // If a suitable block is found
            allocation[i] = worstIdx;
            blockUsed[worstIdx] = 1; // Mark block as allocated
        }
    }

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

int main() {
    int m, n;

    // Get block sizes from user
    printf("Enter the number of blocks: ");
    scanf("%d", &m);
    int blockSize[m];
    printf("Enter the sizes of %d blocks:\n", m);
    for (int i = 0; i < m; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Get process sizes from user
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter the sizes of %d processes:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // First Fit Allocation
    firstFit(blockSize, m, processSize, n);

    // Reset block usage for next allocation method
    printf("\n");
    bestFit(blockSize, m, processSize, n);

    // Reset block usage for next allocation method
    printf("\n");
    worstFit(blockSize, m, processSize, n);

    return 0;
}
