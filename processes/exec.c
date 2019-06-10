#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("exec: My PID is %d.\n", (int) getpid());

    char *args[] = {"./helloExec", "Hello", "World", NULL};

    execvp("./helloExec", args);

    // execvp will be the last function executed
    // then the current process will be replaced by the new program
    printf("Will not print out!!.\n");

    return 0;
}
