#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// each proccess will have its own address space
// processes will be running in parallel
int i = 0;

void doSomeWork(char *name) {
    const int NUM_TIMES = 5;
    for ( ; i < NUM_TIMES; i++) {
        sleep(rand() % 4);
        printf("Done pass %d for %s\n", i, name);
    }
}


int main(int argc, char *argv[]) {

    printf("I am: %d\n", (int) getpid());

    pid_t pid = fork();
    
    srand((int) pid);

    printf("fork() returned: %d\n", (int) pid);

    if (pid < 0) {
        perror("Fork failed!");
    }
    
    if (pid == 0) {
        printf("I am the child with pid: %d\n", (int) getpid());
        doSomeWork("Child");
        exit(42);
    }

    // we must be the parent
    printf("I am the parent, waiting for the child to end.\n");
    doSomeWork("Parent");
    int child_status;
    pid_t child_pid = wait(&child_status);
    printf("Parent knows child %d finished with status %d.\n", (int) child_pid, child_status);
    int child_return_value = WEXITSTATUS(child_status);
    printf("    Return value was %d\n", child_return_value);
    return 0;
}

