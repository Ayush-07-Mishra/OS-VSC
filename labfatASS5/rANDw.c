#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;           // Semaphore for writer access
sem_t mutex;         // Semaphore for reader access
int readcnt = 0;     // Number of active readers
int shared_data = 0; // Shared resource

// Function for reader threads
void* reader(void* arg) {
    static int reader_id = 0; // Static ID for readers
    reader_id++;

    while (1) {
        sem_wait(&mutex); // Lock to update readcnt
        readcnt++;
        if (readcnt == 1) {
            sem_wait(&wrt); // First reader blocks writers
        }
        sem_post(&mutex); // Allow other readers

        // Reading Section
        printf("Reader %d: Read shared data = %d\n", reader_id, shared_data);
        sleep(1); // Simulate reading time

        sem_wait(&mutex); // Lock to update readcnt
        readcnt--;
        if (readcnt == 0) {
            sem_post(&wrt); // Last reader unblocks writers
        }
        sem_post(&mutex); // Unlock mutex
        sleep(1); // Simulate reader idle time
    }
}

// Function for writer threads
void* writer(void* arg) {
    static int writer_id = 0; // Static ID for writers
    writer_id++;

    while (1) {
        sem_wait(&wrt); // Lock for writer

        // Writing Section
        shared_data++;
        printf("Writer %d: Wrote shared data = %d\n", writer_id, shared_data);
        sleep(1); // Simulate writing time

        sem_post(&wrt); // Unlock for other writers/readers
        sleep(1); // Simulate writer idle time
    }
}

int main() {
    pthread_t readers[5], writers[2];

    // Initialize semaphores
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    // Join threads (optional in a real infinite-loop scenario)
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&wrt);
    sem_destroy(&mutex);

    return 0;
}
