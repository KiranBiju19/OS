#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 10

int buffer[MAX];
int in = 0, out = 0;

// Semaphores for synchronization
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

// Producer function
void* producer(void* arg)
{
    while (1) 
    {
        int item = rand() % 100;  // Produce a random item

        sem_wait(&empty);          // Wait if buffer is full
        pthread_mutex_lock(&mutex);

        buffer[in] = item;          // Place item in buffer
        printf("Producer: %d\n", item);
        in = (in + 1) % MAX;        // Move to the next slot

        pthread_mutex_unlock(&mutex);
        sem_post(&full);            // Signal that an item has been added

        sleep(1);                   // Simulate production time
    }
    pthread_exit(NULL);
}

// Consumer function
void* consumer(void* arg)
{
    while (1) 
    {
        sem_wait(&full);            // Wait if buffer is empty
        pthread_mutex_lock(&mutex);
        
        int item = buffer[out];      // Take item from buffer
        printf("Consumer: %d\n", item);
        out = (out + 1) % MAX;       // Move to the next slot
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);            // Signal that an item has been consumed
        
        sleep(1);                    // Simulate consumption time
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, MAX);        // `empty` is initialized to MAX (buffer size)
    sem_init(&full, 0, 0);           // `full` is initialized to 0
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish (in this case, they run indefinitely)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up (though unreachable due to infinite loop)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
