/*******************************************************************************
 *
 * Name: client.c
 *
 * Author: Elijah A. Tucker
 *
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

  if (argc > 1)
  {
    fprintf(stderr, "ERROR: on command line");
    exit(0);
  }

  portno = 31415;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0 )
  {
    error("ERROR opening socket");
  }

  server = gethostbyname("127.0.0.0");

  if ( server == NULL )
  {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }



  return 0;
}
