#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void CLOOK(int requests[], int n, int head) {
    int totalMovement = 0;
    int sorted[n + 1], index = 0;
    sorted[index++] = head;

    for (int i = 0; i < n; i++) sorted[index++] = requests[i];
    qsort(sorted, index, sizeof(int), (int (*)(const void *, const void *))strcmp);

    printf("\nC-LOOK Disk Scheduling\n");
    int headIndex = 0;
    while (sorted[headIndex] != head) headIndex++;

    for (int i = headIndex; i < index; i++) {
        printf("Move from %d to %d with movement %d\n", head, sorted[i], abs(head - sorted[i]));
        totalMovement += abs(head - sorted[i]);
        head = sorted[i];
    }
    for (int i = 0; i < headIndex; i++) {
        printf("Move from %d to %d with movement %d\n", head, sorted[i], abs(head - sorted[i]));
        totalMovement += abs(head - sorted[i]);
        head = sorted[i];
    }
    printf("Total head movement: %d\n", totalMovement);
}

int main() {
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);

    CLOOK(requests, n, head);
    return 0;
}
