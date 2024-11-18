#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Number of philosophers

sem_t chopstick[N]; // Semaphore for chopsticks

void philosopher(int i) {
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
    printf("Philosopher %d finished eating and is now thinking...\n", i + 1);
}

int main() {
    // Initialize semaphores
    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
    }

    // Simulate philosopher actions in order
    for (int i = 0; i < N; i++) {
        philosopher(i); // Call philosopher function
    }

    // Destroy semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}
