#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 2021
#define SA struct sockaddr



int main()
{
        char operator;
        int op1,op2,result;

	int sockfd, connfd, len;
	struct sockaddr_in6 servaddr, cli;

        //craetion du socket
	sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("la création du socket a échoué\n");
		exit(0);
	}
	else
		printf("Socket créé avec succès\n");
	memset(&servaddr, 0 ,sizeof(servaddr));

	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_addr = in6addr_any;
	servaddr.sin6_port = htons(PORT);

        //connecter le serveur avec le client
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("a connexion avec le serveur a échoué\n");
		exit(0);
	}
	else
		printf("connecté au serveur\n");

	// serveur pret a ecouter
	if ((listen(sockfd, 5)) != 0) {
		printf("Échec de l'écoute\n");
		exit(0);
	}
	else
		printf("serveur à l'écoute\n");
	len = sizeof(cli);

	// Accepter les donnes du client
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("échec de l'acceptation du serveur\n");
		exit(0);
	}
	else
		printf("le serveur accepte le client\n");

	// Logique du calculatrice
	read(connfd, &operator,10);
        read(connfd,&op1,sizeof(op1));
        read(connfd,&op2,sizeof(op2));

        switch(operator) {
                case '+': result=op1 + op2;
                printf("Resultat  de (+) est : %d + %d = %d\n",op1, op2, result);
                break;
                case '-':result=op1 - op2;
                        printf("Resultat de (-) est: %d - %d = %d\n",op1, op2, result);
                        break;
                case '*':result=op1 * op2;
                        printf("Resultat de (*) est: %d * %d = %d\n",op1, op2, result);
                        break;
                case '/':result=op1 / op2;
                        printf("Resultat de (/) est : %d / %d = %d\n",op1, op2, result);
                        break;
                default: 
                        printf("Opration n\'existe pas");
        }
  
        write(connfd,&result,sizeof(result));  

	close(sockfd);
}
