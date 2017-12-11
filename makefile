all: server client
server:

	gcc server.c -o server
client:
	gcc client.c -pthread -o client
	
clean: 
	rm server
	rm client