#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILDREN 4

int main(int argc, char *argv)
{
    printf("Parent PID: %d.\n", (int) getpid());

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("Fork failed...");
            exit(1);
        }
        
        if (pid == 0) {
            printf("Forked child..\n.");
            char *args[] = {"./insertion_sort", 
                "2", "1", "3", "4", "5",
                "6", "8", "7", "9", "10",
                NULL};
            execv(args[0], args);
        }
    }

    printf("Parent process is waiting on child proces.\n");
    
    for (int i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }

    return 0;
}
