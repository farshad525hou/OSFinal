/*
Operating Systems and Kernel Design
Assignment 4
Client and Server Communication
Farshad Chowdhury
December 11, 2017
Server.c
This program handles messages sent by a client. It can execute a number
of different actions depenedent on the message sent by the client.
*/


#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<strings.h>
#include<string.h>
#define RECEIVER_HOST "anaconda3.uml.edu" /* Server machine */
/* Declaring errno */
extern int errno;
/* Function for printing error */
void report_error(char *s)
{
 printf("receiver: error in%s, errno = %d\n", s, errno);
 exit(1);
}
/* Dynamically giving the 'size' of message as argument */
void main(int argc, char *argv[])
{
  while(1){
    int size=50;
    int s;
    char m[200]="Request received!";
    char test[200]="list";
    char response[size];
    char msg[size];
    struct sockaddr_in sa = {0}, r_sa = {0};
    int r_sa_l = sizeof(r_sa);
    int len;
    int backlog = 5;
    struct hostent *hp;
    socklen_t length;
    printf("waiting for message\n");
    strcpy(response,m);
    /* Creating the socket and returns error if unsuccesfull */

    if((s= socket(AF_INET, SOCK_DGRAM, PF_UNSPEC)) == -1)
    report_error("socket");

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr=INADDR_ANY;
    sa.sin_port = htons(0213+ 20000); /* define port
    number based on student ID*/

    /* Binding the socket and returns error if unsuccesfull */

    if(bind(s, (struct sockaddr *)&sa, sizeof(sa))== -1)
    report_error("bind");

    listen(s, 10);
    length = sizeof(r_sa);
    /* Receiving message from client and returns error if unsuccessfull */

    if((len = recvfrom(s, msg, size, 0, (struct sockaddr *)&r_sa, &r_sa_l))== -1)
    report_error("recvfrom");
    printf("%s\n",msg);
    //series of if and else statements to execute different function based on client message
    if (strcmp(msg,"list")==0){
      system("pwd");
      sendto(s,response,size,0,(struct sockaddr *)&r_sa,r_sa_l);
      close(s);
    }
    else if(strcmp(msg,"quit")==0){
      char quiting[50]="Exiting Now";
      sendto(s,quiting,size,0,(struct sockaddr *)&r_sa,r_sa_l);
      exit(1);

    }
    else if(strcmp(msg,"cd")==0){
      chdir("/home/fchowdhury");
      sendto(s,response,size,0,(struct sockaddr *)&r_sa,r_sa_l);
    }else if(strcmp(msg,"nothing")==0){
      char nothing[50]="Im doing nothing!";
      sendto(s,nothing,size,0,(struct sockaddr *)&r_sa,r_sa_l);
    }
    else{
      sendto(s,response,size,0,(struct sockaddr *)&r_sa,r_sa_l);
      close(s);
    }
  }
}
