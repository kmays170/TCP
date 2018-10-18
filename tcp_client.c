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
	network_socket = socket(AF_INET, SOCK_STREAM, 0);//creates the socket
	int server_port = atoi(argv[2]); //converts the server port number string argument into an integer
	int to_format = atoi(argv[4]); //converts the to format string argument into an integer
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(server_port);
	server_address.sin_addr.s_addr = inet_addr(argv[1]);//takes in the first argument as the IP address
	
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address)); //establishes connection
	//checking for connection error
	if (connection_status == -1){
		printf("There was an error creating the connection \n\n");
	}
	//code for sending the file name
	char to_file[sizeof(argv[5])];
	strcpy(to_file, argv[5]); //places the 5th argument into to_file
	send(network_socket, to_file, sizeof(to_file), NULL); //sends the to file to the server socket with no flags
	// code for opening the file
	char buffer[255];
	FILE *rfile;
	int words = 0;
	char c; // variable for each character pulled from the file
	rfile = fopen(argv[3], "r"); //opens the file under the name given by the 3rd argument
	//copies the text in the file with no spaces
	while ((c = getc(rfile)) != EOF) //while not at the end of the file get each character
	{
		fscanf(rfile, "%s", buffer); 
		if (!isspace(c) || c != '\t') //if the character isn't a space or /t, increment the word count
			words++;
	}
	write(network_socket, &words, sizeof(int)); //send the number of words to the server
	rewind(rfile);//sets the file position back to the beginning of the file
	char check;
	while (check != EOF) //while check is not a EOF character
	{
		//printf(check);
		fscanf(rfile, "%s", buffer); //read in each character
		write(network_socket, buffer, 255); //send the character to the server socket
		check = fgetc(rfile); //retrieves the next character
	}
	//end of new code
	printf("The server successfully sent the data\n", server_response); //lets the user know the data was ent

	close(network_socket); //close the socket
	return 0;
}
