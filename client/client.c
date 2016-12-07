/*******************************************************************************
 *
 * Name: client.c
 *
 * Author: Elijah A. Tucker
 *
 *
 *
 * This code was addapted from the socket code found on
 * http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
 *
 ******************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error( char *msg )
{
  perror(msg);
  exit(0);
}

int main(int argc, char const *argv[])
{

  int sockfd, portno, n;

  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];
  char ipAddr[16];

  if (argc > 1)
  {
    fprintf(stderr, "ERROR: on command line\n");
    exit(0);
  }

  portno = 31415;

  printf("Enter the server IP Address: ");
  
  scanf("%s", &ipAddr);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0 )
  {
    error("ERROR opening socket to server\n");
  }


  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(ipAddr);
  serv_addr.sin_port = htons(portno);

  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    error("ERROR connecting");
  }

  printf("Please enter the message: ");

  bzero(buffer, 256);
  scanf("%s", &buffer);

  n = write(sockfd, buffer, strlen(buffer));

  if ( n < 0 )
  {
    error("ERROR writing to socket");
  }

  bzero(buffer, 256);
  n = read(sockfd, buffer, 255);

  if ( n < 0 )
  {
    error("ERROR reading from socket");
  }

  printf("%s\n", buffer);

  return 0;
}
