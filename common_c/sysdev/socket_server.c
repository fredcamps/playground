#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#define PROTOCOL          0
#define PORT              8002
#define FAMILY            AF_INET
#define TYPE              SOCK_STREAM
#define MAX_PENDING_CONNS 10
#define REUSE_ADDR        1
#define BUFFER_SIZE       1024


int get_socket_descriptor()
{
  return socket(FAMILY, TYPE, PROTOCOL);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in _server, _client;
    char str_ip[INET_ADDRSTRLEN];
    char buffer[BUFFER_SIZE];
    socklen_t client_addr_len = sizeof(_client);
    bzero(&_server, sizeof(_server));
    _server.sin_addr.s_addr = htonl(INADDR_ANY);
    _server.sin_family = FAMILY;
    _server.sin_port = htons(PORT);
    int sock_descriptor = get_socket_descriptor();
    setsockopt(sock_descriptor, SOL_SOCKET, SO_REUSEADDR, NULL, sizeof(REUSE_ADDR));
    int conn = bind(sock_descriptor, (struct sockaddr *)&_server, sizeof(_server));
    int lis = listen(sock_descriptor, MAX_PENDING_CONNS);

    if (conn < 0) {
        fprintf(stderr, "Error to bind server!");
        exit(1);
    }
    if (lis < 0) {
        fprintf(stderr, "Error when listen port!");
        exit(1);
    } else {
        fprintf(stdout, "Server listening connection on port %d\n", PORT);
    }

    while (1) {
        int cli_sock_fd = accept(sock_descriptor, (struct sockaddr *)&_client, &client_addr_len);
        if (cli_sock_fd < 0) {
            fprintf(stderr, "Error when estabilish connection!");
            exit(1);
        } else {
            fprintf(stdout,
                    "Server accepted a client %s\n",
                    inet_ntop(FAMILY, &_client.sin_addr, str_ip, INET_ADDRSTRLEN));
        }

        sleep(1);

        if (0 > recv(cli_sock_fd, buffer, BUFFER_SIZE, 0)) {
            fprintf(stderr, "Error when retrieve data from buffer \n");
        }
        fprintf(stdout, "%s\n", buffer);

    }

    close(sock_descriptor);

    return 0;
}
