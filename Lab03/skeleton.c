#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* handle_client(void*);

int main() {
    int listenfd;
    int* connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(32000);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 5);
    clilen = sizeof(cliaddr);

    while (1) {
        connfd = malloc(sizeof(int));
        *connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, connfd);
        pthread_detach(thread_id); // Detach the thread to handle cleanup automatically
    }
}

void* handle_client(void* connfd) {
    int sock = *(int *)connfd;
    free(connfd);
    char buffer[1024];
    read(sock, buffer, sizeof(buffer));
    printf("Client says: %s\n", buffer);
    write(sock, "Hello from the server", 21);
    close(sock);
    return NULL;
}
