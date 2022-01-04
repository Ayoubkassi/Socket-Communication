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
	struct sockaddr_in servaddr, cliaddr;
	
	// creer le descripteur du fichier socket
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("la création du socket a échoué");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// liaison du  serveur socket avec l'adresse
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("échec de la liaison");
		exit(EXIT_FAILURE);
	}

	printf("socket lié avec succès\n");
	
	int len, n;

	len = sizeof(cliaddr); 
		printf("Serveur à l'écoute\n");

	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);

	buffer[n] = '\0';
	printf("Client : %s\n", buffer);
	printf("message envoyé.\n");
	
	return 0;
}
