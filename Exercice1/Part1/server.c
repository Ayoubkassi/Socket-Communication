#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 80
#define PORT 2021
#define SA struct sockaddr


int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// creation du socket pour le serveur
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("la création du socket a échoué\n");
		exit(0);
	}
	else
		printf("Socket créé avec succès\n");
	memset(&servaddr, 0,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Liaison Socket serveur
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("échec de la liaison de socket\n");
		exit(0);
	}
	else
		printf("socket lié avec succès\n");

	// serveur est pret a l'ecoute
	if ((listen(sockfd, 5)) != 0) {
		printf("Échec de l'écoute\n");
		exit(0);
	}
	else
		printf("Serveur à l'écoute\n");
	len = sizeof(cli);

	// Accepter le packet de donnes du client
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("échec de l'acceptation du serveur\n");
		exit(0);
	}
	else
		printf("le serveur accepte le client\n");

	// Lancer le chat
	char buffer[MAX];
	int n;

	for (;;) {
		memset(buffer,0, MAX);
		read(connfd, buffer, sizeof(buffer));
		printf("From client: %s\t To client : ", buffer);
		memset(buffer,0, MAX);
		n = 0;
		while ((buffer[n++] = getchar()) != '\n');			
		write(connfd, buffer, sizeof(buffer));

		if (strncmp("exit", buffer, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}

	// fermer socket
	close(sockfd);
}

