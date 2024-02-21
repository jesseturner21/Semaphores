// Author: Jesse Turner
// Description: This program implements a producer-consumer program using semaphores in which items
// are produced into a buffer and then subsequently consumed. The producer loop waits until the
// empty signal is sent, fills the buffer, and then sends the full signal. The consumer loop waits
// until the full signal is sent, consumes all items in the buffer, and then sends the empty signal.
//
// Although this example is run in a single-thread environment, it could easily be adapted to a
// multithreaded environment because of the semaphore synchronization.

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

static sem_t empty, full;
static int buffer[BUFFER_SIZE];
static int count = 0;

// Produces an item into the buffer, printing it to stdout after doing so
static void produce_item(int location) {
    buffer[location] = ++count;
    printf("Produced: %d\n", count);
}

// Consumes an item from the buffer, returning the consumed item and printing it to stdout
static int consume_item(int location) {
    int item = buffer[location];
    printf("Consumed: %d\n", item);
    return item;
}

int main(void) {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    while(1){
        // Produce items
        for (int i = 0; i < BUFFER_SIZE; i++) {
            // Wait until our buffer is empty
            sem_wait(&empty);
            sleep(1);
            // Produce an item into the buffer
            produce_item(i);
            // Notify through the appropriate semaphore that our buffer is full
            sem_post(&full);
        }

        // Consume items
        for (int i = 0; i < BUFFER_SIZE; i++) {
            // Wait until our buffer is full
            sem_wait(&full);
            sleep(1);
            // Consume an item from the buffer
            consume_item(i);
            // Notify through the appropriate semaphore that our buffer is empty
            sem_post(&empty);
        }

    }

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}