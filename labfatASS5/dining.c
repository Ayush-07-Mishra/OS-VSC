#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Number of philosophers

sem_t chopstick[N]; // Semaphore for chopsticks

// Function for philosopher threads
void* philosopher(void* num) {
    int i = *(int*)num; // Philosopher index

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking...\n", i + 1);
        sleep(1);

        // Pick up chopsticks
        sem_wait(&chopstick[i]);
        sem_wait(&chopstick[(i + 1) % N]);

        // Eating
        printf("Philosopher %d is eating...\n", i + 1);
        sleep(2);

        // Put down chopsticks
        sem_post(&chopstick[i]);
        sem_post(&chopstick[(i + 1) % N]);

        // Back to thinking
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int philosopher_ids[N];

    // Initialize semaphores
    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
        philosopher_ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join threads (optional in this infinite simulation)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}
