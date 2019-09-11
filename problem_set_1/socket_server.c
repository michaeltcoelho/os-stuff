#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main() {
    char buffer[1024];

    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;

    int welcomeSocket = 0, newSocket = 0;

    welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serverAddr, '0', sizeof(serverAddr));
    memset(buffer, '0', sizeof(buffer));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2019);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(welcomeSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(welcomeSocket, 20);

    socklen_t addr_size;
    addr_size = sizeof(serverStorage);
    
    while (1) {
        printf("\nRunning server...waiting for clients...\n\n");

        newSocket = accept(welcomeSocket, (struct sockaddr*)&serverStorage, &addr_size);
        
        printf("here Here Hre Hrer djfsjfngdf");

        strcpy(buffer, "Hello World..\n");

        write(newSocket, buffer, strlen(buffer));

        close(newSocket);
        sleep(1);
    }

    return 0;
}
