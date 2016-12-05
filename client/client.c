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
  bzero(ipAddr, 16);
  fgets(ipAddr, 15, stdin);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0 )
  {
    error("ERROR opening socket to server\n");
  }

  server = gethostbyname(ipAddr);

  if ( server == NULL )
  {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;

  bcopy((char *) server->h_addr,
        (char *) &serv_addr.sin_addr.saddr,
        server->h_length);

  serv_addr.sin_port = htons(portno);

  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    error("ERROR connecting");
  }

  printf("Please enter the message: ");

  bzero(buffer, 256);
  fgets(buffer, 255, stdin);

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
