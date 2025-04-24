#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5

typedef struct {
    int next_ticket;
    int now_serving;
    pthread_mutex_t lock; // protects access to next_ticket
    sem_t queue[NUM_THREADS]; // array of semaphores (one per thread)
} fair_mutex_t;

fair_mutex_t fair_mutex;

void fair_mutex_init(fair_mutex_t *fm) {
    fm->next_ticket = 0;
    fm->now_serving = 0;
    pthread_mutex_init(&fm->lock, NULL);
    for (int i = 0; i < NUM_THREADS; ++i)
        sem_init(&fm->queue[i], 0, 0);
}

void fair_mutex_lock(fair_mutex_t *fm, int *my_ticket) {
    pthread_mutex_lock(&fm->lock);
    *my_ticket = fm->next_ticket++;
    pthread_mutex_unlock(&fm->lock);

    // Wait until it's our turn
    while (*my_ticket != fm->now_serving) {
        sem_wait(&fm->queue[*my_ticket]); // wait for turn
    }
}
;
void fair_mutex_unlock(fair_mutex_t *fm) {
    fm->now_serving++;
    if (fm->now_serving < NUM_THREADS)
        sem_post(&fm->queue[fm->now_serving]); // allow next thread
}

void* thread_func(void *arg) {
    int id = *(int*)arg;
    int my_ticket;

    printf("Thread %d wants the lock\n", id);
    fair_mutex_lock(&fair_mutex, &my_ticket);

    printf("Thread %d has the lock (ticket %d)\n", id, my_ticket);
    sleep(1); // Simulate some work
    printf("Thread %d is releasing the lock\n", id);

    fair_mutex_unlock(&fair_mutex);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    fair_mutex_init(&fair_mutex);

    for (int i = 0; i < NUM_THREADS; ++i) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &ids[i]);
        sleep(1); // Add delay to observe ordering
    }

    for (int i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], NULL);

    printf("All threads finished.\n");
    return 0;
}
