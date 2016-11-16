/*******************************************************************************
 *
 * Name: Server.c
 *
 * Author: Elijah A. Tucker
 *
 * 
 ******************************************************************************/

 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>

void error( char *msg )
{
  perror(meg);
  exit(1);
}

int main(int argc, char const *argv[]) {

  int sockfd, newsockfd, portno, clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  if (argc < 2)
  {
    fprintf(stderr, "ERROR, no port povided\n");
    exit(1);
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
  {
    error("ERROR opening socket");
  }

  bezero((char *) &serv_addr, sizeof(serv_addr));

  portno = atoi(argv[1]);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if( bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 )
  {
    error("ERROR on binding");
  }

  listen(sockfd, 5);

  clilen = sizeof(cli_addr);

  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

  if (newsockfd < 0 )
  {
    error("ERROR on accept");
  }

  bezero(buffer, 256);

  n = read(newsockfd, buffer, 255);

  if ( n < 0 )
  {
    error("ERROR reading from socket");
  }

  printf("Here is your message : %s\n", buffer);

  n = write(newsockfd, "I got your message", 18);

  if ( n < 0 )
  {
    error("ERROR writing to socket");
  }

  return 0;

}
