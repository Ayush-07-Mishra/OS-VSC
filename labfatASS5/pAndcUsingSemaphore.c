#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the buffer

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0, out = 0;     // Pointers to the buffer

sem_t empty; // Semaphore to track empty slots
sem_t full;  // Semaphore to track filled slots
sem_t mutex; // Semaphore for mutual exclusion

void producer(int item) {
    sem_wait(&empty); // Wait for an empty slot
    sem_wait(&mutex); // Lock critical section

    // Produce an item
    buffer[in] = item;
    printf("Producer produced: %d\n", item);
    in = (in + 1) % BUFFER_SIZE;

    sem_post(&mutex); // Unlock critical section
    sem_post(&full);  // Signal that a slot is full
}

void consumer() {
    sem_wait(&full);  // Wait for a full slot
    sem_wait(&mutex); // Lock critical section

    // Consume an item
    int item = buffer[out];
    printf("Consumer consumed: %d\n", item);
    out = (out + 1) % BUFFER_SIZE;

    sem_post(&mutex); // Unlock critical section
    sem_post(&empty); // Signal that a slot is empty
}

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // BUFFER_SIZE empty slots initially
    sem_init(&full, 0, 0);            // No full slots initially
    sem_init(&mutex, 0, 1);           // Mutex for critical section

    // Simulate producer and consumer actions
    producer(1); // Producer adds item 1
    producer(2); // Producer adds item 2
    consumer();  // Consumer removes an item
    producer(3); // Producer adds item 3
    consumer();  // Consumer removes an item
    consumer();  // Consumer removes an item
    producer(4); // Producer adds item 4

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
