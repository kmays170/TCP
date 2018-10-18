#include <stdlib.h>
#include <stdio.h>
#include "helper.h"

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

int main(){
	/*
	argv[1] = port server is listening to
	*/
	char server_message[256] = "You have reached the server!";
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	int port = atoi(argv[1]);
	//define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	listen(server_socket, 10);

	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);
	if (client_socket < 0)
		error("Error with the accept");
	//new code
	FILE *f;
	char buffer[255];
	int count = 0;
	int to_format = 1;
	int convert;
	f = fopen("received_file.txt", "w");
	int word_count;
	int letter_count = 0;
	read(client_socket, &word_count, sizeof(int));
	while (count != word_count)
	{
		read(client_socket, buffer, 255);
		while (((int)buffer[letter_count]) != 0)
		{
			convert = (int)buffer[letter_count];
			fprintf(f, "%d", convert);
			letter_count++;
		}
		letter_count = 0;
		count++;
	}
	printf("file received, saved under received_file.txt");
	
	// end of new code
	//send(client_socket, server_message, sizeof(server_message), 0);

	close(server_socket);

	return 0;
}
