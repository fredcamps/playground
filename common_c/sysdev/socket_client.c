#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 8002
#define PROTOCOL    0
#define FAMILY      AF_INET
#define TYPE        SOCK_STREAM
#define BUFFER_SIZE 1024

int get_socket_descriptor()
{
  return socket(FAMILY, TYPE, PROTOCOL);
}


int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];
    int socket_fd = get_socket_descriptor();
    struct sockaddr_in server_socket_addr;

    bzero(&server_socket_addr, sizeof(server_socket_addr));
    server_socket_addr.sin_family = FAMILY;
    server_socket_addr.sin_port = htons(SERVER_PORT);
    server_socket_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    int conn = connect(socket_fd, (struct sockaddr *)&server_socket_addr, sizeof(server_socket_addr));
    if (conn < 0) {
        fprintf(stderr, "Error when connect to server\n");
        exit(1);
    } else {
        fprintf(stdout, "Connect to %s on port: %d\n", SERVER_ADDR, SERVER_PORT);
    }

    fprintf(stdout, "Enter a message to send to server: ");
    scanf("%s", buffer);
    send(socket_fd, buffer, BUFFER_SIZE, 0);

    close(socket_fd);
    return 0;
}
