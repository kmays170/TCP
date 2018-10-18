#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>

int main(int argc, char *argv[]){
	/*
	argv[1] = server IP
	argv[2] = server port
	argv[3] = file path
	argv[4] = to format
	argv[5] = to name
	*/
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	int server_port = atoi(argv[2]);
	int to_format = atoi(argv[4]);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(server_port);
	server_address.sin_addr.s_addr = inet_addr(argv[1]);
	
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	//checking for connection error
	if (connection_status == -1){
		printf("There was an error creating the connection \n\n");
	}
	//code for sending the file name
	char to_file[sizeof(argv[5])];
	strcpy(to_file, argv[5]);
	send(network_socket, to_file, sizeof(to_file), NULL);
	// new code
	char buffer[255];
	FILE *rfile;
	int words = 0;
	char c;
	rfile = fopen(argv[3], "r");
	//copies the text in the file with no spaces
	while ((c = getc(rfile)) != EOF)
	{
		fscanf(rfile, "%s", buffer);
		if (!isspace(c) || c != '\t')
			words++;
	}
	write(network_socket, &words, sizeof(int));
	rewind(rfile);
	char check;
	while (check != EOF)
	{
		//printf(check);
		fscanf(rfile, "%s", buffer);
		write(network_socket, buffer, 255);
		check = fgetc(rfile);
	}
	//end of new code
	printf("The server successfully sent the data\n", server_response);

	close(network_socket);
	return 0;
}
