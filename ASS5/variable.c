#include <stdio.h>

#define MAX 25

// Structure to represent a memory block
struct Block {
    int size;
    int allocated; // 0 if not allocated, 1 if allocated
};

// Function for First Fit allocation
void firstFit(struct Block blocks[], int n, int processSize[], int m) {
    printf("\n--- First Fit Allocation ---\n");
    for (int i = 0; i < m; i++) {
        int allocated = 0;
        for (int j = 0; j < n; j++) {
            if (blocks[j].size >= processSize[i]) {
                printf("Process %d of size %d is allocated to block %d of size %d (First Fit)\n",
                       i + 1, processSize[i], j + 1, blocks[j].size);
                blocks[j].size -= processSize[i];
                allocated = 1;
                break;
            }
        }
        if (!allocated) {
            printf("Process %d of size %d could not be allocated (First Fit)\n", i + 1, processSize[i]);
        }
    }
}

// Function for Best Fit allocation
void bestFit(struct Block blocks[], int n, int processSize[], int m) {
    printf("\n--- Best Fit Allocation ---\n");
    for (int i = 0; i < m; i++) {
        int bestIndex = -1;
        for (int j = 0; j < n; j++) {
            if (blocks[j].size >= processSize[i]) {
                if (bestIndex == -1 || blocks[j].size < blocks[bestIndex].size) {
                    bestIndex = j;
                }
            }
        }
        if (bestIndex != -1) {
            printf("Process %d of size %d is allocated to block %d of size %d (Best Fit)\n",
                   i + 1, processSize[i], bestIndex + 1, blocks[bestIndex].size);
            blocks[bestIndex].size -= processSize[i];
        } else {
            printf("Process %d of size %d could not be allocated (Best Fit)\n", i + 1, processSize[i]);
        }
    }
}

// Function for Worst Fit allocation
void worstFit(struct Block blocks[], int n, int processSize[], int m) {
    printf("\n--- Worst Fit Allocation ---\n");
    for (int i = 0; i < m; i++) {
        int worstIndex = -1;
        for (int j = 0; j < n; j++) {
            if (blocks[j].size >= processSize[i]) {
                if (worstIndex == -1 || blocks[j].size > blocks[worstIndex].size) {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1) {
            printf("Process %d of size %d is allocated to block %d of size %d (Worst Fit)\n",
                   i + 1, processSize[i], worstIndex + 1, blocks[worstIndex].size);
            blocks[worstIndex].size -= processSize[i];
        } else {
            printf("Process %d of size %d could not be allocated (Worst Fit)\n", i + 1, processSize[i]);
        }
    }
}

// Helper function to reset block allocation
void resetBlocks(struct Block blocks[], int n, int initialSizes[]) {
    for (int i = 0; i < n; i++) {
        blocks[i].size = initialSizes[i];
        blocks[i].allocated = 0;
    }
}

int main() {
    int n, m;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);
    struct Block blocks[MAX];
    int initialSizes[MAX];
    
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &blocks[i].size);
        initialSizes[i] = blocks[i].size;
        blocks[i].allocated = 0;
    }

    printf("Enter the number of processes: ");
    scanf("%d", &m);
    int processSize[MAX];
    
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &processSize[i]);
    }

    firstFit(blocks, n, processSize, m);
    
    resetBlocks(blocks, n, initialSizes);
    bestFit(blocks, n, processSize, m);
    
    resetBlocks(blocks, n, initialSizes);
    worstFit(blocks, n, processSize, m);

    return 0;
}
