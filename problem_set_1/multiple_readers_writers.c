#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_THREADS 5

int counter = 0, // shared state
    counter_state = 0; // represents the shared counter's state
                       // 0 - it's free for readers or writers
                       // 1 to NUM_THREADS - it's in reading mode 
                       // -1 - it's in writing mode 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Global Mutex

pthread_cond_t write_mode = PTHREAD_COND_INITIALIZER; // Read condition variable
pthread_cond_t read_mode = PTHREAD_COND_INITIALIZER; // Write condition variable


void* reader() {
    sleep(rand() % 4);

    pthread_mutex_lock(&mutex);
        while (counter_state == -1)
            pthread_cond_wait(&read_mode, &mutex);
        counter_state++;
    pthread_mutex_unlock(&mutex);

    printf("[%d Readers] Counter = %d\n", counter_state, counter);

    pthread_mutex_lock(&mutex);
        counter_state--;
        if (counter_state == 0)
            pthread_cond_signal(&write_mode);
    pthread_mutex_unlock(&mutex);
    fflush(stdout);
}

void* writer() {
    sleep(rand() % 3);

    pthread_mutex_lock(&mutex);
        while (counter_state != 0)
            pthread_cond_wait(&write_mode, &mutex);
        counter_state = -1;
    pthread_mutex_unlock(&mutex);

    printf("[%d Readers] Before writing to counter %d\n", counter_state, counter);

    counter++;

    printf("[%d Readers] After writing to counter %d\n", counter_state, counter);

    pthread_mutex_lock(&mutex);
        counter_state = 0;
        pthread_cond_broadcast(&read_mode);
        pthread_cond_signal(&write_mode);
    pthread_mutex_unlock(&mutex);

    printf("Writter quitting\n");
    fflush(stdout);
}

void wait_for(pthread_t* ids) {
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(ids[i], NULL);
    }
}

void spawn_threads(pthread_t* ids, void *(*f)()) {
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&ids[i], NULL, f, NULL);
    }
}

int main(void) {
    srand((int)getpid());

    pthread_t readers_id[NUM_THREADS];
    pthread_t writers_id[NUM_THREADS];

    spawn_threads(readers_id, reader);
    spawn_threads(writers_id, writer);

    wait_for(readers_id);
    wait_for(writers_id);
}
