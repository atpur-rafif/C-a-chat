#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct Connection{
    int file_descriptor;
} Connection;

#define DEFINE_LIST_GENERIC_IMPLEMENTATION
#define TYPE Connection
#include "./lib/list/generic.h"

int channel[2];
#define READ_END 0
#define WRITE_END 1

typedef struct ThreadParam{
    int file_descriptor;
} ThreadParam;

typedef struct PipeProduct{

} PipeProduct;

void* runner(void* rawParam){
    ThreadParam* param = rawParam;
    int connection = param->file_descriptor;

    write(connection, "Hello, world", 1);
    return 0;
}

int main(int argc, char** argv){
    if(argc != 2){
        printf("Please provide port to listen.\n");
        return 0;
    }

    // Communicating between child thread and main thread
    pipe(channel);

    // Setting up for TCP connection
    int port = atoi(argv[1]);
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = INADDR_ANY
    };
    (void)bind(server_socket, (struct sockaddr*) (&server_address), sizeof(server_address));
    listen(server_socket, 16);

    while(1){
        int connection = accept(server_socket, NULL, NULL);
        ThreadParam param = {
            .file_descriptor = connection
        };

		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, runner, &param);
	}

    return 0;
}