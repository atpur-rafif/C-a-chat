.phony: server client

client:
	mkdir -p bin
	gcc app/client.c -o bin/client

server:
	mkdir -p bin
	gcc app/server.c lib/linked_list.c -o bin/server

c: client
	bin/client

s: server
	bin/server 8080