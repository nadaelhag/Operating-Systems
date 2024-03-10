#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 7
#define MAX_COUNT 10000

int shared_variable = 0; 
int lock = 0;      

void *thread_function(void *arg) {
    int thread_id = *((int *)arg);

    for (int i = 0; i < MAX_COUNT; i++) {
        while (__sync_lock_test_and_set(&lock, 1)) {} 
        shared_variable++; 
        __sync_lock_release(&lock);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, (void *)&thread_ids[i]) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining thread %d\n", i);
            return 1;
        }
    }

    printf("Shared variable value: %d\n", shared_variable);

    return 0;
}
