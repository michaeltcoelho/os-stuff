#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFF_SIZE 3 /* size of shared buffer */

int buffer[BUFF_SIZE]; /* shared buffer */
int add, /* place to add next element */
    rem, /* place to remove next element */
    num = 0; /* number elements in buffer */

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* mutext lock for buffer */
pthread_cond_t consumer_cond = PTHREAD_COND_INITIALIZER; /* consumer waits on cv */
pthread_cond_t producer_cond = PTHREAD_COND_INITIALIZER; /* producer waits on cv */

void* producer(void* param) {
    int i;
    for (i = 1; i <= 20; i++) {
        pthread_mutex_lock(&mutex);
            if (num > BUFF_SIZE)
                exit(1);
            if (num == BUFF_SIZE)
                pthread_cond_wait(&producer_cond, &mutex);
            buffer[add] = i;
            add = (add + 1) % BUFF_SIZE;
            num++;
        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&consumer_cond);
        printf("Producer: inserted %d\n", i);
        fflush(stdout);
    }
    printf("Producer quiting\n");
    fflush(stdout);
    return 0;
}

void* consumer(void* param) {
    int i;
    while (1) {
        pthread_mutex_lock(&mutex);
            if (num < 0)
                exit(1);
            if (num == 0)
                pthread_cond_wait(&consumer_cond, &mutex);
            i = buffer[rem];
            rem = (rem + 1) % BUFF_SIZE;
            num--;
        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&producer_cond);
        printf("Consumed value %d\n", i);
        fflush(stdout);
    }
}

void main(int argc, char *argv[]) {
    pthread_t tid1, tid2; /* thread identifiers */

    if (pthread_create(&tid1, NULL, producer, NULL) != 0) {
        fprintf(stderr, "Unable to create producer thread\n");
        exit(1);
    }
    if (pthread_create(&tid2, NULL, consumer, NULL) != 0) {
        fprintf(stderr, "Unable to create consumer thread\n");
        exit(1);
    }
    pthread_join(tid1, NULL); /* wait for producer to exit */
    pthread_join(tid2, NULL); /* wait for consumer to exit */
    printf("Parent quiting\n");
}
