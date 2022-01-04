#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h> 
#include <unistd.h>
#include<string.h> 
#include<strings.h>
#include <arpa/inet.h>

#define PORT 2021


int main(){

    int b,sockfd,sin_size,con,n,len;
    char operator;
    int op1,op2,result;

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
        printf("socket created sucessfully\n");
    struct sockaddr_in servaddr;

    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=inet_addr("192.168.1.15");
    servaddr.sin_port=PORT;

    sin_size = sizeof(struct sockaddr_in);
    if((con=connect(sockfd,(struct sockaddr *) &servaddr, sin_size))==0); 
    printf("connexion réussie\n");
    printf("Entrez une operation : ");
    scanf("%c",&operator);
    printf("Entrez 2 nombres :\n");
    scanf("%d %d", &op1, &op2);

    write(sockfd,&operator,10);
    write(sockfd,&op1,sizeof(op1));
    write(sockfd,&op2,sizeof(op2));
    read(sockfd,&result,sizeof(result)); 
    printf("Résultat de calcul du serveur est : %d\n",result);  
    
close(sockfd);

}