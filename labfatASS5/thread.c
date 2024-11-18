#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 5 // Define the number of threads

int shared_counter = 0;         // Shared counter
pthread_mutex_t lock;           // Mutex lock

// Thread function
void* thread_function(void* arg) {
    int thread_id = *((int*)arg);

    // Lock the mutex
    pthread_mutex_lock(&lock);

    // Critical section
    printf("Thread %d is entering the critical section.\n", thread_id);
    shared_counter++;
    printf("Thread %d incremented counter to %d.\n", thread_id, shared_counter);

    // Unlock the mutex
    pthread_mutex_unlock(&lock);

    // Exit the thread
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            printf("Error creating thread %d\n", i + 1);
            return 1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the final value of the shared counter
    printf("Final counter value: %d\n", shared_counter);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);
    return 0;
    
}
