#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5;

int buffer[5];

int i =0 ,j = 0;
sem_t full;
sem_t empty;
sem_t mutex;

void producer(int item){
    sem_wait(&empty);
    sem_wait(&mutex);

    buffer[i] = item;
    printf("Producer Produces : %d",item);
    i = (i+1)%BUFFER_SIZE;

    sem_post(&mutex);
    sem_post(&full);
}

void consumer(){
    sem_wait(&full);
    sem_wait(&mutex);

    int item = buffer[j];
    printf("Consumer consumes : %d\n",item);

    sem_post(&mutex);
    sem_wait(&empty);
}


int main(){
    
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
