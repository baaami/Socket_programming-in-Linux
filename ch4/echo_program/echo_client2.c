/*
	echo_client
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFSIZE 1024
void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	
	struct sockaddr_in serv_addr;
	char message[BUFSIZE];
	int str_len;

	if(argc != 3)
	{
		printf("Usage : %s <IP> <PORT>\n", argv[0]);
		exit(1);
	}

	// make socket to access server
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");


	// input ip, port of server to struct object
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	
	if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
	{
		error_handling("connect() error");
	}
	
	while(1)
	{
		/* message input, transfer*/
		fputs("Please input to transfer message (q to quit) : ", stdout);	// standard output
		fgets(message, BUFSIZE, stdin);		// your input string put in message

		if(!strcmp(message,"q\n")) break;
		write(sock, message, strlen(message));

		str_len = read(sock, message, BUFSIZE-1);
		message[str_len] = 0;
		printf("Message from Server : %s\n", message);
	}
	
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
