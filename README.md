# Semaphores

## Description

This program implements a producer-consumer pattern using semaphores. It simulates a scenario where items are produced into a buffer and then consumed. The producer loop waits until the buffer is empty, fills it with items, and then signals that it's full. The consumer loop waits until the buffer is full, consumes all items, and then signals that it's empty.

Although this example is designed for a single-threaded environment, it can be adapted for multithreaded environments due to semaphore synchronization.

## Usage

### Compilation

Compile the program using the following command:

```bash
gcc semaphore.c -o semaphore -Wno-deprecated-declarations
```
### Excecution

Run the program using the following command:

```bash
./semaphore
