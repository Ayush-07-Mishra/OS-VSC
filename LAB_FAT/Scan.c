#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void SCAN(int requests[], int n, int head, int direction, int diskSize) {
    int totalMovement = 0;
    int sorted[n + 3], i;

    for (i = 0; i < n; i++) {
        sorted[i] = requests[i];
    }
    sorted[n] = head;
    sorted[n + 2] = 0;
    sorted[n + 1] = diskSize - 1;
    
    // Sort the array
    qsort(sorted, n + 1, sizeof(int), compare);

    int headIndex = 0;
    while (sorted[headIndex] != head) {
        headIndex++;
    }

    printf("\nSCAN Disk Scheduling\n");

    // Move in the specified direction
    if (direction == 1) { // Moving towards higher values
        for (i = headIndex; i < n + 2; i++) {
            printf("Move from %d to %d\n", head, sorted[i]);
            totalMovement += abs(head - sorted[i]);
            head = sorted[i];
        }
        for (i = headIndex - 1; i >= 0; i--) {
            printf("Move from %d to %d\n", head, sorted[i]);
            totalMovement += abs(head - sorted[i]);
            head = sorted[i];
        }
    } else { // Moving towards lower values
        for (i = headIndex; i >= -1; i--) {
            printf("Move from %d to %d\n", head, sorted[i]);
            totalMovement += abs(head - sorted[i]);
            head = sorted[i];
        }
        for (i = headIndex + 1; i < n + 1; i++) {
            printf("Move from %d to %d\n", head, sorted[i]);
            totalMovement += abs(head - sorted[i]);
            head = sorted[i];
        }
    }

    printf("Total head movement: %d\n", totalMovement);
}

int main() {
    int n, head, diskSize, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &diskSize);

    printf("Enter direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    SCAN(requests, n, head, direction, diskSize);

    return 0;
}
