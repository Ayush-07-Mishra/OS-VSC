#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0; // Current count of items in the buffer

sem_t empty;   // Semaphore for empty spaces
sem_t full;    // Semaphore for filled spaces
pthread_mutex_t mutex; // Mutex for synchronization

void producer() {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&empty);              // Wait for empty space
        pthread_mutex_lock(&mutex);    // Lock the buffer

        // Produce an item and add to the buffer
        buffer[count] = i;
        printf("Producer produced: %d\n", i);
        count++;

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&full);               // Signal that buffer has an item
        sleep(1); // Simulate work
    }
}

void consumer() {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&full);               // Wait for a filled space
        pthread_mutex_lock(&mutex);    // Lock the buffer

        // Consume an item from the buffer
        int item = buffer[count - 1];
        printf("Consumer consumed: %d\n", item);
        count--;

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&empty);              // Signal that buffer has space
        sleep(2); // Simulate work
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, (void *)producer, NULL);
    pthread_create(&cons_thread, NULL, (void *)consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
