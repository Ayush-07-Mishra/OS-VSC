#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void SCAN(int requests[], int n, int head, int direction, int diskSize) {
    int totalMovement = 0;
    int sorted[n + 2], index = 0;

    // Copy requests into a new array and add head and end point based on direction
    for (int i = 0; i < n; i++) {
        sorted[index++] = requests[i];
    }
    sorted[index++] = head;
    if (direction == 1) {
        sorted[index++] = diskSize - 1;  // If moving high, add disk end
    } else {
        sorted[index++] = 0;             // If moving low, add disk start
    }

    // Sort the array
    qsort(sorted, index, sizeof(int), compare);

    // Find the position of the head in the sorted array
    int headIndex;
    for (int i = 0; i < index; i++) {
        if (sorted[i] == head) {
            headIndex = i;
            break;
        }
    }

    printf("\nSCAN Disk Scheduling\n");

    // Traverse in the specified direction
    if (direction == 1) {  // Moving towards higher values
        for (int i = headIndex; i < index; i++) {
            printf("Move from %d to %d with movement %d\n", head, sorted[i], abs(head - sorted[i]));
            totalMovement += abs(head - sorted[i]);
            head = sorted[i];
        }
        // After reaching the end, move back in the opposite direction if needed
        for (int i = headIndex - 1; i >= 0; i--) {
            printf("Move from %d to %d with movement %d\n", head, sorted[i], abs(head - sorted[i]));
            totalMovement += abs(head - sorted[i]);
            head = sorted[i];
        }
    } else {  // Moving towards lower values
        for (int i = headIndex; i >= 0; i--) {
            printf("Move from %d to %d with movement %d\n", head, sorted[i], abs(head - sorted[i]));
            totalMovement += abs(head - sorted[i]);
            head = sorted[i];
        }
        // After reaching the start, move back in the opposite direction if needed
        for (int i = headIndex + 1; i < index; i++) {
            printf("Move from %d to %d with movement %d\n", head, sorted[i], abs(head - sorted[i]));
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
