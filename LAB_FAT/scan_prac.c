#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void scan(int requests[], int n, int head, int diskSize, int direction) {
    int seektime = 0;
    int sorted[n + 3];
    for (int i = 0; i < n; i++) {
        sorted[i] = requests[i];
    }
    sorted[n] = head;
    sorted[n + 1] = 0;
    sorted[n + 2] = diskSize - 1;

    qsort(sorted, n + 3, sizeof(int), compare);

    int headIndex = 0;
    for (int i = 0; i < n + 3; i++) {
        if (sorted[i] == head) {
            headIndex = i;
            break;
        }
    }

    printf("\nSCAN Disk Scheduling\n");

    if (direction == 1) { // Moving towards higher values
        for (int i = headIndex; i < n + 3; i++) {
            printf("Move from %d to %d\n", head, sorted[i]);
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
        for (int i = headIndex - 1; i > 0; i--) {
            printf("Move from %d to %d\n", head, sorted[i]);
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
    } else { // Moving towards lower values
        for (int i = headIndex; i >= 0; i--) {
            printf("Move from %d to %d\n", head, sorted[i]);
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
        for (int i = headIndex + 1; i < n + 2; i++) {
            printf("Move from %d to %d\n", head, sorted[i]);
            seektime += abs(head - sorted[i]);
            head = sorted[i];
        }
    }
    
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

    scan(requests, n, head, diskSize, direction);

    return 0;
}
