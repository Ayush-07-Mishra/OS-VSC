#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void LOOK(int requests[], int n, int head, int direction) {
    int totalMovement = 0;
    int sorted[n + 1], index = 0;

    // Copy requests into sorted array and add the initial head position
    sorted[index++] = head;
    for (int i = 0; i < n; i++) {
        sorted[index++] = requests[i];
    }

    // Sort all requests including the head
    qsort(sorted, index, sizeof(int), compare);

    // Find the initial head position in the sorted array
    int headIndex = 0;
    while (sorted[headIndex] != head) {
        headIndex++;
    }

    printf("\nLOOK Disk Scheduling\n");

    // Move in the initial direction and then reverse
    if (direction == 1) {  // Moving high initially
        // Move from head to the highest request in the list
        for (int i = headIndex; i < index; i++) {
            printf("Move from %d to %d with movement %d\n", head, sorted[i], abs(head - sorted[i]));
            totalMovement += abs(head - sorted[i]);
            head = sorted[i];
        }
        // Reverse direction and move back down to the lowest unvisited request
        for (int i = headIndex - 1; i >= 0; i--) {
            printf("Move from %d to %d with movement %d\n", head, sorted[i], abs(head - sorted[i]));
            totalMovement += abs(head - sorted[i]);
            head = sorted[i];
        }
    } else {  // Moving low initially
        // Move from head to the lowest request in the list
        for (int i = headIndex; i >= 0; i--) {
            printf("Move from %d to %d with movement %d\n", head, sorted[i], abs(head - sorted[i]));
            totalMovement += abs(head - sorted[i]);
            head = sorted[i];
        }
        // Reverse direction and move back up to the highest unvisited request
        for (int i = headIndex + 1; i < index; i++) {
            printf("Move from %d to %d with movement %d\n", head, sorted[i], abs(head - sorted[i]));
            totalMovement += abs(head - sorted[i]);
            head = sorted[i];
        }
    }

    printf("Total head movement: %d\n", totalMovement);
}

int main() {
    int n, head, direction;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    LOOK(requests, n, head, direction);
    return 0;
}
