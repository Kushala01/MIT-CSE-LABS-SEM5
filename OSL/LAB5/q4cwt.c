/*Write two programs, producer.c implementing a producer and consumer.c
implementing a consumer, that do the following:
Your product will sit on a shelf: that is an integer - a count of the items "on the
shelf". This integer may never drop below 0 or rise above 5.
Your producer sets the value of the count to 5. It is the producer program's
responsibility to stock product on the shelf, but not overstocked. The producer may
add one item to the shelf at a time, and must report to STDOUT every time another
item is added as well as the current shelf count.
Your consumer will remove one item from the shelf at a time, provided the item
count has not dropped below zero. The consumer will decrement the counter and
report the new value to STDOUT. Have your consumer report each trip to the shelf,
in which there are no items.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Global variables
int shelf_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;   // Mutex for thread synchronization
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;     // Condition variable for signaling
int done = 0;  // Indicates whether the producer is done adding items

// Consumer thread function
void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait until there is an item on the shelf or the producer is done
        while (shelf_count == 0 && !done) {
            pthread_cond_wait(&cond, &mutex);
        }

        if (shelf_count > 0) {
            shelf_count--;
            printf("Consumer: Removed an item. Shelf count: %d\n", shelf_count);
        } else if (done) {
            printf("Consumer: Exiting.\n");
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }

        pthread_mutex_unlock(&mutex);

        usleep(150000);  // Sleep for a short time before consuming another item
    }
    return NULL;
}

int main() {
    pthread_t consumer_thread;

    // Create the consumer thread
    if (pthread_create(&consumer_thread, NULL, consumer, NULL) != 0) {
        fprintf(stderr, "Error creating consumer thread\n");
        return 1;
    }

    // Simulate the producer adding items
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        shelf_count++;
        printf("Producer: Added an item. Shelf count: %d\n", shelf_count);
        pthread_cond_signal(&cond);  // Signal the consumer that an item is available
        pthread_mutex_unlock(&mutex);
        usleep(100000);  // Sleep for a short time before adding another item
    }

    // Notify consumer that no more items will be added
    pthread_mutex_lock(&mutex);
    done = 1;
    pthread_cond_signal(&cond);  // Signal the consumer to check if it should exit
    pthread_mutex_unlock(&mutex);

    // Wait for the consumer thread to finish
    pthread_join(consumer_thread, NULL);

    return 0;
}
