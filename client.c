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
#define RECEIVER_HOST "anaconda3.uml.edu" /* Server machine */
/* Declaring errno */
extern int errno;
/* Function for error */
void report_error(char *s)
{
 printf("sender: error in %s, errno = %d\n",s,errno);
 exit(1);
}
/* Giving 'size' of message dynamically as argument */
void main(int argc, char *argv[])
{
 int s,i;
 int BUFSIZE = atoi(argv[1]);
 char msg[BUFSIZE];
 char received[BUFSIZE];
 struct sockaddr_in sa= {0};
 int length = sizeof(sa);
struct hostent *hp;
 printf("Enter the message to be sent: \n");
 scanf("%s",msg);
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
 printf("Socket= %d\n",s);
 /* Sending the message to server and returns error if unsuccesfull */
 if(sendto(s, msg, BUFSIZE, 0, (struct sockaddr *) &sa, length)== -1)
 report_error("sendto");
 /* Receives message from server and returns error if unsuccesfull */
 recvfrom(s, received, BUFSIZE, 0, (struct sockaddr *) &sa, &length);
 printf("%s\n",received);
 close(s);
}