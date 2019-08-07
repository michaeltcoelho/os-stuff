#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void* foo(void *pArg) {
    int myNum = *((int*)pArg);
    printf("Thread number %d\n", myNum);
    return 0;
}

int main(void) {
    int i;
    int tNum[NUM_THREADS];
    pthread_t tid[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++) {
        tNum[i] = i;
        pthread_create(&tid[i], NULL, foo, &tNum[i]);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
    return 0;
}
