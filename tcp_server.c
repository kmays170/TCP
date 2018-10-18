#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

//function to translate an integer from dec to binary
int Dec_to_Binary(int arg)
{
	int binary;
	int remainder;
	//the quotient is initialized with the argument
	int quotient = arg;
	//set binary string to have up to 255 characters
	char binary_string[255];
	int index = 0;
	// when the quotient is 0, the calculation can stop
	while (quotient != 0)
	{
		quotient = quotient / 2; // first divide quotient by 2
		remainder = quotient % 2; //then get the remainder
		binary_string[index] = (char)remainder; // the remainder goes into the array for binary characters
		index++; //increment the index
	}
	binary = (int)binary_string; // cast the binar char array as an integer
	return binary;
}
int main(){
	/*
	argv[1] = port server is listening to
	*/
	//initial test message I used for connecting the server to the client
	char server_message[256] = "You have reached the server!";
	int server_socket;
	int port = atoi(argv[1]); //the port value is the value from the first argument (server port)
	server_socket = socket(AF_INET, SOCK_STREAM, 0); //creates the socket
	//Socket creation check
	if (server_socket < 0)
	{
		printf("Socket creation error\n");
		exit(2);
	}
	//define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	listen(server_socket, 10); //passive socket waiting to accept a connection request, with a max of 10 possible pending connections in the queue

	char to_file[255]; //will be used as the buffer for receiving the file name
	int index = 0;
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL); //accepts the connection to the client socket
	// Socket accept check
	if (client_socket < 0)
		error("Error with the accept");
	//code for receiving the to_name argument from the client
	recv(client_socket, to_file, sizeof(to_file), NULL);
	char file_name[sizeof(to_file)]; //the variable that will be used in the fopen code
	strcpy(file_name, to_file); //takes the chars in to_file and places them into file_name

	//Code for opening the file specified in to_file, and writing the translated code to it
	FILE *f;
	char buffer[255];
	int count = 0; //used for the index in the while loop to make sure there are only as many loops as there are words in the file
	int to_format = 1; //set to_format to 1 since there is currently only one type of translation
	int convert; //initialize the variable to hold the converted value
	f = fopen(file_name, "w"); // opens/creates the specified file
	int word_count;
	int letter_count = 0;
	read(client_socket, &word_count, sizeof(int)); //retrieves number of words in the file
	while (count != word_count) // while there are still words left in the file
	{
		read(client_socket, buffer, 255); //read the word and place it in buffer
		while (((int)buffer[letter_count]) != 0) //while the current character is not a null character
		{
			convert = (int)buffer[letter_count];// cast the character into its decimal form
			fprintf(f, "%d", convert);// write this converted value to the file
			letter_count++; //increment letter count
		}
		letter_count = 0; //reset the letter count to 0
		count++;// increment count
	}
	printf("file received, saved under %s\n", file_name ); //let the user know the file has been received
	
	// end of new code

	close(server_socket); //close the socket

	return 0;
}
