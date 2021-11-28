all: server client

server: 
	g++ src/server.cpp -o server -pthread

client:
	g++ src/client.cpp -o client -pthread

clean:
	rm server
	rm client
