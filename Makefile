.phony: server client

client:
	mkdir -p bin
	gcc client.c -o bin/client

server:
	mkdir -p bin
	gcc server.c -o bin/server

c: client
	bin/client

s: server
	bin/server