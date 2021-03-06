/*
Operating Systems and Kernel Design
Assignment 4
Client and Server Communication
Farshad Chowdhury
December 11, 2017
Client.c
This program sends a message to a server and times out if the server
does not respond in time.

*/



#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<errno.h>
#include<arpa/inet.h>
#include<string.h>
#include <pthread.h>
#include <semaphore.h>
#define RECEIVER_HOST "anaconda3.uml.edu" /* Server machine */
/* Declaring errno */
extern int errno;
char received[50]="Empty";
int BUFSIZE = 50;
void sendMSG(char *msg);

/* Function for error */
void report_error(char *s)
{
 printf("sender: error in %s, errno = %d\n",s,errno);
 exit(1);
}
void main(int argc, char *argv[])
{
  int lpchk=1;
  while(lpchk==1){
    char msg[BUFSIZE];
    int loopchk=0;
    strcpy(received,"Empty");
    printf("Enter the message to be sent: \n"); //User prompted for message
    scanf("%s",msg);
    if(strcmp(msg,"quit")==0){
      lpchk= 0;
      exit(1);
    }
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    while(loopchk<3){ //loop used to retry message sending
      pthread_create(&tid,&attr,sendMSG,msg); // thread created to send message
      sleep(3);// main thread sleeps for three seconds before checking array
      if(strcmp(received,"Empty")==0){
        printf("Server did not respond..trying again\n");
        pthread_cancel(tid);
        if(loopchk==2)
        printf("Server did not respond after three attempts \n");
        loopchk++;
      }else{
        loopchk=5;
      }
    }
  }
}
void sendMSG(char *msg){

  int s,i;

  struct sockaddr_in sa= {0};
  int length = sizeof(sa);
  struct hostent *hp;

  /* FILL SOCKET ADDRESS*/
  if((hp = gethostbyname(RECEIVER_HOST))==NULL)
  report_error("gethostbyname");
  bcopy((char*)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
  sa.sin_family = hp->h_addrtype;
  sa.sin_port = htons(0213 + 20000); /* define port
  number based on student ID*/
  /* Creating the socket and returns error if unsuccessfull */
  if((s=socket(AF_INET, SOCK_DGRAM, PF_UNSPEC))== -1)
  report_error("socket");
  /* Sending the message to server and returns error if unsuccesfull */
  if(sendto(s, msg, BUFSIZE, 0, (struct sockaddr *) &sa, length)== -1)
  report_error("sendto");
  printf("message sent!\n");
  /* Receives message from server and returns error if unsuccesfull */
  recvfrom(s, received, BUFSIZE, 0, (struct sockaddr *) &sa, &length);
  printf("%s\n",received);
  close(s);

}
