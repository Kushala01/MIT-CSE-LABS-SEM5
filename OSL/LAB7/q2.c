#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex, writeBlock;
int data = 0;
int readerCount = 0;

void *reader(void *arg) {
    int readerID = *(int *)arg;
    while (1) {
        sem_wait(&mutex);
        readerCount++;
        if (readerCount == 1) {
            sem_wait(&writeBlock);
        }
        sem_post(&mutex);
        printf("Reader %d reads: %d\n", readerID, data);
        sem_wait(&mutex);
        readerCount--;
        if (readerCount == 0) {
            sem_post(&writeBlock);
        }
        sem_post(&mutex);
        // Sleep to simulate some processing time
        usleep(100000);
    }
    return NULL;
}

void *writer(void *arg) {
    int writerID = *(int *)arg;
    while (1) {
        sem_wait(&writeBlock);
        // Writing to the shared data
        data++;
        printf("Writer %d writes: %d\n", writerID, data);
        sem_post(&writeBlock);
        // Sleep to simulate some processing time
        usleep(200000);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int readerIDs[NUM_READERS], writerIDs[NUM_WRITERS];
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);
    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        readerIDs[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIDs[i]);
    }
    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIDs[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIDs[i]);
    }
    // Wait for threads to finish (this will not happen in this example)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&writeBlock);
    return 0;
}