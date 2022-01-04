#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h> 
#include <unistd.h>
#include<string.h> 
#include <arpa/inet.h>

#define PORT 2021

int main(){

        int b,sockfd,connfd,sin_size,l,n,len;
        char operator;
        int op1,op2,result;
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
                printf("socket créé avec succès\n");  

        struct sockaddr_in servaddr;              
        struct sockaddr_in clientaddr;

        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=inet_addr("192.168.1.15");
        servaddr.sin_port=PORT;

        if((bind(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr)))==0)
                printf("liaison réussie\n"); 


        if((listen(sockfd,5))==0) 
                printf("écoute réussie\n");

        sin_size = sizeof(struct sockaddr_in);
        if((connfd=accept(sockfd,(struct sockaddr *)&clientaddr,&sin_size))>0);
        printf("accepter avec succès\n");
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