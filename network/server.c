#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include "server.h"


int main ()
{
  struct sockaddr_in serverInfo = {0};

  serverInfo.sin_family = AF_INET;
  serverInfo.sin_addr.s_addr = INADDR_ANY;
  serverInfo.sin_port = htons (PORT);
  int sockfd = socket (AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    {
      perror ("Socket creation failed");
      return -1;
    }
  printf ("Socket file descriptor: %d\n", sockfd);
if (bind(sockfd, (struct sockaddr *)&serverInfo, sizeof(serverInfo)) == -1) {
    perror("Bind failed");
    pclose(sockfd);
    return -1;

}
printf("Bind successful\n");
  return 0;
}