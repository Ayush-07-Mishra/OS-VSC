#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void aLook(int requests[], int n, int head, int direction, int diskSize) {
    int seektime = 0;
    int sorted[n + 3];

    // Copy requests to sorted array and add head, 0, and diskSize-1
    for (int i = 0; i < n; i++) {
        sorted[i] = requests[i];
    }
    sorted[n] = head;
    sorted[n + 1] = 0;
    sorted[n + 2] = diskSize - 1;

    // Sort the array
    qsort(sorted, n + 3, sizeof(int), compare);

    // Find the index of the head position
    int headIndex = 0;
    for (int i = 0; i < n + 3; i++) {
        if (sorted[i] == head) {
            headIndex = i;
            break;
        }
    }

    // Handle requests in the specified direction
    if (direction == 1) { // Towards higher values
        for (int i = headIndex; i < n + 2; i++) {
            printf("Move from %d to %d is %d\n", head, sorted[i], abs(head - sorted[i]));
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
        for (int i = 1; i < headIndex; i++) {
            printf("Move from %d to %d is %d\n", head, sorted[i], abs(head - sorted[i]));
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
    } else { // Towards lower values
        for (int i = headIndex; i > 0; i--) {
            printf("Move from %d to %d is %d\n", head, sorted[i], abs(head - sorted[i]));
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
        for (int i = n+1; i > headIndex; i--) {
            printf("Move from %d to %d is %d\n", head, sorted[i], abs(head - sorted[i]));
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
    }

    // Print total head movement
    printf("Total head movement: %d\n", seektime);
}

int main() {
    int n, head, diskSize, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size: ");
    scanf("%d", &diskSize);

    printf("Enter the direction (0 - towards lower values, 1 - towards higher values): ");
    scanf("%d", &direction);

    aLook(requests, n, head, direction, diskSize);

    return 0;
}
