// insertion_sort.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void insertion_sort(int *V, int N)
{
    int i, j, aux;
    // start looping over V from index 1
    for (i = 1; i < N; i++) {
        aux = V[i]; // aux = 3, j = 0
        // loop for the data greater than aux on left, moving them to a next pos
        for (j = i; (j > 0) && (aux < V[j - 1]); j--)
            V[j] = V[j - 1];
        V[j] = aux;
    }
}

int main(int argc, char *argv[])
{
    printf("Child PID %d.\n", (int) getpid());

    int v[argc];

    for (int i = 0; i < argc; i++) {
        v[i] = atoi(argv[i]);
    }

    insertion_sort(v, argc);

    printf("Solution: ");
    for (int i = 0; i < argc; i++) {
        printf("%d, ", v[i]);
    }
    printf("\n");
}
