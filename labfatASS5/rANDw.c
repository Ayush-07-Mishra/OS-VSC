#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt, mutex;    // Semaphores for writer and reader access
int readcnt = 0;     // Number of active readers
int shared_data = 0; // Shared resource

void reader() {
    sem_wait(&mutex);
    readcnt++;
    if (readcnt == 1) sem_wait(&wrt); // First reader blocks writers
    sem_post(&mutex);

    // Reading Section
    printf("Reader: Read shared data = %d\n", shared_data);

    sem_wait(&mutex);
    readcnt--;
    if (readcnt == 0) sem_post(&wrt); // Last reader unblocks writers
    sem_post(&mutex);
}

void writer() {
    sem_wait(&wrt);

    // Writing Section
    shared_data++;
    printf("Writer: Wrote shared data = %d\n", shared_data);

    sem_post(&wrt);
}

int main() {
    // Initialize semaphores
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);

    // Simulate actions
    writer(); // Call writer function
    reader(); // Call reader function
    reader(); // Call another reader
    writer(); // Call another writer
    reader(); // Call one more reader

    // Destroy semaphores
    sem_destroy(&wrt);
    sem_destroy(&mutex);

    return 0;
}
