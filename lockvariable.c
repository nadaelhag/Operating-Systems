#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

int shared_variable = 0; 
pthread_mutex_t lock;    

void *thread_function(void *arg) {
    int thread_id = *((int *)arg);
    pthread_mutex_lock(&lock);
    printf("Thread %d is accessing the critical section\n", thread_id);
    shared_variable++; 
    printf("Thread %d updated the shared variable to %d\n", thread_id, shared_variable);
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    pthread_mutex_init(&lock, NULL); 
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
    pthread_mutex_destroy(&lock); 

    return 0;
}
