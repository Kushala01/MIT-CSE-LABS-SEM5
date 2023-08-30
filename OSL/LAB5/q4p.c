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

#define MAX_ITEMS 5  // Maximum number of items on the shelf

int shelf_count = 0;  // Current count of items on the shelf
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex for thread synchronization

// Producer thread function
void* producer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);  // Lock the mutex to protect critical section

        if (shelf_count < MAX_ITEMS) {
            shelf_count++;
            printf("Producer: Added an item. Shelf count: %d\n", shelf_count);
        }

        pthread_mutex_unlock(&mutex);  // Unlock the mutex

        usleep(100000);  // Sleep for a short time before adding another item
    }
    return NULL;
}

int main() {
    pthread_t producer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);  // Create the producer thread

    // Wait for the producer thread to finish (Ctrl+C to exit)
    pthread_join(producer_thread, NULL);

    return 0;
}
