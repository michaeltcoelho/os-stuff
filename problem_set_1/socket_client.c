#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    
    int clientSocket = 0, readStatus = 0;
    char buffer[1024];

    struct sockaddr_in clientAddr;

    memset(buffer, '0', sizeof(buffer));

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        printf("Fail when creating socket...");
        return 1;
    }

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(2019);
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int connected = connect(clientSocket, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
    if (connected < 0) {
        printf("Connection fail due to ip and port issues...\n");
        return 1;
    }

    while ((readStatus = read(clientSocket, buffer, sizeof(buffer))) > 0) {
        printf("Buffer: %s", buffer);
        printf("\n");
    }

    if (readStatus < 0) {
        printf("STDIN error...");
    }
    return 0;
}
