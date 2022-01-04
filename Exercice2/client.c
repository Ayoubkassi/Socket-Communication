#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 2021
#define SA struct sockaddr


int main()
{
    char operator;
    int op1,op2,result;
	int sockfd, connfd;
	struct sockaddr_in6 servaddr, cli;

	// Creation du socket en se basant sur IPV6
	sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("la création du socket a échoué\n");
		exit(0);
	}
	else
		printf("Socket créé avec succès\n");
	memset(&servaddr, 0 ,sizeof(servaddr));

	// completer les informations additionel 
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_addr = in6addr_any;
	servaddr.sin6_port = htons(PORT);

	// connecter le client avec le serveur 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("la connexion avec le serveur a échoué\n");
		exit(0);
	}
	else
		printf("connecté au serveur\n");

	// Logique de calculatrice

    printf("Entrez une operation : ");
    scanf("%c",&operator);
    printf("Entrez 2 nombres : ");
    scanf("%d %d", &op1, &op2);

    write(sockfd,&operator,10);
    write(sockfd,&op1,sizeof(op1));
    write(sockfd,&op2,sizeof(op2));
    read(sockfd,&result,sizeof(result)); 
    printf("Résultat de calcul du serveur est : %d\n",result);

	// fermer socket
	close(sockfd);
}
