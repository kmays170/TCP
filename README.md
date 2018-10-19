# TCP
Application Protocol
Application Architecture:
	For this TCP Project, I used the Client/Server architecture, as specified in the instructions
Message types:  
	My message type is request/response.
Message syntax: 
•The format of the messages: The message syntax that I used is that each message contains one or more ASCII characters  
•The meaning of each field in the format: For the client, with the format <client> <server IP> <server port> <file path> <to format> <to name>,<client> is the name of the client file name with the path (i.e ./tcp_client), <server IP> is the IP address of the server (i.e 127.0.0.1), <server port> is the TCP port of the server (i.e 9002), <file path> is the path of the file to be sent from the server, or just the name if the file is in the same directory (i.e practice.txt),<to_format> tells the server how to translate the file (i.e 1),<to name> tells the server what file to write the translation to (i.e rec.txt). For the server, with the format <server> <port>:<server> is the name of the server file name with the path (i.e ./tcp_server), and <port> is the port the server is listening to (i.e 9002)
•The value range of each field: For my char values, I used an array size of 255
•Why/how do we distinguish between multiple messages?: For this assignment, I focused on setting up the client/server code with only one message being passed
Processing rules:
 	The request is sent by the client, the response is sent by server. The server code must be run before the client code is run, otherwise an error message will be printed to the screen.

Running my code:
	In order to run my code, I used Ubuntu, opened two windows, and navigated to the directory where my files (tcp_server and tcp_client) were located. I then ran the make command for both tcp_client and tcp_server to make sure everything was up to date and error free. Then I ran ./tcp_server <port> in one window first, and ./tcp_client <server IP> <server port> <file path> <to format> <to name> in the other window after.
  
Issues/Known Problems:
	I had difficulties with the unit translation code, so I decided to stick to one type of translation. Although my code reads in the “to format” argument, this value is never used since there is only one type of translation taking place. Therefore, I wasn’t able to use the test cases that focuses on the to_format, as entering in any of the to_format values will give the same result. Also, I wasn’t able to create a server socket where the socket remained open after reading and translating the data sent by the client, so it always closes after it is done. 

References/Code Bases:
	Other than the slides and the textbook, I used the following youtube tutorials to guide me through socket programming:
	https://www.youtube.com/watch?v=LtXEMwSG5-8
	https://www.youtube.com/watch?v=V6CohFrRNTo&t=840s
	https://www.youtube.com/watch?v=9g_nMNJhRVk&t=863s
	https://www.youtube.com/watch?v=2qQTMbYSJGs 
	I also used the c-language definitions developed by IEEE and The Open Group (http://pubs.opengroup.org/onlinepubs/009695399/mindex.html) 
