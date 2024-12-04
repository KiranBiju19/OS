#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

//#define MAX 5
sem_t track;

void* train(void* n) 
{
    int id = *((int*)n);
    while (1) 
    {
        printf("Train %d arrived\n", id + 1);
        
        // Try to enter the critical section (track)
        sem_wait(&track);  // Wait for the track to be available
        
        printf("Train %d is passing\n", id + 1);
        sleep(2); // Simulate time taken to pass
        
        printf("Train %d has passed\n", id + 1);
        printf("\n");
        sem_post(&track); // Release the track
        
        sleep(1); // Simulate some time before the train arrives again
    }
}

int main() 
{
    int MAX;
    scanf("%d",&MAX);
    pthread_t thread_id[MAX];
    sem_init(&track, 0, 1); // Initialize the semaphore to 1 (binary semaphore)

    int train_ids[MAX];
    
    for (int i = 0; i < MAX; i++)
    {
        train_ids[i] = i; // Create train IDs
        pthread_create(&thread_id[i], NULL, train, &train_ids[i]);
    }
    
    // // Join threads (in practice, you might want to implement a way to exit the program)
    for (int i = 0; i < MAX; i++) 
    {
        pthread_join(thread_id[i], NULL);
    }
    
     sem_destroy(&track); // Clean up semaphore
    return 0;
}

