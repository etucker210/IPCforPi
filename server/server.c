/*******************************************************************************
 *
 * Name: Server.c
 *
 * Author: Elijah A. Tucker
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

void error( char *msg )
{
  perror(msg);
  exit(1);
}

int main(int argc, char const *argv[]) {

  int sockfd, newsockfd, portno, clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  if (argc > 1)
  {
    fprintf(stderr, "ERROR, on command line\n");
    exit(1);
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
  {
    error("ERROR opening socket");
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));

  portno = 31415;

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if( bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 )
  {
    error("ERROR on binding to the socket to the client");
  }

  listen(sockfd, 5);

  clilen = sizeof(cli_addr);

  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

  if (newsockfd < 0 )
  {
    error("ERROR on accepting the socket from the client");
  }

  bzero(buffer, 256);

  n = read(newsockfd, buffer, 255);

  if ( n < 0 )
  {
    error("ERROR reading from socket from client");
  }

  printf("Here is your message : %s\n", buffer);

  n = write(newsockfd, "I got your message", 18);

  if ( n < 0 )
  {
    error("ERROR writing to socket to client");
  }

  return 0;

}
