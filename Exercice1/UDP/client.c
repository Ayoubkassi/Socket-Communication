#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#define PORT	2021
#define MAXLINE 1024

int main() {
	int sockfd;
	char buffer[MAXLINE];
	char message[200];
    printf("Entrez un message : ");
    fgets(message,200,stdin);
    message[strlen(message)-1] = '\0';
	struct sockaddr_in	 servaddr;

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("la création du socket a échoué");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int n, len;
	
	sendto(sockfd, (const char *)message, strlen(message),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf(" message envoye.\n");
		

	close(sockfd);
	return 0;
}
