#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char** argv){
    if(argc != 2){
        printf("Please provide port to listen.\n");
        return 0;
    }

    int port = atoi(argv[1]);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = INADDR_ANY
    };

    (void)bind(server_socket, (struct sockaddr*) (&server_address), sizeof(server_address));
    listen(server_socket, 16);

    int connection = accept(server_socket, NULL, NULL);
    write(connection, "test", 4);

    return 0;
}