#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAX 80
#define PORT 2021
#define SA struct sockaddr


int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// Creer Socket pour le client en se basant sur TCP , et Ipv4
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("la création du socket a échoué \n");
		exit(0);
	}
	else{
		printf("Socket créé avec succès\n");
	}

	memset(&servaddr, 0 ,sizeof(servaddr));


	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.15");
	servaddr.sin_port = htons(PORT);

	// connecter le socket de client avec le socket du serveur
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("la connexion avec le serveur a échoué\n");
		exit(0);
	}
	else
		printf("connecté au serveur\n");

	// demarrer le chat

	char buffer[MAX];
	int n;

	//demarrer une boucle infinie de chat
	for(int k=0;k<1;k++) {

		//memset -> permet de mettre en zero une zone memoire en C
		memset(buffer, 0 ,sizeof(buffer));
		printf("Entrer votre message : ");
		n = 0;
		while ((buffer[n++] = getchar()) != '\n')
			;
		write(sockfd, buffer, sizeof(buffer));
		memset(buffer, 0 ,sizeof(buffer));
		read(sockfd, buffer, sizeof(buffer));
		//printf("Du Serveur : %s", buffer);

		//pour quitter le chat
		if ((strncmp(buffer, "exit", 4)) == 0) {
			printf("Sortie client ...\n");
			break;
		}
	}

	// fermer socket
	close(sockfd);
}

