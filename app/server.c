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
#define BUFFER_SIZE 128

typedef struct ThreadParam{
    int file_descriptor;
} ThreadParam;

typedef struct PipeProduct{

} PipeProduct;

void* listener(void* rawParam){
    ThreadParam* param = rawParam;
    int connection = param->file_descriptor;

    printf("Connected\n");
    char buffer[BUFFER_SIZE];
    while(1){
        int count = read(connection, buffer, BUFFER_SIZE - 2);
        if(count == 0) break;

        write(channel[WRITE_END], buffer, count);
        fflush(fdopen(channel[WRITE_END], "w"));
    }
    printf("Disconnected\n");

    return 0;
}

void* broadcaster(void* _){
    while(1){
        char buffer[BUFFER_SIZE];
        int count = read(channel[READ_END], buffer, BUFFER_SIZE - 2);
        buffer[count] = '\0';
        printf("Incoming (%d): %s", count, buffer);
        fflush(stdout);
        fflush(stdout);
    }
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
    int err;
    int port = atoi(argv[1]);
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = INADDR_ANY
    };

    err = bind(server_socket, (struct sockaddr*) (&server_address), sizeof(server_address));
    if(err == -1){
        printf("Can't bind server\n");
        return 0;
    }

    err = listen(server_socket, 16);
    if(err == -1){
        printf("Can't listen to port\n");
        return 0;
    }

    // One thread for broadcasting all data
    pthread_t broadcastThread;
	pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&broadcastThread, &attr, broadcaster, NULL);

    // Main thread manage initial connection 
    while(1){
        int connection = accept(server_socket, NULL, NULL);
        ThreadParam param = {
            .file_descriptor = connection
        };

		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, listener, &param);
	}

    return 0;
}